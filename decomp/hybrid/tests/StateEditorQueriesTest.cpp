#include "AutoTest.h"
#include "Detour.h"
#include "PathController.h"
#include "RoomPiece.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include <limits>

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(float, old5939d0, (CPathController*, const Ogre::Vector3&), "_ZN15CPathController19getClosestPctOfPathERKN4Ogre7Vector3E")
extern "C" float new5939d0(CPathController*, const Ogre::Vector3&) __asm__("_ZN15CPathController19getClosestPctOfPathERKN4Ogre7Vector3E");
TL_ORIGINAL(TArrayList<float>*, old9fa300, (CRoomPiece*, ESNAP_TYPES), "_ZN10CRoomPiece13getSnapValuesE11ESNAP_TYPES")
extern "C" TArrayList<float>* new9fa300(CRoomPiece*, ESNAP_TYPES) __asm__("_ZN10CRoomPiece13getSnapValuesE11ESNAP_TYPES");
TL_ORIGINAL(CLevelTemplateData*, old933fe0, (CDungeon*), "_ZN8CDungeon26getRandomLevelTemplateDataEv")
extern "C" CLevelTemplateData* new933fe0(CDungeon*) __asm__("_ZN8CDungeon26getRandomLevelTemplateDataEv");
TL_ORIGINAL(void,pathCtor,(void*,CResourceManager*),"_ZN15CPathControllerC1EP16CResourceManager")
TL_ORIGINAL(void,roomCtor,(void*,CResourceManager*),"_ZN10CRoomPieceC1EP16CResourceManager")
TL_FUNCTION(randomGet,"_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(strataGet,"_ZN8CDungeon17getStrataTemplateEj")
namespace {
autotest::Capture* capture;unsigned seed;CDungeon* dungeon;CLevelTemplateData* strataSentinel;
int randomValue(CRandomizer* p){bool valid=p==&dungeon->m_randomizer;capture->add(&valid,1);if(!valid)capture->issue=autotest::Capture::InvalidReport;const int choices[]={-1,0,1,3,7,0x7fffffff};return choices[seed%6];}
CLevelTemplateData* getStrata(CDungeon* p,unsigned index){bool valid=p==dungeon;capture->add(&valid,1);capture->add(&index,4);if(!valid)capture->issue=autotest::Capture::InvalidReport;return seed%2?strataSentinel:NULL;}
void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);capture=&out;seed=c.index;
    if(c.op==0) {
        CPathController* object=static_cast<CPathController*>(autotest::allocate(sizeof(CPathController)));pathCtor(object,NULL);
        const float special[]={0,-0.0f,1,-1,3.5f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
        object->m_pathCoordinates.clear();object->m_pathDistances.clear();
        unsigned size=c.index%6==0?0:c.index%6==1?1:(c.index%6-1)*3;
        for(unsigned i=0;i<size;++i)object->m_pathCoordinates.add(float(int(c.index)-32)+float(i)*0.125f);
        for(unsigned i=0;i<5;++i)object->m_pathDistances.add(float(i*3+7));
        object->m_bWalkToPlayer=c.index%5==0;object->m_fUnknown180=special[c.index/5%7];
        Ogre::Vector3 point(special[c.index%7],special[(c.index+1)%7],special[(c.index+2)%7]);
        typedef float(*Fn)(CPathController*,const Ogre::Vector3&);Fn fn=ours?new5939d0:old5939d0;
        unsigned char before[sizeof(CPathController)];std::memcpy(before,object,sizeof(before));
        if(!autotest::beginInvocation(out,fn))return;float value=fn(object,point);out.callCompleted=1;out.add(&value,4);
        bool unchanged=std::memcmp(before,object,sizeof(before))==0;out.add(&unchanged,1);if(!unchanged)out.issue=autotest::Capture::InvalidReport;
    } else if(c.op==1) {
        CRoomPiece* object=static_cast<CRoomPiece*>(autotest::allocate(sizeof(CRoomPiece)));
        roomCtor(object,NULL);
        // Original constructor inlines its initial data allocation; it never
        // calls clearCollisionData. Verify the real initial wrapper instead.
        bool initialized=object->m_pRoomPieceData!=NULL && object->m_pRoomPieceData->m_coreData==NULL && object->m_iVisualIndex_140==-1;
        out.add(&initialized,1);if(!initialized){out.issue=autotest::Capture::InvalidReport;return;}
        CRoomPieceData wrapper;CRoomPieceDataInformation::CRoomPieceCoreData core;
        for(unsigned i=0;i<3;++i){core.m_snapRotation.add(float(i+1));core.m_snapPosition.add(float(i+10));core.m_snapScale.add(float(i+20));}
        wrapper.m_coreData=c.index%3==1?NULL:&core;object->m_pRoomPieceData=c.index%3==0?NULL:&wrapper;
        typedef TArrayList<float>*(*Fn)(CRoomPiece*,ESNAP_TYPES);Fn fn=ours?new9fa300:old9fa300;
        if(!autotest::beginInvocation(out,fn))return;TArrayList<float>* result=fn(object,static_cast<ESNAP_TYPES>(int(c.index/3%7)-2));out.callCompleted=1;
        int identity=!result?0:result==&core.m_snapRotation?1:result==&core.m_snapPosition?2:result==&core.m_snapScale?3:99;out.add(&identity,4);
        if(identity==99)out.issue=autotest::Capture::InvalidReport;
        if(result){unsigned n=result->size();out.add(&n,4);for(unsigned i=0;i<n;++i)out.add(&(*result)[i],4);}
        object->m_pRoomPieceData=NULL;
    } else {
        CDungeon object;dungeon=&object;
        // A bounded typed opaque result: neither side dereferences this pointer.
        // Its real class size avoids undersized fabricated receiver storage;
        // constructing a template would load external dungeon files.
        strataSentinel=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));
        if(!strataSentinel){out.issue=autotest::Capture::InvalidReport;return;}
        for(unsigned i=0;i<c.index/6%5;++i)object.m_levelTemplateData.add(NULL);
        detour::Set patches;TL_REDIRECT(patches,randomGet,&randomValue);TL_REDIRECT(patches,strataGet,&getStrata);
        if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        typedef CLevelTemplateData*(*Fn)(CDungeon*);Fn fn=ours?new933fe0:old933fe0;
        if(!autotest::beginInvocation(out,fn))return;CLevelTemplateData* result=fn(&object);out.callCompleted=1;
        unsigned identity=result==NULL?0:result==strataSentinel?1:99;
        unsigned expected=seed%2?1:0;
        out.add(&identity,4);if(identity!=expected)out.issue=autotest::Capture::InvalidReport;
    }
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_query_5939d0) {return runCases(host,0,84,"state_query_5939d0",(uint64_t)(uintptr_t)old5939d0,original,candidate);}
TL_TEST(state_query_9fa300) {return runCases(host,1,84,"state_query_9fa300",(uint64_t)(uintptr_t)old9fa300,original,candidate);}
TL_TEST(state_query_933fe0) {return runCases(host,2,84,"state_query_933fe0",(uint64_t)(uintptr_t)old933fe0,original,candidate);}
