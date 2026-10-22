# Deterministic exact-object screening

`deterministic_screen.py` is a read-only-input, single-TU, exact-existing-object
orchestrator. It does not recover source, compile C++, call a model, execute the
game, update owners/progress or publish anything. Output is one new JSON file
outside the worktree. Existing output is never overwritten; Python bytecode
writes are disabled. Temporary files inside the unchanged comparator are still
permitted. Unknown cases remain DIFF; no fallback to a model exists.

## Operation

```
python3 -B deterministic_screen.py \
  --manifest /absolute/reviewed-manifest.json \
  --manifest-sha256 <digest supplied by independent review> \
  --output /absolute/new-report.json [--full-on-gain]
```

The caller must supply a manifest and digest whose provenance has been reviewed.
There is intentionally **no automatic “trust current paths” adapter** for old
batch files. A digest is an integrity binding, not evidence that the source was
compiled into the object. The source/object/dependency/compiler binding is an
explicit external reviewed premise. A manifest author able to forge all its
receipts can forge that premise; this script is not an authenticity authority.
Missing or stale bindings fail closed rather than being re-created from current
hashes. Equivalent-but-byte-different headers are not supported in this first
version; they need a separately reviewed adapter/rule, not a boolean assertion.

1. Verify the externally pinned manifest, exact files, current whole tool closure,
   internal header coverage, ownership and source/object compilation binding.
2. Verify prior full-TU result, exact input identity and baseline tool files.
3. Load the declared DB/ELF and pinned literal library. Pin the actual resolved
   `objdump` binary. Use existing `compare_source`, loading an exact prebuilt
   object instead of compiling. All object metadata is parsed unchanged; only
   selected original-function comparisons are screened.
4. Report selected rows and original/object evidence. This is partial evidence,
   **not acceptance**. Aliases are deduplicated by original address; an address
   with any prior MATCH alias is not a new canonical gain.
5. With `--full-on-gain`, only a newly matching canonical candidate triggers a
   second, cold full-TU comparison. Require identical row inventory (including
   missing/extras/aliases), unchanged unknown-reference list and object identity,
   exact preservation of every prior MATCH dictionary, and selected rows equal
   to the screening result.
6. Recheck all input identities and inventories before writing the output.

A full successful run sets `validated_comparator_report=true`, **never**
`promotion_authorized=true`. It does not mutate or promote a ledger. No-new-gain
runs stay `screening_only=true`, even if `--full-on-gain` was supplied. Multi-TU
impact analysis of comparator changes remains a separate integration requirement.
Concurrent hostile replace-and-restore of files is outside this local reviewed
workspace trust model: before/after hashes detect ordinary mutation, not a
transactional filesystem snapshot. Run against immutable/quiescent inputs.

## Manifest schema 1

All file paths are absolute and SHA256 identities are full hex digests.

- `schema`: `1`; `scope`: `"exact-object-single-tu"`.
- `worktree`, `tu`, `owner`: explicit root, `STT_FILE` name and registry owner.
- `inputs`: exactly `source`, `object`, `database`, `elf`, `library`, `owners`,
  `config`, `objdump`; each is `{ "path": "...", "sha256": "..." }`.
- `tool_files`: path → SHA256 map covering exactly all `tools/decomp/**/*.py`.
- `dependencies`: path → SHA256 map of original compile dependencies, including
  all current `decomp/include` files and external/system dependencies from the
  reviewed compilation receipt. This tool checks the stated map, not discovery
  through a compiler.
- `compiler_files`: nonempty path → SHA256 compiler/assembler identity map.
  These files are hashed, **never executed**.
- `baseline_tool_files`: nonempty exact prior comparator dependency map.
- `provenance`: nonempty map binding the independently reviewed compiler,
  source/object and dependency evidence artifacts.
- `binding`, `baseline_result`, `baseline_receipt`: each `{path, sha256}`.
- `selected`: nonempty unique list of `{name, address}` identifying existing
  MATCH/DIFF baseline rows; both name and original address must agree.

`common_identity` is exactly a map of all eight input-role SHA256 values, plus
`dependencies` and `compiler_files` maps. It is reproduced in both receipts.

The `binding` document contains `schema:1`, this `common_identity`, exact parsed
`compiler_config` equal to `decomp/config.json`, and the reviewed `globalized`
list from producing the object.

`baseline_result` is the complete unchanged comparator result for the TU. Every
row must bind the same full object digest. `baseline_receipt` contains
`scope:"full-tu"`, `common_identity`, `result_sha256`, `tool_files` equal to the
baseline map and complete `row_keys` as `[name,address-or-null]` pairs. The
screen stage checks that every parsed object symbol appears in the baseline;
full validation additionally requires exactly identical complete row inventories.
The external review of this receipt establishes that it came from a real full
comparison; labels alone do not establish that fact.

## Output completeness

The report includes scope flags, all appropriate result dictionaries, unknown
references, object digest, canonical new addresses, manifest SHA and checked
input identities. `screen_evidence` contains full object normalization/EH
records and selected original normalization/metadata/literal certificates.
A full validated run also includes `full_evidence` with complete original
normalization records for emitted functions and full result rows. A missing row
has no manufactured original proof. No historical test-PASS or runtime claim is
inferred from MATCH.

## Validation and current limitations

```
python3 -B -m unittest -v test_deterministic_screen
```

Pure synthetic fixtures test identities, baseline binding, owner/address gates,
missing/extra/duplicate/alias completeness, unknown-reference regressions,
exact prior MATCH retention, mutation detection and wrapper restoration.
One independently reviewed historical ExecuteSkillProps existing-object smoke
verified both screen-only (2 selected rows) and optional full-TU (39 rows) modes
against frozen comparator results, including normalization and EH evidence.
It used an exact-byte historical compile-input snapshot, not a fresh current-header
build. Copied source/object/library/baseline mutations were rejected. No source
compilation, game/runtime test or broader source batch was executed. Every future
invocation still requires an independently reviewed complete manifest. This
package is separate from the minimal EH-hoist change.

### Historical coverage is a separate category

Every new canonical candidate is explicitly `category:"strict-match-only"`,
`historically_tested:false`, `countable_historical_gain:false`. This initial
package does not parse historical test receipts or emit a historically-tested
category. A later independently reviewed exact-address coverage adapter would
be required for that; no MATCH result, test file, alias or row name substitutes
for an actual bound PASS receipt. All candidates remain outside any ledger.

### Review hardening

Identity maps use resolved absolute paths. Every role/group/receipt enters one
canonical identity map: conflicting hashes reject instead of overwriting a prior
binding. Distinct execution roles may not share a path; receipts cannot alias an
execution/dependency/tool/compiler input or another receipt. The baseline source
must use canonical `decomp/src/<TU>` spelling, and both screening/full results
must retain that source and TU. Every full row, including unselected DIFF,
MISSING and EXTRA rows, must carry the bound object digest.

A future historical categorization layer could consume an already-audited
summary bound by SHA256 and an exact-address coverage mapping, with the actual
PASS line and completed > 0 / different = 0 / incomplete = 0 counts. That layer
is **not implemented here**; a naked `historically_tested:true` receipt would not
be adequate. Current outputs remain strict-match-only and uncounted.
