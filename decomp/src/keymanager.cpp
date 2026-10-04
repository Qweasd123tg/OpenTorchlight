#include "EmptyStrings.h"
#include "GameNamespaces.h"
#include "KeyManager.h"

void CKeyManager::capture()
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);

    memcpy(bytes + 0x11, bytes + 0x711, 0x200);
    memcpy(bytes + 0x411, bytes + 0xb11, 0x200);
    memcpy(bytes + 0x211, bytes + 0x911, 0x200);

    memset(bytes + 0x711, 0, 0x200);
    memset(bytes + 0xb11, 0, 0x200);
}

void CKeyManager::flushAll()
{
    memset(reinterpret_cast<char *>(this) + 0x711, 0, 0x200);
    memset(reinterpret_cast<char *>(this) + 0x911, 0, 0x200);
    memset(reinterpret_cast<char *>(this) + 0xb11, 0, 0x200);
}

void CKeyManager::flush()
{
    m_bCurrentKeyPressed = false;
    m_sCurrentKeyPressed = 0;
    m_iCurrentKeyPressed = 0;
    m_bCurrentKeyPressedState = false;
    memset(reinterpret_cast<char *>(this) + 0x718, 0, 0x1f9);

    memset(reinterpret_cast<char *>(this) + 0xb11, 0, 0x7);
    memset(reinterpret_cast<char *>(this) + 0xb18, 0, 0x1f9);
}

void CKeyManager::keyEvent(unsigned int eventType, unsigned int keyCode)
{
    extern bool GetKeyState(unsigned int);

    unsigned char *currentKeyPressed =
        reinterpret_cast<unsigned char *>(&m_bCurrentKeyPressed);
    unsigned char *currentKeyHeld =
        reinterpret_cast<unsigned char *>(&m_bCurrentKeyHeld);
    unsigned char *currentKeyReleased =
        reinterpret_cast<unsigned char *>(&m_bCurrentKeyReleased);

    if (eventType == 0x101 || eventType == 0x105)
    {
        if (currentKeyHeld[keyCode + 1])
            currentKeyReleased[keyCode + 1] = 1;
        currentKeyHeld[keyCode + 1] = 0;
    }
    else if (eventType == 0x100 || eventType == 0x104)
    {
        if (!currentKeyHeld[keyCode + 1])
            currentKeyPressed[keyCode + 1] = 1;
        currentKeyHeld[keyCode + 1] = 1;
    }

    m_bRightShift = GetKeyState(0x39);
}

CKeyManager::~CKeyManager()
{
}
