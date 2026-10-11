# GameUI text presentation restoration — 2026-10-11

Restores three original CGameUI entry points in gameui.cpp:

- 0xa8dd00: setSmallText(std::wstring, float), 370 original bytes
- 0xa8de80: setBigText(std::wstring, float), 392 original bytes
- 0xa94c80: setCinematicOpen(std::wstring), 164 original bytes

Original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

Empty message input zeros fade and hides its window while preserving text and
duration. Nonempty big text shows its window before assignment; small text does
not. Both reset fade, preserve duration bits, and assign white foreground and
black shadow colours in original order. Cinematic opening is null guarded,
copies text by value, then reloads the menu and dispatches virtual setOpen.
Original call boundaries are preserved. No alternative gameplay logic is added.

## Validation

- Complete unchanged Stage.validate gate: 617/617 tests passed.
- Accepted functions: 2,686 (2,156 MATCH, 530 behavioral), exactly the previous
  2,683 plus these three. Every prior acceptance and MATCH is preserved.
- Focused differential fixtures: 435 completed comparisons, zero differences
  and zero incomplete cases; 60 separately checked expected unwinds.
- Cases include empty, leading/embedded NUL, BMP and long strings; exact floating
  duration bits; COW copy/clone ownership; callback pointer/vtable mutation;
  repeated calls; complete object sentinel snapshots; real CEGUI temporaries
  and cleanup. Independent expected-state witnesses supplement comparison.
- Four semantic mutations were rejected with completed mismatches: showing
  small text, changing big-text visibility order, clearing retained empty-input
  state, and caching a stale cinematic menu across setText.
- Restored-positive and initial focused binaries have identical SHA-256:
  b8ea1fef5af952478859006e8c6fb9957dbfc45ced1abcd6e5263f1369316106.
- Final input digest:
  3bb53c749ad4dc2909af68d227e0f4bb149b11d16de71ef12f6d81ab8ed0965f.
- Full gate: 1,604.38 seconds; headless execution: 1,327.00 seconds with the
  unchanged two-shard, 1,800-second timeout configuration.

No acceptance tools or guards were changed. Original binary/resources are not
included. Passing the headless gate does not establish live-game playability;
no live-window launch was performed.
