# ParticleUniverse: version pin + source-match strategy

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Static reads only. Upstream clone (OGRECave/particleuniverse, 1.6-era) lives
in `/tmp`, never committed.

## 1. Version: PU 1.0, pre-1.01 (measured, not guessed)

Discriminators from the 1.6 `Changelog.txt` tested against
`research/original-symbols.txt` (hit counts):
- 1.2 markers all ABSENT: `setSpatialHashingUsed` 0 (old `setSpatialHashing`
  present, 4), `BeamRenderer` 0, `setUseController` 0, `startFade` 0,
  `isAutoLoadMaterials` 0, `nedmalloc` 0.
- 1.3 markers all ABSENT: `BaseCollider`, `BaseForceAffector`,
  `VelocityAffector`, `FlashFrequency`, `removeAndDestroyDanglingSceneNodes`
  all 0.
- 1.1 markers all ABSENT: `copyParentAttributeTo` 0,
  `getFastForwardInterval` 0.
- 1.01 marker ABSENT: `destroyTemplate` 0 while
  `removeAllParticleSystemTemplates` 1 → pre-1.01.
- 1.0 features PRESENT: `TextureAnimator` 71, `getParticleSystem` 1,
  `Serializer` 6, `setFixedTimeout` 1. No PhysX (optional, excluded by Runic).
- Consistent with Ogre 1.6.5 + Torchlight 2009. Runic tree:
  `TorchlightMacPort_09b/.../ParticleUniverse` (build paths in binary).

Caveats: `stopFade`/`pause(Real)` (listed under 1.0) absent — possibly inlined
or Runic-trimmed; does not move the pin (all later-version markers absent).

## 2. PU 1.0 source: NOT found online (searched 2026-09-18)

GitHub OGRECave history starts at 1.6 ("First commit, 2013"); fxpression.com
dead; SourceForge ogreaddons has no PU files area reachable; Bitbucket
ogreaddons has no particleuniverse repo; archive.org has no PU 1.0 item.
OPEN: keep looking (old Ogre SDK bundles, vendored game trees); do NOT block
matching on it.

## 3. 1.6-superset strategy + MANDATORY drift warning

Name overlap (rough regexes, batching hint only): binary 1925
`PU::Class::method` pairs vs 1.6 1773 defs → **1023 shared + 16 via
changelog renames** (Collider→BaseCollider, ForceAffector→BaseForceAffector).
Proven drift (verify-every-match rule):
- `DynamicAttributeFixed::getValue`: 1.0 takes `(Particle*, float)`, returns
  `mValue@+0x0c` (`ee0c90: movss 0xc(%rdi)`); 1.6 takes `(Real x = 0)`. Same
  intent, different signature/vtable slot — blind name matching would emit a
  wrong override.
- `ParticleEmitter::isKeepLocal @0xee27d0`: `movzbl +0x259` vs 1.6
  `mKeepLocal` — layouts MUST be re-derived per version, never transferred
  (consistent with the project offsets rule).
Rule: 1.6 source is valid for algorithm intent; every emitted match needs
signature + body + layout verification against the 1.0 binary.

## 4. Mass-match plan (Line A queue)

1. Per-function: symbol → 1.6 body candidate → objdump body compare →
   `library-derived` + drift notes, or `modified-upstream` on mismatch.
2. Priority inside PU: renderers/emitters/affectors actually instantiated by
   Torchlight `.pu` scripts in `pak.zip` (game-reachable subset first —
   Line B pulls from the same list).
3. Ghidra export pass (once scripted) replaces objdump skimming for bodies.
