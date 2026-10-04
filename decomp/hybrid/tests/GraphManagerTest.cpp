#include <map>
#include <string>
#include <vector>
#include <cstring>
#include "AutoTest.h"
#include "GraphManager.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"

TL_ORIGINAL(void, originalManagerLoad, (CGraphManager*, std::wstring),
            "_ZN13CGraphManager9loadGraphESbIwSt11char_traitsIwESaIwEE")
extern "C" void managerAddFloat(CDataGroup*, const std::wstring&, float)
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
struct ManagerView : CRunicCore {
    std::wstring directory;
    std::map<std::wstring,CGraph*> names;
    std::map<std::wstring,CGraph*> filenames;
    TArrayList<CRunicCore*> owned;
    ManagerView() : directory(L""),owned(10) {}
};
typedef char manager_layout[sizeof(ManagerView)==sizeof(CGraphManager)&&sizeof(CGraphManager)==0x90?1:-1];
typedef char files_layout[sizeof(FileSystemView)==sizeof(CFileSystem)?1:-1];
struct Case { unsigned int seed; };

void capture(ManagerView& manager,autotest::Capture& out) {
    std::vector<CGraph*> ids;
    for(int map=0;map<2;++map) {
        const std::map<std::wstring,CGraph*>& values=map?manager.filenames:manager.names;
        size_t count=values.size();out.add(&count,sizeof(count));
        if(count>32)_exit(4);
        for(std::map<std::wstring,CGraph*>::const_iterator i=values.begin();i!=values.end();++i) {
            out.addText(i->first);
            CGraph* graph=i->second;
            unsigned int id=0;
            if(graph) {
                size_t k=0;while(k<ids.size()&&ids[k]!=graph)++k;
                if(k==ids.size())ids.push_back(graph);
                id=k+1;
            }
            out.add(&id,sizeof(id));
            if(graph) {
                out.addText(graph->getName());
                int points=graph->getControlPoints();out.add(&points,sizeof(points));
                for(int line=0;line<2;++line) {
                    float value=graph->getValue(0.5f,line);out.add(&value,sizeof(value));
                }
            }
        }
    }
    out.addHeapInUse();
}
void side(Case& c,bool ours,autotest::Capture& out) {
    FileSystemView files;
    CFileSystem* saved=g_pFileSystem;g_pFileSystem=reinterpret_cast<CFileSystem*>(&files);
    CDataGroup dataA(L"GRAPH",NULL,20,10,NULL),dataB(L"GRAPH",NULL,20,10,NULL),empty(L"GRAPH",NULL,20,10,NULL);
    CDataGroup* data[]={&dataA,&dataB,&empty};
    for(unsigned int d=0;d<3;++d) {
        std::wstring name=d==2?L"":d==0?L"Alpha":c.seed%2?L"ALPHA":L"Beta";
        data[d]->AddDataValue(L"NAME",name,false);
        data[d]->AddDataValue(L"TYPE",std::wstring(c.seed%3?L"LINE":L"RANGE"),false);
        for(unsigned int p=0;p<3;++p) {
            CDataGroup* point=data[d]->AddDataGroup(L"POINT");
            managerAddFloat(point,L"X",float(p));managerAddFloat(point,L"Y",float(p+d+c.seed));
            managerAddFloat(point,L"MINY",float(p));managerAddFloat(point,L"MAXY",float(p+d+4));
        }
    }
    const wchar_t* paths[]={L"media\\graphs\\a.dat",L"MEDIA/GRAPHS/B.DAT",L"media/graphs/empty.dat"};
    for(unsigned int d=0;d<3;++d)
        files.dataGroups[FILESYSTEM::CleanPath(STRINGS::StringUpper(paths[d]))]=data[d];
    {
        ManagerView view;
        CGraphManager* manager=reinterpret_cast<CGraphManager*>(&view);
        if(c.seed%5==0)view.names[L"ALPHA"]=NULL;
        for(unsigned int step=0;step<7;++step) {
            unsigned int selected=(step+c.seed)%3;
            if(step==4)files.dataGroups[FILESYSTEM::CleanPath(STRINGS::StringUpper(paths[0]))]=&dataB;
            if(ours)manager->loadGraph(paths[selected]);else originalManagerLoad(manager,paths[selected]);
            capture(view,out);
        }
        manager->clear();capture(view,out);
    }
    g_pFileSystem=saved;
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(graph_manager_loading_and_duplicates) {
    int failures=0;
    for(unsigned int seed=0;seed<30;++seed) {
        Case c={seed};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    graph manager seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
