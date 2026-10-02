#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
game_dir="${1:-/home/qweasd123tg/Games/Torchlight/game}"
source "$project_root/tools/ghidra/environment.sh"
binary="$game_dir/Torchlight.bin.x86_64"
expected_sha="91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"

if [[ ! -x "$ghidra_home/support/analyzeHeadless" ]]; then
    printf 'Ghidra analyzeHeadless is absent: %s\n' "$ghidra_home" >&2
    exit 2
fi
if [[ ! -f "$binary" ]]; then
    printf 'Original Torchlight ELF is absent: %s\n' "$binary" >&2
    exit 2
fi
actual_sha="$(sha256sum "$binary" | cut -d' ' -f1)"
if [[ "$actual_sha" != "$expected_sha" ]]; then
    printf 'Unsupported Torchlight ELF SHA-256: %s\n' "$actual_sha" >&2
    exit 2
fi

mkdir -p "$analysis_root/config" "$analysis_root/output" "$analysis_root/project"
export XDG_CONFIG_HOME="$analysis_root/config"

common=(
    "$analysis_root/project" OpenTorchlight
    -max-cpu 2
    -analysisTimeoutPerFile 3600
    -scriptPath "$project_root/tools/ghidra"
    -postScript ExportTargetDecompilations.java
        "$project_root/research/decompile-targets.txt"
        "$analysis_root/output"
    -log "$analysis_root/ghidra.log"
    -scriptlog "$analysis_root/script.log"
)

if [[ -f "$analysis_root/project/OpenTorchlight.gpr" ]]; then
    "$ghidra_home/support/analyzeHeadless" "${common[@]}" \
        -process Torchlight.bin.x86_64 -noanalysis
else
    "$ghidra_home/support/analyzeHeadless" "${common[@]}" \
        -import "$binary"
fi

printf 'Ghidra database: %s/project/OpenTorchlight.gpr\n' "$analysis_root"
printf 'Selected decompilations: %s/output\n' "$analysis_root"
