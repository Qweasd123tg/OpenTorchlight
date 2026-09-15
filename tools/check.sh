#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
# Keep portable checks in a separate cache, without touching the original-game
# configuration or running the resource audit against missing files.
if [[ "${1:-}" == "--portable" ]]; then
    if [[ "$#" -ne 1 ]]; then
        printf 'Usage: %s --portable\n' "$0" >&2
        exit 2
    fi
    portable_build="$project_root/build-portable"
    cmake -S "$project_root" -B "$portable_build" -G Ninja \
        -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DTORCHLIGHT_ORIGINAL=
    cmake --build "$portable_build" --parallel "${TORCHLIGHT_BUILD_JOBS:-2}"
    ctest --test-dir "$portable_build" --output-on-failure
    printf 'Portable tests passed; original-game checks and UI audit were not run.\n'
    exit 0
fi

default_game_dir="/home/qweasd123tg/Games/Torchlight/game"
game_dir="${1:-$default_game_dir}"
original="$game_dir/Torchlight.bin.x86_64"

if [[ ! -f "$original" || ! -f "$game_dir/pak.zip" ]]; then
    printf 'Torchlight files were not found in: %s\n' "$game_dir" >&2
    printf 'Usage: %s [path-to-Torchlight-game-directory | --portable]\n' "$0" >&2
    exit 2
fi

cmake --preset dev -S "$project_root" \
    -DTORCHLIGHT_ORIGINAL="$original"
cmake --build --preset dev --parallel "${TORCHLIGHT_BUILD_JOBS:-2}"
ctest --preset dev --test-dir "$project_root/build"
python3 "$project_root/tools/audit_original.py" \
    --game-dir "$game_dir" \
    --output "$project_root/research"

printf 'Build, original comparison, and UI audit passed.\n'
