#include "torchlight/cegui_menu.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include "torchlight/ui_int_property.hpp"
#include "torchlight/ui_dropdown.hpp"
#include "torchlight/dds_texture.hpp"
#include "torchlight/png_texture.hpp"
#include <CEGUI.h>
#include <CEGUIExpatParser.h>
#include <FalModule.h>
#include <falagard/CEGUIFalWidgetLookManager.h>
#include <falagard/CEGUIFalWidgetLookFeel.h>
#include <falagard/CEGUIFalNamedArea.h>
#include <tuple>
#include <set>
#include "torchlight/application_keys.hpp"
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>

namespace torchlight {
namespace {
template<class Function> auto library_call(Function&& function) -> decltype(function()) {
    try { return function(); }
    catch (const CEGUI::Exception& error) {
        throw std::runtime_error("CEGUI: " + std::string(reinterpret_cast<const char*>(error.getMessage().c_str())));
    }
}
std::string string(const CEGUI::String& value) {
    return reinterpret_cast<const char*>(value.c_str());
}
CEGUI::String utf8(const std::string& value) {
    // CEGUI 0.6.2 std::string/char constructors are unencoded codepoints
    // 0..255. Resource/save UTF-8 must use the explicit utf8 constructor.
    return CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
}
UiRect rectangle(const CEGUI::Rect& value) {
    return {value.d_left, value.d_top, value.getWidth(), value.getHeight()};
}
std::array<float, 4> rgba(const CEGUI::colour& value) {
    return {value.getRed(), value.getGreen(), value.getBlue(), value.getAlpha()};
}
class ArchiveProvider final : public CEGUI::ResourceProvider {
  public:
    explicit ArchiveProvider(const PakArchive& archive) : archive_(archive) {}
    void loadRawDataContainer(const CEGUI::String& filename, CEGUI::RawDataContainer& output,
                              const CEGUI::String&) override {
        const auto bytes = archive_.read_normalized(string(filename));
        auto data = std::make_unique<CEGUI::uint8[]>(bytes.size());
        std::copy(bytes.begin(), bytes.end(), data.get());
        output.setData(data.release());
        output.setSize(bytes.size());
    }
    void unloadRawDataContainer(CEGUI::RawDataContainer& data) override {
        delete[] data.getDataPtr();
        data.setData(nullptr);
        data.setSize(0);
    }
  private:
    const PakArchive& archive_;
};
// System owns its Logger even when supplied by the application. No cwd log
// file; report genuine library errors through the application's stderr.
class LibraryLogger final : public CEGUI::Logger {
  public:
    void logEvent(const CEGUI::String& message, CEGUI::LoggingLevel level) override {
        if (level == CEGUI::Errors) std::cerr << "CEGUI: " << string(message) << '\n';
    }
    void setLogFilename(const CEGUI::String&, bool) override {}
};
class QuadRenderer;
class MemoryTexture final : public CEGUI::Texture {
  public:
    MemoryTexture(QuadRenderer&, const PakArchive&);
    CEGUI::ushort getWidth() const override { return static_cast<CEGUI::ushort>(data->width); }
    CEGUI::ushort getHeight() const override { return static_cast<CEGUI::ushort>(data->height); }
    void loadFromFile(const CEGUI::String& filename, const CEGUI::String&) override {
        const auto bytes = archive_.read_normalized(string(filename));
        if (bytes.size() >= 4 && std::memcmp(bytes.data(), "DDS ", 4) == 0) {
            const auto image = decode_dds(bytes);
            loadFromMemory(image.rgba.data(), image.width, image.height, PF_RGBA);
        } else {
            const auto image = decode_png(bytes);
            loadFromMemory(image.rgba.data(), image.width, image.height, PF_RGBA);
        }
    }
    void loadFromMemory(const void* pixels, CEGUI::uint width, CEGUI::uint height,
                        PixelFormat format) override {
        if (!width || !height || width > 4096 || height > 4096 || !pixels)
            throw std::runtime_error("invalid CEGUI texture dimensions");
        // Copy-on-write preserves textures referenced by already returned frames.
        if (!data.unique()) data = std::make_shared<CeguiTextureData>(*data);
        data->width = width;
        data->height = height;
        ++data->revision;
        const auto count = static_cast<std::size_t>(width) * height;
        const auto* input = static_cast<const std::uint8_t*>(pixels);
        data->rgba.resize(count * 4);
        if (format == PF_RGBA) std::copy(input, input + count * 4, data->rgba.begin());
        else for (std::size_t i = 0; i < count; ++i) {
            std::copy(input + i * 3, input + i * 3 + 3, data->rgba.begin() + i * 4);
            data->rgba[i * 4 + 3] = 255;
        }
    }
    std::shared_ptr<CeguiTextureData> data = std::make_shared<CeguiTextureData>();
  private:
    const PakArchive& archive_;
};
class QuadRenderer final : public CEGUI::Renderer {
  public:
    explicit QuadRenderer(const PakArchive& archive) : archive_(archive) {}
    ~QuadRenderer() override { destroyAllTextures(); }
    void addQuad(const CEGUI::Rect& destination, float z, const CEGUI::Texture* texture,
                 const CEGUI::Rect& uv, const CEGUI::ColourRect& colours,
                 CEGUI::QuadSplitMode split) override {
        const auto* memory = dynamic_cast<const MemoryTexture*>(texture);
        if (!memory) throw std::runtime_error("foreign CEGUI texture");
        auto& output = queueing_ ? queued_ : quads;
        output.push_back({rectangle(destination), rectangle(uv),
            {rgba(colours.d_top_left), rgba(colours.d_top_right),
             rgba(colours.d_bottom_left), rgba(colours.d_bottom_right)}, memory->data, z,
            split == CEGUI::BottomLeftToTopRight});
    }
    // renderGUI submits its persistent cache, then draws the mouse cursor with
    // queueing disabled. Immediate quads belong only to this submission.
    void doRender() override { quads = queued_; }
    void clearRenderList() override { queued_.clear(); }
    void setQueueingEnabled(bool value) override { queueing_ = value; }
    bool isQueueingEnabled() const override { return queueing_; }
    CEGUI::Texture* createTexture() override {
        textures_.push_back(std::make_unique<MemoryTexture>(*this, archive_));
        return textures_.back().get();
    }
    CEGUI::Texture* createTexture(const CEGUI::String& filename, const CEGUI::String& group) override {
        auto* texture = createTexture();
        try { texture->loadFromFile(filename, group); }
        catch (...) { destroyTexture(texture); throw; }
        return texture;
    }
    CEGUI::Texture* createTexture(float size) override {
        if (!std::isfinite(size) || size <= 0 || size > 4096)
            throw std::runtime_error("invalid CEGUI texture size");
        unsigned dimension = 1;
        while (dimension < size) dimension *= 2;
        std::vector<std::uint8_t> pixels(static_cast<std::size_t>(dimension) * dimension * 4);
        auto* texture = createTexture();
        try { texture->loadFromMemory(pixels.data(), dimension, dimension, CEGUI::Texture::PF_RGBA); }
        catch (...) { destroyTexture(texture); throw; }
        return texture;
    }
    void destroyTexture(CEGUI::Texture* texture) override {
        textures_.erase(std::remove_if(textures_.begin(), textures_.end(),
            [texture](const auto& item) { return item.get() == texture; }), textures_.end());
    }
    void destroyAllTextures() override { textures_.clear(); }
    float getWidth() const override { return width_; }
    float getHeight() const override { return height_; }
    CEGUI::Size getSize() const override { return {width_, height_}; }
    CEGUI::Rect getRect() const override { return {0, 0, width_, height_}; }
    CEGUI::uint getMaxTextureSize() const override { return 4096; }
    CEGUI::uint getHorzScreenDPI() const override { return 96; }
    CEGUI::uint getVertScreenDPI() const override { return 96; }
    void resize(int width, int height) {
        if (width <= 0 || height <= 0) throw std::invalid_argument("invalid CEGUI viewport");
        if (width_ == width && height_ == height) return;
        width_ = static_cast<float>(width);
        height_ = static_cast<float>(height);
        CEGUI::EventArgs args;
        fireEvent(EventDisplaySizeChanged, args, EventNamespace);
    }
    std::vector<CeguiQuad> quads;
  private:
    const PakArchive& archive_;
    float width_ = 1024, height_ = 768;
    std::vector<std::unique_ptr<MemoryTexture>> textures_;
    std::vector<CeguiQuad> queued_;
    bool queueing_ = true;
};
MemoryTexture::MemoryTexture(QuadRenderer& renderer, const PakArchive& archive)
    : CEGUI::Texture(&renderer), archive_(archive) {}

class FunctionTree final : public UiFunctionTree {
  public:
    std::vector<CEGUI::Window*> windows;
    std::map<CEGUI::Window*, UiLayoutFunction> functions;
    std::size_t child_count(Node node) const override { return windows.at(node)->getChildCount(); }
    Node child(Node node, std::size_t index) const override {
        const auto* window = windows.at(node)->getChildAtIdx(index);
        return static_cast<Node>(std::find(windows.begin(), windows.end(), window) - windows.begin());
    }
    bool has_click_property(Node node) const override { return windows.at(node)->isPropertyPresent("onClick"); }
    std::string click_property(Node node) const override { return string(windows.at(node)->getProperty("onClick")); }
    void set_function(Node node, UiLayoutFunction function) noexcept override {
        // Entries preallocated before mapping: the original operation is a field write.
        functions.find(windows[node])->second = function;
    }
    void collect(CEGUI::Window* window) {
        windows.push_back(window);
        functions.emplace(window, UiLayoutFunction::none);
        for (std::size_t i = 0; i < window->getChildCount(); ++i) collect(window->getChildAtIdx(i));
    }
};
std::string leaf(const std::string& name) {
    return name.substr(name.find_last_of('/') == std::string::npos ? 0 : name.find_last_of('/') + 1);
}
} // namespace

struct CeguiMenu::Impl {
    struct View {
        CeguiPage page;
        std::string prefix;
        CEGUI::Window *root = nullptr, *content = nullptr, *layout = nullptr;
        FunctionTree bindings;
        std::map<std::string, CEGUI::Window*> named;
        std::map<CEGUI::Window*, std::pair<CEGUI::UVector2, CEGUI::UVector2>> original_geometry;
        bool attached = false;
    };
    ArchiveProvider provider;
    QuadRenderer renderer;
    CEGUI::ExpatParser parser;
    std::unique_ptr<CEGUI::System> system;
    CEGUI::Window* sheet = nullptr;
    CEGUI::Window* ingame_sheet = nullptr;
    std::map<CeguiPage, View> views;
    Action action;
    int width = 0, height = 0;
    bool settings_initialized = false;
    std::vector<UiResolution> resolutions;
    std::set<CEGUI::uint> held_keys;
    std::vector<std::tuple<CeguiPage, std::string, UiLayoutFunction>> pending;
    Impl(const PakArchive& archive, Action callback)
        : provider(archive), renderer(archive), action(std::move(callback)) {
        if (CEGUI::System::getSingletonPtr())
            throw std::logic_error("only one CEGUI frontend may own the library System");
        new LibraryLogger();
        system = std::make_unique<CEGUI::System>(&renderer, &provider, &parser);
        registerAllFactoriesFunction();
        CEGUI::SchemeManager::getSingleton().loadScheme("media/UI/GuiLookSkin.scheme");
        system->setDefaultFont("Serif");
        CEGUI::MouseCursor::getSingleton().hide();
        sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "__cegui/sheet");
        sheet->setSize({{1, 0}, {1, 0}});
        // CGameUI aa3666 uses Ingame UI Sheet (+488) for Options;
        // aa36e0 and aa4016 use Sheet (+470) for Settings and Main.
        ingame_sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "__cegui/ingame_sheet");
        ingame_sheet->setSize({{1, 0}, {1, 0}});
        ingame_sheet->setMousePassThroughEnabled(true);
        ingame_sheet->setZOrderingEnabled(false);
        sheet->addChildWindow(ingame_sheet);
        make_view(CeguiPage::main, "main", "mainmenuframe", false);
        if (archive.contains_normalized("media/UI/optionsmenu.layout"))
            make_view(CeguiPage::options, "options", "optionsmenu", true);
        if (archive.contains_normalized("media/UI/settingsmenu.layout")) {
            auto& settings = make_view(CeguiPage::settings, "settings", "settingsmenu", true);
            // CSettingsMenu::createMenus @bd7fbd..bd80e9. The library creates
            // and owns Editbox/DropList/Button and scrollbar children.
            for (const auto* name : {"ResolutionDropdown", "ShadowDropdown", "ParticleDropdown"}) {
                auto* combo = static_cast<CEGUI::Combobox*>(settings.named.at(name));
                combo->getDropList()->setAlwaysOnTop(true);
                combo->getDropList()->setAutoArmEnabled(true);
                combo->setSingleClickEnabled(true);
                combo->getDropList()->setClippedByParent(false);
                combo->setClippedByParent(false);
            }
            settings.named.at("HardwareSkinning")->hide(); // bd801e..bd8027
            // Constructor bd86a9 reads UTF-32LE "Settings" at ff10a0,
            // then setTitle b17e70 -> Window::setText b17f87.
            settings.named.at("Title")->setText("Settings");
        }
        if (archive.contains_normalized("media/UI/charactercreate.layout")) {
            auto& v = make_view(CeguiPage::create, "create", "charactercreate", false);
            static_cast<CEGUI::Editbox*>(v.named.at("EditBox"))->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
                CEGUI::Event::Subscriber(&Impl::submit_name, this)); // c5db84 -> c53f40
            static_cast<CEGUI::Editbox*>(v.named.at("EditBoxPet"))->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
                CEGUI::Event::Subscriber(&Impl::submit_pet_name, this)); // c5dd34 -> c5c2f0
            // Existing portable capability boundary: companion preview/spawn
            // has no recovered application consumer. Preserve its disabled
            // choice controls rather than expose an executable pet choice.
            for (const auto* name : {"Dog", "Cat", "Ferret"}) v.named.at(name)->disable();
        }
        if (archive.contains_normalized("media/UI/characterload.layout"))
            make_view(CeguiPage::load, "load", "characterload", false); // c406a0: root, flags=1
        auto& main = views.at(CeguiPage::main);
        main.named.at("DemoVersion")->hide();
        if (main.named.count("CharacterModsWarning")) main.named.at("CharacterModsWarning")->hide();
        main.named.at("CreditFrame")->hide();
        if (main.named.count("CreditFrameB")) main.named.at("CreditFrameB")->hide();
        main.named.at("Credits")->setText(main_menu_credit_text());
        if (main.named.count("CopyrightInfo"))
            main.named.at("CopyrightInfo")->setText("(v1.15) Torchlight (C) 2009 Runic Games Inc.");
        attach(main, true);
        system->setGUISheet(sheet);
        resize(1024, 768);
    }
    View& make_view(CeguiPage page, const std::string& name, const std::string& layout_name, bool in_content) {
        auto& v = views.emplace(page, View{page, "__cegui/" + name + "/", nullptr, nullptr,
            nullptr, {}, {}, {}, false}).first->second;
        auto& manager = CEGUI::WindowManager::getSingleton();
        v.root = manager.createWindow("DefaultWindow", v.prefix + "root");
        v.root->setSize({{1, 0}, {1, 0}});
        v.root->setProperty("RiseOnClick", "False");
        v.root->setMousePassThroughEnabled(false);
        v.root->setZOrderingEnabled(false);
        auto* back = manager.createWindow("DefaultWindow", v.prefix + "back");
        v.root->addChildWindow(back);
        back->setSize({{1, 0}, {1, 0}});
        back->setProperty("RiseOnClick", "False");
        back->moveToBack();
        back->setZOrderingEnabled(false);
        v.content = manager.createWindow("DefaultWindow", v.prefix + "content");
        v.root->addChildWindow(v.content);
        v.content->setSize({{1, 0}, {1, 0}});
        v.content->setProperty("RiseOnClick", "False");
        v.content->setMousePassThroughEnabled(true);
        v.content->moveToFront();
        v.content->setZOrderingEnabled(false);
        v.layout = manager.loadWindowLayout("media/UI/" + layout_name + ".layout", v.prefix);
        v.bindings.collect(v.layout);
        map_ui_functions(v.bindings, 0);
        for (auto* window : v.bindings.windows) {
            v.named.emplace(leaf(string(window->getName())), window);
            v.original_geometry.emplace(window, std::make_pair(window->getPosition(), window->getSize()));
        }
        subscribe(v.layout);
        // Main attaches to root; Settings/Options to content (bd7079/b8828e).
        (in_content ? v.content : v.root)->addChildWindow(v.layout);
        v.layout->setPosition({{0, 0}, {0, 0}});
        if (page == CeguiPage::options) v.root->setAlwaysOnTop(true); // b8829a
        return v;
    }
    void attach(View& v, bool value) {
        if (v.attached == value) return;
        if (value) {
            (v.page == CeguiPage::options ? ingame_sheet : sheet)->addChildWindow(v.root);
            v.root->moveToBack(); // CSettingsMenu bd5640; CDropdown b178fc
            if (v.page == CeguiPage::options) v.root->moveToFront(); // b87229
        } else (v.page == CeguiPage::options ? ingame_sheet : sheet)->removeChildWindow(v.root);
        v.attached = value;
    }
    bool down(const CEGUI::EventArgs& args) {
        const auto& event = static_cast<const CEGUI::MouseEventArgs&>(args);
        if (event.button != CEGUI::LeftButton) return true;
        for (auto& [page, v] : views) {
            const auto function = v.bindings.functions.find(event.window);
            if (function != v.bindings.functions.end()) {
                pending.emplace_back(page, leaf(string(event.window->getName())), function->second);
                break;
            }
        }
        return true;
    }
    bool double_click(const CEGUI::EventArgs& args) {
        const auto& event = static_cast<const CEGUI::MouseEventArgs&>(args);
        if (event.button != CEGUI::LeftButton) return true;
        const auto found = views.find(CeguiPage::load);
        if (found != views.end() && found->second.attached) {
            const auto binding = found->second.bindings.functions.find(event.window);
            // CContinueGameMenu::onDoubleClick c33537..c3357a: 14..17,
            // deliberately excludes the fifth row. Frontend consumes the
            // selected save/health guard through the same Play path.
            if (binding != found->second.bindings.functions.end() &&
                static_cast<int>(binding->second) >= 14 && static_cast<int>(binding->second) <= 17)
                pending.emplace_back(CeguiPage::load, leaf(string(event.window->getName())), UiLayoutFunction::continue_game);
        }
        const auto main = views.find(CeguiPage::main);
        if (main != views.end() && main->second.bindings.functions.count(event.window))
            return dropdown_default_double_click(); // Main vtable ff3138 -> b05e80.
        return true;
    }
    bool submit_name(const CEGUI::EventArgs&) {
        auto& v = views.at(CeguiPage::create);
        if (!v.named.at("EditBox")->getText().empty()) v.named.at("EditBoxPet")->activate(); // c53f44..c53f5c
        return true;
    }
    bool submit_pet_name(const CEGUI::EventArgs&) {
        auto& v = views.at(CeguiPage::create);
        if (v.named.at("EditBoxPet")->getText().empty()) return true; // c5c30d
        if (v.named.at("EditBox")->getText().empty()) v.named.at("EditBox")->activate(); // c5c470
        else pending.emplace_back(CeguiPage::create, "EditBoxPet", UiLayoutFunction::new_game);
        return true;
    }
    void update_creation() {
        const auto found = views.find(CeguiPage::create);
        if (found == views.end()) return;
        auto& v = found->second;
        // c5cca6..c5cdb1: length checks, with no ASCII whitelist or trim.
        v.named.at("CreatePlayer")->setVisible(!v.named.at("EditBox")->getText().empty() &&
            !v.named.at("EditBoxPet")->getText().empty());
    }
    void subscribe(CEGUI::Window* window) {
        for (std::size_t child = 0; child < window->getChildCount(); ++child)
            subscribe(window->getChildAtIdx(child));
        try {
            if (window->isPropertyPresent("onClick") && !window->getProperty("onClick").empty()) {
                window->setWantsMultiClickEvents(true);
                window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,
                    CEGUI::Event::Subscriber(&Impl::down, this));
                window->subscribeEvent(CEGUI::Window::EventMouseDoubleClick,
                    CEGUI::Event::Subscriber(&Impl::double_click, this));
            }
        } catch (...) {} // Original local subscription catch; prior effects survive.
    }
    void deliver() {
        update_creation();
        auto requests = std::move(pending);
        pending.clear();
        for (const auto& [page, name, function] : requests) action(page, name, function);
    }
    static CEGUI::Combobox* combo(View& v, const char* name) {
        return static_cast<CEGUI::Combobox*>(v.named.at(name));
    }
    static CEGUI::Checkbox* checkbox(View& v, const char* name) {
        return static_cast<CEGUI::Checkbox*>(v.named.at(name));
    }
    static CEGUI::Slider* slider(View& v, const char* name) {
        return static_cast<CEGUI::Slider*>(v.named.at(name));
    }
    // CGameUI::sizeComboList @a849d0..a84bc2: real item metrics, named
    // rendering area, edit height and CEGUI's signed nearest-pixel Y rounding.
    static void size_combo(CEGUI::Combobox* c) {
        auto* list = c->getDropList();
        const float edit_height = c->getEditbox()->getPixelSize().d_height;
        const float list_height = list->getPixelSize().d_height;
        const auto& look = CEGUI::WidgetLookManager::getSingleton().getWidgetLook(list->getLookNFeel());
        const auto& name = list->getHorzScrollbar()->isVisible(false)
            ? "ItemRenderingAreaHScroll" : "ItemRenderingArea";
        const auto area = look.getNamedArea(name).getArea().getPixelRect(*list);
        // The shipped Rect ABI packs top/bottom before left/right. This is
        // rendering-area height, not a width (verified a84af3..a84b17).
        const float border = list_height - area.getHeight();
        const auto& y = list->getYPosition();
        const float scaled_y = y.d_scale * c->getPixelSize().d_height;
        const float offset_y = static_cast<float>(static_cast<int>(scaled_y + (scaled_y > 0 ? .5F : -.5F))) + y.d_offset;
        c->setHeight({0, list->getTotalItemsHeight() + edit_height + border + offset_y - edit_height});
    }
    void size_combos() {
        auto& v = views.at(CeguiPage::settings);
        for (const auto* name : {"ResolutionDropdown", "ShadowDropdown", "ParticleDropdown"})
            size_combo(combo(v, name));
    }
    static void fill(CEGUI::Combobox* c, const std::vector<UiComboOption>& options) {
        for (const auto& option : options) {
            auto item = std::make_unique<CEGUI::ListboxTextItem>(option.text, static_cast<CEGUI::uint>(option.id));
            item->setSelectionColours(CEGUI::colour(1, .5F, .5F, 1));
            c->addItem(item.get());
            item.release(); // Listbox owns auto-deleted items, original constructor arg r9=1.
        }
    }
    static void select(CEGUI::Combobox* c, std::size_t index) {
        c->setItemSelectState(index, true);
    }
    void set_settings(const DisplaySettings& value, const std::vector<UiResolution>& modes) {
        auto& v = views.at(CeguiPage::settings);
        // Evaluated named settings from the live draft; these port slots are
        // not numeric IDs from the original global registration. GetInt's
        // original +0x40/+0x48 reader borrows this table for each call.
        enum IntSetting : std::uint32_t { fullscreen, fsaa, vsync, shadow_detail, width, height };
        static_assert(sizeof(int) == sizeof(std::int32_t));
        const std::array<std::int32_t, 6> integers{{value.fullscreen ? 1 : 0, value.fsaa,
            value.vsync ? 1 : 0, value.shadows_detail, value.res_width, value.res_height}};
        const auto integer = [&](IntSetting key) {
            return ui_int_property(integers.data(), integers.size(), key);
        };
        checkbox(v, "Fullscreen")->setSelected(integer(fullscreen) != 0); // bd5660 -> bd5674
        checkbox(v, "Antialiasing")->setSelected(integer(fsaa) != 0); // bd568d -> bd56a1
        checkbox(v, "RenderBehind")->setSelected(value.render_behind);
        checkbox(v, "Rimlights")->setSelected(value.rimlights);
        checkbox(v, "HardwareSkinning")->setSelected(value.hardware_skinning);
        checkbox(v, "VSync")->setSelected(integer(vsync) != 0); // bd5741 -> bd5755
        checkbox(v, "SoundMute")->setSelected(value.sound_mute);
        checkbox(v, "MusicMute")->setSelected(value.music_mute);
        checkbox(v, "ShowTips")->setSelected(value.show_tips);
        checkbox(v, "ShowFloatyNumbers")->setSelected(value.floaty_numbers);
        checkbox(v, "ShowBlood")->setSelected(value.show_blood);
        checkbox(v, "NetbookMode")->setSelected(value.netbook_mode);
        slider(v, "SoundVolume")->setMaxValue(1);
        slider(v, "SoundVolume")->setCurrentValue(value.sound_volume);
        slider(v, "MusicVolume")->setMaxValue(1);
        slider(v, "MusicVolume")->setCurrentValue(value.music_volume);
        auto* resolution = combo(v, "ResolutionDropdown");
        if (!settings_initialized || resolutions != modes) {
            resolution->resetList();
            resolutions = modes;
            fill(resolution, UiSettingsComboboxes::resolution_options(modes));
        }
        if (resolution->getItemCount()) {
            select(resolution, 0); // bd692e: default row before matching current dimensions
            for (std::size_t n = 0; n < resolution->getItemCount(); ++n) {
                const auto id = resolution->getListboxItemFromIndex(n)->getID();
                const auto& mode = modes.at(id);
                if (mode.width == integer(width) && mode.height == integer(height)) select(resolution, n);
            }
        }
        auto* shadow = combo(v, "ShadowDropdown");
        auto* particle = combo(v, "ParticleDropdown");
        if (!settings_initialized) {
            fill(shadow, UiSettingsComboboxes::shadow_options());
            fill(particle, UiSettingsComboboxes::particle_options());
        }
        select(shadow, 0);
        const auto detail = integer(shadow_detail); // bd61f7 -> native item selection
        if (detail >= 0 && detail < 6)
            select(shadow, static_cast<std::size_t>(detail));
        select(particle, 0);
        for (std::size_t n = 0; n < 3; ++n) {
            if (UiSettingsComboboxes::particle_options()[n].particle_fps >= value.particle_fps) {
                select(particle, n);
                break;
            }
        }
        settings_initialized = true;
        size_combos();
        for (auto* c : {resolution, shadow, particle}) { c->moveToFront(); c->getDropList()->moveToFront(); }
    }
    DisplaySettings settings_values(DisplaySettings value, bool applying) {
        auto& v = views.at(CeguiPage::settings);
        value.fullscreen = checkbox(v, "Fullscreen")->isSelected();
        value.fsaa = checkbox(v, "Antialiasing")->isSelected() ? 1 : 0; // bd53c6..bd53d4
        value.render_behind = checkbox(v, "RenderBehind")->isSelected();
        value.rimlights = checkbox(v, "Rimlights")->isSelected();
        value.hardware_skinning = checkbox(v, "HardwareSkinning")->isSelected();
        value.vsync = checkbox(v, "VSync")->isSelected();
        value.sound_mute = checkbox(v, "SoundMute")->isSelected();
        value.music_mute = checkbox(v, "MusicMute")->isSelected();
        value.show_tips = checkbox(v, "ShowTips")->isSelected();
        value.floaty_numbers = checkbox(v, "ShowFloatyNumbers")->isSelected();
        value.show_blood = checkbox(v, "ShowBlood")->isSelected();
        value.netbook_mode = checkbox(v, "NetbookMode")->isSelected();
        value.sound_volume = slider(v, "SoundVolume")->getCurrentValue();
        value.music_volume = slider(v, "MusicVolume")->getCurrentValue();
        if (const auto* item = combo(v, "ResolutionDropdown")->getSelectedItem()) {
            const auto mode = resolutions.at(item->getID());
            value.res_width = mode.width; value.res_height = mode.height;
        }
        if (const auto* item = combo(v, "ShadowDropdown")->getSelectedItem())
            UiSettingsComboboxes::apply({UiSettingsComboKind::shadow, 0,
                UiSettingsComboboxes::shadow_options().at(item->getID())}, value);
        if (const auto* item = combo(v, "ParticleDropdown")->getSelectedItem())
            UiSettingsComboboxes::apply({UiSettingsComboKind::particle, 0,
                UiSettingsComboboxes::particle_options().at(item->getID())}, value);
        // bd4a11..bd4a42 / bd4c58: Netbook overrides only on Apply.
        if (applying && value.netbook_mode) {
            value.fsaa = 0; value.render_behind = false; value.rimlights = false;
            UiSettingsComboboxes::apply({UiSettingsComboKind::shadow, 0,
                UiSettingsComboboxes::shadow_options().front()}, value);
            UiSettingsComboboxes::apply({UiSettingsComboKind::particle, 0,
                UiSettingsComboboxes::particle_options().front()}, value);
        }
        return value;
    }
    void resize(int w, int h) {
        if (width == w && height == h) return;
        renderer.resize(w, h);
        const float ratio = static_cast<float>(h) / 768.0F;
        for (auto& [page, v] : views) {
            // convertToScreenScale a83ed0 is child-first and scales the
            // four position/size offsets, not min/max area offsets. Keeping
            // pristine geometry makes this host resize adapter noncumulative.
            const auto scale = [&](const auto& self, CEGUI::Window* window) -> void {
                for (std::size_t n = 0; n < window->getChildCount(); ++n)
                    self(self, window->getChildAtIdx(n));
                auto position = v.original_geometry.at(window).first;
                auto size = v.original_geometry.at(window).second;
                position.d_x.d_offset = ui_scale_offset(position.d_x.d_offset, ratio);
                position.d_y.d_offset = ui_scale_offset(position.d_y.d_offset, ratio);
                size.d_x.d_offset = ui_scale_offset(size.d_x.d_offset, ratio);
                size.d_y.d_offset = ui_scale_offset(size.d_y.d_offset, ratio);
                window->setPosition(position);
                window->setSize(size);
            };
            scale(scale, v.layout);
            if (page == CeguiPage::main || page == CeguiPage::create) v.layout->setPosition({{0, 0}, {0, 0}});
        }
        width = w; height = h;
        if (settings_initialized) size_combos();
    }
};

