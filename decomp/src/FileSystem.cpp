#include "EmptyStrings.h"
#include "FileSystem.h"

#include <vector>

#include <OgreConfigFile.h>
#include <OgreLogManager.h>
#include <OgreMaterialManager.h>
#include <OgreMeshManager.h>
#include <OgreMeshSerializer.h>
#include <OgreResourceGroupManager.h>
#include <OgreScriptCompiler.h>
#include <OgreUTFString.h>

#include "BinaryStyle.h"
#include "DataGroup.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "MasterResourceManager.h"
#include "ModFileFilter.h"
#include "ParticleUniverseConstants.h"
#include "Settings.h"
#include "StringUtilities.h"

CFileSystem* g_pFileSystem = NULL;

const std::string g_PakResourceName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

// Runic's OGRE build extends two classes beyond the stock 1.6.5 headers: a
// ResourceGroupManager flag (read by attemptToFindGroupContainingResource)
// raised while mods are active, and ScriptCompiler::getBasePath().
static inline bool& resourceGroupManagerModsActive()
{
    return *reinterpret_cast<bool*>(reinterpret_cast<char*>(&Ogre::ResourceGroupManager::getSingleton()) + 0x110);
}

const Ogre::String& scriptCompilerBasePath(const Ogre::ScriptCompiler* compiler)
    __asm__("_ZNK4Ogre14ScriptCompiler11getBasePathEv");

#define VK_SHIFT 0x10

// True when the upper-case path already starts below the MEDIA folder.
static inline bool isMediaPath(const Ogre::String& path)
{
    const char* text = path.c_str();
    return text[0] == 'M' && text[1] == 'E' && text[2] == 'D' && text[3] == 'I' && text[4] == 'A';
}

// Makes mesh material and skeleton references relative to the MEDIA folder
// of the mesh.
class CMeshListener : public CRunicCore, public Ogre::MeshSerializerListener
{
public:
    virtual void processMaterialName(Ogre::Mesh* mesh, Ogre::String* name)
    {
        Ogre::String path = FILESYSTEM::RemoveFileName(mesh->getName());
        if (path.length() > 5 && !isMediaPath(path))
        {
            unsigned int media = path.find("MEDIA");
            path = path.substr(media, path.length() - media);
        }
        *name = path + *name;
    }

    virtual void processSkeletonName(Ogre::Mesh* mesh, Ogre::String* name)
    {
        Ogre::String path = FILESYSTEM::RemoveFileName(mesh->getName());
        if (path.length() > 5 && !isMediaPath(path))
        {
            unsigned int media = path.find("MEDIA");
            path = path.substr(media, path.length() - media);
        }
        *name = path + *name;
    }
};

