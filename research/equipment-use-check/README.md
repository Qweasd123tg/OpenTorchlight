# Equipment use-on-target protocol

Original useOnTarget(CCharacter*,CBaseUnit*) is0x86e910/598 bytes. Current
fixture compares14944 cases, twice per side. Actor/target/effect/manager state
is controlled and uses verified layouts; target RTTI is real, the scene node
is real Ogre, while effect validity/application, journal/Steam statistics,
skill execution and sound are observers. No online statistics service is used.

Cases cover null target, negative/zero/one/multiple stack entries and charges,
unlimited charge sentinel -9999, absent/empty effect and skill managers,
independent validity/application outcomes, potion and pet/master statistics,
optional/null caster and sound, callback changes and TArrayList capacity fallback.
The calls observe exact effect and owner pointer rereads, cached current
manager list, dynamic list counts and late stack/charge values after sound.
Raw effect owner pointers are fixture inputs only; this does not re-test the
full weak-reference registration lifecycle or all character effect mechanics.

The original caller checks AL after virtual applyEffectOnUnit. The partial
BaseUnit/Character/Equipment headers previously declared void; all three are
corrected to bool, with the same parameter list and vtable position. Original
BaseUnit805130 returns0; Equipment86e690 returns0 normally and1 after identify.
No other source TU is changed. The helper Equipment validity/application
methods are normalized MATCH at86d600/27 bytes and86e690/118 bytes.

Effect owner+48 and Character master+640 are typed without moving later fields.
Character::setMaster825fa0 verifies the latter. The original potion path assumes
a Character target after successful application; no new defensive cast guard
is invented for invalid input. Skill-manager list+60 is the consumable skill
list, and only its first entry is performed by this method.

Final fixture:23/23 sampled viable mutations and27/27 targeted faults killed.
