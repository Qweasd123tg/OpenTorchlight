#include "torchlight/typed_damage.hpp"
#include "torchlight/equipment.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
static float float_bits(std::uint32_t bits) {
    float value; std::memcpy(&value, &bits, sizeof(value)); return value;
}
static AttackEffects effects() {
    unsigned count; if (!(std::cin >> count) || count > 100) throw std::runtime_error("invalid effect count");
    AttackEffects result;
    for (unsigned i=0; i<count; ++i) {
        unsigned kind, type; std::uint32_t bits;
        if (!(std::cin >> kind >> type >> bits) || kind >= 145 || type > 7) throw std::runtime_error("invalid effect");
        float value; std::memcpy(&value, &bits, sizeof(value));
        result.add(static_cast<std::uint16_t>(kind), value, static_cast<std::uint8_t>(type));
    }
    return result;
}
int main() {
    try {
        char mode;
        while (std::cin >> mode) {
            if (mode == 'A') {
                std::int32_t graph; std::array<std::int32_t,7> percent{};
                if (!(std::cin >> graph)) return 2;
                for (auto& value : percent) if (!(std::cin >> value)) return 2;
                const auto result=allocate_weapon_damage(graph,percent);
                std::cout << result.physical;
                for (const auto value : result.bonus) std::cout << ' ' << value;
                std::cout << '\n'; continue;
            }
            if (mode == 'G') {
                std::int32_t magic; if (!(std::cin >> magic)) return 2;
                const auto input=effects();
                std::cout << evaluated_magic(magic,input) << '\n'; continue;
            }
            if (mode == 'D') {
                DamageDefense raw;
                if (!(std::cin >> raw.natural_armor >> raw.defense_attribute)) return 2;
                for (auto& value : raw.elemental_armor) if (!(std::cin >> value)) return 2;
                const auto input=effects(); const auto result=evaluate_damage_defense(raw,input);
                for (const auto value : result.maximum) std::cout << value << ' ';
                for (const auto value : result.percent_taken) std::cout << value << ' ';
                std::cout << '\n'; continue;
            }
            if (mode != 'R' && mode != 'S' && mode != 'L') throw std::runtime_error("invalid mode");
            SkillWeaponRoll skill;
            if (mode == 'S' || mode == 'L') {
                std::uint32_t weapon, soak, speed; unsigned dps;
                if (!(std::cin >> weapon >> soak >> dps >> speed) || dps > 1) return 2;
                skill = {float_bits(weapon), float_bits(soak), dps != 0, float_bits(speed)};
            }
            AttackCharacterValues character; AttackLoadout loadout; AttackDescription attack;
            attack.hand=AttackHand::right; attack.delivery=WeaponDelivery::direct_typed; attack.damage_allocation_known=true;
            unsigned flags; DamageDefense raw; std::uint64_t seed;
            if (!(std::cin >> attack.maximum_damage >> character.strength >> character.dexterity >> character.magic >> flags >> raw.natural_armor >> raw.defense_attribute >> seed)) return 2;
            attack.traits.ranged = (flags & 1) != 0;
            attack.traits.melee_specialization = (flags & 2) != 0;
            attack.traits.ranged_specialization = (flags & 4) != 0;
            attack.traits.shared_specialization = (flags & 8) != 0;
            for (auto& value : attack.damage_bonus) if (!(std::cin >> value)) return 2;
            for (auto& value : raw.elemental_armor) if (!(std::cin >> value)) return 2;
            character.effects=effects(); const auto target=effects();
            if (mode == 'L') { attack.hand=AttackHand::left; loadout.left=attack; }
            else loadout.right=attack;
            if (!seed || seed > UINT32_MAX) throw std::runtime_error("invalid seed");
            TorchlightRandom random(static_cast<std::uint32_t>(seed));
            const auto evaluated = evaluate_damage_defense(raw, target);
            const auto result = mode != 'R'
                ? roll_skill_weapon_damage(attack, loadout, character, evaluated, skill, random)
                : roll_ordinary_damage(attack, loadout, character, evaluated, random);
            std::cout << result.count << ' ' << result.maximum << ' ' << result.rolled << ' ' << result.applied << ' ' << random.state();
            for (std::size_t i=0; i<result.count; ++i) std::cout << ' ' << static_cast<unsigned>(result.types[i]) << ' ' << result.channels[i].applied;
            std::cout << '\n';
        }
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
