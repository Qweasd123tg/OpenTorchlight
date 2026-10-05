# Imported RTTI object regression

This is a standalone diagnostic, not an accepted game function. It must remain
outside the normal hybrid test directory until the importer is fixed.

`tools/decomp/hybrid.py:imports_assembly` represents every unresolved symbol as
an `@function` trampoline. For `_ZTIi`, callers need the address of an RTTI data
object instead. A typed `throw int` / `catch (int)` therefore receives code bytes
where the runtime expects RTTI.

The previous workspace reproduced a failure with zero game translation units
and zero hooks. The child reported status 35584 (exit 139), with no captured
value, whereas the expected result is a normal exit with integer 41. The
current workspace independently reproduced the same zero-hook failure on
2026-10-05. See `run_probe.py`: the baseline is intentionally failing until
the generic importer is corrected.

A `std::runtime_error` fixture was unaffected in the previous investigation:
its type information resolves to an existing original ELF object. A catch-all
is not an adequate regression test because it need not compare the thrown
type's RTTI. Both compared sides crashing is never evidence of equivalence.

The generic importer belongs to the other pipeline worker. Suggested direction:
distinguish object and code imports, preserve object-address semantics, and
check the fixed-address blob's absolute exception-table relocations. A pointer
slot is not itself the imported RTTI object. Add a plain imported-data read as
a separate regression; other data imports have not been exhaustively audited.
