#ifndef LEVELTEMPLATEDATA_H
#define LEVELTEMPLATEDATA_H
#include "RunicCore.h"
#include <string>
#include "TArrayList.h"
#include "Randomizer.h"
#include "GameEnums.h"
class CLevelLayout;
class CChunk : public CRunicCore
{
public:
    virtual ~CChunk();
    int m_chunkValue10;
    int m_odds;
};
struct CLevelCreationRange { float minimum, maximum; };
// Partial: 0x778 bytes, UNIT_LIGHT_FADE is named from load()'s data key.
class CLevelTemplateData : public CRunicCore
{
public:
    bool permitsPortal() const { return m_permitsPortal; }
    bool isTown() const { return m_isTown; }

    float getSightRangeModifier() const { return m_sightRangeModifier; }

    CChunk* getRandomChunk(unsigned int index);
    CLevelLayout* getRandomLayout();
    void resetOdds();
    unsigned int getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION creation,unsigned int area);

    virtual ~CLevelTemplateData();
    bool getUnitLightFade() const { return m_bUnitLightFade; }
private:
    unsigned char m_Padding10[0x18];
    TArrayList<CChunk*> m_chunks; // +0x28
    unsigned char m_Padding40[0x44];
    bool m_permitsPortal; // +0x84
    unsigned char m_Padding85;
    bool m_isTown; // +0x86
    unsigned char m_Padding87[0x11];
    float m_sightRangeModifier; // +0x98
    unsigned char m_Padding9C[0x1c];
    TArrayList<CLevelLayout*> m_layouts; // +0xb8
    unsigned char m_PaddingD0[0x18];
    CRandomizer* m_layoutRandomizer; // +0xe8
    TArrayList<CRandomizer*> m_chunkRandomizers; // +0xf0
    unsigned char m_Padding108[0x4d4];
    CLevelCreationRange m_densityRanges[11]; // +0x5dc
    CLevelCreationRange m_countRanges[11]; // +0x634
    unsigned char m_Padding68C[0x4c];
public:
    std::wstring m_sRimlightTexture;
private:
    unsigned char m_TemplateData6E0[0x763-0x6e0];
    bool m_bUnitLightFade;
    unsigned char m_TemplateData764[0x778-0x764];
};
#endif
