#include <cstring>
#include "AutoTest.h"
namespace {
__attribute__((noinline)) void throwPrimitive() { volatile int value = 41; throw int(value); }
void probe(void*, autotest::Capture& capture) {
    try { throwPrimitive(); }
    catch (int value) { capture.add(&value, sizeof(value)); }
}
}
TL_TEST(primitive_catch_probe) {
    int failures = 0;
    autotest::Outcome outcome;
    autotest::runChild(probe, NULL, outcome);
    int value = 0;
    if (outcome.capture.length == sizeof(value))
        std::memcpy(&value, outcome.capture.data, sizeof(value));
    host->log("    primitive catch status %d size %lu value %d\n", outcome.status,
              (unsigned long)outcome.capture.length, value);
    TL_CHECK(failures, WIFEXITED(outcome.status) && WEXITSTATUS(outcome.status) == 0 && value == 41);
    return failures;
}
