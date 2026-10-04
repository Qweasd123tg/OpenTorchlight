#ifndef CINEMATICS_H
#define CINEMATICS_H

#include "RunicCore.h"
#include "TArrayList.h"

class CCinematic;

class CCinematics : public CRunicCore
{
public:
    virtual ~CCinematics();

    CCinematic* getCinematic(unsigned int);
    static CCinematics* getSingleton();
    CCinematic* getCinematic(const wchar_t*);
    void reload();
    CCinematics(const wchar_t*);

    std::wstring m_sPath;
    TArrayList<CCinematic*> m_lCinematics;
    std::map<std::wstring, unsigned int> m_mapCinematics;
};

#endif
