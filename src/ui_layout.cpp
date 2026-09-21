#include "torchlight/ui_layout.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include "torchlight/ui_skin.hpp"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <string_view>

namespace torchlight {
namespace {
struct Node {
    std::string tag;
    std::string text;
    std::map<std::string, std::string> attrs;
    int parent = -1;
};
void xml_error(const char *s) {
    throw std::runtime_error(std::string("UI XML: ") + s);
}
void append_utf8(std::string &out, unsigned v) {
    if (v == 0 || v > 0x10ffff || (v >= 0xd800 && v <= 0xdfff))
        xml_error("invalid character");
    if (v < 0x80)
        out += static_cast<char>(v);
    else if (v < 0x800) {
        out += static_cast<char>(0xc0 | (v >> 6));
        out += static_cast<char>(0x80 | (v & 63));
    } else if (v < 0x10000) {
        out += static_cast<char>(0xe0 | (v >> 12));
        out += static_cast<char>(0x80 | ((v >> 6) & 63));
        out += static_cast<char>(0x80 | (v & 63));
    } else {
        out += static_cast<char>(0xf0 | (v >> 18));
        out += static_cast<char>(0x80 | ((v >> 12) & 63));
        out += static_cast<char>(0x80 | ((v >> 6) & 63));
        out += static_cast<char>(0x80 | (v & 63));
    }
}
std::string decode(const std::vector<std::uint8_t> &bytes) {
    if (bytes.size() > 8U * 1024U * 1024U)
        xml_error("document too large");
    if (bytes.size() >= 2 && bytes[0] == 0xff && bytes[1] == 0xfe) {
        if (bytes.size() % 2)
            xml_error("odd UTF16 size");
        std::string out;
        for (std::size_t i = 2; i < bytes.size(); i += 2) {
            unsigned c = bytes[i] | (unsigned(bytes[i + 1]) << 8);
            if (c >= 0xd800 && c <= 0xdbff) {
                if (i + 3 >= bytes.size())
                    xml_error("truncated surrogate");
                unsigned lo = bytes[i + 2] | (unsigned(bytes[i + 3]) << 8);
                if (lo < 0xdc00 || lo > 0xdfff)
                    xml_error("invalid surrogate");
                c = 0x10000 + ((c - 0xd800) << 10) + (lo - 0xdc00);
                i += 2;
            }
            append_utf8(out, c);
        }
        return out;
    }
    std::size_t start =
        bytes.size() >= 3 && bytes[0] == 0xef && bytes[1] == 0xbb && bytes[2] == 0xbf ? 3 : 0;
    return {bytes.begin() + static_cast<std::ptrdiff_t>(start), bytes.end()};
}
std::string unescape(std::string_view s) {
    std::string out;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] != '&') {
            out += s[i];
            continue;
        }
        const auto end = s.find(';', i);
        if (end == s.npos || end - i > 16)
            xml_error("invalid entity");
        const auto key = s.substr(i + 1, end - i - 1);
        if (key == "amp")
            out += '&';
        else if (key == "lt")
            out += '<';
        else if (key == "gt")
            out += '>';
        else if (key == "quot")
            out += '"';
        else if (key == "apos")
            out += '\'';
        else if (!key.empty() && key.front() == '#') {
            unsigned code = 0;
            auto number = key.substr(1);
            int base = 10;
            if (!number.empty() && (number.front() == 'x' || number.front() == 'X')) {
                base = 16;
                number.remove_prefix(1);
            }
            const auto r =
                std::from_chars(number.data(), number.data() + number.size(), code, base);
            if (r.ec != std::errc{} || r.ptr != number.data() + number.size())
                xml_error("bad character entity");
            append_utf8(out, code);
        } else
            xml_error("DTD/external entities are not supported");
        i = end;
    }
    return out;
}
std::vector<Node> parse_xml(const std::vector<std::uint8_t> &bytes) {
    const auto text = decode(bytes);
    std::vector<Node> nodes;
    std::vector<int> stack;
    std::size_t p = 0;
    const auto skip = [&] {
        while (p < text.size() && std::isspace(static_cast<unsigned char>(text[p])))
            ++p;
    };
    const auto name = [&]() {
        const auto start = p;
        while (p < text.size() &&
               (std::isalnum(static_cast<unsigned char>(text[p])) || text[p] == '_' ||
                text[p] == '-' || text[p] == ':' || text[p] == '.'))
            ++p;
        if (start == p)
            xml_error("expected name");
        return text.substr(start, p - start);
    };
    while (p < text.size()) {
        const auto next = text.find('<', p);
        if (next == text.npos)
            break;
        if (!stack.empty() && nodes[static_cast<std::size_t>(stack.back())].tag == "Property") {
            std::string body;
            for (auto i = p; i < next; ++i) {
                // XML line-end normalization precedes character references.
                if (text[i] == '\r') {
                    if (i + 1 < next && text[i + 1] == '\n') ++i;
                    body += '\n';
                } else body += text[i];
            }
            nodes[static_cast<std::size_t>(stack.back())].text += unescape(body);
        }
        p = next;
        if (text.compare(p, 4, "<!--") == 0) {
            auto end = text.find("-->", p + 4);
            if (end == text.npos)
                xml_error("unclosed comment");
            p = end + 3;
            continue;
        }
        if (text.compare(p, 2, "<?") == 0) {
            auto end = text.find("?>", p + 2);
            if (end == text.npos)
                xml_error("unclosed declaration");
            p = end + 2;
            continue;
        }
        if (text.compare(p, 2, "<!") == 0)
            xml_error("DTD/CDATA is unsupported");
        ++p;
        bool closing = p < text.size() && text[p] == '/';
        if (closing)
            ++p;
        auto tag = name();
        skip();
        if (closing) {
            if (stack.empty() || nodes[static_cast<std::size_t>(stack.back())].tag != tag)
                xml_error("unmatched close");
            if (p >= text.size() || text[p++] != '>')
                xml_error("bad close");
            stack.pop_back();
            continue;
        }
        Node node;
        node.tag = std::move(tag);
        node.parent = stack.empty() ? -1 : stack.back();
        while (p < text.size() && text[p] != '>' && text[p] != '/') {
            auto key = name();
            skip();
            if (p >= text.size() || text[p++] != '=')
                xml_error("missing equals");
            skip();
            if (p >= text.size() || (text[p] != '\'' && text[p] != '"'))
                xml_error("unquoted attribute");
            const auto quote = text[p++];
            const auto end = text.find(quote, p);
            if (end == text.npos)
                xml_error("unclosed attribute");
            if (!node.attrs.emplace(key, unescape(std::string_view(text).substr(p, end - p)))
                     .second)
                xml_error("duplicate attribute");
            p = end + 1;
            skip();
        }
        bool closed = p < text.size() && text[p] == '/';
        if (closed)
            ++p;
        if (p >= text.size() || text[p++] != '>')
            xml_error("unfinished tag");
        if (nodes.size() >= 10000 || stack.size() >= 64)
            xml_error("document complexity limit");
        nodes.push_back(std::move(node));
        if (!closed)
            stack.push_back(static_cast<int>(nodes.size() - 1));
    }
    if (!stack.empty() || nodes.empty())
        xml_error("incomplete document");
    return nodes;
}
std::string attr(const Node &n, const std::string &key) {
    const auto i = n.attrs.find(key);
    return i == n.attrs.end() ? std::string{} : i->second;
}
std::string upper(std::string s) {
    for (auto &c : s)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}
