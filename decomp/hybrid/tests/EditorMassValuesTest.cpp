// Scalar, reference, string-buffer and mod-list comparisons against the original.
// The reference ABI adapter passes addresses, including intentionally aliased outputs.
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Settings.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" wchar_t editorString[1000] __asm__("sEditorString");
TL_ORIGINAL(void,original0,(int*,int*,int*,bool),"_Z18EditorAmbientColorRiS_S_b")
extern "C" void candidate0(int*,int*,int*,bool) __asm__("_Z18EditorAmbientColorRiS_S_b");
TL_ORIGINAL(void,original1,(int*,int*,int*,bool),"_Z21EditorDiretionalColorRiS_S_b")
extern "C" void candidate1(int*,int*,int*,bool) __asm__("_Z21EditorDiretionalColorRiS_S_b");
TL_ORIGINAL(void,original2,(int*,int*,int*,bool),"_Z26EditorMaterialAmbientColorRiS_S_b")
extern "C" void candidate2(int*,int*,int*,bool) __asm__("_Z26EditorMaterialAmbientColorRiS_S_b");
TL_ORIGINAL(void,original3,(long long,wchar_t*),"_Z19EditorSetObjectNamexPw")
extern "C" void candidate3(long long,wchar_t*) __asm__("_Z19EditorSetObjectNamexPw");
TL_ORIGINAL(wchar_t*,original4,(long long),"_Z19EditorGetObjectNamex")
extern "C" wchar_t* candidate4(long long) __asm__("_Z19EditorGetObjectNamex");
TL_ORIGINAL(void,original5,(const wchar_t*,bool),"_Z13SetModEnabledPKwb")
extern "C" void candidate5(const wchar_t*,bool) __asm__("_Z13SetModEnabledPKwb");
TL_FUNCTION(target_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(target_ambient,"_ZN7CEditor15setAmbientColorEiii")
TL_FUNCTION(target_directional,"_ZN7CEditor19setDirectionalColorEiii")
TL_FUNCTION(target_material,"_ZN7CEditor23setMaterialAmbientColorEiii")
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_getMods,"_ZN14CModFileFilter12getSingletonEv")

