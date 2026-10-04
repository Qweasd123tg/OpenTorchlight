#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include "RunicCore.h"

#pragma pack(push, 1)

class CKeyManager : public CRunicCore
{
public:
    virtual ~CKeyManager();

    bool keyPressed(unsigned int key) const;
    bool keyHeld(unsigned int key) const;
    bool keyReleased(unsigned int key) const;

    int shiftCharacter(int character, bool shifted) const;

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
};

#pragma pack(pop)

#endif
