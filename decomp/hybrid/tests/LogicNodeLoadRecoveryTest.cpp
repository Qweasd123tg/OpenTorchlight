#include <cstdio>
#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "LogicNodeState.h"

TL_ORIGINAL(void, logicLoadOriginal, (CLogicNodeState*, FILE*, unsigned), "_ZN15CLogicNodeState4loadEP8_IO_FILEj")
extern "C" void logicLoadCandidate(CLogicNodeState*, FILE*, unsigned) __asm__("_ZN15CLogicNodeState4loadEP8_IO_FILEj");

namespace {
struct Case { unsigned version, seed, tail; bool negative; };
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    unsigned short units[12] = {0};
    unsigned length = c.seed % 6;
    if (length == 1) units[0] = 'A';
    if (length == 2) { units[0] = 0x416; units[1] = 0x4e2d; }
    if (length == 3) { units[0] = 'a'; units[1] = 0; units[2] = 'z'; }
    if (length == 4) { units[0] = 0xd83d; units[1] = 0xde42; units[2] = 'b'; units[3] = 0x20ac; }
    if (length == 5) { units[0] = 'x'; units[1] = 0xd83d; units[2] = 0xde42; units[3] = 0x416; units[4] = 'y'; }
    FILE* file = tmpfile();
    if (!file) _exit(41);
    unsigned short count = length;
    fwrite(&count, 2, 1, file);
    fwrite(units, 2, length, file);
    unsigned char bytes[96];
    for (unsigned i = 0; i < sizeof(bytes); ++i) bytes[i] = static_cast<unsigned char>(c.seed * 37 + i * 11);
    bytes[0] = c.seed % 4 == 0 ? 0 : c.seed % 4 == 1 ? 1 : c.seed % 4 == 2 ? 0x80 : 0xff;
    bytes[1] = c.seed % 3 ? 0 : 3;
    bytes[2] = c.seed % 2 ? 0 : 0x80;
    bytes[3] = c.seed % 4 == 3 ? 0xff : 0;
    fwrite(bytes, 1, c.tail, file);
    rewind(file);
    union Storage { long double align; char bytes[sizeof(CLogicNodeState)]; } storage;
    std::memset(storage.bytes, 0xa5, sizeof(storage.bytes));
    CLogicNodeState* state = new(storage.bytes) CLogicNodeState;
    state->m_wstrName = c.seed % 2 ? L"previous-name-Ж" : L"";
    // Initialize every field and padding, so partial fread writes remain observable.
    std::memset(reinterpret_cast<char*>(state) + 0x10, 0x5a, 0x18);
    std::memset(reinterpret_cast<char*>(state) + 0x30, 0xa5, 0x30);
    autotest::invoke(out, ours ? logicLoadCandidate : logicLoadOriginal, state, file, c.version);
    if (ours && c.negative) state->m_parentHierarchyHash ^= 1;
    out.add(reinterpret_cast<char*>(state) + 0x10, 0x18);
    out.addText(state->m_wstrName);
    out.add(reinterpret_cast<char*>(state) + 0x30, 0x30);
    long position = ftell(file);
    int eof = feof(file), error = ferror(file);
    out.add(&position, sizeof(position)); out.add(&eof, sizeof(eof)); out.add(&error, sizeof(error));
    unsigned char rest[128]; size_t remaining = fread(rest, 1, sizeof(rest), file);
    out.add(&remaining, sizeof(remaining)); out.add(rest, remaining);
    state->~CLogicNodeState();
    fclose(file);
}
void original(void* p, autotest::Capture& out) { side(p, out, false); }
void candidate(void* p, autotest::Capture& out) { side(p, out, true); }
}

TL_TEST(logic_node_load_recovery)
{
    autotest::Coverage coverage("logic_node_load_recovery", 0x970260);
    const unsigned versions[] = {0, 1, 15, 16, 17, 18, 0xffffffffu};
    const unsigned tails[] = {1, 4, 19, 39, 47, 60, 96};
    for (unsigned v = 0; v < 7; ++v) for (unsigned t = 0; t < 7; ++t) for (unsigned s = 0; s < 6; ++s) {
        Case c = {versions[v], s + v * 6 + t * 42, tails[t], false};
        autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(candidate, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    logic load version %u seed %u tail %u status %d/%d issue %u/%u bytes %lu/%lu\n", c.version, c.seed, c.tail, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case negative = {17, 7, 96, true}; autotest::Outcome a, b;
    autotest::runChild(original, &negative, a); autotest::runChild(candidate, &negative, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    logic load negative control detected %u\n", detected ? 1 : 0);
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
