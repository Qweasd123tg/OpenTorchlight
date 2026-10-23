#include <Ogre.h>
#include <cstring>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/ParticleMaterialBoundary.h"
#define protected public
#define private public
#include "Layout.h"
#include "Timeline.h"
#include "SoundObject.h"
#include "CameraShake.h"
#include "CameraControl.h"
#include "Particle.h"
#include "ParticleTechWrapper.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
#include <ParticleUniverseSystem.h>
#undef private
#undef protected
#include "tests/ParticleNativeOwners.h"

TL_ORIGINAL(void, layoutControlOld, (CLayout*, CLayout::ELAYOUT_FUNCTION_TYPES, bool), "_ZN7CLayout21callFunctionOnObjectsENS_22ELAYOUT_FUNCTION_TYPESEb")
extern "C" void layoutControlNew(CLayout*, CLayout::ELAYOUT_FUNCTION_TYPES, bool) __asm__("_ZN7CLayout21callFunctionOnObjectsENS_22ELAYOUT_FUNCTION_TYPESEb");
TL_FUNCTION(layoutParticleStart, "_ZN9CParticle5StartEv")
TL_FUNCTION(layoutParticleStop, "_ZN9CParticle4StopEb")
TL_FUNCTION(layoutParticlePause, "_ZN9CParticle5PauseEv")
TL_FUNCTION(layoutParticleResume, "_ZN9CParticle6ResumeEv")
TL_FUNCTION(layoutTimelinePlay, "_ZN9CTimeline4PlayEb")
TL_FUNCTION(layoutTimelineBack, "_ZN9CTimeline14Play_BackwardsEv")
TL_FUNCTION(layoutTimelineStop, "_ZN9CTimeline4StopEv")
TL_FUNCTION(layoutTimelinePause, "_ZN9CTimeline5PauseEv")
TL_FUNCTION(layoutTimelineBegin, "_ZN9CTimeline18Reset_To_BeginningEv")
TL_FUNCTION(layoutTimelineEnd, "_ZN9CTimeline12Reset_To_EndEv")
TL_FUNCTION(layoutTimelineEnabled, "_ZN9CTimeline10SetEnabledEb")
TL_FUNCTION(layoutSoundPlay, "_ZN12CSoundObject4playEv")
TL_FUNCTION(layoutSoundStop, "_ZN12CSoundObject4stopEv")
TL_FUNCTION(layoutSoundPause, "_ZN12CSoundObject5pauseEv")
TL_FUNCTION(layoutSoundResume, "_ZN12CSoundObject6resumeEv")
TL_FUNCTION(layoutSoundLoop, "_ZN12CSoundObject9isLoopingEv")
TL_FUNCTION(layoutPosition, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(layoutCamera, "_ZN16CResourceManager16getCameraControlEv")

namespace {
struct Case { unsigned seed, mode, type; int operation; bool particle, immediate, negative; };
autotest::Capture* output;
const Case* input;
ParticleNativeOwners owners;
CLayout* layout;
CCameraControl* camera;
CParticle* particles[2];
CTimeline* timelines[2];
CSoundObject* sounds[2];
CCameraShake* shakes[2];
CEditorBaseObject* ordinary;
CParticleTechWrapper* techniques[2];
bool changed;
void number(unsigned n) { output->add(&n, 4); }
unsigned id(CEditorBaseObject* p)
{
    if (!p) return 0;
    if (p == layout) return 1;
    for (unsigned i = 0; i < 2; ++i) {
        if (p == techniques[i]) return 10 + i;
        if (p == timelines[i]) return 20 + i;
        if (p == sounds[i]) return 30 + i;
        if (p == shakes[i]) return 40 + i;
        if (p == particles[i]) return 50 + i;
    }
    return p == ordinary ? 60 : 99;
}
void mutate()
{
    if (changed) return;
    changed = true;
    if (input->mode == 1) layout->m_Unknown1D0.add(sounds[1]);
    if (input->mode == 2) layout->m_Unknown1D0.clear();
    if (input->mode == 3) layout->m_Unknown1B8 = static_cast<ELAYOUT_TYPES>(layout->m_Unknown1B8 == 1 ? 2 : 1);
    if (input->mode == 4 && layout->m_Unknown1D0.size()) layout->m_Unknown1D0[0] = ordinary;
    if (input->mode == 5) layout->m_pParticle = particles[1];
    if (input->mode == 6 && layout->m_Unknown1D0.size() > 1) layout->m_Unknown1D0[1] = shakes[1];
}
void event(unsigned tag, CEditorBaseObject* object)
{
    number(tag); number(id(object)); number(layout->m_Unknown1D0.size()); mutate();
}
struct Layout : CLayout {
    Layout() : CLayout(owners.resources, static_cast<ELAYOUT_TYPES>(0)) {}
    virtual void BroadcastEvent(unsigned code) { event(1, this); number(code); }
};
struct Technique : CParticleTechWrapper {
    Technique() : CParticleTechWrapper(owners.resources) {}
    virtual void setActivated(bool active) { event(2, this); number(active); m_bEnabled = active; }
};
void particleStart(CParticle* p) { event(3, p); p->m_bUnknown124 = true; }
void particleStop(CParticle* p, bool immediately) { event(4, p); number(immediately); p->m_bUnknown124 = false; }
void particlePause(CParticle* p) { event(5, p); p->m_bUnknown126 = true; }
void particleResume(CParticle* p) { event(6, p); p->m_bUnknown126 = false; }
void timelinePlay(CTimeline* p, bool forward) { event(7, p); number(forward); p->m_bEnabled = true; p->m_bIsPlayingBackwards = !forward; }
void timelineBack(CTimeline* p) { event(8, p); p->m_bEnabled = true; p->m_bIsPlayingBackwards = true; }
void timelineStop(CTimeline* p) { event(9, p); p->m_bEnabled = false; }
void timelinePause(CTimeline* p) { event(10, p); p->m_bEnabled = false; }
void timelineBegin(CTimeline* p) { event(11, p); p->m_fTimelinePosition = 0.0f; }
void timelineEnd(CTimeline* p) { event(12, p); p->m_fTimelinePosition = p->m_fSetTimelineDuration; }
void timelineEnabled(CTimeline* p, bool enabled) { event(13, p); number(enabled); p->m_bEnabled = enabled; }
void soundPlay(CSoundObject* p) { event(14, p); p->m_bSoundPlaying = true; }
void soundStop(CSoundObject* p) { event(15, p); p->m_bSoundPlaying = false; }
void soundPause(CSoundObject* p) { event(16, p); p->m_bSoundPaused = true; }
void soundResume(CSoundObject* p) { event(17, p); p->m_bSoundPaused = false; }
bool soundLoop(CSoundObject* p) { event(18, p); bool loop = (input->seed + id(p)) % 2; number(loop); return loop; }
Ogre::Vector3 position(CPositionableObject* p, bool absolute)
{
    event(19, p); number(absolute);
    return Ogre::Vector3(input->seed * 0.25f, -1.5f, 7.0f);
}
CCameraControl* getCamera(CResourceManager* p)
{
    number(20); number(p == owners.resources); mutate(); return camera;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw); input = &c; output = &out; changed = false;
    camera->clearCameraShakes();
    layout->m_Unknown1B8 = static_cast<ELAYOUT_TYPES>(c.type);
    layout->m_pParticle = c.particle ? particles[0] : NULL;
    layout->m_Unknown1D0.clear();
    CEditorBaseObject* objects[] = {techniques[0], sounds[0], timelines[0], shakes[0], NULL,
        ordinary, techniques[1], sounds[1], timelines[1], shakes[1]};
    const unsigned counts[] = {0, 1, 4, 10, 13, 17};
    unsigned count = counts[c.seed % 6];
    for (unsigned i = 0; i < count; ++i) layout->m_Unknown1D0.add(objects[(i + c.seed / 6) % 10]);
    ParticleUniverse::ParticleSystem* systems[2];
    for (unsigned i = 0; i < 2; ++i) {
        timelines[i]->m_bLayoutCanControl = (c.seed + i) % 3 != 0;
        timelines[i]->m_bEnabled = true; timelines[i]->m_bIsPlayingBackwards = false;
        timelines[i]->m_fTimelinePosition = 0.25f; timelines[i]->m_fSetTimelineDuration = 3.75f + i;
        sounds[i]->m_bSoundStartsOnActivated = (c.seed + i) % 2;
        sounds[i]->m_bSoundPlaying = (c.seed + i) % 3 == 0;
        sounds[i]->m_bSoundPaused = (c.seed + i) % 3 == 1;
        techniques[i]->m_bEnabled = (c.seed + i) % 2;
        systems[i] = techniques[i]->m_pParticleSystem;
        if ((c.seed + i) % 4 == 1) techniques[i]->m_pParticleSystem = NULL;
        shakes[i]->m_fCameraPositionX = -7; shakes[i]->m_fCameraPositionY = -9; shakes[i]->m_fCameraPositionZ = -11;
        shakes[i]->m_bCameraShakeActive = false;
        particles[i]->m_bUnknown124 = false; particles[i]->m_bUnknown126 = false;
    }
    for (unsigned list = 0; list < 2; ++list)
        for (unsigned i = 0; i < (c.seed + list * 3) % 12; ++i) {
            TSafePointer<CCameraShake>* ref = OGRE_NEW_T(TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL)();
            ref->setObject(shakes[i % 2]);
            if (list) camera->m_cameraShakesSecondary.add(ref); else camera->m_cameraShakes.add(ref);
        }
    detour::Set patches;
    TL_REDIRECT(patches, layoutParticleStart, &particleStart); TL_REDIRECT(patches, layoutParticleStop, &particleStop);
    TL_REDIRECT(patches, layoutParticlePause, &particlePause); TL_REDIRECT(patches, layoutParticleResume, &particleResume);
    TL_REDIRECT(patches, layoutTimelinePlay, &timelinePlay); TL_REDIRECT(patches, layoutTimelineBack, &timelineBack);
    TL_REDIRECT(patches, layoutTimelineStop, &timelineStop); TL_REDIRECT(patches, layoutTimelinePause, &timelinePause);
    TL_REDIRECT(patches, layoutTimelineBegin, &timelineBegin); TL_REDIRECT(patches, layoutTimelineEnd, &timelineEnd);
    TL_REDIRECT(patches, layoutTimelineEnabled, &timelineEnabled);
    TL_REDIRECT(patches, layoutSoundPlay, &soundPlay); TL_REDIRECT(patches, layoutSoundStop, &soundStop);
    TL_REDIRECT(patches, layoutSoundPause, &soundPause); TL_REDIRECT(patches, layoutSoundResume, &soundResume);
    TL_REDIRECT(patches, layoutSoundLoop, &soundLoop); TL_REDIRECT(patches, layoutPosition, &position);
    TL_REDIRECT(patches, layoutCamera, &getCamera);
    if (patches.failed()) _exit(41);
    autotest::invoke(out, ours ? layoutControlNew : layoutControlOld, layout,
                     static_cast<CLayout::ELAYOUT_FUNCTION_TYPES>(c.operation), c.immediate);
    if (ours && c.negative) layout->m_bStartOnLoad = !layout->m_bStartOnLoad;
    number(layout->m_bStartOnLoad); number(layout->m_Unknown1B8); number(id(layout->m_pParticle));
    number(layout->m_Unknown1D0.size());
    for (unsigned i = 0; i < layout->m_Unknown1D0.size(); ++i) number(id(layout->m_Unknown1D0[i]));
    number(camera->m_cameraShakes.size()); out.add(reinterpret_cast<char*>(&camera->m_cameraShakes) + 12, 8);
    for (unsigned i = 0; i < camera->m_cameraShakes.size(); ++i) number(id(camera->m_cameraShakes[i]->getObject()));
    number(camera->m_cameraShakesSecondary.size()); out.add(reinterpret_cast<char*>(&camera->m_cameraShakesSecondary) + 12, 8);
    for (unsigned i = 0; i < camera->m_cameraShakesSecondary.size(); ++i) number(id(camera->m_cameraShakesSecondary[i]->getObject()));
    for (unsigned i = 0; i < 2; ++i) {
        number(techniques[i]->m_bEnabled); number(systems[i]->getState());
        number(timelines[i]->m_bEnabled); number(timelines[i]->m_bIsPlayingBackwards);
        out.add(&timelines[i]->m_fTimelinePosition, 4);
        number(sounds[i]->m_bSoundPlaying); number(sounds[i]->m_bSoundPaused);
        out.add(&shakes[i]->m_fCameraPositionX, 12); number(shakes[i]->m_bCameraShakeActive);
        number(particles[i]->m_bUnknown124); number(particles[i]->m_bUnknown126);
        techniques[i]->m_pParticleSystem = systems[i];
    }
    layout->m_pParticle = NULL; layout->m_Unknown1D0.clear(); camera->clearCameraShakes();
}
void original(void* p, autotest::Capture& o) { side(p, o, false); }
void recovered(void* p, autotest::Capture& o) { side(p, o, true); }
int worker(const tlhybrid_host* host)
{
    owners = particleNativeOwners(2);
    CMasterResourceManager* master = CMasterResourceManager::getSingleton();
    if (!master->m_pParticlePreloader) master->m_pParticlePreloader = new CParticlePreloader(NULL);
    CLevel* level = new CLevel(L"layout controls", master->m_pSettings, NULL, owners.resources, owners.scene, NULL, 11, 2);
    owners.resources->m_pLevel = level;
    camera = new CCameraControl(owners.camera, owners.camera, owners.camera, owners.camera, owners.camera);
    layout = new Layout; ordinary = new CEditorBaseObject;
    particlegraphics::MaterialCompileBoundary boundary;
    for (unsigned i = 0; i < 2; ++i) {
        techniques[i] = new Technique; timelines[i] = new CTimeline;
        sounds[i] = new CSoundObject(owners.resources); shakes[i] = new CCameraShake;
        particles[i] = new CParticle(NULL, L"layout fixture", owners.resources);
    }
    autotest::Coverage coverage("layout_control_recovery", 0x9ddc00);
    const int operations[] = {0, 1, 2, 3, 4, -1, 5, 29};
    for (unsigned particle = 0; particle < 2; ++particle)
        for (unsigned type = 0; type < (particle ? 1u : 4u); ++type)
            for (unsigned op = 0; op < 8; ++op) for (unsigned seed = 0; seed < 24; ++seed) {
                Case c = {seed, seed % 7, type, operations[op], particle != 0, (seed / 3) % 2 != 0, false};
                autotest::Outcome a, b;
                autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
                if (coverage.observe(host, a, b)) {
                    host->log("    layout control particle%u type%u op%d seed%u mode%u status%d/%d issue%u/%u bytes%lu/%lu\n", particle, type, c.operation, seed, c.mode, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
                    for (unsigned j = 0; j < a.capture.length && j < b.capture.length; ++j) if (a.capture.data[j] != b.capture.data[j]) { host->log("    first diff%u %02x/%02x\n", j, a.capture.data[j], b.capture.data[j]); break; }
                    for (unsigned j = 0; j < 80 && j * 4 < a.capture.length && j * 4 < b.capture.length; ++j) {
                        unsigned left, right; std::memcpy(&left, a.capture.data + j * 4, 4); std::memcpy(&right, b.capture.data + j * 4, 4);
                        host->log("    word%u %08x/%08x\n", j, left, right);
                    }
                    coverage.report(host); return 1;
                }
            }
    coverage.report(host);
    Case c = {11, 0, 1, 0, false, false, true}; autotest::Outcome a, b;
    autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    layout control negative detected %u\n", unsigned(detected));
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(layout_control_recovery) { return systems_fixture::isolated(worker, host); }
