#include "torchlight/ogre_skeleton.hpp"

#include <algorithm>
#include <cstring>
#include <limits>
#include <string>

namespace torchlight {
namespace {

constexpr std::uint16_t kHeader = 0x1000;
constexpr std::uint16_t kBlendMode = 0x1010;
constexpr std::uint16_t kBone = 0x2000;
constexpr std::uint16_t kBoneParent = 0x3000;
constexpr std::uint16_t kAnimation = 0x4000;
constexpr std::uint16_t kAnimationTrack = 0x4100;
constexpr std::uint16_t kAnimationKeyframe = 0x4110;
constexpr std::uint16_t kAnimationLink = 0x5000;
constexpr std::uint32_t kBoneWithoutScaleSize = 36;
constexpr std::uint32_t kBoneWithScaleSize = 48;
constexpr std::uint32_t kTrackHeaderSize = 8;
constexpr std::uint32_t kKeyframeWithoutScaleSize = 38;
constexpr std::uint32_t kKeyframeWithScaleSize = 50;

struct Chunk {
    std::uint16_t id = 0;
    std::uint32_t size = 0;
    std::size_t begin = 0;
    std::size_t end = 0;
};

class Reader {
public:
    explicit Reader(const std::vector<std::uint8_t>& bytes) : bytes_(bytes) {}

    [[nodiscard]] std::size_t position() const noexcept { return position_; }
    [[nodiscard]] std::size_t size() const noexcept { return bytes_.size(); }
    [[nodiscard]] bool can_read(std::size_t count, std::size_t end) const noexcept {
        return end <= bytes_.size() && position_ <= end && count <= end - position_;
    }

    std::uint16_t read_u16(std::size_t end, const char* description) {
        require(2, end, description);
        const auto value = static_cast<std::uint16_t>(bytes_[position_]) |
                           (static_cast<std::uint16_t>(bytes_[position_ + 1]) << 8U);
        position_ += 2;
        return value;
    }

    std::uint32_t read_u32(std::size_t end, const char* description) {
        require(4, end, description);
        const auto value = static_cast<std::uint32_t>(bytes_[position_]) |
                           (static_cast<std::uint32_t>(bytes_[position_ + 1]) << 8U) |
                           (static_cast<std::uint32_t>(bytes_[position_ + 2]) << 16U) |
                           (static_cast<std::uint32_t>(bytes_[position_ + 3]) << 24U);
        position_ += 4;
        return value;
    }

    float read_float(std::size_t end, const char* description) {
        const auto bits = read_u32(end, description);
        float value = 0.0F;
        static_assert(sizeof(value) == sizeof(bits));
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    }

    std::string read_line(std::size_t end, const char* description) {
        const auto begin = position_;
        while (position_ < end && bytes_[position_] != static_cast<std::uint8_t>('\n')) {
            ++position_;
        }
        if (position_ == end) {
            throw OgreSkeletonError(std::string(description) + " has no newline terminator");
        }
        std::string value(bytes_.begin() + static_cast<std::ptrdiff_t>(begin),
                          bytes_.begin() + static_cast<std::ptrdiff_t>(position_));
        ++position_;
        return value;
    }

    Chunk read_chunk(std::size_t container_end, const char* description) {
        const auto begin = position_;
        const auto id = read_u16(container_end, description);
        const auto size = read_u32(container_end, description);
        if (size < 6U || size > container_end - begin) {
            throw OgreSkeletonError(std::string(description) + " has an invalid size");
        }
        return Chunk{id, size, begin, begin + size};
    }

    void seek(std::size_t position) {
        if (position > bytes_.size()) {
            throw OgreSkeletonError("OGRE skeleton seek exceeds the input");
        }
        position_ = position;
    }

private:
    void require(std::size_t count, std::size_t end, const char* description) const {
        if (end > bytes_.size() || position_ > end || count > end - position_) {
            throw OgreSkeletonError(std::string("Truncated ") + description);
        }
    }

