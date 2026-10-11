# Exact unnamed callback declaration support

## Scope

Tools-only change for explicit unnamed free-function-pointer parameters
`R (*)(A, B)`. Callback return type, ordered argument types, pointer/reference
and const qualifiers, and enclosing method cv qualifiers retain exact identity.
Word-token boundaries remain distinct (`unsigned int` is not `unsignedint`).
No game implementations or acceptance guards are changed.

## Verification

- 294 selected tool tests passed, including 13 new callback test methods with
  adversarial cases and regressions for direct-callee context, declaration
  readiness, header completion, trial headers and namespace generation.
- Independent review passed, including a separate 13-test run, token-collision
  negative controls and verification of the preparation receipts.
- Fresh `llm_loop.py gameui.cpp --address 0xa8ec90 --prepare-only` with the exact
  two-callback `CModalMenu::setContents` declaration resolved callee `0xb7e520`;
  the caller packet was 23,038 bytes with no blocked addresses.
- Changing only the first callback return from `bool` to `int` caused that same
  caller to be blocked for an unresolved exact `setContents` declaration.
- The temporary declaration used by the packet proof is not included in this PR.

Reproduction of the selected tool tests, using the existing pinned toolchain:

```sh
PYTHONPATH=tools/decomp python3 -m unittest \
 test_callback_declarations test_llm_context test_llm_loop_headers \
 test_ghidra_cpp test_llm_definitions test_mutate_overloads test_llm_packet \
 test_llm_loop_pipeline test_converter_acceptance test_sret_overloads \
 test_sret_identity test_llm_loop_drafts test_llm_model
```

Two initial tests required the existing pinned-toolchain environment; rerunning
with it passed all 294. Some existing tests compile and run small test programs.
No game, full hybrid suite or model request was run. These results establish
parser and packet readiness, not game behavior or newly accepted functions.

## Deliberate limits

Named or nested callbacks, member pointers, pointer arrays, pointer-qualified
callbacks, templates inside callback types, calling conventions, attributes,
default callback values and alias expansion remain unsupported. Malformed forms,
nested scopes, bodies and mismatched overloads remain unresolved. Safe false
negatives include embedded comments and alternate nested-cv spelling.
`Gen.root_return` retains its separate nested-parenthesis restriction; this PR
does not enable callback-bearing virtual return-type discovery, callback
code generation or implementation matching.
