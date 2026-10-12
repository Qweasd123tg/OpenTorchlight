"""Build-local original instruction reuse for hook patch-window checks only.

No hook result, replacement symbol, expected bytes or acceptance is cached.
The loaded image is SHA-256 checked against its path once; path metadata and
image identity are pinned before and after every lookup and objdump command.
Identity changes fail closed. Each Context owns one instance; nothing persists.
"""
import hashlib
import shutil
from pathlib import Path

from objdiff_disasm import OriginalInstructions


class PatchWindowInstructions:
    def __init__(self, db, image, run, parse):
        self.image = image
        self.path = Path(image.path)
        self.sha256 = image.sha256
        self.data = image.data
        if not isinstance(self.data, bytes) or hashlib.sha256(self.data).hexdigest() != self.sha256:
            raise RuntimeError('loaded original ELF data does not match its identity')
        self.identity = self._identity()
        self.run, self.parse = run, parse
        self.tool_identity = self._tool_identity()
        digest = hashlib.sha256()
        with self.path.open('rb') as stream:
            for block in iter(lambda: stream.read(1024 * 1024), b''):
                digest.update(block)
        self._check(image)
        if digest.hexdigest() != self.sha256:
            raise RuntimeError('original ELF changed before patch-window disassembly')
        self.cache = OriginalInstructions(db, image, self._run, parse, mode='tu')

    def _identity(self):
        stat = self.path.stat()
        return (stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns)

    @staticmethod
    def _tool_identity():
        path = shutil.which('objdump')
        if path is None:
            return None  # Let the normal objdump call report a missing tool.
        path = Path(path).resolve()
        stat = path.stat()
        return (path, stat.st_dev, stat.st_ino, stat.st_size,
                stat.st_mtime_ns, stat.st_ctime_ns)

    def _check(self, image):
        if self._tool_identity() != self.tool_identity:
            raise RuntimeError('objdump identity changed during patch-window disassembly')
        if (image is not self.image or image.data is not self.data
                or Path(image.path) != self.path
                or image.sha256 != self.sha256 or self._identity() != self.identity):
            raise RuntimeError('original ELF identity changed during patch-window disassembly')

    def _run(self, args):
        self._check(self.image)
        result = self.run(args)
        self._check(self.image)
        return result

    def instructions(self, image, function, run, parse):
        if run is not self.run or parse is not self.parse:
            raise RuntimeError('decoder identity changed during patch-window disassembly')
        self._check(image)
        rows = self.cache.instructions(function)
        self._check(image)
        return rows
