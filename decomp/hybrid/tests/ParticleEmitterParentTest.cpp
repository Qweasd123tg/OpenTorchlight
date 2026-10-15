#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "ParticleEmitterWrapper.h"
#include "EditorScene.h"
extern "C" void* techParentTable[] __asm__("_ZTV20CParticleTechWrapper");
extern "C" void* baseParentTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(void, originalParent, (void*, long long), "_ZN23CParticleEmitterWrapper13setParentGuidEx")
extern "C" void candidateParent(void*, long long) __asm__("_ZN23CParticleEmitterWrapper13setParentGuidEx");
TL_FUNCTION(removeTarget, "_ZN20CParticleTechWrapper13removeEmitterEP23CParticleEmitterWrapper")
TL_FUNCTION(parentTarget, "_ZN23CParticleEmitterWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper")
TL_FUNCTION(lookupTarget, "_ZN12CEditorScene16GetObjectInSceneEx")
namespace {
struct Case { void* object; void* scene; void* nodes[3]; void* old; long long guid; unsigned mode, mutation; };
Case* input; autotest::Capture* output; unsigned removes, parents, lookups;
void invalid() { output->issue = autotest::Capture::InvalidReport; }
void number(unsigned n) { output->add(&n, sizeof(n)); }
unsigned id(void* p) { if (!p) return 0; if (p == input->object) return 1; if (p == input->old) return 2; for (unsigned i=0;i<3;++i) if(p==input->nodes[i]) return 10+i; invalid(); return 99; }
void remove(void* p, void* object) {
    if (p != input->old || object != input->object || removes || parents || lookups) invalid();
    number(1); number(id(p)); number(id(object)); ++removes;
    if (input->mutation) { void* zero = 0; std::memcpy(static_cast<char*>(object)+0x108,&zero,8); }
}
void parent(void* object, void* p) {
    if (object != input->object || (parents == 0 ? p != 0 : p == 0)) invalid();
    number(2); number(id(object)); number(id(p)); ++parents;
    std::memcpy(static_cast<char*>(object)+0x108,&p,8);
}
void* lookup(void* scene, long long guid) {
    if (scene != input->scene || parents != 1 || lookups >= 3) invalid();
    number(3); output->add(&guid,sizeof(guid)); ++lookups;
    if (input->mode == 2 || (input->mode == 7 && guid == 200)) return 0;
    if (guid == 100) return input->nodes[0];
    if (guid == 200) return input->nodes[1];
    if (guid == 300) return input->nodes[2];
    invalid(); return 0;
}
void body(Case& c, bool ours, autotest::Capture& out) {
    input=&c;output=&out;removes=parents=lookups=0;
    detour::Set patches;TL_REDIRECT(patches,removeTarget,&remove);TL_REDIRECT(patches,parentTarget,&parent);TL_REDIRECT(patches,lookupTarget,&lookup);
    if (patches.failed()) { invalid();return; }
    autotest::invoke(out,ours?candidateParent:originalParent,c.object,c.guid);
    unsigned expectedLookups = c.mode < 2 ? 0 : c.mode == 5 || c.mode == 7 ? 2 : c.mode == 6 ? 3 : 1;
    if (removes != (c.old ? 1u : 0u) || parents != (c.mode >= 4 && c.mode <= 6 ? 2u : 1u) || lookups != expectedLookups) invalid();
    long long guid;std::memcpy(&guid,static_cast<char*>(c.object)+0x18,8);if(guid!=c.guid)invalid();
    number(removes);number(parents);number(lookups);out.add(c.object,sizeof(CParticleEmitterWrapper));
    for(unsigned i=0;i<3;++i)out.add(c.nodes[i],sizeof(CParticleTechWrapper));
    patches.restore();
}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
}
TL_TEST(particle_emitter_parent_differential) {
    autotest::Coverage coverage("particle_emitter_parent_differential",(uint64_t)(uintptr_t)&originalParent);
    for(unsigned n=0;n<64;++n){
        unsigned long long object[(sizeof(CParticleEmitterWrapper)+7)/8];
        unsigned long long nodes[3][(sizeof(CParticleTechWrapper)+7)/8];
        unsigned long long scene[4],old[4];
        std::memset(object,0x57+n,sizeof(object));std::memset(nodes,0x79,sizeof(nodes));
        Case c={};c.object=object;c.mode=n%8;c.mutation=n/16%2;c.old=n&8?old:0;c.scene=c.mode==0?0:scene;c.guid=c.mode==1?-1:100;
        for(unsigned i=0;i<3;++i){
            c.nodes[i]=nodes[i];bool tech=(c.mode==4&&i==0)||(c.mode==5&&i==1)||(c.mode==6&&i==2);
            void* table=(tech?techParentTable:baseParentTable)+2;std::memcpy(nodes[i],&table,8);
            long long next=c.mode==3?-1:i==0?200:i==1?300:-1;std::memcpy(reinterpret_cast<char*>(nodes[i])+0x18,&next,8);
        }
        std::memcpy(reinterpret_cast<char*>(object)+0x108,&c.old,8);std::memcpy(reinterpret_cast<char*>(object)+0x48,&c.scene,8);
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        if(coverage.observe(host,a,b)){host->log("    emitter parent case %u child %d/%d issue %u/%u\n",n,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}
    }
    coverage.report(host);return coverage.completed!=64||coverage.different||coverage.missing;
}
