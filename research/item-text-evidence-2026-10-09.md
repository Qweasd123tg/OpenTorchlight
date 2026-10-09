# Item highlight evidence, 2026-10-09

CItem::setItemTextHighlighted(bool), original 0x8c01b0, 2037 bytes. Existing production body unchanged. Strict original context packet complete. Review confirms virtual highlighted/magical calls, missing-label and unchanged-highlight returns, quest/unique/magic/random-socketable/default color priority, selected/unselected globals and highlight-only moveToFront. No set-color branch exists in this base Item function.

384 completed cold/warm original-versus-replacement comparisons pass without differences or incomplete observations. The legacy 96-case test is expanded to independently cover missing/present label and a repeated call. Real headless CEGUI windows/skin and type hierarchy are retained. Capture now includes the complete initialized item and manager buffers with narrow known-pointer normalization, logical type relations, all eleven global color strings, label text/color, visible/disabled/parent/alpha state and hit-test front order. Each measured call uses the exact original/replacement alias and complete per-function coverage. Matching crashes or exceptions cannot accept it.

Candidate 1465 bytes remains DIFF, no unknown references, code fingerprint 899b32536580a793. These are bounded collaborator/state comparisons, not exhaustive CEGUI internals, allocator state, universal exceptions or byte identity.

All seven independently compiled deliberate-fault controls were rejected by completed differences: highlight gate, quest/unique/rare/random colors, default color and front-order condition. Strict Stage validation and independent root validation each passed 192 tests with zero failures. Final accepted total: 1321/5247 functions, 950718 original bytes; 1255 MATCH and 66 behavioral.
