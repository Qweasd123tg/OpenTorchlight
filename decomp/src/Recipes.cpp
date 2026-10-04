#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Recipes.h"
#include "RunicCore.h"

CRecipes* CRecipes::getSingleton()
{
    return static_cast<CRecipes*>(g_pRecipes);
}

CRecipes::CRecipes(const wchar_t* path)
    : CRunicCore(), m_sPath(path), m_recipes(10)
{
    reload();
    if (g_pRecipes == NULL)
        g_pRecipes = this;
}
