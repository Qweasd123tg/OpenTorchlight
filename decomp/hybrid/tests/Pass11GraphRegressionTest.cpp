// Fresh, receipt-bearing Graph regressions. GraphTest.cpp remains unchanged.
// Original ELF: C1/C2 0xc792d0, D1/D2 0xc785a0; graph size 0x58,
// lines 0x18, name 0x30, line count 0x38, flags 0x3c/0x3d, floats 0x40.
#include <map>
#include <string>
#include <vector>
#include <new>
#include <cstring>
#include <cstddef>
#include <limits>
#include "AutoTest.h"
#include "Detour.h"
#include "Graph.h"
#include "DataGroup.h"
#include "FileSystem.h"

TL_ORIGINAL(void, p11OldAddLine, (CGraph*, EGRAPH_TYPES), "_ZN6CGraph12addGraphLineE12EGRAPH_TYPES")
TL_ORIGINAL(void, p11OldLoadLine, (CGraph*, CDataGroup*), "_ZN6CGraph13loadGraphLineEP10CDataGroup")
TL_ORIGINAL(void, p11OldProcess, (CGraph*), "_ZN6CGraph13processPointsEv")
TL_ORIGINAL(int, p11OldCount, (CGraph*), "_ZN6CGraph16getControlPointsEv")
TL_ORIGINAL(void, p11OldAddValue, (CGraph*, float, float, unsigned), "_ZN6CGraph8addValueEffj")
TL_ORIGINAL(bool, p11OldLoad, (CGraph*, const wchar_t*), "_ZN6CGraph9loadGraphEPKw")
TL_ORIGINAL(void, p11OldC1, (CGraph*, const std::wstring&), "_ZN6CGraphC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, p11OldC2, (CGraph*, const std::wstring&), "_ZN6CGraphC2ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, p11OldD1, (CGraph*), "_ZN6CGraphD1Ev")
TL_ORIGINAL(void, p11OldD2, (CGraph*), "_ZN6CGraphD2Ev")
TL_ORIGINAL(float, p11OldValue, (const CGraph*, float, unsigned), "_ZNK6CGraph8getValueEfj")
extern "C" void p11NewAddLine(CGraph*, EGRAPH_TYPES) __asm__("_ZN6CGraph12addGraphLineE12EGRAPH_TYPES");
extern "C" void p11NewLoadLine(CGraph*, CDataGroup*) __asm__("_ZN6CGraph13loadGraphLineEP10CDataGroup");
extern "C" void p11NewProcess(CGraph*) __asm__("_ZN6CGraph13processPointsEv");
extern "C" int p11NewCount(CGraph*) __asm__("_ZN6CGraph16getControlPointsEv");
extern "C" void p11NewAddValue(CGraph*, float, float, unsigned) __asm__("_ZN6CGraph8addValueEffj");
extern "C" bool p11NewLoad(CGraph*, const wchar_t*) __asm__("_ZN6CGraph9loadGraphEPKw");
extern "C" void p11NewC1(CGraph*, const std::wstring&) __asm__("_ZN6CGraphC1ERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void p11NewC2(CGraph*, const std::wstring&) __asm__("_ZN6CGraphC2ERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void p11NewD1(CGraph*) __asm__("_ZN6CGraphD1Ev");
extern "C" void p11NewD2(CGraph*) __asm__("_ZN6CGraphD2Ev");
extern "C" float p11NewValue(const CGraph*, float, unsigned) __asm__("_ZNK6CGraph8getValueEfj");
extern "C" void p11AddFloat(CDataGroup*, const std::wstring&, float)
    __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf");
TL_FUNCTION(p11CoreCtor, "_ZN10CRunicCoreC2Ev")
TL_FUNCTION(p11CoreDtor, "_ZN10CRunicCoreD2Ev")

namespace {
struct FileSystemView {
    FileSystemView() : vptr(0), safePointers(0), resourceGroupsAdded(false), modFileFilter(0),
        initialized(false), pakExists(false), needsRecompress(false), pakTime(0), settings(0),
        resourceGroups(1), massiveDataGroup(0), meshListener(0), scriptListener(0), ownedObjects(10) {}
    void* vptr; void* safePointers;
    bool resourceGroupsAdded; void* modFileFilter; bool initialized;
    std::wstring pakFile; bool pakExists; bool needsRecompress; long long pakTime; void* settings;
    TArrayList<std::string> resourceGroups; void* massiveDataGroup;
    std::map<std::wstring,CDataGroup*> dataGroups;
    void* meshListener; void* scriptListener; TArrayList<void*> ownedObjects;
};
struct GraphView {
    void* vptr; void* safePointers;
    EGRAPH_TYPES type;
    TArrayList<ParticleUniverse::DynamicAttributeCurved*> lines;
    std::wstring name;
    unsigned lineCount;
    bool dirty, infer;
    float firstSlope, otherSlope, firstMax, otherMax, lastX;
};
struct ListView { void* data; unsigned count, capacity, growBy; };
struct CurveView {
    void* vptr; int type; float range; Ogre::SimpleSpline spline;
    ParticleUniverse::InterpolationType interpolation;
    std::vector<Ogre::Vector2> points;
};
typedef char graph_size[sizeof(CGraph)==0x58 && sizeof(GraphView)==0x58 ? 1:-1];
typedef char graph_offsets[offsetof(GraphView,lines)==0x18 && offsetof(GraphView,name)==0x30 &&
    offsetof(GraphView,dirty)==0x3c && offsetof(GraphView,firstSlope)==0x40 ? 1:-1];
typedef char curve_size[sizeof(CurveView)==0xa8 && sizeof(ParticleUniverse::DynamicAttributeCurved)==0xa8 ? 1:-1];
typedef char curve_offsets[offsetof(CurveView,spline)==0x10 && offsetof(CurveView,points)==0x90 ? 1:-1];
typedef char file_layout[sizeof(FileSystemView)==sizeof(CFileSystem) ? 1:-1];
typedef char list_layout[sizeof(ListView)==sizeof(TArrayList<void*>) ? 1:-1];
struct Case { unsigned mode, seed; };
autotest::Capture* active;
CGraph* target;
bool recordingDestruction;
unsigned baseConstructed, baseDestroyed, curveDestroyed;
void number(unsigned n) { active->add(&n,sizeof(n)); }

// The real core ctor writes a process-global object counter. Isolate that
// unrelated global and normalize the base vptr; the graph owns no safe refs.
// Both original and linked core entries are redirected, never the target.
void coreCtor(CRunicCore* p) {
    void* nullPointer=NULL;
    std::memcpy(reinterpret_cast<char*>(p),&nullPointer,sizeof(nullPointer));
    std::memcpy(reinterpret_cast<char*>(p)+8,&nullPointer,sizeof(nullPointer));
    if(reinterpret_cast<void*>(p)==reinterpret_cast<void*>(target)) ++baseConstructed;
}
void coreDtor(CRunicCore* p) {
    void* safe=NULL;
    std::memcpy(&safe,reinterpret_cast<char*>(p)+8,sizeof(safe));
    if(safe) _exit(61); // No fake safe-pointer lifetime is silently accepted.
    if(reinterpret_cast<void*>(p)==reinterpret_cast<void*>(target)) {
        ++baseDestroyed;
        if(recordingDestruction) number(0xc0de);
    }
    void* nullPointer=NULL;
    std::memcpy(reinterpret_cast<char*>(p),&nullPointer,sizeof(nullPointer));
}

void captureCurve(ParticleUniverse::DynamicAttributeCurved* p) {
    const unsigned present=p!=NULL; number(present);
    if(!p) return;
    CurveView& v=*reinterpret_cast<CurveView*>(p);
    active->add(&v.type,sizeof(v.type)); active->add(&v.range,sizeof(v.range));
    active->add(&v.interpolation,sizeof(v.interpolation));
    const size_t count=p->getNumControlPoints(); active->add(&count,sizeof(count));
    if(count>64) _exit(62);
    for(unsigned i=0;i<count;++i) {
        float x,y; p->getControlPointValues(i,x,y);
        active->add(&x,sizeof(x)); active->add(&y,sizeof(y));
    }
    unsigned n=v.spline.getNumPoints(); number(n);
    if(n>64) _exit(63);
    for(unsigned i=0;i<n;++i) {
        const Ogre::Vector3& point=v.spline.getPoint(i); active->add(&point.x,3*sizeof(float));
    }
    // Interior samples also observe spline tangents, not merely its points.
    // Never evaluate a raw PU curve outside its valid x-domain.
    if(n>=2) for(unsigned i=0;i<5;++i) {
        Ogre::Vector3 point=v.spline.interpolate(float(i)*0.25f);
        active->add(&point.x,3*sizeof(float));
    }
}
void captureGraph(CGraph* p) {
    const GraphView& v=*reinterpret_cast<const GraphView*>(p);
    number(v.vptr!=NULL); number(v.safePointers!=NULL);
    active->add(&v.type,sizeof(v.type)); number(v.lineCount);
    active->add(&v.dirty,sizeof(v.dirty)); active->add(&v.infer,sizeof(v.infer));
    active->add(&v.firstSlope,5*sizeof(float)); active->addText(v.name);
    const ListView& l=*reinterpret_cast<const ListView*>(&v.lines);
    number(l.data!=NULL); number(l.count); number(l.capacity); number(l.growBy);
    if(l.count>40 || l.count>l.capacity) _exit(64);
    for(unsigned i=0;i<l.count;++i) captureCurve(v.lines[i]);
}

// Exercise virtual deletion with real owning curve allocations. Each subclass
// records its identity and final curve contents before its real PU destructor.
class TrackedCurve : public ParticleUniverse::DynamicAttributeCurved {
    unsigned id;
public:
    TrackedCurve(unsigned value, ParticleUniverse::InterpolationType type)
      : ParticleUniverse::DynamicAttributeCurved(type), id(value) {}
    virtual ~TrackedCurve() {
        if(recordingDestruction) { number(id); captureCurve(this); ++curveDestroyed; }
    }
};

void fillData(CDataGroup& data,unsigned seed) {
    const wchar_t* types[]={L"LINE",L"line",L"range",L"OTHER"};
    if(seed%7) data.AddDataValue(L"TYPE",std::wstring(types[seed%4]),false);
    if(seed%5) data.AddDataValue(L"NAME",std::wstring(seed+1,L'a'+seed%20)+L" \x3b1",false);
    if(seed%6) data.AddDataValue(L"CURVED",(seed&1)!=0);
    if(seed%7) data.AddDataValue(L"INFER_PASSED_END",(seed&2)!=0);
    for(unsigned i=0;i<seed%7;++i) {
        CDataGroup* point=data.AddDataGroup(L"POINT");
        // Omit fields independently to exercise defaults. X remains ordered.
        p11AddFloat(point,L"X",float(i*2));
        if((seed+i)%4) p11AddFloat(point,L"Y",float(int(seed)-24-int(i)*3)*0.5f);
        if((seed+i)%5) p11AddFloat(point,L"MINY",float(int(i)-int(seed))*0.25f);
        if((seed+i)%6) p11AddFloat(point,L"MAXY",float(int(seed)+9-int(i)*2));
    }
}
void seedScalars(GraphView& v,unsigned seed) {
    v.type=static_cast<EGRAPH_TYPES>(seed%3);
    v.name=std::wstring(seed+1,L'A'+seed%26);
    v.lineCount=1+seed%17; // Deliberately independent of actual list length.
    v.dirty=(seed&1)!=0; v.infer=(seed&2)!=0;
    v.firstSlope=float(int(seed)-30)*0.25f; v.otherSlope=float(40-int(seed))*0.5f;
    v.firstMax=float(int(seed)-20); v.otherMax=float(10-int(seed)); v.lastX=float(seed%9);
}
void addLines(CGraph* graph,unsigned n,unsigned seed,bool points) {
    GraphView& v=*reinterpret_cast<GraphView*>(graph);
    for(unsigned i=0;i<n;++i) {
        p11OldAddLine(graph,static_cast<EGRAPH_TYPES>((seed+i)%3));
        if(points) for(unsigned j=0;j<(seed/3+i*3)%9;++j)
            v.lines[i]->addControlPoint(float(j*2),float(int(seed)-int(i)*4+int(j)*int(j))*0.25f);
    }
}
void captureDead(const unsigned char* bytes) {
    // Read object representation only, not dead std::wstring/vector objects.
    void* data=NULL; std::memcpy(&data,bytes+0x18,sizeof(data)); number(data!=NULL);
    active->add(bytes+0x20,3*sizeof(unsigned)); // cleared count/capacity; growBy
    active->add(bytes+0x10,sizeof(EGRAPH_TYPES));
    active->add(bytes+0x38,sizeof(unsigned));
    active->add(bytes+0x3c,2*sizeof(bool));
    active->add(bytes+0x40,5*sizeof(float));
}

void side(void* context,autotest::Capture& out,bool ours) {
    const Case c=*static_cast<Case*>(context);
    active=&out; recordingDestruction=false;
    baseConstructed=baseDestroyed=curveDestroyed=0;
    unsigned long long storage[(sizeof(CGraph)+7)/8];
    std::memset(storage,0xa5,sizeof(storage)); target=reinterpret_cast<CGraph*>(storage);
    detour::Set detours;
    TL_REDIRECT(detours,p11CoreCtor,&coreCtor);
    TL_REDIRECT(detours,p11CoreDtor,&coreDtor);
    if(detours.failed()) _exit(60);
    {
        CDataGroup data(L"GRAPH",NULL,20,10,NULL); fillData(data,c.seed);
        FileSystemView files; files.dataGroups[L"GRAPH.DAT"]=&data;
        CFileSystem* saved=g_pFileSystem; g_pFileSystem=reinterpret_cast<CFileSystem*>(&files);
        const std::wstring empty;
        GraphView& v=*reinterpret_cast<GraphView*>(target);
        if(c.mode==6 || c.mode==7) {
            const wchar_t* names[]={L"",L"graph.dat",L"GRAPH.DAT",L"Graph.Dat"};
            std::wstring filename=names[c.seed%8==0?0:1+c.seed%3];
            typedef void(*Ctor)(CGraph*,const std::wstring&);
            Ctor fn=c.mode==6?(ours?&p11NewC1:&p11OldC1):(ours?&p11NewC2:&p11OldC2);
            autotest::invoke<Ctor,CGraph*,const std::wstring&>(out,fn,target,filename);
            captureGraph(target); out.addText(filename); number(baseConstructed);
            p11OldD1(target);
        } else {
            p11OldC1(target,empty); seedScalars(v,c.seed);
            if(c.mode==0) {
                const unsigned sizes[]={0,1,2,9,10,11,19,20};
                v.lines.setGrowBy(1+c.seed%5);
                addLines(target,sizes[c.seed%8],c.seed,true);
                EGRAPH_TYPES type=static_cast<EGRAPH_TYPES>(int((c.seed/8)%4)-1);
                captureGraph(target);
                autotest::invoke(out,ours?&p11NewAddLine:&p11OldAddLine,target,type);
                captureGraph(target);
            } else if(c.mode==1) {
                addLines(target,c.seed%4,c.seed,true); captureGraph(target);
                CDataGroup* input=c.seed%13==0?NULL:&data;
                autotest::invoke(out,ours?&p11NewLoadLine:&p11OldLoadLine,target,input);
                captureGraph(target); // Includes the dirty flag before processing.
                p11OldProcess(target); captureGraph(target);
            } else if(c.mode==2 || c.mode==3) {
                addLines(target,c.seed%8,c.seed,true);
                if(c.mode==2 && (c.seed&1)) {
                    p11OldProcess(target);
                    for(unsigned i=0;i<v.lines.size();++i)
                        v.lines[i]->addControlPoint(30.f,float(int(c.seed)-int(i)*2));
                    v.dirty=true;
                }
                captureGraph(target);
                if(c.mode==2) autotest::invoke(out,ours?&p11NewProcess:&p11OldProcess,target);
                else autotest::invoke(out,ours?&p11NewCount:&p11OldCount,target);
                captureGraph(target);
            } else if(c.mode==4) {
                addLines(target,c.seed%5,c.seed,true); captureGraph(target);
                const float xs[]={-3.f,-0.f,0.f,2.5f,8.f,23.f};
                float x=xs[c.seed%6],y=float(int(c.seed)-32)*0.5f;
                if(c.seed==62) x=std::numeric_limits<float>::quiet_NaN();
                if(c.seed==63) y=std::numeric_limits<float>::quiet_NaN();
                autotest::invoke(out,ours?&p11NewAddValue:&p11OldAddValue,target,x,y,c.seed%13);
                captureGraph(target);
            } else if(c.mode==5) {
                addLines(target,c.seed%4,c.seed,true);
                if(c.seed&4) p11OldLoad(target,L"graph.dat");
                captureGraph(target);
                const wchar_t* filename=c.seed&1?L"graph.dat":L"GRAPH.DAT";
                autotest::invoke(out,ours?&p11NewLoad:&p11OldLoad,target,filename);
                captureGraph(target);
            } else if(c.mode==8 || c.mode==9) {
                for(unsigned i=0;i<c.seed%13;++i) {
                    TrackedCurve* curve=NULL;
                    if((i+c.seed)%5) {
                        curve=new TrackedCurve(i,static_cast<ParticleUniverse::InterpolationType>((i+c.seed)%2));
                        for(unsigned j=0;j<(i+c.seed)%7;++j)
                            curve->addControlPoint(float(j*2),float(int(c.seed)-int(i)*3+int(j)));
                        curve->processControlPoints();
                    }
                    v.lines.add(curve);
                }
                // Preserve a COW peer so destruction must release, not corrupt it.
                std::wstring shared=v.name; captureGraph(target); out.addHeapInUse();
                recordingDestruction=true;
                autotest::invoke(out,c.mode==8?(ours?&p11NewD1:&p11OldD1):(ours?&p11NewD2:&p11OldD2),target);
                recordingDestruction=false;
                number(curveDestroyed); number(baseDestroyed);
                captureDead(reinterpret_cast<const unsigned char*>(storage));
                out.addText(shared); out.addHeapInUse();
            } else if(c.mode==10) {
                unsigned n=c.seed%8==0?0:1+c.seed%4;
                addLines(target,n,c.seed,false);
                for(unsigned i=0;i<n;++i) {
                    for(unsigned j=0;j<4;++j)
                        v.lines[i]->addControlPoint(float(j*2),float(int(c.seed)-int(i)*7+int(j)*int(j)));
                    v.lines[i]->processControlPoints();
                    if((i+c.seed)%5==0) { delete v.lines[i]; v.lines[i]=NULL; }
                }
                v.lastX=6.f;
                float x=float(c.seed%5)*1.5f;
                if(v.infer && c.seed%3) x=7.f+float(c.seed%11);
                unsigned line=c.seed%6;
                captureGraph(target);
                const CGraph* graph=target;
                autotest::invoke(out,ours?&p11NewValue:&p11OldValue,graph,x,line);
                captureGraph(target); // getValue must not mutate graph or curves.
            } else _exit(65);
            if(c.mode!=8 && c.mode!=9) p11OldD1(target);
        }
        number(baseConstructed); number(baseDestroyed);
        g_pFileSystem=saved;
    }
    out.addHeapInUse(); target=NULL;
}
void original(void* p,autotest::Capture& out) { side(p,out,false); }
void recovered(void* p,autotest::Capture& out) { side(p,out,true); }
int run(const tlhybrid_host* host,unsigned mode) {
    void* originals[]={ (void*)&p11OldAddLine,(void*)&p11OldLoadLine,(void*)&p11OldProcess,
        (void*)&p11OldCount,(void*)&p11OldAddValue,(void*)&p11OldLoad,(void*)&p11OldC1,
        (void*)&p11OldC2,(void*)&p11OldD1,(void*)&p11OldD2,(void*)&p11OldValue };
    const char* names[]={"pass11_graph_add_line","pass11_graph_load_line","pass11_graph_process",
        "pass11_graph_control_count","pass11_graph_add_value","pass11_graph_load",
        "pass11_graph_ctor_c1","pass11_graph_ctor_c2","pass11_graph_dtor_d1",
        "pass11_graph_dtor_d2","pass11_graph_get_value"};
    autotest::Coverage coverage(names[mode],(uint64_t)(uintptr_t)originals[mode]);
    int failures=0;
    for(unsigned seed=0;seed<64;++seed) {
        Case c={mode,seed}; autotest::Outcome a,b;
        autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
        int result=coverage.observe(host,a,b);
        if(result) {
            ++failures;
            if(failures<=8) host->log("    %s seed %u result %d status %d/%d bytes %lu/%lu\n",
                names[mode],seed,result,a.childStatus,b.childStatus,
                (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        }
    }
    coverage.report(host);
    // Crashes, timeouts, absent receipts and mismatched targets never count.
    if(coverage.completed<20) ++failures;
    return failures;
}
}
TL_TEST(pass11_graph_add_line) { return run(host,0); }
TL_TEST(pass11_graph_load_line) { return run(host,1); }
TL_TEST(pass11_graph_process) { return run(host,2); }
TL_TEST(pass11_graph_control_count) { return run(host,3); }
TL_TEST(pass11_graph_add_value) { return run(host,4); }
TL_TEST(pass11_graph_load) { return run(host,5); }
TL_TEST(pass11_graph_ctor_c1) { return run(host,6); }
TL_TEST(pass11_graph_ctor_c2) { return run(host,7); }
TL_TEST(pass11_graph_dtor_d1) { return run(host,8); }
TL_TEST(pass11_graph_dtor_d2) { return run(host,9); }
TL_TEST(pass11_graph_get_value) { return run(host,10); }
