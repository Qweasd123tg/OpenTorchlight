# Upstream source matching + static pipeline, layer 1

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
All reads static; game never executed. Toolchain lives OUTSIDE the repo
(`~/.local/toolchain`, never committed).

## 1. Library inventory (tool `tools/lib_inventory.py`, data `lib-inventory.*`)

Dynamically linked — code lives in shipped `.so`, NOT in the 17k:
OgreMain-1.6.5 (7698 exports), CEGUIBase (6338), CEGUIOgreRenderer-1.6.5 (54),
FMOD 4.36.21 (3632), FreeImage (344), zzip/SDL2/PCRE/X11/libc (system).
Static third-party symbol hits inside the main binary: ParticleUniverse 9057,
STL 1673, Ogre-inline 781, CEGUI-inline 450, lodepng 103, ConvertUTF 7.

Version pins: Ogre **1.6.5** (SONAME, certain); FMOD **4.36.21** (SONAME,
certain); CEGUI **0.6.x** (`FastLessCompare` ABI + OgreRenderer-1.6.5 pairing,
inferred — needs API-diff confirmation); lodepng **≈2014 API**
(API-set overlap 76/85 vs 2014-12-01, method §2); ParticleUniverse unknown
(MacPort_09b tree paths only); compilers GCC 4.1.2/4.4.6/4.4.7.

## 2. lodepng sanity proof (source-match workflow validates)

Upstream: lvandeve/lodepng @ `bf09e0a` (2014-12-01), fetched read-only to
`/tmp` (never committed).
- `lodepng_read32bitInt @0xf633c0` (0x1f B): big-endian assembly
  `b[0]<<24|b[1]<<16|b[2]<<8|b[3]` == source line 343, op-for-op.
- `lodepng_crc32 @0xf635a0` (0x92 B): lazy table build with polynomial
  `0xedb88320` + `Crc32_crc_table_computed` guard == upstream table-driven
  CRC pattern.
Workflow (symbol → upstream file → body correspondence) works on real code.
lodepng/ConvertUTF (104 fns) currently sit in triage `manual` — they are the
first source-match batch, not manual labor.

## 3. Recount of the 17 023 (measured, replaces hand-waving)

`external_source_first` (3555) decomposes by symbol to: ParticleUniverse
**2976**, STL **393**, Ogre-inline **186**, other **0**.
(`ogre_static`/`stl`/`particle_universe` patterns; check re-runnable.)

New working layout:
- dynamic-lib code: 0 in main binary (separate .so; match by SONAME+dynsym
  only when behavior is needed, e.g. CEGUI renderer calls);
- static PU 2976 + lodepng/ConvertUTF 104 → source-match queue (was: manual);
- STL 393 + Ogre-inline 186 + CEGUI-inline → header/runtime match or
  compiler-glue join (audit open);
- manual residue 3173 minus the 104 above ≈ **3069**, of which 543 already in
  196 shape clusters.

## 4. Ghidra headless: OPERATIONAL (2026-09-18)

- `~/.local/toolchain/jdk-21.0.7+6` (Temurin; system JDK 25 is REJECTED by
  Ghidra — must put JDK 21 first in PATH, JAVA_HOME alone is not enough) +
  `ghidra_11.3.2_PUBLIC`.
- `analyzeHeadless /tmp/opencode/ghidra-proj TorchProj -import <elf>
  -noanalysis`: **import OK** (project created; R_X86_64_COPY warnings for
  .so-provided data are benign).
- Next: scripted export pass (decomp/ASM/CFG/callers/callees/xrefs/strings/
  field refs → JSON per function). Full auto-analysis is RAM-risky here
  (7 GB box, ~1 GB free) — run sharded or with capped analyzers.
- BSim ships with Ghidra (`support/bsim`) but needs PostgreSQL, which is NOT
  installed (no sudo/apt) — BSim/BinDiff stay "scripts-ready, DB pending";
  no vapor was added for them.

## 5. Open / next

- CEGUI exact version (0.6.2 vs 0.7.x API diff against libCEGUIBase dynsym).
- ParticleUniverse version pin (SystemManager strings).
- lodepng 8 binary-only API names (compat wrappers vs Runic edits).
- Ghidra export-pass script + first JSON batch.
- Emitter: blocked on confirmed field maps (none new) — correctly emits zero.
