// The entry and its interpreter execute normally; only the user callback is synthetic.
#include <climits>
#include <cstring>
#include <string>
#include "AutoTest.h"
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"

TL_ORIGINAL(std::wstring, originalListValue,
            (CDescriptorProp*, CEditorScene*, CEditorBaseObject*, unsigned int),
            "_ZN15CDescriptorProp19getListValueByIndexEP12CEditorSceneP17CEditorBaseObjectj")
extern "C" std::wstring candidateListValue(CDescriptorProp*, CEditorScene*, CEditorBaseObject*, unsigned int)
    __asm__("_ZN15CDescriptorProp19getListValueByIndexEP12CEditorSceneP17CEditorBaseObjectj");

namespace {
struct Case { int flags; unsigned index, variant; };
const Case* input;
autotest::Capture* output;
CEditorScene* expectedScene;
CEditorBaseObject* expectedObject;
unsigned calls;
void number(unsigned value) { output->add(&value, sizeof(value)); }
std::wstring callback(CEditorScene* scene, CEditorBaseObject* object,
                      unsigned int index, void* context)
{
    ++calls;
    number(scene == expectedScene); number(object == expectedObject);
    number(context == input); number(index);
    if (scene != expectedScene || object != expectedObject || context != input || index != input->index)
        output->issue = autotest::Capture::InvalidReport;
    switch (input->variant % 6) {
    case 0: return L"";
    case 1: return L"first";
    case 2: return L"\u0422\u0438\u043f \u03a9";
    case 3: return std::wstring(L"embedded\0tail", 13);
    case 4: return std::wstring(1025, L'Z');
    default: return L"last/value";
    }
}
void side(Case& c, bool ours, autotest::Capture& capture)
{
    input = &c; output = &capture; calls = 0;
    unsigned long long sceneToken[2] = {1, 2}, objectToken[2] = {3, 4};
    expectedScene = c.variant & 1 ? reinterpret_cast<CEditorScene*>(sceneToken) : NULL;
    expectedObject = c.variant & 2 ? reinterpret_cast<CEditorBaseObject*>(objectToken) : NULL;
    CDescriptorPropertyInterpreter interpreter(NULL, &callback, &c);
    CDescriptorProp property(L"category", L"name", L"description", NULL, NULL,
                             static_cast<EVARIABLE_TYPES>(c.variant % VARIABLE_TYPE_COUNT), c.flags);
    property.m_pInterpreter = &interpreter;
    std::wstring (*fn)(CDescriptorProp*, CEditorScene*, CEditorBaseObject*, unsigned int) =
        ours ? candidateListValue : originalListValue;
    if (!autotest::beginInvocation(capture, fn)) { property.m_pInterpreter = NULL; return; }
    std::wstring result = fn(&property, expectedScene, expectedObject, c.index);
    capture.callCompleted = 1;
    number(result.size()); capture.add(result.c_str(), result.size() * sizeof(wchar_t));
    number(calls); number(property.m_iFlags); number(property.m_eType);
    number(property.m_pInterpreter == &interpreter);
    if (calls != ((c.flags & CDescriptorProp::FLAG_HAS_LIST_OF_VALUES) ? 1u : 0u) ||
        property.m_iFlags != c.flags || property.m_eType != static_cast<EVARIABLE_TYPES>(c.variant % VARIABLE_TYPE_COUNT) ||
        property.m_pInterpreter != &interpreter || property.m_sName != L"name" ||
        property.m_sDescription != L"description" || property.m_sCategory != L"category")
        capture.issue = autotest::Capture::InvalidReport;
    if (!(c.flags & CDescriptorProp::FLAG_HAS_LIST_OF_VALUES) && !result.empty())
        capture.issue = autotest::Capture::InvalidReport;
    property.m_pInterpreter = NULL;
}
void original(void* data, autotest::Capture& capture) { side(*static_cast<Case*>(data), false, capture); }
void recovered(void* data, autotest::Capture& capture) { side(*static_cast<Case*>(data), true, capture); }
}
TL_TEST(property_list_value_differential)
{
    const int flags[] = {0, 1, 4, 5, 0x100, 0x104, INT_MIN, -1};
    const unsigned indices[] = {0, 1, 9, 31, 0x80000000u, UINT_MAX};
    autotest::Coverage coverage("property_list_value_differential", (uint64_t)(uintptr_t)&originalListValue);
    for (unsigned f = 0; f < 8; ++f) for (unsigned i = 0; i < 6; ++i) {
        Case c = {flags[f], indices[i], i};
        autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host); return 0;
}
