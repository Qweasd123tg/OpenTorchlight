#!/usr/bin/env python3
"""Authored direct-shot fixture; no proprietary game content."""
from pathlib import Path
import argparse
from make_attack_fixture import write_fixture
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('output',type=Path)
write_fixture(p.parse_args().output, with_ranged=True)
