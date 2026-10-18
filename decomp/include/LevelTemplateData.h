#ifndef LEVELTEMPLATEDATA_H
#define LEVELTEMPLATEDATA_H
#include "RunicCore.h"
#include <string>
#include <vector>
#include <OgreVector3.h>
#include "TArrayList.h"
#include "Randomizer.h"
#include "GameEnums.h"
class CResourceManager;
class CChunk : public CRunicCore
{
public:
    virtual ~CChunk();
    int m_chunkValue10;
    int m_odds;
    int m_maxAppearance; // +0x18
    std::wstring m_filename; // +0x20
};

class CChunkType : public CRunicCore
{
public:
    virtual ~CChunkType();
    bool m_entranceChunk; // +0x10
    bool m_exitChunk; // +0x11
    bool m_registeredWithRandomizers; // +0x12
    bool m_mustPlace; // +0x13
    int m_width; // +0x14
    int m_height; // +0x18
    int m_maxAppearance; // +0x1c
    std::wstring m_folder; // +0x20
    TArrayList<std::wstring> m_inclusiveFiles; // +0x28
    std::wstring m_name; // +0x40
    // ABI representation: three floats per exit. Original aggregate name unresolved.
    TArrayList<Ogre::Vector3> m_exits; // +0x48
};

class CChunkInstance : public CRunicCore
{
public:
    virtual ~CChunkInstance();
    int m_chunkTypeIndex; // +0x10; source signedness unresolved
    std::wstring m_name; // +0x18; owning string, semantic name unresolved
    float m_x; // +0x20
    float m_y; // +0x24
    float m_z; // +0x28
    std::vector<int> m_usedExits; // +0x30
};

class CLevelLayout : public CRunicCore
{
public:
    virtual ~CLevelLayout();
    TArrayList<CChunk*> m_chunks; // +0x10; non-owning pointees
    TArrayList<CChunkInstance*> m_chunkInstances; // +0x28; owning pointees
    int m_seed; // +0x40
};
struct CLevelCreationRange { float minimum, maximum; };
// Owning layout: 0x778 bytes. Some trivial members retain descriptive or offset names.
class CLevelTemplateData : public CRunicCore
{
    friend class CLevel;
public:
    CLevelTemplateData(wchar_t const* filename);
    void load(wchar_t const* filename);
    bool permitsPortal() const { return m_permitsPortal; }
    bool isTown() const { return m_isTown; }
    bool getQuestSelectionExcluded() const { return m_questSelectionExcluded; }

    float getSightRangeModifier() const { return m_sightRangeModifier; }

    CChunk* getRandomChunk(unsigned int index);
    CLevelLayout* getRandomLayout();
    // ABI-preserving reconstruction: normal return carries the input seed bits.
    int createRandomLayout(int seed);
    void matchExits(CChunkInstance* chunk, std::vector<CChunkInstance*>& chunks);
    bool intersectsChunks(CChunkInstance* chunk, std::vector<CChunkInstance*>& chunks);
    bool exitsMatch(CChunkInstance* chunk, std::vector<CChunkInstance*>& chunks);
    void resetOdds();
    void chooseUnitSpawners(CResourceManager* resourceManager);
    unsigned int getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION creation,unsigned int area);

    virtual ~CLevelTemplateData();
    bool getUnitLightFade() const { return m_bUnitLightFade; }
