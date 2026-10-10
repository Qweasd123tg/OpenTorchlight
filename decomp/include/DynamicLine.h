#ifndef OTL_DYNAMIC_LINE_H
#define OTL_DYNAMIC_LINE_H
#include "DynamicRenderable.h"
#include <vector>
class CDynamicLine : public CDynamicRenderable {
public:
    virtual ~CDynamicLine();
    virtual void fillHardwareBuffers();
    void setOperationType(Ogre::RenderOperation::OperationType operationType);
    Ogre::RenderOperation::OperationType getOperationType() const;
    const Ogre::Vector3& getPoint(unsigned short index) const;
    unsigned short getNumPoints() const;
    void setPoint(unsigned short index, const Ogre::Vector3& point);
    void clear();
    void update();
    virtual void createVertexDeclaration();
    void addPoint(float x, float y, float z);
    void addPoint(const Ogre::Vector3& point);
private:
    std::vector<Ogre::Vector3> m_points;
    bool m_dirty;
};
typedef char check_dynamic_line_size[sizeof(CDynamicLine)==0x238?1:-1];
#endif
