#!/usr/bin/env python3
"""Original-skin button states on actual GLES/Mesa via the real frame path.

Fixture Test/Toggle: Normal draws the red base, focused draws the green
Hover layer, supplemental PORT buttons keep the fallback chrome (the skin
path must not engage). Not original-game pixel parity.
"""
from __future__ import annotations
import argparse
import ctypes as C
import os
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from egl_context import surfaceless, Unavailable


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, required=True)
    parser.add_argument('--fixture', type=Path, required=True)
    args = parser.parse_args()
    try:
        with surfaceless():
            lib = C.CDLL(str(args.probe.resolve()))
            probe = lib.render_skin_button_probe
            probe.argtypes = [C.c_char_p, C.c_int, C.c_int, C.c_int,
                              C.POINTER(C.c_ubyte), C.c_char_p, C.c_uint]
            probe.restype = C.c_int
            width, height = 256, 192
            frames = []
            for mode in (0, 1, 2):
                pixels = (C.c_ubyte * (width * height * 4))()
                error = C.create_string_buffer(2048)
                if probe(os.fsencode(args.fixture), width, height, mode,
                         pixels, error, len(error)):
                    raise RuntimeError(error.value.decode())
                frames.append(bytes(pixels))

            def pixel(frame: bytes, x: int, y: int) -> tuple[int, ...]:
                offset = ((height - 1 - y) * width + x) * 4
                return tuple(frame[offset:offset + 4])

            normal = pixel(frames[0], 80, 72)
            assert normal[:3] == (255, 0, 0), ('Normal base not red', normal)
            hover = pixel(frames[1], 80, 72)
            assert hover[:3] == (0, 255, 0), ('Hover layer not green', hover)
            fallback = pixel(frames[2], 80, 72)
            assert fallback[:3] not in ((255, 0, 0), (0, 255, 0)), (
                'skin path engaged for supplemental button', fallback)
            assert frames[0] != frames[1], 'focus changed nothing'
            print('PASS: 3 actual GLES frames; skin Normal/Hover states, PORT fallback kept')
        return 0
    except Unavailable as exc:
        print('NOT RUN:', exc)
        return 77
    except Exception as exc:
        print('FAIL:', exc, file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
