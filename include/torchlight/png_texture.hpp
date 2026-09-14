#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace torchlight {

class PngError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct PngImage {
    std::uint32_t width = 0;
    std::uint32_t height = 0;
    std::vector<std::uint8_t> rgba;
};

[[nodiscard]] PngImage decode_png(const std::vector<std::uint8_t>& bytes);

// CWardrobe::update copies the opaque base and source-alpha composites each
// following same-size layer, forcing the destination alpha to 255.
[[nodiscard]] PngImage compose_png_layers(const std::vector<PngImage>& layers);

} // namespace torchlight
