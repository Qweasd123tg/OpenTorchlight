#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace torchlight {

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

} // namespace torchlight
