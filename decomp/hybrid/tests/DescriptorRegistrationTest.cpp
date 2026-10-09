#include <cstring>
#include <string>
#include <stdint.h>
#define protected public
#include "Descriptor.h"
#undef protected
#include "AutoTest.h"
#include "Detour.h"
#include "DescriptorCallbackIdentity.h"
TL_ORIGINAL(void,oldButtonCtor,(void*),"_ZN23CEditorButtonDescriptorC1Ev")
TL_ORIGINAL(void,oldImageCtor,(void*),"_ZN22CEditorImageDescriptorC1Ev")
TL_ORIGINAL(void,oldMissileCtor,(void*),"_ZN18CMissileDescriptorC1Ev")
TL_ORIGINAL(void,oldIncrementCtor,(void*,const wchar_t*,const wchar_t*,const wchar_t*),"_ZN28COutputIncrementorDescriptorC1EPKwS1_S1_")
extern "C" void newButtonCtor(void*) __asm__("_ZN23CEditorButtonDescriptorC1Ev");
extern "C" void newImageCtor(void*) __asm__("_ZN22CEditorImageDescriptorC1Ev");
extern "C" void newMissileCtor(void*) __asm__("_ZN18CMissileDescriptorC1Ev");
extern "C" void newIncrementCtor(void*,const wchar_t*,const wchar_t*,const wchar_t*) __asm__("_ZN28COutputIncrementorDescriptorC1EPKwS1_S1_");
TL_FUNCTION(baseCtorFn,"_ZN21CBaseObjectDescriptorC2EPKwS1_S1_")
TL_FUNCTION(positionableCtorFn,"_ZN29CPositionableObjectDescriptorC2EPKwS1_S1_bbbbb")
TL_FUNCTION(propertyFn,"_ZN11CDescriptor11AddPropertyESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_15EVARIABLE_TYPESi")
TL_FUNCTION(interpretedFn,"_ZN11CDescriptor35AddPropertyWithInterpreterFunctionsESbIwSt11char_traitsIwESaIwEES3_S3_PvS4_PFjP12CEditorSceneP17CEditorBaseObjectRKS3_S4_EPFS3_S6_S8_jS4_ES4_15EVARIABLE_TYPESi")
TL_FUNCTION(inputFn,"_ZN11CDescriptor13AddInputLogicE13EINPUT_EVENTS")
TL_FUNCTION(outputFn,"_ZN11CDescriptor14AddOutputLogicE14EOUTPUT_EVENTS")
namespace {
struct Case {unsigned kind,flags,text,returnStyle,fill;};
autotest::Capture* capture;const Case* input;CDescriptor* descriptor;unsigned calls;
void n(unsigned x){capture->add(&x,sizeof(x));}
void ptr(void* p){uintptr_t value=callbackIdentity(p);capture->add(&value,sizeof(value));}
unsigned returned(){++calls;return input->returnStyle?0xffffffffU-calls:calls;}
void base(void* p,const wchar_t* name,const wchar_t* group,const wchar_t* description){n(1);n(p==descriptor);capture->addText(std::wstring(name));capture->addText(std::wstring(group));capture->addText(std::wstring(description));descriptor->m_iFlags=input->flags;}
void positionable(void* p,const wchar_t* name,const wchar_t* group,const wchar_t* description,bool a,bool b,bool c,bool d,bool e){n(2);base(p,name,group,description);n(a);n(b);n(c);n(d);n(e);}
unsigned property(CDescriptor* p,std::wstring category,std::wstring name,std::wstring description,void* setter,void* getter,EVARIABLE_TYPES type,int flags){n(3);n(p==descriptor);capture->addText(category);capture->addText(name);capture->addText(description);ptr(setter);ptr(getter);n(type);n(flags);n(descriptor->m_iFlags);return returned();}
unsigned interpreted(CDescriptor* p,std::wstring category,std::wstring name,std::wstring description,void* setter,void* getter,PropertyStringToIndexFunction from,PropertyIndexToStringFunction to,void* user,EVARIABLE_TYPES type,int flags){n(4);n(p==descriptor);capture->addText(category);capture->addText(name);capture->addText(description);ptr(setter);ptr(getter);ptr((void*)from);ptr((void*)to);ptr(user);n(type);n(flags);n(descriptor->m_iFlags);return returned();}
unsigned addInput(CDescriptor* p,EINPUT_EVENTS event){n(5);n(p==descriptor);n(event);return returned();}
unsigned addOutput(CDescriptor* p,EOUTPUT_EVENTS event){n(6);n(p==descriptor);n(event);return returned();}
void side(const Case& c,bool ours,autotest::Capture& out){
 capture=&out;input=&c;calls=0;uint64_t memory[128];const unsigned char fills[]={0,0x5a,0xff};memset(memory,fills[c.fill],sizeof(memory));descriptor=(CDescriptor*)memory;
 detour::Set d;TL_REDIRECT(d,baseCtorFn,&base);TL_REDIRECT(d,positionableCtorFn,&positionable);TL_REDIRECT(d,propertyFn,&property);TL_REDIRECT(d,interpretedFn,&interpreted);TL_REDIRECT(d,inputFn,&addInput);TL_REDIRECT(d,outputFn,&addOutput);if(d.failed())_exit(43);
 if(c.kind==0)autotest::invoke(out,ours?&newButtonCtor:&oldButtonCtor,(void*)descriptor);
 if(c.kind==1)autotest::invoke(out,ours?&newImageCtor:&oldImageCtor,(void*)descriptor);
 if(c.kind==2)autotest::invoke(out,ours?&newMissileCtor:&oldMissileCtor,(void*)descriptor);
 if(c.kind==3){std::wstring name=c.text==0?L"name":c.text==1?L"":c.text==2?L"\u03a9\u4e2d":std::wstring(200,L'N');std::wstring group=L"group"+name,description=L"description"+name;autotest::invoke(out,ours?&newIncrementCtor:&oldIncrementCtor,(void*)descriptor,name.c_str(),group.c_str(),description.c_str());}
 n(100);n(calls);out.add(memory,sizeof(memory));
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
int run(const tlhybrid_host* host,unsigned kind,const char* name,uint64_t address){
 autotest::Coverage coverage(name,address);unsigned flags[]={0,0x20,0x40,0x4148,0x80000000U,0xffffffffU,0x55555555U,0xaaaaaaaaU};unsigned total=0;
 for(unsigned fill=0;fill<3;++fill)for(unsigned f=0;f<8;++f)for(unsigned text=0;text<(kind==3?4U:1U);++text)for(unsigned returns=0;returns<2;++returns){Case c={kind,flags[f],text,returns,fill};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 if(pair||autotest::incomplete(x)||autotest::incomplete(y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    ctor %u flags %u text %u status %d/%d bytes %lu/%lu first %lu\n",kind,c.flags,text,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>32?first-32:0;i<first+48&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){unsigned u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %x/%x\n",(unsigned long)i,u,v);}return 1;}}
 coverage.report(host);host->log("    descriptor registration: %u cases\n",total);return 0;
}
}
TL_TEST(button_descriptor_registration){return run(host,0,"button_descriptor_registration",(uint64_t)(uintptr_t)&oldButtonCtor);}
TL_TEST(image_descriptor_registration){return run(host,1,"image_descriptor_registration",(uint64_t)(uintptr_t)&oldImageCtor);}
TL_TEST(missile_descriptor_registration){return run(host,2,"missile_descriptor_registration",(uint64_t)(uintptr_t)&oldMissileCtor);}
TL_TEST(increment_descriptor_registration){return run(host,3,"increment_descriptor_registration",(uint64_t)(uintptr_t)&oldIncrementCtor);}
