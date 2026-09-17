#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
output="${1:-$root_dir/OpenTorchlight-gpt-pro.zip}"

cd "$root_dir"
mapfile -d '' files < <(git ls-files --cached --others --exclude-standard -z)
if (( ${#files[@]} == 0 )); then
    echo "No project files found" >&2
    exit 1
fi

rm -f "$output"
zip -q "$output" "${files[@]}"
echo "Created $output with ${#files[@]} files ($(du -h "$output" | cut -f1))"
