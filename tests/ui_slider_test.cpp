#include "torchlight/ui_skin.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
void eq(float a,float b,const char* message){require(std::isfinite(a)&&std::abs(a-b)<1e-5F,message);}
}
int main(int argc,char** argv){try {
    require(argc<=2,"usage: ui_slider_test [original-pak.zip]");
    const UiRect parent{100,50,255,25};
    eq(ui_slider_value_from_thumb(100,parent,24),0,"left endpoint");
    eq(ui_slider_value_from_thumb(331,parent,24),1,"right endpoint");
    eq(ui_slider_value_from_thumb(215.5F,parent,24),116.0F/231,"positive half rounds away");
    eq(ui_slider_value_from_thumb(215.49F,parent,24),115.0F/231,"below half rounds down");
    eq(ui_slider_value_from_thumb(-100,parent,24),0,"left clamp");
    eq(ui_slider_value_from_thumb(500,parent,24),1,"right clamp");
    eq(ui_slider_value_from_thumb(331,parent,24,2),2,"nonunit maximum");
    eq(ui_slider_value_from_thumb(120,parent,255),0,"zero travel");
    eq(ui_slider_value_from_thumb(120,parent,256),0,"negative travel");
    eq(ui_slider_value_from_thumb(120,parent,24,0),0,"zero maximum");
    eq(ui_slider_value_from_thumb(120,parent,24,-1),0,"negative maximum");
    eq(ui_slider_value_from_thumb(std::numeric_limits<float>::quiet_NaN(),parent,24),0,"NaN input");
    eq(ui_slider_value_from_thumb(120,parent,std::numeric_limits<float>::infinity()),0,"infinite width");
    if(argc==2) {
        PakArchive pak(argv[1]);UiResources r(pak);auto& skin=r.skin();
        UiResolvedWidget w;w.type="GuiLook/Slider";w.name="music";w.rect=parent;
        const auto thumb=[&](float value,float max=1){return skin.slider_thumb(r,w,value,max,1024,768);};
        auto t=thumb(.5F);require(bool(t),"original slider child not admitted");
        require(t->name=="music__auto_thumb__"&&t->type=="GuiLook/SliderThumb","child identity");
        eq(t->rect.width,24,"resource .095 width rounded");eq(t->rect.height,24,"resource .95 height rounded");
        eq(t->rect.x,216,"updateThumb half-value quantized position");eq(t->rect.y,50,"track top");
        eq(thumb(-1)->rect.x,100,"value low clamp");eq(thumb(2)->rect.x,331,"value high clamp");
        eq(thumb(1,2)->rect.x,216,"nonunit maximum geometry");
        require(!thumb(std::numeric_limits<float>::quiet_NaN()),"NaN geometry admitted");
        w.properties["CurrentValue"]="0.5";
        auto frame=skin.compile(r,w,{},1024,768);
        require(frame.handled&&frame.diagnostics.empty()&&frame.draws.size()==2,"track then thumb compile");
        require(frame.states==std::vector<std::string>{"Enabled","Normal"},"parent and child state order");
        eq(frame.draws.back().destination.x,216,"compiled thumb position");
        w.enabled=false;frame=skin.compile(r,w,{},1024,768);
        require(frame.states==std::vector<std::string>{"Disabled","Disabled"},"disabled child inheritance");
        w.enabled=true;w.properties["VerticalSlider"]="True";
        require(!thumb(.5F),"vertical outside reviewed scope");
        frame=skin.compile(r,w,{},1024,768);
        require(std::find(frame.diagnostics.begin(),frame.diagnostics.end(),"automatic-children-not-instantiated:1")!=frame.diagnostics.end(),"unknown shape diagnostic lost");
        w.properties.erase("VerticalSlider");w.properties["ReversedDirection"]="True";
        require(!thumb(.5F),"reversed outside reviewed scope");
        w.properties.clear();w.rect={10,20,510,50};t=thumb(.5F);
        require(bool(t),"resized slider");eq(t->rect.width,48,"resource-relative resized width");
        eq(t->rect.height,48,"resource-relative resized height");eq(t->rect.x,241,"resized position");
    }
    std::cout<<"PASS "<<checks<<" slider checks (pure math/resource compiler, no GL)\n";return 0;
}catch(const std::exception& e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
