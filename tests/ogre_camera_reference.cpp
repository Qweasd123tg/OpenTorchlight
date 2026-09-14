// Test-only ABI bridge to the SHA-pinned, installed OGRE 1.6.5 library.
// Built with the old libstdc++ string ABI. No headers, game startup, plugins,
// render-system initialization, windows, or GPU calls from the original.
#include <array>
#include <cstddef>
#include <cstring>
#include <dlfcn.h>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

namespace {
void* library = nullptr;
alignas(std::max_align_t) std::array<std::byte, 0x2000> root{};
alignas(std::max_align_t) std::array<std::byte, 0x1000> buffers{};
// Constructor writes through 0x59f in this exact build (validated in Python).
alignas(std::max_align_t) std::array<std::byte, 0x5a0> camera{};
std::array<void*, 0x250 / 8> renderer_vtable{};
void* renderer = nullptr;
bool root_ready = false;
bool buffers_ready = false;
bool camera_ready = false;
using NodeStorage = std::array<std::byte, 0x1000>;
std::vector<std::unique_ptr<NodeStorage>> nodes;

template <typename T> T symbol(const char* name) {
    const auto address = dlsym(library, name);
    if (!address) throw std::runtime_error(std::string("Missing OGRE symbol: ") + name);
    return reinterpret_cast<T>(address);
}

// RenderSystem_GL.so:0x272f0 is exactly a 64-byte copy for both values of bool.
// Frustum needs this sole render-system method to build its CPU projection.
void convert_projection(void*, const float* source, float* destination, bool) {
    std::memcpy(destination, source, 16 * sizeof(float));
}
} // namespace

extern "C" void reference_close() {
    for (const auto& node : nodes)
        symbol<void (*)(void*)>("_ZN4Ogre4Node17removeAllChildrenEv")(node->data());
    for (const auto& node : nodes)
        symbol<void (*)(void*)>("_ZN4Ogre4NodeD1Ev")(node->data());
    nodes.clear();
    if (camera_ready) symbol<void (*)(void*)>("_ZN4Ogre6CameraD1Ev")(camera.data());
    camera_ready = false;
    if (buffers_ready)
        symbol<void (*)(void*)>("_ZN4Ogre28DefaultHardwareBufferManagerD1Ev")(buffers.data());
    buffers_ready = false;
    if (root_ready) {
        // Root must not attempt to shut down the fixture's renderer adapter.
        std::memset(root.data() + 0x18, 0, sizeof(void*));
        symbol<void (*)(void*)>("_ZN4Ogre4RootD1Ev")(root.data());
    }
    root_ready = false;
    if (library) dlclose(library);
    library = nullptr;
}

extern "C" bool reference_open(const char* path, const char* log_path) {
    try {
        if (library) return false;
        library = dlopen(path, RTLD_NOW | RTLD_LOCAL);
        if (!library) return false;
        symbol<void (*)(void*, const std::string&, const std::string&, const std::string&)>(
            "_ZN4Ogre4RootC1ERKSsS2_S2_")(root.data(), "", "", log_path);
        root_ready = true;
        renderer_vtable[0x248 / 8] = reinterpret_cast<void*>(&convert_projection);
        renderer = renderer_vtable.data();
        void* renderer_object = &renderer;
        // Root::getRenderSystem(): mov 0x18(%rdi),%rax; ret.
        std::memcpy(root.data() + 0x18, &renderer_object, sizeof(void*));
        symbol<void (*)(void*)>("_ZN4Ogre28DefaultHardwareBufferManagerC1Ev")(buffers.data());
        buffers_ready = true;
        symbol<void (*)(void*, const std::string&, void*)>(
            "_ZN4Ogre6CameraC1ERKSsPNS_12SceneManagerE")(camera.data(), "CameraReference", nullptr);
        camera_ready = true;
        return true;
    } catch (...) {
        reference_close();
        return false;
    }
}

