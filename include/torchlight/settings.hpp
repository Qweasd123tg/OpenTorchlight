#pragma once
#include <cstdint>
#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {
// resource-derived: original settings are UTF-16LE "KEY :value" lines in
// ~/.runicgames/Torchlight/{settings,local_settings}.txt (observed 52 + 79
// lines on a real install). We never touch those files; our copies live in
// $XDG_DATA_HOME/opentorchlight/. Unknown keys and malformed lines roundtrip
// untouched so a hand-edited file is never truncated by a load/save cycle.
class SettingsFile {
  public:
    static SettingsFile load(const std::filesystem::path &path);
    void save(const std::filesystem::path &path) const;
    [[nodiscard]] std::string get(const std::string &key,
                                  const std::string &fallback = {}) const;
    void set(const std::string &key, const std::string &value);
    [[nodiscard]] int get_int(const std::string &key, int fallback) const noexcept;
    [[nodiscard]] float get_float(const std::string &key, float fallback) const noexcept;
    void set_int(const std::string &key, int value);
    void set_float(const std::string &key, float value);

  private:
    // File order is preserved; malformed lines are kept verbatim at the end.
    std::vector<std::pair<std::string, std::string>> entries_;
    std::vector<std::string> passthrough_;
};
struct DisplaySettings {
    int res_width = 1280, res_height = 720;
    int window_width = 800, window_height = 600;
    bool fullscreen = false; // current port UX; original default file says 1.
    bool vsync = true;       // current port behavior (eglSwapInterval 1).
    int fsaa = 0;
    bool render_behind = true;
    bool hardware_skinning = false;
    bool shadows_enabled = false;
    int shadows_detail = 1;
    bool rimlights = true;
    int max_particles = 5000;
    bool show_tips = true, show_blood = true, floaty_numbers = true;
    bool netbook_mode = false;
    bool sound_mute = false, music_mute = false;
    // original-code: KSETTINGS_F_MUSICVOLUME / F_SOUNDVOLUME exist as float
    // keys (symbols); no observed file values, slider write-back open.
    float music_volume = 1.0F, sound_volume = 1.0F;
};
[[nodiscard]] DisplaySettings load_display_settings(const std::filesystem::path &directory);
void store_display_settings(const std::filesystem::path &directory,
                            const DisplaySettings &settings);
[[nodiscard]] std::filesystem::path settings_directory();
} // namespace torchlight
