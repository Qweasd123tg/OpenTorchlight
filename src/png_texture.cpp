#include "torchlight/png_texture.hpp"

#include <png.h>

#include <limits>

namespace torchlight {

PngImage decode_png(const std::vector<std::uint8_t>& bytes) {
    if (bytes.empty()) {
        throw PngError("PNG input is empty");
    }
    png_image image{};
    image.version = PNG_IMAGE_VERSION;
    if (png_image_begin_read_from_memory(&image, bytes.data(), bytes.size()) == 0) {
        throw PngError("PNG header is invalid");
    }
    image.format = PNG_FORMAT_RGBA;
    const auto output_size = PNG_IMAGE_SIZE(image);
    if (output_size == 0 || output_size > std::numeric_limits<std::size_t>::max()) {
        png_image_free(&image);
        throw PngError("PNG output size is invalid");
    }
    PngImage result;
    result.width = image.width;
    result.height = image.height;
    result.rgba.resize(static_cast<std::size_t>(output_size));
    if (png_image_finish_read(&image, nullptr, result.rgba.data(), 0, nullptr) == 0) {
        png_image_free(&image);
        throw PngError("PNG pixel decoding failed");
    }
    png_image_free(&image);
    return result;
}

} // namespace torchlight
