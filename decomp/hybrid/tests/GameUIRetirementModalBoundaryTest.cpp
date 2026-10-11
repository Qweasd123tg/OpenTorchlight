
// Supplemental old-consumer regression: retirement modal boundary in the actual
// public updateIngameUI entry. Expected prefix stops are not target acceptance.
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
TL_FUNCTION(rTranslator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(rTranslation,"_ZN16CStringTranslate18getTranslateStringEPKw")
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{unsigned state,present,sound,mode;int limit;unsigned level,emptyUntil,failAt,locale;};
struct World{unsigned long long ui[0x1a08/8],actors[2][0x400/8],targets[2][0x300/8],radio[0x800/8],cinema[0x100/8],menus[6][8],vt[16],actorVT[0x350/8],sounds[2],settings,globals[0x50/8];unsigned calls;bool thrown;World(){std::memset(this,0,sizeof(*this));}};
World*w;const Case*input;autotest::Capture*out;bool reachedBoundary;
struct PrefixStop {};
struct ModalStop {};
unsigned iteration, modalCalls, stateCalls;
const std::wstring* expectedTitle;
const std::wstring* expectedBody;
void require(bool ok){if(!ok)_exit(75);}
std::wstring valueFor(unsigned which){
 std::wstring value(input->locale==1?L"Перевод ":input->locale==2?L"翻译 ":L"translated ");
 value += which?L"You cannot retire until you reach level ":L"Retire";
 value.append(1024,which?L'B':L'T');
 value.append(L"\0Ω",2);
 return value;
}
void stop(){reachedBoundary=true;throw PrefixStop();}
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
void state(void*p,unsigned value){++stateCalls;n(17);n(actorID(p));n(value);at<unsigned>(p,0x330)=value;}
void defaultMenu(void*p,bool value){n(18);n(menuID(p));n(value);}
void slots(void*p){n(19);n(p==w->ui);stop();}
void*global(){n(20);return w->globals;}
std::wstring format(int value){n(21);n(value);return L"limit";}
void modal(void*p,std::wstring title,std::wstring body,bool choice){
 ++modalCalls;n(22);n(p==w->ui);out->addText(title);out->addText(body);n(choice);
 require(p==w->ui&&!choice&&title==*expectedTitle&&body==*expectedBody);
 // Detach both real by-value strings. The caller must destroy these allocations
 // on the exceptional path as well as on a normal return from the modal stub.
 title.assign(4096,L'X');body.assign(8192,L'Y');
 if(iteration==1)throw ModalStop();
}
void*actor(){return at<void*>(w->ui,0x38);}void*target(unsigned offset){return at<void*>(actor(),offset);}
void* translator(){n(40);return w->globals;}
std::wstring translation(void* who,const wchar_t* key){
 require(who==w->globals);std::wstring source(key);
 unsigned which=source==L"Retire"?0:1;
 require(which==0||source==L"You cannot retire until you reach level ");
 n(41);n(which);++w->calls;return valueFor(which);
}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;reachedBoundary=false;
 std::wstring titleWitness=valueFor(0),bodyWitness=valueFor(1)+L"limit";
 expectedTitle=&titleWitness;expectedBody=&bodyWitness;
 at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x38)=w->actors[0];w->actorVT[0x348/8]=reinterpret_cast<unsigned long long>(&state);w->vt[0x18/8]=reinterpret_cast<unsigned long long>(&defaultMenu);w->vt[0x38/8]=reinterpret_cast<unsigned long long>(&owner);w->vt[0x40/8]=reinterpret_cast<unsigned long long>(&open);
 for(unsigned i=0;i<2;++i){at<void*>(w->actors[i],0)=w->actorVT;at<unsigned>(w->actors[i],0x330)=c.state;at<unsigned>(w->actors[i],0x100)=c.level+i;at<void*>(w->actors[i],0x340)=c.present?w->targets[i]:NULL;at<void*>(w->actors[i],0x350)=c.present?w->targets[i]:NULL;at<void*>(w->targets[i],0x298)=c.sound?&w->sounds[i]:NULL;}
 const unsigned offsets[]={0x4d8,0x4f0,0x500,0x4f8,0x508,0x578};for(unsigned i=0;i<6;++i){w->menus[i][0]=reinterpret_cast<unsigned long long>(w->vt);at<void*>(w->ui,offsets[i])=w->menus[i];}
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned i=0;i<4;++i)*reinterpret_cast<unsigned char*>(guards[i])=1;
 at<int>(w->globals,0x48)=c.limit;*reinterpret_cast<unsigned char*>(0x14b9bd8)=0;*reinterpret_cast<unsigned char*>(0x14b9be0)=0;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,updateSlots,&slots);TL_REDIRECT(patches,closeAll,&all);TL_REDIRECT(patches,queueSound,&sound);TL_REDIRECT(patches,merchantPlayer,&player);TL_REDIRECT(patches,combinePlayer,&player);TL_REDIRECT(patches,enchantPlayer,&player);TL_REDIRECT(patches,stashPlayer,&player);TL_REDIRECT(patches,enchantOwner,&itemOwner);TL_REDIRECT(patches,enchantOpen,&enchanting);TL_REDIRECT(patches,gameGlobals,&global);TL_REDIRECT(patches,formatLimit,&format);TL_REDIRECT(patches,modalDialog,&modal);TL_REDIRECT(patches,rTranslator,&translator);TL_REDIRECT(patches,rTranslation,&translation);if(patches.failed())_exit(42);
 // Warm lazy caches and exception runtime, then inject one modal failure and
 // make two successful retries. Success means reaching the original updateSlots
 // prefix boundary, not completion of this large frame entry.
 long long stableHeap=0;
 for(iteration=0;iteration<4;++iteration){
  at<unsigned>(w->actors[0],0x330)=at<unsigned>(w->actors[1],0x330)=0x1b;
  reachedBoundary=false;modalCalls=stateCalls=0;
  autotest::Capture invocation;invocation.reset();out=&invocation;
  unsigned caught=0;
  try{
   autotest::invoke(invocation,expected?&restoredUpdate:&originalUpdate,
                    static_cast<void*>(w->ui),0.125f,static_cast<void*>(NULL),static_cast<void*>(NULL));
  }catch(const ModalStop&){caught=1;}
   catch(const PrefixStop&){caught=2;}
   catch(...){_exit(76);}
  require(invocation.callStarted==1&&!invocation.callCompleted&&!invocation.issue);
  require(modalCalls==1&&w->calls==2);
  require(caught==(iteration==1?1u:2u));
  require(reachedBoundary==(iteration!=1));
  require(stateCalls==(iteration==1?0u:1u));
  require(at<unsigned>(w->actors[0],0x330)==(iteration==1?0x1bu:2u));
  require(actor()==w->actors[0]);
  require(titleWitness==valueFor(0)&&bodyWitness==valueFor(1)+L"limit");
  // All temporary witnesses above are destroyed before this measurement.
  long long heap=mallinfo().uordblks;
  if(iteration==0)stableHeap=heap;else require(heap==stableHeap);
  n(iteration);n(caught);n(modalCalls);n(stateCalls);n(w->calls);
  out->add(&heap,sizeof(heap));
  if(iteration==0){capture.callTarget=invocation.callTarget;capture.callStarted=1;capture.callCompleted=0;}
  else require(capture.callTarget==invocation.callTarget);
  capture.add(invocation.data,invocation.length);
 }
 out=&capture;
}

void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_retirement_modal_boundary_unwind){
 for(unsigned locale=0;locale<3;++locale){
  Case c={0x1b,1,0,0,60,30,0,0,locale};autotest::Outcome a,b;
  autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);
  bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&
   !a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&
   !a.capture.callCompleted&&!b.capture.callCompleted&&
   a.capture.callTarget==static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&originalUpdate))&&
   host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&
   a.capture.length==b.capture.length&&
   !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
  if(!ok){host->log("    retirement modal boundary locale %u status %d/%d issues %u/%u bytes %lu/%lu\n",
   locale,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,
   (unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}
 }
 host->log("    EXPECTED RETIREMENT PREFIX: 3 locales; warm, modal unwind, two retries; string heap stable; not normal completion coverage\n");
 return 0;
}
