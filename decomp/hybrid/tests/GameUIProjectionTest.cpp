// Exact ABI and raw floating-bit differential receipts for screen projection.
// Matrix4 is passed by value (64-byte stack argument); Vector3 returns in XMM0/1.
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include <xmmintrin.h>
#include <CEGUI.h>
#include <OgreVector3.h>
#include <OgreMatrix4.h>
#include "GameUI.h"
#include "TextEvent.h"
#include "TLinkedList.h"
#include "SubMenu.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(Ogre::Vector3, originalProjection, (CGameUI*,const Ogre::Vector3*,const Ogre::Vector3*,Ogre::Matrix4), "_ZN7CGameUI17getScreenPositionEPKN4Ogre7Vector3ES3_NS0_7Matrix4E")
extern "C" Ogre::Vector3 recoveredProjection(CGameUI*,const Ogre::Vector3*,const Ogre::Vector3*,Ogre::Matrix4) __asm__("_ZN7CGameUI17getScreenPositionEPKN4Ogre7Vector3ES3_NS0_7Matrix4E");
TL_ORIGINAL(void, originalUpdate, (CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool), "_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb")
extern "C" void recoveredUpdate(CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool) __asm__("_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb");
TL_FUNCTION(coveredFunction, "_ZN7CGameUI11leftCoveredEv")
TL_FUNCTION(edgeFunction, "_ZN7CGameUI14leftScreenEdgeEv")
extern "C" char nodeAllocate[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char nodeRelease[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char windowRemove[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char windowPosition[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char windowProperty[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");

namespace {
typedef TLinkedListNode<CTextEvent*> Node;
typedef std::vector<CSubMenu*> MenuVector;
typedef char check_gameui_size[sizeof(CGameUI)==0x1a08?1:-1];
typedef char check_matrix_size[sizeof(Ogre::Matrix4)==64?1:-1];
typedef char check_vector_size[sizeof(Ogre::Vector3)==12?1:-1];
struct List { Node* head; };
struct Case {
    Ogre::Matrix4 matrix;
    Ogre::Vector3 point, offset;
    float width,height,ratio,edge,elapsed;
    unsigned mutation,alias,realHelpers,layout,lifetime,flags,ticks,fault;
    bool covered,show;
    Case():point(1.25f,-2.75f,7.125f),offset(-.25f,1.125f,.5f),
      width(1280.f),height(720.f),ratio(.75f),edge(217.25f),elapsed(.125f),
      mutation(0),alias(0),realHelpers(0),layout(3),lifetime(0),flags(3),ticks(1),fault(0),covered(false),show(true) {
        for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col)matrix[row][col]=row==col?1.f:0.f;
    }
};
struct Stop {};
struct Block { unsigned char* p;unsigned size,kind;bool released; };
enum { Raw, UI, Event, NodeKind, MenuTable };
enum { Covered=1, Edge, Right, Open, MenuEdge, Position, Property, Remove, Allocate, Release };
const Case* current;
autotest::Capture* capture;
CGameUI* ui;
Ogre::Vector3* point;
Ogre::Vector3* offset;
Ogre::Matrix4* matrix;
Block blocks[40];unsigned blockCount,coveredCount,edgeCount,positionCount,propertyCount,removeCount,allocCount,freeCount,mutationCount;
CSubMenu* menus[3];
CTextEvent* events[3];CEGUI::Window* windows[5];List* lists[2];
void require(bool condition) { if(!condition)_exit(90); }
template<class T>T& at(void* p,unsigned n) {return *reinterpret_cast<T*>(static_cast<char*>(p)+n);}
void number(unsigned n) {capture->add(&n,4);}
void floating(float n) {capture->add(&n,4);}
void pointer(const void* p) {capture->addPointer(p);}
void vector(const Ogre::Vector3& v) {floating(v.x);floating(v.y);floating(v.z);}
float bits(unsigned n) {float f;std::memcpy(&f,&n,4);return f;}
void tag(unsigned n) {number(n);if(current->fault==n)throw Stop();}
void* guarded(unsigned size,unsigned kind=Raw,unsigned fill=0) {
    require(blockCount<40);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));require(p!=0);
    std::memset(p,0xd3,16);std::memset(p+16,fill,size);std::memset(p+16+size,0x6c,16);
    Block& b=blocks[blockCount++];b.p=p+16;b.size=size;b.kind=kind;b.released=false;return b.p;
}
unsigned blockIndex(void* p) {for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p)return i;_exit(91);return 0;}
void mutate(unsigned boundary) {
    unsigned m=current->mutation;
    if((m==1||m==3||m==4||m==5||m==6) && boundary==Covered) {
        at<float>(ui,0x1684)=853.375f;at<float>(ui,0x1688)=999.25f;at<float>(ui,0x1680)=-.375f;
        if(m==4||m==5||m==6) {
            // Only the caller-owned source is mutated; the 64-byte stack copy
            // inside getScreenPosition must retain all sixteen original words.
            point->x=-21.25f;point->y=17.5f;point->z=.03125f;
            offset->x=.75f;offset->y=-91.125f;offset->z=47.25f;
            for(unsigned r=0;r<4;++r)for(unsigned c=0;c<4;++c)(*matrix)[r][c]=17.5f+r*4+c;
        }
        ++mutationCount;
    }
    if((m==2||m==3||m==5||m==6) && boundary==Edge) {
        at<float>(ui,0x1684)=1111.625f;at<float>(ui,0x1688)=3.75f;at<float>(ui,0x1680)=7.25f;
        if(m==6){point->y=bits(0x7fc76543u);offset->z=bits(0x7f800000u);(*matrix)[1][1]=bits(0xff800000u);}
        ++mutationCount;
    }
}
bool covered(CGameUI* p) {tag(Covered);pointer(p);require(p==ui);++coveredCount;floating(at<float>(ui,0x1684));floating(at<float>(ui,0x1688));floating(at<float>(ui,0x1680));mutate(Covered);return current->covered;}
float edge(CGameUI* p) {tag(Edge);pointer(p);require(p==ui);++edgeCount;floating(at<float>(ui,0x1684));mutate(Edge);return current->edge;}
unsigned menuIndex(CSubMenu* p) {for(unsigned i=0;i<3;++i)if(menus[i]==p)return i;_exit(92);return 0;}
void forbidden() {_exit(93);}
bool isRight(CSubMenu* p) {tag(Right);pointer(p);unsigned i=menuIndex(p);return i==0;}
bool isOpen(CSubMenu* p) {tag(Open);pointer(p);unsigned i=menuIndex(p);return current->covered && i==1;}
float menuEdge(CSubMenu* p) {tag(MenuEdge);pointer(p);return menuIndex(p)==1?current->edge:current->edge*.5f;}
void ceguiString(const CEGUI::String& s) {number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void property(void* w,const CEGUI::String& key,const CEGUI::String& value) {tag(Property);pointer(w);ceguiString(key);ceguiString(value);++propertyCount;}
void position(CEGUI::Window* w,const CEGUI::UVector2& value) {tag(Position);pointer(w);floating(value.d_x.d_scale);floating(value.d_x.d_offset);floating(value.d_y.d_scale);floating(value.d_y.d_offset);++positionCount;}
void remove(CEGUI::Window* parent,CEGUI::Window* child) {tag(Remove);pointer(parent);pointer(child);++removeCount;require(child!=0);if(at<CEGUI::Window*>(child,0xb0)==parent)at<CEGUI::Window*>(child,0xb0)=0;}
void* allocate(size_t size,const char* file,int line,const char* function) {
    tag(Allocate);number(size);number(file!=0);number(line);number(function!=0);require(size==sizeof(Node));++allocCount;void* p=guarded(size,NodeKind,0xa5);pointer(p);return p;
}
void release(void* p) {number(Release);pointer(p);unsigned i=blockIndex(p);require(blocks[i].kind==NodeKind&&!blocks[i].released);Node* n=static_cast<Node*>(p);require(!n->m_pNext&&!n->m_pPrevious);blocks[i].released=true;++freeCount;}
void nodeState(Node* n) {pointer(n->m_Data);pointer(n->m_pNext);pointer(n->m_pPrevious);}
void append(List* list,CTextEvent* e) {
    Node* n=static_cast<Node*>(guarded(sizeof(Node),NodeKind));n->m_Data=e;
    if(!list->head){list->head=n;return;}Node* tail=list->head;unsigned count=0;while(tail->m_pNext){require(++count<3);tail=tail->m_pNext;}tail->m_pNext=n;n->m_pPrevious=tail;
}
void snapshot(bool integration) {
    number(coveredCount);number(edgeCount);number(positionCount);number(propertyCount);number(removeCount);number(allocCount);number(freeCount);number(mutationCount);
    vector(*point);vector(*offset);capture->add(matrix,sizeof(*matrix));
    if(integration)for(unsigned j=0;j<2;++j) {
        pointer(lists[j]->head);Node* prior=0;unsigned count=0;
        for(Node* n=lists[j]->head;n;n=n->m_pNext){require(++count<=3);require(n->m_pPrevious==prior);require(!blocks[blockIndex(n)].released);pointer(n);nodeState(n);prior=n;}number(count);
    }
    number(blockCount);
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];pointer(b.p);number(b.size);number(b.kind);number(b.released);
        for(unsigned j=0;j<16;++j)require(b.p[-16+int(j)]==0xd3&&b.p[b.size+j]==0x6c);
        capture->add(b.p-16,16);capture->add(b.p+b.size,16);
        if(b.kind==UI && current->realHelpers) {
            capture->add(b.p,0x1930);number(at<MenuVector>(ui,0x1930).size());for(unsigned j=0;j<at<MenuVector>(ui,0x1930).size();++j)pointer(at<MenuVector>(ui,0x1930)[j]);capture->add(b.p+0x1948,b.size-0x1948);
        } else if(b.kind==Event) {
            capture->add(b.p,0x20);capture->addText(reinterpret_cast<CTextEvent*>(b.p)->m_Text);capture->add(b.p+0x28,0x50);pointer(reinterpret_cast<CTextEvent*>(b.p)->m_pWindow);capture->add(b.p+0x80,8);
        } else if(b.kind==NodeKind)nodeState(reinterpret_cast<Node*>(b.p));
        else if(b.kind==MenuTable) {
            for(unsigned j=0;j<13;++j){void* p=reinterpret_cast<void**>(b.p)[j];void* expected=reinterpret_cast<void*>(&forbidden);if(j==3)expected=reinterpret_cast<void*>(&isRight);if(j==4)expected=reinterpret_cast<void*>(&isOpen);if(j==6)expected=reinterpret_cast<void*>(&menuEdge);require(p==expected);}
        } else capture->add(b.p,b.size);
    }
}
void setup(const Case& c,bool integration) {
    autotest::g_arenaUsed=0;blockCount=coveredCount=edgeCount=positionCount=propertyCount=removeCount=allocCount=freeCount=mutationCount=0;
    ui=static_cast<CGameUI*>(guarded(sizeof(CGameUI),UI,0x5a));
    at<float>(ui,0x1684)=c.width;at<float>(ui,0x1688)=c.height;at<float>(ui,0x1680)=c.ratio;
    point=static_cast<Ogre::Vector3*>(guarded(sizeof(*point)));::new(point)Ogre::Vector3(c.point);
    offset=c.alias==1?point:static_cast<Ogre::Vector3*>(guarded(sizeof(*offset)));if(c.alias!=1)::new(offset)Ogre::Vector3(c.offset);
    matrix=static_cast<Ogre::Matrix4*>(guarded(sizeof(*matrix)));::new(matrix)Ogre::Matrix4(c.matrix);
    if(c.realHelpers) {
        ::new(&at<MenuVector>(ui,0x1930))std::vector<CSubMenu*>();
        void** table=static_cast<void**>(guarded(13*sizeof(void*),MenuTable));for(unsigned j=0;j<13;++j)table[j]=reinterpret_cast<void*>(&forbidden);
        table[3]=reinterpret_cast<void*>(&isRight);table[4]=reinterpret_cast<void*>(&isOpen);table[6]=reinterpret_cast<void*>(&menuEdge);
        for(unsigned i=0;i<3;++i){menus[i]=static_cast<CSubMenu*>(guarded(sizeof(CSubMenu)));at<void**>(menus[i],0)=table;if(i<c.layout)at<MenuVector>(ui,0x1930).push_back(menus[i]);}
    }
    if(!integration)return;
    for(unsigned j=0;j<5;++j)windows[j]=static_cast<CEGUI::Window*>(guarded(sizeof(CEGUI::Window)));
    for(unsigned j=0;j<2;++j)lists[j]=static_cast<List*>(guarded(sizeof(List)));
    at<List*>(ui,0x1698)=lists[0];at<List*>(ui,0x16a0)=lists[1];at<CEGUI::Window*>(ui,0x488)=windows[3];
    for(unsigned j=0;j<3;++j) {
        CTextEvent* e=static_cast<CTextEvent*>(guarded(sizeof(CTextEvent),Event,0xa5));events[j]=e;at<void*>(e,0)=0;at<void*>(e,8)=0;
        ::new(&e->m_Text)std::string(j%2?"critical":"retained label");::new(&e->m_Colour28)CEGUI::colour(.25f,.5f,.75f,1.f);::new(&e->m_Colour40)CEGUI::colour(.75f,.5f,.25f,1.f);
        e->m_Value10=c.point.x+j*.25f;e->m_Value14=c.point.y-j*.75f;e->m_Value18=c.point.z;
        e->m_Value60=1.f;e->m_Value64=.75f;e->m_Value68=c.lifetime==1?1.f:(c.lifetime==2?bits(0x7fc12345u):(c.lifetime==3?-0.f:200.f));
        e->m_Unrecovered6C=23.25f+j*2.5f;e->m_Value70=.125f+j*.25f;
        e->m_pWindow=windows[j];e->m_Flag80=(c.flags&1)!=0;e->m_Flag81=(c.flags&2)!=0;e->m_Flag82=j==1;
        at<CEGUI::Window*>(windows[j],0xb0)=windows[(j&1)?4:3];if(j<c.layout)append(lists[1],e);
    }
}
void side(void* raw,autotest::Capture& out,bool ours,bool integration) {
    current=static_cast<Case*>(raw);capture=&out;setup(*current,integration);_mm_setcsr(0x1f80);
    detour::Set d;if(!current->realHelpers){TL_REDIRECT(d,coveredFunction,&covered);TL_REDIRECT(d,edgeFunction,&edge);}
    if(integration){d.redirect(nodeAllocate,nodeAllocate,&allocate);d.redirect(nodeRelease,nodeRelease,&release);d.redirect(windowRemove,windowRemove,&remove);d.redirect(windowPosition,windowPosition,&position);d.redirect(windowProperty,windowProperty,&property);}
    require(!d.failed());bool threw=false;
    try {
        for(unsigned tick=0;tick<current->ticks;++tick) {
            number(tick);
            if(integration) {
                void(*fn)(CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool)=ours?&recoveredUpdate:&originalUpdate;
                if(!tick)require(autotest::beginInvocation(out,fn));fn(ui,current->elapsed,*offset,*matrix,current->show);
            } else {
                Ogre::Vector3(*fn)(CGameUI*,const Ogre::Vector3*,const Ogre::Vector3*,Ogre::Matrix4)=ours?&recoveredProjection:&originalProjection;
                if(!tick)require(autotest::beginInvocation(out,fn));Ogre::Vector3 result=fn(ui,point,offset,*matrix);vector(result);
                if(!current->realHelpers){require(coveredCount==tick+1);require(edgeCount==(current->covered?tick+1:0));}
            }
            snapshot(integration);
        }
        out.callCompleted=1;
    } catch(const Stop&){threw=true;} catch(...){_exit(94);}
    number(threw);require(bool(current->fault)==threw);snapshot(integration);
    if(current->realHelpers)at<MenuVector>(ui,0x1930).~MenuVector();
}
void oldSide(void* p,autotest::Capture& out){side(p,out,false,false);}
void newSide(void* p,autotest::Capture& out){side(p,out,true,false);}
void oldComposed(void* p,autotest::Capture& out){side(p,out,false,true);}
void newComposed(void* p,autotest::Capture& out){side(p,out,true,true);}
int run(const tlhybrid_host* host,const char* name,const std::vector<Case>& cases,bool integration,const std::vector<Case>& faults) {
    uint64_t address=integration?(uint64_t)(uintptr_t)&originalUpdate:(uint64_t)(uintptr_t)&originalProjection;
    autotest::Coverage coverage(name,address);
    if(!host->comparison_pair||!host->comparison_pair((uint64_t)(uintptr_t)&originalProjection,(uint64_t)(uintptr_t)&recoveredProjection))return 1;
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(integration?oldComposed:oldSide,&c,a);autotest::runChild(integration?newComposed:newSide,&c,b);
        if(coverage.observe(host,a,b)) {
            size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
            host->log("    projection %s case %u mutation %u alias %u real %u covered %u: exits %d/%d issues %u/%u lengths %u/%u first %u\n",name,i,c.mutation,c.alias,c.realHelpers,c.covered,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned)a.capture.length,(unsigned)b.capture.length,(unsigned)first);
            if(first+4<=a.capture.length&&first+4<=b.capture.length){unsigned x,y;std::memcpy(&x,a.capture.data+first,4);std::memcpy(&y,b.capture.data+first,4);host->log("    differing words %08x / %08x\n",x,y);}coverage.report(host);return 1;
        }
    }
    coverage.report(host);if(coverage.completed<20)return 1;
    unsigned unwinds=0;for(unsigned i=0;i<faults.size();++i) {
        Case c=faults[i];autotest::Outcome a,b;autotest::runChild(integration?oldComposed:oldSide,&c,a);autotest::runChild(integration?newComposed:newSide,&c,b);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==address&&host->comparison_pair(address,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
        if(!ok){host->log("    projection expected unwind %u exits %d/%d complete %u/%u lengths %u/%u failed\n",i,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted,(unsigned)a.capture.length,(unsigned)b.capture.length);return 1;}++unwinds;
    }
    host->log("    %s: %u separately checked expected unwinds, excluded from normal coverage\n",name,unwinds);return 0;
}
}

