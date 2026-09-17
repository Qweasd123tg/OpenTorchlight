#!/usr/bin/env python3
"""Authored regeneration/equipment resources, never original gameplay data."""
from pathlib import Path
import sys
from make_attack_fixture import write_fixture
if __name__ == '__main__':
    write_fixture(Path(sys.argv[1]), with_rewards=True, with_vitals=True)
