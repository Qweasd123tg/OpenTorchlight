// The blob throws and catches through the process's C++ runtime: the type_info of a
// fundamental type and of library classes live in libstdc++, the blob's own classes get
// theirs with a vtable from it.
#include <exception>
#include <stdexcept>

#include "HybridTest.h"

namespace
{
struct BlobError
{
    int code;
};

struct DerivedError : public std::runtime_error
{
    DerivedError() : std::runtime_error("derived") {}
};

void throwInt(int value)
{
    throw value;
}
}

TL_TEST(Hybrid_exceptions)
{
    int failures = 0;
    int caught = 0;
    try {
        throwInt(7);
    } catch (int value) {
        caught = value;
    }
    TL_CHECK(failures, caught == 7);

    caught = 0;
    try {
        BlobError error = {3};
        throw error;
    } catch (const BlobError& error) {
        caught = error.code;
    }
    TL_CHECK(failures, caught == 3);

    caught = 0;
    try {
        throw std::runtime_error("library");
    } catch (const std::exception& error) {
        caught = error.what()[0] == 'l' ? 1 : -1;
    }
    TL_CHECK(failures, caught == 1);

    caught = 0;
    try {
        throw DerivedError();
    } catch (const std::runtime_error& error) {
        caught = error.what()[0] == 'd' ? 1 : -1;
    } catch (...) {
        caught = -2;
    }
    TL_CHECK(failures, caught == 1);
    return failures;
}
