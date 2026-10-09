# Exact overload identities in direct-callee context

The read-only context scanner previously matched only a qualified function name.
A real CGameUI::menuItemClick packet (0xa8f780, original ELF SHA256
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b)
therefore reported no gaps even though CResourceManager::createUnit(CDataGroup*,
int, bool, bool), 0xd78c50, had only its distinct long-long overload declared.

The context index now reuses the existing conservative declaration-signature
parser to require parameter and member-cv identity as well as qualified name.
It handles existing named parameters, simple defaults, const spelling and
explicit destructors. Unsupported forms, unresolved typedef equivalence and
missing parameter/cv metadata stay unresolved. The same test covers TU-local
classes. Return and static status are not asserted by this lookup because the
ordinary Itanium symbol does not encode them. No declaration is synthesized.
Pinned template and compiler-generated destructor rules remain unchanged.

On the real prepared tree, this adds exactly the missing createUnit overload
gap, removes no gap and preserves the same 20 whole dependency headers.
The original was only inspected, never invoked by this experiment.

Focused verification: 100 offline tests passed, including 16 new overload
regressions. Existing test fixtures now carry their actual declared parameter
identities rather than name-only synthetic records.
Full verification: 513 tool tests (512 passed, one existing Ghidra/JDK skip);
168 independent root headless tests passed. Acceptance stays 1208 / 783251.

No game source, game header, ownership assignment or acceptance gate changed.
