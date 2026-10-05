#include <cstring>
#include <new>
#include <Ogre.h>
#include <map>
#define protected public
#define private public
#include "Equipment.h"
#include "GenericModel.h"
#include "Particle.h"
#include "ParticlePreloader.h"
#include "MasterResourceManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentParticles,(CEquipment*),"_ZN10CEquipment15createParticlesEv")
TL_FUNCTION(ptIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ptQuest,"_ZN9CBaseUnit14getIsQuestUnitEv")
TL_FUNCTION(ptDamage,"_ZN10CEquipment14getDamageBonusE13EDAMAGE_TYPES")
TL_FUNCTION(ptMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(ptLoad,"_ZN18CParticlePreloader12LoadParticleESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ptCreate,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(ptParent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(ptPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(ptStart,"_ZN9CParticle5StartEv")
extern "C" void* particleEquipmentTable[] __asm__("_ZTV10CEquipment");
namespace {
typedef char particle_name_offset[__builtin_offsetof(CParticle,m_pUnknown110)==0x110?1:-1];
typedef char particle_name_storage[sizeof(std::wstring)==sizeof(void*)?1:-1];
typedef char preloader_offset[__builtin_offsetof(CMasterResourceManager,m_pParticlePreloader)==0xf8?1:-1];
typedef char preloader_size[sizeof(CParticlePreloader)==0xc8?1:-1];
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T* get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned id,classification,damage,state,attachment,custom,failure,mode;};struct World;
World* world;const Case* input;autotest::Capture* capture;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void vector(const Ogre::Vector3& v){real(v.x);real(v.y);real(v.z);}void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
std::wstring& name(CParticle* p){return *reinterpret_cast<std::wstring*>(&p->m_pUnknown110);}
struct World{
 Raw<CEquipment> item;Raw<CGenericModel> model;Raw<CParticle> particles[8];Raw<CMasterResourceManager> master;Raw<CResourceManager> resources;unsigned long long preloader[4];
 void* itemTable[110];void* particleTable[2];Ogre::SceneNode modelNode;Ogre::SceneNode* nodes[8];unsigned creates,starts,destroys;bool dead[8];
 World():modelNode(NULL),creates(0),starts(0),destroys(0){std::memcpy(itemTable,particleEquipmentTable+2,sizeof(itemTable));void** t=itemTable;std::memcpy(item.get(),&t,sizeof(t));new(&item.get()->m_sUnknown3D8)std::wstring();std::memset(dead,0,sizeof(dead));for(unsigned i=0;i<8;++i){nodes[i]=new Ogre::SceneNode(NULL);particles[i].get()->m_pSceneNode=nodes[i];new(&name(particles[i].get()))std::wstring();}model.get()->m_pSceneNode=&modelNode;master.get()->m_pParticlePreloader=reinterpret_cast<CParticlePreloader*>(preloader);}
 ~World(){typedef std::wstring Text;for(unsigned i=0;i<8;++i){name(particles[i].get()).~Text();delete nodes[i];}item.get()->m_sUnknown3D8.~Text();}
 int id(const CParticle* p){if(!p)return -1;for(unsigned i=0;i<8;++i)if(p==particles[i].get())return i;return -2;}
};
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){number(10);number(p==world->item.get());number(type);return type==UNITTYPES::UNIQUE?(input->classification&2)!=0:type==UNITTYPES::WEAPON?(input->classification&8)!=0:type==UNITTYPES::PISTOL?(input->classification&16)!=0:false;}
bool quest(CBaseUnit* p){number(11);number(p==world->item.get());return (input->classification&1)!=0;}
bool magical(CEquipment* p){number(12);number(p==world->item.get());return (input->classification&4)!=0;}
int damage(CEquipment* p,EDAMAGE_TYPES type){number(13);number(p==world->item.get());number(type);static const int values[13][4]={{0,0,0,0},{2,0,0,0},{0,3,0,0},{0,0,4,0},{0,0,0,5},{7,7,7,7},{0,8,8,0},{0,0,9,9},{-1,-2,-3,-4},{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};unsigned i=type==DAMAGE_ELECTRIC?0:type==DAMAGE_FIRE?1:type==DAMAGE_ICE?2:type==DAMAGE_POISON?3:4;return i<4?values[input->damage][i]:9999;}
CMasterResourceManager* master(){number(14);if(input->mode==2)world->item.get()->m_sUnknown3D8=L"during_singleton";return world->master.get();}
void load(CParticlePreloader* p,std::wstring value){number(15);number(p==reinterpret_cast<CParticlePreloader*>(world->preloader));text(value);}
CParticle* create(CResourceManager* p,const wchar_t* value){number(16);number(p==world->resources.get());text(value);unsigned call=world->creates++;if(input->mode==1){world->item.get()->m_bVisible=!world->item.get()->m_bVisible;world->item.get()->m_pEquippedTo=NULL;world->item.get()->m_pUnitModel=world->model.get();}if((input->failure>>(call%2))&1)return NULL;unsigned id=2+call;if(id>=8)_exit(47);CParticle* result=world->particles[id].get();name(result)=value;return result;}
void destroy(CParticle* p){number(17);int id=world->id(p);number(id);if(id<0||world->dead[id])_exit(48);world->dead[id]=true;++world->destroys;if(world->nodes[id]->getParentSceneNode())world->nodes[id]->getParentSceneNode()->removeChild(world->nodes[id]);if(input->mode==2)world->item.get()->m_pUnitModel=NULL;}
void parent(CSceneNodeObject* p,Ogre::SceneNode* node,bool keep){CParticle* particle=static_cast<CParticle*>(p);int id=world->id(particle);number(18);number(id);number(node==&world->modelNode);number(keep);if(id<0||world->dead[id])_exit(49);Ogre::SceneNode* old=world->nodes[id]->getParentSceneNode();if(old)old->removeChild(world->nodes[id]);if(node)node->addChild(world->nodes[id]);}
void position(CPositionableObject* p,const Ogre::Vector3& v){int id=world->id(static_cast<CParticle*>(p));number(19);number(id);vector(v);p->m_vPosition=v;if(id>=0)world->nodes[id]->setPosition(v);}
void start(CParticle* p){number(20);number(world->id(p));++world->starts;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;World w;world=&w;w.itemTable[86]=reinterpret_cast<void*>(&magical);w.particleTable[0]=w.particleTable[1]=reinterpret_cast<void*>(&destroy);for(unsigned i=0;i<8;++i){void** t=w.particleTable;std::memcpy(w.particles[i].get(),&t,sizeof(t));w.nodes[i]->setPosition(3,4,5);}
 w.item.get()->m_pResourceManager=w.resources.get();w.item.get()->m_sUnknown3D8=c.custom?L"Particles/custom.layout":L"";w.item.get()->m_bVisible=(c.attachment&1)!=0;w.item.get()->m_pEquippedTo=c.attachment&2?reinterpret_cast<CCharacter*>(&w.preloader):NULL;w.item.get()->m_pUnitModel=c.attachment&4?w.model.get():NULL;
 static const wchar_t* active[]={L"",L"weapon_electricity",L"weapon_fire",L"weapon_ice",L"weapon_poison",L"weapon_electricity",L"weapon_fire",L"weapon_ice",L"",L"weapon_electricity",L"weapon_fire",L"weapon_ice",L"weapon_poison"};std::wstring activeName=active[c.damage];if(!activeName.empty()&&(c.classification&16))activeName+=L"_pistol";
 name(w.particles[0].get())=c.state==1?(c.classification&1?L"quest_item":c.classification&2?L"unique_weapon":c.classification&4?L"magic_weapon":L"generic_weapon"):L"other";name(w.particles[1].get())=c.state==1?activeName:L"other";
 w.item.get()->m_pParticle_3D0=c.state?w.particles[0].get():NULL;w.item.get()->m_pParticle=c.state?w.particles[1].get():NULL;
 detour::Set patches;TL_REDIRECT(patches,ptIsa,&isa);TL_REDIRECT(patches,ptQuest,&quest);TL_REDIRECT(patches,ptDamage,&damage);TL_REDIRECT(patches,ptMaster,&master);TL_REDIRECT(patches,ptLoad,&load);TL_REDIRECT(patches,ptCreate,&create);TL_REDIRECT(patches,ptParent,&parent);TL_REDIRECT(patches,ptPosition,&position);TL_REDIRECT(patches,ptStart,&start);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(ours)w.item.get()->createParticles();else originalEquipmentParticles(w.item.get());number(w.id(w.item.get()->m_pParticle_3D0));number(w.id(w.item.get()->m_pParticle));number(w.creates);number(w.starts);number(w.destroys);text(w.item.get()->m_sUnknown3D8);number(w.item.get()->m_bVisible);for(unsigned i=0;i<8;++i){number(w.dead[i]);number(w.nodes[i]->getParentSceneNode()==&w.modelNode);vector(w.nodes[i]->getPosition());}}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_particles_differential){int failures=0;for(unsigned n=0;n<2144;++n){Case c={n,0,0,0,5,0,0,0};if(n<1248){c.classification=n%32;c.damage=(n/32)%13;c.state=n/416;}else if(n<2016){unsigned j=n-1248;static const unsigned types[]={0,8,24,9};c.attachment=j%8;c.custom=(j/8)%2;c.failure=(j/16)%4;c.state=(j/64)%3;c.classification=types[j/192];c.damage=(j/32)%13;}else{unsigned j=n-2016;c.classification=31;c.damage=j%13;c.state=(j/16)%3;c.attachment=j%8;c.custom=(j/8)%2;c.mode=1+j/64;}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    particles case %u status %d/%d lengths %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    equipment particles: 2144 cases, two calls per side\n");return failures;}
