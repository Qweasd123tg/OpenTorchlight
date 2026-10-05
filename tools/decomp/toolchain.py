#!/usr/bin/env python3
"""Original-compiler toolchain for the decomp track.

`original-code`, .comment of the shipped ELF (in link order):
  [0x00] GCC 4.4.6 (Red Hat 4.4.6-4)   glibc crt objects, merged by ld
  [0x2c] GCC 4.4.7 (Red Hat 4.4.7-3)   every game object, merged by ld
  61 x   GCC 4.1.2 (Red Hat 4.1.2-51)  prebuilt static-library objects from an
                                      assembler that did not mark .comment mergeable
Game code also shows GCC >= 4.4 features: `[clone .clone.N]` (IPA-CP) and direct
`__cxa_atexit(dtor)` registration. We therefore fetch exactly gcc 4.4.7-3.el6 with
binutils 2.20.51.0.2-5.36.el6 and the CentOS 6.4 glibc/kernel headers from the
CentOS vault, plus the pinned OGRE 1.6.5 archive for its headers. Everything is
extracted into a cache directory whose path must not contain spaces (the GCC
driver composes sub-commands from specs).

    python3 tools/decomp/toolchain.py setup
    python3 tools/decomp/toolchain.py cc decomp/src/RunicCore.cpp -o /tmp/x.o
    python3 tools/decomp/toolchain.py cc FILE -S -o FILE.s
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.request

ROOT = Path(__file__).resolve().parents[2]
CONFIG = ROOT / "decomp" / "config.json"
VAULT = "https://vault.centos.org/6.4/os/x86_64/Packages/"
RPMS = {
    "cpp-4.4.7-3.el6.x86_64.rpm": "c6da133d2a49c60c21a21d1a9011b6c7ca86c90ddeead9fbd3d511240a936066",
    "gcc-4.4.7-3.el6.x86_64.rpm": "ee5ce795fbab3e040722ff1433e45783922c54669e93eb882c2dd3599df5d144",
    "gcc-c++-4.4.7-3.el6.x86_64.rpm": "f7530ae18667a7a28c110a250727af6fffaf0ce20cf0c3b8deab38809cd750b1",
    "libstdc++-devel-4.4.7-3.el6.x86_64.rpm": "c462b3238ef079f79330946818d949779ad18e23f21876b16756d6ee0256642b",
    "libstdc++-4.4.7-3.el6.x86_64.rpm": "40782298be4fabef812f7f5f57a507b0b677b9de2a056df9e72242f907fbb3e0",
    "libgcc-4.4.7-3.el6.x86_64.rpm": "6ea1489aacaa4d024dcc804de658ff192cf4cde9570b659eef58d91f90b6bf99",
    "libgomp-4.4.7-3.el6.x86_64.rpm": "a573151f19c40feaa026c6e9701bd65098a58ed905a795e4c95fe81f5e7c87da",
    "gmp-4.3.1-7.el6_2.2.x86_64.rpm": "ec257a3a9b58ac802f344623cf4bb8a507c75583c18c0a3d798dafd69059b7fe",
    "mpfr-2.4.1-6.el6.x86_64.rpm": "20d2ce3bc1ea03844a0beb1726b01ef50d8555b3c9facb65264055a634709cf4",
    "ppl-0.10.2-11.el6.x86_64.rpm": "3a11f39d0564597f5b66e8c623f6f0acbe1cc97d70679d6797b1d38eeb4f4e9a",
    "cloog-ppl-0.15.7-1.2.el6.x86_64.rpm": "911246e85a7bebc0872cba05d87941e7871b494931f295e2abebdc64f1c28020",
    "glibc-headers-2.12-1.107.el6.x86_64.rpm": "183fc4f18598e6c4eac5c75e3299a9fafb3468ea36eab6acea365104d8e3cbf1",
    "glibc-devel-2.12-1.107.el6.x86_64.rpm": "f0162adeb816f1f111000a48112fef828876e44114fd5b396f7b59e9b3632621",
    "kernel-headers-2.6.32-358.el6.x86_64.rpm": "cb79b7c214402c80dc4e579a19e8ca235faf8b93b958d95cca15e1f473b4595a",
    "binutils-2.20.51.0.2-5.36.el6.x86_64.rpm": "a8dfefada3011c0f1631a1cafab3ddb766fd0151d9815ab13f372188cb1c0523",
}
# Same archive and digest as third_party/ogre-1.6.5-math/source-inputs.json.
OGRE = ("ogre-v1-6-5.tar.bz2",
        "https://sourceforge.net/projects/ogre/files/ogre/1.6.5/ogre-v1-6-5.tar.bz2/download",
        "7fc0e948679c1c1f10751756d267a41d0e3395a6520a23f7853a0ae39a1281f5")
GCC_TRIPLE = "x86_64-redhat-linux"
GCC_VERSION = "4.4.7"
EXPECTED_COMMENT = "GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"


def cache_dir():
    base = Path(os.environ.get("OTL_DECOMP_CACHE", Path.home() / ".cache" / "opentorchlight" / "decomp"))
    if " " in str(base):
        raise SystemExit(f"OTL_DECOMP_CACHE must not contain spaces: {base}")
    return base


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def fetch(url, target, digest):
    if target.exists() and sha256(target) == digest:
        return target
    target.parent.mkdir(parents=True, exist_ok=True)
    tmp = target.with_suffix(target.suffix + ".part")
    print(f"fetch {url}")
    with urllib.request.urlopen(url) as response, open(tmp, "wb") as out:
        shutil.copyfileobj(response, out)
    actual = sha256(tmp)
    if actual != digest:
        tmp.unlink()
        raise SystemExit(f"checksum mismatch for {url}: {actual}")
    tmp.rename(target)
    return target


def setup():
    cache = cache_dir()
    downloads = cache / "downloads"
    root = cache / "gcc447"
    stamp = root / ".complete.json"
    expected = {"rpms": RPMS, "ogre": OGRE[2]}
    if stamp.exists() and json.loads(stamp.read_text()) == expected:
        print(f"toolchain ready: {root}")
        return
    if root.exists():
        shutil.rmtree(root)
    root.mkdir(parents=True)
    for name, digest in RPMS.items():
        rpm = fetch(VAULT + name, downloads / name, digest)
        cpio = subprocess.run(["rpm2cpio", str(rpm)], check=True, capture_output=True).stdout
        subprocess.run(["cpio", "-idmu", "--quiet"], input=cpio, cwd=root, check=True,
                       capture_output=True)
    archive = fetch(OGRE[1], downloads / OGRE[0], OGRE[2])
    ogre = root / "ogre-1.6.5"
    with tarfile.open(archive) as tar:
        members = [m for m in tar.getmembers()
                   if m.name.startswith(("ogre/OgreMain/include/", "ogre/COPYING"))
                   and ".." not in m.name]
        tar.extractall(ogre, members=members, filter="data")
    stamp.write_text(json.dumps(expected, sort_keys=True))
    check = compile_source(None, None, probe=True)
    print(f"toolchain ready: {root}\n  {check}")


def config():
    return json.loads(CONFIG.read_text())


def include_args(root, cfg):
    gcc_inc = root / "usr" / "include" / "c++" / GCC_VERSION
    args = ["-nostdinc", "-nostdinc++"]
    for path in (gcc_inc, gcc_inc / GCC_TRIPLE, gcc_inc / "backward",
                 root / "usr" / "lib" / "gcc" / GCC_TRIPLE / GCC_VERSION / "include",
                 root / "usr" / "include"):
        args += ["-isystem", str(path)]
    for item in cfg.get("include", []):
        args += ["-I", str(ROOT / item)]
    # Generated headers for work in progress (llm_loop.py); committed sources must not need them.
    for item in filter(None, os.environ.get("OTL_EXTRA_INCLUDE", "").split(":")):
        args += ["-I", item]
    for item in cfg.get("system_include", []):
        path = item.replace("@OGRE@", str(root / "ogre-1.6.5" / "ogre"))
        path = path if os.path.isabs(path) else str(ROOT / path)
        args += ["-isystem", path]
    return args


def driver_env(root):
    env = dict(os.environ)
    env["LD_LIBRARY_PATH"] = str(root / "usr" / "lib64")
    env["LC_ALL"] = "C"
    return env


CC_CACHE = Path(__file__).resolve().parents[2] / "build-decomp" / "cc-cache"


def _digest(cmd, source, deps):
    h = hashlib.sha256("\0".join(cmd).encode())
    for path in [source, *deps]:
        try:
            h.update(Path(path).read_bytes())
        except OSError:
            return None
    return h.hexdigest()


def _cache_lookup(cmd, source):
    """Cached output for this command, keyed by the source and the headers it used last time."""
    index = CC_CACHE / (hashlib.sha256(("\0".join(cmd) + str(source)).encode()).hexdigest() + ".json")
    if not index.exists():
        return index, None
    entry = json.loads(index.read_text())
    digest = _digest(cmd, source, entry["deps"])
    if digest and digest == entry["digest"] and (CC_CACHE / entry["output"]).exists():
        return index, CC_CACHE / entry["output"]
    return index, None


def jobs():
    """Parallel compiler processes: OTL_JOBS, by default all cores but one (at most 5)."""
    if os.environ.get("OTL_JOBS"):
        return max(1, int(os.environ["OTL_JOBS"]))
    return max(1, min(5, (os.cpu_count() or 2) - 1))


def parallel_map(fn, items):
    """[fn(x) for x in items] on jobs() threads (the work is in compiler subprocesses), in order;
    the first exception, SystemExit included, is raised after the others finish."""
    items = list(items)
    if jobs() == 1 or len(items) < 2:
        return [fn(x) for x in items]
    with ThreadPoolExecutor(max_workers=jobs()) as pool:
        futures = [pool.submit(fn, x) for x in items]
    return [f.result() for f in futures]


def compile_source(source, output, extra=(), assembly=False, probe=False, quiet=False, cache=True):
    """Compile with GCC 4.4.7-3.el6 and binutils 2.20.51; returns the output path.

    Results are cached in build-decomp/cc-cache by source, dependency and flag
    digests; set OTL_NO_CC_CACHE=1 or cache=False to bypass (side outputs such
    as dumps are not cached)."""
    root = cache_dir() / "gcc447"
    if not (root / ".complete.json").exists():
        raise SystemExit("toolchain missing; run: python3 tools/decomp/toolchain.py setup")
    cfg = config()
    gxx = root / "usr" / "bin" / "g++"
    base = [str(gxx), f"-B{root}/usr/libexec/gcc/{GCC_TRIPLE}/{GCC_VERSION}/", f"-B{root}/usr/bin/"]
    with tempfile.TemporaryDirectory(prefix="otl-cc-") as tmp:
        if probe:
            source = Path(tmp) / "probe.cpp"
            source.write_text("int probe(int x) { return x * 3; }\n")
        out = Path(tmp) / ("out.s" if assembly else "out.o")
        cmd = base + include_args(root, cfg) + list(cfg["cflags"]) + list(extra)
        cmd += ["-S" if assembly else "-c"]
        use_cache = cache and not probe and not os.environ.get("OTL_NO_CC_CACHE")
        if use_cache:
            index, hit = _cache_lookup(cmd, source)
            if hit:
                output = Path(output)
                output.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(hit, output)
                return output
        depfile = Path(tmp) / "out.d"
        cmd_full = cmd + [str(source), "-o", str(out)] + (["-MD", "-MF", str(depfile)] if use_cache else [])
        result = subprocess.run(cmd_full, env=driver_env(root), capture_output=True, text=True)
        if result.returncode:
            if quiet:
                raise SystemExit(f"compile failed: {source}\n{result.stderr}")
            sys.stderr.write(result.stderr)
            raise SystemExit(f"compile failed: {source}")
        if result.stderr.strip() and not quiet:
            sys.stderr.write(result.stderr)
        if probe:
            comment = subprocess.run(["readelf", "-p", ".comment", str(out)], capture_output=True,
                                     text=True).stdout
            if EXPECTED_COMMENT not in comment:
                raise SystemExit(f"unexpected compiler identity:\n{comment}")
            return EXPECTED_COMMENT
        output = Path(output)
        output.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(out, output)
        if use_cache and depfile.exists():
            # Make-style dependency list: "\\ " escapes spaces in paths, "\\\n" continues lines.
            body = depfile.read_text().replace("\\\n", " ").split(": ", 1)[1].replace("\\ ", "\0")
            deps = [d.replace("\0", " ") for d in body.split() if d.replace("\0", " ") != str(source)]
            digest = _digest(cmd, source, deps)
            if digest:
                CC_CACHE.mkdir(parents=True, exist_ok=True)
                name = digest + (".s" if assembly else ".o")
                shutil.copyfile(out, CC_CACHE / name)
                partial = index.with_suffix(f".{os.getpid()}.{id(out)}.tmp")
                partial.write_text(json.dumps({"deps": deps, "digest": digest, "output": name}))
                os.replace(partial, index)
    return output


def assemble(source, output):
    root = cache_dir() / "gcc447"
    subprocess.run([str(root / "usr" / "bin" / "as"), "--64", "-o", str(output), str(source)],
                   env=driver_env(root), check=True)
    return output


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("setup")
    cc = sub.add_parser("cc")
    cc.add_argument("source", type=Path)
    cc.add_argument("-o", "--output", type=Path, required=True)
    cc.add_argument("-S", dest="assembly", action="store_true")
    cc.add_argument("extra", nargs="*")
    sub.add_parser("env")
    args = parser.parse_args()
    if args.command == "setup":
        setup()
    elif args.command == "cc":
        print(compile_source(args.source, args.output, args.extra, args.assembly))
    else:
        root = cache_dir() / "gcc447"
        print(json.dumps({"root": str(root), "config": config(),
                          "include_args": include_args(root, config())}, indent=1))


if __name__ == "__main__":
    main()
