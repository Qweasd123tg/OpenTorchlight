#pragma once

#include "torchlight/randomizer.hpp"
#include "torchlight/ui_dropdown_animation.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace torchlight {

class PakArchive;

// Bank-local sample IDs have different bindings in the original menu
// constructors. A cue names the resolved resource, not a global sample ID.
enum class UiSoundRequest : std::uint8_t {
    center_open, center_close, inventory_open, inventory_close, stats_open, stats_close
};
enum class UiPanelSoundBank : std::uint8_t { inventory, merchant, quest, skill };
[[nodiscard]] std::optional<UiSoundRequest> ui_panel_sound_request(UiPanelSoundBank, int sample) noexcept;

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
    std::uint64_t rate_remainder = 0; // numerator over fixed output rate; portable interpolation
};

// Bounded one-shot PCM mixer for the original UI sound bank. One persistent
// worker owns the optional ALSA stream; play() never creates a thread.
// UI.DAT selection and per-channel gain follow the original. ALSA mixing,
// oldest-voice eviction at the resource max-audible bound, and the locally
// seeded VolatileRandom stream are portable adapters; they do not claim the
// process-global FMOD device/mixer/RNG state. Mixed-rate PCM uses portable
// linear interpolation; output_rate stays fixed for each voice's lifetime.
class UiSoundPlayer {
public:
    explicit UiSoundPlayer(const PakArchive& archive);
    ~UiSoundPlayer();
    UiSoundPlayer(const UiSoundPlayer&) = delete;
    UiSoundPlayer& operator=(const UiSoundPlayer&) = delete;

    void play(DropdownSoundRequest request);
    void play(UiSoundRequest request);
    void set_levels(float sound_volume, bool sound_mute) noexcept;
    void stop();

    [[nodiscard]] const UiPcmSound& sound(DropdownSoundRequest request) const;
    [[nodiscard]] const UiPcmSound& sound(UiSoundRequest request) const;
    [[nodiscard]] static UiPcmSound decode_pcm16_wav(
        const std::vector<std::uint8_t>& bytes);
    [[nodiscard]] static float channel_gain(float volume, float variation,
                                            VolatileRandom& random) noexcept;
    [[nodiscard]] static std::vector<std::int16_t> mix(
        std::vector<UiSoundVoice>& voices, std::size_t frames,
        float group_volume, bool muted, std::uint32_t output_rate = 44100);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace torchlight
