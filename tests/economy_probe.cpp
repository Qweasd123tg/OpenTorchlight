#include "torchlight/economy.hpp"
#include <cstring>
#include <iostream>
using namespace torchlight;
int main(){char op;std::int32_t buy,sell,ub,us,count,identified;std::uint32_t raw;
 try{while(std::cin>>op>>buy>>sell>>ub>>us>>count>>identified>>raw){float barter;std::memcpy(&barter,&raw,4);EquipmentPrices p{buy,sell,ub,us};
  if(op=='b')std::cout<<equipment_buy_price(p,count,identified!=0,barter)<<'\n';
  else if(op=='s')std::cout<<equipment_sell_price(p,count,identified!=0,barter)<<'\n';else return 2;}return 0;
 }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
