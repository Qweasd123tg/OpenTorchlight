#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include "ParticleNativeOwners.h"
#include "ParticleEmitterWrapper.h"
#include "AffectorWrapper.h"
#include <ParticleUniverseAffector.h>
#include "ParticleTechWrapper.h"
#include <ParticleUniverseEmitter.h>
#include <ParticleUniverseTechnique.h>
#include <ParticleUniverseSystem.h>

TL_ORIGINAL(void, parentOldTechCtor, (CParticleTechWrapper*, CResourceManager*), "_ZN20CParticleTechWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, parentOldTechDtor, (CParticleTechWrapper*), "_ZN20CParticleTechWrapperD1Ev")
TL_ORIGINAL(void, parentOldEmitterCtor, (CParticleEmitterWrapper*, CResourceManager*), "_ZN23CParticleEmitterWrapperC1EP16CResourceManager")
TL_ORIGINAL(void, parentOldEmitterDtor, (CParticleEmitterWrapper*), "_ZN23CParticleEmitterWrapperD1Ev")
TL_ORIGINAL(void, parentOriginal, (CParticleEmitterWrapper*, CParticleTechWrapper*), "_ZN23CParticleEmitterWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper")
extern "C" void parentRecovered(CParticleEmitterWrapper*, CParticleTechWrapper*) __asm__("_ZN23CParticleEmitterWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper");

TL_ORIGINAL(void, parentOldAffectorCtor, (CAffectorWrapper*, CResourceManager*, std::string), "_ZN16CAffectorWrapperC1EP16CResourceManagerSs")
TL_ORIGINAL(void, parentOldAffectorDtor, (CAffectorWrapper*), "_ZN16CAffectorWrapperD1Ev")
TL_ORIGINAL(void, parentOldAffectorParent, (CAffectorWrapper*, CParticleTechWrapper*), "_ZN16CAffectorWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper")
TL_ORIGINAL(void, oldAddEmitter, (CParticleTechWrapper*, CParticleEmitterWrapper*), "_ZN20CParticleTechWrapper10addEmitterEP23CParticleEmitterWrapper")
TL_ORIGINAL(void, oldRemoveEmitter, (CParticleTechWrapper*, CParticleEmitterWrapper*), "_ZN20CParticleTechWrapper13removeEmitterEP23CParticleEmitterWrapper")
TL_ORIGINAL(void, oldAddAffector, (CParticleTechWrapper*, CAffectorWrapper*), "_ZN20CParticleTechWrapper11addAffectorEP16CAffectorWrapper")
TL_ORIGINAL(void, oldRemoveAffector, (CParticleTechWrapper*, CAffectorWrapper*), "_ZN20CParticleTechWrapper14removeAffectorEP16CAffectorWrapper")
extern "C" void newAddEmitter(CParticleTechWrapper*, CParticleEmitterWrapper*) __asm__("_ZN20CParticleTechWrapper10addEmitterEP23CParticleEmitterWrapper");
extern "C" void newRemoveEmitter(CParticleTechWrapper*, CParticleEmitterWrapper*) __asm__("_ZN20CParticleTechWrapper13removeEmitterEP23CParticleEmitterWrapper");
extern "C" void newAddAffector(CParticleTechWrapper*, CAffectorWrapper*) __asm__("_ZN20CParticleTechWrapper11addAffectorEP16CAffectorWrapper");
extern "C" void newRemoveAffector(CParticleTechWrapper*, CAffectorWrapper*) __asm__("_ZN20CParticleTechWrapper14removeAffectorEP16CAffectorWrapper");

namespace {
template<class T> union Storage { long double alignment; char bytes[sizeof(T)]; };
struct Case { unsigned seed; bool negative; unsigned operation; };
CResourceManager* resources;
ParticleNativeOwners owners;
unsigned profile;
unsigned operation;
void number(autotest::Capture& out, long long value) { out.add(&value, sizeof(value)); }

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    Storage<CParticleTechWrapper> techStorage[2];
    CParticleTechWrapper* techs[2];
    for (unsigned i = 0; i < 2; ++i) {
        techs[i] = reinterpret_cast<CParticleTechWrapper*>(techStorage[i].bytes);
        parentOldTechCtor(techs[i], resources);
    }
    Storage<CParticleEmitterWrapper> emitterStorage[3];
    CParticleEmitterWrapper* emitters[3];
    for (unsigned i = 0; i < 3; ++i) {
        emitters[i] = reinterpret_cast<CParticleEmitterWrapper*>(emitterStorage[i].bytes);
        parentOldEmitterCtor(emitters[i], resources);
        parentOriginal(emitters[i], techs[(c.seed + i) % 2]);
    }
    Storage<CAffectorWrapper> affectorStorage;
    CAffectorWrapper* affector = reinterpret_cast<CAffectorWrapper*>(affectorStorage.bytes);
    parentOldAffectorCtor(affector, resources, "LinearForce");
    parentOldAffectorParent(affector, techs[0]);
    CParticleEmitterWrapper* target = emitters[c.seed % 3];
    if (c.seed % 4 == 0) parentOriginal(target, NULL);
    if (c.seed % 4 == 1) {
        ParticleUniverse::ParticleTechnique* old = target->m_pEmitter->getParentTechnique();
        if (old) old->removeEmitter(target->m_pEmitter);
    }
    CParticleTechWrapper* destination = c.seed % 3 == 0 ? NULL : techs[(c.seed / 3) % 2];
    CParticleTechWrapper* selected = techs[(c.seed / 3) % 2];
    // These helpers are called after the wrapper's parent field is assigned.
    // Start new attachments in that same state, with no old native technique.
    if (c.operation == 1 && (target->m_pParticleTechWrapper != selected || c.seed & 4)) {
        parentOriginal(target, NULL);
        target->m_pParticleTechWrapper = selected;
    }
    if (c.operation == 1 && target->m_pEmitter->getParentTechnique())
        target->m_pEmitter->getParentTechnique()->removeEmitter(target->m_pEmitter);
    if (c.operation == 3 && (affector->m_pParticleTechWrapper != selected || c.seed & 4)) {
        parentOldAffectorParent(affector, NULL);
        affector->m_pParticleTechWrapper = selected;
    }
    techs[0]->m_bPlaying = bool(c.seed & 8);
    techs[1]->m_bPlaying = bool(c.seed & 16);
    particleNativeSetEditorMode(owners, profile == 0);
    if (c.operation == 0) {
        typedef void (*Function)(CParticleEmitterWrapper*, CParticleTechWrapper*);
        Function function = ours ? parentRecovered : parentOriginal;
        if (!autotest::beginInvocation(out, function)) return;
        function(target, destination);
        if (c.seed % 5 == 0) function(target, destination);
    } else if (c.operation <= 2) {
        typedef void (*Function)(CParticleTechWrapper*, CParticleEmitterWrapper*);
        Function function = c.operation == 1 ? (ours ? newAddEmitter : oldAddEmitter)
            : (ours ? newRemoveEmitter : oldRemoveEmitter);
        if (!autotest::beginInvocation(out, function)) return;
        function(selected, c.seed % 11 == 10 ? NULL : target);
    } else {
        typedef void (*Function)(CParticleTechWrapper*, CAffectorWrapper*);
        Function function = c.operation == 3 ? (ours ? newAddAffector : oldAddAffector)
            : (ours ? newRemoveAffector : oldRemoveAffector);
        if (!autotest::beginInvocation(out, function)) return;
        function(selected, c.seed % 11 == 10 ? NULL : affector);
    }
    out.callCompleted = 1;
    CParticleTechWrapper* actual = target->m_pParticleTechWrapper;
    if (ours && c.negative) {
        if (c.operation == 0) target->m_pParticleTechWrapper = actual ? NULL : techs[0];
        else if (c.operation <= 2) selected->m_Unknown1D8.add(NULL);
        else selected->m_Unknown1F0.add(NULL);
    }
    for (unsigned i = 0; i < 3; ++i) {
        number(out, emitters[i]->m_pParticleTechWrapper == NULL);
        for (unsigned j = 0; j < 2; ++j) {
            number(out, emitters[i]->m_pParticleTechWrapper == techs[j]);
            number(out, emitters[i]->m_pEmitter->getParentTechnique() == techs[j]->m_technique);
        }
    }
    for (unsigned i = 0; i < 2; ++i) {
        number(out, techs[i]->m_bPlaying);
        number(out, techs[i]->m_pParticleSystem != NULL);
        if (techs[i]->m_pParticleSystem) number(out, techs[i]->m_pParticleSystem->getState());
        out.add(reinterpret_cast<const char*>(&techs[i]->m_Unknown1D8) + 12, 8);
        number(out, techs[i]->m_Unknown1D8.size());
        for (unsigned j = 0; j < techs[i]->m_Unknown1D8.size(); ++j)
            for (unsigned k = 0; k < 3; ++k)
                number(out, techs[i]->m_Unknown1D8[j] == emitters[k]);
        number(out, techs[i]->m_technique->getNumEmitters());
        for (unsigned j = 0; j < techs[i]->m_technique->getNumEmitters(); ++j)
            for (unsigned k = 0; k < 3; ++k)
                number(out, techs[i]->m_technique->getEmitter(j) == emitters[k]->m_pEmitter);
    }
    // Affector ownership and order are observed independently from emitters.
    for (unsigned i = 0; i < 2; ++i) {
        number(out, techs[i]->m_Unknown1F0.size());
        out.add(reinterpret_cast<const char*>(&techs[i]->m_Unknown1F0) + 12, 8);
        for (unsigned j = 0; j < techs[i]->m_Unknown1F0.size(); ++j)
            number(out, techs[i]->m_Unknown1F0[j] == affector);
        number(out, techs[i]->m_technique->getNumAffectors());
        for (unsigned j = 0; j < techs[i]->m_technique->getNumAffectors(); ++j)
            number(out, techs[i]->m_technique->getAffector(j) == affector->m_pAffector);
    }
    target->m_pParticleTechWrapper = actual;
    particleNativeSetEditorMode(owners, true);
    selected->m_Unknown1D8.remove(NULL);
    selected->m_Unknown1F0.remove(NULL);
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 2; ++j) oldRemoveEmitter(techs[j], emitters[i]);
        parentOldEmitterDtor(emitters[i]);
    }
    for (unsigned j = 0; j < 2; ++j) oldRemoveAffector(techs[j], affector);
    parentOldAffectorDtor(affector);
    for (unsigned i = 0; i < 2; ++i) parentOldTechDtor(techs[i]);
}
void before(void* c, autotest::Capture& out) { side(c, out, false); }
void after(void* c, autotest::Capture& out) { side(c, out, true); }

