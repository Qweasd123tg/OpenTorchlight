"""Offline transport tests: python3 tools/decomp/test_llm_model.py."""
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import llm_model as transport


def result(stdout="", stderr="", code=0):
    return subprocess.CompletedProcess([], code, stdout, stderr)


def events(sid, text="```cpp\nint f() { return 1; }\n```", error=None):
    rows = [{"type": "step_start", "sessionID": sid},
            {"type": "reasoning", "part": {"text": "ignore"}},
            {"type": "text", "part": {"text": text}, "sessionID": sid},
            {"type": "step_finish", "part": {"tokens": {"input": 2}, "cost": 0}}]
    if error:
        rows.append({"type": "error", "error": {"message": error}})
    return "\n".join(map(json.dumps, rows))


class TransportTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="llm-model-test-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for name, value in (("ROOT", self.root), ("AGENT_DIR", self.root / "agent")):
            p = patch.object(transport, name, value)
            p.start()
            self.addCleanup(p.stop)
        self.sleep = patch.object(transport.time, "sleep").start()
        self.addCleanup(patch.stopall)

    def model(self, **kwargs):
        return transport.Model("explicit/model#variant", self.root / "logs", **kwargs)

    def available(self):
        info = dict(transport.CONFIG["agents"][transport.AGENT_ID])
        info["permissions"] = [{"action": "read", "resource": "*", "effect": "allow"},
                               transport.DENY, {"action": "browser", "resource": "*", "effect": "deny"}]
        return result(json.dumps({"data": info}))

    def logs(self):
        return [json.loads(line) for line in (self.root / "logs" / "calls.jsonl").read_text().splitlines()]

    def test_stdin_success_and_session(self):
        m = self.model()
        prompt = "x" * 300000
        def run(command, **kwargs):
            if command[1] == "api":
                self.assertIn("x-opencode-directory:" + str(transport.AGENT_DIR), command)
                return self.available()
            self.assertNotIn(prompt, command)
            self.assertEqual(kwargs["input"], prompt)
            self.assertEqual(kwargs["timeout"], 180)
            self.assertEqual(kwargs["env"]["PWD"], str(transport.AGENT_DIR))
            self.assertNotIn("--standalone", command)
            self.assertEqual(command[command.index("-m") + 1], m.model)
            return result(events(command[-1]))
        with patch.object(transport.subprocess, "run", side_effect=run):
            code, sid = m.ask(prompt, tag="large")
        self.assertEqual(code, "int f() { return 1; }")
        self.assertTrue(sid.startswith("ses_"))
        self.assertEqual(m.sent, len(prompt))
        self.assertEqual(len(self.logs()), 1)
        self.assertEqual(self.logs()[0]["status"], "ok")
        self.assertTrue(Path(self.logs()[0]["raw"]).joinpath("stdout.txt").exists())

    def test_profile_has_no_forced_summary_step_limit(self):
        profile = transport.CONFIG["agents"][transport.AGENT_ID]
        self.assertNotIn("steps", profile)
        self.assertEqual([transport.DENY], profile["permissions"])
        self.assertEqual([transport.DENY], transport.CONFIG["permissions"])

    def test_step_limited_profile_is_not_used(self):
        m = self.model(timeout=3)
        info = dict(transport.CONFIG["agents"][transport.AGENT_ID], steps=1)
        with patch.object(m, "_run", return_value=result(json.dumps({"data": info}))):
            with patch.object(transport.time, "monotonic", side_effect=[0, 0, 0, 3, 3]):
                self.assertIn("configuration does not match", m._available())

    def test_transient_retry_and_counters(self):
        m = self.model(retries=2)
        count = 0
        def run(command, **kwargs):
            nonlocal count
            if command[1] == "api":
                return self.available()
            count += 1
            return result(events(command[-1], "", "HTTP 429 rate limit"), code=1) if count < 3 else result(events(command[-1]))
        with patch.object(transport.subprocess, "run", side_effect=run):
            code, sid = m.ask("abc", session="ses_existing")
        self.assertTrue(code)
        self.assertEqual(sid, "ses_existing")
        self.assertEqual(m.sent, 9)
        self.assertEqual([r["status"] for r in self.logs()], ["transient", "transient", "ok"])
        self.assertEqual(self.sleep.call_count, 2)

    def test_permanent_errors_stop(self):
        for message, kind in (("Unauthorized HTTP 401", "authentication"),
                              ("ModelNotFoundError unknown model", "invalid_model"),
                              ("CERT_HAS_EXPIRED certificate", "certificate"),
                              ("unexpected CLI failure", "cli_error")):
            with self.subTest(message=message):
                m = self.model()
                m._ready = True
                with patch.object(transport.subprocess, "run", return_value=result(stderr=message, code=1)) as run:
                    self.assertEqual(m.ask("abc")[0], "")
                self.assertEqual(run.call_count, 1)
                self.assertEqual(self.logs()[-1]["status"], kind)

    def test_invalid_output_is_not_retried(self):
        for text in ("", "int f();", "```cpp\n\n```", "prose\n```cpp\nint f();\n```",
                     "```cpp\nint f();\n```\n```cpp\nint g();\n```"):
            m = self.model()
            m._ready = True
            with patch.object(transport.subprocess, "run", side_effect=lambda cmd, **kw: result(events(cmd[-1], text))) as run:
                code, _ = m.ask("abc")
            self.assertEqual(code, "")
            self.assertEqual(run.call_count, 1)
            self.assertEqual(self.logs()[-1]["status"], "invalid_answer")

    def test_timeout_partial_bytes_and_child_cancellation(self):
        m = self.model(timeout=.5)
        m._ready = True
        def run(command, **kwargs):
            if command[1] == "run":
                raise subprocess.TimeoutExpired(command, .5, output=events("ses_child").encode(), stderr=b"partial stderr")
            self.assertEqual(command[1:], ["api", "post", "/api/session/ses_child/interrupt"])
            return result('{"interrupted":true}')
        with patch.object(transport.subprocess, "run", side_effect=run) as runner:
            code, sid = m.ask("abc", session="ses_child")
        self.assertEqual((code, sid), ("", "ses_child"))
        self.assertEqual(runner.call_count, 2)
        record = self.logs()[-1]
        self.assertEqual(record["status"], "timeout")
        self.assertEqual(Path(record["raw"]).joinpath("stderr.txt").read_text(), "partial stderr")
        self.assertGreater(m.received, 0)

    def test_native_events_and_malformed_json(self):
        output = '\n'.join(['noise', '[]', '{bad', json.dumps({"type": "session.text.delta", "data": {"delta": "do not duplicate"}}),
            json.dumps({"type": "session.text.ended", "data": {"sessionID": "ses_child", "text": "```cpp\nint x;\n```"}})])
        self.assertEqual(transport._parse(output, None)[:2], ("```cpp\nint x;\n```", "ses_child"))

    def test_concurrent_calls(self):
        m = self.model()
        def run(command, **kwargs):
            if command[1] == "api":
                return self.available()
            return result(events(command[-1]))
        with patch.object(transport.subprocess, "run", side_effect=run):
            with ThreadPoolExecutor(max_workers=8) as pool:
                answers = list(pool.map(lambda i: m.ask("abc", tag=str(i)), range(32)))
        self.assertTrue(all(code for code, _ in answers))
        self.assertEqual(len({sid for _, sid in answers}), 32)
        self.assertEqual(m.sent, 96)
        rows = self.logs()
        self.assertEqual(len(rows), 32)
        self.assertEqual(len({r["raw"] for r in rows}), 32)
        self.assertEqual(rows[-1]["received"], m.received)

    def test_agent_poll_not_fixed_sleep(self):
        m = self.model()
        with patch.object(m, "_run", side_effect=[result(code=1), self.available()]):
            self.assertEqual(m._available(), "")
        self.sleep.assert_called_once_with(1)

    def test_missing_executable_logged(self):
        m = self.model()
        with patch.object(transport.subprocess, "run", side_effect=FileNotFoundError("opencode not installed")):
            self.assertEqual(m.ask("abc")[0], "")
        self.assertEqual(self.logs()[-1]["sent_chars"], 0)
        self.assertIn("not installed", self.logs()[-1]["errors"][0])

    def test_transient_exhaustion(self):
        m = self.model(retries=1)
        m._ready = True
        with patch.object(transport.subprocess, "run", return_value=result(stderr="HTTP 503 unavailable", code=1)) as run:
            self.assertEqual(m.ask("abc")[0], "")
        self.assertEqual(run.call_count, 2)
        self.assertEqual(m.sent, 6)

    def test_encoded_cli_model_error(self):
        m = self.model()
        m._ready = True
        with patch.object(transport.subprocess, "run", return_value=result(
                json.dumps({"_tag": "ModelNotFoundError", "message": "bad selection"}),
                "HTTP 404 Not Found", 1)) as run:
            self.assertEqual(m.ask("abc")[0], "")
        self.assertEqual(run.call_count, 1)
        self.assertEqual(self.logs()[-1]["status"], "invalid_model")

    def test_cancellation_failure_does_not_retry(self):
        m = self.model()
        m._ready = True
        with patch.object(transport.subprocess, "run", side_effect=[
                subprocess.TimeoutExpired("run", 180), subprocess.TimeoutExpired("interrupt", 5)]) as run:
            self.assertEqual(m.ask("abc")[0], "")
        self.assertEqual(run.call_count, 2)
        self.assertIn("error", self.logs()[-1]["cancellation"])

    def test_availability_auth_stops_without_generation(self):
        m = self.model()
        with patch.object(transport.subprocess, "run", return_value=result(stderr="401 unauthorized", code=1)) as run:
            self.assertEqual(m.ask("abc")[0], "")
        self.assertEqual(run.call_count, 1)
        self.assertEqual(m.sent, 0)
        self.assertEqual(self.logs()[-1]["status"], "agent_unavailable")

    def test_availability_deadline(self):
        m = self.model(timeout=3)
        with patch.object(m, "_run", return_value=result(stderr="not ready", code=1)) as run:
            with patch.object(transport.time, "monotonic", side_effect=[0, 0, 0, 3, 3]):
                self.assertIn("agent unavailable", m._available())
        self.assertEqual(run.call_count, 1)

    def test_no_default_model_fallback(self):
        for model in ("", "auto", "provider/", "provider/model#"):
            with self.assertRaises(ValueError):
                transport.Model(model, self.root / "logs")

    def test_errors_are_separate_for_each_parallel_session(self):
        model = self.model()
        model._ready = True
        def run(command, **kwargs):
            sid = command[-1]
            return result(stderr="Unauthorized HTTP 401", code=1) if sid == "ses_bad" else result(events(sid))
        with patch.object(transport.subprocess, "run", side_effect=run):
            with ThreadPoolExecutor(max_workers=2) as pool:
                answers = list(pool.map(lambda sid: model.ask("abc", session=sid), ("ses_good", "ses_bad")))
        self.assertTrue(answers[0][0])
        self.assertIsNone(model.error_for("ses_good"))
        self.assertIn("authentication", model.error_for("ses_bad"))


if __name__ == "__main__":
    unittest.main()