// Resolves material and texture references of material scripts relative to
// the script folder, falling back to MEDIA/SHAREDTEXTURES/.
class CScriptListener : public CRunicCore, public Ogre::ScriptCompilerListener
{
public:
    virtual bool handleEvent(Ogre::ScriptCompiler* compiler, const Ogre::String& name,
                             const std::vector<Ogre::Any>& args, Ogre::Any* retval)
    {
        if (name == "processMaterialName")
        {
            Ogre::String path;
            if (scriptCompilerBasePath(compiler).find("media/") == 0)
                path = STRINGS::StringUpper(scriptCompilerBasePath(compiler));
            else
                path = STRINGS::StringUpper("media/" + scriptCompilerBasePath(compiler));
            if (path.length() > 5 && !isMediaPath(path))
            {
                unsigned int media = path.find("MEDIA");
                path = path.substr(media, path.length() - media);
            }
            Ogre::String* material = Ogre::any_cast<Ogre::String*>(args[0]);
            *material = path + *material;
            return true;
        }

        if (name == "processTextureNames")
        {
            Ogre::String path;
            if (Ogre::StringUtil::startsWith(scriptCompilerBasePath(compiler), "media/", false))
                path = scriptCompilerBasePath(compiler);
            else
                path = "MEDIA/" + scriptCompilerBasePath(compiler);

            // Textures are shipped as png or dds.
            Ogre::String* texture = Ogre::any_cast<Ogre::String*>(args[0]);
            unsigned int length = texture->length();
            if (length > 3)
            {
                const char* text = texture->c_str();
                if (!(text[length - 3] == 'p' && text[length - 2] == 'n' && text[length - 1] == 'g') &&
                    !(text[length - 3] == 'd' && text[length - 2] == 'd' && text[length - 1] == 's'))
                    *texture = texture->substr(0, length - 3) + "png";
            }

            if (Ogre::StringUtil::startsWith(*texture, "..", false))
            {
                std::vector<Ogre::String> textureParts = Ogre::StringUtil::split(*texture, "/", 0);
                std::vector<Ogre::String> pathParts = Ogre::StringUtil::split(path, "/", 0);
                *texture = "";
                unsigned int parents = 0;
                for (unsigned int i = 0; i < textureParts.size(); i++)
                {
                    if (textureParts[i] == "..")
                    {
                        parents++;
                    }
                    else
                    {
                        *texture = *texture + textureParts[i];
                        if (i != textureParts.size() - 1)
                            *texture = *texture + "/";
                    }
                }
                path = "";
                for (unsigned int i = 0; i < pathParts.size() - parents; i++)
                    path = path + pathParts[i] + "/";
            }

            std::wstring textureName = STRINGS::StringUpper(STRINGS::StringConvertToWide(*texture));
            std::wstring fullName = STRINGS::StringUpper(STRINGS::StringConvertToWide(path)) + textureName;
            CFileInfo info;
            g_pFileSystem->getFileInfo(fullName, info, false, false, false);
            if (info.m_bExists)
            {
                *texture = info.m_sResourceName;
            }
            else
            {
                CFileInfo shared;
                g_pFileSystem->getFileInfo(L"MEDIA/SHAREDTEXTURES/" + textureName, shared, false, false, false);
                if (shared.m_bExists)
                    *texture = shared.m_sResourceName;
                else
                    *texture = path + *texture;
            }
            return true;
        }
        return false;
    }

    virtual Ogre::Any createObject(Ogre::ScriptCompiler* compiler, const Ogre::String& type,
                                   const std::vector<Ogre::Any>& args)
    {
        if (type == "Material")
        {
            Ogre::String name = Ogre::any_cast<Ogre::String>(args[1]);
            if (Ogre::StringUtil::startsWith(scriptCompilerBasePath(compiler), "media/", false))
                name = STRINGS::StringUpper(scriptCompilerBasePath(compiler)) + name;
            else
                name = STRINGS::StringUpper("media/" + scriptCompilerBasePath(compiler)) + name;
            Ogre::Material* material = static_cast<Ogre::Material*>(
                Ogre::MaterialManager::getSingleton().create(name, compiler->getResourceGroup()).get());
            Ogre::Any result(material);
            return result;
        }
        return Ogre::Any();
    }
};

bool CFileSystem::getNeedsToRecompressEverything()
{
    if (m_pModFileFilter)
        return m_pModFileFilter->m_bNeedsToRecompressEverything | m_bNeedsToRecompressEverything;
    return m_bNeedsToRecompressEverything;
}

void CFileSystem::clean()
{
    if (m_pModFileFilter)
    {
        delete m_pModFileFilter;
        m_pModFileFilter = NULL;
    }
}

CFileSystem* CFileSystem::getSingleton()
{
    return g_pFileSystem;
}

unsigned int CFileSystem::getNumberOfMods()
{
    if (m_pModFileFilter)
        return m_pModFileFilter->getNumberOfActiveMods();
    return 0;
}

void CFileSystem::getEnabledModNames(TArrayList<std::wstring>* names)
{
    if (m_pModFileFilter)
        m_pModFileFilter->getEnabledModNames(names);
}

void CFileSystem::getModNames(TArrayList<std::wstring>* names)
{
    if (m_pModFileFilter)
        m_pModFileFilter->getModNames(names);
}

Ogre::DataStreamPtr CFileSystem::getDataStream(CFileInfo& info)
{
    if (info.m_bExists &&
        (info.m_eLocation == FILE_LOCATION_PAK || info.m_eLocation == FILE_LOCATION_RESOURCE_GROUP))
    {
        const std::string& group = info.m_sResourceGroup.empty()
                                       ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
                                       : info.m_sResourceGroup;
        return Ogre::ResourceGroupManager::getSingleton().openResource(info.m_sResourceName, group, false, NULL);
    }
    return Ogre::DataStreamPtr();
}

