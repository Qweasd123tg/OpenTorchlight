#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"

class CEditorScene;
class CEditorBaseObject;

TL_ORIGINAL(std::wstring, oldCameraGroup,
    (CEditorScene*, CEditorBaseObject*, unsigned int, void*),
    "_ZN27CCameraControllerDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
TL_ORIGINAL(std::wstring, oldInteractiveGroup,
    (CEditorScene*, CEditorBaseObject*, unsigned int, void*),
    "_ZN22CInteractiveDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring newCameraGroup(CEditorScene*, CEditorBaseObject*, unsigned int, void*)
    __asm__("_ZN27CCameraControllerDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" std::wstring newInteractiveGroup(CEditorScene*, CEditorBaseObject*, unsigned int, void*)
    __asm__("_ZN22CInteractiveDescriptor18GetGroupStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");

namespace {
typedef std::wstring (*GroupFunction)(CEditorScene*, CEditorBaseObject*, unsigned int, void*);
struct Case {
    unsigned int kind, index, pointers;
};

void side(void* context, autotest::Capture& out, bool ours)
{
    const Case& input = *static_cast<Case*>(context);
    uint64_t scene[8], object[8], user[4];
    std::memset(scene, 0x5a, sizeof(scene));
    std::memset(object, 0xa5, sizeof(object));
    std::memset(user, 0xc3, sizeof(user));
    // These arguments are unused in the original; sentinels also detect writes.
    CEditorScene* sceneArg = input.pointers ? reinterpret_cast<CEditorScene*>(scene) : 0;
    CEditorBaseObject* objectArg = input.pointers == 1
        ? reinterpret_cast<CEditorBaseObject*>(object) : 0;
    void* userArg = input.pointers == 2 ? user : 0;
    GroupFunction function = input.kind
        ? (ours ? &newInteractiveGroup : &oldInteractiveGroup)
        : (ours ? &newCameraGroup : &oldCameraGroup);
    autotest::invoke<GroupFunction, CEditorScene*, CEditorBaseObject*, unsigned int, void*>(
        out, function, sceneArg, objectArg, input.index, userArg);
    out.add(scene, sizeof(scene));
    out.add(object, sizeof(object));
    out.add(user, sizeof(user));
}

void original(void* context, autotest::Capture& out) { side(context, out, false); }
void replacement(void* context, autotest::Capture& out) { side(context, out, true); }

int run(const tlhybrid_host* host, unsigned int kind, const char* name)
{
    const unsigned int indices[] = {0, 1, 2, 3, 17, 0x7fffffffU, 0x80000000U, 0xffffffffU};
    GroupFunction function = kind ? &oldInteractiveGroup : &oldCameraGroup;
    autotest::Coverage coverage(name, reinterpret_cast<uintptr_t>(function));
    for (unsigned int pointers = 0; pointers < 3; ++pointers) {
        for (unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]); ++i) {
            Case input = {kind, indices[i], pointers};
            autotest::Outcome before, after;
            autotest::runChild(original, &input, before);
            autotest::runChild(replacement, &input, after);
            if (coverage.observe(host, before, after)) {
                host->log("    group-name index %u pointers %u exits %d/%d\n",
                          input.index, pointers, before.childStatus, after.childStatus);
                coverage.report(host);
                return 1;
            }
        }
    }
    coverage.report(host);
    return 0;
}
}

TL_TEST(camera_descriptor_group_names)
{
    return run(host, 0, "camera_descriptor_group_names");
}

TL_TEST(interactive_descriptor_group_names)
{
    return run(host, 1, "interactive_descriptor_group_names");
}
