#include "EmptyStrings.h"
#include "FileSystem.h"
#include "RefManagerInterpreterFunc.h"
#include "ParticleUniverseConstants.h"
#include "FileUtilities.h"

CRefManagerInterpreterFunc::CRefManagerInterpreterFunc()
{
}

static std::map<std::wstring, unsigned int> g_MeshFilesByName;
static std::map<unsigned int, std::wstring> g_MeshFilesByIndex;

std::wstring CRefManagerInterpreterFunc::GetModelResourceStringByID(CEditorScene* scene, unsigned int id, void* data)
{
    if (id != (unsigned int)-1 && scene)
    {
        std::map<unsigned int, std::wstring>::iterator it = g_MeshFilesByIndex.find(id);
        if (it != g_MeshFilesByIndex.end())
            return it->second;
    }
    return EMPTY_WSTRING;
}

CRefManagerInterpreterFunc::~CRefManagerInterpreterFunc()
{
}

unsigned int CRefManagerInterpreterFunc::GetModelResourceIDByString(CEditorScene* scene, const std::wstring& name,
                                                                    void* data)
{
    if (name == L"" || !scene)
        return (unsigned int)-1;
    std::wstring path = FILESYSTEM::CleanPath(name);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path, info, false, true, false);
    if (!info.m_bExists)
        return (unsigned int)-1;
    std::map<std::wstring, unsigned int>::iterator it = g_MeshFilesByName.find(path);
    if (it == g_MeshFilesByName.end())
    {
        unsigned int id = g_MeshFilesByName.size();
        g_MeshFilesByName[path] = id;
        g_MeshFilesByIndex[id] = path;
        return id;
    }
    return it->second;
}
