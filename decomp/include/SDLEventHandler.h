#ifndef SDL_EVENT_HANDLER_H
#define SDL_EVENT_HANDLER_H
#include <map>
// Partial SDL type declaration. The recovered map stores numeric scan codes.
enum SDL_Scancode { SDL_SCANCODE_UNKNOWN = 0, SDL_NUM_SCANCODES = 512 };
class SDLEventHandler
{
public:
    virtual ~SDLEventHandler();
private:
    unsigned char m_unrecovered8[0x10];
    std::map<SDL_Scancode,unsigned short> m_scanCodes;
};
#endif
