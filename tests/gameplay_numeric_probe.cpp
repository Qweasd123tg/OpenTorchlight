#include "torchlight/consumable.hpp"
#include "torchlight/population.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
namespace {
float number(std::uint32_t bits) {float value;std::memcpy(&value,&bits,4);return value;}
std::uint32_t bits(float value) {std::uint32_t n;std::memcpy(&n,&value,4);return n;}
}
int main(){try{
    char kind;
    while(std::cin>>kind){
        if(kind=='r') {std::uint32_t value;if(!(std::cin>>value))return 2;std::cout<<bits(torchlight::finite_recovery_rate(number(value)))<<'\n';}
        else if(kind=='p') {std::uint32_t seed,a,b,c,d,n;if(!(std::cin>>seed>>a>>b>>c>>d>>n))return 2;
            torchlight::TorchlightRandom random(seed);
            std::cout<<torchlight::population_count(number(a),number(b),number(c),number(d),n,random)<<' '<<random.state()<<'\n';}
        else return 2;
    }
    return std::cin.eof()?0:2;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
