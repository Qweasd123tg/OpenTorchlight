#include "torchlight/dds_texture.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>

namespace torchlight {
namespace {

constexpr std::uint32_t dds_magic = 0x20534444U;
constexpr std::uint32_t dds_header_size = 124U;
constexpr std::uint32_t dds_pixel_format_size = 32U;
constexpr std::uint32_t ddpf_alpha_pixels = 0x1U;
constexpr std::uint32_t ddpf_four_cc = 0x4U;
constexpr std::uint32_t ddpf_rgb = 0x40U;
constexpr std::size_t pixel_data_offset = 128U;

constexpr std::uint32_t four_cc(char a, char b, char c, char d) noexcept {
    return static_cast<std::uint32_t>(static_cast<unsigned char>(a)) |
           (static_cast<std::uint32_t>(static_cast<unsigned char>(b)) << 8U) |
           (static_cast<std::uint32_t>(static_cast<unsigned char>(c)) << 16U) |
           (static_cast<std::uint32_t>(static_cast<unsigned char>(d)) << 24U);
}

std::uint16_t little_u16(const std::uint8_t* data) noexcept {
    return static_cast<std::uint16_t>(data[0]) |
           static_cast<std::uint16_t>(static_cast<std::uint16_t>(data[1]) << 8U);
}

std::uint32_t little_u32(const std::uint8_t* data) noexcept {
    return static_cast<std::uint32_t>(data[0]) |
           (static_cast<std::uint32_t>(data[1]) << 8U) |
           (static_cast<std::uint32_t>(data[2]) << 16U) |
           (static_cast<std::uint32_t>(data[3]) << 24U);
}

std::size_t checked_pixel_bytes(std::uint32_t width, std::uint32_t height) {
    if (width == 0 || height == 0) {
        throw DdsError("DDS dimensions must be positive");
    }
    constexpr auto maximum = std::numeric_limits<std::size_t>::max();
    if (width > maximum / height || static_cast<std::size_t>(width) * height > maximum / 4U) {
        throw DdsError("DDS dimensions overflow the output buffer size");
    }
    return static_cast<std::size_t>(width) * height * 4U;
}

std::size_t checked_source_bytes(std::uint32_t width, std::uint32_t height,
                                 std::size_t block_size) {
    const auto blocks_wide = (static_cast<std::size_t>(width) + 3U) / 4U;
    const auto blocks_high = (static_cast<std::size_t>(height) + 3U) / 4U;
    if (blocks_wide > std::numeric_limits<std::size_t>::max() / blocks_high ||
        blocks_wide * blocks_high > std::numeric_limits<std::size_t>::max() / block_size) {
        throw DdsError("DDS block count overflows the source size");
    }
    return blocks_wide * blocks_high * block_size;
}

std::array<std::uint8_t, 4> rgb565(std::uint16_t value) noexcept {
    const auto red = static_cast<std::uint8_t>((value >> 11U) & 0x1fU);
    const auto green = static_cast<std::uint8_t>((value >> 5U) & 0x3fU);
    const auto blue = static_cast<std::uint8_t>(value & 0x1fU);
    return {static_cast<std::uint8_t>((red << 3U) | (red >> 2U)),
            static_cast<std::uint8_t>((green << 2U) | (green >> 4U)),
            static_cast<std::uint8_t>((blue << 3U) | (blue >> 2U)), 255U};
}

std::array<std::array<std::uint8_t, 4>, 4> color_palette(const std::uint8_t* block,
                                                         bool allow_transparency) noexcept {
    const auto color0 = little_u16(block);
    const auto color1 = little_u16(block + 2);
    std::array<std::array<std::uint8_t, 4>, 4> palette{};
    palette[0] = rgb565(color0);
    palette[1] = rgb565(color1);
    if (allow_transparency && color0 <= color1) {
        for (unsigned channel = 0; channel < 3; ++channel) {
            palette[2][channel] = static_cast<std::uint8_t>(
                (static_cast<unsigned>(palette[0][channel]) + palette[1][channel]) / 2U);
        }
        palette[2][3] = 255U;
        palette[3] = {0U, 0U, 0U, 0U};
    } else {
        for (unsigned channel = 0; channel < 3; ++channel) {
            palette[2][channel] = static_cast<std::uint8_t>(
                (2U * palette[0][channel] + palette[1][channel]) / 3U);
            palette[3][channel] = static_cast<std::uint8_t>(
                (palette[0][channel] + 2U * palette[1][channel]) / 3U);
        }
        palette[2][3] = 255U;
        palette[3][3] = 255U;
    }
    return palette;
}

void write_pixel(DdsImage& image, std::uint32_t x, std::uint32_t y,
                 const std::array<std::uint8_t, 4>& pixel) {
    if (x >= image.width || y >= image.height) {
        return;
    }
    const auto offset = (static_cast<std::size_t>(y) * image.width + x) * 4U;
    std::copy(pixel.begin(), pixel.end(), image.rgba.begin() + static_cast<std::ptrdiff_t>(offset));
}

void decode_dxt_color_block(DdsImage& image, const std::uint8_t* colors,
                            std::uint32_t block_x, std::uint32_t block_y,
                            bool allow_transparency,
                            const std::array<std::uint8_t, 16>* alpha) {
    const auto palette = color_palette(colors, allow_transparency);
    const auto selectors = little_u32(colors + 4);
    for (std::uint32_t pixel = 0; pixel < 16; ++pixel) {
        auto color = palette[(selectors >> (pixel * 2U)) & 0x3U];
        if (alpha != nullptr) {
            color[3] = (*alpha)[pixel];
        }
        write_pixel(image, block_x * 4U + pixel % 4U, block_y * 4U + pixel / 4U, color);
    }
}

void decode_dxt(DdsImage& image, const std::uint8_t* source, std::size_t source_size) {
    const bool is_dxt1 = image.format == DdsFormat::dxt1;
    const std::size_t block_size = is_dxt1 ? 8U : 16U;
    const auto required = checked_source_bytes(image.width, image.height, block_size);
    if (source_size < required) {
        throw DdsError("DDS compressed top mip is truncated");
    }
    const auto blocks_wide = (image.width + 3U) / 4U;
    const auto blocks_high = (image.height + 3U) / 4U;
    for (std::uint32_t block_y = 0; block_y < blocks_high; ++block_y) {
        for (std::uint32_t block_x = 0; block_x < blocks_wide; ++block_x) {
            const auto* block = source +
                                (static_cast<std::size_t>(block_y) * blocks_wide + block_x) *
                                    block_size;
            if (is_dxt1) {
                decode_dxt_color_block(image, block, block_x, block_y, true, nullptr);
                continue;
            }
            std::array<std::uint8_t, 16> alpha{};
            if (image.format == DdsFormat::dxt3) {
                for (unsigned pixel = 0; pixel < 16; ++pixel) {
                    const auto nibble = static_cast<std::uint8_t>(
                        (block[pixel / 2U] >> ((pixel % 2U) * 4U)) & 0xfU);
                    alpha[pixel] = static_cast<std::uint8_t>((nibble << 4U) | nibble);
                }
            } else {
                std::array<std::uint8_t, 8> palette{};
                palette[0] = block[0];
                palette[1] = block[1];
                if (palette[0] > palette[1]) {
                    for (unsigned index = 2; index < 8; ++index) {
                        palette[index] = static_cast<std::uint8_t>(
                            ((8U - index) * palette[0] + (index - 1U) * palette[1]) / 7U);
                    }
                } else {
                    for (unsigned index = 2; index < 6; ++index) {
                        palette[index] = static_cast<std::uint8_t>(
                            ((6U - index) * palette[0] + (index - 1U) * palette[1]) / 5U);
                    }
                    palette[6] = 0U;
                    palette[7] = 255U;
                }
                std::uint64_t selectors = 0;
                for (unsigned byte = 0; byte < 6; ++byte) {
                    selectors |= static_cast<std::uint64_t>(block[2U + byte]) << (byte * 8U);
                }
                for (unsigned pixel = 0; pixel < 16; ++pixel) {
                    alpha[pixel] = palette[(selectors >> (pixel * 3U)) & 0x7U];
                }
            }
            decode_dxt_color_block(image, block + 8, block_x, block_y, false, &alpha);
        }
    }
}

std::uint8_t extract_channel(std::uint32_t pixel, std::uint32_t mask,
                             std::uint8_t fallback) noexcept {
    if (mask == 0) {
        return fallback;
    }
    unsigned shift = 0;
    while (((mask >> shift) & 1U) == 0U) {
        ++shift;
    }
    const auto shifted_mask = mask >> shift;
    const auto value = (pixel & mask) >> shift;
    return static_cast<std::uint8_t>((static_cast<std::uint64_t>(value) * 255U +
                                      shifted_mask / 2U) /
                                     shifted_mask);
}

void decode_rgb(DdsImage& image, const std::uint8_t* source, std::size_t source_size,
                std::uint32_t bits, std::uint32_t red_mask, std::uint32_t green_mask,
                std::uint32_t blue_mask, std::uint32_t alpha_mask) {
    const auto bytes_per_pixel = static_cast<std::size_t>(bits / 8U);
    const auto row_bytes = static_cast<std::size_t>(image.width) * bytes_per_pixel;
    if (row_bytes > std::numeric_limits<std::size_t>::max() - 3U) {
        throw DdsError("DDS row size overflows");
    }
    const auto stride = (row_bytes + 3U) & ~std::size_t{3U};
    if (image.height > std::numeric_limits<std::size_t>::max() / stride ||
        source_size < stride * image.height) {
        throw DdsError("DDS uncompressed top mip is truncated");
    }
    for (std::uint32_t y = 0; y < image.height; ++y) {
        const auto* row = source + static_cast<std::size_t>(y) * stride;
        for (std::uint32_t x = 0; x < image.width; ++x) {
            const auto* encoded = row + static_cast<std::size_t>(x) * bytes_per_pixel;
            std::uint32_t pixel = encoded[0] | (static_cast<std::uint32_t>(encoded[1]) << 8U) |
                                  (static_cast<std::uint32_t>(encoded[2]) << 16U);
            if (bytes_per_pixel == 4U) {
                pixel |= static_cast<std::uint32_t>(encoded[3]) << 24U;
            }
            write_pixel(image, x, y,
                        {extract_channel(pixel, red_mask, 0U),
                         extract_channel(pixel, green_mask, 0U),
                         extract_channel(pixel, blue_mask, 0U),
                         extract_channel(pixel, alpha_mask, 255U)});
        }
    }
}

} // namespace

DdsImage decode_dds(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < pixel_data_offset) {
        throw DdsError("DDS file is shorter than its header");
    }
    if (little_u32(bytes.data()) != dds_magic || little_u32(bytes.data() + 4) != dds_header_size ||
        little_u32(bytes.data() + 76) != dds_pixel_format_size) {
        throw DdsError("DDS header is invalid");
    }

