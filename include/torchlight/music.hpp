#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace torchlight {
// Music track mapping. Statuses: TITLE on menus and TOWN in town follow the
// observed file names for those exact screens (inferred, not traced);
// per-theme files (MINES/CRYPT/...) are inferred from UPPER(theme) convention
// seen in CGameClient::loadLevel (StringUpper before playMusic); boss and
// combat tracks stay open (boss states are open too).
[[nodiscard]] std::string music_track_for_menu();
[[nodiscard]] std::string music_track_for_dungeon(const std::string &dungeon_name,
                                                 const std::string &theme);
// Background OGG streamer (vorbisfile -> ALSA). Volume is linear gain from
// settings (curve open); fades are linear over the requested seconds
// (original fade shape open). Thread-safe.
class MusicPlayer {
  public:
    MusicPlayer();
    ~MusicPlayer();
    MusicPlayer(const MusicPlayer &) = delete;
    MusicPlayer &operator=(const MusicPlayer &) = delete;
    // Requests a track from the game music directory (e.g. "TOWN.OGG").
    // Empty request stops. Switching stops the current track first, like the
    // original stopMusic/playMusic sequence (no crossfade in evidence).
    void request(const std::string &music_directory, const std::string &track,
                 float volume, bool muted);
    void stop();
    // Live level change without restarting the track (Apply in settings).
    void set_levels(float volume, bool muted);
    [[nodiscard]] std::string current() const;
    // Test hooks (no audio device needed).
    [[nodiscard]] static float apply_gain(float sample, float volume, bool muted);
    [[nodiscard]] static std::vector<std::int16_t> mix_frame(float left, float right,
                                                             float gain);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace torchlight
