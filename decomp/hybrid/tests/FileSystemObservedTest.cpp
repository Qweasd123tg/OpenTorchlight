// Shadow test: the decompiled CFileSystem and its mesh and script listeners
// against the original machine code. Every file the test touches lives in a
// fresh directory under /tmp/opencode: it stands in for the installation
// (GetApplicationPath and the working directory point there for the duration),
// for a mod folder and for two OGRE FileSystem archives registered as resource
// groups. OGRE gets a Root with a silent log and no plugins.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ftw.h>
#include <map>
#include <new>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <vector>

#include <OgreAny.h>
#include <OgreLogManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>

#include "FileSystem.h"
#include "FileUtilities.h"
#include "AutoTest.h"

TL_ORIGINAL(void, originalCoreConstruct, (void*), "_ZN10CRunicCoreC2Ev")
TL_ORIGINAL(void, originalDestroy, (void*), "_ZN11CFileSystemD2Ev")
TL_ORIGINAL(bool, originalIsNewer, (void*, CFileInfo&, CFileInfo&), "_ZN11CFileSystem20fileIsNewerOrEqualToER9CFileInfoS1_")
TL_ORIGINAL(int, originalGetAbsolutePath, (void*, const std::wstring&, CFileInfo&, bool),
            "_ZN11CFileSystem15getAbsolutePathERKSbIwSt11char_traitsIwESaIwEER9CFileInfob")
TL_ORIGINAL(void, originalGetFileInfo, (void*, const std::wstring&, CFileInfo&, bool, bool, bool),
            "_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_ORIGINAL(void, originalGetFilesInDirectory,
            (void*, TArrayList<std::wstring>&, std::string&, std::string&, bool, bool, bool, const std::string&),
            "_ZN11CFileSystem19getFilesInDirectoryER10TArrayListISbIwSt11char_traitsIwESaIwEEERSsS7_bbbRKSs")
TL_ORIGINAL(unsigned int, originalGetFileList,
            (void*, const std::wstring&, TArrayList<std::wstring>&, std::wstring, bool, bool, bool, bool),
            "_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_ORIGINAL(void, originalProcessMaterialName, (void*, Ogre::Mesh*, Ogre::String*),
            "_ZN13CMeshListener19processMaterialNameEPN4Ogre4MeshEPSs")
TL_ORIGINAL(void, originalProcessSkeletonName, (void*, Ogre::Mesh*, Ogre::String*),
            "_ZN13CMeshListener19processSkeletonNameEPN4Ogre4MeshEPSs")
TL_ORIGINAL(bool, originalHandleEvent,
            (void*, Ogre::ScriptCompiler*, const Ogre::String&, const std::vector<Ogre::Any>&, Ogre::Any*),
            "_ZN15CScriptListener11handleEventEPN4Ogre14ScriptCompilerERKSsRKSt6vectorINS0_3AnyESaIS6_EEPS6_")
TL_ORIGINAL(void, originalAddString, (void*, std::string), "_ZN10TArrayListISsE3addESs")

// The listener classes exist only inside FileSystem.cpp: reach the decompiled
// methods by symbol.
extern "C" void ourProcessMaterialName(void*, Ogre::Mesh*, Ogre::String*)
    __asm__("_ZN13CMeshListener19processMaterialNameEPN4Ogre4MeshEPSs");
extern "C" void ourProcessSkeletonName(void*, Ogre::Mesh*, Ogre::String*)
    __asm__("_ZN13CMeshListener19processSkeletonNameEPN4Ogre4MeshEPSs");
extern "C" bool ourHandleEvent(void*, Ogre::ScriptCompiler*, const Ogre::String&, const std::vector<Ogre::Any>&,
                               Ogre::Any*)
    __asm__("_ZN15CScriptListener11handleEventEPN4Ogre14ScriptCompilerERKSsRKSt6vectorINS0_3AnyESaIS6_EEPS6_");
extern "C" void ourAddString(void*, std::string) __asm__("_ZN10TArrayListISsE3addESs");