extern "C" bool reference_camera(const float* position, const float* target,
    float aspect, float fov_radians, float near_clip, float far_clip,
    float* view, float* projection) {
    try {
        if (!camera_ready) return false;
        symbol<void (*)(void*, const float*)>("_ZN4Ogre6Camera11setPositionERKNS_7Vector3E")(
            camera.data(), position);
        symbol<void (*)(void*, const float*)>("_ZN4Ogre6Camera6lookAtERKNS_7Vector3E")(
            camera.data(), target);
        symbol<void (*)(void*, float)>("_ZN4Ogre7Frustum14setAspectRatioEf")(camera.data(), aspect);
        symbol<void (*)(void*, const float*)>("_ZN4Ogre7Frustum7setFOVyERKNS_6RadianE")(
            camera.data(), &fov_radians);
        symbol<void (*)(void*, float)>("_ZN4Ogre7Frustum19setNearClipDistanceEf")(
            camera.data(), near_clip);
        symbol<void (*)(void*, float)>("_ZN4Ogre7Frustum18setFarClipDistanceEf")(
            camera.data(), far_clip);
        const auto* v = symbol<const float* (*)(void*)>(
            "_ZNK4Ogre6Camera13getViewMatrixEv")(camera.data());
        const auto* p = symbol<const float* (*)(void*)>(
            "_ZNK4Ogre7Frustum19getProjectionMatrixEv")(camera.data());
        std::memcpy(view, v, 16 * sizeof(float));
        std::memcpy(projection, p, 16 * sizeof(float));
        return true;
    } catch (...) { return false; }
}

extern "C" bool reference_ground(float viewport_x, float viewport_y,
                                  float height, float* output) {
    try {
        // Ray returns via the SysV hidden sret pointer; layout is origin + direction.
        std::array<float, 6> ray{};
        symbol<void (*)(float*, void*, float, float)>(
            "_ZNK4Ogre6Camera22getCameraToViewportRayEff")(
                ray.data(), camera.data(), viewport_x, viewport_y);
        if (ray[4] == 0) return false;
        const float distance = (height - ray[1]) / ray[4];
        for (unsigned i = 0; i < 3; ++i) output[i] = ray[i] + ray[i + 3] * distance;
        return distance >= 0;
    } catch (...) { return false; }
}

extern "C" bool reference_rotation(const float* basis, float* rotation) {
    try {
        std::array<float, 4> quaternion{};
        symbol<void (*)(float*, const float*)>("_ZN4Ogre10Quaternion18FromRotationMatrixERKNS_7Matrix3E")(
            quaternion.data(), basis);
        symbol<float (*)(float*)>("_ZN4Ogre10Quaternion9normaliseEv")(quaternion.data());
        symbol<void (*)(const float*, float*)>("_ZNK4Ogre10Quaternion16ToRotationMatrixERNS_7Matrix3E")(
            quaternion.data(), rotation);
        return true;
    } catch (...) { return false; }
}

extern "C" void* reference_node(void* parent, const float* position,
                                const float* orientation, const float* scale,
                                float* world_matrix) {
    try {
        auto storage = std::make_unique<NodeStorage>();
        void* node = storage->data();
        symbol<void (*)(void*, const std::string&)>("_ZN4Ogre4NodeC1ERKSs")(
            node, "ReferenceNode" + std::to_string(nodes.size()));
        nodes.push_back(std::move(storage));
        symbol<void (*)(void*, const float*)>("_ZN4Ogre4Node11setPositionERKNS_7Vector3E")(
            node, position);
        symbol<void (*)(void*, const float*)>("_ZN4Ogre4Node8setScaleERKNS_7Vector3E")(node, scale);
        std::array<float, 4> quaternion{};
        symbol<void (*)(float*, const float*)>("_ZN4Ogre10Quaternion18FromRotationMatrixERKNS_7Matrix3E")(
            quaternion.data(), orientation);
        symbol<void (*)(void*, const float*)>("_ZN4Ogre4Node14setOrientationERKNS_10QuaternionE")(
            node, quaternion.data());
        if (parent) symbol<void (*)(void*, void*)>("_ZN4Ogre4Node8addChildEPS0_")(parent, node);
        const float* matrix = symbol<const float* (*)(void*)>(
            "_ZNK4Ogre4Node17_getFullTransformEv")(node);
        std::memcpy(world_matrix, matrix, 16 * sizeof(float));
        return node;
    } catch (...) { return nullptr; }
}
