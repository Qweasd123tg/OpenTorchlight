#include "torchlight/pak_archive.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <limits>
#include <sstream>

#include <zlib.h>

namespace torchlight {
namespace {

constexpr std::uint32_t local_signature = 0x04034b50;
constexpr std::uint32_t central_signature = 0x02014b50;
constexpr std::uint32_t end_signature = 0x06054b50;
constexpr std::size_t end_record_size = 22;
constexpr std::size_t maximum_comment_size = 65535;

std::string normalize_entry_name(std::string_view name) {
    std::string result;
    result.reserve(name.size());
    for (const unsigned char character : name) {
        if (character == '\\') {
            result.push_back('/');
        } else if (character >= 'A' && character <= 'Z') {
            result.push_back(static_cast<char>(character - 'A' + 'a'));
        } else {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
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

std::uint64_t checked_add(std::uint64_t left, std::uint64_t right, std::string_view context) {
    if (right > std::numeric_limits<std::uint64_t>::max() - left) {
        throw PakError(std::string(context) + ": integer overflow");
    }
    return left + right;
}

std::vector<std::uint8_t> read_at(std::ifstream& stream, std::uint64_t offset, std::size_t size,
                                  std::uint64_t file_size, std::string_view context) {
    if (checked_add(offset, size, context) > file_size ||
        offset > static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max())) {
        throw PakError(std::string(context) + ": range is outside the archive");
    }
    std::vector<std::uint8_t> result(size);
    stream.clear();
    stream.seekg(static_cast<std::streamoff>(offset));
    if (!stream || (size != 0 && !stream.read(reinterpret_cast<char*>(result.data()),
                                              static_cast<std::streamsize>(size)))) {
        throw PakError(std::string(context) + ": could not read archive bytes");
    }
    return result;
}

std::uint32_t calculate_crc(const std::vector<std::uint8_t>& bytes) noexcept {
    uLong crc = crc32(0L, Z_NULL, 0);
    std::size_t offset = 0;
    while (offset < bytes.size()) {
        const auto count = static_cast<uInt>(std::min<std::size_t>(
            bytes.size() - offset, std::numeric_limits<uInt>::max()));
        crc = crc32(crc, bytes.data() + offset, count);
        offset += count;
    }
    return static_cast<std::uint32_t>(crc);
}

std::vector<std::uint8_t> inflate_raw(const std::vector<std::uint8_t>& compressed,
                                      std::uint32_t expected_size, std::string_view name) {
    std::vector<std::uint8_t> output(expected_size);
    std::uint8_t empty_output = 0;
    z_stream stream{};
    stream.next_in = const_cast<Bytef*>(compressed.data());
    stream.avail_in = static_cast<uInt>(compressed.size());
    stream.next_out = output.empty() ? &empty_output : output.data();
    stream.avail_out = output.empty() ? 1U : static_cast<uInt>(output.size());
    if (inflateInit2(&stream, -MAX_WBITS) != Z_OK) {
        throw PakError("Could not initialize Deflate for " + std::string(name));
    }
    const int result = inflate(&stream, Z_FINISH);
    const auto total_out = stream.total_out;
    const auto total_in = stream.total_in;
    inflateEnd(&stream);
    if (result != Z_STREAM_END || total_out != expected_size || total_in != compressed.size()) {
        throw PakError("Invalid Deflate stream for " + std::string(name));
    }
    return output;
}

} // namespace

PakArchive::PakArchive(const std::filesystem::path& path) : path_(path) {
    std::ifstream stream(path_, std::ios::binary);
    if (!stream) {
        throw PakError("Could not open archive: " + path_.string());
    }
    stream.seekg(0, std::ios::end);
    const auto end = stream.tellg();
    if (end < 0) {
        throw PakError("Could not determine archive size: " + path_.string());
    }
    file_size_ = static_cast<std::uint64_t>(end);
    if (file_size_ < end_record_size) {
        throw PakError("Archive is too short: " + path_.string());
    }

    const auto tail_size = static_cast<std::size_t>(std::min<std::uint64_t>(
        file_size_, end_record_size + maximum_comment_size));
    const auto tail_offset = file_size_ - tail_size;
    const auto tail = read_at(stream, tail_offset, tail_size, file_size_, "ZIP end record");
    std::size_t end_offset = tail.size();
    for (std::size_t candidate = tail.size() - end_record_size + 1; candidate-- > 0;) {
        if (little_u32(tail.data() + candidate) == end_signature) {
            const auto comment_size = little_u16(tail.data() + candidate + 20);
            if (candidate + end_record_size + comment_size == tail.size()) {
                end_offset = candidate;
                break;
            }
        }
    }
    if (end_offset == tail.size()) {
        throw PakError("ZIP end record was not found: " + path_.string());
    }

    const auto* record = tail.data() + end_offset;
    const auto disk = little_u16(record + 4);
    const auto central_disk = little_u16(record + 6);
    const auto entries_on_disk = little_u16(record + 8);
    const auto entry_count = little_u16(record + 10);
    const auto central_size = little_u32(record + 12);
    const auto central_offset = little_u32(record + 16);
    if (disk != 0 || central_disk != 0 || entries_on_disk != entry_count) {
        throw PakError("Multi-disk ZIP archives are not supported");
    }
    if (entry_count == 0xffffU || central_size == 0xffffffffU || central_offset == 0xffffffffU) {
        throw PakError("ZIP64 archives are not supported");
    }
    const auto absolute_end_offset = tail_offset + end_offset;
    if (checked_add(central_offset, central_size, "ZIP central directory") > absolute_end_offset) {
        throw PakError("ZIP central directory is outside the archive");
    }
    const auto central = read_at(stream, central_offset, central_size, file_size_,
                                 "ZIP central directory");

    entries_.reserve(entry_count);
    index_.reserve(entry_count);
    normalized_index_.reserve(entry_count);
    std::size_t offset = 0;
    for (std::uint32_t number = 0; number < entry_count; ++number) {
        if (central.size() - offset < 46 || little_u32(central.data() + offset) != central_signature) {
            throw PakError("Invalid ZIP central directory entry " + std::to_string(number));
        }
        const auto* header = central.data() + offset;
        const auto name_size = little_u16(header + 28);
        const auto extra_size = little_u16(header + 30);
        const auto comment_size = little_u16(header + 32);
        const auto record_size = checked_add(46, checked_add(name_size, checked_add(extra_size,
            comment_size, "ZIP entry"), "ZIP entry"), "ZIP entry");
        if (record_size > central.size() - offset) {
            throw PakError("Truncated ZIP central directory entry " + std::to_string(number));
        }
        Entry entry;
        entry.flags = little_u16(header + 8);
        entry.compression_method = little_u16(header + 10);
        entry.crc32 = little_u32(header + 16);
        entry.compressed_size = little_u32(header + 20);
        entry.uncompressed_size = little_u32(header + 24);
        entry.local_header_offset = little_u32(header + 42);
        entry.name.assign(reinterpret_cast<const char*>(header + 46), name_size);
        if ((entry.flags & 1U) != 0) {
            throw PakError("Encrypted ZIP entries are not supported: " + entry.name);
        }
        if (entry.name.find('\0') != std::string::npos) {
            throw PakError("ZIP entry name contains a NUL byte");
        }
        const auto entry_index = entries_.size();
        const auto inserted = index_.emplace(entry.name, entry_index).second;
        if (!inserted) {
            throw PakError("Duplicate ZIP entry: " + entry.name);
        }
        if (!normalized_index_.emplace(normalize_entry_name(entry.name), entry_index).second) {
            throw PakError("ZIP entries collide after path normalization: " + entry.name);
        }
        entries_.push_back(std::move(entry));
        offset += static_cast<std::size_t>(record_size);
    }
    if (offset != central.size()) {
        throw PakError("Unexpected data after ZIP central directory entries");
    }
}

const PakArchive::Entry* PakArchive::find(std::string_view name) const noexcept {
    const auto found = index_.find(std::string(name));
    return found == index_.end() ? nullptr : &entries_[found->second];
}

const PakArchive::Entry* PakArchive::find_normalized(std::string_view name) const noexcept {
    const auto found = normalized_index_.find(normalize_entry_name(name));
    return found == normalized_index_.end() ? nullptr : &entries_[found->second];
}

std::vector<std::uint8_t> PakArchive::read(std::string_view name) const {
    const auto* entry = find(name);
    if (entry == nullptr) {
        throw PakError("ZIP entry was not found: " + std::string(name));
    }
    return read(*entry);
}

std::vector<std::uint8_t> PakArchive::read_normalized(std::string_view name) const {
    const auto* entry = find_normalized(name);
    if (entry == nullptr) {
        throw PakError("ZIP entry was not found after path normalization: " + std::string(name));
    }
    return read(*entry);
}

std::vector<std::uint8_t> PakArchive::read(const Entry& entry) const {
    if (entry.is_directory()) {
        return {};
    }
    if (entry.compression_method != 0 && entry.compression_method != 8) {
        throw PakError("Unsupported ZIP compression method for " + entry.name);
    }
    std::ifstream stream(path_, std::ios::binary);
    if (!stream) {
        throw PakError("Could not reopen archive: " + path_.string());
    }
    const auto header = read_at(stream, entry.local_header_offset, 30, file_size_,
                                "ZIP local header for " + entry.name);
    if (little_u32(header.data()) != local_signature) {
        throw PakError("Invalid ZIP local header for " + entry.name);
    }
    if (little_u16(header.data() + 8) != entry.compression_method) {
        throw PakError("ZIP compression method mismatch for " + entry.name);
    }
    const auto name_size = little_u16(header.data() + 26);
    const auto extra_size = little_u16(header.data() + 28);
    auto data_offset = checked_add(entry.local_header_offset, 30, "ZIP file data");
    data_offset = checked_add(data_offset, name_size, "ZIP file data");
    data_offset = checked_add(data_offset, extra_size, "ZIP file data");
    const auto compressed = read_at(stream, data_offset, entry.compressed_size, file_size_,
                                    "ZIP file data for " + entry.name);

    std::vector<std::uint8_t> output;
    if (entry.compression_method == 0) {
        if (entry.compressed_size != entry.uncompressed_size) {
            throw PakError("Stored ZIP size mismatch for " + entry.name);
        }
        output = compressed;
    } else {
        output = inflate_raw(compressed, entry.uncompressed_size, entry.name);
    }
    if (calculate_crc(output) != entry.crc32) {
        throw PakError("ZIP CRC mismatch for " + entry.name);
    }
    return output;
}

} // namespace torchlight
