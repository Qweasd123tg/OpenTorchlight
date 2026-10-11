// Original/replacement comparisons for independent editor API calls.
// Inputs exercise disabled and missing-service guards, exact arguments,
// string contents, receiver identity, callback order and changing singletons.
#include <Ogre.h>
#include <cstring>
#include <climits>
#include <limits>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Editor.h"
#include "iEditorResourceManager.h"

TL_ORIGINAL(void, original0, (unsigned int, bool), "_Z18EditorSetFlagStatejb")
extern "C" void candidate0(unsigned int, bool) __asm__("_Z18EditorSetFlagStatejb");
TL_ORIGINAL(void, original1, (bool), "_Z27EditorResnapSelectedObjectsb")
extern "C" void candidate1(bool) __asm__("_Z27EditorResnapSelectedObjectsb");
TL_ORIGINAL(void, original2, (), "_Z22EditorResetOrientationv")
extern "C" void candidate2() __asm__("_Z22EditorResetOrientationv");
TL_ORIGINAL(void, original3, (), "_Z16EditorResetScalev")
extern "C" void candidate3() __asm__("_Z16EditorResetScalev");
TL_ORIGINAL(void, original4, (float), "_Z24EditorApplyRotationNoisef")
extern "C" void candidate4(float) __asm__("_Z24EditorApplyRotationNoisef");
TL_ORIGINAL(void, original5, (bool), "_Z25EditorSnapObjectsToGroundb")
extern "C" void candidate5(bool) __asm__("_Z25EditorSnapObjectsToGroundb");
TL_ORIGINAL(void, original6, (float), "_Z22EditorApplyNormalNoisef")
extern "C" void candidate6(float) __asm__("_Z22EditorApplyNormalNoisef");
TL_ORIGINAL(void, original7, (float, bool), "_Z21EditorApplyScaleNoisefb")
extern "C" void candidate7(float, bool) __asm__("_Z21EditorApplyScaleNoisefb");
TL_ORIGINAL(void, original8, (wchar_t*), "_Z30EditorSetEditorCompletedQuestsPw")
extern "C" void candidate8(wchar_t*) __asm__("_Z30EditorSetEditorCompletedQuestsPw");
TL_ORIGINAL(void, original9, (wchar_t*), "_Z27EditorSetEditorActiveQuestsPw")
extern "C" void candidate9(wchar_t*) __asm__("_Z27EditorSetEditorActiveQuestsPw");
TL_ORIGINAL(void, original10, (const wchar_t*), "_Z15EditorCreateModPKw")
extern "C" void candidate10(const wchar_t*) __asm__("_Z15EditorCreateModPKw");
TL_ORIGINAL(void, original11, (wchar_t*), "_Z17EditorReloadSkillPw")
extern "C" void candidate11(wchar_t*) __asm__("_Z17EditorReloadSkillPw");
TL_ORIGINAL(void, original12, (), "_Z18reloadSpawnClassesv")
extern "C" void candidate12() __asm__("_Z18reloadSpawnClassesv");
TL_ORIGINAL(void, original13, (wchar_t*), "_Z22EditorSetEditorPetTypePw")
extern "C" void candidate13(wchar_t*) __asm__("_Z22EditorSetEditorPetTypePw");
TL_ORIGINAL(void, original14, (wchar_t*), "_Z29EditorSetEditorCharacterClassPw")
extern "C" void candidate14(wchar_t*) __asm__("_Z29EditorSetEditorCharacterClassPw");
TL_ORIGINAL(void, original15, (wchar_t*), "_Z15EditorPlayMusicPw")
extern "C" void candidate15(wchar_t*) __asm__("_Z15EditorPlayMusicPw");
TL_FUNCTION(target_setFlag, "_ZN7CEditor7setFlagE13EEDITOR_FLAGS")
TL_FUNCTION(target_removeFlag, "_ZN7CEditor10removeFlagE13EEDITOR_FLAGS")
TL_FUNCTION(target_resnap, "_ZN20CEditorObjectManager27EditorResnapSelectedObjectsEb")
TL_FUNCTION(target_orientation, "_ZN20CEditorObjectManager22EditorResetOrientationEv")
TL_FUNCTION(target_scale, "_ZN20CEditorObjectManager16EditorResetScaleEv")
TL_FUNCTION(target_rotationNoise, "_ZN20CEditorObjectManager24EditorApplyRotationNoiseEf")
TL_FUNCTION(target_snapGround, "_ZN20CEditorObjectManager25EditorSnapObjectsToGroundEb")
TL_FUNCTION(target_normalNoise, "_ZN20CEditorObjectManager22EditorApplyNormalNoiseEf")
TL_FUNCTION(target_scaleNoise, "_ZN20CEditorObjectManager21EditorApplyScaleNoiseEfb")
TL_FUNCTION(target_completed, "_ZN7CEditor18setCompletedQuestsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_active, "_ZN7CEditor15setActiveQuestsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_modSingleton, "_ZN14CModFileFilter12getSingletonEv")
TL_FUNCTION(target_modCreate, "_ZN14CModFileFilter9addNewModERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_skillSingleton, "_ZN12CSkillParser12getSingletonEv")
TL_FUNCTION(target_parseSkill, "_ZN12CSkillParser10parseSkillERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_spawnSingleton, "_ZN17CSpawnClassParser12getSingletonEv")
TL_FUNCTION(target_spawnReload, "_ZN17CSpawnClassParser19reloadFromDirectoryEPKw")
TL_FUNCTION(target_getClient, "_ZN7CEditor13getGameClientEv")
TL_FUNCTION(target_createPet, "_ZN11CGameClient20setEditorCreationPetESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_createClass, "_ZN11CGameClient22setEditorCreationClassESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_masterSingleton, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(target_playMusic, "_ZN13CSoundManager9playMusicERSbIwSt11char_traitsIwESaIwEEb")

namespace {
struct Case { unsigned operation, mode, flag; bool value; float amount; unsigned text; };
const Case* input;
autotest::Capture* capture;
unsigned clientCalls;
void* editors[2]; void* managers[2]; void* clients[2]; void* master;
void* mods; void* skills; void* spawns; void* sound;
void number(unsigned n) { capture->add(&n, sizeof(n)); }
unsigned identity(void* p) {
    if (!p) return 0;
    for (unsigned i=0;i<2;++i) {
        if (p==editors[i]) return 10+i;
        if (p==managers[i]) return 20+i;
        if (p==clients[i]) return 30+i;
    }
    if(p==master) return 40; if(p==mods) return 50;
    if(p==skills) return 60; if(p==spawns) return 70;
    if(p==sound) return 80;
    return 999;
}
void event(unsigned id, void* p) { number(id); number(identity(p)); }
void swapEditor() { if(input->mode==6) gEditor=static_cast<CEditor*>(editors[1]); }
void setFlag(void*p,unsigned v){event(1,p);number(v);}
void removeFlag(void*p,unsigned v){event(2,p);number(v);}
void resnap(void*p,bool v){event(3,p);number(v);}
void orientation(void*p){event(4,p);}
void scale(void*p){event(5,p);}
void rotationNoise(void*p,float v){event(6,p);capture->add(&v,4);}
void snapGround(void*p,bool v){event(7,p);number(v);}
void normalNoise(void*p,float v){event(8,p);capture->add(&v,4);}
void scaleNoise(void*p,float v,bool b){event(9,p);capture->add(&v,4);number(b);}
void completed(void*p,const std::wstring&s){event(10,p);capture->addText(s);swapEditor();}
void active(void*p,const std::wstring&s){event(11,p);capture->addText(s);swapEditor();}
void* modSingleton(){event(12,mods);swapEditor();return mods;}
void modCreate(void*p,const std::wstring&s){event(13,p);capture->addText(s);}
void* skillSingleton(){event(14,skills);swapEditor();return skills;}
void parseSkill(void*p,const std::wstring&s){event(15,p);capture->addText(s);}
void* spawnSingleton(){event(16,spawns);swapEditor();return spawns;}
void spawnReload(void*p,const wchar_t*s){event(17,p);capture->addText(std::wstring(s));}
void* getClient(void*p){event(18,p);++clientCalls;swapEditor();return input->mode==4||(input->mode==9&&clientCalls>1)?NULL:clients[(clientCalls-1)%2];}
void createPet(void*p,std::wstring s){event(19,p);capture->addText(s);}
void createClass(void*p,std::wstring s){event(20,p);capture->addText(s);}
void* masterSingleton(){event(21,master);swapEditor();return master;}
int playMusic(void*p,std::wstring&s,bool value){event(22,p);capture->addText(s);number(value);return 197;}
struct Resource : iEditorResourceManager {
    virtual void editorUpdateSceneOnce(int){}
    virtual void* getWindowHandle(){return 0;}
    virtual CSettings* getSettings(){return 0;}
    virtual Ogre::SceneManager* getSceneManager(){return 0;}
    virtual CSoundManager* getSoundManager(){return 0;}
    virtual Ogre::RenderWindow* getRenderWindow(){return 0;}
    virtual Ogre::Camera* getGameCamera(){return 0;}
    virtual void updateAspectRatio(float,float){}
    virtual CGameClient* getGameClient(){event(23,this);swapEditor();return input->mode==4?NULL:static_cast<CGameClient*>(clients[0]);}
};
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,sizeof(v));}
void side(Case&c,bool ours,autotest::Capture&out) {
    input=&c; capture=&out; clientCalls=0;
    unsigned long long editor[2][0x1f8/8], manager[2][32], client[2][32], masterStorage[0x190/8];
    unsigned long long modStorage[32],skillStorage[32],spawnStorage[32],soundStorage[32];
    std::memset(editor,0,sizeof(editor));std::memset(manager,0,sizeof(manager));
    std::memset(client,0,sizeof(client));std::memset(masterStorage,0,sizeof(masterStorage));
    Resource resource;
    master=masterStorage;mods=modStorage;skills=skillStorage;spawns=spawnStorage;sound=soundStorage;
    for(unsigned i=0;i<2;++i){editors[i]=editor[i];managers[i]=manager[i];clients[i]=client[i];
        reinterpret_cast<char*>(editor[i])[0x49]=(c.mode==1 || c.mode==7);
        pointerAt(editor[i],0x58,c.mode==2||c.mode==7?NULL:&resource);
        pointerAt(editor[i],0x120,c.mode==3?NULL:managers[i]);}
    pointerAt(master,0x98,c.mode==5?NULL:sound);
    gEditor=static_cast<CEditor*>(editors[0]);
    std::wstring value;
    switch(c.text%6){case 0:value=L"";break;case 1:value=L"quest_1";break;
        case 2:value=L"мод и квест Ω";break;case 3:value=std::wstring(1024,L'x');break;
        case 4:value=L"a;b,c\nsecond";break;default:value=std::wstring(L"a\0hidden",8);break;}
    wchar_t* text=const_cast<wchar_t*>(value.c_str());
    detour::Set patches;
    TL_REDIRECT(patches,target_setFlag,&setFlag);
    TL_REDIRECT(patches,target_removeFlag,&removeFlag);
    TL_REDIRECT(patches,target_resnap,&resnap);
    TL_REDIRECT(patches,target_orientation,&orientation);
    TL_REDIRECT(patches,target_scale,&scale);
    TL_REDIRECT(patches,target_rotationNoise,&rotationNoise);
    TL_REDIRECT(patches,target_snapGround,&snapGround);
    TL_REDIRECT(patches,target_normalNoise,&normalNoise);
    TL_REDIRECT(patches,target_scaleNoise,&scaleNoise);
    TL_REDIRECT(patches,target_completed,&completed);
    TL_REDIRECT(patches,target_active,&active);
    TL_REDIRECT(patches,target_modSingleton,&modSingleton);
    TL_REDIRECT(patches,target_modCreate,&modCreate);
    TL_REDIRECT(patches,target_skillSingleton,&skillSingleton);
    TL_REDIRECT(patches,target_parseSkill,&parseSkill);
    TL_REDIRECT(patches,target_spawnSingleton,&spawnSingleton);
    TL_REDIRECT(patches,target_spawnReload,&spawnReload);
    TL_REDIRECT(patches,target_getClient,&getClient);
    TL_REDIRECT(patches,target_createPet,&createPet);
    TL_REDIRECT(patches,target_createClass,&createClass);
    TL_REDIRECT(patches,target_masterSingleton,&masterSingleton);
    TL_REDIRECT(patches,target_playMusic,&playMusic);
    if(patches.failed()) _exit(41);
    switch(c.operation) {
    case 0: autotest::invoke(out,ours?&candidate0:&original0, c.flag, c.value);break;
    case 1: autotest::invoke(out,ours?&candidate1:&original1, c.value);break;
    case 2: autotest::invoke(out,ours?&candidate2:&original2);break;
    case 3: autotest::invoke(out,ours?&candidate3:&original3);break;
    case 4: autotest::invoke(out,ours?&candidate4:&original4, c.amount);break;
    case 5: autotest::invoke(out,ours?&candidate5:&original5, c.value);break;
    case 6: autotest::invoke(out,ours?&candidate6:&original6, c.amount);break;
    case 7: autotest::invoke(out,ours?&candidate7:&original7, c.amount, c.value);break;
    case 8: autotest::invoke(out,ours?&candidate8:&original8, text);break;
    case 9: autotest::invoke(out,ours?&candidate9:&original9, text);break;
    case 10: autotest::invoke(out,ours?&candidate10:&original10, c.mode == 8 ? NULL : text);break;
    case 11: autotest::invoke(out,ours?&candidate11:&original11, text);break;
    case 12: autotest::invoke(out,ours?&candidate12:&original12);break;
    case 13: autotest::invoke(out,ours?&candidate13:&original13, text);break;
    case 14: autotest::invoke(out,ours?&candidate14:&original14, text);break;
    case 15: autotest::invoke(out,ours?&candidate15:&original15, text);break;

    }
    number(clientCalls);number(identity(gEditor));
    out.add(editor,sizeof(editor));out.add(manager,sizeof(manager));out.add(client,sizeof(client));
    patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}
void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}

TL_TEST(editor_mass_controls_differential) {
    int failures=0;
    const unsigned flags[]={0,1,2,3,0x80000000u,0xffffffffu,0x12345678u};
    const float values[]={0.0f,-0.0f,1.0f,-1.0f,0.125f,1234.5f,
        std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()};
    const uint64_t addresses[]={
        (uint64_t)(uintptr_t)&original0,
        (uint64_t)(uintptr_t)&original1,
        (uint64_t)(uintptr_t)&original2,
        (uint64_t)(uintptr_t)&original3,
        (uint64_t)(uintptr_t)&original4,
        (uint64_t)(uintptr_t)&original5,
        (uint64_t)(uintptr_t)&original6,
        (uint64_t)(uintptr_t)&original7,
        (uint64_t)(uintptr_t)&original8,
        (uint64_t)(uintptr_t)&original9,
        (uint64_t)(uintptr_t)&original10,
        (uint64_t)(uintptr_t)&original11,
        (uint64_t)(uintptr_t)&original12,
        (uint64_t)(uintptr_t)&original13,
        (uint64_t)(uintptr_t)&original14,
        (uint64_t)(uintptr_t)&original15
    };
    for(unsigned operation=0;operation<16;++operation) {

        autotest::Coverage coverage("editor_mass_controls_differential",addresses[operation]);
        for(unsigned n=0;n<384;++n){
            Case c={operation,n%10,flags[(n/10)%7],((n/10)%2)!=0,values[(n/20)%9],(n/10)%6};
            autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
            int result=coverage.observe(host,a,b);
            if(result){host->log("    editor control operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);++failures;break;}
        }
        coverage.report(host);if(failures)return failures;
    }
    return failures;
}
