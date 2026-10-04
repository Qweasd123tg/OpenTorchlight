#ifndef FORMATIONNODE_H
#define FORMATIONNODE_H

#include <string>

#include "PositionableObject.h"
#include "iLevelUpdate.h"

namespace Ogre {
    class Camera;
    class Vector3;
}

class CEditorScene;
class CResourceManager;
class CFormationNodeSaveAndLoad;

class CFormationNode : public CPositionableObject, public iLevelUpdate
{
public:
    virtual ~CFormationNode();

    virtual long long updateLevelObject(
        float fTime,
        Ogre::Camera* pCamera,
        const Ogre::Vector3& vTargetPosition);

    void setLayoutFile(
        const std::wstring& layoutFile,
        CResourceManager* pResourceManager);

    CFormationNode(
        CResourceManager* pResourceManager,
        CFormationNodeSaveAndLoad* pSaveAndLoad);

    bool m_bActivationStarted;
    unsigned char m_alignmentPadding[7];
    CEditorScene* m_pEditorScene;
};

#endif
