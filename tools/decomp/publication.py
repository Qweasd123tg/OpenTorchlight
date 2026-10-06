"""Isolated TU attempts and checked, locked publication of source and headers."""
from contextlib import contextmanager
import fcntl
import hashlib
import os
from pathlib import Path
import shutil
import tempfile

import elfdb
import toolchain


@contextmanager
def tree_lock(root=elfdb.ROOT, exclusive=False):
    path = root / "build-decomp" / "publication.lock"
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a+") as stream:
        fcntl.flock(stream, fcntl.LOCK_EX if exclusive else fcntl.LOCK_SH)
        try:
            yield
        finally:
            fcntl.flock(stream, fcntl.LOCK_UN)


def tree_state(root):
    return {p.relative_to(root).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
            for base in (root / "decomp/src", root / "decomp/include")
            for p in sorted(base.rglob("*")) if p.is_file()}


class Stage:
    def __init__(self, root=elfdb.ROOT):
        self.root = root
        work = root / "build-decomp" / "attempts"
        work.mkdir(parents=True, exist_ok=True)
        self.path = Path(tempfile.mkdtemp(prefix="tu-", dir=work))
        with tree_lock(root):
            self.baseline = tree_state(root)
            shutil.copytree(root / "decomp", self.path / "decomp")
        build = self.path / "build-decomp"
        build.mkdir()
        for name in ("include-gen", "drafts", "types.json", "examples.json"):
            source = root / "build-decomp" / name
            if source.is_dir():
                shutil.copytree(source, build / name)
            elif source.exists():
                shutil.copy2(source, build / name)
        for name in ("db", "scaffold"):
            source = root / "build-decomp" / name
            if source.exists():
                (build / name).symlink_to(source, target_is_directory=True)

    @contextmanager
    def activate(self):
        import autotest
        import descriptors
        import ghidra_cpp
        import headers
        import llm_loop
        import promote
        import properties
        replacements = [(llm_loop, "ROOT", self.path), (headers, "ROOT", self.path),
                        (ghidra_cpp, "ROOT", self.path), (ghidra_cpp, "_SRET", None), (ghidra_cpp, "_SRET_INPUT", None),
                        (toolchain, "CC_CACHE", self.path / "build-decomp/cc-cache"),
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

    def validate(self):
        """Check every final TU and the complete headless suite before publishing."""
        import hybrid
        import objdiff
        with self.activate():
            os.environ.pop("OTL_EXTRA_INCLUDE", None)
            original = objdiff.Original()
            sources = sorted((self.path / "decomp/src").rglob("*.cpp"))
            units = toolchain.parallel_map(lambda p: objdiff.compare_source(p, original, quiet=True), sources)
            if any(unit.get("unknown") for unit in units):
                raise RuntimeError("final sources contain unknown original signatures")
            count = len(list((self.path / "decomp/hybrid/tests").glob("*.cpp")))
            shards = max(1, int(os.environ.get("OTL_SELFTEST_SHARDS", "0")) or min(4, toolchain.jobs()))
            os.environ.setdefault("OTL_SELFTEST_TIMEOUT", str(120 + 20 * ((count + shards - 1) // shards)))
            blob, loader = hybrid.build(out=self.path / "build-decomp/hybrid/final", src=self.path / "decomp/src",
                                        tests=sorted((self.path / "decomp/hybrid/tests").glob("*.cpp")), verbose=False)
            code, report = hybrid.selftest(blob, loader)
            if code:
                raise RuntimeError("final headless selftest failed:\n" + "\n".join(report))
        self.validated = tree_state(self.path)

    def publish(self):
        if getattr(self, "validated", None) != tree_state(self.path):
            raise RuntimeError("publication requires validation of the unchanged final tree")
        final = tree_state(self.path)
        changed = [name for name in sorted(set(final) | set(self.baseline))
                   if final.get(name) != self.baseline.get(name)]
        with tree_lock(self.root, exclusive=True):
            if tree_state(self.root) != self.baseline:
                raise RuntimeError("source/header tree changed during the attempt; rebase and validate again")
            originals = {name: (self.root / name).read_bytes() if (self.root / name).exists() else None
                         for name in changed}
            try:
                for name in changed:
                    self._replace(name, (self.path / name).read_bytes() if name in final else None)
            except BaseException:
                for name, data in originals.items():
                    self._replace(name, data)
                raise
        return changed

    def _replace(self, name, data):
        target = self.root / name
        if data is None:
            target.unlink(missing_ok=True)
            return
        target.parent.mkdir(parents=True, exist_ok=True)
        fd, temporary = tempfile.mkstemp(prefix=".publish-", dir=target.parent)
        try:
            with os.fdopen(fd, "wb") as stream:
                stream.write(data)
            os.chmod(temporary, target.stat().st_mode & 0o777 if target.exists() else 0o644)
            os.replace(temporary, target)
        finally:
            Path(temporary).unlink(missing_ok=True)
