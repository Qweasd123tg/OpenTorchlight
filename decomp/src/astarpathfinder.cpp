#include "EmptyStrings.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "AstarPathfinder.h"

CAstarPathfinder::CAstarPathfinder(float fOriginX, float fOriginY,
    unsigned int iWidth, unsigned int iHeight, short** pTiles,
    short** pOccupiedTiles, float fTileSize) : CRunicCore()
{
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_fTileSize = fTileSize;
    m_pTiles = pTiles;
    m_pOccupiedTiles = pOccupiedTiles;
    m_iTileCount = iWidth * iHeight;
    m_fOriginX = fOriginX;
    m_fOriginY = fOriginY;
    m_pClosest = NULL;
    m_pOpen = NULL;
    m_pClosed = NULL;
    m_pCurrent = NULL;
    m_bPathFound = false;
    m_bGoalBlocked = false;
    m_bIgnoreOccupancy = false;
    m_bCompletePath = true;
    m_iMaxIterations = 150;
    m_pStack = static_cast<NodeStack*>(calloc(1, sizeof(NodeStack)));
}

CAstarPathfinder::~CAstarPathfinder()
{
    freeNodes();
    free(m_pStack);
    free(m_pOpen);
    free(m_pClosed);
    m_pTiles = NULL;
    m_pOccupiedTiles = NULL;
}

bool CAstarPathfinder::reachedGoal()
{
    if (m_bPathFound)
        return m_pCurrent->m_pParent == NULL;
    return true;
}

unsigned int CAstarPathfinder::tileIndex(unsigned int iX, unsigned int iY)
{
    return iY * m_iWidth + iX;
}

bool CAstarPathfinder::tileFree(unsigned int iX, unsigned int iY, ENodeDirection)
{
    if (iX < m_iWidth && iY < m_iHeight && m_pTiles[iX][iY] < 1)
    {
        if (m_bIgnoreOccupancy)
            return true;
        return m_pOccupiedTiles[iX][iY] < 1;
    }
    return false;
}

void CAstarPathfinder::advanceNextNode()
{
    m_pCurrent = m_pCurrent->m_pParent;
}

float CAstarPathfinder::getNodeX()
{
    return float(m_pCurrent->m_iX) * m_fTileSize + m_fTileSize * 0.5f + m_fOriginX;
}

float CAstarPathfinder::getNodeY()
{
    return float(m_pCurrent->m_iY) * m_fTileSize + m_fTileSize * 0.5f + m_fOriginY;
}

float CAstarPathfinder::getNextNodeX()
{
    return float(m_pCurrent->m_pParent->m_iX) * m_fTileSize + m_fTileSize * 0.5f + m_fOriginX;
}

float CAstarPathfinder::getNextNodeY()
{
    return float(m_pCurrent->m_pParent->m_iY) * m_fTileSize + m_fTileSize * 0.5f + m_fOriginY;
}

CAstarPathfinder::CAstarNode* CAstarPathfinder::reverseNodes(CAstarNode* pNode)
{
    if (pNode)
    {
        CAstarNode* pPrevious = NULL;
        CAstarNode* pNext = pNode->m_pParent;
        if (pNext)
        {
            do
            {
                pNode->m_pParent = pPrevious;
                pPrevious = pNode;
                pNode = pNext;
                pNext = pNode->m_pParent;
            } while (pNext);
        }
        pNode->m_pParent = pPrevious;
    }
    return pNode;
}

CAstarPathfinder::CAstarNode* CAstarPathfinder::returnBestNode()
{
    CAstarNode* pNode = m_pOpen->m_pNext;
    if (pNode)
    {
        m_pOpen->m_pNext = pNode->m_pNext;
        pNode->m_pNext = m_pClosed->m_pNext;
        m_pClosed->m_pNext = pNode;
        return pNode;
    }
    m_bPathFound = false;
    return NULL;
}

CAstarPathfinder::CAstarNode* CAstarPathfinder::openNode(unsigned int iTile)
{
    CAstarNode* pNode = m_pOpen->m_pNext;
    while (pNode)
    {
        if (pNode->m_iTile == iTile)
            return pNode;
        pNode = pNode->m_pNext;
    }
    return NULL;
}

