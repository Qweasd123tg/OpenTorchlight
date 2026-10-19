#include <cstring>
#include "AutoTest.h"
#define private public
#define protected public
#include "Character.h"
#include "CullingBounds.h"
#include "ResourceManager.h"
#include "Path.h"
#undef private
#undef protected
#include "tests/NativeGameServices.h"
TL_ORIGINAL(void,ctorOriginal,(CCharacter*,CResourceManager*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,ctorNativeDtor,(CCharacter*),"_ZN10CCharacterD1Ev")
extern "C" void ctorRecovered(CCharacter*,CResourceManager*) __asm__("_ZN10CCharacterC1EP16CResourceManager");
namespace {
struct Case{unsigned seed,control;};CResourceManager*resource;const tlhybrid_host*logger;
void initEmptyGlobals(){
 const uintptr_t a[]={0x14286f0,0x1428720,0x1429ea0,0x1476060,0x14781e0,0x1479460,0x147c340,0x147e8e0,0x147fac0,0x1480a40,0x1482e00,0x1484120,0x14872e0,0x148e500,0x148f960,0x14afec0,0x14b3300,0x14b5868,0x14b58e8,0x14e68b0,0x14ee340,0x14f2668,0x1500740,0x1500820,0x15019a0,0x150b428,0x150c8a0,0x150c980};
 for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i){void*p;std::memcpy(&p,(void*)a[i],sizeof(p));if(!p)new((void*)a[i])std::string;}
 const uintptr_t b[]={0x14286f8,0x1428728,0x1429ea8,0x1476068,0x14781e8,0x1479468,0x147c348,0x147e8e8,0x147fac8,0x1480a48,0x1482e08,0x1484128,0x14872e8,0x148e508,0x148f968,0x14afec8,0x14b3308,0x14b5870,0x14b58f0,0x14e68b8,0x14ee348,0x14f2670,0x1500748,0x1500828,0x15019a8,0x150b430,0x150c8a8,0x150c988};
 for(unsigned i=0;i<sizeof(b)/sizeof(b[0]);++i){void*p;std::memcpy(&p,(void*)b[i],sizeof(p));if(!p)new((void*)b[i])std::wstring;}
}

void pointer(unsigned char*bytes,CCharacter*p,void*member){size_t at=static_cast<unsigned char*>(member)-reinterpret_cast<unsigned char*>(p);std::memset(bytes+at,0,sizeof(void*));}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);CCharacter*p=static_cast<CCharacter*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCharacter),0,0,0));std::memset(p,int(c.seed*37+11)&255,sizeof(CCharacter));int before=g_iTotalCountOfObjects;typedef void(*F)(CCharacter*,CResourceManager*);F fn=ours?ctorRecovered:ctorOriginal;autotest::invoke(out,fn,p,c.seed%2?resource:NULL);int delta=g_iTotalCountOfObjects-before;out.add(&delta,sizeof(delta));if(ours&&c.control)p->m_maxHPBase^=1;
 unsigned char bytes[sizeof(CCharacter)];std::memcpy(bytes,p,sizeof(bytes));std::memset(bytes,0,sizeof(void*));ptrdiff_t missile=reinterpret_cast<char*>(static_cast<iMissile*>(p))-reinterpret_cast<char*>(p),inventory=reinterpret_cast<char*>(static_cast<iInventoryListener*>(p))-reinterpret_cast<char*>(p);out.add(&missile,sizeof(missile));out.add(&inventory,sizeof(inventory));std::memset(bytes+missile,0,sizeof(void*));std::memset(bytes+inventory,0,sizeof(void*));pointer(bytes,p,&p->m_pCullingBounds);pointer(bytes,p,&p->m_movementPath);pointer(bytes,p,&p->m_equipmentParticles.m_pData);out.add(bytes,sizeof(bytes));unsigned valid=p->m_pCullingBounds!=NULL&&p->m_movementPath!=NULL&&p->m_equipmentParticles.size()==12&&p->m_equipmentParticles.m_nCapacity==12&&p->m_equipmentParticles.m_nGrowBy==12;out.add(&valid,sizeof(valid));if(!valid)out.issue=autotest::Capture::InvalidReport;
 if(p->m_pCullingBounds){out.add(&p->m_pCullingBounds->m_vMinimum,sizeof(Ogre::Vector3)*6);}
 if(p->m_movementPath){CPath&q=*p->m_movementPath;out.add(q.m_sObjectName.data(),q.m_sObjectName.size());out.add(&q.m_fPathLength,sizeof(float));out.add(&q.m_vOrigin,sizeof(Ogre::Vector3));unsigned sizes[]={q.m_lPoints.size(),q.m_lRadiusLeft.size(),q.m_lRadiusRight.size(),q.m_lSegmentAngle.size(),q.m_lPointDistance.size()};out.add(sizes,sizeof(sizes));out.add(&q.m_bClosedPath,sizeof(bool));out.add(q.m_sName.data(),q.m_sName.size());}
 TSafePointer<CCharacter>weak;weak.setObject(p);ctorNativeDtor(p);unsigned invalid=weak.getObject()==NULL;out.add(&invalid,sizeof(invalid));if(!invalid)out.issue=autotest::Capture::InvalidReport;Ogre::NedAllocImpl::deallocBytes(p);delta=g_iTotalCountOfObjects-before;out.add(&delta,sizeof(delta));}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_constructor_native){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;CResourceManager resources(NULL);resources.m_pSceneManager=native.scene;resource=&resources;int failures=0;autotest::Coverage coverage("character_constructor_native",(uintptr_t)&ctorOriginal);for(unsigned i=0;i<64;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    constructor seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    constructor negative detected%u\n",unsigned(caught));return failures;}
