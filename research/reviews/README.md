# External reviews

These files preserve external analysis against a named project snapshot. They
are navigation aids, not original-code evidence by themselves. Before changing
runtime behavior, verify each finding against the current source and the
original resources, assembly, or a differential execution test as required by
`AGENTS.md`.

## 2026-09-15 review status

The current tree has resolved two verified combat findings (attack cooldown
retention and rolled-damage mitigation), the spawner ownership finding, and
the player-side ordinary attack path through animation HIT events. Enemy HIT
consumption, character stats, equipment models, collision range, material
overrides, and update phases remain open until their original execution paths
are traced and reproduced.
