# 03-layout-and-images

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/ui_layout.cpp:316–454`

SHA256 полного файла: `d7b82bdadff2ce2795c75ad371321aa641b377168e156277041cff2ba4964cb9`

```text
  316 | std::vector<UiResolvedWidget> UiLayout::resolve(int width, int height) const {
  317 |     if (width <= 0 || height <= 0)
  318 |         throw std::invalid_argument("invalid UI viewport");
  319 |     // original-code: CEGUI resolves UnifiedAreaRect directly against the real
  320 |     // window (per-axis scale, no letterboxing). The old portable small-window
  321 |     // zoom shifted buttons ~32px and shrank them at 1280x720 while fonts ran
  322 |     // full size. Small-window readability (original: netbook mode) stays open.
  323 |     const float w = static_cast<float>(width), h = static_cast<float>(height);
  324 |     std::vector<UiResolvedWidget> result;
  325 |     for (const auto &node : widgets_) {
  326 |         const auto parent = node.parent < 0 ? UiRect{0, 0, w, h}
  327 |                                             : result.at(static_cast<std::size_t>(node.parent)).rect;
  328 |         UiResolvedWidget v;
  329 |         v.name = node.name;
  330 |         v.type = node.type;
  331 |         v.parent = node.parent;
  332 |         v.properties = node.properties;
  333 |         v.has_clip = true;
  334 |         v.rect = parent;
  335 |         v.text = node.property("Text");
  336 |         v.font = node.property("Font");
  337 |         v.callback = node.property("onClick");
  338 |         v.image = node.property("Image");
  339 |         if (v.image.empty())
  340 |             v.image = node.property("NormalImage");
  341 |         // Opening a page makes its root visible; child visibility is retained.
  342 |         v.visible = (node.parent < 0 || upper(node.property("Visible")) != "FALSE") &&
  343 |                     (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].visible);
  344 |         v.enabled = upper(node.property("Disabled")) != "TRUE" &&
  345 |                     upper(node.property("Enabled")) != "FALSE" &&
  346 |                     (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].enabled);
  347 |         if (const auto area = node.property("UnifiedAreaRect"); !area.empty()) {
  348 |             const auto a = numbers(area);
  349 |             if (a.size() != 8)
  350 |                 xml_error("area must contain eight values");
  351 |             v.rect = {parent.x + parent.width * a[0] + a[1], parent.y + parent.height * a[2] + a[3],
  352 |                       parent.width * (a[4] - a[0]) + a[5] - a[1],
  353 |                       parent.height * (a[6] - a[2]) + a[7] - a[3]};
  354 |         } else {
  355 |             if (const auto p = node.property("UnifiedPosition"); !p.empty()) {
  356 |                 const auto a = numbers(p);
  357 |                 if (a.size() != 4)
  358 |                     xml_error("position must contain four values");
  359 |                 v.rect.x = parent.x + parent.width * a[0] + a[1];
  360 |                 v.rect.y = parent.y + parent.height * a[2] + a[3];
  361 |             }
  362 |             if (const auto s = node.property("UnifiedSize"); !s.empty()) {
  363 |                 const auto a = numbers(s);
  364 |                 if (a.size() != 4)
  365 |                     xml_error("size must contain four values");
  366 |                 v.rect.width = parent.width * a[0] + a[1];
  367 |                 v.rect.height = parent.height * a[2] + a[3];
  368 |             }
  369 |         }
  370 |         const auto horizontal = upper(node.property("HorizontalAlignment"));
  371 |         const auto vertical = upper(node.property("VerticalAlignment"));
  372 |         if (horizontal == "CENTRE" || horizontal == "CENTER")
  373 |             v.rect.x += (parent.width - v.rect.width) * .5F;
  374 |         else if (horizontal == "RIGHT")
  375 |             v.rect.x += parent.width - v.rect.width;
  376 |         if (vertical == "CENTRE" || vertical == "CENTER")
  377 |             v.rect.y += (parent.height - v.rect.height) * .5F;
  378 |         else if (vertical == "BOTTOM")
  379 |             v.rect.y += parent.height - v.rect.height;
  380 |         for (auto x : {v.rect.x, v.rect.y, v.rect.width, v.rect.height})
  381 |             if (!std::isfinite(x) || std::abs(x) > 1e7F)
  382 |                 xml_error("layout bounds out of range");
  383 |         // Bounded subset: clip to viewport and each clipping ancestor. A child
  384 |         // may opt out of parent clipping, but never of the framebuffer bounds.
  385 |         const UiRect ancestor = node.parent < 0 || upper(node.property("ClippedByParent")) == "FALSE"
  386 |                                     ? UiRect{0, 0, w, h}
  387 |                                     : result[static_cast<std::size_t>(node.parent)].clip;
  388 |         const float x = std::max(v.rect.x, ancestor.x), y = std::max(v.rect.y, ancestor.y);
  389 |         v.clip = {x, y, std::max(0.0F, std::min(v.rect.x + v.rect.width,
  390 |                        ancestor.x + ancestor.width) - x),
  391 |                        std::max(0.0F, std::min(v.rect.y + v.rect.height,
  392 |                        ancestor.y + ancestor.height) - y)};
  393 |         result.push_back(std::move(v));
  394 |     }
  395 |     for (auto &v : result) {
  396 |         v.clip = {std::max(v.clip.x, 0.0F), std::max(v.clip.y, 0.0F),
  397 |                   std::min(v.clip.width, w - v.clip.x), std::min(v.clip.height, h - v.clip.y)};
  398 |         if (v.clip.width < 0) v.clip.width = 0;
  399 |         if (v.clip.height < 0) v.clip.height = 0;
  400 |     }
  401 |     return result;
  402 | }
  403 | const UiLayout *UiResources::layout(const std::string &path) {
  404 |     if (const auto it = layouts_.find(path); it != layouts_.end())
  405 |         return &it->second;
  406 |     const auto *entry = archive_->find_normalized(path);
  407 |     if (!entry)
  408 |         return nullptr;
  409 |     return &layouts_.emplace(path, UiLayout::parse(archive_->read(*entry))).first->second;
  410 | }
  411 | std::optional<UiImage> UiResources::image(const std::string &reference) {
  412 |     if (reference.empty())
  413 |         return std::nullopt;
  414 |     if (!images_loaded_) {
  415 |         images_loaded_ = true;
  416 |         for (const auto &entry : archive_->entries()) {
  417 |             const auto upper_name = upper(entry.name);
  418 |             if (upper_name.size() < 9 || upper_name.substr(upper_name.size() - 9) != ".IMAGESET")
  419 |                 continue;
  420 |             try {
  421 |                 const auto nodes = parse_xml(archive_->read(entry));
  422 |                 if (nodes.front().tag != "Imageset")
  423 |                     continue;
  424 |                 const auto set = attr(nodes.front(), "Name"),
  425 |                            file = attr(nodes.front(), "Imagefile");
  426 |                 auto base = entry.name.substr(0, entry.name.find_last_of("/\\") + 1);
  427 |                 const auto *texture = archive_->find_normalized(file);
  428 |                 if (!texture)
  429 |                     texture = archive_->find_normalized(base + file);
  430 |                 if (!texture) {
  431 |                     diagnostics_.push_back("imageset texture absent: " + entry.name);
  432 |                     continue;
  433 |                 }
  434 |                 for (const auto &n : nodes)
  435 |                     if (n.tag == "Image") {
  436 |                         UiImage image{texture->name, dimension(n, "XPos"), dimension(n, "YPos"),
  437 |                                       dimension(n, "Width"), dimension(n, "Height")};
  438 |                         images_[set + "/" + attr(n, "Name")] = std::move(image);
  439 |                     }
  440 |             } catch (const std::exception &e) {
  441 |                 diagnostics_.push_back(entry.name + ": " + e.what());
  442 |             }
  443 |         }
  444 |     }
  445 |     const auto set_pos = reference.find("set:"), image_pos = reference.find("image:");
  446 |     if (set_pos == std::string::npos || image_pos == std::string::npos)
  447 |         return std::nullopt;
  448 |     const auto token = [&](std::size_t p) {
  449 |         const auto end = reference.find_first_of(" \t\r\n", p);
  450 |         return reference.substr(p, end == std::string::npos ? end : end - p);
  451 |     };
  452 |     const auto key = token(set_pos + 4) + "/" + token(image_pos + 6);
  453 |     const auto it = images_.find(key);
  454 |     return it == images_.end() ? std::nullopt : std::optional<UiImage>(it->second);
```

## `include/torchlight/ui_layout.hpp:9–107`

SHA256 полного файла: `022c2c3b34f0c8a66ddd250243935c2c18ab3659da25fcbe45c37cced8d7d953`

```text
    9 | // Bounded subset of original CEGUI XML; not a replacement for the full skin engine.
   10 | struct UiRect {
   11 |     float x = 0, y = 0, width = 0, height = 0;
   12 |     [[nodiscard]] bool contains(float px, float py) const noexcept {
   13 |         return width > 0 && height > 0 && px >= x && py >= y && px < x + width && py < y + height;
   14 |     }
   15 | };
   16 | struct UiWidget {
   17 |     std::string name, type;
   18 |     std::int32_t parent = -1;
   19 |     std::map<std::string, std::string> properties;
   20 |     [[nodiscard]] std::string property(const std::string &key) const;
   21 | };
   22 | enum class UiTextHorizontal { left, centre, right };
   23 | enum class UiTextVertical { top, centre, bottom };
   24 | struct UiTextStyle {
   25 |     UiTextHorizontal horizontal = UiTextHorizontal::left;
   26 |     UiTextVertical vertical = UiTextVertical::top;
   27 |     bool wrap = false;
   28 | };
   29 | struct UiResolvedWidget {
   30 |     std::string name, type, text, callback, image, font;
   31 |     UiRect rect;
   32 |     bool visible = true, enabled = true;
   33 |     std::int32_t parent = -1;
   34 |     UiRect clip;
   35 |     // Resolved resource widgets have an authoritative clip, including an empty one.
   36 |     // Hand-authored PORT widgets may omit it; empty must never mean "unclipped".
   37 |     bool has_clip = false;
   38 |     std::map<std::string, std::string> properties;
   39 |     [[nodiscard]] std::string property(const std::string &key) const;
   40 |     [[nodiscard]] UiTextStyle text_style() const;
   41 | };
   42 | // Bounded port of the intersection/UV adjustment in CEGUI::Imageset::draw
   43 | // (bundled libCEGUIBase.so.1 @0xe6f20). Not pixel-rounding/colour parity.
   44 | struct UiImageGeometry {
   45 |     UiRect destination, source;
   46 | };
   47 | [[nodiscard]] std::optional<UiImageGeometry> clip_ui_image(
   48 |     UiRect destination, UiRect source, const UiRect *clip = nullptr);
   49 | class UiLayout {
   50 |   public:
   51 |     [[nodiscard]] static UiLayout parse(const std::vector<std::uint8_t> &bytes);
   52 |     [[nodiscard]] std::vector<UiResolvedWidget> resolve(int width, int height) const;
   53 |     [[nodiscard]] const std::vector<UiWidget> &widgets() const noexcept {
   54 |         return widgets_;
   55 |     }
   56 | 
   57 |   private:
   58 |     std::vector<UiWidget> widgets_;
   59 | };
   60 | struct UiImage {
   61 |     std::string texture_path;
   62 |     float x = 0, y = 0, width = 0, height = 0;
   63 | };
   64 | // Bounded GuiLook.looknfeel extraction for widget types this renderer draws.
   65 | struct UiWidgetImages {
   66 |     std::string normal, hover, pushed, disabled;
   67 | };
   68 | // resource-derived: one Falagard TextComponent pass. Coordinates are absolute
   69 | // pixels plus a multiple of the widget size (LeftEdge/TopEdge AbsoluteDim and
   70 | // UnifiedDim(scale, Width|Height) with Add/Subtract); colour names a
   71 | // TextColour-like widget property resolved against the widget, then the look
   72 | // default. Checkbox labels live past the box (x + width + 5).
   73 | struct UiTextPass {
   74 |     float dx = 0, dy = 0;
   75 |     float x_scale = 0, y_scale = 0;
   76 |     std::string colour_property;
   77 |     std::string colour_default{"FFFFFFFF"};
   78 |     // resource-derived: per-TextComponent VertFormat/HorzFormat type.
   79 |     // Unset means the component defers to the widget formatting properties
   80 |     // (HorzFormatProperty/VertFormatProperty, e.g. StaticText/ItemText).
   81 |     std::optional<UiTextHorizontal> horz;
   82 |     std::optional<UiTextVertical> vert;
   83 | };
   84 | // resource-derived: wrap width of the look's first TextComponent Area
   85 | // (Width, or RightEdge minus LeftEdge). Non-positive means the area is
   86 | // degenerate and text runs to the viewport edge (Checkbox labels).
   87 | struct UiTextLayout {
   88 |     float width_abs = 0, width_scale = 0;
   89 | };
   90 | class UiResources {
   91 |   public:
   92 |     explicit UiResources(const PakArchive &archive) : archive_(&archive) {
   93 |     }
   94 |     [[nodiscard]] const UiLayout *layout(const std::string &path);
   95 |     [[nodiscard]] std::optional<UiImage> image(const std::string &reference);
   96 |     // Case-insensitive lookup by the original CEGUI <Font Name=...>. The
   97 |     // returned cache is mutated by rasterization; callers own the screen size.
   98 |     [[nodiscard]] UiFont *font(const std::string &name);
   99 |     // WidgetLook PropertyDefinition initialValue from media/UI/GuiLook.looknfeel.
  100 |     [[nodiscard]] std::optional<UiWidgetImages> widget_images(const std::string &type);
  101 |     // Ordered Falagard TextComponent passes for the look (shadow/outline first,
  102 |     // main text last). Absent when the look defines none: the caller keeps its
  103 |     // single-pass fallback instead of inventing geometry.
  104 |     [[nodiscard]] std::optional<std::vector<UiTextPass>> widget_text_passes(
  105 |         const std::string &type);
  106 |     [[nodiscard]] std::optional<UiTextLayout> widget_text_layout(const std::string &type);
  107 |     // PropertyDefinition initialValue for the look ("" when absent).
```

