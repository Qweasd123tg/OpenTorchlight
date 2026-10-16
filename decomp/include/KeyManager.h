#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include "RunicCore.h"

#pragma pack(push, 1)

class CKeyManager : public CRunicCore
{
public:
    virtual ~CKeyManager();

    bool keyPressed(unsigned int key);
    bool keyHeld(unsigned int key);
    bool keyReleased(unsigned int key);

    int shiftCharacter(int character, bool shifted);

    void capture();
    void flushAll();
    void flush();
    void keyEvent(unsigned int eventType, unsigned int keyCode);

    CKeyManager();

    bool m_bRightShift;

    unsigned char m_pressed[0x200];
    unsigned char m_held[0x200];
    unsigned char m_released[0x200];
    unsigned char m_unrecovered611[0x100];
    unsigned char m_currentPressed[0x200];
    unsigned char m_currentHeld[0x200];
    unsigned char m_currentReleased[0x200];
} __attribute__((aligned(8)));

#pragma pack(pop)

// Complete live storage: original capture/flush touch through +0xd10.
typedef char key_size[sizeof(CKeyManager)==0xd18?1:-1];
typedef char key_alignment[__alignof__(CKeyManager)==8?1:-1];
#define KEY_OFFSET(F,O) typedef char key_offset_##F[__builtin_offsetof(CKeyManager,F)==O?1:-1]
KEY_OFFSET(m_bRightShift,0x10);
KEY_OFFSET(m_pressed,0x11);
KEY_OFFSET(m_held,0x211);
KEY_OFFSET(m_released,0x411);
KEY_OFFSET(m_currentPressed,0x711);
KEY_OFFSET(m_currentHeld,0x911);
KEY_OFFSET(m_currentReleased,0xb11);
KEY_OFFSET(m_unrecovered611,0x611);
#undef KEY_OFFSET

#endif