// Cache behind FILESYSTEM::GetApplicationPath(): when non-empty it is the
// installation folder.
extern std::wstring g_applicationPathCache __asm__("_ZZN10FILESYSTEM18GetApplicationPathEvE12absolutePath");

extern "C" void candidateCoreConstruct (void*) __asm__("_ZN10CRunicCoreC2Ev");
extern "C" void candidateDestroy (void*) __asm__("_ZN11CFileSystemD2Ev");
extern "C" bool candidateIsNewer (void*, CFileInfo&, CFileInfo&) __asm__("_ZN11CFileSystem20fileIsNewerOrEqualToER9CFileInfoS1_");
extern "C" int candidateGetAbsolutePath (void*, const std::wstring&, CFileInfo&, bool) __asm__("_ZN11CFileSystem15getAbsolutePathERKSbIwSt11char_traitsIwESaIwEER9CFileInfob");
extern "C" void candidateGetFileInfo (void*, const std::wstring&, CFileInfo&, bool, bool, bool) __asm__("_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb");
extern "C" void candidateGetFilesInDirectory (void*, TArrayList<std::wstring>&, std::string&, std::string&, bool, bool, bool, const std::string&) __asm__("_ZN11CFileSystem19getFilesInDirectoryER10TArrayListISbIwSt11char_traitsIwESaIwEEERSsS7_bbbRKSs");
extern "C" unsigned int candidateGetFileList (void*, const std::wstring&, TArrayList<std::wstring>&, std::wstring, bool, bool, bool, bool) __asm__("_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb");
extern "C" void candidateProcessMaterialName (void*, Ogre::Mesh*, Ogre::String*) __asm__("_ZN13CMeshListener19processMaterialNameEPN4Ogre4MeshEPSs");
extern "C" void candidateProcessSkeletonName (void*, Ogre::Mesh*, Ogre::String*) __asm__("_ZN13CMeshListener19processSkeletonNameEPN4Ogre4MeshEPSs");
extern "C" bool candidateHandleEvent (void*, Ogre::ScriptCompiler*, const Ogre::String&, const std::vector<Ogre::Any>&, Ogre::Any*) __asm__("_ZN15CScriptListener11handleEventEPN4Ogre14ScriptCompilerERKSsRKSt6vectorINS0_3AnyESaIS6_EEPS6_");
extern "C" void candidateAddString (void*, std::string) __asm__("_ZN10TArrayListISsE3addESs");
namespace
{

// Raw layouts used only to build identical inputs for both implementations.
struct FileSystemView
{
    FileSystemView() : resourceGroups(1), ownedObjects(10) {}

