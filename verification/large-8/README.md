# Large-8 verification evidence

This directory describes this pass only. Original pak.zip and the pinned ELF were not available. The core suite uses authored fixtures and bounded cached instruction exports; historical large-5/large-6 results are not new validation.

* `input.sha256`, `environment.json`: input archive and execution environment.
* `baseline.log`: unmodified input, 33/33 core.
* `core.log`, `verification.json`: final canonical core run, 40/40, zero skip/fail. Other groups NOT RUN.
* `focused-tests.log`: seven new tests, included in the above forty.
* `sanitizer-{config,build,tests}.log`, `sanitizer.junit.xml`: ten selected ASan/UBSan tests, not the full forty. Configuration and commands are below.
* `coverage-audit.json`: original function statuses unchanged; one new port-only system row.

The unchanged gold scalar export matches on 10,107 valid-domain inputs. This is NOT the whole original actor/RNG/runtime. The native reward cycle uses real port components with authored data, NOT a new full `run_application` scene. Existing core Mesa UI coverage does not establish new progression-HUD/desktop coverage.

```bash
python3 tools/check.py --core --jobs 4 --report /mnt/data/opentorchlight_core_verification.json
python3 tools/coverage_map.py --check

cmake -S . -B build-reward-sanitized -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DTORCHLIGHT_ENABLE_RENDER=OFF -DTORCHLIGHT_ENABLE_DESKTOP=OFF \
  '-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer -fno-pie' \
  '-DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined -no-pie'
cmake --build build-reward-sanitized --target reward_cycle_test reward_resource_probe \
  world_gold_probe checkpoint_upgrade_probe save_checkpoint_test frontend_fixture -j4
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
ctest --test-dir build-reward-sanitized \
  -R '^(progression_numeric|reward_cycle|reward_fresh_process|legacy_reward_save_migration|world_gold_export_comparison|reward_resource_graphs|reward_unavailable|save_checkpoint|save_fresh_process|save_atomic_process)$' \
  --output-on-failure --output-junit reward-sanitized.xml -j4
```

Native probes are instrumented; Python, Mesa and dynamically executed original instruction bytes are not. Assembly-backed comparison is Linux x86-64 bounded evidence. The source tree was built and tested; archive/patch equivalence is checked separately during packaging, not mislabeled as a fresh external-resource or desktop build.
