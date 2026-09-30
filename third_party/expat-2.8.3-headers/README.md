# Expat 2.8.3 public headers

Unmodified public headers from the official `R_2_8_3` tag:
https://github.com/libexpat/libexpat/tree/R_2_8_3/expat/lib

MIT notices are retained in both headers. These headers are a build fallback
when the host has `libexpat.so.1` but no development headers. The implementation
is the host Expat library; it is not vendored here. Only the stable XML 1.0
parser API used by the original CEGUI 0.6.2 Expat module is called.
The initial verified host runtime is `expat_2.8.3`.

SHA-256:

- `expat.h`: `d3f19ed52dc975741ecc5a0fc553f910a241d60c76fa4621356d0cdb0490ca28`
- `expat_external.h`: `f24009bc2a8914caeb0480d1ce0765e98ba4845d2e3b03029b09304130715231`
