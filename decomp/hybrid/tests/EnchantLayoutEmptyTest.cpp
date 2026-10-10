#include <cstring>
#include <string>
#include <vector>
#include <new>
#include <map>
#define private public
#define protected public
#include <CEGUI.h>
#include "EnchantMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Character.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldLayout, (CEnchantMenu*), "_ZN12CEnchantMenu12updateLayoutEv")
extern "C" void newLayout(CEnchantMenu*) __asm__("_ZN12CEnchantMenu12updateLayoutEv");
TL_FUNCTION(queryFn,"_ZN10CInventory21getEquipmentRefInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(createFn,"_ZN10CEquipment10createIconER7CGameUIb")
TL_FUNCTION(globalsFn,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(priceFn,"_ZN10CEquipment12enchantPriceEv")
TL_FUNCTION(formatIntFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(formatFloatFn,"_ZN7STRINGS17GetValueAsWStringEf")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(getSizeFn,"_ZNK5CEGUI6Window7getSizeEv");
IMPORT(setSizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(backFn,"_ZN5CEGUI6Window10moveToBackEv");
IMPORT(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMPORT(tooltipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
IMPORT(positionFn,"_ZNK5CEGUI6Window11getPositionEv");
IMPORT(setPositionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(visibleFn,"_ZNK5CEGUI6Window9isVisibleEb");
IMPORT(updateFn,"_ZN5CEGUI6Window6updateEf");
IMPORT(imageFn,"_ZNK5CEGUI8Imageset8getImageERKNS_6StringE");
IMPORT(imageStringFn,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
IMPORT(showFn,"_ZN5CEGUI6Window10setVisibleEb");
#undef IMPORT
namespace {
struct Case {unsigned guard,children,holes,count,capacity,mutate; unsigned sockets,identified,create,visible,mode,index,gemCapacity,stackMode,coordinate;unsigned service,typeCase,enchantCount,probability,translation,cross,empty;};
autotest::Capture* cap;CEnchantMenu* menu;CInventory* inventory;CEGUI::Window* win[430];CEquipment* item[3];const Case* input;CEquipmentRef* equipped;CEquipment* gems[2];CEGUI::UVector2 pos,parentPos;CEGUI::Image* image;CGameGlobals* globals;std::map<std::wstring,int>* translations;
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
long query(CInventory* p,unsigned i){number(9);number(p==inventory);number(i);if(input->mutate&&i==(unsigned)menu->m_aiSlotData[3])menu->m_pSocketedSizeWindows[3]=0;return !input->empty&&i==(unsigned)menu->m_aiSlotData[input->index]?(long)equipped:0;}
void slot(CEnchantMenu* p,CEquipment* e,int index,int data){number(10);number(p==menu);int n=-1;for(int i=0;i<3;++i)if(e==item[i])n=i;number(n);number(index);number(data);}
bool magical(CEquipment* p){number(11);number(p==item[0]);return input->mode>0;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(12);number(p==item[0]);number(t);const int types[]={0,8,13,17,24,39,8};return (input->mode==1&&int(t)==0x36)||(input->mode==2&&int(t)==0x37)||(input->typeCase&&int(t)==types[input->typeCase]);}
void create(CEquipment* p,CGameUI* ui,bool b){number(13);number(p==item[0]?0:p==gems[0]?1:2);number(ui==menu->m_pGameUI);number(b);p->m_pIconWindow=input->create==2?0:win[p==item[0]?416:p==gems[0]?417:418];}
const CEGUI::UVector2& position(const CEGUI::Window* p){number(14);number(id(p));return p==win[415]?parentPos:pos;}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){number(15);number(id(p));cap->add(&v,sizeof(v));}
void add(CEGUI::Window* p,CEGUI::Window* q){number(16);number(id(p));number(id(q));p->d_children.push_back(q);q->d_parent=p;}
bool visible(const CEGUI::Window* p,bool b){number(17);number(id(p));number(b);return input->visible;}
void update(CEGUI::Window* p,float dt){number(18);number(id(p));cap->add(&dt,sizeof(dt));}
const CEGUI::Image& getImage(const CEGUI::Imageset* p,const CEGUI::String& s){number(19);number(p==menu->m_pImageset);text(s);return *image;}
CEGUI::String imageString(const CEGUI::Image* p){number(20);number(p==image);return CEGUI::String("spy-image");}
void show(CEGUI::Window* p,bool b){number(21);number(id(p));number(b);}
CGameGlobals* getGlobals(){number(22);return globals;}
CStringTranslate* singleton(){number(23);return (CStringTranslate*)image;}
std::wstring translate(CStringTranslate* p,const wchar_t* key){number(24);number(p==(CStringTranslate*)image);std::wstring s(key);cap->addText(s);int n=(*translations)[s]++;if(input->translation==1||(input->translation==2&&n==0))return std::wstring();return input->translation==3?s+L" \u03a9 \u4e2d\u6587":s+L" translated";}
int price(CEquipment* p){number(25);number(p==item[0]);return input->enchantCount?123:-1;}
std::wstring formatInt(int value){number(26);number(value);return L"price";}
std::wstring formatFloat(float value){number(27);cap->add(&value,sizeof(value));return L"chance";}
float bits(unsigned value){float f;std::memcpy(&f,&value,sizeof(f));return f;}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;
 unsigned long long mem[(sizeof(CEnchantMenu)+7)/8]={0},cmem[(sizeof(CCharacter)+7)/8]={0},imem[(sizeof(CInventory)+7)/8]={0},rmem[3][(sizeof(CEquipmentRef)+7)/8]={0},emem[3][(sizeof(CEquipment)+7)/8]={0};
 unsigned long long wmem[430][(sizeof(CEGUI::Window)+7)/8]={0};
 menu=(CEnchantMenu*)mem;inventory=(CInventory*)imem;CCharacter* character=(CCharacter*)cmem;
 for(int i=0;i<430;++i){win[i]=(CEGUI::Window*)wmem[i];new(&win[i]->d_children)std::vector<CEGUI::Window*>;}
 for(int i=0;i<1;++i){menu->m_pSocketedSizeWindows[i]=i<1&&c.holes&&(i%3==0)?0:win[i];menu->m_pMainGlowWindows[i]=win[82+i];menu->m_pMainSocketGlowWindows[i]=win[164+i];menu->m_pMainStackWindows[i]=win[246+i];menu->m_aiSlotData[i]=19+11*i;for(unsigned j=0;j<c.children;++j)win[i]->d_children.push_back(win[420+j]);}
 menu->m_pSocketedIconParent=win[410];menu->m_pBackground=win[411];menu->m_pPanel=win[412];menu->m_pForeground=win[413];menu->m_pDescription=win[414];menu->m_iMode=c.service;
 for(unsigned j=0;j<c.children;++j)win[410]->d_children.push_back(win[420+j]);
 menu->m_bOpen=c.guard!=1;menu->m_pCharacter=c.guard==2?0:character;character->m_pInventory=c.guard==3?0:inventory;
 CEquipmentRef* refs[3];int slots[]={18,19,81};for(int i=0;i<3;++i){refs[i]=(CEquipmentRef*)rmem[i];item[i]=(CEquipment*)emem[i];refs[i]->m_pUnknown10=item[i];refs[i]->m_iSlot=slots[i];}
 equipped=refs[0];gems[0]=item[1];gems[1]=item[2];
 unsigned long long uiMem[(sizeof(CGameUI)+7)/8]={0},imageMem[(sizeof(CEGUI::Image)+7)/8]={0};
 image=(CEGUI::Image*)imageMem;menu->m_pGameUI=(CGameUI*)uiMem;menu->m_pImageset=(CEGUI::Imageset*)imageMem;
 unsigned long long globalMem[(sizeof(CGameGlobals)+7)/8]={0};globals=(CGameGlobals*)globalMem;std::map<std::wstring,int> localTranslations;translations=&localTranslations;
 const int counts[]={-1,0,2,3,5};item[0]->m_iUnknown344=counts[c.enchantCount];
 globals->m_iEnchanterMaxEnchantments=3;globals->m_iShrineMaxEnchantments=4;
 float base=5.0f,increment=2.0f,maximum=40.0f;
 if(c.probability==1)base=100.0f;else if(c.probability==2)base=-10.0f;else if(c.probability==3)base=bits(0x7fc12345);else if(c.probability==4)maximum=bits(0x7fc54321);else if(c.probability==5){base=bits(0x80000000);increment=bits(0x80000000);maximum=0.0f;}else if(c.probability==6)base=bits(0x7f800000);else if(c.probability==7)maximum=bits(0xff800000);
 globals->m_fEnchanterDisenchantBase=base;globals->m_fEnchanterDisenchantPerEnchant=increment;globals->m_fEnchanterDisenchantMax=maximum;
 globals->m_fShrineDisenchantBase=base+0.25f;globals->m_fShrineDisenchantPerEnchant=increment*2.0f;globals->m_fShrineDisenchantMax=maximum;
 void* vt[128]={0};vt[0x2b0/8]=(void*)&magical;*(void***)item[0]=vt;
 menu->m_pMainStackWindows[c.index]=(c.stackMode||c.empty)?win[246+c.index]:0;item[0]->m_iUnknown238=c.stackMode==5?37:(int)c.stackMode-2;item[0]->m_bUnknown348=c.identified;item[0]->m_iSocketCount=c.sockets;item[0]->m_SocketedEquipment.m_pData=gems;item[0]->m_SocketedEquipment.m_nCount=c.sockets;item[0]->m_SocketedEquipment.m_nCapacity=c.gemCapacity;
 for(int i=0;i<3;++i){item[i]->m_pIconWindow=c.create?0:win[416+i];win[416+i]->d_parent=win[419];}
 for(int i=0;i<1;++i)win[i]->d_parent=win[415];
 pos=CEGUI::UVector2(CEGUI::UDim(0.25f,c.coordinate?-11.75f:11.25f),CEGUI::UDim(0.5f,c.coordinate?-17.25f:17.75f));
 parentPos=CEGUI::UVector2(CEGUI::UDim(0.75f,c.coordinate?5.125f:-7.625f),CEGUI::UDim(-0.25f,c.coordinate?9.875f:-3.125f));
 TArrayList<CEquipmentRef*>& equipmentRefs=inventory->m_equipmentRefs;equipmentRefs.m_pData=refs;equipmentRefs.m_nCount=c.count;equipmentRefs.m_nCapacity=c.capacity;
 detour::Set d;TL_REDIRECT(d,queryFn,&query);
 d.redirect(getSizeFn,getSizeFn,&size);d.redirect(setSizeFn,setSizeFn,&setSize);d.redirect(removeFn,removeFn,&remove);d.redirect(frontFn,frontFn,&front);d.redirect(backFn,backFn,&back);d.redirect(propertyFn,propertyFn,&property);d.redirect(textFn,textFn,&setText);d.redirect(tooltipFn,tooltipFn,&tooltip);
 TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,createFn,&create);
 d.redirect(positionFn,positionFn,&position);d.redirect(setPositionFn,setPositionFn,&setPosition);d.redirect(addFn,addFn,&add);d.redirect(visibleFn,visibleFn,&visible);d.redirect(updateFn,updateFn,&update);d.redirect(imageFn,imageFn,&getImage);d.redirect(imageStringFn,imageStringFn,&imageString);
 d.redirect(showFn,showFn,&show);TL_REDIRECT(d,globalsFn,&getGlobals);TL_REDIRECT(d,translateSingletonFn,&singleton);TL_REDIRECT(d,translateFn,&translate);TL_REDIRECT(d,priceFn,&price);TL_REDIRECT(d,formatIntFn,&formatInt);TL_REDIRECT(d,formatFloatFn,&formatFloat);if(d.failed())_exit(42);
 for(int frame=0;frame<2;++frame){number(100+frame);if(frame==0){if(ours)autotest::invoke(out,&newLayout,menu);else autotest::invoke(out,&oldLayout,menu);}else{if(c.cross&&(c.service==0x15||c.service==0x16))menu->m_iMode=c.service==0x15?0x16:0x15;if(ours)newLayout(menu);else oldLayout(menu);}}
 for(int i=0;i<1;++i){number(win[i]->d_children.size());number(menu->m_pSocketedSizeWindows[i]!=0);}number(win[410]->d_children.size());for(int i=416;i<=418;++i){number(win[i]->d_mousePassThroughEnabled);number(win[i]->d_muted);number(id(win[i]->d_parent));}
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(enchant_layout_empty){
 autotest::Coverage coverage("enchant_layout_empty",(uint64_t)(uintptr_t)&oldLayout);int failures=0,total=0;
 const unsigned modes[]={0,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c};
 for(unsigned guard=0;guard<4;++guard)for(unsigned child=0;child<3;++child)for(unsigned holes=0;holes<2;++holes)for(unsigned mode=0;mode<9;++mode)for(unsigned translation=0;translation<4;++translation){
 Case c={guard,child,holes,0,0,0,0,1,0,0,0,0,0,1,0,modes[mode],0,0,0,translation,1,1};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;
 if(!ok){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    empty guard %u children %u holes %u service %u translation %u: exit %d/%d bytes %lu/%lu first %lu\n",guard,child,holes,c.service,translation,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);return 1;}
 }coverage.report(host);host->log("    enchant empty: %d cases\n",total);return failures;
}
