#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace torchlight {

// Port-native optional observation. No pointers appear in the trace; the sink
// supplies an ordered sequence. No callback is invoked unless explicitly scoped.
struct RandomObservation {
    enum class Kind { seed, integer, real } kind = Kind::seed;
    std::uint64_t before = 0, after = 0;
    std::int32_t integer_low = 0, integer_high = 0, integer_result = 0;
    float real_low = 0, real_high = 0, real_result = 0;
};
using RandomObserver = void (*)(const RandomObservation&, void*) noexcept;
class RandomObservationScope {
public:
    RandomObservationScope(RandomObserver, void*) noexcept;
    ~RandomObservationScope();
    RandomObservationScope(const RandomObservationScope&) = delete;
    RandomObservationScope& operator=(const RandomObservationScope&) = delete;
private:
    RandomObserver previous_;
    void* previous_context_;
};

// The deterministic generator used by the original Linux build. Seed zero was
// time-based there; recovered code requires an explicit non-zero seed instead.
class TorchlightRandom {
public:
    explicit TorchlightRandom(std::uint32_t seed);

    [[nodiscard]] std::uint64_t state() const noexcept { return state_; }
    [[nodiscard]] std::int32_t integer_between(std::int32_t low, std::int32_t high) noexcept;
    [[nodiscard]] float between(float low, float high) noexcept;

private:
    friend struct CheckpointAccess;
    [[nodiscard]] std::uint64_t advance() noexcept;

    std::uint64_t state_;
};

// CRandomizer's normal mode: negative and zero weights are ineffective and the
// first cumulative interval strictly greater than the random sample wins.
[[nodiscard]] std::size_t weighted_index(const std::vector<float>& weights,
                                         TorchlightRandom& random);

// The original's separate volatile stream (UTILITIES::randomBetweenVolatile
// @0xc92b50): 64-bit LCG, multiplier 0x29777B41, process-global state.
// Bit-exact integer transcription; the double bit-trick yields frac in
// [0,1). NaN bounds take the random path (jp), equal bounds return low.
class VolatileRandom {
public:
    explicit VolatileRandom(std::uint64_t seed) noexcept : state_(seed) {}

    [[nodiscard]] std::uint64_t state() const noexcept { return state_; }
    [[nodiscard]] float between(float low, float high) noexcept;

private:
    std::uint64_t state_;
};

} // namespace torchlight
