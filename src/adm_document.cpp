#include "torchlight/adm_document.hpp"

#include "torchlight/pak_archive.hpp"

#include <cstring>
#include <limits>
#include <string_view>
#include <unordered_map>

namespace torchlight {
namespace {

constexpr std::uint32_t torchlight_one_version = 1;
constexpr std::uint32_t maximum_dictionary_entries = 1U << 20U;
constexpr std::uint32_t maximum_group_items = 1U << 24U;
constexpr std::size_t maximum_group_depth = 1024;

class Reader {
public:
    explicit Reader(const std::vector<std::uint8_t>& bytes) : bytes_(bytes) {}

    std::uint32_t read_u32(std::string_view context) {
        require(4, context);
        const auto value = static_cast<std::uint32_t>(bytes_[offset_]) |
                           (static_cast<std::uint32_t>(bytes_[offset_ + 1]) << 8U) |
                           (static_cast<std::uint32_t>(bytes_[offset_ + 2]) << 16U) |
                           (static_cast<std::uint32_t>(bytes_[offset_ + 3]) << 24U);
        offset_ += 4;
        return value;
    }

    std::uint64_t read_u64(std::string_view context) {
        const auto low = read_u32(context);
        const auto high = read_u32(context);
        return static_cast<std::uint64_t>(low) | (static_cast<std::uint64_t>(high) << 32U);
    }

    std::u16string read_utf16(std::uint32_t length) {
        if (length > (std::numeric_limits<std::size_t>::max() / 2U)) {
            throw PakError("ADM UTF-16 string length overflow");
        }
        const auto byte_count = static_cast<std::size_t>(length) * 2U;
        require(byte_count, "ADM UTF-16 string");
        std::u16string text;
        text.reserve(length);
        for (std::uint32_t index = 0; index < length; ++index) {
            const auto low = static_cast<std::uint16_t>(bytes_[offset_]);
            const auto high = static_cast<std::uint16_t>(bytes_[offset_ + 1]);
            text.push_back(static_cast<char16_t>(low | (high << 8U)));
            offset_ += 2;
        }
        return text;
    }

    [[nodiscard]] std::size_t offset() const noexcept { return offset_; }
    [[nodiscard]] std::size_t size() const noexcept { return bytes_.size(); }

private:
    void require(std::size_t count, std::string_view context) const {
        if (count > bytes_.size() - offset_) {
            throw PakError("Truncated " + std::string(context) + " at byte " +
                           std::to_string(offset_));
        }
    }

    const std::vector<std::uint8_t>& bytes_;
    std::size_t offset_ = 0;
};

template <typename To, typename From>
To copy_bits(From value) noexcept {
    static_assert(sizeof(To) == sizeof(From));
    To result;
    std::memcpy(&result, &value, sizeof(result));
    return result;
}

class Parser {
public:
    explicit Parser(const std::vector<std::uint8_t>& bytes) : reader_(bytes) {}

    AdmDocument parse() {
        AdmDocument document;
        document.version = reader_.read_u32("ADM version");
        if (document.version != torchlight_one_version) {
            throw PakError("Unsupported ADM version: " + std::to_string(document.version));
        }
        const auto dictionary_count = read_count("ADM dictionary", maximum_dictionary_entries);
        document.dictionary.reserve(dictionary_count);
        dictionary_.reserve(dictionary_count);
        for (std::uint32_t index = 0; index < dictionary_count; ++index) {
            AdmDictionaryEntry entry;
            entry.id = reader_.read_u32("ADM dictionary id");
            const auto length = reader_.read_u32("ADM dictionary string length");
            entry.text = reader_.read_utf16(length);
            if (!dictionary_.emplace(entry.id, entry.text).second) {
                throw PakError("Duplicate ADM dictionary id: " + std::to_string(entry.id));
            }
            document.dictionary.push_back(std::move(entry));
        }
        document.root = parse_group(0);
        if (reader_.offset() != reader_.size()) {
            throw PakError("Trailing bytes after ADM root group at byte " +
                           std::to_string(reader_.offset()));
        }
        return document;
    }

private:
    std::uint32_t read_count(std::string_view context, std::uint32_t maximum) {
        const auto count = reader_.read_u32(context);
        if (count > maximum) {
            throw PakError(std::string(context) + " count is too large: " + std::to_string(count));
        }
        return count;
    }

    const std::u16string& dictionary_text(std::uint32_t id, std::string_view context) const {
        const auto found = dictionary_.find(id);
        if (found == dictionary_.end()) {
            throw PakError(std::string(context) + " references unknown ADM dictionary id " +
                           std::to_string(id));
        }
        return found->second;
    }

    AdmProperty parse_property() {
        AdmProperty property;
        property.name_id = reader_.read_u32("ADM property name");
        property.name = dictionary_text(property.name_id, "ADM property name");
        const auto raw_type = reader_.read_u32("ADM property type");
        if (raw_type < static_cast<std::uint32_t>(AdmValueType::integer) ||
            raw_type > static_cast<std::uint32_t>(AdmValueType::note)) {
            throw PakError("Unknown ADM property type: " + std::to_string(raw_type));
        }
        property.type = static_cast<AdmValueType>(raw_type);
        switch (property.type) {
        case AdmValueType::integer:
            property.value = copy_bits<std::int32_t>(reader_.read_u32("ADM integer"));
            break;
        case AdmValueType::floating:
            property.value = copy_bits<float>(reader_.read_u32("ADM float"));
            break;
        case AdmValueType::double_precision:
            property.value = copy_bits<double>(reader_.read_u64("ADM double"));
            break;
        case AdmValueType::unsigned_integer:
            property.value = reader_.read_u32("ADM unsigned integer");
            break;
        case AdmValueType::string:
        case AdmValueType::translation:
        case AdmValueType::note: {
            const auto id = reader_.read_u32("ADM text value");
            property.value = dictionary_text(id, "ADM text value");
            break;
        }
        case AdmValueType::boolean:
            property.value = reader_.read_u32("ADM boolean") != 0;
            break;
        case AdmValueType::integer64:
            property.value = copy_bits<std::int64_t>(reader_.read_u64("ADM integer64"));
            break;
        }
        return property;
    }

    AdmGroup parse_group(std::size_t depth) {
        if (depth >= maximum_group_depth) {
            throw PakError("ADM group nesting is too deep");
        }
        AdmGroup group;
        group.name_id = reader_.read_u32("ADM group name");
        group.name = dictionary_text(group.name_id, "ADM group name");
        const auto property_count = read_count("ADM property", maximum_group_items);
        group.properties.reserve(property_count);
        for (std::uint32_t index = 0; index < property_count; ++index) {
            group.properties.push_back(parse_property());
        }
        const auto group_count = read_count("ADM subgroup", maximum_group_items);
        group.groups.reserve(group_count);
        for (std::uint32_t index = 0; index < group_count; ++index) {
            group.groups.push_back(parse_group(depth + 1));
        }
        return group;
    }

    Reader reader_;
    std::unordered_map<std::uint32_t, std::u16string> dictionary_;
};

} // namespace

const AdmProperty* AdmGroup::find_property(const std::u16string& property_name) const noexcept {
    for (const auto& property : properties) {
        if (property.name == property_name) {
            return &property;
        }
    }
    return nullptr;
}

AdmDocument parse_adm(const std::vector<std::uint8_t>& bytes) {
    return Parser(bytes).parse();
}

} // namespace torchlight
