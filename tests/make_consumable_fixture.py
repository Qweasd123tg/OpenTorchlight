#!/usr/bin/env python3
"""Authored recovery fixture; no original assets."""
from pathlib import Path
import argparse
from make_attack_fixture import write_fixture
if __name__ == '__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('output',type=Path)
    write_fixture(p.parse_args().output,with_rewards=True,with_consumables=True)
