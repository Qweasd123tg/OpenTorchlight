#include "UnitResourceList.h"

TArrayList<std::wstring> * CUnitResourceList::getPlayerClassNames()
{
    return &m_playerClassNames;
}
