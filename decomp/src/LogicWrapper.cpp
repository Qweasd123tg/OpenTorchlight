#include "EmptyStrings.h"
#include "LogicWrapper.h"

CLogicWrapper::CLogicWrapper(CDescriptor* descriptor, unsigned int id, std::wstring& name)
    : m_pDescriptor(descriptor), m_iID(id), m_sName(name)
{
}

CLogicWrapper::~CLogicWrapper()
{
}
