"""Shared-cache storage regressions with deterministic fake compiler outputs.

Extract only the adjacent toolchain's storage functions. No compiler, game, or
external cache is required; each test owns its temporary inputs and cache.
"""
import ast
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
import errno
import fcntl
import hashlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile
import threading
from types import SimpleNamespace
import unittest
from unittest.mock import patch

TOOLCHAIN = Path(__file__).with_name("toolchain.py")
PAYLOAD = b"synthetic immutable compiler output\n"


def load_cache_functions(cache, backend, stats):
    names = {"sha256", "_store_shared_output", "_shared_compile"}
    tree = ast.parse(TOOLCHAIN.read_text())
    tree.body = [node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name in names]
    scope = dict(Path=Path, os=os, fcntl=fcntl, hashlib=hashlib, json=json, shutil=shutil,
                 threading=threading, sys=sys, SHARED_CC_CACHE=cache, _SHARED_BYPASS=object(),
                 _shared_flags=lambda flags: flags, _compiler_identity=lambda *args: "pinned-id",
                 _shared_preprocess=lambda cmd, source, root, tmp: (source.read_bytes(), b""),
                 _shared_count=lambda name: stats.update([name]), driver_env=lambda root: {},
                 run_compiler=backend)
    exec(compile(tree, str(TOOLCHAIN), "exec"), scope)
    return scope