    DdsImage image;
    image.height = little_u32(bytes.data() + 12);
    image.width = little_u32(bytes.data() + 16);
    image.mip_count = std::max(1U, little_u32(bytes.data() + 28));
    image.rgba.resize(checked_pixel_bytes(image.width, image.height));

    const auto pixel_flags = little_u32(bytes.data() + 80);
    const auto encoded_format = little_u32(bytes.data() + 84);
    const auto* source = bytes.data() + pixel_data_offset;
    const auto source_size = bytes.size() - pixel_data_offset;
    if ((pixel_flags & ddpf_four_cc) != 0U) {
        if (encoded_format == four_cc('D', 'X', 'T', '1')) {
            image.format = DdsFormat::dxt1;
        } else if (encoded_format == four_cc('D', 'X', 'T', '3')) {
            image.format = DdsFormat::dxt3;
        } else if (encoded_format == four_cc('D', 'X', 'T', '5')) {
            image.format = DdsFormat::dxt5;
        } else {
            throw DdsError("DDS FourCC is unsupported: " + std::to_string(encoded_format));
        }
        decode_dxt(image, source, source_size);
        return image;
    }

    const auto bits = little_u32(bytes.data() + 88);
    if ((pixel_flags & ddpf_rgb) == 0U || (bits != 24U && bits != 32U)) {
        throw DdsError("DDS uncompressed pixel format is unsupported");
    }
    image.format = bits == 24U ? DdsFormat::rgb24 : DdsFormat::rgba32;
    const auto alpha_mask = (pixel_flags & ddpf_alpha_pixels) != 0U
                                ? little_u32(bytes.data() + 104)
                                : 0U;
    decode_rgb(image, source, source_size, bits, little_u32(bytes.data() + 92),
               little_u32(bytes.data() + 96), little_u32(bytes.data() + 100), alpha_mask);
    return image;
}

} // namespace torchlight
