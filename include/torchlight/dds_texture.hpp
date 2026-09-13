#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace torchlight {

class DdsError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

enum class DdsFormat {
    dxt1,
    dxt3,
    dxt5,
    rgb24,
    rgba32,
};

struct DdsImage {
    std::uint32_t width = 0;
    std::uint32_t height = 0;
    std::uint32_t mip_count = 1;
    DdsFormat format = DdsFormat::dxt1;
    std::vector<std::uint8_t> rgba;
};

[[nodiscard]] DdsImage decode_dds(const std::vector<std::uint8_t>& bytes);

} // namespace torchlight
