#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include "RunicCore.h"

enum ENodeDirection
{
    NODE_ANY, NODE_NORTH, NODE_SOUTH, NODE_EAST, NODE_WEST,
    NODE_NORTHEAST, NODE_NORTHWEST, NODE_SOUTHEAST, NODE_SOUTHWEST
};

class CAstarPathfinder : public CRunicCore
{
public:
    class CAstarNode
    {
    public:
        float m_fTotalCost;
        float m_fGoalCost;
        float m_fPathCost;
        int m_iX;
        int m_iY;
        unsigned int m_iTile;
        CAstarNode* m_pParent;
        CAstarNode* m_pChildren[8];
        CAstarNode* m_pNext;
    };

    // The propagation stack consists of unsymbolized two-pointer records.
    struct NodeStack
    {
        CAstarNode* m_pNode;
        NodeStack* m_pNext;
    };

    CAstarPathfinder(float, float, unsigned int, unsigned int, short**, short**, float);
    virtual ~CAstarPathfinder();
    bool reachedGoal();
    unsigned int tileIndex(unsigned int, unsigned int);
    bool tileFree(unsigned int, unsigned int, ENodeDirection);
    void advanceNextNode();
    float getNodeX();
    float getNodeY();
    float getNextNodeX();
    float getNextNodeY();
    CAstarNode* reverseNodes(CAstarNode*);
    CAstarNode* returnBestNode();
    CAstarNode* openNode(unsigned int);
    CAstarNode* closedNode(unsigned int);
    void insert(CAstarNode*);
    CAstarNode* pop();
    void freeNodes();
    void push(CAstarNode*);
    void propagateDown(CAstarNode*);
    void generateSuccessor(CAstarNode*, unsigned int, unsigned int, unsigned int, unsigned int);
    void generateSuccessors(CAstarNode*, unsigned int, unsigned int);
    void createPath(int, int, int, int, bool);
    void findNearestWideOpen(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&);
    void findNearestOpen(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&);
    void findNearestOpenDirected(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&);
    bool findPath(float, float, float, float);

    CAstarNode* m_pClosest;
    CAstarNode* m_pOpen;
    CAstarNode* m_pClosed;
    CAstarNode* m_pCurrent;
    NodeStack* m_pStack;
    bool m_bPathFound;
    unsigned int m_iHeight;
    unsigned int m_iWidth;
    float m_fTileSize;
    unsigned int m_iTileCount;
    short** m_pTiles;
    short** m_pOccupiedTiles;
    float m_fOriginX;
    float m_fOriginY;
    bool m_bGoalBlocked;
    bool m_bIgnoreOccupancy;
    bool m_bCompletePath;
    int m_iMaxIterations;
};

#endif
