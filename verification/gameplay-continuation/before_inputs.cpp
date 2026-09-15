#include "torchlight/attack_action.hpp"
#include <iostream>
int main(){
 torchlight::UnitDefinition u; auto d=torchlight::load_innate_attack(u,1,2);
 std::cout<<"missing innate: range="<<d.range<<" strike="<<d.strike_range<<" unavailable="<<(!d.unavailable_reason.empty())<<'\n';
 std::cout<<"horizontal reach across 3-unit height="<<torchlight::within_horizontal_reach({0,0,0},{0,3,0},0,0,1)<<'\n';
}
