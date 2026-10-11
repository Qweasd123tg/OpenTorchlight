// The actual pinned Ogre 1.6.5 ChildNodeIterator carries two two-word
// libstdc++ TR1 hash iterators. Do not replace it with std::map/vector cursors.
#include <cstring>
#include <cstdio>
#include <cstddef>
#include <OgreSceneNode.h>
#include "AutoTest.h"
TL_ORIGINAL(unsigned,oldCount,(Ogre::SceneNode*),"_Z13CountChildrenPN4Ogre9SceneNodeE")
extern "C" unsigned newCount(Ogre::SceneNode*) __asm__("_Z13CountChildrenPN4Ogre9SceneNodeE");
namespace {
typedef Ogre::Node::ChildNodeMap Map;
typedef Ogre::Node::ChildNodeIterator Iterator;
// Pinned GCC 4.4.7 tr1_impl/hashtable_policy.h: value at +0, next at +16.
typedef std::tr1::__detail::_Hash_node<Map::value_type, false> HashNode;
typedef char PinnedNodeIs24Bytes[sizeof(HashNode)==24?1:-1];
typedef char PinnedNextOffset[offsetof(HashNode,_M_next)==16?1:-1];
enum { BucketCount=97, MaxEdges=256 };
typedef char PinnedIteratorIs32Bytes[sizeof(Iterator)==32?1:-1];
typedef char PinnedHashIteratorIs16Bytes[sizeof(Map::iterator)==16?1:-1];
struct Case { unsigned shape,variant; Case(unsigned s,unsigned v):shape(s),variant(v){} };
struct Owner { unsigned char* guarded; void* node; HashNode** buckets; unsigned id,edges; } owners[96];
unsigned count,visits,semanticErrors,edgeCount;HashNode* edgeNodes[MaxEdges];HashNode* emptyBuckets[1]; autotest::Capture* cap;void* table[58];
void infrastructureFailure(){cap->issue=autotest::Capture::InvalidReport;}
void semanticFailure(){++semanticErrors;}
bool oracleGood(const autotest::Capture& o){unsigned footer[2];if(o.length<sizeof(footer))return false;std::memcpy(footer,o.data+o.length-sizeof(footer),sizeof(footer));return footer[0]==0xcc105e01u&&footer[1]==0;}
void number(unsigned n){cap->add(&n,sizeof(n));}
void* makeNode(){Owner& o=owners[count];o.id=count++;o.guarded=(unsigned char*)autotest::allocate(0x240);if(!o.guarded)_exit(71);std::memset(o.guarded,0xd3,16);std::memset(o.guarded+16,0xa5,0x220);std::memset(o.guarded+0x230,0x6c,16);o.node=o.guarded+16;
 void** v=table;std::memcpy(o.node,&v,sizeof(v));
 o.buckets=(HashNode**)autotest::allocate((BucketCount+1)*sizeof(HashNode*));if(!o.buckets)_exit(71);o.buckets[BucketCount]=reinterpret_cast<HashNode*>(0x1000);o.edges=0;return o.node;}
Owner* find(void* node){for(unsigned i=0;i<count;++i)if(owners[i].node==node)return &owners[i];semanticFailure();return 0;}
Iterator emptyIterator(){Map::iterator end(emptyBuckets[0],emptyBuckets);return Iterator(end,end);}
Iterator children(void* self){Owner* o=find(self);if(!o)return emptyIterator();number(o->id);++visits;unsigned first=0;while(!o->buckets[first])++first;return Iterator(Map::iterator(o->buckets[first],o->buckets+first),Map::iterator(o->buckets[BucketCount],o->buckets+BucketCount));}
Iterator wrong(void* self){semanticFailure();number(0xf001);return emptyIterator();}
void edgeAt(void* from,void* to,unsigned key,unsigned bucket){Owner* o=find(from);if(!o||bucket>=BucketCount||edgeCount==MaxEdges){infrastructureFailure();return;}char text[40];std::sprintf(text,"child-%u",key);
 // Construct the actual pinned node (including its actual const string key).
 // No unordered_map object, insertion, hashing, rehash policy or prime data.
 HashNode initial={Map::value_type(text,static_cast<Ogre::Node*>(to)),o->buckets[bucket]};
 void* storage=autotest::allocate(sizeof(HashNode));if(!storage)_exit(71);HashNode* node=new(storage)HashNode(initial);edgeNodes[edgeCount++]=node;o->buckets[bucket]=node;++o->edges;
}
void edge(void* from,void* to,unsigned key){edgeAt(from,to,key,key%BucketCount);}
unsigned build(const Case& c){void* root=makeNode();unsigned expected=0;
 switch(c.shape){
 case 0:break; // empty root, still invokes the virtual iterator
 case 1:for(unsigned i=0;i<c.variant+1;++i){edge(root,makeNode(),i);++expected;}break;
 case 2:{void* parent=root;for(unsigned i=0;i<c.variant+1;++i){void* child=makeNode();edge(parent,child,i);parent=child;++expected;}break;}
 case 3:for(unsigned i=0;i<12;++i){void* child=i%3==c.variant?0:makeNode();edge(root,child,i);if(child)++expected;}break;
 case 4:{for(unsigned i=0;i<5;++i){void* branch=makeNode();edge(root,branch,i);++expected;for(unsigned j=0;j<3;++j){void* leaf=(i+j+c.variant)%4==0?0:makeNode();edge(branch,leaf,30+i*3+j);if(leaf)++expected;}}break;}
 case 5:{// Repeated child pointers count once per edge, not once per identity.
 void* common=makeNode();void* leaf=makeNode();edge(common,leaf,99);for(unsigned i=0;i<5;++i)edge(root,common,i);expected=10;break;}
 case 6:{// Distant occupied buckets, with leading/intermediate/trailing gaps.
 const unsigned wanted[]={1,19,43,79};for(unsigned i=0;i<4;++i){edgeAt(root,makeNode(),c.variant*10+i,wanted[i]);++expected;}break;}
 case 8:for(unsigned i=0;i<c.variant+1;++i)edge(root,0,i);break;
 case 7:{// Eight actual linked nodes in one bucket, including null values.
 for(unsigned i=0;i<8;++i){void* child=(i+c.variant)%3==0?0:makeNode();edgeAt(root,child,i,7);if(child)++expected;}break;}
 }
 return expected;}
void side(void* p,autotest::Capture& out,bool candidate){const Case& c=*(Case*)p;cap=&out;autotest::g_arenaUsed=0;count=visits=semanticErrors=edgeCount=0;emptyBuckets[0]=reinterpret_cast<HashNode*>(0x1000);for(unsigned i=0;i<58;++i)table[i]=(void*)&wrong;table[57]=(void*)&children;
 unsigned expected=build(c);typedef unsigned(*Fn)(Ogre::SceneNode*);Fn fn=candidate?&newCount:&oldCount;
 if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(static_cast<Ogre::SceneNode*>(owners[0].node));out.callCompleted=1;number(result);number(visits);if(result!=expected||visits!=expected+1)semanticFailure();
 for(unsigned i=0;i<count;++i){Owner& o=owners[i];for(unsigned j=0;j<16;++j)if(o.guarded[j]!=0xd3||o.guarded[0x230+j]!=0x6c)semanticFailure();out.add(o.guarded,0x240);
 // Buckets and actual nodes live at deterministic arena addresses. Snapshot
 // without traversing candidate-mutated links; invalid links stay semantic.
 number(o.edges);out.add(o.buckets,(BucketCount+1)*sizeof(HashNode*));
 }
 number(edgeCount);for(unsigned i=0;i<edgeCount;++i){HashNode* node=edgeNodes[i];out.addText(node->_M_v.first);void* value=node->_M_v.second;out.add(&value,sizeof(value));out.add(&node->_M_next,sizeof(node->_M_next));if(value&&!autotest::inArena(value))semanticFailure();}
 // Only real pinned hash nodes were constructed; no fake owner/map lifetime.
 for(unsigned i=0;i<edgeCount;++i)edgeNodes[i]->~HashNode();number(0xcc105e01u);number(semanticErrors);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(gameui_count_children_closure){autotest::Coverage coverage("gameui_count_children_closure",0xa83250);unsigned completed=0;
 const unsigned variants[]={1,12,64,3,4,1,4,4,12};for(unsigned shape=0;shape<9;++shape)for(unsigned variant=0;variant<variants[shape];++variant){Case c(shape,variant);autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++completed;int compared=coverage.observe(host,a,b);if(compared||!oracleGood(a.capture)||!oracleGood(b.capture)){host->log(" CountChildren shape=%u variant=%u\n",shape,variant);coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=completed||coverage.missing||coverage.different;}
