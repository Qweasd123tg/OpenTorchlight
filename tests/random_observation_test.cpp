#include "torchlight/randomizer.hpp"
#include <array>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
struct Records { std::array<RandomObservation, 10> items{}; std::size_t count = 0; };
void record(const RandomObservation& e, void* p) noexcept {
    auto& r = *static_cast<Records*>(p);
    if (r.count < r.items.size()) r.items[r.count++] = e;
}
int main() {
    try {
        const auto require = [](bool ok) { if (!ok) throw std::runtime_error("observation changed RNG or lost a call"); };
        TorchlightRandom baseline(49);
        auto a = baseline.integer_between(-10, 20); auto b = baseline.between(-2, 7);
        Records r, nested;
        {
            RandomObservationScope scope(record, &r);
            TorchlightRandom random(49);
            require(random.integer_between(-10,20) == a); require(random.between(-2,7) == b);
            require(random.integer_between(5,5) == 5);
            { RandomObservationScope inner(record, &nested); require(random.between(0,0) == 0); }
            require(random.state() == baseline.state());
            require(random.integer_between(9,1) == 9);
        }
        TorchlightRandom after(49); (void)after.integer_between(1,10);
        require(r.count == 5 && nested.count == 1);
        require(r.items[0].kind == RandomObservation::Kind::seed);
        require(r.items[1].kind == RandomObservation::Kind::integer && r.items[1].before == 49);
        require(r.items[2].kind == RandomObservation::Kind::real && r.items[2].before == r.items[1].after);
        require(r.items[3].before == r.items[3].after && r.items[4].before == r.items[4].after);
        std::cout << "RNG sequence, degenerate calls, nested observer and unchanged results checked.\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
