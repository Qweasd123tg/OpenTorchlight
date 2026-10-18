#ifndef SDL_EVENT_HANDLER_H
#define SDL_EVENT_HANDLER_H
#include <map>
union SDL_Event;
class CGameClient;
// Partial SDL type declaration. The recovered map stores numeric scan codes.
enum SDL_Scancode { SDL_SCANCODE_UNKNOWN = 0, SDL_NUM_SCANCODES = 512 };
class SDLEventHandler
{
public:
    virtual ~SDLEventHandler();
    SDLEventHandler();
    void ProcessEvent(const SDL_Event&);
private:
    friend class CGame;
    CGameClient* m_gameClient; // +0x8 nativeProcessEvent/constructor
    unsigned short m_modifiers; // +0x10 SDL_GetModState baseline
    unsigned char m_gap12[6];
    std::map<SDL_Scancode,unsigned short> m_scanCodes;
};
#endif
