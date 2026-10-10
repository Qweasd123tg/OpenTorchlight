#include "DynamicLine.h"
#include <OgreVertexIndexData.h>



// Imported source candidates; historical status is not fresh acceptance.
void CDynamicLine::setOperationType(Ogre::RenderOperation::OperationType operationType)
{
    mRenderOp.operationType = operationType;
}

Ogre::RenderOperation::OperationType CDynamicLine::getOperationType() const
{
    return mRenderOp.operationType;
}

const Ogre::Vector3& CDynamicLine::getPoint(unsigned short index) const
{
    return m_points[index];
}

unsigned short CDynamicLine::getNumPoints() const
{
    return m_points.size();
}

void CDynamicLine::setPoint(unsigned short index, const Ogre::Vector3& point)
{
    m_points[index] = point;
    m_dirty = true;
}

void CDynamicLine::clear()
{
    m_points.clear();
    m_dirty = true;
}

void CDynamicLine::update()
{
    if (m_dirty) fillHardwareBuffers();
}

void CDynamicLine::createVertexDeclaration()
{
    mRenderOp.vertexData->vertexDeclaration->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION, 0);
}

void CDynamicLine::addPoint(float x, float y, float z)
{
    m_points.push_back(Ogre::Vector3(x, y, z));
    m_dirty = true;
}

void CDynamicLine::addPoint(const Ogre::Vector3& point)
{
    m_points.push_back(point);
    m_dirty = true;
}
