// Normal original/replacement calls, including callbacks which alter their own list.
#include <climits>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#define private public
#include "DynamicPropertyFile.h"
#undef private

TL_ORIGINAL(bool, originalInt, (CDynamicPropertyFile*, unsigned int, int), "_ZN20CDynamicPropertyFile6SetIntEji")
TL_ORIGINAL(bool, originalFloat, (CDynamicPropertyFile*, unsigned int, float), "_ZN20CDynamicPropertyFile8SetFloatEjf")
extern "C" bool candidateInt(CDynamicPropertyFile*, unsigned int, int) __asm__("_ZN20CDynamicPropertyFile6SetIntEji");
extern "C" bool candidateFloat(CDynamicPropertyFile*, unsigned int, float) __asm__("_ZN20CDynamicPropertyFile8SetFloatEjf");
namespace {
struct Case { unsigned op, size, property, mode, bits; };
const Case* input;
autotest::Capture* output;
CDynamicPropertyFile* receiver;
unsigned calls;
void number(unsigned value) { output->add(&value, sizeof(value)); }
void callbackB(unsigned property) {
    ++calls; number(2); number(property);
    if (property != input->property) output->issue = autotest::Capture::InvalidReport;
}
void callbackA(unsigned property) {
    ++calls; number(1); number(property);
    if (property != input->property) output->issue = autotest::Capture::InvalidReport;
    unsigned observed;
    if (input->op == 0) std::memcpy(&observed, &receiver->m_intValues[property], 4);
    else std::memcpy(&observed, &receiver->m_floatValues[property], 4);
    number(observed);
    if (observed != input->bits) output->issue = autotest::Capture::InvalidReport;
    if (input->mode == 2) receiver->m_callbacks[property].push_back(&callbackB);
    if (input->mode == 3) receiver->m_callbacks[property].clear();
}
void side(Case& c, bool ours, autotest::Capture& capture) {
    input = &c; output = &capture; calls = 0;
    unsigned long long storage[sizeof(CDynamicPropertyFile)/8];
    std::memset(storage, 0xa5, sizeof(storage));
    receiver = reinterpret_cast<CDynamicPropertyFile*>(storage);
    new (&receiver->m_intValues) std::vector<int>(c.size, 0x13572468);
    new (&receiver->m_floatValues) std::vector<float>(c.size, 13.25f);
    new (&receiver->m_callbacks) std::vector<std::vector<CDynamicPropertyFile::StatChangeCallback> >;
    if (c.mode != 0) {
        receiver->m_callbacks.resize(c.size);
        for (unsigned i = 0; i < c.size; ++i) {
            receiver->m_callbacks[i].push_back(&callbackA);
            if (c.mode == 3) receiver->m_callbacks[i].push_back(&callbackB);
        }
    }
    unsigned char before[sizeof(storage)]; std::memcpy(before, storage, sizeof(before));
    bool result;
    if (c.op == 0) {
        bool (*fn)(CDynamicPropertyFile*, unsigned, int) = ours ? candidateInt : originalInt;
        if (!autotest::beginInvocation(capture, fn)) return;
        int value; std::memcpy(&value, &c.bits, 4); result = fn(receiver, c.property, value);
    } else {
        bool (*fn)(CDynamicPropertyFile*, unsigned, float) = ours ? candidateFloat : originalFloat;
        if (!autotest::beginInvocation(capture, fn)) return;
        float value; std::memcpy(&value, &c.bits, 4); result = fn(receiver, c.property, value);
    }
    capture.callCompleted = 1;
    number(result); number(calls);
    if (result != (c.property < c.size)) capture.issue = autotest::Capture::InvalidReport;
    unsigned expectedCalls = c.property >= c.size || c.mode == 0 ? 0 : c.mode == 2 ? 2 : 1;
    if (calls != expectedCalls) capture.issue = autotest::Capture::InvalidReport;
    for (unsigned i = 0; i < c.size; ++i) {
        unsigned intBits, floatBits; std::memcpy(&intBits, &receiver->m_intValues[i], 4);
        std::memcpy(&floatBits, &receiver->m_floatValues[i], 4);
        number(intBits); number(floatBits);
        unsigned expectedInt = c.op == 0 && c.property == i ? c.bits : 0x13572468u;
        float initial = 13.25f; unsigned expectedFloat; std::memcpy(&expectedFloat, &initial, 4);
        if (c.op == 1 && c.property == i) expectedFloat = c.bits;
        if (intBits != expectedInt || floatBits != expectedFloat) capture.issue = autotest::Capture::InvalidReport;
    }
    number(receiver->m_callbacks.size());
    for (unsigned i = 0; i < receiver->m_callbacks.size(); ++i) {
        number(receiver->m_callbacks[i].size());
        for (unsigned j = 0; j < receiver->m_callbacks[i].size(); ++j)
            number(receiver->m_callbacks[i][j] == &callbackA ? 1 : receiver->m_callbacks[i][j] == &callbackB ? 2 : 999);
    }
    // All bytes outside the three live vector objects must remain untouched.
    for (unsigned i = 0; i < sizeof(storage); ++i)
        if (i < 0x28 || i >= 0x70)
            if (reinterpret_cast<unsigned char*>(storage)[i] != before[i]) capture.issue = autotest::Capture::InvalidReport;
    receiver->m_callbacks.~vector(); receiver->m_floatValues.~vector(); receiver->m_intValues.~vector();
}
void original(void* data, autotest::Capture& capture) { side(*static_cast<Case*>(data), false, capture); }
void recovered(void* data, autotest::Capture& capture) { side(*static_cast<Case*>(data), true, capture); }
}
TL_TEST(dynamic_property_setters_differential) {
    const unsigned sizes[] = {0, 1, 3, 8};
    const unsigned indices[] = {0, 1, 2, 7, 8, UINT_MAX};
    const unsigned ints[] = {0, 1, 0xffffffffu, 0x80000000u, 0x7fffffffu, 0x12345678u, 255, 1024};
    const unsigned floats[] = {0, 0x80000000u, 0x3f800000u, 0xbf800000u, 0x7f800000u, 0xff800000u, 0x7fc12345u, 1};
    const uint64_t addresses[] = {(uint64_t)(uintptr_t)&originalInt, (uint64_t)(uintptr_t)&originalFloat};
    for (unsigned op = 0; op < 2; ++op) {
        autotest::Coverage coverage("dynamic_property_setters_differential", addresses[op]);
        for (unsigned s = 0; s < 4; ++s) for (unsigned i = 0; i < 6; ++i) for (unsigned m = 0; m < 4; ++m) {
            unsigned v = (s * 3 + i + m) % 8;
            Case c = {op, sizes[s], indices[i], m, op == 0 ? ints[v] : floats[v]};
            autotest::Outcome a, b; autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
            if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
        }
        coverage.report(host);
    }
    return 0;
}
