#!/usr/bin/env python3
"""Compile-check the unchanged gameplay section without Wayland/EGL headers.

Only DesktopWindow/require_egl are replaced by declarations. This is explicitly
NOT a desktop build, link test, rendering test or validation of Wayland APIs.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, required=True)
    parser.add_argument('--compiler', required=True)
    args = parser.parse_args()
    source = (args.root / 'src/linux_desktop_main.cpp').read_text()
    for include in ('EGL/egl.h', 'GLES2/gl2.h', 'wayland-client.h', 'wayland-egl.h',
                    'xdg-shell-client-protocol.h'):
        source = source.replace(f'#include <{include}>\n', '')
    start = source.index('void require_egl(')
    end = source.index('struct LoadedDesktopLevel {', start)
    window_declaration = '''
class DesktopWindow {
public:
    DesktopWindow(int, int);
    bool process_events();
    std::optional<std::array<int, 2>> take_left_click();
    std::vector<std::uint32_t> take_key_presses();
    int width() const noexcept;
    int height() const noexcept;
    void draw_scene_frame(torchlight::GlesSceneRenderer&,
                          const std::vector<torchlight::InventoryViewLine>&, bool);
};
'''
    source = source[:start] + window_declaration + source[end:]
    with tempfile.TemporaryDirectory(prefix='torchlight-gameplay-syntax-') as directory:
        path = Path(directory) / 'gameplay.cpp'
        path.write_text(source)
        result = subprocess.run([args.compiler, '-std=c++17', '-fsyntax-only', '-Wall',
                                 '-Wextra', '-Wpedantic', '-Werror',
                                 '-I' + str(args.root / 'include'), str(path)], check=False)
    if result.returncode == 0:
        print('Desktop gameplay section type-checked; window/GL wrapper excluded, no linking or rendering.')
    return result.returncode


if __name__ == '__main__':
    raise SystemExit(main())
