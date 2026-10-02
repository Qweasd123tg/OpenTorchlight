#include "torchlight/gold_pickup.hpp"
#include <cstring>
#include <iostream>
using namespace torchlight;
float scalar(std::uint32_t bits) {float value;std::memcpy(&value,&bits,sizeof(value));return value;}
int main() {
    bool alive,moving;std::uint32_t x,y,z,size;
    while(std::cin>>alive>>moving>>x>>y>>z>>size) {
        if(size>64)return 2;
        std::vector<GoldPickupPoint> points;
        for(std::uint32_t n=0;n<size;++n) {
            bool gold;std::uint32_t px,py,pz;
            if(!(std::cin>>gold>>px>>py>>pz))return 2;
            points.push_back({n+1,{scalar(px),scalar(py),scalar(pz)},gold});
        }
        const auto selected=auto_gold_targets({scalar(x),scalar(y),scalar(z)},alive,moving,points);
        std::cout<<selected.size();for(const auto id:selected)std::cout<<' '<<id;std::cout<<'\n';
    }
    return std::cin.eof()?0:2;
}
