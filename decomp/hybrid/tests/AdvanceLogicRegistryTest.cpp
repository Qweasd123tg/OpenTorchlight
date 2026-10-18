#include "ParentPairs.h"
#include "Descriptor.h"
#define private public
#include "DescriptorController.h"
#undef private
extern CDescriptorController originalController __asm__("_ZL22g_DescriptorController");
TL_ORIGINAL(void,oldRegister,(CDescriptor*,CDescriptorProp*,bool),"_ZN21CDescriptorController21addDescriptorPropertyEP11CDescriptorP15CDescriptorPropb")
extern "C" void newRegister(CDescriptor*,CDescriptorProp*,bool) __asm__("_ZN21CDescriptorController21addDescriptorPropertyEP11CDescriptorP15CDescriptorPropb");
namespace {
struct Descriptor:CDescriptor{Descriptor():CDescriptor(0){}virtual CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}void name(const std::wstring&s){m_sName=s;}};
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;const wchar_t*keys[]={L"",L"A",L"AA",L"AB",L"Ж",L"missing"};std::wstring query=keys[seed/7%6];if(seed%17==0){query.append(1,wchar_t(0));query+=L"tail";}Descriptor descriptor;descriptor.name(query);CDescriptorProp property(L"category",L"name",L"description",NULL,NULL,VARIABLE_TYPE_INTEGER,0);CDescriptorProp*values[]={NULL,&property,reinterpret_cast<CDescriptorProp*>(autotest::allocate(16))};typedef std::map<std::wstring,TArrayList<CDescriptorProp*>*> Cache;Cache*maps[]={&originalController.m_Properties,&originalController.m_DefaultProperties};for(unsigned j=0;j<2;++j){maps[j]->clear();for(unsigned k=0;k<5;++k)if((seed+j+k)%3){TArrayList<CDescriptorProp*>*list=new TArrayList<CDescriptorProp*>(1+seed%3);for(unsigned i=0;i<(seed+j+k)%24;++i)list->add(values[(i+k)%3]);(*maps[j])[keys[k]]=list;}}typedef void(*Fn)(CDescriptor*,CDescriptorProp*,bool);Fn fn=ours?newRegister:oldRegister;if(!autotest::beginInvocation(out,fn))return;for(unsigned r=0;r<3;++r)fn(seed%11==0?NULL:&descriptor,values[(seed+r)%3],(seed+r)&1);out.callCompleted=1;for(unsigned j=0;j<2;++j){parentpairs::scalar(out,maps[j]->size());for(Cache::iterator i=maps[j]->begin();i!=maps[j]->end();++i){out.addText(i->first);parentpairs::scalar(out,i->second->size());out.add(reinterpret_cast<char*>(i->second)+12,8);for(unsigned k=0;k<i->second->size();++k){unsigned identity=99;for(unsigned q=0;q<3;++q)if((*i->second)[k]==values[q])identity=q;parentpairs::scalar(out,identity);if(identity==99)out.issue=autotest::Capture::InvalidReport;}delete i->second;}maps[j]->clear();}}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_logic_register_property){return parentpairs::run(host,"advance_logic_register_property",(uintptr_t)oldRegister,96,a,b);}
