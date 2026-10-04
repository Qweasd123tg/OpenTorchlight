#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "GameEnums.h"
#include "RunicCore.h"

class CMouseManager : public CRunicCore
{
public:
    virtual ~CMouseManager();
    void mouseEvent(unsigned int, unsigned int);
    bool buttonPressed(EMouseButton);
    bool buttonHeld(EMouseButton);
    bool buttonDoubleClick(EMouseButton);
    long long* virtualMousePosition(float, float, float, float);
    void capture();
    void flushAll();
    void flush();
    void update(void*);
    CMouseManager();

    // fields
    short m_iUnknown10;
    bool m_bUnknown12;
    short m_iUnknown13;
    bool m_bUnknown15;
    short m_iUnknown16;
    bool m_bUnknown18;
    short m_iUnknown19;
    bool m_bUnknown1B;
    short m_iUnknown1C;
    bool m_bUnknown1E;
    short m_iUnknown1F;
    bool m_bUnknown21;
    unsigned char m_gap22[0x6];
    long long m_iUnknown28;
    long long m_iUnknown30;
    long long m_iUnknown38;
    long long m_iUnknown40;
    int m_iUnknown48;
    int m_iUnknown4C;
};

#endif
