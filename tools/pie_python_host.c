/* Optional host for fixed-address original-code test probes. The game itself
 * does not use this executable. Build with -fPIE -pie and Python embed flags. */
#include <Python.h>
int main(int argc, char **argv) {
    return Py_BytesMain(argc, argv);
}
