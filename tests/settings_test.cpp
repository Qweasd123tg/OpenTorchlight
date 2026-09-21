#include "torchlight/settings.hpp"
#include <cstdio>
#include <filesystem>
#include <fstream>
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
        // resource-derived: observed original local_settings.txt Spiderweb
        // ("FULLSCREEN :1", "RES_WIDTH :1280", "X_RATIO :1.250000", ...).
        const std::filesystem::path dir =
            std::filesystem::temp_directory_path() / "ot-settings-probe";
        std::error_code ec;
        std::filesystem::remove_all(dir, ec);
        // Absent files yield portable defaults, never an error.
        const auto fresh = load_display_settings(dir);
        require(fresh.res_width == 1280 && fresh.res_height == 720, "default res wrong");
        require(!fresh.fullscreen && fresh.vsync, "default window policy wrong");
        require(!fresh.shadows_enabled && fresh.rimlights, "default render flags wrong");
        // Roundtrip preserves known keys, unknown keys and malformed lines.
        {
            SettingsFile file;
            file.set("RES_WIDTH", "800");
            file.set("CUSTOM FUTURE KEY", "7");
            file.save(dir / "local_settings.txt");
            // Append garbage the parser must carry through untouched.
            std::ofstream raw(dir / "local_settings.txt", std::ios::binary | std::ios::app);
            raw << "MALFORMED LINE WITHOUT COLON\n";
            raw.close();
        }
        DisplaySettings changed;
        changed.res_width = 800;
        changed.res_height = 600;
        changed.fullscreen = true;
        changed.vsync = false;
        changed.shadows_enabled = true;
        changed.music_mute = true;
        changed.lighting_enabled = false;
        changed.shadow_resolution = 512;
        changed.particle_fps = 40.0F;
        changed.particle_percent = 100.0F;
        store_display_settings(dir, changed);
        const auto back = load_display_settings(dir);
        require(back.res_width == 800 && back.res_height == 600, "res roundtrip wrong");
        require(back.fullscreen && !back.vsync, "flags roundtrip wrong");
        require(back.shadows_enabled && back.music_mute, "render/audio roundtrip wrong");
        require(!back.lighting_enabled && back.shadow_resolution == 512 &&
                    back.particle_fps == 40.0F && back.particle_percent == 100.0F &&
                    back.max_particles == 5000, "settings combo fields did not roundtrip independently");
        const auto raw = SettingsFile::load(dir / "local_settings.txt");
        require(raw.get("LIGHTING_ENABLED") == "0" && raw.get("SHADOWRESOLUTION") == "512" &&
                    raw.get_float("PARTICLEFPS", 0) == 40.0F &&
                    raw.get_float("PARTICLE_EMIT_PCT", 0) == 100.0F,
                "settings combo source keys differ");
        require(raw.get("CUSTOM FUTURE KEY") == "7", "unknown key dropped");
        require(raw.get("X_RATIO") == "0.781250", "derived X_RATIO wrong");
        require(raw.get("Y_RATIO") == "0.781250", "derived Y_RATIO wrong");
        // Malformed/typeless access never throws and keeps fallbacks.
        require(raw.get_int("CUSTOM FUTURE KEY", 0) == 7, "int accessor wrong");
        require(raw.get_int("MISSING", 42) == 42, "int fallback wrong");
        require(raw.get_float("X_RATIO", 0) > 0.78F && raw.get_float("X_RATIO", 0) < 0.79F,
                "float accessor wrong");
        require(raw.get_float("MISSING", 1.5F) == 1.5F, "float fallback wrong");
        // Observed original file parses with its real keys intact.
        require(raw.get("FULLSCREEN") == "1", "original key lost");
        std::filesystem::remove_all(dir, ec);
        std::cout << "settings: " << checks
                  << " assertions; authored files plus observed original key names\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
