# Historical UI oracle retained for the HUD correction

These sources and `verification/large-15/prior-original-ui-probes.json` come
from the preceding UI audit. They are not new runs on the current port.
The current release tests the common application separately: mouse down dispatch,
off-target release, no duplicate command. No original executable is included.

Run with a fingerprint-compatible external original ELF and Linux x86-64 PIE
Python, unprivileged, in a separate process. `--help` lists the original
arguments. This controlled-function oracle does not render the original game.
