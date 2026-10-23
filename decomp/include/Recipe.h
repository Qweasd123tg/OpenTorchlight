#ifndef RECIPE_H
#define RECIPE_H

#include <OgreMemoryAllocatorConfig.h>
#include <string>

#include "TArrayList.h"
#include "UnitTypes.h"

class CDataGroup;

// Unnamed ingredient/result records allocated by CRecipe::load.
struct RecipeInput : public Ogre::GeneralAllocatedObject
{
    RecipeInput() : m_type(static_cast<UNITTYPES::EUNITTYPES>(0)) {}

    UNITTYPES::EUNITTYPES m_type;
    std::wstring m_unit;
    int m_count;
};

struct RecipeOutput : public Ogre::GeneralAllocatedObject
{
    std::wstring m_spawnClass;
    std::wstring m_unit;
};

class CRecipe : public Ogre::GeneralAllocatedObject
{
public:
    CRecipe() : m_inputs(10), m_outputs(10) {}
    ~CRecipe()
    {
        m_inputs.deleteAll();
        m_outputs.deleteAll();
    }
    void load(CDataGroup*);

    unsigned char m_unknown0[8];
    TArrayList<RecipeInput*> m_inputs;
    TArrayList<RecipeOutput*> m_outputs;
};

#endif
