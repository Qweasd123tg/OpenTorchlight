#include "EmptyStrings.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <algorithm>
#include <cmath>
#include "LevelTemplateData.h"
#include "Utilities.h"

CChunk* CLevelTemplateData::getRandomChunk(unsigned int index)
{
    return m_chunks[m_chunkRandomizers[index]->getRandom()];
}

CLevelLayout* CLevelTemplateData::getRandomLayout()
{
    if (!m_layoutRandomizer || !m_layoutRandomizer->hasChoices()) return NULL;
    return m_layouts[m_layoutRandomizer->getRandom()];
}

void CLevelTemplateData::resetOdds()
{
    for (unsigned int i = 0; i < m_chunkRandomizers.size(); ++i) {
        int count = static_cast<int>(m_chunkRandomizers[i]->getChoiceCount());
        for (int j = 0; j < count; ++j) {
            int choice = m_chunkRandomizers[i]->getChoice(j);
            m_chunkRandomizers[i]->setChoiceOdds(choice, m_chunks[choice]->m_odds);
        }
    }
}

unsigned int CLevelTemplateData::getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION creation, unsigned int area)
{
    float minimum = m_countRanges[creation].minimum;
    float maximum = m_countRanges[creation].maximum;
    if (!(minimum <= 0.0f) || !(maximum <= 0.0f)) {
        float low = maximum < minimum ? maximum : minimum;
        float high = maximum > minimum ? maximum : minimum;
        return UTILITIES::randomIntegerBetween(static_cast<int>(low), static_cast<int>(high));
    }
    minimum = m_densityRanges[creation].minimum;
    maximum = m_densityRanges[creation].maximum;
    if (!(minimum <= 0.0f) && !(maximum <= 0.0f)) {
        float scale = static_cast<float>(area) / 6.5f;
        float low = maximum < minimum ? maximum : minimum;
        float high = maximum > minimum ? maximum : minimum;
        return static_cast<unsigned int>(::ceilf(UTILITIES::randomBetween(low * scale, high * scale)));
    }
    return 0;
}

CLevelTemplateData::~CLevelTemplateData()
{
    if (m_layoutRandomizer) {
        delete m_layoutRandomizer;
        m_layoutRandomizer = NULL;
    }
    m_chunkRandomizers.deleteAll();
    m_requiredChunkTypes.clear();
    m_baseLayouts.clear();
    m_layouts.deleteAll();
    m_chunkTypes.deleteAll();
    m_chunks.deleteAll();
}

