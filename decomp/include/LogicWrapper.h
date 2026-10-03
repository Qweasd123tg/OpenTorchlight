#ifndef LOGICWRAPPER_H
#define LOGICWRAPPER_H

#include <string>

#include "RunicCore.h"

class CDescriptor;

// Partial: LogicWrapper.cpp. A named logic input or output of a descriptor.
class CLogicWrapper : public CRunicCore
{
public:
    CLogicWrapper(CDescriptor* descriptor, unsigned int id, std::wstring& name);
    virtual ~CLogicWrapper();

    CDescriptor* m_pDescriptor;
    unsigned int m_iID;
    std::wstring m_sName;
};

#endif
