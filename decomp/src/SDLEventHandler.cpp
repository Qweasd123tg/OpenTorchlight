#include "SDLEventHandler.h"

SDLEventHandler::~SDLEventHandler()
{
}

#include "LinuxUtils.h"

SDLEventHandler::SDLEventHandler() : m_gameClient(NULL), m_modifiers(0)
{
    m_scanCodes[static_cast<SDL_Scancode>(41)] = 27;
    m_scanCodes[static_cast<SDL_Scancode>(39)] = 48;
    m_scanCodes[static_cast<SDL_Scancode>(30)] = 49;
    m_scanCodes[static_cast<SDL_Scancode>(31)] = 50;
    m_scanCodes[static_cast<SDL_Scancode>(32)] = 51;
    m_scanCodes[static_cast<SDL_Scancode>(33)] = 52;
    m_scanCodes[static_cast<SDL_Scancode>(34)] = 53;
    m_scanCodes[static_cast<SDL_Scancode>(35)] = 54;
    m_scanCodes[static_cast<SDL_Scancode>(36)] = 55;
    m_scanCodes[static_cast<SDL_Scancode>(37)] = 56;
    m_scanCodes[static_cast<SDL_Scancode>(38)] = 57;
    m_scanCodes[static_cast<SDL_Scancode>(45)] = 189;
    m_scanCodes[static_cast<SDL_Scancode>(46)] = 61;
    m_scanCodes[static_cast<SDL_Scancode>(42)] = 8;
    m_scanCodes[static_cast<SDL_Scancode>(43)] = 9;
    m_scanCodes[static_cast<SDL_Scancode>(20)] = 81;
    m_scanCodes[static_cast<SDL_Scancode>(26)] = 87;
    m_scanCodes[static_cast<SDL_Scancode>(8)] = 69;
    m_scanCodes[static_cast<SDL_Scancode>(21)] = 82;
    m_scanCodes[static_cast<SDL_Scancode>(23)] = 84;
    m_scanCodes[static_cast<SDL_Scancode>(28)] = 89;
    m_scanCodes[static_cast<SDL_Scancode>(24)] = 85;
    m_scanCodes[static_cast<SDL_Scancode>(12)] = 73;
    m_scanCodes[static_cast<SDL_Scancode>(18)] = 79;
    m_scanCodes[static_cast<SDL_Scancode>(19)] = 80;
    m_scanCodes[static_cast<SDL_Scancode>(47)] = 219;
    m_scanCodes[static_cast<SDL_Scancode>(48)] = 221;
    m_scanCodes[static_cast<SDL_Scancode>(40)] = 13;
    m_scanCodes[static_cast<SDL_Scancode>(224)] = 162;
    m_scanCodes[static_cast<SDL_Scancode>(4)] = 65;
    m_scanCodes[static_cast<SDL_Scancode>(22)] = 83;
    m_scanCodes[static_cast<SDL_Scancode>(7)] = 68;
    m_scanCodes[static_cast<SDL_Scancode>(9)] = 70;
    m_scanCodes[static_cast<SDL_Scancode>(10)] = 71;
    m_scanCodes[static_cast<SDL_Scancode>(11)] = 72;
    m_scanCodes[static_cast<SDL_Scancode>(13)] = 74;
    m_scanCodes[static_cast<SDL_Scancode>(14)] = 75;
    m_scanCodes[static_cast<SDL_Scancode>(15)] = 76;
    m_scanCodes[static_cast<SDL_Scancode>(51)] = 186;
    m_scanCodes[static_cast<SDL_Scancode>(52)] = 222;
    m_scanCodes[static_cast<SDL_Scancode>(53)] = 192;
    m_scanCodes[static_cast<SDL_Scancode>(225)] = 160;
    m_scanCodes[static_cast<SDL_Scancode>(49)] = 220;
    m_scanCodes[static_cast<SDL_Scancode>(29)] = 90;
    m_scanCodes[static_cast<SDL_Scancode>(27)] = 88;
    m_scanCodes[static_cast<SDL_Scancode>(6)] = 67;
    m_scanCodes[static_cast<SDL_Scancode>(25)] = 86;
    m_scanCodes[static_cast<SDL_Scancode>(5)] = 66;
    m_scanCodes[static_cast<SDL_Scancode>(17)] = 78;
    m_scanCodes[static_cast<SDL_Scancode>(16)] = 77;
    m_scanCodes[static_cast<SDL_Scancode>(54)] = 188;
    m_scanCodes[static_cast<SDL_Scancode>(55)] = 190;
    m_scanCodes[static_cast<SDL_Scancode>(56)] = 191;
    m_scanCodes[static_cast<SDL_Scancode>(229)] = 161;
    m_scanCodes[static_cast<SDL_Scancode>(85)] = 106;
    m_scanCodes[static_cast<SDL_Scancode>(226)] = 164;
    m_scanCodes[static_cast<SDL_Scancode>(44)] = 32;
    m_scanCodes[static_cast<SDL_Scancode>(57)] = 20;
    m_scanCodes[static_cast<SDL_Scancode>(58)] = 112;
    m_scanCodes[static_cast<SDL_Scancode>(59)] = 113;
    m_scanCodes[static_cast<SDL_Scancode>(60)] = 114;
    m_scanCodes[static_cast<SDL_Scancode>(61)] = 115;
    m_scanCodes[static_cast<SDL_Scancode>(62)] = 116;
    m_scanCodes[static_cast<SDL_Scancode>(63)] = 117;
    m_scanCodes[static_cast<SDL_Scancode>(64)] = 118;
    m_scanCodes[static_cast<SDL_Scancode>(65)] = 120;
    m_scanCodes[static_cast<SDL_Scancode>(66)] = 120;
    m_scanCodes[static_cast<SDL_Scancode>(67)] = 121;
    m_scanCodes[static_cast<SDL_Scancode>(83)] = 144;
    m_scanCodes[static_cast<SDL_Scancode>(71)] = 145;
    m_scanCodes[static_cast<SDL_Scancode>(95)] = 103;
    m_scanCodes[static_cast<SDL_Scancode>(96)] = 104;
    m_scanCodes[static_cast<SDL_Scancode>(97)] = 105;
    m_scanCodes[static_cast<SDL_Scancode>(86)] = 109;
    m_scanCodes[static_cast<SDL_Scancode>(92)] = 100;
    m_scanCodes[static_cast<SDL_Scancode>(93)] = 101;
    m_scanCodes[static_cast<SDL_Scancode>(94)] = 102;
    m_scanCodes[static_cast<SDL_Scancode>(87)] = 107;
    m_scanCodes[static_cast<SDL_Scancode>(89)] = 97;
    m_scanCodes[static_cast<SDL_Scancode>(90)] = 98;
    m_scanCodes[static_cast<SDL_Scancode>(91)] = 99;
    m_scanCodes[static_cast<SDL_Scancode>(98)] = 96;
    m_scanCodes[static_cast<SDL_Scancode>(220)] = 110;
    m_scanCodes[static_cast<SDL_Scancode>(68)] = 122;
    m_scanCodes[static_cast<SDL_Scancode>(69)] = 123;
    m_scanCodes[static_cast<SDL_Scancode>(104)] = 124;
    m_scanCodes[static_cast<SDL_Scancode>(105)] = 125;
    m_scanCodes[static_cast<SDL_Scancode>(106)] = 126;
    m_scanCodes[static_cast<SDL_Scancode>(88)] = 13;
    m_scanCodes[static_cast<SDL_Scancode>(228)] = 163;
    m_scanCodes[static_cast<SDL_Scancode>(84)] = 111;
    m_scanCodes[static_cast<SDL_Scancode>(230)] = 165;
    m_scanCodes[static_cast<SDL_Scancode>(72)] = 19;
    m_scanCodes[static_cast<SDL_Scancode>(74)] = 36;
    m_scanCodes[static_cast<SDL_Scancode>(82)] = 38;
    m_scanCodes[static_cast<SDL_Scancode>(75)] = 33;
    m_scanCodes[static_cast<SDL_Scancode>(80)] = 37;
    m_scanCodes[static_cast<SDL_Scancode>(79)] = 39;
    m_scanCodes[static_cast<SDL_Scancode>(77)] = 35;
    m_scanCodes[static_cast<SDL_Scancode>(81)] = 40;
    m_scanCodes[static_cast<SDL_Scancode>(78)] = 34;
    m_scanCodes[static_cast<SDL_Scancode>(73)] = 45;
    m_scanCodes[static_cast<SDL_Scancode>(76)] = 46;
    m_scanCodes[static_cast<SDL_Scancode>(227)] = 91;
    m_scanCodes[static_cast<SDL_Scancode>(231)] = 92;
    m_scanCodes[static_cast<SDL_Scancode>(101)] = 93;
    m_scanCodes[static_cast<SDL_Scancode>(282)] = 95;
    ClearKeyState();
}

