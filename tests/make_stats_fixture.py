#!/usr/bin/env python3
"""Authored resources only, no original bytes."""
import sys
from pathlib import Path
from make_attack_fixture import write_fixture
write_fixture(Path(sys.argv[1]), with_stats=True)
