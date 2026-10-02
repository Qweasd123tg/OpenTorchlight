#include "torchlight/gold_pickup.hpp"
#include <cmath>

namespace torchlight {
std::vector<std::uint64_t> auto_gold_targets(const std::array<float,3>& player,
    bool alive,bool moving,const std::vector<GoldPickupPoint>& items) {
    std::vector<std::uint64_t> result;
    if(!alive||!moving)return result;
    for(const auto& item:items) {
        if(!item.gold)continue;
        const float dx=item.position[0]-player[0];
        const float dz=item.position[2]-player[2];
        const float xx=dx*dx;
        const float xx0=xx+0.0F;
        const float zz=dz*dz;
        const float square=xx0+zz;
        const float distance=std::sqrt(square);
        // original-code literal @0xfa86d4 = 0x40400000; UCOMISS/JBE
        // excludes exact 3.0 and unordered values, and ignores Y completely.
        if(distance<3.0F)result.push_back(item.id);
    }
    return result;
}
} // namespace torchlight
