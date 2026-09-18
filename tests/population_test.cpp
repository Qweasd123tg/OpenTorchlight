#include "ai_cooldown_fixture.hpp"
#include "torchlight/population.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/collision_scene.hpp"
#include "torchlight/random_level.hpp"
#include "torchlight/actor_motion.hpp"
#include <cmath>
#include <iostream>
#include <limits>
using namespace torchlight;
namespace {
unsigned checks = 0;
void require(bool b, const char* what) { ++checks; if (!b) throw std::runtime_error(what); }
void floor(CollisionScene& c, float x0, float z0, float x1, float z1) {
    c.triangles.push_back({{{{x0,0,z0},{x1,0,z1},{x1,0,z0}}}});
    c.triangles.push_back({{{{x0,0,z0},{x0,0,z1},{x1,0,z1}}}});
}
CampaignCheckpoint checkpoint(RuntimeEntityWorld& world, LogicRuntime& logic, EnemyController& enemies) {
    CampaignCheckpoint c; c.slot="population"; c.class_guid=1;c.resource_identity=1;c.character_name="Population";
    FloorCheckpoint f; f.address={u"Town",0}; f.layout_identity=checkpoint_layout_identity(test_fixture::layout());
    f.world=CheckpointAccess::capture(world);f.logic=CheckpointAccess::capture(logic);f.enemies=CheckpointAccess::capture(enemies);
    c.floors.push_back(f);return c;
}
void cycle(const char* path) {
    TorchlightRandom rng(17), untouched(17);
    require(population_count(0,0,.01F,.01F,650,rng)==1,"density pathable divisor incorrect");
    require(population_count(0,0,.01F,.01F,651,rng)==2,"density does not ceil");
    require(population_count(2,2,99,99,0,rng)==2,"fixed count not overriding density");
    require(population_count(0,0,0,.5F,999,rng)==0,"one zero density must suppress population");
    require(rng.state()==untouched.state(),"constant count unnecessarily consumes RNG");
    for (int i=0;i<100;++i) { auto n=population_count(7,3,0,0,1,rng); require(n>=3 && n<=7,"reversed count range"); }
    bool rejected=false;try {static_cast<void>(population_count(0,0,std::numeric_limits<float>::infinity(),1,1,rng));} catch(const std::invalid_argument&) {rejected=true;}
    require(rejected,"nonfinite density accepted");
    CollisionScene scene;floor(scene,0,0,30,30);floor(scene,40,0,50,10);
    auto grid=NavigationGrid::build(scene,.4F);
    // original-code: rejection sampling has no connectivity/exclusion policy
    // (research/population-placement.md). Walkability is per-cell now.
    require(grid_point_walkable(grid,5,5),"open floor cell rejected");
    require(!grid_point_walkable(grid,35,5),"gap between islands accepted");
    require(!grid_point_walkable(grid,100,100),"out-of-bounds accepted");
    {
        // Determinism and bounds of the original-order sampler on an authored grid.
        TorchlightRandom a(5), b(5);
        const auto pa = section_spawn_point(grid,0,30,0,30,0,{},a);
        const auto pb = section_spawn_point(grid,0,30,0,30,0,{},b);
        require(pa.has_value() && pb.has_value(),"authored section point missing");
        require(*pa==*pb,"same seed section point differs");
        require((*pa)[0]>=0&&(*pa)[0]<=30&&(*pa)[2]>=0&&(*pa)[2]<=30,"section point outside rect");
        // Point exclusions use the original 1.0 radius: a wall of exclusions
        // forces exhaustion to nullopt instead of inventing a placement.
        std::vector<std::array<float,3>> wall;
        for(float x=0;x<=30;x+=0.5F) for(float z=0;z<=30;z+=0.5F) wall.push_back({x,0,z});
        TorchlightRandom c(5);
        require(!section_spawn_point(grid,0,30,0,30,0,wall,c).has_value(),"exhaustion must yield nullopt");
    }
    test_fixture::World f(path), other(path);EnemyController enemies(1);
    TorchlightRandom choice(1);
    require(f.spawn_classes.roll(u"ZERO_REQUIRED", choice).size()==1,"zero WEIGHT discarded");
    require(f.spawn_classes.roll(u"DEFAULT_REQUIRED", choice).size()==1,"absent weight / zero count discarded");
    PopulationSettings s;s.monster_class=u"POPULATION";s.minimum_count=12;s.maximum_count=12;s.minimum_level=2;s.maximum_level=4;
    const auto report=f.world.populate(s,grid,{1,0,1});
    std::cout<<"created="<<report.created<<" missing="<<report.missing_resources<<" unsupported="<<report.unsupported_resources<<'\n';
    require(report.created==12 && report.requested==12,"authored population not created");
    const auto again=other.world.populate(s,grid,{1,0,1});require(again.created==12,"same seed create count");
    require(encode_checkpoint(checkpoint(f.world,f.logic,enemies))==encode_checkpoint(checkpoint(other.world,other.logic,enemies)),"same seed population differs");
    for(const auto& e:f.world.entities()) require(e.level>=2&&e.level<=4&&e.alive&&e.combat_targetable,"population level/hostility not applied");
    const auto before=encode_checkpoint(checkpoint(f.world,f.logic,enemies));
    require(f.world.populate(s,grid,{1,0,1}).already_generated,"repeat population not rejected");
    require(encode_checkpoint(checkpoint(f.world,f.logic,enemies))==before,"repeat population mutates state");
    auto saved=decode_checkpoint(before);test_fixture::World restored(path);EnemyController restored_enemies(99);
    CheckpointAccess::restore_floor(saved.floors[0],restored.world,restored.logic,restored_enemies);
    require(restored.world.populate(s,grid,{1,0,1}).already_generated,"restored floor repopulates");
    require(encode_checkpoint(checkpoint(restored.world,restored.logic,restored_enemies))==before,"restored population differs");
    const auto killed=f.world.entities()[0].id;
    require(f.world.apply_damage(killed,100000,f.logic,true).killed,"populated monster cannot die");
    static_cast<void>(f.world.resolve_death_loot(f.logic));
    require(!f.world.find(killed)->alive,"populated monster resurrected during loot");
    test_fixture::World invalid(path);s.randomized_class=true;s.monster_class=u"POPULATION";
    const auto invalid_before=encode_checkpoint(checkpoint(invalid.world,invalid.logic,enemies));
    rejected=false;try{static_cast<void>(invalid.world.populate(s,grid,{1,0,1}));}catch(const std::runtime_error&){rejected=true;}
    require(rejected&&encode_checkpoint(checkpoint(invalid.world,invalid.logic,enemies))==invalid_before,"failed population commits partial state");
    s.monster_class=u"RANDOM_POPULATION";require(invalid.world.populate(s,grid,{1,0,1}).created==12,"random nested class not resolved");
    test_fixture::World none(path);s.randomized_class=false;s.monster_class=u"NONE";require(none.world.populate(s,grid,{1,0,1}).created==0,"boss NONE class spawns mobs");
    test_fixture::World unsafe(path);s.monster_class=u"UNSAFE_POPULATION";require(unsafe.world.populate(s,grid,{1,0,1}).unsupported_resources==12&&unsafe.world.entities().empty(),"non-monster hostile population");
}
void original(const char* path) {
    PakArchive archive(path);MasterResourceIndex resources(parse_adm(archive.read_normalized("media/MASTERRESOURCEUNITS.DAT.ADM")));
    UnitDefinitionLoader definitions(archive);SpawnClassCatalog classes(archive);UnitTypeHierarchy hierarchy(archive);UnitTypeResourceIndex types(archive,hierarchy,resources,definitions);
    LevelSceneLoader loader(archive);LevelsetCatalog levelsets(archive);auto dungeon=loader.load_dungeon(u"media/dungeons/MAIN.DAT");
    require(dungeon.strata.size()>4,"original strata missing");
    auto first=loader.load_rules(dungeon.strata[0].ruleset);apply_population_overrides(first.population,dungeon.strata[0].population_overrides);
    require(first.population.monster_class==u"MINEFLOOR1"&&std::abs(first.population.minimum_density-.0175F)<1e-7F,"first stratum overrides lost");
    auto fifth=loader.load_rules(dungeon.strata[4].ruleset);apply_population_overrides(fifth.population,dungeon.strata[4].population_overrides);
    require(fifth.population.monster_class==u"GOTHICFLOOR1"&&fifth.population.minimum_level==4,"fifth floor used depth as monster level");
    auto boss=loader.load_rules(dungeon.strata[3].ruleset);apply_population_overrides(boss.population,dungeon.strata[3].population_overrides);
    require(boss.population.monster_class==u"NONE","boss population incorrectly inferred");
    RandomLevelGenerator generator(loader);auto generated=generator.generate(first,42);
    auto composition=compose_generated_level_layout(loader,generated);static_cast<void>(expand_layout_links(loader,composition.layout));
    auto collision=build_generated_level_collision(archive,levelsets,loader,generated);
    auto nav=NavigationGrid::build(collision,.4F);auto entry=generated_player_start(loader,generated);
    RuntimeEntityWorld world(composition.layout,resources,definitions,classes,types,42,1);
    const auto count_before=world.entities().size();const auto report=world.populate(first.population,nav,entry);
    std::cout<<"actual requested="<<report.requested<<" created="<<report.created<<" missing="<<report.missing_resources<<" unsupported="<<report.unsupported_resources<<" unplaced="<<report.unplaced<<"\n";
    require(report.requested>0&&report.created>0,"real mine population empty");
    require(report.missing_resources==0&&report.unsupported_resources==0,"real ordinary mine species unresolved");
    require(world.entities().size()==count_before+report.created,"real population accounting");
    for(std::size_t i=count_before;i<world.entities().size();++i) {
        const auto& e=world.entities()[i];require(e.level==1&&e.alive&&e.combat_targetable&&e.maximum_health>0,"real monster invalid");
        require(!e.mesh_path.empty()&&archive.contains_normalized(e.mesh_path),"real population invisible mesh");
    }
    std::cout<<"original_mine nodes="<<report.pathable_nodes<<" candidates="<<report.reachable_nodes<<" requested="<<report.requested<<" created="<<report.created<<" unplaced="<<report.unplaced<<'\n';
}
}
int main(int argc,char**argv) {try {
    if(argc==3&&std::string(argv[1])=="--original")original(argv[2]);
    else if(argc==2)cycle(argv[1]);else throw std::runtime_error("arguments");
    std::cout<<"checks="<<checks<<" passed\n";return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
