// Numeric adapter only; source and constants are described by compare_attack_speed.py.
#include "torchlight/attack_action.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
float decode(std::uint32_t b){float f;std::memcpy(&f,&b,4);return f;}
std::uint32_t encode(float f){std::uint32_t b;std::memcpy(&b,&f,4);return b;}
int main(){
    std::uint32_t d,h,r;
    while(std::cin>>d>>h>>r){
        torchlight::AttackEffects e;e.add(0x16,decode(h));e.add(0x8c,decode(r));
        std::cout<<encode(torchlight::ordinary_attack_speed(decode(d),e,false))<<' '
                 <<encode(torchlight::ordinary_attack_speed(decode(d),e,true))<<'\n';
    }
    return std::cin.eof()?0:2;
}
