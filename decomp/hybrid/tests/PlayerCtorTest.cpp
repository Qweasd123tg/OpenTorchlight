#include <string>
#include <map>
#include <vector>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "ResourceManager.h"
#include "FileSystem.h"
#include "DynamicLine.h"
#include "Path.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerCtor,(CPlayer*,CResourceManager*),"_ZN7CPlayerC1EP16CResourceManager")
extern "C" void newPlayerCtor(CPlayer*,CResourceManager*) __asm__("_ZN7CPlayerC1EP16CResourceManager");
TL_FUNCTION(pct_line,"_ZN12CDynamicLineC1EN4Ogre15RenderOperation13OperationTypeE")
TL_FUNCTION(pct_point,"_ZN12CDynamicLine8addPointEfff")
TL_FUNCTION(pct_align,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(pct_unique,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(pct_files,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(pct_mods,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
namespace {
struct Case{unsigned index;}; struct State{Case c;autotest::Capture*out;CPlayer*self;Ogre::SceneManager*scene;Ogre::SceneNode*root,*base,*lineNode;CDynamicLine*line;};State*active;
void num(unsigned n){active->out->add(&n,4);}void fp(float n){active->out->add(&n,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&s){num(s.size());active->out->add(s.data(),s.size());}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*sizeof(wchar_t));}
Ogre::SceneNode*create(Ogre::SceneManager*p){num(1);num(p==active->scene);return active->base;}Ogre::SceneNode*root(Ogre::SceneManager*p){num(2);num(p==active->scene);return active->root;}
Ogre::SceneNode*child(Ogre::SceneNode*p,const std::string&name,const Ogre::Vector3&v,const Ogre::Quaternion&q){num(3);num(p==active->root);text(name);vec(v);fp(q.w);fp(q.x);fp(q.y);fp(q.z);return active->lineNode;}
void attach(Ogre::SceneNode*p,Ogre::MovableObject*o){num(4);num(p==active->lineNode);num(o==active->line);}void visible(Ogre::SceneNode*p,bool v,bool children){num(5);num(p==active->lineNode);num(v);num(children);}
void line(CDynamicLine*p,Ogre::RenderOperation::OperationType op){num(6);num(op);active->line=p;new(&p->m_points)std::vector<Ogre::Vector3>;p->m_dirty=false;}
void point(CDynamicLine*p,float x,float y,float z){num(7);num(p==active->line);fp(x);fp(y);fp(z);p->m_points.push_back(Ogre::Vector3(x,y,z));p->m_dirty=true;}
void align(CCharacter*p,EAlignment a){num(8);num(p==active->self);num(a);p->m_alignment=a;}
std::string unique(const std::string&s){num(9);text(s);return s+"17";}CFileSystem*files(){num(10);return reinterpret_cast<CFileSystem*>(0x11223300);}
void mods(CFileSystem*p,TArrayList<std::wstring>*l){num(11);num(p==reinterpret_cast<CFileSystem*>(0x11223300));num(l->m_nGrowBy);for(unsigned i=0;i<active->c.index%13;++i)l->add(i%2?L"mod alpha":L"модификация");}
void initText(){const unsigned addresses[]={0x147c340,0x148a300};for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(addresses[i]);std::memcpy(&p,a,8);if(!p)new(a)std::string;}const unsigned wides[]={0x147c348,0x148a308};for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(wides[i]);std::memcpy(&p,a,8);if(!p)new(a)std::wstring;}}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;initText();s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));std::memset(s.self,(c.index*37+17)&255,sizeof(CPlayer));CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.scene=static_cast<Ogre::SceneManager*>(autotest::allocate(sizeof(Ogre::SceneManager)));s.root=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.base=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.lineNode=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));r->m_pSceneManager=s.scene;
void**sm=static_cast<void**>(autotest::allocate(0x400));sm[0x230/8]=reinterpret_cast<void*>(&create);sm[0x250/8]=reinterpret_cast<void*>(&root);*reinterpret_cast<void***>(s.scene)=sm;void**nt=static_cast<void**>(autotest::allocate(0x400));nt[0x328/8]=reinterpret_cast<void*>(&child);nt[0x278/8]=reinterpret_cast<void*>(&attach);nt[0x378/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(s.root)=nt;*reinterpret_cast<void***>(s.lineNode)=nt;*reinterpret_cast<void***>(s.base)=nt;
typedef void(*F)(CPlayer*,CResourceManager*);F f=ours?newPlayerCtor:oldPlayerCtor;if(!autotest::beginInvocation(out,f))return;f(s.self,r);out.callCompleted=1;CPlayer&p=*s.self;num(p.m_levelUpParticle==NULL);num(p.m_godMode);num(p.m_cheatMarker);num(p.m_savedLevels.size());num(p.m_savedLevels.capacity());num(p.m_hasPortal);num(p.m_portalDepth);wide(p.m_portalDungeon);vec(p.m_portalPosition);num(p.m_returnDepth);wide(p.m_returnDungeon);num(p.m_levelSaveSerial);for(unsigned i=0;i<18;++i)num(p.m_journalPrefix[i]);out.add(p.m_Padding824,4);num(p.m_fishingPole==NULL);num(p.m_fishingParticle==NULL);num(p.m_fishingPath!=NULL);num(p.m_fishingLine==s.line);num(p.m_fishingLineNode==s.lineNode);fp(p.m_fishingTime);fp(p.m_fishingValue854);fp(p.m_fishingDelay);num(p.m_fishingFlag);out.add(p.m_Padding85D,3);fp(p.m_fishingValue860);out.add(p.m_Padding864,4);num(p.m_questManager==NULL);out.add(p.m_Padding870,20);fp(p.m_deathDelay);wide(p.m_manaGraph);wide(p.m_hpGraph);wide(p.m_statPointsGraph);wide(p.m_skillPointsGraph);wide(p.m_famePointsGraph);out.add(p.m_itemLinks,sizeof p.m_itemLinks);out.add(p.m_skillMap,sizeof p.m_skillMap);out.add(p.m_leftSkillMap,sizeof p.m_leftSkillMap);out.add(p.m_functionSkills,sizeof p.m_functionSkills);out.add(p.m_leftFunctionSkills,sizeof p.m_leftFunctionSkills);out.add(p.m_PaddingA10,4);num(p.m_playerTranslucent);num(p.m_saveOnDeath);num(p.m_followersEnabled);out.add(p.m_PaddingA17,41);num(p.m_dungeonTrackers.m_nCount);num(p.m_dungeonTrackers.m_nCapacity);num(p.m_dungeonTrackers.m_nGrowBy);num(p.m_loadedModNames.m_nCount);num(p.m_loadedModNames.m_nCapacity);num(p.m_loadedModNames.m_nGrowBy);for(unsigned i=0;i<p.m_loadedModNames.m_nCount;++i)wide(p.m_loadedModNames[i]);num(p.m_maxHPBase);fp(p.m_fHPFloat);out.add(&p.m_turnRate288,4);num(p.m_iMeleeStat);num(p.m_rangedStat);num(p.m_magicStat);num(p.m_defenseStat);num(p.m_naturalArmor);num(p.m_alignment);CPath&path=*p.m_fishingPath;text(path.m_sObjectName);text(path.m_sName);fp(path.m_fPathLength);vec(path.m_vOrigin);num(path.m_bClosedPath);num(path.m_lPoints.size());for(unsigned i=0;i<path.m_lPoints.size();++i){vec(path.m_lPoints[i]);fp(path.m_lRadiusLeft[i]);fp(path.m_lRadiusRight[i]);}num(p.m_fishingLine->m_points.size());for(unsigned i=0;i<p.m_fishingLine->m_points.size();++i)vec(p.m_fishingLine->m_points[i]);num(p.m_fishingLine->m_dirty);
}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_ctor){detour::Set h;TL_REDIRECT(h,pct_line,&line);TL_REDIRECT(h,pct_point,&point);TL_REDIRECT(h,pct_align,&align);TL_REDIRECT(h,pct_unique,&unique);TL_REDIRECT(h,pct_files,&files);TL_REDIRECT(h,pct_mods,&mods);if(h.failed())return 1;autotest::Coverage coverage("all_player_ctor",0x8f3450);for(unsigned i=0;i<256;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player ctor seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k]){host->log("    first byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=256||coverage.different||coverage.missing;}
