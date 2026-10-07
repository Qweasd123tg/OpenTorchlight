"""Real GCC controls for shared backend compilation across isolated attempts."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import threading
import unittest
from unittest.mock import patch

import publication
import toolchain


PINNED = toolchain.cache_dir() / "gcc447"


@unittest.skipUnless((PINNED / ".complete.json").exists(), "requires pinned GCC 4.4.7")
class SharedCompilerCache(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="otl-shared-cc-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.shared = self.root / "shared"
        for name, value in (("SHARED_CC_CACHE", self.shared), ("CC_CACHE", self.root / "local")):
            context = patch.object(toolchain, name, value)
            context.start()
            self.addCleanup(context.stop)
        context = patch.dict(os.environ, {}, clear=False)
        context.start()
        self.addCleanup(context.stop)
        os.environ.pop("OTL_NO_CC_CACHE", None)
        toolchain.shared_cache_stats(reset=True)

    def source(self, name="one", text='extern "C" int result(){return 11;}\n'):
        directory = self.root / name
        directory.mkdir(parents=True, exist_ok=True)
        path = directory / "Probe.cpp"
        path.write_text(text)
        return path

    def compile(self, source, name, extra=(), assembly=False, cache=True):
        return toolchain.compile_source(source, self.root / name, extra, assembly=assembly, cache=cache, quiet=True)

    def execute(self, obj, declaration='extern "C" int result();', expression="result()", string=False):
        main = obj.with_suffix(".main.cpp")
        main.write_text('#include <cstdio>\n' + declaration + '\nint main(){std::printf("' +
                        ("%s" if string else "%d") + '",' + expression + ');}\n')
        executable = obj.with_suffix(".exe")
        subprocess.run(["g++", "-no-pie", str(obj), str(main), "-o", str(executable)], capture_output=True, check=True)
        return subprocess.run([str(executable)], capture_output=True, text=True, check=True).stdout

    def test_two_real_stage_attempts_share_objects_and_assembly(self):
        project = self.root / "project"
        (project / "decomp/src").mkdir(parents=True)
        (project / "decomp/include").mkdir()
        (project / "decomp/src/Probe.cpp").write_text('extern "C" int result(){return 11;}\n')
        (project / "decomp/config.json").write_text(json.dumps({"cflags": ["-O2", "-DNDEBUG"], "include": ["decomp/include"]}))
        first, second = publication.Stage(project), publication.Stage(project)
        outputs = []
        for index, stage in enumerate((first, second)):
            with stage.activate():
                source = stage.path / "decomp/src/Probe.cpp"
                obj = self.compile(source, str(index) + ".o")
                asm = self.compile(source, str(index) + ".s", assembly=True)
                cold = self.compile(source, str(index) + "-cold.o", cache=False)
                self.assertEqual(cold.read_bytes(), obj.read_bytes())
                outputs.append((obj.read_bytes(), asm.read_bytes()))
        self.assertEqual(outputs[0], outputs[1])
        self.assertEqual({"hit": 2, "miss": 2, "fallback": 0}, toolchain.shared_cache_stats())
        self.assertIn(b'.file\t"Probe.cpp"', outputs[0][1])
        self.assertEqual("11", self.execute(self.root / "1.o"))
        self.assertEqual(2, len(list((project / "build-decomp/shared-cc-cache").glob("*/input.ii"))))

    def test_real_file_base_file_line_and_timestamp_values_are_preserved(self):
        text = '''extern "C" const char* file(){return __FILE__;}
extern "C" const char* base(){return __BASE_FILE__;}
extern "C" const char* stamp(){return __TIMESTAMP__;}
extern "C" int line(){return __LINE__;}
'''
        for name in ("first", "second"):
            source = self.source(name, text)
            obj = self.compile(source, name + ".o")
            cold = self.compile(source, name + "-cold.o", cache=False)
            self.assertEqual(cold.read_bytes(), obj.read_bytes())
            for function in ("file", "base"):
                self.assertEqual(str(source), self.execute(obj, 'extern "C" const char* ' + function + '();',
                                                          function + "()", string=True))
            self.assertEqual("4", self.execute(obj, 'extern "C" int line();', "line()"))
        self.assertEqual(0, toolchain.shared_cache_stats()["hit"])
        self.assertEqual(2, toolchain.shared_cache_stats()["miss"])
        source = self.source("timestamp", 'extern "C" const char* stamp(){return __TIMESTAMP__;}\n')
        os.utime(source, (1600000000, 1600000000))
        first = self.compile(source, "stamp-first.o")
        os.utime(source, (1600003600, 1600003600))
        second = self.compile(source, "stamp-second.o")
        self.assertNotEqual(first.read_bytes(), second.read_bytes())
        self.assertNotEqual(self.execute(first, 'extern "C" const char* stamp();', "stamp()", True),
                            self.execute(second, 'extern "C" const char* stamp();', "stamp()", True))

    def test_shadow_header_add_remove_and_contents_are_resolved_each_time(self):
        high, low = self.root / "high", self.root / "low"
        high.mkdir(); low.mkdir()
        (low / "Value.h").write_text("#define VALUE 7\n")
        source = self.source(text='#include "Value.h"\nextern "C" int result(){return VALUE;}\n')
        flags = ["-I", str(high), "-I", str(low)]
        first = self.compile(source, "low.o", flags)
        (high / "Value.h").write_text("#define VALUE 99\n")
        second = self.compile(source, "high.o", flags)
        (high / "Value.h").unlink()
        restored = self.compile(source, "restored.o", flags)
        self.assertEqual("7", self.execute(first))
        self.assertEqual("99", self.execute(second))
        self.assertEqual(first.read_bytes(), restored.read_bytes())
        self.assertEqual({"hit": 1, "miss": 2, "fallback": 0}, toolchain.shared_cache_stats())

    def test_configuration_and_semantic_flags_invalidate_cache(self):
        source = self.source(text='extern "C" int result(){return VALUE;}\n')
        first = self.compile(source, "seven.o", ["-DVALUE=7"])
        second = self.compile(source, "ninetynine.o", ["-DVALUE=99"])
        cfg = toolchain.config()
        cfg["cflags"] = ["-O0", "-DNDEBUG"]
        with patch.object(toolchain, "config", return_value=cfg):
            unoptimized = self.compile(source, "unoptimized.o", ["-DVALUE=7"])
        self.assertEqual("7", self.execute(first))
        self.assertEqual("99", self.execute(second))
        self.assertNotEqual(first.read_bytes(), unoptimized.read_bytes())
        self.assertEqual(3, toolchain.shared_cache_stats()["miss"])

    def test_compiler_content_changes_invalidate_even_same_executable_path(self):
        base = self.root / "fake-toolchain"
        gcc = base / "gcc447"
        (gcc / "usr/bin").mkdir(parents=True)
        libexec = gcc / "usr/libexec/gcc" / toolchain.GCC_TRIPLE / toolchain.GCC_VERSION
        libexec.mkdir(parents=True)
        for name in ("cc1plus",):
            (libexec / name).symlink_to(PINNED / "usr/libexec/gcc" / toolchain.GCC_TRIPLE / toolchain.GCC_VERSION / name)
        (gcc / "usr/lib64").symlink_to(PINNED / "usr/lib64", target_is_directory=True)
        shutil.copy2(PINNED / "usr/bin/g++", gcc / "usr/bin/g++")
        (gcc / "usr/bin/as").symlink_to(PINNED / "usr/bin/as")
        (gcc / ".complete.json").write_text("{}")
        source = self.source()
        with patch.object(toolchain, "cache_dir", return_value=base), \
                patch.object(toolchain, "config", return_value={"cflags": ["-O2"], "include": []}):
            first = self.compile(source, "old-compiler.o")
            with (gcc / "usr/bin/g++").open("ab") as stream:
                stream.write(b"compiler identity regression marker\n")
            second = self.compile(source, "new-compiler.o")
        self.assertEqual(first.read_bytes(), second.read_bytes())
        self.assertEqual({"hit": 0, "miss": 2, "fallback": 0}, toolchain.shared_cache_stats())

    def test_debug_and_unknown_flags_fall_back_to_real_source_compilation(self):
        source = self.source()
        for index, flags in enumerate((["-g"], ["-fno-inline-functions"], ["--coverage"])):
            output = self.compile(source, "fallback" + str(index) + ".o", flags)
            cold = self.compile(source, "fallback" + str(index) + "-cold.o", flags, cache=False)
            if flags != ["--coverage"]:  # coverage embeds its output pathname
                self.assertEqual(cold.read_bytes(), output.read_bytes())
        self.assertEqual({"hit": 0, "miss": 0, "fallback": 3}, toolchain.shared_cache_stats())
        self.assertFalse(self.shared.exists())

    def test_incbin_payload_changes_cannot_reuse_any_object_cache(self):
        payload = self.root / "payload.bin"
        payload.write_bytes(b"\x07")
        text = ('extern "C" const unsigned char payload[];\n'
                'asm(".pushsection .rodata\\n.globl payload\\npayload:\\n.incbin \\\"' +
                str(payload) + '\\\"\\n.popsection");\n'
                'extern "C" int result(){return payload[0];}\n')
        source = self.source(text=text)
        first = self.compile(source, "incbin-seven.o")
        payload.write_bytes(b"\x63")
        second = self.compile(source, "incbin-ninetynine.o")
        self.assertEqual("7", self.execute(first))
        self.assertEqual("99", self.execute(second))
        self.assertEqual({"hit": 0, "miss": 0, "fallback": 2}, toolchain.shared_cache_stats())

    def test_corrupt_cached_output_is_recompiled(self):
        source = self.source()
        first = self.compile(source, "first.o")
        cached = next(self.shared.glob("*/output.o"))
        cached.write_bytes(b"corrupt cached object")
        second = self.compile(source, "repaired.o")
        self.assertEqual(first.read_bytes(), second.read_bytes())
        self.assertEqual(2, toolchain.shared_cache_stats()["miss"])

    def test_two_concurrent_requests_compile_once_under_key_lock(self):
        sources = [self.source("first"), self.source("second")]
        backend = []
        mutex = threading.Lock()
        real_run = subprocess.run
        def run(command, *args, **kwargs):
            if "-c" in command and any(str(item).endswith("input.ii") for item in command):
                with mutex:
                    backend.append(command)
            return real_run(command, *args, **kwargs)
        with patch.object(toolchain.subprocess, "run", side_effect=run):
            outputs = toolchain.parallel_map(lambda item: self.compile(item, item.parent.name + ".o"), sources)
        self.assertEqual(1, len(backend))
        self.assertEqual(outputs[0].read_bytes(), outputs[1].read_bytes())
        self.assertEqual({"hit": 1, "miss": 1, "fallback": 0}, toolchain.shared_cache_stats())

    def test_existing_pch_uses_original_pipeline_without_reusing_outputs(self):
        source = self.source(text='#include "Value.h"\nextern "C" int result(){return VALUE;}\n')
        header = source.parent / "Value.h"
        header.write_text("#define VALUE 7\n")
        # A discovered PCH (even an invalid one) is deliberately unsupported.
        Path(str(header) + ".gch").write_bytes(b"unsupported PCH contents")
        first = self.compile(source, "pch-seven.o")
        header.write_text("#define VALUE 99\n")
        second = self.compile(source, "pch-ninetynine.o")
        self.assertEqual("7", self.execute(first))
        self.assertEqual("99", self.execute(second))
        self.assertEqual({"hit": 0, "miss": 0, "fallback": 2}, toolchain.shared_cache_stats())


if __name__ == "__main__":
    unittest.main()