CAstarPathfinder::CAstarNode* CAstarPathfinder::closedNode(unsigned int iTile)
{
    CAstarNode* pNode = m_pClosed->m_pNext;
    while (pNode)
    {
        if (pNode->m_iTile == iTile)
            return pNode;
        pNode = pNode->m_pNext;
    }
    return NULL;
}

void CAstarPathfinder::insert(CAstarNode* pNode)
{
    CAstarNode* pPrevious = m_pOpen;
    CAstarNode* pNext = pPrevious->m_pNext;
    if (pNext)
    {
        while (pNext && pNode->m_fTotalCost > pNext->m_fTotalCost)
        {
            pPrevious = pNext;
            pNext = pNext->m_pNext;
        }
        pNode->m_pNext = pNext;
    }
    pPrevious->m_pNext = pNode;
}

CAstarPathfinder::CAstarNode* CAstarPathfinder::pop()
{
    NodeStack* pEntry = m_pStack->m_pNext;
    CAstarNode* pNode = pEntry->m_pNode;
    m_pStack->m_pNext = pEntry->m_pNext;
    free(pEntry);
    return pNode;
}

void CAstarPathfinder::freeNodes()
{
    if (m_pOpen)
    {
        CAstarNode* pNode = m_pOpen->m_pNext;
        while (pNode)
        {
            CAstarNode* pNext = pNode->m_pNext;
            free(pNode);
            pNode = pNext;
        }
    }
    if (m_pClosed)
    {
        CAstarNode* pNode = m_pClosed->m_pNext;
        while (pNode)
        {
            CAstarNode* pNext = pNode->m_pNext;
            free(pNode);
            pNode = pNext;
        }
    }
}

void CAstarPathfinder::push(CAstarNode* pNode)
{
    NodeStack* pEntry = static_cast<NodeStack*>(calloc(1, sizeof(NodeStack)));
    pEntry->m_pNode = pNode;
    pEntry->m_pNext = m_pStack->m_pNext;
    m_pStack->m_pNext = pEntry;
}

void CAstarPathfinder::propagateDown(CAstarNode* pNode)
{
    float fCost = pNode->m_fPathCost;
    for (unsigned int i = 0; i < 8 && pNode->m_pChildren[i]; ++i)
    {
        CAstarNode* pChild = pNode->m_pChildren[i];
        float fNewCost = fCost + 1.0f;
        if (pChild->m_fPathCost > fNewCost)
        {
            pChild->m_fPathCost = fNewCost;
            pChild->m_pParent = pNode;
            pChild->m_fTotalCost = fNewCost + pChild->m_fGoalCost;
            push(pChild);
        }
    }
    while (m_pStack->m_pNext)
    {
        pNode = pop();
        for (unsigned int i = 0; i < 8 && pNode->m_pChildren[i]; ++i)
        {
            CAstarNode* pChild = pNode->m_pChildren[i];
            float fNewCost = pNode->m_fPathCost + 1.0f;
            if (pChild->m_fPathCost > fNewCost)
            {
                pChild->m_fPathCost = fNewCost;
                pChild->m_pParent = pNode;
                pChild->m_fTotalCost = fNewCost + pChild->m_fGoalCost;
                push(pChild);
            }
        }
    }
}

