#ifndef UNITRESOURCELIST_H
#define UNITRESOURCELIST_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "DataGroup.h"
#include "GameEnums.h"
#include "Hierarchy.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CUnitResourceList : public CRunicCore
{
public:
    virtual ~CUnitResourceList();
    static CUnitResourceList* getSingleton();
    long long getDataGroupByGuid(long long);
    char* getPlayerClassNames();
    CUnitResourceList();
    long long* getGroupByName(const std::wstring&);
    void getUnitNames(TArrayList<std::wstring >&);
    int getDataGroupsByUnitType(unsigned int, TArrayList<CDataGroup*>&);
    void clearDataOut();
    long long getDataGroupByObjectName(const std::wstring&);
    long long getDataGroupByFileName(const wchar_t*, const wchar_t*);
    long long getDataGroupByFileName(const std::wstring&, const std::wstring&);
    long long getDataGroupByObjectName(const std::wstring&, const std::wstring&);
    CDataGroup* parseChildFile(const std::wstring&, bool);
    void addNewItem(const std::wstring&, CDataGroup*, bool);
    void loadFile(ERESOURCE_GROUPS, std::wstring, std::wstring, bool, CDataGroup*);
    void parseMasterDirectory(ERESOURCE_GROUPS, std::wstring, std::wstring, CDataGroup*, bool);
    void InitUnitResourceList(CResourceSettings*, CHierarchy*);

    // fields
    CResourceSettings* m_pResourceSettings;
    long long m_Unknown18;
    int m_iUnknown20;
    unsigned char m_gap24[0x4] __attribute__((aligned(4)));
    void* m_pUnknown28;
    void* m_pUnknown30;
    long long m_iUnknown38;
    long long m_iUnknown40;
    long long m_Unknown48;
    int m_iUnknown50;
    unsigned char m_gap54[0x4] __attribute__((aligned(4)));
    void* m_pUnknown58;
    long long m_iUnknown60;
    long long m_iUnknown68;
    long long m_iUnknown70;
    long long m_Unknown78;
    int m_iUnknown80;
    unsigned char m_gap84[0x4] __attribute__((aligned(4)));
    void* m_pUnknown88;
    long long m_iUnknown90;
    long long m_iUnknown98;
    long long m_iUnknownA0;
    long long m_UnknownA8;
    int m_iUnknownB0;
    unsigned char m_gapB4[0x4] __attribute__((aligned(4)));
    void* m_pUnknownB8;
    long long m_iUnknownC0;
    long long m_iUnknownC8;
    long long m_iUnknownD0;
    unsigned char m_PlayerClassNames[0x18] __attribute__((aligned(8)));
    unsigned char m_gapF0[0x8] __attribute__((aligned(8)));
    CHierarchy* m_pHierarchy;
    unsigned char m_Unknown100[0x18] __attribute__((aligned(8)));
    void* m_pUnknown118;
};

#endif
