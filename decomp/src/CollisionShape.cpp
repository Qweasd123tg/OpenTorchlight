#include "CollisionShape.h"

void CCollisionShape::update(float)
{
}
void CCollisionShape::updateCollision()
{
    if (!m_pResourceManager->getEditorIsRunning())
        getEnabled();
}
void CCollisionShape::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (enabled)
        BroadcastEvent(6);
    else
        BroadcastEvent(7);
    updateCollision();
}

CCollisionShape::CCollisionShape(CResourceManager* resources) : CShape(resources)
{
    setEnabled(true);
}

CCollisionShape::~CCollisionShape()
{
    setEnabled(false);
}
