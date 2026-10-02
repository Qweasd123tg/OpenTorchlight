#include "torchlight/pak_archive.hpp"
#include "torchlight/panel_open.hpp"
#include "torchlight/ui_sound.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
void put16(std::vector<std::uint8_t>& bytes, std::uint16_t value) {
    bytes.push_back(static_cast<std::uint8_t>(value));
    bytes.push_back(static_cast<std::uint8_t>(value >> 8U));
}
void put32(std::vector<std::uint8_t>& bytes, std::uint32_t value) {
    put16(bytes, static_cast<std::uint16_t>(value));
    put16(bytes, static_cast<std::uint16_t>(value >> 16U));
}
std::vector<std::uint8_t> wav() {
    std::vector<std::uint8_t> result;
    const auto tag = [&](const char* text) {
        result.insert(result.end(), text, text + 4);
    };
    tag("RIFF"); put32(result, 40); tag("WAVE");
    tag("fmt "); put32(result, 16); put16(result, 1); put16(result, 1);
    put32(result, 44100); put32(result, 88200); put16(result, 2); put16(result, 16);
    tag("data"); put32(result, 4); put16(result, 16384); put16(result, 32767);
    return result;
}
} // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 1 || argc == 2, "usage: ui_sound_test [original-pak.zip]");
        const auto decoded = torchlight::UiSoundPlayer::decode_pcm16_wav(wav());
        require(decoded.sample_rate == 44100U && decoded.channels == 1U &&
                    decoded.samples.size() == 2U && decoded.samples[0] == 16384 &&
                    decoded.samples[1] == 32767,
                "bounded PCM16 WAV decoder changed");

        torchlight::VolatileRandom random(0x12345678U);
        const auto gain = torchlight::UiSoundPlayer::channel_gain(0.2F, 0.2F, random);
        require(gain >= 0.2F && gain < 0.4F && random.state() != 0x12345678U,
                "original additive [volume,volume+variation) gain changed");
        torchlight::VolatileRandom capped_random(7U);
        require(torchlight::UiSoundPlayer::channel_gain(0.9F, 0.2F, capped_random) <= 1.0F,
                "channel gain lost original min(result,1) cap");

        auto sound = decoded;
        std::vector<torchlight::UiSoundVoice> voices{{&sound, 0U, 1.0F}};
        auto mixed = torchlight::UiSoundPlayer::mix(voices, 2U, 0.5F, false);
        require(mixed.size() == 4U && mixed[0] == 8192 && mixed[1] == 8192 &&
                    mixed[2] == 16383 && mixed[3] == 16383 && voices.empty(),
                "mono one-shot mix/group gain or completion changed");
        voices.push_back({&sound, 0U, 1.0F});
        mixed = torchlight::UiSoundPlayer::mix(voices, 1U, 1.0F, true);
        require(mixed[0] == 0 && mixed[1] == 0,
                "sound group mute did not silence an active voice");

        // Different source/output rates must retain duration and stereo order.
        sound.sample_rate = 48000; sound.channels = 2;
        sound.samples = {1000,-1000,2000,-2000,3000,-3000,4000,-4000};
        voices = {{&sound,0U,1.0F}};
        mixed = torchlight::UiSoundPlayer::mix(voices,2U,1.0F,false,24000);
        require(mixed == std::vector<std::int16_t>({1000,-1000,3000,-3000}) && voices.empty(),
                "48 kHz PCM played at output frame rate instead of source rate");
        sound.sample_rate = 24000; sound.samples = {1000,-1000,3000,-3000};
        voices = {{&sound,0U,1.0F}};
        mixed = torchlight::UiSoundPlayer::mix(voices,4U,1.0F,false,48000);
        require(mixed == std::vector<std::int16_t>({1000,-1000,2000,-2000,3000,-3000,3000,-3000}) && voices.empty(),
                "portable PCM interpolation changed duration or channels");

        using Bank = torchlight::UiPanelSoundBank;
        using Cue = torchlight::UiSoundRequest;
        const std::array<std::pair<Bank,const torchlight::PanelProfile*>,4> panels{{
            {Bank::inventory,&torchlight::panel_profile_inventory()},
            {Bank::quest,&torchlight::panel_profile_quest()},
            {Bank::skill,&torchlight::panel_profile_skill()},
            {Bank::merchant,&torchlight::panel_profile_merchant()}}};
        for (const auto& [bank,profile] : panels) {
            torchlight::PanelOpenState panel(*profile);
            require(!torchlight::ui_panel_sound_request(bank,panel.set_open(false,false).sound_sample),
                    "closed panel emitted an audio cue");
            require(torchlight::ui_panel_sound_request(bank,panel.set_open(true,false).sound_sample) ==
                    (bank == Bank::merchant ? Cue::stats_open : Cue::inventory_open),
                    "bank-local opening ID resolved to the wrong resource");
            require(!torchlight::ui_panel_sound_request(bank,panel.set_open(true,false).sound_sample),
                    "same-state panel replayed opening audio");
            const auto close_cue = torchlight::ui_panel_sound_request(bank,panel.set_open(false,false).sound_sample);
            require(close_cue == (bank == Bank::merchant ? Cue::stats_close : Cue::inventory_close),
                    "bank-local closing ID resolved to the wrong resource");
            require(!torchlight::ui_panel_sound_request(bank,999),"unknown bank slot guessed an audio cue");
        }

        if (argc == 1) {
            std::cout << "PASS: PCM16 decode, additive gain, mute and mixer completion\n";
            return 0;
        }
        const torchlight::PakArchive archive(argv[1]);
        // Constructor parses resources and starts no output thread/device.
        torchlight::UiSoundPlayer player(archive);
        const auto& open = player.sound(torchlight::DropdownSoundRequest::open);
        const auto& close = player.sound(torchlight::DropdownSoundRequest::close);
        require(open.sample_rate == 44100U && open.channels == 1U &&
                    open.samples.size() == 30622U && close.sample_rate == 44100U &&
                    close.channels == 1U && close.samples.size() == 27986U,
                "CenterOpen/CenterClose WAV resources changed");
        require(std::abs(open.volume - 0.2F) < 0.000001F &&
                    std::abs(open.volume_variation - 0.2F) < 0.000001F &&
                    std::abs(close.volume - 0.2F) < 0.000001F &&
                    std::abs(close.volume_variation - 0.2F) < 0.000001F,
                "UI.DAT channel gain parameters changed");
        const auto& inventory_open = player.sound(Cue::inventory_open);
        const auto& inventory_close = player.sound(Cue::inventory_close);
        const auto& stats_open = player.sound(Cue::stats_open);
        const auto& stats_close = player.sound(Cue::stats_close);
        require(inventory_open.sample_rate == 44100 && inventory_open.channels == 2 && inventory_open.samples.size() == 55272 &&
                inventory_close.sample_rate == 48000 && inventory_close.channels == 2 && inventory_close.samples.size() == 43520 &&
                stats_open.sample_rate == 44100 && stats_open.channels == 2 && stats_open.samples.size() == 55272 &&
                stats_close.sample_rate == 44100 && stats_close.channels == 2 && stats_close.samples.size() == 47808,
                "panel sound resource PCM/rate/channel identity changed");
        voices = {{&inventory_close,0U,1.0F}};
        mixed = torchlight::UiSoundPlayer::mix(voices,19992U,1.0F,false);
        require(voices.empty() && mixed.size() == 39984U,"original 48 kHz close sound duration changed at 44.1 kHz output");
        player.stop();
        std::cout << "PASS: UI.DAT mapping, PCM16 decode, original additive gain and bounded mixer\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