bool CeguiMenu::available(const PakArchive& archive) {
    return archive.contains_normalized("media/UI/GuiLookSkin.scheme") &&
           archive.contains_normalized("media/UI/mainmenuframe.layout");
}
CeguiMenu::CeguiMenu(const PakArchive& archive, Action action)
    : impl_(library_call([&] { return std::make_unique<Impl>(archive, std::move(action)); })) {}
CeguiMenu::~CeguiMenu() = default;
void CeguiMenu::state(bool open, bool can_continue, bool credits, bool linux_credits) {
    library_call([&] {
    auto& i = *impl_;
    // Retain the library tree when closing; reattach the same windows on open.
    auto& v = i.views.at(CeguiPage::main);
    i.attach(v, open);
    v.named.at("ContinueLast")->setVisible(can_continue);
    v.named.at("CreditFrame")->setVisible(credits);
    if (v.named.count("CreditFrameB")) v.named.at("CreditFrameB")->setVisible(linux_credits);
    });
}
void CeguiMenu::resize(int width, int height) { library_call([&] { impl_->resize(width, height); }); }
void CeguiMenu::pointer_event(const UiPointerEvent& event) {
    if (!std::isfinite(event.x) || !std::isfinite(event.y))
        throw std::invalid_argument("invalid CEGUI pointer position");
    if (event.button >= CEGUI::MouseButtonCount) throw std::invalid_argument("invalid CEGUI pointer button");
    library_call([&] {
    auto& i = *impl_;
    if (event.kind == UiPointerEventKind::leave) i.system->injectMouseLeaves();
    else {
        i.system->injectMousePosition(event.x, event.y);
        if (event.button >= CEGUI::MouseButtonCount) throw std::invalid_argument("invalid CEGUI pointer button");
        const auto button = static_cast<CEGUI::MouseButton>(event.button);
        if (event.kind == UiPointerEventKind::button_down) i.system->injectMouseButtonDown(button);
        else if (event.kind == UiPointerEventKind::button_up) i.system->injectMouseButtonUp(button);
    }
    i.deliver();
    });
}
void CeguiMenu::advance(float seconds) {
    if (!std::isfinite(seconds) || seconds < 0) throw std::invalid_argument("invalid CEGUI time pulse");
    library_call([&] { impl_->system->injectTimePulse(seconds); impl_->deliver(); });
}
CeguiMenuFrame CeguiMenu::frame(int width, int height) {
    return library_call([&] {
    auto& i = *impl_;
    i.resize(width, height);
    i.update_creation();
    i.system->renderGUI();
    CeguiMenuFrame result;
    result.quads = i.renderer.quads;
    for (auto& [page, v] : i.views) for (auto* window : v.bindings.windows) {
        CeguiWidget widget;
        widget.page = page;
        widget.name = page == CeguiPage::main ? leaf(string(window->getName())) : string(window->getName());
        widget.type = string(window->getType());
        widget.text = string(window->getText());
        if (window->getFont()) widget.font = string(window->getFont()->getProperty("Name"));
        widget.rect = rectangle(window->getUnclippedPixelRect());
        widget.clip = rectangle(window->getPixelRect());
        widget.has_clip = true;
        widget.visible = v.attached && window->isVisible();
        widget.enabled = !window->isDisabled();
        widget.layout_function = v.bindings.functions.at(window);
        if (window->isPropertyPresent("Selected")) widget.properties["Selected"] = string(window->getProperty("Selected"));
        if (window->isPropertyPresent("CurrentValue")) widget.properties["CurrentValue"] = string(window->getProperty("CurrentValue"));
        if (window->isPropertyPresent("onClick")) widget.callback = string(window->getProperty("onClick"));
        result.widgets.push_back(std::move(widget));
    }
    return result;
    });
}
bool CeguiMenu::has_linux_credits() const { return impl_->views.at(CeguiPage::main).named.count("CreditFrameB") != 0; }
void CeguiMenu::settings_state(bool open, const DisplaySettings& value, const std::vector<UiResolution>& modes) {
    library_call([&] {
        auto& i = *impl_;
        const auto found = i.views.find(CeguiPage::settings);
        if (found == i.views.end()) { if (open) throw std::runtime_error("missing native settings layout"); return; }
        auto& v = found->second;
        const bool opening = open && !v.attached;
        i.attach(v, open);
        if (opening || (open && i.resolutions != modes)) i.set_settings(value, modes);
    });
}
DisplaySettings CeguiMenu::settings_values(DisplaySettings base, bool applying) const {
    return library_call([&] { return impl_->settings_values(base, applying); });
}
void CeguiMenu::options_state(bool attached, const std::array<float, 2>& position) {
    library_call([&] {
        const auto found = impl_->views.find(CeguiPage::options);
        if (found == impl_->views.end()) { if (attached) throw std::runtime_error("missing native options layout"); return; }
        auto& v = found->second;
        impl_->attach(v, attached);
        v.content->setPosition({{0, position[0]}, {0, position[1]}});
    });
}
void CeguiMenu::creation_state(bool open, const std::string& class_name,
    const std::string& display_name, const std::string& description) {
    library_call([&] {
        const auto found = impl_->views.find(CeguiPage::create);
        if (found == impl_->views.end()) { if (open) throw std::runtime_error("missing native creation layout"); return; }
        auto& v = found->second;
        const bool opening = open && !v.attached;
        impl_->attach(v, open);
        if (opening) {
            v.named.at("EditBox")->setText(""); // c5c67a
            v.named.at("EditBox")->activate(); // c5c697
            v.named.at("EditBoxPet")->setText("Spot"); // UTF-8 ff3168 -> c5c826
        }
        if (open) {
            v.named.at("CharacterClass")->setText(utf8(display_name)); // DISPLAYNAME, c5cdf6 -> c5cfa9
            v.named.at("CharacterClassDescription")->setText(utf8(description));
            for (const auto* name : {"Destroyer", "Vanquisher", "Alchemist"}) {
                auto internal = std::string(name);
                std::transform(internal.begin(), internal.end(), internal.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
                auto selected = class_name;
                std::transform(selected.begin(), selected.end(), selected.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
                static_cast<CEGUI::RadioButton*>(v.named.at(name))->setSelected(internal == selected);
            }
        }
        impl_->update_creation();
    });
}
std::string CeguiMenu::creation_name() const {
    return library_call([&] { return string(impl_->views.at(CeguiPage::create).named.at("EditBox")->getText()); });
}
void CeguiMenu::load_state(bool open, const std::vector<CeguiLoadEntry>& entries,
    std::size_t scroll, std::size_t selected, bool confirmation) {
    library_call([&] {
        const auto found = impl_->views.find(CeguiPage::load);
        if (found == impl_->views.end()) { if (open) throw std::runtime_error("missing native load layout"); return; }
        auto& v = found->second;
        impl_->attach(v, open);
        if (!open) return;
        for (std::size_t row = 0; row < 5; ++row) {
            const auto suffix = std::to_string(row + 1);
            const bool occupied = scroll < entries.size() && row < entries.size() - scroll;
            auto* slot = v.named.at("Player" + suffix);
            auto* name = v.named.at("Player" + suffix + "Name");
            auto* description = v.named.at("Player" + suffix + "Desc");
            auto* highlight = v.named.at("PlayerHighlight" + suffix);
            // c3b3a9..c3b3cd, c3b725..c3b752: show occupied rows.
            slot->setVisible(occupied); name->setVisible(occupied); description->setVisible(occupied);
            name->setText(utf8(occupied ? entries[scroll + row].name : ""));
            description->setText(utf8(occupied ? entries[scroll + row].description : ""));
            highlight->setVisible(occupied && selected == scroll + row);
            if (occupied) highlight->moveToFront(); // c3c571 -> c3c57e, even when hidden
        }
        v.named.at("ScrollUp")->setVisible(scroll != 0); // c3b78b / c3d5ad
        v.named.at("ScrollDown")->setVisible(scroll < entries.size() && entries.size() - scroll > 5);
        v.named.at("Continue")->setVisible(!entries.empty()); // c3b7eb
        v.named.at("Delete")->setVisible(!entries.empty()); // c3b815
        v.named.at("CharacterName")->setText(utf8(selected < entries.size() ? entries[selected].name : ""));
        // Original uses enabled-mod/SVB comparison. OTC has no such producer.
        v.named.at("CharacterModsWarning")->hide();
        v.named.at("DeleteConfirm")->setVisible(confirmation);
    });
}
namespace {
CEGUI::uint scan_code(std::uint32_t physical) {
    // Linux/host -> CEGUI's documented DirectInput scan-code namespace.
    // The unextended US block has identical values; extended evdev codes do not.
    if (physical > 0 && physical <= physical_key::F12) return physical;
    switch (physical) {
    case physical_key::KPENTER: return CEGUI::Key::NumpadEnter;
    case physical_key::RIGHTCTRL: return CEGUI::Key::RightControl;
    case physical_key::KPSLASH: return CEGUI::Key::Divide;
    case physical_key::RIGHTALT: return CEGUI::Key::RightAlt;
    case physical_key::HOME: return CEGUI::Key::Home;
    case physical_key::UP: return CEGUI::Key::ArrowUp;
    case physical_key::PAGEUP: return CEGUI::Key::PageUp;
    case physical_key::LEFT: return CEGUI::Key::ArrowLeft;
    case physical_key::RIGHT: return CEGUI::Key::ArrowRight;
    case physical_key::END: return CEGUI::Key::End;
    case physical_key::DOWN: return CEGUI::Key::ArrowDown;
    case physical_key::PAGEDOWN: return CEGUI::Key::PageDown;
    case physical_key::INSERT: return CEGUI::Key::Insert;
    case physical_key::DELETE: return CEGUI::Key::Delete;
    default: return 0;
    }
}
}
void CeguiMenu::keyboard_event(const UiKeyboardEvent& event) {
    library_call([&] {
        auto& i = *impl_;
        if (event.kind == UiKeyboardEventKind::text) {
            const CEGUI::String text(reinterpret_cast<const CEGUI::utf8*>(event.text.c_str()));
            for (std::size_t n = 0; n < text.length(); ++n) i.system->injectChar(text[n]);
        } else if (event.kind == UiKeyboardEventKind::leave) {
            const auto keys = std::move(i.held_keys); i.held_keys.clear();
            for (const auto key : keys) i.system->injectKeyUp(key);
        } else if (const auto code = scan_code(event.key)) {
            if (event.kind == UiKeyboardEventKind::key_down) { i.held_keys.insert(code); i.system->injectKeyDown(code); }
            else { i.held_keys.erase(code); i.system->injectKeyUp(code); }
        }
        i.deliver();
    });
}
void CeguiMenu::focus(CeguiPage page, const std::string& name) {
    library_call([&] { impl_->views.at(page).named.at(leaf(name))->activate(); });
}
} // namespace torchlight
