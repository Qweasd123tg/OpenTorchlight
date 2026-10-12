#!/usr/bin/env python3
"""Compile and accept a deterministic full-TU candidate without model calls.

    python3 tools/decomp/candidate.py T.cpp --input candidate/T.cpp
    python3 tools/decomp/candidate.py T.cpp --provider trial

Diagnostics and rejected bodies stay in build-decomp/attempts. --publish
requires final MATCH for all definitions, followed by the whole headless suite.
Trial builds with permissive flags are never acceptance evidence.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re

import elfdb
import evidence
import objdiff
import promote
import publication
import acceptance
import toolchain

POLICY_VERSION = 2


def failure_class(message):
    """Stable cause groups for repairing shared rules instead of paying per body."""
    lines = [line for line in message.splitlines() if "error:" in line]
    normalized = re.sub(r"(?:/[^\s:]+)+:\d+(?::\d+)?", "<source>", "\n".join(lines) or message)
    normalized = re.sub(r"\b(?:param_|local_|uVar|iVar|pVar)\w*\b", "<temporary>", normalized)
    return hashlib.sha256(normalized.encode()).hexdigest()[:16], normalized


def evaluate(tu, source, publish=False, root=elfdb.ROOT, stage=None, incremental=False, retries=1):
    db = elfdb.load_db()
    if tu not in {t["name"] for t in db["tus"] if t["kind"] == "game"}:
        raise ValueError(f"unknown game TU: {tu}")
    candidate = Path(source).read_bytes()
    inputs = evidence.input_digest(db)
    proposal = json.dumps(publication.tree_state(stage.path), sort_keys=True).encode() if stage else b""
    policy = json.dumps({"version": POLICY_VERSION, "incremental": bool(incremental)}, sort_keys=True).encode()
    key = hashlib.sha256(tu.encode() + b"\0" + candidate + inputs.encode() + proposal + policy).hexdigest()
    failures = root / "build-decomp/candidate-failures"
    failures.mkdir(parents=True, exist_ok=True)
    cached = failures / f"{key}.json"
    if cached.exists():
        result = json.loads(cached.read_text())
        result["cached_failure"] = True
        return result
    stage = stage or publication.Stage(root)
    target = stage.path / "decomp/src" / tu
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(candidate)
    result = {"schema": 2, "policy": POLICY_VERSION, "incremental": bool(incremental),
              "tu": tu, "provider": "deterministic", "attempt": str(stage.path),
              "input_digest": inputs, "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
              "published": False}
    try:
        with stage.activate():
            os.environ["OTL_EXTRA_INCLUDE"] = str(stage.path / "build-decomp/include-gen")
            original = objdiff.Original(db=db)
            diagnostic = objdiff.compare_source(target, original, quiet=True)
            promote.promote(target, regenerate=False)
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            final = objdiff.compare_source(target, original, quiet=True)
            result.update(diagnostic_object=diagnostic["object_digest"], final_object=final["object_digest"],
                          final_object_changed=diagnostic["object_digest"] != final["object_digest"],
                          functions=final["functions"], unknown=final.get("unknown", []))
            definitions = [r for r in final["functions"] if r["status"] != "MISSING" and not r.get("weak")]
            prior = {}
            before_object = None
            if (root / "decomp/src" / tu).exists():
                # Compare the actual original context, with its actual hand headers.
                saved_root, saved_extra = os.environ.pop("OTL_INCLUDE_ROOT", None), os.environ.pop("OTL_EXTRA_INCLUDE", None)
                saved_config = toolchain.CONFIG
                try:
                    toolchain.CONFIG = root / "decomp/config.json"
                    before = objdiff.compare_source(root / "decomp/src" / tu, original, quiet=True)
                    before_object = before.get("object_digest")
                    prior = {r["address"]: r for r in before["functions"]
                             if r.get("address") and r["status"] != "MISSING" and not r.get("weak")}
                finally:
                    toolchain.CONFIG = saved_config
                    if saved_root is not None:
                        os.environ["OTL_INCLUDE_ROOT"] = saved_root
                    if saved_extra is not None:
                        os.environ["OTL_EXTRA_INCLUDE"] = saved_extra
            added = [r for r in definitions if r.get("address") not in prior]
            wanted = added if incremental else definitions
            result["new_matched"] = [r["address"] for r in added if r.get("address") and r["status"] == "MATCH"]
            remaining = {r["address"] for r in definitions if r.get("address")}
            result["missing_previous"] = sorted(set(prior) - remaining)
            preserved = preserve_existing(root / "decomp/src" / tu, target, prior, definitions, db,
                                          before_object=before_object, after_object=final.get("object_digest")) if prior else True
            needs_comparison = bool(wanted) and (not preserved or any(r["status"] != "MATCH" for r in wanted))
            # A green suite cannot compensate for dropping an existing definition.
            if result["missing_previous"]:
                result["status"] = "DIFF"
                result["reason"] = "candidate omitted existing definitions: " + ", ".join(result["missing_previous"])
            elif not definitions or (incremental and not added) or final.get("unknown"):
                result["status"] = "DIFF"
                result["reason"] = "empty/no-new definitions or unknown signature; cannot accept candidate"
            else:
                result["status"] = "MATCH"
        if result["status"] == "MATCH" and (needs_comparison or publish):
            stage.validate()
            target_unit = next(u for u in stage.final_units if Path(u["source"]).name == tu)
            result["final_object"] = target_unit["object_digest"]
            result["functions"] = target_unit["functions"]
            after = [r for r in target_unit["functions"] if r["status"] != "MISSING" and not r.get("weak")]
            wanted = [r for r in after if not incremental or r.get("address") not in prior]
            preserved = preserve_existing(root / "decomp/src" / tu, target, prior, after, db,
                                          before_object=before_object, after_object=target_unit["object_digest"],
                                          fresh_covered=stage.covered) if prior else True
            if not preserved or any(r["status"] != "MATCH" and r.get("address") not in stage.covered for r in wanted):
                result["status"] = "DIFF"
                result["reason"] = "final definitions lack preserved or freshly executed behavioral evidence"
            else:
                result["status"] = "BEHAVIORAL" if any(r["status"] != "MATCH" for r in wanted) else "MATCH"
                result["comparison_evidence"] = acceptance.comparison_bindings(db, stage.final_units, stage.report,
                                                                              stage.path, stage.validated_inputs)
        if publish and result["status"] in ("MATCH", "BEHAVIORAL"):
            if evidence.input_digest(db) != inputs:
                raise RuntimeError("inputs changed during candidate validation")
            result["files"] = stage.publish()
            result["published"] = True
    except (SystemExit, RuntimeError) as error:
        if (retries and publish and publication.tree_state(root) != stage.baseline):
            stage.rebase()
            retried = evaluate(tu, target, publish=publish, root=root, stage=stage,
                               incremental=incremental, retries=retries-1)
            retried["rebased"] = True
            return retried
        result["status"] = "ERROR"
        result["reason"] = str(error)
        result["failure_class"], result["compiler_diagnostics"] = failure_class(str(error))
    (stage.path / "result.json").write_text(json.dumps(result, indent=1, ensure_ascii=False) + "\n")
    if result["status"] == "DIFF":
        temporary = cached.with_suffix(f".{os.getpid()}.tmp")
        temporary.write_text(json.dumps(result, indent=1, ensure_ascii=False))
        os.replace(temporary, cached)
    return result


def preserve_existing(before, after, prior, definitions, db, *, before_object=None, after_object=None, fresh_covered=()):
    """Do not replace existing source bodies or change their compiler context silently."""
    import mutate
    old, new = before.read_text(), after.read_text()
    old_mask, new_mask = mutate.mask(old), mutate.mask(new)
    final = {r["address"]: r for r in definitions if r.get("address")}
    for address, row in prior.items():
        other = final.get(address)
        if not other or (row["status"] == "MATCH" and other["status"] != "MATCH"):
            if other and address in fresh_covered:
                continue
            return False
        if row["status"] != "MATCH":
            if other["status"] == "MATCH" or address in fresh_covered:
                continue
            old_object = before_object or row.get("object_digest")
            new_object = after_object or other.get("object_digest")
            if not old_object or old_object != new_object:
                return False
            if row.get("code") != other.get("code") or row.get("metadata_reasons") != other.get("metadata_reasons"):
                return False
            function = db["functions"].get(address)
            if function and function.get("kind") == "compiler":
                continue  # no source definition; identical normalized code/data and metadata above
            a = mutate.definition(old, old_mask, function) if function else None
            b = mutate.definition(new, new_mask, function) if function else None
            if not a or not b or old[a[0]:a[1] + 1] != new[b[0]:b[1] + 1]:
                return False
    return True


def _comparison_frames(report, names):
    """Bind diagnostics to loader frames, not the freely chosen Coverage label.

    Repeated rows are retained individually; neither aliases nor counts are inferred.
    Framing is operational evidence only and does not change canonical acceptance.
    """
    active, seen, finished, coverage = None, set(), [], []
    for line in report:
        begin = re.fullmatch(r'tlhybrid: begin (\w+)', line)
        end = re.fullmatch(r'tlhybrid: (\w+)\s+(PASS|FAIL) \((-?\d+)\)', line)
        row = re.fullmatch(r'\s+coverage ([^\r\n]+?) (0x[0-9a-f]+) completed (\d+) different (\d+) incomplete (\d+)', line)
        if begin:
            name = begin[1]
            if active is not None or name not in names or name in seen:
                raise ValueError('unknown, nested or duplicated test begin: ' + name)
            active = name
            seen.add(name)
        elif end:
            if active is None or end[1] != active:
                raise ValueError('unmatched or duplicated test verdict: ' + end[1])
            finished.append(end.groups())
            active = None
        elif row:
            if active is None:
                raise ValueError('coverage outside a test frame')
            coverage.append((active, *row.groups()))
        elif line.startswith('tlhybrid: begin ') or line.lstrip().startswith('coverage '):
            raise ValueError('malformed test/coverage record')
    if active is not None or seen != set(names) or len(finished) != len(names):
        raise ValueError('incomplete test frames')
    return finished, coverage


class Cycle:
    """Continue one prepared attempt using the existing build and publication APIs.

    The journal is operational evidence, never authority to restore Stage.validated.
    No model calls, commands, scheduler changes, automatic retries or rebases.
    """
    SCHEMA = 1

    def __init__(self, stage, spec):
        import time
        if not isinstance(spec, dict):
            raise ValueError('cycle specification must be an object')
        self.stage, self.spec = stage, json.loads(json.dumps(spec))
        self.work = stage.path / 'build-decomp/candidate-cycle'
        self.work.mkdir(parents=True, exist_ok=True)
        self.path = self.work / 'checkpoint.json'
        self.live_gate = False
        self._validate_spec()
        loaded = self.path.exists()
        self.state = json.loads(self.path.read_text()) if loaded else {
            'schema': self.SCHEMA, 'status': 'READY', 'phases': {}, 'published': False}
        if (not isinstance(self.state, dict) or self.state.get('schema') != self.SCHEMA
                or not isinstance(self.state.get('phases'), dict)):
            raise RuntimeError('invalid cycle checkpoint')
        if loaded:
            checksum = self.state.get('checkpoint_sha256')
            if checksum != self._digest({k: v for k, v in self.state.items() if k != 'checkpoint_sha256'}):
                raise RuntimeError('corrupt cycle checkpoint checksum')
            if self.state.get('identity', {}).get('spec') != self.spec:
                raise RuntimeError('cycle specification changed; refusing recovery or resume')
        self._recover_mutant()
        import autotest
        autotest.write_runtime(stage.path / "build-decomp/hybrid/autotests")
        identity = self._identity()
        if 'identity' in self.state and self.state['identity'] != identity:
            raise RuntimeError('cycle inputs changed; prepare a new attempt')
        self.state['identity'] = identity
        self.state['identity_sha256'] = self._digest(identity)
        self.state['execution'] = {key: os.environ.get(key) for key in (
            'OTL_JOBS', 'OTL_COMPARE_JOBS', 'OTL_BUILD_JOBS', 'OTL_SELFTEST_JOBS',
            'OTL_SELFTEST_SHARDS', 'OTL_SELFTEST_TIMEOUT', 'OTL_COMPILER_SLOTS', 'OTL_SELFTEST_SLOTS')}
        self.state['stage_copy'] = {'reused_existing_stage': True, 'files_copied': 0, 'bytes_copied': 0}
        self._check_phases()
        for row in self.state['phases'].values():
            for name, digest in row.get('artifacts', {}).items():
                path = self._local(name, self.work)
                if not path.is_file() or toolchain.sha256(path) != digest:
                    raise RuntimeError('missing or corrupt cycle artifact: ' + name)
        # A saved success cannot re-create the in-memory publication capability.
        if 'gate' in self.state['phases'] and not self.state.get('published'):
            self.state['status'] = 'REVALIDATION_REQUIRED'
        self._save()

    @staticmethod
    def _digest(value):
        return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

    @staticmethod
    def _local(name, base):
        path = Path(name)
        if not isinstance(name, str) or path.is_absolute() or '..' in path.parts or path.as_posix() != name:
            raise ValueError('invalid relative cycle path')
        result = base / path
        if not result.resolve().is_relative_to(base.resolve()):
            raise ValueError('cycle path escapes attempt')
        return result

    def _validate_spec(self):
        s = self.spec
        if set(s) != {'schema', 'tu', 'addresses', 'focused', 'regression', 'controls'} or s['schema'] != 1:
            raise ValueError('unsupported cycle specification')
        if not isinstance(s['tu'], str) or not re.fullmatch(r'[A-Za-z0-9_.-]+\.cpp', s['tu']):
            raise ValueError('invalid TU')
        if (not isinstance(s['addresses'], list) or not s['addresses']
                or not all(isinstance(a, str) for a in s['addresses'])
                or len(set(s['addresses'])) != len(s['addresses']) or
                any(not re.fullmatch(r'0x[0-9a-f]+', a) for a in s['addresses'])):
            raise ValueError('explicit unique target addresses required')
        tests = self.stage.path / 'decomp/hybrid/tests'
        for group in ('focused', 'regression'):
            if (not isinstance(s[group], list) or not s[group]
                    or not all(isinstance(n, str) for n in s[group])
                    or len(set(s[group])) != len(s[group])):
                raise ValueError('nonempty unique ' + group + ' fixtures required')
            for name in s[group]:
                if (not re.fullmatch(r'[A-Za-z0-9_.-]+\.cpp', name)
                        or Path(name).stem == 'AutoTestRuntime' or not self._local(name, tests).is_file()):
                    raise ValueError('missing fixture: ' + name)
        names = set()
        if not isinstance(s['controls'], list) or not s['controls']:
            raise ValueError('negative controls required')
        for c in s['controls']:
            if (not isinstance(c, dict) or set(c) != {'name', 'old', 'new', 'count', 'test', 'address'}
                    or not all(isinstance(c[k], str) for k in ('name', 'old', 'new', 'test', 'address')) or
                    not re.fullmatch(r'[a-z0-9][a-z0-9-]*', c['name']) or c['name'] in names or
                    not isinstance(c['old'], str) or not c['old'] or c['old'] == c['new'] or
                    not isinstance(c['new'], str) or type(c['count']) is not int or c['count'] < 1 or
                    not re.fullmatch(r'\w+', c['test']) or c['address'] not in s['addresses']):
                raise ValueError('invalid negative control')
            names.add(c['name'])

    def _identity(self):
        import llm_loop
        stage = self.stage
        tree = publication.tree_state(stage.path)
        if publication.tree_state(stage.root) != stage.baseline:
            raise RuntimeError('live baseline changed; prepare a new attempt')
        if {n: h for n, h in tree.items() if n.startswith('tools/')} != {
                n: h for n, h in stage.baseline.items() if n.startswith('tools/')}:
            raise RuntimeError('staged tools differ from baseline')
        # activate redirects paths, not imported Python. Reject old attempts under new tools.
        runtime = Path(__file__).resolve().parent
        for name, digest in tree.items():
            if name.startswith('tools/decomp/') and toolchain.sha256(runtime / Path(name).relative_to('tools/decomp')) != digest:
                raise RuntimeError('loaded tools differ from attempt')
        packet = stage.path / 'build-decomp/llm-loop' / self.spec['tu']
        prepared = json.loads((packet / 'result.json').read_text())
        checkpoint = json.loads((packet / 'checkpoint.json').read_text())
        selected = {f['address'] for f in checkpoint['settings']['selected']}
        if not prepared.get('prepared') or prepared.get('blocked') or not set(self.spec['addresses']) <= selected:
            raise RuntimeError('matching unblocked --prepare-only packet required')
        packet_hashes = {n: toolchain.sha256(packet / n) for n in ('result.json', 'checkpoint.json')}
        for address in self.spec['addresses']:
            prompt = packet / 'prompts' / (address + '.md')
            if not prompt.is_file() or not prompt.stat().st_size:
                raise RuntimeError('missing prepared prompt: ' + address)
            packet_hashes['prompts/' + prompt.name] = toolchain.sha256(prompt)
        with stage.activate():
            context = llm_loop.packet_inputs(stage.path)
        if checkpoint.get('inputs') != context:
            raise RuntimeError('prepared context changed; prepare a new attempt')
        # The worker supplies this TU and fixtures; changed headers/tools need fresh packets.
        stable = lambda t: {n: h for n, h in t.items()
                            if n != 'decomp/src/' + self.spec['tu']
                            and not n.startswith('decomp/hybrid/tests/')}
        if stable(checkpoint.get('tree', {})) != stable(tree):
            raise RuntimeError('prepared source/header/tool context changed')
        return {'spec': self.spec, 'tree': tree, 'baseline': stage.baseline,
                'inputs': stage._input_digest(), 'packet': packet_hashes, 'context': context,
                'generated': stage._generated_tests_state()}

    def _check_phases(self):
        order = ['compare', 'focused'] + ['control-' + c['name'] for c in self.spec['controls']] + ['regression', 'gate']
        phases = self.state['phases']
        if set(phases) != set(order[:len(phases)]):
            raise RuntimeError('invalid or out-of-order cycle phases')
        for index, name in enumerate(order[:len(phases)]):
            row = phases[name]
            if (not isinstance(row, dict) or row.get('status') not in ('RUNNING', 'PASS', 'FAIL')
                    or not isinstance(row.get('artifacts', {}), dict)):
                raise RuntimeError('invalid phase state: ' + name)
            if row['status'] != 'PASS' and index != len(phases) - 1:
                raise RuntimeError('cycle continued after incomplete phase: ' + name)
            required = {name + '.json'} if name in ('compare', 'gate') else {name + '.json', name + '.log'}
            if row['status'] == 'PASS' and not required <= set(row.get('artifacts', {})):
                raise RuntimeError('missing successful phase receipts: ' + name)

    def _save(self):
        self.state['checkpoint_sha256'] = self._digest({k: v for k, v in self.state.items() if k != 'checkpoint_sha256'})
        publication._replace_file(self.work, self.path.name,
                                  json.dumps(self.state, indent=2, sort_keys=True).encode())

    def _artifact(self, name, data):
        data = data if isinstance(data, bytes) else json.dumps(data, sort_keys=True, indent=2).encode()
        publication._replace_file(self.work, name, data)
        return {name: hashlib.sha256(data).hexdigest()}

    def _recover_mutant(self):
        mutation = self.state.get('mutation')
        if not mutation:
            return
        name = 'decomp/src/' + self.spec['tu']
        if (mutation.get('identity_sha256') != self.state.get('identity_sha256')
                or mutation.get('source') != name
                or mutation.get('golden') != self.state.get('identity', {}).get('tree', {}).get(name)
                or mutation.get('backup') != 'golden-source.bin'):
            raise RuntimeError('mutant journal does not match saved source identity')
        source = self._local(name, self.stage.path)
        backup = self._local(mutation['backup'], self.work)
        if toolchain.sha256(backup) != mutation['golden']:
            raise RuntimeError('corrupt mutant recovery backup; manual repair required')
        if toolchain.sha256(source) not in (mutation['golden'], mutation['mutant']):
            raise RuntimeError('source changed during mutant recovery; manual repair required')
        publication._replace_file(source.parent, source.name, backup.read_bytes())
        self.state.pop('mutation')
        self._save()

    def _step(self, name, action):
        import time
        old = self.state['phases'].get(name)
        if old and old.get('status') == 'PASS':
            return
        if old:
            raise RuntimeError('interrupted or failed phase requires diagnosis: ' + name)
        row = self.state['phases'][name] = {'status': 'RUNNING'}
        self.state['status'] = 'RUNNING'
        self.state['phase'] = name
        self._save()
        start = time.monotonic()
        compiler, cache = toolchain.compiler_stats(), toolchain.shared_cache_stats()
        try:
            row.update(action() or {})
            row['status'] = 'PASS'
        except BaseException as error:
            row.update(status='FAIL', error=str(error), error_type=type(error).__name__)
            try:
                row.setdefault('artifacts', {}).update(self._artifact(name + '-error.log', str(error).encode()))
            except OSError:
                pass
            self.state['status'] = 'STOPPED'
            raise
        finally:
            row['seconds'] = time.monotonic() - start
            # Diagnostic counters cannot invalidate successful canonical validation.
            try:
                row['compiler'] = {k: v - compiler.get(k, 0) for k, v in toolchain.compiler_stats().items()}
                row['cache'] = {k: v - cache.get(k, 0) for k, v in toolchain.shared_cache_stats().items()}
                label = 'final' if name == 'gate' else 'cycle-' + name
                for filename in ('build-timings.json', 'selftest-timing.json'):
                    timing = self.stage.path / 'build-decomp/hybrid' / label / filename
                    if timing.is_file():
                        row.setdefault('artifacts', {}).update(self._artifact(name + '-' + filename, timing.read_bytes()))
            except Exception as error:
                row['telemetry_error'] = str(error)
            self._save()

    def _compare(self):
        import difflib
        stage = self.stage
        name = 'decomp/src/' + self.spec['tu']
        before = (stage.root / name).read_text().splitlines(True) if (stage.root / name).exists() else []
        after = (stage.path / name).read_text().splitlines(True)
        artifacts = self._artifact('candidate.diff', ''.join(difflib.unified_diff(
            before, after, fromfile='a/' + name, tofile='b/' + name)).encode())
        self.state['phases']['compare']['artifacts'] = artifacts
        with stage.activate():
            os.environ.pop('OTL_EXTRA_INCLUDE', None)
            original = objdiff.Original()
            row = objdiff.compare_source(stage.path / 'decomp/src' / self.spec['tu'], original, quiet=True)
        addresses = {f.get('address') for f in row['functions'] if f['status'] not in ('MISSING', 'EXTRA')}
        artifacts.update(self._artifact('compare.json', row))
        self.state['phases']['compare']['artifacts'] = artifacts
        if row.get('unknown') or not set(self.spec['addresses']) <= addresses:
            raise RuntimeError('candidate has unknown signatures or missing targets')
        return {'artifacts': artifacts}

    def _tests(self, label, fixtures, control=None):
        import autotest
        import hybrid
        stage = self.stage
        with stage.activate():
            os.environ.pop('OTL_EXTRA_INCLUDE', None)
            tests = [stage.path / 'decomp/hybrid/tests' / n for n in fixtures]
            names = [n for p in tests for n in re.findall(r'TL_TEST\s*\(\s*(\w+)\s*\)', p.read_text())]
            if not names or len(set(names)) != len(names):
                raise RuntimeError('empty or duplicated test inventory')
            tests.append(autotest.write_runtime(stage.path / 'build-decomp/hybrid/autotests'))
            blob, loader = hybrid.build(out=stage.path / 'build-decomp/hybrid' / ('cycle-' + label),
                                        src=stage.path / 'decomp/src', tests=tests, verbose=False)
            code, report = hybrid.selftest(blob, loader)
        artifacts = self._artifact(label + '.log', ('\n'.join(report) + '\n').encode())
        framing_error = None
        try:
            finished, framed = _comparison_frames(report, names)
        except ValueError as error:
            finished, framed = [], []
            framing_error = str(error)
        complete = framing_error is None
        coverage = [row[1:] for row in framed]
        valid_rows = all(int(c) > 0 and int(d) <= int(c) and int(i) == 0
                         for _, _, _, c, d, i in framed)
        if control:
            good = (control['test'] in names and code == 1 and complete and valid_rows
                    and all(status == ('FAIL' if n == control['test'] else 'PASS')
                            and (int(count) != 0 if n == control['test'] else count == '0')
                            for n, status, count in finished)
                    and any(owner == control['test'] and n == control['test'] and a == control['address']
                            and int(c) > 0 and int(d) > 0 and int(i) == 0
                            for owner, n, a, c, d, i in framed)
                    and all(int(d) == 0 for owner, _, _, _, d, _ in framed if owner != control['test']))
        else:
            # Child labels can describe successful regression lanes, but cannot widen
            # target coverage beyond a matching registered/passed test name.
            covered = {a for owner, n, a, c, d, i in framed if owner == n
                       and int(c) > 0 and int(d) == 0 and int(i) == 0}
            good = (code == 0 and complete and valid_rows
                    and all(s == 'PASS' and c == '0' for _, s, c in finished)
                    and all(int(d) == 0 for _, _, _, _, d, _ in framed))
            if label == 'focused':
                good = good and set(self.spec['addresses']) <= covered
        row = {'code': code, 'complete': complete, 'coverage': coverage,
               'framed_coverage': framed, 'framing_error': framing_error,
               'blob_sha256': toolchain.sha256(blob), 'loader_sha256': toolchain.sha256(loader)}
        artifacts.update(self._artifact(label + '.json', row))
        # Persist failure logs before returning the concrete failure.
        self.state['phases'][self.state['phase']]['artifacts'] = artifacts
        if not good:
            raise RuntimeError(label + ': failed/incomplete comparative outcome; see ' + label + '.log')
        return {'artifacts': artifacts, 'code': code, 'complete': complete}

    def _control(self, control):
        source = self.stage.path / 'decomp/src' / self.spec['tu']
        golden = source.read_bytes()
        text = golden.decode('utf-8')
        if text.count(control['old']) != control['count']:
            raise RuntimeError('negative control replacement count mismatch: ' + control['name'])
        mutant = text.replace(control['old'], control['new']).encode()
        backup = 'golden-source.bin'
        self._artifact(backup, golden)
        self.state['mutation'] = {'backup': backup, 'source': 'decomp/src/' + self.spec['tu'],
                                  'identity_sha256': self.state['identity_sha256'],
                                  'golden': hashlib.sha256(golden).hexdigest(),
                                  'mutant': hashlib.sha256(mutant).hexdigest()}
        self._save()
        try:
            publication._replace_file(source.parent, source.name, mutant)
            return self._tests('control-' + control['name'], self.spec['focused'], control)
        finally:
            if toolchain.sha256(source) not in (hashlib.sha256(golden).hexdigest(), hashlib.sha256(mutant).hexdigest()):
                raise RuntimeError('source changed during control; journal retained for manual recovery')
            publication._replace_file(source.parent, source.name, golden)
            if toolchain.sha256(source) != hashlib.sha256(golden).hexdigest():
                raise RuntimeError('mutant cleanup failed')
            self.state.pop('mutation', None)
            self._save()

    def _gate(self):
        self.stage.validate()  # The single unchanged canonical gate.
        self.live_gate = True  # Set before optional report/accounting work.
        return self._gate_receipt()

    def _gate_receipt(self):
        return {'artifacts': self._artifact('gate.json', {
            'inputs': self.stage.validated_inputs, 'tree': self.stage.validated,
            'objects': self.stage.final_objects, 'fixtures': self.stage.validated_fixtures,
            'report': self.stage.report, 'covered': sorted(self.stage.covered),
            'units': self.stage.final_units, 'baseline_units': self.stage.baseline_units})}

    def run(self, allow_gate=False):
        if self.state['status'] in ('STOPPED', 'REVALIDATION_REQUIRED', 'PUBLISHED', 'CANCELLED',
                                    'PUBLICATION_FAILED', 'PUBLISHED_RECEIPT_ERROR'):
            return self.state
        try:
            self._step('compare', self._compare)
            self._step('focused', lambda: self._tests('focused', self.spec['focused']))
            for control in self.spec['controls']:
                self._step('control-' + control['name'], lambda c=control: self._control(c))
            self._step('regression', lambda: self._tests('regression', self.spec['regression']))
            self.state['phase'] = 'input-verification'
            if self._identity() != self.state['identity']:
                raise RuntimeError('cycle inputs changed during checks')
            if allow_gate:
                self._step('gate', self._gate)
                self.state['status'] = 'AWAITING_RELEASE'
            else:
                self.state['status'] = 'READY_FOR_GATE'
            self._save()
        except BaseException as error:
            self.state.update(status='RECEIPT_ERROR' if self.live_gate else 'STOPPED', error=str(error))
            try:
                self._save()
            except OSError:
                pass
            if isinstance(error, KeyboardInterrupt):
                raise
        return self.state

    def persist_gate_receipt(self):
        # Safe persistence retry retains the same completed validation; no build rerun.
        if not self.live_gate or self.state['status'] != 'RECEIPT_ERROR':
            raise RuntimeError('no live validated receipt to persist')
        row = self.state['phases']['gate']
        row.update(self._gate_receipt())
        row['status'] = 'PASS'
        row.pop('error', None)
        row.pop('error_type', None)
        self.state.pop('error', None)
        self.state['status'] = 'AWAITING_RELEASE'
        self._save()

    def release(self, request):
        """Called only with an explicit existing release; never reconstruct validation."""
        if (not self.state.get('published') and self.state['status'] in ('AWAITING_RELEASE', 'RECEIPT_ERROR', 'PUBLICATION_FAILED')
                and request == {'action': 'cancel', 'identity_sha256': self.state['identity_sha256']}):
            self.state['status'] = 'CANCELLED'
            self._save()
            return self.state
        expected = {'action': 'publish', 'identity_sha256': self.state['identity_sha256'],
                    'inputs_digest': self.stage.validated_inputs if self.live_gate else None}
        if request != expected or not self.live_gate or self.state['status'] != 'AWAITING_RELEASE':
            raise RuntimeError('exact release and live canonical validation required')
        try:
            changed = self.stage.publish()  # Same live Stage. No validate(), rebase(), or retry.
        except (Exception, SystemExit) as error:
            # publish() can fail during cleanup after its committed marker. Do not
            # infer rollback or repeat a possibly completed publication.
            self.state.update(status='PUBLICATION_FAILED', published=None,
                              publication_outcome='unknown; verify existing publication journal and live tree',
                              error=str(error))
            try:
                self._save()
            except OSError:
                pass
            raise RuntimeError('publication stopped; live Stage retained: ' + str(error)) from error
        self.state.update(status='PUBLISHED', published=True, files=changed)
        try:
            self._save()
        except OSError as error:
            self.state.update(status='PUBLISHED_RECEIPT_ERROR', error=str(error))
            raise
        return self.state

    def summary(self):
        summary = {k: self.state[k] for k in ('status', 'phase', 'identity_sha256', 'published', 'publication_outcome', 'error')
                   if k in self.state}
        packet = self.stage.path / 'build-decomp/llm-loop' / self.spec['tu']
        summary.update(checkpoint=str(self.path), prepared_packet=str(packet / 'result.json'),
                       prompts=str(packet / 'prompts'), source=str(self.stage.path / 'decomp/src' / self.spec['tu']))
        summary['phases'] = {name: {'status': row['status'], 'seconds': row.get('seconds')}
                             for name, row in self.state['phases'].items()}
        row = self.state['phases'].get(self.state.get('phase'), {})
        summary['evidence'] = [str(self.work / n) for n in sorted(row.get('artifacts', {}))]
        summary['failure_package'] = {'minimized_seed': None, 'automatic_minimization': False,
                                      'input_identity_sha256': self.state['identity_sha256'],
                                      'candidate_diff': str(self.work / 'candidate.diff')
                                      if (self.work / 'candidate.diff').is_file() else None}
        if 'error' in summary:
            summary['error'] = summary['error'][:2000]
        return summary


def continue_cycle(tu, attempt, spec_path, gate=False, release_request=None):
    """CLI adapter; retain validated Stage while polling an explicit release file."""
    import fcntl
    import time
    import parallel
    if not re.fullmatch(r'[A-Za-z0-9_.-]+\.cpp', tu):
        raise ValueError('invalid TU')
    if owner := parallel.owned_by_others(tu):
        raise RuntimeError(tu + ' belongs to ' + owner + '; set OTL_OWNER')
    if gate and release_request is None:
        raise ValueError('--gate requires --release-request to retain live validated Stage')
    spec = json.loads(spec_path.read_text())
    if not isinstance(spec, dict) or spec.get('tu') != tu:
        raise ValueError('cycle spec TU mismatch')
    stage = publication.Stage.resume(attempt, root=elfdb.ROOT)
    locks = stage.root / 'build-decomp/llm-loop-locks'
    locks.mkdir(parents=True, exist_ok=True)
    with (locks / (tu + '.lock')).open('a+') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        cycle = Cycle(stage, spec)
        cycle.run(allow_gate=gate)
        try:
            print(json.dumps(cycle.summary()), flush=True)
        except BrokenPipeError:
            pass
        seen_request, last_error = None, None
        retry_at, retry_delay = 0.0, 1.0
        def notice(error):
            nonlocal last_error
            message = str(error)
            if message != last_error:
                last_error = message
                try:
                    print(json.dumps({'status': cycle.state['status'], 'release_error': message}), flush=True)
                except BrokenPipeError:
                    pass
        while cycle.live_gate and cycle.state['status'] in ('AWAITING_RELEASE', 'RECEIPT_ERROR', 'PUBLICATION_FAILED'):
            try:
                # Cancellation has priority even if disk exhaustion blocks optional receipts.
                try:
                    raw = release_request.read_bytes() if release_request.exists() else None
                    request = json.loads(raw) if raw is not None else None
                except (OSError, ValueError) as error:
                    notice(error)
                    raw, request = None, None
                if request == {'action': 'cancel', 'identity_sha256': cycle.state['identity_sha256']}:
                    cycle.release(request)
                    break
                if cycle.state['status'] == 'RECEIPT_ERROR' and time.monotonic() >= retry_at:
                    retry_at = time.monotonic() + retry_delay
                    retry_delay = min(60.0, retry_delay * 2)
                    cycle.persist_gate_receipt()
                    try:
                        print(json.dumps(cycle.summary()), flush=True)
                    except BrokenPipeError:
                        pass
                if raw is not None and raw != seen_request and cycle.state['status'] == 'AWAITING_RELEASE':
                    seen_request = raw
                    cycle.release(request)
                    break
            except (OSError, ValueError, RuntimeError) as error:
                # Neither persistence nor a malformed release destroys live validation.
                notice(error)
            time.sleep(1)
        return cycle.summary()


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tu")
    parser.add_argument("--input", type=Path)
    parser.add_argument("--provider", choices=("trial",), help="use the converted TU from draft_trial.py")
    parser.add_argument("--publish", action="store_true")
    parser.add_argument("--cycle-spec", type=Path, help="continue an existing prepared Stage without model calls")
    parser.add_argument("--attempt", type=Path)
    parser.add_argument("--gate", action="store_true", help="run the canonical gate once, after scheduler admission")
    parser.add_argument("--release-request", type=Path, help="wait for an exact publish/cancel request, retaining live Stage")
    args = parser.parse_args()
    if args.cycle_spec:
        if not args.attempt or args.input or args.provider or args.publish:
            parser.error("--cycle-spec requires --attempt; do not combine with provider or --publish")
        try:
            result = continue_cycle(args.tu, args.attempt, args.cycle_spec, args.gate, args.release_request)
        except (ValueError, RuntimeError, OSError, SystemExit) as error:
            result = {'status': 'STOPPED', 'phase': 'admission', 'error': str(error),
                      'attempt': str(args.attempt), 'published': False}
        print(json.dumps(result, sort_keys=True))
        return 0 if result["status"] in ("READY_FOR_GATE", "PUBLISHED") else 1
    if args.attempt or args.gate or args.release_request:
        parser.error("cycle options require --cycle-spec")
    if bool(args.input) == bool(args.provider):
        parser.error("choose exactly one deterministic provider: --input or --provider trial")
    import parallel
    if args.publish and (owner := parallel.owned_by_others(args.tu)):
        parser.error(f"{args.tu} belongs to {owner}; set OTL_OWNER")
    source = args.input or elfdb.ROOT / "build-decomp/trial" / args.tu
    if args.provider:
        import ghidra_draft
        state, reasons = ghidra_draft.draft_state(args.tu, elfdb.load_db())
        if state != "fresh":
            parser.error(f"draft provider unavailable ({state}): {'; '.join(reasons)}")
    result = evaluate(args.tu, source, args.publish)
    print(json.dumps(result, indent=1, ensure_ascii=False))
    return 0 if result["status"] in ("MATCH", "BEHAVIORAL") else 1


if __name__ == "__main__":
    raise SystemExit(main())
