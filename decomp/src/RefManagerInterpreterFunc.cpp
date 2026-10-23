#include "EmptyStrings.h"
#include "GameVariables.h"
#include "RefManagerInterpreterFunc.h"
#include "EditorScene.h"
#include "RunicCore.h"

std::wstring CRefManagerInterpreterFunc::GetModelResourceStringByID(CEditorScene* scene, unsigned int id, void* data)
{
    std::map<unsigned int, std::wstring>* meshFiles =
        reinterpret_cast<std::map<unsigned int, std::wstring>*>(g_MeshFilesByIndex);

    if (scene != NULL && id != 0xFFFFFFFF) {
        std::map<unsigned int, std::wstring>::iterator it = meshFiles->find(id);
        if (it != meshFiles->end())
            return it->second;
    }
    return EMPTY_WSTRING;
}

CRefManagerInterpreterFunc::~CRefManagerInterpreterFunc()
{
}

CRefManagerInterpreterFunc::CRefManagerInterpreterFunc()
    : CRunicCore()
{
}

#include "FileSystem.h"
#include "FileUtilities.h"

unsigned int CRefManagerInterpreterFunc::GetModelResourceIDByString(
    CEditorScene* scene, const std::wstring& name, void*)
{
    if (name == L"" || !scene) return ~0u;
    std::wstring filename = FILESYSTEM::CleanPath(name);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(filename, info, false, true, false);
    if (!info.m_bExists) return ~0u;
    std::map<std::wstring, unsigned int>::iterator found = g_MeshFilesByName.find(filename);
    if (found != g_MeshFilesByName.end()) return found->second;
    unsigned int id = g_MeshFilesByName.size();
    g_MeshFilesByName[filename] = id;
    std::map<unsigned int, std::wstring>* meshFiles =
        reinterpret_cast<std::map<unsigned int, std::wstring>*>(g_MeshFilesByIndex);
    (*meshFiles)[id] = filename;
    return id;
}
