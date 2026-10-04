#ifndef PATHNODE_H
#define PATHNODE_H

#include <OgreVector3.h>
#include <string>

#include "PositionableObject.h"

class CPathController;
class CResourceManager;
class CTextEvent;

class CPathNode : public CPositionableObject
{
public:
    virtual ~CPathNode();

    virtual void setVisible(bool bVisible);
    virtual void positionUpdated(const Ogre::Vector3& position);

    void setText(const std::wstring& text);
    CPathNode(CPathController* pathController, CResourceManager* resourceManager);

    CPathController* m_pPathController;
    CTextEvent* m_pTextEvent;
    std::wstring m_sText;
    long long m_iReservedState;
    long long m_iReservedValue;
};

#endif