private:
    friend class CGameUI;
    friend class CMusicObject;
    friend class CDungeon;
    friend class CQuestUnitData;
    TArrayList<CChunkType*> m_chunkTypes; // +0x10; owning pointees
    TArrayList<CChunk*> m_chunks; // +0x28
    TArrayList<CChunkType*> m_requiredChunkTypes; // +0x40; non-owning pointees
    bool m_randomized; // +0x58
    bool m_requiresExit; // +0x59
    bool m_dontStore; // +0x5a
    std::wstring m_string60; // +0x60; owning string, semantic name unresolved
    std::wstring m_name; // +0x68
    bool m_hasPathing; // +0x70
    bool m_hasAutomap; // +0x71
    bool m_populate; // +0x72
    int m_minChunks; // +0x74
    int m_maxChunks; // +0x78
    int m_monsterLevelMin; // +0x7c
    int m_monsterLevelMax; // +0x80
    bool m_permitsPortal; // +0x84
    bool m_permitsPetDeparture; // +0x85, checked by CGameUI::onClick
    bool m_isTown; // +0x86
    bool m_questSelectionExcluded; // +0x87, checked by CQuest::reinitializeQuest
    float m_tileBasis; // +0x88
    float m_chunkWidthBasis; // +0x8c
    float m_chunkHeightBasis; // +0x90
    float m_cameraMultiplier; // +0x94
    float m_sightRangeModifier; // +0x98
    std::wstring m_automap; // +0xa0
    float m_automapWidth; // +0xa8
    float m_automapHeight; // +0xac
    float m_automapAngle; // +0xb0
    TArrayList<CLevelLayout*> m_layouts; // +0xb8
    TArrayList<CLevelLayout*> m_baseLayouts; // +0xd0; non-owning pointees
    CRandomizer* m_layoutRandomizer; // +0xe8
    TArrayList<CRandomizer*> m_chunkRandomizers; // +0xf0
    CRandomizer m_generalChunkRandomizer; // +0x108
    CRandomizer m_entranceChunkRandomizer; // +0x170
    CRandomizer m_randomizer1D8; // +0x1d8; directional pool
    CRandomizer m_randomizer240; // +0x240; directional pool
    CRandomizer m_randomizer2A8; // +0x2a8; directional pool
    CRandomizer m_randomizer310; // +0x310; directional pool
    CRandomizer m_randomizer378; // +0x378; directional pool
    CRandomizer m_randomizer3E0; // +0x3e0; directional pool
    CRandomizer m_randomizer448; // +0x448; directional pool
    CRandomizer m_randomizer4B0; // +0x4b0; directional pool
    std::wstring m_music; // +0x518
    std::wstring m_unitSpawnerNames[11]; // +0x520
    std::wstring m_selectedUnitSpawners[11]; // +0x578, owning selection results
    bool m_useSpawnClass[11]; // +0x5d0
    CLevelCreationRange m_densityRanges[11]; // +0x5dc
    CLevelCreationRange m_countRanges[11]; // +0x634
    float m_regionBoundsX; // +0x68c
    float m_regionBoundsY; // +0x690
    float m_regionBoundsZ; // +0x694
    std::wstring m_cinematic; // +0x698
    std::wstring m_skybox; // +0x6a0
    std::wstring m_levelParticle; // +0x6a8
    std::wstring m_water; // +0x6b0
    std::wstring m_postWater; // +0x6b8
    std::wstring m_midWater; // +0x6c0
    std::wstring m_filename; // +0x6c8
    std::wstring m_torchlightTexture; // +0x6d0
public:
    std::wstring m_sRimlightTexture;
private:
    std::wstring m_shadowFadeTexture; // +0x6e0
    std::wstring m_lightMaskTexture; // +0x6e8
    std::wstring m_mainMenuRules; // +0x6f0
    float m_fogStart; // +0x6f8
    float m_fogEnd; // +0x6fc
    // Scalar fields preserve observed member initialization order before m_levelName.
    float m_lightmapColorR; // +0x700
    float m_lightmapColorG; // +0x704
    float m_lightmapColorB; // +0x708
    float m_lightmapColorA; // +0x70c
    float m_fogColorR; // +0x710
    float m_fogColorG; // +0x714
    float m_fogColorB; // +0x718
    float m_fogColorA; // +0x71c
    float m_ambientColorR; // +0x720
    float m_ambientColorG; // +0x724
    float m_ambientColorB; // +0x728
    float m_ambientColorA; // +0x72c
    float m_materialAmbientColorR; // +0x730
    float m_materialAmbientColorG; // +0x734
    float m_materialAmbientColorB; // +0x738
    float m_materialAmbientColorA; // +0x73c
    float m_directionalColorR; // +0x740
    float m_directionalColorG; // +0x744
    float m_directionalColorB; // +0x748
    float m_directionalColorA; // +0x74c
    float m_directionalX; // +0x750
    float m_directionalY; // +0x754
    float m_directionalZ; // +0x758
    float m_directionalIntensity; // +0x75c
    bool m_orthographicShadows; // +0x760
    bool m_state761; // +0x761; semantic name unresolved
    bool m_randomLayoutGenerated; // +0x762
    bool m_bUnitLightFade;
    float m_unitFadeDistance; // +0x764
    float m_unitFadeStart; // +0x768
    bool m_showFloorNumber; // +0x76c
    std::wstring m_levelName; // +0x770
};
#endif
