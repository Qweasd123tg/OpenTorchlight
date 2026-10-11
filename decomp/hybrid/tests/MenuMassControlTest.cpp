// Branch-complete dispatch cases include reentrant collaborators and exact
// object state. Every receipt belongs to one actual original/replacement call.
#include <cstring>
#include <string>
#include <vector>
#include <limits>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,original0,(void*,int,std::wstring),"_ZN12COptionsMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate0(void*,int,std::wstring) __asm__("_ZN12COptionsMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original1,(void*,int,std::wstring),"_ZN10CModalMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate1(void*,int,std::wstring) __asm__("_ZN10CModalMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original2,(void*,void*),"_ZN8CDieMenu17handle_ExitButtonERKN5CEGUI9EventArgsE")
extern "C" bool candidate2(void*,void*) __asm__("_ZN8CDieMenu17handle_ExitButtonERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original3,(void*,void*),"_ZN8CDieMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
extern "C" bool candidate3(void*,void*) __asm__("_ZN8CDieMenu18handle_CloseButtonERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original4,(void*,void*),"_ZN12CFishingMenu14handle_onClickERKN5CEGUI9EventArgsE")
extern "C" bool candidate4(void*,void*) __asm__("_ZN12CFishingMenu14handle_onClickERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original5,(void*,int),"_ZN12CFishingMenu7onClickE15ELayoutFunction")
extern "C" bool candidate5(void*,int) __asm__("_ZN12CFishingMenu7onClickE15ELayoutFunction");
TL_ORIGINAL(bool,original6,(void*,void*),"_ZN10CQuestMenu14handle_onClickERKN5CEGUI9EventArgsE")
extern "C" bool candidate6(void*,void*) __asm__("_ZN10CQuestMenu14handle_onClickERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original7,(void*,int,std::wstring),"_ZN11CDialogMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate7(void*,int,std::wstring) __asm__("_ZN11CDialogMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original8,(void*,int,std::wstring),"_ZN9CMainMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate8(void*,int,std::wstring) __asm__("_ZN9CMainMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original9,(void*,int,std::wstring),"_ZN15CDifficultyMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate9(void*,int,std::wstring) __asm__("_ZN15CDifficultyMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original10,(void*,int,std::wstring),"_ZN17CContinueGameMenu13onDoubleClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate10(void*,int,std::wstring) __asm__("_ZN17CContinueGameMenu13onDoubleClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original11,(void*,int,std::wstring),"_ZN17CContinueGameMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate11(void*,int,std::wstring) __asm__("_ZN17CContinueGameMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(bool,original12,(void*,void*),"_ZN13CDropdownMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
extern "C" bool candidate12(void*,void*) __asm__("_ZN13CDropdownMenu18handle_CloseButtonERKN5CEGUI9EventArgsE");
TL_FUNCTION(target_closeAll,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(target_toggleSettings,"_ZN7CGameUI14toggleSettingsEv")
TL_FUNCTION(target_targetItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(target_giveQuest,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(target_completeQuest,"_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(target_canLoad,"_ZN7CGameUI7canLoadEv")
TL_FUNCTION(target_requestState,"_ZN7CGameUI19requestSetGameStateE10EGameState5EMenu")
TL_FUNCTION(target_scrollUp,"_ZN17CContinueGameMenu8scrollUpEv")
TL_FUNCTION(target_scrollDown,"_ZN17CContinueGameMenu10scrollDownEv")
TL_FUNCTION(target_selectCharacter,"_ZN17CContinueGameMenu15selectCharacterEib")
TL_FUNCTION(target_deleteCharacter,"_ZN17CContinueGameMenu15deleteCharacterEv")
TL_FUNCTION(target_removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" char target_visible[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char target_isVisible[] __asm__("_ZNK5CEGUI6Window9isVisibleEb");

namespace {
struct Case {unsigned op,mode,variant;int event,button;bool opened,closing,flag;float hp;};
const Case* input;autotest::Capture* capture;void* objects[12];void* activeSelf;
void num(unsigned x){capture->add(&x,4);}unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<12;++i)if(objects[i]==p)return i+1;return 999;}
void eventCall(unsigned n,void*p){num(n);num(identity(p));}
void ptrAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void uintAt(void*p,unsigned at,unsigned v){std::memcpy(static_cast<char*>(p)+at,&v,4);}
void* ptr(void*p,unsigned at){void*v;std::memcpy(&v,static_cast<char*>(p)+at,8);return v;}
void change(){if(input->mode==5)ptrAt(objects[1],0x38,objects[4]);if(input->mode==6){ptrAt(activeSelf,0x40,objects[2]);ptrAt(activeSelf,0x38,objects[2]);}}
void ai(void*p,int state){eventCall(1,p);num(state);change();}
void fish(void*p){eventCall(2,p);change();}
bool clicked(void*p,int id){eventCall(3,p);num(id);return input->flag;}
void open(void*p,bool flag){eventCall(4,p);num(flag);change();}
void closeAll(void*p){eventCall(5,p);num(static_cast<unsigned char*>(p)[0x12f9]);change();}
void toggleSettings(void*p){eventCall(6,p);change();}
void targetItem(void*p,void*item){eventCall(7,p);num(identity(item));change();}
long long giveQuest(void*p,void*q,void*u,bool b){eventCall(8,p);num(identity(q));num(identity(u));num(b);return -1;}
long long completeQuest(void*p,void*q){eventCall(9,p);num(identity(q));return 0x1234567812345678LL;}
bool canLoad(void*p){eventCall(10,p);change();return input->flag;}
void requestState(void*p,int state,int menu){eventCall(11,p);num(state);num(menu);change();}
void scrollUp(void*p){eventCall(12,p);}void scrollDown(void*p){eventCall(13,p);}
bool selectCharacter(void*p,int index,bool b){eventCall(14,p);num(index);num(b);return input->flag;}
void deleteCharacter(void*p){eventCall(15,p);}
void visible(void*p,bool b){eventCall(16,p);num(b);change();}
bool isVisible(void*p,bool b){eventCall(17,p);num(b);return input->flag;}
void accepted(void*p,void*d){eventCall(18,p);num(identity(d));}
void declined(void*p,void*d){eventCall(19,p);num(identity(d));}
void removeSafe(void*p,void*safe,unsigned index){eventCall(20,p);num(index);num(static_cast<char*>(safe)-static_cast<char*>(objects[5]));}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;
 unsigned long long self[128]={0},ui[2][840]={{0}},players[2][360]={{0}},client[1900]={0},window[2][300]={{0}},dialog[32]={0},saved[64]={0},misc[2][32]={{0}},event[16]={0};
 objects[0]=self;objects[1]=ui[0];objects[2]=ui[1];objects[3]=players[0];objects[4]=players[1];objects[5]=client;objects[6]=window[0];objects[7]=window[1];objects[8]=dialog;objects[9]=saved;objects[10]=misc[0];objects[11]=misc[1];activeSelf=self;
 void* menuTable[20]={0};void* playerTable[140]={0};
 menuTable[6]=reinterpret_cast<void*>(&clicked);menuTable[7]=reinterpret_cast<void*>(&open);menuTable[13]=reinterpret_cast<void*>(&clicked);
 playerTable[0x348/8]=reinterpret_cast<void*>(&ai);playerTable[0x340/8]=reinterpret_cast<void*>(&fish);
 ptrAt(self,0,menuTable);ptrAt(players[0],0,playerTable);ptrAt(players[1],0,playerTable);
 reinterpret_cast<char*>(self)[0x30]=c.opened;reinterpret_cast<char*>(self)[0x31]=c.closing;reinterpret_cast<char*>(self)[0x32]=c.variant&1;
 ptrAt(self,0x40,ui[0]);ptrAt(ui[0],0x38,players[0]);ptrAt(ui[1],0x38,players[1]);
 ptrAt(ui[0],0x1920,client);ptrAt(ui[1],0x1920,client);uintAt(players[0],0x330,c.mode==8?34:2);
 ptrAt(players[0],0x868,misc[0]);ptrAt(players[1],0x868,misc[1]);
 ptrAt(dialog,0x10,misc[1]);uintAt(dialog,0x70,c.mode==8?3:2);
 ptrAt(self,0xc0,misc[0]);ptrAt(self,0xe8,c.mode==3?NULL:reinterpret_cast<void*>(&accepted));ptrAt(self,0xf0,c.mode==4?NULL:reinterpret_cast<void*>(&declined));
 if(c.op==7)ptrAt(self,0xf0,c.mode==3?NULL:dialog);
 if(c.op==8){ptrAt(self,0xe8,window[0]);ptrAt(self,0xf0,c.mode==3?NULL:window[1]);}
 if(c.op==9){ptrAt(self,0xc8,window[0]);reinterpret_cast<char*>(self)[0xd0]=c.flag;reinterpret_cast<char*>(window[0])[0x732]=(c.variant&1)!=0;}
 if(c.op==4||c.op==5){ptrAt(self,0x38,ui[0]);reinterpret_cast<char*>(self)[0x30]=c.opened;}
 if(c.op==10||c.op==11){
  std::vector<void*>*v=new(reinterpret_cast<char*>(self)+0x1e8)std::vector<void*>;
  if(c.mode!=9||c.op==11)v->push_back(saved);uintAt(self,0xc8,0);std::memcpy(reinterpret_cast<char*>(saved)+0xe0,&c.hp,4);ptrAt(self,0x198,window[0]);
 }
 // All four safe-pointer slots have observable independent null/non-null states.
 const unsigned safeOffsets[]={0x1f8,0x1e8,0x1c8,0x1d8};
 for(unsigned i=0;i<4;++i){ptrAt(client,safeOffsets[i],(c.variant&(1u<<i))?NULL:misc[i%2]);uintAt(client,safeOffsets[i]+8,0x80000000u+c.variant+i);}
 ptrAt(event,0x10,c.mode==2?NULL:window[0]);uintAt(event,0x28,c.button);ptrAt(window[0],0x1d8,&c.event);
 std::wstring text=c.flag?L"menu payload":L"";
 detour::Set patches;
 TL_REDIRECT(patches,target_closeAll,&closeAll);
 TL_REDIRECT(patches,target_toggleSettings,&toggleSettings);
 TL_REDIRECT(patches,target_targetItem,&targetItem);
 TL_REDIRECT(patches,target_giveQuest,&giveQuest);
 TL_REDIRECT(patches,target_completeQuest,&completeQuest);
 TL_REDIRECT(patches,target_canLoad,&canLoad);
 TL_REDIRECT(patches,target_requestState,&requestState);
 TL_REDIRECT(patches,target_scrollUp,&scrollUp);
 TL_REDIRECT(patches,target_scrollDown,&scrollDown);
 TL_REDIRECT(patches,target_selectCharacter,&selectCharacter);
 TL_REDIRECT(patches,target_deleteCharacter,&deleteCharacter);
 TL_REDIRECT(patches,target_removeSafe,&removeSafe);
 patches.redirect(target_visible,target_visible,&visible);
 patches.redirect(target_isVisible,target_isVisible,&isVisible);
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.event,text);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,c.event,text);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,event);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,event);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,event);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,c.event);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,event);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self,c.event,text);break;
 case 8:autotest::invoke(out,ours?candidate8:original8,self,c.event,text);break;
 case 9:autotest::invoke(out,ours?candidate9:original9,self,c.event,text);break;
 case 10:autotest::invoke(out,ours?candidate10:original10,self,c.event,text);break;
 case 11:autotest::invoke(out,ours?candidate11:original11,self,c.event,text);break;
 case 12:autotest::invoke(out,ours?candidate12:original12,self,event);break;

 }
 // Vectors are encoded by logical contents, independent of allocation addresses.
 if(c.op==10||c.op==11){std::vector<void*>*v=reinterpret_cast<std::vector<void*>*>(reinterpret_cast<char*>(self)+0x1e8);num(v->size());for(unsigned i=0;i<v->size();++i)num(identity((*v)[i]));v->~vector();std::memset(reinterpret_cast<char*>(self)+0x1e8,0,24);}
 out.add(self,sizeof(self));out.add(ui,sizeof(ui));out.add(players,sizeof(players));out.add(client,sizeof(client));out.add(dialog,sizeof(dialog));out.add(window,sizeof(window));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host*host,unsigned first,unsigned last,const char*name){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8,(uint64_t)(uintptr_t)&original9,(uint64_t)(uintptr_t)&original10,(uint64_t)(uintptr_t)&original11,(uint64_t)(uintptr_t)&original12};
 const int events[]={-1,0,1,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,34,64,65,66,67,90,94,95,0x7fffffff};
 const float hp[]={0.0f,-1.0f,1.0f,100.25f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
 for(unsigned op=first;op<last;++op){autotest::Coverage coverage(name,addresses[op]);
  for(unsigned n=0;n<1080;++n){Case c={op,n%10,(n/10)%16,events[(n/10)%27],static_cast<int>((n/40)%4),((n/10)&1)!=0,((n/20)&1)!=0,((n/30)&1)!=0,hp[(n/10)%6]};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    menu dispatch op %u case %u event %d pair %d status %d/%d bytes %lu/%lu\n",op,n,c.event,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }coverage.report(host);
 }return 0;
}
}
TL_TEST(menu_mass_buttons_differential){return run(host,0,7,"menu_mass_buttons_differential");}
TL_TEST(menu_mass_dispatch_differential){return run(host,7,13,"menu_mass_dispatch_differential");}