bool CFileSystem::fileIsNewerOrEqualTo(CFileInfo& file, CFileInfo& other)
{
    if (!other.m_bExists)
        return true;
    if (!file.m_bExists)
        return false;

    long long fileTime;
    if (file.m_eLocation == FILE_LOCATION_PAK)
        fileTime = m_iPakFileTime;
    else
        fileTime = FILESYSTEM::GetFileTime((STRINGS::StringConvertToWide(file.m_sModName) + file.m_sPath).c_str());

    long long otherTime;
    if (other.m_eLocation == FILE_LOCATION_PAK)
        otherTime = m_iPakFileTime;
    else
        otherTime = FILESYSTEM::GetFileTime((STRINGS::StringConvertToWide(other.m_sModName) + other.m_sPath).c_str());

    return fileTime >= otherTime;
}

void CFileSystem::reload()
{
    if (m_pModFileFilter)
        m_pModFileFilter->refreshAllMods();
    else if (m_pSettings->m_pCmdLineParser->GetIntParam(L"SAFEMODE", 0) == 0)
        m_pModFileFilter = new CModFileFilter();
    m_bInitialized = true;
}

CDataGroup* CFileSystem::getDataGroup(const std::wstring& name)
{
    std::wstring path = FILESYSTEM::CleanPath(STRINGS::StringUpper(name));
    if (path.c_str()[0] == L'/')
        path = path.substr(1, path.length() - 1);

    std::map<std::wstring, CDataGroup*>::iterator found = m_DataGroups.find(path);
    if (found == m_DataGroups.end())
        return NULL;
    return found->second;
}

CFileSystem::~CFileSystem()
{
    clean();
    g_pFileSystem = NULL;
    if (m_pMassiveDataGroup)
    {
        delete m_pMassiveDataGroup;
        m_pMassiveDataGroup = NULL;
    }
    if (m_pMeshListener)
    {
        delete m_pMeshListener;
        m_pMeshListener = NULL;
    }
    if (m_pScriptListener)
    {
        delete m_pScriptListener;
        m_pScriptListener = NULL;
    }
    m_OwnedObjects.deleteAll();
}

int CFileSystem::getAbsolutePath(const std::wstring& path, CFileInfo& info, bool bModsOnly)
{
    std::wstring fullPath = EMPTY_WSTRING;
    std::string resourceGroup = "MOD";
    if (m_pModFileFilter)
        fullPath = m_pModFileFilter->getFilePath(path, resourceGroup, info);

    if (fullPath != EMPTY_WSTRING)
    {
        info.m_sPath = fullPath;
        info.m_sResourceName = STRINGS::StringConvertToUTF8(fullPath);
        info.m_eLocation = FILE_LOCATION_RESOURCE_GROUP;
        info.m_sResourceGroup = resourceGroup;
        info.m_bExists = true;
        return FILE_LOCATION_RESOURCE_GROUP;
    }

    if (bModsOnly)
        return FILE_LOCATION_NONE;

    if (m_bResourceGroupsAdded)
    {
        std::string name = STRINGS::StringConvertToUTF8(path);
        bool bFound = false;
        for (unsigned int i = 0; i < m_ResourceGroups.size(); i++)
        {
            if (Ogre::ResourceGroupManager::getSingleton().resourceExists(m_ResourceGroups[i], name))
            {
                info.m_sPath = path;
                info.m_sResourceName = name;
                info.m_bExists = true;
                info.m_sResourceGroup = m_ResourceGroups[i];
                bFound = true;
                break;
            }
        }
        if (!bFound && Ogre::ResourceGroupManager::getSingleton().resourceExists(g_PakResourceName, name))
        {
            info.m_sPath = path;
            info.m_sResourceName = name;
            info.m_bExists = true;
            bFound = true;
        }
        if (bFound)
        {
            if (m_bPakExists)
            {
                info.m_eLocation = FILE_LOCATION_PAK;
                return FILE_LOCATION_PAK;
            }
            info.m_eLocation = FILE_LOCATION_RESOURCE_GROUP;
            return FILE_LOCATION_RESOURCE_GROUP;
        }
    }

    fullPath = FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetApplicationPath(), path);
    if (FILESYSTEM::FileExists(fullPath))
    {
        info.m_sPath = fullPath;
        info.m_eLocation = FILE_LOCATION_DISK;
        info.m_sResourceName = STRINGS::StringConvertToUTF8(fullPath);
        info.m_bExists = true;
        return FILE_LOCATION_DISK;
    }

    fullPath = EMPTY_WSTRING;
    info.m_bExists = false;
    info.m_sPath = EMPTY_WSTRING;
    info.m_sResourceName = "";
    return FILE_LOCATION_NONE;
}

