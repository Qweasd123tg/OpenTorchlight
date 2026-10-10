#ifndef ROOMPIECE_H
#define ROOMPIECE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "GameEnums.h"
#include "GenericModel.h"
#include "MasterResourceManager.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iCollision.h"
#include "iHighlight.h"
#include "iSnap.h"

class CRoomPiece : public CPositionableObject, public iSnap, public iHighlight, public iCollision
{
public:
    virtual ~CRoomPiece();
    virtual void setParentGuid(long long);
    virtual void setVisible(bool);
    virtual void scaleUpdated(const Ogre::Vector3&);
    virtual TArrayList<float>* getSnapValues(ESNAP_TYPES);
    virtual void setHighlighted(bool);
    virtual void getCollisionMesh();
    char getRoomPieceIsScalable();
    int getVisualMeshCountInRoomPiece();
    void clearCollisionData();
    bool getRoomPieceIsAnimated();
    void updateAnimation(float);
    CRoomPiece(CResourceManager*);
    void resetRoomPiece();
    void setCollisionMeshFilePath(const std::wstring&);
    void setMeshFilePath(const std::wstring&);
    void initRoomPiece();
    void setRoomPieceGuid(long long);
    void selectNewVisualIndex();

    // fields
    long long m_iCollisionMesh;
    CGenericModel* m_pGenericModel;
    void* m_pUnknown128;
    CMasterResourceManager* m_pMasterResourceManager;
    int m_iVisualIndex;
    unsigned char m_gap13C[0x4] __attribute__((aligned(4)));
    long long m_iVisualIndex_140;
    void* m_pRoomPieceName;
    bool m_bCollisionEnabled;
    bool m_bUnknown151;
    bool m_bUnknown152;
    bool m_bIsBakeable;
    bool m_bUnknown154;
    bool m_bVisibleOnMap;
    unsigned char m_gap156[0x2];
    int m_iUnknown158;
    bool m_bUnknown15C;
    bool m_bUnknown15D;

public:
    // Inline accessors behind the descriptors' property functions.
    void setCollisionEnabled(bool value) { m_bCollisionEnabled = value; }
    void setVisibleOnMap(bool value) { m_bVisibleOnMap = value; }
    int getVisualIndex() const { return m_iVisualIndex; }
    bool getVisibleOnMap() const { return m_bVisibleOnMap; }
    bool getCollisionEnabled() const { return m_bCollisionEnabled; }
};

#endif
