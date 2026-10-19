#include <string>
#include <map>
#include <vector>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "ResourceManager.h"
#include "DynamicLine.h"
#include "Path.h"
#include "GenericModel.h"
#include "QuestManager.h"
#include "DungeonTracker.h"
#include "LevelState.h"
#include "Particle.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerDestroy,(CPlayer*),"_ZN7CPlayerD1Ev")
extern "C" void newPlayerDestroy(CPlayer*) __asm__("_ZN7CPlayerD1Ev");
TL_FUNCTION(pdt_base1,"_ZN10CCharacterD1Ev")
TL_FUNCTION(pdt_base2,"_ZN10CCharacterD2Ev")
TL_FUNCTION(pdt_remove,"_ZN14OGRE_UTILITIES25removeChildFromParentNodeEPN4Ogre9SceneNodeE")
TL_FUNCTION(pdt_quest,"_ZN13CQuestManager9setPlayerEP7CPlayer")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;Ogre::SceneNode*lineNode,*poleNode,*parent;Ogre::SceneManager*scene;void*objects[9];unsigned deletes[9];};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}unsigned id(void*p){if(!p)return 0;for(unsigned i=0;i<9;++i)if(active->objects[i]==p)return i+1;return 99;}
void base(CCharacter*p){num(1);num(p==active->self);num(active->self->m_savedLevels.size());num(active->self->m_dungeonTrackers.m_nCount);num(active->self->m_loadedModNames.m_nCount);num(active->self->m_questManager==NULL);num(active->self->m_levelUpParticle==NULL);num(active->self->m_fishingPole==NULL);num(active->self->m_fishingParticle==NULL);num(active->self->m_fishingPath==NULL);num(active->self->m_fishingLine==NULL);num(active->self->m_fishingLineNode==NULL);}
Ogre::Node*nodeParent(Ogre::SceneNode*p){return p->mParent;}void detachParent(Ogre::SceneNode*p){num(2);num(p==active->lineNode);}void quest(CQuestManager*,CPlayer*p){num(3);num(p==NULL);}
void detach(Ogre::SceneNode*p,Ogre::MovableObject*o){num(4);num(p==active->lineNode);num(id(o));}void children(Ogre::SceneNode*p){num(5);num(p==active->lineNode);}void destroy(Ogre::SceneManager*p,Ogre::SceneNode*n){num(6);num(p==active->scene);num(n==active->lineNode);}Ogre::Node*removeChild(Ogre::SceneNode*p,Ogre::Node*n){num(7);num(p==active->parent);num(n==active->poleNode);return n;}
void visible(CGenericModel*p,bool flag){num(8);num(id(p));num(flag);}
void ownedDestroy(CRunicCore*p){unsigned i=id(p);num(9);num(i);if(i<1||i>9)std::abort();++active->deletes[i-1];p->CRunicCore::~CRunicCore();Ogre::NedAllocImpl::deallocBytes(p);}
void lineDestroy(CDynamicLine*p){unsigned i=id(p);num(10);num(i);if(i!=1)std::abort();++active->deletes[0];Ogre::NedAllocImpl::deallocBytes(p);}
class Saved:public CLevelState{public:Saved(int i):CLevelState(i){}virtual~Saved(){unsigned i=id(this);num(11);num(i);++active->deletes[i-1];}};
template<class T>T*owned(unsigned i){T*p=static_cast<T*>(Ogre::NedAllocImpl::allocBytes(sizeof(T),0,0,0));std::memset(p,0,sizeof(T));new(p)CRunicCore;active->objects[i]=p;void**v=static_cast<void**>(autotest::allocate(0x100));v[1]=reinterpret_cast<void*>(&ownedDestroy);v[0x50/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(p)=v;return p;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;void*empty=NULL;std::memcpy(&empty,reinterpret_cast<void*>(0x14949c8),8);if(!empty)new(reinterpret_cast<void*>(0x14949c8))std::wstring;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));CPlayer&p=*s.self;CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.scene=static_cast<Ogre::SceneManager*>(autotest::allocate(sizeof(Ogre::SceneManager)));s.lineNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.parent=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.poleNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));r->m_pSceneManager=s.scene;p.m_pResourceManager=r;
void**sm=static_cast<void**>(autotest::allocate(0x400));sm[0x248/8]=reinterpret_cast<void*>(&destroy);*reinterpret_cast<void***>(s.scene)=sm;void**nt=static_cast<void**>(autotest::allocate(0x400));nt[0xc0/8]=reinterpret_cast<void*>(&nodeParent);nt[0x2a0/8]=reinterpret_cast<void*>(&detach);nt[0x1f0/8]=reinterpret_cast<void*>(&children);nt[0x1e0/8]=reinterpret_cast<void*>(&removeChild);*reinterpret_cast<void***>(s.lineNode)=nt;*reinterpret_cast<void***>(s.parent)=nt;*reinterpret_cast<void***>(s.poleNode)=nt;s.poleNode->mParent=hash(1)&1?s.parent:NULL;
new(&p.m_savedLevels)std::vector<CLevelState*>;new(&p.m_portalDungeon)std::wstring(L"portal");new(&p.m_returnDungeon)std::wstring(L"return");new(&p.m_manaGraph)std::wstring(L"mana");new(&p.m_hpGraph)std::wstring(L"hp");new(&p.m_statPointsGraph)std::wstring(L"stat");new(&p.m_skillPointsGraph)std::wstring(L"skill");new(&p.m_famePointsGraph)std::wstring(L"fame");new(&p.m_dungeonTrackers)TArrayList<CDungeonTracker*>(5);new(&p.m_loadedModNames)TArrayList<std::wstring>(10);for(unsigned i=0;i<hash(2)%9;++i){CDungeonTracker*t=new CDungeonTracker;t->m_name=i%2?L"dungeon":L"";t->m_levels.push_back(i);p.m_dungeonTrackers.add(i%3?t:NULL);if(i%3==0)delete t;}for(unsigned i=0;i<hash(3)%13;++i)p.m_loadedModNames.add(i%2?L"mod":L"мод");
if(hash(4)&1){p.m_fishingLine=static_cast<CDynamicLine*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDynamicLine),0,0,0));s.objects[0]=p.m_fishingLine;void**v=static_cast<void**>(autotest::allocate(0x10));v[1]=reinterpret_cast<void*>(&lineDestroy);*reinterpret_cast<void***>(p.m_fishingLine)=v;}p.m_fishingLineNode=hash(5)&1?s.lineNode:NULL;p.m_questManager=hash(6)&1?static_cast<CQuestManager*>(autotest::allocate(sizeof(CQuestManager))):NULL;
if(hash(7)&1){p.m_fishingPole=owned<CGenericModel>(1);p.m_fishingPole->m_pSceneNode=s.poleNode;}if(hash(8)&1)p.m_fishingParticle=owned<CGenericModel>(2);if(hash(9)&1)p.m_levelUpParticle=owned<CParticle>(3);if(hash(10)&1){p.m_fishingPath=new CPath("fishing",false,Ogre::Vector3::ZERO);s.objects[4]=p.m_fishingPath;}for(unsigned i=0;i<hash(11)%4;++i){Saved*v=new Saved(i);s.objects[5+i]=v;p.m_savedLevels.push_back(v);p.m_savedLevels.push_back(NULL);}
TSafePointer<CRunicCore> weak[4];for(unsigned i=0;i<4;++i)if(s.objects[i+1])weak[i].setObject(static_cast<CRunicCore*>(s.objects[i+1]));typedef void(*F)(CPlayer*);F f=ours?newPlayerDestroy:oldPlayerDestroy;if(!autotest::beginInvocation(out,f))return;f(s.self);out.callCompleted=1;for(unsigned i=0;i<9;++i)num(s.deletes[i]);for(unsigned i=0;i<4;++i)num(weak[i].getObject()==NULL);
}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_destroy){detour::Set h;TL_REDIRECT(h,pdt_base1,&base);TL_REDIRECT(h,pdt_base2,&base);TL_REDIRECT(h,pdt_remove,&detachParent);TL_REDIRECT(h,pdt_quest,&quest);if(h.failed())return 1;autotest::Coverage coverage("all_player_destroy",0x8fb700);for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player destroy seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
