#ifndef RECIPES_H
#define RECIPES_H

#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CRecipe;

class CRecipes : public CRunicCore
{
public:
    virtual ~CRecipes();
    static CRecipes* getSingleton();
    void reload();
    CRecipes(const wchar_t*);

    std::wstring m_sPath;
    TArrayList<CRecipe*> m_recipes;
};

#endif
