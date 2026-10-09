# Literal-initialized array context, 2026-10-08

The existing header EffectDefines.h defines six const std::string objects in
its gEFFECT_STAT_MODIFIER_ICON_NAMES array. The declaration scanner previously
omitted the complete initializer-bearing definition, falsely blocking recovery.

Recognize only existing static/const std::string or std::wstring arrays whose
initializer is a flat list of string literals. Preserve the complete source
slice and namespace. No type inference, C++ execution, omitted initializer,
macro/call/expression guessing, or interpretation as a byte string. Ordinary
TU-local ELF owner checks remain unchanged. Function-local arrays stay excluded.

Six added regression methods cover narrow/wide/namespace cases, seven rejected
unsupported initializer forms, function scope, wrong TU identity, and following
declarations. All 65 focused tests pass. Against the original skill-tooltip
entry, only the false icon-array gap disappears; the remaining nine genuine
missing declarations are preserved, with the same selected class headers.
Full validation: 454 tool tests (453 passed, one existing Ghidra/JDK skip),
164 headless tests passed, unchanged accepted 1179 functions / 643054 bytes.
