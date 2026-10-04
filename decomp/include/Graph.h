#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "RunicCore.h"
#include "TArrayList.h"
#include "ParticleDynamicAttribute.h"
class CDataGroup;
enum EGRAPH_TYPES { GRAPH_LINEAR = 0, GRAPH_CURVED = 1 };

class CGraph : public CRunicCore
{
public:
    CGraph(const std::wstring& filename);
    CGraph(EGRAPH_TYPES type, std::wstring name, unsigned int lines);
    virtual ~CGraph();
    float getValue(float x, unsigned int line) const;
    void processPoints();
    int getControlPoints();
    void clear(unsigned int line);
    void addGraphLine(EGRAPH_TYPES type);
    void addValue(float x, float y, unsigned int line);
    void loadGraphLine(CDataGroup* data);
    bool loadGraph(const wchar_t* filename);
private:
    EGRAPH_TYPES m_eType;
    TArrayList<ParticleUniverse::DynamicAttributeCurved*> m_Lines;
    std::wstring m_sName;
    unsigned int m_iLineCount;
    bool m_bNeedsProcessing;
    bool m_bInferPastEnd;
    float m_fFirstSlope;
    float m_fOtherSlope;
    float m_fFirstMax;
    float m_fOtherMax;
    float m_fLastX;
};
#endif
