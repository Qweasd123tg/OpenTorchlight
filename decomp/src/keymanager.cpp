#include "EmptyStrings.h"
#include "GameNamespaces.h"
#include "KeyManager.h"

void CKeyManager::capture()
{
    memcpy(m_pressed, m_currentPressed, sizeof(m_pressed));
    memcpy(m_released, m_currentReleased, sizeof(m_released));
    memcpy(m_held, m_currentHeld, sizeof(m_held));
    memset(m_currentPressed, 0, sizeof(m_currentPressed));
    memset(m_currentReleased, 0, sizeof(m_currentReleased));
}

void CKeyManager::flushAll()
{
    memset(m_currentHeld, 0, sizeof(m_currentHeld));
    memset(m_currentPressed, 0, sizeof(m_currentPressed));
    memset(m_currentReleased, 0, sizeof(m_currentReleased));
}

void CKeyManager::flush()
{
    memset(m_currentPressed, 0, sizeof(m_currentPressed));
    memset(m_currentReleased, 0, sizeof(m_currentReleased));
}

extern "C" const unsigned char* SDL_GetKeyboardState(int*);

void CKeyManager::keyEvent(unsigned int eventType, unsigned int keyCode)
{
    unsigned char *currentKeyPressed =
        reinterpret_cast<unsigned char *>(m_currentPressed);
    unsigned char *currentKeyHeld =
        reinterpret_cast<unsigned char *>(m_currentHeld);
    unsigned char *currentKeyReleased =
        reinterpret_cast<unsigned char *>(m_currentReleased);

    if (eventType == 0x101 || eventType == 0x105)
    {
        if (currentKeyHeld[keyCode])
            currentKeyReleased[keyCode] = 1;
        currentKeyHeld[keyCode] = 0;
    }
    else if (eventType == 0x100 || eventType == 0x104)
    {
        if (!currentKeyHeld[keyCode])
            currentKeyPressed[keyCode] = 1;
        currentKeyHeld[keyCode] = 1;
    }

    m_bRightShift = SDL_GetKeyboardState(0)[0x39] != 0;
}

CKeyManager::~CKeyManager()
{
}


bool CKeyManager::keyPressed(unsigned int key)
{
    return m_pressed[key] == 1;
}

bool CKeyManager::keyHeld(unsigned int key)
{
    return m_held[key] == 1 || m_pressed[key] == 1;
}

bool CKeyManager::keyReleased(unsigned int key)
{
    return m_released[key] == 1;
}


int CKeyManager::shiftCharacter(int character, bool shifted)
{
    switch (character)
    {
    case 0x13: return '*';
    case 0x20: return ' ';
    case 0x30: case 0x60: return shifted ? 41 : 48;
    case 0x31: case 0x61: return shifted ? 33 : 49;
    case 0x32: case 0x62: return shifted ? 64 : 50;
    case 0x33: case 0x63: return shifted ? 35 : 51;
    case 0x34: case 0x64: return shifted ? 36 : 52;
    case 0x35: case 0x65: return shifted ? 37 : 53;
    case 0x36: case 0x66: return shifted ? 94 : 54;
    case 0x37: case 0x67: return shifted ? 38 : 55;
    case 0x38: case 0x68: return shifted ? 42 : 56;
    case 0x39: case 0x69: return shifted ? 40 : 57;
    case 0x41: return shifted ? 65 : 97;
    case 0x42: return shifted ? 66 : 98;
    case 0x43: return shifted ? 67 : 99;
    case 0x44: return shifted ? 68 : 100;
    case 0x45: return shifted ? 69 : 101;
    case 0x46: return shifted ? 70 : 102;
    case 0x47: return shifted ? 71 : 103;
    case 0x48: return shifted ? 72 : 104;
    case 0x49: return shifted ? 73 : 105;
    case 0x4a: return shifted ? 74 : 106;
    case 0x4b: return shifted ? 75 : 107;
    case 0x4c: return shifted ? 76 : 108;
    case 0x4d: return shifted ? 77 : 109;
    case 0x4e: return shifted ? 78 : 110;
    case 0x4f: return shifted ? 79 : 111;
    case 0x50: return shifted ? 80 : 112;
    case 0x51: return shifted ? 81 : 113;
    case 0x52: return shifted ? 82 : 114;
    case 0x53: return shifted ? 83 : 115;
    case 0x54: return shifted ? 84 : 116;
    case 0x55: return shifted ? 85 : 117;
    case 0x56: return shifted ? 86 : 118;
    case 0x57: return shifted ? 87 : 119;
    case 0x58: return shifted ? 88 : 120;
    case 0x59: return shifted ? 89 : 121;
    case 0x5a: return shifted ? 90 : 122;
    case 0x6a: return '*';
    case 0x6b: return '+';
    case 0x6d: return '-';
    case 0x6e: return '.';
    case 0x6f: return '/';
    case 0xba: return shifted ? ':' : ';';
    case 0xbb: return shifted ? '+' : '=';
    case 0xbc: return shifted ? '<' : ',';
    case 0xbd: return shifted ? '_' : '-';
    case 0xbe: return shifted ? '>' : '.';
    case 0xbf: return shifted ? '?' : '/';
    case 0xc0: return '~';
    case 0xdb: return shifted ? '{' : '[';
    case 0xdc: return shifted ? '|' : '\\';
    case 0xdd: return shifted ? '}' : ']';
    case 0xde: return shifted ? 34 : 39;
    default: return character;
    }
}

extern "C" const unsigned char* SDL_GetKeyboardState(int*);

CKeyManager::CKeyManager() : CRunicCore(), m_bRightShift(false)
{
    flushAll();
    m_bRightShift = SDL_GetKeyboardState(0)[0x39] != 0;
}
