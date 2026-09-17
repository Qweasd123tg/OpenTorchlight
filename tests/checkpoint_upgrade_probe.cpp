#include "torchlight/save_store.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: checkpoint_upgrade_probe owned-test-save");
        std::ifstream input(argv[1],std::ios::binary);
        if(!input) throw std::runtime_error("cannot read legacy fixture");
        const std::vector<std::uint8_t> bytes{std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>()};
        if(bytes.size()<20 || bytes[8]!=1) throw std::runtime_error("fixture is not v1");
        const auto saved=torchlight::decode_checkpoint(bytes);
        if(saved.player.progression) throw std::runtime_error("v1 invented progression");
        for(const auto& floor:saved.floors) for(const auto& entity:floor.world.entities)
            if(entity.gold_amount || entity.experience_reward || entity.player_kill || entity.reward_claimed)
                throw std::runtime_error("v1 migration manufactured world rewards");
        const auto current=torchlight::encode_checkpoint(saved);
        if(current[8]!=torchlight::kCheckpointFormatVersion || torchlight::encode_checkpoint(torchlight::decode_checkpoint(current))!=current)
            throw std::runtime_error("current-version upgrade not canonical");
        input.close();
        std::ofstream output(argv[1],std::ios::binary|std::ios::trunc);
        output.write(reinterpret_cast<const char*>(current.data()),static_cast<std::streamsize>(current.size()));
        output.close();if(!output)throw std::runtime_error("cannot write upgraded fixture");
        std::cout<<"PASS: frozen unmodified-large-7 v1 fixture upgraded without retroactive rewards\n";
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
