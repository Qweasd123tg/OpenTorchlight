#include "AutoTest.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsNativeGame.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/MenuModelGpuBoundary.h"
#include "FileSystem.h"
#include <OgreTextureUnitState.h>
TL_ORIGINAL(void, materialsOriginal, (CGame*), "_ZN5CGame15createMaterialsEv")
extern "C" void materialsCandidate(CGame*) __asm__("_ZN5CGame15createMaterialsEv");
TL_FUNCTION(materialsFileInfo, "_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
namespace {
autotest::Capture* capture;
unsigned variant, lookups;
void number(unsigned v) { capture->add(&v, 4); }
void real(float v) { capture->add(&v, 4); }
void colour(const Ogre::ColourValue& c) { real(c.r); real(c.g); real(c.b); real(c.a); }
void fileInfo(CFileSystem* self, const std::wstring& path, CFileInfo& out, bool compiled, bool binary, bool mods) {
    number(self == CFileSystem::getSingleton()); capture->addText(path);
    number(compiled); number(binary); number(mods); number(lookups++);
    out.m_sResourceName = variant == 0 ? "" : variant == 1 ? "trail.dds" : variant == 2 ? "dir/\320\277\321\203\321\202\321\214.dds" : std::string(300, 'x') + ".dds";
    out.m_sResourceName += Ogre::StringConverter::toString(lookups);
    out.m_bExists = (variant & 1) != 0;
    out.m_eLocation = variant;
}
void material(const std::string& name) {
    Ogre::MaterialPtr m = Ogre::MaterialManager::getSingleton().getByName(name);
    capture->addText(name); number(!m.isNull());
    if (m.isNull()) { capture->issue = autotest::Capture::InvalidReport; return; }
    number(m->getReceiveShadows()); number(m->getNumTechniques());
    for (unsigned t = 0; t < m->getNumTechniques(); ++t) {
        Ogre::Technique* tech = m->getTechnique(t); number(tech->getNumPasses());
        for (unsigned p = 0; p < tech->getNumPasses(); ++p) {
            Ogre::Pass* pass = tech->getPass(p);
            number(pass->getPolygonMode()); number(pass->getLightingEnabled()); real(pass->getShininess());
            colour(pass->getSelfIllumination()); colour(pass->getAmbient()); colour(pass->getDiffuse()); colour(pass->getSpecular());
            number(pass->getDepthCheckEnabled()); number(pass->getDepthWriteEnabled()); number(pass->getDepthFunction());
            number(pass->getCullingMode()); number(pass->getSourceBlendFactor()); number(pass->getDestBlendFactor()); number(pass->getMaxSimultaneousLights());
            number(pass->getFogOverride()); number(pass->getFogMode()); colour(pass->getFogColour()); real(pass->getFogDensity()); real(pass->getFogStart()); real(pass->getFogEnd());
            number(pass->getNumTextureUnitStates());
            for (unsigned u = 0; u < pass->getNumTextureUnitStates(); ++u) {
                Ogre::TextureUnitState* unit = pass->getTextureUnitState(u);
                capture->addText(unit->getTextureName()); number(unit->getTextureCoordSet()); number(unit->getTextureType()); number(unit->getNumFrames());
            }
        }
    }
}
struct Case { unsigned variant, old, defaults; };
void side(void* raw, autotest::Capture& out, bool ours) {
    Case c = *static_cast<Case*>(raw); variant = c.variant; lookups = 0; capture = &out;
    SystemsNativeGame owner(Ogre::Root::getSingletonPtr(), CMasterResourceManager::getSingleton()->m_pSettings);
    CGame* game = owner.game;
    if (c.old) {
        Ogre::MaterialPtr old = Ogre::MaterialManager::getSingleton().create("old-game-material", "General");
        game->m_particleMaterial = old;
        if (c.old == 2) game->m_behindMaterial = old;
    }
    Ogre::MaterialPtr defaults = Ogre::MaterialManager::getSingleton().getDefaultSettings();
    Ogre::Pass* initial = defaults->getTechnique(0)->getPass(0);
    initial->setDepthCheckEnabled((c.defaults & 1) != 0);
    initial->setSpecular(Ogre::ColourValue(.125f * c.defaults, .25f, .5f, .75f));
    initial->setShininess(float(c.defaults) * 7.5f);
    menugui::ModelGpuBoundary graphics;
    detour::Set input; TL_REDIRECT(input, materialsFileInfo, &fileInfo); if (input.failed()) _exit(64);
    void (*fn)(CGame*) = ours ? materialsCandidate : materialsOriginal;
    if (autotest::beginInvocation(out, fn)) { fn(game); out.callCompleted = 1; }
    input.restore(); number(lookups);
    number(menugui::materialPreparationCalls()); number(menugui::automaticHardwareChecks()); number(menugui::materialLoadCalls()); number(menugui::texturePreparationCalls()); number(menugui::textureLoadCalls());
    number(!game->m_particleMaterial.isNull()); number(!game->m_behindMaterial.isNull());
    if (!game->m_particleMaterial.isNull()) out.addText(game->m_particleMaterial->getName());
    if (!game->m_behindMaterial.isNull()) out.addText(game->m_behindMaterial->getName());
    const char* names[] = { "Wireframe", "WireframeOverlay", "WeaponTrail", "WeaponTrailEvil", "ArrowTrail", "ArrowTrailReflect", "lightBlue", "lightYellow", "lightOrange", "WireframeBlue", "WireframeYellow", "RenderBehind", "Points", "FishingLine" };
    for (unsigned i = 0; i < sizeof(names)/sizeof(names[0]); ++i) material(names[i]);
    const char* shadows[] = { "RenderShadow", "RenderShadowSkinned", "RenderShadowSkinnedThree", "RenderShadowSkinnedTwo", "RenderShadowSkinnedOne" };
    for (unsigned i = 0; i < 64; ++i) for (unsigned j = 0; j < 5; ++j) material(shadows[j] + Ogre::StringConverter::toString(i));
}
void original(void* p, autotest::Capture& out) { side(p, out, false); }
void candidate(void* p, autotest::Capture& out) { side(p, out, true); }
int worker(const tlhybrid_host* host) {
    nativegame::Services services;
    autotest::Stats stats = {0,0,0}; unsigned cases = 0; int failures = 0;
    autotest::Coverage coverage("game_materials_native", reinterpret_cast<uintptr_t>(materialsOriginal));
    for (unsigned variant = 0; variant < 4; ++variant) for (unsigned old = 0; old < 3; ++old) for (unsigned defaults = 0; defaults < 4; ++defaults) {
        Case c = {variant, old, defaults};
        bool ok = autotest::compareCase(original, candidate, &c, stats, host, "game_materials_native", cases++, &coverage);
        TL_CHECK(failures, ok);
    }
    coverage.report(host); return failures + stats.incomplete + (coverage.completed != cases);
}
}
TL_TEST(game_materials_native) { return systems_fixture::isolated(&worker, host); }