    const std::vector<std::uint8_t>& bytes_;
    std::size_t position_ = 0;
};

std::array<float, 3> read_vector3(Reader& reader, std::size_t end,
                                  const char* description) {
    return {reader.read_float(end, description), reader.read_float(end, description),
            reader.read_float(end, description)};
}

std::array<float, 4> read_quaternion(Reader& reader, std::size_t end,
                                     const char* description) {
    return {reader.read_float(end, description), reader.read_float(end, description),
            reader.read_float(end, description), reader.read_float(end, description)};
}

OgreSkeletonTrack parse_track(Reader& reader, const Chunk& chunk) {
    OgreSkeletonTrack track;
    track.bone_handle = reader.read_u16(chunk.end, "animation track bone handle");
    while (reader.can_read(6, chunk.end)) {
        const auto keyframe_chunk = reader.read_chunk(chunk.end, "animation keyframe chunk");
        if (keyframe_chunk.id != kAnimationKeyframe ||
            (keyframe_chunk.size != kKeyframeWithoutScaleSize &&
             keyframe_chunk.size != kKeyframeWithScaleSize)) {
            throw OgreSkeletonError("Unsupported OGRE animation keyframe chunk");
        }
        OgreSkeletonKeyframe keyframe;
        keyframe.time = reader.read_float(keyframe_chunk.end, "keyframe time");
        keyframe.rotation = read_quaternion(reader, keyframe_chunk.end, "keyframe rotation");
        keyframe.translation =
            read_vector3(reader, keyframe_chunk.end, "keyframe translation");
        if (keyframe_chunk.size == kKeyframeWithScaleSize) {
            keyframe.scale = read_vector3(reader, keyframe_chunk.end, "keyframe scale");
        }
        if (reader.position() != keyframe_chunk.end) {
            throw OgreSkeletonError("OGRE keyframe has trailing data");
        }
        track.keyframes.push_back(keyframe);
    }
    if (reader.position() != chunk.end) {
        throw OgreSkeletonError("OGRE animation track has trailing data");
    }
    return track;
}

OgreSkeletonAnimation parse_animation(Reader& reader, const Chunk& chunk) {
    OgreSkeletonAnimation animation;
    animation.name = reader.read_line(chunk.end, "animation name");
    animation.length = reader.read_float(chunk.end, "animation length");
    while (reader.can_read(6, chunk.end)) {
        const auto track_chunk = reader.read_chunk(chunk.end, "animation track chunk");
        if (track_chunk.id != kAnimationTrack || track_chunk.size < kTrackHeaderSize) {
            throw OgreSkeletonError("Unsupported OGRE animation child chunk");
        }
        animation.tracks.push_back(parse_track(reader, track_chunk));
    }
    if (reader.position() != chunk.end) {
        throw OgreSkeletonError("OGRE animation has trailing data");
    }
    return animation;
}

} // namespace

OgreSkeleton parse_ogre_skeleton(const std::vector<std::uint8_t>& bytes) {
    Reader reader(bytes);
    if (reader.read_u16(reader.size(), "OGRE skeleton header") != kHeader) {
        throw OgreSkeletonError("OGRE skeleton has the wrong header");
    }
    OgreSkeleton skeleton;
    skeleton.serializer_version =
        reader.read_line(reader.size(), "OGRE skeleton serializer version");
    if (skeleton.serializer_version != "[Serializer_v1.10]") {
        throw OgreSkeletonError("Unsupported OGRE skeleton serializer version");
    }

    while (reader.can_read(6, reader.size())) {
        const auto begin = reader.position();
        const auto id = reader.read_u16(reader.size(), "OGRE skeleton chunk ID");
        const auto size = reader.read_u32(reader.size(), "OGRE skeleton chunk size");
        if (size < 6U) {
            throw OgreSkeletonError("OGRE skeleton chunk is shorter than its header");
        }
        if (id == kBone) {
            if (size != kBoneWithoutScaleSize && size != kBoneWithScaleSize) {
                throw OgreSkeletonError("Unsupported OGRE bone chunk size");
            }
            OgreSkeletonBone bone;
            bone.name = reader.read_line(reader.size(), "bone name");
            bone.handle = reader.read_u16(reader.size(), "bone handle");
            bone.position = read_vector3(reader, reader.size(), "bone position");
            bone.orientation = read_quaternion(reader, reader.size(), "bone orientation");
            if (size == kBoneWithScaleSize) {
                bone.scale = read_vector3(reader, reader.size(), "bone scale");
            }
            skeleton.bones.push_back(std::move(bone));
            continue;
        }
        if (size > reader.size() - begin) {
            throw OgreSkeletonError("OGRE skeleton chunk exceeds the input");
        }
        const Chunk chunk{id, size, begin, begin + size};
        switch (id) {
        case kBlendMode:
            static_cast<void>(reader.read_u16(chunk.end, "skeleton blend mode"));
            break;
        case kBoneParent: {
            const auto child = reader.read_u16(chunk.end, "child bone handle");
            const auto parent = reader.read_u16(chunk.end, "parent bone handle");
            const auto found = std::find_if(skeleton.bones.begin(), skeleton.bones.end(),
                                            [child](const auto& bone) {
                                                return bone.handle == child;
                                            });
            if (found == skeleton.bones.end()) {
                throw OgreSkeletonError("OGRE parent chunk references an absent child bone");
            }
            found->parent_handle = parent;
            break;
        }
        case kAnimation:
            skeleton.animations.push_back(parse_animation(reader, chunk));
            break;
        case kAnimationLink: {
            OgreSkeletonAnimationLink link;
            link.skeleton_file = reader.read_line(chunk.end, "linked skeleton name");
            link.scale = reader.read_float(chunk.end, "linked skeleton scale");
            skeleton.animation_links.push_back(std::move(link));
            break;
        }
        default:
            throw OgreSkeletonError("Unsupported OGRE skeleton chunk " +
                                    std::to_string(id));
        }
        reader.seek(chunk.end);
    }
    if (reader.position() != reader.size()) {
        throw OgreSkeletonError("OGRE skeleton has trailing data");
    }
    for (const auto& bone : skeleton.bones) {
        if (bone.parent_handle &&
            std::none_of(skeleton.bones.begin(), skeleton.bones.end(),
                         [&bone](const auto& candidate) {
                             return candidate.handle == *bone.parent_handle;
                         })) {
            throw OgreSkeletonError("OGRE parent chunk references an absent parent bone");
        }
    }
    return skeleton;
}

} // namespace torchlight
