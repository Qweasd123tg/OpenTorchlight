# Detaching an equipped item's visual objects

`CEquipment::detachFromLocation`, 0x86ee20, 493 original bytes.
The restored implementation also achieves normalized MATCH (100%) with the
original compiler.

3,584 differential cases, two calls per side, use real Ogre scene nodes.
All 21 targeted mutations are killed. Primary/secondary paperdoll entries use
51 distinct entity identities across two actors and all twelve slots to avoid
correlated fixture values concealing a wrong index.

The original's equipped/primary-model/entity gates are preserved. The primary
model is reparented only when it already has a parent. A particle is stopped
immediately, detached when necessary, then attached to the item. The secondary
model is removed from its parent but is not reparented. Bone-detach exceptions
are swallowed; actor and slot are read again for the paperdoll setter. The
fixture includes exceptions and actor/slot/particle replacement callbacks.
The equipped actor is cleared only inside the successful outer gate.

The original requires a nonnull model from the actor's virtual getUnitModel and
a parent for a present secondary model. These are fixture preconditions, not
new guards silently added to game code. Renderable entities, bone-detach,
particle-stop and paperdoll services are spies; no rendering is launched.
