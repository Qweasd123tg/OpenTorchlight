#ifndef SPAWNCLASSPARSER_H
#define SPAWNCLASSPARSER_H

#include <map>
#include <string>
#include "RunicCore.h"

class CSpawnClass;
class CSpawnClassData;

// RTTI gives the base; named _Rb_tree calls establish both member maps.
// Only declarations needed by the recovered functions are included here.
class CSpawnClassParser : public CRunicCore
{
public:
    void reloadFromDirectory(const wchar_t* path);

    virtual ~CSpawnClassParser();
    static CSpawnClassParser* getSingleton();
    void clear();
    CSpawnClassData* getSpawnClassDataByName(const std::wstring&);
    CSpawnClass* getSpawnClass(const std::wstring&);
    CSpawnClassParser();

    std::map<std::wstring, CSpawnClass*> m_spawnClasses;
    std::map<std::wstring, CSpawnClassData*> m_spawnClassData;
};

#endif
