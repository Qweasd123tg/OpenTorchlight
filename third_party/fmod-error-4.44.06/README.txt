FMOD ErrorString source evidence
===============================

Only the enum-indexed FMOD_ErrorString header function is established by this
source: 96 of 96 terminated strings match the original SoundManager compiler
table, including whitespace. This does not identify the complete FMOD SDK or
runtime as 4.44.06; the project runtime pin remains 4.36.21.

The untouched manufacturer headers originate from the pinned mirror listed in
source-inputs.json. Their original Firelight copyright notices are preserved.
No separate license text was present in the mirrored include directory.

decomp/include/FmodErrors.h changes only the include to FmodInterface.h. Its
function body is otherwise identical. FmodInterface.h uses the complete original
result enum, whose ABI and numeric values are checked separately. No manufacturer
header structure or whole-SDK layout is claimed by this narrow bridge.
