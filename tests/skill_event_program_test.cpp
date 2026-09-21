#include "torchlight/skill_event_program.hpp"
#include "torchlight/skills.hpp"
#include "torchlight/resource_fields.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
using namespace torchlight;
int checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
template<class F> void rejects(F&& operation, const char* message) {
    try { operation(); } catch (const std::invalid_argument&) { ++checks; return; }
    throw std::runtime_error(message);
}
void set(AdmGroup& group, std::u16string name, AdmValue value) {
    const auto found = std::find_if(group.properties.begin(), group.properties.end(),
        [&](const auto& p) { return p.name == name; });
    if (found != group.properties.end()) found->value = std::move(value);
    else group.properties.push_back({0, std::move(name), AdmValueType::string, std::move(value)});
}
void run(const char* path) {
    PakArchive pak(path);
    LevelSceneLoader loader(pak);
    // Reuse the production LEVEL inheritance evaluator, never a second parser.
    SkillCatalog catalog(pak);
    const auto* seeking = catalog.find(u"Seeking Shot");
    require(seeking && seeking->rank(1), "real SEEKING rank missing");
    const auto original = seeking->rank(1)->resource;
    const auto program = compile_skill_event_program(original, loader);
    require(program.events.size() == 2, "START/TRIGGER pair missing");
    require(program.events[0].type == SkillEventType::start && program.events[0].attaches,
        "START attachment lost");
    require(program.events[0].layout_path.find("warmup.layout") != std::string::npos,
        "START uses TRIGGER layout");
    const auto& trigger = program.events[1];
    require(trigger.type == SkillEventType::trigger && trigger.weapon_damage_pct == 40 &&
        trigger.soak_scale_pct == 60 && trigger.use_dps, "TRIGGER scalars lost");
    require(trigger.layout_path.find("seeking.layout") != std::string::npos,
        "TRIGGER uses START layout");
    require(program.use_weapon_animation && program.range == 13 && program.find_target_angle == 15 &&
        program.visual_effects_pending, "activation metadata lost");
    require(!trigger.scene.objects.empty(), "real TRIGGER scene not loaded");
    const auto rank_two = compile_skill_event_program(seeking->rank(2)->resource, loader);
    require(rank_two.events[1].weapon_damage_pct == 44 && rank_two.events[1].soak_scale_pct == 62,
        "production rank evaluator not consumed");
    auto changed = original;
    set(changed, u"NAME", std::u16string(u"Different resource skill"));
    require(compile_skill_event_program(changed, loader).events.size() == 2, "skill NAME whitelist");
    changed = original;
    auto& properties = changed.groups[1].properties;
    properties.erase(std::remove_if(properties.begin(), properties.end(), [](const auto& p) {
        return p.name == u"SOAKSCALEPCT" || p.name == u"USEDPS";
    }), properties.end());
    const auto defaults = compile_skill_event_program(changed, loader);
    require(defaults.events[1].soak_scale_pct == 100 && !defaults.events[1].use_dps,
        "constructor defaults lost");
    for (const auto& name : {u"CHANCE", u"TARGET_TYPE", u"ANIMATION"}) {
        changed = original; set(changed, name, std::u16string(u"unsupported"));
        rejects([&] { (void)compile_skill_event_program(changed, loader); }, "unknown gameplay field accepted");
    }
    changed = original; changed.groups[1].groups.push_back({0, u"EFFECT", {}, {}});
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "nested effect accepted");
    changed = original; changed.groups[1].name = u"EVENT_END";
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "unsupported event accepted");
    changed = original; changed.groups.pop_back();
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "no TRIGGER accepted");
    changed = original; changed.groups.push_back(changed.groups.back());
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "duplicate TRIGGER accepted");
    changed = original; set(changed.groups[1], u"WEAPONDAMAGEPCT", 0.0F);
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "zero weapon damage accepted");
    changed = original; set(changed.groups[1], u"SOAKSCALEPCT", std::numeric_limits<float>::infinity());
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "nonfinite scalar accepted");
    changed = original; set(changed.groups[1], u"USEDPS", std::u16string(u"true"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "untyped boolean accepted");
    changed = original; set(changed.groups[1], u"FILE", std::u16string(u"media/missing.layout"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "missing layout accepted");
    changed = original; set(changed.groups[1], u"FILE", std::u16string(u"media/layouts/test/LOGICTEST.LAYOUT"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "arbitrary gameplay scene accepted");
    changed = original; set(changed.groups[1], u"FILE", resource_fields::text(changed.groups[0],u"FILE"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "cosmetic scene silently accepted as missile program");
    changed = original; set(changed.groups[0], u"FILE", resource_fields::text(changed.groups[1],u"FILE"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "missile START scene accepted");
    changed = original; set(changed, u"REQUIREMENT_LEFT", std::u16string(u"itemcategorymelee"));
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "melee requirement accepted");
    changed = original;
    changed.properties.erase(std::remove_if(changed.properties.begin(), changed.properties.end(),
        [](const auto& p) { return p.name == u"FINDTARGETANGLE"; }), changed.properties.end());
    rejects([&] { (void)compile_skill_event_program(changed, loader); }, "unknown target angle default accepted");
}
}
int main(int argc, char** argv) {
    try {
        if (argc != 2) { std::cerr << "usage: skill_event_program_test <pak.zip>\n"; return 77; }
        run(argv[1]);
        std::cout << "PASS skill event program checks=" << checks << '\n';
        return 0;
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
