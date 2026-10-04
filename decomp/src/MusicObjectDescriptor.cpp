#include "EmptyStrings.h"
#include "MusicObjectDescriptor.h"

CMusicObjectDescriptor::CMusicObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"MUSIC", L"FILE NAME", L"Music File Name", (void*)Set_setMusicFile, (void*)Get_getMusicFile, VARIABLE_TYPE_STRING, 2);
    AddProperty(L"PROPERTIES", L"LOOPS", L"If true the music loops. if not it'll blend back into background music.", (void*)Set_setLoops, (void*)Get_getLoops, VARIABLE_TYPE_BOOL, 0);
    AddOutputLogic(OUTPUT_EVENT_PLAYING);
    AddOutputLogic(OUTPUT_EVENT_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_SOUND_ENDED);
    AddInputLogic(INPUT_EVENT_PLAY);
    AddInputLogic(INPUT_EVENT_STOP);
    AddInputLogic(INPUT_EVENT_PLAY_LEVEL_MUSIC);
}

CMusicObjectDescriptor::~CMusicObjectDescriptor()
{
}
