 CollisionModelRef::~CollisionModelRef()
{
    if (m_pCollisionModel) { delete m_pCollisionModel; m_pCollisionModel = NULL; }
}
