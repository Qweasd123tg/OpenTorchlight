#include "torchlight/settings.hpp"
#include <charconv>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdexcept>

namespace torchlight {
namespace {
std::string narrow_lossy(const std::u16string &value) {
    std::string out;
    out.reserve(value.size());
    for (const auto c : value)
        out.push_back(c < 0x80 ? static_cast<char>(c) : '?');
    return out;
}
std::u16string widen_ascii(const std::string &value) {
    std::u16string out;
    out.reserve(value.size());
    for (const auto c : value)
        out.push_back(static_cast<unsigned char>(c) < 0x80 ? static_cast<char16_t>(c) : u'?');
    return out;
}
bool parse_int(const std::string &value, int &out) noexcept {
    const auto parsed =
        std::from_chars(value.data(), value.data() + value.size(), out);
    return parsed.ec == std::errc{} && parsed.ptr == value.data() + value.size();
}
bool parse_float(const std::string &value, float &out) noexcept {
    const auto parsed =
        std::from_chars(value.data(), value.data() + value.size(), out);
    return parsed.ec == std::errc{} && parsed.ptr == value.data() + value.size() &&
           std::isfinite(out);
}
std::string trim(const std::string &value) {
    std::size_t first = 0, last = value.size();
    while (first < last && (value[first] == ' ' || value[first] == '\t' || value[first] == '\r'))
        ++first;
    while (last > first &&
           (value[last - 1] == ' ' || value[last - 1] == '\t' || value[last - 1] == '\r'))
        --last;
    return value.substr(first, last - first);
}
} // namespace
SettingsFile SettingsFile::load(const std::filesystem::path &path) {
    SettingsFile file;
    std::ifstream in(path, std::ios::binary);
    if (!in)
        return file;
    const std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                          std::istreambuf_iterator<char>());
    std::u16string text;
    if (bytes.size() >= 2 && bytes[0] == 0xff && bytes[1] == 0xfe) {
        // A trailing orphan byte is ignored: settings must degrade to
        // defaults, never fail the whole file on one stray byte.
        const auto words = (bytes.size() - 2) / 2;
        for (std::size_t i = 0; i < words; ++i)
            text.push_back(static_cast<char16_t>(bytes[2 + i * 2] | (bytes[2 + i * 2 + 1] << 8)));
    } else {
        for (const auto b : bytes)
            text.push_back(static_cast<char16_t>(b));
    }
    std::size_t start = 0;
    while (start <= text.size()) {
        auto end = text.find(u'\n', start);
        if (end == std::u16string::npos) end = text.size();
        auto line = narrow_lossy(text.substr(start, end - start));
        start = end + 1;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (trim(line).empty()) continue;
        // Observed separator is " :" (space before colon); accept plain colon too.
        const auto colon = line.find(':');
        if (colon == std::string::npos) {
            file.passthrough_.push_back(line);
            continue;
        }
        const auto key = trim(line.substr(0, colon));
        const auto value = trim(line.substr(colon + 1));
        if (key.empty()) {
            file.passthrough_.push_back(line);
            continue;
        }
        bool duplicate = false;
        for (auto &entry : file.entries_)
            if (entry.first == key) {
                entry.second = value; // LAST wins, like the layout parser.
                duplicate = true;
                break;
            }
        if (!duplicate) file.entries_.emplace_back(key, value);
    }
    return file;
}
void SettingsFile::save(const std::filesystem::path &path) const {
    std::u16string text;
    for (const auto &entry : entries_) {
        text += widen_ascii(entry.first);
        text += u" :";
        text += widen_ascii(entry.second);
        text += u'\n';
    }
    for (const auto &line : passthrough_) {
        text += widen_ascii(line);
        text += u'\n';
    }
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    const auto tmp = path.string() + ".tmp";
    {
        std::ofstream out(tmp, std::ios::binary | std::ios::trunc);
        if (!out) throw std::runtime_error("cannot write settings file");
        out.put(static_cast<char>(0xff));
        out.put(static_cast<char>(0xfe));
        for (const auto c : text) {
            out.put(static_cast<char>(c & 0xff));
            out.put(static_cast<char>((c >> 8) & 0xff));
        }
        out.flush();
        if (!out) throw std::runtime_error("cannot write settings file");
    }
    std::filesystem::rename(tmp, path, ec);
    if (ec) throw std::runtime_error("cannot replace settings file");
}
std::string SettingsFile::get(const std::string &key, const std::string &fallback) const {
    for (const auto &entry : entries_)
        if (entry.first == key) return entry.second;
    return fallback;
}
void SettingsFile::set(const std::string &key, const std::string &value) {
    for (auto &entry : entries_)
        if (entry.first == key) {
            entry.second = value;
            return;
        }
    entries_.emplace_back(key, value);
}
int SettingsFile::get_int(const std::string &key, int fallback) const noexcept {
    int value = 0;
    return parse_int(get(key), value) ? value : fallback;
}
float SettingsFile::get_float(const std::string &key, float fallback) const noexcept {
    float value = 0;
    return parse_float(get(key), value) ? value : fallback;
}
void SettingsFile::set_int(const std::string &key, int value) {
    set(key, std::to_string(value));
}
void SettingsFile::set_float(const std::string &key, float value) {
    char buffer[32]{};
    const auto parsed =
        std::to_chars(buffer, buffer + sizeof(buffer), value, std::chars_format::fixed, 6);
    set(key, std::string(buffer, parsed.ptr));
}
std::filesystem::path settings_directory() {
    if (const char *x = std::getenv("XDG_DATA_HOME");
        x && *x && std::filesystem::path(x).is_absolute())
        return std::filesystem::path(x) / "opentorchlight";
    if (const char *h = std::getenv("HOME"); h && *h && std::filesystem::path(h).is_absolute())
        return std::filesystem::path(h) / ".local" / "share" / "opentorchlight";
    throw std::runtime_error("set HOME or XDG_DATA_HOME for settings");
}
DisplaySettings load_display_settings(const std::filesystem::path &directory) {
    const auto file =
        SettingsFile::load(directory / "local_settings.txt");
    DisplaySettings settings;
    settings.res_width = file.get_int("RES_WIDTH", settings.res_width);
    settings.res_height = file.get_int("RES_HEIGHT", settings.res_height);
    settings.window_width = file.get_int("WINDOW_WIDTH", settings.window_width);
    settings.window_height = file.get_int("WINDOW_HEIGHT", settings.window_height);
    settings.fullscreen = file.get_int("FULLSCREEN", settings.fullscreen ? 1 : 0) != 0;
    settings.vsync = file.get_int("VSYNCH", settings.vsync ? 1 : 0) != 0;
    settings.fsaa = file.get_int("FSAA", settings.fsaa);
    settings.render_behind = file.get_int("RENDERBEHIND", 1) != 0;
    settings.hardware_skinning = file.get_int("ALLOW HWSKINNING", 0) != 0;
    settings.shadows_enabled = file.get_int("SHADOWS_ENABLED", 0) != 0;
    settings.shadows_detail = file.get_int("SHADOWS_DETAIL", settings.shadows_detail);
    settings.rimlights = file.get_int("RIMLIGHTS_ENABLED", 1) != 0;
    settings.max_particles = file.get_int("MAX_PARTICLES", settings.max_particles);
    settings.lighting_enabled = file.get_int("LIGHTING_ENABLED", 1) != 0;
    settings.shadow_resolution = file.get_int("SHADOWRESOLUTION", settings.shadow_resolution);
    settings.particle_fps = file.get_float("PARTICLEFPS", settings.particle_fps);
    settings.particle_percent = file.get_float("PARTICLE_EMIT_PCT", settings.particle_percent);
    settings.show_tips = file.get_int("SHOW TIPS", 1) != 0;
    settings.show_blood = file.get_int("SHOW BLOOD", 1) != 0;
    settings.floaty_numbers = file.get_int("FLOATY_NUMBERS", 1) != 0;
    settings.netbook_mode = file.get_int("NETBOOK MODE", 0) != 0;
    settings.sound_mute = file.get_int("SOUND MUTE", 0) != 0;
    settings.music_mute = file.get_int("MUSIC MUTE", 0) != 0;
    settings.music_volume = file.get_float("F_MUSICVOLUME", 1.0F);
    settings.sound_volume = file.get_float("F_SOUNDVOLUME", 1.0F);
    if (!(settings.music_volume >= 0.0F) || !(settings.music_volume <= 1.0F))
        settings.music_volume = 1.0F;
    if (!(settings.sound_volume >= 0.0F) || !(settings.sound_volume <= 1.0F))
        settings.sound_volume = 1.0F;
    if (settings.res_width <= 0 || settings.res_height <= 0 ||
        settings.res_width > 7680 || settings.res_height > 4320) {
        settings.res_width = 1280;
        settings.res_height = 720;
    }
    return settings;
}
void store_display_settings(const std::filesystem::path &directory,
                            const DisplaySettings &settings) {
    auto file = SettingsFile::load(directory / "local_settings.txt");
    file.set_int("RES_WIDTH", settings.res_width);
    file.set_int("RES_HEIGHT", settings.res_height);
    file.set_int("WINDOW_WIDTH", settings.window_width);
    file.set_int("WINDOW_HEIGHT", settings.window_height);
    file.set_int("FULLSCREEN", settings.fullscreen ? 1 : 0);
    file.set_int("VSYNCH", settings.vsync ? 1 : 0);
    file.set_int("FSAA", settings.fsaa);
    file.set_int("RENDERBEHIND", settings.render_behind ? 1 : 0);
    file.set_int("ALLOW HWSKINNING", settings.hardware_skinning ? 1 : 0);
    file.set_int("SHADOWS_ENABLED", settings.shadows_enabled ? 1 : 0);
    file.set_int("SHADOWS_DETAIL", settings.shadows_detail);
    file.set_int("RIMLIGHTS_ENABLED", settings.rimlights ? 1 : 0);
    file.set_int("MAX_PARTICLES", settings.max_particles);
    file.set_int("LIGHTING_ENABLED", settings.lighting_enabled ? 1 : 0);
    file.set_int("SHADOWRESOLUTION", settings.shadow_resolution);
    file.set_float("PARTICLEFPS", settings.particle_fps);
    file.set_float("PARTICLE_EMIT_PCT", settings.particle_percent);
    file.set_int("SHOW TIPS", settings.show_tips ? 1 : 0);
    file.set_int("SHOW BLOOD", settings.show_blood ? 1 : 0);
    file.set_int("FLOATY_NUMBERS", settings.floaty_numbers ? 1 : 0);
    file.set_int("NETBOOK MODE", settings.netbook_mode ? 1 : 0);
    file.set_int("SOUND MUTE", settings.sound_mute ? 1 : 0);
    file.set_int("MUSIC MUTE", settings.music_mute ? 1 : 0);
    file.set_float("F_MUSICVOLUME", settings.music_volume);
    file.set_float("F_SOUNDVOLUME", settings.sound_volume);
    // Observed derived values (RES/native): 1280/1024=1.25, 720/768=0.9375.
    char buffer[32]{};
    auto ratio = [&](float value) {
        const auto parsed = std::to_chars(buffer, buffer + sizeof(buffer), value,
                                          std::chars_format::fixed, 6);
        return std::string(buffer, parsed.ptr);
    };
    file.set("X_RATIO", ratio(static_cast<float>(settings.res_width) / 1024.0F));
    file.set("Y_RATIO", ratio(static_cast<float>(settings.res_height) / 768.0F));
    file.save(directory / "local_settings.txt");
}
} // namespace torchlight
