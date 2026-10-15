#include <string>
#include <cstring>
#include <cwctype>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
TL_ORIGINAL(unsigned int, original, (void*,void*,const std::wstring&,void*), "_ZN22CRandomGroupDescriptor24getPlayerClassIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned int candidate(void*,void*,const std::wstring&,void*) __asm__("_ZN22CRandomGroupDescriptor24getPlayerClassIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_FUNCTION(upperTarget,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(singletonTarget,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(namesTarget,"_ZN17CUnitResourceList19getPlayerClassNamesEv")
namespace {
struct Case {unsigned count,capacity,seed;std::wstring query;std::wstring names[4];unsigned long long array[3];unsigned long long resource[4];};
Case* input;autotest::Capture* capture;unsigned uppers,singletons,nameCalls;
void invalid(){capture->issue=autotest::Capture::InvalidReport;}void num(unsigned n){capture->add(&n,sizeof(n));}
std::wstring upper(const std::wstring& query){++uppers;if(&query!=&input->query)invalid();num(1);std::wstring result=query;for(unsigned i=0;i<result.size();++i)if(result[i]>=L'a'&&result[i]<=L'z')result[i]-=L'a'-L'A';return result;}
void* singleton(){++singletons;num(2);return input->resource;}
void* names(void* p){++nameCalls;num(3);if(p!=input->resource)invalid();return input->array;}
void captureString(autotest::Capture& out,const std::wstring& s){unsigned n=s.size();out.add(&n,4);out.add(s.data(),n*sizeof(wchar_t));}
void side(Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;uppers=singletons=nameCalls=0;unsigned long long originalArray[3];std::memcpy(originalArray,c.array,sizeof(originalArray));unsigned long long originalResource[4];std::memcpy(originalResource,c.resource,sizeof(originalResource));std::wstring before=c.query;std::wstring oldNames[4];for(unsigned i=0;i<4;++i)oldNames[i]=c.names[i];
 detour::Set d;TL_REDIRECT(d,upperTarget,&upper);TL_REDIRECT(d,singletonTarget,&singleton);TL_REDIRECT(d,namesTarget,&names);if(d.failed()){invalid();return;}
 unsigned int(*fn)(void*,void*,const std::wstring&,void*)=ours?candidate:original;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(reinterpret_cast<void*>(0x12345678),reinterpret_cast<void*>(0x23456789),c.query,reinterpret_cast<void*>(0x34567890));out.callCompleted=1;num(result);
 unsigned expect=0;if(!c.query.empty()){std::wstring upperQuery=c.query;for(unsigned i=0;i<upperQuery.size();++i)if(upperQuery[i]>=L'a'&&upperQuery[i]<=L'z')upperQuery[i]-=L'a'-L'A';for(unsigned i=0;i<c.count;++i)if(c.names[i<c.capacity?i:0]==upperQuery){expect=i+1;break;}}
 if(result!=expect||uppers!=(c.query.empty()?0u:1u)||singletons!=uppers||nameCalls!=uppers||c.query!=before||std::memcmp(originalArray,c.array,sizeof(originalArray))||std::memcmp(originalResource,c.resource,sizeof(originalResource)))invalid();num(uppers);num(singletons);num(nameCalls);out.add(c.array,sizeof(c.array));out.add(c.resource,sizeof(c.resource));for(unsigned i=0;i<4;++i){if(c.names[i]!=oldNames[i])invalid();captureString(out,c.names[i]);}captureString(out,c.query);
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(followup_player_class_id){autotest::Coverage coverage("followup_player_class_id",reinterpret_cast<uintptr_t>(&original));const unsigned counts[]={0,1,3,4,4,4};const unsigned capacities[]={4,4,4,4,2,0};const wchar_t* queries[]={L"",L"warrior",L"HUNTER",L"MAGE",L"MISSING",L"mage ",L"HUNTERX",L"\u041a\u043b\u0430\u0441\u0441"};for(unsigned layout=0;layout<6;++layout)for(unsigned q=0;q<8;++q){Case c;c.count=counts[layout];c.capacity=capacities[layout];c.seed=q;c.query=queries[q];c.names[0]=L"WARRIOR";c.names[1]=L"MAGE";c.names[2]=L"HUNTER";c.names[3]=L"MAGE";std::memset(c.resource,0x76,sizeof(c.resource));std::memset(c.array,0,sizeof(c.array));void* data=c.names;std::memcpy(c.array,&data,8);std::memcpy(reinterpret_cast<char*>(c.array)+8,&c.count,4);std::memcpy(reinterpret_cast<char*>(c.array)+12,&c.capacity,4);autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player class layout %u query %u exit %d/%d issue %u/%u\n",layout,q,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed==48?0:1;}
