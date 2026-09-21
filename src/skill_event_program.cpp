#include "torchlight/skill_event_program.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/resource_fields.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace torchlight {
namespace {
namespace rf = resource_fields;
void fields(const AdmGroup& group, const std::set<std::u16string>& allowed) {
    for (const auto& property : group.properties) {
        const auto name = rf::upper(property.name);
        if (!allowed.count(name))
            throw std::invalid_argument("unsupported skill event program field: " + rf::ascii(name));
    }
}
float scalar(const AdmGroup& group, const std::u16string& name, float fallback) {
    const auto value = rf::number(group, name, fallback);
    if (!std::isfinite(value) || std::abs(value) > std::numeric_limits<float>::max())
        throw std::invalid_argument("skill event program scalar overflow: " + rf::ascii(name));
    return static_cast<float>(value);
}
}

SkillEventProgram compile_skill_event_program(const AdmGroup& rank, const LevelSceneLoader& loader) {
    fields(rank, {u"NAME", u"DISPLAYNAME", u"DESCRIPTION", u"SKILL_ICON", u"SKILL_ICON_INACTIVE",
        u"ACTIVATION_TYPE", u"TARGET_ALIGNMENT", u"USEWEAPONANIMATION", u"RANGE", u"FINDTARGETANGLE",
        u"REQUIREMENT_RIGHT", u"REQUIREMENT_LEFT", u"MAX_INVEST_LEVEL", u"MAXLEVEL", u"CAN_LEFT_MAP",
        u"UNIQUE_GUID", u"MANACOST", u"LEVEL_REQUIRED", u"COOLDOWNMS", u"MONSTERCOOLDOWNMS", u"SPEED"});
    if (rf::upper(rf::text(rank, u"ACTIVATION_TYPE")) != u"NORMAL" ||
        rf::upper(rf::text(rank, u"TARGET_ALIGNMENT")) != u"EVIL" ||
        !rf::flag(rank, u"USEWEAPONANIMATION") ||
        rf::upper(rf::text(rank, u"REQUIREMENT_RIGHT")) != u"ITEMCATEGORYRANGED" ||
        rf::upper(rf::text(rank, u"REQUIREMENT_LEFT")) != u"ITEMCATEGORYRANGED")
        throw std::invalid_argument("skill event program requires NORMAL EVIL ranged weapon activation");
    SkillEventProgram program;
    program.use_weapon_animation = true;
    if (!rf::field(rank, u"FINDTARGETANGLE"))
        throw std::invalid_argument("skill event program requires explicit FINDTARGETANGLE");
    program.range = scalar(rank, u"RANGE", 0);
    program.find_target_angle = scalar(rank, u"FINDTARGETANGLE", 0);
    if (!(program.range > 0) || program.find_target_angle < 0)
        throw std::invalid_argument("unsupported skill targeting range or angle");
    bool has_trigger = false, has_start = false;
    for (const auto& group : rank.groups) {
        const auto name = rf::upper(group.name);
        SkillEventDefinition event;
        if (name == u"EVENT_START") {
            if (has_start) throw std::invalid_argument("duplicate skill START event");
            has_start = true;
            fields(group, {u"FILE", u"ATTACHES"});
            event.type = SkillEventType::start;
            event.attaches = rf::flag(group, u"ATTACHES");
        } else if (name == u"EVENT_TRIGGER") {
            if (has_trigger) throw std::invalid_argument("duplicate skill TRIGGER event");
            has_trigger = true;
            fields(group, {u"FILE", u"WEAPONDAMAGEPCT", u"SOAKSCALEPCT", u"USEDPS"});
            event.type = SkillEventType::trigger;
            event.weapon_damage_pct = scalar(group, u"WEAPONDAMAGEPCT", 0);
            event.soak_scale_pct = scalar(group, u"SOAKSCALEPCT", 100);
            event.use_dps = rf::flag(group, u"USEDPS");
            if (!(event.weapon_damage_pct > 0))
                throw std::invalid_argument("skill TRIGGER requires positive weapon damage");
        } else {
            throw std::invalid_argument("unsupported skill event group: " + rf::ascii(name));
        }
        if (!group.groups.empty()) throw std::invalid_argument("nested skill event effects are unsupported");
        const auto file = rf::text(group, u"FILE");
        if (file.empty()) throw std::invalid_argument("skill event requires a layout FILE");
        event.layout_path = compiled_adm_path(file);
        try { event.scene = loader.load_layout(event.layout_path); }
        catch (const std::exception& error) {
            throw std::invalid_argument("cannot load skill event layout: " + std::string(error.what()));
        }
        // Portable admission boundary, not a claim to implement arbitrary
        // editor scenes. Do not silently discard other gameplay objects.
        if (!event.scene.logic_groups.empty())
            throw std::invalid_argument("skill scene logic graphs are unsupported");
        bool missile_spawner=false;
        for (const auto& object:event.scene.objects) {
            if (object.descriptor==u"Unit Spawner") {
                const auto* group=object.find_property(u"GROUP");
                const auto* resource=object.find_property(u"RESOURCE");
                const auto* group_name=group?std::get_if<std::u16string>(&group->value):nullptr;
                const auto* resource_name=resource?std::get_if<std::u16string>(&resource->value):nullptr;
                if (event.type!=SkillEventType::trigger || !group_name || *group_name!=u"Missiles" ||
                    !resource_name || resource_name->empty())
                    throw std::invalid_argument("skill scene requires a TRIGGER missile spawner");
                missile_spawner=true;
            } else if (object.descriptor!=u"Timeline" && object.descriptor!=u"Sound" &&
                       object.descriptor!=u"Layout Link Particle")
                throw std::invalid_argument("unsupported skill scene object: "+rf::ascii(object.descriptor));
        }
        for (const auto& point:event.scene.timeline_points) {
            const auto target=std::find_if(event.scene.objects.begin(),event.scene.objects.end(),
                [&](const auto& object){return object.id==point.target_object_id;});
            if (target==event.scene.objects.end())
                throw std::invalid_argument("skill timeline target is missing");
            if (target->descriptor==u"Unit Spawner" &&
                (point.time_percent!=0 || point.input_name!=u"Spawn Units"))
                throw std::invalid_argument("unsupported timed skill spawn");
        }
        if (event.type==SkillEventType::trigger && !missile_spawner)
            throw std::invalid_argument("skill TRIGGER scene has no missile spawner");
        program.events.push_back(std::move(event));
    }
    if (!has_trigger) throw std::invalid_argument("skill event program has no TRIGGER");
    // The original event layouts contain particles/sounds/attachment visuals.
    // Preserve their scenes, but do not claim renderer parity.
    program.visual_effects_pending = true;
    return program;
}
} // namespace torchlight
