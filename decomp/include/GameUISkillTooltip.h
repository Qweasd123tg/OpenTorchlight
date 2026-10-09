#ifndef SKILL_TOOLTIP_HELPERS_H
#define SKILL_TOOLTIP_HELPERS_H
// Draft helpers for the complete entry; only placement currently has executed evidence.
#include "SkillTooltip.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "SkillManager.h"
#include "GameUI.h"
#include "GameUIData.h"
#include "EffectDefines.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include <CEGUI.h>
#include <math.h>
namespace skill_tooltip {
struct Size {float width,height;};
inline __attribute__((always_inline)) unsigned nextIndex(unsigned level){unsigned n=level+1u;return static_cast<int>(n)<2?2u:n;}
inline __attribute__((always_inline)) float maxSecond(float a,float b){return a>b?a:b;}
inline __attribute__((always_inline)) CEGUI::String utf8(const std::string& text){return CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str()));}
inline __attribute__((always_inline)) Size measureExtentFirst(CEGUI::Font* font,const std::string& text,float bound,int format,float padding){
 float lineHeight=font->getFontHeight()+2.0f;CEGUI::Rect rect(0,0,bound,1000.0f);
 float extent=font->getFormattedTextExtent(utf8(text),rect,static_cast<CEGUI::TextFormatting>(format),1.0f)+padding;
 int lines=static_cast<int>(font->getFormattedLineCount(utf8(text),rect,static_cast<CEGUI::TextFormatting>(format),1.0f));
 Size result={extent,float(lines)*lineHeight};return result;
}
inline __attribute__((always_inline)) Size measureLinesFirst(CEGUI::Font* font,const std::string& text,float bound,int format,float lineHeight){
 CEGUI::Rect rect(0,0,bound,1000.0f);
 int lines=static_cast<int>(font->getFormattedLineCount(utf8(text),rect,static_cast<CEGUI::TextFormatting>(format),1.0f));
 float extent=font->getFormattedTextExtent(utf8(text),rect,static_cast<CEGUI::TextFormatting>(format),1.0f)+4.0f;
 Size result={extent,float(lines)*lineHeight};return result;
}
inline __attribute__((always_inline)) void setSize(CEGUI::Window*& window,const Size& size){window->setSize(CEGUI::UVector2(CEGUI::UDim(0,size.width),CEGUI::UDim(0,size.height)));}
inline __attribute__((always_inline)) void setText(CEGUI::Window*& window,const std::string& text){window->setText(utf8(text));}
inline __attribute__((always_inline)) void setY(CEGUI::Window*& window,float y){const CEGUI::UVector2& p=window->getPosition();CEGUI::UVector2 next(CEGUI::UDim(0.0f+p.d_x.d_scale,0.0f+p.d_x.d_offset),CEGUI::UDim(0,y+0.0f));window->setPosition(next);}
inline __attribute__((always_inline)) void setTextColour(CEGUI::Window*& window,float red,float green,float blue,float alpha){CEGUI::String value=CEGUI::PropertyHelper::colourToString(CEGUI::colour(red,green,blue,alpha));window->setProperty("TextColour",value);}
inline __attribute__((always_inline)) float layoutStatRows(CGameUI*& ui,CEGUI::Window** icons,CEGUI::Window** labels,float* offsets,const float* bonuses,float y,float gap){
 float height=0.0f;int slot=0;
 for(int stat=0;stat<4;++stat){if(bonuses[stat]!=0.0f){
  icons[slot]->setVisible(true);labels[slot]->setVisible(true);
  const CEGUI::Image* image=ui->getImageFromImageSet(reinterpret_cast<const unsigned char*>(gEFFECT_STAT_MODIFIER_ICON_NAMES[stat].c_str()));
  CEGUI::String imageValue=CEGUI::PropertyHelper::imageToString(image);icons[slot]->setProperty("Image",imageValue);
  std::string text=STRINGS::GetValueAsString(static_cast<int>(::ceilf(100.0f*bonuses[stat])))+"%";
  setText(labels[slot],text);
  setY(icons[slot],y+offsets[slot]);setY(labels[slot],y+offsets[slot+4]);
  float iconHeight=icons[slot]->getHeight().asAbsolute(1.0f);height=maxSecond(iconHeight+offsets[slot],height);
  float labelHeight=labels[slot]->getHeight().asAbsolute(1.0f);height=maxSecond(labelHeight+offsets[slot+4],height);
  ++slot;
 }}
 if(height>0.0f)height=gap+height;
 for(;slot<4;++slot){icons[slot]->setVisible(false);labels[slot]->setVisible(false);}
 return height;
}
inline __attribute__((always_inline)) void place(CSkillTooltip* tip,float mouseX,float mouseY){
 float viewportWidth=g_pGameUI->getWindowWidth();float viewportHeight=g_pGameUI->getWindowHeight();
 float width=tip->m_pWindow->getWidth().asAbsolute(1.0f);float height=tip->m_pWindow->getHeight().asAbsolute(1.0f);
 float x=(mouseX-width)-26.0f;float y=(mouseY-height)-26.0f;
 float vw=float(static_cast<unsigned>(static_cast<long>(viewportWidth)));if((x+width)+26.0f>vw)x=vw-(width+26.0f);
 float vh=float(static_cast<unsigned>(static_cast<long>(viewportHeight)));if((y+height)+26.0f>vh)y=vh-(height+26.0f);
 if(0.0f>x-26.0f)x=mouseX+26.0f;if(y-26.0f<0.0f)y=26.0f;
 tip->m_pWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
}
}
#endif