    void* vptr;
    void* safePointers;
    bool resourceGroupsAdded;
    void* modFileFilter;
    bool initialized;
    std::wstring pakFile;
    bool pakExists;
    bool needsToRecompressEverything;
    long long pakFileTime;
    void* settings;
    TArrayList<std::string> resourceGroups;
    void* massiveDataGroup;
    std::map<std::wstring, void*> dataGroups;
    void* meshListener;
    void* scriptListener;
    TArrayList<void*> ownedObjects;
};

struct ModView
{
    char unused00[0x10];
    std::string name;
    std::map<std::wstring, std::wstring> files;
    std::string resourceGroup;
    char unused50[0x18];
    std::wstring directory;
    bool enabled;
    int index;
};

struct ModFilterView
{
    void* vptr;
    void* safePointers;
    std::wstring modsFile;
    TArrayList<ModView*> mods;
    bool unused30;
    bool needsToRecompressEverything;
};

struct ArrayView
{
    void* data;
    unsigned int count;
    unsigned int capacity;
    unsigned int growBy;
};

std::string g_root;
std::wstring g_wideRoot;

std::wstring widen(const std::string& text)
{
    return std::wstring(text.begin(), text.end());
}

std::string narrow(const std::wstring& text)
{
    std::string result;
    for (size_t i = 0; i < text.size(); i++)
        result += char(text[i]);
    return result;
}

void makeDirectories(const std::string& path)
{
    for (size_t slash = path.find('/', 1); slash != std::string::npos; slash = path.find('/', slash + 1))
        mkdir(path.substr(0, slash).c_str(), 0755);
    mkdir(path.c_str(), 0755);
}

void writeFile(const std::string& relative, long when)
{
    std::string path = g_root + "/" + relative;
    makeDirectories(path.substr(0, path.rfind('/')));
    FILE* file = std::fopen(path.c_str(), "wb");
    if (file)
    {
        std::fputs("[DATA]\n[/DATA]\n", file);
        std::fclose(file);
    }
    struct utimbuf times;
    times.actime = when;
    times.modtime = when;
    utime(path.c_str(), &times);
}

int removeEntry(const char* path, const struct stat*, int, struct FTW*)
{
    return std::remove(path);
}

void createTree()
{
    // The installation: loose files under MEDIA/.
    writeFile("game/MEDIA/DISK.DAT", 1000);
    writeFile("game/MEDIA/DISK.DAT.ADM", 2000);
    writeFile("game/MEDIA/DISK.DAT.CMP", 500);
    writeFile("game/MEDIA/OLD.DAT", 3000);
    writeFile("game/MEDIA/OLD.DAT.ADM", 2000);
    writeFile("game/MEDIA/OLD.DAT.CMP", 4000);
    writeFile("game/MEDIA/DISKONLY.DAT", 1000);
    writeFile("game/MEDIA/SOUND.OGG", 1000);
    writeFile("game/MEDIA/SOUND.OGG.ADM", 2000);
    writeFile("game/MEDIA/MUSIC.WAV", 1000);
    writeFile("game/MEDIA/TEX.PNG", 1000);
    writeFile("game/MEDIA/TEX2.PNG", 1000);
    writeFile("game/MEDIA/TEX2.DDS", 1000);
    writeFile("game/MEDIA/PIC.JPG", 1000);
    writeFile("game/MEDIA/RAW.DDS", 1000);
    writeFile("game/MEDIA/DATA.CMP", 1000);
    writeFile("game/MEDIA/SUB/NESTED.DAT", 1000);
    writeFile("game/MEDIA/UNITS/UNIT.DAT", 1000);
    writeFile("game/media/lower.dat", 1000);
    writeFile("game/MEDIA/MATERIALS/STONE.PNG", 1000);
    writeFile("game/MEDIA/SHAREDTEXTURES/SHARED.PNG", 1000);

    // The mod folder; its file map below points into it.
    writeFile("mod/MEDIA/MODONLY.DAT", 1000);
    writeFile("mod/MEDIA/MODONLY.DAT.ADM", 2000);
    writeFile("mod/MEDIA/MODOLD.DAT", 3000);
    writeFile("mod/MEDIA/MODOLD.DAT.ADM", 2000);
    writeFile("mod/MEDIA/MODTEX.PNG", 1000);
    writeFile("mod/MEDIA/MODTEX2.PNG", 1000);
    writeFile("mod/MEDIA/MODTEX2.DDS", 1000);
    writeFile("mod/MEDIA/BOTH.DAT", 1000);
    writeFile("mod/MEDIA/MODCMP.DAT", 1000);
    writeFile("mod/MEDIA/MODCMP.DAT.CMP", 2000);
    writeFile("mod/MEDIA/DISKONLY.DAT.ADM", 2000);
    writeFile("mod/MEDIA/SUB/MODNESTED.DAT", 1000);

    // Archives for the resource groups.
    writeFile("rg0/MEDIA/RG.DAT", 1000);
    writeFile("rg0/MEDIA/RG.DAT.ADM", 2000);
    writeFile("rg0/MEDIA/BOTH.DAT", 1000);
    writeFile("rg0/MEDIA/RGTEX.PNG", 1000);
    writeFile("rg0/MEDIA/RGTEX2.PNG", 1000);
    writeFile("rg0/MEDIA/RGTEX2.DDS", 1000);
    writeFile("rg0/MEDIA/SUB/R.DAT", 1000);
    writeFile("rg0/MEDIA/R2.DAT.ADM", 1000);
    writeFile("general/MEDIA/GEN.DAT", 1000);
    writeFile("general/MEDIA/GEN.DAT.CMP", 1000);
    writeFile("general/MEDIA/BOTH.DAT", 1000);
    writeFile("general/MEDIA/RG.DAT", 1000);
    writeFile("general/MEDIA/SUB/G.DAT", 1000);
}

bool g_ogreReady = false;

void ensureOgre(const tlhybrid_host* host)
{
    if (!Ogre::LogManager::getSingletonPtr())
    {
        void* memory = std::calloc(1, 0x1000);
        Ogre::LogManager* logs = new (memory) Ogre::LogManager();
        logs->createLog("FileSystemTest", true, false, true);
    }
    if (!Ogre::Root::getSingletonPtr())
    {
        // Runic's OGRE may lay Root out differently from the stock header.
        void* memory = std::calloc(1, 0x10000);
        new (memory) Ogre::Root("", "", "");
    }
    Ogre::ResourceGroupManager& groups = Ogre::ResourceGroupManager::getSingleton();
    groups.addResourceLocation(g_root + "/rg0", "FileSystem", "FSTESTOBSERVED", true);
    groups.addResourceLocation(g_root + "/general", "FileSystem",
                               Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    g_ogreReady = true;
    (void)host;
}

ModView g_enabledMod;
ModView g_disabledMod;
ModFilterView g_activeFilter;
ModFilterView g_inactiveFilter;

void setupMod(ModView& mod, bool enabled)
{
    new (&mod.name) std::string(g_root + "/mod/");
    new (&mod.files) std::map<std::wstring, std::wstring>();
    new (&mod.resourceGroup) std::string("MODRG");
    new (&mod.directory) std::wstring(g_wideRoot + L"/mod/");
    mod.enabled = enabled;
    mod.index = 0;
    const wchar_t* files[] = {L"MEDIA/MODONLY.DAT", L"MEDIA/MODONLY.DAT.ADM", L"MEDIA/MODOLD.DAT",
                              L"MEDIA/MODOLD.DAT.ADM", L"MEDIA/MODTEX.PNG", L"MEDIA/MODTEX2.PNG",
                              L"MEDIA/MODTEX2.DDS", L"MEDIA/BOTH.DAT", L"MEDIA/MODCMP.DAT",
                              L"MEDIA/MODCMP.DAT.CMP", L"MEDIA/DISKONLY.DAT.ADM"};
    for (unsigned int i = 0; i < sizeof(files) / sizeof(files[0]); i++)
        mod.files[files[i]] = files[i];
}

void setupFilter(ModFilterView& filter, bool active)
{
    std::memset(&filter, 0, sizeof(filter));
    new (&filter.modsFile) std::wstring();
    new (&filter.mods) TArrayList<ModView*>(2);
    if (active)
        filter.mods.add(&g_enabledMod);
    filter.mods.add(&g_disabledMod);
}

enum
{
    GROUPS = 1,
    INITIALIZED = 2,
    PAK = 4,
    MODS = 8,
    INACTIVE_MODS = 16
};

const int kConfigs[] = {0,
                        INITIALIZED,
                        INITIALIZED | MODS,
                        INITIALIZED | INACTIVE_MODS,
                        INITIALIZED | GROUPS,
                        INITIALIZED | GROUPS | MODS,
                        INITIALIZED | GROUPS | PAK,
                        INITIALIZED | GROUPS | PAK | MODS,
                        INITIALIZED | PAK | INACTIVE_MODS,
                        INITIALIZED | PAK};

void buildSystem(FileSystemView* fs, int config)
{
    new (fs) FileSystemView;
    fs->vptr = NULL;
    fs->safePointers = NULL;
    fs->resourceGroupsAdded = (config & GROUPS) != 0;
    fs->modFileFilter = (config & MODS) ? static_cast<void*>(&g_activeFilter)
                        : (config & INACTIVE_MODS) ? static_cast<void*>(&g_inactiveFilter)
                                                   : NULL;
    fs->initialized = (config & INITIALIZED) != 0;
    fs->pakFile = g_wideRoot + L"/pak.zip";
    fs->pakExists = (config & PAK) != 0;
    fs->needsToRecompressEverything = false;
    fs->pakFileTime = 1500;
    fs->settings = NULL;
    fs->resourceGroups.add("FSTESTOBSERVED");
    fs->massiveDataGroup = NULL;
    fs->meshListener = NULL;
    fs->scriptListener = NULL;
}

void destroySystem(FileSystemView* fs)
{
    fs->~FileSystemView();
}

void prefill(CFileInfo& info, int variant)
{
    info.m_sModName = "premod";
    info.m_sResourceName = "preresource";
    info.m_sPath = L"prepath";
    info.m_eFormat = 7;
    info.m_eLocation = 9;
    info.m_sResourceGroup = "pregroup";
    info.m_bExists = (variant & 1) != 0;
}

bool sameInfo(const CFileInfo& a, const CFileInfo& b)
{
    return a.m_sModName == b.m_sModName && a.m_sResourceName == b.m_sResourceName && a.m_sPath == b.m_sPath &&
           a.m_eFormat == b.m_eFormat && a.m_eLocation == b.m_eLocation && a.m_sResourceGroup == b.m_sResourceGroup &&
           a.m_bExists == b.m_bExists;
}

void logInfo(const tlhybrid_host* host, const char* side, const CFileInfo& info)
{
    host->log("    %s: mod '%s' resource '%s' path '%s' format %d location %d group '%s' exists %d\n", side,
              info.m_sModName.c_str(), info.m_sResourceName.c_str(), narrow(info.m_sPath).c_str(), info.m_eFormat,
              info.m_eLocation, info.m_sResourceGroup.c_str(), int(info.m_bExists));
}

bool sameList(TArrayList<std::wstring>& a, TArrayList<std::wstring>& b)
{
    const ArrayView* va = reinterpret_cast<const ArrayView*>(&a);
    const ArrayView* vb = reinterpret_cast<const ArrayView*>(&b);
    if (a.size() != b.size() || va->growBy != vb->growBy)
        return false;
    for (unsigned int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void logList(const tlhybrid_host* host, const char* side, TArrayList<std::wstring>& list)
{
    host->log("    %s: %u entries, grow by %u\n", side, list.size(),
              reinterpret_cast<const ArrayView*>(&list)->growBy);
    for (unsigned int i = 0; i < list.size() && i < 12; i++)
        host->log("      %s\n", narrow(list[i]).c_str());
}

std::vector<std::wstring> pathInputs()
{
    const wchar_t* relative[] = {
        L"media/disk.dat", L"MEDIA/OLD.DAT", L"media/diskonly.dat", L"media/sound.ogg", L"media/music.wav",
        L"media/tex.png", L"media/tex2.png", L"media/pic.jpg", L"media/raw.dds", L"media/data.cmp",
        L"media/missing.dat", L"media/modonly.dat", L"media/modold.dat", L"media/modtex.png", L"media/modtex2.png",
        L"media/both.dat", L"media/modcmp.dat", L"media/rg.dat", L"media/r2.dat", L"media/gen.dat",
        L"media/rgtex.png", L"media/rgtex2.png", L"media\\sub\\nested.dat", L"media//sub/r.dat", L"", L"a",
        L"x.out"};
    std::vector<std::wstring> inputs(relative, relative + sizeof(relative) / sizeof(relative[0]));
    inputs.push_back(g_wideRoot + L"/game/media/lower.dat");
    inputs.push_back(g_wideRoot + L"/game/MEDIA/DISK.DAT");
    inputs.push_back(g_wideRoot + L"/game/media/nothere.dat");
    return inputs;
}

// Deletion recorder standing in for every object the destructor owns.
struct FakeObject
{
    void** vptr;
    int id;
};

struct DeletionLog
{
    enum { kCapacity = 32 };
    int ids[kCapacity];
    size_t total;
    unsigned int stored;
    bool overflow;

    DeletionLog() { reset(); }
    void reset()
    {
        total = stored = 0;
        overflow = false;
        std::memset(ids, 0, sizeof(ids));
    }
    void add(int id)
    {
        // Keep diagnostics bounded too, even for a repeatedly deleting candidate.
        if (total != static_cast<size_t>(-1))
            ++total;
        else
            overflow = true;
        if (stored >= kCapacity)
        {
            overflow = true;
            return;
        }
        ids[stored++] = id;
    }
    bool complete() const
    {
        return !overflow && stored <= kCapacity && total == stored;
    }
};

bool sameDeletionLog(const DeletionLog& a, const DeletionLog& b)
{
    // Reject unobserved tails before choosing any byte count for memcmp.
    return a.complete() && b.complete() && a.total == b.total &&
           std::memcmp(a.ids, b.ids, a.stored * sizeof(a.ids[0])) == 0;
}

DeletionLog g_deleted;

void fakeDestroy(FakeObject*) {}

void fakeDelete(FakeObject* self)
{
    g_deleted.add(self->id);
}

void* g_fakeVtable[4] = {reinterpret_cast<void*>(&fakeDestroy), reinterpret_cast<void*>(&fakeDelete), NULL, NULL};

// Ogre::Resource::getName is virtual; the listeners only call that on a mesh.
std::string g_meshName;

const std::string& fakeGetName(void*)
{
    return g_meshName;
}

void* g_fakeMeshVtable[64];

} // namespace


namespace {
struct Case{unsigned op,seed;};
void infoCapture(const CFileInfo&i,autotest::Capture&out){out.addText(i.m_sModName);out.addText(i.m_sResourceName);out.addText(i.m_sPath);out.add(&i.m_eFormat,4);out.add(&i.m_eLocation,4);out.addText(i.m_sResourceGroup);out.add(&i.m_bExists,1);}
void listCapture(TArrayList<std::wstring>&list,autotest::Capture&out){ArrayView*v=reinterpret_cast<ArrayView*>(&list);out.add(&v->count,12);if(v->count>2048)_exit(53);for(unsigned i=0;i<list.size();++i)out.addText(list[i]);}
void body(Case&c,bool ours,autotest::Capture&out){
 unsigned long long memory[0xc0/8];std::memset(memory,0xa5,sizeof(memory));FileSystemView*fs=reinterpret_cast<FileSystemView*>(memory);
 if(c.op==0){
  new(fs)FileSystemView;originalCoreConstruct(fs);FakeObject objects[8];for(int i=0;i<8;++i){objects[i].vptr=g_fakeVtable;objects[i].id=i+1;}
  fs->resourceGroupsAdded=true;fs->modFileFilter=c.seed&1?&objects[0]:NULL;fs->initialized=true;fs->pakFile=L"pak.zip";fs->pakExists=true;fs->needsToRecompressEverything=false;fs->pakFileTime=c.seed+5;fs->settings=NULL;
  fs->resourceGroups.add("ZIP0");if(c.seed&16)fs->resourceGroups.add("ZIP");fs->massiveDataGroup=c.seed&2?&objects[1]:NULL;fs->dataGroups[L"MEDIA/A.DAT"]=&objects[7];fs->meshListener=c.seed&4?&objects[2]:NULL;fs->scriptListener=c.seed&8?&objects[3]:NULL;
  for(unsigned i=0;i<c.seed%5;++i)fs->ownedObjects.add(i==2?NULL:&objects[4+i%3]);g_pFileSystem=reinterpret_cast<CFileSystem*>(fs);g_deleted.reset();
  autotest::invoke(out,ours?candidateDestroy:originalDestroy,static_cast<void*>(fs));if(!g_deleted.complete()){out.issue=autotest::Capture::Overflow;return;}out.add(&g_deleted.stored,4);out.add(g_deleted.ids,4*g_deleted.stored);unsigned singleton=g_pFileSystem==NULL;out.add(&singleton,4);out.add(memory,sizeof(memory));out.addHeapInUse();return;
 }
 unsigned config=c.op==2?c.seed/60:c.op==3?c.seed/240:c.op==5?c.seed/240:1;
 buildSystem(fs,kConfigs[config%10]);
 if(c.op==1){
  const char*mods[]={"","mod/","nowhere/"};const wchar_t*paths[]={L"MEDIA/DISK.DAT",L"MEDIA/OLD.DAT.ADM",L"MEDIA/NONE.DAT",L"MEDIA/MODONLY.DAT"};const int locations[]={FILE_LOCATION_DISK,FILE_LOCATION_PAK,FILE_LOCATION_RESOURCE_GROUP,FILE_LOCATION_NONE};const long long times[]={500,1000,2500,-1};
  unsigned bits=c.seed*2654435761u;CFileInfo a,b;a.m_bExists=(bits>>1)%5!=0;b.m_bExists=(bits>>4)%5!=0;std::string ma=mods[(bits>>7)%3],mb=mods[(bits>>9)%3];a.m_sModName=ma=="mod/"?g_root+"/mod/":ma;b.m_sModName=mb=="mod/"?g_root+"/mod/":mb;a.m_sPath=paths[(bits>>11)%4];b.m_sPath=paths[(bits>>13)%4];a.m_eLocation=locations[(bits>>15)%4];b.m_eLocation=locations[(bits>>17)%4];if((bits>>19)%3==0)a.m_sPath=g_wideRoot+L"/game/"+a.m_sPath;fs->pakFileTime=times[(bits>>21)%4];
  bool(*fn)(void*,CFileInfo&,CFileInfo&)=ours?candidateIsNewer:originalIsNewer;if(!autotest::beginInvocation(out,fn))return;bool result=fn(fs,a,b);out.callCompleted=1;out.add(&result,1);infoCapture(a,out);infoCapture(b,out);
 }else if(c.op==2||c.op==3){
  std::vector<std::wstring>inputs=pathInputs();unsigned flags=c.op==2?c.seed%2:c.seed%8,index=(c.seed/(c.op==2?2:8))%inputs.size();CFileInfo info;prefill(info,flags);
  if(c.op==2){int(*fn)(void*,const std::wstring&,CFileInfo&,bool)=ours?candidateGetAbsolutePath:originalGetAbsolutePath;if(!autotest::beginInvocation(out,fn))return;int result=fn(fs,inputs[index],info,flags!=0);out.callCompleted=1;out.add(&result,4);}
  else{void(*fn)(void*,const std::wstring&,CFileInfo&,bool,bool,bool)=ours?candidateGetFileInfo:originalGetFileInfo;if(!autotest::beginInvocation(out,fn))return;fn(fs,inputs[index],info,flags&1,flags&2,flags&4);out.callCompleted=1;}
  infoCapture(info,out);out.addText(inputs[index]);
 }else if(c.op==4){
  const char*dirs[][2]={{"MEDIA/","*.DAT"},{"MEDIA/","*"},{"MEDIA/SUB/","*.DAT"},{"NOPE/","*.DAT"},{"MEDIA/","*.ADM"},{"MEDIA/","RG"}};const char*groups[]={"","FSTESTOBSERVED","General"};
  unsigned d=(c.seed/16)%6,g=(c.seed/96)%3,flags=c.seed%16;fs->resourceGroupsAdded=true;fs->pakExists=c.seed>=288;TArrayList<std::wstring>list(3);if(flags&8)list.add(L"MEDIA/RG.DAT");std::string dir=dirs[d][0],pattern=dirs[d][1],group=groups[g];
  void(*fn)(void*,TArrayList<std::wstring>&,std::string&,std::string&,bool,bool,bool,const std::string&)=ours?candidateGetFilesInDirectory:originalGetFilesInDirectory;if(!autotest::beginInvocation(out,fn))return;fn(fs,list,dir,pattern,flags&1,flags&2,flags&4,group);out.callCompleted=1;
  listCapture(list,out);out.addText(dir);out.addText(pattern);out.addText(group);
 }else{
  const wchar_t*dirs[]={L"",L"MEDIA/",L"media/",L"MEDIA\\SUB",L"MEDIA/SUB/"};const wchar_t*patterns[]={L"*.DAT",L"*",L"*.dat"};unsigned flags=c.seed%16,d=(c.seed/48)%5,p=(c.seed/16)%3;TArrayList<std::wstring>list(4);std::wstring dir=dirs[d],pattern=patterns[p];
  unsigned(*fn)(void*,const std::wstring&,TArrayList<std::wstring>&,std::wstring,bool,bool,bool,bool)=ours?candidateGetFileList:originalGetFileList;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(fs,dir,list,pattern,flags&1,flags&2,flags&4,flags&8);out.callCompleted=1;out.add(&result,4);listCapture(list,out);out.addText(dir);out.addText(pattern);
 }
 out.add(memory,sizeof(memory));out.addText(fs->pakFile);unsigned n=fs->resourceGroups.size();out.add(&n,4);for(unsigned i=0;i<n;++i)out.addText(fs->resourceGroups[i]);destroySystem(fs);
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){
 char pattern[]="/tmp/opencode/fs-observed-XXXXXX";mkdir("/tmp/opencode",0755);if(!mkdtemp(pattern))return 1;g_root=pattern;g_wideRoot=widen(g_root);createTree();
 char savedDirectory[4096];if(!getcwd(savedDirectory,sizeof(savedDirectory)))return 1;FILESYSTEM::GetApplicationPath();std::wstring savedApplicationPath=g_applicationPathCache;g_applicationPathCache=g_wideRoot+L"/game/";if(chdir((g_root+"/game").c_str()))return 1;
 ensureOgre(host);setupMod(g_enabledMod,true);setupMod(g_disabledMod,false);setupFilter(g_activeFilter,true);setupFilter(g_inactiveFilter,false);
 const uint64_t addresses[]={(uint64_t)(uintptr_t)originalDestroy,(uint64_t)(uintptr_t)originalIsNewer,(uint64_t)(uintptr_t)originalGetAbsolutePath,(uint64_t)(uintptr_t)originalGetFileInfo,(uint64_t)(uintptr_t)originalGetFilesInDirectory,(uint64_t)(uintptr_t)originalGetFileList};
 const unsigned count[]={32,1024,600,2400,576,2400};autotest::Coverage coverage(name,addresses[op]);int failed=0;
 for(unsigned n=0;n<count[op];++n){Case c={op,n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){size_t k=0;while(k<a.capture.length&&k<b.capture.length&&a.capture.data[k]==b.capture.data[k])++k;host->log("    filesystem op %u case %u status %d/%d first %lu bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)k,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failed=1;break;}}
 coverage.report(host);if(chdir(savedDirectory))failed=1;g_applicationPathCache=savedApplicationPath;
 Ogre::ResourceGroupManager&groups=Ogre::ResourceGroupManager::getSingleton();groups.removeResourceLocation(g_root+"/rg0","FSTESTOBSERVED");groups.removeResourceLocation(g_root+"/general",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
 nftw(g_root.c_str(),removeEntry,16,FTW_DEPTH|FTW_PHYS);return failed;
}
}
TL_TEST(filesystem_destroy_observed){return run(host,0,"filesystem_destroy_observed");}
TL_TEST(filesystem_newer_observed){return run(host,1,"filesystem_newer_observed");}
TL_TEST(filesystem_absolute_observed){return run(host,2,"filesystem_absolute_observed");}
TL_TEST(filesystem_info_observed){return run(host,3,"filesystem_info_observed");}
TL_TEST(filesystem_directory_observed){return run(host,4,"filesystem_directory_observed");}
TL_TEST(filesystem_list_observed){return run(host,5,"filesystem_list_observed");}
