#ifndef REFMANAGERINTERPRETERFUNC_H
#define REFMANAGERINTERPRETERFUNC_H

#include <string>

#include "EditorScene.h"
#include "RunicCore.h"

// Maps model files referenced by editor properties to small IDs and back.
class CRefManagerInterpreterFunc : public CRunicCore
{
public:
    CRefManagerInterpreterFunc();
    virtual ~CRefManagerInterpreterFunc();

    static std::wstring GetModelResourceStringByID(CEditorScene* scene, unsigned int id, void* data);
    static unsigned int GetModelResourceIDByString(CEditorScene* scene, const std::wstring& name, void* data);
};

#endif
