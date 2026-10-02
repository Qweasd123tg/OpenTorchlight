#include "torchlight/ui_screen_scale.hpp"
#include "torchlight/generated/ui_state_queries.hpp"
#include <cmath>
#include <cstring>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr float kBaseHeight = 768.0F;
constexpr float kBaseWidth = 1024.0F;
constexpr std::uint64_t ui = 0x10000, properties = 0x30000, float_array = 0x40000;
constexpr std::uint64_t stack_base = 0x20000, stack_entry = stack_base + 0x80;
constexpr std::uint64_t return_sentinel = 0x7ff00000;
class FloatPropertyMemory final : public pcode::Memory {
    const float* values_;
    std::size_t count_;
    pcode::ByteState<0x100> stack_;
public:
    FloatPropertyMemory(const float* values, std::size_t count) : values_(values), count_(count) {
        stack_.write(stack_entry - stack_base, 8, return_sentinel);
    }
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address >= stack_base && address < stack_base + 0x100)
            return stack_.read(static_cast<std::size_t>(address - stack_base), width,
                               "UI scale read of uninitialized private stack");
        if (address == ui + 0x78 && width == 8) return properties;
        if (address == properties + 0x58 && width == 8) return float_array;
        if (address == properties + 0x60 && width == 8)
            return float_array + static_cast<std::uint64_t>(count_) * 4;
        // An evaluated named YRATIO view has one populated property slot.
        // This is an adapter index, not an original global key-ID assertion.
        if (address == 0x150b470 && width == 4) return 0;
        if (address == 0xfa8760 && width == 4) return UINT32_C(0xbf800000);
        if (width == 4 && address >= float_array && (address - float_array) % 4 == 0) {
            const auto index = (address - float_array) / 4;
            if (index < count_ && values_) {
                std::uint32_t bits = 0;
                std::memcpy(&bits, &values_[index], sizeof(bits));
                return bits;
            }
        }
        throw std::logic_error("UI float property read outside reviewed binding");
    }
    void write(std::uint64_t address, std::size_t width, std::uint64_t value) override {
        if (address >= stack_base && address < stack_base + 0x100) {
            stack_.write(static_cast<std::size_t>(address - stack_base), width, value);
            return;
        }
        throw std::logic_error("UI float query attempted a non-stack write");
    }
};
float result_float(std::uint64_t bits) {
    const auto scalar = static_cast<std::uint32_t>(bits);
    float value = 0;
    std::memcpy(&value, &scalar, sizeof(value));
    return value;
}
} // namespace

float ui_float_property(const float* values, std::size_t count, std::uint32_t index) {
    FloatPropertyMemory memory(values, count);
    pcode::RegisterFile registers;
    registers.write(0x38, 8, properties);
    registers.write(0x20, 8, stack_entry);
    registers.write(0x30, 4, index);
    return result_float(pcode_generated::fn_00c6e410(memory, registers, return_sentinel));
}

float ui_scale_offset(float offset, float ratio) {
    FloatPropertyMemory memory(&ratio, 1);
    pcode::RegisterFile registers;
    registers.write(0x38, 8, ui);
    registers.write(0x20, 8, stack_entry);
    std::uint32_t bits = 0;
    std::memcpy(&bits, &offset, sizeof(bits));
    registers.write(0x1200, 4, bits);
    return result_float(pcode_generated::fn_00a83e70(memory, registers, return_sentinel));
}

float ui_screen_ratio(int width, int height, UiScreenScaleRatio which) {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("invalid UI viewport");
    const float value = which == UiScreenScaleRatio::x_ratio
        ? static_cast<float>(width) / kBaseWidth
        : static_cast<float>(height) / kBaseHeight;
    if (!std::isfinite(value))
        throw std::invalid_argument("non-finite screen ratio");
    return value;
}

void ui_scale_area_offsets(std::array<float, 8> &area, float ratio) {
    // original-code: convertToScreenScale scales only the two UDim offsets of
    // getPosition() and then only the two UDim offsets of getSize().
    for (const std::size_t i : {1U, 3U, 5U, 7U})
        area[i] = ui_scale_offset(area[i], ratio);
}

void ui_scale_vector_offsets(std::array<float, 4> &vector, float ratio) {
    vector[1] = ui_scale_offset(vector[1], ratio);
    vector[3] = ui_scale_offset(vector[3], ratio);
}

std::optional<UiScreenScaleRatio> ui_screen_scale_for_layout(const std::string &layout_path) {
    // All confirmed call sites pass `false`, i.e. YRATIO for both axes.
    // HUD/game stage: CGameUI::create call @0xaa07dc (checked against the
    // decompiled game_ui.c:9464 chain). Controller menus, each verified in
    // the shipped ELF by xor-edx + call convertToScreenScale in its
    // createMenus: CMainMenu @0xc52bd5, CNewGameMenu @0xc5d8f5,
    // CContinueGameMenu @0xc4067d, COptionsMenu @0xb881ad,
    // CSettingsMenu @0xbd705d. The menu->layout pairing (MainMenu/
    // mainmenuframe etc.) is resource-derived from layout contents and the
    // port's page mapping; layouts absent here (e.g. loading) have unknown
    // policy: no scaling is applied for them rather than an invented one.
    const auto leaf = layout_path.substr(layout_path.find_last_of('/') + 1);
    for (const char *name : {"bottomhud.layout", "pethud.layout", "inventorymenu.layout",
                             "merchantmenu.layout", "petmenu.layout", "journalmenu.layout",
                             "questmenu.layout", "stashmenu.layout", "enchantmenu.layout",
                             "combinemenu.layout", "mainmenuframe.layout",
                             "charactercreate.layout", "characterload.layout",
                             "optionsmenu.layout", "settingsmenu.layout"})
        if (leaf == name)
            return UiScreenScaleRatio::y_ratio;
    return std::nullopt;
}
} // namespace torchlight
