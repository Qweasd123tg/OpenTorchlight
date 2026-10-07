// Bounded collaborator-spy differential probe. Not full behavioral acceptance.
#include <cstring>
#include <string>
#include <map>
#include <vector>
#define private public
#define protected public
#include <CEGUI.h>
#include "Equipment.h"
#include "GameUI.h"
#include "MerchantMenu.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalMerchant, (CMerchantMenu*,CEquipment*,int,int), "_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii")
extern "C" void restoredMerchant(CMerchantMenu*,CEquipment*,int,int) __asm__("_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii");
TL_FUNCTION(mpIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(mpCreate,"_ZN10CEquipment10createIconER7CGameUIb")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(mpPosition,"_ZNK5CEGUI6Window11getPositionEv");
IMPORT(mpSize,"_ZNK5CEGUI6Window7getSizeEv");
IMPORT(mpSetPosition,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(mpSetSize,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(mpRemove,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(mpAdd,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(mpFront,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(mpProperty,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(mpImage,"_ZNK5CEGUI8Imageset8getImageERKNS_6StringE");
IMPORT(mpVisible,"_ZN5CEGUI6Window10setVisibleEb");
IMPORT(mpText,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMPORT(mpImageString,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
#undef IMPORT
namespace {
struct Case {unsigned sockets;bool identified;unsigned create;unsigned count,capacity,mode,stackMode,coordinate;};
autotest::Capture* cap;const Case* input;CEGUI::Window* windows[10];CEGUI::Image* image;CEGUI::UVector2 pos;CMerchantMenu* currentMenu;int currentSlot;CEquipment* mainItem;CEquipment* children[2];
void number(int x){cap->add(&x,sizeof(x));}
int id(const CEGUI::Window* p){for(int i=0;i<10;++i)if(p==windows[i])return i;return p?99:-1;}
void text(const CEGUI::String& s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void vec(const CEGUI::UVector2& v){cap->add(&v,sizeof(v));}
const CEGUI::UVector2& getPosition(const CEGUI::Window* p){number(1);number(id(p));return pos;}
CEGUI::UVector2 getSize(const CEGUI::Window* p){number(2);number(id(p));return CEGUI::UVector2(CEGUI::UDim(0,32+id(p)),CEGUI::UDim(0,48+id(p)));}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){number(3);number(id(p));vec(v);}
void setSize(CEGUI::Window* p,const CEGUI::UVector2& v){number(4);number(id(p));vec(v);}
void remove(CEGUI::Window* p,CEGUI::Window* c){number(5);number(id(p));number(id(c));c->d_parent=0;}
void add(CEGUI::Window* p,CEGUI::Window* c){number(6);number(id(p));number(id(c));c->d_parent=p;}
void front(CEGUI::Window* p){number(7);number(id(p));}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){number(8);int i=-1;for(int n=0;n<10;++n)if(static_cast<CEGUI::PropertySet*>(windows[n])==p)i=n;number(i);text(k);text(v);}
const CEGUI::Image& getImage(const CEGUI::Imageset* imageset,const CEGUI::String& n){number(9);number(imageset==currentMenu->m_pImageset);text(n);return *image;}
CEGUI::String imageString(const CEGUI::Image* p){number(10);number(p==image);return CEGUI::String("spy-image");}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(11);number(p==static_cast<CBaseUnit*>(mainItem));number(t);return (input->mode==3&&int(t)==0x36)||(input->mode==5&&int(t)==0x37);}
bool canEquip(CEquipment* p,CCharacter* who,bool b){number(12);number(p==mainItem);number(who==currentMenu->m_pCanEquipCharacter);number(b);return input->mode!=1&&input->mode!=2;}
bool magical(CEquipment* p){number(13);number(p==mainItem);return input->mode==2||input->mode==4||input->mode==5;}
void visible(CEGUI::Window* p,bool b){number(15);number(id(p));number(b);}
void setText(CEGUI::Window* p,const CEGUI::String& s){number(16);number(id(p));text(s);}
void create(CEquipment* p,CGameUI&,bool b){number(14);number(b);if(input->create==3)currentMenu->m_pSlotWindows[currentSlot]=windows[8];if(input->create==2){p->m_pIconWindow=0;return;}p->m_pIconWindow=windows[p==mainItem?0:p==children[0]?6:9];}
void side(const Case& c,bool ours,autotest::Capture& out){
 input=&c;cap=&out;
 unsigned long long menuMem[(0x3478+7)/8]={0},itemMem[(sizeof(CEquipment)+7)/8]={0},childMem[2][(sizeof(CEquipment)+7)/8]={0},uiMem[0x1a08/8+1]={0},wmem[10][(sizeof(CEGUI::Window)+7)/8]={0},imem[(sizeof(CEGUI::Image)+7)/8]={0};
 CMerchantMenu* m=(CMerchantMenu*)menuMem;CEquipment* item=(CEquipment*)itemMem;mainItem=item;children[0]=(CEquipment*)childMem[0];children[1]=(CEquipment*)childMem[1];for(int i=0;i<10;++i)windows[i]=(CEGUI::Window*)wmem[i];image=(CEGUI::Image*)imem;
 void* vtable[128]={0};vtable[0x2f8/8]=(void*)&canEquip;vtable[0x2b0/8]=(void*)&magical;*(void***)item=vtable;
 const int slot=1,data=3;currentMenu=m;currentSlot=slot;
 m->m_pGameUI=(CGameUI*)uiMem;m->m_pCanEquipCharacter=(CCharacter*)windows[5];m->m_pSlotWindows[slot]=windows[1];m->m_pSocketedSizeWindows[slot]=windows[8];m->m_pSocketedIconParent=windows[7];m->m_pSocketGlowWindows[slot]=windows[2];m->m_pUnidentifiedWindows[slot]=windows[3];m->m_pSlotGlowWindows[slot]=windows[4];m->m_pStackWindows[slot]=c.stackMode?windows[9]:0;m->m_pImageset=(CEGUI::Imageset*)imem;
 item->m_pIconWindow=c.create?0:windows[0];item->m_bUnknown348=c.identified;item->m_iSocketCount=c.sockets;item->m_iUnknown238=c.stackMode<4?int(c.stackMode)-1:37;
 item->m_SocketedEquipment.m_pData=children;item->m_SocketedEquipment.m_nCount=c.count;item->m_SocketedEquipment.m_nCapacity=c.capacity;
 for(int k=0;k<2;++k){children[k]->m_pIconWindow=c.create?0:windows[k?9:6];windows[k?9:6]->d_parent=windows[5];}
 windows[0]->d_parent=windows[5];pos=CEGUI::UVector2(CEGUI::UDim(0,c.coordinate?-11.75f:11),CEGUI::UDim(0,c.coordinate?-17.25f:17));
 detour::Set p;TL_REDIRECT(p,mpIsa,&isa);TL_REDIRECT(p,mpCreate,&create);
 p.redirect(mpPosition,mpPosition,&getPosition);p.redirect(mpSize,mpSize,&getSize);p.redirect(mpSetPosition,mpSetPosition,&setPosition);p.redirect(mpSetSize,mpSetSize,&setSize);p.redirect(mpRemove,mpRemove,&remove);p.redirect(mpAdd,mpAdd,&add);p.redirect(mpFront,mpFront,&front);p.redirect(mpProperty,mpProperty,&property);p.redirect(mpImage,mpImage,&getImage);p.redirect(mpImageString,mpImageString,&imageString);p.redirect(mpVisible,mpVisible,&visible);p.redirect(mpText,mpText,&setText);
 if(p.failed())_exit(42);
 if(ours)autotest::invoke(out,&restoredMerchant,m,item,slot,data);else autotest::invoke(out,&originalMerchant,m,item,slot,data);
 number(100);number(windows[0]->d_mousePassThroughEnabled);number(windows[0]->d_riseOnClick);number(windows[0]->d_muted);number(windows[0]->d_userData==&m->m_aiSlotData[data]);for(int k=0;k<2;++k){number(windows[k?9:6]->d_mousePassThroughEnabled);number(windows[k?9:6]->d_riseOnClick);number(windows[k?9:6]->d_muted);}
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(merchant_pet_slot_differential){
 int failures=0;unsigned total=0;autotest::Coverage coverage("merchant_pet_slot_differential",(uint64_t)(uintptr_t)&originalMerchant);for(unsigned s=0;s<3;++s)for(unsigned ident=0;ident<2;++ident)for(unsigned cr=0;cr<4;++cr)for(unsigned cnt=0;cnt<3;++cnt)for(unsigned capacity=0;capacity<3;++capacity)for(unsigned mode=0;mode<6;++mode)for(unsigned sm=0;sm<5;++sm)for(unsigned xy=0;xy<2;++xy){Case c={s,bool(ident),cr,cnt,capacity,mode,sm,xy};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
 int pair=coverage.observe(host,x,y);++total;
 bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;
 size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;
 if(!ok)host->log("    merchant sockets %u identified %u create %u count %u capacity %u mode %u stack %u coordinate %u: exit %d/%d bytes %lu/%lu first %lu %s\n",s,ident,cr,cnt,capacity,mode,sm,xy,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first,ok?"same":"DIFFERENT");if(!ok)++failures;
 }coverage.report(host);host->log("    merchant pet slot: %u bounded UI-spy cases, %d differences\n",total,failures);return failures;
}
