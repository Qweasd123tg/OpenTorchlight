/* Test infrastructure only: keep Python's executable away from the fixed
 * virtual addresses used by bounded, pinned original-function comparisons.
 * This does not load or execute the game. */
#include <Python.h>
int main(int argc, char **argv) { return Py_BytesMain(argc, argv); }