void CFileSystem::getFileInfo(const std::wstring& path, CFileInfo& info, bool bCompiled, bool bBinary,
                              bool bModsOnly)
{
    info.m_sResourceName = "";
    info.m_sResourceGroup = "";
    info.m_sModName = "";
    info.m_sPath = path;
    info.m_eFormat = FILE_FORMAT_TEXT;
    info.m_eLocation = FILE_LOCATION_DISK;
    info.m_bExists = false;

    if (bModsOnly && (m_pModFileFilter == NULL || m_pModFileFilter->getNumberOfActiveMods() == 0))
        return;

    if (!m_bInitialized)
    {
        if (FILESYSTEM::FileExists(path))
        {
            info.m_sResourceName = STRINGS::StringConvertToUTF8(path);
            info.m_bExists = true;
        }
        return;
    }

    if (path.empty())
        return;

    CFileInfo source;
    std::wstring upperPath = STRINGS::StringUpper(FILESYSTEM::CleanPath(path));
    int extensionStart = upperPath.length() - 3;
    if (extensionStart < 1)
        extensionStart = 1;
    std::wstring extension = upperPath.substr(extensionStart);

    bool bCompressible = true;
    if ((extension[0] == L'O' && extension[1] == L'U' && extension[2] == L'T') ||
        (extension[0] == L'W' && extension[1] == L'A' && extension[2] == L'V') ||
        (extension[0] == L'O' && extension[1] == L'G' && extension[2] == L'G'))
        bCompressible = false;

    int location = FILE_LOCATION_NONE;
    if (!m_bPakExists)
    {
        if (path[0] == L'/' && FILESYSTEM::FileExists(path))
            location = getAbsolutePath(path, source, bModsOnly);
        else
            location = getAbsolutePath(upperPath, source, bModsOnly);
    }

    // Textures are shipped as DDS: look for the converted file first.
    if ((extension[0] == L'J' && extension[1] == L'P' && extension[2] == L'G') ||
        (extension[0] == L'P' && extension[1] == L'N' && extension[2] == L'G'))
    {
        getFileInfo(upperPath.substr(0, upperPath.length() - 3) + L"DDS", info, bCompiled, true, false);
        if (info.m_bExists)
            return;
        bCompressible = false;
    }

    if (m_bPakExists)
        location = getAbsolutePath(upperPath, source, true);

    if ((source.m_bExists || (m_bPakExists && location == FILE_LOCATION_NONE)) &&
        ((extension[0] == L'J' && extension[1] == L'P' && extension[2] == L'G') ||
         (extension[0] == L'P' && extension[1] == L'N' && extension[2] == L'G') ||
         (extension[0] == L'D' && extension[1] == L'D' && extension[2] == L'S')))
    {
        if (m_bPakExists && location == FILE_LOCATION_NONE)
            location = getAbsolutePath(upperPath, source, bModsOnly);
        if (location != FILE_LOCATION_NONE)
        {
            info.m_bExists = true;
            info.m_eLocation = source.m_eLocation;
            info.m_sPath = source.m_sPath;
            info.m_sResourceName = source.m_sResourceName;
            info.m_eFormat = FILE_FORMAT_RAW;
            info.m_sResourceGroup = source.m_sResourceGroup;
            info.m_sModName = source.m_sModName;
        }
        return;
    }

    if (bCompressible && !bCompiled && bBinary)
    {
        std::wstring binaryPath;
        binaryPath = upperPath + L".ADM";
        info.m_eLocation = getAbsolutePath(binaryPath, info, bModsOnly);
        if (info.m_bExists && (!source.m_bExists || info.m_sResourceGroup == source.m_sResourceGroup) &&
            ((m_bPakExists && getNumberOfMods() == 0) || fileIsNewerOrEqualTo(info, source)))
        {
            info.m_bExists = true;
            info.m_sResourceName = STRINGS::StringConvertToUTF8(info.m_sPath);
            info.m_eFormat = FILE_FORMAT_BINARY;
            return;
        }
    }
    else if (bCompiled)
    {
        std::wstring compiledPath;
        compiledPath = upperPath + L".CMP";
        info.m_eLocation = getAbsolutePath(compiledPath, info, bModsOnly);
        if (info.m_bExists && (!source.m_bExists || info.m_sResourceGroup == source.m_sResourceGroup) &&
            ((m_bPakExists && getNumberOfMods() == 0) || fileIsNewerOrEqualTo(info, source)))
        {
            info.m_bExists = true;
            info.m_sResourceName = STRINGS::StringConvertToUTF8(info.m_sPath);
            info.m_eFormat = FILE_FORMAT_COMPILED;
            return;
        }
    }

    if (m_bPakExists && !source.m_bExists)
    {
        if (path[0] == L'/' && FILESYSTEM::FileExists(path))
            getAbsolutePath(path, source, bModsOnly);
        else
            getAbsolutePath(upperPath, source, bModsOnly);
    }

    if (!source.m_bExists)
    {
        info.m_sResourceName = "";
        info.m_sResourceGroup = "";
        info.m_sPath = upperPath;
        info.m_eFormat = FILE_FORMAT_TEXT;
        info.m_eLocation = FILE_LOCATION_DISK;
        info.m_bExists = false;
        info.m_sModName = "";
        Ogre::LogManager::getSingleton().logMessage(
            STRINGS::StringConvertToUTF8(L"File not found given location : " + upperPath), Ogre::LML_CRITICAL);
        return;
    }

    info.m_bExists = true;
    info.m_eLocation = source.m_eLocation;
    info.m_sPath = source.m_sPath;
    info.m_sResourceName = source.m_sResourceName;
    info.m_sResourceGroup = source.m_sResourceGroup;
    info.m_sModName = source.m_sModName;
    info.m_eFormat = extension == L"CMP" ? FILE_FORMAT_COMPILED : FILE_FORMAT_TEXT;
}

