#include <cstring>
#include <limits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Missile.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalMissileApply,(CEquipment*,CMissile*,CCharacter*,const Ogre::Vector3*,float,float),"_ZN10CEquipment22missileApplyingEffectsEP8CMissileP10CCharacterPKN4Ogre7Vector3Eff")
TL_FUNCTION(maEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(maAttack,"_ZN10CCharacter10rollAttackER6CLevelPS_P10CEquipmentjff13EDAMAGE_TYPES")
extern "C" void* missileApplyCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* missileApplyEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" bool tracedoriginalMissileApply(CEquipment*,CMissile*,CCharacter*,const Ogre::Vector3*,float,float) __asm__("_ZN10CEquipment22missileApplyingEffectsEP8CMissileP10CCharacterPKN4Ogre7Vector3Eff");
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,owner,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
struct World;World*world;
struct World{Raw<CEquipment>item,other;Raw<CCharacter>actors[3];Raw<CMissile>missile;Raw<CResourceManager>managers[2];unsigned long long levels[2];void*table[112];unsigned getters,attacks;
 World():getters(0),attacks(0){std::memset(table,0,sizeof(table));*reinterpret_cast<void***>(item.get())=table;void**t=missileApplyEquipmentTable+2;std::memcpy(other.get(),&t,sizeof(t));t=missileApplyCharacterTable+2;for(unsigned i=0;i<3;++i)std::memcpy(actors[i].get(),&t,sizeof(t));for(unsigned i=0;i<2;++i)managers[i].get()->m_pLevel=reinterpret_cast<CLevel*>(&levels[i]);}
 int id(CCharacter*p){for(unsigned i=0;i<3;++i)if(p==actors[i].get())return i;return p?-2:-1;}
};
bool enemy(CCharacter*t,CCharacter*owner){number(10);number(world->id(t));number(world->id(owner));if(input->mode==1)world->missile.get()->m_bUnknown294=!world->missile.get()->m_bUnknown294;if(input->mode==2)world->missile.get()->m_pRunicCore=world->actors[1].get();return input->flags&1;}
CCharacter*equipped(CEquipment*p){number(11);number(p==world->item.get());unsigned n=world->getters++;if(input->mode==3)world->item.get()->m_pResourceManager=world->managers[1].get();if(input->mode==4&&n%2==1)world->item.get()->m_pResourceManager=world->managers[1].get();if(input->flags&8)return NULL;return world->actors[(input->mode==5&&n%2)?1:0].get();}
bool attack(CCharacter*p,CLevel&level,CCharacter*target,CEquipment*item,unsigned type,float damage,float effect,EDAMAGE_TYPES dt){number(12);number(world->id(p));number(&level==reinterpret_cast<CLevel*>(&world->levels[0])?0:&level==reinterpret_cast<CLevel*>(&world->levels[1])?1:2);number(world->id(target));number(item==world->item.get());number(type);real(damage);real(effect);number(dt);++world->attacks;return input->flags&16;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.table[0x340/8]=reinterpret_cast<void*>(&equipped);CEquipment*p=w.item.get();p->m_pResourceManager=(c.flags&4)?NULL:w.managers[0].get();CMissile*m=w.missile.get();m->m_pRunicCore=c.owner==0?static_cast<CRunicCore*>(w.actors[0].get()):c.owner==1?static_cast<CRunicCore*>(w.other.get()):NULL;m->m_bUnknown294=(c.flags&2)!=0;CCharacter*t=(c.flags&32)?NULL:w.actors[2].get();Ogre::Vector3 position(3,5,7);static const float values[]={-1.0f,-0.0f,0.125f,1.0f,3.25f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float damage=values[c.n%7],effect=values[(c.n/7)%7];
 detour::Set patches;TL_REDIRECT(patches,maEnemy,&enemy);TL_REDIRECT(patches,maAttack,&attack);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalMissileApply:&originalMissileApply,p,m,t,c.n%2?&position:static_cast<const Ogre::Vector3*>(NULL),damage,effect);}else{bool result=ours?p->CEquipment::missileApplyingEffects(m,t,c.n%2?&position:NULL,damage,effect):originalMissileApply(p,m,t,c.n%2?&position:NULL,damage,effect);number(result);}number(w.getters);number(w.attacks);number(m->m_bUnknown294);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_missile_apply_differential){
autotest::Coverage coverage0("equipment_missile_apply_differential",(uint64_t)(uintptr_t)&originalMissileApply);
int failures=0;for(unsigned n=0;n<2304;++n){Case c={n,n%64,(n/64)%3,(n/192)%6};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    missile apply case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    missile apply: 2304 cases, two calls per side\n");{coverage0.report(host);return failures;}}
