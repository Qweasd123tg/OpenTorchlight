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

    bool m_bKeyPressed;
    short m_sKeyPressed;
    int m_iKeyPressed;
    bool m_bKeyPressedState;
    unsigned char m_keyPressedPadding[0x1f8];

    bool m_bKeyHeld;
    short m_sKeyHeld;
    int m_iKeyHeld;
    bool m_bKeyHeldState;
    unsigned char m_keyHeldPadding[0x1f8];

    bool m_bKeyReleased;
    short m_sKeyReleased;
    int m_iKeyReleased;
    bool m_bKeyReleasedState;
    unsigned char m_keyReleasedPadding[0x2f8];

    bool m_bCurrentKeyPressed;
    short m_sCurrentKeyPressed;
    int m_iCurrentKeyPressed;
    bool m_bCurrentKeyPressedState;
    unsigned char m_currentKeyPressedPadding[0x1f8];

    bool m_bCurrentKeyHeld;
    short m_sCurrentKeyHeld;
    int m_iCurrentKeyHeld;
    bool m_bCurrentKeyHeldState;
    unsigned char m_currentKeyHeldPadding[0x1f8];

    bool m_bCurrentKeyReleased;
    short m_sCurrentKeyReleased;
    int m_iCurrentKeyReleased;
    bool m_bCurrentKeyReleasedState;
    unsigned char m_currentKeyReleasedPadding[0x1f8];
} __attribute__((aligned(8)));

#pragma pack(pop)

// Complete live storage: original capture/flush touch through +0xd10.
typedef char key_size[sizeof(CKeyManager)==0xd18?1:-1];
typedef char key_alignment[__alignof__(CKeyManager)==8?1:-1];
#define KEY_OFFSET(F,O) typedef char key_offset_##F[__builtin_offsetof(CKeyManager,F)==O?1:-1]
KEY_OFFSET(m_bRightShift,0x10);
KEY_OFFSET(m_bKeyPressed,0x11);
KEY_OFFSET(m_bKeyHeld,0x211);
KEY_OFFSET(m_bKeyReleased,0x411);
KEY_OFFSET(m_bCurrentKeyPressed,0x711);
KEY_OFFSET(m_bCurrentKeyHeld,0x911);
KEY_OFFSET(m_bCurrentKeyReleased,0xb11);
KEY_OFFSET(m_currentKeyReleasedPadding,0xb19);
#undef KEY_OFFSET

#endif
