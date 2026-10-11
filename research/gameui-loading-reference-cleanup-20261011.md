# GameUI loading visibility and reference cleanup

Restores two original CGameUI methods in gameui.cpp:
- cleanupReferences(), 0xa988b0, 868 original bytes
- setLoadingVisible(bool), 0xa9c3b0, 711 original bytes

Both are accepted by original-versus-restored behavioral comparisons, not byte-exact MATCH.

## Behavior and boundaries

Cleanup preserves ordered menu/tooltip resets, safe-pointer detachment and retained indices, equipment references and icon lookup, null mouseover clearing, five virtual setOwner(NULL) calls through slot 7, duplicate merchant player rebinding, and conditional cursor reset. Vtable evidence distinguishes setOwner from setOpen; the compiled audit requires five slot-7 calls and rejects slot 8.

Loading preserves the manager gate, child membership, UTF-8 loading tip construction, add/text/remove order, rendering even when the loading child already exists, and manager singleton reloads around rendering. A rendering exception retains the original flag state.

An ELF-wide caller scan found one cleanup and nine loading call sites in five unrecovered callers. Source/header scans found no restored consumers. Existing same-TU boundaries are preserved explicitly; all 87 prior exact GameUI matches remain exact.

## Verification

- Baseline: d59eb455bc4d14a52ebbec5de886f976a8f7b555
- Accepted functions: 2692 to 2694, comprising 2159 MATCH and 535 behavioral acceptances
- Full headless suite: 627/627 PASS; every prior acceptance retained
- Focused and restored-positive runs: 24/24 PASS each
- New normal comparison cases: 243 cleanup and 672 loading
- Separate expected-exception/recovery cases: 210 cleanup and 85 loading; these are not counted as completed normal coverage
- Four deliberate negative controls detected completed differences with zero incomplete comparisons: omitted duplicate merchant binding, incorrect safe index reset, cached manager, and skipped rendering for an existing child
- Real CEGUI allocation failure is exercised by a narrowly scoped allocator relocation hook with identity checks and restoration before retry
- The same validated Stage published locally with identical source tree, input digest, and all 279 production object identities

Validated input SHA-256: 53dad68c40090e10d0b5a53f76523bc544bb484375ac4965731cf89f57e48114

The full gate took 1017.20 seconds, including 738.99 seconds for headless tests, with eight shards, four workers, shared selftest capacity four, and compiler capacity two. A one-second process-tree sampler observed peak aggregate RSS of 1127384 KiB. This includes the driver, double-counts shared mappings, and may miss brief peaks; it is not a guaranteed memory bound.

## Limits

No live-window gameplay was exercised, and headless PASS does not establish playability. The renderer is detoured for comparison. Cleanup executes real CEGUI string lifetimes without a separate allocation/destructor-order oracle. Loading covers ASCII, BMP, embedded NUL, and long strings; non-BMP behavior remains outside this fixture because of an original uninitialized-tail quirk. No runtime resources or original binary are included.
