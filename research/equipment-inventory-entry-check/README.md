# Entering an inventory and updating the attached layout

`addedToInventory`, 0x884a20, 383 original bytes: 4,096 differential cases,
two calls per side, all 20 targeted mutations killed. The test observes quest,
icon, price, parent-GUID, state/event, scene-removal and particle-stop calls,
plus final inventory and visibility state. Collaborators are controlled spies;
resetVisualLayout is the already recovered implementation.

Order matters: a transfer quest event precedes storing the new inventory. For
a gambler icon, the inventory is stored before rebuilding the icon and price.
Parent GUID and unit state precede the player/master pickup quest; event 27
precedes setting Item flag 1f2. Scene removal, deferred particle stop and layout
reset follow. Callback changes to the current resource manager, inventory,
master, scene owner and particle pointer are included. Original nonnull client
and actor preconditions are preserved, not replaced with new recovery guards.

`updateVisualLayout`, 0x86d670, 394 bytes, achieves normalized MATCH (100%). It
lazily constructs a CLayout of type 2, loads ATTACHEDLAYOUT with the original
flags, starts it, restores visibility, updates it, and follows the model's
DERIVED position and orientation. MATCH is the acceptance basis; this entry
has no separate visual/rendering claim or new window-launch test.

Shared declarations: EditorScene::RemoveObjectInScene(CEditorBaseObject*) is
void; SceneNodeObject's inline getVisible reads byte +0x81, also confirmed by
the original descriptor getter at 0x625770. No foreign source TU was edited.
