#ifndef DESCRIPTOR_PROPERTY_INTERPRETER_H
#define DESCRIPTOR_PROPERTY_INTERPRETER_H

#include <string>
#include "RunicCore.h"
class CEditorScene;
class CEditorBaseObject;

class CDescriptorPropertyInterpreter : public CRunicCore
{
public:
    typedef unsigned int (*ValueFunction)(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*);
    typedef std::wstring (*NameFunction)(CEditorScene*, CEditorBaseObject*, unsigned int, void*);

    CDescriptorPropertyInterpreter(ValueFunction value, NameFunction name, void* context);
    virtual ~CDescriptorPropertyInterpreter();
    void SetInterpreterFunctions(ValueFunction value, NameFunction name, void* context);
    unsigned int GetValue(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& name);
    std::wstring GetValue(CEditorScene* scene, CEditorBaseObject* object, unsigned int value);

private:
    ValueFunction m_pValueFunction;
    NameFunction m_pNameFunction;
    void* m_pContext;
};
#endif
