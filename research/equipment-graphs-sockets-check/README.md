# Equipment graph values, sockets, render queues and prices

Ten entries / 2,319 original bytes. Five are normalized MATCH (100%):
setGraphDamage 0x87dfa0, setGraphAC 0x87e0c0, getMaxSockets 0x87f880,
getFlavorDescription 0x87d5f0 and getSet 0x87d6b0.

Independent comparisons pass 9,072 graph/enchant-price cases, 12,544 socket
cases, 224 render-behind cases and 8,192 trade-price cases. Each case calls
both implementations twice. The five non-MATCH entries kill all 58 final
targeted faults: enchantPrice 9, addSockets 15, setRenderBehind 11, buyPrice 12,
sellPrice 11. The resumed runner can select entries without repeating completed
ones; final per-entry results are copied under results/.

## Important preserved details

Graph damage reads the capped signed +0x28c value AFTER the graph callback;
graph armor captures it BEFORE that callback. Percentage arithmetic is unsigned
32-bit before conversion to float. Armor is clamped to at least one, while
weapon damage is not. The two graph setters also have exact normalized matches.

getMaxSockets returns a signed 32-bit int, not the old generated unsigned-long
placeholder. Its real DataGroup query uses default 2; absent DataGroup returns 0.
addSockets uses signed comparisons, a cached maximum, category checks before
re-reading the current socket count, and a strict roll < chance * 10 test.
NaN does not grant the second socket. Count changes during random/global calls
do not replace the captured base count. The fixture uses real DataGroups and
controlled category/random/global services, not a statistical RNG claim.

Enchant price uses PRICE_ENCHANT and ENCHANTER_PRICE_PER_ENCHANT (+0x6c),
reads the unsigned enchant-count view after callbacks, truncates the extra and
base terms separately, and clamps to 300. The global field name comes from the
original reload key. Broad out-of-range conversion/overflow behavior is not
claimed by the bounded numerical fixture.

Render-behind selects queue 50 or 88 for current primary/secondary model
entities. A missing primary model gates the entire operation. Model/entity
services are spies; no renderer is started. A cached-secondary mutation survived
the initial fixture because the replacement had already occurred during the
primary callback. An independent replacement during the secondary callback was
added; all eleven mutations are now killed. The original result is retained.

Trade prices multiply by max(stack, 1). Unidentified prices bypass player
modifiers. Buying queries the first player before its positive-price gate,
re-reads the player for effect 83 / damage discriminator 7, truncates the
percentage discount and clamps to one only when applying it. Selling has no
positive-price gate or invented floor. Service traces cover callbacks changing
resource manager, prices, stack and identification.

## ABI and boundaries

getFlavorDescription returns std::wstring by value via the hidden result
pointer, not CEquipment*. The declaration is corrected; the implementation and
getSet are MATCH. Nonnull DataGroup remains their original precondition.
GenericModel::setRenderBehind is a nonvirtual service declaration. The verified
GameGlobals field carving preserves layout. No foreign source TU or generic
pipeline was changed. Every differential comparison requires normal exits;
paired crashes do not count as equivalence.
