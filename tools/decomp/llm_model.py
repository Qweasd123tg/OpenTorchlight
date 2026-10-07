"""Bounded, tools-denied OpenCode V2 transport for llm_loop.

Counters count prompt/answer characters for each transport attempt, not tokens.
Errors return ('', session_id); details are in calls.jsonl and ignored raw files.
CLI stdin and JSON record shapes were verified against the installed V2 binary;
configuration/API contracts: https://opencode.ai/v2/docs/{config,agents,api}.
"""
from __future__ import annotations

import hashlib
import json
import math
import os
from pathlib import Path
import re
import subprocess
import threading
import time
from urllib.parse import quote
import uuid

ROOT = Path(__file__).resolve().parents[2]
AGENT_ID = "otl-code-only-v2"
DENY = {"action": "*", "resource": "*", "effect": "deny"}
SYSTEM = ("Translate decompiled x86-64 code (GCC 4.4.7 -O2, Linux) back into "
          "C++98 source. Answer with exactly one fenced ```cpp code block and "
          "nothing else. Do not use tools.")
CONFIG = {"$schema": "https://opencode.ai/config.json", "default_agent": AGENT_ID,
          "permissions": [DENY], "snapshots": False, "warming": False,
          "compaction": {"auto": False}, "lsp": False, "formatter": False,
          "agents": {AGENT_ID: {"description": "Code only, no tools",
                                   "mode": "primary", "system": SYSTEM,
                                    "permissions": [DENY]}}}
CONFIG_TEXT = json.dumps(CONFIG, sort_keys=True, indent=2) + "\n"
AGENT_DIR = Path("/tmp/opencode") / ("llm-model-v2-" + hashlib.sha256(
    CONFIG_TEXT.encode()).hexdigest()[:16])
_PREPARE_LOCK = threading.Lock()
_LOG_LOCK = threading.Lock()


def _atomic(path, text):
    temporary = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    temporary.write_text(text, encoding="utf-8")
    os.replace(temporary, path)


def _string(value):
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return value or ""


def _parse(output, session):
    """CLI JSON records, plus native V2 text-ended/failure records.

    Never concatenate reasoning, tool output or native deltas with final text.
    """
    texts, errors, usage = [], [], []
    for line in output.splitlines():
        try:
            event = json.loads(line)
        except ValueError:
            continue
        if not isinstance(event, dict):
            continue
        data = event.get("data")
        data = data if isinstance(data, dict) else {}
        session = event.get("sessionID") or data.get("sessionID") or session
        kind = event.get("type")
        part = event.get("part")
        part = part if isinstance(part, dict) else {}
        if isinstance(event.get("_tag"), str) and event["_tag"].endswith("Error"):
            errors.append(json.dumps(event, ensure_ascii=False))
        elif kind == "text" and isinstance(part.get("text"), str):
            texts.append(part["text"])
        elif kind == "session.text.ended" and isinstance(data.get("text"), str):
            texts.append(data["text"])
        elif kind in ("error", "session.step.failed", "session.execution.failed"):
            errors.append(json.dumps(event.get("error", data.get("error", event)),
                                     ensure_ascii=False))
        elif kind == "session.execution.interrupted":
            errors.append("session interrupted: " + str(data.get("reason", "unknown")))
        elif kind == "step_finish":
            usage.append({k: part[k] for k in ("tokens", "cost", "reason") if k in part})
    return "".join(texts), session, errors, usage


def _failure_kind(message):
    text = message.lower()
    if any(s in text for s in ("certificate", "cert_", "self signed", "tls", "ssl")):
        return "certificate"
    if any(s in text for s in ("unauthorized", "authentication", "invalid api key",
                               "missing api key", "needs_auth", "401", "403", "credential")):
        return "authentication"
    if any(s in text for s in ("modelnotfound", "model not found", "invalid model",
                               "unknown model", "providernotfound", "provider not found")):
        return "invalid_model"
    if any(s in text for s in ("429", "rate limit", "rate_limit", "too many requests",
                               "unavailable", "overloaded", "502", "503", "504",
                               "econnreset", "econnrefused", "temporarily", "connection reset")):
        return "transient"
    return "cli_error"


