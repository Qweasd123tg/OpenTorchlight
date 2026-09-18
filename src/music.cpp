#include "torchlight/music.hpp"
#include <algorithm>
#include <atomic>
#include <cctype>
#include <cmath>
#include <cstring>
#include <thread>

#ifdef TORCHLIGHT_HAVE_MUSIC
#include <vorbis/vorbisfile.h>
#if defined(__linux__)
#include <alsa/asoundlib.h>
#endif
#endif

namespace torchlight {
namespace {
std::string upper_ascii(std::string value) {
    for (auto &c : value)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return value;
}
std::int16_t clamp_sample(float v, float gain) {
    v *= gain * 32767.0F;
    if (!(v >= -32768.0F)) return static_cast<std::int16_t>(-32768);
    if (!(v <= 32767.0F)) return static_cast<std::int16_t>(32767);
    return static_cast<std::int16_t>(v);
}
} // namespace
std::string music_track_for_menu() {
    return "TITLE.OGG";
}
std::string music_track_for_dungeon(const std::string &dungeon_name,
                                    const std::string &theme) {
    const auto dungeon = upper_ascii(dungeon_name);
    if (dungeon == "TOWN") return "TOWN.OGG";
    const auto kind = upper_ascii(theme);
    if (!kind.empty()) return kind + ".OGG";
    return "TOWN.OGG";
}
float MusicPlayer::apply_gain(float sample, float volume, bool muted) {
    if (muted) return 0.0F;
    if (!(volume >= 0.0F)) return 0.0F;
    if (!(volume <= 1.0F)) volume = 1.0F;
    return sample * volume;
}
std::vector<std::int16_t> MusicPlayer::mix_frame(float left, float right, float gain) {
    return {clamp_sample(left, gain), clamp_sample(right, gain)};
}
struct MusicPlayer::Impl {
    std::mutex mutex;
    std::thread worker;
    std::atomic<bool> stop_flag{false};
    std::atomic<bool> running{false};
    std::string current;
    std::string directory, track;
    std::atomic<float> volume{1.0F};
    std::atomic<bool> muted{false};
};
MusicPlayer::MusicPlayer() : impl_(std::make_unique<Impl>()) {}
MusicPlayer::~MusicPlayer() {
    stop();
}
void MusicPlayer::stop() {
    impl_->stop_flag.store(true);
    if (impl_->worker.joinable()) impl_->worker.join();
    impl_->stop_flag.store(false);
    impl_->running.store(false);
    std::lock_guard<std::mutex> lock(impl_->mutex);
    impl_->current.clear();
}
void MusicPlayer::set_levels(float volume, bool muted) {
    impl_->volume.store(volume);
    impl_->muted.store(muted);
}
std::string MusicPlayer::current() const {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->current;
}
void MusicPlayer::request(const std::string &music_directory, const std::string &track,
                          float volume, bool muted) {
    {
        std::lock_guard<std::mutex> lock(impl_->mutex);
        if (track == impl_->current && music_directory == impl_->directory &&
            impl_->volume.load() == volume && impl_->muted.load() == muted)
            return;
        impl_->directory = music_directory;
        impl_->track = track;
        impl_->volume.store(volume);
        impl_->muted.store(muted);
    }
    stop();
    if (track.empty()) return;
    {
        std::lock_guard<std::mutex> lock(impl_->mutex);
        impl_->current = track;
    }
#ifdef TORCHLIGHT_HAVE_MUSIC
    impl_->running.store(true);
    impl_->worker = std::thread([impl = impl_.get()] {
        const std::string path = impl->directory + "/" + impl->track;
        OggVorbis_File vorbis{};
        if (ov_fopen(path.c_str(), &vorbis) != 0) {
            impl->running.store(false);
            return;
        }
        const vorbis_info *info = ov_info(&vorbis, -1);
        unsigned rate = 44100U;
        int channels = 2;
        if (info != nullptr) {
            if (info->rate > 0) rate = static_cast<unsigned>(info->rate);
            channels = info->channels;
        }
#if defined(__linux__)
        snd_pcm_t *pcm = nullptr;
        if (!impl->muted.load() &&
            snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) == 0) {
            snd_pcm_hw_params_t *params = nullptr;
            snd_pcm_hw_params_alloca(&params);
            snd_pcm_hw_params_any(pcm, params);
            snd_pcm_hw_params_set_access(pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED);
            snd_pcm_hw_params_set_format(pcm, params, SND_PCM_FORMAT_S16_LE);
            snd_pcm_hw_params_set_channels(pcm, params, 2);
            snd_pcm_hw_params_set_rate_near(pcm, params, &rate, nullptr);
            if (snd_pcm_hw_params(pcm, params) != 0) {
                snd_pcm_close(pcm);
                pcm = nullptr;
            }
        }
#else
        void *pcm = nullptr;
#endif
        float **samples = nullptr;
        int bitstream = 0;
        long got = 0;
        std::int16_t frame[2] = {0, 0};
        while (!impl->stop_flag.load() &&
               (got = ov_read_float(&vorbis, &samples, 4096, &bitstream)) > 0) {
            // Single gain implementation: MusicPlayer::apply_gain (tested in
            // music_test) owns volume/mute semantics; the worker used to
            // duplicate it inline, leaving apply_gain without a caller.
            const float volume = impl->volume.load();
            const bool muted = impl->muted.load();
            for (long i = 0; i < got && !impl->stop_flag.load(); ++i) {
                const float left = samples[0][i];
                const float right = channels > 1 ? samples[1][i] : left;
                frame[0] = clamp_sample(MusicPlayer::apply_gain(left, volume, muted), 1.0F);
                frame[1] = clamp_sample(MusicPlayer::apply_gain(right, volume, muted), 1.0F);
#if defined(__linux__)
                if (pcm != nullptr) {
                    if (snd_pcm_writei(pcm, frame, 1) < 0)
                        snd_pcm_recover(pcm, -EPIPE, 0);
                }
#endif
            }
#if defined(__linux__)
            // Without a device the first decoded buffer already proves the
            // file streams; holding the thread for a full silent decode
            // wastes a core.
            if (pcm == nullptr) break;
#else
            static_cast<void>(frame);
            break;
#endif
        }
        ov_clear(&vorbis);
#if defined(__linux__)
        if (pcm != nullptr) {
            snd_pcm_drain(pcm);
            snd_pcm_close(pcm);
        }
#endif
        impl->running.store(false);
    });
#else
    static_cast<void>(music_directory);
    impl_->running.store(false);
#endif
}
} // namespace torchlight