CLevelTemplateData::CLevelTemplateData(wchar_t const* filename)
    : m_chunkTypes(10),
      m_chunks(10),
      m_requiredChunkTypes(10),
      m_randomized(true),
      m_requiresExit(true),
      m_dontStore(false),
      m_string60(EMPTY_WSTRING),
      m_name(EMPTY_WSTRING),
      m_hasPathing(true),
      m_hasAutomap(true),
      m_populate(true),
      m_minChunks(2),
      m_maxChunks(3),
      m_monsterLevelMin(-1),
      m_monsterLevelMax(-1),
      m_permitsPortal(true),
      m_permitsPetDeparture(true),
      m_isTown(false),
      m_questSelectionExcluded(false),
      m_tileBasis(4.0f),
      m_chunkWidthBasis(25.0f),
      m_chunkHeightBasis(25.0f),
      m_cameraMultiplier(1.0f),
      m_sightRangeModifier(0.0f),
      m_automap(EMPTY_WSTRING),
      m_automapWidth(1.0f),
      m_automapHeight(1.0f),
      m_automapAngle(0.0f),
      m_layouts(10),
      m_baseLayouts(10),
      m_layoutRandomizer(NULL),
      m_chunkRandomizers(2),
      m_generalChunkRandomizer(RANDOMIZER_NORMAL),
      m_entranceChunkRandomizer(RANDOMIZER_NORMAL),
      m_randomizer1D8(RANDOMIZER_NORMAL),
      m_randomizer240(RANDOMIZER_NORMAL),
      m_randomizer2A8(RANDOMIZER_NORMAL),
      m_randomizer310(RANDOMIZER_NORMAL),
      m_randomizer378(RANDOMIZER_NORMAL),
      m_randomizer3E0(RANDOMIZER_NORMAL),
      m_randomizer448(RANDOMIZER_NORMAL),
      m_randomizer4B0(RANDOMIZER_NORMAL),
      m_music(L"media/music/Crypt.ogg"),
      m_regionBoundsX(50.0f),
      m_regionBoundsY(50.0f),
      m_regionBoundsZ(50.0f),
      m_cinematic(L""),
      m_skybox(L""),
      m_levelParticle(L""),
      m_water(EMPTY_WSTRING),
      m_postWater(EMPTY_WSTRING),
      m_midWater(EMPTY_WSTRING),
      m_torchlightTexture(L"media/sharedtextures/lantern.dds"),
      m_sRimlightTexture(L"media/sharedtextures/rimlight.dds"),
      m_shadowFadeTexture(L"media/sharedtextures/shadowfade.dds"),
      m_lightMaskTexture(L"media/sharedtextures/lightmask.dds"),
      m_mainMenuRules(L"media/layouts/mainmenus/mainmenu_cryptrules.dat"),
      m_lightmapColorR(1.0f),
      m_lightmapColorG(1.0f),
      m_lightmapColorB(1.0f),
      m_lightmapColorA(1.0f),
      m_fogColorR(1.0f),
      m_fogColorG(1.0f),
      m_fogColorB(1.0f),
      m_fogColorA(1.0f),
      m_ambientColorR(1.0f),
      m_ambientColorG(1.0f),
      m_ambientColorB(1.0f),
      m_ambientColorA(1.0f),
      m_materialAmbientColorR(1.0f),
      m_materialAmbientColorG(1.0f),
      m_materialAmbientColorB(1.0f),
      m_materialAmbientColorA(1.0f),
      m_directionalColorR(1.0f),
      m_directionalColorG(1.0f),
      m_directionalColorB(1.0f),
      m_directionalColorA(1.0f),
      m_orthographicShadows(false),
      m_state761(false),
      m_randomLayoutGenerated(false),
      m_bUnitLightFade(true),
      m_unitFadeDistance(14.5f),
      m_unitFadeStart(7.0f),
      m_showFloorNumber(true),
      m_levelName(L"Dungeon")
{
    for (unsigned int i = 0; i < 11; ++i)
        m_useSpawnClass[i] = false;

    m_unitSpawnerNames[0] = L"MONSTERSET";
    m_unitSpawnerNames[1] = L"MONSTERSETCHAMPION";
    m_unitSpawnerNames[2] = L"PROPS";
    m_unitSpawnerNames[5] = EMPTY_WSTRING;
    m_unitSpawnerNames[7] = EMPTY_WSTRING;
    m_unitSpawnerNames[3] = L"NPCS";
    m_unitSpawnerNames[4] = L"CREEPS";
    m_unitSpawnerNames[6] = L"FISH_SPAWN";
    m_unitSpawnerNames[8] = L"MONSTERSET";
    m_unitSpawnerNames[9] = EMPTY_WSTRING;
    m_unitSpawnerNames[10] = L"MONSTERSETCHAMPION";

    m_densityRanges[0].minimum = 0.01f;
    m_densityRanges[0].maximum = 0.0125f;
    m_densityRanges[1].minimum = 0.00025f;
    m_densityRanges[1].maximum = 0.0004f;
    m_densityRanges[2].minimum = 0.005f;
    m_densityRanges[2].maximum = 0.0075f;
    m_densityRanges[5].minimum = 0.0012f;
    m_densityRanges[5].maximum = 0.0017f;
    m_densityRanges[7].minimum = 0.001f;
    m_densityRanges[7].maximum = 0.002f;
    m_densityRanges[3].minimum = 0.0f;
    m_densityRanges[3].maximum = 0.0f;
    m_densityRanges[4].minimum = 0.0f;
    m_densityRanges[4].maximum = 0.0f;
    m_densityRanges[6].minimum = 0.0f;
    m_densityRanges[6].maximum = 0.0f;
    m_densityRanges[8].minimum = 0.0f;
    m_densityRanges[8].maximum = 0.0f;
    m_densityRanges[9].minimum = 0.0f;
    m_densityRanges[9].maximum = 0.0f;
    m_densityRanges[10].minimum = 0.0f;
    m_densityRanges[10].maximum = 0.0f;

    m_countRanges[0].minimum = 0.0f;
    m_countRanges[0].maximum = 0.0f;
    m_countRanges[1].minimum = 0.0f;
    m_countRanges[1].maximum = 0.0f;
    m_countRanges[2].minimum = 0.0f;
    m_countRanges[2].maximum = 0.0f;
    m_countRanges[5].minimum = 0.0f;
    m_countRanges[5].maximum = 0.0f;
    m_countRanges[7].minimum = 0.0f;
    m_countRanges[7].maximum = 0.0f;
    m_countRanges[3].minimum = 0.0f;
    m_countRanges[3].maximum = 0.0f;
    m_countRanges[4].minimum = 0.0f;
    m_countRanges[4].maximum = 0.0f;
    m_countRanges[6].minimum = 0.0f;
    m_countRanges[6].maximum = 0.0f;
    m_countRanges[8].minimum = 0.0f;
    m_countRanges[8].maximum = 0.0f;
    m_countRanges[9].minimum = 0.0f;
    m_countRanges[9].maximum = 0.0f;
    m_countRanges[10].minimum = 0.0f;
    m_countRanges[10].maximum = 0.0f;

    load(filename);
}

