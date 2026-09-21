#pragma once

#include "torchlight/randomizer.hpp"
#include "torchlight/ui_dropdown_animation.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace torchlight {

class PakArchive;

struct UiPcmSound {
    std::uint32_t sample_rate = 0;
    std::uint16_t channels = 0;
    std::vector<std::int16_t> samples;
    float volume = 0.0F;
    float volume_variation = 0.0F;
};

struct UiSoundVoice {
    const UiPcmSound* sound = nullptr;
    std::size_t frame = 0;
    float gain = 1.0F;
};

// Bounded one-shot PCM mixer for the original UI sound bank. One persistent
// worker owns the optional ALSA stream; play() never creates a thread.
// UI.DAT selection and per-channel gain follow the original. ALSA mixing,
// oldest-voice eviction at the resource max-audible bound, and the locally
// seeded VolatileRandom stream are portable adapters; they do not claim the
// process-global FMOD device/mixer/RNG state.
class UiSoundPlayer {
public:
    explicit UiSoundPlayer(const PakArchive& archive);
    ~UiSoundPlayer();
    UiSoundPlayer(const UiSoundPlayer&) = delete;
    UiSoundPlayer& operator=(const UiSoundPlayer&) = delete;

    void play(DropdownSoundRequest request);
    void set_levels(float sound_volume, bool sound_mute) noexcept;
    void stop();

    [[nodiscard]] const UiPcmSound& sound(DropdownSoundRequest request) const;
    [[nodiscard]] static UiPcmSound decode_pcm16_wav(
        const std::vector<std::uint8_t>& bytes);
    [[nodiscard]] static float channel_gain(float volume, float variation,
                                            VolatileRandom& random) noexcept;
    [[nodiscard]] static std::vector<std::int16_t> mix(
        std::vector<UiSoundVoice>& voices, std::size_t frames,
        float group_volume, bool muted);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace torchlight