void CFileSystem::getFilesInDirectory(TArrayList<std::wstring>& files, std::string& directory, std::string& pattern,
                                      bool bRecursive, bool bSkipDuplicateCheck, bool bStripExtension,
                                      const std::string& resourceGroup)
{
    Ogre::FileInfoListPtr fileList;
    if (m_bPakExists)
    {
        std::string search = directory + pattern + ".*";
        fileList = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(
            resourceGroup.empty() ? g_PakResourceName : resourceGroup, search, false);
    }
    if (!m_bPakExists || fileList.isNull() || fileList->size() == 0)
    {
        std::wstring localPath = FILESYSTEM::GetLocalPath();
        std::string search = directory;
        search = search + pattern;
        fileList = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(
            resourceGroup.empty() ? g_PakResourceName : resourceGroup, directory + pattern, false);
    }

    files.setGrowBy(fileList->size() + 1);
    for (unsigned int i = 0; i < fileList->size(); i++)
    {
        Ogre::FileInfo fileInfo = (*fileList)[i];
        std::wstring name = STRINGS::StringUpper(STRINGS::StringConvertToWide(fileInfo.filename));
        if (m_bPakExists && bStripExtension && name.length() > 4)
            name = name.substr(0, name.length() - 4);

        bool bDuplicate = false;
        if (!bSkipDuplicateCheck)
        {
            for (unsigned int j = 0; j < files.size(); j++)
            {
                if (files[j] == name)
                {
                    bDuplicate = true;
                    break;
                }
            }
        }
        if (!bDuplicate)
            files.add(name);
    }
}

