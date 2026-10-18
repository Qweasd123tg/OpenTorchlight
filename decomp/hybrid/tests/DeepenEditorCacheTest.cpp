#include <map>
#include <string>
#include "AutoTest.h"
#include "DescriptorController.h"
#include "DescriptorRegistry.h"
#include "EditorBaseObject.h"
#define private public
#include "TArrayList.h"
#undef private
TL_ORIGINAL(void,dcOld,(const std::wstring&,CEditorBaseObject*),"_ZN21CDescriptorController19returnCarchedObjectERKSbIwSt11char_traitsIwESaIwEEP17CEditorBaseObject")
extern "C" void dcNew(const std::wstring&,CEditorBaseObject*) __asm__("_ZN21CDescriptorController19returnCarchedObjectERKSbIwSt11char_traitsIwESaIwEEP17CEditorBaseObject");
namespace {
struct Case{unsigned seed;};autotest::Capture*cap;std::wstring key;unsigned callbacks;
void n(unsigned x){cap->add(&x,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}
struct Probe:public CEditorBaseObject{unsigned id;Probe():id(0){}virtual void removedFromSceneAndAddedToCache(){++callbacks;n(7);n(id);std::map<std::wstring,TArrayList<CEditorBaseObject*>*>::iterator i=g_CachedObjects.find(key);if(i==g_CachedObjects.end()||!i->second||i->second->size()==0||(*i->second)[i->second->size()-1]!=this)invalid();}};
void clean(){for(std::map<std::wstring,TArrayList<CEditorBaseObject*>*>::iterator i=g_CachedObjects.begin();i!=g_CachedObjects.end();++i)delete i->second;g_CachedObjects.clear();}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=static_cast<Case*>(raw)->seed;cap=&out;callbacks=0;clean();Probe objects[3];for(unsigned i=0;i<3;++i)objects[i].id=i+1;key=seed%3==0?L"":seed%3==1?L"Key":L"Ж";TArrayList<CEditorBaseObject*>*other=new TArrayList<CEditorBaseObject*>(2);other->add(&objects[2]);g_CachedObjects[L"untouched"]=other;
 if(seed&1){TArrayList<CEditorBaseObject*>*list=new TArrayList<CEditorBaseObject*>(1000);unsigned count=seed%5==0?1000:seed%5==1?999:seed%5;for(unsigned i=0;i<count;++i)list->add(&objects[i%3]);g_CachedObjects[key]=list;}
 CEditorBaseObject*arg=seed%7?&objects[seed%3]:NULL;typedef void(*Fn)(const std::wstring&,CEditorBaseObject*);Fn fn=ours?dcNew:dcOld;if(!autotest::beginInvocation(out,fn))return;fn(key,arg);out.callCompleted=1;if(callbacks!=unsigned(arg!=NULL))invalid();n(callbacks);n(g_CachedObjects.size());for(std::map<std::wstring,TArrayList<CEditorBaseObject*>*>::iterator i=g_CachedObjects.begin();i!=g_CachedObjects.end();++i){out.addText(i->first);TArrayList<CEditorBaseObject*>*list=i->second;n(list->size());for(unsigned j=0;j<list->size();++j){unsigned id=0;for(unsigned k=0;k<3;++k)if((*list)[j]==&objects[k])id=k+1;if(!id)invalid();n(id);}}clean();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(deepen_editor_descriptor_cache){autotest::Coverage coverage("deepen_editor_descriptor_cache",(uintptr_t)&dcOld);for(unsigned seed=0;seed<48;++seed){Case c={seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("cache seed%u issue%u/%u exit%d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
