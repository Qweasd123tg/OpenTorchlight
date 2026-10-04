#ifndef RANDOMNAMES_H
#define RANDOMNAMES_H

#include <string>

#include "Randomizer.h"
#include "TArrayList.h"

class CRandomName;

class CRandomNames
{
public:
    static CRandomNames* getSingleton();
    void load(const wchar_t* filename);
    CRandomNames(const wchar_t* filename);
    CRandomNames* generateName(bool withTitle);
    ~CRandomNames();

    int m_nWeight;
    TArrayList<CRandomName*> m_prefixes;
    TArrayList<std::wstring> m_suffixes;
    TArrayList<std::wstring> m_center;
    CRandomizer* m_pRandomizer;
    int m_nCenterChance;
};

#endif
