#pragma once

namespace torchlight::original_combat_inputs {
// original-code: pinned ELF rodata, independently extracted by the integrator.
// See research/original-combat-inputs.json for virtual addresses, bytes and hash.
inline constexpr float speed_one = 1.0F;                  // 0xfa47fc
inline constexpr float percentage_divisor = 100.0F;       // 0xfa483c
inline constexpr float minimum_attack_speed = 0.2F;       // 0xfa86e8
inline constexpr float innate_attack_range = 0.375F;      // 0xfce4f8
inline constexpr float innate_strike_range = 0.5F;         // 0xfa4810
inline constexpr float melee_vertical_cutoff = 2.5F;      // 0xfce4c4
inline constexpr float ai_flag_one_speed_multiplier = 1.5F; // 0xfce498
inline constexpr char effect_catalog_path[] = "media/EffectsList.dat"; // 0xff82c8
inline constexpr char effect_catalog_compiled_path[] = "media/EffectsList.dat.adm";
} // namespace torchlight::original_combat_inputs
