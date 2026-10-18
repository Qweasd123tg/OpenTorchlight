#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <string>
#include <map>
#include <vector>
#include "RunicCore.h"

#include "UnitTypes.h"
#include "TArrayList.h"

// Unit type hierarchy (media/unittypes.hie), with layouts from the constructor.
class CDataGroup;

class CHierarchy : public CRunicCore
{
public:
    virtual ~CHierarchy();
    CHierarchy(const wchar_t* filename);
    void parseHierachy(CDataGroup* group);
    // Typed parameters from the original symbol; Boolean tail contract from CResourceManager::ISA.
    bool ISA(unsigned int type, unsigned int parent);
    UNITTYPES::EUNITTYPES getTypeIDByName(const std::wstring& name);
    std::wstring getTypeName(unsigned int type);
    void getTypeNames(TArrayList<std::wstring>* names);
    std::map<unsigned int, std::vector<unsigned int> > m_parentTypes;
    std::map<std::wstring, unsigned int> m_typeIDs;
    TArrayList<unsigned int> m_types;
};

#endif
