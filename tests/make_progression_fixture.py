#!/usr/bin/env python3
"""Authored reward fixture: no original game resources."""
from pathlib import Path
import sys
from make_attack_fixture import write_fixture
if __name__ == '__main__':
    path = Path(sys.argv[1])
    path.parent.mkdir(parents=True, exist_ok=True)
    write_fixture(path, with_rewards=True)