int worker(const tlhybrid_host* host)
{
    owners = particleNativeOwners(0);
    resources = owners.resources;
    if (!resources) return 1;
    const char* labels[] = {"emitter_parent_", "tech_add_emitter_", "tech_remove_emitter_", "tech_add_affector_", "tech_remove_affector_"};
    const unsigned long addresses[] = {0xa32a50, 0xa3cbd0, 0xa3cab0, 0xa3c8d0, 0xa3c7b0};
    std::string label = std::string(labels[operation]) + (profile == 0 ? "editor_recovery" : "runtime_recovery");
    autotest::Coverage coverage(label.c_str(), addresses[operation]);
    for (unsigned i = 0; i < 48; ++i) {
        Case c = {i, false, operation};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    parent seed%u status%d/%d issue%u/%u started%u/%u completed%u/%u\n", i,
                a.childStatus, b.childStatus, a.capture.issue, b.capture.issue,
                a.capture.callStarted, b.capture.callStarted, a.capture.callCompleted, b.capture.callCompleted);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c = {11, true, operation};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    emitter parent negative control detected %u\n", detected ? 1u : 0u);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(emitter_parent_editor_recovery) { profile = 0; operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(emitter_parent_runtime_recovery) { profile = 1; operation = 0; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_add_emitter_editor_recovery) { profile = 0; operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_add_emitter_runtime_recovery) { profile = 1; operation = 1; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_remove_emitter_editor_recovery) { profile = 0; operation = 2; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_remove_emitter_runtime_recovery) { profile = 1; operation = 2; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_add_affector_editor_recovery) { profile = 0; operation = 3; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_add_affector_runtime_recovery) { profile = 1; operation = 3; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_remove_affector_editor_recovery) { profile = 0; operation = 4; return systems_fixture::isolated(worker, host); }
TL_TEST(tech_remove_affector_runtime_recovery) { profile = 1; operation = 4; return systems_fixture::isolated(worker, host); }