void CLevelTemplateData::load(wchar_t const* filename)
{
    if (!filename || !*filename) return;
    m_filename = filename;
    CFileInfo fileInfo;
    CFileSystem::getSingleton()->getFileInfo(m_filename, fileInfo, false, true, false);
    if (!fileInfo.m_bExists) return;

    std::wstring directory = m_filename;
    directory = directory.substr(0, directory.length() - FILESYSTEM::GetFileName(directory).length());
    CDataGroup data(L"LEVELLAYOUT", NULL, 20, 10, NULL);
    data.LoadFile(filename, NULL);
    m_monsterLevelMin = data.GetDataValue(L"MONSTER_LVL_MIN", m_monsterLevelMin);
    m_monsterLevelMax = data.GetDataValue(L"MONSTER_LVL_MAX", m_monsterLevelMax);
    m_questSelectionExcluded = data.GetDataValue(L"NO_RANDOM_QUESTS", false);
    m_tileBasis = data.GetDataValue(L"TILEBASIS", m_tileBasis);
    m_chunkWidthBasis = data.GetDataValue(L"CHUNKWIDTHBASIS", m_chunkWidthBasis);
    m_chunkHeightBasis = data.GetDataValue(L"CHUNKHEIGHTBASIS", m_chunkHeightBasis);
    m_requiresExit = data.GetDataValue(L"REQUIRESEXIT", m_requiresExit);
    m_dontStore = data.GetDataValue(L"DONTSTORE", m_dontStore);
    m_randomized = data.GetDataValue(L"RANDOMIZED", m_randomized);
    m_hasPathing = data.GetDataValue(L"HASPATHING", m_hasPathing);
    m_hasAutomap = data.GetDataValue(L"HASAUTOMAP", m_hasAutomap);
    m_minChunks = data.GetDataValue(L"MINCHUNKS", m_minChunks);
    m_maxChunks = data.GetDataValue(L"MAXCHUNKS", m_maxChunks);
    m_populate = data.GetDataValue(L"POPULATE", m_populate);
    m_orthographicShadows = data.GetDataValue(L"ORTHOGRAPHICSHADOWS", m_orthographicShadows);
    m_bUnitLightFade = data.GetDataValue(L"UNIT_LIGHT_FADE", m_bUnitLightFade);
    m_unitFadeDistance = data.GetDataValue(L"UNIT_FADE_DISTANCE", m_unitFadeDistance);
    m_unitFadeStart = data.GetDataValue(L"UNIT_FADE_START", m_unitFadeStart);
    m_cameraMultiplier = data.GetDataValue(L"CAMERAMULT", 1.0f);
    m_music = data.GetDataValue(L"MUSIC", m_music);
    m_showFloorNumber = data.GetDataValue(L"SHOWFLOORNUMBER", m_showFloorNumber);
    m_levelName = data.GetDataValue(L"LEVELNAME", m_levelName);
    m_name = STRINGS::StringUpper(data.GetDataValue(L"NAME", EMPTY_WSTRING));
    m_sRimlightTexture = data.GetDataValue(L"RIMLIGHT", m_sRimlightTexture);
    m_torchlightTexture = data.GetDataValue(L"TORCHLIGHT", m_torchlightTexture);
    m_shadowFadeTexture = data.GetDataValue(L"SHADOWFADE", m_shadowFadeTexture);
    m_lightMaskTexture = data.GetDataValue(L"LIGHTMASK", m_lightMaskTexture);
    int lightmapR = data.GetDataValue(L"LIGHTMAP RED", 24);
    int lightmapG = data.GetDataValue(L"LIGHTMAP GREEN", 24);
    int lightmapB = data.GetDataValue(L"LIGHTMAP BLUE", 24);
    m_lightmapColorA = 1.0f;
    m_lightmapColorB = static_cast<float>(lightmapB) / 255.0f;
    m_lightmapColorG = static_cast<float>(lightmapG) / 255.0f;
    m_lightmapColorR = static_cast<float>(lightmapR) / 255.0f;
    m_cinematic = data.GetDataValue(L"CINEMATIC", m_cinematic);
    m_skybox = data.GetDataValue(L"SKYBOX", m_skybox);
    m_levelParticle = data.GetDataValue(L"LEVELPARTICLE", m_levelParticle);
    m_water = data.GetDataValue(L"WATER", m_water);
    m_postWater = data.GetDataValue(L"POSTWATER", m_postWater);
    m_midWater = data.GetDataValue(L"MIDWATER", m_midWater);
    m_mainMenuRules = data.GetDataValue(L"MAINMENURULES", m_mainMenuRules);
    m_automap = data.GetDataValue(L"AUTOMAP", EMPTY_WSTRING);
    m_automapWidth = data.GetDataValue(L"AUTOMAP_WIDTH", m_automapWidth);
    m_automapHeight = data.GetDataValue(L"AUTOMAP_HEIGHT", m_automapHeight);
    m_automapAngle = data.GetDataValue(L"AUTOMAP_ANGLE", m_automapAngle);

    CFileSystem::getSingleton()->getFileInfo(m_sRimlightTexture, fileInfo, false, true, false);
    m_sRimlightTexture = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_torchlightTexture, fileInfo, false, true, false);
    m_torchlightTexture = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_shadowFadeTexture, fileInfo, false, true, false);
    m_shadowFadeTexture = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_lightMaskTexture, fileInfo, false, true, false);
    m_lightMaskTexture = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_skybox, fileInfo, false, true, false);
    m_skybox = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_water, fileInfo, false, true, false);
    m_water = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_postWater, fileInfo, false, true, false);
    m_postWater = fileInfo.m_sPath;
    CFileSystem::getSingleton()->getFileInfo(m_midWater, fileInfo, false, true, false);
    m_midWater = fileInfo.m_sPath;
    m_sightRangeModifier = data.GetDataValue(L"ACTIVERANGEMOD", 0.0f);
    int ambientR = data.GetDataValue(L"AMBIENT RED", 74);
    int ambientG = data.GetDataValue(L"AMBIENT GREEN", 74);
    int ambientB = data.GetDataValue(L"AMBIENT BLUE", 74);
    m_ambientColorA = 1.0f;
    m_ambientColorB = static_cast<float>(ambientB) / 255.0f;
    m_ambientColorG = static_cast<float>(ambientG) / 255.0f;
    m_ambientColorR = static_cast<float>(ambientR) / 255.0f;
    int materialR = data.GetDataValue(L"MATERIAL AMBIENT RED", 92);
    int materialG = data.GetDataValue(L"MATERIAL AMBIENT GREEN", 92);
    int materialB = data.GetDataValue(L"MATERIAL AMBIENT BLUE", 92);
    m_materialAmbientColorA = 1.0f;
    m_materialAmbientColorB = static_cast<float>(materialB) / 255.0f;
    m_materialAmbientColorG = static_cast<float>(materialG) / 255.0f;
    m_materialAmbientColorR = static_cast<float>(materialR) / 255.0f;
    int directionalR = data.GetDataValue(L"DIRECTIONAL RED", 238);
    int directionalG = data.GetDataValue(L"DIRECTIONAL GREEN", 219);
    int directionalB = data.GetDataValue(L"DIRECTIONAL BLUE", 155);
    float regionX = data.GetDataValue(L"REGIONBOUNDS X", 50.0f);
    float regionY = data.GetDataValue(L"REGIONBOUNDS Y", 50.0f);
    float regionZ = data.GetDataValue(L"REGIONBOUNDS Z", 50.0f);
    m_regionBoundsX = regionX;
    m_regionBoundsY = regionY;
    m_regionBoundsZ = regionZ;
    float directionalX = data.GetDataValue(L"DIRECTIONAL X", 1.0f);
    float directionalY = data.GetDataValue(L"DIRECTIONAL Y", 0.0f);
    float directionalZ = data.GetDataValue(L"DIRECTIONAL Z", 0.0f);
    m_directionalX = directionalX;
    m_directionalY = directionalY;
    m_directionalZ = directionalZ;
    m_directionalIntensity = data.GetDataValue(L"DIRECTIONAL INTENSITY", 1.0f);
    m_directionalColorA = 1.0f;
    m_directionalColorB = (static_cast<float>(directionalB) / 255.0f) * m_directionalIntensity;
    m_directionalColorG = (static_cast<float>(directionalG) / 255.0f) * m_directionalIntensity;
    m_directionalColorR = (static_cast<float>(directionalR) / 255.0f) * m_directionalIntensity;
    float fogR = static_cast<float>(data.GetDataValue(L"FOG RED", 30));
    float fogG = static_cast<float>(data.GetDataValue(L"FOG GREEN", 42));
    float fogB = static_cast<float>(data.GetDataValue(L"FOG BLUE", 58));
    m_fogColorA = 1.0f;
    m_fogColorB = fogB / 255.0f;
    m_fogColorG = fogG / 255.0f;
    m_fogColorR = fogR / 255.0f;
    m_fogStart = static_cast<float>(data.GetDataValue(L"FOG START", 24));
    m_fogEnd = static_cast<float>(data.GetDataValue(L"FOG END", 50));

    std::vector<CDataGroup*> groups;
    unsigned int typeCount = data.GetDataGroupsMatchingName(L"CHUNKTYPE", &groups);
    for (unsigned int i = 0; i < typeCount; ++i) {
        CDataGroup* group = groups[i];
        std::wstring name = EMPTY_WSTRING;
        name = group->GetDataValue(L"NAME", name);
        CChunkType* type = new CChunkType;
        type->m_entranceChunk = false;
        type->m_exitChunk = false;
        type->m_registeredWithRandomizers = false;
        type->m_mustPlace = false;
        type->m_folder = name;
        type->m_name = name;
        type->m_exits.setGrowBy(10);
        type->m_mustPlace = group->GetDataValue(L"MUST_PLACE", false);
        type->m_entranceChunk = group->GetDataValue(L"ENTRANCE_CHUNK", false);
        type->m_exitChunk = group->GetDataValue(L"EXIT_CHUNK", false);
        type->m_maxAppearance = group->GetDataValue(L"MAX_APPEARANCE", 10);
        type->m_folder = directory + group->GetDataValue(L"FOLDER", name);
        // The original uses OR here and appends even after an existing separator.
        if (type->m_folder[type->m_folder.length() - 1] != L'/' ||
            type->m_folder[type->m_folder.length() - 1] != L'\\')
            type->m_folder = type->m_folder + L"/";
        type->m_width = group->GetDataValue(L"WIDTH", 1);
        type->m_height = group->GetDataValue(L"HEIGHT", 1);
        if (type->m_mustPlace) m_requiredChunkTypes.add(type);
        std::vector<CDataGroup*> exitGroups;
        unsigned int exitCount = group->GetDataGroupsMatchingName(L"EXIT", &exitGroups);
        for (unsigned int j = 0; j < exitCount; ++j) {
            float x = exitGroups[j]->GetDataValue(L"X", 0.0f);
            float y = exitGroups[j]->GetDataValue(L"Y", 0.0f);
            float z = exitGroups[j]->GetDataValue(L"Z", 0.0f);
            type->m_exits.add(Ogre::Vector3(x, y, z));
        }
        m_chunkTypes.add(type);
        CDataGroup* inclusive = group->GetDataGroupByName(L"INCLUSIVE_FILES", false);
        if (inclusive) {
            CFileInfo chunkInfo;
            for (unsigned int j = 0; j < inclusive->GetNumberOfDataValues(); ++j) {
                CDataValue* value = inclusive->GetDataValue(j);
                if (value->GetValueType() == CDataValue::DATAVALUE_TRANSLATE ||
                    value->GetValueType() == CDataValue::DATAVALUE_STRING) {
                    std::wstring path = STRINGS::StringUpper(type->m_folder + value->GetValueString(true) + L".LAYOUT");
                    CFileSystem::getSingleton()->getFileInfo(path, chunkInfo, true, true, false);
                    if (chunkInfo.m_bExists) type->m_inclusiveFiles.add(path);
                }
            }
        }
        exitGroups.clear();
    }
    for (unsigned int i = 0; i < typeCount; ++i)
        m_chunkRandomizers.add(new CRandomizer(RANDOMIZER_NORMAL));
    groups.clear();

    TArrayList<std::wstring> files(25);
    for (unsigned int i = 0; i < m_chunkTypes.size(); ++i) {
        CChunkType* type = m_chunkTypes[i];
        files.clear();
        if (type->m_inclusiveFiles.size()) {
            for (unsigned int j = 0; j < type->m_inclusiveFiles.size(); ++j)
                files.add(type->m_inclusiveFiles[j]);
        } else {
            CFileSystem::getSingleton()->getFileList(type->m_folder, files, L"*.layout", false, true, false, false);
        }
        std::vector<std::wstring> sortedFiles;
        for (unsigned int j = 0; j < files.size(); ++j)
            if (files[j].find(L"/MERGE/") == std::wstring::npos)
                sortedFiles.push_back(files[j]);
        std::sort(sortedFiles.begin(), sortedFiles.end());
        for (unsigned int j = 0; j < sortedFiles.size(); ++j) {
            CChunk* chunk = new CChunk;
            chunk->m_chunkValue10 = i;
            chunk->m_odds = 1;
            chunk->m_maxAppearance = type->m_maxAppearance;
            chunk->m_filename = sortedFiles[j];
            m_chunkRandomizers[i]->addChoice(m_chunks.size(), 1);
            m_chunks.add(chunk);
            if (!type->m_registeredWithRandomizers) {
                type->m_registeredWithRandomizers = true;
                if (type->m_entranceChunk) {
                    m_entranceChunkRandomizer.addChoice(i, 1);
                } else if (!type->m_exitChunk) {
                    m_generalChunkRandomizer.addChoice(i, 1);
                    if (type->m_exits.size() == 1) {
                        float z = static_cast<float>(type->m_height) * m_tileBasis * m_chunkHeightBasis * -0.5f + type->m_exits[0].z;
                        float x = type->m_exits[0].x;
                        if (z > 0.0f && z > ::fabsf(x)) m_randomizer378.addChoice(i, 1);
                        else if (z < 0.0f && ::fabsf(z) > ::fabsf(x)) m_randomizer3E0.addChoice(i, 1);
                        else if (x > 0.0f && x > ::fabsf(z)) m_randomizer4B0.addChoice(i, 1);
                        else if (x < 0.0f && ::fabsf(x) > ::fabsf(z)) m_randomizer448.addChoice(i, 1);
                    }
                } else if (type->m_exits.size() == 1) {
                    float z = static_cast<float>(type->m_height) * m_tileBasis * m_chunkHeightBasis * -0.5f + type->m_exits[0].z;
                    float x = type->m_exits[0].x;
                    if (z > 0.0f && z > ::fabsf(x)) m_randomizer1D8.addChoice(i, 1);
                    else if (z < 0.0f && ::fabsf(z) > ::fabsf(x)) m_randomizer240.addChoice(i, 1);
                    else if (x > 0.0f && x > ::fabsf(z)) m_randomizer310.addChoice(i, 1);
                    else if (x < 0.0f && ::fabsf(x) > ::fabsf(z)) m_randomizer2A8.addChoice(i, 1);
                }
            }
        }
    }
    groups.clear();
    m_layoutRandomizer = new CRandomizer(RANDOMIZER_NORMAL);
    if (m_chunks.size() == 0) return;
    unsigned int layoutCount = data.GetDataGroupsMatchingName(L"LAYOUT", &groups);
    for (unsigned int i = 0; i < layoutCount; ++i) {
        m_layoutRandomizer->addChoice(i, 1);
        CLevelLayout* layout = new CLevelLayout;
        layout->m_chunks.setGrowBy(10);
        layout->m_chunkInstances.setGrowBy(10);
        layout->m_seed = 0;
        m_layouts.add(layout);
        m_baseLayouts.add(layout);
        std::vector<unsigned int> appearances;
        for (unsigned int j = 0; j < m_chunks.size(); ++j) appearances.push_back(0);
        std::vector<CDataGroup*> randomGroups;
        unsigned int count = groups[i]->GetDataGroupsMatchingName(L"CHUNK_RANDOM", &randomGroups);
        for (unsigned int j = 0; j < count; ++j) {
            CDataGroup* group = randomGroups[j];
            std::wstring typeName = group->GetDataValue(L"TYPE", EMPTY_WSTRING);
            int typeIndex = -1;
            for (unsigned int k = 0; k < m_chunkTypes.size(); ++k) {
                if (m_chunkTypes[k]->m_name == typeName) {
                    typeIndex = k;
                    break;
                }
            }
            float x = group->GetDataValue(L"X", 0.0f);
            float y = group->GetDataValue(L"Y", 0.0f);
            float z = group->GetDataValue(L"Z", 0.0f);
            CChunkInstance* instance = new CChunkInstance;
            instance->m_chunkTypeIndex = typeIndex;
            instance->m_name = EMPTY_WSTRING;
            instance->m_z = z;
            instance->m_y = y;
            instance->m_x = x;
            int choice = m_chunkRandomizers[instance->m_chunkTypeIndex]->getRandom();
            ++appearances[choice];
            CChunk* chunk = m_chunks[choice];
            if (appearances[choice] >= static_cast<unsigned int>(chunk->m_maxAppearance))
                m_chunkRandomizers[instance->m_chunkTypeIndex]->setChoiceOdds(choice, 0);
            layout->m_chunkInstances.add(instance);
            layout->m_chunks.add(chunk);
        }
        resetOdds();
        randomGroups.clear();
    }
    groups.clear();
}