class SyntheticStorage(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="otl-storage-synthetic-")
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.cache = self.root / "cache"
        self.stats = Counter()
        self.calls = []
        self.mutex = threading.Lock()
        self.scope = load_cache_functions(self.cache, self.backend, self.stats)

    def backend(self, command, **kwargs):
        source = next(Path(arg) for arg in command if str(arg).endswith("/input.ii"))
        self.assertEqual("input.ii", source.name)
        self.assertNotIn(self.cache, source.parents)
        with self.mutex:
            self.calls.append(str(source))
        output = Path(command[command.index("-o") + 1])
        output.write_bytes(PAYLOAD)
        return SimpleNamespace(returncode=0, stderr="")

    def invoke(self, key="one", name="result", flags=None):
        source = self.root / (key + ".cpp")
        if not source.exists():
            source.write_bytes(("# 1 \"Probe.cpp\"\n// " + key).encode())
        output = self.root / (name + ".o")
        with tempfile.TemporaryDirectory(prefix="compile-", dir=self.root) as tmp:
            result = self.scope["_shared_compile"](["synthetic-g++", "-c"], source, output,
                      self.root, flags or [], False, True, tmp)
        self.assertFalse(Path(tmp).exists())
        return result

    def blobs(self):
        return [p for p in self.cache.glob("objects/*/*") if len(p.name) == 64]

    def test_different_semantic_keys_share_bytes_and_do_not_retain_inputs(self):
        a = self.invoke("a", "a")
        b = self.invoke("b", "b")
        cached = list(self.cache.glob("*/output.o"))
        self.assertEqual(2, len(cached))
        self.assertEqual(2, self.stats["miss"])
        self.assertEqual(0, self.stats["hit"])
        self.assertEqual(1, len(self.blobs()))
        self.assertEqual(cached[0].stat().st_ino, cached[1].stat().st_ino)
        self.assertNotEqual(a.stat().st_ino, cached[0].stat().st_ino)
        self.assertEqual([], list(self.cache.rglob("input.ii")))
        self.assertEqual(PAYLOAD, b.read_bytes())

    def test_caller_mutation_is_isolated_and_hit_manifest_is_verified(self):
        self.invoke().write_bytes(b"modified caller output")
        self.assertEqual(PAYLOAD, self.invoke(name="again").read_bytes())
        self.assertEqual(1, len(self.calls))
        manifest = next(self.cache.glob("*/result.json"))
        manifest.write_text("{}")
        self.assertEqual(PAYLOAD, self.invoke(name="repaired").read_bytes())
        self.assertEqual(2, len(self.calls))

    def test_corrupt_blob_replaced_without_modifying_old_inode(self):
        self.invoke("a", "a"); self.invoke("b", "b")
        blob = self.blobs()[0]
        old_inode = blob.stat().st_ino
        blob.write_bytes(b"corrupt shared inode")
        self.assertEqual(PAYLOAD, self.invoke("a", "repaired-a").read_bytes())
        self.assertNotEqual(old_inode, blob.stat().st_ino)
        self.assertEqual(1, sum(p.read_bytes() != PAYLOAD for p in self.cache.glob("*/output.o")))
        self.assertEqual(PAYLOAD, self.invoke("b", "repaired-b").read_bytes())
        self.assertTrue(all(p.stat().st_ino == blob.stat().st_ino for p in self.cache.glob("*/output.o")))
        self.assertEqual(4, self.stats["miss"])

    def test_backend_failure_leaves_no_cache_payload(self):
        self.scope["run_compiler"] = lambda *a, **k: SimpleNamespace(returncode=1, stderr="synthetic failure")
        self.assertIs(self.scope["_SHARED_BYPASS"], self.invoke())
        self.assertEqual([], list(self.cache.rglob("input.ii")))
        self.assertEqual([], list(self.cache.glob("*/result.json")))
        self.assertEqual([], self.blobs())

    def test_backend_exception_leaves_no_cache_input(self):
        def fail(*a, **k):
            raise OSError("synthetic backend failure")
        self.scope["run_compiler"] = fail
        with self.assertRaises(OSError):
            self.invoke()
        self.assertEqual([], list(self.cache.rglob("input.ii")))
        self.assertEqual([], list(self.root.glob("compile-*")))

    def test_hardlink_unavailable_falls_back_to_separate_copy(self):
        with patch.object(os, "link", side_effect=OSError(errno.EXDEV, "synthetic cross-device link")):
            self.invoke("a", "a"); self.invoke("b", "b")
        cached = list(self.cache.glob("*/output.o"))
        self.assertNotEqual(cached[0].stat().st_ino, cached[1].stat().st_ino)
        self.assertTrue(all(p.read_bytes() == PAYLOAD for p in cached + self.blobs()))

    def test_concurrent_same_key_has_one_backend_call(self):
        # Precreate the source to avoid a test-only source creation race.
        (self.root / "one.cpp").write_bytes(b"same source")
        with ThreadPoolExecutor(max_workers=8) as pool:
            outputs = list(pool.map(lambda n: self.invoke(name=str(n)), range(8)))
        self.assertEqual(1, len(self.calls))
        self.assertEqual(1, self.stats["miss"])
        self.assertEqual(7, self.stats["hit"])
        self.assertTrue(all(p.read_bytes() == PAYLOAD for p in outputs))

    def test_concurrent_different_keys_converge_on_one_content_inode(self):
        with ThreadPoolExecutor(max_workers=8) as pool:
            outputs = list(pool.map(lambda n: self.invoke(str(n), str(n)), range(8)))
        cached = list(self.cache.glob("*/output.o"))
        self.assertEqual(8, len(cached))
        self.assertEqual(8, self.stats["miss"])
        self.assertEqual(1, len({p.stat().st_ino for p in cached}))
        self.assertEqual(1, len(self.blobs()))
        self.assertTrue(all(p.read_bytes() == PAYLOAD for p in outputs))
        self.assertEqual([], list(self.cache.rglob(".blob-*")))
        self.assertEqual([], list(self.cache.rglob(".output-*")))

    def test_failed_publication_keeps_old_blob_and_cleans_temporary_files(self):
        self.invoke("a", "a")
        blob = self.blobs()[0]
        inode = blob.stat().st_ino
        real_replace = os.replace
        def fail_entry(source, target):
            if Path(source).name.startswith(".output-"):
                raise OSError("synthetic publish failure")
            return real_replace(source, target)
        with patch.object(os, "replace", side_effect=fail_entry):
            with self.assertRaises(OSError):
                self.invoke("b", "b")
        self.assertEqual(inode, blob.stat().st_ino)
        self.assertEqual(PAYLOAD, blob.read_bytes())
        self.assertEqual(1, len(list(self.cache.glob("*/result.json"))))
        self.assertEqual([], list(self.cache.rglob(".blob-*")))
        self.assertEqual([], list(self.cache.rglob(".output-*")))


if __name__ == "__main__":
    unittest.main()
