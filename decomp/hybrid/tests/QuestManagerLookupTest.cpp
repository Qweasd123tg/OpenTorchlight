// Real GCC 4.4.7 maps, not hand-written trees. ASM d2dca0/d2dda0.
#include <map>
#include <string>
#include <cstring>
#include <cstddef>
#include "AutoTest.h"
#define WARG (void*,const std::wstring&)
TL_ORIGINAL(char,oldComplete,WARG,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(long long,oldName,WARG,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char newComplete WARG __asm__("_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE");
extern "C" long long newName WARG __asm__("_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE");
#undef WARG
namespace quest_lookup {
typedef std::map<std::wstring,void*> Names;
typedef std::map<std::wstring,bool> Complete;
typedef std::_Rb_tree_node<Names::value_type> NameNode;
typedef std::_Rb_tree_node<Complete::value_type> CompleteNode;
typedef char NameMapSize[sizeof(Names)==48?1:-1];
typedef char CompleteMapSize[sizeof(Complete)==48?1:-1];
typedef char NodeHeaderSize[sizeof(std::_Rb_tree_node_base)==32?1:-1];
typedef char NodeValueOffset[offsetof(NameNode,_M_value_field)==32?1:-1];
typedef char CompleteValueOffset[offsetof(CompleteNode,_M_value_field)==32?1:-1];
typedef char LeftOffset[offsetof(std::_Rb_tree_node_base,_M_left)==16?1:-1];
typedef char RightOffset[offsetof(std::_Rb_tree_node_base,_M_right)==24?1:-1];
struct Case { unsigned target,shape,query,variant; };
struct NodeSnapshot { void* p; unsigned char bytes[48]; };
unsigned errors;autotest::Capture* cap;
void need(bool b){if(!b)++errors;}
void num(unsigned n){cap->add(&n,sizeof(n));}
bool same(const std::wstring& a,const std::wstring& b){if(a.size()!=b.size())return false;for(unsigned i=0;i<a.size();++i)if(a[i]!=b[i])return false;return true;}
std::wstring key(unsigned i){
 static const wchar_t* words[]={L"",L"a",L"aa",L"alpine quest with a long shared prefix 001",L"m",L"z",L"\u0416\u0443\u043a",L"\u732b\u706b"};
 if(i<8)return std::wstring(words[i]);
 if(i==8){const wchar_t w[]={L'a',0,L'b'};return std::wstring(w,3);}
 static const wchar_t* misses[]={L"0",L"ab",L"alpine quest with a long shared prefix 002",L"n",L"zz",L"\u0416",L"\u732b\u706b\u5929"};
 return std::wstring(misses[(i-9)%7]);
}
void side(void* context,autotest::Capture& out,bool candidate){
 const Case& c=*(Case*)context;cap=&out;errors=0;autotest::g_arenaUsed=0;
 unsigned char* raw=(unsigned char*)autotest::allocate(0xd0);std::memset(raw,0xa5,0xd0);void* owner=raw+16;
 Names* names=new(raw+16+0x40)Names;Complete* complete=new(raw+16+0x70)Complete;
 std::wstring keys[9];void* values[9];bool flags[9];bool present[9];
 for(unsigned i=0;i<9;++i){keys[i]=key(i);values[i]=(i+c.variant)%3?autotest::allocate(16):0;flags[i]=(i+(c.variant==2?1:0))%2;present[i]=c.shape==2||(c.shape==1&&i==(c.variant*3)%9);}
 // Reverse and scrambled insertion orders force different legitimate RB shapes.
 static const unsigned shuffled[]={4,1,7,0,3,6,8,2,5};
 for(unsigned j=0;j<9;++j){unsigned i=c.variant==0?j:c.variant==1?8-j:shuffled[j];if(present[i]){names->insert(Names::value_type(keys[i],values[i]));complete->insert(Complete::value_type(keys[i],flags[i]));}}
 need((char*)names->end()._M_node==(char*)owner+0x48);need((char*)complete->end()._M_node==(char*)owner+0x78);
 void* nameRoot=0;void* completeRoot=0;std::memcpy(&nameRoot,(char*)owner+0x50,8);std::memcpy(&completeRoot,(char*)owner+0x80,8);
 need(nameRoot==(void*)names->end()._M_node->_M_parent);need(completeRoot==(void*)complete->end()._M_node->_M_parent);
 unsigned char before[0xd0];std::memcpy(before,raw,sizeof(before));NodeSnapshot nodes[18];unsigned n=0;
 for(Names::iterator i=names->begin();i!=names->end();++i){nodes[n].p=i._M_node;std::memcpy(nodes[n++].bytes,i._M_node,48);}
 for(Complete::iterator i=complete->begin();i!=complete->end();++i){nodes[n].p=i._M_node;std::memcpy(nodes[n++].bytes,i._M_node,48);}
 std::wstring query=key(c.query);void* expected=0;unsigned expectedComplete=0;
 for(unsigned i=0;i<9;++i)if(present[i]&&same(keys[i],query)){expected=values[i];expectedComplete=flags[i];}
 if(c.target==0){typedef long long(*Fn)(void*,const std::wstring&);Fn f=candidate?&newName:&oldName;if(!autotest::beginInvocation(out,f))return;long long value=f(owner,query);out.callCompleted=1;need(value==reinterpret_cast<long long>(expected));out.addPointer(reinterpret_cast<void*>(value));}
 else {typedef char(*Fn)(void*,const std::wstring&);Fn f=candidate?&newComplete:&oldComplete;if(!autotest::beginInvocation(out,f))return;unsigned char value=f(owner,query);out.callCompleted=1;num(value);need(value==expectedComplete);}
 need(!std::memcmp(before,raw,sizeof(before)));for(unsigned i=0;i<n;++i)need(!std::memcmp(nodes[i].bytes,nodes[i].p,48));
 need(same(query,key(c.query)));num(names->size());num(complete->size());
 // Iterate only after topology bytes were independently checked unchanged.
 if(errors==0){for(Names::iterator i=names->begin();i!=names->end();++i){out.addText(i->first);out.addPointer(i->second);}for(Complete::iterator i=complete->begin();i!=complete->end();++i){out.addText(i->first);num(i->second);}}
 names->~Names();complete->~Complete();num(0x514c4f4bu);num(errors);
}
void a(void* c,autotest::Capture& o){side(c,o,false);}void b(void* c,autotest::Capture& o){side(c,o,true);}
bool good(const autotest::Capture& c){unsigned f[2];if(c.length<8)return false;std::memcpy(f,c.data+c.length-8,8);return f[0]==0x514c4f4bu&&!f[1];}
int run(const tlhybrid_host* host,unsigned target){autotest::Coverage coverage(target?"questmanager_complete_lookup":"questmanager_name_lookup",target?0xd2dca0:0xd2dda0);unsigned count=0;
 for(unsigned shape=0;shape<3;++shape)for(unsigned variant=0;variant<3;++variant)for(unsigned query=0;query<16;++query){Case c={target,shape,query,variant};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;if(coverage.observe(host,x,y)||!good(x.capture)||!good(y.capture)){host->log(" lookup target=%u shape=%u variant=%u query=%u\n",target,shape,variant,query);coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;}
}
TL_TEST(questmanager_name_lookup){return quest_lookup::run(host,0);}
TL_TEST(questmanager_complete_lookup){return quest_lookup::run(host,1);}
