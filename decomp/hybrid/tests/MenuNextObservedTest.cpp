// Each child performs one actual target call, with complete object snapshots.
#include <cstring>
#include <limits>
#include "AutoTest.h"
#include "Detour.h"
#include "Settings.h"
TL_ORIGINAL(void,original0,(void*,float),"_ZN8CTipMenu6updateEf")
extern "C" void candidate0(void*,float) __asm__("_ZN8CTipMenu6updateEf");
TL_ORIGINAL(void,original1,(void*,bool),"_ZN8CTipMenu7setOpenEb")
extern "C" void candidate1(void*,bool) __asm__("_ZN8CTipMenu7setOpenEb");
TL_ORIGINAL(void,original2,(void*,float),"_ZN13CWaypointMenu6updateEf")
extern "C" void candidate2(void*,float) __asm__("_ZN13CWaypointMenu6updateEf");
TL_ORIGINAL(void,original3,(void*,float),"_ZN8CDieMenu6updateEf")
extern "C" void candidate3(void*,float) __asm__("_ZN8CDieMenu6updateEf");
TL_ORIGINAL(void,original4,(void*,bool,void*),"_ZN16CQuestDialogMenu27broadcastAcceptedOrDeclinedEbP9CBaseUnit")
extern "C" void candidate4(void*,bool,void*) __asm__("_ZN16CQuestDialogMenu27broadcastAcceptedOrDeclinedEbP9CBaseUnit");
TL_FUNCTION(target_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(target_setInt,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(target_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(target_removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(target_requestState,"_ZN7CGameUI19requestSetGameStateE10EGameState5EMenu")
TL_FUNCTION(target_gold,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(target_fame,"_ZN10CCharacter9awardFameER6CLevelPS_ib")
TL_FUNCTION(target_experience,"_ZN10CCharacter15awardExperienceER6CLevelPS_ib")
extern "C" char target_remove[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char target_position[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char target_ordering[] __asm__("_ZN5CEGUI6Window19setZOrderingEnabledEb");
extern "C" char target_add[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char target_top[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char target_front[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");

namespace {
struct Case {unsigned op,seed,flags,mode;float elapsed;};Case*input;autotest::Capture*output;void*active;void*uis[2];void*clients[2];void*units[2];void*settings[2];void*windows[3];void*resources[2];void*masterObject;unsigned calls;
void num(unsigned x){output->add(&x,4);}void ptr(void*p){output->add(&p,8);}void event(unsigned n,void*p){num(n);ptr(p);num(static_cast<unsigned char*>(active)[0x31]);}
void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void word(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}
void change(){++calls;if(input->mode==1){put(active,0x40,uis[1]);put(active,0x38,settings[1]);}if(input->mode==2){put(active,0x18,windows[calls%3]);put(active,0x10,windows[(calls+1)%3]);put(active,0x20,windows[(calls+2)%3]);}if(input->mode==3){put(uis[0],0x1920,clients[1]);put(clients[0],0x58,units[1]);}if(input->mode==4){put(units[0],0x68,calls&1?resources[1]:NULL);put(units[1],0x68,calls&1?NULL:resources[0]);word(active,0xf8,0u-calls);word(active,0xfc,0x80000000u+calls);word(active,0xc4,91+calls);}if(input->mode==5){static_cast<unsigned char*>(active)[0xc1]=input->flags&16?1:0;put(active,0xc0,units[1]);static_cast<unsigned char*>(active)[0x1eb]=0;put(active,0x120,NULL);}if(input->mode==6){KSETTINGS_SHOW_TIPS=1234+calls;KSETTINGS_RES_HEIGHT=4321+calls;static_cast<unsigned char*>(windows[0])[0x732]=1;}}
void* master(){event(1,masterObject);change();return masterObject;}
void setInt(void*p,unsigned key,int value){event(2,p);num(key);num(value);word(p,0x10,key);word(p,0x14,value);change();}
int getInt(void*p,unsigned key){event(3,p);num(key);change();return int(input->seed*67)-89;}
void removeSafe(void*p,void*safe,unsigned index){event(4,p);ptr(safe);num(index);change();}
void requestState(void*p,int state,int menu){event(5,p);num(state);num(menu);word(p,0x1914,state);word(p,0x1918,menu);change();}
void gold(void*p,int amount){event(6,p);num(amount);word(p,0x110,amount);change();}
void fame(void*p,void*level,void*source,int amount,bool bonus){event(7,p);ptr(level);ptr(source);num(amount);num(bonus);change();}
void experience(void*p,void*level,void*source,int amount,bool bonus){event(8,p);ptr(level);ptr(source);num(amount);num(bonus);change();}
void remove(void*p,void*child){event(9,p);ptr(child);change();}
void position(void*p,const void*v){event(10,p);output->add(v,16);change();}
void ordering(void*p,bool b){event(11,p);num(b);change();}
void add(void*p,void*child){event(12,p);ptr(child);change();}
void top(void*p,bool b){event(13,p);num(b);change();}
void front(void*p){event(14,p);change();}
void broadcast(void*p,unsigned kind){event(15,p);num(kind);num(static_cast<unsigned char*>(active)[0x1eb]);change();}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;
 unsigned long long storage[0x500/8],ui[2][0x1a08/8],client[2][0x3910/8],unit[2][0xc00/8],window[3][0x800/8],setting[2][0x160/8],resource[2][0x40/8],masterData[0x190/8];
 std::memset(storage,(c.seed*17+19)&255,sizeof(storage));std::memset(ui,0,sizeof(ui));std::memset(client,0,sizeof(client));std::memset(unit,0,sizeof(unit));std::memset(window,0,sizeof(window));std::memset(setting,0,sizeof(setting));std::memset(resource,0,sizeof(resource));std::memset(masterData,0,sizeof(masterData));void*self=storage;active=self;masterObject=masterData;
 void*unitTable[16]={0};unitTable[6]=reinterpret_cast<void*>(&broadcast);
 for(unsigned i=0;i<2;++i){uis[i]=ui[i];clients[i]=client[i];units[i]=unit[i];settings[i]=setting[i];resources[i]=resource[i];put(uis[i],0x1920,clients[i]);put(clients[i],0x58,units[i]);put(units[i],0,unitTable);put(units[i],0x68,c.flags&64?NULL:resources[i]);put(resources[i],0x18,window[i]);}
 for(unsigned i=0;i<3;++i)windows[i]=window[i];put(masterData,0x90,settings[1]);put(self,0x40,uis[0]);put(self,0x38,settings[0]);put(self,0x10,windows[0]);put(self,0x18,windows[1]);put(self,0x20,windows[2]);put(self,0xd0,windows[0]);
 static_cast<unsigned char*>(self)[0x30]=c.flags&1;static_cast<unsigned char*>(self)[0x31]=(c.flags&2)!=0;static_cast<unsigned char*>(windows[0])[0x732]=(c.flags&16)!=0;
 static_cast<unsigned char*>(self)[0xc0]=(c.flags&8)!=0;static_cast<unsigned char*>(self)[0xc1]=(c.flags&16)!=0;
 const unsigned values[]={0,1,1000,0xffffffffu,0x80000000u,0x7fffffffu,42,0xdeadbeefu};word(self,0xf8,values[(c.seed/8)%8]);word(self,0xfc,values[(c.seed/16)%8]);word(self,0x100,values[(c.seed/32)%8]);word(self,0xc4,values[(c.seed/8+3)%8]);
 const unsigned offsets[]={0x1f8,0x1e8,0x1c8,0x1d8};for(unsigned n=0;n<2;++n)for(unsigned i=0;i<4;++i){put(clients[n],offsets[i],c.flags&(4u<<i)?NULL:units[(i+n)%2]);word(clients[n],offsets[i]+8,0x80000000u+c.seed+i);}
 if(c.op==4){put(self,0xc0,c.flags&16?NULL:units[0]);put(self,0x120,c.flags&32?NULL:resources[0]);static_cast<unsigned char*>(self)[0x1eb]=(c.flags&64)!=0;}
 KSETTINGS_SHOW_TIPS=701;KSETTINGS_RES_WIDTH=702;KSETTINGS_RES_HEIGHT=703;
 detour::Set patches;
 TL_REDIRECT(patches,target_master,&master);
 TL_REDIRECT(patches,target_setInt,&setInt);
 TL_REDIRECT(patches,target_getInt,&getInt);
 TL_REDIRECT(patches,target_removeSafe,&removeSafe);
 TL_REDIRECT(patches,target_requestState,&requestState);
 TL_REDIRECT(patches,target_gold,&gold);
 TL_REDIRECT(patches,target_fame,&fame);
 TL_REDIRECT(patches,target_experience,&experience);
 patches.redirect(target_remove,target_remove,&remove);
 patches.redirect(target_position,target_position,&position);
 patches.redirect(target_ordering,target_ordering,&ordering);
 patches.redirect(target_add,target_add,&add);
 patches.redirect(target_top,target_top,&top);
 patches.redirect(target_front,target_front,&front);
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.elapsed);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,(c.flags&4)!=0);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,c.elapsed);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,c.elapsed);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,(c.flags&4)!=0,c.flags&8?units[1]:NULL);break;

 }num(calls);num(KSETTINGS_SHOW_TIPS);num(KSETTINGS_RES_WIDTH);num(KSETTINGS_RES_HEIGHT);out.add(storage,sizeof(storage));out.add(ui,sizeof(ui));out.add(client,sizeof(client));out.add(unit,sizeof(unit));out.add(window,sizeof(window));out.add(setting,sizeof(setting));out.add(resource,sizeof(resource));out.add(masterData,sizeof(masterData));patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void candidate(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4};autotest::Coverage coverage(name,addresses[op]);const float elapsed[]={0.0f,-0.0f,0.016f,-2.0f,1000.0f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),1.0f};
 for(unsigned n=0;n<1024;++n){Case c={op,n,n/8,n%8,elapsed[(n/16)%8]};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    menu next %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(menu_next_tip_update){return run(host,0,"menu_next_tip_update");}
TL_TEST(menu_next_tip_open){return run(host,1,"menu_next_tip_open");}
TL_TEST(menu_next_waypoint_update){return run(host,2,"menu_next_waypoint_update");}
TL_TEST(menu_next_die_update){return run(host,3,"menu_next_die_update");}
TL_TEST(menu_next_quest_dialog_broadcast){return run(host,4,"menu_next_quest_dialog_broadcast");}
