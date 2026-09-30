#include "torchlight/cegui_menu.hpp"
#include "torchlight/dds_texture.hpp"
#include "torchlight/png_texture.hpp"
#include <CEGUI.h>
#include <CEGUITinyXMLParser.h>
#include <FalModule.h>
#include <algorithm>
#include <cmath>
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
    ArchiveProvider provider;
    QuadRenderer renderer;
    CEGUI::TinyXMLParser parser;
    std::unique_ptr<CEGUI::System> system;
    CEGUI::Window* sheet = nullptr;
    CEGUI::Window* root = nullptr;
    CEGUI::Window* layout = nullptr;
    FunctionTree bindings;
    std::map<std::string, CEGUI::Window*> named;
    std::vector<std::pair<CEGUI::Window*, CEGUI::URect>> original_areas;
    Action action;
    int width = 0, height = 0;
    bool open = true;
    Impl(const PakArchive& archive, Action callback)
        : provider(archive), renderer(archive), action(std::move(callback)) {
        if (CEGUI::System::getSingletonPtr())
            throw std::logic_error("only one CEGUI frontend may own the library System");
        new LibraryLogger(); // CEGUI::System destroys its logger on normal teardown.
        system = std::make_unique<CEGUI::System>(&renderer, &provider, &parser);
        registerAllFactoriesFunction();
        CEGUI::SchemeManager::getSingleton().loadScheme("media/UI/GuiLookSkin.scheme");
        system->setDefaultFont("Serif");
        CEGUI::MouseCursor::getSingleton().hide();
        auto& manager = CEGUI::WindowManager::getSingleton();
        sheet = manager.createWindow("DefaultWindow", "__cegui/sheet");
        sheet->setSize({{1, 0}, {1, 0}});
        root = manager.createWindow("DefaultWindow", "__cegui/main/root");
        root->setSize({{1, 0}, {1, 0}});
        root->setProperty("RiseOnClick", "False");
        root->setMousePassThroughEnabled(false);
        root->setZOrderingEnabled(false);
        sheet->addChildWindow(root);
        auto* back = manager.createWindow("DefaultWindow", "__cegui/main/back");
        root->addChildWindow(back);
        back->setSize({{1, 0}, {1, 0}});
        back->setProperty("RiseOnClick", "False");
        back->moveToBack();
        back->setZOrderingEnabled(false);
        auto* content = manager.createWindow("DefaultWindow", "__cegui/main/content");
        root->addChildWindow(content);
        content->setSize({{1, 0}, {1, 0}});
        content->setProperty("RiseOnClick", "False");
        content->setMousePassThroughEnabled(true);
        content->moveToFront();
        content->setZOrderingEnabled(false);
        layout = manager.loadWindowLayout("media/UI/mainmenuframe.layout", CEGUI::String("__cegui/main/"));
        bindings.collect(layout);
        map_ui_functions(bindings, 0);
        for (auto* window : bindings.windows) {
            named.emplace(leaf(string(window->getName())), window);
            original_areas.emplace_back(window, window->getArea());
        }
        subscribe(layout);
        root->addChildWindow(layout);
        layout->setPosition({{0, 0}, {0, 0}});
        // CMainMenu::createMenus, including required versus optional windows.
        named.at("DemoVersion")->hide();
        if (named.count("CharacterModsWarning")) named.at("CharacterModsWarning")->hide();
        named.at("CreditFrame")->hide();
        if (named.count("CreditFrameB")) named.at("CreditFrameB")->hide();
        named.at("Credits")->setText(main_menu_credit_text());
        if (named.count("CopyrightInfo"))
            named.at("CopyrightInfo")->setText("(v1.15) Torchlight (C) 2009 Runic Games Inc.");
        system->setGUISheet(sheet);
        resize(1024, 768);
    }
    bool down(const CEGUI::EventArgs& args) {
        const auto& event = static_cast<const CEGUI::MouseEventArgs&>(args);
        if (event.button != CEGUI::LeftButton) return true;
        // Queue rather than mutate controller during a library callback. Frontend
        // consumes after inject returns, preserving safe event/window ownership.
        pending.emplace_back(leaf(string(event.window->getName())), bindings.functions.at(event.window));
        return true;
    }
    bool double_click(const CEGUI::EventArgs&) { return true; }
    void subscribe(CEGUI::Window* window) {
        const auto count = window->getChildCount();
        for (std::size_t child = 0; child < count; ++child) subscribe(window->getChildAtIdx(child));
        // CDropdownMenu::mapEventHandlers: child-first; down before double.
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
    std::vector<std::pair<std::string, UiLayoutFunction>> pending;
    void deliver() {
        auto requests = std::move(pending);
        pending.clear();
        for (const auto& item : requests) action(item.first, item.second);
    }
    void resize(int w, int h) {
        if (width == w && height == h) return;
        renderer.resize(w, h);
        const float ratio = static_cast<float>(h) / 768.0F;
        for (const auto& item : original_areas) {
            auto area = item.second;
            area.d_min.d_x.d_offset *= ratio;
            area.d_min.d_y.d_offset *= ratio;
            area.d_max.d_x.d_offset *= ratio;
            area.d_max.d_y.d_offset *= ratio;
            item.first->setArea(area);
        }
        layout->setPosition({{0, 0}, {0, 0}});
        width = w;
        height = h;
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
    if (i.open != open) {
        if (open) i.sheet->addChildWindow(i.root);
        else i.sheet->removeChildWindow(i.root);
        i.open = open;
    }
    i.named.at("ContinueLast")->setVisible(can_continue);
    i.named.at("CreditFrame")->setVisible(credits);
    if (i.named.count("CreditFrameB")) i.named.at("CreditFrameB")->setVisible(linux_credits);
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
    i.system->renderGUI();
    CeguiMenuFrame result;
    result.quads = i.renderer.quads;
    for (auto* window : i.bindings.windows) {
        UiResolvedWidget widget;
        widget.name = leaf(string(window->getName()));
        widget.type = string(window->getType());
        widget.text = string(window->getText());
        widget.rect = rectangle(window->getUnclippedPixelRect());
        widget.clip = rectangle(window->getPixelRect());
        widget.has_clip = true;
        widget.visible = i.open && window->isVisible();
        widget.enabled = !window->isDisabled();
        widget.layout_function = i.bindings.functions.at(window);
        if (window->isPropertyPresent("onClick")) widget.callback = string(window->getProperty("onClick"));
        result.widgets.push_back(std::move(widget));
    }
    return result;
    });
}
bool CeguiMenu::has_linux_credits() const { return impl_->named.count("CreditFrameB") != 0; }
} // namespace torchlight
