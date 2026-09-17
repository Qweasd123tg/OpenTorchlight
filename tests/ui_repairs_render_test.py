#!/usr/bin/env python3
"""Authored UI regression on actual GLES/Mesa, not original-game pixel parity."""
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
            probe = lib.render_ui_repairs_probe
            probe.argtypes = [C.c_char_p, C.c_int, C.POINTER(C.c_ubyte), C.c_char_p, C.c_uint]
            probe.restype = C.c_int
            width, height = 256, 192
            frames = []
            for stage in range(12):
                pixels = (C.c_ubyte * (width * height * 4))()
                error = C.create_string_buffer(2048)
                if probe(os.fsencode(args.fixture), stage, pixels, error, len(error)):
                    raise RuntimeError(error.value.decode())
                frames.append(bytes(pixels))
            def pixel(frame: bytes, x: int, y: int) -> tuple[int, ...]:
                offset = ((height - 1 - y) * width + x) * 4
                return tuple(frame[offset:offset+4])
            assert frames[0] == frames[1] == frames[11], 'empty overlay still paints over the game'
            assert frames[0] != frames[2], 'explicit diagnostics disappeared'
            assert frames[0] != frames[3], 'modal inventory overlay disappeared'
            assert frames[0] == frames[5], 'zero clip was treated as no clip'
            assert pixel(frames[4],40,40)[0] > 240, 'visible clipped image missing'
            for x,y in ((20,40),(60,40),(40,20),(40,55)):
                assert pixel(frames[4],x,y) == pixel(frames[0],x,y), 'image leaked outside clip'
            assert frames[6] == frames[7], 'empty original image became a PORT rectangle'
            assert frames[6] != frames[8], 'supplemental control fallback disappeared'
            assert frames[6] == frames[10], 'explicit empty DisabledImage inherited NormalImage'
            for y in (50,51,75,98,99):
                rgba=pixel(frames[9],70,y)
                assert rgba[1]>240 and rgba[0]<10, ('invented selection border',y,rgba)
            print('PASS: 12 actual GLES frames; clipping, empty skins, selection chrome, opt-in diagnostics')
        return 0
    except Unavailable as exc:
        print('NOT RUN:',exc); return 77
    except Exception as exc:
        print('FAIL:',exc,file=sys.stderr); return 1


if __name__ == '__main__':
    raise SystemExit(main())
