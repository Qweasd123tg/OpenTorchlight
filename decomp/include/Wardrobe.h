#ifndef OTL_WARDROBE_H
#define OTL_WARDROBE_H
#include "RunicCore.h"
#include <string>
class CInventory;
#include "WardrobeDefines.h"
// Partial layout: original getters address meshes at 0x88 and textures at 0xb0.
class CWardrobe : public CRunicCore {
    char m_Unrecovered10[0x88-0x10];
public:
    virtual ~CWardrobe();
    void update(CInventory*);
    void setBaseTexture(EWardrobeSlot,std::wstring);
    std::wstring m_meshes[5];
    std::wstring m_textures[5];
private:
    char m_UnrecoveredD8[0x108-0xd8];
};
typedef char check_wardrobe_size[sizeof(CWardrobe)==0x108?1:-1];
#endif
