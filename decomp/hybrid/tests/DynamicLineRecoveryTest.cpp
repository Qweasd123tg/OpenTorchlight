#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include "ParticleNativeOwners.h"
#include <OgreSimpleRenderable.h>
#include <OgreVertexIndexData.h>
#include <OgreHardwareBufferManager.h>
#include <OgreMaterialManager.h>
#include <vector>
#include <cstring>
#include <fenv.h>
#define private public
#define protected public
#include "DynamicLine.h"
#undef protected
#undef private

TL_ORIGINAL(void, lineOldCtor, (CDynamicLine*, Ogre::RenderOperation::OperationType), "_ZN12CDynamicLineC1EN4Ogre15RenderOperation13OperationTypeE")
TL_ORIGINAL(void, lineOldFill, (CDynamicLine*), "_ZN12CDynamicLine19fillHardwareBuffersEv")
TL_ORIGINAL(void, lineOldDtor, (CDynamicLine*), "_ZN12CDynamicLineD1Ev")
extern "C" void lineNewFill(CDynamicLine*) __asm__("_ZN12CDynamicLine19fillHardwareBuffersEv");

namespace {
struct Case { unsigned index; bool negative; };
union Storage { long double alignment; char bytes[sizeof(CDynamicLine)]; };
template<class T> void value(autotest::Capture& out, T v) { out.add(&v, sizeof(v)); }

Ogre::Vector3 point(unsigned i, unsigned mode)
{
    Ogre::Vector3 p(float(int(i % 7) - 3) * 1.25f,
                    float(int(i % 11) - 5) * 0.125f,
                    float(int(i % 13) - 6) * -2.0f);
    if (mode == 1) p = Ogre::Vector3(2, -3, 4);
    if (mode == 2) { p.x = -0.0f; p.y = 0.0f; p.z = i % 2 ? -0.0f : 0.0f; }
    if (mode == 3 && i % 4 == 0) p.x = __builtin_nanf("");
    if (mode == 4 && i % 3 == 0) p.z = i % 2 ? __builtin_inff() : -__builtin_inff();
    if (mode == 5) { p.x *= 1e20f; p.y *= 1e-20f; }
    return p;
}

void capture(autotest::Capture& out, CDynamicLine* line)
{
    value(out, line->m_dirty);
    value(out, line->m_vertexCapacity);
    value(out, line->m_indexCapacity);
    value(out, line->m_points.size());
    if (!line->m_points.empty()) out.add(&line->m_points[0], line->m_points.size() * sizeof(Ogre::Vector3));
    const Ogre::AxisAlignedBox& box = line->getBoundingBox();
    value(out, box.isNull()); value(out, box.isInfinite());
    out.add(&box.getMinimum(), sizeof(Ogre::Vector3));
    out.add(&box.getMaximum(), sizeof(Ogre::Vector3));
    Ogre::RenderOperation op;
    line->getRenderOperation(op);
    value(out, op.operationType); value(out, op.useIndexes); value(out, op.indexData == NULL);
    value(out, op.vertexData->vertexCount); value(out, op.vertexData->vertexStart);
    Ogre::VertexDeclaration* decl = op.vertexData->vertexDeclaration;
    value(out, decl->getElementCount());
    for (unsigned i = 0; i < decl->getElementCount(); ++i) {
        const Ogre::VertexElement* element = decl->getElement(i);
        value(out, element->getSource()); value(out, element->getOffset());
        value(out, element->getType()); value(out, element->getSemantic()); value(out, element->getIndex());
    }
    Ogre::HardwareVertexBufferSharedPtr buffer = op.vertexData->vertexBufferBinding->getBuffer(0);
    value(out, buffer->getNumVertices()); value(out, buffer->getVertexSize());
    value(out, buffer->getSizeInBytes()); value(out, buffer->getUsage()); value(out, buffer->isLocked());
    if (op.vertexData->vertexCount != line->m_points.size() ||
        op.vertexData->vertexCount > buffer->getNumVertices() || buffer->getVertexSize() != 12) {
        out.issue = autotest::Capture::InvalidReport;
        return;
    }
    const void* bytes = buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
    out.add(bytes, op.vertexData->vertexCount * buffer->getVertexSize());
    buffer->unlock();
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    Storage storage;
    std::memset(storage.bytes, 0x5a, sizeof(storage.bytes));
    CDynamicLine* line = reinterpret_cast<CDynamicLine*>(storage.bytes);
    const Ogre::RenderOperation::OperationType types[] = {
        Ogre::RenderOperation::OT_LINE_STRIP, Ogre::RenderOperation::OT_LINE_LIST,
        Ogre::RenderOperation::OT_POINT_LIST
    };
    lineOldCtor(line, types[c.index % 3]);
    const unsigned counts[] = {0, 1, 2, 3, 7, 8, 9, 15, 16, 17, 33, 65};
    const unsigned previous[] = {0, 1, 4, 17, 80, 0, 8, 65};
    unsigned oldCount = previous[c.index / 12];
    if (oldCount) {
        for (unsigned i = 0; i < oldCount; ++i) line->addPoint(point(i, 0));
        lineOldFill(line);
        line->clear();
    }
    for (unsigned i = 0; i < counts[c.index % 12]; ++i)
        line->addPoint(point(i, (c.index / 12 + c.index) % 6));
    Ogre::AxisAlignedBox box;
    box.setInfinite();
    line->setBoundingBox(box);
    line->m_dirty = c.index % 2 != 0;
    typedef void (*Function)(CDynamicLine*);
    Function function = ours ? lineNewFill : lineOldFill;
    feclearexcept(FE_ALL_EXCEPT);
    if (!autotest::beginInvocation(out, function)) return;
    function(line);
    out.callCompleted = 1;
    value(out, fetestexcept(FE_ALL_EXCEPT));
    if (ours && c.negative) line->m_dirty = true;
    capture(out, line);
    lineOldDtor(line);
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }

int worker(const tlhybrid_host* host)
{
    if (!particleNativeOwners(0).resources) return 1;
    Ogre::MaterialManager& materials = Ogre::MaterialManager::getSingleton();
    if (!materials.resourceExists("FishingLine")) {
        Ogre::MaterialPtr material = materials.create("FishingLine", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        material->removeAllTechniques();
    }
    autotest::Coverage coverage("dynamic_line_fill_recovery", 0x86b500);
    for (unsigned i = 0; i < 96; ++i) {
        Case c = {i, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    line seed%u status%d/%d issue%u/%u bytes%lu/%lu\n", i,
                a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    Case c = {41, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    line negative control detected%u\n", detected ? 1u : 0u);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) ||
        !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}

TL_TEST(dynamic_line_fill_recovery) { return systems_fixture::isolated(worker, host); }
