# StatsMenuFill construction and destruction

Restored three original entry points (1869 original bytes): destructor at
0xc1fc40 (323 bytes), deleting destructor at 0xc1fd90 (18 bytes), and constructor
at 0xc2b080 (1528 bytes). Both destructors are machine MATCH. The constructor
remains behavioral DIFF: the instruction sequence and size agree, but the strict
comparator does not promote six ambiguous linked wide-string literals or their
EH metadata. No comparator or acceptance rule was weakened.

## Fresh context and layout

The packet resolver now recognizes only the existing, pinned
TArrayList<CEGUI::Window*> D1/D2 destructor specialization. It requires the exact
scope, qualified name, parameter/cv signature, kind, weak binding, both mangled
names, and both matching weak original-ELF address/name/size identities. The
reviewed TArrayList.h bytes must match SHA256
 e45608b683e95c9fb0a5eb0129bb99c3d09826270d14b06cf1f407a35208b4be.
No template specialization or API is invented. The shallow class scanner omits
templates, so this narrowly authenticated body is handled separately. Negative
unit cases retain gaps for wrong DB/ELF identities, changed source, and unrelated
unresolved dependencies. The Python suite passes 629 tests (one existing skip).

Constructor declarations and fields through +0x190 were recovered before new
prepare-only packets. CResourceManager::getGraph returns CGraph*: the original
returns null or tail-calls the already recovered CGraphManager::getGraph.
Both final lifetime packets are complete. Compile-time checks verify sizeof
0x198 and trailing offsets +0x168/+0x170/+0x178/+0x180/+0x188/+0x18c/+0x190.
The derived fill sound bank at +0x180 remains distinct from the base +0x80 bank.

## Runtime evidence

The constructor fixture executes the real original and candidate bodies with
controlled collaborators. It compares full menu state plus trailing canaries,
full sound-bank state, argument/order traces, all four lookup strings and GUIDs,
sample IDs, title, graph lookup, base parameters, and allocation behavior.
All 16 sound-presence masks, two canary patterns, changed singleton/bank identities,
and null/present graph results give 128 successful comparisons with no differences
or incomplete calls. Only known pointer identities are canonicalized; unknown
values are retained. Existing createMenus and sound implementations are separate
collaborators, not claimed newly covered by this fixture.

Fourteen injected collaborator failure points across both patterns/identity
profiles give 56 matching exception unwinds. They are checked separately and do
not count as successful-completion acceptance. Original cleanup behavior,
including the raw sound-bank ownership during constructor failure, is preserved.
Six independently compiled defects (array growth, sound lookup, sample ID,
initial interval, graph key, base argument) are rejected by completed differences;
the final unmodified candidate passes again.

## Aggregate result

Isolated candidate and integrated root each pass all 205 headless tests. All
previous accepted addresses remain accepted, with exactly these three added.
Total: 1356/5247 functions, 985776 original bytes; 1277 MATCH and 79 behavioral.
This slice is based on the accounting/open-transition changes in PR44.
