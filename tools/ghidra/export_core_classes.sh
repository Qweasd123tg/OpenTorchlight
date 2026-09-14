#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
ghidra_home="${GHIDRA_HOME:-/tmp/ghidra_12.1.3_PUBLIC}"
analysis_root="${TORCHLIGHT_GHIDRA_ROOT:-/tmp/opentorchlight-ghidra}"
project_file="$analysis_root/project/OpenTorchlight.gpr"
output_dir="$project_root/research/decompiled-core"

if [[ ! -x "$ghidra_home/support/analyzeHeadless" ]]; then
    echo "Ghidra analyzeHeadless is absent: $ghidra_home" >&2
    exit 2
fi
if [[ ! -f "$project_file" ]]; then
    echo "Run tools/ghidra/analyze_original.sh first: $project_file is absent" >&2
    exit 2
fi

mkdir -p "$analysis_root/config" "$output_dir"
export XDG_CONFIG_HOME="$analysis_root/config"

"$ghidra_home/support/analyzeHeadless" \
    "$analysis_root/project" OpenTorchlight \
    -max-cpu 2 \
    -scriptPath "$project_root/tools/ghidra" \
    -process Torchlight.bin.x86_64 -noanalysis \
    -postScript ExportClassDecompilations.java \
        "$project_root/research/decompile-classes.txt" "$output_dir" \
    -log "$analysis_root/core-export.log" \
    -scriptlog "$analysis_root/core-export-script.log"

printf 'Core class decompilations: %s\n' "$output_dir"
