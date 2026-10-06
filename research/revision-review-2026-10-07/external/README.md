# Revision review

Start with **REPORT_RU.md**. **IMPLEMENTATION_ADDENDUM_RU.txt** is a standalone task for the implementing agent.

Run:

```bash
python3 run_all.py /path/to/OpenTorchlight-main --out /tmp/otl-revision-review
```

Requires Linux, Python, host gcc/g++ and binutils. No downloads, models, Ghidra or game execution. Writes go to a fresh results directory and synthetic temporary projects. The reviewed original archive is not patched.

The probes demonstrate boundaries and counterexamples; a successful probe may mean that a defect was reproduced, not that the project passed that safety requirement. Read `detected`, `false_MATCH`, `proof_type` and the report. Patched versions may correctly stop reproducing a defect.

`results/existing-summary.json` distinguishes passed, skipped and not-run original tests. `results/jump-tables/results.json` contains actual comparison decisions and native execution of artificial reference/candidate binaries. No Torchlight behavior is inferred from those binaries.

Numbered code copies in `source_excerpts` are reference text, not executable patches. Native binaries are reproducible but omitted from the distribution.
