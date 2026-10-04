#ifndef KEYMANAGER_H
#define KEYMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "RunicCore.h"

class CKeyManager : public CRunicCore
{
public:
    virtual ~CKeyManager();
    bool keyPressed(unsigned int);
    bool keyHeld(unsigned int);
    bool keyReleased(unsigned int);
    int shiftCharacter(int, bool);
    void capture();
    void flushAll();
    void flush();
    void keyEvent(unsigned int, unsigned int);
    CKeyManager();

    // fields
    bool m_bUnknown10;
    bool m_bUnknown11;
    short m_iUnknown12;
    int m_iUnknown14;
    bool m_bUnknown18;
    unsigned char m_gap19[0x1f8];
    bool m_bUnknown211;
    short m_iUnknown212;
    int m_iUnknown214;
    bool m_bUnknown218;
    unsigned char m_gap219[0x1f8];
    bool m_bUnknown411;
    short m_iUnknown412;
    int m_iUnknown414;
    bool m_bUnknown418;
    unsigned char m_gap419[0x2f8];
    bool m_bUnknown711;
    short m_iUnknown712;
    int m_iUnknown714;
    bool m_bUnknown718;
    unsigned char m_gap719[0x1f8];
    bool m_bUnknown911;
    short m_iUnknown912;
    int m_iUnknown914;
    bool m_bUnknown918;
    unsigned char m_gap919[0x1f8];
    bool m_bUnknownB11;
    short m_iUnknownB12;
    int m_iUnknownB14;
    bool m_bUnknownB18;
};

#endif
