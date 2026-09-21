#include "torchlight/ui_sound.hpp"

#include "torchlight/adm_document.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/resource_fields.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstring>
#include <limits>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

#ifdef TORCHLIGHT_HAVE_MUSIC
#if defined(__linux__)
#include <alsa/asoundlib.h>
#endif
#endif

namespace torchlight {
namespace {

std::uint16_t u16(const std::vector<std::uint8_t>& bytes, std::size_t at) {
    if (at + 2U > bytes.size()) throw std::invalid_argument("truncated WAV uint16");
    return static_cast<std::uint16_t>(bytes[at]) |
           static_cast<std::uint16_t>(bytes[at + 1U] << 8U);
}

std::uint32_t u32(const std::vector<std::uint8_t>& bytes, std::size_t at) {
    if (at + 4U > bytes.size()) throw std::invalid_argument("truncated WAV uint32");
    return static_cast<std::uint32_t>(bytes[at]) |
           (static_cast<std::uint32_t>(bytes[at + 1U]) << 8U) |
           (static_cast<std::uint32_t>(bytes[at + 2U]) << 16U) |
           (static_cast<std::uint32_t>(bytes[at + 3U]) << 24U);
}

bool fourcc(const std::vector<std::uint8_t>& bytes, std::size_t at, const char* value) {
    return at + 4U <= bytes.size() &&
           std::memcmp(bytes.data() + at, value, 4U) == 0;
}

const AdmGroup* sound_group(const AdmGroup& group, const std::u16string& wanted) {
    if (resource_fields::upper(group.name) == u"SOUND" &&
        resource_fields::upper(resource_fields::text(group, u"NAME")) == wanted) {
        return &group;
    }
    for (const auto& child : group.groups) {
        if (const auto* found = sound_group(child, wanted)) return found;
    }
    return nullptr;
}

std::u16string descendant_text(const AdmGroup& group, const std::u16string& key) {
    if (const auto* field = resource_fields::field(group, key)) {
        if (const auto* value = std::get_if<std::u16string>(&field->value)) return *value;
        throw std::invalid_argument("UI sound file field has wrong type");
    }
    for (const auto& child : group.groups) {
        const auto value = descendant_text(child, key);
        if (!value.empty()) return value;
    }
    return {};
}

std::int16_t clamp_pcm(float value) {
    const float scaled = value * 32768.0F;
    if (!(scaled >= -32768.0F)) return std::numeric_limits<std::int16_t>::min();
    if (!(scaled <= 32767.0F)) return std::numeric_limits<std::int16_t>::max();
    return static_cast<std::int16_t>(scaled);
}

std::size_t request_index(DropdownSoundRequest request) {
    return request == DropdownSoundRequest::open ? 0U : 1U;
}

} // namespace

struct UiSoundPlayer::Impl {
    std::array<UiPcmSound, 2> sounds;
    std::mutex mutex;
    std::condition_variable wake;
    std::vector<UiSoundVoice> voices;
    VolatileRandom random{
        static_cast<std::uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
    std::atomic<float> group_volume{1.0F};
    std::atomic<bool> muted{false};
    std::atomic<bool> stopping{false};
    std::thread worker;
    bool worker_started = false;

    explicit Impl(const PakArchive& archive) {
        const auto document = parse_adm(archive.read_normalized("media/sounds/UI.DAT.adm"));
        const std::array<std::u16string, 2> names{u"CENTEROPEN", u"CENTERCLOSE"};
        const std::array<std::int64_t, 2> guids{
            INT64_C(2190439802373280222), INT64_C(2190439810963214814)};
        for (std::size_t index = 0; index < names.size(); ++index) {
            const auto* definition = sound_group(document.root, names[index]);
            if (definition == nullptr) throw std::runtime_error("UI sound definition is absent");
            if (resource_fields::upper(resource_fields::text(*definition, u"CATEGORY")) != u"UI" ||
                resource_fields::flag(*definition, u"LOOPS", true) ||
                resource_fields::number(*definition, u"FREQUENCYVARIATION", -1.0) != 0.0 ||
                resource_fields::guid(*definition, u"GUID") != guids[index]) {
                throw std::runtime_error("dropdown UI sound contract changed");
            }
            const auto file = descendant_text(*definition, u"FILE");
            if (file.empty()) throw std::runtime_error("dropdown UI sound has no FILE");
            auto decoded = UiSoundPlayer::decode_pcm16_wav(
                archive.read_normalized(resource_fields::ascii(file)));
            decoded.volume = static_cast<float>(
                resource_fields::number(*definition, u"VOLUME", -1.0));
            decoded.volume_variation = static_cast<float>(
                resource_fields::number(*definition, u"VOLUMEVARIATION", -1.0));
            if (decoded.volume < 0.0F || decoded.volume_variation < 0.0F) {
                throw std::runtime_error("dropdown UI sound has invalid gain data");
            }
            sounds[index] = std::move(decoded);
        }
        if (sounds[0].sample_rate != sounds[1].sample_rate) {
            throw std::runtime_error("dropdown UI sounds use different sample rates");
        }
    }

    void run() {
#if defined(TORCHLIGHT_HAVE_MUSIC) && defined(__linux__)
        snd_pcm_t* pcm = nullptr;
        unsigned rate = sounds[0].sample_rate;
        if (snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) == 0) {
            // ALSA's bounded portable backend may soft-resample, while the
            // resource mixer itself stays at the exact 44100 Hz WAV rate.
            if (snd_pcm_set_params(pcm, SND_PCM_FORMAT_S16_LE,
                                   SND_PCM_ACCESS_RW_INTERLEAVED, 2U, rate,
                                   1, 500000U) != 0) {
                snd_pcm_close(pcm);
                pcm = nullptr;
            }
        }
#else
        void* pcm = nullptr;
#endif
        while (!stopping.load()) {
            std::vector<std::int16_t> output;
            {
                std::unique_lock<std::mutex> lock(mutex);
                wake.wait(lock, [&] { return stopping.load() || !voices.empty(); });
                if (stopping.load()) break;
                output = UiSoundPlayer::mix(
                    voices, 512U, group_volume.load(), muted.load());
            }
#if defined(TORCHLIGHT_HAVE_MUSIC) && defined(__linux__)
            if (pcm != nullptr && !output.empty()) {
                snd_pcm_uframes_t remaining =
                    static_cast<snd_pcm_uframes_t>(output.size() / 2U);
                snd_pcm_uframes_t offset = 0U;
                while (remaining != 0U && !stopping.load()) {
                    const auto written = snd_pcm_writei(
                        pcm, output.data() + offset * 2U, remaining);
                    if (written < 0) {
                        if (snd_pcm_recover(pcm, static_cast<int>(written), 0) < 0) break;
                        continue;
                    }
                    if (written == 0) break;
                    offset += static_cast<snd_pcm_uframes_t>(written);
                    remaining -= static_cast<snd_pcm_uframes_t>(written);
                }
            } else if (pcm == nullptr) {
                std::lock_guard<std::mutex> lock(mutex);
                voices.clear();
            }
#else
            static_cast<void>(pcm);
            std::lock_guard<std::mutex> lock(mutex);
            voices.clear();
#endif
        }
#if defined(TORCHLIGHT_HAVE_MUSIC) && defined(__linux__)
        if (pcm != nullptr) {
            snd_pcm_drop(pcm);
            snd_pcm_close(pcm);
        }
#endif
    }
};

UiPcmSound UiSoundPlayer::decode_pcm16_wav(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 12U || !fourcc(bytes, 0U, "RIFF") || !fourcc(bytes, 8U, "WAVE")) {
        throw std::invalid_argument("UI sound is not RIFF/WAVE");
    }
    UiPcmSound result;
    bool have_format = false;
    bool have_data = false;
    std::size_t cursor = 12U;
    while (cursor + 8U <= bytes.size()) {
        const auto size = static_cast<std::size_t>(u32(bytes, cursor + 4U));
        const auto body = cursor + 8U;
        if (size > bytes.size() - body) throw std::invalid_argument("truncated WAV chunk");
        if (fourcc(bytes, cursor, "fmt ")) {
            if (size < 16U || u16(bytes, body) != 1U || u16(bytes, body + 14U) != 16U) {
                throw std::invalid_argument("UI WAV is not PCM16");
            }
            result.channels = u16(bytes, body + 2U);
            result.sample_rate = u32(bytes, body + 4U);
            const auto block_align = u16(bytes, body + 12U);
            if ((result.channels != 1U && result.channels != 2U) ||
                result.sample_rate == 0U || block_align != result.channels * 2U) {
                throw std::invalid_argument("UI WAV has unsupported format fields");
            }
            have_format = true;
        } else if (fourcc(bytes, cursor, "data")) {
            if ((size & 1U) != 0U) throw std::invalid_argument("UI WAV PCM data is unaligned");
            result.samples.resize(size / 2U);
            for (std::size_t index = 0; index < result.samples.size(); ++index) {
                result.samples[index] = static_cast<std::int16_t>(u16(bytes, body + index * 2U));
            }
            have_data = true;
        }
        cursor = body + size + (size & 1U);
    }
    if (!have_format || !have_data || result.samples.empty() ||
        result.samples.size() % result.channels != 0U) {
        throw std::invalid_argument("UI WAV lacks a complete PCM stream");
    }
    return result;
}

