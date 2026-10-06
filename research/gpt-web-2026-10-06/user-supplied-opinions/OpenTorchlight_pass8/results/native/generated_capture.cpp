// Automatically inferred from archival CKeyManager::capture instruction listing.
// Test candidate only. Offsets are not claims about original field names.
#include <cstring>
extern "C" void generated_capture(unsigned char* object) {
    std::memcpy(object + 0x11, object + 0x711, 512);
    std::memcpy(object + 0x411, object + 0xb11, 512);
    std::memcpy(object + 0x211, object + 0x911, 512);
    std::memset(object + 0x711, 0, 512);
    std::memset(object + 0xb11, 0, 512);
}
