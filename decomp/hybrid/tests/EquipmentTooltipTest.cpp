#include <string>
#include <cstring>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreUTFString.h>
#include "GameUI.h"
#include "EquipmentTooltip.h"
#include "Equipment.h"
#include "Character.h"
#include "Inventory.h"
#include "SubMenu.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldTooltip,(CGameUI*,CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*),"_ZN7CGameUI20showEquipmentTooltipEP10CCharacterP10CEquipmentP17CEquipmentTooltipS5_S5_")
extern "C" void newTooltip(CGameUI*,CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*) __asm__("_ZN7CGameUI20showEquipmentTooltipEP10CCharacterP10CEquipmentP17CEquipmentTooltipS5_S5_");
TL_FUNCTION(keyFn,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(questFn,"_ZN9CBaseUnit14getIsQuestUnitEv")
TL_FUNCTION(nameFn,"_ZN10CEquipment15getFullItemNameEb")
TL_FUNCTION(typeFn,"_ZN10CEquipment16getEquipmentTypeEb")
TL_FUNCTION(statsFn,"_ZN10CEquipment17getEquipmentStatsEv")
TL_FUNCTION(effectsFn,"_ZN10CEquipment19getEquipmentEffectsEv")
TL_FUNCTION(flavorFn,"_ZN10CEquipment20getFlavorDescriptionEv")
TL_FUNCTION(setFn,"_ZN10CEquipment6getSetEv")
TL_FUNCTION(dpsFn,"_ZN10CEquipment3DPSEv")
TL_FUNCTION(buyFn,"_ZN10CEquipment8buyPriceEv")
TL_FUNCTION(sellFn,"_ZN10CEquipment9sellPriceEv")
TL_FUNCTION(slotFn,"_ZN10CInventory17findEquipmentSlotEP10CEquipment")
TL_FUNCTION(valueFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(uvalueFn,"_ZN7STRINGS17GetValueAsWStringEj")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(replaceFn,"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(globalsFn,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(reqLevelFn,"_ZN10CEquipment19getLevelRequirementEP10CCharacter")
TL_FUNCTION(reqStrengthFn,"_ZN10CEquipment22getStrengthRequirementEP10CCharacter")
TL_FUNCTION(reqDexterityFn,"_ZN10CEquipment23getDexterityRequirementEP10CCharacter")
TL_FUNCTION(reqMagicFn,"_ZN10CEquipment19getMagicRequirementEP10CCharacter")
TL_FUNCTION(reqDefenseFn,"_ZN10CEquipment21getDefenseRequirementEP10CCharacter")
TL_FUNCTION(strengthFn,"_ZN10CCharacter8strengthEv")
TL_FUNCTION(dexterityFn,"_ZN10CCharacter9dexterityEv")
TL_FUNCTION(magicFn,"_ZN10CCharacter5magicEv")
TL_FUNCTION(defenseFn,"_ZN10CCharacter7defenseEv")
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

namespace {
struct Case{unsigned kind,owner,magical,identified,peers,cached,serial;};
autotest::Capture* cap;const Case* input;CGameUI* ui;CEquipment* item;CCharacter* actors[3];CInventory* inventory;CEquipmentTooltip* tips[3];CGameGlobals* globals;CStringTranslate* translator;CSubMenu* merchant;
CEGUI::Window* windows[18];CEGUI::Font* fonts[5];CEGUI::UVector2 positions[18],sizes[18];unsigned calls,fontCalls,magicCalls,reqCalls[5],attributeCalls[4],flavorCalls,globalsCalls;void* eqTable[128];void* merchantTable[16];
const uintptr_t caches[]={0x14b9b60,0x14b9b58,0x14b9b50,0x14b9b48,0x14b9b40,0x14b9b38,0x14b9b30,0x14b9b28,0x14b9b20,0x14b9b18,0x14b9b10,0x14b9b08,0x14b9b00,0x14b9af8,0x14b9af0,0x14b9ae8};
const uintptr_t guards[]={0x14b9a68,0x14b9a70,0x14b9a78,0x14b9a80,0x14b9a88,0x14b9a90,0x14b9a98,0x14b9aa0,0x14b9aa8,0x14b9ab0,0x14b9ab8,0x14b9ac0,0x14b9ac8,0x14b9ad0,0x14b9ad8,0x14b9ae0};

template<class T>T& at(void* p,size_t off){return *(T*)((char*)p+off);}
void n(int v){cap->add(&v,4);}void f(float v){cap->add(&v,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int wid(const CEGUI::Window* p){for(int i=0;i<18;++i)if(p==windows[i])return i;return p?-2:-1;}
int aid(const CCharacter* p){for(int i=0;i<3;++i)if(p==actors[i])return i;return p?-2:-1;}
int fid(const CEGUI::Font* p){for(int i=0;i<5;++i)if(p==fonts[i])return i;return -1;}
bool changing(){return input->serial%3==1;}
void change(){++calls;if(changing()){positions[16].d_x.d_offset+=11;positions[17].d_x.d_offset-=7;positions[17].d_y.d_offset+=13;at<long>(ui,0x12d0)+=3;}}
float width(CGameUI* p){n(1);n(p==ui);return input->serial%17==0?0.0f:input->serial%17==1?-1.0f:1920.0f;}
float height(CGameUI* p){n(2);n(p==ui);return input->serial%5==0?60.0f:1080.0f;}
CEGUI::UDim getWidth(const CEGUI::Window* p){n(3);n(wid(p));change();return sizes[wid(p)].d_x;}
CEGUI::UDim getHeight(const CEGUI::Window* p){n(4);n(wid(p));change();return sizes[wid(p)].d_y;}
const CEGUI::UVector2& getPosition(const CEGUI::Window* p){n(5);n(wid(p));change();return positions[wid(p)];}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(wid(p));cap->add(&v,sizeof(v));positions[wid(p)]=v;}
void add(CEGUI::Window* p,CEGUI::Window* child){n(7);n(wid(p));n(wid(child));child->d_parent=p;}void remove(CEGUI::Window* p,CEGUI::Window* child){n(8);n(wid(p));n(wid(child));child->d_parent=0;}void front(CEGUI::Window* p){n(9);n(wid(p));}
short key(unsigned k){n(10);n(k);return input->serial%4==0?-32768:input->serial%4==1?1:0;}
void text(CEGUI::Window* p,const CEGUI::String& s){n(11);n(wid(p));str(s);p->d_text=s;}
void visible(CEGUI::Window* p,bool b){n(12);n(wid(p));n(b);p->d_visible=b;}
void size(CEGUI::Window* p,const CEGUI::UVector2& s){n(13);n(wid(p));cap->add(&s,sizeof(s));sizes[wid(p)]=s;}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(14);n(wid(static_cast<CEGUI::Window*>(p)));str(k);str(v);if(changing())for(unsigned i=0;i<5;++i)fonts[i]->d_ascender+=.125f;}
CEGUI::Font* font(const CEGUI::Window* p,bool inherit){n(15);n(wid(p));n(inherit);++fontCalls;return fonts[(wid(p)+(changing()?fontCalls:0))%5];}
float extent(CEGUI::Font* p,const CEGUI::String& s,const CEGUI::Rect& area,CEGUI::TextFormatting fmt,float scale){n(16);n(fid(p));str(s);cap->add(&area,sizeof(area));n(fmt);f(scale);float result=float(s.length()*5+fid(p)*2)+.25f;if(input->serial%19==0)result=-result;return result;}
size_t lines(CEGUI::Font* p,const CEGUI::String& s,const CEGUI::Rect& area,CEGUI::TextFormatting fmt,float scale){n(17);n(fid(p));str(s);cap->add(&area,sizeof(area));n(fmt);f(scale);return input->serial%23==0?size_t(0x100000001ULL):s.empty()?0:1+fid(p)%2;}
float scaled(CGameUI* p,float x){n(18);n(p==ui);f(x);const float scales[]={1,.75f,-.5f,-0.0f};return x*scales[(input->serial/17)%4];}
bool has(unsigned id){unsigned kind=input->kind;if(kind==11)return id==8||id==10||id==13||id==17||id==21||id==54||id==55||id==160;if(id==8)return kind==1||kind==2||kind==6;if(id==10)return kind==2;if(id==13)return kind==3;if(id==17)return kind==4;if(id==21)return kind==5;if(id==103)return kind==6;if(id==54)return kind==7;if(id==55)return kind==8;if(id==160)return kind==9;return false;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(19);n((void*)p==(void*)item?10:aid((CCharacter*)p));n(type);if((void*)p==(void*)item)return has(type);return (input->owner==1&&type==UNITTYPES::MERCHANT)||(input->owner==2&&type==UNITTYPES::GAMBLER);}
bool quest(CBaseUnit* p){n(20);n((void*)p==(void*)item);return input->kind==6;}
bool magical(CEquipment* p){n(21);n(p==item);n(++magicCalls);return input->magical;}
std::wstring label(const wchar_t* normal){unsigned mode=(input->serial/3)%4;if(mode==1)return L"";if(mode==2)return std::wstring(normal)+L" Ω中";if(mode==3)return std::wstring(normal)+L"\\nnext";return normal;}
std::wstring name(CEquipment* p,bool b){n(22);n(p==item);n(b);return label(L"Item");}
std::wstring type(CEquipment* p,bool b){n(23);n(p==item);n(b);return label(b?L"known type":L"unknown type");}
std::wstring stats(CEquipment* p){n(24);n(p==item);return label(L"stats");}
std::wstring effects(CEquipment* p){n(25);n(p==item);return label(L"effects");}
std::wstring flavor(CEquipment* p){n(26);n(p==item);n(++flavorCalls);return label(L"flavor");}
std::wstring set(CEquipment* p){n(27);n(p==item);return input->kind==10?L"set":L"";}
long dps(CEquipment* p){n(28);n(p==item);return input->serial%7==0?long(0x100000005ULL):long(42);}
int buy(CEquipment* p){n(29);n(p==item);return input->serial%3==0?-7:input->serial%3==1?500:10;}
int sell(CEquipment* p){n(30);n(p==item);return input->serial%3==0?-4:11;}
int slot(CInventory* p,CEquipment* e){n(31);n(p==inventory);n(e==item);const int slots[]={-1,0,1,8,9,999};return slots[input->serial%6];}
std::wstring value(int x){n(32);n(x);char b[32];std::sprintf(b,"%d",x);return std::wstring(b,b+std::strlen(b));}
std::wstring uvalue(unsigned x){n(33);n(x);char b[32];std::sprintf(b,"%u",x);return std::wstring(b,b+std::strlen(b));}
std::string convert(const std::wstring& s){n(34);cap->addText(s);return Ogre::UTFString(s).asUTF8();}
std::wstring replace(std::wstring s,const std::wstring& find,const std::wstring& with){n(35);cap->addText(s);cap->addText(find);cap->addText(with);size_t pos=0;while(!find.empty()&&(pos=s.find(find,pos))!=std::wstring::npos){s.replace(pos,find.size(),with);pos+=with.size();}return s;}
CStringTranslate* singleton(){n(36);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* s){n(37);n(p==translator);cap->addText(std::wstring(s));return input->serial%13==0?L"":std::wstring(s);}
CGameGlobals* getGlobals(){n(38);n(++globalsCalls);return globals;}
int requirement(CEquipment* p,CCharacter* actor,unsigned kind){n(39);n(p==item);n(aid(actor));n(kind);n(++reqCalls[kind]);int mode=(input->serial/7)%5;int result=mode==0?0:mode==1?-1:mode==2?10:mode==3?50:(kind%2?0:35);if(changing()){result+=reqCalls[kind];ui->m_pCharacter=actor==actors[0]?actors[1]:actors[0];}return result;}
int reqLevel(CEquipment* p,CCharacter* a){return requirement(p,a,0);}int reqStrength(CEquipment* p,CCharacter* a){return requirement(p,a,1);}int reqDexterity(CEquipment* p,CCharacter* a){return requirement(p,a,2);}int reqMagic(CEquipment* p,CCharacter* a){return requirement(p,a,3);}int reqDefense(CEquipment* p,CCharacter* a){return requirement(p,a,4);}
int attribute(CCharacter* p,unsigned k){n(40);n(aid(p));n(k);n(++attributeCalls[k]);return (p==actors[0]?30:60)+int(k)+(changing()?attributeCalls[k]:0);}
int strength(CCharacter* p){return attribute(p,0);}int dexterity(CCharacter* p){return attribute(p,1);}int magic(CCharacter* p){return attribute(p,2);}int defense(CCharacter* p){return attribute(p,3);}
bool merchantOpen(CSubMenu* p){n(41);n(p==merchant);return input->serial%2==0;}
void side(const Case& c,bool ours,autotest::Capture& out){cap=&out;input=&c;calls=fontCalls=magicCalls=flavorCalls=globalsCalls=0;memset(reqCalls,0,sizeof(reqCalls));memset(attributeCalls,0,sizeof(attributeCalls));
 unsigned long long um[900]={0},em[180]={0},am[3][256]={0},tm[3][24]={0},wm[18][(sizeof(CEGUI::Window)+7)/8],fm[5][(sizeof(CEGUI::Font)+7)/8],im[32]={0},gm[100]={0},trm[32]={0},mm[16]={0};memset(wm,0,sizeof(wm));memset(fm,0,sizeof(fm));ui=(CGameUI*)um;item=(CEquipment*)em;inventory=(CInventory*)im;globals=(CGameGlobals*)gm;translator=(CStringTranslate*)trm;merchant=(CSubMenu*)mm;
 for(int i=0;i<3;++i){actors[i]=(CCharacter*)am[i];actors[i]->m_iUnitLevel=c.serial%29==0?0xffffffffU:30+i*30;actors[i]->m_iGold=c.serial%31==0?-1:100+i*200;actors[i]->m_pInventory=inventory;}
 ui->m_pCharacter=actors[0];CCharacter* owner=c.owner==0?actors[0]:actors[2];at<CSubMenu*>(ui,0x4f0)=merchant;merchantTable[4]=(void*)&merchantOpen;*(void***)merchant=merchantTable;eqTable[0x2b0/8]=(void*)&magical;*(void***)item=eqTable;at<long long>(item,0x10)=77;item->m_bUnknown348=c.identified;item->m_iUnknown338=c.serial%3==0?-11:34;
 for(int i=0;i<18;++i){windows[i]=(CEGUI::Window*)wm[i];new(&windows[i]->d_text)CEGUI::String("initial");windows[i]->d_visible=c.serial%2;positions[i]=CEGUI::UVector2(CEGUI::UDim(i%2?-.0f:.25f,i*3),CEGUI::UDim(.0f,40+i*2));sizes[i]=CEGUI::UVector2(CEGUI::UDim(.25f,160),CEGUI::UDim(-.5f,100));}
 positions[16].d_x.d_offset=c.serial%2?100:900;positions[17].d_x.d_offset=c.serial%2?600:300;positions[17].d_y.d_offset=c.serial%4>=2?1000:30;
 for(int i=0;i<5;++i){fonts[i]=(CEGUI::Font*)fm[i];fonts[i]->d_ascender=12.0f+i;fonts[i]->d_descender=-2.0f;}
 for(int i=0;i<3;++i){tips[i]=(CEquipmentTooltip*)tm[i];tips[i]->m_pParent=windows[0];tips[i]->m_pRoot=windows[i==0?1:i+15];tips[i]->m_iCachedItemGuid=c.cached?77:66;}
 for(int i=0;i<14;++i)at<CEGUI::Window*>(tips[0],0x28+i*8)=windows[i+2];windows[1]->d_parent=c.serial%2?windows[0]:0;at<long>(ui,0x12d0)=c.serial%2?25:1800;at<long>(ui,0x12d8)=c.serial%4>=2?1200:5;
 new(&globals->m_sQuestColor)std::wstring(L"quest");new(&globals->m_sSetColor)std::wstring(L"set");new(&globals->m_sUniqueColor)std::wstring(L"unique");new(&globals->m_sRareColor)std::wstring(L"rare");new(&globals->m_sRandomEnchantColor)std::wstring(L"random");
 for(unsigned i=0;i<sizeof(caches)/sizeof(*caches);++i){new((void*)caches[i])std::wstring(c.serial%11==0?L"cached":L"");*(unsigned char*)guards[i]=c.serial%11==0;}
 detour::Set d,d2;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(keyFn,key);R(widthFn,width);R(heightFn,height);R(scaledFn,scaled);R(isaFn,isa);R(questFn,quest);R(nameFn,name);R(typeFn,type);R(statsFn,stats);R(effectsFn,effects);R(flavorFn,flavor);R(setFn,set);R(dpsFn,dps);R(buyFn,buy);R(sellFn,sell);R(slotFn,slot);R(valueFn,value);R(uvalueFn,uvalue);R(convertFn,convert);R(replaceFn,replace);R(translateSingletonFn,singleton);R(translateFn,translate);R(globalsFn,getGlobals);R(reqLevelFn,reqLevel);R(reqStrengthFn,reqStrength);R(reqDexterityFn,reqDexterity);R(reqMagicFn,reqMagic);R(reqDefenseFn,reqDefense);R(strengthFn,strength);R(dexterityFn,dexterity);R(magicFn,magic);R(defenseFn,defense);
#undef R
#define I(N,F) d2.redirect(N,N,&F)
 I(getWidthFn,getWidth);I(getHeightFn,getHeight);I(getPositionFn,getPosition);I(setPositionFn,setPosition);I(sizeFn,size);I(addFn,add);I(removeFn,remove);I(frontFn,front);I(textFn,text);I(visibleFn,visible);I(propertyFn,property);I(fontFn,font);I(extentFn,extent);I(linesFn,lines);
#undef I
 if(d.failed()||d2.failed())_exit(43);
 for(unsigned frame=0;frame<2;++frame){if(frame&&c.cached)at<long long>(item,0x10)=78;n(90);n(frame);if(frame){if(ours)newTooltip(ui,owner,item,tips[0],c.peers?tips[1]:0,c.peers==2?tips[2]:0);else oldTooltip(ui,owner,item,tips[0],c.peers?tips[1]:0,c.peers==2?tips[2]:0);}else{if(ours)autotest::invoke(out,&newTooltip,ui,owner,item,tips[0],c.peers?tips[1]:(CEquipmentTooltip*)0,c.peers==2?tips[2]:(CEquipmentTooltip*)0);else autotest::invoke(out,&oldTooltip,ui,owner,item,tips[0],c.peers?tips[1]:(CEquipmentTooltip*)0,c.peers==2?tips[2]:(CEquipmentTooltip*)0);}n(91);cap->add(&tips[0]->m_iCachedItemGuid,8);for(unsigned i=0;i<18;++i){n(wid(windows[i]->d_parent));n(windows[i]->d_visible);str(windows[i]->d_text);}cap->add(positions,sizeof(positions));cap->add(sizes,sizeof(sizes));}
 for(unsigned i=0;i<sizeof(caches)/sizeof(*caches);++i){cap->addText(*(std::wstring*)caches[i]);n(*(unsigned char*)guards[i]);}
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(equipment_tooltip_differential){autotest::Coverage coverage("equipment_tooltip_differential",(uint64_t)(uintptr_t)&oldTooltip);unsigned serial=0;for(unsigned kind=0;kind<12;++kind)for(unsigned owner=0;owner<4;++owner)for(unsigned magical=0;magical<2;++magical)for(unsigned identified=0;identified<2;++identified)for(unsigned peers=0;peers<3;++peers)for(unsigned cached=0;cached<2;++cached){Case c={kind,owner,magical,identified,peers,cached,serial++};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    case %u kind %u owner %u magical %u identified %u peers %u cached %u status %d/%d bytes %lu/%lu first %lu\n",c.serial,kind,owner,magical,identified,peers,cached,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>40?(first-40)&~size_t(3):0;i<first+140&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);float uf,vf;memcpy(&uf,&u,4);memcpy(&vf,&v,4);host->log("      %lu %d/%d floats %g/%g\n",(unsigned long)i,u,v,double(uf),double(vf));}return 1;}}coverage.report(host);return 0;}
