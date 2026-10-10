#ifndef SETS_H
#define SETS_H

#include <functional>
#include <map>
#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CEffectGroupManager;
class CSet;

class CSets : public CRunicCore
{
public:

    virtual ~CSets();

    CSet* getSet(unsigned int index);
    static CSets* getSingleton();
    void getSetNames(TArrayList<std::wstring>& setNames);
    CSet* getSet(const wchar_t* name);
    void reload(CEffectGroupManager* effectGroupManager);
    CSets(const wchar_t* path, CEffectGroupManager* effectGroupManager);

    std::wstring m_path;
    TArrayList<CSet*> m_sets;
    std::map<std::wstring, unsigned int, std::less<std::wstring> > m_setIndices;
};

#endif
