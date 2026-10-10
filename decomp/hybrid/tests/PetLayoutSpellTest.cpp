#include <cstring>
#include <string>
#include <vector>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include "PetMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Character.h"
#include "Skill.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldLayout, (CPetMenu*), "_ZN8CPetMenu12updateLayoutEv")
extern "C" void newLayout(CPetMenu*) __asm__("_ZN8CPetMenu12updateLayoutEv");
TL_FUNCTION(queryFn,"_ZN10CInventory21getEquipmentRefInSlotEj")
TL_FUNCTION(slotFn,"_ZN8CPetMenu11setSlotIconEP10CEquipmentii")
TL_FUNCTION(knownFn,"_ZN10CCharacter13getKnownSpellEj")
TL_FUNCTION(iconFn,"_ZN6CSkill12getSkillIconEv")
TL_FUNCTION(uiImageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(getSizeFn,"_ZNK5CEGUI6Window7getSizeEv");
IMPORT(setSizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(backFn,"_ZN5CEGUI6Window10moveToBackEv");
IMPORT(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMPORT(tooltipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
IMPORT(imageStringFn,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
#undef IMPORT
namespace {
struct Case {unsigned guard,children,holes,count,capacity,mutate;unsigned mask,mode,translation;};
autotest::Capture* cap;CPetMenu* menu;CInventory* inventory;CEGUI::Window* win[430];CEquipment* item[3];const Case* input;CSkill* skills[4];std::wstring* icons[4];CEGUI::Image* image;int translates[3];
void number(int n){cap->add(&n,sizeof(n));}
int id(const CEGUI::Window* p){for(int i=0;i<430;++i)if(p==win[i])return i;return -1;}
void text(const CEGUI::String& s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void remove(CEGUI::Window* p,CEGUI::Window* q){number(1);number(id(p));number(id(q));for(size_t i=0;i<p->d_children.size();++i)if(p->d_children[i]==q){p->d_children.erase(p->d_children.begin()+i);break;}q->d_parent=0;}
CEGUI::UVector2 size(const CEGUI::Window* p){number(2);number(id(p));return CEGUI::UVector2(CEGUI::UDim(0.25f,32+id(p)),CEGUI::UDim(0.5f,48+id(p)));}
void setSize(CEGUI::Window* p,const CEGUI::UVector2& v){number(3);number(id(p));cap->add(&v,sizeof(v));}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){number(4);int n=-1;for(int i=0;i<430;++i)if(static_cast<CEGUI::PropertySet*>(win[i])==p)n=i;number(n);text(k);text(v);}
void setText(CEGUI::Window* p,const CEGUI::String& s){number(5);number(id(p));text(s);}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){number(6);number(id(p));text(s);}
void front(CEGUI::Window* p){number(7);number(id(p));}
void back(CEGUI::Window* p){number(8);number(id(p));}
long query(CInventory* p,unsigned i){number(9);number(p==inventory);number(i);if(input->mutate&&i==11)menu->m_pSocketedSizeWindows[i]=0;return 0;}
void slot(CPetMenu* p,CEquipment* e,int index,int data){number(10);number(p==menu);int n=-1;for(int i=0;i<3;++i)if(e==item[i])n=i;number(n);number(index);number(data);}
CSkill* known(CCharacter* p,unsigned index){number(11);number(p==menu->m_pCharacter);number(index);return input->mode==0|| (input->mode==3&&index==1)?0:skills[index];}
const std::wstring& icon(CSkill* p){int index=0;for(int i=0;i<2;++i)if(skills[i]==p)index=i;number(12);number(index);return *icons[index];}
const CEGUI::Image* uiImage(CGameUI* p,const unsigned char* s){number(13);number(p==menu->m_pGameUI);cap->addText(std::string((const char*)s));return image;}
CEGUI::String imageString(const CEGUI::Image* p){number(14);number(p==image);return CEGUI::String("spell-image");}
CStringTranslate* singleton(){number(15);return (CStringTranslate*)image;}
std::wstring translate(CStringTranslate* p,const wchar_t* s){number(16);number(p==(CStringTranslate*)image);std::wstring key(s);cap->addText(key);int index=key==L"Hold [CTRL] and left-click to"?0:key==L"un-learn this spell"?1:2;int n=translates[index]++;number(index);if(input->translation==1||(input->translation==2&&n==0))return std::wstring();return input->translation==3?key+L" \u03a9 \u4e2d\u6587 \u041f\u0435\u0440\u0435\u0432\u043e\u0434":key+L" translated";}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;
 unsigned long long mem[(sizeof(CPetMenu)+7)/8]={0},cmem[(sizeof(CCharacter)+7)/8]={0},imem[(sizeof(CInventory)+7)/8]={0},rmem[3][(sizeof(CEquipmentRef)+7)/8]={0},emem[3][(sizeof(CEquipment)+7)/8]={0};
 unsigned long long wmem[430][(sizeof(CEGUI::Window)+7)/8]={0};
 menu=(CPetMenu*)mem;inventory=(CInventory*)imem;CCharacter* character=(CCharacter*)cmem;
 for(int i=0;i<430;++i){win[i]=(CEGUI::Window*)wmem[i];new(&win[i]->d_children)std::vector<CEGUI::Window*>;}
 for(int i=0;i<82;++i){menu->m_pSocketedSizeWindows[i]=i<12&&c.holes&&(i%3==0)?0:win[i];menu->m_pMainGlowWindows[i]=win[82+i];menu->m_pMainSocketGlowWindows[i]=win[164+i];menu->m_pMainStackWindows[i]=(i+c.holes)%2?win[246+i]:0;menu->m_pMainUnidentifiedWindows[i]=win[328+i];new(&menu->m_DefaultSlotImages[i])CEGUI::String("default-image");new(&menu->m_DefaultSlotTooltips[i])CEGUI::String("default-tip");for(unsigned j=0;j<c.children;++j)win[i]->d_children.push_back(win[420+j]);}
 menu->m_pSocketedIconParent=win[410];menu->m_pBackground=win[411];menu->m_pPanel=win[412];menu->m_pSocketOverlay=win[413];menu->m_pIconLayer=win[415];menu->m_pForeground48=win[414];
 for(unsigned j=0;j<c.children;++j)win[410]->d_children.push_back(win[420+j]);
 menu->m_bOpenPartial=c.guard!=1;menu->m_pCharacter=c.guard==2?0:character;character->m_pInventory=c.guard==3?0:inventory;
 CEquipmentRef* refs[3];int slots[]={18,19,81};for(int i=0;i<3;++i){refs[i]=(CEquipmentRef*)rmem[i];item[i]=(CEquipment*)emem[i];refs[i]->m_pUnknown10=item[i];refs[i]->m_iSlot=slots[i];}
 unsigned long long uiMem[(sizeof(CGameUI)+7)/8]={0},imageMem[(sizeof(CEGUI::Image)+7)/8]={0},skillMem[4][(sizeof(CSkill)+7)/8]={0};
 image=(CEGUI::Image*)imageMem;menu->m_pGameUI=(CGameUI*)uiMem;
 std::wstring iconNames[4];for(int i=0;i<2;++i){skills[i]=(CSkill*)skillMem[i];skills[i]->m_Guid=0x112233440000LL+i;icons[i]=&iconNames[i];if(c.mode!=1&&!(c.mode==3&&i==2))iconNames[i]=L"skill_icon";menu->m_pSpellWindows[i]=(c.mask&(1u<<i))?win[424+i]:0;menu->m_SpellGuids[i]=-10-i;}for(int i=0;i<3;++i)translates[i]=0;
 TArrayList<CEquipmentRef*>& equipmentRefs=inventory->m_equipmentRefs;equipmentRefs.m_pData=refs;equipmentRefs.m_nCount=c.count;equipmentRefs.m_nCapacity=c.capacity;
 detour::Set d;TL_REDIRECT(d,queryFn,&query);TL_REDIRECT(d,slotFn,&slot);
 d.redirect(getSizeFn,getSizeFn,&size);d.redirect(setSizeFn,setSizeFn,&setSize);d.redirect(removeFn,removeFn,&remove);d.redirect(frontFn,frontFn,&front);d.redirect(backFn,backFn,&back);d.redirect(propertyFn,propertyFn,&property);d.redirect(textFn,textFn,&setText);d.redirect(tooltipFn,tooltipFn,&tooltip);
 TL_REDIRECT(d,knownFn,&known);TL_REDIRECT(d,iconFn,&icon);TL_REDIRECT(d,uiImageFn,&uiImage);TL_REDIRECT(d,translateSingletonFn,&singleton);TL_REDIRECT(d,translateFn,&translate);d.redirect(imageStringFn,imageStringFn,&imageString);
 if(d.failed())_exit(42);
 for(int frame=0;frame<2;++frame){number(100+frame);if(frame==0){if(ours)autotest::invoke(out,&newLayout,menu);else autotest::invoke(out,&oldLayout,menu);}else{if(ours)newLayout(menu);else oldLayout(menu);}for(int i=0;i<2;++i){cap->add(&menu->m_SpellGuids[i],sizeof(long long));number(win[424+i]->d_userData==&menu->m_NoSpell?1:win[424+i]->d_userData==&menu->m_SpellGuids[i]?2:0);}}
 for(int i=0;i<82;++i){number(win[i]->d_children.size());number(menu->m_pSocketedSizeWindows[i]!=0);}number(win[410]->d_children.size());
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(pet_layout_spells){
 autotest::Coverage coverage("pet_layout_spells",(uint64_t)(uintptr_t)&oldLayout);int failures=0,total=0;
 for(unsigned mask=0;mask<4;++mask)for(unsigned mode=0;mode<4;++mode)for(unsigned translation=0;translation<4;++translation){Case c={0,0,0,0,0,0,mask,mode,translation};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;
 if(!ok){++failures;size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    mask %u mode %u translation %u: exit %d/%d bytes %lu/%lu first %lu\n",mask,mode,translation,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);}
 }coverage.report(host);host->log("    pet layout spells: %d cases, %d differences\n",total,failures);return failures;
}
