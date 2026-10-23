#include "AutoTest.h"
#include <Ogre.h>
#include <fstream>
#include <iterator>
#define private public
#define protected public
#include "EditorScene.h"
#include "Descriptor.h"
#include "DescriptorManager.h"
#include "DescriptorLoadConfiguration.h"
#include "OgreReader.h"
#include "RandomGroupDescriptor.h"
#include "LogicGroupDescriptor.h"
#undef protected
#undef private
#include "Utilities.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"

TL_ORIGINAL(bool,compressedObjectOld,(CEditorScene*,CDescriptorLoadConfiguration&,COgreReader&,CEditorBaseObject*,bool),"_Z26loadObjectByCompressedFileP12CEditorSceneR28CDescriptorLoadConfigurationR11COgreReaderP17CEditorBaseObjectb")
extern "C" bool compressedObjectNew(CEditorScene*,CDescriptorLoadConfiguration&,COgreReader&,CEditorBaseObject*,bool) __asm__("_Z26loadObjectByCompressedFileP12CEditorSceneR28CDescriptorLoadConfigurationR11COgreReaderP17CEditorBaseObjectb");
TL_ORIGINAL(void,compressedSceneCtor,(CEditorScene*,const wchar_t*),"_ZN12CEditorSceneC1EPKw")
TL_ORIGINAL(void,compressedSceneDtor,(CEditorScene*),"_ZN12CEditorSceneD1Ev")
TL_ORIGINAL(void,compressedSceneInit,(CEditorScene*,CResourceManager*,unsigned),"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_ORIGINAL(CEditorBaseObject*,compressedCreateOld,(CEditorScene*,CDescriptor*,CEditorBaseObject*,CEditorBaseObject*,bool),"_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b")
TL_ORIGINAL(CDescriptor*,compressedLookupOld,(CDescriptorManager*,unsigned,bool),"_ZN18CDescriptorManager22GetDescriptorByCreatedEjb")
TL_ORIGINAL(bool,compressedReadObjectOld,(CDescriptor*,COgreReader&,CEditorBaseObject*,CDescriptorLoadConfiguration&),"_ZN11CDescriptor24loadObjectFromBinaryFileER11COgreReaderP17CEditorBaseObjectR28CDescriptorLoadConfiguration")
TL_ORIGINAL(void,compressedReadOld,(COgreReader*,void*,unsigned),"_ZN11COgreReader4readEPvj")
TL_FUNCTION(compressedCreateEntry,"_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b")
TL_FUNCTION(compressedLookupEntry,"_ZN18CDescriptorManager22GetDescriptorByCreatedEjb")
TL_FUNCTION(compressedReadObjectEntry,"_ZN11CDescriptor24loadObjectFromBinaryFileER11COgreReaderP17CEditorBaseObjectR28CDescriptorLoadConfiguration")
TL_FUNCTION(compressedReadEntry,"_ZN11COgreReader4readEPvj")

namespace {
struct Case { unsigned seed; bool observed,negative; };
nativegame::Services* services;
const Case* input;autotest::Capture* output;
CDescriptorLoadConfiguration* configuration;TArrayList<CEditorBaseObject*>* alternate;
unsigned lookups,creates,loads,reads;
detour::Set lookupHook,createHook,loadHook,readHook;
void number(unsigned long long value){output->add(&value,sizeof value);}
void identity(CEditorBaseObject* object){number(object!=NULL);if(object){number(object->getGuid());number(object->getOriginalGuid());output->addText(object->getName());}}
void checkHooks(){if(lookupHook.failed()||createHook.failed()||loadHook.failed()||readHook.failed())output->issue=autotest::Capture::InvalidReport;}
CDescriptor* lookup(CDescriptorManager* manager,unsigned id,bool create){
 number(1);number(id);number(create);++lookups;
 lookupHook.restore();CDescriptor* result=compressedLookupOld(manager,id,create);TL_REDIRECT(lookupHook,compressedLookupEntry,&lookup);checkHooks();
 number(result!=NULL);if(result){number(result->m_iID);output->addText(result->m_sName);}
 if(input->seed/20%6==1&&lookups==1)return NULL;
 if(input->seed/20%6==4)configuration->m_createdObjects=alternate;
 return result;
}
CEditorBaseObject* create(CEditorScene* scene,CDescriptor* descriptor,CEditorBaseObject* source,CEditorBaseObject* parent,bool load){
 number(2);number(descriptor->m_iID);number(source==NULL);number(parent==NULL);number(load);++creates;
 if(input->seed/20%6==2&&creates==1)return NULL;
 createHook.restore();CEditorBaseObject* result=compressedCreateOld(scene,descriptor,source,parent,load);TL_REDIRECT(createHook,compressedCreateEntry,&create);checkHooks();identity(result);
 if(input->seed/20%6==5)configuration->m_createdObjects=NULL;
 return result;
}
bool load(CDescriptor* descriptor,COgreReader& reader,CEditorBaseObject* object,CDescriptorLoadConfiguration& cfg){
 number(3);number(descriptor->m_iID);number(&cfg==configuration);identity(object);++loads;
 number(cfg.m_createdObjects!=NULL);if(cfg.m_createdObjects){number(cfg.m_createdObjects->size());identity((*cfg.m_createdObjects)[cfg.m_createdObjects->size()-1]);}
 loadHook.restore();bool result=compressedReadObjectOld(descriptor,reader,object,cfg);TL_REDIRECT(loadHook,compressedReadObjectEntry,&load);checkHooks();number(result);identity(object);
 return input->seed/20%6==3&&loads==1?false:result;
}
void read(COgreReader* reader,void* bytes,unsigned size){
 number(4);number(reader->m_iPosition);number(size);++reads;
 readHook.restore();compressedReadOld(reader,bytes,size);TL_REDIRECT(readHook,compressedReadEntry,&read);checkHooks();number(reader->m_iPosition);
}
struct Scene {
 CResourceManager resources;CEditorScene* scene;
 Scene():resources(services->scene),scene(static_cast<CEditorScene*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditorScene),0,0,0))){compressedSceneCtor(scene,L"Compressed Fixture");compressedSceneInit(scene,&resources,0);}
 ~Scene(){compressedSceneDtor(scene);Ogre::NedAllocImpl::deallocBytes(scene);}
};
void word(std::ofstream& file,unsigned value){file.write(reinterpret_cast<const char*>(&value),4);}
void list(TArrayList<CEditorBaseObject*>& values){number(values.size());number(values.m_nCapacity);number(values.m_nGrowBy);for(unsigned i=0;i<values.size();++i)identity(values[i]);}
void side(void* raw,autotest::Capture& out,bool ours){
 input=static_cast<Case*>(raw);output=&out;unsigned seed=input->seed;lookups=creates=loads=reads=0;
 UTILITIES::setSeed(seed*73+19);UTILITIES::setSeedVolatile(seed*37+5);
 int before=g_iTotalCountOfObjects;
 {
 Scene fixture;CEditorScene& scene=*fixture.scene;
 CDescriptor* descriptors[2]={new CRandomGroupDescriptor,new CLogicGroupDescriptor(L"Logic Fixture",L"Fixture",L"Compressed")};
 for(unsigned i=0;i<2;++i){descriptors[i]->m_iID=800+i;scene.AddDescriptor(descriptors[i]);}
 CEditorBaseObject* roots[4];
 for(unsigned i=0;i<4;++i){roots[i]=compressedCreateOld(&scene,descriptors[i%2],NULL,NULL,false);if(!roots[i])std::abort();roots[i]->SetName(i&1?L"Объект Ω":L"");roots[i]->setOriginalGuid(10000+i);roots[i]->setParentGuid(i?roots[0]->getGuid():-1);}
 CDescriptorLoadConfiguration cfg;configuration=&cfg;cfg.m_iVersion=37;cfg.m_Remaps[771]=991;cfg.m_iParentGuid=seed%2?3333:-1;
 TArrayList<CEditorBaseObject*> created(seed%3+1),other(2);alternate=&other;
 for(unsigned i=0;i<seed/3%10;++i)created.add(i&1?roots[i%4]:NULL);
 if(seed/20%2)cfg.m_createdObjects=&created;
 char path[]="/tmp/otl-compressed-object-XXXXXX";int fd=mkstemp(path);if(fd<0)std::abort();close(fd);
 unsigned mode=seed%10;bool group=seed/10%2;unsigned count=seed/20%4;
 {
 std::ofstream file(path,std::ios::binary);
 if(mode==1)word(file,~0u);
 else if(mode==2)word(file,~1u);
 else if(mode!=0){
  unsigned root=group?0:seed/40%4;descriptors[root%2]->saveObjectInBinaryFile(file,roots[root],NULL);
  if(mode!=8){
   word(file,mode==3?0:mode==9?7:count);
   if(group){word(file,seed%3?0xf0000000u+seed:0);word(file,seed%7?0x80000000u+seed:~0u);}
   else for(unsigned i=0;i<count;++i){
    if(mode==5&&i==count/2){word(file,~1u);break;}
    if(mode==6&&i==0){word(file,~0u);continue;}
    unsigned child=(i+seed/80)%4;descriptors[child%2]->saveObjectInBinaryFile(file,roots[child],NULL);
    unsigned grand=mode==4&&i==0?2:0;word(file,grand);
    for(unsigned j=0;j<grand;++j){descriptors[j%2]->saveObjectInBinaryFile(file,roots[j],NULL);word(file,0);}
   }
  }
 }
 }
 std::ifstream file(path,std::ios::binary);std::string data((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());file.close();unlink(path);
 COgreReader reader;Ogre::DataStreamPtr stream(new Ogre::MemoryDataStream(data.empty()?NULL:const_cast<char*>(data.data()),data.size(),false));reader.ReadFile(stream);
 if(input->observed){TL_REDIRECT(lookupHook,compressedLookupEntry,&lookup);TL_REDIRECT(createHook,compressedCreateEntry,&create);TL_REDIRECT(loadHook,compressedReadObjectEntry,&load);TL_REDIRECT(readHook,compressedReadEntry,&read);checkHooks();}
 bool result=false;
 if(autotest::beginInvocation(out,ours?compressedObjectNew:compressedObjectOld)){
  result=(ours?compressedObjectNew:compressedObjectOld)(&scene,cfg,reader,seed%2?roots[2]:NULL,group);out.callCompleted=1;
 }
 lookupHook.restore();createHook.restore();loadHook.restore();readHook.restore();
 if(ours&&input->negative)result=!result;
 number(result);number(reader.m_iPosition);number(reader.m_iSize);number(lookups);number(creates);number(loads);number(reads);
 list(created);list(other);number(cfg.m_createdObjects==&created);number(cfg.m_createdObjects==&other);number(cfg.m_Remaps.size());
 for(std::map<long long,long long>::iterator i=cfg.m_Remaps.begin();i!=cfg.m_Remaps.end();++i){number(i->first);number(i->second);}
 number(scene.m_Objects.size());
 for(std::map<long long,CEditorBaseObject*>::iterator i=scene.m_Objects.begin();i!=scene.m_Objects.end();++i){number(i->first);CEditorBaseObject* object=i->second;identity(object);number(object->getParentGuid());number(object->getSceneOwner()==&scene);number(object->getDescriptor()->m_iID);CRandomGroup* r=dynamic_cast<CRandomGroup*>(object);number(r!=NULL);if(r){number(r->m_iMinimumChildren);number(r->m_iMaximumChildren);number(r->m_iChildSelectionLimit);number(r->m_iChildSpawnLimit);}}
 }
 number(g_iTotalCountOfObjects-before);
}
void oldSide(void* p,autotest::Capture& out){side(p,out,false);}void newSide(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,bool observed){
 initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;nativeeditor::Controls controls(native);
 const char* name=observed?"compressed_object_observed":"compressed_object_native";autotest::Coverage coverage(name,0x74c660);
 for(unsigned i=0;i<240;++i){Case c={i,observed,false};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,32000);autotest::runChild(newSide,&c,b,8000,32000);if(coverage.observe(host,a,b)){host->log("    compressed seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);Case c={34,observed,true};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,32000);autotest::runChild(newSide,&c,b,8000,32000);autotest::Coverage negative(name,0x74c660);int detected=negative.observe(host,a,b);host->log("    compressed negative observed%u detected%u completed%u incomplete%u\n",unsigned(observed),unsigned(detected==1),negative.completed,negative.missing);return detected!=1||negative.completed!=1||negative.missing;
}
int nativeWorker(const tlhybrid_host* h){return run(h,false);}int observedWorker(const tlhybrid_host* h){return run(h,true);}
}
TL_TEST(compressed_object_native){return systems_fixture::isolated(nativeWorker,host,240);}
TL_TEST(compressed_object_observed){return systems_fixture::isolated(observedWorker,host,240);}
