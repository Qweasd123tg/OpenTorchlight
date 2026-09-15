#include "torchlight/attack_action.hpp"
#include <iostream>
int main(int argc,char**argv){
    if(argc!=2)return 2;
    try{
        torchlight::PakArchive pak(argv[1]);const auto c=torchlight::AttackEffectCatalog::discover(pak);
        if(!c){std::cout<<"NONE\n";return 0;}
        const auto value=c->find(u"HASTE");
        if(!value)return 3;
        std::cout<<"FOUND "<<*value<<'\n';
    }catch(const std::exception&){std::cout<<"INVALID\n";}
    return 0;
}