float UiSoundPlayer::channel_gain(float volume, float variation,
                                  VolatileRandom& random) noexcept {
    return std::min(volume + random.between(0.0F, variation), 1.0F);
}

std::vector<std::int16_t> UiSoundPlayer::mix(
    std::vector<UiSoundVoice>& voices, std::size_t frames,
    float group_volume, bool muted) {
    const float group_gain = muted || !(group_volume >= 0.0F)
                                 ? 0.0F : std::min(group_volume, 1.0F);
    std::vector<std::int16_t> output(frames * 2U);
    for (std::size_t frame = 0; frame < frames; ++frame) {
        float left = 0.0F;
        float right = 0.0F;
        for (auto& voice : voices) {
            if (voice.sound == nullptr) continue;
            const auto& sound = *voice.sound;
            const auto total_frames = sound.samples.size() / sound.channels;
            if (voice.frame >= total_frames) continue;
            const auto sample = voice.frame * sound.channels;
            left += static_cast<float>(sound.samples[sample]) / 32768.0F * voice.gain;
            right += static_cast<float>(sound.samples[
                sample + (sound.channels == 2U ? 1U : 0U)]) / 32768.0F * voice.gain;
            ++voice.frame;
        }
        output[frame * 2U] = clamp_pcm(left * group_gain);
        output[frame * 2U + 1U] = clamp_pcm(right * group_gain);
    }
    voices.erase(std::remove_if(voices.begin(), voices.end(), [](const auto& voice) {
        return voice.sound == nullptr ||
               voice.frame >= voice.sound->samples.size() / voice.sound->channels;
    }), voices.end());
    return output;
}

