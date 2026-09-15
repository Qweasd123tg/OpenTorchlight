# large-5 verification logs

Input ZIP SHA256 is in input.sha256. Baseline: unmodified input portable 21/21.
Fresh portable and sanitizer: 28/28. focused-tests.log identifies authored vs
original resources and the actual real Mesa renderer. capabilities.log records
missing development dependencies and the unavailable full desktop target.
Sanitizer flags are in FRONTEND_CAMPAIGN_RESULT_RU.md; Python/Mesa host disables
LSan only for gles_ui_headless, native tests keep leak detection.

No original pak/ELF or full Wayland desktop was executed. Earlier integration
logs elsewhere in the input tree are historical and not evidence for this patch.
The final distribution is separately applied to a clean input, rebuilt and hash
compared during packaging. Logs contain original local paths; they are evidence,
not paths hard-coded into the implementation.
