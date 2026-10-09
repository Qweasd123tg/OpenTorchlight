#include <string>
#include <cstring>
#include <cstdio>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreUTFString.h>
#include "GameUI.h"
#include "SkillTooltip.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "SkillManager.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldTooltip,(CSkillTooltip*,CBaseUnit*,CSkill*,float,float),"_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff")
extern "C" void newTooltip(CSkillTooltip*,CBaseUnit*,CSkill*,float,float) __asm__("_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff");
TL_FUNCTION(nameFn,"_ZN6CSkill7getNameEv")
TL_FUNCTION(levelFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(fillFn,"_ZN6CSkill18fillOutStatBonusesERA6_fbj")
TL_FUNCTION(iconFn,"_ZN6CSkill12getSkillIconEv")
TL_FUNCTION(displayFn,"_ZN6CSkill14getDisplayNameEv")
TL_FUNCTION(descriptionFn,"_ZN6CSkill24getSkillLevelDescriptionEP9CBaseUnitj")
TL_FUNCTION(typeFn,"_ZN6CSkill23getSkillTypeDisplayNameEv")
TL_FUNCTION(manaOTFn,"_ZN6CSkill23getSkillLevelManaCostOTEP9CBaseUnitj")
TL_FUNCTION(manaFn,"_ZN6CSkill21getSkillLevelManaCostEP9CBaseUnitj")
TL_FUNCTION(cooldownFn,"_ZN6CSkill21getSkillLevelCooldownEP9CBaseUnitj")
TL_FUNCTION(statsFn,"_ZN6CSkill18getSkillLevelStatsEP9CBaseUnitj")
TL_FUNCTION(usageFn,"_ZN6CSkill24getSkillUsageDescriptionEv")
TL_FUNCTION(reqLevelFn,"_ZN6CSkill29getLevelRequiredForInvestmentEv")
TL_FUNCTION(reqSkillFn,"_ZN6CSkill29getSkillRequiredForInvestmentEv")
TL_FUNCTION(findSkillFn,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(imageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(valueFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(uvalueFn,"_ZN7STRINGS17GetValueAsWStringEj")
TL_FUNCTION(nvalueFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(narrowFn,"_ZN7STRINGS21StringConvertToNarrowEPKw")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
extern "C" char getWidthFn[] __asm__("_ZNK5CEGUI6Window8getWidthEv");
extern "C" char getHeightFn[] __asm__("_ZNK5CEGUI6Window9getHeightEv");
extern "C" char getPositionFn[] __asm__("_ZNK5CEGUI6Window11getPositionEv");
extern "C" char setPositionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char sizeFn[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char addFn[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char frontFn[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char propertyFn[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char fontFn[] __asm__("_ZNK5CEGUI6Window7getFontEb");
extern "C" char extentFn[] __asm__("_ZN5CEGUI4Font22getFormattedTextExtentERKNS_6StringERKNS_4RectENS_14TextFormattingEf");
extern "C" char linesFn[] __asm__("_ZN5CEGUI4Font21getFormattedLineCountERKNS_6StringERKNS_4RectENS_14TextFormattingEf");
extern "C" char imageToStringFn[] __asm__("_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");

namespace {
struct Case{unsigned profile,content,bonuses,mutate;};
autotest::Capture* cap;const Case* input;CSkillTooltip* tip;CSkill* skill;CSkill* required;CBaseUnit* owner;CSkillManager* managers[2];CStringTranslate* translator;CGameUI* ui[2];
CEGUI::Window* windows[35];CEGUI::Font* fonts[5];CEGUI::Image* images[4];CEGUI::UVector2 positions[35],sizes[35];std::wstring names[6];unsigned calls,levelCalls,fontCalls,frame;
const uintptr_t caches[]={0x14b9d08,0x14b9d00,0x14b9cf8,0x14b9cf0,0x14b9ce8,0x14b9ce0,0x14b9cd8,0x14b9cd0,0x14b9cc8};
const uintptr_t guards[]={0x14b9c80,0x14b9c88,0x14b9c90,0x14b9c98,0x14b9ca0,0x14b9ca8,0x14b9cb0,0x14b9cb8,0x14b9cc0};
template<class T>T& at(void* p,size_t off){return *(T*)((char*)p+off);}
CGameUI*& globalUI(){return *(CGameUI**)0x14b9c68;}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int wid(const CEGUI::Window* p){for(int i=0;i<35;++i)if(p==windows[i])return i;return p?-2:-1;}
int fid(const CEGUI::Font* p){for(int i=0;i<5;++i)if(p==fonts[i])return i;return -1;}
int sid(const CSkill* p){return p==skill?0:p==required?1:-1;}
void change(){++calls;if(input->mutate&2){for(int i=0;i<8;++i){tip->m_StatOffsets[i]+=.125f;tip->m_NextStatOffsets[i]-=.25f;}globalUI()=calls%2?ui[0]:ui[1];}}
float width(CGameUI* p){n(1);n(p==ui[0]?0:p==ui[1]?1:-1);if(input->mutate&2)globalUI()=ui[1];return input->profile%5==0?100:1920;}
float height(CGameUI* p){n(2);n(p==ui[0]?0:p==ui[1]?1:-1);return input->profile%3==0?60:1080;}
float scaled(CGameUI* p,float x){n(3);n(p==ui[0]?0:p==ui[1]?1:-1);f(x);change();const float scales[]={1,.75f,-.5f,1.5f};return x*scales[input->profile%4];}
CEGUI::UDim getWidth(const CEGUI::Window* p){n(4);n(wid(p));change();return sizes[wid(p)].d_x;}
CEGUI::UDim getHeight(const CEGUI::Window* p){n(5);n(wid(p));change();return sizes[wid(p)].d_y;}
const CEGUI::UVector2& getPosition(const CEGUI::Window* p){n(6);n(wid(p));change();return positions[wid(p)];}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& x){n(7);n(wid(p));cap->add(&x,sizeof(x));positions[wid(p)]=x;}
void size(CEGUI::Window* p,const CEGUI::UVector2& x){n(8);n(wid(p));cap->add(&x,sizeof(x));sizes[wid(p)]=x;}
void text(CEGUI::Window* p,const CEGUI::String& s){n(9);n(wid(p));str(s);p->d_text=s;}
void visible(CEGUI::Window* p,bool v){n(10);n(wid(p));n(v);p->d_visible=v;change();}
void property(CEGUI::PropertySet* p,const CEGUI::String& key,const CEGUI::String& v){n(11);n(wid(static_cast<CEGUI::Window*>(p)));str(key);str(v);if(input->mutate&2)for(int i=0;i<5;++i)fonts[i]->d_ascender+=.125f;}
CEGUI::Font* font(const CEGUI::Window* p,bool inherit){n(12);n(wid(p));n(inherit);++fontCalls;return fonts[(wid(p)+(input->mutate&2?fontCalls:0))%5];}
float extent(CEGUI::Font* p,const CEGUI::String& s,const CEGUI::Rect& rect,CEGUI::TextFormatting fmt,float scale){n(13);n(fid(p));str(s);cap->add(&rect,sizeof(rect));n(fmt);f(scale);return float(s.length()*5+fid(p)*2)+.25f;}
size_t lines(CEGUI::Font* p,const CEGUI::String& s,const CEGUI::Rect& rect,CEGUI::TextFormatting fmt,float scale){n(14);n(fid(p));str(s);cap->add(&rect,sizeof(rect));n(fmt);f(scale);return s.empty()?0:1+fid(p)%2;}
void add(CEGUI::Window* p,CEGUI::Window* child){n(15);n(wid(p));n(wid(child));child->d_parent=p;}void front(CEGUI::Window* p){n(16);n(wid(p));}
const std::wstring& name(CSkill* p){n(17);n(sid(p));return names[0];}
void level(CSkill* p){n(18);n(sid(p));n(++levelCalls);const unsigned levels[]={0,1,3,0xffffffffu};unsigned v=levels[input->profile%4];if(input->mutate&1){const unsigned sequence[]={0,1,2,3,0x7fffffffu,0x80000000u,0xffffffffu,4};v=sequence[(levelCalls+frame+input->profile)%8];}at<unsigned>(p,0xe0)=v;}
void fill(CSkill* p,float (&values)[6],bool flag,unsigned rank){n(19);n(sid(p));n(flag);n(rank);for(int i=0;i<6;++i){float v=0;unsigned mode=(input->bonuses+i)%8;if(mode==1)v=.12f;else if(mode==2)v=-.031f;else if(mode==3)v=1.0f;else if(mode==4)v=std::numeric_limits<float>::quiet_NaN();else if(mode==5)v=.0001f;else if(mode==6)v=-0.0f;else if(mode==7)v=.56f;if(input->bonuses==0)v=0;values[i]=v;}cap->add(values,sizeof(values));}
const std::wstring& icon(CSkill* p){n(20);n(sid(p));return names[1];}
const std::wstring& display(CSkill* p){n(21);n(sid(p));return names[p==required?3:2];}
std::wstring type(CSkill* p){n(22);n(sid(p));return input->content%3==0?L"":L"type Ω中";}
std::wstring description(CSkill* p,CBaseUnit* unit,unsigned rank){n(23);n(sid(p));n(unit==owner);n(rank);if(input->content%3==0)return L"";if(input->content%3==1)return L"same description";return rank%2?L"odd description Ω中":L"even description";}
int manaOT(CSkill* p,CBaseUnit* unit,unsigned rank){n(24);n(sid(p));n(unit==owner);n(rank);return input->content%3==0?0:input->content%3==1?7:-3;}
int mana(CSkill* p,CBaseUnit* unit,unsigned rank){n(25);n(sid(p));n(unit==owner);n(rank);return input->content%2?13:-2;}
int cooldown(CSkill* p,CBaseUnit* unit,unsigned rank){n(26);n(sid(p));n(unit==owner);n(rank);return input->content%3==0?0:input->content%3==1?6:-1;}
std::wstring stats(CSkill* p,CBaseUnit* unit,unsigned rank){n(27);n(sid(p));n(unit==owner);n(rank);return input->content%2?L"stats Ω中":L"";}
const std::wstring& usage(CSkill* p){n(28);n(sid(p));return names[4];}
unsigned requiredLevel(CSkill* p){n(29);n(sid(p));return input->profile%3?17:0;}
const std::wstring& requiredName(CSkill* p){n(30);n(sid(p));if(input->mutate&2)at<CSkillManager*>(owner,0x1c8)=managers[1];return names[5];}
CSkill* findSkill(CSkillManager* p,const std::wstring& name){n(31);n(p==managers[0]?0:p==managers[1]?1:-1);cap->addText(name);return input->content%3==1?0:required;}
const CEGUI::Image* image(CGameUI* p,const unsigned char* name){n(32);n(p==ui[0]?0:p==ui[1]?1:-1);std::string s((const char*)name);n(s.size());cap->add(s.data(),s.size());return images[s.size()%4];}
CEGUI::String imageToString(const CEGUI::Image* p){int id=-1;for(int i=0;i<4;++i)if(images[i]==p)id=i;n(33);n(id);char b[32];std::sprintf(b,"Image_%d",id);return CEGUI::String(b);}
std::wstring value(int x){n(34);n(x);char b[32];std::sprintf(b,"%d",x);return std::wstring(b,b+std::strlen(b));}
std::wstring uvalue(unsigned x){n(35);n(x);char b[32];std::sprintf(b,"%u",x);return std::wstring(b,b+std::strlen(b));}
std::string nvalue(int x){n(36);n(x);char b[32];std::sprintf(b,"%d",x);return b;}
std::string convert(const std::wstring& x){n(37);cap->addText(x);return Ogre::UTFString(x).asUTF8();}
std::string narrow(const wchar_t* x){n(38);std::wstring s(x);cap->addText(s);return std::string(s.begin(),s.end());}
CStringTranslate* singleton(){n(39);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* x){n(40);n(p==translator);cap->addText(std::wstring(x));return input->content==5?L"":std::wstring(x)+L" Ω";}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;cap=&out;calls=levelCalls=fontCalls=frame=0;unsigned long long um[2][900]={0},sm[2][44]={0},tm[47]={0},om[100]={0},mm[2][40]={0},tr[32]={0},im[4][32]={0},wm[35][(sizeof(CEGUI::Window)+7)/8],fm[5][(sizeof(CEGUI::Font)+7)/8];memset(wm,0,sizeof(wm));memset(fm,0,sizeof(fm));
 ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];skill=(CSkill*)sm[0];required=(CSkill*)sm[1];tip=(CSkillTooltip*)tm;owner=(CBaseUnit*)om;managers[0]=(CSkillManager*)mm[0];managers[1]=(CSkillManager*)mm[1];translator=(CStringTranslate*)tr;
 names[0]=L"Skill_A";names[1]=L"skill_icon";names[2]=L"Skill Ω中";names[3]=L"Required Skill";names[4]=c.content%2?L"Usage Ω中":L"";names[5]=c.content%3?L"required":L"";
 new((char*)tip+0x18)std::wstring(L"different");tip->m_iIndex=-9;at<unsigned>(skill,0xe0)=1;const unsigned counts[]={0,1,4,7};at<unsigned>(skill,0xa8)=counts[(c.profile/4)%4];at<unsigned>(skill,0x158)=c.content%2?9:0;at<int>(skill,0x60)=c.profile&4?4:3;at<bool>(skill,0x6b)=c.bonuses&2;at<bool>(skill,0x6d)=!(c.bonuses&4);at<CSkillManager*>(owner,0x1c8)=managers[0];
 for(int i=0;i<35;++i){windows[i]=(CEGUI::Window*)wm[i];new(&windows[i]->d_text)CEGUI::String();sizes[i]=CEGUI::UVector2(CEGUI::UDim(.25f,70+i),CEGUI::UDim(-.5f,16+i));positions[i]=CEGUI::UVector2(CEGUI::UDim(.125f,5+i),CEGUI::UDim(-.25f,10+i));}
 for(int i=0;i<5;++i){fonts[i]=(CEGUI::Font*)fm[i];fonts[i]->d_ascender=12+i*2;fonts[i]->d_descender=-3-i;}
 for(int i=0;i<4;++i)images[i]=(CEGUI::Image*)im[i];
 tip->m_pGameUI=ui[1];globalUI()=ui[0];tip->m_pRoot=windows[1];tip->m_pWindow=windows[0];windows[0]->d_parent=c.profile%2?windows[1]:0;
 for(int i=0;i<16;++i)at<CEGUI::Window*>(tip,0x38+i*8)=windows[i+2];
 for(int i=0;i<4;++i){tip->m_pStatIcons[i]=windows[18+i];tip->m_pStatLabels[i]=windows[22+i];tip->m_pNextStatIcons[i]=windows[26+i];tip->m_pNextStatLabels[i]=windows[30+i];}
 for(int i=0;i<8;++i){tip->m_StatOffsets[i]=float(i*3);tip->m_NextStatOffsets[i]=float(i*5);}
 for(unsigned i=0;i<9;++i){new((void*)caches[i])std::wstring(c.content%2?L"":L"cached");*(unsigned char*)guards[i]=1;}
 const char* iconNames[]={"iconmelee","iconranged","icondefense","iconmagic","iconmagic","iconmagic"};for(int i=0;i<6;++i)new((void*)(0x14b8d40+i*8))std::string(iconNames[i]);
 detour::Set d;
 TL_REDIRECT(d,nameFn,&name);
 TL_REDIRECT(d,levelFn,&level);
 TL_REDIRECT(d,fillFn,&fill);
 TL_REDIRECT(d,iconFn,&icon);
 TL_REDIRECT(d,displayFn,&display);
 TL_REDIRECT(d,descriptionFn,&description);
 TL_REDIRECT(d,typeFn,&type);
 TL_REDIRECT(d,manaOTFn,&manaOT);
 TL_REDIRECT(d,manaFn,&mana);
 TL_REDIRECT(d,cooldownFn,&cooldown);
 TL_REDIRECT(d,statsFn,&stats);
 TL_REDIRECT(d,usageFn,&usage);
 TL_REDIRECT(d,reqLevelFn,&requiredLevel);
 TL_REDIRECT(d,reqSkillFn,&requiredName);
 TL_REDIRECT(d,findSkillFn,&findSkill);
 TL_REDIRECT(d,imageFn,&image);
 TL_REDIRECT(d,widthFn,&width);
 TL_REDIRECT(d,heightFn,&height);
 TL_REDIRECT(d,scaledFn,&scaled);
 TL_REDIRECT(d,valueFn,&value);
 TL_REDIRECT(d,uvalueFn,&uvalue);
 TL_REDIRECT(d,nvalueFn,&nvalue);
 TL_REDIRECT(d,convertFn,&convert);
 TL_REDIRECT(d,narrowFn,&narrow);
 TL_REDIRECT(d,translateSingletonFn,&singleton);
 TL_REDIRECT(d,translateFn,&translate);
 d.redirect(getWidthFn,getWidthFn,&getWidth);
 d.redirect(getHeightFn,getHeightFn,&getHeight);
 d.redirect(getPositionFn,getPositionFn,&getPosition);
 d.redirect(setPositionFn,setPositionFn,&setPosition);
 d.redirect(sizeFn,sizeFn,&size);
 d.redirect(addFn,addFn,&add);
 d.redirect(frontFn,frontFn,&front);
 d.redirect(textFn,textFn,&text);
 d.redirect(visibleFn,visibleFn,&visible);
 d.redirect(propertyFn,propertyFn,&property);
 d.redirect(fontFn,fontFn,&font);
 d.redirect(extentFn,extentFn,&extent);
 d.redirect(linesFn,linesFn,&lines);
 d.redirect(imageToStringFn,imageToStringFn,&imageToString);

 if(d.failed())_exit(43);
 for(frame=0;frame<2;++frame){n(80);n(frame);if(frame&&c.content%2)names[0]=L"Skill_B";float x=c.profile%2?25:1800;float y=c.content%2?5:1000;
  if(frame){if(ours)newTooltip(tip,owner,skill,x,y);else oldTooltip(tip,owner,skill,x,y);}else{if(ours)autotest::invoke(out,&newTooltip,tip,owner,skill,x,y);else autotest::invoke(out,&oldTooltip,tip,owner,skill,x,y);}
  n(90);n(tip->m_iIndex);cap->addText(tip->m_sText);n(calls);n(levelCalls);n(fontCalls);n(globalUI()==ui[0]?0:1);cap->add(positions,sizeof(positions));cap->add(sizes,sizeof(sizes));for(int i=0;i<35;++i){n(windows[i]->d_visible);str(windows[i]->d_text);}cap->add(tip->m_StatOffsets,sizeof(tip->m_StatOffsets));cap->add(tip->m_NextStatOffsets,sizeof(tip->m_NextStatOffsets));
 }
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(skill_tooltip_content_differential){autotest::Coverage cv("skill_tooltip_content_differential",(uint64_t)(uintptr_t)&oldTooltip);unsigned count=0;for(unsigned profile=0;profile<16;++profile)for(unsigned content=0;content<6;++content)for(unsigned bonuses=0;bonuses<8;++bonuses)for(unsigned mutate=0;mutate<4;++mutate){Case c={profile,content,bonuses,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;if(cv.observe(host,x,y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    profile %u content %u bonuses %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",profile,content,bonuses,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>80?(first-80)&~size_t(3):0;i<first+160&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}}cv.report(host);host->log("    skill tooltip content: %u completed comparisons, two frames each\n",count);return 0;}
