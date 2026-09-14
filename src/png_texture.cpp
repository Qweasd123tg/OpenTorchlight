#include "torchlight/png_texture.hpp"

#include <png.h>

#include <limits>
#include <stdexcept>

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

PngImage compose_png_layers(const std::vector<PngImage>& layers) {
    if (layers.empty()) {
        throw PngError("PNG layer stack is empty");
    }
    PngImage result = layers.front();
    if (result.width == 0 || result.height == 0 ||
        result.rgba.size() !=
            static_cast<std::size_t>(result.width) * result.height * 4U) {
        throw PngError("PNG base layer dimensions are invalid");
    }
    for (std::size_t pixel = 0; pixel < result.rgba.size(); pixel += 4U) {
        result.rgba[pixel + 3U] = 255U;
    }
    for (std::size_t layer_index = 1; layer_index < layers.size(); ++layer_index) {
        const auto& layer = layers[layer_index];
        if (layer.width != result.width || layer.height != result.height ||
            layer.rgba.size() != result.rgba.size()) {
            throw PngError("PNG wardrobe layers have different dimensions");
        }
        for (std::size_t pixel = 0; pixel < result.rgba.size(); pixel += 4U) {
            const auto alpha = layer.rgba[pixel + 3U];
            if (alpha == 255U) {
                result.rgba[pixel] = layer.rgba[pixel];
                result.rgba[pixel + 1U] = layer.rgba[pixel + 1U];
                result.rgba[pixel + 2U] = layer.rgba[pixel + 2U];
            } else if (alpha != 0U) {
                const float source_weight = static_cast<float>(alpha) / 255.0F;
                const float destination_weight = 1.0F - source_weight;
                for (std::size_t channel = 0; channel < 3U; ++channel) {
                    result.rgba[pixel + channel] = static_cast<std::uint8_t>(
                        static_cast<float>(layer.rgba[pixel + channel]) * source_weight +
                        static_cast<float>(result.rgba[pixel + channel]) *
                            destination_weight);
                }
            }
            result.rgba[pixel + 3U] = 255U;
        }
    }
    return result;
}

} // namespace torchlight
