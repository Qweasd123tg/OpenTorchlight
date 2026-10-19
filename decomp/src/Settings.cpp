#include "Settings.h"

void CSettings::findClosestResolution(int width,int height,int& resultWidth,int& resultHeight)
{
    for (unsigned int i = 0; i < m_resolutions.size(); ++i) {
        if (m_resolutions[i].width == width && m_resolutions[i].height == height) {
            resultWidth = width;
            resultHeight = height;
            return;
        }
        if (width >= m_resolutions[i].width) {
            resultWidth = m_resolutions[i].width;
            resultHeight = m_resolutions[i].height;
        }
    }
}

void CSettings::addResolutionCombo(int width, int height, bool flag8, bool flagA, bool flag9)
{
    CSettingsResolution resolution;
    resolution.width = width;
    resolution.height = height;
    resolution.flag8 = flag8;
    resolution.flagA = flagA;
    resolution.flag9 = flag9;
    m_resolutions.add(resolution);
}

CSettings::~CSettings()
{
    if (m_pCmdLineParser) { delete m_pCmdLineParser; m_pCmdLineParser = NULL; }
}

#include "GameVariables.h"
#include "LinuxUtils.h"
#include "StringUtilities.h"

CSettings::CSettings(std::wstring commandLine, std::wstring directory,
                     std::wstring file, std::wstring secondaryFile)
    : CDynamicPropertyFile(std::wstring(directory.c_str()), std::wstring(file.c_str()),
                           std::wstring(secondaryFile.c_str())),
      m_pCmdLineParser(NULL), m_resolutions(10)
{
    m_pCmdLineParser = new CCmdLineParser(commandLine);
    KSETTINGS_LEVEL_SEED = GetIntPropertyIndex(L"LEVEL_SEED", 0, false);
    KSETTINGS_OPENGL = GetIntPropertyIndex(L"OPENGL", 1, false);
    KSETTINGS_RENDERBEHIND = GetIntPropertyIndex(L"RENDERBEHIND", 1, false);
    KSETTINGS_FULLSCREEN = GetIntPropertyIndex(L"FULLSCREEN", 1, false);
    KSETTINGS_RESTART_ON_FULLSCREEN_CHANGE = GetIntPropertyIndex(L"RESTART_ON_FULLSCREEN_CHANGE", 0, false);
    KSETTINGS_RESTARTING = GetIntPropertyIndex(L"RESTARTING", 0, false);
    KSETTINGS_FLOATY_NUMBERS = GetIntPropertyIndex(L"FLOATY_NUMBERS", 1, false);
    KSETTINGS_F_PARTICLEFPS = GetFloatPropertyIndex(L"PARTICLEFPS", 40.0f, false);
    KSETTINGS_F_PARTICLE_PCT = GetFloatPropertyIndex(L"PARTICLE_EMIT_PCT", 1.0f, false);
    KSETTINGS_F_ANIMATION_FPS = GetFloatPropertyIndex(L"ANIMATION_FPS", 1000.0f, false);
    KSETTINGS_VSYNCH = GetIntPropertyIndex(L"VSYNCH", 0, false);
    KSETTINGS_WIN_WIDTH = GetIntPropertyIndex(L"WINDOW_WIDTH", 800, false);
    KSETTINGS_WIN_HEIGHT = GetIntPropertyIndex(L"WINDOW_HEIGHT", 600, false);
    KSETTINGS_RES_WIDTH = GetIntPropertyIndex(L"RES_WIDTH", 800, false);
    KSETTINGS_RES_HEIGHT = GetIntPropertyIndex(L"RES_HEIGHT", 600, false);
    KSETTINGS_XRATIO = GetFloatPropertyIndex(L"X_RATIO", 1.0f, false);
    KSETTINGS_YRATIO = GetFloatPropertyIndex(L"Y_RATIO", 1.0f, false);
    KSETTINGS_MAX_FPS = GetIntPropertyIndex(L"MAX_FPS", 200, false);
    KSETTINGS_CURRENT_FPS = GetIntPropertyIndex(L"CURRENT FPS", 0, false);
    KSETTINGS_F_AVERAGE_FPS = GetFloatPropertyIndex(L"AVERAGE FPS", 0.0f, false);
    KSETTINGS_MAX_PARTICLES = GetIntPropertyIndex(L"MAX_PARTICLES", 5000, false);
    KSETTINGS_SHADOWS_ENABLED = GetIntPropertyIndex(L"SHADOWS_ENABLED", 1, false);
    KSETTINGS_SHADOW_DETAIL = GetIntPropertyIndex(L"SHADOWS_DETAIL", 4, false);
    KSETTINGS_RIMLIGHTS_ENABLED = GetIntPropertyIndex(L"RIMLIGHTS_ENABLED", 1, false);
    KSETTINGS_LIGHTING_ENABLED = GetIntPropertyIndex(L"LIGHTING_ENABLED", 1, false);
    KSETTINGS_DONT_POPULATE = GetIntPropertyIndex(L"DONT POPULATE LEVEL", 0, false);
    KSETTINGS_NO_PET = GetIntPropertyIndex(L"NO PET", 0, false);
    KSETTINGS_DISPLAY_PATHING = GetIntPropertyIndex(L"DISPLAY PATHS", 0, false);
    KSETTINGS_ENABLE_DSP = GetIntPropertyIndex(L"ENABLE DSP", 0, false);
    KSETTINGS_CONSOLE_NOPAUSE = GetIntPropertyIndex(L"CONSOLE NOPAUSE", 0, false);
    KSETTINGS_NO_SOUNDS = GetIntPropertyIndex(L"NO SOUNDS", 0, false);
    KSETTINGS_SHOW_TIPS = GetIntPropertyIndex(L"SHOW TIPS", 1, true);
    KSETTINGS_NETBOOK_MODE = GetIntPropertyIndex(L"NETBOOK MODE", 0, false);
    KSETTINGS_ALLOW_HWSKINNING = GetIntPropertyIndex(L"ALLOW HWSKINNING", 1, false);
    KSETTINGS_ALLOW_CONSOLE = GetIntPropertyIndex(L"CONSOLE", 0, true);
    KSETTINGS_GAME_COMPLETED_ONCE = GetIntPropertyIndex(L"GAME_COMPLETED_ONCE", 0, true);
    KSETTINGS_RETIREE_QUEST = GetStringPropertyIndex(L"RETIREE_QUEST", L"COMPLETEDONCE", true);
    KSETTINGS_AI_FREEZE = GetIntPropertyIndex(L"FREEZE AI", 0, false);
    KSETTINGS_PLAYER_UNTARGETABLE = GetIntPropertyIndex(L"PLAYER NO TARGET", 0, false);
    KSETTINGS_DESTROY_MONSTERS_AFTER_DEATH = GetIntPropertyIndex(L"DESTROY DEAD CORPSE", 0, false);
    KSETTINGS_UPDATE_PERF = GetIntPropertyIndex(L"UPDATE DISPLAY STATS", 0, false);
    KSETTINGS_DISPLAY_STATS = GetIntPropertyIndex(L"DISPLAY STATS", 0, false);
    KSETTINGS_COMBAT_LOG = GetIntPropertyIndex(L"COMBAT LOG", 0, false);
    KSETTINGS_SOUND_DEBUG = GetIntPropertyIndex(L"SOUND DEBUG", 0, false);
    KSETTINGS_MAX_RENDER_FPS = GetIntPropertyIndex(L"MAX_RENDER_FPS", 60, false);
    KSETTINGS_NUM_TICKS_PER_SECOND = GetIntPropertyIndex(L"NUM TICKS PER SECOND", 0, false);
    KSETTINGS_GAME_TYPE = GetIntPropertyIndex(L"GAME TYPE", 0, false);
    KSETTINGS_S_NAME = GetStringPropertyIndex(L"NAME", L"TESTING", false);
    KSETTINGS_S_PATH_RESOURCES = GetStringPropertyIndex(L"RESOURCES PATH", L"media\\", false);
    KSETTINGS_S_PATH_SCREENSHOTS = GetStringPropertyIndex(L"SCREENSHOT PATH", L"screenshots\\", false);
    KSETTINGS_S_EDITOR_RESOURCES = GetStringPropertyIndex(L"EDITOR RESOURCES PATH", L"DataEditor\\", false);
    KSETTINGS_F_PARTICLE_FALLOFF = GetFloatPropertyIndex(L"PARTICLE FALL OFF", 130.0f, false);
    KSETTINGS_F_FOV = GetFloatPropertyIndex(L"FOV", 45.0f, false);
    KSETTINGS_F_NEARCLIP = GetFloatPropertyIndex(L"NEARCLIP", 0.10000000149011612f, false);
    KSETTINGS_F_FARCLIP = GetFloatPropertyIndex(L"FARCLIP", 1000.0f, false);
    KSETTINGS_F_SOUNDVOLUME = GetFloatPropertyIndex(L"SOUND VOLUME", 0.800000011920929f, false);
    KSETTINGS_F_MUSICVOLUME = GetFloatPropertyIndex(L"MUSIC VOLUME", 0.5f, false);
    KSETTINGS_SOUNDMUTE = GetIntPropertyIndex(L"SOUND MUTE", 0, false);
    KSETTINGS_MUSICMUTE = GetIntPropertyIndex(L"MUSIC MUTE", 0, false);
    KSETTINGS_FSAA = GetIntPropertyIndex(L"FSAA", 0, false);
    KSETTINGS_SHADOW_RESOLUTION = GetIntPropertyIndex(L"SHADOWRESOLUTION", 512, false);
    KSETTINGS_DISPLAY_COLLISION = GetIntPropertyIndex(L"DISPLAY_COLLISION", 0, false);
    KSETTINGS_OVERRIDE_LIGHTING = GetIntPropertyIndex(L"DOVERRIDE_LIGHTING", 0, false);
    KSETTINGS_AMBIENT_LIGHT_RED = GetIntPropertyIndex(L"AMBIENT RED", 76, false);
    KSETTINGS_AMBIENT_LIGHT_GREEN = GetIntPropertyIndex(L"AMBIENT GREEN", 76, false);
    KSETTINGS_AMBIENT_LIGHT_BLUE = GetIntPropertyIndex(L"AMBIENT BLUE", 76, false);
    KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED = GetIntPropertyIndex(L"MATERIAL AMBIENT RED", 76, false);
    KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN = GetIntPropertyIndex(L"MATERIAL AMBIENT GREEN", 76, false);
    KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE = GetIntPropertyIndex(L"MATERIAL AMBIENT BLUE", 76, false);
    KSETTINGS_DIRECTIONAL_LIGHT_RED = GetIntPropertyIndex(L"DIRECTIONAL RED", 255, false);
    KSETTINGS_DIRECTIONAL_LIGHT_GREEN = GetIntPropertyIndex(L"DIRECTIONAL GREEN", 255, false);
    KSETTINGS_DIRECTIONAL_LIGHT_BLUE = GetIntPropertyIndex(L"DIRECTIONAL BLUE", 255, false);
    KSETTINGS_F_DIRECTIONAL_INTENSITY = GetFloatPropertyIndex(L"DIRECTIONAL INTENSITY", 1.5f, false);
    KSETTINGS_F_AUTOMAP_ZOOM = GetFloatPropertyIndex(L"AUTOMAP ZOOM", 30.0f, true);
    KSETTINGS_AUTOMAP = GetIntPropertyIndex(L"AUTOMAP", 1, true);
    KSETTINGS_S_VERSION = GetStringPropertyIndex(L"VERSION", L"0", false);
    KSETTINGS_TOGGLE_ITEM_NAME = GetIntPropertyIndex(L"TOGGLE DROPPED ITEMS", 0, false);
    KSETTINGS_SHOW_MISSILE_TRAILS = GetIntPropertyIndex(L"SHOW MISSILE TRAILS", 0, false);
    KSETTINGS_SHOW_DAMAGE_SHAPES = GetIntPropertyIndex(L"SHOW DAMAGE SHAPES", 0, false);
    KSETTINGS_S_ZIP_LOADING = GetStringPropertyIndex(L"ZIP", L"", false);
    KSETTINGS_ZIP_COUNT = GetIntPropertyIndex(L"NUMZIPS", 0, false);
    KSETTINGS_DEBUG_LOGIC = GetIntPropertyIndex(L"LOGIC LOGGING", 0, false);
    KSETTINGS_LOG_CONSOLE = GetIntPropertyIndex(L"LOG CONSOLE", 0, false);
    KSETTINGS_STEAM_CLOUD = GetIntPropertyIndex(L"STEAMCLOUD", 0, false);
    KSETTINGS_IGNORE_STEAM_CLOUD = GetIntPropertyIndex(L"IGNORE STEAM CLOUD", 0, false);
    KSETTINGS_SHOW_BLOOD = GetIntPropertyIndex(L"SHOW BLOOD", 1, true);
    KSETTINGS_NO_CAMERASHAKE = GetIntPropertyIndex(L"NO CAMERA SHAKE", 0, true);
    KSETTINGS_KEYMAP_1 = GetIntPropertyIndex(L"KEYMAP_1", 49, true);
    KSETTINGS_KEYMAP_2 = GetIntPropertyIndex(L"KEYMAP_2", 50, true);
    KSETTINGS_KEYMAP_3 = GetIntPropertyIndex(L"KEYMAP_3", 51, true);
    KSETTINGS_KEYMAP_4 = GetIntPropertyIndex(L"KEYMAP_4", 52, true);
    KSETTINGS_KEYMAP_5 = GetIntPropertyIndex(L"KEYMAP_5", 53, true);
    KSETTINGS_KEYMAP_6 = GetIntPropertyIndex(L"KEYMAP_6", 54, true);
    KSETTINGS_KEYMAP_7 = GetIntPropertyIndex(L"KEYMAP_7", 55, true);
    KSETTINGS_KEYMAP_8 = GetIntPropertyIndex(L"KEYMAP_8", 56, true);
    KSETTINGS_KEYMAP_9 = GetIntPropertyIndex(L"KEYMAP_9", 57, true);
    KSETTINGS_KEYMAP_0 = GetIntPropertyIndex(L"KEYMAP_0", 48, true);
    KSETTINGS_FKEYMAP_1 = GetIntPropertyIndex(L"FKEYMAP_1", 112, true);
    KSETTINGS_FKEYMAP_2 = GetIntPropertyIndex(L"FKEYMAP_2", 113, true);
    KSETTINGS_FKEYMAP_3 = GetIntPropertyIndex(L"FKEYMAP_3", 114, true);
    KSETTINGS_FKEYMAP_4 = GetIntPropertyIndex(L"FKEYMAP_4", 115, true);
    KSETTINGS_FKEYMAP_5 = GetIntPropertyIndex(L"FKEYMAP_5", 116, true);
    KSETTINGS_FKEYMAP_6 = GetIntPropertyIndex(L"FKEYMAP_6", 117, true);
    KSETTINGS_FKEYMAP_7 = GetIntPropertyIndex(L"FKEYMAP_7", 118, true);
    KSETTINGS_FKEYMAP_8 = GetIntPropertyIndex(L"FKEYMAP_8", 119, true);
    KSETTINGS_FKEYMAP_9 = GetIntPropertyIndex(L"FKEYMAP_9", 120, true);
    KSETTINGS_FKEYMAP_10 = GetIntPropertyIndex(L"FKEYMAP_10", 121, true);
    KSETTINGS_FKEYMAP_11 = GetIntPropertyIndex(L"FKEYMAP_11", 122, true);
    KSETTINGS_FKEYMAP_12 = GetIntPropertyIndex(L"FKEYMAP_12", 123, true);
    KSETTINGS_KEYMAP_INVENTORY = GetIntPropertyIndex(L"KEYMAP_INVENTORY", 73, true);
    KSETTINGS_KEYMAP_PET = GetIntPropertyIndex(L"KEYMAP_PET", 80, true);
    KSETTINGS_KEYMAP_STATS = GetIntPropertyIndex(L"KEYMAP_STATS", 67, true);
    KSETTINGS_KEYMAP_SKILLS = GetIntPropertyIndex(L"KEYMAP_SKILLS", 83, true);
    KSETTINGS_KEYMAP_QUESTS = GetIntPropertyIndex(L"KEYMAP_QUESTS", 81, true);
    KSETTINGS_KEYMAP_JOURNAL = GetIntPropertyIndex(L"KEYMAP_JOURNAL", 74, true);
    KSETTINGS_KEYMAP_OPTIONS = GetIntPropertyIndex(L"KEYMAP_OPTIONS", 27, true);
    KSETTINGS_KEYMAP_PAUSE = GetIntPropertyIndex(L"KEYMAP_PAUSE", 13, true);
    KSETTINGS_KEYMAP_AUTOMAP = GetIntPropertyIndex(L"KEYMAP_AUTOMAP", 65, true);
    KSETTINGS_KEYMAP_AUTOMAPZOOMIN = GetIntPropertyIndex(L"KEYMAP_AUTOMAPZOOMIN", 219, true);
    KSETTINGS_KEYMAP_AUTOMAPZOOMOUT = GetIntPropertyIndex(L"KEYMAP_AUTOMAPZOOMOUT", 221, true);
    KSETTINGS_KEYMAP_HOLDPOS = GetIntPropertyIndex(L"KEYMAP_HOLDPOS", 16, true);
    KSETTINGS_KEYMAP_SHOWITEMS = GetIntPropertyIndex(L"KEYMAP_SHOWITEMS", 18, true);
    KSETTINGS_KEYMAP_CYCLESKILLUP = GetIntPropertyIndex(L"KEYMAP_CYCLESKILLUP", 190, true);
    KSETTINGS_KEYMAP_CYCLESKILLDOWN = GetIntPropertyIndex(L"KEYMAP_CYCLESKILLDOWN", 188, true);
    KSETTINGS_KEYMAP_SWAPSKILLS = GetIntPropertyIndex(L"KEYMAP_SWAPSKILLS", 9, true);
    KSETTINGS_KEYMAP_WEAPONSET = GetIntPropertyIndex(L"KEYMAP_WEAPONSET", 87, true);
    KSETTINGS_KEYMAP_CLOSEALL = GetIntPropertyIndex(L"KEYMAP_CLOSEALL", 32, true);
    KSETTINGS_KEYMAP_ZOOMIN = GetIntPropertyIndex(L"KEYMAP_ZOOMIN", 187, true);
    KSETTINGS_KEYMAP_ZOOMOUT = GetIntPropertyIndex(L"KEYMAP_ZOOMOUT", 189, true);
    KSETTINGS_KEYMAP_CONSOLE_PRESS = GetIntPropertyIndex(L"KEYMAP_CONSOLEKEY_PRESS", 192, true);
    KSETTINGS_KEYMAP_CONSOLE_HOLD = GetIntPropertyIndex(L"KEYMAP_CONSOLEKEY_HOLD", 16, true);
}