TL_TEST(gameui_projection_exact_bits) {
    std::vector<Case> cases,faults;
    for(unsigned i=0;i<20;++i) {
        Case c;c.covered=(i&1)!=0;c.width=640.f+i*41.125f;c.height=480.f+i*29.375f;c.ratio=(int(i%5)-1)*.4375f;c.edge=17.125f+i*9.75f;
        for(unsigned r=0;r<4;++r)for(unsigned k=0;k<4;++k)c.matrix[r][k]=(int(r*4+k)-6)*.03125f+(r==k?1.f:0.f);
        c.point=Ogre::Vector3(i*.5f-5.f,i*.25f-3.f,i%3?-8.25f:7.5f);c.offset=Ogre::Vector3(.375f,-.625f,1.125f);cases.push_back(c);
    }
    // Independent denominator/second reciprocal and viewport bit boundaries.
    const unsigned special[]={0u,0x80000000u,1u,0x80000001u,0x007fffffu,0x00800000u,0x00800001u,0x3effffffu,0x3f000000u,0x3f000001u,0x3f7fffffu,0x3f800000u,0x3f800001u,0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0xffc76543u};
    for(unsigned which=0;which<8;++which)for(unsigned i=0;i<sizeof(special)/sizeof(special[0]);++i) {
        Case c;float v=bits(special[i]);c.covered=(i&1)!=0;c.point.z=1.f;c.offset.z=0.f;
        if(which==0)c.matrix[3][3]=v;
        else if(which==1){c.matrix[2][2]=0.f;c.matrix[2][3]=v;}
        else if(which==2)c.width=v;
        else if(which==3)c.height=v;
        else if(which==4)c.ratio=v;
        else if(which==5){c.edge=v;c.covered=true;}
        else if(which==6)c.point.x=v;
        else c.offset.y=v;
        cases.push_back(c);
    }
    // Reciprocal overflow/underflow and rounding persist through both divides.
    for(unsigned i=0;i<12;++i) {
        Case c;c.matrix[3][3]=bits(i&1?0x7f000001u:0x00800001u);c.matrix[2][2]=bits(i&2?0x00800001u:0x7f000001u);c.point.z=bits(0x3f800001u);c.offset.z=bits(0xb3800000u);c.covered=(i&4)!=0;c.alias=i%3==0?1:0;cases.push_back(c);
    }
    for(unsigned covered=0;covered<2;++covered)for(unsigned mutation=1;mutation<=6;++mutation)for(unsigned alias=0;alias<2;++alias) {
        Case c;c.covered=covered!=0;c.mutation=mutation;c.alias=alias;c.ticks=2;cases.push_back(c);
    }
    // Exercise the already accepted helpers through valid, bounded menu lists.
    for(unsigned length=0;length<=3;++length)for(unsigned covered=0;covered<2;++covered)for(unsigned edge=0;edge<3;++edge) {
        Case c;c.realHelpers=1;c.layout=length;c.covered=covered!=0;c.edge=edge==0?-13.25f:(edge==1?217.25f:bits(0x7fc12345u));cases.push_back(c);
    }
    // Height/normalised y cancellation must preserve sign-bit negation.
    for(unsigned i=0;i<8;++i){Case c;c.point=Ogre::Vector3(0.f,i&1?1.f:-1.f,1.f);c.offset=Ogre::Vector3(0.f,0.f,0.f);c.height=bits(i&2?0x80000000u:0u);c.width=bits(i&4?0x80000000u:0u);cases.push_back(c);}
    // All negative-zero row terms produce an actual -0 denominator, unlike
    // merely putting -0 in the final translation after positive-zero terms.
    for(unsigned axis=2;axis<4;++axis)for(unsigned sign=0;sign<2;++sign) {
        Case c;c.point=Ogre::Vector3(1.f,2.f,3.f);c.offset=Ogre::Vector3(0.f,0.f,0.f);
        for(unsigned k=0;k<4;++k)c.matrix[axis][k]=bits(sign?0x80000000u:0u);cases.push_back(c);
    }
    for(unsigned tag=Covered;tag<=Edge;++tag){Case c;c.covered=true;c.fault=tag;c.mutation=4;faults.push_back(c);}
    return run(host,"gameui_projection_exact_bits",cases,false,faults);
}
TL_TEST(gameui_projection_lifecycle_composed) {
    std::vector<Case> cases,faults;
    for(unsigned lifetime=0;lifetime<4;++lifetime)for(unsigned flags=0;flags<4;++flags)for(unsigned covered=0;covered<2;++covered) {
        Case c;c.lifetime=lifetime;c.flags=flags;c.covered=covered!=0;c.ticks=2;c.matrix[3][2]=.125f;cases.push_back(c);
    }
    for(unsigned i=0;i<8;++i){Case c;c.show=(i&1)!=0;c.covered=(i&2)!=0;c.flags=i%4;c.lifetime=i%4;c.layout=i%4;c.ticks=2;c.mutation=i%6+1;cases.push_back(c);}
    for(unsigned tag=Covered;tag<=Edge;++tag){Case c;c.covered=true;c.fault=tag;faults.push_back(c);}
    return run(host,"gameui_projection_lifecycle_composed",cases,true,faults);
}
