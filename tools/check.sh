#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
default_game_dir="/home/qweasd123tg/Документы/Torchlight/game"
game_dir="${1:-$default_game_dir}"
original="$game_dir/Torchlight.bin.x86_64"

if [[ ! -f "$original" || ! -f "$game_dir/pak.zip" ]]; then
    printf 'Torchlight files were not found in: %s\n' "$game_dir" >&2
    printf 'Usage: %s [path-to-Torchlight-game-directory]\n' "$0" >&2
    exit 2
fi

cmake --preset dev -S "$project_root" \
    -DTORCHLIGHT_ORIGINAL="$original"
cmake --build --preset dev
ctest --preset dev --test-dir "$project_root/build"
python3 "$project_root/tools/audit_original.py" \
    --game-dir "$game_dir" \
    --output "$project_root/research"

printf 'Build, original comparison, and UI audit passed.\n'
