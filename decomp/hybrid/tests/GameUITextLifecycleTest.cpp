// Bounded differential receipts for the four pooled text-event lifecycle entries.
// Collaborator detours do not replace any of the four functions under test.
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include <limits>
#include <CEGUI.h>
#include <OgreCamera.h>
#include <OgreSphere.h>
#include <OgreMatrix4.h>
#include "GameUI.h"
#include "TextEvent.h"
#include "TLinkedList.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, oldHide, (CGameUI*), "_ZN7CGameUI14hideTextEventsEv")
TL_ORIGINAL(void, oldReturn, (CGameUI*,CTextEvent*), "_ZN7CGameUI21returnTextEventObjectEP10CTextEvent")
TL_ORIGINAL(void, oldUpdate, (CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool), "_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb")
TL_ORIGINAL(void, oldAdd, (CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour), "_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
extern "C" void newHide(CGameUI*) __asm__("_ZN7CGameUI14hideTextEventsEv");
extern "C" void newReturn(CGameUI*,CTextEvent*) __asm__("_ZN7CGameUI21returnTextEventObjectEP10CTextEvent");
extern "C" void newUpdate(CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool) __asm__("_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb");
extern "C" void newAdd(CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour) __asm__("_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_");
TL_FUNCTION(eventUpdate, "_ZN10CTextEvent6updateEPN5CEGUI6WindowEf")
TL_FUNCTION(projectEvent, "_ZN7CGameUI17getScreenPositionEPKN4Ogre7Vector3ES3_NS0_7Matrix4E")
TL_FUNCTION(produceEvent, "_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
TL_ORIGINAL(CTextEvent*, originalProducer, (CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour,bool), "_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
TL_FUNCTION(settingInt, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(editorMode, "_ZN16CResourceManager18getEditorIsRunningEv")
extern "C" unsigned floatyKey __asm__("KSETTINGS_FLOATY_NUMBERS");
extern "C" char nodeAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char nodeFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char removeWindow[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char positionWindow[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char propertyWindow[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char textWindow[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char fontWindow[] __asm__("_ZNK5CEGUI6Window7getFontEb");
extern "C" char extentFont[] __asm__("_ZN5CEGUI4Font13getTextExtentERKNS_6StringEf");
extern "C" char sizeWindow[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char addWindow[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");

namespace {
typedef TLinkedListNode<CTextEvent*> Node;
struct List { Node* head; };
enum { Hide, Return, Update, Add };
enum { Detach=1, Allocate, Release, Tick, Project, Position, Setting, Visible, Produce,
       Property, Text, Font, Extent, Size, Editor, Attach };
enum { RawBlock, EventBlock, NodeBlock, StringBlock, UIBlock, CameraBlock, TableBlock };
struct Case {
    unsigned kind, layout, pool, windows, value, flags, mutation, text, fault, real, ticks;
    bool allow, visible;
    int setting;
    Case(unsigned k=0) : kind(k),layout(3),pool(2),windows(2),value(4),flags(15),
        mutation(0),text(1),fault(0),real(0),ticks(1),allow(true),visible(true),setting(1) {}
};
struct Stop {};
struct Block { unsigned char* p; unsigned size,type; bool released; };
const Case* current;
autotest::Capture* capture;
Block blocks[96]; unsigned blockCount, callCount, allocCount, freeCount, tickCount, projectCount;
unsigned faultHits, mutationDone;
CGameUI* ui;
CTextEvent* events[8];
CEGUI::Window* windows[12];
CEGUI::Font* fontObject;
List* shells[4]; // free, active, alternate free, alternate active
Node* spare;
void* settings;
void* resource;
Ogre::Camera* cameras[2];
Ogre::Vector3* argumentPosition;
Ogre::Matrix4* argumentMatrix;
std::string* argumentText;
CEGUI::colour* colours[2];

template<class T> T& at(void* p,unsigned offset) { return *reinterpret_cast<T*>(static_cast<char*>(p)+offset); }
void number(unsigned x) { capture->add(&x,sizeof(x)); }
void floating(float x) { capture->add(&x,sizeof(x)); }
void pointer(const void* p) { capture->addPointer(p); }
void require(bool x) { if(!x) _exit(90); }
void step(unsigned tag) { number(tag); ++callCount; if(current->fault==tag) { ++faultHits; throw Stop(); } }
void vector(const Ogre::Vector3& v) { floating(v.x); floating(v.y); floating(v.z); }
void observeColour(const CEGUI::colour& c) { floating(c.getRed());floating(c.getGreen());floating(c.getBlue());floating(c.getAlpha()); }
void ceguiText(const CEGUI::String& s) { number(s.length()); for(size_t i=0;i<s.length();++i)number(s[i]); }
float value(unsigned i) {
    static const unsigned bits[]={0xbf800000u,0x80000000u,0u,1u,0x41280000u,0x7f800000u,0x7fc12345u};
    float result; unsigned b=bits[i%7];std::memcpy(&result,&b,4);return result;
}
void* guarded(unsigned size,unsigned type=RawBlock,unsigned fill=0) {
    require(blockCount<96);
    unsigned char* raw=static_cast<unsigned char*>(autotest::allocate(size+32)); require(raw!=0);
    std::memset(raw,0xd3,16);std::memset(raw+16,fill,size);std::memset(raw+16+size,0x6c,16);
    Block& b=blocks[blockCount++];b.p=raw+16;b.size=size;b.type=type;b.released=false;return b.p;
}
unsigned blockIndex(const void* p) {
    for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p)return i;
    _exit(91);return 0;
}
unsigned eventIndex(const CTextEvent* e) { for(unsigned i=0;i<8;++i)if(events[i]==e)return i;_exit(92);return 0; }
void nodeState(Node* p) { pointer(p);pointer(p->m_Data);pointer(p->m_pNext);pointer(p->m_pPrevious); }
Node* makeNode(CTextEvent* e) { Node* n=static_cast<Node*>(guarded(sizeof(Node),NodeBlock));n->m_Data=e;return n; }
void append(List* l,CTextEvent* e) {
    Node* p=makeNode(e);if(!l->head){l->head=p;return;}Node* tail=l->head;
    unsigned n=0;while(tail->m_pNext){require(++n<12);tail=tail->m_pNext;}tail->m_pNext=p;p->m_pPrevious=tail;
}
void moveShell(unsigned from,unsigned to,unsigned offset) {
    require(!shells[to]->head);shells[to]->head=shells[from]->head;shells[from]->head=0;at<List*>(ui,offset)=shells[to];
}
void forbidVirtual() { _exit(93); }
void* allocateNode(size_t size,const char* file,int line,const char* function) {
    step(Allocate);number(size);number(file!=0);number(line);number(function!=0);
    require(size==sizeof(Node));++allocCount;
    if(!mutationDone && current->mutation==3) {
        // The original captures the destination shell BEFORE calling allocBytes.
        at<List*>(ui,0x1698)=shells[2];mutationDone=1;
    } else if(!mutationDone && current->mutation==4) {
        List* l=at<List*>(ui,0x1698);spare->m_pNext=l->head;
        if(l->head)l->head->m_pPrevious=spare;l->head=spare;mutationDone=1;
    }
    void* p=guarded(size,NodeBlock,0xa5);pointer(p);return p;
}
void releaseNode(void* raw) {
    // No exceptions are injected into the deallocation/no-throw boundary.
    number(Release);++callCount;Node* p=static_cast<Node*>(raw);nodeState(p);
    unsigned i=blockIndex(p);require(blocks[i].type==NodeBlock && !blocks[i].released);
    require(!p->m_pNext && !p->m_pPrevious);blocks[i].released=true;++freeCount;
    if(!mutationDone && current->mutation==2) { moveShell(0,2,0x1698);mutationDone=1; }
}
void detach(CEGUI::Window* parent,CEGUI::Window* child) {
    step(Detach);pointer(parent);pointer(child);
    if(child) {
        pointer(at<void*>(child,0xb0));
        // CEGUI clears only an actual child's parent; an ingame-sheet expiry
        // call may be followed by removal from a different actual parent.
        if(at<CEGUI::Window*>(child,0xb0)==parent)at<CEGUI::Window*>(child,0xb0)=0;
    }
    if(!mutationDone && current->mutation==1) {
        moveShell(1,3,0x16a0);moveShell(0,2,0x1698);mutationDone=1;
    }
}
void updateEvent(CTextEvent* e,CEGUI::Window* sheet,float elapsed) {
    step(Tick);pointer(e);pointer(sheet);floating(elapsed);++tickCount;
    unsigned index=eventIndex(e);floating(e->m_Value68);number(e->m_Flag82);
    e->m_Value68=value(current->value+index);
    if(current->mutation==10)e->m_Flag82=!e->m_Flag82;
    if(current->mutation==11) {
        e->m_Value10=-17.25f-index;e->m_Value14=31.5f+index;e->m_Value18=-0.f;
        e->m_Unrecovered6C=13.25f+index;e->m_pWindow=windows[8+index%2];
    }
    if(current->mutation==12)at<CEGUI::Window*>(ui,0x488)=windows[11];
    if(current->mutation==13) {
        (*argumentMatrix)[index%4][(index+1)%4]=-70.5f-index;argumentPosition->z=11.75f+index;
    }
    if(current->mutation==14) {
        e->m_Value68=10.f;
        if(!mutationDone) {
            // Detach the saved successor safely. The loop must still visit it,
            // then stop at its new null next link, leaving the third node alone.
            Node* first=at<List*>(ui,0x16a0)->head;Node* second=first->m_pNext;
            require(second && second->m_pNext);
            first->m_pNext=second->m_pNext;second->m_pNext->m_pPrevious=first;
            second->m_pNext=second->m_pPrevious=0;shells[3]->head=second;mutationDone=1;
        }
    }
    if(current->mutation==17){e->m_pWindow=0;e->m_Value68=-1.f;}
}
Ogre::Vector3 project(CGameUI* owner,const Ogre::Vector3* p,const Ogre::Vector3* reference,Ogre::Matrix4 matrix) {
    step(Project);pointer(owner);pointer(p);pointer(reference);vector(*p);vector(*reference);
    capture->add(&matrix,sizeof(matrix));number(reference==argumentPosition);
    CTextEvent* e=0;for(unsigned i=0;i<8;++i)if(p==reinterpret_cast<Ogre::Vector3*>(&events[i]->m_Value10))e=events[i];
    require(e!=0);number(eventIndex(e));++projectCount;
    if(current->mutation==15) {
        e->m_Unrecovered6C=-23.5f;e->m_pWindow=windows[9];
        (*argumentMatrix)[3][2]+=2.5f;
    }
    return Ogre::Vector3(87.125f+projectCount*3.f,-19.75f-projectCount,1234.5f);
}
void position(CEGUI::Window* w,const CEGUI::UVector2& p) {
    step(Position);pointer(w);floating(p.d_x.d_scale);floating(p.d_x.d_offset);floating(p.d_y.d_scale);floating(p.d_y.d_offset);
    require(w!=0);std::memcpy(static_cast<char*>(static_cast<void*>(w))+0x200,&p,sizeof(p));
}
int setting(void* p,unsigned key) {
    step(Setting);pointer(p);number(key);number(key==floatyKey);
    if(current->mutation==20)at<Ogre::Camera*>(ui,0x10)=cameras[1];
    return current->setting;
}
bool visible(const Ogre::Camera* camera,const Ogre::Sphere& sphere,Ogre::FrustumPlane* culledBy) {
    step(Visible);pointer(camera);floating(sphere.getRadius());vector(sphere.getCenter());number(culledBy==0);
    if(current->mutation==21) { argumentPosition->x=-101.25f;argumentPosition->z=-0.f;*argumentText=std::string("changed\0text",12); }
    return current->visible;
}
CTextEvent* produce(CGameUI* owner,const Ogre::Vector3& p,const std::string& text,float scale,float duration,CEGUI::colour first,CEGUI::colour second,bool animate) {
    step(Produce);pointer(owner);pointer(&p);pointer(&text);vector(p);capture->addText(text);
    floating(scale);floating(duration);observeColour(first);observeColour(second);number(animate);
    number(&p==argumentPosition);number(&text==argumentText);events[7]->m_Value70=scale;return events[7];
}
void property(void* p,const CEGUI::String& key,const CEGUI::String& v) { step(Property);pointer(p);ceguiText(key);ceguiText(v); }
void text(CEGUI::Window* p,const CEGUI::String& v) { step(Text);pointer(p);ceguiText(v); }
CEGUI::Font* font(const CEGUI::Window* p,bool inherited) { step(Font);pointer(p);number(inherited);return fontObject; }
float extent(CEGUI::Font* p,const CEGUI::String& v,float scale) { step(Extent);pointer(p);ceguiText(v);floating(scale);return 11.25f+v.length()*2.5f; }
void size(CEGUI::Window* p,const CEGUI::UVector2& v) { step(Size);pointer(p);floating(v.d_x.d_scale);floating(v.d_x.d_offset);floating(v.d_y.d_scale);floating(v.d_y.d_offset); }
bool editor(void* p) { step(Editor);pointer(p);return (current->flags&1)!=0; }
void attach(CEGUI::Window* p,CEGUI::Window* child) { step(Attach);pointer(p);pointer(child);at<CEGUI::Window*>(child,0xb0)=p; }

void listState(List* list) {
    pointer(list);pointer(list->head);Node* previous=0;unsigned count=0;
    for(Node* p=list->head;p;p=p->m_pNext) {
        require(++count<=12);unsigned b=blockIndex(p);require(blocks[b].type==NodeBlock && !blocks[b].released);
        require(p->m_pPrevious==previous);nodeState(p);previous=p;
    }
    number(count);unsigned backwards=0;
    for(Node* p=previous;p;p=p->m_pPrevious){require(++backwards<=12);pointer(p);}
    require(backwards==count);number(backwards);
}
void snapshot() {
    number(callCount);number(allocCount);number(freeCount);number(tickCount);number(projectCount);number(mutationDone);
    for(unsigned i=0;i<4;++i)listState(shells[i]);
    number(blockCount);
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];pointer(b.p);number(b.size);number(b.type);number(b.released);
        for(unsigned j=0;j<16;++j)require(b.p[-16+int(j)]==0xd3 && b.p[b.size+j]==0x6c);
        capture->add(b.p-16,16);capture->add(b.p+b.size,16);
        if(b.type==EventBlock) {
            CTextEvent* e=reinterpret_cast<CTextEvent*>(b.p);
            // The only heap-dependent field is the COW string pointer. All
            // other bytes were initialized, including padding and colour caches.
            capture->add(b.p,0x20);capture->addText(e->m_Text);capture->add(b.p+0x28,0x50);
            pointer(e->m_pWindow);capture->add(b.p+0x80,8);
        } else if(b.type==StringBlock)capture->addText(*reinterpret_cast<std::string*>(b.p));
        else if(b.type==NodeBlock)nodeState(reinterpret_cast<Node*>(b.p));
        else if(b.type==CameraBlock){pointer(at<void*>(b.p,0));capture->add(b.p+8,b.size-8);}
        else if(b.type==TableBlock) {
            // Function addresses are fixed fixture wiring, not state. Detect
            // any table corruption without recording process code addresses.
            for(unsigned j=0;j<b.size/sizeof(void*);++j) {
                void* expected=reinterpret_cast<void*>(&forbidVirtual);
                if(b.size==0x340 && j==0x328/sizeof(void*))expected=reinterpret_cast<void*>(&visible);
                require(reinterpret_cast<void**>(b.p)[j]==expected);
            }
        } else capture->add(b.p,b.size);
    }
}
void setup(const Case& c) {
    autotest::g_arenaUsed=0;blockCount=callCount=allocCount=freeCount=tickCount=projectCount=faultHits=mutationDone=0;
    ui=static_cast<CGameUI*>(guarded(0x1b00,UIBlock,0x5a));
    settings=guarded(0x180);resource=guarded(128);
    void** eventTable=static_cast<void**>(guarded(0x40,TableBlock));
    for(unsigned i=0;i<8;++i)eventTable[i]=reinterpret_cast<void*>(&forbidVirtual);
    void** cameraTable=static_cast<void**>(guarded(0x340,TableBlock));
    for(unsigned i=0;i<0x340/8;++i)cameraTable[i]=reinterpret_cast<void*>(&forbidVirtual);
    cameraTable[0x328/8]=reinterpret_cast<void*>(&visible);
    for(unsigned i=0;i<2;++i){cameras[i]=static_cast<Ogre::Camera*>(guarded(0x100,CameraBlock));at<void**>(cameras[i],0)=cameraTable;}
    for(unsigned i=0;i<12;++i)windows[i]=static_cast<CEGUI::Window*>(guarded(0x400));
    fontObject=static_cast<CEGUI::Font*>(guarded(0x400));at<float>(fontObject,0x278)=13.5f;at<float>(fontObject,0x27c)=-2.25f;
    for(unsigned i=0;i<4;++i)shells[i]=static_cast<List*>(guarded(sizeof(List)));
    for(unsigned i=0;i<8;++i) {
        CTextEvent* e=static_cast<CTextEvent*>(guarded(sizeof(CTextEvent),EventBlock,0xa5));events[i]=e;at<void**>(e,0)=eventTable;
        ::new(&e->m_Text)std::string(i%2?"unchanged event":"retained label");
        ::new(&e->m_Colour28)CEGUI::colour(.13f+i*.01f,.27f,.39f,.51f);
        ::new(&e->m_Colour40)CEGUI::colour(.93f,.71f,.49f,.17f+i*.01f);
        e->m_Value10=1.25f+i;e->m_Value14=-4.5f-i;e->m_Value18=-0.f;
        e->m_Value60=1.f;e->m_Value64=.75f;e->m_Value68=67.25f;
        e->m_Unrecovered6C=7.5f+i*3.25f;e->m_Value70=.125f+i*.25f;
        e->m_Flag80=false;e->m_Flag81=false;e->m_Flag82=(c.flags&(1u<<i))!=0;
        unsigned w=c.windows==3?i%3:c.windows;
        e->m_pWindow=w?windows[i]:0;at<CEGUI::Window*>(windows[i],0xb0)=w==2?windows[10]:0;
    }
    for(unsigned i=0;i<c.pool;++i)append(shells[0],events[5+i]);
    if(c.kind==Return) {
        if(c.layout==9) { /* Empty active list; valid unlisted event. */ }
        else if(c.layout==0){append(shells[1],events[1]);append(shells[1],events[2]);}
        else if(c.layout<=4) {
            for(unsigned i=0;i<4;++i) {
                unsigned id=i+1;
                if((c.layout==1&&i==0)||(c.layout==2&&i==2)||(c.layout==3&&i==3)||(c.layout==4&&(i==0||i==2)))id=0;
                append(shells[1],events[id]);
            }
        } else {
            // Free-list head/interior/tail hit, including active/free overlap.
            shells[0]->head=0;for(unsigned i=0;i<3;++i)append(shells[0],events[i==((c.layout-5)%3)?0:5+i]);
            append(shells[1],events[c.layout==8?0:1]);append(shells[1],events[2]);
        }
    } else if(c.kind==Add) {
        // Real-producer integration uses a nonempty pool: no fake constructor.
        if(c.real && !shells[0]->head)append(shells[0],events[5]);
        append(shells[1],events[0]);
    } else {
        const unsigned counts[]={0,1,2,4};for(unsigned i=0;i<counts[c.layout%4];++i)append(shells[1],events[i]);
    }
    spare=makeNode(events[7]);
    at<List*>(ui,0x1698)=shells[0];at<List*>(ui,0x16a0)=shells[1];at<void*>(ui,0x78)=settings;
    at<Ogre::Camera*>(ui,0x10)=cameras[0];at<CEGUI::Window*>(ui,0x488)=windows[10];
    at<CEGUI::Window*>(ui,0x470)=windows[11];at<void*>(ui,0x1308)=resource;
    // Pause is unrelated state: neither pause value changes these four APIs.
    at<bool>(ui,0x1999)=(c.text&1)!=0;
    argumentPosition=static_cast<Ogre::Vector3*>(guarded(sizeof(Ogre::Vector3)));
    ::new(argumentPosition)Ogre::Vector3(value(c.value),-37.25f,12.125f);
    argumentMatrix=static_cast<Ogre::Matrix4*>(guarded(sizeof(Ogre::Matrix4)));
    for(unsigned r=0;r<4;++r)for(unsigned col=0;col<4;++col)(*argumentMatrix)[r][col]=(r*4+col)*1.125f-7.5f;
    (*argumentMatrix)[1][2]=-0.f;
    argumentText=static_cast<std::string*>(guarded(sizeof(std::string),StringBlock));::new(argumentText)std::string();
    switch(c.text%5) {case 0:break;case 1:*argumentText="123 critical";break;case 2:*argumentText="\xd0\x96\xe2\x98\x83";break;case 3:*argumentText=std::string("A\0B",3);break;default:*argumentText=std::string(80,'Q');break;}
    for(unsigned i=0;i<2;++i)colours[i]=static_cast<CEGUI::colour*>(guarded(sizeof(CEGUI::colour),RawBlock,0xa5));
    ::new(colours[0])CEGUI::colour(.21f,.43f,.65f,.87f);::new(colours[1])CEGUI::colour(.92f,.74f,.56f,.38f);
    if(c.real && c.kind==Update) {
        for(unsigned i=0;i<4;++i) {
            events[i]->m_Value68=c.value==0?1.f:(c.value==1?200.f:0.f);
            events[i]->m_Flag80=(c.flags&1)!=0;events[i]->m_Flag81=(c.flags&2)!=0;
            // Alternate actual parent exercises the expiry double-detach path.
            at<CEGUI::Window*>(windows[i],0xb0)=(i&1)?windows[11]:windows[10];
        }
    }
}

void side(void* raw,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(raw);capture=&out;setup(*current);
    detour::Set d;
    d.redirect(nodeAlloc,nodeAlloc,&allocateNode);d.redirect(nodeFree,nodeFree,&releaseNode);
    d.redirect(removeWindow,removeWindow,&detach);d.redirect(positionWindow,positionWindow,&position);
    d.redirect(propertyWindow,propertyWindow,&property);
    TL_REDIRECT(d,projectEvent,&project);TL_REDIRECT(d,settingInt,&setting);
    if(!(current->real && current->kind==Update))TL_REDIRECT(d,eventUpdate,&updateEvent);
    if(current->real && current->kind==Add) {
        // Both parents enter the actual original accepted producer. Do not
        // patch its original entry and then accidentally recurse into a spy.
        if(produceEvent_linked!=produceEvent_original)d.redirect(produceEvent_linked,produceEvent_linked,&originalProducer);
        d.redirect(textWindow,textWindow,&text);d.redirect(fontWindow,fontWindow,&font);
        d.redirect(extentFont,extentFont,&extent);d.redirect(sizeWindow,sizeWindow,&size);
        d.redirect(addWindow,addWindow,&attach);TL_REDIRECT(d,editorMode,&editor);
    } else TL_REDIRECT(d,produceEvent,&produce);
    require(!d.failed());bool threw=false;
    try {
        for(unsigned tick=0;tick<current->ticks;++tick) {
            number(0x100+tick);
            if(current->kind==Hide) {
                void(*fn)(CGameUI*)=ours?&newHide:&oldHide;
                if(!tick)require(autotest::beginInvocation(out,fn));fn(ui);
            } else if(current->kind==Return) {
                void(*fn)(CGameUI*,CTextEvent*)=ours?&newReturn:&oldReturn;
                if(!tick)require(autotest::beginInvocation(out,fn));fn(ui,events[0]);
            } else if(current->kind==Update) {
                void(*fn)(CGameUI*,float,Ogre::Vector3&,Ogre::Matrix4&,bool)=ours?&newUpdate:&oldUpdate;
                if(!tick)require(autotest::beginInvocation(out,fn));
                float elapsed=current->real?.125f:(tick?-.25f:value(current->text));
                fn(ui,elapsed,*argumentPosition,*argumentMatrix,current->allow);
            } else {
                void(*fn)(CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour)=ours?&newAdd:&oldAdd;
                if(!tick)require(autotest::beginInvocation(out,fn));
                fn(ui,*argumentPosition,*argumentText,value((current->value+2)%7),value(current->value),*colours[0],*colours[1]);
            }
            // Completion covers every requested repeat/tick, not only the first.
            snapshot();
        }
        out.callCompleted=1;
    } catch(const Stop&) { threw=true; } catch(...) { _exit(94); }
    number(threw);number(faultHits);snapshot();
    require(bool(current->fault)==threw);
}
void originalSide(void* p,autotest::Capture& out) { side(p,out,false); }
void candidateSide(void* p,autotest::Capture& out) { side(p,out,true); }
uint64_t address(unsigned kind) {
    switch(kind){case Hide:return (uint64_t)(uintptr_t)&oldHide;case Return:return (uint64_t)(uintptr_t)&oldReturn;
        case Update:return (uint64_t)(uintptr_t)&oldUpdate;default:return (uint64_t)(uintptr_t)&oldAdd;}
}
int run(const tlhybrid_host* host,const char* name,unsigned kind,const std::vector<Case>& cases,const std::vector<Case>& faults) {
    autotest::Coverage coverage(name,address(kind));
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        if(coverage.observe(host,a,b)) {
            size_t first=0;while(first<a.capture.length && first<b.capture.length && a.capture.data[first]==b.capture.data[first])++first;
            host->log("    lifecycle %s case %u layout %u value %u flags %u mutation %u real %u: exits %d/%d issues %u/%u lengths %u/%u first %u\n",
                name,i,c.layout,c.value,c.flags,c.mutation,c.real,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,
                (unsigned)a.capture.length,(unsigned)b.capture.length,(unsigned)first);coverage.report(host);return 1;
        }
    }
    coverage.report(host);if(coverage.completed<20)return 1;
    unsigned unwinds=0;
    for(unsigned i=0;i<faults.size();++i) {
        Case c=faults[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        bool ok=a.reportValid && b.reportValid && !a.childStatus && !b.childStatus && !a.capture.issue && !b.capture.issue &&
            a.capture.callStarted==1 && b.capture.callStarted==1 && !a.capture.callCompleted && !b.capture.callCompleted &&
            a.capture.callTarget==address(kind) && host->comparison_pair && host->comparison_pair(address(kind),b.capture.callTarget) &&
            a.capture.length==b.capture.length && !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
        if(!ok){host->log("    lifecycle %s expected unwind %u tag %u failed: exits %d/%d complete %u/%u\n",name,i,c.fault,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted);return 1;}
        ++unwinds;
    }
    host->log("    %s: %u separately checked expected unwinds, excluded from normal coverage\n",name,unwinds);return 0;
}
}

TL_TEST(gameui_text_lifecycle_hide) {
    std::vector<Case> cases,faults;
    // 4 lengths x 3 window/parent branches x 2 pool lengths, deliberately bounded.
    for(unsigned length=0;length<4;++length)for(unsigned window=0;window<3;++window)for(unsigned pool=0;pool<2;++pool) {
        Case c(Hide);c.layout=length;c.windows=window;c.pool=pool?2:0;c.text=length+window;c.ticks=2;cases.push_back(c);
    }
    for(unsigned mutation=1;mutation<=4;++mutation){Case c(Hide);c.mutation=mutation;c.windows=2;cases.push_back(c);}
    Case mixed(Hide);mixed.windows=3;cases.push_back(mixed);
    const unsigned tags[]={Detach,Allocate};for(unsigned i=0;i<2;++i){Case c(Hide);c.fault=tags[i];faults.push_back(c);}
    return run(host,"gameui_text_lifecycle_hide",Hide,cases,faults);
}
TL_TEST(gameui_text_lifecycle_return) {
    std::vector<Case> cases,faults;
    for(unsigned layout=0;layout<10;++layout)for(unsigned window=0;window<3;++window) {
        Case c(Return);c.layout=layout;c.windows=window;c.pool=layout%3;c.ticks=2;c.text=layout;cases.push_back(c);
    }
    for(unsigned mutation=1;mutation<=4;++mutation){Case c(Return);c.layout=2;c.mutation=mutation;cases.push_back(c);}
    const unsigned tags[]={Detach,Allocate};for(unsigned i=0;i<2;++i){Case c(Return);c.layout=2;c.fault=tags[i];faults.push_back(c);}
    return run(host,"gameui_text_lifecycle_return",Return,cases,faults);
}
TL_TEST(gameui_text_lifecycle_update) {
    std::vector<Case> cases,faults;
    // Exact seven-way float boundary matrix, four independent filter states.
    for(unsigned v=0;v<7;++v)for(unsigned flags=0;flags<4;++flags) {
        Case c(Update);c.layout=1;c.value=v;c.flags=flags&1;c.allow=(flags&2)!=0;c.text=v;cases.push_back(c);
    }
    for(unsigned mutation=10;mutation<=17;++mutation) {
        if(mutation==16)continue;
        Case c(Update);c.mutation=mutation;c.value=4;c.flags=15;c.allow=mutation!=10;c.layout=3;cases.push_back(c);
    }
    for(unsigned mutation=1;mutation<=4;++mutation) {
        Case c(Update);c.mutation=mutation;c.allow=false;c.flags=0;cases.push_back(c);
    }
    for(unsigned window=0;window<4;++window){Case c(Update);c.windows=window;c.value=0;c.allow=false;c.flags=0;cases.push_back(c);}
    for(unsigned v=0;v<7;++v){Case c(Update);c.value=v;c.flags=5;c.allow=false;c.ticks=2;c.windows=2;cases.push_back(c);}
    Case empty(Update);empty.layout=0;cases.push_back(empty);
    // Real original CTextEvent::update: expiry, motion, no-animation, alpha,
    // actual-parent vs sheet removal, and the following lifecycle recycle.
    for(unsigned flags=0;flags<4;++flags)for(unsigned v=0;v<3;++v) {
        Case c(Update);c.real=1;c.flags=flags;c.value=v;c.windows=2;c.ticks=2;cases.push_back(c);
    }
    const unsigned tags[]={Tick,Project,Position,Detach,Allocate};
    for(unsigned i=0;i<5;++i){Case c(Update);c.layout=1;c.value=i<3?4:0;c.fault=tags[i];faults.push_back(c);}
    return run(host,"gameui_text_lifecycle_update",Update,cases,faults);
}
TL_TEST(gameui_text_lifecycle_add) {
    std::vector<Case> cases,faults;const int settingsValues[]={0,1,-1,7};
    for(unsigned s=0;s<4;++s)for(unsigned visible=0;visible<2;++visible)for(unsigned text=0;text<5;++text) {
        Case c(Add);c.setting=settingsValues[s];c.visible=visible!=0;c.text=text;c.value=(s+text)%7;
        c.mutation=20;cases.push_back(c);
    }
    for(unsigned v=0;v<7;++v){Case c(Add);c.value=v;c.text=v%5;c.mutation=21;cases.push_back(c);}
    for(unsigned flags=0;flags<2;++flags)for(unsigned text=0;text<5;++text) {
        Case c(Add);c.real=1;c.flags=flags;c.text=text;c.value=4;c.windows=2;cases.push_back(c);
    }
    const unsigned tags[]={Setting,Visible,Produce};for(unsigned i=0;i<3;++i){Case c(Add);c.fault=tags[i];faults.push_back(c);}
    return run(host,"gameui_text_lifecycle_add",Add,cases,faults);
}
