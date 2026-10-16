#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <new>
#include <fenv.h>
#include <OgreVector3.h>
#define private public
#include "LevelTemplateData.h"
#undef private
#include "AutoTest.h"

TL_ORIGINAL(void, geometryOwnerConstruct, (void*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, geometryOwnerDestroy, (void*), "_ZN18CLevelTemplateDataD1Ev")
TL_ORIGINAL(bool, originalIntersects, (CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&), "_ZN18CLevelTemplateData16intersectsChunksEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
TL_ORIGINAL(bool, originalExits, (CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&), "_ZN18CLevelTemplateData10exitsMatchEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
extern "C" bool candidateIntersects(CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&) __asm__("_ZN18CLevelTemplateData16intersectsChunksEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE");
extern "C" bool candidateExits(CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&) __asm__("_ZN18CLevelTemplateData10exitsMatchEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE");

namespace {
struct Case { unsigned operation, index; };
float bits(unsigned n) { float x; std::memcpy(&x,&n,4); return x; }
unsigned next(unsigned& seed) { seed=seed*1664525u+1013904223u; return seed; }
float coordinate(unsigned& seed) { return static_cast<float>(static_cast<int>(next(seed)%81)-40)*0.25f; }
void instance(CChunkInstance& x,int type,float a,float b,float c) {
    x.m_chunkTypeIndex=type; x.m_x=a; x.m_y=b; x.m_z=c;
    x.m_name=L"geometry instance"; x.m_usedExits.push_back(7); x.m_usedExits.push_back(-1);
}
void captureInstance(autotest::Capture& out,CChunkInstance& x) {
    out.add(&x.m_chunkTypeIndex,4); out.add(&x.m_x,12);
    unsigned n=x.m_usedExits.size(); out.add(&n,4);
    for(unsigned i=0;i<n;++i)out.add(&x.m_usedExits[i],4);
    n=x.m_name.size(); out.add(&n,4); out.add(x.m_name.data(),n*sizeof(wchar_t));
}
void side(Case& c,bool ours,autotest::Capture& out) {
    // The original constructor starts every real string/list/randomizer lifetime.
    // Its null filename path returns without file access; no opaque bytes are used as objects.
    union Storage { long double align; unsigned char bytes[0x778]; } storage;
    std::memset(storage.bytes,0xa5,sizeof(storage.bytes));
    geometryOwnerConstruct(storage.bytes, NULL);
    CLevelTemplateData* owner=reinterpret_cast<CLevelTemplateData*>(storage.bytes);
    CChunkType* types[3];
    for(unsigned i=0;i<3;++i) {
        types[i]=new CChunkType;
        types[i]->m_entranceChunk=false; types[i]->m_exitChunk=false;
        types[i]->m_registeredWithRandomizers=false; types[i]->m_mustPlace=false;
        types[i]->m_width=4+i; types[i]->m_height=2+i; types[i]->m_maxAppearance=1;
        types[i]->m_folder=L"folder"; types[i]->m_name=L"type";
        types[i]->m_inclusiveFiles.add(L"file"); owner->m_chunkTypes.add(types[i]);
    }
    // GrowBy=10 gives valid spare storage; out-of-capacity indices must select element zero.
    owner->m_tileBasis=1.0f; owner->m_chunkWidthBasis=2.0f; owner->m_chunkHeightBasis=2.0f;
    CChunkInstance current, first, second;
    instance(current,0,0,0,0); instance(first,1,0,0,0); instance(second,2,30,0,30);
    std::vector<CChunkInstance*> peers;
    unsigned seed=c.index*7919u+17u;
    unsigned mode=c.index%32u;
    if(c.index>=1088) {
        unsigned directed=c.index-1088;
        peers.push_back(&first);
        if(directed<18) {
            unsigned face=directed/3, nudge=directed%3;
            float boundary=0.0f;
            switch(face) { case 0: boundary=7.6f;break; case 1: boundary=-9.5f;break;
                case 2: boundary=2000.0f;break;case 3:boundary=-2000.0f;break;
                case 4:boundary=7.9f;break;default:boundary=-9.9f;break; }
            if(nudge) boundary=::nextafterf(boundary,nudge==1?-HUGE_VALF:HUGE_VALF);
            if(face<2)first.m_x=boundary;else if(face<4)first.m_y=boundary;else first.m_z=boundary;
            types[0]->m_exits.add(Ogre::Vector3(0,0,2));
            types[1]->m_exits.add(Ogre::Vector3(0,0,2));
        } else if(directed<27) {
            unsigned axis=(directed-18)/3,nudge=(directed-18)%3;
            float distance=2.0f;
            if(nudge)distance=::nextafterf(distance,nudge==1?0.0f:HUGE_VALF);
            types[0]->m_exits.add(Ogre::Vector3(0,0,2));
            types[1]->m_exits.add(Ogre::Vector3(axis==0?distance:0,axis==1?distance:0,2+(axis==2?distance:0)));
        } else {
            types[0]->m_exits.add(Ogre::Vector3(0,0,2));
            first.m_x=0;second.m_x=40;second.m_z=0;
            peers.push_back(&second);
            if(directed==28) { peers[0]=&second;peers[1]=&first; }
            if(directed==29)types[2]->m_exits.add(Ogre::Vector3(-40,0,2));
            if(directed==30)types[1]->m_exits.add(Ogre::Vector3(0,0,2));
            if(directed==31) { peers.clear(); }
        }
    } else if(c.index<64) {
        float ex=0.0f,ey=0.0f,ez=2.0f;
        switch(mode%8) {
            case 0: ez=6; break; case 1: ez=-2; break;
            case 2: ex=4; break; case 3: ex=-4; break;
            case 4: ex=2;ez=4;break; case 5: ex=-2;ez=0;break;
            case 6: ex=0;ez=2;break; default: ex=0;ez=0;break;
        }
        types[0]->m_exits.add(Ogre::Vector3(ex,ey,ez));
        types[1]->m_exits.add(Ogre::Vector3(ex,ey,ez));
        types[2]->m_exits.add(Ogre::Vector3(ex,ey,ez));
        if(mode>=8&&mode<16)first.m_x=40;
        if(mode>=16&&mode<24)types[1]->m_exits.clear();
        if(mode>=24) { first.m_x=0;first.m_y=2001; }
        if(c.index&32) { peers.push_back(&second); peers.push_back(&first); }
        else { peers.push_back(&first); peers.push_back(&second); }
    } else {
        const int widths[]={-2,0,1,2,4,7};
        for(unsigned i=0;i<3;++i) {
            types[i]->m_width=widths[next(seed)%6]; types[i]->m_height=widths[next(seed)%6];
            unsigned count=next(seed)%4;
            for(unsigned j=0;j<count;++j)types[i]->m_exits.add(Ogre::Vector3(coordinate(seed),coordinate(seed),coordinate(seed)));
        }
        current.m_x=coordinate(seed);current.m_y=coordinate(seed);current.m_z=coordinate(seed);
        first.m_x=coordinate(seed);first.m_y=coordinate(seed);first.m_z=coordinate(seed);
        second.m_x=coordinate(seed);second.m_y=coordinate(seed);second.m_z=coordinate(seed);
        const float basis[]={0.0f,-0.0f,0.1f,0.5f,1.0f,2.0f,-1.0f,6.5f};
        owner->m_tileBasis=basis[(c.index/32)%8];
        owner->m_chunkWidthBasis=basis[(c.index/7)%8];owner->m_chunkHeightBasis=basis[(c.index/13)%8];
        if(mode!=0)peers.push_back(&first);
        if(mode&1)peers.push_back(&second);
        if(mode==2)peers.push_back(&current);
        if(mode==3)current.m_chunkTypeIndex=-1;
        if(mode==4)first.m_chunkTypeIndex=0x7fffffff;
        if(mode==5) { current.m_x=0;first.m_x=0;current.m_y=0;first.m_y=2000; }
        if(mode==6) { first.m_z=current.m_z;first.m_x=current.m_x;first.m_y=current.m_y; }
        if(mode>=24) {
            const unsigned exceptional[]={0x7fc01234u,0x7f800000u,0xff800000u,0x80000000u};
            float exceptionalValue=bits(exceptional[(c.index/32)%4]);
            switch(mode) {
                case 24: current.m_x=exceptionalValue;break;
                case 25: current.m_y=exceptionalValue;break;
                case 26: current.m_z=exceptionalValue;break;
                case 27: first.m_x=exceptionalValue;break;
                case 28: first.m_y=exceptionalValue;break;
                case 29: first.m_z=exceptionalValue;break;
                case 30: owner->m_tileBasis=exceptionalValue;break;
                default: if(types[0]->m_exits.size())types[0]->m_exits[0].x=exceptionalValue;break;
            }
        }
    }
    bool (*fn)(CLevelTemplateData*,CChunkInstance*,std::vector<CChunkInstance*>&)=
        c.operation==0?(ours?candidateIntersects:originalIntersects):(ours?candidateExits:originalExits);
    unsigned char ownerBefore[sizeof(storage.bytes)];std::memcpy(ownerBefore,storage.bytes,sizeof(ownerBefore));
    feclearexcept(FE_ALL_EXCEPT);
    if(!autotest::beginInvocation(out,fn)) return;
    bool result=fn(owner,&current,peers);out.callCompleted=1;out.add(&result,sizeof(result));
    int exceptions=fetestexcept(FE_ALL_EXCEPT);out.add(&exceptions,sizeof(exceptions));
    bool ownerChanged=std::memcmp(ownerBefore,storage.bytes,sizeof(ownerBefore))!=0;out.add(&ownerChanged,sizeof(ownerChanged));
    captureInstance(out,current);captureInstance(out,first);captureInstance(out,second);
    for(unsigned i=0;i<3;++i) {
        out.add(&types[i]->m_width,8);unsigned n=types[i]->m_exits.size();out.add(&n,4);
        for(unsigned j=0;j<n;++j)out.add(&types[i]->m_exits[j],12);
    }
    unsigned n=peers.size();out.add(&n,4);for(unsigned i=0;i<n;++i) { unsigned id=peers[i]==&first?1:peers[i]==&second?2:0;out.add(&id,4); }
    geometryOwnerDestroy(owner);
}
void original(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name) {
    uint64_t address=static_cast<uint64_t>(reinterpret_cast<uintptr_t>(operation==0?originalIntersects:originalExits));
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<1120;++i) {
        Case c={operation,i};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    geometry case %u/%u status %d/%d bytes %lu/%lu\n",operation,i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte %u: %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return 0;
}
}
TL_TEST(level_template_intersections){return run(host,0,"level_template_intersections");}
TL_TEST(level_template_exit_matches){return run(host,1,"level_template_exit_matches");}
