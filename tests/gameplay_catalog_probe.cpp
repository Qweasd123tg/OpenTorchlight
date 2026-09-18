// Resource inventory, not an original-code or whole-game equivalence test.
#include "torchlight/diagnostic_json.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/unit_type.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace torchlight;
namespace {
std::string narrow(std::u16string_view s){std::string r;for(const auto c:s)r.push_back(c<128?static_cast<char>(c):'?');return r;}
}
int main(int argc,char**argv){try {
    if(argc!=3)throw std::runtime_error("usage: gameplay_catalog_probe pak.zip report.json");
    PakArchive pak(argv[1]);UnitDefinitionLoader defs(pak);UnitTypeHierarchy hierarchy(pak);
    MasterResourceIndex resources(parse_adm(pak.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
    std::array<unsigned,5> categories{};unsigned seen=0,melee_blocked=0,excluded=0,requirements=0;
    std::ostringstream examples;bool comma=false;unsigned examples_count=0;
    for(const auto&r:resources.records()) {
        if(r.kind!=MasterResourceKind::item)continue;
        if(r.do_not_create){++excluded;continue;}
        const auto d=defs.load(r);
        bool required=false;
        for(const auto*key:{u"LEVEL_REQUIRED",u"STRENGTH_REQUIRED",u"DEXTERITY_REQUIRED",u"MAGIC_REQUIRED",u"DEFENSE_REQUIRED"}) {
            const auto*p=d->find_property(key);
            if(p&&p->type==AdmValueType::integer&&std::get<std::int32_t>(p->value)>0)required=true;
        }
        if(required)++requirements;
        if(!hierarchy.is_a_id(r.unit_type,8))continue;
        ++seen;const auto delivery=load_weapon_delivery(*d);++categories.at(static_cast<std::size_t>(delivery));
        const auto traits=weapon_attack_traits(r.unit_type,hierarchy);
        AttackDescription attack;attack.delivery=delivery;attack.traits=traits;
        if(!traits.ranged&&!ordinary_delivery_supported(attack)) {
            ++melee_blocked;
            if(examples_count++<12) {
                if(comma) examples<<',';
                comma=true;
                examples<<"{\"name\":";diagnostic::string(examples,narrow(r.name));
                examples<<",\"type\":";diagnostic::string(examples,narrow(r.unit_type));
                examples<<",\"path\":";diagnostic::string(examples,r.compiled_adm_path());
                examples<<",\"reason\":";diagnostic::string(examples,weapon_delivery_issue(delivery));examples<<'}';
            }
        }
    }
    std::ofstream out(argv[2]);
    out<<"{\"scope\":\"Current inherited UNIT loader + original unit-type hierarchy, non-DONTCREATE master item records. Not active instances, drop reachability, supported full weapons or an ELF comparison.\","
       <<"\"weapon_records\":"<<seen<<",\"excluded_DONTCREATE_items\":"<<excluded
       <<",\"items_with_positive_requirement_properties\":"<<requirements
       <<",\"delivery\":{\"unverified\":"<<categories[0]<<",\"direct_physical\":"<<categories[1]
       <<",\"missile\":"<<categories[2]<<",\"weapon_skill\":"<<categories[3]<<",\"unsupported_damage\":"<<categories[4]
       <<"},\"known_unsupported_melee\":"<<melee_blocked<<",\"examples\":["<<examples.str()<<"]}\n";
    if(!out)throw std::runtime_error("cannot write catalog report");
    std::cout<<"weapons="<<seen<<" known_unsupported_melee="<<melee_blocked<<" requirement_records="<<requirements<<'\n';
    return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
