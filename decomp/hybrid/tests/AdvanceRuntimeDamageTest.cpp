#include "SmallMassCompare.h"
#include "TArrayList.h"
#include <cstdio>
TL_ORIGINAL(void,damageCtorOld,(void*,void*),"_ZN12CDamageShapeC1EP16CResourceManager")
TL_ORIGINAL(void,damageDtorOld,(void*),"_ZN12CDamageShapeD1Ev")
TL_ORIGINAL(void,damageEnabledOld,(void*,bool),"_ZN12CDamageShape10setEnabledEb")
TL_ORIGINAL(void,formationSaveOld,(void*,FILE*),"_ZN25CFormationNodeSaveAndLoad17saveFormationNodeEP8_IO_FILE")
TL_ORIGINAL(void,formationLoadOld,(void*,FILE*),"_ZN25CFormationNodeSaveAndLoad17loadFormationNodeEP8_IO_FILE")
extern "C" void damageCtorNew(void*,void*) __asm__("_ZN12CDamageShapeC1EP16CResourceManager");
extern "C" void damageDtorNew(void*) __asm__("_ZN12CDamageShapeD1Ev");
extern "C" void damageEnabledNew(void*,bool) __asm__("_ZN12CDamageShape10setEnabledEb");
extern "C" void formationSaveNew(void*,FILE*) __asm__("_ZN25CFormationNodeSaveAndLoad17saveFormationNodeEP8_IO_FILE");
extern "C" void formationLoadNew(void*,FILE*) __asm__("_ZN25CFormationNodeSaveAndLoad17loadFormationNodeEP8_IO_FILE");
TL_FUNCTION(damageShapeCtor,"_ZN6CShapeC1EP16CResourceManager")
TL_FUNCTION(damageShapeDtor,"_ZN6CShapeD1Ev")
TL_FUNCTION(damageEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(damageEnableCall,"_ZN12CDamageShape10setEnabledEb")
TL_FUNCTION(damageVisibleCall,"_ZN16CSceneNodeObject10setVisibleEb")
TL_FUNCTION(damageGraphCall,"_ZN16CResourceManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(damageRemove,"_ZN6CLevel29removeCharacterUpdateListenerEP22iLevelUpdatedCharacter")
TL_FUNCTION(damageAdd,"_ZN6CLevel26addCharacterUpdateListenerEP22iLevelUpdatedCharacter")
TL_FUNCTION(damageInstant,"_ZN12CDamageShape15doInstantDamageEv")
TL_FUNCTION(damageVisual,"_ZN6CShape12updateVisualEbf")
TL_FUNCTION(damageMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(damageSetting,"_ZN20CDynamicPropertyFile6GetIntEj")
namespace {
using namespace smallmass;void* resources;void* masterObject;void* token;unsigned calls;unsigned editorCalls;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void shapeCtor(void* p,void* r){record(1,p);pointer(r);field<void*>(p,0x68)=r;}
void shapeDtor(void* p){record(2,p);}
bool editor(void* p){record(3,p);return input->index%7==0 || (++editorCalls>1 && input->index&32);}
void enabled(void* p,bool e){record(4,p);number(e);}
void visible(void* p,bool v){record(5,p);number(v);}
void* graph(void* p,const std::wstring& n){record(6,p);text(n);return input->index&1?token:0;}
void remove(void* p,void* listener){record(7,p);pointer(listener);}
void add(void* p,void* listener){record(8,p);pointer(listener);}
void instant(void* p){record(9,p);}
void visual(void* p,bool v,float t){record(10,p);number(v);floating(t);}
void* master(){record(11,masterObject);return masterObject;}
int setting(void* p,unsigned key){record(12,p);number(key);return input->index&8;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=editorCalls=0;autotest::g_arenaUsed=0;void* self=object(c.op<3?0x200:0x38);resources=object(0x48);masterObject=object(0x190);token=object(0x20);void* level=object(0x20);field<void*>(resources,0x18)=c.index&1?level:0;field<void*>(masterObject,0x90)=token;
 if(c.op<3){field<void*>(self,0x68)=resources;void** table=static_cast<void**>(object(0x50));table[0x40/8]=reinterpret_cast<void*>(&enabled);field<void*>(self,0)=table;void** listeners=c.index&2?new void*[4]:0;void** targets=c.index&4?new void*[5]:0;list(self,0x1c8,listeners,listeners?2:0,listeners?4:0);list(self,0x1e0,targets,targets?3:0,targets?5:0);field<int>(self,0x1ac)=int(c.index%5)-2;field<int>(self,0x1b0)=61;field<float>(self,0x19c)=c.index%4==0?bits(0x7fc00000):float(int(c.index%3)-1)*.25f;field<bool>(self,0x1a5)=c.index&16;field<bool>(self,0x180)=true;field<bool>(self,0x1a6)=true;
 detour::Set d;TL_REDIRECT(d,damageShapeCtor,&shapeCtor);TL_REDIRECT(d,damageShapeDtor,&shapeDtor);TL_REDIRECT(d,damageEditor,&editor);TL_REDIRECT(d,damageVisibleCall,&visible);TL_REDIRECT(d,damageGraphCall,&graph);TL_REDIRECT(d,damageRemove,&remove);TL_REDIRECT(d,damageAdd,&add);TL_REDIRECT(d,damageInstant,&instant);TL_REDIRECT(d,damageVisual,&visual);TL_REDIRECT(d,damageMaster,&master);TL_REDIRECT(d,damageSetting,&setting);if(c.op==0)TL_REDIRECT(d,damageEnableCall,&enabled);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){autotest::invoke(out,ours?damageCtorNew:damageCtorOld,self,resources);pointer(field<void*>(self,0x178));out.add(static_cast<char*>(self)+0x180,1);out.add(static_cast<char*>(self)+0x184,37);out.add(static_cast<char*>(self)+0x1ac,28);number(field<unsigned>(self,0x1d0));number(field<unsigned>(self,0x1d4));number(field<unsigned>(self,0x1d8));number(field<unsigned>(self,0x1e8));number(field<unsigned>(self,0x1ec));number(field<unsigned>(self,0x1f0));number(field<unsigned>(self,0x1f8));delete[] listeners;delete[] targets;}
 else if(c.op==1){autotest::invoke(out,ours?damageDtorNew:damageDtorOld,self);number(field<void*>(self,0x1c8)!=0);number(field<unsigned>(self,0x1d0));number(field<unsigned>(self,0x1d4));number(field<void*>(self,0x1e0)!=0);number(field<unsigned>(self,0x1e8));}
 else{autotest::invoke(out,ours?damageEnabledNew:damageEnabledOld,self,bool(c.index&2));number(field<bool>(self,0x82));floating(field<float>(self,0x194));floating(field<float>(self,0x198));floating(field<float>(self,0x19c));number(field<unsigned>(self,0x1b0));number(field<bool>(self,0x180));number(field<bool>(self,0x1a6));number(field<unsigned>(self,0x1e8));number(field<unsigned>(self,0x1ec));delete[] field<void**>(self,0x1c8);delete[] field<void**>(self,0x1e0);}
 number(calls);
 }else{
 std::wstring name=c.index%4==0?L"":c.index%4==1?L"Formation/Юникод.layout":c.index%4==2?std::wstring(L"A\0B",3):std::wstring(c.index,L'Z');new(static_cast<char*>(self)+0x18)std::wstring(c.op==3?name:L"PREVIOUS");field<float>(self,0x2c)=c.index*.125f;field<float>(self,0x30)=-.25f;field<float>(self,0x34)=bits(c.index&1?0x80000000:0x7fc00000);FILE* f=tmpfile();if(!f){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==3){autotest::invoke(out,ours?formationSaveNew:formationSaveOld,self,f);long length=ftell(f);number(length);rewind(f);unsigned char bytes[1024];size_t size=fread(bytes,1,sizeof(bytes),f);number(size);out.add(bytes,size);}
 else{unsigned length=name.length();fwrite(&length,4,1,f);for(unsigned i=0;i<length;++i){unsigned short value=name[i];fwrite(&value,2,1,f);}float values[3]={float(c.index)+.5f,-2.5f,3.75f};fwrite(values,1,c.index%4==0?c.index%13:12,f);rewind(f);autotest::invoke(out,ours?formationLoadNew:formationLoadOld,self,f);text(field<std::wstring>(self,0x18));out.add(static_cast<char*>(self)+0x2c,12);number(ftell(f));}
 fclose(f);field<std::wstring>(self,0x18).~basic_string();
 }
}
}
TL_TEST(advance_runtime_damage_ctor){return smallmass::run(host,0,"advance_runtime_damage_ctor",(uintptr_t)damageCtorOld,execute,84);}
TL_TEST(advance_runtime_damage_dtor){return smallmass::run(host,1,"advance_runtime_damage_dtor",(uintptr_t)damageDtorOld,execute,84);}
TL_TEST(advance_runtime_damage_enabled){return smallmass::run(host,2,"advance_runtime_damage_enabled",(uintptr_t)damageEnabledOld,execute,126);}
TL_TEST(advance_runtime_formation_save){return smallmass::run(host,3,"advance_runtime_formation_save",(uintptr_t)formationSaveOld,execute,48);}
TL_TEST(advance_runtime_formation_load){return smallmass::run(host,4,"advance_runtime_formation_load",(uintptr_t)formationLoadOld,execute,48);}