UiSoundPlayer::UiSoundPlayer(const PakArchive& archive)
    : impl_(std::make_unique<Impl>(archive)) {}
UiSoundPlayer::~UiSoundPlayer() { stop(); }

void UiSoundPlayer::play(DropdownSoundRequest request) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->stopping.load()) return;
    if (!impl_->worker_started) {
        impl_->worker_started = true;
        impl_->worker = std::thread([impl = impl_.get()] { impl->run(); });
    }
    // Each UI sound's group sets FMOD max-audible=6. The port's oldest-voice
    // eviction is an output-backend policy; FMOD behavior enum 1 remains open.
    constexpr std::size_t kMaximumVoices = 6U;
    const auto& sound = impl_->sounds[request_index(request)];
    const auto same_sound = static_cast<std::size_t>(std::count_if(
        impl_->voices.begin(), impl_->voices.end(), [&](const auto& voice) {
            return voice.sound == &sound;
        }));
    if (same_sound >= kMaximumVoices) {
        const auto oldest = std::find_if(
            impl_->voices.begin(), impl_->voices.end(), [&](const auto& voice) {
                return voice.sound == &sound;
            });
        impl_->voices.erase(oldest);
    }
    impl_->voices.push_back({&sound, 0U,
        channel_gain(sound.volume, sound.volume_variation, impl_->random)});
    impl_->wake.notify_one();
}

void UiSoundPlayer::set_levels(float sound_volume, bool sound_mute) noexcept {
    impl_->group_volume.store(sound_volume);
    impl_->muted.store(sound_mute);
}

void UiSoundPlayer::stop() {
    if (!impl_ || impl_->stopping.exchange(true)) return;
    impl_->wake.notify_all();
    if (impl_->worker.joinable()) impl_->worker.join();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    impl_->voices.clear();
}

const UiPcmSound& UiSoundPlayer::sound(DropdownSoundRequest request) const {
    return impl_->sounds[request_index(request)];
}

} // namespace torchlight
