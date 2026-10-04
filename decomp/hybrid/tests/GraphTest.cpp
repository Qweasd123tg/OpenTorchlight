#include <map>
#include <string>
#include <vector>
#include <new>
#include <cstring>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "AutoTest.h"
#include "Graph.h"
#include "DataGroup.h"
#include "FileSystem.h"

TL_ORIGINAL(bool, originalLoadGraph, (CGraph*, const wchar_t*), "_ZN6CGraph9loadGraphEPKw")
TL_ORIGINAL(void, originalLoadGraphLine, (CGraph*, CDataGroup*), "_ZN6CGraph13loadGraphLineEP10CDataGroup")
TL_ORIGINAL(void, originalAddGraphLine, (CGraph*, EGRAPH_TYPES), "_ZN6CGraph12addGraphLineE12EGRAPH_TYPES")
extern "C" void addFloat(CDataGroup*, const std::wstring&, float)
    __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf");

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
    unsigned int lineCount;
    bool dirty; bool infer;
    float firstSlope, otherSlope, firstMax, otherMax, lastX;
};
typedef char graph_size[sizeof(CGraph)==0x58?1:-1];
typedef char particle_curve_size[sizeof(ParticleUniverse::DynamicAttributeCurved)==0xa8?1:-1];
typedef char graph_layout[sizeof(GraphView)==sizeof(CGraph)?1:-1];
typedef char filesystem_layout[sizeof(FileSystemView)==sizeof(CFileSystem)?1:-1];
struct Case { CDataGroup* data; bool twice; int operation; int seed; };

void captureGraph(CGraph& graph, autotest::Capture& out) {
    const GraphView& v=*reinterpret_cast<const GraphView*>(&graph);
    out.add(&v.type,sizeof(v.type));
    out.add(&v.lineCount,sizeof(v.lineCount));
    out.add(&v.dirty,sizeof(v.dirty));
    out.add(&v.infer,sizeof(v.infer));
    out.add(&v.firstSlope,5*sizeof(float));
    out.addText(v.name);
    unsigned int count=v.lines.size(); out.add(&count,sizeof(count));
    struct ListView { void* data; unsigned int count, capacity, growBy; };
    const ListView& list=*reinterpret_cast<const ListView*>(&v.lines);
    out.add(&list.capacity,sizeof(list.capacity));
    out.add(&list.growBy,sizeof(list.growBy));
    if(count>16) _exit(4);
    for(unsigned int i=0;i<count;++i) {
        ParticleUniverse::DynamicAttributeCurved* curve=v.lines[i];
        size_t n=curve->getNumControlPoints();out.add(&n,sizeof(n));
        if(n>32) _exit(4);
        for(unsigned int k=0;k<n;++k) {
            float x,y;curve->getControlPointValues(k,x,y);
            out.add(&x,sizeof(x));out.add(&y,sizeof(y));
        }
        // Snapshot the processed spline itself; evaluating a raw PU curve
        // outside its domain is not a valid probe of CGraph::loadGraph.
        struct CurveView {
            void* vptr; int type; float range; Ogre::SimpleSpline spline;
            ParticleUniverse::InterpolationType interpolation;
            std::vector<Ogre::Vector2> points;
        };
        typedef char curve_layout[sizeof(CurveView)==sizeof(ParticleUniverse::DynamicAttributeCurved)?1:-1];
        const CurveView& view=*reinterpret_cast<const CurveView*>(curve);
        out.add(&view.range,sizeof(view.range));
        out.add(&view.interpolation,sizeof(view.interpolation));
        unsigned int splinePoints=view.spline.getNumPoints();
        out.add(&splinePoints,sizeof(splinePoints));
        if(splinePoints>32)_exit(4);
        for(unsigned int k=0;k<splinePoints;++k) {
            const Ogre::Vector3& point=view.spline.getPoint(k);
            out.add(&point.x,3*sizeof(float));
        }
    }
}

