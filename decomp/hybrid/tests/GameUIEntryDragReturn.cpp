
#include "GameUIUpdate.h"
// Original frame prefix through opening seven NPC/item menu states.
#include <cstring>
#include <stdexcept>
#include <string>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void restoredUpdate(void*,float,void*,void*) __asm__("_ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(updateSlots,"_ZN7CGameUI11updateSlotsEv")
TL_FUNCTION(closeAll,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(queueSound,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(merchantPlayer,"_ZN13CMerchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(combinePlayer,"_ZN12CCombineMenu9setPlayerEP10CCharacter")
TL_FUNCTION(enchantPlayer,"_ZN12CEnchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(stashPlayer,"_ZN10CStashMenu9setPlayerEP10CCharacter")
TL_FUNCTION(enchantOwner,"_ZN12CEnchantMenu12setOwnerItemEP5CItem")
TL_FUNCTION(enchantOpen,"_ZN12CEnchantMenu7setOpenEb8EAIState")
TL_FUNCTION(gameGlobals,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(formatLimit,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(modalDialog,"_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(dragISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dragReturn,"_ZN7CGameUI17returnDraggedItemEv")
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{unsigned state,present,sound,mode;int limit;unsigned level;unsigned inventoryOpen,serviceOpen,drag,dragOwner,dragType;};
struct World{unsigned long long ui[0x1a08/8],actors[2][0x400/8],targets[2][0x300/8],radio[0x800/8],cinema[0x100/8],menus[6][8],vt[16],actorVT[0x350/8],sounds[2],settings,globals[0x50/8];World(){std::memset(this,0,sizeof(*this));}};
World*w;const Case*input;autotest::Capture*out;bool reachedBoundary;
void stop(){reachedBoundary=true;throw std::runtime_error("gameui boundary");}
void n(unsigned x){out->add(&x,sizeof(x));}void real(float x){out->add(&x,sizeof(x));}
unsigned menuID(void*p){for(unsigned i=0;i<6;++i)if(p==w->menus[i])return i;return 99;}
unsigned actorID(void*p){return p==w->actors[0]?0:p==w->actors[1]?1:99;}
unsigned targetID(void*p){return p==w->targets[0]?0:p==w->targets[1]?1:99;}
void swapActor(unsigned mode){if(input->mode==mode)at<void*>(w->ui,0x38)=w->actors[1];}
int zero(void*,unsigned){return 0;}bool yes(void*,unsigned){return true;}
void all(void*p){n(10);n(p==w->ui);swapActor(1);}
void sound(void*p,int sample,float a,float b){n(11);n(p==&w->sounds[0]?0:1);n(sample);real(a);real(b);}
void open(void*p,bool value){n(12);n(menuID(p));n(value);if(menuID(p)==0)swapActor(2);}
void owner(void*p,void*who){n(13);n(menuID(p));n(targetID(who));swapActor(3);}
void player(void*p,void*who){n(14);n(menuID(p));n(actorID(who));swapActor(4);}
void itemOwner(void*p,void*who){n(15);n(menuID(p));n(targetID(who));swapActor(3);}
void enchanting(void*p,bool value,unsigned state){n(16);n(menuID(p));n(value);n(state);}
void state(void*p,unsigned value){n(17);n(actorID(p));n(value);at<unsigned>(p,0x330)=value;}
void defaultMenu(void*p,bool value){n(18);n(menuID(p));n(value);}
void slots(void*p){n(19);n(p==w->ui);stop();}
void*global(){n(20);return w->globals;}
std::wstring format(int value){n(21);n(value);return L"limit";}
void modal(void*p,std::wstring title,std::wstring body,bool choice){n(22);n(p==w->ui);n(title.size());out->add(title.data(),title.size()*sizeof(wchar_t));n(body.size());out->add(body.data(),body.size()*sizeof(wchar_t));n(choice);}
bool isOpen(void*p){n(23);unsigned id=menuID(p);n(id);return id==0?input->inventoryOpen:input->serviceOpen;}
void*getOwner(void*p){n(24);n(menuID(p));return input->present?w->targets[0]:NULL;}
void*actor(){return at<void*>(w->ui,0x38);}void*target(unsigned offset){return at<void*>(actor(),offset);}
void model(){gameui_detail::Labels labels={"","","",""};gameui_detail::Frame frame(w->ui,NULL,NULL,0.125f,labels);frame.serviceMenus(L"Retire",L"Cannot retire");frame.questAndFishing();}
bool dragIsA(void* p,unsigned type){n(40);n(p==w->targets[0]);n(type);return input->dragType;}
void dragReturnNow(void* p){n(41);n(p==w->ui);at<void*>(w->ui,0xb8)=NULL;}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;reachedBoundary=false;
 at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x38)=w->actors[0];w->actorVT[0x348/8]=reinterpret_cast<unsigned long long>(&state);w->vt[0x10/8]=reinterpret_cast<unsigned long long>(&getOwner);w->vt[0x28/8]=reinterpret_cast<unsigned long long>(&isOpen);w->vt[0x18/8]=reinterpret_cast<unsigned long long>(&defaultMenu);w->vt[0x38/8]=reinterpret_cast<unsigned long long>(&owner);w->vt[0x40/8]=reinterpret_cast<unsigned long long>(&open);
 for(unsigned i=0;i<2;++i){at<void*>(w->actors[i],0)=w->actorVT;at<unsigned>(w->actors[i],0x330)=c.state;at<unsigned>(w->actors[i],0x100)=c.level+i;at<void*>(w->actors[i],0x340)=c.present?w->targets[i]:NULL;at<void*>(w->actors[i],0x350)=c.present?w->targets[i]:NULL;at<void*>(w->targets[i],0x298)=c.sound?&w->sounds[i]:NULL;}
 const unsigned offsets[]={0x4d8,0x4f0,0x500,0x4f8,0x508,0x578};for(unsigned i=0;i<6;++i){w->menus[i][0]=reinterpret_cast<unsigned long long>(w->vt);at<void*>(w->ui,offsets[i])=w->menus[i];}
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
 at<int>(w->globals,0x48)=c.limit;if(c.state==0x1b){new(reinterpret_cast<void*>(0x14b9bf0))std::wstring(L"Retire");new(reinterpret_cast<void*>(0x14b9be8))std::wstring(L"Cannot retire");*reinterpret_cast<unsigned char*>(0x14b9bd8)=1;*reinterpret_cast<unsigned char*>(0x14b9be0)=1;}
 at<void*>(w->ui,0xb8)=c.drag?w->targets[1]:NULL;at<void*>(w->ui,0xc8)=c.dragOwner?w->targets[0]:NULL;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,updateSlots,&slots);TL_REDIRECT(patches,closeAll,&all);TL_REDIRECT(patches,queueSound,&sound);TL_REDIRECT(patches,merchantPlayer,&player);TL_REDIRECT(patches,combinePlayer,&player);TL_REDIRECT(patches,enchantPlayer,&player);TL_REDIRECT(patches,stashPlayer,&player);TL_REDIRECT(patches,enchantOwner,&itemOwner);TL_REDIRECT(patches,enchantOpen,&enchanting);TL_REDIRECT(patches,gameGlobals,&global);TL_REDIRECT(patches,formatLimit,&format);TL_REDIRECT(patches,modalDialog,&modal);TL_REDIRECT(patches,dragISA,&dragIsA);TL_REDIRECT(patches,dragReturn,&dragReturnNow);if(patches.failed())_exit(42);
 try{if(expected)restoredUpdate(w->ui,0.125f,NULL,NULL);else originalUpdate(w->ui,0.125f,NULL,NULL);_exit(43);}catch(const std::runtime_error&e){if(!reachedBoundary||std::strcmp(e.what(),"gameui boundary")!=0)_exit(44);}n(at<unsigned>(w->actors[0],0x330));n(at<unsigned>(w->actors[1],0x330));n(actorID(actor()));
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_entry_recovered_drag_return){
 int failures=0;unsigned count=0;const unsigned states[]={0x14,0x1c,0x12,0x26,0x27};
 for(unsigned st=0;st<5;++st)for(unsigned inv=0;inv<2;++inv)for(unsigned menu=0;menu<2;++menu)
 for(unsigned present=0;present<2;++present)for(unsigned sound=0;sound<2;++sound)for(unsigned mode=0;mode<5;++mode)for(unsigned drag=0;drag<2;++drag)for(unsigned owner=0;owner<2;++owner)for(unsigned type=0;type<2;++type){
 Case c={states[st],present,sound,mode,-1,30,inv,menu,drag,owner,type};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);
 bool ok=a.reportValid&&b.reportValid&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
 TL_CHECK(failures,ok);if(!ok){host->log(" closing case %u state %x inv %u menu %u present %u sound %u mode %u status %d/%d sizes %lu/%lu\n",count,c.state,inv,menu,present,sound,mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return failures;}++count;
 }host->log("    recovered closing menus: %u original-compared cases\n",count);return failures;
}
