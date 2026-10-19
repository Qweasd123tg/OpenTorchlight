#ifndef GAMECLIENT_NATIVE_STEAM_H
#define GAMECLIENT_NATIVE_STEAM_H
#include "SteamStats.h"
namespace gameclient_fixture {
struct SteamOwner {
    CSteamStats*previous;
    CSteamStats*stats;
    SteamOwner():previous(CSteamStats::getSingleton()),stats(new CSteamStats) {
        typedef char SteamSize[sizeof(CSteamStats)==0xa0?1:-1];
        if(CSteamStats::getSingleton()!=stats)std::abort();
    }
    ~SteamOwner(){delete stats;*reinterpret_cast<CSteamStats**>(0x153a840)=previous;}
private:
    SteamOwner(const SteamOwner&);
    SteamOwner&operator=(const SteamOwner&);
};
}
#endif
