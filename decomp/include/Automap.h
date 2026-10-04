#ifndef AUTOMAP_H
#define AUTOMAP_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreBillboard.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <string>
#include "ResourceManager.h"
#include "RunicCore.h"

class CAutomap : public CRunicCore
{
public:
    virtual ~CAutomap();
    void clear();
    void setRevealed(int, int, float);
    int getRevealed(int, int);
    void clearNPCIcons();
    void setNPCBillboardVisible(Ogre::Billboard*, bool);
    void finalize();
    void setPetPosition(const Ogre::Vector3&);
    void setPlayerPosition(const Ogre::Vector3&);
    void setPetVisible(bool);
    void update(const Ogre::Vector3&, float);
    void zoom(float);
    void setVisible(bool);
    void setFullscreen(bool);
    void* addTile(int, const Ogre::Vector3&, const Ogre::Vector3&, bool, bool);
    CAutomap(CResourceManager*, Ogre::SceneManager*);
    void setFullMap(std::wstring, float, float, Ogre::Vector3&, Ogre::Vector3&, float);

    // fields
    CResourceManager* m_pResourceManager;
    void* m_pUnknown18;
    void* m_pUnknown20;
    void* m_pUnknown28;
    void* m_pUnknown30;
    void* m_pUnknown38;
    void* m_pUnknown40;
    long long m_iUnknown48;
    unsigned char m_Unknown50[0x18] __attribute__((aligned(8)));
    bool m_bUnknown68;
    unsigned char m_gap69[0x7];
    long long m_iUnknown70;
    unsigned char m_Unknown78[0x18] __attribute__((aligned(8)));
    int m_iUnknown90;
    int m_iUnknown94;
    void* m_pUnknown98;
    bool m_bUnknownA0;
    bool m_bUnknownA1;
    bool m_bUnknownA2;
    unsigned char m_gapA3[0x5];
    void* m_pUnknownA8;
    long long m_iUnknownB0;
    void* m_pUnknownB8;
    void* m_pUnknownC0;
    long long m_iUnknownC8;
    void* m_pUnknownD0;
    void* m_pUnknownD8;
    long long m_iUnknownE0;
    long long m_iUnknownE8;
    long long m_iUnknownF0;
    long long m_iUnknownF8;
    long long m_iUnknown100;
    unsigned char m_Unknown108[0x18] __attribute__((aligned(8)));
    void* m_pUnknown120;
    long long m_iUnknown128;
    long long m_Unknown130;
    long long m_iUnknown138;
    void* m_pUnknown140;
    int m_iUnknown148;
    unsigned char m_gap14C[0x4] __attribute__((aligned(4)));
    void* m_pUnknown150;
    long long m_iUnknown158;
    long long m_Unknown160;
    long long m_iUnknown168;
    void* m_pUnknown170;
    int m_iUnknown178;
};

#endif
