#pragma once
#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_font.hpp"
#include <map>
#include <array>
#include <optional>

namespace torchlight {
// Bounded subset of original CEGUI XML; not a replacement for the full skin engine.
struct UiRect {
    float x = 0, y = 0, width = 0, height = 0;
    [[nodiscard]] bool contains(float px, float py) const noexcept {
        return width > 0 && height > 0 && px >= x && py >= y && px < x + width && py < y + height;
    }
};
struct UiWidget {
    std::string name, type;
    std::int32_t parent = -1;
    std::map<std::string, std::string> properties;
    [[nodiscard]] std::string property(const std::string &key) const;
};
enum class UiTextHorizontal { left, centre, right };
enum class UiTextVertical { top, centre, bottom };
struct UiTextStyle {
    UiTextHorizontal horizontal = UiTextHorizontal::left;
    UiTextVertical vertical = UiTextVertical::top;
    bool wrap = false;
};
struct UiResolvedWidget {
    std::string name, type, text, callback, image, font;
    UiRect rect;
    bool visible = true, enabled = true;
    std::int32_t parent = -1;
    UiRect clip;
    std::map<std::string, std::string> properties;
    [[nodiscard]] std::string property(const std::string &key) const;
    [[nodiscard]] UiTextStyle text_style() const;
};
class UiLayout {
  public:
    [[nodiscard]] static UiLayout parse(const std::vector<std::uint8_t> &bytes);
    [[nodiscard]] std::vector<UiResolvedWidget> resolve(int width, int height) const;
    [[nodiscard]] const std::vector<UiWidget> &widgets() const noexcept {
        return widgets_;
    }

  private:
    std::vector<UiWidget> widgets_;
};
struct UiImage {
    std::string texture_path;
    float x = 0, y = 0, width = 0, height = 0;
};
// Bounded GuiLook.looknfeel extraction for widget types this renderer draws.
struct UiWidgetImages {
    std::string normal, hover, pushed, disabled;
};
class UiResources {
  public:
    explicit UiResources(const PakArchive &archive) : archive_(&archive) {
    }
    [[nodiscard]] const UiLayout *layout(const std::string &path);
    [[nodiscard]] std::optional<UiImage> image(const std::string &reference);
    // Case-insensitive lookup by the original CEGUI <Font Name=...>. The
    // returned cache is mutated by rasterization; callers own the screen size.
    [[nodiscard]] UiFont *font(const std::string &name);
    // WidgetLook PropertyDefinition initialValue from media/UI/GuiLook.looknfeel.
    [[nodiscard]] std::optional<UiWidgetImages> widget_images(const std::string &type);
    [[nodiscard]] const std::vector<std::string> &diagnostics() const noexcept {
        return diagnostics_;
    }

  private:
    const PakArchive *archive_;
    std::map<std::string, UiLayout> layouts_;
    std::map<std::string, UiImage> images_;
    std::map<std::string, UiFont> fonts_;
    std::map<std::string, UiWidgetImages> widget_images_;
    std::vector<std::string> diagnostics_;
    bool images_loaded_ = false, fonts_loaded_ = false, looknfeel_loaded_ = false;
};
} // namespace torchlight
