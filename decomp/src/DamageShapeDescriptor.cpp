#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "EmptyStrings.h"
#include "DamageShapeDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "DamageShape.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

static unsigned char g_DescriptorController[96];

CDamageShapeDescriptor::CDamageShapeDescriptor()
    : CShapeDescriptor(L"Damage Shape", L"Causes damage to units", L"damageshape", true, true, false)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"DAMAGE TYPE", L"The type of damage used", (void*)Set_setDamageType, (void*)Get_getDamageType, GetDamageTypeIDByString, GetDamageTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"UNITTYPE", L"The unittype allowed to be damaged.", (void*)Set_setDamageOnlyUnitTypeByUnitTypeLoadIndex, (void*)Get_getDamageOnlyUnitTypeLoadIndex, getUnitTypeIDByString, getUnitTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"ALIGNMENT", L"The alignment type that can be damaged( evil vs good ).", (void*)Set_setAlignmentTypAllowedToDamage, (void*)Get_getAlignmentTypAllowedToDamage, getAlignmentIDByString, getAlignmentStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"PROPERTIES", L"UPDATE IN EDITOR", L"If true the damage shape will update in the editor.", (void*)Set_setUpdateInEditor, (void*)Get_getUpdateInEditor, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ENABLED", L"Enabled or not. If disabled won't update.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"DOT", L"If True does damage over time.", (void*)Set_setDamageOverTime, (void*)Get_getDamageOverTime, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"TARGET CORPSE", L"If true it will only target corpses.", (void*)Set_setTargetOnlyDead, (void*)Get_getTargetOnlyDead, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"MAX UNITS TO HIT", L"The max units that the damage shape can hit.", (void*)Set_setTotalNumberOfTargets, (void*)Get_getTotalNumberOfTargets, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"DAMAGE", L"MIN", L"The min damage.", (void*)Set_setMinDamage, (void*)Get_getMinDamage, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"DAMAGE", L"MAX", L"The max damage.", (void*)Set_setMaxDamage, (void*)Get_getMaxDamage, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMER", L"LOOPS", L"If true it will loop for ever.", (void*)Set_setLoopsForEver, (void*)Get_getLoopsForEver, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"TIMER", L"LOOP COUNT", L"The number of times it will loop.", (void*)Set_setNumLoops, (void*)Get_getNumLoops, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"TIMER", L"TIMER", L"The time that will do damage.", (void*)Set_setTimer, (void*)Get_getTimer, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMER", L"PAUSE TIMER", L"The game will pause and then do the timer.", (void*)Set_setDelayTimer, (void*)Get_getDelayTimer, VARIABLE_TYPE_FLOAT, 0);
}

CDamageShapeDescriptor::~CDamageShapeDescriptor()
{
}

std::wstring CDamageShapeDescriptor::GetDamageTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData)
{
    if (index >= 7)
        return gDAMAGE_TYPES[0];

    return gDAMAGE_TYPES[index];
}

unsigned int CDamageShapeDescriptor::getAlignmentIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int i = 0; i < 7; ++i)
        if (::KALIGNMENT_STRINGS[i] == value)
            return i;

    return 0;
}

unsigned int CDamageShapeDescriptor::GetDamageTypeIDByString(
    CEditorScene*,
    CEditorBaseObject*,
    const std::wstring& value,
    void*)
{
    for (unsigned int i = 0; i < 7; ++i) {
        if (gDAMAGE_TYPES[i] == value)
            return i;
    }
    return 0;
}

void CDamageShapeDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CDamageShape* damageShape = dynamic_cast<CDamageShape*>(object);
    if (damageShape == NULL)
        return;
    if (event == 2) {
        damageShape->setEnabled(true);
        return;
    }
    if (event == 3) {
        damageShape->setEnabled(false);
        return;
    }
}

CEditorBaseObject* CDamageShapeDescriptor::CreateObject(CEditorScene* scene)
{
    return new CDamageShape(scene->getResourceManager());
}

CDamageShapeDescriptor* getSingleton()
{
    return reinterpret_cast<CDamageShapeDescriptor*>(g_DescriptorController);
}

std::wstring CDamageShapeDescriptor::getAlignmentStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 6)
        return KALIGNMENT_STRINGS[0];
    return KALIGNMENT_STRINGS[index];
}

void CDamageShapeDescriptor::update(float elapsed)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CDamageShape* shape = dynamic_cast<CDamageShape*>(m_Objects[i]);
        if (shape)
            shape->updateLevelObject(elapsed, NULL, Ogre::Vector3::ZERO);
    }
}

void CDamageShapeDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    if (scene->getResourceManager()->getEditorIsRunning())
        return;
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CDamageShape* shape = dynamic_cast<CDamageShape*>(m_Objects[i]);
        if (shape && shape->getEnabled()) {
            shape->setEnabled(false);
            shape->setEnabled(true);
        }
    }
}

std::wstring CDamageShapeDescriptor::getUnitTypeStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    if (index < hierarchy->m_types.size()) {
        unsigned int type = hierarchy->m_types[index];
        if (type != static_cast<unsigned int>(-1))
            return CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeName(type);
    }
    return CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeName(0);
}
unsigned int CDamageShapeDescriptor::getUnitTypeIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    unsigned int type = hierarchy->getTypeIDByName(value);
    for (unsigned int index = 0; index < hierarchy->m_types.size(); ++index) {
        if (hierarchy->m_types[index] == type)
            return index;
    }
    return 0;
}
