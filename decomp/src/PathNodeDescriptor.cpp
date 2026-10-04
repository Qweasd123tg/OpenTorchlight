#include "EmptyStrings.h"
#include "PathNodeDescriptor.h"

CPathNodeDescriptor::CPathNodeDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, true)
{
    m_iFlags |= DESCRIPTOR_FLAG_NOT_SAVED;
    m_iFlags &= ~DESCRIPTOR_FLAG_CLONABLE;
}

CPathNodeDescriptor::~CPathNodeDescriptor()
{
}
