"""Isolated TU attempts and checked, locked publication of source and headers."""
from contextlib import contextmanager
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import tempfile

import elfdb
import toolchain


def _sync_directory(path):
    fd = os.open(path, os.O_RDONLY | os.O_DIRECTORY)
    try:
        os.fsync(fd)
    finally:
        os.close(fd)


def _write_file(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("wb") as stream:
        stream.write(data)
        stream.flush()
        os.fsync(stream.fileno())


def _replace_file(root, name, data, mode=None):
    target = root / name
    if data is None:
        target.unlink(missing_ok=True)
        if target.parent.exists():
            _sync_directory(target.parent)
        return
    target.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=".publish-", dir=target.parent)
    try:
        with os.fdopen(fd, "wb") as stream:
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(temporary, mode if mode is not None else
                 (target.stat().st_mode & 0o777 if target.exists() else 0o644))
        os.replace(temporary, target)
        _sync_directory(target.parent)
    finally:
        Path(temporary).unlink(missing_ok=True)


def _journal(root):
    return root / "build-decomp/publication-journal"


def _recover(root):
    """Caller holds the exclusive tree lock; incomplete writes are rolled back."""
    journal = _journal(root)
    if not journal.exists():
        return
    if not (journal / "committed").exists():
        manifest = json.loads((journal / "manifest.json").read_text())
        if manifest.get("schema") != 1:
            raise RuntimeError("unrecognized publication recovery journal")
        for row in manifest["files"]:
            name = row["name"]
            if not name.startswith("decomp/") or ".." in Path(name).parts:
                raise RuntimeError("invalid publication recovery path")
            data = (journal / row["backup"]).read_bytes() if row["backup"] else None
            if data is not None and hashlib.sha256(data).hexdigest() != row["sha256"]:
                raise RuntimeError("damaged publication backup; refusing a mixed tree")
            _replace_file(root, name, data, row.get("mode"))
    # Rename first: even a crash during recursive cleanup cannot leave a partial
    # journal which the next reader mistakes for an incomplete transaction.
    garbage = Path(tempfile.mkdtemp(prefix="publication-finished-", dir=journal.parent))
    garbage.rmdir()
    os.replace(journal, garbage)
    _sync_directory(garbage.parent)
    shutil.rmtree(garbage)


@contextmanager
def tree_lock(root=elfdb.ROOT, exclusive=False):
    root = Path(root)
    path = root / "build-decomp" / "publication.lock"
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a+") as stream:
        fcntl.flock(stream, fcntl.LOCK_EX if exclusive else fcntl.LOCK_SH)
        try:
            if exclusive:
                _recover(root)
            elif _journal(root).exists():
                fcntl.flock(stream, fcntl.LOCK_UN)
                fcntl.flock(stream, fcntl.LOCK_EX)
                _recover(root)
                fcntl.flock(stream, fcntl.LOCK_SH)
            yield
        finally:
            fcntl.flock(stream, fcntl.LOCK_UN)


def tree_state(root):
    """All staged validation materials, including tests, configuration and tools."""
    root = Path(root)
    return {p.relative_to(root).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
            for base in (root / "decomp", root / "tools/decomp")
            for p in sorted(base.rglob("*")) if p.is_file() and "__pycache__" not in p.parts
            and not p.name.startswith(".publish-")}


