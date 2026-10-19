#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <OgreVector3.h>
#include "RunicCore.h"

// Both template types inherit CRunicCore (native RTTI fd6c40/fd6be0).
template<class T> class CQuadtreeNode : public CRunicCore
{
public:
    virtual ~CQuadtreeNode();
    void addData(T, const Ogre::Vector3&, const Ogre::Vector3&, float);
    void sort(const Ogre::Vector3&, const Ogre::Vector3&, bool, std::vector<T>&);

    Ogre::Vector3 m_maximum; // +0x10
    Ogre::Vector3 m_minimum; // +0x1c
    bool m_subdivided; // +0x28
    CQuadtreeNode<T>* m_children[4]; // +0x30
    std::vector<T> m_data; // +0x50
    std::vector<Ogre::Vector3> m_dataMinimum; // +0x68
    std::vector<Ogre::Vector3> m_dataMaximum; // +0x80; sizeof 0x98
};

template<class T> class CQuadtree : public CRunicCore
{
public:
    virtual ~CQuadtree();

    float m_minimumCellSize; // +0x10
    Ogre::Vector3 m_minimum; // +0x14
    Ogre::Vector3 m_maximum; // +0x20
    CQuadtreeNode<T>* m_root; // +0x30; sizeof 0x38
};

#endif
