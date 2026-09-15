#include "torchlight/inventory_view.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace { std::size_t checks=0;
void require(bool b,const char* message){++checks;if(!b)throw std::runtime_error(message);}
}
int main() {
    try {
        PlayerPrototype prototype; prototype.minimum_health=prototype.maximum_health=100;
        WeaponPrototype weapon; weapon.name=u"STARTER"; weapon.display_name=u"Test sword";
        weapon.base_weapon_damage=20; weapon.speed=50; prototype.starting_weapon=weapon;
        PlayerSession session(prototype,1);
        InventoryView view;
        require(view.selected_id(session.inventory())==1,"first stored instance selected");
        const auto rows=view.lines(session,2);
        require(std::any_of(rows.begin(),rows.end(),[](const auto& row){return row.selected && row.text.find("[ON]")!=std::string::npos;}),"equipped and selected row visible");
        require(std::any_of(rows.begin(),rows.end(),[](const auto& row){return row.text.find("STORED DAMAGE")!=std::string::npos;}),"stored numeric roll visible");
        auto inventory=session.inventory();
        for(int i=0;i<50;++i) {InventoryItem item;item.name=u"COPY";static_cast<void>(inventory.store(item));}
        for(int i=0;i<80;++i)view.move(1,inventory);
        require(view.selected_id(inventory)==51,"selection clamps below last entry");
        for(int i=0;i<80;++i)view.move(-1,inventory);
        require(view.selected_id(inventory)==1,"selection clamps above first entry");
        PlayerInventory empty;view.move(1,empty);
        require(view.selected_id(empty)==0,"empty selection safe");
        require(view.selected_id(session.inventory())==1,"return to nonempty selection safe");
        view.status=inventory_change_message(InventoryChange::busy);
        // Do not compare iterators from different temporary views.
        const auto with_status=view.lines(session);
        require(std::any_of(with_status.begin(),with_status.end(),[](const auto& row){return row.text.find("ATTACK IN PROGRESS")!=std::string::npos;}),"failure reason visible in window");
        for(int c=0;c<256;++c) for(const auto row:inventory_glyph(static_cast<char>(c)))
            require(row<32,"glyph remains inside five columns");
        require(inventory_glyph('a')==inventory_glyph('A'),"font handles lowercase names");
        std::cout<<"inventory_view_checks="<<checks<<'\n';return 0;
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
