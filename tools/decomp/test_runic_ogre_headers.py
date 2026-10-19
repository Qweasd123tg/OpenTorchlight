"""Pinned SDK extension: concurrent setup, idempotence and drift rejection."""
from concurrent.futures import ThreadPoolExecutor
import hashlib
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import toolchain


class RunicOgreHeaders(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="otl-runic-sdk-")
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.header = self.root / "ogre-1.6.5/ogre/OgreMain/include/OgreMesh.h"
        self.header.parent.mkdir(parents=True)
        self.original = b"class Mesh {\n        const SkeletonPtr& getSkeleton(void) const;\n};\n"
        self.extended = (
            b"class Mesh {\n        const SkeletonPtr& getSkeleton(void) const;\n"
            b"\n        // Exported by the pinned Runic OGRE 1.6.5 runtime.\n"
            b"        unsigned short getMaxBoneAssignments(void) const;\n};\n"
        )
        self.header.write_bytes(self.original)
        for name, data in (("RUNIC_MESH_HEADER_ORIGINAL", self.original),
                           ("RUNIC_MESH_HEADER_EXTENDED", self.extended)):
            context = patch.object(toolchain, name, hashlib.sha256(data).hexdigest())
            context.start()
            self.addCleanup(context.stop)

    def test_concurrent_install_is_atomic_and_preserves_permissions(self):
        self.header.chmod(0o640)
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(toolchain.prepare_runic_ogre_headers, [self.root] * 8))
        self.assertEqual(self.extended, self.header.read_bytes())
        self.assertEqual(0o640, self.header.stat().st_mode & 0o777)
        self.assertEqual([], list(self.header.parent.glob(".runic-mesh-*")))

    def test_repeat_does_not_replace_an_already_extended_header(self):
        toolchain.prepare_runic_ogre_headers(self.root)
        before = self.header.stat()
        toolchain.prepare_runic_ogre_headers(self.root)
        after = self.header.stat()
        self.assertEqual((before.st_ino, before.st_mtime_ns),
                         (after.st_ino, after.st_mtime_ns))

    def test_foreign_edits_are_rejected_without_mutation(self):
        for data in (self.original + b"// foreign edit\n",
                     self.extended + b"// foreign edit\n"):
            with self.subTest(data=data):
                self.header.write_bytes(data)
                with self.assertRaisesRegex(SystemExit, "unexpected OgreMesh.h digest"):
                    toolchain.prepare_runic_ogre_headers(self.root)
                self.assertEqual(data, self.header.read_bytes())

    def test_prepared_sdk_does_not_require_a_writable_lock(self):
        self.header.write_bytes(self.extended)
        original_open = Path.open

        def readonly_open(path, *args, **kwargs):
            if path.name == ".runic-sdk.lock":
                raise PermissionError("read-only SDK")
            return original_open(path, *args, **kwargs)

        with patch.object(Path, "open", readonly_open), \
                patch.object(toolchain.fcntl, "flock", side_effect=AssertionError("unexpected lock")):
            toolchain.prepare_runic_ogre_headers(self.root)
            self.header.write_bytes(self.extended + b"// drift\n")
            with self.assertRaisesRegex(SystemExit, "unexpected OgreMesh.h digest"):
                toolchain.prepare_runic_ogre_headers(self.root)

    def test_unexpected_extension_digest_cannot_replace_input(self):
        with patch.object(toolchain, "RUNIC_MESH_HEADER_EXTENDED", "0" * 64):
            with self.assertRaisesRegex(SystemExit, "unexpected extended OgreMesh.h digest"):
                toolchain.prepare_runic_ogre_headers(self.root)
        self.assertEqual(self.original, self.header.read_bytes())

    def test_nonunique_anchor_cannot_replace_input(self):
        data = self.original * 2
        self.header.write_bytes(data)
        with patch.object(toolchain, "RUNIC_MESH_HEADER_ORIGINAL", hashlib.sha256(data).hexdigest()):
            with self.assertRaisesRegex(SystemExit, "declaration anchor is not unique"):
                toolchain.prepare_runic_ogre_headers(self.root)
        self.assertEqual(data, self.header.read_bytes())


if __name__ == "__main__":
    unittest.main()