void runSide(Case& c,bool ours,autotest::Capture& out) {
    FileSystemView files;
    files.dataGroups[L"GRAPH.DAT"]=c.data;
    CFileSystem* saved=g_pFileSystem;
    g_pFileSystem=reinterpret_cast<CFileSystem*>(&files);
    {
        CGraph graph(L"");
        if(c.operation==1) {
            GraphView& view=*reinterpret_cast<GraphView*>(&graph);
            view.type=static_cast<EGRAPH_TYPES>(c.seed%3);
            for(int i=0;i<c.seed%3;++i)originalAddGraphLine(&graph,view.type);
            CDataGroup* input=c.seed%12==0?NULL:c.data;
            if(ours)graph.loadGraphLine(input);else originalLoadGraphLine(&graph,input);
            graph.processPoints();
            captureGraph(graph,out);
        } else if(c.operation==2) {
            int initial=c.seed%4==0?10:c.seed%4==1?9:0;
            for(int i=0;i<initial;++i)originalAddGraphLine(&graph,GRAPH_LINEAR);
            EGRAPH_TYPES type=static_cast<EGRAPH_TYPES>(c.seed%3);
            if(ours)graph.addGraphLine(type);else originalAddGraphLine(&graph,type);
            captureGraph(graph,out);
        } else {
        int repetitions=c.twice?2:1;
        for(int i=0;i<repetitions;++i) {
            bool result=ours?graph.loadGraph(L"graph.dat"):originalLoadGraph(&graph,L"graph.dat");
            out.add(&result,sizeof(result));
            captureGraph(graph,out);
        }
        }
    }
    g_pFileSystem=saved;
    out.addHeapInUse();
}

bool run(Case& c,bool ours,autotest::Capture& out) {
    int fds[2];if(pipe(fds)!=0)return false;
    pid_t child=fork();
    if(child==0) {
        close(fds[0]);
        prctl(PR_SET_DUMPABLE,0,0,0,0);
        signal(SIGSEGV,autotest::crashed);signal(SIGBUS,autotest::crashed);
        signal(SIGABRT,autotest::crashed);alarm(2);
        autotest::Capture captured={};runSide(c,ours,captured);
        if(captured.length>=autotest::Capture::kSize)_exit(5);
        size_t at=0;
        while(at<captured.length) {
            ssize_t n=write(fds[1],captured.data+at,captured.length-at);
            if(n<=0)_exit(6);at+=n;
        }
        _exit(0);
    }
    close(fds[1]);out.length=0;
    while(out.length<autotest::Capture::kSize) {
        ssize_t n=read(fds[0],out.data+out.length,autotest::Capture::kSize-out.length);
        if(n<=0)break;out.length+=n;
    }
    close(fds[0]);int status=0;
    if(child<0||waitpid(child,&status,0)!=child)return false;
    return WIFEXITED(status)&&WEXITSTATUS(status)==0&&out.length>0;
}
}

TL_TEST(graph_curve_loading) {
    int failures=0;
    for(int seed=0;seed<48;++seed) {
        CDataGroup data(L"GRAPH",NULL,20,10,NULL);
        data.AddDataValue(L"TYPE",std::wstring(seed%3==0?L"LINE":seed%3==1?L"range":L"other"),false);
        data.AddDataValue(L"NAME",std::wstring(seed%2?L"curve α":L""),false);
        if (seed % 5 != 0)
            data.AddDataValue(L"CURVED",(seed&1)!=0);
        if (seed % 7 != 0)
            data.AddDataValue(L"INFER_PASSED_END",(seed&2)!=0);
        const int points=(seed/3)%4;
        for(int i=0;i<points;++i) {
            CDataGroup* point=data.AddDataGroup(L"POINT");
            addFloat(point,L"X",float(i*2));
            addFloat(point,L"Y",float(5-i*3));
            addFloat(point,L"MINY",float(i-4));
            addFloat(point,L"MAXY",float(9-i*2));
        }
        for(int operation=0;operation<3;++operation) {
        Case c={&data,(seed&4)!=0,operation,seed};
        autotest::Capture a={},b={};
        bool left=run(c,false,a),right=run(c,true,b);
        // Two failing children are never a successful comparison.
        bool same=left&&right&&a.length==b.length&&std::memcmp(a.data,b.data,a.length)==0;
        if(!same)host->log("    graph seed %d original=%d ours=%d bytes=%lu/%lu\n",seed,left,right,(unsigned long)a.length,(unsigned long)b.length);
        TL_CHECK(failures,same);
        }
    }
    return failures;
}
