#include <cstring>
#include <limits>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "GameStateController.h"
#include "GameClient.h"
TL_ORIGINAL(void, originalStateSwitch, (CGameStateController*,bool), "_ZN20CGameStateController17doActualGameStateEb")
TL_ORIGINAL(void, originalStateUpdate, (CGameStateController*,float), "_ZN20CGameStateController6updateEf")
TL_FUNCTION(uiSingleton,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(closeLeft,"_ZN7CGameUI9closeLeftEv")
TL_FUNCTION(closeRight,"_ZN7CGameUI10closeRightEv")
TL_FUNCTION(closeMenus,"_ZN7CGameUI10closeMenusEv")
TL_FUNCTION(closeAll,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(menuVisible,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(cameraSingleton,"_ZN14CCameraControl12getSingletonEv")
TL_FUNCTION(cinematic,"_ZN14CCameraControl16setCinematicModeEb")
TL_FUNCTION(npcIcons,"_ZN6CLevel14updateNPCIconsEv")
TL_FUNCTION(disableSkills,"_ZN13CSkillManager21globallyDisableSkillsEb")
TL_FUNCTION(stopPath,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(meshVisible,"_ZN10CCharacter14setMeshVisibleEbb")
TL_FUNCTION(stopSkill,"_ZN7CPlayer24attemptToStopPlayerSkillEb")
TL_FUNCTION(hp,"_ZN10CCharacter2HPEv")
TL_FUNCTION(maxHP,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(editor,"_ZN16CResourceManager18getEditorIsRunningEv")
extern "C" void* controlTable[] __asm__("_ZTV20CGameStateController");
extern "C" void* playerTable[] __asm__("_ZTV7CPlayer");
namespace {
struct Case {unsigned int seed;bool update;};
std::vector<unsigned int> trace;
void* players[2];void* clients[2];void* resources[2];void* levels[2];void* uis[2];void* camera;void* controller;
unsigned int mode,uiCalls,swaps;bool updating;int currentHP,maximumHP;
void pointerAt(void* p,size_t at,void* v) {std::memcpy(static_cast<char*>(p)+at,&v,sizeof(v));}
void valueAt(void* p,size_t at,unsigned int v) {std::memcpy(static_cast<char*>(p)+at,&v,4);}
unsigned int who(void* p) {for(unsigned int i=0;i<2;++i){if(p==players[i])return 10+i;if(p==clients[i])return 20+i;if(p==resources[i])return 30+i;if(p==levels[i])return 40+i;if(p==uis[i])return 50+i;}return p==camera?60:p==NULL?0:99;}
void record(unsigned int id,void* p,unsigned int a=0,unsigned int b=0) {trace.push_back(id);trace.push_back(who(p));trace.push_back(a);trace.push_back(b);}
void changeClient() {if(mode&8){++swaps;pointerAt(controller,0x58,resources[swaps&1]);}}
void enable(void* p,bool v) {record(1,p,v);changeClient();}
void stop(void* p) {record(2,p);}
void mesh(void* p,bool a,bool b) {record(3,p,a,b);}
void stopActiveSkill(void* p,bool v) {record(4,p,v);}
void* ui() {void* p=mode==4&&uiCalls==0?NULL:uis[uiCalls&1];++uiCalls;record(5,p);return p;}
void left(void* p) {record(6,p);}
void right(void* p) {record(7,p);}
void menus(void* p) {record(8,p);}
void all(void* p) {record(9,p);}
void visible(void* p,bool v) {record(10,p,v);changeClient();}
void* cameraGet() {record(11,camera);return camera;}
void cinema(void* p,bool v) {record(12,p,v);changeClient();}
void icons(void* p) {record(13,p);}
void skills(bool v) {record(14,NULL,v);}
int getHP(void* p) {record(15,p,static_cast<unsigned int>(currentHP));changeClient();return currentHP;}
int getMaxHP(void* p) {record(16,p,static_cast<unsigned int>(maximumHP));if(mode&4){float changed=25.0f;std::memcpy(static_cast<char*>(controller)+0x6c,&changed,4);}return maximumHP;}
bool isEditor(void* p) {record(17,p);return mode==1;}
void event(void* p,unsigned int id) {record(18,p,id);}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long self[0x78/8],resource[2][0x48/8],client[2][0x3910/8],player[2][0xa70/8],level[2][8],uiStorage[2][8],cameraStorage[8];
    std::memset(self,0,sizeof(self));std::memset(resource,0,sizeof(resource));std::memset(client,0,sizeof(client));std::memset(player,0,sizeof(player));
    controller=self;camera=cameraStorage;mode=c.seed%16;uiCalls=swaps=0;updating=c.update;trace.clear();
    void* table[10];std::memcpy(table,controlTable,sizeof(table));table[8]=reinterpret_cast<void*>(&event);pointerAt(self,0,table+2);
    void* ptable[11];std::memcpy(ptable,playerTable,sizeof(ptable));ptable[10]=reinterpret_cast<void*>(&enable);
    for(unsigned int i=0;i<2;++i){players[i]=player[i];clients[i]=client[i];resources[i]=resource[i];levels[i]=level[i];uis[i]=uiStorage[i];pointerAt(player[i],0,ptable+2);pointerAt(client[i],0x58,player[i]);pointerAt(resource[i],0x18,level[i]);}
    TArrayList<CGameClient*>* lists[2];for(unsigned int i=0;i<2;++i){lists[i]=new(reinterpret_cast<char*>(resource[i])+0x28)TArrayList<CGameClient*>;lists[i]->add(static_cast<CGameClient*>(clients[i]));}
    pointerAt(self,0x58,resource[0]);int state=static_cast<int>(c.seed/32)%9-1;std::memcpy(reinterpret_cast<char*>(self)+0x64,&state,4);
    if(!c.update){if(mode==0)pointerAt(self,0x58,NULL);if(mode==1)lists[0]->clear();if(mode==2)(*lists[0])[0]=NULL;if(mode==3)pointerAt(client[0],0x58,NULL);}
    else {if(mode==2)pointerAt(client[0],0x58,NULL);const int hps[]={0,1,10,90,100,-1,(-2147483647-1)};currentHP=hps[(c.seed/16)%7];maximumHP=hps[(c.seed/7)%7];float previous[]={0,1,100,90,-1,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};float old=previous[(c.seed/3)%7];std::memcpy(reinterpret_cast<char*>(self)+0x6c,&old,4);}
    detour::Set patches;TL_REDIRECT(patches,uiSingleton,&ui);TL_REDIRECT(patches,closeLeft,&left);TL_REDIRECT(patches,closeRight,&right);TL_REDIRECT(patches,closeMenus,&menus);TL_REDIRECT(patches,closeAll,&all);TL_REDIRECT(patches,menuVisible,&visible);TL_REDIRECT(patches,cameraSingleton,&cameraGet);TL_REDIRECT(patches,cinematic,&cinema);TL_REDIRECT(patches,npcIcons,&icons);TL_REDIRECT(patches,disableSkills,&skills);TL_REDIRECT(patches,stopPath,&stop);TL_REDIRECT(patches,meshVisible,&mesh);TL_REDIRECT(patches,stopSkill,&stopActiveSkill);TL_REDIRECT(patches,hp,&getHP);TL_REDIRECT(patches,maxHP,&getMaxHP);TL_REDIRECT(patches,editor,&isEditor);
    bool failed=patches.failed();out.add(&failed,sizeof(failed));if(failed)_exit(17);
    CGameStateController* object=reinterpret_cast<CGameStateController*>(self);
    if(c.update){if(ours)object->update(0.125f);else originalStateUpdate(object,0.125f);}
    else{bool enabled=(c.seed&16)!=0;if(ours)object->doActualGameState(enabled);else originalStateSwitch(object,enabled);}
    size_t n=trace.size();out.add(&n,sizeof(n));for(size_t i=0;i<n;++i)out.add(&trace[i],4);out.add(reinterpret_cast<char*>(self)+0x6c,4);for(unsigned int i=0;i<2;++i)out.add(reinterpret_cast<char*>(client[i])+0x10bc,1);out.add(&uiCalls,4);out.add(&swaps,4);
    patches.restore();lists[0]->~TArrayList<CGameClient*>();lists[1]->~TArrayList<CGameClient*>();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,bool update) {
    int failures=0;unsigned int count=update?336:288;
    for(unsigned int seed=0;seed<count;++seed){Case c={seed,update};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    state %s seed %u statuses %d/%d bytes %lu/%lu\n",update?"update":"switch",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}return failures;
}
}
TL_TEST(game_state_switch_callbacks) {return run(host,false);}
TL_TEST(game_state_update_callbacks) {return run(host,true);}
