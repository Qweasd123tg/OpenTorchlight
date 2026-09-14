#pragma once

#include "torchlight/pak_archive.hpp"

#include <cstddef>
#include <string_view>
#include <vector>

namespace torchlight {

class StatGraph {
public:
    StatGraph(const PakArchive& archive, std::string_view path);

    [[nodiscard]] float value(float x) const noexcept;
    [[nodiscard]] std::size_t size() const noexcept { return points_.size(); }

private:
    struct Point {
        float x = 0.0F;
        float y = 0.0F;
    };

    std::vector<Point> points_;
};

} // namespace torchlight
