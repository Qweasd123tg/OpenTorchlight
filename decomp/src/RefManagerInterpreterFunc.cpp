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