namespace {
struct Case{unsigned operation,mode,text,match,count;long long guid;int value;bool write,alias;};
const Case* input;autotest::Capture* capture;unsigned calls;void* editors[2];void* settings[2];void* object;void* mods;
void number(unsigned n){capture->add(&n,4);}
unsigned identity(void*p){return !p?0:p==editors[0]?1:p==editors[1]?2:p==settings[0]?3:p==settings[1]?4:p==object?5:p==mods?6:99;}
void event(unsigned code,void*p){number(code);number(identity(p));}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
int getInt(void*p,unsigned key){event(1,p);number(key);++calls;if(input->mode==4)editorGlobal=editors[calls%2];return static_cast<int>(key^static_cast<unsigned>(input->value));}
void color(unsigned code,void*p,int r,int g,int b){event(code,p);capture->add(&r,4);capture->add(&g,4);capture->add(&b,4);}
void ambient(void*p,int r,int g,int b){color(2,p,r,g,b);}
void directional(void*p,int r,int g,int b){color(3,p,r,g,b);}
void material(void*p,int r,int g,int b){color(4,p,r,g,b);}
void* lookup(long long id){number(5);capture->add(&id,8);if(input->mode==4)editorGlobal=editors[1];return input->mode==3?NULL:object;}
void* getMods(){event(6,mods);return input->mode==4?reinterpret_cast<void*>(-24LL):mods;}
void setName(void*p,const std::wstring&v){event(7,p);capture->addText(v);*reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x40)=v;}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;calls=0;
 unsigned long long editor[2][64]={{0}},setting[2][64]={{0}},objectBytes[16]={0},modManager[16]={0},modBytes[6][16]={{0}};
 void* modPointers[6];void* vtable[8]={0};vtable[4]=reinterpret_cast<void*>(&setName);
 object=objectBytes;mods=modManager;pointerAt(object,0,vtable);
 for(unsigned i=0;i<2;++i){editors[i]=editor[i];settings[i]=setting[i];reinterpret_cast<char*>(editor[i])[0x49]=c.mode==1;
  pointerAt(editor[i],0x58,c.mode==2?NULL:setting[i]);pointerAt(editor[i],0x50,setting[i]);}
 editorGlobal=editors[0];
 unsigned* keys[]={&KSETTINGS_AMBIENT_LIGHT_RED,&KSETTINGS_AMBIENT_LIGHT_GREEN,&KSETTINGS_AMBIENT_LIGHT_BLUE,
  &KSETTINGS_DIRECTIONAL_LIGHT_RED,&KSETTINGS_DIRECTIONAL_LIGHT_GREEN,&KSETTINGS_DIRECTIONAL_LIGHT_BLUE,
  &KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED,&KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN,&KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE};
 for(unsigned i=0;i<9;++i)*keys[i]=0xf0000000u+37*i+c.text;
 std::wstring name;
 switch(c.text%7){case 0:name=L"";break;case 1:name=L"test";break;case 2:name=L"Тест Ω";break;case 3:name=std::wstring(999,L'z');break;
  case 4:name=std::wstring(1000,L'a');break;case 5:name=std::wstring(1024,L'b');break;default:name=std::wstring(L"a\0b",3);break;}
 std::wstring* objectName=::new(static_cast<char*>(object)+0x40)std::wstring(name);
 std::memset(editorString,0x5a,sizeof(editorString));
 for(unsigned i=0;i<6;++i){modPointers[i]=modBytes[i];::new(reinterpret_cast<char*>(modBytes[i])+0x50)std::wstring(i==c.match||i==c.match+1?name:L"other");reinterpret_cast<char*>(modBytes[i])[0x70]=!c.write;}
 pointerAt(mods,0x18,modPointers);unsigned count=c.count,capacity=c.mode==6?2:6;
 std::memcpy(static_cast<char*>(mods)+0x20,&count,4);std::memcpy(static_cast<char*>(mods)+0x24,&capacity,4);
 int values[]={c.value,c.value/2,static_cast<int>(~static_cast<unsigned>(c.value))};
 detour::Set patches;
 TL_REDIRECT(patches,target_getInt,&getInt);
 TL_REDIRECT(patches,target_ambient,&ambient);
 TL_REDIRECT(patches,target_directional,&directional);
 TL_REDIRECT(patches,target_material,&material);
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_getMods,&getMods);
 if(patches.failed())_exit(41);
 switch(c.operation){
 case 0:autotest::invoke(out,ours?&candidate0:&original0,&values[0],c.alias?&values[0]:&values[1],c.alias?&values[0]:&values[2],c.write);break;
 case 1:autotest::invoke(out,ours?&candidate1:&original1,&values[0],c.alias?&values[0]:&values[1],c.alias?&values[0]:&values[2],c.write);break;
 case 2:autotest::invoke(out,ours?&candidate2:&original2,&values[0],c.alias?&values[0]:&values[1],c.alias?&values[0]:&values[2],c.write);break;
 case 3:autotest::invoke(out,ours?&candidate3:&original3,c.guid,c.mode==5?NULL:const_cast<wchar_t*>(name.c_str()));break;
 case 4:{wchar_t*(*fn)(long long)=ours?&candidate4:&original4;if(!autotest::beginInvocation(out,fn))return;wchar_t* result=fn(c.guid);out.callCompleted=1;number(!result?0:result==editorString?1:99);break;}
 case 5:autotest::invoke(out,ours?&candidate5:&original5,name.c_str(),c.write);break;

 }
 out.add(values,sizeof(values));out.add(editorString,sizeof(editorString));out.addText(*objectName);number(calls);number(identity(editorGlobal));
 for(unsigned i=0;i<6;++i){out.add(reinterpret_cast<char*>(modBytes[i])+0x70,8);std::wstring* s=reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(modBytes[i])+0x50);out.addText(*s);s->~basic_string();}
 objectName->~basic_string();patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(editor_mass_values_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5};

 const int integers[]={0,1,-1,255,256,2147483647,(-2147483647-1)};
 for(unsigned operation=0;operation<6;++operation){autotest::Coverage coverage("editor_mass_values_differential",addresses[operation]);
  for(unsigned n=0;n<588;++n){Case c={operation,n%7,(n/7)%7,(n/49)%7,(n/7)%7,static_cast<long long>(n)*0x123456789LL,integers[(n/49)%7],((n/7)%2)!=0,((n/49)%2)!=0};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    editor values operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }coverage.report(host);
 }return 0;
}
