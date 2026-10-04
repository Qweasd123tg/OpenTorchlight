#include "EmptyStrings.h"
#include "DamageShapeDescriptor.h"

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
