// Entries, RTTI and indexing are real; only external object operations are spies.
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, original0, (void*, float), "_ZN22CDamageShapeDescriptor6updateEf")
extern "C" void candidate0(void*, float) __asm__("_ZN22CDamageShapeDescriptor6updateEf");
TL_ORIGINAL(void, original1, (void*, void*), "_ZN22CDamageShapeDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate1(void*, void*) __asm__("_ZN22CDamageShapeDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original2, (void*, void*), "_ZN19CTimelineDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate2(void*, void*) __asm__("_ZN19CTimelineDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original3, (void*, void*), "_ZN22CRandomGroupDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate3(void*, void*) __asm__("_ZN22CRandomGroupDescriptor24descriptorSceneActivatedEP12CEditorScene");
TL_ORIGINAL(void, original4, (void*, float), "_ZN22CEditorImageDescriptor6updateEf")
extern "C" void candidate4(void*, float) __asm__("_ZN22CEditorImageDescriptor6updateEf");
TL_ORIGINAL(void, original5, (void*, float), "_ZN23CEditorButtonDescriptor6updateEf")
extern "C" void candidate5(void*, float) __asm__("_ZN23CEditorButtonDescriptor6updateEf");
TL_ORIGINAL(void, original6, (void*, void*), "_ZN26CAnimationPlayerDescriptor24descriptorSceneActivatedEP12CEditorScene")
extern "C" void candidate6(void*, void*) __asm__("_ZN26CAnimationPlayerDescriptor24descriptorSceneActivatedEP12CEditorScene");
extern "C" void* animationTable[] __asm__("_ZTV16CAnimationPlayer");
TL_FUNCTION(playTarget,"_ZN16CAnimationPlayer13playAnimationEb")
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" void* damageTable[] __asm__("_ZTV12CDamageShape");
extern "C" void* timelineTable[] __asm__("_ZTV9CTimeline");
extern "C" void* randomTable[] __asm__("_ZTV12CRandomGroup");
TL_FUNCTION(editorTarget,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(timelineTarget,"_ZN9CTimeline10SetEnabledEb")
TL_FUNCTION(childrenTarget,"_ZN12CEditorScene18setChildrenVisibleExb")
TL_FUNCTION(imageTarget,"_ZN12CEditorImage6updateEf")
namespace {
struct Case { unsigned op,layout,editor,mutation; float elapsed; };
const Case* input; autotest::Capture* cap;
void* descriptor;void* scene;void* resource;void* objects[4];unsigned calls,queries,enabledQueries;
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void num(unsigned n){cap->add(&n,sizeof(n));}
void pointer(void* p,unsigned off,void* v){std::memcpy(static_cast<char*>(p)+off,&v,sizeof(v));}
void expect(void* p,unsigned off,void* v){void* a=0;std::memcpy(&a,static_cast<char*>(p)+off,sizeof(a));if(a!=v)invalid();}
unsigned identity(void* p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==objects[i])return i+1;return 99;}
void call(void* p){unsigned id=identity(p);if(id==99)invalid();num(id);++calls;if(p)static_cast<unsigned char*>(p)[0x182]^=calls;if(input->mutation==1&&calls==1){unsigned z=0;std::memcpy(static_cast<char*>(descriptor)+0xe8,&z,4);}}
bool editor(void* p){if(p!=resource)invalid();++queries;num(100);return input->editor!=0;}
bool enabled(void* p){if(identity(p)==99)invalid();++enabledQueries;num(101);num(identity(p));return static_cast<unsigned char*>(p)[0x82]!=0;}
void setEnabled(void* p,bool v){num(102);num(v);call(p);static_cast<unsigned char*>(p)[0x82]=v;}
void play(void* p,bool v){num(107);num(v);if(!v)invalid();call(p);}
void timelineEnabled(void* p,bool v){num(103);num(v);if(v!=(identity(p)!=2))invalid();call(p);static_cast<unsigned char*>(p)[0xa1]=v;}
long long damageUpdate(void* p,float dt,void* camera,const void* zero){num(104);if(camera)invalid();const uint32_t* xyz=static_cast<const uint32_t*>(zero);if(xyz[0]||xyz[1]||xyz[2])invalid();cap->add(&dt,4);if(std::memcmp(&dt,&input->elapsed,4))invalid();call(p);return 0x123456789LL;}
void children(void* p,long long id,bool visible){num(105);if(p!=scene||visible)invalid();unsigned who=99;for(unsigned i=0;i<4;++i){long long a=0;std::memcpy(&a,static_cast<char*>(objects[i])+0x10,8);if(a==id)who=i+1;}if(who==99){invalid();return;}num(who);call(objects[who-1]);}
void image(void* p,float dt){num(106);cap->add(&dt,4);if(std::memcmp(&dt,&input->elapsed,4))invalid();call(p);}
void side(Case& c,bool ours,autotest::Capture& out){
 input=&c;cap=&out;calls=queries=enabledQueries=0;
 uint64_t descBytes[48]={0},objectBytes[4][128]={{0}},sceneBytes[24]={0},resourceBytes[8]={0};
 void* array[6]={0};void* table[65]={0};descriptor=descBytes;scene=sceneBytes;resource=resourceBytes;
 void** originalTable=c.op<2?damageTable:c.op==2?timelineTable:c.op==6?animationTable:randomTable;
 std::memcpy(table,originalTable,sizeof(table));table[2+0x40/8]=reinterpret_cast<void*>(&setEnabled);table[2+0x48/8]=reinterpret_cast<void*>(&enabled);table[2+0x1d8/8]=reinterpret_cast<void*>(&damageUpdate);
 for(unsigned i=0;i<4;++i){objects[i]=objectBytes[i];pointer(objects[i],0,i==3?baseTable+2:table+2);long long id=0x1234567890000LL+i;std::memcpy(static_cast<char*>(objects[i])+0x10,&id,8);static_cast<unsigned char*>(objects[i])[0x82]=i!=1;static_cast<unsigned char*>(objects[i])[0x81]=i!=1;static_cast<unsigned char*>(objects[i])[0x8a]=i!=1;static_cast<unsigned char*>(objects[i])[0x90]=i!=1;}
 unsigned count=0,capacity=6;
 switch(c.layout){case 0:break;case 1:count=1;array[0]=objects[0];break;case 2:count=1;break;case 3:count=1;array[0]=objects[3];break;case 4:count=6;array[0]=objects[0];array[1]=0;array[2]=objects[3];array[3]=objects[1];array[4]=objects[2];array[5]=objects[0];break;case 5:count=4;capacity=2;array[0]=objects[0];array[1]=objects[1];break;case 6:count=4;capacity=0;array[0]=objects[2];break;case 7:count=6;array[0]=objects[1];array[1]=objects[2];array[2]=objects[0];array[3]=objects[2];array[4]=objects[1];array[5]=objects[0];break;}
 unsigned expected=0,expectedEnabled=0,expectedCount=count;
 for(unsigned i=0;i<expectedCount;++i){void* p=array[i<capacity?i:0];if((c.op<4||c.op==6)&&(!p||p==objects[3]))continue;if(c.op==1){if(c.editor)continue;++expectedEnabled;if(p==objects[1])continue;expected+=2;}else if(c.op==6){if(c.editor||p==objects[1])continue;++expected;}else if(c.op==3){if(p!=objects[1])continue;++expected;}else ++expected;if(c.mutation==1&&expected)expectedCount=0;}
 pointer(descriptor,0xe0,array);pointer(descriptor,0x48,scene);std::memcpy(static_cast<char*>(descriptor)+0xe8,&count,4);std::memcpy(static_cast<char*>(descriptor)+0xec,&capacity,4);pointer(scene,0x68,resource);
 detour::Set d;TL_REDIRECT(d,editorTarget,&editor);if(c.op==2)TL_REDIRECT(d,timelineTarget,&timelineEnabled);if(c.op==3)TL_REDIRECT(d,childrenTarget,&children);if(c.op==4||c.op==5)TL_REDIRECT(d,imageTarget,&image);if(c.op==6)TL_REDIRECT(d,playTarget,&play);if(d.failed()){invalid();return;}
 switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,descriptor,c.elapsed);break;case 1:autotest::invoke(out,ours?candidate1:original1,descriptor,scene);break;case 2:autotest::invoke(out,ours?candidate2:original2,descriptor,scene);break;case 3:autotest::invoke(out,ours?candidate3:original3,descriptor,scene);break;case 4:autotest::invoke(out,ours?candidate4:original4,descriptor,c.elapsed);break;case 5:autotest::invoke(out,ours?candidate5:original5,descriptor,c.elapsed);break;case 6:autotest::invoke(out,ours?candidate6:original6,descriptor,scene);break;}
 if(calls!=expected||queries!=((c.op==1||c.op==6)?1u:0u)||enabledQueries!=expectedEnabled)invalid();num(calls);num(queries);num(enabledQueries);
 expect(descriptor,0xe0,array);expect(descriptor,0x48,scene);pointer(descriptor,0xe0,0);pointer(descriptor,0x48,0);out.add(descriptor,sizeof(descBytes));
 for(unsigned i=0;i<4;++i){expect(objects[i],0,i==3?baseTable+2:table+2);pointer(objects[i],0,0);out.add(objects[i],sizeof(objectBytes[i]));}
 for(unsigned i=0;i<6;++i)num(array[i]?identity(array[i]):0);expect(scene,0x68,resource);pointer(scene,0x68,0);out.add(scene,sizeof(sceneBytes));out.add(resource,sizeof(resourceBytes));
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);const uint32_t times[]={0,0x3c888889,0xbf800000,0x7fc12345};for(unsigned layout=0;layout<8;++layout)for(unsigned editor=0;editor<2;++editor)for(unsigned mutation=0;mutation<2;++mutation){Case c={operation,layout,editor,mutation,0};std::memcpy(&c.elapsed,&times[(layout+editor+mutation)%4],4);autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    followup traversal %u layout %u editor %u mutation %u exit %d/%d issue %u/%u bytes %lu/%lu\n",operation,layout,editor,mutation,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed==32?0:1;}
}
TL_TEST(damage_descriptor_update) { return run(host,0,"damage_descriptor_update",reinterpret_cast<uintptr_t>(&original0)); }
TL_TEST(damage_descriptor_activate) { return run(host,1,"damage_descriptor_activate",reinterpret_cast<uintptr_t>(&original1)); }
TL_TEST(timeline_descriptor_activate) { return run(host,2,"timeline_descriptor_activate",reinterpret_cast<uintptr_t>(&original2)); }
TL_TEST(random_group_descriptor_activate) { return run(host,3,"random_group_descriptor_activate",reinterpret_cast<uintptr_t>(&original3)); }
TL_TEST(image_descriptor_update) { return run(host,4,"image_descriptor_update",reinterpret_cast<uintptr_t>(&original4)); }
TL_TEST(button_descriptor_update) { return run(host,5,"button_descriptor_update",reinterpret_cast<uintptr_t>(&original5)); }
TL_TEST(animation_descriptor_start_on_load) {return run(host,6,"animation_descriptor_start_on_load",reinterpret_cast<uintptr_t>(&original6));}