unsigned int CFileSystem::getFileList(const std::wstring& directory, TArrayList<std::wstring>& files,
                                      std::wstring pattern, bool bRecursive, bool bStripExtension, bool bModsOnly,
                                      bool bSkipMods)
{
    if (directory.empty())
        return 0;

    std::wstring path = FILESYSTEM::CleanPath(directory);
    if (m_pModFileFilter && !bSkipMods)
        m_pModFileFilter->getFiles(path, files, pattern, bRecursive);

    if (!bModsOnly && m_bResourceGroupsAdded)
    {
        for (unsigned int i = 0; i < m_ResourceGroups.size(); i++)
        {
            std::string utf8Path = STRINGS::StringConvertToUTF8(path);
            std::string utf8Pattern = STRINGS::StringConvertToUTF8(pattern);
            getFilesInDirectory(files, utf8Path, utf8Pattern, bRecursive, files.size() == 0, bStripExtension,
                                m_ResourceGroups[i]);
        }
        if (!m_bPakExists)
        {
            std::string utf8Path = STRINGS::StringConvertToUTF8(path);
            std::string utf8Pattern = STRINGS::StringConvertToUTF8(pattern);
            getFilesInDirectory(files, utf8Path, utf8Pattern, bRecursive, files.size() == 0, bStripExtension,
                                g_PakResourceName);
        }
    }
    return files.size();
}

void CFileSystem::buildMassiveDataGroup()
{
    std::vector<std::wstring> unused;
    TArrayList<std::wstring> files(10);
    getFileList(L"media/", files, L"*.dat", true, true, false, false);
    getFileList(L"media/", files, L"*.animation", true, true, false, false);

    m_pMassiveDataGroup->m_DataGroups.setGrowBy(files.size() + 1);
    for (unsigned int i = 0; i < files.size(); i++)
    {
        std::wstring path = STRINGS::StringUpper(files[i]);
        size_t mediaPos = path.find(L"MEDIA/");
        if (path.find(L"UNITS/") != std::wstring::npos)
            continue;
        if (path.substr(mediaPos + 6, path.length() - 6 - mediaPos).find(L"/") == std::wstring::npos)
            continue;

        path = FILESYSTEM::CleanPath(path.substr(mediaPos, path.length() - mediaPos));
        CDataGroup* group = m_pMassiveDataGroup->AddDataGroup(path);
        group->LoadFile(path, NULL);
        group->SetGroupName(path);
        m_DataGroups[path] = group;
    }

    if ((m_pModFileFilter == NULL || m_pModFileFilter->getNumberOfActiveMods() == 0) && !m_bPakExists)
        m_pMassiveDataGroup->SaveToFile(FILESYSTEM::GetApplicationPath() + L"/media/massfile.dat");
    else
        m_pMassiveDataGroup->SaveToFile(FILESYSTEM::GetAppDataPath() + L"massfile.dat");
}