std::vector<float> numbers(const std::string &s) {
    std::vector<float> out;
    const char *p = s.data();
    const char *end = p + s.size();
    while (p < end) {
        while (p < end && (*p == '{' || *p == '}' || *p == ',' ||
                           std::isspace(static_cast<unsigned char>(*p))))
            ++p;
        if (p == end)
            break;
        float v = 0;
        const auto parsed = std::from_chars(p, end, v);
        if (parsed.ec != std::errc{} || parsed.ptr == p || !std::isfinite(v))
            xml_error("bad unified dimension");
        out.push_back(v);
        p = parsed.ptr;
        if (out.size() > 8)
            xml_error("too many dimension values");
    }
    return out;
}
float dimension(const Node &n, const std::string &key) {
    const auto list = numbers(attr(n, key));
    if (list.size() != 1 || list[0] < 0)
        xml_error("invalid image region");
    return list[0];
}

// Production adapter for the immutable resource tree. Event subscription,
// dynamic slot userData and CEGUI object lifetimes are separate contracts.
class LayoutFunctions final : public UiFunctionTree {
  public:
    explicit LayoutFunctions(std::vector<UiWidget> &widgets) : widgets_(widgets), children_(widgets.size()) {
        for (std::size_t i = 0; i < widgets.size(); ++i)
            if (widgets[i].parent >= 0)
                children_.at(static_cast<std::size_t>(widgets[i].parent)).push_back(i);
    }
    std::size_t child_count(Node n) const override { return children_[n].size(); }
    Node child(Node n, std::size_t i) const override { return children_[n][i]; }
    bool has_click_property(Node n) const override { return widgets_[n].properties.count("onClick") != 0; }
    std::string click_property(Node n) const override { return widgets_[n].property("onClick"); }
    void set_function(Node n, UiLayoutFunction value) noexcept override { widgets_[n].layout_function = value; }
  private:
    std::vector<UiWidget> &widgets_;
    std::vector<std::vector<Node>> children_;
};
} // namespace
std::string UiWidget::property(const std::string &key) const {
    const auto i = properties.find(key);
    return i == properties.end() ? std::string{} : i->second;
}
UiLayout UiLayout::parse(const std::vector<std::uint8_t> &bytes) {
    UiLayout result;
    const auto nodes = parse_xml(bytes);
    std::vector<int> parent_window(nodes.size(), -1);
    for (std::size_t n = 0; n < nodes.size(); ++n) {
        const auto &node = nodes[n];
        const auto parent =
            node.parent < 0 ? -1 : parent_window[static_cast<std::size_t>(node.parent)];
        parent_window[n] = parent;
        if (node.tag == "Window") {
            UiWidget widget;
            widget.name = attr(node, "Name");
            widget.type = attr(node, "Type");
            widget.parent = parent;
            if (widget.name.empty())
                xml_error("window without Name");
            result.widgets_.push_back(std::move(widget));
            parent_window[n] = static_cast<int>(result.widgets_.size() - 1);
        } else if (node.tag == "Property" && parent >= 0) {
            const auto key = attr(node, "Name");
            // original-code: CEGUI 0.6.2 reads the case-sensitive Name
            // attribute and ignores a Property whose resulting name is empty.
            if (key.empty())
                continue;
            // original-code: shipped GUILayout_xmlHandler::elementPropertyStart
            // @0xe4e80 sets a nonempty Value immediately. Otherwise text()
            // @0xe3560 accumulates the body; elementPropertyEnd @0xe3090 sets it.
            // Full adapter boundary: research/mainmenu-controller-painter.md.
            const auto value = attr(node, "Value");
            result.widgets_[static_cast<std::size_t>(parent)].properties[key] =
                value.empty() ? node.text : value; // LAST wins
        }
    }
    if (result.widgets_.empty())
        xml_error("layout without windows");
    LayoutFunctions bindings(result.widgets_);
    for (std::size_t i = 0; i < result.widgets_.size(); ++i)
        if (result.widgets_[i].parent < 0)
            map_ui_functions(bindings, i);
    return result;
}
UiLayout UiLayout::from_widgets(std::vector<UiWidget> widgets) {
    if (widgets.empty()) throw std::invalid_argument("layout without windows");
    for (std::size_t i = 0; i < widgets.size(); ++i) {
        if (widgets[i].name.empty()) throw std::invalid_argument("window without name");
        if (widgets[i].parent < -1 ||
            (widgets[i].parent >= 0 && static_cast<std::size_t>(widgets[i].parent) >= i))
            throw std::invalid_argument("invalid window parent order");
    }
    UiLayout result;
    result.widgets_ = std::move(widgets);
    return result;
}
std::string UiResolvedWidget::property(const std::string &key) const {
    const auto i = properties.find(key);
    return i == properties.end() ? std::string{} : i->second;
}
std::optional<std::size_t> ui_target_at_position(
    const std::vector<UiResolvedWidget>& widgets, float x, float y) {
    std::optional<std::size_t> target;
    for (std::size_t i = 0; i < widgets.size(); ++i) {
        const auto& w = widgets[i];
        // visible/enabled already include ancestors. A fully transparent
        // window still participates: original targeting never tests alpha.
        if (!w.visible || !w.enabled || upper(w.property("MousePassThroughEnabled")) == "TRUE" ||
            !w.rect.contains(x, y) || (w.has_clip && !w.clip.contains(x, y))) continue;
        if (!target || w.paint_order >= widgets[*target].paint_order) target = i;
    }
    return target;
}
UiTextStyle UiResolvedWidget::text_style() const {
    UiTextStyle style;
    // resource-derived: layouts align StaticText-like widgets with
    // HorzTextFormatting (Left/Centre/RightAligned + WordWrap variants, 56
    // uses) and VertFormatting (Top/Centre/BottomAligned, 32 uses). Bare
    // HorzFormatting never occurs in the shipped layouts.
    auto h = upper(property("HorzTextFormatting"));
    if (h.empty()) h = upper(property("HorzFormatting")); // fallback-port injection only
    style.wrap = h.find("WORDWRAP") != std::string::npos;
    if (h.find("CENTRE") != std::string::npos || h.find("CENTER") != std::string::npos)
        style.horizontal = UiTextHorizontal::centre;
    else if (h.find("RIGHT") != std::string::npos)
        style.horizontal = UiTextHorizontal::right;
    const auto v = upper(property("VertFormatting"));
    if (v.find("CENTRE") != std::string::npos || v.find("CENTER") != std::string::npos)
        style.vertical = UiTextVertical::centre;
    else if (v.find("BOTTOM") != std::string::npos)
        style.vertical = UiTextVertical::bottom;
    return style;
}
std::optional<UiImageGeometry> clip_ui_image(UiRect destination, UiRect source,
                                             const UiRect *clip) {
    const auto valid = [](const UiRect &r) {
        return std::isfinite(r.x) && std::isfinite(r.y) && std::isfinite(r.width) &&
               std::isfinite(r.height) && r.width > 0 && r.height > 0 &&
               std::isfinite(r.x + r.width) && std::isfinite(r.y + r.height);
    };
    if (!valid(destination) || !valid(source)) return std::nullopt;
    if (clip == nullptr) return UiImageGeometry{destination, source};
    if (!valid(*clip)) return std::nullopt;
    const float left = std::max(destination.x, clip->x);
    const float top = std::max(destination.y, clip->y);
    const float right = std::min(destination.x + destination.width, clip->x + clip->width);
    const float bottom = std::min(destination.y + destination.height, clip->y + clip->height);
    if (right <= left || bottom <= top) return std::nullopt;
    // original-code structure: intersect the destination and proportionally
    // move BOTH UV edges. Shrinking geometry alone would squeeze the image.
    const float u_per_pixel = source.width / destination.width;
    const float v_per_pixel = source.height / destination.height;
    UiRect cropped{source.x + (left - destination.x) * u_per_pixel,
                   source.y + (top - destination.y) * v_per_pixel,
                   (right - left) * u_per_pixel, (bottom - top) * v_per_pixel};
    if (!valid(cropped)) return std::nullopt;
    return UiImageGeometry{{left, top, right - left, bottom - top}, cropped};
}
std::vector<UiResolvedWidget> UiLayout::resolve(int width, int height) const {
    return resolve(width, height, 1.0F);
}
std::vector<UiResolvedWidget> UiLayout::resolve(int width, int height,
                                                float screen_scale_ratio) const {
    UiLayoutState state;
    state.offset_ratio = screen_scale_ratio;
    return resolve(width, height, state);
}
std::vector<UiResolvedWidget> UiLayout::resolve(int width, int height, const UiLayoutState &state) const {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("invalid UI viewport");
    // Library stage: CEGUI resolves relative dimensions against the actual
    // parent, not a letterbox. The game stage is explicit: CGameUI::
    // convertToScreenScale @0xa83ed0 scales POSITION/SIZE offsets uniformly
    // by height/768 (false) or width/1024 (true). Fonts have their own scale.
    // Evaluate from immutable XML: never rescale last frame's rectangles.
    // Small-window readability (original: netbook mode) stays open.
    const float w = static_cast<float>(width), h = static_cast<float>(height);
    const float screen_scale_ratio = state.offset_ratio.value_or(
        state.screen_scale == UiScreenScale::height
            ? ui_screen_ratio(width, height, UiScreenScaleRatio::y_ratio)
            : state.screen_scale == UiScreenScale::width
                ? ui_screen_ratio(width, height, UiScreenScaleRatio::x_ratio) : 1.0F);
    if (!std::isfinite(screen_scale_ratio) || screen_scale_ratio <= 0.0F)
        throw std::invalid_argument("invalid screen scale ratio");
    std::vector<UiResolvedWidget> result;
    for (std::size_t node_index = 0; node_index < widgets_.size(); ++node_index) {
        const auto& node = widgets_[node_index];
        const auto parent = node.parent < 0 ? UiRect{0, 0, w, h}
                                            : result.at(static_cast<std::size_t>(node.parent)).rect;
        UiResolvedWidget v;
        v.name = node.name;
        v.type = node.type;
        v.parent = node.parent;
        v.properties = node.properties;
        v.has_clip = true;
        float alpha = 1.0F;
        if (const auto raw = node.property("Alpha"); !raw.empty()) {
            const auto parsed = std::from_chars(raw.data(), raw.data() + raw.size(), alpha);
            if (parsed.ec != std::errc{} || parsed.ptr != raw.data() + raw.size() ||
                !std::isfinite(alpha)) xml_error("invalid Alpha");
        }
        v.effective_alpha = std::clamp(alpha, 0.0F, 1.0F);
        if (node.parent >= 0 && upper(node.property("InheritsAlpha")) != "FALSE")
            v.effective_alpha *= result[static_cast<std::size_t>(node.parent)].effective_alpha;
        v.rect = parent;
        v.text = node.property("Text");
        v.font = node.property("Font");
        v.callback = node.property("onClick");
        v.layout_function = node.layout_function;
        v.image = node.property("Image");
        if (v.image.empty())
            v.image = node.property("NormalImage");
        // Opening a page makes its root visible; child visibility is retained.
        const auto visibility = state.visibility.find(node.name);
        const bool local_visible = visibility == state.visibility.end()
            ? (node.parent < 0 || upper(node.property("Visible")) != "FALSE")
            : visibility->second;
        v.visible = local_visible &&
                    (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].visible);
        v.enabled = upper(node.property("Disabled")) != "TRUE" &&
                    upper(node.property("Enabled")) != "FALSE" &&
                    (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].enabled);
        if (const auto area = node.property("UnifiedAreaRect"); !area.empty()) {
            const auto parsed = numbers(area);
            if (parsed.size() != 8)
                xml_error("area must contain eight values");
            // original-code: CGameUI::convertToScreenScale @0xa83ed0 scales
            // the four UDim offsets by one ratio, scales preserved. Applied
            // here to freshly parsed pristine values, never written back.
            // Size subtlety (audit cross-check): the original scales
            // getPosition()/getSize() UVector2s, and vendored
            // CEGUI::Window::getSize @0x111bd0 computes the size offset as
            // max-min with subss BEFORE the scale mult. So the size term is
            // (max-min)*ratio, NOT max*ratio-min*ratio (float rounding
            // differs). Position offsets are scaled directly.
            std::array<float, 8> a{parsed[0], parsed[1], parsed[2], parsed[3],
                                   parsed[4], parsed[5], parsed[6], parsed[7]};
            ui_scale_area_offsets(a, screen_scale_ratio);
            const float size_x = (parsed[5] - parsed[1]) * screen_scale_ratio;
            const float size_y = (parsed[7] - parsed[3]) * screen_scale_ratio;
            v.rect = {parent.x + parent.width * a[0] + a[1], parent.y + parent.height * a[2] + a[3],
                      parent.width * (a[4] - a[0]) + size_x,
                      parent.height * (a[6] - a[2]) + size_y};
        } else {
            if (const auto p = node.property("UnifiedPosition"); !p.empty()) {
                const auto parsed = numbers(p);
                if (parsed.size() != 4)
                    xml_error("position must contain four values");
                std::array<float, 4> a{parsed[0], parsed[1], parsed[2], parsed[3]};
                ui_scale_vector_offsets(a, screen_scale_ratio);
                v.rect.x = parent.x + parent.width * a[0] + a[1];
                v.rect.y = parent.y + parent.height * a[2] + a[3];
            }
            if (const auto s = node.property("UnifiedSize"); !s.empty()) {
                const auto parsed = numbers(s);
                if (parsed.size() != 4)
                    xml_error("size must contain four values");
                std::array<float, 4> a{parsed[0], parsed[1], parsed[2], parsed[3]};
                ui_scale_vector_offsets(a, screen_scale_ratio);
                v.rect.width = parent.width * a[0] + a[1];
                v.rect.height = parent.height * a[2] + a[3];
            }
        }
        if (std::find(state.zero_position_nodes.begin(), state.zero_position_nodes.end(),
                      node_index) != state.zero_position_nodes.end()) {
            v.rect.x = parent.x;
            v.rect.y = parent.y;
        }
        const auto horizontal = upper(node.property("HorizontalAlignment"));
        const auto vertical = upper(node.property("VerticalAlignment"));
        if (horizontal == "CENTRE" || horizontal == "CENTER")
            v.rect.x += (parent.width - v.rect.width) * .5F;
        else if (horizontal == "RIGHT")
            v.rect.x += parent.width - v.rect.width;
        if (vertical == "CENTRE" || vertical == "CENTER")
            v.rect.y += (parent.height - v.rect.height) * .5F;
        else if (vertical == "BOTTOM")
            v.rect.y += parent.height - v.rect.height;
        for (auto x : {v.rect.x, v.rect.y, v.rect.width, v.rect.height})
            if (!std::isfinite(x) || std::abs(x) > 1e7F)
                xml_error("layout bounds out of range");
        // Bounded subset: clip to viewport and each clipping ancestor. A child
        // may opt out of parent clipping, but never of the framebuffer bounds.
        const UiRect ancestor = node.parent < 0 || upper(node.property("ClippedByParent")) == "FALSE"
                                    ? UiRect{0, 0, w, h}
                                    : result[static_cast<std::size_t>(node.parent)].clip;
        const float x = std::max(v.rect.x, ancestor.x), y = std::max(v.rect.y, ancestor.y);
        v.clip = {x, y, std::max(0.0F, std::min(v.rect.x + v.rect.width,
                       ancestor.x + ancestor.width) - x),
                       std::max(0.0F, std::min(v.rect.y + v.rect.height,
                       ancestor.y + ancestor.height) - y)};
        result.push_back(std::move(v));
    }
    for (auto &v : result) {
        v.clip = {std::max(v.clip.x, 0.0F), std::max(v.clip.y, 0.0F),
                  std::min(v.clip.width, w - v.clip.x), std::min(v.clip.height, h - v.clip.y)};
        if (v.clip.width < 0) v.clip.width = 0;
        if (v.clip.height < 0) v.clip.height = 0;
    }
    // original-code: bundled Window::addWindowToDrawList @0x1163d0 inserts
    // ordinary siblings before the AlwaysOnTop group. Initial add order:
    // each child's entire subtree is visited before moving on, and AlwaysOnTop
    // siblings come later in the draw list. Iterative traversal avoids
    // unbounded C++ recursion on untrusted XML.
    std::vector<std::vector<std::size_t>> children(result.size() + 1);
    for (std::size_t i = 0; i < result.size(); ++i) {
        const auto parent = result[i].parent;
        children[parent < 0 ? result.size() : static_cast<std::size_t>(parent)].push_back(i);
    }
    for (auto &siblings : children)
        std::stable_partition(siblings.begin(), siblings.end(), [&](std::size_t i) {
            return upper(result[i].property("AlwaysOnTop")) != "TRUE";
        });
    // Window::moveToFront_impl(false) @0x116550: first raise ancestors,
    // then remove/reinsert this window at the end of its own Z-order group.
    // ZOrderingEnabled gates reordering, independently of visibility.
    for (const auto& name : state.move_to_front) {
        const auto found = std::find_if(result.begin(), result.end(),
            [&](const auto& widget) { return widget.name == name; });
        if (found == result.end()) continue;
        std::vector<std::size_t> lineage;
        for (auto index = static_cast<std::size_t>(found - result.begin());;) {
            lineage.push_back(index);
            if (result[index].parent < 0) break;
            index = static_cast<std::size_t>(result[index].parent);
        }
        for (auto entry = lineage.rbegin(); entry != lineage.rend(); ++entry) {
            const auto index = *entry;
            const auto parent = result[index].parent;
            if (parent < 0 || upper(result[index].property("ZOrderingEnabled")) == "FALSE") continue;
            auto& siblings = children[static_cast<std::size_t>(parent)];
            siblings.erase(std::find(siblings.begin(), siblings.end(), index));
            const bool on_top = upper(result[index].property("AlwaysOnTop")) == "TRUE";
            const auto position = on_top ? siblings.end() :
                std::find_if(siblings.begin(), siblings.end(), [&](std::size_t sibling) {
                    return upper(result[sibling].property("AlwaysOnTop")) == "TRUE";
                });
            siblings.insert(position, index);
        }
    }
    std::vector<std::size_t> pending(children.back().rbegin(), children.back().rend());
    std::size_t order = 0;
    while (!pending.empty()) {
        const auto i = pending.back(); pending.pop_back();
        result[i].paint_order = order++;
        pending.insert(pending.end(), children[i].rbegin(), children[i].rend());
    }
    return result;
}
float pixel_align_ui(float value) noexcept {
    // NaN takes the -0.5 branch (ucomiss ja falls through) and converts to
    // INT_MIN, exactly like the original cvttss2si; infinities convert the
    // same way. std::trunc reproduces truncation-toward-zero.
    const float shifted = value + (value > 0.0F ? 0.5F : -0.5F);
    if (!std::isfinite(shifted))
        return -2147483648.0F;
    const float truncated = std::trunc(shifted);
    if (truncated <= -2147483648.0F || truncated >= 2147483648.0F)
        return -2147483648.0F;
    return truncated;
}
std::array<float, 2> ui_image_render_offset(const UiImage &image, float screen_width,
                                            float screen_height) noexcept {
    const float horz =
        image.auto_scaled ? screen_width / image.native_horz : 1.0F;
    const float vert =
        image.auto_scaled ? screen_height / image.native_vert : 1.0F;
    return {pixel_align_ui(image.offset_x * horz), pixel_align_ui(image.offset_y * vert)};
}
void UiResources::attach_window_renderer(const std::string& name, const std::string& type) {
    if (window_renderers_.count(name)) throw std::invalid_argument("duplicate live UI renderer instance");
    const auto renderer = type == "DefaultWindow" ? std::string{} : skin().renderer(type);
    // Name registration ends at destroy(), while factory objects remain in
    // the dead pool. A replacement may legitimately reuse the same name.
    ++window_factories_[name];
    if (!renderer.empty()) window_renderers_.emplace(name, RendererInstance{type, renderer, true});
}
void UiResources::detach_window_renderer(const std::string& name) {
    const auto it = window_renderers_.find(name);
    if (it == window_renderers_.end()) return;
    it->second.attached = false;
    // RenderCache owns commands and copied text, not the shared texture/font.
    const auto listeners = cache_invalidators_;
    for (const auto& [token, invalidate] : listeners) { (void)token; invalidate(name); }
}
void UiResources::destroy_window_renderer(const std::string& name) {
    window_renderers_.erase(name);
}
void UiResources::destroy_window_factory(const std::string& name) {
    const auto it = window_factories_.find(name);
    if (it != window_factories_.end() && --it->second == 0) window_factories_.erase(it);
}
std::optional<std::string> UiResources::window_renderer(const std::string& name) const {
    const auto it = window_renderers_.find(name);
    if (it == window_renderers_.end()) return std::nullopt;
    return it->second.attached ? it->second.renderer : std::string{};
}
std::size_t UiResources::subscribe_window_cache(CacheInvalidator callback) {
    const auto token = ++next_cache_invalidator_;
    cache_invalidators_.emplace(token, std::move(callback));
    return token;
}
void UiResources::unsubscribe_window_cache(std::size_t token) { cache_invalidators_.erase(token); }
const UiLayout *UiResources::layout(const std::string &path) {
    if (const auto it = layouts_.find(path); it != layouts_.end())
        return &it->second;
    const auto *entry = archive_->find_normalized(path);
    if (!entry)
        return nullptr;
    return &layouts_.emplace(path, UiLayout::parse(archive_->read(*entry))).first->second;
}
std::optional<UiImage> UiResources::image(const std::string &reference) {
    if (reference.empty())
        return std::nullopt;
    if (!images_loaded_) {
        images_loaded_ = true;
        for (const auto &entry : archive_->entries()) {
            const auto upper_name = upper(entry.name);
            if (upper_name.size() < 9 || upper_name.substr(upper_name.size() - 9) != ".IMAGESET")
                continue;
            try {
                const auto nodes = parse_xml(archive_->read(entry));
                if (nodes.front().tag != "Imageset")
                    continue;
                const auto set = attr(nodes.front(), "Name"),
                           file = attr(nodes.front(), "Imagefile");
                // original-code: per-imageset NativeHorzRes/NativeVertRes and
                // AutoScaled feed CEGUI::Imageset::notifyScreenResolution
                // (factors screen/native per axis when auto-scaled, else 1).
                // Defaults 640x480 are constructor immediates in the shipped
                // libCEGUIBase.so.1; every shipped set declares its own.
                const auto native = [&](const char *key, float fallback) {
                    const auto text = attr(nodes.front(), key);
                    if (text.empty())
                        return fallback;
                    const auto list = numbers(text);
                    if (list.size() != 1)
                        xml_error("invalid imageset native resolution");
                    return list[0];
                };
                const float native_horz = native("NativeHorzRes", 640.0F);
                const float native_vert = native("NativeVertRes", 480.0F);
                const bool auto_scaled = upper(attr(nodes.front(), "AutoScaled")) == "TRUE";
                if (native_horz <= 0 || native_vert <= 0)
                    xml_error("invalid imageset native resolution");
                auto base = entry.name.substr(0, entry.name.find_last_of("/\\") + 1);
                const auto *texture = archive_->find_normalized(file);
                if (!texture)
                    texture = archive_->find_normalized(base + file);
                if (!texture) {
                    diagnostics_.push_back("imageset texture absent: " + entry.name);
                    continue;
                }
                // Signed: XOffset/YOffset are routinely negative (e.g. -8).
                const auto offset = [&](const Node &node, const char *key) {
                    const auto text = attr(node, key);
                    if (text.empty())
                        return 0.0F;
                    const auto list = numbers(text);
                    if (list.size() != 1)
                        xml_error("invalid image offset");
                    return list[0];
                };
                for (const auto &n : nodes)
                    if (n.tag == "Image") {
                        UiImage image{texture->name, dimension(n, "XPos"), dimension(n, "YPos"),
                                      dimension(n, "Width"), dimension(n, "Height"),
                                      offset(n, "XOffset"), offset(n, "YOffset"), native_horz,
                                      native_vert, auto_scaled};
                        images_[set + "/" + attr(n, "Name")] = std::move(image);
                    }
            } catch (const std::exception &e) {
                diagnostics_.push_back(entry.name + ": " + e.what());
            }
        }
    }
    const auto set_pos = reference.find("set:"), image_pos = reference.find("image:");
    if (set_pos == std::string::npos || image_pos == std::string::npos)
        return std::nullopt;
    const auto token = [&](std::size_t p) {
        const auto end = reference.find_first_of(" \t\r\n", p);
        return reference.substr(p, end == std::string::npos ? end : end - p);
    };
    const auto key = token(set_pos + 4) + "/" + token(image_pos + 6);
    const auto it = images_.find(key);
    return it == images_.end() ? std::nullopt : std::optional<UiImage>(it->second);
}
namespace {
// resource-derived: evaluates one Falagard edge/size Dim inside a TextComponent
// Area as (absolute pixels + scale * widget extent). Children forms observed
// in GuiLook.looknfeel: AbsoluteDim, UnifiedDim(scale, Width|Height) with an
// optional nested DimOperator, and direct DimOperator. Anything else fails the
// whole look so the caller keeps its single-pass fallback instead of rendering
// invented geometry.
bool dim_value(const std::vector<Node> &nodes, std::size_t dim, float extent,
               float &absolute, float &scale, std::string &error) {
    absolute = 0;
    scale = 0;
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].parent != static_cast<int>(dim)) continue;
        if (nodes[i].tag == "AbsoluteDim") {
            const auto raw = attr(nodes[i], "value");
            float v = 0;
            const auto parsed =
                std::from_chars(raw.data(), raw.data() + raw.size(), v);
            if (parsed.ec != std::errc{} || parsed.ptr != raw.data() + raw.size() ||
                !std::isfinite(v)) {
                error = "bad AbsoluteDim";
                return false;
            }
            absolute += v;
        } else if (nodes[i].tag == "UnifiedDim") {
            const auto type = attr(nodes[i], "scale");
            const auto kind = attr(nodes[i], "type");
            if (kind != "Width" && kind != "Height") {
                error = "unsupported UnifiedDim";
                return false;
            }
            float s = 0;
            const auto parsed =
                std::from_chars(type.data(), type.data() + type.size(), s);
            if (parsed.ec != std::errc{} || parsed.ptr != type.data() + type.size() ||
                !std::isfinite(s)) {
                error = "bad UnifiedDim scale";
                return false;
            }
            scale += s;
            for (std::size_t k = 0; k < nodes.size(); ++k) {
                if (nodes[k].parent != static_cast<int>(i)) continue;
                if (nodes[k].tag != "DimOperator") {
                    error = "unsupported UnifiedDim child";
                    return false;
                }
                const auto op = attr(nodes[k], "op");
                bool have_operand = false;
                for (std::size_t m = 0; m < nodes.size(); ++m) {
                    if (nodes[m].parent != static_cast<int>(k) ||
                        nodes[m].tag != "AbsoluteDim")
                        continue;
                    const auto raw = attr(nodes[m], "value");
                    float v = 0;
                    const auto operand =
                        std::from_chars(raw.data(), raw.data() + raw.size(), v);
                    if (operand.ec != std::errc{} ||
                        operand.ptr != raw.data() + raw.size() || !std::isfinite(v)) {
                        error = "bad DimOperator operand";
                        return false;
                    }
                    have_operand = true;
                    if (op == "Add") absolute += v;
                    else if (op == "Subtract") absolute -= v;
                    else {
                        error = "unsupported DimOperator";
                        return false;
                    }
                    break;
                }
                if (!have_operand) {
                    error = "DimOperator without operand";
                    return false;
                }
            }
        } else if (nodes[i].tag == "DimOperator") {
            const auto op = attr(nodes[i], "op");
            bool have_operand = false;
            for (std::size_t k = 0; k < nodes.size(); ++k) {
                if (nodes[k].parent != static_cast<int>(i) ||
                    nodes[k].tag != "AbsoluteDim")
                    continue;
                const auto raw = attr(nodes[k], "value");
                float v = 0;
                const auto operand =
                    std::from_chars(raw.data(), raw.data() + raw.size(), v);
                if (operand.ec != std::errc{} || operand.ptr != raw.data() + raw.size() ||
                    !std::isfinite(v)) {
                    error = "bad DimOperator operand";
                    return false;
                }
                have_operand = true;
                if (op == "Add") absolute += v;
                else if (op == "Subtract") absolute -= v;
                else {
                    error = "unsupported DimOperator";
                    return false;
                }
                break;
            }
            if (!have_operand) {
                error = "DimOperator without operand";
                return false;
            }
        } else {
            error = "unsupported Dim child";
            return false;
        }
    }
    static_cast<void>(extent);
    return true;
}
} // namespace
void UiResources::ensure_looknfeel() {
    if (looknfeel_loaded_)
        return;
    looknfeel_loaded_ = true;
    const auto *entry = archive_->find_normalized("media/UI/GuiLook.looknfeel");
    if (!entry)
        return;
    try {
        const auto text = decode(archive_->read(*entry));
        std::size_t position = 0;
        while (true) {
            const auto start = text.find("<WidgetLook", position);
            if (start == std::string::npos) break;
            const auto section_end = text.find("</WidgetLook>", start);
            if (section_end == std::string::npos)
                throw std::runtime_error("unterminated WidgetLook");
            position = section_end + 13;
            const auto section = text.substr(start, position - start);
            const auto nodes = parse_xml({section.begin(), section.end()});
            if (nodes.empty() || nodes.front().tag != "WidgetLook") continue;
            const auto look = upper(attr(nodes.front(), "name"));
            UiWidgetImages images;
            std::map<std::string, std::string> defaults;
            // Only direct defaults, never similarly named properties
            // of a Child/ImagerySection or a later WidgetLook.
            for (const auto &n : nodes) {
                if (n.parent != 0 || n.tag != "PropertyDefinition") continue;
                const auto key = attr(n, "name"), value = attr(n, "initialValue");
                if (key == "NormalImage") images.normal = value;
                else if (key == "HoverImage") images.hover = value;
                else if (key == "PushedImage") images.pushed = value;
                else if (key == "DisabledImage") images.disabled = value;
                if (!key.empty()) defaults[key] = value;
            }
            widget_images_.insert_or_assign(look, std::move(images));
            look_defaults_.insert_or_assign(look, std::move(defaults));
            // Ordered TextComponent passes in document order (shadow first).
            // Areas are widget-relative: absolute pixels plus a multiple of the
            // widget extent (Checkbox labels start past the box). Width comes
            // from the first component (Width, or RightEdge minus LeftEdge).
            std::vector<UiTextPass> passes;
            UiTextLayout text_layout;
            bool have_layout = false;
            std::string failure;
            for (std::size_t t = 0; t < nodes.size() && failure.empty(); ++t) {
                if (nodes[t].tag != "TextComponent") continue;
                UiTextPass pass;
                bool have_x = false, have_y = false;
                float left_abs = 0, left_scale = 0, top_abs = 0, top_scale = 0;
                float width_abs = 0, width_scale = 0, right_abs = 0, right_scale = 0;
                bool have_width = false, have_right = false;
                for (std::size_t i = 0; i < nodes.size() && failure.empty(); ++i) {
                    if (nodes[i].parent != static_cast<int>(t)) continue;
                    if (nodes[i].tag == "Area") {
                        for (std::size_t d = 0; d < nodes.size() && failure.empty(); ++d) {
                            if (nodes[d].parent != static_cast<int>(i) ||
                                nodes[d].tag != "Dim")
                                continue;
                            const auto kind = attr(nodes[d], "type");
                            float absolute = 0, scale = 0;
                            if (kind == "LeftEdge") {
                                if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
                                left_abs = absolute;
                                left_scale = scale;
                                have_x = true;
                            } else if (kind == "TopEdge") {
                                if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
                                top_abs = absolute;
                                top_scale = scale;
                                have_y = true;
                            } else if (kind == "Width") {
                                if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
                                width_abs = absolute;
                                width_scale = scale;
                                have_width = true;
                            } else if (kind == "RightEdge") {
                                if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
                                right_abs = absolute;
                                right_scale = scale;
                                have_right = true;
                            } else if (kind == "Height" || kind == "BottomEdge") {
                                float ignored_abs = 0, ignored_scale = 0;
                                if (!dim_value(nodes, d, 0, ignored_abs, ignored_scale, failure))
                                    break;
                            } else {
                                failure = "unsupported Area Dim";
                                break;
                            }
                        }
                    } else if (nodes[i].tag == "ColourProperty") {
                        pass.colour_property = attr(nodes[i], "name");
                    } else if (nodes[i].tag == "HorzFormat") {
                        // resource-derived: Checkbox LeftAligned, StandardButton
                        // CentreAligned; StaticText/ItemText use *Property and
                        // stay deferred to the widget (pass fields unset).
                        const auto format = upper(attr(nodes[i], "type"));
                        if (format.find("CENTRE") != std::string::npos ||
                            format.find("CENTER") != std::string::npos)
                            pass.horz = UiTextHorizontal::centre;
                        else if (format.find("RIGHT") != std::string::npos)
                            pass.horz = UiTextHorizontal::right;
                        else if (format.find("LEFT") != std::string::npos ||
                                 format.find("JUSTIFIED") != std::string::npos)
                            pass.horz = UiTextHorizontal::left;
                    } else if (nodes[i].tag == "VertFormat") {
                        const auto format = upper(attr(nodes[i], "type"));
                        if (format.find("CENTRE") != std::string::npos ||
                            format.find("CENTER") != std::string::npos)
                            pass.vert = UiTextVertical::centre;
                        else if (format.find("BOTTOM") != std::string::npos)
                            pass.vert = UiTextVertical::bottom;
                        else if (format.find("TOP") != std::string::npos)
                            pass.vert = UiTextVertical::top;
                    }
                }
                if (!failure.empty()) break;
                if (!have_x || !have_y) {
                    failure = "TextComponent without LeftEdge/TopEdge";
                    break;
                }
                pass.dx = left_abs;
                pass.x_scale = left_scale;
                pass.dy = top_abs;
                pass.y_scale = top_scale;
                if (!have_layout) {
                    if (have_width) {
                        text_layout.width_abs = width_abs;
                        text_layout.width_scale = width_scale;
                    } else if (have_right) {
                        text_layout.width_abs = right_abs - left_abs;
                        text_layout.width_scale = right_scale - left_scale;
                    } else {
                        failure = "TextComponent without Width/RightEdge";
                        break;
                    }
                    have_layout = true;
                }
                passes.push_back(std::move(pass));
            }
            if (failure.empty()) {
                if (!passes.empty()) {
                    widget_text_.insert_or_assign(look, std::move(passes));
                    if (have_layout)
                        widget_text_origin_.insert_or_assign(look, text_layout);
                }
            } else {
                diagnostics_.push_back("GuiLook.looknfeel " + look + ": " + failure);
            }
        }
    } catch (const std::exception &e) {
        diagnostics_.push_back("GuiLook.looknfeel: " + std::string(e.what()));
    }
}
std::optional<UiWidgetImages> UiResources::widget_images(const std::string &type) {
    if (type.empty())
        return std::nullopt;
    ensure_looknfeel();
    const auto it = widget_images_.find(upper(type));
    if (it == widget_images_.end())
        return std::nullopt;
    return it->second;
}
std::optional<std::vector<UiTextPass>> UiResources::widget_text_passes(
    const std::string &type) {
    if (type.empty())
        return std::nullopt;
    ensure_looknfeel();
    const auto it = widget_text_.find(upper(type));
    if (it == widget_text_.end())
        return std::nullopt;
    return it->second;
}
std::optional<UiTextLayout> UiResources::widget_text_layout(const std::string &type) {
    if (type.empty())
        return std::nullopt;
    ensure_looknfeel();
    const auto it = widget_text_origin_.find(upper(type));
    if (it == widget_text_origin_.end())
        return std::nullopt;
    return it->second;
}
std::string UiResources::look_default(const std::string &type, const std::string &key) {
    if (type.empty() || key.empty())
        return {};
    ensure_looknfeel();
    const auto it = look_defaults_.find(upper(type));
    if (it == look_defaults_.end())
        return {};
    const auto kv = it->second.find(key);
    return kv == it->second.end() ? std::string{} : kv->second;
}
UiFont *UiResources::font(const std::string &name) {
    if (name.empty())
        return nullptr;
    if (!fonts_loaded_) {
        fonts_loaded_ = true;
        for (const auto &entry : archive_->entries()) {
            const auto upper_name = upper(entry.name);
            if (upper_name.size() < 5 || upper_name.substr(upper_name.size() - 5) != ".FONT")
                continue;
            try {
                auto definition =
                    parse_ui_font_definition(archive_->read(entry), entry.name);
                auto key = upper(definition.name);
                fonts_.emplace(std::move(key), UiFont(*archive_, std::move(definition)));
            } catch (const std::exception &e) {
                diagnostics_.push_back(entry.name + ": " + e.what());
            }
        }
    }
    const auto it = fonts_.find(upper(name));
    if (it == fonts_.end())
        return nullptr;
    return &it->second;
}
std::vector<UiSkinNode> ui_skin_xml(const std::vector<std::uint8_t>& bytes) {
    std::vector<UiSkinNode> result;
    for (const auto& node : parse_xml(bytes))
        result.push_back({node.tag, node.attrs, node.parent});
    return result;
}
UiSkin& UiResources::skin() {
    if (!skin_) skin_ = std::make_shared<UiSkin>(*archive_);
    return *skin_;
}
std::array<float, 4> UiImage::scaled_metrics(int w, int h) const {
    const float sx = auto_scaled ? static_cast<float>(w) / native_horz : 1.0F;
    const float sy = auto_scaled ? static_cast<float>(h) / native_vert : 1.0F;
    // Image::setHorz/VertScaling rounds native dimensions AND offsets.
    return {ui_pixel_aligned(width * sx), ui_pixel_aligned(height * sy),
            ui_pixel_aligned(offset_x * sx), ui_pixel_aligned(offset_y * sy)};
}
} // namespace torchlight
