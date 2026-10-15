#include <cstring>
#include <map>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "EditorBaseObject.h"
#include "EditorObjectManager.h"
#include "iSelected.h"
TL_ORIGINAL(void, old_registered, (void*, CEditorBaseObject*), "_ZN20CEditorObjectManager19EditorObjectCreatedEP17CEditorBaseObject")
extern "C" void new_registered(void*, CEditorBaseObject*) __asm__("_ZN20CEditorObjectManager19EditorObjectCreatedEP17CEditorBaseObject");
TL_ORIGINAL(void, old_selected, (void*, CEditorBaseObject*), "_ZN20CEditorObjectManager20EditorObjectSelectedEP17CEditorBaseObject")
extern "C" void new_selected(void*, CEditorBaseObject*) __asm__("_ZN20CEditorObjectManager20EditorObjectSelectedEP17CEditorBaseObject");
TL_FUNCTION(highlight, "_ZN20CEditorObjectManager15highlightObjectEP17CEditorBaseObject")
namespace {
struct Case {unsigned operation, seed;};
autotest::Capture* output;
CEditorBaseObject* objects[4];
CEditorObjectManager* manager;
unsigned mode;
void number(unsigned n) {output->add(&n, sizeof(n));}
unsigned identity(CEditorBaseObject* object)
{
    if (!object) return 0;
    for (unsigned i = 0; i < 4; ++i) if (object == objects[i]) return i + 1;
    output->issue = autotest::Capture::InvalidReport; return ~0u;
}
void callback(unsigned event, CEditorBaseObject* object)
{
    number(event); number(identity(object));
    TArrayList<CEditorBaseObject*>* list = manager->getSelectedObjects();
    number(list->size());
    if (mode == event) {list->clear(); list->add(objects[3]);}
}
class SelectedObject : public CEditorBaseObject, public iSelected
{
public:
    virtual void editorSelectionChanged(bool selected)
    {
        number(selected); callback(1, this);
    }
};
void highlighted(CEditorObjectManager* received, CEditorBaseObject* object)
{
    if (received != manager) output->issue = autotest::Capture::InvalidReport;
    callback(2, object);
}
void recordList(TArrayList<CEditorBaseObject*>* list)
{
    unsigned capacity, growBy;
    std::memcpy(&capacity, reinterpret_cast<char*>(list) + 12, 4);
    std::memcpy(&growBy, reinterpret_cast<char*>(list) + 16, 4);
    number(list->size()); number(capacity); number(growBy);
    for (unsigned i = 0; i < list->size(); ++i) number(identity((*list)[i]));
}
void side(void* p, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(p); output = &out; mode = (c.seed / 8) % 3;
    // Private manager member offsets are the original target ASM: map+0x10,
    // selected+0x40, created+0x58, control+0x70, changed flags+0x78/0x79.
    uint64_t storage[16]; std::memset(storage, 0, sizeof(storage));
    manager = reinterpret_cast<CEditorObjectManager*>(storage);
    CEditorObjectManager::ObjectMap* map = new (reinterpret_cast<char*>(storage) + 0x10) CEditorObjectManager::ObjectMap;
    TArrayList<CEditorBaseObject*>* selected = new (reinterpret_cast<char*>(storage) + 0x40) TArrayList<CEditorBaseObject*>(2);
    TArrayList<CEditorBaseObject*>* created = new (reinterpret_cast<char*>(storage) + 0x58) TArrayList<CEditorBaseObject*>(2);
    CEditorBaseObject base1, base2;
    SelectedObject selected1, selected2;
    objects[0] = &base1; objects[1] = &selected1; objects[2] = &base2; objects[3] = &selected2;
    const long long guids[] = {0, -1, 0x100000001LL, -0x100000001LL};
    for (unsigned i = 0; i < 4; ++i) objects[i]->setGuid(guids[(i + c.seed / 4) % 4]);
    unsigned layout = c.seed % 8;
    if (layout == 1) selected->add(objects[3]);
    if (layout == 2) selected->add(objects[c.seed % 2]);
    if (layout >= 3 && layout <= 5) {
        selected->add(objects[2]); selected->add(objects[c.seed % 2]);
        if (layout >= 4) selected->add(objects[3]);
        if (layout == 5) selected->add(objects[c.seed % 2]);
    }
    if (layout == 6) {selected->add(objects[3]); unsigned zero = 0; std::memcpy(reinterpret_cast<char*>(selected) + 8, &zero, 4);}
    if (layout == 7) {selected->add(objects[2]); selected->add(objects[3]);}
    if (c.seed & 16) {created->add(objects[3]); created->add(objects[2]);}
    if (c.seed & 32) {(*map)[objects[0]->getGuid()] = objects[2]; (*map)[objects[3]->getGuid()] = objects[3];}
    reinterpret_cast<unsigned char*>(storage)[0x78] = bool(c.seed & 64);
    reinterpret_cast<unsigned char*>(storage)[0x79] = bool(c.seed & 128);
    CEditorBaseObject* target = c.seed % 10 == 9 ? 0 : objects[c.seed % 2];
    detour::Set patches; TL_REDIRECT(patches, highlight, &highlighted);
    if (patches.failed()) {out.issue = autotest::Capture::InvalidReport; return;}
    typedef void (*Fn)(void*, CEditorBaseObject*);
    Fn fn = c.operation ? (ours ? new_registered : old_registered) : (ours ? new_selected : old_selected);
    if (!autotest::beginInvocation(out, fn)) return;
    fn(storage, target); out.callCompleted = 1;
    recordList(selected); recordList(created);
    number(map->size());
    for (CEditorObjectManager::ObjectMap::const_iterator it = map->begin(); it != map->end(); ++it) {
        out.add(&it->first, sizeof(it->first)); number(identity(it->second));
    }
    out.add(reinterpret_cast<unsigned char*>(storage) + 0x78, 2);
    created->~TArrayList<CEditorBaseObject*>(); selected->~TArrayList<CEditorBaseObject*>();
    typedef CEditorObjectManager::ObjectMap Map; map->~Map();
}
void original(void* p, autotest::Capture& out) {side(p, out, false);}
void recovered(void* p, autotest::Capture& out) {side(p, out, true);}
int run(const tlhybrid_host* host, unsigned operation, const char* name, uintptr_t address)
{
    autotest::Coverage coverage(name, address);
    for (unsigned seed = 0; seed < 160; ++seed) {
        Case c = {operation, seed}; autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    editor registration op %u seed %u statuses %d/%d\n", operation, seed, a.status, b.status);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(editor_object_registered) {return run(host, 1, "editor_object_registered", reinterpret_cast<uintptr_t>(&old_registered));}
TL_TEST(editor_object_selected) {return run(host, 0, "editor_object_selected", reinterpret_cast<uintptr_t>(&old_selected));}
