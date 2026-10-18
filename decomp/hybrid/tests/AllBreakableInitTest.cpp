#include <string>
#include <vector>
#include <map>
#include <new>
#define private public
#define protected public
#include "Breakable.h"
#include "DataGroup.h"
#include "GenericModel.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "MasterResourceManager.h"
#include "Particle.h"
#include "ParticlePreloader.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "TRepository.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void, oldBreakInit, (CBreakable*,CDataGroup*,bool), "_ZN10CBreakable8unitInitEP10CDataGroupb")
extern "C" void newBreakInit(CBreakable*,CDataGroup*,bool) __asm__("_ZN10CBreakable8unitInitEP10CDataGroupb");
TL_FUNCTION(initParent,"_ZN5CItem8unitInitEP10CDataGroupb")
TL_FUNCTION(initMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(initModel,"_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(initChild,"_ZN16CSceneNodeObject17sceneNodeAddChildEPS_")
TL_FUNCTION(initRim,"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(initBehind,"_ZN13CGenericModel15setRenderBehindEb")
TL_FUNCTION(initCollision,"_ZN22CMasterResourceManager17addCollisionModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(initPreload,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(initParticle,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(initSound,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(initAddSound,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(initShadow,"_ZN9CBaseUnit15setCastsShadowsEb")
TL_FUNCTION(initThemes,"_ZN9CBaseUnit14unitInitThemesEv")
TL_FUNCTION(initClean,"_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case { unsigned index; };
struct State {
    autotest::Capture* out; Case c; CBreakable* object; CDataGroup* data;
    CDataGroup* inherited; CMasterResourceManager* master; CResourceManager* resources;
    CGenericModel* model; CCollisionModel* collision; CParticle* particle;
    CSoundData* sound; CSoundBank* bank;
};
State* active;
void num(unsigned n){active->out->add(&n,4);}
void fp(float n){active->out->add(&n,4);}
void text(const std::wstring& s){num(s.size());active->out->add(s.data(),s.size()*sizeof(wchar_t));}
void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
void parent(CItem* self,CDataGroup* data,bool flag){if(self!=active->object||data!=active->data)invalid();num(1);num(flag);self->m_pDataGroup=active->inherited;}
CMasterResourceManager* master(){num(2);return active->master;}
CGenericModel* model(CResourceManager* resources,Ogre::SceneManager* scene,const wchar_t* name,const wchar_t* group,bool skin,bool b,bool c){
    if(resources!=active->resources||scene!=resources->m_pSceneManager)invalid();num(3);text(name);text(group);num(skin);num(b);num(c);return active->model;
}
void child(CSceneNodeObject* self,CSceneNodeObject* model){if(self!=active->object||model!=active->model)invalid();num(4);}
void modelVisible(CSceneNodeObject* self,bool flag){if(self!=active->model)invalid();num(5);num(flag);}
void modelPosition(CPositionableObject* self,float x,float y,float z){if(self!=active->model)invalid();num(6);fp(x);fp(y);fp(z);}
void renderQueue(Ogre::Entity*,unsigned char queue){num(7);num(queue);}
void rim(CGenericModel* self,std::wstring name){if(self!=active->model)invalid();num(8);text(name);}
void behind(CGenericModel* self,bool flag){if(self!=active->model)invalid();num(9);num(flag);}
CCollisionModel* collision(CMasterResourceManager* self,std::wstring name){if(self!=active->master)invalid();num(10);text(name);return active->collision;}
void preload(CParticlePreloader* self,std::wstring name){if(self!=active->master->m_pParticlePreloader)invalid();num(11);text(name);}
CParticle* particle(CResourceManager* self,const wchar_t* name){if(self!=active->resources)invalid();num(12);text(name);return active->c.index&16?NULL:active->particle;}
CSoundData* sound(CSoundBankDataInformation* self,const std::wstring& name){if(self!=active->master->m_pSoundBankDataInformation)invalid();num(13);text(name);return active->c.index&32?NULL:active->sound;}
void addSound(CSoundBank* self,int index,long long guid){if(self!=active->bank)invalid();num(14);num(index);active->out->add(&guid,sizeof(guid));}
void shadows(CBaseUnit* self,bool enabled){if(self!=active->object)invalid();num(15);num(enabled);self->m_bCastsShadows=enabled;}
void visible(CItem* self,bool flag,bool immediate){if(self!=active->object)invalid();num(16);num(flag);num(immediate);}
void themes(CBaseUnit* self){if(self!=active->object)invalid();num(17);}
std::wstring clean(const std::wstring& input){num(18);text(input);return std::wstring(L"clean:")+input;}
CDataGroup* group(){std::wstring empty;return new CDataGroup(L"UNIT",NULL,8,8,new TRepository<std::wstring>(empty));}
void side(Case& c,bool ours,autotest::Capture& out){
    autotest::g_arenaUsed=0;State s;active=&s;s.out=&out;s.c=c;
    const unsigned cells[]={0x14dd9c8,0x14dd9d8,0x14dda88,0x152f138,0x147ad48};
    for(unsigned i=0;i<5;++i)new(reinterpret_cast<void*>(cells[i]))std::wstring();
    s.data=group();s.inherited=group();
    const wchar_t* meshes[]={L"",L"box",L"Жестянка",L"already.mesh"};
    const wchar_t* particles[]={L"",L"SPARK",L"dir/spark",L"dir/sparks",L"dir\\sparks",L"longbarefilename",L"/1234567",L"/12345678"};
    s.data->AddDataValue(L"RESOURCEDIRECTORY",c.index&1?L"media/props/":L"",false);
    s.data->AddDataValue(L"MESHFILE",meshes[(c.index/2)%4],false);
    if(c.index&8)s.data->AddDataValue(L"COLLISIONFILE",c.index&64?L"":L"special/collider.mesh",false);
    s.data->AddDataValue(L"INTERACT_PARTICLE",particles[(c.index/7)%8],false);
    s.data->AddDataValue(L"INTERACT_SOUND",L"wrong input",false);
    s.data->AddDataValue(L"ALLOW_HWSKINNING",bool(c.index&2));
    s.inherited->AddDataValue(L"INTERACT_SOUND",c.index&64?L"":L"MiXeD_soundЖ",false);
    s.inherited->AddDataValue(L"ALLOW_HWSKINNING",bool(c.index&4));
    s.inherited->AddDataValue(L"SHADOWS",bool(c.index&8));
    s.object=static_cast<CBreakable*>(autotest::allocate(sizeof(CBreakable)));
    s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));
    s.resources->m_pSceneManager=reinterpret_cast<Ogre::SceneManager*>(autotest::allocate(16));
    CLevel* level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));
    CLevelTemplateData* data=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));
    new(&data->m_sRimlightTexture)std::wstring(L"level rim.dds");
    level->m_pLevelTemplateData=c.index&128?data:NULL;s.resources->m_pLevel=c.index&256?NULL:level;
    s.object->m_pResourceManager=s.resources;s.object->m_bLevelLighting=c.index&512;s.object->m_bBlocksPath=c.index&1024;
    s.bank=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.object->m_pSoundBank=s.bank;
    s.master=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));
    s.master->m_pParticlePreloader=static_cast<CParticlePreloader*>(autotest::allocate(sizeof(CParticlePreloader)));
    s.master->m_pSoundBankDataInformation=static_cast<CSoundBankDataInformation*>(autotest::allocate(sizeof(CSoundBankDataInformation)));
    s.model=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));
    void** mv=static_cast<void**>(autotest::allocate(0x60));mv[0x50/8]=reinterpret_cast<void*>(&modelVisible);mv[0x58/8]=reinterpret_cast<void*>(&modelPosition);*reinterpret_cast<void***>(s.model)=mv;
    s.model->m_pEntity=static_cast<Ogre::Entity*>(autotest::allocate(16));
    void** ev=static_cast<void**>(autotest::allocate(0x148));ev[0x140/8]=reinterpret_cast<void*>(&renderQueue);*reinterpret_cast<void***>(s.model->m_pEntity)=ev;
    s.collision=static_cast<CCollisionModel*>(autotest::allocate(16));s.particle=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));
    s.sound=static_cast<CSoundData*>(autotest::allocate(sizeof(CSoundData)));s.sound->m_iGuid=0x1234567890123LL;
    void** bv=static_cast<void**>(autotest::allocate(0x2c8));bv[0x2c0/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(s.object)=bv;
    typedef void(*Fn)(CBreakable*,CDataGroup*,bool);Fn fn=ours?newBreakInit:oldBreakInit;
    if(!autotest::beginInvocation(out,fn))return;fn(s.object,c.index%19==0?NULL:s.data,c.index&1);out.callCompleted=1;
    num(s.object->m_pUnitModel==s.model);num(s.object->m_collisionModel==s.collision);num(s.object->m_particle==s.particle);
    num(s.object->m_bPathingFlag19C);num(s.object->m_bItemFlag1F0);num(s.object->m_bCastsShadows);
    data->m_sRimlightTexture.~basic_string();delete s.data;delete s.inherited;
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(all_breakable_unit_init){
    detour::Set hooks;
    TL_REDIRECT(hooks,initParent,&parent);TL_REDIRECT(hooks,initMaster,&master);TL_REDIRECT(hooks,initModel,&model);
    TL_REDIRECT(hooks,initChild,&child);TL_REDIRECT(hooks,initRim,&rim);TL_REDIRECT(hooks,initBehind,&behind);
    TL_REDIRECT(hooks,initCollision,&collision);TL_REDIRECT(hooks,initPreload,&preload);TL_REDIRECT(hooks,initParticle,&particle);
    TL_REDIRECT(hooks,initSound,&sound);TL_REDIRECT(hooks,initAddSound,&addSound);TL_REDIRECT(hooks,initShadow,&shadows);
    TL_REDIRECT(hooks,initThemes,&themes);TL_REDIRECT(hooks,initClean,&clean);
    if(hooks.failed())return 1;autotest::Coverage coverage("all_breakable_unit_init",0x80d970);
    for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;
}
