#include <string>
#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(std::wstring, original0, (void*, void*, unsigned int, void*), "_ZN22CSoundObjectDescriptor22GetSoundDataStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring candidate0(void*, void*, unsigned int, void*) __asm__("_ZN22CSoundObjectDescriptor22GetSoundDataStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned int, original1, (void*, void*, const std::wstring&, void*), "_ZN22CSoundObjectDescriptor22GetSoundDataIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate1(void*, void*, const std::wstring&, void*) __asm__("_ZN22CSoundObjectDescriptor22GetSoundDataIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring, original2, (void*, void*, unsigned int, void*), "_ZN22CSoundObjectDescriptor26GetSoundCategoryStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring candidate2(void*, void*, unsigned int, void*) __asm__("_ZN22CSoundObjectDescriptor26GetSoundCategoryStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
extern "C" void* baseTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" void* soundTable[] __asm__("_ZTV12CSoundObject");
TL_FUNCTION(singletonTarget,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(soundNameTarget,"_ZN25CSoundBankDataInformation27getSoundNameByCategoryIndexEjj")
TL_FUNCTION(soundIndexTarget,"_ZN25CSoundBankDataInformation29getSoundIndexInCategoryByNameEjRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(categoryNameTarget,"_ZN25CSoundBankDataInformation19getCategoryNameByIDEj")
namespace {
struct Case{unsigned op,layout,category,index,result,mutation;std::wstring value;};
const Case* input;autotest::Capture* output;void* object;void* masters[2];void* banks[2];unsigned singletonCalls,calls;
void num(unsigned n){output->add(&n,sizeof(n));}void invalid(){output->issue=autotest::Capture::InvalidReport;}
void pointer(void* p,unsigned off,void* v){std::memcpy(static_cast<char*>(p)+off,&v,sizeof(v));}
void expect(void* p,unsigned off,void* v){void* actual=0;std::memcpy(&actual,static_cast<char*>(p)+off,sizeof(actual));if(actual!=v)invalid();}
void* singleton(){unsigned i=input->mutation==1&&singletonCalls?1:0;++singletonCalls;num(100);num(i);return masters[i];}
void bank(void* p){unsigned id=p==banks[0]?0:p==banks[1]?1:99;if(id==99)invalid();num(id);++calls;static_cast<unsigned char*>(p)[0x10]^=calls;}
std::wstring soundName(void* p,unsigned category,unsigned index){num(101);bank(p);num(category);num(index);if(category!=input->category||index!=input->index)invalid();return input->value;}
unsigned soundIndex(void* p,unsigned category,const std::wstring& value){num(102);bank(p);num(category);if(category!=input->category||&value!=&input->value||value!=input->value)invalid();return input->result;}
std::wstring categoryName(void* p,unsigned index){num(103);bank(p);num(index);if(index!=(calls==1?input->index:0u))invalid();return calls==1?input->value:std::wstring(L"fallback category");}
void captureString(autotest::Capture& out,const std::wstring& value){unsigned n=value.size();out.add(&n,4);out.add(value.data(),n*sizeof(wchar_t));}
void side(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;singletonCalls=calls=0;uint64_t objectBytes[64]={0},masterBytes[2][64]={{0}},bankBytes[2][16]={{0}};object=c.layout==0?0:objectBytes;for(unsigned i=0;i<2;++i){masters[i]=masterBytes[i];banks[i]=bankBytes[i];pointer(masters[i],0x100,banks[i]);}
 pointer(objectBytes,0,c.layout==2?baseTable+2:soundTable+2);std::memcpy(reinterpret_cast<char*>(objectBytes)+0x110,&c.category,4);
 detour::Set d;TL_REDIRECT(d,singletonTarget,&singleton);TL_REDIRECT(d,soundNameTarget,&soundName);TL_REDIRECT(d,soundIndexTarget,&soundIndex);TL_REDIRECT(d,categoryNameTarget,&categoryName);if(d.failed()){invalid();return;}
 void* scene=reinterpret_cast<void*>(0x34567890);void* user=reinterpret_cast<void*>(0x45678901);
 if(c.op==0){std::wstring (*fn)(void*,void*,unsigned int,void*)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(scene,object,c.index,user);out.callCompleted=1;captureString(out,value);if(value!=(c.layout==1?c.value:std::wstring()))invalid();}
 else if(c.op==1){unsigned int(*fn)(void*,void*,const std::wstring&,void*)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(scene,object,c.value,user);out.callCompleted=1;num(result);if(result!=(c.layout==1&&c.result!=0xffffffff?c.result:0u))invalid();}
 else {std::wstring (*fn)(void*,void*,unsigned int,void*)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(scene,object,c.index,user);out.callCompleted=1;captureString(out,value);if(value!=(c.value.empty()?std::wstring(L"fallback category"):c.value))invalid();}
 unsigned expected=c.op<2?(c.layout==1?1:0):(c.value.empty()?2:1);if(calls!=expected||singletonCalls!=expected)invalid();num(calls);num(singletonCalls);expect(objectBytes,0,c.layout==2?baseTable+2:soundTable+2);pointer(objectBytes,0,0);out.add(objectBytes,sizeof(objectBytes));for(unsigned i=0;i<2;++i){expect(masters[i],0x100,banks[i]);pointer(masters[i],0x100,0);out.add(masters[i],sizeof(masterBytes[i]));out.add(banks[i],sizeof(bankBytes[i]));}captureString(out,c.value);
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);const unsigned categories[]={0,1,0xffffffff,0x80000000};const unsigned indices[]={0,2,0xffffffff,0x80000000};const wchar_t* values[]={L"",L"SOUND",L"audio",L"Тест"};for(unsigned n=0;n<48;++n){Case c;c.op=operation;c.layout=n%3;c.category=categories[(n/3)%4];c.index=indices[(n/6)%4];c.result=indices[(n/3)%4];c.mutation=n/24;c.value=values[(n/3)%4];autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    sound converter %u case %u exit %d/%d issue %u/%u bytes %lu/%lu\n",operation,n,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed==48?0:1;}
}
TL_TEST(followup_sound_data_name) {return run(host,0,"followup_sound_data_name",reinterpret_cast<uintptr_t>(&original0));}
TL_TEST(followup_sound_data_index) {return run(host,1,"followup_sound_data_index",reinterpret_cast<uintptr_t>(&original1));}
TL_TEST(followup_sound_category_name) {return run(host,2,"followup_sound_category_name",reinterpret_cast<uintptr_t>(&original2));}
