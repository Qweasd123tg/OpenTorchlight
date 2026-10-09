# Pinned SDK data and implicit-destructor context, 2026-10-08

The Combine createMenus packet at 0xad7a50 was blocked by seven SDK-owned data
objects and the compiler-provided CFileInfo destructor, in addition to one real
missing game declaration. This change fixes those eight false gaps only.

SDK data recognition requires agreement of the DB and original ELF object
identity/size, GLOBAL or WEAK binding, an exact R_X86_64_COPY relocation, allocated
writable BSS bounds, exact Itanium mangling and an existing SDK declaration.
The supported profile is pinned CEGUI 0.6.2 on this x86-64 GCC 4.4.7 target:
String objects 176 bytes; pointers and size_type 8 bytes. The original COPY objects
and compiler-exported CEGUI::String layout independently agree on 176.

Only five reviewed SDK headers are eligible, with exact SHA256 content pins:
Window, String, Singleton, ImagesetManager, WindowManager. Changed, unlisted,
out-of-directory, missing, wrong-size, wrong-scope and non-COPY inputs remain
gaps. Event members must actually be declared static const String; npos has its
own declaration; singleton ownership requires the SDK template and manager's
matching inheritance. This is not a blanket namespace exemption. Context cites
the existing declaration and header hash; no game variable is synthesized.

Implicit-destructor recognition is separately limited to weak compiler-generated
D1/D2 identities for a uniquely defined top-level class in a real mapped header.
Forward declarations, ambiguous classes, wrong symbols, ordinary/strong methods
and deleting D0 variants remain blocked. C++98 already implicitly declares these
destructors; the whole existing header is supplied, not a guessed signature or
body. Return hints from disassembly are not treated as destructor prototypes.

All 77 focused context tests pass. Added tests cover supported SDK data forms,
ELF/COPY/ABI disagreements, declaration and content-pin mismatch, an out-of-SDK
symlink, ordinary game globals, and implicit-destructor identity/ambiguity.
A negative pin test caught an initially omitted digest comparison; the tested
candidate includes the comparison and reads raw bytes for exact hashing.

On the original Combine entry, exactly eight false gaps disappear and the real
missing CCombineMenu::mapEventHandlers declaration stays blocked. Selected game
headers are unchanged. No recovered function or acceptance is added by this
preparation-only improvement. Full verification: 466 tool tests (465 passed, one existing Ghidra/JDK skip);
166 headless tests passed in the independent root check. Accepted coverage is
unchanged at 1185 functions / 733100 original bytes.
