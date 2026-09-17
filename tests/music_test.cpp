#include "torchlight/music.hpp"
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool ok, const char *message) {
    ++checks;
    if (!ok) throw std::runtime_error(message);
}
} // namespace
int main() {
    try {
        // Track mapping statuses are documented in music.hpp.
        require(music_track_for_menu() == "TITLE.OGG", "menu track wrong");
        require(music_track_for_dungeon("Town", "") == "TOWN.OGG", "town track wrong");
        require(music_track_for_dungeon("town", "") == "TOWN.OGG", "town case wrong");
        require(music_track_for_dungeon("Main", "mine") == "MINE.OGG", "theme track wrong");
        require(music_track_for_dungeon("Main", "") == "TOWN.OGG", "theme fallback wrong");
        // Gain math: mute silences, out-of-range clamps, NaN is contained.
        require(MusicPlayer::apply_gain(0.5F, 1.0F, false) == 0.5F, "unity gain wrong");
        require(MusicPlayer::apply_gain(0.5F, 1.0F, true) == 0.0F, "mute wrong");
        require(MusicPlayer::apply_gain(0.5F, 2.0F, false) == 0.5F, "gain clamp wrong");
        require(MusicPlayer::apply_gain(0.5F, -1.0F, false) == 0.0F, "gain floor wrong");
        // Mixer clamps to int16 without wrapping.
        const auto loud = MusicPlayer::mix_frame(2.0F, -2.0F, 1.0F);
        require(loud.size() == 2 && loud[0] == 32767 && loud[1] == -32768,
                "mixer clamp wrong");
        const auto silent = MusicPlayer::mix_frame(0.5F, 0.25F, 0.0F);
        require(silent[0] == 0 && silent[1] == 0, "mixer silence wrong");
        // Player state machine needs no audio device for these paths.
        MusicPlayer player;
        require(player.current().empty(), "fresh player claims a track");
        player.request("", "", 1.0F, false);
        require(player.current().empty(), "empty request set a track");
        player.request("/nonexistent-music-dir", "MISSING.OGG", 0.5F, true);
        require(player.current() == "MISSING.OGG", "request not recorded");
        player.stop();
        require(player.current().empty(), "stop did not clear the track");
        std::cout << "music: " << checks
                  << " assertions; mapping/volume/mixer/state without audio hardware\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
