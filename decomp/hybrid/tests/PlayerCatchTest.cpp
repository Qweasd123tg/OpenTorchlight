#include <string>
#include <vector>
#include <map>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "Equipment.h"
#include "Inventory.h"
#include "GameUI.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "GenericModel.h"
#include "StringTranslate.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerCatch,(CPlayer*,float,CLevel&),"_ZN7CPlayer14fishingAICatchEfR6CLevel")
extern "C" void newPlayerCatch(CPlayer*,float,CLevel&) __asm__("_ZN7CPlayer14fishingAICatchEfR6CLevel");
TL_FUNCTION(pca_playing,"_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(pca_translator,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(pca_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(pca_spawn,"_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(pca_units,"_ZN16CResourceManager23createUnitsBySpawnClassEP11CSpawnClassR10TArrayListIP9CBaseUnitEjP10CCharacterS8_ii")
TL_FUNCTION(pca_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(pca_pickup,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(pca_add,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(pca_position,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(pca_ui,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(pca_modal,"_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(pca_stat,"_ZN7CPlayer25incrementJournalStatisticE17EJournalStatistici")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CBaseUnit*objects[5];CResourceManager*resources;CInventory*inventory;CLevel*level;CGameUI*ui;Ogre::SceneNode*right,*left;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float f){active->out->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}unsigned id(CBaseUnit*p){if(!p)return 0;for(unsigned i=0;i<5;++i)if(active->objects[i]==p)return i+1;return 99;}
class Gear:public CEquipment{public:Gear(unsigned i):CEquipment(NULL){m_sItemName=i%2?L"fish Ж":L"equipment";}virtual const std::wstring&getItemName(){num(1);num(id(this));return m_sItemName;}virtual void drop(){num(2);num(id(this));}};
class Other:public CItem{public:Other():CItem(NULL){}virtual void setActiveInLevel(bool){}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}};
bool playing(const CGenericModel*,const std::string&s){num(3);num(s.size());active->out->add(s.data(),s.size());return hash(1)%5==0;}CStringTranslate*translator(){num(4);return reinterpret_cast<CStringTranslate*>(0x11223300);}std::wstring translate(CStringTranslate*,const wchar_t*p){num(5);wide(p);return hash(2)%7?std::wstring(p)+L" переведено":L"";}CSpawnClass*spawn(CResourceManager*p,const std::wstring&s){num(6);num(p==active->resources);wide(s);return reinterpret_cast<CSpawnClass*>(0x11224400);}
void units(CResourceManager*p,CSpawnClass*s,TArrayList<CBaseUnit*>&l,unsigned count,CCharacter*a,CCharacter*b,int level,int flags){num(7);num(p==active->resources);num(s==reinterpret_cast<CSpawnClass*>(0x11224400));num(count);num(a==active->self);num(b==active->self);num(level);num(flags);num(l.m_nGrowBy);for(unsigned i=0;i<hash(3)%7;++i)l.add(i%6==5?NULL:active->objects[i%5]);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(8);num(id(p));num(t);return hash(10+id(p))&1;}CEquipment*pickup(CInventory*p,CEquipment*e,bool b){num(9);num(p==active->inventory);num(id(e));num(b);return hash(20+id(e))%3?e:NULL;}void add(CLevel*p,CItem*i,const Ogre::Vector3&v,bool flag){num(10);num(p==active->level);num(id(i));vec(v);num(flag);}void position(CPositionableObject*p,const Ogre::Vector3&v){num(11);num(id(static_cast<CBaseUnit*>(p)));vec(v);p->m_vPosition=v;}CGameUI*ui(CResourceManager*){num(12);return active->ui;}void modal(CGameUI*p,std::wstring title,std::wstring body,bool b){num(13);num(p==active->ui);wide(title);wide(body);num(b);}void journal(CPlayer*p,EJournalStatistic t,int amount){num(14);num(p==active->self);num(t);num(amount);p->m_journalStats[int(t)]+=amount;}void state(CPlayer*p,EAIState st){num(15);num(st);p->m_eAIState=st;if(hash(4)%3==0)p->m_weaponsHidden=!p->m_weaponsHidden;}void visible(Ogre::SceneNode*p,bool a,bool b){num(16);num(p==active->right?1:p==active->left?2:99);num(a);num(b);}
void init(){const unsigned a[]={0x1480a48,0x1479468};for(unsigned i=0;i<2;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(a[i]),8);if(!p)new(reinterpret_cast<void*>(a[i]))std::wstring;}}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;init();s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.inventory=static_cast<CInventory*>(autotest::allocate(sizeof(CInventory)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.right=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.left=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));for(unsigned i=0;i<4;++i)s.objects[i]=new Gear(i);s.objects[4]=new Other;CLevelTemplateData*t=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));new(&t->m_selectedUnitSpawners[6])std::wstring(hash(5)&1?L"custom fish spawn":L"");s.level->m_pLevelTemplateData=hash(6)%3?t:NULL;CPlayer&p=*s.self;p.m_pResourceManager=s.resources;p.m_pInventory=hash(7)%3?s.inventory:NULL;p.m_pUnitModel=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));p.m_fishingFlag=hash(8)&1;p.m_weaponsHidden=hash(9)&1;p.m_pRightHandNode=hash(30)&1?s.right:NULL;p.m_pLeftHandNode=hash(31)&1?s.left:NULL;p.m_vPosition=Ogre::Vector3(float(int(hash(32)%31)-15),float(int(hash(33)%31)-15),float(int(hash(34)%31)-15));p.m_eAIState=static_cast<EAIState>(7);p.m_journalStats[14]=17;void**v=static_cast<void**>(autotest::allocate(0x360));v[0x348/8]=reinterpret_cast<void*>(&state);*reinterpret_cast<void***>(&p)=v;void**nv=static_cast<void**>(autotest::allocate(0x380));nv[0x378/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(s.right)=nv;*reinterpret_cast<void***>(s.left)=nv;typedef void(*F)(CPlayer*,float,CLevel&);F f=ours?newPlayerCatch:oldPlayerCatch;if(!autotest::beginInvocation(out,f))return;f(&p,.125f,*s.level);f(&p,.25f,*s.level);out.callCompleted=1;num(p.m_eAIState);num(p.m_weaponsHidden);num(p.m_journalStats[14]);for(unsigned i=0;i<5;++i)vec(s.objects[i]->m_vPosition);t->m_selectedUnitSpawners[6].~basic_string();
// Real native Equipment/Item constructors establish RTTI and owned state. Items
// survive the observed fishing operation; the child exits with these live units.
}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_fishing_catch){detour::Set h;TL_REDIRECT(h,pca_playing,&playing);TL_REDIRECT(h,pca_translator,&translator);TL_REDIRECT(h,pca_translate,&translate);TL_REDIRECT(h,pca_spawn,&spawn);TL_REDIRECT(h,pca_units,&units);TL_REDIRECT(h,pca_isa,&isa);TL_REDIRECT(h,pca_pickup,&pickup);TL_REDIRECT(h,pca_add,&add);TL_REDIRECT(h,pca_position,&position);TL_REDIRECT(h,pca_ui,&ui);TL_REDIRECT(h,pca_modal,&modal);TL_REDIRECT(h,pca_stat,&journal);if(h.failed())return 1;autotest::Coverage coverage("all_player_fishing_catch",0x8fa300);for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player catch seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
