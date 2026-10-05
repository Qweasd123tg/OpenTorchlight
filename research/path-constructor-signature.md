# CPath constructor signature discrepancy

Verified on 2026-10-04 in the supplied ff3a9e2-based checkout, while examining
Equipment::drop. The `path.cpp` TU belongs to the parallel `opencode` worker;
its implementation has not been changed by this Equipment work.

The original function at **0xc89550** (338 bytes) is:

    CPath::CPath(std::string, bool, const Ogre::Vector3&)

Its original symbols are `_ZN5CPathC1ESsbRKN4Ogre7Vector3E` and
`_ZN5CPathC2ESsbRKN4Ogre7Vector3E`.

The supplied `decomp/include/Path.h` instead declares a `std::wstring`
constructor, and `decomp/src/path.cpp` (line 657 at the inspected revision)
defines that wide-string signature. These are different C++ symbols.
The integrated comparison explicitly reports the original narrow-string
constructor as **MISSING**. Passing other hybrid tests therefore does not
establish that this constructor has been recovered: existing narrow-string
callers can still use the original ELF implementation.

The owning worker should reconcile the constructor signature and its string
members against the original constructor/copy constructor/destructor before
claiming this part complete. Changing only a call site to use the wide-string
constructor would conceal the discrepancy rather than recover the original
interface. Equipment work may declare the correct narrow constructor and use
the original implementation as a dependency in the meantime; that does not
count as reconstructing the constructor itself.

## Additional mutable spline signature (2026-10-05)

While recovering Equipment::updateDrop, another signature discrepancy was
verified. Original0xc879e0 is the mutable method
`CPath::GetSplinePositionAtDistance(float)`, mangled
`_ZN5CPath27GetSplinePositionAtDistanceEf`. Its Vector3 return is confirmed at
the caller's SSE return registers.

The supplied header and path.cpp define a const-qualified draft instead,
whose mangled name contains `_ZNK5CPath...`. It is a different symbol. A verified
mutable declaration was added alongside the draft, so the Equipment caller
uses the original ELF dependency. The const draft implementation was not
changed or claimed recovered. The owning worker should reconcile it against
the original mutable signature; passing a caller test is not proof that this
missing CPath implementation has been reconstructed.
