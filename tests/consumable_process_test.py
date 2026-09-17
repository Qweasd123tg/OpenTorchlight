#!/usr/bin/env python3
"""Two independent processes, no shared in-memory inventory/timers."""
import subprocess,sys,tempfile
with tempfile.TemporaryDirectory(prefix='ot-potions-') as directory:
    for mode in ('--write','--read'):
        subprocess.run([sys.argv[1],mode,sys.argv[2],directory],check=True)
