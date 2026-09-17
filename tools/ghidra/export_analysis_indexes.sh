#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
game_dir="${1:-/home/qweasd123tg/Games/Torchlight/game}"
ghidra_home="${GHIDRA_HOME:-/tmp/ghidra_12.1.3_PUBLIC}"
analysis_root="${TORCHLIGHT_GHIDRA_ROOT:-/tmp/opentorchlight-ghidra}"
binary="$game_dir/Torchlight.bin.x86_64"
expected_sha="91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"

if [[ ! -x "$ghidra_home/support/analyzeHeadless" ]]; then
    echo "Ghidra analyzeHeadless is absent: $ghidra_home" >&2
    exit 2
fi
if [[ ! -f "$analysis_root/project/OpenTorchlight.gpr" ]]; then
    echo "Run tools/ghidra/analyze_original.sh first" >&2
    exit 2
fi
actual_sha="$(sha256sum "$binary" | cut -d' ' -f1)"
if [[ "$actual_sha" != "$expected_sha" ]]; then
    echo "Unsupported Torchlight ELF SHA-256: $actual_sha" >&2
    exit 2
fi

mkdir -p "$analysis_root/config"
export XDG_CONFIG_HOME="$analysis_root/config"

"$ghidra_home/support/analyzeHeadless" \
    "$analysis_root/project" OpenTorchlight \
    -max-cpu 2 \
    -scriptPath "$project_root/tools/ghidra" \
    -process Torchlight.bin.x86_64 -noanalysis \
    -postScript ExportCallGraph.java "$project_root/research/original-callgraph.tsv" \
    -log "$analysis_root/index-export.log" \
    -scriptlog "$analysis_root/index-export-script.log"

strings -a -t x -n 5 "$binary" |
    sed 's/[[:blank:]]*$//' > "$project_root/research/original-strings.txt.tmp"
mv "$project_root/research/original-strings.txt.tmp" \
   "$project_root/research/original-strings.txt"

printf 'Call graph: %s/research/original-callgraph.tsv\n' "$project_root"
printf 'ELF strings: %s/research/original-strings.txt\n' "$project_root"
