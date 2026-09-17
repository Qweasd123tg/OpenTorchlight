#include "torchlight/ui_layout.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
void eq(float a, float b, const char *message) { require(std::abs(a-b) < 0.000001F, message); }
}
int main() {
    try {
        const UiRect destination{10, 20, 100, 80}, uv{.1F, .2F, .4F, .6F};
        auto q = clip_ui_image(destination, uv);
        require(q.has_value(), "unclipped image rejected");
        eq(q->destination.width, 100, "unclipped width");
        eq(q->source.x, .1F, "unclipped UV");
        UiRect clip{35, 40, 50, 40};
        q = clip_ui_image(destination, uv, &clip);
        require(q.has_value(), "visible intersection rejected");
        eq(q->destination.x, 35, "destination left"); eq(q->destination.y, 40, "destination top");
        eq(q->destination.width, 50, "destination width"); eq(q->destination.height, 40, "destination height");
        eq(q->source.x, .2F, "left UV was squeezed instead of cropped");
        eq(q->source.y, .35F, "top UV was squeezed instead of cropped");
        eq(q->source.width, .2F, "UV width"); eq(q->source.height, .3F, "UV height");
        clip = {10,20,100,80}; q=clip_ui_image(destination,uv,&clip);
        eq(q->source.width,.4F,"equal clip changed UV");
        clip = {0,0,0,0}; require(!clip_ui_image(destination,uv,&clip),"empty clip became unclipped");
        clip = {110,20,10,80}; require(!clip_ui_image(destination,uv,&clip),"touching edge rendered");
        clip = {1000,1000,10,10}; require(!clip_ui_image(destination,uv,&clip),"disjoint clip rendered");
        require(!clip_ui_image({0,0,0,10},uv),"zero image accepted");
        require(!clip_ui_image({0,0,-10,10},uv),"negative image accepted");
        require(!clip_ui_image({0,0,std::numeric_limits<float>::infinity(),10},uv),"infinite image accepted");
        // Overfill remains allowed by the HUD formula; clipping restricts its
        // visible destination, without clamping the simulation's fraction.
        clip={0,100,10,40}; q=clip_ui_image({0,80,10,60},{0,0,1,1},&clip);
        require(q.has_value(),"overfill disappeared"); eq(q->destination.y,100,"overfill leaked above parent");
        eq(q->destination.height,40,"overfill leaked below parent"); eq(q->source.y,1.0F/3.0F,"overfill UV");
        const std::string xml = "<GUILayout><Window Name='root'><Property Name='UnifiedAreaRect' Value='{{0,20},{0,20},{0,80},{0,80}}'/><Window Name='child'><Property Name='UnifiedAreaRect' Value='{{0,-10},{0,-10},{0,100},{0,100}}'/></Window><Window Name='free'><Property Name='UnifiedAreaRect' Value='{{0,-10},{0,-10},{0,100},{0,100}}'/><Property Name='ClippedByParent' Value='False'/></Window></Window></GUILayout>";
        const auto widgets=UiLayout::parse({xml.begin(),xml.end()}).resolve(100,100);
        require(widgets[1].has_clip,"resolved clip not authoritative");
        eq(widgets[1].clip.x,20,"ancestor left"); eq(widgets[1].clip.width,60,"ancestor width");
        eq(widgets[2].clip.x,10,"ClippedByParent=False lost"); eq(widgets[2].clip.width,90,"viewport clipping lost");
        std::cout << "ui_image_clip: " << checks << " assertions; bounded geometry, not full CEGUI parity\n";
        return 0;
    } catch(const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
