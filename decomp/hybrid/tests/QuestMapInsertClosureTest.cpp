// Direct actual-definition closure for the existing weak helper at 0xd344d0.
// GCC 4.4 COW wstring + genuine std::map node/header ABI; no copied helper.
#include <map>
#include <string>
#include <cstdlib>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
typedef std::map<std::wstring,bool> QMap;
typedef QMap::value_type QValue;
typedef std::_Rb_tree_node_base QBase;
typedef std::_Rb_tree_node<QValue> QNode;
typedef QMap::iterator QIterator;
#define INSERT_SYMBOL "_ZNSt8_Rb_treeISbIwSt11char_traitsIwESaIwEESt4pairIKS3_bESt10_Select1stIS6_ESt4lessIS3_ESaIS6_EE10_M_insert_EPKSt18_Rb_tree_node_baseSF_RKS6_"
TL_ORIGINAL(QIterator, oldInsert, (void*,const QBase*,const QBase*,const QValue&), INSERT_SYMBOL)
extern "C" QIterator newInsert(void*,const QBase*,const QBase*,const QValue&) __asm__(INSERT_SYMBOL);
extern "C" char nodeNew[] __asm__("_Znwm");
extern "C" char nodeDelete[] __asm__("_ZdlPv");
extern "C" char wideCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
namespace {
typedef char MapSize[sizeof(QMap)==48?1:-1];
typedef char NodeSize[sizeof(QNode)==48?1:-1];
typedef char BaseSize[sizeof(QBase)==32?1:-1];
typedef char WideSize[sizeof(std::wstring)==8?1:-1];
typedef char IteratorSize[sizeof(QIterator)==8?1:-1];
struct Case { unsigned shape,key,value,forced,fault; };
struct CopyFailure {};
autotest::Capture* cap;unsigned errors,allocations,deletions,copies,fault;
void* allocated;QBase* known[40];unsigned knownCount,visitedCount;bool visited[40];
std::wstring expectedKeys[40];bool expectedValues[40];unsigned expectedCount;
void n(unsigned x){cap->add(&x,sizeof(x));}
void check(bool x){if(!x)++errors;}
void* allocateNode(size_t size){++allocations;check(size==sizeof(QNode));if(fault==1)throw std::bad_alloc();void* p=std::malloc(size);if(!p)throw std::bad_alloc();allocated=p;return p;}
void deleteNode(void* p){if(p==allocated)++deletions;else ++errors;std::free(p);}
void failCopy(void*,const std::wstring&){++copies;throw CopyFailure();}
QBase* header(QMap* m){return reinterpret_cast<QBase*>(reinterpret_cast<char*>(m)+8);}
size_t& count(QMap* m){return *reinterpret_cast<size_t*>(reinterpret_cast<char*>(m)+40);}
const QValue& value(QBase* p){return static_cast<QNode*>(p)->_M_value_field;}
int identity(QBase* p){for(unsigned i=0;i<knownCount;++i)if(known[i]==p)return i;return -1;}
// Independent expected sequence uses a bounded insertion-sort array, never map::insert.
void expect(const std::wstring& key,bool v){unsigned at=expectedCount;while(at&&key<expectedKeys[at-1]){expectedKeys[at]=expectedKeys[at-1];expectedValues[at]=expectedValues[at-1];--at;}expectedKeys[at]=key;expectedValues[at]=v;++expectedCount;}
void seed(QMap* m,const std::wstring& key,bool v){
 QBase* h=header(m);QBase* parent=h;QBase* p=h->_M_parent;bool left=true;
 while(p){parent=p;left=key<value(p).first;p=left?p->_M_left:p->_M_right;}
 QNode* node=static_cast<QNode*>(::operator new(sizeof(QNode)));
 new(&node->_M_value_field)QValue(key,v);
 std::_Rb_tree_insert_and_rebalance(left,node,parent,*h);++count(m);known[knownCount++]=node;expect(key,v);
}
// Bounded membership check precedes every dereference of a tree link.
unsigned inspect(QBase* p,QBase* parent,unsigned depth){
 if(!p)return 1;int id=identity(p);if(id<0||depth>knownCount||visited[id]){++errors;return 0;}visited[id]=true;++visitedCount;
 check(p->_M_parent==parent);check(p->_M_color==std::_S_red||p->_M_color==std::_S_black);
 unsigned l=inspect(p->_M_left,p,depth+1);
 // In-order output is compared against the independent sorted sequence below.
 unsigned r=inspect(p->_M_right,p,depth+1);check(l==r);
 if(p->_M_color==std::_S_red){if(p->_M_left&&identity(p->_M_left)>=0)check(p->_M_left->_M_color==std::_S_black);if(p->_M_right&&identity(p->_M_right)>=0)check(p->_M_right->_M_color==std::_S_black);}
 return l+(p->_M_color==std::_S_black);
}
unsigned orderedIndex;
void ordered(QBase* p,unsigned depth){if(!p||depth>knownCount)return;if(identity(p)<0)return;
 ordered(p->_M_left,depth+1);if(orderedIndex>=expectedCount){++errors;return;}
 const QValue& v=value(p);check(v.first==expectedKeys[orderedIndex]);check(v.second==expectedValues[orderedIndex]);cap->addText(v.first);n(v.second);++orderedIndex;ordered(p->_M_right,depth+1);
}
std::wstring keyFor(unsigned k){
 const wchar_t* keys[]={L"",L"A",L"AA",L"AB",L"B",L"M",L"N",L"Z",L"quest",L"quest/child",L"\u041a\u0432\u0435\u0441\u0442",L"\u4efb\u52a1"};
 if(k<12)return std::wstring(keys[k]);if(k==12)return std::wstring(180,L'q');if(k==13)return std::wstring(180,L'z');
 const wchar_t embedded[]={L'q',0,L'x'};return std::wstring(embedded,3);
}
void side(void* raw,autotest::Capture& out,bool candidate){
 const Case& c=*static_cast<Case*>(raw);cap=&out;errors=allocations=deletions=copies=knownCount=visitedCount=expectedCount=0;allocated=0;fault=c.fault;std::memset(visited,0,sizeof(visited));autotest::g_arenaUsed=0;
 unsigned char* storage=static_cast<unsigned char*>(autotest::allocate(sizeof(QMap)+32));std::memset(storage,0xa9,sizeof(QMap)+32);QMap* m=new(storage+16)QMap;
 const unsigned seeds[]={5,2,9,1,4,7,11,3,6,8,10,12,13,14};
 unsigned seedsCount=c.shape==0?0:c.shape==1?1:c.shape==2?5:14;
 for(unsigned i=0;i<seedsCount;++i)if(seeds[i]!=c.key)seed(m,keyFor(seeds[i]),(i%3)==1);
 std::wstring key=keyFor(c.key);QValue input(key,c.value!=0);QBase* h=header(m);QBase* parent=h;QBase* p=h->_M_parent;bool left=true;
 while(p){parent=p;left=key<value(p).first;p=left?p->_M_left:p->_M_right;}
 // x non-null requests a left insertion. Only select it when that is a valid
 // empty child slot; no malformed tree or duplicate-key input is credited.
 const QBase* x=c.forced&&(parent==h||left)?h:0;
 unsigned char priorMap[48];std::memcpy(priorMap,m,48);
 typedef QIterator(*Fn)(void*,const QBase*,const QBase*,const QValue&);Fn fn=candidate?&newInsert:&oldInsert;
 QIterator result;unsigned caught=0;
 {
  detour::Set redirects;redirects.redirect(nodeNew,nodeNew,&allocateNode);redirects.redirect(nodeDelete,nodeDelete,&deleteNode);if(c.fault==2)redirects.redirect(wideCopy,wideCopy,&failCopy);
  if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(!autotest::beginInvocation(out,fn))return;
  try{result=fn(m,x,parent,input);out.callCompleted=1;}catch(const std::bad_alloc&){caught=1;}catch(const CopyFailure&){caught=2;}catch(...){caught=3;}
 }
 check(caught==c.fault);check(allocations==1);check(deletions==(c.fault==2?1u:0u));check(copies==(c.fault==2?1u:0u));
 if(!caught){check(result._M_node==allocated);check(allocated!=0);known[knownCount++]=static_cast<QBase*>(allocated);expect(key,c.value!=0);}
 else check(std::memcmp(priorMap,m,48)==0);
 check(input.first==key&&input.second==(c.value!=0));check(count(m)==expectedCount);check(h->_M_color==std::_S_red);
 if(expectedCount){check(h->_M_parent&&identity(h->_M_parent)>=0);if(h->_M_parent&&identity(h->_M_parent)>=0)check(h->_M_parent->_M_color==std::_S_black);inspect(h->_M_parent,h,0);check(visitedCount==expectedCount);
  check(identity(h->_M_left)>=0&&identity(h->_M_right)>=0);if(!errors){orderedIndex=0;ordered(h->_M_parent,0);check(orderedIndex==expectedCount);check(value(h->_M_left).first==expectedKeys[0]);check(value(h->_M_right).first==expectedKeys[expectedCount-1]);}}
 else check(!h->_M_parent&&h->_M_left==h&&h->_M_right==h);
 for(unsigned i=0;i<16;++i)check(storage[i]==0xa9&&storage[64+i]==0xa9);
 n(caught);n(allocations);n(deletions);n(copies);n(expectedCount);n(visitedCount);n(x!=0);n(left);n(result._M_node==allocated&&!caught);
 // True map lifetime destruction uses the same real allocator storage.
 if(!errors)m->~QMap();n(0x344d0c01);n(errors);
}
void before(void* p,autotest::Capture& o){side(p,o,false);}void after(void* p,autotest::Capture& o){side(p,o,true);}
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=sizeof(tail))std::memcpy(tail,o.capture.data+o.capture.length-sizeof(tail),sizeof(tail));return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x344d0c01&&!tail[1];}
bool runPair(const tlhybrid_host* host,autotest::Coverage& cv,Case& c){autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault){if(cv.observe(host,a,b))ok=false;}else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==(uint64_t)(uintptr_t)&oldInsert&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok)host->log(" map insert shape=%u key=%u value=%u forced=%u fault=%u status=%d/%d issue=%u/%u\n",c.shape,c.key,c.value,c.forced,c.fault,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);return ok;}
}
TL_TEST(quest_map_insert_closure){autotest::Coverage cv("quest_map_insert_closure",0xd344d0);unsigned completed=0;
 for(unsigned shape=0;shape<4;++shape)for(unsigned key=0;key<15;++key)for(unsigned v=0;v<2;++v){Case c={shape,key,v,(key+v)%2,0};if(!runPair(host,cv,c)){cv.report(host);return 1;}++completed;}
 cv.report(host);return cv.completed!=completed||cv.missing||cv.different;}
TL_TEST(quest_map_insert_exceptions){autotest::Coverage cv("map insert expected exceptions excluded from coverage",0xd344d0);unsigned witnesses=0;
 for(unsigned fault=1;fault<=2;++fault)for(unsigned shape=0;shape<4;++shape)for(unsigned v=0;v<2;++v){Case c={shape,14,v,v,fault};if(!runPair(host,cv,c))return 1;++witnesses;}
 host->log(" map insert: %u expected exception witnesses, no completed coverage credited\n",witnesses);return 0;}
