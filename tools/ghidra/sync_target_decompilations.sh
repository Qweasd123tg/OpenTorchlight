#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
source_dir="${1:-${TORCHLIGHT_GHIDRA_ROOT:-$root_dir/build-ghidra}/output}"
target_dir="$root_dir/research/decompiled"
targets_file="$root_dir/research/decompile-targets.txt"

if [[ ! -d "$source_dir" ]]; then
    echo "Ghidra export directory not found: $source_dir" >&2
    exit 1
fi

mkdir -p "$target_dir"
find "$target_dir" -maxdepth 1 -type f -name '*.c' -delete
find "$target_dir" -maxdepth 1 -type f -name '*.error.txt' -delete

count=0
decompiled=0
failed=0
while read -r address label extra; do
    [[ -z "${address:-}" || "$address" == \#* ]] && continue
    if [[ -n "${extra:-}" ]]; then
        echo "Invalid target line: $address $label $extra" >&2
        exit 1
    fi

    source_file="$source_dir/$label.c"
    error_file="$source_dir/$label.error.txt"
    if [[ -f "$source_file" ]]; then
        expected="${address#0x}"
        expected="${expected,,}"
        actual="$(sed -n 's@^/\* address=\([[:xdigit:]]*\).*@\1@p' "$source_file" | head -n 1)"
        actual="${actual,,}"
        if [[ "$actual" != "${expected#00}" && "${actual#00}" != "${expected#00}" ]]; then
            echo "Address mismatch for $label: expected $address, got ${actual:-none}" >&2
            exit 1
        fi
        cp "$source_file" "$target_dir/$label.c"
        decompiled=$((decompiled + 1))
    elif [[ -f "$error_file" ]]; then
        cp "$error_file" "$target_dir/$label.error.txt"
        failed=$((failed + 1))
    else
        echo "Missing targeted export or error marker for $label" >&2
        exit 1
    fi
    count=$((count + 1))
done < "$targets_file"

cat > "$target_dir/README.md" <<EOF
# Targeted Ghidra exports

This directory contains $count address-scoped exports from the original Linux
executable identified in ../decompiler-workflow.md: $decompiled decompiled C
files and $failed explicit decompiler failure records. The matching assembly
for failed targets is stored in ../disassembly/. Regenerate the exports with
tools/ghidra/analyze_original.sh and synchronize them with
tools/ghidra/sync_target_decompilations.sh.

Pseudocode is a navigation aid. Confirm material conclusions against assembly,
resources, or a differential execution test.
EOF

echo "Synchronized $count targets ($decompiled C, $failed errors) into $target_dir"
