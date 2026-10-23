#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Recipes.h"
#include "RunicCore.h"
#include "Recipe.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "Hierarchy.h"
#include "MasterResourceManager.h"

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

CRecipes::~CRecipes()
{
    m_recipes.deleteAll();
    g_pRecipes = NULL;
}

void CRecipe::load(CDataGroup* group)
{
    std::vector<CDataGroup*> groups;
    unsigned int count = group->GetDataGroupsMatchingName(L"INGREDIENT", &groups);
    for (unsigned int i = 0; i < count; ++i)
    {
        CDataGroup* ingredientGroup = groups[i];
        std::wstring unit = ingredientGroup->GetDataValue(L"UNIT", L"");
        std::wstring unitType = ingredientGroup->GetDataValue(L"UNITTYPE", L"");
        int requiredCount = ingredientGroup->GetDataValue(L"COUNT", 1);
        RecipeInput* ingredient = new RecipeInput;
        ingredient->m_count = requiredCount;
        if (unitType != EMPTY_WSTRING)
            ingredient->m_type = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(unitType);
        else
            ingredient->m_type = static_cast<UNITTYPES::EUNITTYPES>(22);
        ingredient->m_unit = unit;
        m_inputs.add(ingredient);
    }

    groups.clear();
    count = group->GetDataGroupsMatchingName(L"RESULT", &groups);
    for (unsigned int i = 0; i < count; ++i)
    {
        CDataGroup* resultGroup = groups[i];
        std::wstring unit = resultGroup->GetDataValue(L"UNIT", L"");
        std::wstring spawnClass = resultGroup->GetDataValue(L"SPAWNCLASS", L"");
        RecipeOutput* result = new RecipeOutput;
        result->m_spawnClass = spawnClass;
        result->m_unit = unit;
        m_outputs.add(result);
    }
}

void CRecipes::reload()
{
    m_recipes.deleteAll();
    TArrayList<std::wstring> files(10);
    CFileSystem::getSingleton()->getFileList(m_sPath, files, L"*.dat", true, true, false, false);
    m_recipes.setGrowBy(files.size() + 1);
    for (unsigned int i = 0; i < files.size(); ++i)
    {
        CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
        group.LoadFile(files[i], NULL);
        CRecipe* recipe = new CRecipe;
        recipe->load(&group);
        m_recipes.add(recipe);
    }
}
