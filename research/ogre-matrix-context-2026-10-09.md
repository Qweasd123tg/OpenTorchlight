# Pinned OGRE Matrix4 identity context, 2026-10-09

BaseUnit rayCollision (0x800f70, 1693 bytes) and sphereCollision (0x801610, 2021 bytes) strict packets were blocked by references to subobjects of Ogre::Matrix4::IDENTITY at 0x1423fc8..0x1423ff8.

The original ELF has one 64-byte global OBJECT at 0x1423fc0 named _ZN4Ogre7Matrix48IDENTITYE, with an exact R_X86_64_COPY relocation. The pinned OGRE 1.6.5 header declares Real m[4][4] and static const Matrix4 IDENTITY. Float Real matches the pinned profile. OgreMatrix4.h SHA256 is 9d379f1bd2be7be264de50fed7b6ddad034af06e30eb30a3c2ce752f36e8d416.

Extend the existing exact constant recognizer by that single identity. Seven pinned SDK headers and the configuration hash are checked, alongside raw/demangled symbol identity, defined global/weak OBJECT size, COPY identity, writable NOBITS extent, declaration owner/type/constness/uniqueness and float/narrow-string profile. Interior references belong to the containing object; no standalone symbols or general OGRE whitelist are invented.

130 offline tests pass. Matrix identity/ABI mismatch and declaration mismatch tests were added; positive tests cover all sixteen four-byte subobject offsets. Changed-header checks now include Matrix4. Both real strict packets are complete. Function bodies, checker, publication guard and runtime remain unchanged; this tooling patch alone adds no accepted functions.

The publication Stage deliberately rejects changed tool implementations. That restriction is retained. The unchanged checker passed all 192 hybrid tests in the isolated checkout; after exact-scope integration, independent root verification also passed all 192 tests. Root offline tests: 130 passed. The first isolated execution was interrupted without a final receipt; its log was preserved and the full isolated check restarted. It was not treated as a pass. Acceptance remains 1321/5247, 950718 bytes, 1255 MATCH + 66 behavioral.
