#include "torchlight/randomizer.hpp"

#include <cstring>
#include <stdexcept>

namespace torchlight {
namespace {
thread_local RandomObserver observer = nullptr;
thread_local void* observer_context = nullptr;
void emit(const RandomObservation& value) noexcept { if (observer) observer(value, observer_context); }
}
RandomObservationScope::RandomObservationScope(RandomObserver callback, void* context) noexcept
    : previous_(observer), previous_context_(observer_context) { observer = callback; observer_context = context; }
RandomObservationScope::~RandomObservationScope() { observer = previous_; observer_context = previous_context_; }


TorchlightRandom::TorchlightRandom(std::uint32_t seed) : state_(seed) {
    if (seed == 0) {
        throw std::invalid_argument("TorchlightRandom requires a non-zero seed");
    }
    if (observer) { RandomObservation event; event.after = seed; emit(event); }
}

std::uint64_t TorchlightRandom::advance() noexcept {
    state_ = static_cast<std::uint64_t>(static_cast<std::uint32_t>(state_)) *
                 UINT64_C(0x29777b41) +
             (state_ >> 32U);
    return state_;
}

std::int32_t TorchlightRandom::integer_between(std::int32_t low, std::int32_t high) noexcept {
    const auto before = state_;
    const auto finish = [&](std::int32_t result) noexcept {
        if (observer) {
            RandomObservation event; event.kind = RandomObservation::Kind::integer;
            event.before = before; event.after = state_;
            event.integer_low = low; event.integer_high = high; event.integer_result = result; emit(event);
        }
        return result;
    };
    if (high <= low) return finish(low);
    const auto value = advance();
    const auto span = static_cast<std::uint32_t>(high) - static_cast<std::uint32_t>(low) + 1U;
    const auto offset = static_cast<std::uint32_t>(value) % span;
    const auto result = static_cast<std::int64_t>(low) + static_cast<std::int64_t>(offset);
    return finish(result > high ? high : static_cast<std::int32_t>(result));
}

float TorchlightRandom::between(float low, float high) noexcept {
    const auto before = state_;
    const auto finish = [&](float result) noexcept {
        if (observer) {
            RandomObservation event; event.kind = RandomObservation::Kind::real;
            event.before = before; event.after = state_;
            event.real_low = low; event.real_high = high; event.real_result = result; emit(event);
        }
        return result;
    };
    if (high == low) return finish(low);
    const auto first = advance();
    const auto second = advance();
    const std::uint64_t mantissa =
        (static_cast<std::uint64_t>(static_cast<std::uint32_t>(second)) + (first << 32U)) &
        UINT64_C(0x000fffffffffffff);
    const std::uint64_t bits = UINT64_C(0x3ff0000000000000) | mantissa;
    double unit = 0.0;
    std::memcpy(&unit, &bits, sizeof(unit));
    unit -= 1.0;
    return finish(low + static_cast<float>(static_cast<double>(high - low) * unit));
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

float VolatileRandom::between(float low, float high) noexcept {
    // original-code @0xc92b50, transcribed op-for-op. ucomiss(lo,hi): NaN
    // takes jp into the random path; equal takes je home with low.
    // (NaN == NaN) is false, so NaN correctly falls through below.
    if (low == high)
        return low;
    const float range_f = high - low;
    const double range_d = static_cast<double>(range_f);
    constexpr std::uint64_t kMul = 0x29777B41u;
    // original-code @0xc92ba8: movabs $0xfffffffffffff (52 fraction bits).
    // Keeping only 44 bits incorrectly restricts the fraction to [0,1/256).
    constexpr std::uint64_t kMask52 = UINT64_C(0x000fffffffffffff);
    constexpr std::uint64_t kExp = 0x3FF0000000000000ull;
    const std::uint64_t lo32 = state_ & 0xFFFFFFFFu;
    const std::uint64_t hi32 = state_ >> 32;
    const std::uint64_t t2 = lo32 * kMul + hi32;
    const std::uint64_t t3 = (t2 & 0xFFFFFFFFu) * kMul + (t2 >> 32);
    state_ = t3;
    const std::uint64_t bits =
        ((t3 & 0xFFFFFFFFu) + ((t2 & 0xFFFFFFFFu) << 32)) & kMask52;
    const std::uint64_t raw = bits | kExp;
    double frac = 0.0;
    std::memcpy(&frac, &raw, sizeof(frac));
    frac = frac - 1.0;
    const float scaled = static_cast<float>(range_d * frac);
    return low + scaled;
}

} // namespace torchlight
