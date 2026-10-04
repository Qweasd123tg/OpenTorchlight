#include <cstring>
#include <limits>
#include <map>
#include <new>
#include <vector>
#include "AutoTest.h"
#include "HeadlessGui.h"
#include "Item.h"
#include "Editor.h"
#include "GameGlobals.h"
#include "MasterResourceManager.h"

TL_ORIGINAL(void, originalItemUpdate, (CItem*,Ogre::Camera*,const Ogre::Vector3&,float), "_ZN5CItem6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void* updateItemTable[] __asm__("_ZTV5CItem");
extern CGameGlobals* updateGlobals __asm__("_ZL14g_pGameGlobals");
extern CMasterResourceManager* m_pMasterResourceManager;
extern unsigned int KSETTINGS_NETBOOK_MODE;
namespace {
// Fixed-function test materials need no GPU. Mark their single real technique
// supported explicitly, avoiding RenderSystem compilation in a headless test.
class CpuMaterial : public Ogre::Material {
public:
    CpuMaterial(const Ogre::String& name,Ogre::ResourceHandle handle)
      : Ogre::Material(Ogre::MaterialManager::getSingletonPtr(),name,handle,"General") {
        if(!getNumTechniques())createTechnique();
        if(!getTechnique(0)->getNumPasses())getTechnique(0)->createPass();
    }
    void ready() {
        mSupportedTechniques.clear();mSupportedTechniques.push_back(getTechnique(0));
        LodTechniques* lods=new LodTechniques;(*lods)[0]=getTechnique(0);
        mBestTechniquesBySchemeList[0]=lods;mCompilationRequired=false;
    }
};
// Camera visibility is an ABI-level collaborator stub: Frustum construction
// itself requires a RenderSystem. Record the real forwarded AABB and return
// the chosen visibility decision; no camera projection/rendering is claimed.
struct ProbeCamera {
    void** vptr;bool visible;unsigned int calls;Ogre::AxisAlignedBox last;void* table[128];
    ProbeCamera(Ogre::SceneManager*,bool result):visible(result),calls(0) {
        std::memset(table,0,sizeof(table));table[100]=reinterpret_cast<void*>(&check);vptr=table;
    }
    static bool check(ProbeCamera* self,const Ogre::AxisAlignedBox& box,Ogre::FrustumPlane*) {
        ++self->calls;self->last=box;return self->visible;
    }
};
struct Case { unsigned int seed;Ogre::SceneManager* scene;bool nanViewer; };
void* modelPointer;unsigned int modelLookups;std::vector<unsigned int> themeCalls;
void* modelForFrame(void*) {++modelLookups;return modelPointer;}
void themeForFrame(void*,CUnitTheme*,bool added) {themeCalls.push_back(added?1:0);}
void pointerAt(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void floatAt(void* p,size_t offset,float value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    CpuMaterial source("item-frame-source",91001),target("item-frame-target",91002);
    Ogre::Pass* src=source.getTechnique(0)->getPass(0);Ogre::Pass* dst=target.getTechnique(0)->getPass(0);
    src->setAmbient(0.2f,0.4f,0.6f);src->setDiffuse(0.8f,0.6f,0.4f,0.9f);src->setSelfIllumination(0.3f,0.2f,0.1f);
    dst->setAmbient(0.01f,0.02f,0.03f);dst->setDiffuse(0.1f,0.2f,0.3f,0.4f);dst->setSelfIllumination(0.1f,0.1f,0.1f);
    source.ready();target.ready();
    ProbeCamera camera(c.scene,(c.seed&1)!=0);
    long long item[0x220/8],model[0x250/8],bounds[0xb8/8],manager[0x48/8],globals[0x2d0/8],editor[0x1f8/8],master[0x190/8],settings[0x140/8],hierarchy[0x100/8],bank[0xd0/8],sound[0x20/8];
    std::memset(item,0,sizeof(item));std::memset(model,0,sizeof(model));std::memset(bounds,0,sizeof(bounds));std::memset(manager,0,sizeof(manager));
    std::memset(globals,0,sizeof(globals));std::memset(editor,0,sizeof(editor));std::memset(master,0,sizeof(master));std::memset(settings,0,sizeof(settings));
    std::memset(hierarchy,0,sizeof(hierarchy));std::memset(bank,0,sizeof(bank));std::memset(sound,0,sizeof(sound));
    char* self=reinterpret_cast<char*>(item);
    void* table[89];std::memcpy(table,updateItemTable+2,sizeof(table));table[60]=reinterpret_cast<void*>(&modelForFrame);table[59]=reinterpret_cast<void*>(&themeForFrame);pointerAt(item,0,table);
    self[0x81]=(c.seed>>1)&1;self[0x208]=(c.seed>>2)&1;self[0x198]=(c.seed&8)==0;self[0x218]=(c.seed>>4)&1;self[0x209]=(c.seed>>5)&1;self[0x19a]=1;
    const float times[]={0,1,-1,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};
    floatAt(item,0x1e0,times[c.seed%5]);floatAt(item,0x204,0.5f);floatAt(model,0x228,-17);
    floatAt(globals,0xa8,10);floatAt(globals,0xac,24);floatAt(globals,0xb0,40);floatAt(globals,0xb4,16);floatAt(globals,0xb8,30);
    CGameGlobals* savedGlobals=updateGlobals;updateGlobals=reinterpret_cast<CGameGlobals*>(globals);
    CEditor* savedEditor=gEditor;gEditor=reinterpret_cast<CEditor*>(editor);int flags=c.seed%4;std::memcpy(reinterpret_cast<char*>(editor)+0x64,&flags,4);
    CMasterResourceManager* savedMaster=m_pMasterResourceManager;unsigned int savedIndex=KSETTINGS_NETBOOK_MODE;
    m_pMasterResourceManager=reinterpret_cast<CMasterResourceManager*>(master);KSETTINGS_NETBOOK_MODE=0;
    std::vector<int>* ints=new(reinterpret_cast<char*>(settings)+0x40)std::vector<int>(1,c.seed%7==0?1:0);pointerAt(master,0x90,settings);
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;
    Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10)Relations;pointerAt(manager,0x20,hierarchy);pointerAt(item,0x68,manager);
    unsigned int type=c.seed&1?29:0;std::memcpy(self+0x1ac,&type,4);
    Ogre::Vector3 position(c.seed%4==0?107.0f:7.0f,3,-2);std::memcpy(self+0x84,&position,sizeof(position));
    Ogre::Vector3 minimum=position-Ogre::Vector3(1,1,1),maximum=position+Ogre::Vector3(1,1,1);
    std::memcpy(reinterpret_cast<char*>(bounds)+0x40,&minimum,sizeof(minimum));std::memcpy(reinterpret_cast<char*>(bounds)+0x4c,&maximum,sizeof(maximum));pointerAt(item,0x1c0,bounds);
    const float distances[]={0,2,10,12,20,50};Ogre::Vector3 viewer=position+Ogre::Vector3(0,0,distances[c.seed%6]);
    if(c.nanViewer)viewer.z=std::numeric_limits<float>::quiet_NaN();
    unsigned char material[64];std::memset(material,0,sizeof(material));pointerAt(material,8,&source);pointerAt(material,0x10,&target);
    pointerAt(model,0x208,material);pointerAt(model,0x210,material+sizeof(material));pointerAt(model,0x218,material+sizeof(material));modelPointer=c.seed%7?model:NULL;modelLookups=0;
    TArrayList<CUnitTheme*>* added=new(self+0x120)TArrayList<CUnitTheme*>(2);TArrayList<CUnitTheme*>* removed=new(self+0x108)TArrayList<CUnitTheme*>(2);
    added->add(NULL);removed->add(NULL);themeCalls.clear();
    TArrayList<int>* channels=new(reinterpret_cast<char*>(bank)+0x18)TArrayList<int>(2);channels->add(-1);
    TArrayList<float>* volumes=new(reinterpret_cast<char*>(bank)+0x30)TArrayList<float>(2);volumes->add(0.5f);pointerAt(bank,0x10,sound);
    if(c.seed%4==0)pointerAt(item,0x1d8,bank);
    const float elapsedValues[]={0,0.25f,1,1000,-0.25f,std::numeric_limits<float>::quiet_NaN()};float elapsed=elapsedValues[c.seed%6];
    CItem* object=reinterpret_cast<CItem*>(item);
    if(ours)object->CItem::update(reinterpret_cast<Ogre::Camera*>(&camera),viewer,elapsed);else originalItemUpdate(object,reinterpret_cast<Ogre::Camera*>(&camera),viewer,elapsed);
    out.add(self+0x190,1);out.add(self+0x198,3);out.add(self+0x204,5);out.add(self+0x1e0,4);out.add(self+0x81,1);
    out.add(&modelLookups,sizeof(modelLookups));out.add(reinterpret_cast<char*>(model)+0x228,4);out.add(material,8);out.add(material+0x34,4);
    out.add(&camera.calls,sizeof(camera.calls));if(camera.calls) {out.add(&camera.last.getMinimum(),sizeof(Ogre::Vector3));out.add(&camera.last.getMaximum(),sizeof(Ogre::Vector3));}
    const Ogre::ColourValue* colors[]={&dst->getAmbient(),&dst->getDiffuse(),&dst->getSelfIllumination()};for(int i=0;i<3;++i)out.add(colors[i],sizeof(Ogre::ColourValue));
    size_t n=themeCalls.size();out.add(&n,sizeof(n));for(size_t i=0;i<n;++i)out.add(&themeCalls[i],sizeof(themeCalls[i]));
    unsigned int channelCount=channels->size(),volumeCount=volumes->size();out.add(&channelCount,4);out.add(&volumeCount,4);out.add(reinterpret_cast<char*>(sound)+0x10,4);
    added->~TArrayList<CUnitTheme*>();removed->~TArrayList<CUnitTheme*>();channels->~TArrayList<int>();volumes->~TArrayList<float>();relations->~Relations();ints->~vector<int>();
    updateGlobals=savedGlobals;gEditor=savedEditor;m_pMasterResourceManager=savedMaster;KSETTINGS_NETBOOK_MODE=savedIndex;
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(item_frame_visibility_sound_and_light) {
    int failures=0;
    tlheadless::Environment environment;
    Ogre::SceneManager* scene=environment.root().createSceneManager(Ogre::ST_GENERIC,"item-frame-scene");
    for(unsigned int special=0;special<2;++special)
    for(unsigned int seed=0;seed<96;++seed) {
        Case c={seed,scene,special!=0};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    item frame seed %u/%u status %d/%d bytes %lu/%lu\n",seed,special,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    environment.root().destroySceneManager(scene);
    return failures;
}
