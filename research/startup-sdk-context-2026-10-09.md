# Pinned startup SDK data context

Reviewed tool improvement; no game implementation or acceptance-rule change.
Final root verification: 532 tool tests (531 passed, one existing skip) and all
171 headless tests passed. Acceptance remains 1210 functions / 803972 bytes.

The existing CEGUI singleton rule now knows the pinned FontManager and
SchemeManager owner headers. Exact template ownership, ELF symbol and COPY
relocation identity, writable BSS and pointer-size checks remain mandatory.
Header changes remain gaps; there is no namespace-wide exemption.

The additional OGRE rule applies only to
Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME. The original object is
an eight-byte COPY import, and the vendor declaration is static String (not
const). Four exact OGRE 1.6.5 header hashes plus the unchanged default
repository build-profile hash are required. The declaration's class/namespace
and type are checked, and changed profiles or escaping header symlinks fail
closed. This supplies declaration context, not game-function acceptance.
A GCC 4.4.7 compile-only probe independently verifies Ogre::String is the same
type as std::string, sizeof(String) is eight and the member is non-const under
this pinned default profile. No compiler/ELF/DB reload is added to packet lookup.

The isolated full tool suite passes 532 tests: 531 passed, one existing
Ghidra/JDK skip. New tests cover both manager owners, missing COPY evidence,
OGRE copy/size mismatches, changed configuration/header pins, wrong declaration
owner/namespace/type, non-BSS/readonly objects and SDK path escape.

On the original 32473-byte CGameUI::create entry, this tool-only change removes
exactly three false SDK data gaps (31 -> 28). All genuine missing declarations
remain. Separately reviewed private game declarations and the constructor-owned
key array produce a fresh complete preparation packet with zero blocked or
already-existing targets. That private startup body has not been authored or
invoked; no SDL, renderer, filesystem or audio startup effects were executed.