class Stage:
    def __init__(self, root=elfdb.ROOT):
        root = self.root = Path(root)
        work = root / "build-decomp" / "attempts"
        work.mkdir(parents=True, exist_ok=True)
        self.path = Path(tempfile.mkdtemp(prefix="tu-", dir=work))
        with tree_lock(root):
            self.baseline = tree_state(root)
            shutil.copytree(root / "decomp", self.path / "decomp")
            if (root / "tools/decomp").exists():
                shutil.copytree(root / "tools/decomp", self.path / "tools/decomp",
                                ignore=shutil.ignore_patterns("__pycache__"))
        build = self.path / "build-decomp"
        build.mkdir()
        for name in ("include-gen", "drafts", "types.json", "examples.json", "progress.json"):
            source = root / "build-decomp" / name
            if source.is_dir():
                shutil.copytree(source, build / name)
            elif source.exists():
                shutil.copy2(source, build / name)
        for name in ("db", "scaffold"):
            source = root / "build-decomp" / name
            if source.exists():
                (build / name).symlink_to(source, target_is_directory=True)
        self._link_external_inputs()
        self._save_baseline()

    def _link_external_inputs(self):
        # These pinned library sources are read-only inputs. toolchain.include_args
        # reads them from the live checkout, so the staged evidence must see the
        # same files as well; they are never part of the publication delta.
        source = self.root / "third_party"
        target = self.path / "third_party"
        if source.is_dir():
            if target.is_symlink() and target.resolve() != source.resolve():
                target.unlink()
            if not target.exists():
                target.symlink_to(source.resolve(), target_is_directory=True)

    def _save_baseline(self):
        data = {"schema": 1, "root": str(self.root.resolve()), "baseline": self.baseline}
        temporary = self.path / "stage.json.tmp"
        _write_file(temporary, json.dumps(data, sort_keys=True).encode())
        os.replace(temporary, self.path / "stage.json")
        _sync_directory(self.path)

    @classmethod
    def resume(cls, path, root=None):
        """Open an existing attempt after a process exit; its validation is lost."""
        path = Path(path).resolve()
        saved = json.loads((path / "stage.json").read_text())
        if saved.get("schema") != 1 or not isinstance(saved.get("baseline"), dict):
            raise RuntimeError("unsupported saved Stage metadata")
        saved_root = Path(saved["root"]).resolve()
        if root is not None and Path(root).resolve() != saved_root:
            raise RuntimeError("saved Stage root mismatch")
        attempts = (saved_root / "build-decomp/attempts").resolve()
        if path.parent != attempts:
            raise RuntimeError("saved Stage must be inside root/build-decomp/attempts")
        for name, digest in saved["baseline"].items():
            if (not isinstance(name, str) or Path(name).is_absolute() or ".." in Path(name).parts
                    or Path(name).as_posix() != name
                    or not name.startswith(("decomp/", "tools/decomp/"))
                    or not isinstance(digest, str) or not re.fullmatch(r"[0-9a-f]{64}", digest)):
                raise RuntimeError("invalid saved Stage baseline")
        instance = cls.__new__(cls)
        instance.path = path
        instance.root = saved_root
        instance.baseline = saved["baseline"]
        instance.validated = None
        instance.validated_inputs = None
        instance._link_external_inputs()
        return instance

    @contextmanager
    def activate(self):
        import autotest
        import descriptors
        import ghidra_cpp
        import headers
        import llm_loop
        import promote
        import properties
        import hybrid
        replacements = [(llm_loop, "ROOT", self.path), (headers, "ROOT", self.path),
                        (ghidra_cpp, "ROOT", self.path), (ghidra_cpp, "_SRET", None), (ghidra_cpp, "_SRET_INPUT", None),
                        (toolchain, "CC_CACHE", self.path / "build-decomp/cc-cache"),
                        (toolchain, "SHARED_CC_CACHE", self.root / "build-decomp/shared-cc-cache"),
                        (toolchain, "CONFIG", self.path / "decomp/config.json"),
                        (hybrid, "ROOT", self.path), (hybrid, "SRC", self.path / "decomp/src"),
                        (hybrid, "HYBRID", self.path / "decomp/hybrid"),
                        (hybrid, "TESTS", self.path / "decomp/hybrid/tests"),
                        (hybrid, "OUT", self.path / "build-decomp/hybrid"),
                        (headers, "INCLUDE", self.path / "decomp/include"),
                        (headers, "OUT", self.path / "build-decomp/include-gen"),
                        (headers, "DRAFTS", self.path / "build-decomp/drafts"),
                        (headers, "TYPES", self.path / "build-decomp/types.json"),
                        (promote, "INCLUDE", self.path / "decomp/include"),
                        (promote, "GEN", self.path / "build-decomp/include-gen"),
                        (autotest, "ROOT", self.path),
                        (autotest, "TYPES", self.path / "build-decomp/types.json"),
                        (autotest, "OUT", self.path / "build-decomp/hybrid/autotests")]
        for module in (descriptors, properties):
            replacements.extend([(module, "ROOT", self.path), (module, "INCLUDE", self.path / "decomp/include"),
                                 (module, "SRC", self.path / "decomp/src")])
        replacements.append((descriptors, "GEN", self.path / "build-decomp/include-gen"))
        saved = [(module, name, getattr(module, name)) for module, name, _ in replacements]
        environment = {k: os.environ.get(k) for k in ("OTL_INCLUDE_ROOT", "OTL_EXTRA_INCLUDE",
                                                     "OTL_SELFTEST_TIMEOUT", "OTL_AUTOTEST")}
        for module, name, value in replacements:
            setattr(module, name, value)
        os.environ["OTL_INCLUDE_ROOT"] = str(self.path)
        try:
            yield self
        finally:
            for module, name, value in saved:
                setattr(module, name, value)
            for key, value in environment.items():
                if value is None:
                    os.environ.pop(key, None)
                else:
                    os.environ[key] = value

    def validate(self, coverage_provider=None, baseline_covered=None):
        """Check every final TU and the complete headless suite before publishing."""
        import hybrid
        import objdiff
        import autotest
        self.validated = None
        self.validated_inputs = None
        autotest.write_runtime(self.path / "build-decomp/hybrid/autotests")
        final_state = tree_state(self.path)
        final_fixtures = self._generated_tests_state()
        final_inputs = self._input_digest()
        tool_changes = [name for name in set(final_state) | set(self.baseline)
                        if name.startswith("tools/") and final_state.get(name) != self.baseline.get(name)]
        if tool_changes:
            raise RuntimeError("Stage cannot validate or publish changed tool implementation: " + ", ".join(sorted(tool_changes)))
        with tree_lock(self.root):
            if tree_state(self.root) != self.baseline:
                raise RuntimeError("source/header tree changed during the attempt; rebase and validate again")
            original = objdiff.Original()
            if baseline_covered is None:
                import acceptance
                baseline_covered = acceptance.prior_compared(self.root, getattr(original, "db", {"functions": {}}))
            saved_config = toolchain.CONFIG
            saved_environment = {key: os.environ.get(key) for key in ("OTL_INCLUDE_ROOT", "OTL_EXTRA_INCLUDE")}
            try:
                toolchain.CONFIG = self.root / "decomp/config.json"
                os.environ["OTL_INCLUDE_ROOT"] = str(self.root)
                os.environ.pop("OTL_EXTRA_INCLUDE", None)
                baseline_sources = sorted((self.root / "decomp/src").rglob("*.cpp"))
                baseline_units = toolchain.parallel_map(lambda p: objdiff.compare_source(p, original, quiet=True, scores=False), baseline_sources)
            finally:
                toolchain.CONFIG = saved_config
                for key, value in saved_environment.items():
                    if value is None:
                        os.environ.pop(key, None)
                    else:
                        os.environ[key] = value
        with self.activate():
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            sources = sorted((self.path / "decomp/src").rglob("*.cpp"))
            units = toolchain.parallel_map(lambda p: objdiff.compare_source(p, original, quiet=True, scores=False), sources)
            if any(unit.get("unknown") for unit in units):
                raise RuntimeError("final sources contain unknown original signatures")
            # Reject impossible structural changes before compiling/running the
            # expensive fixtures. This grants no behavioral coverage: the full
            # preservation check below still runs with fresh execution evidence.
            self._preserve(baseline_units, units, set(), final_state,
                           db=getattr(original, "db", {}), structural_only=True)
            tests = sorted((self.path / "decomp/hybrid/tests").glob("*.cpp"))
            tests += sorted((self.path / "build-decomp/hybrid/autotests").glob("*.cpp"))
            count = len(tests)
            shards = max(1, int(os.environ.get("OTL_SELFTEST_SHARDS", "0")) or min(4, toolchain.jobs()))
            os.environ.setdefault("OTL_SELFTEST_TIMEOUT", str(120 + 20 * ((count + shards - 1) // shards)))
            blob, loader = hybrid.build(out=self.path / "build-decomp/hybrid/final", src=self.path / "decomp/src",
                                        tests=tests, verbose=False)
            code, report = hybrid.selftest(blob, loader)
            if code:
                raise RuntimeError("final headless selftest failed:\n" + "\n".join(report))
            if coverage_provider is None:
                import check
                covered = check.shadow_covered(getattr(original, "db", {"functions": {}}), report)
            else:
                covered = set(coverage_provider(self, units, report))
        self._preserve(baseline_units, units, covered, final_state, baseline_covered,
                       db=getattr(original, "db", {}))
        if tree_state(self.path) != final_state:
            raise RuntimeError("validation inputs changed while the final tree was being checked")
        if self._generated_tests_state() != final_fixtures:
            raise RuntimeError("generated comparison fixtures changed during validation")
        if self._input_digest() != final_inputs:
            raise RuntimeError("external validation inputs changed during the final checks")
        with tree_lock(self.root):
            if tree_state(self.root) != self.baseline:
                raise RuntimeError("source/header tree changed during validation; rebase and validate again")
        self.baseline_units, self.final_units = baseline_units, units
        self.validation_db = getattr(original, "db", {"functions": {}})
        self.final_objects = {source.relative_to(self.path).as_posix(): unit.get("object_digest")
                              for source, unit in zip(sources, units)}
        self.covered, self.report = covered, report
        self.validated = final_state
        self.validated_inputs = final_inputs
        self.validated_fixtures = final_fixtures
        return units

    def _generated_tests_state(self):
        base = self.path / "build-decomp/hybrid/autotests"
        return {p.relative_to(base).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
                for p in sorted(base.rglob("*")) if p.is_file()}

    def _input_digest(self):
        """Fingerprint the actual staged build, compiler, original and runtime."""
        import evidence
        with self.activate():
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            return evidence.input_digest(elfdb.load_db(), root=self.path)

    def _preserve(self, baseline_units, final_units, covered, final_state, baseline_covered=(), db=None, structural_only=False):
        db = db or {}
        functions = db.get("functions", {})
        def definitions(units):
            result = {}
            for index, unit in enumerate(units):
                owner = unit.get("tu") or Path(unit.get("source", str(index))).name
                for row in unit["functions"]:
                    address = row.get("address")
                    if (row["status"] == "MISSING"
                            or functions.get(address, {}).get("kind") == "compiler"):
                        continue  # hybrid does not hook compiler initialization functions
                    key = (owner, row.get("name") or address, address)
                    result.setdefault(key, []).append((row, unit.get("object_digest", row.get("object_digest"))))
            return result
        before, after = definitions(baseline_units), definitions(final_units)
        # An unchanged instruction stream is insufficient for EH and data.
        # Unknown existing definitions are allowed only with the same full object
        # and runtime/build policy, or a fresh comparison of this final build.
        # Header/ownership edits are not changes to an already compiled object:
        # the SHA-256 below covers its complete bytes (code, data, relocations, EH).
        # Any affected object still changes digest and requires fresh evidence.
        # This preserves an UNACCEPTED definition; it never accepts one.
        # Tests may be added for a new candidate without changing an unrelated,
        # still unaccepted definition. This is not reuse of a behavioral receipt:
        # previously accepted DIFFs must appear in the new executed comparisons.
        context = lambda state: {key: value for key, value in state.items()
                                 if not key.startswith(("decomp/src/", "decomp/hybrid/tests/"))
                                 and not key.startswith("decomp/include/")
                                 and key not in ("decomp/autotests.json", "decomp/owners.json")}
        same_context = context(self.baseline) == context(final_state)
        for key, old_rows in before.items():
            if key not in after:
                # An EXTRA without an original symbol is never a game hook.
                # Inlining an existing SDK helper may remove that out-of-line
                # definition. The final link above checks remaining references;
                # dropping it does not accept a replacement or lose a game body.
                original_names = {n for f in functions.values() for n in f.get("names", [])}
                if all(row["status"] == "EXTRA" and not row.get("address")
                       and row.get("name") not in original_names for row, _ in old_rows):
                    continue
                raise RuntimeError("existing definition disappeared: " + str(key[2] or key[1]))
        for key, rows in after.items():
            old_rows = before.get(key, [])
            for row, new_object in rows:
                address = row.get("address")
                name = row.get("name", "")
                if row["status"] == "EXTRA" or not address:
                    if self._helper_extra(name):
                        continue
                    if (same_context and new_object and old_rows
                            and all(old_object == new_object for _, old_object in old_rows)):
                        continue
                    import objdiff
                    original_names = {n for f in functions.values() for n in f.get("names", [])}
                    invented = objdiff.unknown_members({"classes": db.get("classes", {})}, original_names, [name])
                    if invented:
                        raise RuntimeError("invented game definition: " + name)
                    raise RuntimeError("unsupported extra definition: " + name)
                if structural_only:
                    continue
                if row["status"] == "MATCH" or address in covered:
                    continue
                if not old_rows:
                    raise RuntimeError("new definition lacks MATCH or fresh behavioral evidence: " + address)
                if any(old["status"] == "MATCH" for old, _ in old_rows):
                    raise RuntimeError("previous MATCH lost without fresh behavioral evidence: " + address)
                if address in baseline_covered:
                    raise RuntimeError("previous behavioral acceptance lost without fresh comparison: " + address)
                if (not same_context or not new_object
                        or any(not old_object or old_object != new_object for _, old_object in old_rows)):
                    raise RuntimeError("existing DIFF changed without fresh behavioral evidence: " + address)

    @staticmethod
    def _compiler_extra(name):
        return bool(re.match(r"^(?:_GLOBAL__[ID]_|__tcf_\d+(?:$|\.)|"
                             r"_Z41__static_initialization_and_destruction_0ii(?:$|\.))", name))

    @classmethod
    def _helper_extra(cls, name):
        # Only pinned standard-library template namespaces and GCC initialization
        # scaffolding. Game helpers are not accepted merely because they are weak.
        # GCC's Sb substitution encodes std::basic_string, rather than NSt.
        # This exact UTF-16 allocator cleanup is emitted by the pinned libstdc++
        # header through Ogre::UTFString. Do not allow arbitrary Sb members.
        utf16_cleanup = "_ZNSbItSt11char_traitsItESaItEE4_Rep10_M_disposeERKS1_"
        return name == utf16_cleanup or cls._compiler_extra(name) or bool(re.match(
            r"^_Z(?:St|N[KVR]*(?:St|9__gnu_cxx))\d+[A-Za-z_][A-Za-z_0-9]*I", name))

    def rebase(self, validate=False, coverage_provider=None):
        """Reapply the saved file delta to the current tree, without regenerating it."""
        local = tree_state(self.path)
        with tree_lock(self.root):
            live = tree_state(self.root)
            changed = {name for name in set(self.baseline) | set(local)
                       if local.get(name) != self.baseline.get(name)}
            conflicts = [name for name in changed if live.get(name) != self.baseline.get(name)
                         and live.get(name) != local.get(name)]
            if conflicts:
                raise RuntimeError("rebase conflicts: " + ", ".join(sorted(conflicts)))
            self.validated = None
            self.validated_inputs = None
            updates = {name for name in set(local) | set(live) if name not in changed}
            for name in sorted(updates):
                target = self.path / name
                if name not in live:
                    target.unlink(missing_ok=True)
                else:
                    target.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(self.root / name, target)
            self.baseline = live
            self._save_baseline()
        self.validated = None
        self.validated_inputs = None
        for name in ("baseline_units", "final_units", "final_objects", "validation_db", "covered", "report",
                     "validated_fixtures"):
            self.__dict__.pop(name, None)
        if validate:
            self.validate(coverage_provider=coverage_provider)
        return sorted(changed)

    def publish(self):
        if getattr(self, "validated", None) != tree_state(self.path):
            raise RuntimeError("publication requires validation of the unchanged final tree")
        if not getattr(self, "validated_inputs", None):
            raise RuntimeError("publication requires validation of the complete build inputs")
        if (hasattr(self, "validated_fixtures")
                and self._generated_tests_state() != self.validated_fixtures):
            raise RuntimeError("generated comparison fixtures changed after validation")
        final = tree_state(self.path)
        changed = [name for name in sorted(set(final) | set(self.baseline))
                   if final.get(name) != self.baseline.get(name)]
        if any(not name.startswith("decomp/") for name in changed):
            raise RuntimeError("Stage publication only supports decomp files")
        with tree_lock(self.root, exclusive=True):
            if tree_state(self.root) != self.baseline:
                raise RuntimeError("source/header tree changed during the attempt; rebase and validate again")
            if self._input_digest() != self.validated_inputs:
                raise RuntimeError("build inputs changed after validation")
            if (hasattr(self, "validated_fixtures")
                    and self._generated_tests_state() != self.validated_fixtures):
                raise RuntimeError("generated comparison fixtures changed after validation")
            if hasattr(self, "validation_db"):
                import acceptance
                self._preserve(self.baseline_units, self.final_units, self.covered, final,
                               acceptance.prior_compared(self.root, self.validation_db), db=self.validation_db)
            contents = {name: (self.path / name).read_bytes() if name in final else None for name in changed}
            if any(data is not None and hashlib.sha256(data).hexdigest() != final[name]
                   for name, data in contents.items()):
                raise RuntimeError("publication inputs changed while capturing the validated tree")
            journal = self._prepare_journal(changed)
            try:
                for name in changed:
                    self._replace(name, contents[name])
                self._verify_published_objects()
                if tree_state(self.root) != final or tree_state(self.path) != self.validated:
                    raise RuntimeError("publication tree changed during final object verification")
                if self._input_digest() != self.validated_inputs:
                    raise RuntimeError("build inputs changed during publication verification")
                if (hasattr(self, "validated_fixtures")
                        and self._generated_tests_state() != self.validated_fixtures):
                    raise RuntimeError("generated comparison fixtures changed during publication verification")
                _write_file(journal / "committed", b"1\n")
                _sync_directory(journal)
            except BaseException:
                _recover(self.root)
                raise
            _recover(self.root)
        return changed

    def _verify_published_objects(self):
        """Before commit, prove that live paths build the objects actually tested.

        The caller owns the exclusive tree lock and an unfinished journal. Do
        not enter another tree_lock here: recovery would roll back this write.
        A path-dependent __FILE__ value is a different object, even with the
        same source bytes. Such a candidate is rolled back rather than stamped
        with the Stage's prior behavioral result.
        """
        import objdiff
        expected = getattr(self, "final_objects", None)
        if expected is None or any(not digest for digest in expected.values()):
            raise RuntimeError("publication requires final checked source objects")
        sources = sorted((self.root / "decomp/src").rglob("*.cpp"))
        if {source.relative_to(self.root).as_posix() for source in sources} != set(expected):
            raise RuntimeError("published source set differs from the validated Stage")
        original = objdiff.Original()
        saved_config, saved_cache = toolchain.CONFIG, toolchain.SHARED_CC_CACHE
        environment = {key: os.environ.get(key) for key in ("OTL_INCLUDE_ROOT", "OTL_EXTRA_INCLUDE")}
        try:
            toolchain.CONFIG = self.root / "decomp/config.json"
            toolchain.SHARED_CC_CACHE = self.root / "build-decomp/shared-cc-cache"
            os.environ["OTL_INCLUDE_ROOT"] = str(self.root)
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            units = toolchain.parallel_map(lambda source: objdiff.compiled_identity(source, original, quiet=True), sources)
        finally:
            toolchain.CONFIG, toolchain.SHARED_CC_CACHE = saved_config, saved_cache
            for key, value in environment.items():
                if value is None:
                    os.environ.pop(key, None)
                else:
                    os.environ[key] = value
        for source, unit in zip(sources, units):
            name = source.relative_to(self.root).as_posix()
            if unit.get("unknown") or unit.get("object_digest") != expected[name]:
                raise RuntimeError("published object differs from checked Stage (including path-sensitive inputs): " + name)

    def _prepare_journal(self, changed):
        parent = self.root / "build-decomp"
        pending = Path(tempfile.mkdtemp(prefix="publication-prepare-", dir=parent))
        rows = []
        try:
            for index, name in enumerate(changed):
                target = self.root / name
                data = target.read_bytes() if target.exists() else None
                backup = "backup-" + str(index) if data is not None else None
                if backup:
                    _write_file(pending / backup, data)
                rows.append({"name": name, "backup": backup,
                             "sha256": hashlib.sha256(data).hexdigest() if data is not None else None,
                             "mode": target.stat().st_mode & 0o777 if data is not None else None})
            _write_file(pending / "manifest.json", json.dumps({"schema": 1, "files": rows}).encode())
            _sync_directory(pending)
            journal = _journal(self.root)
            os.replace(pending, journal)
            _sync_directory(parent)
            return journal
        finally:
            if pending.exists():
                shutil.rmtree(pending)

    def _replace(self, name, data):
        _replace_file(self.root, name, data)