bool CLevelTemplateData::intersectsChunks(CChunkInstance* chunk, std::vector<CChunkInstance*>& chunks)
{
    CChunkType* type = m_chunkTypes[chunk->m_chunkTypeIndex];
    float width = static_cast<float>(type->m_width);
    float pitch = m_chunkWidthBasis * m_tileBasis - 0.1f;
    float minX = -0.5f * pitch + chunk->m_x;
    float maxX = (width - 1.0f) * pitch + 0.5f * pitch + chunk->m_x;
    float minY = chunk->m_y + -1000.0f;
    float maxY = chunk->m_y + 1000.0f;
    float minZ = chunk->m_z + 0.0f;
    // The original uses width for the Z extent as well.
    float maxZ = m_chunkHeightBasis * width * m_tileBasis - 0.1f + chunk->m_z;
    for (int i = 0; i < static_cast<int>(chunks.size()); ++i) {
        CChunkInstance* other = chunks[i];
        CChunkType* otherType = m_chunkTypes[other->m_chunkTypeIndex];
        if (-0.5f * pitch + other->m_x > maxX) continue;
        if (other->m_y + -1000.0f > maxY) continue;
        if (other->m_z + 0.0f > maxZ) continue;
        float otherWidth = static_cast<float>(otherType->m_width);
        if (minX > (otherWidth - 1.0f) * pitch + 0.5f * pitch + other->m_x) continue;
        if (minY > other->m_y + 1000.0f) continue;
        if (minZ > otherWidth * m_chunkHeightBasis * m_tileBasis - 0.1f + other->m_z) continue;
        return true;
    }
    return false;
}

