# Existing TSafePointer template in recovery context, 2026-10-08

The packet for CGameUI::menuItemClick (0xa8f780) reported two false missing
declarations: TSafePointer<CCharacter>::setObject and the CEquipment version.
Their implementation already exists in SafePointer.h; the intentionally shallow
scanner does not parse template classes and inline bodies as ordinary methods.

This narrowly recognizes that existing reviewed setObject(T*) template. It
requires a flat class argument, exact method/qualified name/parameters/CV and
Itanium symbol, weak compiler-generated DB classification, an actual defined
weak ELF STT_FUNC at the same address/name/size, an unchanged raw-byte SHA256
of SafePointer.h, and one uniquely mapped complete pointee class header.
Changed headers, missing/ambiguous/forward pointees, different methods or
signatures, mismatched DB/ELF identities, ordinary or strong definitions remain
gaps. No general template or namespace exemption is added. It supplies the
whole existing SafePointer and pointee headers; no prototype/specialization/body
is synthesized. The pin must be explicitly reviewed if that header changes.

84 focused context tests pass, including seven new methods with adversarial
subcases. Against the original image, exactly the two false gaps disappear;
all eleven real missing game method declarations stay blocked, no new gaps
appear, and only SafePointer.h is newly selected. No function acceptance changes.
Full verification:473 tool tests (472 passed, one existing Ghidra/JDK skip);
168 independent root headless tests passed. Acceptance stays1187/780930.
