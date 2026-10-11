// Shadow test: editor API functions of EditorBaseObject.cpp that differ from the
// original only in register allocation or block layout. gEditor points at a
// fake editor whose object manager holds a real std::map of fake objects.
#include <cstring>
#include <map>

#include "Editor.h"
#include "EditorBaseObject.h"
#include "EditorDLL.h"
#include "AutoTest.h"
#include <limits>
#include "TArrayList.h"

TL_ORIGINAL(int, originalGetObjectDescriptorID, (long long), "_Z27EditorGetObjectDescriptorIDx")
TL_ORIGINAL(void, originalParticleMovementConfig, (float&, float&, bool), "_Z28EditorParticleMovementConfigRfS_b")

extern "C" int candidateGetObjectDescriptorID (long long) __asm__("_Z27EditorGetObjectDescriptorIDx");
extern "C" void candidateParticleMovementConfig (float&, float&, bool) __asm__("_Z28EditorParticleMovementConfigRfS_b");
namespace
{

// CEditor offsets (from CEditor::CEditor).
const int kEditorSize = 0x1f8;
const int kDisabled = 0x49;
const int kEditorResourceManager = 0x58;
const int kObjectManager = 0x120;
const int kParticleMovementA = 0x1c0;
const int kParticleMovementB = 0x1c4;

// CEditorBaseObject offsets.
const int kObjectSize = 0x58;
const int kGuid = 0x10;
const int kDescriptor = 0x38;
const int kSceneOwner = 0x48;
// CEditorScene::m_pDescriptorManager.
const int kDescriptorManager = 0x100;

struct FakeObjectManager
{
    void* vptr;
    void* safePointers;
    std::map<long long, CEditorBaseObject*> objects;
    TArrayList<CEditorBaseObject*> selected;
    TArrayList<CEditorBaseObject*> created;
    void* control;
    bool flags[2];
};

const int kObjects = 6;

char g_editor[kEditorSize];
char g_objects[kObjects][kObjectSize];
char g_scenes[2][0x190];
char g_dummy[16];
FakeObjectManager* g_manager;

unsigned int g_seed = 9001;

unsigned int nextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return g_seed >> 8;
}

void setPointer(char* object, int offset, const void* value)
{
    std::memcpy(object + offset, &value, sizeof(value));
}

void randomEditor()
{
    g_editor[kDisabled] = char(nextRandom() % 5 == 0);
    setPointer(g_editor, kEditorResourceManager, (nextRandom() % 5 == 0) ? 0 : g_dummy);
    setPointer(g_editor, kObjectManager, g_manager);
}

void randomWorld()
{
    g_manager->objects.clear();
    setPointer(g_scenes[0], kDescriptorManager, 0);
    setPointer(g_scenes[1], kDescriptorManager, g_dummy);
    for (int i = 0; i < kObjects; i++)
    {
        std::memset(g_objects[i], 0, kObjectSize);
        long long guid = 100 + i;
        std::memcpy(g_objects[i] + kGuid, &guid, sizeof(guid));
        unsigned int scene = nextRandom() % 3;
        setPointer(g_objects[i], kSceneOwner, scene == 2 ? 0 : g_scenes[scene]);
        setPointer(g_objects[i], kDescriptor, (nextRandom() % 3) ? g_dummy : 0);
        if (nextRandom() % 4)
            g_manager->objects[guid] = reinterpret_cast<CEditorBaseObject*>(g_objects[i]);
    }
}

} // namespace


namespace {
struct Case{unsigned seed,op;};
void body(Case&c,bool ours,autotest::Capture&out){
 g_seed=c.seed*713+37;g_manager=new FakeObjectManager();std::memset(g_editor,c.seed,sizeof(g_editor));randomEditor();randomWorld();gEditor=reinterpret_cast<CEditor*>(g_editor);
 if(c.op==0){long long guid=c.seed%8==0?-1:98+int(c.seed%(kObjects+4));autotest::invoke(out,ours?candidateGetObjectDescriptorID:originalGetObjectDescriptorID,guid);}
 else{
  const float values[]={0.0f,-0.0f,-1.0f,0.125f,32.5f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-999.75f};
  float a=values[c.seed%8],b=values[(c.seed/8)%8],x=values[(c.seed/16)%8],y=values[(c.seed/24)%8];std::memcpy(g_editor+kParticleMovementA,&x,4);std::memcpy(g_editor+kParticleMovementB,&y,4);
  void(*fn)(float&,float&,bool)=ours?candidateParticleMovementConfig:originalParticleMovementConfig;if(!autotest::beginInvocation(out,fn))return;fn(a,b,((c.seed/64)&1)!=0);out.callCompleted=1;out.add(&a,4);out.add(&b,4);
 }
 out.add(g_editor,sizeof(g_editor));out.add(g_objects,sizeof(g_objects));out.add(g_scenes,sizeof(g_scenes));out.add(g_dummy,sizeof(g_dummy));unsigned n=g_manager->objects.size();out.add(&n,4);
 for(std::map<long long,CEditorBaseObject*>::const_iterator it=g_manager->objects.begin();it!=g_manager->objects.end();++it){out.add(&it->first,8);long k=(reinterpret_cast<char*>(it->second)-g_objects[0])/kObjectSize;out.add(&k,sizeof(k));}
 delete g_manager;g_manager=NULL;gEditor=NULL;
}
void original(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){autotest::Coverage coverage(name,op?(uint64_t)(uintptr_t)originalParticleMovementConfig:(uint64_t)(uintptr_t)originalGetObjectDescriptorID);
 for(unsigned seed=0;seed<512;++seed){Case c={seed,op};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    editor base %u/%u status %d/%d\n",op,seed,a.status,b.status);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(editor_descriptor_id_observed){return run(host,0,"editor_descriptor_id_observed");}
TL_TEST(editor_particle_config_observed){return run(host,1,"editor_particle_config_observed");}
