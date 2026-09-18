#include "torchlight/ui_skin.hpp"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <set>
#include <stdexcept>

namespace torchlight {
namespace {
using Node = UiSkinNode;
std::string attr(const Node& n, const char* key) {
    const auto i = n.attributes.find(key);
    return i == n.attributes.end() ? std::string{} : i->second;
}
float number(const std::string& s, float fallback = 0) {
    if (s.empty()) return fallback;
    float f = 0;
    const auto r = std::from_chars(s.data(), s.data() + s.size(), f);
    if (r.ec != std::errc{} || r.ptr != s.data() + s.size() || !std::isfinite(f))
        throw std::runtime_error("invalid finite number: " + s);
    return f;
}
bool truth(const std::string& s, bool fallback = false) {
    if (s.empty()) return fallback;
    return s == "True" || s == "true" || s == "TRUE" || s == "1";
}
UiColour argb(const std::string& s) {
    unsigned v = 0;
    const auto r = std::from_chars(s.data(), s.data() + s.size(), v, 16);
    if (s.size() != 8 || r.ec != std::errc{} || r.ptr != s.data() + s.size())
        throw std::runtime_error("invalid ARGB colour: " + s);
    return {float((v >> 16) & 255) / 255, float((v >> 8) & 255) / 255,
            float(v & 255) / 255, float((v >> 24) & 255) / 255};
}
UiColours multiply(UiColours a, const UiColours& b) {
    for (std::size_t i = 0; i < 4; ++i)
        for (std::size_t j = 0; j < 4; ++j) a[i][j] *= b[i][j];
    return a;
}
std::string image_ref(const Node& n) {
    return "set:" + attr(n, "imageset") + " image:" + attr(n, "image");
}
} // namespace
UiColours ui_white() { return {{{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}}; }
UiColours ui_colours(const std::string& s) {
    if (s.empty()) return ui_white();
    if (s.size() == 8) { const auto c = argb(s); return {{c,c,c,c}}; }
    UiColours out = ui_white();
    const char* keys[] = {"tl:", "tr:", "bl:", "br:"};
    for (std::size_t i = 0; i < 4; ++i) {
        const auto p = s.find(keys[i]);
        if (p == std::string::npos) throw std::runtime_error("incomplete colour rectangle");
        out[i] = argb(s.substr(p + 3, 8));
    }
    return out;
}
UiColours ui_colour_subrectangle(const UiColours& c,float left,float right,float top,float bottom) {
    // Bundled ColourRect::getColourAtPoint @0xc7000 / getSubRectangle @0xc7360.
    // No clamp: source extrapolates outside [0,1], too. Keep float operation order.
    UiColours out;
    const std::array<float,4> xs{left,right,left,right},ys{top,top,bottom,bottom};
    for(std::size_t corner=0;corner<4;++corner)for(std::size_t channel=0;channel<4;++channel) {
        const float h1=(c[1][channel]-c[0][channel])*xs[corner]+c[0][channel];
        const float h2=(c[3][channel]-c[2][channel])*xs[corner]+c[2][channel];
        out[corner][channel]=(h2-h1)*ys[corner]+h1;
    }
    return out;
}
UiRect ui_intersect(UiRect a, UiRect b) {
    const float x = std::max(a.x,b.x), y = std::max(a.y,b.y);
    return {x,y,std::max(0.0F,std::min(a.x+a.width,b.x+b.width)-x),
                std::max(0.0F,std::min(a.y+a.height,b.y+b.height)-y)};
}
float ui_pixel_aligned(float value) {
    const float rounded=std::trunc(value+(value>0.0F?0.5F:-0.5F));
    return rounded==0.0F?0.0F:rounded; // cvttss2si/cvtsi2ss yields positive zero
}

struct UiSkin::Impl {
    std::vector<Node> nodes;
    std::vector<std::vector<int>> children;
    struct Look {
        int node = -1;
        std::map<std::string, std::string> defaults;
        std::map<std::string, int> states, sections;
        std::size_t auto_children = 0;
    };
    struct Mapping { std::string look, renderer; };
    std::map<std::string, Look> looks;
    std::map<std::string, Mapping> mappings;
    explicit Impl(const PakArchive& archive) {
        if (const auto* e = archive.find_normalized("media/UI/GuiLook.looknfeel"))
            nodes = ui_skin_xml(archive.read(*e));
        children.resize(nodes.size());
        for (std::size_t i=0; i<nodes.size(); ++i) {
            const auto p = nodes[i].parent;
            if (p >= 0) children.at(static_cast<std::size_t>(p)).push_back(static_cast<int>(i));
        }
        for (std::size_t i=0; i<nodes.size(); ++i) if (nodes[i].tag == "WidgetLook") {
            Look l; l.node=static_cast<int>(i);
            for (const int c : children[i]) {
                const auto& n = nodes[c]; const auto name = attr(n,"name");
                // CEGUI attributes are case-sensitive. Do not silently repair
                // initialvalue / Value in the game's data (some are deliberately unused).
                if (n.tag == "PropertyDefinition") l.defaults[name]=attr(n,"initialValue");
                else if (n.tag == "Property") l.defaults[name]=attr(n,"value");
                else if (n.tag == "StateImagery") l.states[name]=c;
                else if (n.tag == "ImagerySection") l.sections[name]=c;
                else if (n.tag == "Child") ++l.auto_children;
            }
            looks.emplace(attr(nodes[i],"name"), std::move(l));
        }
        if (const auto* e = archive.find_normalized("media/UI/GuiLookSkin.scheme"))
            for (const auto& n : ui_skin_xml(archive.read(*e)))
                if (n.tag == "FalagardMapping")
                    mappings[attr(n,"WindowType")]={attr(n,"LookNFeel"),attr(n,"Renderer")};
    }
    const Mapping* mapping(const std::string& type) const {
        const auto m=mappings.find(type);
        return m == mappings.end() ? nullptr : &m->second;
    }
    const Look* look(const std::string& type) const {
        const auto* m=mapping(type);
        const auto i=looks.find(m ? m->look : type);
        return i==looks.end()?nullptr:&i->second;
    }
    struct Compiler {
        const Impl& s; UiResources& resources; const UiResolvedWidget& w;
        const Look& own; int width,height; UiSkinFrame out;
        UiRect viewport;
        std::string prop(const std::string& name) const {
            // Runtime Image / Text / Font values are authoritative even when
            // their original XML properties remain unchanged.
            if (name=="Image") return w.image;
            if (name=="Text") return w.text;
            if (name=="Font" && !w.font.empty()) return w.font;
            const auto i=w.properties.find(name);
            if(i!=w.properties.end()) return i->second;
            const auto d=own.defaults.find(name);
            return d==own.defaults.end()?std::string{}:d->second;
        }
        int child(int n,const char* tag) const {
            for(int c:s.children.at(n)) if(s.nodes[c].tag==tag) return c;
            return -1;
        }
        std::string format(int n, const char* direct, const char* indirect,
                           const char* fallback) const {
            if(const int c=child(n,direct);c>=0) return attr(s.nodes[c],"type");
            if(const int c=child(n,indirect);c>=0) {
                const auto v=prop(attr(s.nodes[c],"name"));
                return v.empty()?std::string(fallback):v;
            }
            return fallback;
        }
        UiColours colours(int n) const {
            for(int c:s.children.at(n)) {
                const auto& x=s.nodes[c];
                if(x.tag=="ColourProperty" || x.tag=="ColourRectProperty")
                    return ui_colours(prop(attr(x,"name")));
                if(x.tag=="Colours") return {{argb(attr(x,"topLeft")),argb(attr(x,"topRight")),
                                                argb(attr(x,"bottomLeft")),argb(attr(x,"bottomRight"))}};
            }
            return ui_white();
        }
        float dim(int n,unsigned depth=0) const {
            if(depth>32) throw std::runtime_error("dimension-depth-limit");
            const auto& x=s.nodes.at(n); float v=0;
            if(x.tag=="Dim") {
                // Falagard_xmlHandler::elementAnyDimEnd @0x1d0a20:
                // after a top-level BaseDim is closed the stack is empty.
                // A sibling DimOperator cannot attach to it; its BaseDim
                // operand becomes the NEW root. Last root wins, not a sum.
                bool found=false;
                for(int c:s.children[n]) {
                    if(s.nodes[c].tag=="DimOperator") {
                        for(int operand:s.children[c]) {v=dim(operand,depth+1);found=true;}
                    } else {v=dim(c,depth+1);found=true;}
                }
                if(!found)throw std::runtime_error("dimension-without-base");
                return v;
            }
            if(x.tag=="AbsoluteDim") v=number(attr(x,"value"));
            else if(x.tag=="UnifiedDim") {
                const auto type=attr(x,"type");
                if(type!="Width" && type!="Height") throw std::runtime_error("unsupported-unified-axis:"+type);
                v=number(attr(x,"scale"))*(type=="Width"?w.rect.width:w.rect.height)+number(attr(x,"offset"));
            } else if(x.tag=="ImageDim") {
                const auto image=resources.image(image_ref(x));
                if(!image) throw std::runtime_error("missing-dimension-image:"+image_ref(x));
                const auto m=image->scaled_metrics(width,height); const auto d=attr(x,"dimension");
                if(d=="Width") v=m[0]; else if(d=="Height") v=m[1];
                else if(d=="XOffset") v=m[2]; else if(d=="YOffset") v=m[3];
                else throw std::runtime_error("unsupported-image-dimension:"+d);
            } else if(x.tag=="PropertyDim") {
                if(!attr(x,"widget").empty()) throw std::runtime_error("requires-child:"+attr(x,"widget"));
                const auto raw=prop(attr(x,"name"));
                if(raw.empty()) throw std::runtime_error("missing-dimension-property:"+attr(x,"name"));
                // Scalar properties only. Unified-dimension properties need
                // PropertyHelper::stringToUDim and are not guessed as floats.
                if(!attr(x,"type").empty()) throw std::runtime_error("unified-property-dimension");
                v=number(raw);
            } else if(x.tag=="WidgetDim") {
                if(!attr(x,"widget").empty()) throw std::runtime_error("requires-child:"+attr(x,"widget"));
                const auto d=attr(x,"dimension");
                if(d=="Width"||d=="RightEdge") v=w.rect.width;
                else if(d=="Height"||d=="BottomEdge") v=w.rect.height;
                else if(d=="LeftEdge"||d=="TopEdge") v=0;
                else throw std::runtime_error("unsupported-widget-dimension:"+d);
            } else if(x.tag=="FontDim") {
                auto name=attr(x,"font");if(name.empty())name=prop("Font");if(name.empty())name="Serif";
                auto* f=resources.font(name);if(!f||!f->valid())throw std::runtime_error("font-dimension-unavailable:"+name);
                f->notify_screen_size(float(width),float(height));
                if(attr(x,"type")!="LineSpacing")throw std::runtime_error("unsupported-font-dimension:"+attr(x,"type"));
                v=f->line_height()+number(attr(x,"padding"));
            } else throw std::runtime_error("unsupported-dimension:"+x.tag);
            for(int c:s.children[n]) if(s.nodes[c].tag=="DimOperator") {
                if(s.children[c].size()!=1) throw std::runtime_error("invalid-dimension-operator");
                const float rhs=dim(s.children[c][0],depth+1); const auto op=attr(s.nodes[c],"op");
                if(op=="Add")v+=rhs;else if(op=="Subtract")v-=rhs;else if(op=="Multiply")v*=rhs;
                else if(op=="Divide"&&rhs!=0)v/=rhs;else throw std::runtime_error("invalid-dimension-operation:"+op);
            }
            if(!std::isfinite(v)||std::abs(v)>1e7F)throw std::runtime_error("dimension-out-of-range");
            return v;
        }
        UiRect area(int component) const {
            const int a=child(component,"Area");if(a<0)throw std::runtime_error("component-without-area");
            float left=0,top=0,ww=w.rect.width,hh=w.rect.height;
            std::optional<float> right,bottom;
            for(int d:s.children[a]) {
                const auto kind=attr(s.nodes[d],"type"); const auto value=dim(d);
                if(kind=="LeftEdge")left=value;else if(kind=="TopEdge")top=value;
                else if(kind=="Width")ww=value;else if(kind=="Height")hh=value;
                else if(kind=="RightEdge")right=value;else if(kind=="BottomEdge")bottom=value;
                else throw std::runtime_error("unsupported-area-dimension:"+kind);
            }
            return {w.rect.x+left,w.rect.y+top,right?*right-left:ww,bottom?*bottom-top:hh};
        }
        void emit_image(const std::string& reference, UiRect r, UiRect clip,
                        UiColours colour, const std::string& section) {
            if(reference.empty())return; // explicit empty image is legal
            const auto image=resources.image(reference);
            if(!image)throw std::runtime_error("missing-image:"+reference);
            const auto m=image->scaled_metrics(width,height);
            r.x+=m[2];r.y+=m[3];
            auto g=clip_ui_image(r,{image->x,image->y,image->width,image->height},&clip);
            if(!g)return;
            auto& d=g->destination;
            const float right=ui_pixel_aligned(d.x+d.width),bottom=ui_pixel_aligned(d.y+d.height);
            d.x=ui_pixel_aligned(d.x);d.y=ui_pixel_aligned(d.y);d.width=right-d.x;d.height=bottom-d.y;
            if(d.width<=0||d.height<=0)return;
            UiSkinDraw q; q.destination=d;q.source=g->source;q.clip=clip;q.colours=colour;
            q.texture=image->texture_path;q.section=section;
            if(out.draws.size()>=16384)throw std::runtime_error("quad-budget-exceeded");
            out.draws.push_back(std::move(q));
        }
        void formatted(const std::string& reference, UiRect r, UiRect clip, UiColours colour,
                       const std::string& horz,const std::string& vert,const std::string& section) {
            if(reference.empty())return;
            const auto image=resources.image(reference);
            if(!image)throw std::runtime_error("missing-image:"+reference);
            auto m=image->scaled_metrics(width,height);float iw=m[0],ih=m[1];
            if(r.width<=0||r.height<=0||iw<=0||ih<=0)return;
            float x=r.x,y=r.y;std::size_t nx=1,ny=1;
            if(horz=="Stretched")iw=r.width;
            else if(horz=="Tiled")nx=static_cast<std::size_t>((r.width+(iw-1))/iw);
            else if(horz=="CentreAligned")x+=ui_pixel_aligned((r.width-iw)*.5F);
            else if(horz=="RightAligned")x+=r.width-iw;
            else if(horz!="LeftAligned")throw std::runtime_error("unsupported-horizontal-format:"+horz);
            if(vert=="Stretched")ih=r.height;
            else if(vert=="Tiled")ny=static_cast<std::size_t>((r.height+(ih-1))/ih);
            else if(vert=="CentreAligned")y+=ui_pixel_aligned((r.height-ih)*.5F);
            else if(vert=="BottomAligned")y+=r.height-ih;
            else if(vert!="TopAligned")throw std::runtime_error("unsupported-vertical-format:"+vert);
            if(nx>16384||ny>16384||nx*ny>16384)throw std::runtime_error("tile-budget-exceeded");
            for(std::size_t row=0;row<ny;++row)for(std::size_t col=0;col<nx;++col) {
                const auto c=((horz=="Tiled"&&col+1==nx)||(vert=="Tiled"&&row+1==ny))?
                    ui_intersect(clip,r):clip;
                emit_image(reference,{x+float(col)*iw,y+float(row)*ih,iw,ih},c,colour,section);
            }
        }
        void frame(int n,UiRect r,UiRect clip,UiColours colour,const std::string& section) {
            // CEGUI::FrameComponent::render_impl: natural corners, stretched
            // edges, formatted background. Offsets affect both edge lengths
            // and image origins. No invented nine-slice border thickness.
            std::map<std::string,std::pair<std::string,std::array<float,4>>> parts;
            for(int c:s.children[n])if(s.nodes[c].tag=="Image") {
                const auto ref=image_ref(s.nodes[c]);const auto im=resources.image(ref);
                if(!im)throw std::runtime_error("missing-frame-image:"+ref);
                parts[attr(s.nodes[c],"type")]={ref,im->scaled_metrics(width,height)};
            }
            if(r.width<=0||r.height<=0)return;
            const bool monochrome=colour[0]==colour[1]&&colour[0]==colour[2]&&colour[0]==colour[3];
            auto piece_colours=[&](UiRect rect,const std::array<float,4>& m) {
                if(monochrome)return colour;
                // RenderCache applies window translation AFTER colours are cached.
                // Recover window-local coordinates, retaining the component
                // origin (not normalising to the component itself; 0x1adc38+).
                const float left=(rect.x-w.rect.x+m[2])/r.width,
                            top=(rect.y-w.rect.y+m[3])/r.height;
                return ui_colour_subrectangle(colour,left,left+rect.width/r.width,
                                               top,top+rect.height/r.height);
            };
            float to=0,bo=0,lo=0,ro=0,tw=r.width,bw=r.width,lh=r.height,rh=r.height;
            auto draw=[&](const char* name,auto geometry,auto adjust) {
                const auto p=parts.find(name);if(p==parts.end())return;
                const auto m=p->second.second;const auto rect=ui_intersect(geometry(m),r);
                adjust(m);emit_image(p->second.first,rect,clip,piece_colours(rect,m),section+":"+name);
            };
            draw("TopLeftCorner",[&](auto m){return UiRect{r.x,r.y,m[0],m[1]};},[&](auto m){to+=m[0]+m[2];lo+=m[1]+m[3];tw-=to;lh-=lo;});
            draw("TopRightCorner",[&](auto m){return UiRect{r.x+r.width-m[0],r.y,m[0],m[1]};},[&](auto m){ro+=m[1]+m[3];tw-=m[0]-m[2];rh-=ro;});
            draw("BottomLeftCorner",[&](auto m){return UiRect{r.x,r.y+r.height-m[1],m[0],m[1]};},[&](auto m){bo+=m[0]+m[2];bw-=bo;lh-=m[1]-m[3];});
            draw("BottomRightCorner",[&](auto m){return UiRect{r.x+r.width-m[0],r.y+r.height-m[1],m[0],m[1]};},[&](auto m){bw-=m[0]-m[2];rh-=m[1]-m[3];});
            UiRect bg=r;
            draw("TopEdge",[&](auto m){return UiRect{r.x+to,r.y,tw,m[1]};},[&](auto m){bg.y+=m[1]+m[3];bg.height-=m[1]+m[3];});
            draw("BottomEdge",[&](auto m){return UiRect{r.x+bo,r.y+r.height-m[1],bw,m[1]};},[&](auto m){bg.height-=m[1]-m[3];});
            draw("LeftEdge",[&](auto m){return UiRect{r.x,r.y+lo,m[0],lh};},[&](auto m){bg.x+=m[0]+m[2];bg.width-=m[0]+m[2];});
            draw("RightEdge",[&](auto m){return UiRect{r.x+r.width-m[0],r.y+ro,m[0],rh};},[&](auto m){bg.width-=m[0]-m[2];});
            if(const auto p=parts.find("Background");p!=parts.end())
                formatted(p->second.first,bg,clip,piece_colours(bg,p->second.second),format(n,"HorzFormat","HorzFormatProperty","Stretched"),
                          format(n,"VertFormat","VertFormatProperty","Stretched"),section+":Background");
        }
        void component(int n,UiRect clip,UiColours colour,const std::string& section) {
            const auto r=area(n);const auto& node=s.nodes[n];colour=multiply(colour,colours(n));
            if(node.tag=="FrameComponent") { frame(n,r,clip,colour,section);return; }
            if(node.tag=="ImageryComponent") {
                std::string ref;
                if(const int c=child(n,"Image");c>=0)ref=image_ref(s.nodes[c]);
                else if(const int c=child(n,"ImageProperty");c>=0)ref=prop(attr(s.nodes[c],"name"));
                formatted(ref,r,clip,colour,format(n,"HorzFormat","HorzFormatProperty","Stretched"),
                          format(n,"VertFormat","VertFormatProperty","Stretched"),section);return;
            }
            if(node.tag=="TextComponent") {
                UiSkinDraw q;q.kind=UiSkinDraw::Kind::text;q.destination=r;q.clip=clip;q.colours=colour;q.section=section;
                q.text=w.text;q.font=prop("Font");if(q.font.empty())q.font="Serif";
                if(const int c=child(n,"Text");c>=0) {
                    const auto t=attr(s.nodes[c],"string"),f=attr(s.nodes[c],"font");
                    if(!t.empty()) q.text=t;
                    if(!f.empty()) q.font=f;
                }
                if(const int c=child(n,"TextProperty");c>=0)q.text=prop(attr(s.nodes[c],"name"));
                if(const int c=child(n,"FontProperty");c>=0)q.font=prop(attr(s.nodes[c],"name"));
                auto h=format(n,"HorzFormat","HorzFormatProperty","LeftAligned");
                auto v=format(n,"VertFormat","VertFormatProperty","TopAligned");
                if(h.find("Justified")!=std::string::npos)throw std::runtime_error("justified-text-not-implemented");
                q.text_style.wrap=h.find("WordWrap")!=std::string::npos;
                if(h.find("Centre")!=std::string::npos)q.text_style.horizontal=UiTextHorizontal::centre;
                else if(h.find("Right")!=std::string::npos)q.text_style.horizontal=UiTextHorizontal::right;
                if(v.find("Centre")!=std::string::npos)q.text_style.vertical=UiTextVertical::centre;
                else if(v.find("Bottom")!=std::string::npos)q.text_style.vertical=UiTextVertical::bottom;
                if(!q.text.empty())out.draws.push_back(std::move(q));
            }
        }
        void state(const std::string& name) {
            const auto st=own.states.find(name);
            if(st==own.states.end()){out.diagnostics.push_back("missing-state:"+name);return;}
            out.states.push_back(name);
            const auto clip=attr(s.nodes[st->second],"clipped")=="false"?viewport:(w.has_clip?w.clip:viewport);
            auto alpha=ui_white();for(auto& c:alpha)c[3]*=w.effective_alpha;
            auto layers=s.children[st->second];
            std::stable_sort(layers.begin(),layers.end(),[&](int a,int b){return number(attr(s.nodes[a],"priority"))<number(attr(s.nodes[b],"priority"));});
            for(int l:layers)if(s.nodes[l].tag=="Layer")for(int ref:s.children[l])if(s.nodes[ref].tag=="Section") {
                if(number(attr(s.nodes[l],"priority"))!=0) {
                    out.diagnostics.push_back("nonzero-layer-priority-not-implemented");continue;
                }
                const auto external=attr(s.nodes[ref],"look");const auto sec=attr(s.nodes[ref],"section");
                const auto source=external.empty()?&own:s.look(external);
                if(!source||!source->sections.count(sec)){out.diagnostics.push_back("missing-section:"+external+":"+sec);continue;}
                const auto n=source->sections.at(sec);
                const auto sc=attr(s.nodes[ref],"clipped")=="false"?viewport:clip;
                try {
                    const auto c=multiply(multiply(alpha,colours(ref)),colours(n));
                    // Bundled ImagerySection::render @0x1b1790 keeps three
                    // separate vectors: images, text, frames (not XML order).
                    for(const char* tag:{"ImageryComponent","TextComponent","FrameComponent"})
                        for(int k:s.children[n])if(s.nodes[k].tag==tag) {
                            const auto before=out.draws.size();
                            try{component(k,sc,c,sec);}catch(const std::exception& e){out.draws.resize(before);out.diagnostics.push_back(sec+":"+e.what());}
                        }
                } catch(const std::exception& e){out.diagnostics.push_back(sec+":"+e.what());}
            }
        }
    };
};
UiSkin::UiSkin(const PakArchive& a):impl_(std::make_unique<Impl>(a)){}
UiSkin::~UiSkin()=default;
std::string UiSkin::renderer(const std::string& type) const {
    const auto* m=impl_->mapping(type);return m?m->renderer:std::string{};
}
std::vector<std::string> UiSkin::states(const std::string& type) const {
    std::vector<std::string> r;const auto* l=impl_->look(type);if(l)for(const auto& x:l->states)r.push_back(x.first);return r;
}
std::size_t UiSkin::automatic_children(const std::string& type) const {
    const auto* l=impl_->look(type);return l?l->auto_children:0;
}
UiSkinFrame UiSkin::compile(UiResources& resources,const UiResolvedWidget& w,UiSkinState input,int width,int height) const {
    const auto* look=impl_->look(w.type);const auto render=renderer(w.type);
    if(!look||render.empty())return {};
    Impl::Compiler c{*impl_,resources,w,*look,width,height,{}, {0,0,float(width),float(height)}};
    const std::set<std::string> supported={"Falagard/Button","Falagard/ToggleButton","Falagard/Default","Falagard/StaticImage","Falagard/Slider","Falagard/Scrollbar","Falagard/Listbox"};
    if(!supported.count(render)){c.out.diagnostics.push_back("unsupported-renderer:"+render);return c.out;}
    c.out.handled=true;
    if(!w.visible||width<=0||height<=0)return c.out;
    if(look->auto_children)c.out.diagnostics.push_back("automatic-children-not-instantiated:"+std::to_string(look->auto_children));
    if(render=="Falagard/Button"||render=="Falagard/ToggleButton") {
        const bool selected=input.selected||truth(c.prop("Selected"));
        const std::string prefix=render=="Falagard/ToggleButton"&&selected?"Selected":"";
        std::string state=!w.enabled?"Disabled":input.pushed?(input.hover?"Pushed":"PushedOff"):(input.hover?"Hover":"Normal");
        if(!look->states.count(prefix+state))state=!w.enabled?"Disabled":(input.hover?"Hover":"Normal");
        c.state(prefix+state);
    } else if(render=="Falagard/StaticImage") {
        const bool frame=truth(c.prop("FrameEnabled"),true),bg=truth(c.prop("BackgroundEnabled"),true);
        const std::string enabled=w.enabled?"Enabled":"Disabled";
        if(frame)c.state(enabled+"Frame");
        if(bg)c.state((frame?"WithFrame":"NoFrame")+enabled+"Background");
        c.state(enabled);
        if(!w.image.empty())c.state(!frame&&look->states.count("NoFrameImage")?"NoFrameImage":"WithFrameImage");
    } else c.state(w.enabled?"Enabled":"Disabled");
    // The compiler above expands sections; RenderCache::render @0xf48a0
    // then visits the image cache before the text cache FOR THIS WINDOW.
    // All supported active source layers currently have priority zero.
    // Do not reintroduce the old global "images of every window then text" bug.
    std::stable_partition(c.out.draws.begin(),c.out.draws.end(),[](const UiSkinDraw& q){
        return q.kind==UiSkinDraw::Kind::image;
    });
    return std::move(c.out);
}
} // namespace torchlight
