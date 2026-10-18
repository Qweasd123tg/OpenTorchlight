#include "DynamicRenderable.h"

Ogre::Real CDynamicRenderable::getBoundingRadius() const
{
    return sqrtf(std::max(mBox.getMaximum().squaredLength(),
                          mBox.getMinimum().squaredLength()));
}

#include <OgreCamera.h>

Ogre::Real CDynamicRenderable::getSquaredViewDepth(const Ogre::Camera* camera) const
{
    Ogre::Vector3 center = mBox.getMinimum() +
        (mBox.getMaximum() - mBox.getMinimum()) * 0.5f;
    return (camera->getDerivedPosition() - center).squaredLength();
}

#include <OgreHardwareBufferManager.h>

CDynamicRenderable::CDynamicRenderable()
    : Ogre::SimpleRenderable()
{
}

CDynamicRenderable::~CDynamicRenderable()
{
    if (mRenderOp.vertexData) {
        delete mRenderOp.vertexData;
        mRenderOp.vertexData = NULL;
    }
    if (mRenderOp.indexData) {
        delete mRenderOp.indexData;
        mRenderOp.indexData = NULL;
    }
}

void CDynamicRenderable::initialize(Ogre::RenderOperation::OperationType type, bool useIndices)
{
    mRenderOp.operationType = type;
    mRenderOp.useIndexes = useIndices;
    mRenderOp.vertexData = new Ogre::VertexData;
    if (useIndices)
        mRenderOp.indexData = new Ogre::IndexData;
    m_vertexCapacity = m_indexCapacity = 0;
    createVertexDeclaration();
}

void CDynamicRenderable::prepareHardwareBuffers(size_t vertexCount, size_t indexCount)
{
    size_t capacity = m_vertexCapacity;
    if (vertexCount > capacity || !capacity) {
        if (!capacity)
            capacity = 1;
        while (vertexCount > capacity)
            capacity <<= 1;
    } else if (vertexCount < capacity / 2) {
        while (vertexCount < capacity / 2)
            capacity >>= 1;
    }
    if (capacity != m_vertexCapacity) {
        m_vertexCapacity = capacity;
        mRenderOp.vertexData->vertexBufferBinding->setBinding(0,
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                mRenderOp.vertexData->vertexDeclaration->getVertexSize(0), m_vertexCapacity,
                Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY, false));
    }
    mRenderOp.vertexData->vertexCount = vertexCount;
    if (mRenderOp.useIndexes) {
        capacity = m_indexCapacity;
        if (indexCount > capacity || !capacity) {
            if (!capacity)
                capacity = 1;
            while (indexCount > capacity)
                capacity <<= 1;
        } else if (indexCount < capacity / 2) {
            while (indexCount < capacity / 2)
                capacity >>= 1;
        }
        if (capacity != m_indexCapacity) {
            m_indexCapacity = capacity;
            mRenderOp.indexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
                Ogre::HardwareIndexBuffer::IT_16BIT, m_indexCapacity,
                Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY, false);
        }
        mRenderOp.indexData->indexCount = indexCount;
    }
}
