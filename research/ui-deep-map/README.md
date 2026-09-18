# UI deep-map: provenance and status

External bundle: `OpenTorchlight-UI-deep-map(1).zip`
SHA-256 `c951ee2bbcc984a49fee627f3fa1b38107e80ca82b61c2f1796d0313791328eb`
(base: large-16, 860 files; static audit only — nothing in it was compiled
or executed by its author).

## What was imported here and why

- `01–12-*.md`: 12 evidence fragments (UI frame composition, input, layouts,
  looknfeel, fonts, mesh parser, HUD, render scenes, inventory open/anchors/
  events). Status: analysis with original-code addresses (`reference/asm/`
  in the bundle), NOT port behavior claims. Used as an index for future UI
  passes; each future patch still needs its own differential proof.
- `mesh_boundaries.json`: physical-chunk evidence behind U03 (18 submesh
  parts, 72 local bone assignments in 7 UI meshes). Consumed by the applied
  `src/ogre_mesh.cpp` trailing-records fix; per-file counts re-verified
  against pak bytes (character 12, inventory 8, journal 12, merchant 8,
  pet 8, quest 12, skill 12; dropdown's 6 shared bindings excluded).

## What was deliberately NOT imported

- `data/widgets*.json`, `imagesets.json`, `looknfeel.json`, `schemes.json`,
  `original_ui_*.tsv`, `resources.json`, `ui_skeletons.json`,
  `ui_material_descriptors.json`, `menu_background_resources.json`,
  `animation_descriptors.json` (~1.7 MB of derived metadata): reproducible
  from the bundle's `tools/extract_ui_reference.py` + `scan_ui*.py` against
  the real pak; referenced here by bundle path, not copied.
- `reference/asm/*` (55 bounded exports incl. `convertToScreenScale @0xa83ed0`,
  `rescaleUI @0x5791c0`, `getIsPaused @0x56e570`, `mapEventHandlers @0xa97e00`,
  `CInventoryMenu::update @0xb4f9d0`, CEGUI 0.6.2 excerpts): stays in the
  external bundle; pulled per-patch when a UI boundary is implemented.
- No ELF, library, font, texture or full-disassembly content is redistributed.

## Applied from this bundle

- U03 mesh-bindings candidate (`patch-source-only/ui-mesh-bindings.patch`):
  applied after base-hash match, byte-level pak verification and a full-pak
  parse run (3312 meshes; delta exactly +72, all other totals unchanged).
  The candidate's own "not compiled, not executed" caveat is discharged by
  `original_ogre_meshes` (477080) plus the per-file check above.
- U01–U02, U04–U25: open. In particular U06 (screen scale) overlaps the
  `backup-pre-large16` P1 evidence; U19 confirms the large-16 HUD-down fix
  must be kept and NOT extended to all controls.
