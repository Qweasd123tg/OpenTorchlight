#!/usr/bin/env python3
"""Verify the supplied patch in a temporary tree; never patch the user's repository."""
from __future__ import annotations
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

FILES = ("tools/decomp/ghidra_draft.py", "tools/decomp/ghidra/DecompDrafts.java")

def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("repo", type=Path, help="Root of the original OpenTorchlight source snapshot")
    parser.add_argument("--out", type=Path, default=Path("pass9-check-results"))
    parser.add_argument("--benchmark", action="store_true", help="Also measure two unchanged C++ source files with host g++")
    args = parser.parse_args()
    repo, output = args.repo.resolve(), args.out.resolve()
    package = Path(__file__).resolve().parent
    for relative in FILES:
        if not (repo / relative).is_file():
            parser.error(f"Required file is missing: {repo / relative}")
    if shutil.which("git") is None:
        parser.error("git is required to check and apply the patch in a temporary directory")
    output.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE="1")
    with tempfile.TemporaryDirectory(prefix="otl-pass9-check-") as directory:
        preview = Path(directory)
        for relative in FILES:
            destination = preview / relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(repo / relative, destination)
        patch = package / "patches/draft-retry-isolation.patch"
        subprocess.run(["git", "apply", "--check", str(patch)], cwd=preview, env=env, check=True)
        subprocess.run(["git", "apply", str(patch)], cwd=preview, env=env, check=True)
        compile((preview / FILES[0]).read_text(), FILES[0], "exec")
        subprocess.run([sys.executable, str(package / "scripts/test_drafts.py"), str(repo),
                        str(preview), str(output / "draft-regressions.json")], env=env, check=True)
    if args.benchmark:
        subprocess.run([sys.executable, str(package / "scripts/benchmark_pch.py"), str(repo), str(output)],
                       env=env, check=True)
    print(f"Results: {output}\nThe repository was not patched. Ghidra and the game were not executed.")
    return 0

if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, subprocess.CalledProcessError) as error:
        print(f"Check failed: {error}", file=sys.stderr)
        raise SystemExit(1)
