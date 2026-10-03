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
#include "HybridTest.h"

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
    groups.addResourceLocation(g_root + "/rg0", "FileSystem", "FSTEST0", true);
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
    fs->resourceGroups.add("FSTEST0");
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

int g_deleted[32];
int g_deletedCount;

void fakeDestroy(FakeObject*) {}

void fakeDelete(FakeObject* self)
{
    if (g_deletedCount < 32)
        g_deleted[g_deletedCount] = self->id;
    g_deletedCount++;
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

TL_TEST(FileSystem_layout)
{
    int failures = 0;
    static FileSystemView view;
    char* base = reinterpret_cast<char*>(&view);
    TL_CHECK(failures, sizeof(CFileSystem) == 0xc0);
    TL_CHECK(failures, sizeof(FileSystemView) == 0xc0);
    TL_CHECK(failures, reinterpret_cast<char*>(&view.pakFile) - base == 0x28);
    TL_CHECK(failures, reinterpret_cast<char*>(&view.pakFileTime) - base == 0x38);
    TL_CHECK(failures, reinterpret_cast<char*>(&view.resourceGroups) - base == 0x48);
    TL_CHECK(failures, reinterpret_cast<char*>(&view.dataGroups) - base == 0x68);
    TL_CHECK(failures, reinterpret_cast<char*>(&view.ownedObjects) - base == 0xa8);
    TL_CHECK(failures, sizeof(CFileInfo) == 0x30);
    static ModView mod;
    char* modBase = reinterpret_cast<char*>(&mod);
    TL_CHECK(failures, reinterpret_cast<char*>(&mod.files) - modBase == 0x18);
    TL_CHECK(failures, reinterpret_cast<char*>(&mod.resourceGroup) - modBase == 0x48);
    TL_CHECK(failures, reinterpret_cast<char*>(&mod.directory) - modBase == 0x68);
    TL_CHECK(failures, reinterpret_cast<char*>(&mod.index) - modBase == 0x74);
    static ModFilterView filter;
    TL_CHECK(failures, reinterpret_cast<char*>(&filter.mods) - reinterpret_cast<char*>(&filter) == 0x18);
    TL_CHECK(failures,
             reinterpret_cast<char*>(&filter.needsToRecompressEverything) - reinterpret_cast<char*>(&filter) == 0x31);
    return failures;
}

TL_TEST(FileSystem_destructor_shadow)
{
    int failures = 0;
    CFileSystem* savedSingleton = g_pFileSystem;
    for (int variant = 0; variant < 16; variant++)
    {
        int logs[2][32];
        int counts[2];
        FakeObject objects[2][8];
        unsigned char after[2][0xc0];
        for (int side = 0; side < 2; side++)
        {
            static char buffer[0xc0] __attribute__((aligned(16)));
            FileSystemView* fs = reinterpret_cast<FileSystemView*>(buffer);
            new (fs) FileSystemView;
            originalCoreConstruct(fs);
            for (int i = 0; i < 8; i++)
            {
                objects[side][i].vptr = g_fakeVtable;
                objects[side][i].id = i + 1;
            }
            fs->resourceGroupsAdded = true;
            fs->modFileFilter = (variant & 1) ? &objects[side][0] : NULL;
            fs->initialized = true;
            fs->pakFile = L"pak.zip";
            fs->pakExists = true;
            fs->needsToRecompressEverything = false;
            fs->pakFileTime = 5;
            fs->settings = NULL;
            fs->resourceGroups.add("ZIP0");
            fs->resourceGroups.add("ZIP");
            fs->massiveDataGroup = (variant & 2) ? &objects[side][1] : NULL;
            fs->dataGroups[L"MEDIA/A.DAT"] = &objects[side][7];
            fs->meshListener = (variant & 4) ? &objects[side][2] : NULL;
            fs->scriptListener = (variant & 8) ? &objects[side][3] : NULL;
            for (int i = 0; i < variant % 5; i++)
                fs->ownedObjects.add(i == 2 ? NULL : &objects[side][4 + (i % 3)]);
            g_pFileSystem = reinterpret_cast<CFileSystem*>(fs);
            g_deletedCount = 0;
            if (side == 0)
                originalDestroy(fs);
            else
                reinterpret_cast<CFileSystem*>(fs)->CFileSystem::~CFileSystem();
            counts[side] = g_deletedCount;
            std::memcpy(logs[side], g_deleted, sizeof(g_deleted));
            std::memcpy(after[side], buffer, sizeof(buffer));
            TL_CHECK(failures, g_pFileSystem == NULL);
        }
        TL_CHECK(failures, counts[0] == counts[1]);
        TL_CHECK(failures, std::memcmp(logs[0], logs[1], counts[0] * sizeof(int)) == 0);
        // Pointer fields the destructor clears (the deleted objects differ per side).
        const size_t cleared[] = {0x18, 0x60, 0x98, 0xa0, 0xa8};
        for (unsigned int i = 0; i < sizeof(cleared) / sizeof(cleared[0]); i++)
            TL_CHECK(failures, std::memcmp(after[0] + cleared[i], after[1] + cleared[i], 8) == 0);
        TL_CHECK(failures, std::memcmp(after[0] + 0xb0, after[1] + 0xb0, 0xc) == 0);
        if (failures)
        {
            host->log("    variant %d: deleted %d vs %d\n", variant, counts[0], counts[1]);
            break;
        }
    }
    g_pFileSystem = savedSingleton;
    return failures;
}

TL_TEST(FileSystem_resolve_shadow)
{
    int failures = 0;
    char pattern[] = "/tmp/opencode/fstest-XXXXXX";
    mkdir("/tmp/opencode", 0755);
    if (!mkdtemp(pattern))
    {
        host->log("    cannot create a temporary directory\n");
        return 1;
    }
    g_root = pattern;
    g_wideRoot = widen(g_root);
    createTree();

    char savedDirectory[4096];
    if (!getcwd(savedDirectory, sizeof(savedDirectory)))
        savedDirectory[0] = 0;
    FILESYSTEM::GetApplicationPath();
    std::wstring savedApplicationPath = g_applicationPathCache;
    g_applicationPathCache = g_wideRoot + L"/game/";
    if (chdir((g_root + "/game").c_str()) != 0)
        failures++;

    ensureOgre(host);
    setupMod(g_enabledMod, true);
    setupMod(g_disabledMod, false);
    setupFilter(g_activeFilter, true);
    setupFilter(g_inactiveFilter, false);

    static char buffers[2][0xc0] __attribute__((aligned(16)));
    FileSystemView* systems[2] = {reinterpret_cast<FileSystemView*>(buffers[0]),
                                  reinterpret_cast<FileSystemView*>(buffers[1])};
    std::vector<std::wstring> inputs = pathInputs();
    int calls = 0;

    // getAbsolutePath
    for (unsigned int c = 0; c < sizeof(kConfigs) / sizeof(kConfigs[0]) && failures == 0; c++)
    {
        buildSystem(systems[0], kConfigs[c]);
        buildSystem(systems[1], kConfigs[c]);
        for (unsigned int i = 0; i < inputs.size() && failures == 0; i++)
        {
            for (int modsOnly = 0; modsOnly < 2 && failures == 0; modsOnly++)
            {
                CFileInfo a, b;
                prefill(a, i + modsOnly);
                prefill(b, i + modsOnly);
                int ra = originalGetAbsolutePath(systems[0], inputs[i], a, modsOnly != 0);
                int rb = reinterpret_cast<CFileSystem*>(systems[1])->getAbsolutePath(inputs[i], b, modsOnly != 0);
                calls++;
                TL_CHECK(failures, ra == rb);
                TL_CHECK(failures, sameInfo(a, b));
                if (failures)
                {
                    host->log("    getAbsolutePath config %d '%s' modsOnly %d: %d vs %d\n", kConfigs[c],
                              narrow(inputs[i]).c_str(), modsOnly, ra, rb);
                    logInfo(host, "original", a);
                    logInfo(host, "decomp", b);
                }
            }
        }
        destroySystem(systems[0]);
        destroySystem(systems[1]);
    }

    // getFileInfo, which also drives getAbsolutePath and fileIsNewerOrEqualTo
    for (unsigned int c = 0; c < sizeof(kConfigs) / sizeof(kConfigs[0]) && failures == 0; c++)
    {
        buildSystem(systems[0], kConfigs[c]);
        buildSystem(systems[1], kConfigs[c]);
        for (unsigned int i = 0; i < inputs.size() && failures == 0; i++)
        {
            for (int flags = 0; flags < 8 && failures == 0; flags++)
            {
                bool compiled = flags & 1, binary = flags & 2, modsOnly = flags & 4;
                CFileInfo a, b;
                prefill(a, flags);
                prefill(b, flags);
                originalGetFileInfo(systems[0], inputs[i], a, compiled, binary, modsOnly);
                reinterpret_cast<CFileSystem*>(systems[1])->getFileInfo(inputs[i], b, compiled, binary, modsOnly);
                calls++;
                TL_CHECK(failures, sameInfo(a, b));
                if (failures)
                {
                    host->log("    getFileInfo config %d '%s' flags %d\n", kConfigs[c], narrow(inputs[i]).c_str(),
                              flags);
                    logInfo(host, "original", a);
                    logInfo(host, "decomp", b);
                }
            }
        }
        destroySystem(systems[0]);
        destroySystem(systems[1]);
    }

    // fileIsNewerOrEqualTo on its own
    {
        const char* modNames[] = {"", "mod/", "nowhere/"};
        const wchar_t* paths[] = {L"MEDIA/DISK.DAT", L"MEDIA/OLD.DAT.ADM", L"MEDIA/NONE.DAT", L"MEDIA/MODONLY.DAT"};
        const int locations[] = {FILE_LOCATION_DISK, FILE_LOCATION_PAK, FILE_LOCATION_RESOURCE_GROUP,
                                 FILE_LOCATION_NONE};
        const long long pakTimes[] = {500, 1000, 2500, -1};
        for (int step = 0; step < 4000 && failures == 0; step++)
        {
            unsigned int r = unsigned(step) * 2654435761u;
            CFileInfo file, other;
            file.m_bExists = (r >> 1) % 5 != 0;
            other.m_bExists = (r >> 4) % 5 != 0;
            std::string fileMod = modNames[(r >> 7) % 3];
            std::string otherMod = modNames[(r >> 9) % 3];
            file.m_sModName = fileMod == "mod/" ? g_root + "/mod/" : fileMod;
            other.m_sModName = otherMod == "mod/" ? g_root + "/mod/" : otherMod;
            file.m_sPath = paths[(r >> 11) % 4];
            other.m_sPath = paths[(r >> 13) % 4];
            file.m_eLocation = locations[(r >> 15) % 4];
            other.m_eLocation = locations[(r >> 17) % 4];
            if ((r >> 19) % 3 == 0)
                file.m_sPath = g_wideRoot + L"/game/" + file.m_sPath;
            buildSystem(systems[0], INITIALIZED);
            buildSystem(systems[1], INITIALIZED);
            systems[0]->pakFileTime = systems[1]->pakFileTime = pakTimes[(r >> 21) % 4];
            bool ra = originalIsNewer(systems[0], file, other);
            bool rb = reinterpret_cast<CFileSystem*>(systems[1])->fileIsNewerOrEqualTo(file, other);
            calls++;
            TL_CHECK(failures, ra == rb);
            if (failures)
                host->log("    fileIsNewerOrEqualTo step %d: %d vs %d\n", step, int(ra), int(rb));
            destroySystem(systems[0]);
            destroySystem(systems[1]);
        }
    }

    // getFilesInDirectory
    {
        const char* directories[][2] = {{"MEDIA/", "*.DAT"}, {"MEDIA/", "*"}, {"MEDIA/SUB/", "*.DAT"},
                                        {"NOPE/", "*.DAT"}, {"MEDIA/", "*.ADM"}, {"MEDIA/", "RG"}};
        const char* groups[] = {"", "FSTEST0", "General"};
        for (int config = 0; config < 2 && failures == 0; config++)
        {
            buildSystem(systems[0], INITIALIZED | GROUPS | (config ? PAK : 0));
            buildSystem(systems[1], INITIALIZED | GROUPS | (config ? PAK : 0));
            for (unsigned int d = 0; d < sizeof(directories) / sizeof(directories[0]) && failures == 0; d++)
            {
                for (int g = 0; g < 3 && failures == 0; g++)
                {
                    for (int flags = 0; flags < 16 && failures == 0; flags++)
                    {
                        TArrayList<std::wstring> la(3), lb(3);
                        if (flags & 8)
                        {
                            la.add(L"MEDIA/RG.DAT");
                            lb.add(L"MEDIA/RG.DAT");
                        }
                        std::string dirA = directories[d][0], dirB = directories[d][0];
                        std::string patA = directories[d][1], patB = directories[d][1];
                        std::string group = groups[g];
                        originalGetFilesInDirectory(systems[0], la, dirA, patA, flags & 1, flags & 2, flags & 4, group);
                        reinterpret_cast<CFileSystem*>(systems[1])
                            ->getFilesInDirectory(lb, dirB, patB, flags & 1, flags & 2, flags & 4, group);
                        calls++;
                        TL_CHECK(failures, sameList(la, lb));
                        TL_CHECK(failures, dirA == dirB && patA == patB);
                        if (failures)
                        {
                            host->log("    getFilesInDirectory pak %d '%s%s' group '%s' flags %d\n", config,
                                      directories[d][0], directories[d][1], groups[g], flags);
                            logList(host, "original", la);
                            logList(host, "decomp", lb);
                        }
                    }
                }
            }
            destroySystem(systems[0]);
            destroySystem(systems[1]);
        }
    }

    // getFileList
    {
        const wchar_t* directories[] = {L"", L"MEDIA/", L"media/", L"MEDIA\\SUB", L"MEDIA/SUB/"};
        const wchar_t* patterns[] = {L"*.DAT", L"*", L"*.dat"};
        for (unsigned int c = 0; c < sizeof(kConfigs) / sizeof(kConfigs[0]) && failures == 0; c++)
        {
            buildSystem(systems[0], kConfigs[c]);
            buildSystem(systems[1], kConfigs[c]);
            for (unsigned int d = 0; d < sizeof(directories) / sizeof(directories[0]) && failures == 0; d++)
            {
                for (unsigned int p = 0; p < sizeof(patterns) / sizeof(patterns[0]) && failures == 0; p++)
                {
                    for (int flags = 0; flags < 16 && failures == 0; flags++)
                    {
                        TArrayList<std::wstring> la(4), lb(4);
                        unsigned int ra = originalGetFileList(systems[0], directories[d], la, patterns[p], flags & 1,
                                                              flags & 2, flags & 4, flags & 8);
                        unsigned int rb = reinterpret_cast<CFileSystem*>(systems[1])->getFileList(
                            directories[d], lb, patterns[p], flags & 1, flags & 2, flags & 4, flags & 8);
                        calls++;
                        TL_CHECK(failures, ra == rb);
                        TL_CHECK(failures, sameList(la, lb));
                        if (failures)
                        {
                            host->log("    getFileList config %d '%s' '%s' flags %d: %u vs %u\n", kConfigs[c],
                                      narrow(directories[d]).c_str(), narrow(patterns[p]).c_str(), flags, ra, rb);
                            logList(host, "original", la);
                            logList(host, "decomp", lb);
                        }
                    }
                }
            }
            destroySystem(systems[0]);
            destroySystem(systems[1]);
        }
    }

    // CScriptListener::handleEvent resolves textures through g_pFileSystem.
    {
        CFileSystem* savedSingleton = g_pFileSystem;
        buildSystem(systems[0], 0);
        g_pFileSystem = reinterpret_cast<CFileSystem*>(systems[0]);
        const char* events[] = {"processMaterialName", "processTextureNames", "createObject", ""};
        const char* basePaths[] = {"media/materials/", "Media/Materials/", "levels/town/", "MEDIA/X/", "a/b/c/d/"};
        const char* names[] = {"stone.png", "stone.tga", "stone.dds", "shared.jpg", "missing.png", "ab",
                               "../materials/stone.png", "../../x.png", "..\\y.png", "MAT_ROCK", ""};
        static char compiler[0x100] __attribute__((aligned(16)));
        std::memset(compiler, 0, sizeof(compiler));
        std::string* basePath = new (compiler + 0x40) std::string();
        for (unsigned int e = 0; e < 4 && failures == 0; e++)
        {
            for (unsigned int b = 0; b < 5 && failures == 0; b++)
            {
                for (unsigned int n = 0; n < sizeof(names) / sizeof(names[0]) && failures == 0; n++)
                {
                    *basePath = basePaths[b];
                    Ogre::String nameA = names[n], nameB = names[n];
                    std::vector<Ogre::Any> argsA, argsB;
                    argsA.push_back(Ogre::Any(&nameA));
                    argsB.push_back(Ogre::Any(&nameB));
                    std::string event = events[e];
                    bool ra = originalHandleEvent(NULL, reinterpret_cast<Ogre::ScriptCompiler*>(compiler), event,
                                                  argsA, NULL);
                    bool rb =
                        ourHandleEvent(NULL, reinterpret_cast<Ogre::ScriptCompiler*>(compiler), event, argsB, NULL);
                    calls++;
                    TL_CHECK(failures, ra == rb);
                    TL_CHECK(failures, nameA == nameB);
                    TL_CHECK(failures, *basePath == basePaths[b]);
                    if (failures)
                        host->log("    handleEvent '%s' base '%s' name '%s': %d '%s' vs %d '%s'\n", events[e],
                                  basePaths[b], names[n], int(ra), nameA.c_str(), int(rb), nameB.c_str());
                }
            }
        }
        basePath->~basic_string();
        g_pFileSystem = savedSingleton;
        destroySystem(systems[0]);
    }

    // CMeshListener
    {
        g_fakeMeshVtable[0xc8 / sizeof(void*)] = reinterpret_cast<void*>(&fakeGetName);
        void* mesh[2] = {g_fakeMeshVtable, NULL};
        const char* meshNames[] = {"MEDIA/MODELS/ROCK.MESH", "/data/MEDIA/MODELS/ROCK.MESH",
                                   "media/MEDIA/a.mesh", "ROCK.MESH", "MEDIA/ROCK.MESH", "ab/c.mesh", ""};
        const char* names[] = {"ROCK.MATERIAL", "", "SKEL/ROCK.SKELETON"};
        for (unsigned int m = 0; m < sizeof(meshNames) / sizeof(meshNames[0]) && failures == 0; m++)
        {
            for (unsigned int n = 0; n < 3 && failures == 0; n++)
            {
                g_meshName = meshNames[m];
                Ogre::String a = names[n], b = names[n], c = names[n], d = names[n];
                Ogre::Mesh* fakeMesh = reinterpret_cast<Ogre::Mesh*>(mesh);
                int threw = 0;
                try { originalProcessMaterialName(NULL, fakeMesh, &a); } catch (...) { threw |= 1; }
                try { ourProcessMaterialName(NULL, fakeMesh, &b); } catch (...) { threw |= 2; }
                try { originalProcessSkeletonName(NULL, fakeMesh, &c); } catch (...) { threw |= 4; }
                try { ourProcessSkeletonName(NULL, fakeMesh, &d); } catch (...) { threw |= 8; }
                calls += 2;
                TL_CHECK(failures, a == b);
                TL_CHECK(failures, c == d);
                TL_CHECK(failures, threw == 0 || threw == 15);
                if (failures)
                    host->log("    mesh '%s' name '%s': '%s' vs '%s', '%s' vs '%s'\n", meshNames[m], names[n],
                              a.c_str(), b.c_str(), c.c_str(), d.c_str());
            }
        }
    }

    if (chdir(savedDirectory) != 0)
        failures++;
    g_applicationPathCache = savedApplicationPath;
    nftw(g_root.c_str(), removeEntry, 16, FTW_DEPTH | FTW_PHYS);
    if (failures == 0)
        host->log("    %d calls compared\n", calls);
    return failures;
}

TL_TEST(FileSystem_stringListAdd_shadow)
{
    int failures = 0;
    for (unsigned int growBy = 1; growBy < 5 && failures == 0; growBy++)
    {
        TArrayList<std::string> a(growBy), b(growBy);
        for (int i = 0; i < 40 && failures == 0; i++)
        {
            char text[32];
            std::sprintf(text, "entry %d", i * 7);
            originalAddString(&a, text);
            ourAddString(&b, text);
            const ArrayView* va = reinterpret_cast<const ArrayView*>(&a);
            const ArrayView* vb = reinterpret_cast<const ArrayView*>(&b);
            TL_CHECK(failures, va->count == vb->count && va->capacity == vb->capacity && va->growBy == vb->growBy);
            for (unsigned int j = 0; j < a.size() && failures == 0; j++)
                TL_CHECK(failures, a[j] == b[j]);
        }
    }
    return failures;
}
