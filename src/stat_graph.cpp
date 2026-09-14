#include "torchlight/stat_graph.hpp"

#include "torchlight/adm_document.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

namespace torchlight {
namespace {

class StatGraphError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

float required_float(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr || property->type != AdmValueType::floating) {
        throw StatGraphError("Stat graph point is missing a floating coordinate");
    }
    return std::get<float>(property->value);
}

} // namespace

StatGraph::StatGraph(const PakArchive& archive, std::string_view path) {
    const auto document = parse_adm(archive.read_normalized(path));
    if (document.root.name != u"LINE") {
        throw StatGraphError("Stat graph root is not LINE: " + std::string(path));
    }
    points_.reserve(document.root.groups.size());
    for (const auto& group : document.root.groups) {
        if (group.name != u"POINT") {
            throw StatGraphError("Stat graph child is not POINT: " + std::string(path));
        }
        const auto x = required_float(group, u"X");
        const auto y = required_float(group, u"Y");
        if (!std::isfinite(x) || !std::isfinite(y)) {
            throw StatGraphError("Stat graph contains a non-finite point: " +
                                 std::string(path));
        }
        points_.push_back({x, y});
    }
    if (points_.empty() ||
        !std::is_sorted(points_.begin(), points_.end(),
                        [](const auto& left, const auto& right) {
                            return left.x < right.x;
                        })) {
        throw StatGraphError("Stat graph is empty or unordered: " + std::string(path));
    }
}

float StatGraph::value(float x) const noexcept {
    if (x <= points_.front().x) {
        return points_.front().y;
    }
    for (std::size_t index = 1; index < points_.size(); ++index) {
        if (x <= points_[index].x) {
            const auto& left = points_[index - 1U];
            const auto& right = points_[index];
            const auto span = right.x - left.x;
            return span <= 0.0F
                       ? right.y
                       : left.y + (right.y - left.y) * ((x - left.x) / span);
        }
    }
    if (points_.size() == 1U) {
        return points_.back().y;
    }
    const auto& left = points_[points_.size() - 2U];
    const auto& right = points_.back();
    const auto span = right.x - left.x;
    return span <= 0.0F
               ? right.y
               : right.y + (right.y - left.y) * ((x - right.x) / span);
}

} // namespace torchlight
