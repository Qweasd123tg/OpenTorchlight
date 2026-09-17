# large-13 verification

`all-tests.xml` and `all-tests.log`: single completed final run after the build.
`core/assets/reference/render.xml`: views of that same run, not extra executions.
Two UI tests carry both core and render labels. `asan-ubsan.xml`: selected
separate sanitizer run. `new-subsystems.xml` and reference-before-final are
additional overlapping checks, not additive totals.

Native/reference labels prove only the bounded comparisons described in each
test. Real resource tests are not original-process traces. The service/skill
scenario has an explicit XP/gold fixture and is not campaign completion.

Current runtime lacks FreeType SDK and uses the existing prototype fallback;
headless Mesa is real, desktop/OS input delivery is NOT RUN. No original game
assets, libraries, fonts or screenshots are distributed in this folder.

The source-input manifest covers code/tests, including comments. Checkpoint v4
fixture bytes are authored by the unchanged previous writer on authored data.
See verification.json for hashes, known limitations and exact feature scope.