#include "SDL.h"
#include "GameClient.h"

void SDLEventHandler::ProcessEvent(const SDL_Event& event)
{
    if (!m_gameClient) return;
    switch (event.type) {
    case 0x400:
        UpdateCursorPos(event.motion.x,event.motion.y);
        return;
    case 0x401:
    case 0x402: {
        unsigned key=0, message=0;
        switch (event.button.button) {
        case 1: key=1; message=0x201; break;
        case 2: key=4; message=0x207; break;
        case 3: key=2; message=0x204; break;
        }
        if (key) {
            m_gameClient->mouseEvent(message+(event.button.state==1?0:1),0);
            UpdateKeyState(key,event.button.state==1);
        }
        UpdateCursorPos(event.button.x,event.button.y);
        return;
    }
    case 0x303:
        m_gameClient->keyEvent(0x102,event.text.text[0],0);
        return;
    case 0x403:
        if (event.wheel.x) m_gameClient->mouseEvent(0x20a,event.wheel.x<<16);
        // The original also processes the shared keyboard fields for wheel events.
    case 0x300:
    case 0x301:
        break;
    default:
        return;
    }
    std::map<SDL_Scancode,unsigned short>::iterator scan=m_scanCodes.find(event.key.keysym.scancode);
    if (scan!=m_scanCodes.end()) {
        m_gameClient->keyEvent(event.key.state==1?0x100:0x101,scan->second,0);
        UpdateKeyState(scan->second,event.key.state==1);
    }
    unsigned short modifiers=SDL_GetModState();
    if (((m_modifiers&3)!=0) != ((modifiers&3)!=0)) {
        bool pressed=(modifiers&3)!=0;
        m_gameClient->keyEvent(pressed?0x100:0x101,0x10,0);
        UpdateKeyState(0x10,pressed);
    }
    if (((m_modifiers&0xc0)!=0) != ((modifiers&0xc0)!=0)) {
        bool pressed=(modifiers&0xc0)!=0;
        m_gameClient->keyEvent(pressed?0x100:0x101,0x11,0);
        UpdateKeyState(0x11,pressed);
    }
    if (((m_modifiers&0x300)!=0) != ((modifiers&0x300)!=0)) {
        bool pressed=(modifiers&0x300)!=0;
        m_gameClient->keyEvent(pressed?0x100:0x101,0x12,0);
        UpdateKeyState(0x12,pressed);
    }
    m_modifiers=modifiers;
}
