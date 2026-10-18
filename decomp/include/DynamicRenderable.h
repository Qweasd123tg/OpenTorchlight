#ifndef OTL_DYNAMIC_RENDERABLE_H
#define OTL_DYNAMIC_RENDERABLE_H
#include <OgreSimpleRenderable.h>
class CDynamicRenderable : public Ogre::SimpleRenderable {
public:
    CDynamicRenderable();
    void initialize(Ogre::RenderOperation::OperationType operationType, bool useIndices);
    void prepareHardwareBuffers(size_t vertexCount, size_t indexCount);
    virtual ~CDynamicRenderable();
    virtual Ogre::Real getBoundingRadius() const;
    virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera*) const;
    virtual void createVertexDeclaration()=0;
    virtual void fillHardwareBuffers()=0;
protected:
    size_t m_vertexCapacity;
    size_t m_indexCapacity;
};
typedef char check_dynamic_renderable_size[sizeof(CDynamicRenderable)==0x218?1:-1];
#endif
