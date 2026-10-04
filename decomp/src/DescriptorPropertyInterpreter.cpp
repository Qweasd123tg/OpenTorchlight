#include "EmptyStrings.h"
#include "DescriptorPropertyInterpreter.h"

CDescriptorPropertyInterpreter::CDescriptorPropertyInterpreter(ValueFunction value, NameFunction name, void* context)
    : m_pValueFunction(value), m_pNameFunction(name), m_pContext(context)
{
}

CDescriptorPropertyInterpreter::~CDescriptorPropertyInterpreter()
{
}

void CDescriptorPropertyInterpreter::SetInterpreterFunctions(ValueFunction value, NameFunction name, void* context)
{
    if (value != NULL && name != NULL)
    {
        m_pValueFunction = value;
        m_pNameFunction = name;
        m_pContext = context;
    }
}

unsigned int CDescriptorPropertyInterpreter::GetValue(CEditorScene* scene, CEditorBaseObject* object,
                                                      const std::wstring& name)
{
    if (m_pValueFunction != NULL)
        return m_pValueFunction(scene, object, name, m_pContext);
    return 0;
}

std::wstring CDescriptorPropertyInterpreter::GetValue(CEditorScene* scene, CEditorBaseObject* object,
                                                     unsigned int value)
{
    if (m_pNameFunction != NULL)
        return m_pNameFunction(scene, object, value, m_pContext);
    return EMPTY_WSTRING;
}
