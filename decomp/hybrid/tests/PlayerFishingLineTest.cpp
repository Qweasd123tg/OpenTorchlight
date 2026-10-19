#include <string>
#include <vector>
#include <map>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "GenericModel.h"
#include "Item.h"
#include "Path.h"
#include "DynamicLine.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerFishingLine,(CPlayer*,float),"_ZN7CPlayer17updateFishingLineEf")
extern "C" void newPlayerFishingLine(CPlayer*,float) __asm__("_ZN7CPlayer17updateFishingLineEf");
TL_FUNCTION(pfl_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(pfl_setPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(pfl_lineUpdate,"_ZN12CDynamicLine6updateEv")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CGenericModel*model,*fish;CItem*target;Ogre::SkeletonInstance*skeleton;Ogre::Bone*bones[4];Ogre::SceneNode*node;CDynamicLine*line;unsigned positionCalls;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float f){active->out->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&s){num(s.size());active->out->add(s.data(),s.size());}float scalar(unsigned n){return float(int(hash(n)%129)-64)*.125f;}
Ogre::Bone*bone(Ogre::SkeletonInstance*p,const std::string&name){num(1);num(p==active->skeleton);text(name);const char*names[]={"tag_zfishpoleend","tag_zfishcenter","tag_zfishlure","tag_zfishlureend"};for(unsigned i=0;i<4;++i)if(name==names[i])return active->bones[i];std::abort();return NULL;}
const Ogre::Vector3&derived(Ogre::Bone*p){num(2);unsigned i=0;while(i<4&&p!=active->bones[i])++i;num(i);return p->mDerivedPosition;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){num(3);num(p==active->self?1:p==active->model?2:p==active->target?3:99);num(absolute);++active->positionCalls;return p->m_vPosition;}
const Ogre::Matrix4&orientation(CPlayer*p){num(4);num(p==active->self);return p->m_mOrientation;}const Ogre::Vector3&forward(CPlayer*p){num(5);num(p==active->self);return p->m_vForward;}
void lineUpdate(CDynamicLine*p){num(6);num(p==active->line);num(p->m_points.size());for(unsigned i=0;i<p->m_points.size();++i)vec(p->m_points[i]);num(p->m_dirty);p->m_dirty=false;}
void need(Ogre::SceneNode*p,bool force){num(7);num(p==active->node);num(force);}void visible(CGenericModel*p,bool flag){num(8);num(p==active->fish);num(flag);p->m_bVisible=flag;}void setPosition(CPositionableObject*p,const Ogre::Vector3&v){num(9);num(p==active->fish);vec(v);p->m_vPosition=v;}void setOrientation(CGenericModel*p,Ogre::Vector3&a,Ogre::Vector3&b){num(10);num(p==active->fish);vec(a);vec(b);p->m_vForward=a;p->m_vUp=b;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.model=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));s.fish=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));s.target=static_cast<CItem*>(autotest::allocate(sizeof(CItem)));new(s.target)CRunicCore;s.skeleton=static_cast<Ogre::SkeletonInstance*>(autotest::allocate(sizeof(Ogre::SkeletonInstance)));s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.line=static_cast<CDynamicLine*>(autotest::allocate(sizeof(CDynamicLine)));new(&s.line->m_points)std::vector<Ogre::Vector3>(16,Ogre::Vector3(17,-3,8));s.line->m_dirty=false;CPath*path=new CPath("line",false,Ogre::Vector3::ZERO);path->AddPoint(Ogre::Vector3(2,1,-3),7,8);CPlayer&p=*s.self;p.m_pUnitModel=s.model;s.model->m_pSkeleton=s.skeleton;p.m_fishingPath=path;p.m_fishingLine=s.line;p.m_fishingLineNode=s.node;p.m_fishingParticle=s.fish;p.m_fishingFlag=hash(1)&1;new(&p.m_targetItem)TSafePointer<CItem>;if(hash(2)%3)p.m_targetItem.setObject(s.target);p.m_vPosition=Ogre::Vector3(scalar(3),scalar(4),scalar(5));s.model->m_vPosition=Ogre::Vector3(scalar(6),scalar(7),scalar(8));s.target->m_vPosition=Ogre::Vector3(scalar(9),scalar(10),scalar(11));p.m_vForward=Ogre::Vector3(scalar(12),scalar(13),scalar(14));s.fish->m_vPosition=Ogre::Vector3(7,8,9);s.fish->m_vForward=Ogre::Vector3(1,2,3);s.fish->m_vUp=Ogre::Vector3(4,5,6);
for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)p.m_mOrientation[i][j]=i==j?1.0f:scalar(20+4*i+j)*(i==3?.001f:.125f);void**pv=static_cast<void**>(autotest::allocate(0x200));pv[0xe8/8]=reinterpret_cast<void*>(&orientation);pv[0x130/8]=reinterpret_cast<void*>(&forward);*reinterpret_cast<void***>(&p)=pv;void**fv=static_cast<void**>(autotest::allocate(0x140));fv[0x50/8]=reinterpret_cast<void*>(&visible);fv[0x128/8]=reinterpret_cast<void*>(&setOrientation);*reinterpret_cast<void***>(s.fish)=fv;void**sv=static_cast<void**>(autotest::allocate(0x220));sv[0x1b0/8]=reinterpret_cast<void*>(&bone);*reinterpret_cast<void***>(s.skeleton)=sv;void**bv=static_cast<void**>(autotest::allocate(0x210));bv[0x200/8]=reinterpret_cast<void*>(&derived);for(unsigned i=0;i<4;++i){s.bones[i]=static_cast<Ogre::Bone*>(autotest::allocate(sizeof(Ogre::Bone)));s.bones[i]->mDerivedPosition=Ogre::Vector3(scalar(40+3*i)+i*3,scalar(41+3*i),scalar(42+3*i));*reinterpret_cast<void***>(s.bones[i])=bv;}void**nv=static_cast<void**>(autotest::allocate(0x260));nv[0x258/8]=reinterpret_cast<void*>(&need);*reinterpret_cast<void***>(s.node)=nv;typedef void(*F)(CPlayer*,float);F f=ours?newPlayerFishingLine:oldPlayerFishingLine;if(!autotest::beginInvocation(out,f))return;f(&p,scalar(60));out.callCompleted=1;num(path->m_lPoints.size());for(unsigned i=0;i<path->m_lPoints.size();++i){vec(path->m_lPoints[i]);fp(path->m_lRadiusLeft[i]);fp(path->m_lRadiusRight[i]);}fp(path->m_fPathLength);vec(s.fish->m_vPosition);vec(s.fish->m_vForward);vec(s.fish->m_vUp);num(s.fish->m_bVisible);num(s.positionCalls);p.m_targetItem.~TSafePointer();s.target->CRunicCore::~CRunicCore();delete path;s.line->m_points.~vector();}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_fishing_line){detour::Set h;TL_REDIRECT(h,pfl_position,&position);TL_REDIRECT(h,pfl_setPosition,&setPosition);TL_REDIRECT(h,pfl_lineUpdate,&lineUpdate);if(h.failed())return 1;autotest::Coverage coverage("all_player_fishing_line",0x8efbc0);for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player line seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
