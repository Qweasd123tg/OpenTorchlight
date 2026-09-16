#!/usr/bin/env python3
"""Run the actual common application loop with scripted physical input and real GLES.
Golden outputs are port regressions, not original-game reference measurements.
"""
from __future__ import annotations
import argparse
import ctypes as C
import hashlib
import json
import os
from pathlib import Path
import sys
from egl_context import surfaceless, Unavailable

def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()

def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--library", type=Path, required=True)
    p.add_argument("--game-dir", type=Path, required=True)
    p.add_argument("--save-dir", type=Path, required=True)
    p.add_argument("--script", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    for path in (a.library, a.script, a.game_dir / "pak.zip"):
        if not path.is_file():
            p.error(f"required input missing: {path}")
    a.output = a.output.resolve()
    if a.output.exists() and any(a.output.iterdir()):
        p.error("output must be a fresh/empty directory (captures are never overwritten)")
    game, saves = a.game_dir.resolve(), a.save_dir.resolve()
    if saves == game or game.is_relative_to(saves) or (saves / "pak.zip").exists():
        p.error("save directory must be isolated from the game/resources directory")
    if a.output == saves or a.output.is_relative_to(saves) or saves.is_relative_to(a.output):
        p.error("capture and save directories must not overlap")
    # The repository may be the game's parent directory; outputs are explicit,
    # so explicit dedicated child directories are allowed; game inputs are never replaced.
    if a.output == game or game.is_relative_to(a.output):
        p.error("capture output must not replace or contain the game/resources directory")
    a.output.mkdir(parents=True, exist_ok=True)
    evidence = {"schema": 1, "status": "RUNNING", "evidence": "port-regression-not-original",
                "pak_sha256": sha256(game / "pak.zip"), "script_sha256": sha256(a.script),
                "library_sha256": sha256(a.library), "clock": "scripted dt; default 1/60, optional [0,0.1]; not original scheduler",
                "input": "same menu/key/pointer handlers as Wayland; no OS input delivery"}
    rc = 1
    try:
        with surfaceless() as context:
            evidence["graphics"] = context
            print(json.dumps(context), flush=True)
            lib = C.CDLL(os.fspath(a.library.resolve()))
            run = lib.run_application_scenario
            run.argtypes = [C.c_char_p] * 4 + [C.c_char_p, C.c_uint]
            run.restype = C.c_int
            error = C.create_string_buffer(8192)
            rc = run(os.fsencode(game), os.fsencode(saves), os.fsencode(a.script.resolve()),
                     os.fsencode(a.output), error, len(error))
            if rc:
                raise RuntimeError(error.value.decode("utf-8", "replace"))
        evidence["status"] = "PASSED"
        print("PASSED common application scenario; no original process or Wayland window executed")
    except Unavailable as exc:
        evidence.update(status="NOT RUN", error=str(exc))
        print(f"NOT RUN: {exc}", file=sys.stderr)
        rc = 77
    except Exception as exc:
        evidence.update(status="FAILED", error=str(exc))
        print(f"FAILED: {exc}", file=sys.stderr)
        rc = 1
    finally:
        (a.output / "environment.json").write_text(json.dumps(evidence, indent=2) + "\n")
    return rc
if __name__ == "__main__":
    raise SystemExit(main())
