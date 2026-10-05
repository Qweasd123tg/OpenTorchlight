# Equipment item-label colors

`setItemTextHighlighted(bool)`, original 0x8824f0, 2368 bytes.
384 cases: 96 old/new highlight, magical, quest and six type combinations,
independently crossed with set and label presence. Headless CEGUI loads the
real game skin and compares label color plus actual sibling hit-test ordering.
The original quest test and type hierarchy implementation are used; set lookup
and virtual highlighted/magical responses are controlled. Equal old/new and
null labels are ordinary successful no-op cases, not crashes.

11/11 sampled viable mutations and 15/15 targeted semantic mutations killed.
Quest overrides set, set overrides unique, unique overrides magic/socketable,
and ordinary items use white / 0.8 gray. No highlight state is assigned here.
Changing the color only happens on differing highlight state, and moveToFront
only on a change to highlighted. Renderer screenshots and end-to-end game
interaction are outside this headless function check.
