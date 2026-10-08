#!/usr/bin/env python3
"""Reproduce the bounded six-index transfer test; optional deliberate receiver mutant.
Requires the normal pinned toolchain and read-only original-game inputs.
"""
import argparse
import os
from pathlib import Path
import shutil
import sys
root = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(root / "tools/decomp"))
import hybrid
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--negative-control", action="store_true")
args = parser.parse_args()
work = root / "build-decomp/attempts/stash-pet-transfer-repro"
if args.negative_control:
    work = work.with_name(work.name + "-negative")
(work / "src").mkdir(parents=True, exist_ok=True)
(work / "tests").mkdir(exist_ok=True)
for name in ("MerchantMenu.cpp", "StashMenu.cpp"):
    shutil.copy2(root / "decomp/src" / name, work / "src" / name)
if args.negative_control:
    source = work / "src/StashMenu.cpp"
    text = source.read_text()
    assert text.count("m_pUnknown3410->getImage") == 8
    source.write_text(text.replace("m_pUnknown3410->getImage",
        "reinterpret_cast<CEGUI::Imageset*>(m_pUnknown30)->getImage"))
fixture = (root / "decomp/hybrid/tests/StashPetTransfer.cpp").read_text()
assert "const int slot=19,data=25;" in fixture
tests = []
indices = [(0, 0), (1, 3), (18, 399), (19, 25), (60, 144), (81, 399)]
if args.negative_control:
    indices = [(19, 25)]
    for old, new in [("mode<6", "mode<1"), ("sm<5", "sm<1"),
                     ("xy<2", "xy<1"), ("cnt<3", "cnt<1"),
                     ("capacity<3", "capacity<1"), ("cr<4", "cr<1")]:
        assert old in fixture
        fixture = fixture.replace(old, new)
for slot, data in indices:
    path = work / "tests" / ("StashPet%d.cpp" % slot)
    text = fixture.replace("const int slot=19,data=25;",
                           "const int slot=%d,data=%d;" % (slot, data))
    text = text.replace("stash_pet_slot_transfer", "stash_pet_slot_boundary_%d" % slot)
    path.write_text(text)
    tests.append(path)
os.environ.setdefault("OTL_SELFTEST_TIMEOUT", "600")
extra = os.environ.get("OTL_EXTRA_INCLUDE", "")
os.environ["OTL_EXTRA_INCLUDE"] = str(root / "decomp/hybrid/tests") + (":" + extra if extra else "")
blob, loader = hybrid.build(out=work / "build", src=work / "src", tests=tests)
code, lines = hybrid.selftest(blob, loader, shards=1)
report = "\n".join(lines) + "\n"
(work / "result.log").write_text(report)
print(report)
# The negative control is deliberately expected to return nonzero.
raise SystemExit(code)
