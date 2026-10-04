#include "EmptyStrings.h"
#include "Graph.h"
#include "DataGroup.h"
#include "StringUtilities.h"
#include <algorithm>

CGraph::CGraph(const std::wstring& filename)
    : m_eType(GRAPH_LINEAR), m_Lines(10), m_sName(L""), m_iLineCount(1),
      m_bNeedsProcessing(false), m_bInferPastEnd(false), m_fFirstSlope(0),
      m_fOtherSlope(0), m_fFirstMax(0), m_fOtherMax(0), m_fLastX(0)
{
    if (filename != EMPTY_WSTRING)
        loadGraph(filename.c_str());
}

CGraph::CGraph(EGRAPH_TYPES type, std::wstring name, unsigned int lines)
    : m_eType(type), m_Lines(10), m_sName(name), m_iLineCount(lines),
      m_bNeedsProcessing(false), m_bInferPastEnd(false), m_fFirstSlope(0),
      m_fOtherSlope(0), m_fFirstMax(0), m_fOtherMax(0), m_fLastX(0)
{
    // addGraphLine updates the loop bound, as in the original constructor.
    for (unsigned int i = 0; i < m_iLineCount; ++i)
        addGraphLine(m_eType);
}

CGraph::~CGraph()
{
    for (unsigned int i = 0; i < m_Lines.size(); ++i)
        delete m_Lines[i];
    m_Lines.clear();
}

float CGraph::getValue(float x, unsigned int line) const
{
    if (m_bInferPastEnd && x > m_fLastX)
    {
        if (line != 0)
            return (x - m_fLastX) * m_fOtherSlope + m_fOtherMax;
        return (x - m_fLastX) * m_fFirstSlope + m_fFirstMax;
    }
    if (line < m_Lines.size() && m_Lines[line] != NULL)
        return m_Lines[line]->getValue(NULL, x);
    return 0;
}

void CGraph::processPoints()
{
    for (unsigned int i = 0; i < m_Lines.size(); ++i)
        m_Lines[i]->processControlPoints();
    m_bNeedsProcessing = false;
}

int CGraph::getControlPoints()
{
    int points = 0;
    for (unsigned int i = 0; i < m_Lines.size(); ++i)
        points = std::max(points, static_cast<int>(m_Lines[i]->getNumControlPoints()));
    return points;
}

void CGraph::clear(unsigned int line)
{
    if (line < m_iLineCount && m_Lines[line] != NULL)
        m_Lines[line]->removeAllControlPoints();
}

void CGraph::addGraphLine(EGRAPH_TYPES type)
{
    if (type == GRAPH_CURVED)
        m_Lines.add(new ParticleUniverse::DynamicAttributeCurved(ParticleUniverse::IT_SPLINE));
    else
        m_Lines.add(new ParticleUniverse::DynamicAttributeCurved(ParticleUniverse::IT_LINEAR));
    m_iLineCount = m_Lines.size();
}

void CGraph::addValue(float x, float y, unsigned int line)
{
    if (x > m_fLastX)
        m_fLastX = x;
    while (line >= m_Lines.size())
        addGraphLine(m_eType);
    if (line == 0)
        m_fFirstMax = std::max(m_fFirstMax, y);
    else
        m_fOtherMax = std::max(m_fOtherMax, y);
    m_bNeedsProcessing = true;
    m_Lines[line]->addControlPoint(x, y);
}

void CGraph::loadGraphLine(CDataGroup* data)
{
    if (data == NULL || data->GetNumberOfDataGroups() == 0)
        return;
    float lastFirst = 0;
    float lastOther = 0;
    for (unsigned int i = 0; i < data->GetNumberOfDataGroups(); ++i)
    {
        CDataGroup* point = data->GetDataGroup(i);
        float x = point->GetDataValue(L"X", 0.0f);
        float first, other;
        if (m_Lines.size() == 1)
        {
            first = other = point->GetDataValue(L"Y", 0.0f);
            addValue(x, first, 0);
        }
        else
        {
            first = point->GetDataValue(L"MINY", 0.0f);
            other = point->GetDataValue(L"MAXY", 0.0f);
            addValue(x, first, 0);
            addValue(x, other, 1);
        }
        if (i == data->GetNumberOfDataGroups() - 1)
        {
            m_fFirstSlope = first - lastFirst;
            m_fOtherSlope = other - lastOther;
        }
        else
        {
            lastFirst = first;
            lastOther = other;
        }
    }
}

bool CGraph::loadGraph(const wchar_t* filename)
{
    CDataGroup data(L"", NULL, 20, 10, NULL);
    data.LoadFile(filename, NULL);
    std::wstring type = STRINGS::StringUpper(data.GetDataValue(L"TYPE", L"LINE"));
    m_eType = static_cast<EGRAPH_TYPES>(data.GetDataValue(L"CURVED", false));
    m_sName = data.GetDataValue(L"NAME", EMPTY_WSTRING);
    m_bInferPastEnd = data.GetDataValue(L"INFER_PASSED_END", false);
    if (type != L"LINE")
        addGraphLine(m_eType);
    addGraphLine(m_eType);
    loadGraphLine(&data);
    processPoints();
    m_bNeedsProcessing = false;
    return true;
}