void CAstarPathfinder::generateSuccessor(CAstarNode* pParent, unsigned int iX,
    unsigned int iY, unsigned int iGoalX, unsigned int iGoalY)
{
    float fCost = pParent->m_fPathCost + 1.0f;
    unsigned int iTile = tileIndex(iX, iY);
    CAstarNode* pNode = openNode(iTile);
    if (pNode)
    {
        unsigned int i = 0;
        while (i < 8 && pParent->m_pChildren[i])
            ++i;
        pParent->m_pChildren[i] = pNode;
        if (pNode->m_fPathCost > fCost)
        {
            pNode->m_fPathCost = fCost;
            pNode->m_pParent = pParent;
            pNode->m_fTotalCost = fCost + pNode->m_fGoalCost;
        }
        return;
    }
    pNode = closedNode(iTile);
    if (pNode)
    {
        unsigned int i = 0;
        while (i < 8 && pParent->m_pChildren[i])
            ++i;
        pParent->m_pChildren[i] = pNode;
        if (pNode->m_fPathCost > fCost)
        {
            pNode->m_fPathCost = fCost;
            pNode->m_pParent = pParent;
            pNode->m_fTotalCost = fCost + pNode->m_fGoalCost;
            propagateDown(pNode);
        }
        return;
    }
    pNode = static_cast<CAstarNode*>(calloc(1, sizeof(CAstarNode)));
    pNode->m_pParent = pParent;
    pNode->m_fPathCost = fCost;
    pNode->m_iTile = iTile;
    pNode->m_iX = iX;
    pNode->m_iY = iY;
    float fDX = float(int(iX - iGoalX));
    float fDY = float(int(iY - iGoalY));
    pNode->m_fGoalCost = fDX * fDX + fDY * fDY;
    pNode->m_fTotalCost = fCost + pNode->m_fGoalCost;
    insert(pNode);
    unsigned int i = 0;
    while (i < 8 && pParent->m_pChildren[i])
        ++i;
    if (!m_pClosest || m_pClosest->m_fGoalCost > pNode->m_fGoalCost)
        m_pClosest = pNode;
    pParent->m_pChildren[i] = pNode;
}

void CAstarPathfinder::generateSuccessors(CAstarNode* pNode, unsigned int iGoalX, unsigned int iGoalY)
{
    unsigned int iX = pNode->m_iX;
    unsigned int iY = pNode->m_iY;
    if (tileFree(iX, iY - 1, NODE_NORTH))
    {
        if (tileFree(iX - 1, iY, NODE_WEST) && tileFree(iX - 1, iY - 1, NODE_NORTHWEST))
            generateSuccessor(pNode, iX - 1, iY - 1, iGoalX, iGoalY);
        if (tileFree(iX - 1, iY - 1, NODE_NORTH) || tileFree(iX + 1, iY - 1, NODE_NORTH))
            generateSuccessor(pNode, iX, iY - 1, iGoalX, iGoalY);
        if (tileFree(iX + 1, iY, NODE_EAST) && tileFree(iX + 1, iY - 1, NODE_NORTHEAST))
            generateSuccessor(pNode, iX + 1, iY - 1, iGoalX, iGoalY);
    }
    if ((tileFree(iX + 1, iY - 1, NODE_NORTH) || tileFree(iX + 1, iY + 1, NODE_NORTH)) &&
        tileFree(iX + 1, iY, NODE_EAST))
        generateSuccessor(pNode, iX + 1, iY, iGoalX, iGoalY);
    if (tileFree(iX, iY + 1, NODE_SOUTH))
    {
        if (tileFree(iX + 1, iY, NODE_EAST) && tileFree(iX + 1, iY + 1, NODE_SOUTHEAST))
            generateSuccessor(pNode, iX + 1, iY + 1, iGoalX, iGoalY);
        if (tileFree(iX - 1, iY + 1, NODE_NORTH) || tileFree(iX + 1, iY + 1, NODE_NORTH))
            generateSuccessor(pNode, iX, iY + 1, iGoalX, iGoalY);
        if (tileFree(iX - 1, iY, NODE_WEST) && tileFree(iX - 1, iY + 1, NODE_SOUTHWEST))
            generateSuccessor(pNode, iX - 1, iY + 1, iGoalX, iGoalY);
    }
    if ((tileFree(iX - 1, iY - 1, NODE_NORTH) || tileFree(iX - 1, iY + 1, NODE_NORTH)) &&
        tileFree(iX - 1, iY, NODE_WEST))
        generateSuccessor(pNode, iX - 1, iY, iGoalX, iGoalY);
}