bool CLevelTemplateData::exitsMatch(CChunkInstance* chunk, std::vector<CChunkInstance*>& chunks)
{
    CChunkType* type = m_chunkTypes[chunk->m_chunkTypeIndex];
    if (static_cast<int>(type->m_exits.size()) <= 0) return true;
    float centerZ = static_cast<float>(type->m_height) * m_tileBasis * m_chunkHeightBasis * 0.5f + chunk->m_z;
    for (int i = 0; i < static_cast<int>(type->m_exits.size()); ++i) {
        const Ogre::Vector3& exit = type->m_exits[i];
        float x = exit.x + chunk->m_x;
        float y = exit.y + chunk->m_y;
        float z = chunk->m_z + exit.z;
        float dx = x - chunk->m_x;
        float dz = z - centerZ;
        if (dz > 0.0f && dz > ::fabsf(dx))
            z += 1.5f * m_tileBasis;
        else if (dz < 0.0f && ::fabsf(dz) > ::fabsf(dx))
            z += -1.5f * m_tileBasis;
        else if (dx > 0.0f && dx > ::fabsf(dz))
            x += 1.5f * m_tileBasis;
        else if (dx < 0.0f && ::fabsf(dx) > ::fabsf(dz))
            x += -1.5f * m_tileBasis;

        bool matched = true;
        for (int j = 0; j < static_cast<int>(chunks.size()); ++j) {
            CChunkInstance* other = chunks[j];
            CChunkType* otherType = m_chunkTypes[other->m_chunkTypeIndex];
            float pitch = m_chunkWidthBasis * m_tileBasis - 0.1f;
            bool inside = false;
            if (x >= -0.5f * pitch + other->m_x) {
                float width = static_cast<float>(otherType->m_width);
                inside = 0.5f * pitch + (width - 1.0f) * pitch + other->m_x >= x &&
                y >= -1000.0f + other->m_y &&
                1000.0f + other->m_y >= y &&
                z >= other->m_z + 0.0f &&
                width * m_chunkHeightBasis * m_tileBasis - 0.1f + other->m_z >= z;
            }
            if (inside) {
                matched = false;
                for (int k = 0; k < static_cast<int>(otherType->m_exits.size()); ++k) {
                    const Ogre::Vector3& otherExit = otherType->m_exits[k];
                    float distanceX = otherExit.x + other->m_x - x;
                    float distanceY = otherExit.y + other->m_y - y;
                    float distanceZ = otherExit.z + other->m_z - z;
                    float distance = ::sqrtf((distanceX * distanceX + distanceY * distanceY) + distanceZ * distanceZ);
                    if (m_tileBasis + m_tileBasis > distance) {
                        matched = true;
                        break;
                    }
                }
            }
            // An outside first peer accepts the exit; later outside peers do not.
            if (matched) break;
            matched = false;
        }
        if (!matched) return false;
    }
    return true;
}
