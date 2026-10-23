#include <Ogre.h>
#include <cstring>
#include <vector>
#include <fenv.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Editor.h"
#include "SkipCutscene.h"
#include "AnimationPlayer.h"
#include "CameraController.h"
#include "CameraControl.h"
#include "CameraShake.h"
#include "LogicTimer.h"
#include "Descriptor.h"
#include "DescriptorManager.h"
#include "EditorScene.h"
#include "Character.h"
#include "Player.h"
#include "GameClient.h"
#include "GameUI.h"
#include "SkillManager.h"
#undef protected
#undef private
#include "tests/NativeMenuClient.h"
#include "tests/GameClientUiOwner.h"
#include "tests/FinishLevelFixture.h"

TL_ORIGINAL(void,skipOriginal,(CSkipCutscene*,float),"_ZN13CSkipCutscene6updateEf")
extern "C" void skipCandidate(CSkipCutscene*,float) __asm__("_ZN13CSkipCutscene6updateEf");
TL_ORIGINAL(bool,skipKeyValue,(CKeyManager*,unsigned),"_ZN11CKeyManager10keyPressedEj")
TL_ORIGINAL(void,skipAnimationOriginal,(CAnimationPlayer*,bool),"_ZN16CAnimationPlayer13stopAnimationEb")
TL_ORIGINAL(void,skipCameraOriginal,(CCameraController*),"_ZN17CCameraController10stopCameraEv")
TL_ORIGINAL(void,skipTimerOriginal,(CLogicTimer*,bool),"_ZN11CLogicTimer10setEnabledEb")
TL_ORIGINAL(void,skipClearOriginal,(CCameraControl*),"_ZN14CCameraControl17clearCameraShakesEv")
TL_ORIGINAL(void,skipSkillsOriginal,(bool),"_ZN13CSkillManager21globallyDisableSkillsEb")
TL_ORIGINAL(void,skipMeshOriginal,(CCharacter*,bool,bool),"_ZN10CCharacter14setMeshVisibleEbb")
TL_ORIGINAL(TArrayList<CEditorBaseObject*>*,skipListsOriginal,(CEditorScene*,const std::wstring&),"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(skipKey,"_ZN11CKeyManager10keyPressedEj")
TL_FUNCTION(skipAnimation,"_ZN16CAnimationPlayer13stopAnimationEb")
TL_FUNCTION(skipCamera,"_ZN17CCameraController10stopCameraEv")
TL_FUNCTION(skipTimer,"_ZN11CLogicTimer10setEnabledEb")
TL_FUNCTION(skipClear,"_ZN14CCameraControl17clearCameraShakesEv")
TL_FUNCTION(skipSkills,"_ZN13CSkillManager21globallyDisableSkillsEb")
TL_FUNCTION(skipMesh,"_ZN10CCharacter14setMeshVisibleEbb")
TL_FUNCTION(skipLists,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(skipClose,"_ZN7CGameUI8closeAllEv")
TL_ORIGINAL(void,skipEditorCtor,(CEditor*),"_ZN7CEditorC1Ev")
TL_FUNCTION(skipDirectory,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(skipCopy,"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")

namespace {
struct Case{unsigned seed;bool sequence,negative;};
struct Descriptor: CDescriptor {
    explicit Descriptor(const wchar_t* name):CDescriptor(0){m_sName=name;}
    CEditorBaseObject* CreateObject(CEditorScene*){return NULL;}
};
struct Table {
    void*** owner;void** original;std::vector<void*> copy;
    Table(void* p,unsigned bytes):owner(reinterpret_cast<void***>(p)),original(*owner),copy(bytes/8){std::memcpy(&copy[0],original-2,bytes);*owner=&copy[2];}
    void replace(unsigned offset,void* callback){copy[2+offset/8]=callback;}
    void restore(){if(owner){*owner=original;owner=NULL;}}
    ~Table(){restore();}
};
const Case* current;autotest::Capture* output;CSkipCutscene* self;
CResourceManager* resources;CResourceManager* alternative;CGameClient* client;CGameUI* ui;CCameraControl* camera;
CPlayer* players[2];Table* playerTables[2];Table* cameraTables[9];CEditorScene* scenes[2];Descriptor* descriptors[3];
CAnimationPlayer* animations[9];CCameraController* cameras[9];CLogicTimer* timers[9];
detour::Set keyHook,animationHook,cameraHook,timerHook,clearHook,skillsHook,meshHook,listHook;
unsigned keyCalls,closeCalls,animationCalls,cameraCalls,timerCalls,clearCalls,eventCalls,step,playerCalls,animationAppends,timerAppends;
bool listMutation;unsigned mode;
bool directory(const std::wstring&){return true;}
void copy(const std::wstring&,const std::wstring&){}
void number(long long value){output->add(&value,sizeof value);}
void real(float value){output->add(&value,sizeof value);}
unsigned playerID(CPlayer* p){return p==players[0]?0:p==players[1]?1:99;}
unsigned objectID(CEditorBaseObject* p){if(p==self)return 100;for(unsigned i=0;i<9;++i){if(p==animations[i])return i;if(p==cameras[i])return 20+i;if(p==timers[i])return 40+i;}return 99;}
void flags(){number(self->m_bEnabled);number(self->m_bSkipRequested);number(self->m_bSkillsDisabled);number(resources->m_bFlag1);number(alternative->m_bFlag1);number(m_gDisableSkillFromBeingCasted);number(self->getParentGuid());}
void valid(){if(keyHook.failed()||animationHook.failed()||cameraHook.failed()||timerHook.failed()||clearHook.failed()||skillsHook.failed()||meshHook.failed()||listHook.failed())std::abort();}
void event(CEditorBaseObject* p,unsigned value)
{
    number(10);number(objectID(p));number(value);++eventCalls;flags();
    if(p==self&&value==114){
        if(mode==2)self->m_bSkillsDisabled=!self->m_bSkillsDisabled;
        if(mode==3)self->m_pResourceManager=alternative;
    }
    if(p==self&&value==7&&mode==4)self->m_bSkillsDisabled=!self->m_bSkillsDisabled;
    if(value==112&&mode==5&&!listMutation&&descriptors[0]->m_Objects.size()&&descriptors[0]->m_Objects.m_nCapacity>=descriptors[0]->m_Objects.size()){
        listMutation=true;++animationAppends;descriptors[0]->m_Objects.add(animations[8]);
    }
}
bool key(CKeyManager* p,unsigned value){number(11);number(p==client->getKeyManager());number(value);++keyCalls;keyHook.restore();bool result=skipKeyValue(p,value);TL_REDIRECT(keyHook,skipKey,&key);valid();number(result);return result;}
void skills(bool value){number(12);number(value);flags();skillsHook.restore();skipSkillsOriginal(value);TL_REDIRECT(skillsHook,skipSkills,&skills);valid();}
void close(CGameUI* p)
{
    // This native UI owner has empty menu pools. closeAll's concrete menu
    // receivers are a deliberate external boundary, not fabricated objects.
    number(13);number(p==ui);++closeCalls;flags();
    if(mode==0)self->SetSceneOwner(scenes[1]); // update must retain its pre-close scene.
    if(mode==1)self->m_pResourceManager=alternative;
    if(mode==6)self->setParentGuid(self->getParentGuid()+7);
}
TArrayList<CEditorBaseObject*>* lists(CEditorScene* p,const std::wstring& name)
{
    number(14);number(p==scenes[0]?0:p==scenes[1]?1:99);output->addText(name);flags();
    listHook.restore();TArrayList<CEditorBaseObject*>* result=skipListsOriginal(p,name);TL_REDIRECT(listHook,skipLists,&lists);valid();number(result!=NULL);if(result){number(result->size());number(result->m_nCapacity);}return result;
}
void animation(CAnimationPlayer* p,bool force)
{
    number(15);number(objectID(p));number(force);flags();++animationCalls;
    animationHook.restore();skipAnimationOriginal(p,force);TL_REDIRECT(animationHook,skipAnimation,&animation);valid();
    if(mode==7)self->setParentGuid(self->getParentGuid()+1);
}
void stopCamera(CCameraController* p)
{
    number(16);number(objectID(p));flags();++cameraCalls;
    cameraHook.restore();skipCameraOriginal(p);TL_REDIRECT(cameraHook,skipCamera,&stopCamera);valid();
}
void timer(CLogicTimer* p,bool value)
{
    number(17);number(objectID(p));number(value);flags();++timerCalls;
    timerHook.restore();skipTimerOriginal(p,value);TL_REDIRECT(timerHook,skipTimer,&timer);valid();
    if(mode==8&&!listMutation&&descriptors[2]->m_Objects.size()&&descriptors[2]->m_Objects.m_nCapacity>=descriptors[2]->m_Objects.size()){
        listMutation=true;++timerAppends;descriptors[2]->m_Objects.add(timers[8]);
    }
}
void clear(CCameraControl* p)
{
    number(18);number(p==camera);flags();number(p->m_cameraShakes.size());number(p->m_cameraShakesSecondary.size());++clearCalls;
    clearHook.restore();skipClearOriginal(p);TL_REDIRECT(clearHook,skipClear,&clear);valid();
}
void cyclePlayer(){if(mode==9)client->m_pPlayer=players[(++playerCalls)%2];}
void enabled(CPlayer* p,bool value){unsigned i=playerID(p);number(19);number(i);number(value);flags();typedef void(*F)(CPlayer*,bool);reinterpret_cast<F>(playerTables[i]->original[0x40/8])(p,value);cyclePlayer();}
void path(CPlayer* p,CPathController* value){unsigned i=playerID(p);number(20);number(i);number(value==NULL);flags();typedef void(*F)(CPlayer*,CPathController*);reinterpret_cast<F>(playerTables[i]->original[0x310/8])(p,value);cyclePlayer();}
void visible(CPlayer* p,bool value){unsigned i=playerID(p);number(21);number(i);number(value);flags();typedef void(*F)(CPlayer*,bool);reinterpret_cast<F>(playerTables[i]->original[0x50/8])(p,value);cyclePlayer();}
void ai(CPlayer* p,EAIState value){number(22);number(playerID(p));number(value);p->m_eAIState=value;}
void mesh(CCharacter* p,bool value,bool recursive){number(23);number(playerID(static_cast<CPlayer*>(p)));number(value);number(recursive);flags();meshHook.restore();skipMeshOriginal(p,value,recursive);TL_REDIRECT(meshHook,skipMesh,&mesh);valid();}
bool cameraEnabled(CCameraController* p){unsigned id=objectID(p)-20;number(24);number(objectID(p));typedef bool(*F)(CCameraController*);bool value=reinterpret_cast<F>(cameraTables[id]->original[0x48/8])(p);number(value);return value;}
void restoreHooks(){keyHook.restore();animationHook.restore();cameraHook.restore();timerHook.restore();clearHook.restore();skillsHook.restore();meshHook.restore();listHook.restore();}
void snapshot()
{
    flags();number(self->getSceneOwner()==scenes[0]?0:1);number(self->m_pResourceManager==resources?0:1);number(client->m_pPlayer==players[0]?0:1);
    number(keyCalls);number(closeCalls);number(animationCalls);number(cameraCalls);number(timerCalls);number(clearCalls);number(eventCalls);number(playerCalls);
    for(unsigned i=0;i<9;++i){number(animations[i]->m_bAnimationPlaying);number(animations[i]->m_bStartOnLoad);number(cameras[i]->m_bEnabled);number(cameras[i]->m_bUnknown163);real(cameras[i]->m_fUnknown15C);number(timers[i]->m_bEnabled);real(timers[i]->m_fTimeRemaining);number(timers[i]->m_iRepeatsLeft);}
    for(unsigned i=0;i<2;++i){number(players[i]->m_bEnabled);number(players[i]->m_characterVisible);number(players[i]->m_bVisible);number(players[i]->m_forcedHidden);number(players[i]->m_eAIState);number(players[i]->m_pathToFollow.getObject()==NULL);real(players[i]->m_pathTime);real(players[i]->m_pathGraceTime);number(players[i]->m_isPathing);output->add(&players[i]->m_pathDestination,12);}
    output->add(&client->m_cameraPosition,12);number(client->m_cameraState);number(camera->m_cameraShakes.size());number(camera->m_cameraShakesSecondary.size());
    for(unsigned i=0;i<3;++i)number(descriptors[i]->m_Objects.size());
}
void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);output=&out;mode=current->seed/64%10;listMutation=false;
    keyCalls=closeCalls=animationCalls=cameraCalls=timerCalls=clearCalls=eventCalls=playerCalls=animationAppends=timerAppends=0;
    CPlayer* previousPlayer=client->m_pPlayer;client->m_pPlayer=players[0];int before=g_iTotalCountOfObjects;
    CResourceManager second(resources->getSceneManager());alternative=&second;second.m_GameClients.add(client);second.m_bFlag1=current->seed&1;
    gEditor->m_iFlags=current->seed/32%2?0:2;resources->m_bFlag1=!(current->seed&1);m_gDisableSkillFromBeingCasted=current->seed&2;
    CEditorScene sceneA(L"Skip original scene"),sceneB(L"Skip replacement scene");scenes[0]=&sceneA;scenes[1]=&sceneB;
    CSkipCutscene object(resources);self=&object;self->setGuid(900+current->seed);long long parent=current->seed%29==0?-1:800+current->seed;
    self->setParentGuid(parent);self->SetSceneOwner(&sceneA);self->m_bEnabled=current->seed&1;self->m_bSkipRequested=current->seed&2;self->m_bSkillsDisabled=current->seed&4;
    CEditorBaseObject ancestor;ancestor.setGuid(700+current->seed);ancestor.setParentGuid(parent);sceneA.m_Objects[ancestor.getGuid()]=&ancestor;
    const wchar_t* categories[]={L"Animation Controller",L"Camera Controller",L"Timer"};
    unsigned profile=current->seed/32%6,objectCount=profile<2?0:profile==2?1:profile==4?8:5;
    for(unsigned i=0;i<3;++i){descriptors[i]=new Descriptor(categories[i]);if(profile!=0)sceneA.m_pDescriptorManager->AddDescriptor(descriptors[i]);}
    std::vector<Table*> tables;Table selfTable(self,0x50);selfTable.replace(0x30,reinterpret_cast<void*>(&event));
    for(unsigned i=0;i<9;++i){
        animations[i]=new CAnimationPlayer(resources);cameras[i]=new CCameraController(resources);timers[i]=new CLogicTimer(resources);
        CEditorBaseObject* group[]={animations[i],cameras[i],timers[i]};
        long long parents[]={parent,self->getGuid(),ancestor.getGuid(),123456,-1};
        for(unsigned k=0;k<3;++k){group[k]->setGuid(10000+k*100+i);group[k]->setParentGuid(i==8?parent:parents[i%5]);group[k]->SetSceneOwner(&sceneA);Table*t=new Table(group[k],k==1?0x1e0:0x50);t->replace(0x30,reinterpret_cast<void*>(&event));if(k==1){cameraTables[i]=t;t->replace(0x48,reinterpret_cast<void*>(&cameraEnabled));}tables.push_back(t);if(i<objectCount)descriptors[k]->m_Objects.add(group[k]);}
        animations[i]->m_bAnimationPlaying=(current->seed/8+i)%2;animations[i]->m_bStartOnLoad=(current->seed/16+i)%3==0;
        cameras[i]->m_bEnabled=(current->seed/8+i)%2;cameras[i]->m_bUnknown163=(current->seed/16+i)%2;cameras[i]->m_fUnknown15C=8.5f;
        timers[i]->m_bEnabled=(current->seed/8+i)%2;timers[i]->m_fMinTime=1.25f;timers[i]->m_fMaxTime=-1;timers[i]->m_fTimeRemaining=99;timers[i]->m_iRepeatsLeft=3;
    }
    unsigned capacities[3];for(unsigned k=0;k<3;++k){capacities[k]=descriptors[k]->m_Objects.m_nCapacity;if(profile==5)descriptors[k]->m_Objects.m_nCapacity=1;}
    Table player0(players[0],0x4c8),player1(players[1],0x4c8);playerTables[0]=&player0;playerTables[1]=&player1;
    TSafePointer<CPlayer> witnesses[2];
    for(unsigned i=0;i<2;++i){witnesses[i].setObject(players[i]);playerTables[i]->replace(0x40,reinterpret_cast<void*>(&enabled));playerTables[i]->replace(0x50,reinterpret_cast<void*>(&visible));playerTables[i]->replace(0x310,reinterpret_cast<void*>(&path));playerTables[i]->replace(0x348,reinterpret_cast<void*>(&ai));players[i]->m_bEnabled=false;players[i]->m_characterVisible=false;players[i]->m_bVisible=false;players[i]->m_forcedHidden=true;players[i]->m_eAIState=static_cast<EAIState>(100+i);players[i]->m_isPathing=true;players[i]->m_pathTime=42;players[i]->m_vPosition=Ogre::Vector3(i+1,i+2,i+3);}
    CCameraShake* shake=new CCameraShake;TSafePointer<CCameraShake> shakeWitness;shakeWitness.setObject(shake);
    TSafePointer<CCameraShake>* reference=OGRE_NEW_T(TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL)();reference->setObject(shake);camera->m_cameraShakes.add(reference);camera->m_cameraShakesSecondary.add(reference);
    TSafePointer<CCameraShake>* empty=OGRE_NEW_T(TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL)();camera->m_cameraShakes.add(empty);
    TL_REDIRECT(keyHook,skipKey,&key);TL_REDIRECT(animationHook,skipAnimation,&animation);TL_REDIRECT(cameraHook,skipCamera,&stopCamera);TL_REDIRECT(timerHook,skipTimer,&timer);TL_REDIRECT(clearHook,skipClear,&clear);TL_REDIRECT(skillsHook,skipSkills,&skills);TL_REDIRECT(meshHook,skipMesh,&mesh);TL_REDIRECT(listHook,skipLists,&lists);
    detour::Set closeHook;TL_REDIRECT(closeHook,skipClose,&close);valid();if(closeHook.failed())std::abort();
    typedef void(*Fn)(CSkipCutscene*,float);Fn function=ours?skipCandidate:skipOriginal;
    const unsigned floatBits[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x7f800000u,0xff800000u,0x7fc01234u,1};float elapsed;unsigned bits=floatBits[current->seed/8%8];std::memcpy(&elapsed,&bits,4);
    feclearexcept(FE_ALL_EXCEPT);if(!autotest::beginInvocation(out,function))return;
    for(step=0;step<(current->sequence?3u:1u);++step){unsigned pressed=current->seed/8%4;client->getKeyManager()->m_pressed[27]=static_cast<unsigned char>(step==0?pressed:0);number(step);function(self,elapsed);snapshot();number(shakeWitness.getObject()==NULL);}
    out.callCompleted=1;number(fetestexcept(FE_ALL_EXCEPT));restoreHooks();closeHook.restore();
    if(ours&&current->negative)self->m_bSkipRequested=!self->m_bSkipRequested;flags();
    for(unsigned k=0;k<3;++k)descriptors[k]->m_Objects.m_nCapacity=profile==5?capacities[k]:descriptors[k]->m_Objects.m_nCapacity;
    for(unsigned i=0;i<tables.size();++i){tables[i]->restore();delete tables[i];}
    for(unsigned k=0;k<3;++k)descriptors[k]->m_Objects.clear();sceneA.m_Objects.clear();
    for(unsigned i=0;i<9;++i){animations[i]->SetSceneOwner(NULL);cameras[i]->SetSceneOwner(NULL);timers[i]->SetSceneOwner(NULL);delete animations[i];delete cameras[i];delete timers[i];}
    if(profile==0)for(unsigned k=0;k<3;++k)delete descriptors[k];
    skipClearOriginal(camera);number(shakeWitness.getObject()==NULL);if(shakeWitness.getObject())std::abort();
    player0.restore();player1.restore();client->m_pPlayer=NULL;
    for(unsigned i=0;i<2;++i){nativegame::destroyPlayer(players[i]);number(witnesses[i].getObject()==NULL);if(witnesses[i].getObject())std::abort();}
    client->m_pPlayer=previousPlayer;self->SetSceneOwner(NULL);selfTable.restore();
    // before includes the two player owners; their real D1s invalidated witnesses.
    number(g_iTotalCountOfObjects-before);number(animationAppends);number(timerAppends);
    unsigned reached=(animationAppends?1u:0u)|(timerAppends?2u:0u)|(playerCalls>=3?4u:0u);
    output->add(&reached,sizeof reached);
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host*host,bool sequence)
{
    tlheadless::Environment* environment=new tlheadless::Environment;environment->loadGameSkin();nativegame::Services* services=new nativegame::Services;if(!services->ready())return 1;
    CEditor* editor=static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor),0,0,0));{detour::Set setup;TL_REDIRECT(setup,skipDirectory,&directory);TL_REDIRECT(setup,skipCopy,&copy);if(setup.failed())return 1;skipEditorCtor(editor);}gEditor=editor;editor->m_iFlags=2;
    menugui::Audio* audio=new menugui::Audio(services->master);menugui::Client* owner=new menugui::Client(*services->settings,services->master,*services->master->m_pSoundManager);(void)audio;
    gameclient_fixture::UiOwner* uiOwner=new gameclient_fixture::UiOwner(*services->settings,*owner->client,owner->camera->m_cameras[0],owner->scenes[0],owner->scenes[1],owner->scenes[2],owner->resources);
    resources=owner->resources;client=owner->client;camera=owner->camera;ui=uiOwner->ui;client->m_pGameUI=ui;
    finishlevel::initializeCharacterText();void* categoryData=NULL;std::memcpy(&categoryData,reinterpret_cast<void*>(0x150e108),sizeof categoryData);if(!categoryData)new(reinterpret_cast<void*>(0x150e108))std::wstring(L"MONSTERS");players[0]=nativegame::createPlayer(resources);players[1]=nativegame::createPlayer(resources);
    const char* label=sequence?"skip_cutscene_sequence":"skip_cutscene_update";autotest::Coverage coverage(label,0xde5980);unsigned count=sequence?384:768;unsigned reached=0;
    for(unsigned i=0;i<count;++i){Case c={i,sequence,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,3000,15000);autotest::runChild(candidate,&c,b,3000,15000);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    skip sequence%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",sequence,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}
        if(a.capture.length<sizeof(unsigned)||b.capture.length<sizeof(unsigned))return 1;unsigned observed=0;std::memcpy(&observed,a.capture.data+a.capture.length-sizeof observed,sizeof observed);reached|=observed;
    }
    unsigned required=sequence?1u:7u;host->log("    skip sequence%u reached-mask%u required%u\n",sequence,reached,required);if((reached&required)!=required){coverage.report(host);return 1;}
    coverage.report(host);Case c={263,sequence,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,3000,15000);autotest::runChild(candidate,&c,b,3000,15000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    skip sequence%u negative detected%u completed%u\n",sequence,unsigned(detected),unsigned(completed));return !detected||!completed;
}
int one(const tlhybrid_host* host){return run(host,false);}int sequence(const tlhybrid_host*host){return run(host,true);}
}
TL_TEST(skip_cutscene_update){return systems_fixture::isolated(one,host,180);}
TL_TEST(skip_cutscene_sequence){return systems_fixture::isolated(sequence,host,180);}
