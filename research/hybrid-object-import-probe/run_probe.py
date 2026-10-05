"""Standalone expected-failure diagnostic; no restored game TUs or hooks."""
import sys
from pathlib import Path
sys.path.insert(0, 'tools/decomp')
import hybrid
root = Path('build-decomp/primitive-catch-probe-minimal').resolve()
(root / 'src').mkdir(parents=True, exist_ok=True)
test = Path('research/hybrid-object-import-probe/PrimitiveCatchProbeTest.cpp').resolve()
blob, loader = hybrid.build(out=root/'hybrid', src=root/'src', tests=[test])
code, report = hybrid.selftest(blob, loader)
print('\n'.join(report))
raise SystemExit(code)
