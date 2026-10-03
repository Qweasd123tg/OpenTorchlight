#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <map>
#include <string>

#include <OgreDataStream.h>

#include "EmptyStrings.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CDataGroup;
class CMeshListener;
class CModFileFilter;
class CScriptListener;
class CSettings;

enum EFileFormat
{
    FILE_FORMAT_COMPILED,  // ".CMP" next to the source file
    FILE_FORMAT_BINARY,    // ".ADM" next to the source file
    FILE_FORMAT_TEXT,
    FILE_FORMAT_RAW,       // layouts and sounds, never compiled
    FILE_FORMAT_UNKNOWN
};

enum EFileLocation
{
    FILE_LOCATION_DISK,
    FILE_LOCATION_PAK,
    FILE_LOCATION_RESOURCE_GROUP,
    FILE_LOCATION_NONE
};

// Where a game file was found and how to open it.
class CFileInfo
{
public:
    CFileInfo()
        : m_sResourceName(EMPTY_STRING), m_sPath(EMPTY_WSTRING), m_eFormat(FILE_FORMAT_UNKNOWN),
          m_eLocation(FILE_LOCATION_NONE), m_bExists(false)
    {
    }

    std::string m_sModName;
    std::string m_sResourceName;
    std::wstring m_sPath;
    int m_eFormat;
    int m_eLocation;
    std::string m_sResourceGroup;
    bool m_bExists;
};

// Resolves game files across mods, the pak archives listed in resources.cfg
// and the loose files of the installation, and owns the massive data group
// compiled from the media folder.
class CFileSystem : public CRunicCore
{
public:
    CFileSystem(bool bRebuildMassFile);
    virtual ~CFileSystem();

    static CFileSystem* getSingleton();

    bool getNeedsToRecompressEverything();
    void clean();
    unsigned int getNumberOfMods();
    void getEnabledModNames(TArrayList<std::wstring>* names);
    void getModNames(TArrayList<std::wstring>* names);
    Ogre::DataStreamPtr getDataStream(CFileInfo& info);
    bool fileIsNewerOrEqualTo(CFileInfo& file, CFileInfo& other);
    void reload();
    CDataGroup* getDataGroup(const std::wstring& name);
    int getAbsolutePath(const std::wstring& path, CFileInfo& info, bool bModsOnly);
    void getFileInfo(const std::wstring& path, CFileInfo& info, bool bCompiled, bool bBinary, bool bModsOnly);
    void getFilesInDirectory(TArrayList<std::wstring>& files, std::string& directory, std::string& pattern,
                             bool bRecursive, bool bAllowDuplicates, bool bStripExtension,
                             const std::string& resourceGroup);
    unsigned int getFileList(const std::wstring& directory, TArrayList<std::wstring>& files, std::wstring pattern,
                             bool bRecursive, bool bStripExtension, bool bModsOnly, bool bSkipMods);
    void buildMassiveDataGroup();

private:
    bool m_bResourceGroupsAdded;
    CModFileFilter* m_pModFileFilter;
    bool m_bInitialized;
    std::wstring m_sPakFile;
    bool m_bPakExists;
    bool m_bNeedsToRecompressEverything;
    long long m_iPakFileTime;
    CSettings* m_pSettings;
    TArrayList<std::string> m_ResourceGroups;
    CDataGroup* m_pMassiveDataGroup;
    std::map<std::wstring, CDataGroup*> m_DataGroups;
    CMeshListener* m_pMeshListener;
    CScriptListener* m_pScriptListener;
    TArrayList<CRunicCore*> m_OwnedObjects;
};

extern CFileSystem* g_pFileSystem;

#endif