void CSettings::assignDefault(int capability, int performance, std::string renderer)
{
    int detail;
    if (performance <= 300) {
        performance = 1000;
        detail = 3;
    } else {
        detail = performance > 1999 ? 4 : 3;
    }
    if (capability < 600) detail = 3;
    if (performance < 1800) detail = 2;
    if (capability < 512) detail = 2;
    if (performance < 1600) detail = performance > 999 ? 1 : 0;
    if (capability < 390) detail = 0;

    int particleDetail = 2;
    int maximumShadow = 5;
    if (STRINGS::StringUpper(renderer).find("INTEL") != std::string::npos &&
        STRINGS::StringUpper(renderer).find("GMA") != std::string::npos) {
        detail = 0;
        particleDetail = 0;
        maximumShadow = 0;
    }
    if (STRINGS::StringUpper(renderer).find("INTEGRATED") != std::string::npos && detail == 4)
        detail = 3;

    int width, height;
    LinuxUtils::GetDesktopResolution(width, height);
    int resultWidth = width, resultHeight = height;
    static const float resolutionScale[5] = {0.5f, 0.6f, 0.8f, 0.9f, 1.0f};
    if (detail != 4) {
        width = static_cast<int>(static_cast<float>(width) * resolutionScale[detail]);
        height = static_cast<int>(static_cast<float>(height) * resolutionScale[detail]);
    }
    SetInt(KSETTINGS_FSAA, detail >= 3 ? 1 : 0);
    SetInt(KSETTINGS_NETBOOK_MODE, detail == 0 ? 1 : 0);
    findClosestResolution(width, height, resultWidth, resultHeight);
    SetInt(KSETTINGS_RES_WIDTH, resultWidth);
    SetInt(KSETTINGS_RES_HEIGHT, resultHeight);
    SetInt(KSETTINGS_SHADOW_DETAIL, detail == 4 ? maximumShadow : detail + 1);
    SetInt(KSETTINGS_LIGHTING_ENABLED, 1);
    SetInt(KSETTINGS_SHADOWS_ENABLED, detail != 0 ? 1 : 0);
    SetInt(KSETTINGS_SHADOW_RESOLUTION, detail < 2 ? 128 : 128 << (detail - 1));
    if (detail < 2) particleDetail = detail;
    SetFloat(KSETTINGS_F_PARTICLEFPS, KParticleFPSDetail[particleDetail]);
    SetFloat(KSETTINGS_F_PARTICLE_PCT, KParticlePCTDetail[particleDetail]);
}
