#include "torchlight/randomizer.hpp"

#include <cstring>
#include <stdexcept>

namespace torchlight {

TorchlightRandom::TorchlightRandom(std::uint32_t seed) : state_(seed) {
    if (seed == 0) {
        throw std::invalid_argument("TorchlightRandom requires a non-zero seed");
    }
}

std::uint64_t TorchlightRandom::advance() noexcept {
    state_ = static_cast<std::uint64_t>(static_cast<std::uint32_t>(state_)) *
                 UINT64_C(0x29777b41) +
             (state_ >> 32U);
    return state_;
}

std::int32_t TorchlightRandom::integer_between(std::int32_t low, std::int32_t high) noexcept {
    if (high <= low) {
        return low;
    }
    const auto value = advance();
    const auto span = static_cast<std::uint32_t>(high) - static_cast<std::uint32_t>(low) + 1U;
    const auto offset = static_cast<std::uint32_t>(value) % span;
    const auto result = static_cast<std::int64_t>(low) + static_cast<std::int64_t>(offset);
    return result > high ? high : static_cast<std::int32_t>(result);
}

float TorchlightRandom::between(float low, float high) noexcept {
    if (high == low) {
        return low;
    }
    const auto first = advance();
    const auto second = advance();
    const std::uint64_t mantissa =
        (static_cast<std::uint64_t>(static_cast<std::uint32_t>(second)) + (first << 32U)) &
        UINT64_C(0x000fffffffffffff);
    const std::uint64_t bits = UINT64_C(0x3ff0000000000000) | mantissa;
    double unit = 0.0;
    std::memcpy(&unit, &bits, sizeof(unit));
    unit -= 1.0;
    return low + static_cast<float>(static_cast<double>(high - low) * unit);
}

std::size_t weighted_index(const std::vector<float>& weights, TorchlightRandom& random) {
    float total = 0.0F;
    for (const auto weight : weights) {
        total += weight;
    }
    if (!(total > 0.0F)) {
        throw std::invalid_argument("Weighted choice has no positive weight");
    }
    const auto sample = random.between(0.0F, 1.0F);
    float cumulative = 0.0F;
    for (std::size_t index = 0; index < weights.size(); ++index) {
        cumulative += weights[index] / total;
        if (cumulative > sample) {
            return index;
        }
    }
    // CRandomizer::getRandom() returns choice zero if float rounding leaves a
    // gap after the final cumulative interval.
    return 0;
}

} // namespace torchlight