void CAstarPathfinder::createPath(int iGoalX, int iGoalY, int iStartX, int iStartY, bool bReverse)
{
    unsigned int iGoal = tileIndex(iGoalX, iGoalY);
    m_pClosest = NULL;
    m_bPathFound = true;
    free(m_pOpen);
    free(m_pClosed);
    m_pOpen = static_cast<CAstarNode*>(calloc(1, sizeof(CAstarNode)));
    m_pClosed = static_cast<CAstarNode*>(calloc(1, sizeof(CAstarNode)));
    CAstarNode* pNode = static_cast<CAstarNode*>(calloc(1, sizeof(CAstarNode)));
    pNode->m_fPathCost = 0.0f;
    float fDX = float(iStartX - iGoalX);
    float fDY = float(iStartY - iGoalY);
    pNode->m_fGoalCost = fDX * fDX + fDY * fDY;
    pNode->m_fTotalCost = pNode->m_fGoalCost + 0.0f;
    pNode->m_iX = iStartX;
    pNode->m_iY = iStartY;
    pNode->m_iTile = tileIndex(iStartX, iStartY);
    m_pOpen->m_pNext = pNode;
    int iIterations = 0;
    while (true)
    {
        pNode = returnBestNode();
        if (m_bGoalBlocked && m_pClosest && m_pClosest->m_fGoalCost < 2.0f)
        {
            m_bCompletePath = false;
            pNode = m_pClosest;
            break;
        }
        if (!pNode || iIterations > m_iMaxIterations)
        {
            if (!m_pClosest)
                m_bPathFound = false;
            else
            {
                m_bCompletePath = false;
                pNode = m_pClosest;
            }
            break;
        }
        if (pNode->m_iTile == iGoal)
            break;
        ++iIterations;
        generateSuccessors(pNode, iGoalX, iGoalY);
    }
    if (bReverse)
        pNode = reverseNodes(pNode);
    m_pCurrent = pNode;
}

void CAstarPathfinder::findNearestWideOpen(unsigned int iFallbackX, unsigned int iFallbackY,
    unsigned int iX, unsigned int iY, unsigned int& iResultX, unsigned int& iResultY)
{
    float fTargetX = float(iX) * m_fTileSize + m_fOriginX;
    float fTargetY = float(iY) * m_fTileSize + m_fOriginY;
    float fBest = 9999.0f;
    for (int iTestX = int(iX - 16); iTestX <= int(iX + 16); ++iTestX)
        for (int iTestY = int(iY - 16); iTestY <= int(iY + 16); ++iTestY)
        {
            if (iTestY < 0 || iTestX < 0 || !tileFree(iTestX, iTestY, NODE_ANY) ||
                !tileFree(iTestX, iTestY - 1, NODE_ANY) || !tileFree(iTestX, iTestY + 1, NODE_ANY) ||
                !tileFree(iTestX - 1, iTestY, NODE_ANY) || !tileFree(iTestX + 1, iTestY, NODE_ANY))
                continue;
            float fDX = float(iTestX) * m_fTileSize + m_fOriginX - fTargetX;
            float fDY = float(iTestY) * m_fTileSize + m_fOriginY - fTargetY;
            float fDistance = sqrtf(fDX * fDX + 0.0f + fDY * fDY);
            if (fDistance < fBest)
            {
                iResultX = iTestX;
                iResultY = iTestY;
                fBest = fDistance;
            }
        }
    if (fBest == 9999.0f)
    {
        iResultX = iFallbackX;
        iResultY = iFallbackY;
    }
}

void CAstarPathfinder::findNearestOpen(unsigned int iFallbackX, unsigned int iFallbackY,
    unsigned int iX, unsigned int iY, unsigned int& iResultX, unsigned int& iResultY)
{
    float fTargetX = float(iX) * m_fTileSize + m_fOriginX;
    float fTargetY = float(iY) * m_fTileSize + m_fOriginY;
    float fBest = 9999.0f;
    for (int iTestX = int(iX - 16); iTestX <= int(iX + 16); ++iTestX)
        for (int iTestY = int(iY - 16); iTestY <= int(iY + 16); ++iTestY)
        {
            if (iTestY < 0 || iTestX < 0 || !tileFree(iTestX, iTestY, NODE_ANY))
                continue;
            float fDX = float(iTestX) * m_fTileSize + m_fOriginX - fTargetX;
            float fDY = float(iTestY) * m_fTileSize + m_fOriginY - fTargetY;
            float fDistance = sqrtf(fDX * fDX + 0.0f + fDY * fDY);
            if (fDistance < fBest)
            {
                iResultX = iTestX;
                iResultY = iTestY;
                fBest = fDistance;
            }
        }
    if (fBest == 9999.0f)
    {
        iResultX = iFallbackX;
        iResultY = iFallbackY;
    }
}

