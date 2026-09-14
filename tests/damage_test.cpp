#include "torchlight/damage.hpp"

#include <iostream>
#include <stdexcept>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main() {
    try {
        torchlight::DamageDefense defense;
        defense.natural_armor = 40;
        defense.defense_attribute = 25;
        defense.elemental_armor[static_cast<std::size_t>(
            torchlight::DamageType::fire)] = 20;
        require(defense.effective(torchlight::DamageType::physical) == 50 &&
                    defense.effective(torchlight::DamageType::fire) == 25,
                "defense attribute did not scale armor with ceil");

        torchlight::TorchlightRandom physical_random(17);
        const auto physical = torchlight::mitigate_damage(
            30, 30, torchlight::DamageType::physical, 1.0F,
            defense, physical_random);
        require(physical.rolled_defense >= 25 &&
                    physical.rolled_defense <= 50 &&
                    physical.applied == 1,
                "physical armor roll or minimum damage is wrong");

        torchlight::TorchlightRandom fire_random(17);
        const auto fire = torchlight::mitigate_damage(
            30, 60, torchlight::DamageType::fire, 1.0F,
            defense, fire_random);
        require(fire.rolled_defense >= 13 && fire.rolled_defense <= 25 &&
                    fire.applied ==
                        30 - static_cast<std::int32_t>(
                                 static_cast<float>(fire.rolled_defense) * 0.5F),
                "elemental armor scaling is wrong");

        torchlight::DamageDefense immune;
        immune.elemental_armor[static_cast<std::size_t>(
            torchlight::DamageType::ice)] = 100;
        torchlight::TorchlightRandom ice_random(5);
        require(torchlight::mitigate_damage(
                    10, 10, torchlight::DamageType::ice, 1.0F,
                    immune, ice_random).applied == 0,
                "elemental defense did not allow complete absorption");
        std::cout << "PASS: physical and elemental armor match modifyDamage\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
