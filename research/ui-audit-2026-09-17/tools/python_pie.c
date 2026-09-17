/* PIE host for isolated original-code tests when distro python is non-PIE.
 * Uses the system Python shared library; does not relocate original game code. */
#include <Python.h>
int main(int argc, char **argv) { return Py_BytesMain(argc, argv); }
