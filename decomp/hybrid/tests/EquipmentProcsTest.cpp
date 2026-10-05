#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "SkillManager.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentProcs,(CEquipment*,CCharacter*,EEFFECT_TYPE,CBaseUnit*),"_ZN10CEquipment12executeProcsEP10CCharacter12EEFFECT_TYPEP9CBaseUnit")
TL_FUNCTION(prHas,"_ZN9CBaseUnit9hasEffectE12EEFFECT_TYPE")
TL_FUNCTION(prRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(prValue,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(prSkill,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(prExecute,"_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
TL_FUNCTION(prPosition,"_ZN19CPositionableObject11getPositionEb")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,count,match,roll,value,flags,mode;};struct World;World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void vector(const Ogre::Vector3& v){real(v.x);real(v.y);real(v.z);}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
TArrayList<CEffect*>* lists(CEffectManager* p){return reinterpret_cast<TArrayList<CEffect*>*>(p->m_EffectData10+0x18);}
struct World{Raw<CEquipment> item;Raw<CCharacter> actor;Raw<CBaseUnit> target,parent;Raw<CEffect> effects[8];Raw<CEffectManager> managers[2];Raw<CSkillManager> skills[2];unsigned long long tokens[8];Ogre::SceneNode parentNode,actorNode,targetNode;unsigned rolls,values,gets,executes,positions;bool changed;
 World():parentNode(NULL),actorNode(NULL),targetNode(NULL),rolls(0),values(0),gets(0),executes(0),positions(0),changed(false){parentNode.addChild(&actorNode);parentNode.addChild(&targetNode);parentNode.setPosition(13,17,-19);parentNode.setOrientation(Ogre::Quaternion(Ogre::Degree(37),Ogre::Vector3::UNIT_Y));actorNode.setPosition(2,3,5);targetNode.setPosition(-7,11,23);actorNode.setOrientation(Ogre::Quaternion(Ogre::Degree(21),Ogre::Vector3::UNIT_X));actor.get()->m_pSceneNode=&actorNode;actor.get()->m_pParentPositionableObject=parent.get();actor.get()->m_vPosition=actorNode.getPosition();target.get()->m_pSceneNode=&targetNode;target.get()->m_pParentPositionableObject=parent.get();target.get()->m_vPosition=targetNode.getPosition();parent.get()->m_pSceneNode=&parentNode;for(unsigned i=0;i<8;++i){new(&effects[i].get()->m_sName)std::wstring(L"skill");effects[i].get()->m_sName+=wchar_t(L'A'+i);effects[i].get()->m_iLevel=i*7+1;effects[i].get()->m_eType=static_cast<EEFFECT_TYPE>((input->match>>i%4)&1?73:74);}for(unsigned m=0;m<2;++m)for(unsigned a=0;a<4;++a){new(lists(managers[m].get())+a)TArrayList<CEffect*>;for(unsigned j=0;j<(a==3?1:(input->count+a)%4);++j)lists(managers[m].get())[a].add(effects[(m*4+a+j)%8].get());}}
 ~World(){for(unsigned m=0;m<2;++m)for(unsigned a=0;a<4;++a)lists(managers[m].get())[a].~TArrayList<CEffect*>();for(unsigned i=0;i<8;++i){typedef std::wstring Text;effects[i].get()->m_sName.~Text();}}
 int id(CEffect* p){for(unsigned i=0;i<8;++i)if(p==effects[i].get())return i;return -1;}
};
bool has(CBaseUnit* p,EEFFECT_TYPE type){number(10);number(p==world->item.get());number(type);return (input->flags&1)!=0;}
int random(int minimum,int maximum){number(11);number(minimum);number(maximum);++world->rolls;if(input->mode==1&&!world->changed){world->changed=true;lists(world->managers[0].get())[0][0]=world->effects[7].get();}static const int rolls[]={0,1,25,50,99,100};return rolls[input->roll];}
float value(CEffect* p,EEFFECT_VALUES type){number(12);number(world->id(p));number(type);++world->values;static const float values[]={-1,0,0.5f,1,25,49.999996f,50,99,100,101};float result=values[input->value%10];if(input->value==10){unsigned bits=0x7fc00000;std::memcpy(&result,&bits,4);}return result;}
CSkill* skill(CSkillManager* p,const std::wstring& name,int level){number(13);number(p==world->skills[1].get());text(name);number(level);++world->gets;if(input->mode==4)world->item.get()->m_pSkillManager=world->skills[1].get();if(input->mode==6){world->targetNode.translate(Ogre::Vector3(1,2,3));world->target.get()->m_vPosition=world->targetNode.getPosition();}return input->flags&8?NULL:reinterpret_cast<CSkill*>(&world->tokens[(world->gets-1)%8]);}
CSkill* execute(CSkillManager* p,CSkill* skill,CBaseUnit* caster,ESKILL_ACTIVATION_TYPE activation,const Ogre::Vector3& position,const Ogre::Quaternion& orientation,const Ogre::Vector3& targetPosition,CBaseUnit* target){number(14);number(p==world->skills[1].get());number(caster==world->actor.get());number(activation);vector(position);real(orientation.w);real(orientation.x);real(orientation.y);real(orientation.z);vector(targetPosition);number(target==world->target.get()?1:target==NULL?0:-1);number(skill==reinterpret_cast<CSkill*>(&world->tokens[(world->gets-1)%8]));++world->executes;if(input->mode==2&&!world->changed){world->changed=true;lists(world->managers[0].get())[0].add(world->effects[7].get());}if(input->mode==3)world->item.get()->m_pEffectManager=world->managers[1].get();return skill;}
detour::Set positionPatch;
Ogre::Vector3 position(CPositionableObject* p,bool absolute){number(15);number(p==world->actor.get()?1:p==world->target.get()?2:-1);number(absolute);++world->positions;if(input->mode==5&&p==world->actor.get())world->actorNode.setOrientation(Ogre::Quaternion(Ogre::Degree(13+world->positions*7),Ogre::Vector3::UNIT_Z));positionPatch.restore();Ogre::Vector3 result=reinterpret_cast<Ogre::Vector3(*)(CPositionableObject*,bool)>(prPosition_original)(p,absolute);TL_REDIRECT(positionPatch,prPosition,&position);return result;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.item.get()->m_pEffectManager=w.managers[0].get();w.item.get()->m_pSkillManager=c.flags&2?w.skills[0].get():NULL;if(c.mode==7)for(unsigned a=0;a<3;++a)if(lists(w.managers[0].get())[a].size()>1)lists(w.managers[0].get())[a].m_nCapacity=1;detour::Set patches;TL_REDIRECT(patches,prHas,&has);TL_REDIRECT(patches,prRandom,&random);TL_REDIRECT(patches,prValue,&value);TL_REDIRECT(patches,prSkill,&skill);TL_REDIRECT(patches,prExecute,&execute);TL_REDIRECT(positionPatch,prPosition,&position);if(patches.failed()||positionPatch.failed())_exit(42);for(unsigned repeat=0;repeat<2;++repeat){CBaseUnit* target=c.flags&4?w.target.get():NULL;if(ours)w.item.get()->executeProcs(w.actor.get(),static_cast<EEFFECT_TYPE>(73),target);else originalEquipmentProcs(w.item.get(),w.actor.get(),static_cast<EEFFECT_TYPE>(73),target);number(w.rolls);number(w.values);number(w.gets);number(w.executes);number(w.positions);}positionPatch.restore();}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_procs_differential){int failures=0;for(unsigned n=0;n<9284;++n){Case c={n,n%4,(n/4)%16,(n/64)%6,(n/384)%11,(n/24)%16,0};if(n>=8448){unsigned j=n-8448;c.count=1+j%3;c.match=15;c.roll=0;c.value=9;c.flags=3+(j%2?4:0);c.mode=1+(j/96)%7;}if(n>=9152){unsigned j=n-9152;c.count=1;c.match=15;c.roll=j%6;c.value=(j/6)%11;c.flags=3+(j/66?4:0);c.mode=0;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WEXITSTATUS(b.status)==0&&WIFEXITED(b.status)&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    procs case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(!ok){for(unsigned k=0;k<a.capture.length&&k<b.capture.length;k+=4){unsigned av=0,bv=0;std::memcpy(&av,a.capture.data+k,4);std::memcpy(&bv,b.capture.data+k,4);if(av!=bv)host->log("    offset %u %08x/%08x\n",k,av,bv);}}TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment procs: 9284 cases, two calls per side\n");return failures;}