void CAstarPathfinder::findNearestOpenDirected(unsigned int iFallbackX, unsigned int iFallbackY,
    unsigned int iX, unsigned int iY, unsigned int& iResultX, unsigned int& iResultY)
{
    float fX = float(iX) * m_fTileSize + m_fOriginX;
    float fY = float(iY) * m_fTileSize + m_fOriginY;
    float fDX = float(iFallbackX) * m_fTileSize + m_fOriginX - fX;
    float fDY = float(iFallbackY) * m_fTileSize + m_fOriginY - fY;
    float fSquaredLength = fDX * fDX + 0.0f + fDY * fDY;
    int iSteps = int(sqrtf(fSquaredLength) / m_fTileSize);
    float fLength = sqrtf(fSquaredLength);
    if (fLength > 1e-08)
    {
        float fInverse = 1.0f / fLength;
        fDX *= fInverse;
        fDY *= fInverse;
    }
    float fTileSize = m_fTileSize;
    float fOriginX = m_fOriginX;
    float fOriginY = m_fOriginY;
    for (int i = 0; i < iSteps; ++i)
    {
        unsigned int iTestX = (unsigned int)(long)floorf((fX - fOriginX) / fTileSize);
        unsigned int iTestY = (unsigned int)(long)floorf((fY - fOriginY) / fTileSize);
        if (tileFree(iTestX, iTestY, NODE_ANY))
        {
            iResultX = iTestX;
            iResultY = iTestY;
            return;
        }
        fX += fDX * fTileSize;
        fY += fDY * fTileSize;
    }
    iResultX = iFallbackX;
    iResultY = iFallbackY;
}

bool CAstarPathfinder::findPath(float fStartX, float fStartY, float fGoalX, float fGoalY)
{
    m_bCompletePath = true;
    m_bGoalBlocked = false;
    fStartX -= m_fOriginX;
    fStartY -= m_fOriginY;
    fGoalX -= m_fOriginX;
    fGoalY -= m_fOriginY;
    unsigned int iStartX = (unsigned int)(long)floorf((fStartX < 0.0f ? 0.0f : fStartX) / m_fTileSize);
    unsigned int iStartY = (unsigned int)(long)floorf((fStartY < 0.0f ? 0.0f : fStartY) / m_fTileSize);
    unsigned int iGoalX = (unsigned int)(long)floorf((fGoalX < 0.0f ? 0.0f : fGoalX) / m_fTileSize);
    unsigned int iGoalY = (unsigned int)(long)floorf((fGoalY < 0.0f ? 0.0f : fGoalY) / m_fTileSize);
    if (!tileFree(iGoalX, iGoalY, NODE_ANY))
    {
        m_bGoalBlocked = true;
        unsigned int iNewX = iGoalX;
        unsigned int iNewY = iGoalY;
        findNearestOpen(iStartX, iStartY, iGoalX, iGoalY, iNewX, iNewY);
        iGoalX = iNewX;
        iGoalY = iNewY;
    }
    if (!tileFree(iStartX, iStartY, NODE_ANY) ||
        !tileFree(iStartX, iStartY - 1, NODE_ANY) || !tileFree(iStartX, iStartY + 1, NODE_ANY) ||
        !tileFree(iStartX + 1, iStartY, NODE_ANY) || !tileFree(iStartX - 1, iStartY, NODE_ANY))
    {
        findNearestWideOpen(iGoalX, iGoalY, iStartX, iStartY, iStartX, iStartY);
        if (!tileFree(iStartX, iStartY, NODE_ANY))
        {
            m_bPathFound = false;
            return false;
        }
    }
    if (tileIndex(iStartX, iStartY) != tileIndex(iGoalX, iGoalY))
    {
        m_bPathFound = true;
        freeNodes();
        createPath(iGoalX, iGoalY, iStartX, iStartY, true);
        return m_bPathFound;
    }
    m_bPathFound = false;
    return false;
}
