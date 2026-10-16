#ifndef INTERACT_H
#define INTERACT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "iMenuListener.h"
#include "BaseUnit.h"
#include "Graph.h"
#include "SafePointer.h"

class CDataGroup;

class CInteract : public CEditorBaseObject, public iMenuListener
{
public:
    virtual ~CInteract();
    virtual void menuEventOccured(void*, EMENU_TYPE, EMENU_EVENT);
    void update(float);
    void setUnitInteractWithByIndex(unsigned int, std::wstring);
    void configureSpecificUnitIndex(EINTERACTABLE_UNITS);
    void interactWithUnit(EINTERACTABLE_UNITS);
    void configureUnitsInLevel();
    CInteract(CResourceManager*);

    // fields
    std::wstring m_sUnknown60;
    CResourceManager* m_pResourceManager;
    std::wstring m_pUnknown70;
    std::wstring m_sUnknown78;
    CDataGroup* m_pUnitDataGroup;
    TSafePointer<CBaseUnit> m_unit;
    float m_fUnknown98;
    float m_fUnknown9C;
    float m_fUnknownA0;
    float m_fUnknownA4;
    float m_fUnknownA8;
    float m_fUnknownAC;
    float m_fUnknownB0;
    float m_fUnknownB4;
    float m_fUnknownB8;
    float m_fUnknownBC;
    int m_UnknownC0;
    unsigned char m_gapC4[0x4] __attribute__((aligned(4)));
    CGraph m_cameraGraph;
    int m_iUnknown120;
};

#endif