CFileSystem::CFileSystem(bool bForceRebuild)
    : m_bResourceGroupsAdded(false), m_pModFileFilter(NULL), m_bInitialized(false), m_sPakFile(EMPTY_WSTRING),
      m_bPakExists(false), m_bNeedsToRecompressEverything(false), m_pSettings(NULL), m_ResourceGroups(1),
      m_pMassiveDataGroup(NULL), m_pMeshListener(NULL), m_pScriptListener(NULL), m_OwnedObjects(10)
{
    if (g_pFileSystem != NULL)
        return;
    g_pFileSystem = this;
    m_pSettings = CMasterResourceManager::getSingleton()->m_pSettings;

    Ogre::ConfigFile config;
    config.load(Ogre::UTFString(FILESYSTEM::GetLocalPath()) + Ogre::UTFString("resources.cfg"), "\t:=", true);
    m_pSettings->SetString(KSETTINGS_S_ZIP_LOADING, EMPTY_WSTRING);

    Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();
    std::string sectionName;
    std::string typeName;
    std::string archiveName;
    TArrayList<std::string> zipArchives(10);
    std::string zipFile;
    TArrayList<std::string> fileSystemArchives(10);
    while (sections.hasMoreElements())
    {
        sectionName = sections.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = sections.getNext();
        for (Ogre::ConfigFile::SettingsMultiMap::iterator it = settings->begin(); it != settings->end(); ++it)
        {
            typeName = it->first;
            archiveName = it->second;
            if (archiveName != "")
            {
                if (typeName == "Zip")
                    m_pSettings->SetString(KSETTINGS_S_ZIP_LOADING,
                                           STRINGS::StringConvertToWide(archiveName.c_str(), 5000));
                std::string upperType = STRINGS::StringUpper(typeName);
                if (upperType.find("ZIP") != std::string::npos && typeName != "Zip")
                    zipArchives.add(archiveName);
                else if (typeName == "Zip")
                    zipFile = archiveName;
                else
                    fileSystemArchives.add(archiveName);
            }
        }
    }

    m_pSettings->SetInt(KSETTINGS_ZIP_COUNT, zipArchives.size());
    m_pMassiveDataGroup = new CDataGroup(L"MAINDATA", NULL, 20, 10, NULL);
    m_bResourceGroupsAdded = true;

    m_sPakFile = m_pSettings->GetString(KSETTINGS_S_ZIP_LOADING);
    if (m_sPakFile != EMPTY_WSTRING && FILESYSTEM::FileExists(m_sPakFile))
    {
        m_bPakExists = true;
        m_iPakFileTime = FILESYSTEM::GetFileTime(m_sPakFile.c_str());
    }
    for (int i = 0; i < m_pSettings->GetInt(KSETTINGS_ZIP_COUNT); i++)
    {
        std::string pakName = "pak" + STRINGS::GetValueAsString(i) + ".zip";
        m_ResourceGroups.add("ZIP" + STRINGS::GetValueAsString(i));
        if (FILESYSTEM::FileExists(m_sPakFile))
        {
            long long pakTime = FILESYSTEM::GetFileTime(m_sPakFile.c_str());
            if (pakTime >= m_iPakFileTime)
                m_iPakFileTime = pakTime;
        }
    }
    if (m_bPakExists)
        m_ResourceGroups.add("ZIP");

    reload();

    for (unsigned int i = 0; i < zipArchives.size(); i++)
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(zipArchives[i], "Zip",
                                                                       "ZIP" + STRINGS::GetValueAsString(i), true);
    if (zipFile != EMPTY_STRING)
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(zipFile, "Zip", "ZIP", true);
    for (unsigned int i = 0; i < fileSystemArchives.size(); i++)
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
            fileSystemArchives[i], "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);

    m_pScriptListener = new CScriptListener();
    m_pMeshListener = new CMeshListener();
    Ogre::MeshManager::getSingleton().setListener(m_pMeshListener);
    Ogre::ScriptCompilerManager::getSingleton().setListener(m_pScriptListener);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    if (getNumberOfMods() != 0)
        resourceGroupManagerModsActive() = true;

    bool bRecompress = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    if (!m_bPakExists)
    {
        if (bRecompress)
            bRecompress = false;
        else
        {
            m_bNeedsToRecompressEverything = true;
            bRecompress = true;
            bForceRebuild = true;
        }
    }
    if (m_pSettings->m_pCmdLineParser->GetIntParam(L"DEVNOCOMPRESS", 0) == 1)
    {
        bForceRebuild = !bForceRebuild;
        bRecompress = !bRecompress;
        m_bNeedsToRecompressEverything = !m_bNeedsToRecompressEverything;
    }

    CFileInfo massFile;
    if (getNumberOfMods() == 0)
        getFileInfo(L"media/massfile.dat", massFile, false, true, false);
    else if (!FILESYSTEM::FileExists(FILESYSTEM::GetAppDataPath() + L"massfile.dat"))
        bForceRebuild = true;

    if (!massFile.m_bExists || bForceRebuild ||
        (m_pModFileFilter && m_pModFileFilter->m_bNeedsToRecompressEverything) || bRecompress)
    {
        m_bNeedsToRecompressEverything = true;
        buildMassiveDataGroup();
    }

    if (getNumberOfMods() != 0 && FILESYSTEM::FileExists(FILESYSTEM::GetAppDataPath() + L"massfile.dat.adm"))
    {
        CBinaryStyle style;
        m_pMassiveDataGroup->LoadFile(FILESYSTEM::GetAppDataPath() + L"massfile.dat", &style, NULL);
    }
    else
        m_pMassiveDataGroup->LoadFile(L"media/massfile.dat", NULL);

    for (unsigned int i = 0; i < m_pMassiveDataGroup->m_DataGroups.size(); i++)
        m_DataGroups[m_pMassiveDataGroup->m_DataGroups[i]->GetGroupName()] = m_pMassiveDataGroup->m_DataGroups[i];
}
