#include "EmptyStrings.h"
#include "ResourceSettings.h"
#include "FileUtilities.h"

unsigned int KRESOURCESETTING_S_MASTERRESOURCEFILE;
unsigned int KRESOURCESETTING_S_PARTICLE_SYSTEMS;
unsigned int KRESOURCESETTING_S_PARTICLE_MATERIALS;
unsigned int KRESOURCESETTING_S_PARTICLE_IMAGES;
unsigned int KRESOURCESETTING_S_ROOM_DATA_FOLDER;
unsigned int KRESOURCESETTING_S_SOUND_DATA_FOLDER;
unsigned int KRESOURCESETTING_S_SKILL_FOLDER;
unsigned int KRESOURCESETTING_S_MISSILE_FOLDER;
unsigned int KRESOURCESETTING_S_AFFIXES_FOLDER;
unsigned int KRESOURCESETTING_S_GRAPH_MANAGER;
unsigned int KRESOURCESETTING_S_TRANSLATE_FILE;

CResourceSettings::CResourceSettings()
    : CDynamicPropertyFile(FILESYSTEM::GetAppDataPath(), L"resourceconfig.dat", L"")
{
    KRESOURCESETTING_S_MASTERRESOURCEFILE = GetStringPropertyIndex(L"Master Resource File", L"media\\resources.dat", false);
    KRESOURCESETTING_S_PARTICLE_SYSTEMS = GetStringPropertyIndex(L"Particle files", L"media\\particles\\scripts", false);
    KRESOURCESETTING_S_PARTICLE_MATERIALS = GetStringPropertyIndex(L"Particle materials", L"media\\particles\\materials", false);
    KRESOURCESETTING_S_PARTICLE_IMAGES = GetStringPropertyIndex(L"Particle images", L"media\\particles\\images", false);
    KRESOURCESETTING_S_ROOM_DATA_FOLDER = GetStringPropertyIndex(L"Room data folder", L"media\\levelsets\\", false);
    KRESOURCESETTING_S_SOUND_DATA_FOLDER = GetStringPropertyIndex(L"Sound data folder", L"media\\sounds\\", false);
    KRESOURCESETTING_S_SKILL_FOLDER = GetStringPropertyIndex(L"Skill path", L"media\\skills\\", false);
    KRESOURCESETTING_S_MISSILE_FOLDER = GetStringPropertyIndex(L"Missile path", L"media\\missiles\\", false);
    KRESOURCESETTING_S_AFFIXES_FOLDER = GetStringPropertyIndex(L"Affix Folder", L"media\\affixes\\", false);
    KRESOURCESETTING_S_GRAPH_MANAGER = GetStringPropertyIndex(L"Graphs path", L"media\\graphs\\", false);
    KRESOURCESETTING_S_TRANSLATE_FILE = GetStringPropertyIndex(L"Translate File", L"translations\\translation.dat", false);
}

CResourceSettings::~CResourceSettings()
{
}
