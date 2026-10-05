# Equipment missile launch

Original fireMissiles(CCharacter*,CCharacter*)0x87f120,1881 bytes. Bool return
verified in performAttack at847a1d(testAL). getEquippedTo899550 returns field290
and matches all8 bytes; it is compiler-inline code, not another game function.

4896 cases twice per side use real Ogre SceneNodes, bounding-box/vector/quaternion
math, DataGroups, TArrayList allocation/growth and CRunicCore weak-pointer
registration/removal. Controlled collaborators are left-weapon lookup,
preloader/factory, entity bounding-box access and final fireMissile dispatch.
Captures include service order, launch/aim float bits, owner/target identity,
listener subobject identity, retained references, registration indexes and
cleanup state. Covers empty missile name, null shooter, factory failure,
left/right hand, model/no model, absent/zero/half/double scale, finite/null/
infinite bounds, no/normal/coincident/nearzero targets, list growth, already
registered listener, wrong primary-pointer listener, repeated shots and target
movement/equipped-owner change during creation.

An initial fixture was rejected despite14/16 kills: target nodes had no logical
parent, so getPosition(true) and(false) both read the same untouched local
position. This also hid the target-movement callback. The corrected fixture
sets coherent local positions and a real translated parent node with a logical
parent link. Nearzero cases use zero parent translation to retain small deltas.
Both absolute-position mutations now die. Initial evidence remains in
initial-mutations-parentless.json. Final sampled result16/16 viable killed;
all21 targeted semantic mutations killed, including the late second target
position read, right-hand/left-hand selection, quaternion axes, owner choice,
secondary iMissile pointer, listener deduplication and weak-reference retention.

The function registers the Equipment iMissile subobject at+230 before firing,
then retains a new Ogre-allocated safe pointer at+410. Missile listener list
at+1c8 and original layouts are checked. Non-null shooter hand nodes and
model/entity pairs obey original preconditions; invalid both-crash cases are
never accepted. This verifies launch orchestration, not subsequent projectile
flight/collision/damage behavior, which remains CMissile's responsibility.
