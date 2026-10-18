#include <cstring>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "Hierarchy.h"
#include "DataGroup.h"
#undef private
TL_ORIGINAL(void,dhParseOld,(CHierarchy*,CDataGroup*),"_ZN10CHierarchy13parseHierachyEP10CDataGroup")
extern "C" void dhParseNew(CHierarchy*,CDataGroup*) __asm__("_ZN10CHierarchy13parseHierachyEP10CDataGroup");
TL_ORIGINAL(void,dhCtorOld,(CHierarchy*,const wchar_t*),"_ZN10CHierarchyC1EPKw")
extern "C" void dhCtorNew(CHierarchy*,const wchar_t*) __asm__("_ZN10CHierarchyC1EPKw");
TL_ORIGINAL(void,dhDtorOld,(CHierarchy*),"_ZN10CHierarchyD1Ev")
extern "C" void dhDtorNew(CHierarchy*) __asm__("_ZN10CHierarchyD1Ev");
TL_FUNCTION(dhLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;unsigned seed,calls;bool fill;std::wstring path;
void n(unsigned v){cap->add(&v,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void tree(CDataGroup*root){if(seed%7==0)return;CDataGroup*types=root->AddDataGroup(L"UNITTYPES");const wchar_t*names[]={L"one",L"Two",L"one",L"Ж"};for(unsigned i=0;i<seed%6;++i){CDataGroup*t=types->AddDataGroup(names[i%4]);if(i%4==3&&seed&4)continue;t->AddDataValue(L"ID",unsigned(i%3+100));for(unsigned j=0;j<(seed+i)%4;++j)t->AddDataValue(j&1?L"ANCESTOR":L"PARENT",unsigned(200+j+i));}}
void load(CDataGroup*p,const std::wstring&name,CTimerStatics*t){++calls;n(1);cap->addText(name);cap->addText(p->GetGroupName());if(t||name!=path||p->m_DataValues.size()||p->m_DataGroups.size())invalid();if(fill)tree(p);}
void snapshot(CHierarchy*p){n(p->m_parentTypes.size());for(std::map<unsigned,std::vector<unsigned> >::iterator i=p->m_parentTypes.begin();i!=p->m_parentTypes.end();++i){n(i->first);n(i->second.size());for(unsigned j=0;j<i->second.size();++j)n(i->second[j]);}n(p->m_typeIDs.size());for(std::map<std::wstring,unsigned>::iterator i=p->m_typeIDs.begin();i!=p->m_typeIDs.end();++i){cap->addText(i->first);n(i->second);}n(p->m_types.size());n(p->m_types.m_nGrowBy);for(unsigned i=0;i<p->m_types.size();++i)n(p->m_types[i]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;calls=0;path=seed&1?L"synthetic/unittypes.hie":L"";uint64_t bytes[(sizeof(CHierarchy)+7)/8];CHierarchy*p=reinterpret_cast<CHierarchy*>(bytes);detour::Set d;TL_REDIRECT(d,dhLoad,&load);if(d.failed()){invalid();return;}fill=c.mode==1;
 if(c.mode==1){typedef void(*Fn)(CHierarchy*,const wchar_t*);Fn fn=ours?dhCtorNew:dhCtorOld;if(!autotest::beginInvocation(out,fn))return;fn(p,path.c_str());out.callCompleted=1;snapshot(p);n(calls);if(calls!=1)invalid();dhDtorOld(p);}
 else {fill=false;dhCtorOld(p,path.c_str());p->m_parentTypes[99].push_back(77);p->m_typeIDs[L"EXISTING"]=99;p->m_types.add(99);if(c.mode==0){CDataGroup root(L"root",NULL,2,2,NULL);tree(&root);CDataGroup*arg=seed%9==0?NULL:&root;typedef void(*Fn)(CHierarchy*,CDataGroup*);Fn fn=ours?dhParseNew:dhParseOld;if(!autotest::beginInvocation(out,fn))return;fn(p,arg);out.callCompleted=1;snapshot(p);n(calls);dhDtorOld(p);}
 else{for(unsigned i=0;i<seed%7;++i){p->m_parentTypes[200+i].push_back(i);p->m_typeIDs[std::wstring(i+1,L'x')]=i;p->m_types.add(i);}out.addHeapInUse();n(g_iTotalCountOfObjects);typedef void(*Fn)(CHierarchy*);Fn fn=ours?dhDtorNew:dhDtorOld;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;out.addHeapInUse();n(g_iTotalCountOfObjects);}}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<48;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("hierarchy mode%u seed%u issue%u/%u exit%d/%d lengths%lu/%lu\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_hierarchy_parse){return run(host,0,"deepen_editor_hierarchy_parse",(uintptr_t)&dhParseOld);}
TL_TEST(deepen_editor_hierarchy_ctor){return run(host,1,"deepen_editor_hierarchy_ctor",(uintptr_t)&dhCtorOld);}
TL_TEST(deepen_editor_hierarchy_dtor){return run(host,2,"deepen_editor_hierarchy_dtor",(uintptr_t)&dhDtorOld);}
