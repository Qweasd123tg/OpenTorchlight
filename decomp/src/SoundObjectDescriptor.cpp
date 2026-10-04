#include "EmptyStrings.h"
#include "SoundObjectDescriptor.h"

CSoundObjectDescriptor::CSoundObjectDescriptor()
    : CPositionableObjectDescriptor(L"Sound", L"A sound for in the game", L"SOUND", true, false, false, false, false)
{
    AddProperty(L"SOUND", L"START ON ACTIVATE", L"when true, the sound will start as soon as the room the player enters becomes active.", (void*)Set_setSoundStartsOnActivated, (void*)Get_getSoundStartsOnActivated, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"SOUND", L"ENVIRONMENTAL", L"when true the sound will fade in and out depending on the players position and it's radius.", (void*)Set_setEnvironmental, (void*)Get_getEnvironmental, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"SOUND", L"VOLUME", L"sets the volume on the sound", (void*)Set_setVolume, (void*)Get_getVolume, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SOUND", L"RADIUS", L"sets the radius on the sound", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
    unsigned int categoryProperty = AddPropertyWithInterpreterFunctions(L"FILE", L"CATEGORY", L"The category of the sound file.", (void*)Set_setSoundBankCategory, (void*)Get_getSoundBankCategory, GetSoundCategoryIDByString, GetSoundCategoryStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 260);
    unsigned int soundGroupProperty = AddPropertyWithInterpreterFunctions(L"FILE", L"SOUND GROUP", L"The sound bank group to use.", (void*)Set_setSoundBankNameIndex, (void*)Get_getSoundBankNameIndex, GetSoundDataIDByString, GetSoundDataStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 260);
    LinkProperty(categoryProperty, soundGroupProperty);
    AddProperty(L"GUID", L"GUID", L"NO SHOW", (void*)Set_setSoundBankGuidByString, (void*)Get_getSoundBankGuidAsString, VARIABLE_TYPE_STRING, 128);
    AddOutputLogic(OUTPUT_EVENT_PLAYING);
    AddOutputLogic(OUTPUT_EVENT_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_SOUND_ENDED);
    AddOutputLogic(OUTPUT_EVENT_PAUSED);
    AddOutputLogic(OUTPUT_EVENT_RESUMED);
    AddInputLogic(INPUT_EVENT_PLAY);
    AddInputLogic(INPUT_EVENT_STOP);
    AddInputLogic(INPUT_EVENT_PAUSE);
    AddInputLogic(INPUT_EVENT_RESUME);
}

CSoundObjectDescriptor::~CSoundObjectDescriptor()
{
}
