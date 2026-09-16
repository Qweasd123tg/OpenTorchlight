#include "torchlight/ui_layout.hpp"
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
            result.widgets_[static_cast<std::size_t>(parent)].properties[key] =
                attr(node, "Value"); // LAST wins
        }
    }
    if (result.widgets_.empty())
        xml_error("layout without windows");
    return result;
}
std::string UiResolvedWidget::property(const std::string &key) const {
    const auto i = properties.find(key);
    return i == properties.end() ? std::string{} : i->second;
}
UiTextStyle UiResolvedWidget::text_style() const {
    UiTextStyle style;
    const auto h = upper(property("HorzFormatting"));
    style.wrap = h.find("WORDWRAP") != std::string::npos;
    if (h.find("CENTRE") != std::string::npos || h.find("CENTER") != std::string::npos)
        style.horizontal = UiTextHorizontal::centre;
    else if (h.find("RIGHT") != std::string::npos)
        style.horizontal = UiTextHorizontal::right;
    const auto v = upper(property("VertFormatting"));
    if (v == "VERTCENTRED" || v == "CENTRE" || v == "CENTER" || v == "CENTREALIGNED")
        style.vertical = UiTextVertical::centre;
    else if (v == "BOTTOMALIGNED" || v == "BOTTOM")
        style.vertical = UiTextVertical::bottom;
    return style;
}
std::vector<UiResolvedWidget> UiLayout::resolve(int width, int height) const {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("invalid UI viewport");
    // Portable small-window policy: letterbox the original pixel-offset layout.
    const float w = static_cast<float>(std::max(width, 1024)),
                h = static_cast<float>(std::max(height, 768));
    const float zoom = std::min(width / w, height / h);
    const float ox = (width - w * zoom) * .5F, oy = (height - h * zoom) * .5F;
    std::vector<UiResolvedWidget> result;
    for (const auto &node : widgets_) {
        const auto parent = node.parent < 0 ? UiRect{0, 0, w, h}
                                            : result.at(static_cast<std::size_t>(node.parent)).rect;
        UiResolvedWidget v;
        v.name = node.name;
        v.type = node.type;
        v.parent = node.parent;
        v.properties = node.properties;
        v.rect = parent;
        v.text = node.property("Text");
        v.font = node.property("Font");
        v.callback = node.property("onClick");
        v.image = node.property("Image");
        if (v.image.empty())
            v.image = node.property("NormalImage");
        // Opening a page makes its root visible; child visibility is retained.
        v.visible = (node.parent < 0 || upper(node.property("Visible")) != "FALSE") &&
                    (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].visible);
        v.enabled = upper(node.property("Disabled")) != "TRUE" &&
                    upper(node.property("Enabled")) != "FALSE" &&
                    (node.parent < 0 || result[static_cast<std::size_t>(node.parent)].enabled);
        if (const auto area = node.property("UnifiedAreaRect"); !area.empty()) {
            const auto a = numbers(area);
            if (a.size() != 8)
                xml_error("area must contain eight values");
            v.rect = {parent.x + parent.width * a[0] + a[1], parent.y + parent.height * a[2] + a[3],
                      parent.width * (a[4] - a[0]) + a[5] - a[1],
                      parent.height * (a[6] - a[2]) + a[7] - a[3]};
        } else {
            if (const auto p = node.property("UnifiedPosition"); !p.empty()) {
                const auto a = numbers(p);
                if (a.size() != 4)
                    xml_error("position must contain four values");
                v.rect.x = parent.x + parent.width * a[0] + a[1];
                v.rect.y = parent.y + parent.height * a[2] + a[3];
            }
            if (const auto s = node.property("UnifiedSize"); !s.empty()) {
                const auto a = numbers(s);
                if (a.size() != 4)
                    xml_error("size must contain four values");
                v.rect.width = parent.width * a[0] + a[1];
                v.rect.height = parent.height * a[2] + a[3];
            }
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
        v.rect.x = ox + v.rect.x * zoom;
        v.rect.y = oy + v.rect.y * zoom;
        v.rect.width *= zoom;
        v.rect.height *= zoom;
        v.clip = {ox + v.clip.x * zoom, oy + v.clip.y * zoom,
                  v.clip.width * zoom, v.clip.height * zoom};
    }
    return result;
}
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
                auto base = entry.name.substr(0, entry.name.find_last_of("/\\") + 1);
                const auto *texture = archive_->find_normalized(file);
                if (!texture)
                    texture = archive_->find_normalized(base + file);
                if (!texture) {
                    diagnostics_.push_back("imageset texture absent: " + entry.name);
                    continue;
                }
                for (const auto &n : nodes)
                    if (n.tag == "Image") {
                        UiImage image{texture->name, dimension(n, "XPos"), dimension(n, "YPos"),
                                      dimension(n, "Width"), dimension(n, "Height")};
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
std::optional<UiWidgetImages> UiResources::widget_images(const std::string &type) {
    if (type.empty())
        return std::nullopt;
    if (!looknfeel_loaded_) {
        looknfeel_loaded_ = true;
        const auto *entry = archive_->find_normalized("media/UI/GuiLook.looknfeel");
        if (entry) {
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
                    UiWidgetImages images;
                    // Only direct defaults, never similarly named properties
                    // of a Child/ImagerySection or a later WidgetLook.
                    for (const auto &n : nodes) {
                        if (n.parent != 0 || n.tag != "PropertyDefinition") continue;
                        const auto key = attr(n, "name"), value = attr(n, "initialValue");
                        if (key == "NormalImage") images.normal = value;
                        else if (key == "HoverImage") images.hover = value;
                        else if (key == "PushedImage") images.pushed = value;
                        else if (key == "DisabledImage") images.disabled = value;
                    }
                    widget_images_.insert_or_assign(upper(attr(nodes.front(), "name")),
                                                    std::move(images));
                }
            } catch (const std::exception &e) {
                diagnostics_.push_back("GuiLook.looknfeel: " + std::string(e.what()));
            }
        }
    }
    const auto it = widget_images_.find(upper(type));
    if (it == widget_images_.end())
        return std::nullopt;
    return it->second;
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
} // namespace torchlight
