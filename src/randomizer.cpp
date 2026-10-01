#include "torchlight/randomizer.hpp"
#include "torchlight/recovered/mwc_float.hpp"

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
    // original-code @0xc92a70: shared reviewed recipe with volatile @0xc92b50.
    // One finish/observer event remains owned by this production wrapper.
    return finish(recovered::mwc_between(state_, low, high));
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
    // original-code @0xc92b50; port-owned stream, original global lifetime open.
    return recovered::mwc_between(state_, low, high);
}

} // namespace torchlight
