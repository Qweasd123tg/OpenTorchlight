# Core game runtime exports

This directory contains Ghidra pseudocode for 1,552 functions from 36 central
Torchlight runtime classes. The selection covers characters, player state,
equipment, models, animation, combat, skills, effects, missiles, AI, paths,
levels, spawning, triggers, and the main game loop. It excludes third-party
libraries, editor UI, and bulk resource descriptors.

The source executable is
`Torchlight.bin.x86_64`, SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Seventeen functions record an explicit decompilation failure inside their
class file; their symbols and addresses remain available in
`../original-symbols.txt` for targeted assembly export.

Regenerate this directory from the saved Ghidra project with:

```sh
tools/ghidra/export_core_classes.sh
```

The class selection is defined in `../decompile-classes.txt`. Ghidra pseudocode
is navigation evidence; verify conclusions against assembly, resources, or a
differential execution test before changing the implementation.
