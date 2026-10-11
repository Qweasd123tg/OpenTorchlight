#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <fenv.h>
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
#include "TArrayList.h"
#include "Settings.h"
TL_ORIGINAL(bool,original0,(void*,void*),"_ZN13CDropdownMenu20handle_onDoubleClickERKN5CEGUI9EventArgsE")
extern "C" bool candidate0(void*,void*) __asm__("_ZN13CDropdownMenu20handle_onDoubleClickERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original1,(void*,void*),"_ZN13CDropdownMenu14handle_onClickERKN5CEGUI9EventArgsE")
extern "C" bool candidate1(void*,void*) __asm__("_ZN13CDropdownMenu14handle_onClickERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original2,(void*,int,std::wstring),"_ZN8CDieMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE")
extern "C" bool candidate2(void*,int,std::wstring) __asm__("_ZN8CDieMenu7onClickE15ELayoutFunctionSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,original3,(void*,bool),"_ZN14CCinematicMenu7setOpenEb")
extern "C" void candidate3(void*,bool) __asm__("_ZN14CCinematicMenu7setOpenEb");
TL_ORIGINAL(void,original4,(void*,float),"_ZN14CCinematicMenu6updateEf")
extern "C" void candidate4(void*,float) __asm__("_ZN14CCinematicMenu6updateEf");
TL_ORIGINAL(void,original5,(void*,bool),"_ZN16CQuestDialogMenu7setOpenEb")
extern "C" void candidate5(void*,bool) __asm__("_ZN16CQuestDialogMenu7setOpenEb");
TL_ORIGINAL(void,original6,(void*),"_ZN17CContinueGameMenu15deleteCharacterEv")
extern "C" void candidate6(void*) __asm__("_ZN17CContinueGameMenu15deleteCharacterEv");
TL_ORIGINAL(void,original7,(void*),"_ZN10CQuestMenu12abandonQuestEv")
extern "C" void candidate7(void*) __asm__("_ZN10CQuestMenu12abandonQuestEv");
TL_FUNCTION(target_wide,"_ZN7STRINGS19StringConvertToWideEPKcj")
TL_FUNCTION(target_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(target_expGate,"_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(target_fameGate,"_ZN22CMasterResourceManager8fameGateEi")
TL_FUNCTION(target_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(target_getFloat,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(target_stop,"_ZN10CSoundBank4stopEv")
TL_FUNCTION(target_ingame,"_ZN7CGameUI18setIngameUIVisibleEb")
TL_FUNCTION(target_interactive,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(target_removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(target_broadcast,"_ZN13CDropdownMenu14broadcastEventE10EMENU_TYPE11EMENU_EVENT")
TL_FUNCTION(target_held,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(target_pressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(target_textUpdate,"_ZN14CCinematicMenu17updateTextDisplayEf")
TL_FUNCTION(target_baseUpdate,"_ZN13CDropdownMenu6updateEf")
TL_FUNCTION(target_audioLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(target_dialogStop,"_ZN12CQuestDialog15stopDialogSoundEv")
TL_FUNCTION(target_savePath,"_ZN10FILESYSTEM15GetSaveDataPathEv")
TL_FUNCTION(target_assemble,"_ZN10FILESYSTEM20AssembleAbsolutePathERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(target_deleteFile,"_Z10DeleteFilePKw")
TL_FUNCTION(target_reload,"_ZN17CContinueGameMenu11reloadFilesEb")
TL_FUNCTION(target_select,"_ZN17CContinueGameMenu15selectCharacterEib")
TL_FUNCTION(target_listUpdate,"_ZN17CContinueGameMenu19updateCharacterListEv")
TL_FUNCTION(target_details,"_ZN6CQuest15getQuestDetailsEv")
TL_FUNCTION(target_play,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(target_removeQuest,"_ZN13CQuestManager11removeQuestEP6CQuestb")
extern "C" char target_utf8[] __asm__("_ZNK5CEGUI6String15build_utf8_buffEv");
extern "C" char target_removeChild[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char target_position[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char target_addChild[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char target_back[] __asm__("_ZN5CEGUI6Window10moveToBackEv");

namespace {
struct List{void**data;unsigned count,capacity,grow,pad;};struct Case{unsigned op,seed,flags,mode;int function;float elapsed,volume;};Case*input;autotest::Capture*output;void*active;void*uis[2];void*clients[2];void*players[2];void*windows[3];void*settings[2];void*masterData;void*quests[8];void*managers[2];void*audioObject;unsigned calls;int*functions;
void num(unsigned n){output->add(&n,4);}void ptr(void*p){output->add(&p,8);}void fl(float f){output->add(&f,4);}void event(unsigned n,void*p){num(n);ptr(p);num(static_cast<unsigned char*>(active)[0x30]);num(static_cast<unsigned char*>(active)[0x31]);}
void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void word(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}
void change(){++calls;if(input->mode==1){put(active,0x40,uis[calls%2]);put(active,0x38,settings[calls%2]);}if(input->mode==2){put(uis[0],0x1920,clients[1]);put(clients[0],0x58,players[1]);word(players[0],0x100,100+calls);word(players[0],0x450,13+calls);}if(input->mode==3){put(active,0x18,windows[calls%3]);put(active,0x10,windows[(calls+1)%3]);put(active,0x20,windows[(calls+2)%3]);functions[0]=100+calls;}if(input->mode==4){static_cast<unsigned char*>(active)[0x30]=(calls&1)!=0;static_cast<unsigned char*>(active)[0x31]=(calls&2)!=0;}if(input->mode==5){KSETTINGS_F_MUSICVOLUME=111+calls;KSETTINGS_MUSICMUTE=222+calls;}if(input->mode==6&&input->op==7){List*l=reinterpret_cast<List*>(static_cast<char*>(managers[0])+0x18);if(l->count>1)--l->count;}}
const char*utf8(void*p){event(1,p);change();return input->flags&8?"":input->flags&16?"title / text":"UTF8 payload";}
std::wstring wide(const char*p,unsigned maximum){num(2);num(maximum);std::string str(p);num(str.size());output->add(str.data(),str.size());change();return input->flags&8?L"":input->flags&16?L"prefix Ω text":L"0123456789abcdefghij";}
bool click(void*p,int function,std::wstring text){event(3,p);num(function);output->addText(text);change();return input->flags&16;}
void open(void*p,bool value){event(4,p);num(value);static_cast<unsigned char*>(p)[0x30]=value;change();}
void*master(){event(5,masterData);change();return masterData;}
int expGate(void*p,int level){event(6,p);num(level);change();return static_cast<int>(input->seed*1234567u+calls*54321u);}
int fameGate(void*p,int level){event(7,p);num(level);change();return static_cast<int>(input->seed*7654321u-calls*4321u);}
int getInt(void*p,unsigned key){event(8,p);num(key);change();return input->flags%4==0?0:input->flags%4==1?1:-3;}
float getFloat(void*p,unsigned key){event(9,p);num(key);change();return input->volume;}
void stop(void*p){event(10,p);change();}
void ingame(void*p,bool value){event(11,p);num(value);change();}
void interactive(void*p,bool value){event(12,p);num(value);change();}
void removeSafe(void*p,void*safe,unsigned index){event(13,p);ptr(safe);num(index);change();}
void broadcast(void*p,int type,int kind){event(14,p);num(type);num(kind);change();}
bool held(void*p,int button){event(15,p);num(button);change();return (input->flags>>(button+3))&1;}
bool pressed(void*p,int button){event(16,p);num(button);change();return (input->flags>>(button+5))&1;}
void textUpdate(void*p,float elapsed){event(17,p);fl(elapsed);change();}
void baseUpdate(void*p,float elapsed){event(18,p);fl(elapsed);change();}
void audioLevels(void*p,float sound,float music,bool muteSound,bool muteMusic){event(19,p);fl(sound);fl(music);num(muteSound);num(muteMusic);change();}
void dialogStop(void*p){event(20,p);change();}
std::wstring savePath(){num(21);change();return input->flags&1?L"/tmp/Сохранения/":L"";}
std::wstring assemble(const std::wstring&base,const std::wstring&path){num(22);output->addText(base);output->addText(path);change();return base+L"/"+path;}
int deleteFile(const wchar_t*path){num(23);output->addText(std::wstring(path));change();if(input->mode==5)word(active,0xc8,8);return input->flags&1;}
void reload(void*p,bool b){event(24,p);num(b);change();if(input->mode==6)word(active,0xc8,5);}
bool select(void*p,int index,bool b){event(25,p);num(index);num(b);change();return input->flags&1;}
void listUpdate(void*p){event(26,p);change();}
std::wstring details(void*p){event(27,p);unsigned i=0;for(;i<8&&p!=quests[i];++i){}change();return (i+input->seed)%3==0?L"":(i&1)?L"Quest Ω":L"Details";}
void play(void*p,int kind,void*node,float a,float b,bool flag){event(28,p);num(kind);ptr(node);fl(a);fl(b);num(flag);change();if(input->mode==5){List*l=reinterpret_cast<List*>(static_cast<char*>(managers[0])+0x18);for(unsigned i=0;i<l->count;++i)l->data[i]=quests[7-i];}}
long long removeQuest(void*p,void*q,bool force){event(29,p);ptr(q);num(force);change();return -1;}
void layout(void*p){event(30,p);change();}
void enabled(void*p,bool value){event(31,p);num(value);change();}
void removeChild(void*p,void*child){event(32,p);ptr(child);change();}
void position(void*p,const void*v){event(33,p);output->add(v,16);change();}
void addChild(void*p,void*child){event(34,p);ptr(child);change();}
void back(void*p){event(35,p);change();}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;unsigned long long selfData[0x420/8],ui[2][0x1a08/8]={{0}},client[2][0x3910/8]={{0}},player[2][0xc00/8]={{0}},window[3][0x800/8]={{0}},setting[2][0x160/8]={{0}},masterStorage[0x190/8]={0},quest[8][0x210/8]={{0}},manager[2][0x100/8]={{0}},sound[0x80/8]={0},eventData[0x60/8]={0};std::memset(selfData,(c.seed*31+7)&255,sizeof(selfData));void*self=selfData;active=self;masterData=masterStorage;audioObject=sound;int funcs[2]={c.function,91};functions=funcs;void*event=eventData;
 void*menuTable[24]={0};menuTable[7]=reinterpret_cast<void*>(&open);menuTable[8]=reinterpret_cast<void*>(&click);menuTable[9]=c.op==7?reinterpret_cast<void*>(&layout):reinterpret_cast<void*>(&click);void*unitTable[16]={0};unitTable[8]=reinterpret_cast<void*>(&enabled);put(self,0,menuTable);
 for(unsigned i=0;i<2;++i){uis[i]=ui[i];clients[i]=client[i];players[i]=player[i];settings[i]=setting[i];managers[i]=manager[i];put(uis[i],0x1920,clients[i]);put(clients[i],0x58,players[i]);put(players[i],0,unitTable);put(players[i],0x868,c.flags&32?NULL:managers[i]);word(players[i],0x100,c.seed*1234567u);word(players[i],0x444,0x80000000u+c.seed);word(players[i],0x450,0xffffffffu-c.seed);}
 for(unsigned i=0;i<3;++i){windows[i]=window[i];put(windows[i],0x1d8,&funcs[i%2]);unsigned prefix=c.flags&8?0:c.flags&16?3:7;if(c.mode==7&&c.op<2)prefix=c.flags&16?0xffffffffu:40;word(windows[i],0x680,prefix);}
 for(unsigned i=0;i<8;++i){quests[i]=quest[i];static_cast<unsigned char*>(quests[i])[0x208]=((c.flags+i)&1)!=0;}
 void*questValues[2][8];for(unsigned k=0;k<2;++k){for(unsigned i=0;i<8;++i)questValues[k][i]=quests[(i+k)%8];List list={questValues[k],c.flags%9,c.mode==7?1:8,2,0};std::memcpy(static_cast<char*>(managers[k])+0x18,&list,sizeof(list));}
 put(masterStorage,0x90,settings[1]);put(masterStorage,0x98,audioObject);put(self,0x40,uis[0]);put(self,0x38,settings[0]);put(self,0x10,windows[0]);put(self,0x18,windows[1]);put(self,0x20,windows[2]);put(self,0x80,c.flags&8?NULL:audioObject);put(self,0xc0,c.flags&16?NULL:players[0]);put(self,0x120,c.flags&8?NULL:quests[0]);put(self,0x180,players[0]);put(self,0x1d8,audioObject);word(self,0x18c,(c.flags/2)%10);
 static_cast<unsigned char*>(self)[0x30]=(c.flags&1)!=0;static_cast<unsigned char*>(self)[0x31]=(c.flags&2)!=0;static_cast<unsigned char*>(self)[0x32]=(c.flags&4)!=0;static_cast<unsigned char*>(self)[0x1e9]=(c.flags&64)!=0;
 std::memcpy(static_cast<char*>(self)+0xf8,&c.volume,4);std::memcpy(static_cast<char*>(self)+0xdc,&c.elapsed,4);
 const unsigned safe[]={0x1f8,0x1e8,0x1c8,0x1d8};for(unsigned k=0;k<2;++k)for(unsigned i=0;i<4;++i){put(clients[k],safe[i],c.flags&(4u<<i)?NULL:quests[i]);word(clients[k],safe[i]+8,0x80000000u+i+c.seed);}
 put(event,0x10,c.flags&64?NULL:windows[0]);word(event,0x28,(c.flags/4)%3);std::wstring text=L"payload";
 if(c.op==6){std::vector<void*>*states=new(static_cast<char*>(self)+0x1e8)std::vector<void*>;std::vector<std::wstring>*paths=new(static_cast<char*>(self)+0x218)std::vector<std::wstring>;for(unsigned i=0;i<5;++i){states->push_back(quests[i]);paths->push_back(i&1?L"Player.save":L"Персонаж / one.svt");}word(self,0xc8,(c.flags/2)%8);}
 KSETTINGS_RES_WIDTH=101;KSETTINGS_RES_HEIGHT=102;KSETTINGS_F_SOUNDVOLUME=103;KSETTINGS_F_MUSICVOLUME=104;KSETTINGS_SOUNDMUTE=105;KSETTINGS_MUSICMUTE=106;detour::Set patches;
 TL_REDIRECT(patches,target_wide,&wide);
 TL_REDIRECT(patches,target_master,&master);
 TL_REDIRECT(patches,target_expGate,&expGate);
 TL_REDIRECT(patches,target_fameGate,&fameGate);
 TL_REDIRECT(patches,target_getInt,&getInt);
 TL_REDIRECT(patches,target_getFloat,&getFloat);
 TL_REDIRECT(patches,target_stop,&stop);
 TL_REDIRECT(patches,target_ingame,&ingame);
 TL_REDIRECT(patches,target_interactive,&interactive);
 TL_REDIRECT(patches,target_removeSafe,&removeSafe);
 TL_REDIRECT(patches,target_broadcast,&broadcast);
 TL_REDIRECT(patches,target_held,&held);
 TL_REDIRECT(patches,target_pressed,&pressed);
 TL_REDIRECT(patches,target_textUpdate,&textUpdate);
 TL_REDIRECT(patches,target_baseUpdate,&baseUpdate);
 TL_REDIRECT(patches,target_audioLevels,&audioLevels);
 TL_REDIRECT(patches,target_dialogStop,&dialogStop);
 TL_REDIRECT(patches,target_savePath,&savePath);
 TL_REDIRECT(patches,target_assemble,&assemble);
 TL_REDIRECT(patches,target_deleteFile,&deleteFile);
 TL_REDIRECT(patches,target_reload,&reload);
 TL_REDIRECT(patches,target_select,&select);
 TL_REDIRECT(patches,target_listUpdate,&listUpdate);
 TL_REDIRECT(patches,target_details,&details);
 TL_REDIRECT(patches,target_play,&play);
 TL_REDIRECT(patches,target_removeQuest,&removeQuest);
 patches.redirect(target_utf8,target_utf8,&utf8);
 patches.redirect(target_removeChild,target_removeChild,&removeChild);
 patches.redirect(target_position,target_position,&position);
 patches.redirect(target_addChild,target_addChild,&addChild);
 patches.redirect(target_back,target_back,&back);
 if(patches.failed()){num(patches.failure());const void*site=patches.failureSite();out.add(&site,8);return;}feclearexcept(FE_ALL_EXCEPT);unsigned fault=0;
 switch(c.op){
 case 0:{bool(*fn)(void*,void*)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;try{bool result=fn(self,event);out.callCompleted=1;num(0);num(result);}catch(const std::out_of_range&e){fault=1;num(1);std::string what=e.what();num(what.size());out.add(what.data(),what.size());}break;}
 case 1:{bool(*fn)(void*,void*)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;try{bool result=fn(self,event);out.callCompleted=1;num(0);num(result);}catch(const std::out_of_range&e){fault=1;num(1);std::string what=e.what();num(what.size());out.add(what.data(),what.size());}break;}
 case 2:autotest::invoke(out,ours?candidate2:original2,self,c.function,text);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,(c.flags&4)!=0);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,c.elapsed);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,(c.flags&4)!=0);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self);break;

 }num(fetestexcept(FE_ALL_EXCEPT));num(calls);num(KSETTINGS_F_MUSICVOLUME);num(KSETTINGS_MUSICMUTE);
 if(c.op==6){std::vector<void*>*states=reinterpret_cast<std::vector<void*>*>(static_cast<char*>(self)+0x1e8);std::vector<std::wstring>*paths=reinterpret_cast<std::vector<std::wstring>*>(static_cast<char*>(self)+0x218);num(states->size());for(unsigned i=0;i<states->size();++i)ptr((*states)[i]);num(paths->size());for(unsigned i=0;i<paths->size();++i)out.addText((*paths)[i]);states->~vector();paths->~vector();std::memset(static_cast<char*>(self)+0x1e8,0,24);std::memset(static_cast<char*>(self)+0x218,0,24);}
 out.add(selfData,sizeof(selfData));out.add(ui,sizeof(ui));out.add(client,sizeof(client));out.add(player,sizeof(player));out.add(window,sizeof(window));out.add(setting,sizeof(setting));out.add(masterStorage,sizeof(masterStorage));out.add(quest,sizeof(quest));out.add(manager,sizeof(manager));out.add(questValues,sizeof(questValues));out.add(funcs,sizeof(funcs));patches.restore();observed_witness::finish(out,fault);
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7};const unsigned values[]={0,0x80000000u,0x3e800000u,0x3f000000u,0x3f800000u,0x40000000u,0xbf800000u,0x7f800000u,0xff800000u,0x7fc00123u};const int functions[]={-1,0,10,14,15,16,17,0x7fffffff,(-2147483647-1)};autotest::Coverage coverage(name,addresses[op]);unsigned witnesses=0;for(unsigned n=0;n<1440;++n){Case c={op,n,n/8,n%8,functions[(n/8)%9],0,0};unsigned a=values[(n/8)%10],b=values[(n/80)%10];std::memcpy(&c.elapsed,&a,4);std::memcpy(&c.volume,&b,4);autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(recovered,&c,y);const unsigned expectedFault=op<2&&c.mode==7&&!(c.flags&64)&&(op==0||(c.flags/4)%3==0)?1u:0u;if(observed_witness::observe(host,coverage,x,y,expectedFault,witnesses)){host->log("    menu more %u/%u status %d/%d bytes %lu/%lu\n",op,n,x.status,y.status,(unsigned long)x.capture.length,(unsigned long)y.capture.length);for(unsigned i=0;i<x.capture.length&&i<y.capture.length;++i)if(x.capture.data[i]!=y.capture.data[i]){host->log("    first byte %u %u/%u\n",i,(unsigned char)x.capture.data[i],(unsigned char)y.capture.data[i]);break;}if(x.capture.length==12){unsigned reason;unsigned long long site;std::memcpy(&reason,x.capture.data,4);std::memcpy(&site,x.capture.data+4,8);host->log("    patch %u at 0x%llx\n",reason,site);}coverage.report(host);return 1;}if(expectedFault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,x,y,expectedFault))return 1;}coverage.report(host);const unsigned exceptions=op==0?116u:op==1?40u:0u;return observed_witness::totals(host,coverage,witnesses,1440-exceptions,exceptions)?0:1;}
}
TL_TEST(menu_more_double_click){return run(host,0,"menu_more_double_click");}
TL_TEST(menu_more_click){return run(host,1,"menu_more_click");}
TL_TEST(menu_more_die_click){return run(host,2,"menu_more_die_click");}
TL_TEST(menu_more_cinematic_open){return run(host,3,"menu_more_cinematic_open");}
TL_TEST(menu_more_cinematic_update){return run(host,4,"menu_more_cinematic_update");}
TL_TEST(menu_more_quest_open){return run(host,5,"menu_more_quest_open");}
TL_TEST(menu_more_delete_character){return run(host,6,"menu_more_delete_character");}
TL_TEST(menu_more_abandon_quest){return run(host,7,"menu_more_abandon_quest");}
