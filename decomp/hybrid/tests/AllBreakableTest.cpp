#include <string>
#include <vector>
#include <map>
#include <new>
#include <stdint.h>
#define private public
#define protected public
#include "Breakable.h"
#include "Character.h"
#include "Level.h"
#include "Particle.h"
#include "Skill.h"
#include "SkillManager.h"
#include "SoundBank.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void, oldBreakUpdate, (CBreakable*,Ogre::Camera*,const Ogre::Vector3&,float), "_ZN10CBreakable6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
TL_ORIGINAL(bool, oldBreakInteract, (CBreakable*,CCharacter*), "_ZN10CBreakable8interactEP10CCharacter")
extern "C" void newBreakUpdate(CBreakable*,Ogre::Camera*,const Ogre::Vector3&,float) __asm__("_ZN10CBreakable6updateEPN4Ogre6CameraERKNS0_7Vector3Ef");
extern "C" bool newBreakInteract(CBreakable*,CCharacter*) __asm__("_ZN10CBreakable8interactEP10CCharacter");
TL_FUNCTION(parentBreakUpdate,"_ZN5CItem6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
TL_FUNCTION(parentBreakInteract,"_ZN5CItem8interactEP10CCharacter")
TL_FUNCTION(breakSelect,"_ZN9CBaseUnit17selectRandomSkillEv")
TL_FUNCTION(breakExecute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(breakPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(breakSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(breakParticleStart,"_ZN9CParticle5StartEv")
TL_FUNCTION(breakIsA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(breakJournal,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(breakQueue,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(breakPlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(breakLoot,"_ZN6CLevel12rollTreasureEP10CCharacterS1_RKN4Ogre7Vector3E")
namespace {
struct Case { unsigned mode, index; };
struct State {
    autotest::Capture* out; Case c; CBreakable* object; CCharacter* character;
    CLevel* level; CSkillManager* manager; CSkill* skill; CParticle* particle;
    Ogre::SceneNode* node; CSoundBank* bank; CSoundBank* voice;
    Ogre::Quaternion orientation; int selection;
};
State* active;
void num(unsigned n){active->out->add(&n,4);}
void fp(float n){active->out->add(&n,4);}
void vec(const Ogre::Vector3& n){fp(n.x);fp(n.y);fp(n.z);}
void issue(){active->out->issue=autotest::Capture::InvalidReport;}
void update(CItem* p,Ogre::Camera* camera,const Ogre::Vector3& pos,float elapsed){
    if(p!=active->object||camera)issue();num(1);vec(pos);fp(elapsed);
    // Realistic base update can change the range state before this override reads it.
    if(active->c.index&16)p->m_bInActiveRange=!p->m_bInActiveRange;
}
bool parent(CItem* p,CCharacter* c){if(p!=active->object||c!=active->character)issue();num(2);num(p->m_bItemFlag218);return false;}
int select(CBaseUnit* p){if(p!=active->object)issue();num(3);return active->selection;}
void remove(CBaseUnit* p,CLevel& l){if(p!=active->object||&l!=active->level)issue();num(4);}
void visible(CItem* p,bool v,bool immediate){if(p!=active->object)issue();num(5);num(v);num(immediate);}
Ogre::Vector3 position(CPositionableObject* p,bool absolute){
    num(6);num(absolute);if(p==active->object){num(0);return Ogre::Vector3(3,7,-11);}
    if(p==active->character){num(1);return Ogre::Vector3(-13,17,19);}issue();return Ogre::Vector3::ZERO;
}
const Ogre::Quaternion& orientation(Ogre::SceneNode* p){if(p!=active->node)issue();num(7);return active->orientation;}
CSkill* execute(CSkillManager* m,CSkill* skill,CBaseUnit* caster,ESKILL_ACTIVATION_TYPE activation,
                const Ogre::Vector3& pos,const Ogre::Quaternion& orient,const Ogre::Vector3& target,CBaseUnit* unit){
    if(m!=active->manager||skill!=active->skill||caster!=active->object||unit!=active->character)issue();
    num(8);num(activation);vec(pos);vec(target);fp(orient.w);fp(orient.x);fp(orient.y);fp(orient.z);
    num(caster->m_bPathingFlag19C);return active->c.index&32?NULL:skill;
}
bool isA(CBaseUnit* p,UNITTYPES::EUNITTYPES type){if(p!=active->character)issue();num(9);num(type);return (active->c.index&64)==0;}
void journal(CCharacter* p,EJournalStatistic stat,int count){if(p!=active->character)issue();num(10);num(stat);num(count);}
void queue(CSoundBank* p,int index,float volume,float radius){if(p!=active->voice)issue();num(11);num(index);fp(volume);fp(radius);}
void setPosition(CPositionableObject* p,const Ogre::Vector3& v){if(p!=active->particle)issue();num(12);vec(v);}
void start(CParticle* p){if(p!=active->particle)issue();num(13);}
int play(CSoundBank* p,int index,Ogre::SceneNode* n,float volume,float radius,bool flag){if(p!=active->bank||n!=active->node)issue();num(14);num(index);fp(volume);fp(radius);num(flag);return 42;}
void loot(CLevel* p,CCharacter* c,CCharacter* source,const Ogre::Vector3& v){if(p!=active->level||c!=active->character||source)issue();num(15);vec(v);}
void side(Case& c,bool ours,autotest::Capture& out){
    autotest::g_arenaUsed=0; State s;active=&s;s.out=&out;s.c=c;s.orientation=Ogre::Quaternion(1.0f,0.25f,-0.5f,0.75f);
    s.object=static_cast<CBreakable*>(autotest::allocate(sizeof(CBreakable)));
    s.character=c.index&1?static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter))):NULL;
    s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));
    CResourceManager* resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));
    resources->m_pLevel=s.level;
    s.object->m_pResourceManager=resources;s.object->m_vPosition=Ogre::Vector3(-23,29,31);
    s.object->m_vScale=Ogre::Vector3(2,4,8);s.object->m_vUp=Ogre::Vector3(-0.25f,1.25f,0.75f);s.object->m_fBaseUnitValue194=2.5f;
    s.object->m_bBlocksPath=c.index&2;s.object->m_bInActiveRange=c.index&4;
    s.object->m_bItemFlag218=c.index&8;s.object->m_bPathingFlag19C=c.index&16;
    s.bank=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.object->m_pSoundBank=s.bank;
    s.voice=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));if(s.character)s.character->m_levelSound=c.index&128?NULL:s.voice;
    s.particle=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));s.object->m_particle=c.index&256?s.particle:NULL;
    s.manager=static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager)));s.object->m_pSkillManager=s.manager;
    CSkill** skills=static_cast<CSkill**>(autotest::allocate(sizeof(CSkill*)*3));
    s.skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));s.skill->m_eActivationType=static_cast<ESKILL_ACTIVATION_TYPE>((c.index/5)%5);
    s.skill->m_skillType=(c.index/7)%4;
    skills[0]=s.skill;skills[1]=c.index&512?NULL:s.skill;skills[2]=s.skill;
    s.manager->m_OtherSkills.m_pData=skills;s.manager->m_OtherSkills.m_nCount=3;s.manager->m_OtherSkills.m_nCapacity=c.index&1024?0:3;
    s.selection=static_cast<int>((c.index/3)%6)-1;
    s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(16));s.object->m_pSceneNode=s.node;
    void** nv=static_cast<void**>(autotest::allocate(0xd0));nv[0xc8/8]=reinterpret_cast<void*>(&orientation);*reinterpret_cast<void***>(s.node)=nv;
    void** bv=static_cast<void**>(autotest::allocate(0x2c8));bv[0x268/8]=reinterpret_cast<void*>(&remove);bv[0x2c0/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(s.object)=bv;
    if(c.mode==0){
        typedef void(*Fn)(CBreakable*,Ogre::Camera*,const Ogre::Vector3&,float);Fn fn=ours?newBreakUpdate:oldBreakUpdate;
        if(!autotest::beginInvocation(out,fn))return;fn(s.object,NULL,Ogre::Vector3(0.5f,-1,2),0.125f);out.callCompleted=1;
    }else{
        unsigned gate=c.index%17;
        if(gate==0)s.object->m_interacted=true;
        if(gate==1)s.object->m_pResourceManager=NULL;
        if(gate==2)resources->m_pLevel=NULL;
        typedef bool(*Fn)(CBreakable*,CCharacter*);Fn fn=ours?newBreakInteract:oldBreakInteract;
        if(!autotest::beginInvocation(out,fn))return;bool result=fn(s.object,s.character);out.callCompleted=1;num(result);
    }
    out.add(s.object,sizeof(CBreakable));
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned mode,const char* name,uintptr_t address,unsigned cases){
    detour::Set hooks;
    TL_REDIRECT(hooks,parentBreakUpdate,&update);TL_REDIRECT(hooks,parentBreakInteract,&parent);
    TL_REDIRECT(hooks,breakSelect,&select);TL_REDIRECT(hooks,breakExecute,&execute);
    TL_REDIRECT(hooks,breakPosition,&position);TL_REDIRECT(hooks,breakSetPosition,&setPosition);
    TL_REDIRECT(hooks,breakParticleStart,&start);TL_REDIRECT(hooks,breakIsA,&isA);
    TL_REDIRECT(hooks,breakJournal,&journal);TL_REDIRECT(hooks,breakQueue,&queue);
    TL_REDIRECT(hooks,breakPlay,&play);TL_REDIRECT(hooks,breakLoot,&loot);
    if(hooks.failed())return 1;autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<cases;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log(" breakable mode%u seed%u exits%d/%d issues%u/%u\n",mode,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=cases||coverage.different||coverage.missing;
}
}
TL_TEST(all_breakable_update){return run(host,0,"all_breakable_update",0x8051b0,32);}
TL_TEST(all_breakable_interact){return run(host,1,"all_breakable_interact",0x8052a0,2048);}
