# SkillMenu controls and tab handling

Ten original entries restored, 718 original bytes. Eight strict MATCH:
setOwner 0xbd87c0, close callback 0xbd87d0, clearSkillTooltip 0xbd87f0,
mouse-through 0xbd8800, processInput 0xbd8810, mouse-over 0xbd8840,
mouse-out 0xbd8870, spend-skill callback 0xbd8a30.
Tab selection onClick 0xbd88b0 and mouse dispatch 0xbd8880 remain DIFF and are
accepted only by fresh completed original/candidate comparisons.

The original onClick returns true on every normal path, and handle_onClick
forwards the virtual result. Its previous void declaration was corrected to
bool without moving the virtual slot. The sound-bank pointer at 0xe8 replaces
existing padding; object size and all later fields remain unchanged.
A missing nonvirtual clearSkillTooltip declaration was added after checking its
original 13-byte body. Prepare-only packets were regenerated after declarations.

Tab tests: 48 completed equal cases cover open/closed state, actions outside and
inside the 64/65/66 range, window/tab visibility, exact callback order and model
mutations during callbacks. Dispatch tests: 576 completed equal cases cover
null/present windows, three mouse buttons, true/false virtual results, actions,
state patterns and exact member-pointer dispatch. Full menu bytes plus canaries
and collaborator states are compared. Five compiled intentional defects are
rejected by completed differences, zero incomplete pairs; clean rerun passes.

The first aggregate run caught an existing fixture comparing literal original
function addresses with their newly recovered replacements in updateLayout
subscriptions. Only the three known original/replacement callback identities
(mouse-over, mouse-out, spend-skill) are canonicalized. Their full this-adjustment,
unknown addresses, event names and receiver identity remain checked. A deliberate
wrong-handler substitution is rejected by a completed difference; clean layout
comparison passes all 2048 cases. No production behavior or acceptance gate was
weakened to suppress the failure.

Normal Stage.validate/publish and independent root check.py pass all 217 tests.
All prior accepted addresses are retained; exactly these ten entries are added.
Total: 1384/5247 functions, 992144 original bytes, 1296 MATCH + 88 behavioral.
Tests are bounded headless comparisons, not proof of interactive playability.
