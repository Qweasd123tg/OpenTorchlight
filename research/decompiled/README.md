# Targeted Ghidra exports

This directory contains 36 address-scoped exports from the original Linux
executable identified in ../decompiler-workflow.md: 33 decompiled C
files and 3 explicit decompiler failure records. The matching assembly
for failed targets is stored in ../disassembly/. Regenerate the exports with
tools/ghidra/analyze_original.sh and synchronize them with
tools/ghidra/sync_target_decompilations.sh.

Pseudocode is a navigation aid. Confirm material conclusions against assembly,
resources, or a differential execution test.
