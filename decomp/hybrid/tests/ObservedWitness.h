// Fixture-only accounting: a caught exception is not a completed primary call.
#ifndef OBSERVED_WITNESS_H
#define OBSERVED_WITNESS_H
#include "AutoTest.h"
namespace observed_witness {
inline void finish(autotest::Capture& capture, unsigned fault)
{
    capture.add(&fault, sizeof(fault));
}
inline bool hasFault(const autotest::Capture& capture, unsigned expected)
{
    if (capture.length < sizeof(unsigned) || capture.length > autotest::Capture::kSize) return false;
    unsigned actual = 0;
    std::memcpy(&actual, capture.data + capture.length - sizeof(actual), sizeof(actual));
    return actual == expected;
}
inline int observe(const tlhybrid_host* host, autotest::Coverage& coverage,
                   const autotest::Outcome& a, const autotest::Outcome& b,
                   unsigned expectedFault, unsigned& witnesses)
{
    // The fault category comes from the caught value/type, never the case's expectation.
    if (!hasFault(a.capture, expectedFault) || !hasFault(b.capture, expectedFault)) {
        ++coverage.missing;
        return 2;
    }
    if (!expectedFault) return coverage.observe(host, a, b);
    const bool valid = a.childStatus == 0 && b.childStatus == 0 &&
        a.reportValid && b.reportValid && !autotest::incomplete(a) && !autotest::incomplete(b) &&
        a.capture.issue == autotest::Capture::Complete && b.capture.issue == autotest::Capture::Complete &&
        a.capture.callStarted == 1 && b.capture.callStarted == 1 &&
        a.capture.callCompleted == 0 && b.capture.callCompleted == 0 &&
        a.capture.callTarget == coverage.original && host && host->abi_version == TLHYBRID_ABI_VERSION &&
        host->comparison_pair && host->comparison_pair(coverage.original, b.capture.callTarget);
    if (!valid) { ++coverage.missing; return 2; }
    if (a.capture.length != b.capture.length ||
        std::memcmp(a.capture.data, b.capture.data, a.capture.length)) {
        ++coverage.different;
        return 1;
    }
    ++witnesses;
    return 0;
}
// Exercise the actual clean pair's gate without attributing these mutations to coverage.
// Each replacement-side corruption must fail closed; the caller's outcomes are untouched.
inline bool negativeControls(const tlhybrid_host* host, const autotest::Coverage& coverage,
                             const autotest::Outcome& a, const autotest::Outcome& b,
                             unsigned expectedFault)
{
    if (!expectedFault) return false;
    for (unsigned mutation = 0; mutation < 8; ++mutation) {
        autotest::Outcome changed = b;
        switch (mutation) {
        case 0: changed.capture.callCompleted = 1; break;
        case 1: changed.capture.callStarted = 0; break;
        case 2: changed.capture.callTarget = 0; break;
        case 3: changed.reportValid = false; break;
        case 4: changed.capture.issue = autotest::Capture::InvalidReport; break;
        case 5: changed.capture.data[changed.capture.length - 1] ^= 1; break;
        case 6: changed.capture.data[0] ^= 1; break;
        case 7: changed.capture.length = 0; break;
        }
        autotest::Coverage probe(coverage.name, coverage.original);
        unsigned witnesses = 0;
        if (observe(host, probe, a, changed, expectedFault, witnesses) == 0 ||
            witnesses != 0 || probe.completed != 0) return false;
    }
    host->log("    %s rejected 8 replacement-report negative controls\n", coverage.name);
    return true;
}
inline bool totals(const tlhybrid_host* host, const autotest::Coverage& coverage,
                   unsigned witnesses, unsigned normalExpected, unsigned exceptionExpected)
{
    host->log("    %s expected-exception witnesses %u (excluded from completed coverage)\n", coverage.name, witnesses);
    return coverage.completed == normalExpected && witnesses == exceptionExpected &&
        coverage.different == 0 && coverage.missing == 0;
}
}
#endif