class Model:
    def __init__(self, model, log, timeout=180, retries=2):
        if not isinstance(model, str) or not re.fullmatch(r"[^/#\s]+/[^#\s]+(?:#[^#\s]+)?", model):
            raise ValueError("an explicit provider/model#variant reference is required")
        if not math.isfinite(timeout) or timeout <= 0 or not isinstance(retries, int) or retries < 0:
            raise ValueError("timeout must be positive and finite; retries a nonnegative integer")
        self.model, self.log = model, Path(log)
        self.timeout, self.retries = timeout, retries
        self.sent = self.received = 0
        self._lock = threading.Lock()
        self._sessions = {}
        self._errors = {}
        self._ready = False
        self.log.mkdir(parents=True, exist_ok=True)
        self.raw = ROOT / "build-decomp" / "llm-model" / uuid.uuid4().hex
        self.raw.mkdir(parents=True, exist_ok=True)
        with _PREPARE_LOCK:
            AGENT_DIR.mkdir(parents=True, exist_ok=True)
            config = AGENT_DIR / "opencode.json"
            if not config.exists() or config.read_text() != CONFIG_TEXT:
                _atomic(config, CONFIG_TEXT)
        self.env = dict(os.environ, PWD=str(AGENT_DIR))

    def _run(self, command, **kwargs):
        return subprocess.run(["opencode"] + command, cwd=AGENT_DIR, env=self.env,
                              capture_output=True, text=True, encoding="utf-8",
                              errors="replace", **kwargs)

    def _available(self):
        # Installed V2 uses this location header; its deepObject query is not decoded.
        path = "/api/agent/" + AGENT_ID
        deadline = time.monotonic() + min(30, self.timeout)
        cause = "agent not yet registered"
        while time.monotonic() < deadline:
            try:
                result = self._run(["api", "get", path, "--header",
                                    "x-opencode-directory:" + str(AGENT_DIR)],
                                   timeout=min(5, max(.1, deadline - time.monotonic())))
                if result.returncode == 0:
                    info = json.loads(result.stdout).get("data", {})
                    rules = info.get("permissions", [])
                    deny_index = max((i for i, rule in enumerate(rules) if rule == DENY), default=-1)
                    if (info.get("system") == SYSTEM and info.get("mode") == "primary"
                            and info.get("steps") is None and deny_index >= 0
                            and all(rule.get("effect") == "deny" for rule in rules[deny_index:])):
                        return ""
                    cause = "agent configuration does not match deny-all profile"
                else:
                    cause = result.stderr or result.stdout or "agent query failed"
                    if _failure_kind(cause) in ("authentication", "certificate", "invalid_model"):
                        break
            except (ValueError, subprocess.TimeoutExpired, OSError) as error:
                cause = str(error)
                if isinstance(error, FileNotFoundError):
                    break
            remaining = deadline - time.monotonic()
            if remaining > 0:
                time.sleep(min(1, remaining))
        return "agent unavailable: " + cause[:1000]

    def _record(self, record, directory, stdout, stderr, sent=0, received=0):
        _atomic(directory / "stdout.txt", stdout)
        _atomic(directory / "stderr.txt", stderr)
        with self._lock, _LOG_LOCK:
            self.sent += sent
            self.received += received
            record.update(sent=self.sent, received=self.received,
                          sent_chars=sent, received_chars=received,
                          raw=str(directory))
            _atomic(directory / "attempt.json", json.dumps(record, ensure_ascii=False) + "\n")
            with (self.log / "calls.jsonl").open("a", encoding="utf-8") as stream:
                stream.write(json.dumps(record, ensure_ascii=False) + "\n")

    def ask(self, prompt, session=None, tag=""):
        """Return (full fenced C++ block contents or '', session ID).

        retries is the number of additional attempts, only for transient failures.
        Timeouts/invalid answers are terminal to avoid duplicate paid requests.
        """
        if session:
            with self._lock:
                lock = self._sessions.setdefault(session, threading.Lock())
            with lock:
                return self._ask(prompt, session, tag)
        return self._ask(prompt, session, tag)

    def error_for(self, session):
        """Per-session diagnostic; a shared last_error would race model workers."""
        with self._lock:
            return self._errors.get(session)

    def _ask(self, prompt, session, tag):
        call = uuid.uuid4().hex
        sid = session or "ses_" + uuid.uuid4().hex
        call_start = time.monotonic()
        with self._lock:
            readiness = "" if self._ready else self._available()
            self._ready = not readiness
        for attempt in range(self.retries + 1):
            directory = self.raw / (call + "-" + str(attempt + 1))
            directory.mkdir()
            _atomic(directory / "prompt.txt", prompt)
            start, wall = time.monotonic(), time.time()
            record = dict(call=call, tag=tag, model=self.model, attempt=attempt + 1,
                          started=wall, session=sid, status="", errors=[], usage=[])
            stdout = stderr = text = code = ""
            returncode = None
            sent = 0
            status = "agent_unavailable" if readiness else ""
            errors = [readiness] if readiness else []
            if not readiness:
                command = ["run", "--agent", AGENT_ID, "-m", self.model,
                           "--format", "json", "--title", "OpenTorchlight code-only",
                           "--session", sid]
                sent = len(prompt)
                try:
                    result = self._run(command, input=prompt, timeout=self.timeout)
                    stdout, stderr, returncode = result.stdout, result.stderr, result.returncode
                except subprocess.TimeoutExpired as error:
                    stdout, stderr = _string(error.stdout), _string(error.stderr)
                    status = "timeout"
                    errors.append("model call exceeded %.3fs" % self.timeout)
                    try:
                        cancel = self._run(["api", "post", "/api/session/" + quote(sid, safe="")
                                            + "/interrupt"], timeout=5)
                        record["cancellation"] = dict(returncode=cancel.returncode,
                                                      stdout=cancel.stdout, stderr=cancel.stderr)
                    except (subprocess.TimeoutExpired, OSError) as cancel_error:
                        record["cancellation"] = {"error": str(cancel_error)}
                except OSError as error:
                    status = "cli_error"
                    errors.append(str(error))
                text, event_sid, event_errors, usage = _parse(stdout, sid)
                # The ID was selected before starting; never interrupt an ID from output.
                if event_sid != sid:
                    errors.append("CLI returned an unexpected session ID: " + str(event_sid))
                errors.extend(event_errors)
                record["usage"] = usage
                if not status:
                    if errors or returncode != 0:
                        if stderr:
                            errors.append(stderr[:2000])
                        if returncode != 0 and stdout and not event_errors:
                            errors.append(stdout[:2000])
                        if not errors:
                            errors.append("opencode exited with status " + str(returncode))
                        status = _failure_kind("\n".join(errors))
                    else:
                        match = re.fullmatch(r"\s*```(?:cpp|c\+\+)\s*\n(.*?)\n```\s*", text, re.S)
                        code = match.group(1).strip() if match else ""
                        if "```" in code:
                            code = ""
                        status = "ok" if code else "invalid_answer"
                        if not code:
                            errors.append("expected one nonempty fenced cpp block and no other text")
            record.update(status=status, errors=errors, returncode=returncode,
                          elapsed=time.monotonic() - start,
                          call_elapsed=time.monotonic() - call_start)
            self._record(record, directory, stdout, stderr, sent, len(text))
            if status != "transient" or attempt == self.retries:
                with self._lock:
                    self._errors[sid] = None if code else status + ": " + "; ".join(errors)
                return code, sid
            time.sleep(min(2 ** (attempt + 1), 8))
        return "", sid
