#include <cstring>
#include <new>
#include <string>
#include <limits>
#include <CEGUI.h>
#include <OgreVector3.h>
#include "GameUI.h"
#include "TextEvent.h"
#include "TLinkedList.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(CTextEvent*,oldTextEvent,(CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour,bool),"_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
extern "C" CTextEvent* newTextEvent(CGameUI*,const Ogre::Vector3&,const std::string&,float,float,CEGUI::colour,CEGUI::colour,bool) __asm__("_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b");
TL_FUNCTION(createEvent,"_ZN10CTextEvent10createTextEP7CGameUIPN5CEGUI6WindowE")
TL_FUNCTION(editorMode,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(coreConstructor,"_ZN10CRunicCoreC1Ev")
extern "C" char allocLinked[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeLinked[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char textLinked[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char fontLinked[] __asm__("_ZNK5CEGUI6Window7getFontEb");
extern "C" char extentLinked[] __asm__("_ZN5CEGUI4Font13getTextExtentERKNS_6StringEf");
extern "C" char sizeLinked[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char propertyLinked[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char addLinked[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char removeLinked[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
namespace {
struct Case {unsigned pool,flags,text,value,mutation,fault;};
struct Stop{};struct List{TLinkedListNode<CTextEvent*>*head;};
const Case*c;autotest::Capture*cap;CGameUI*ui;CTextEvent*event;List*freeList;List*activeList;
CEGUI::Window*windows[5];CEGUI::Font*fonts[2];void*resource;unsigned calls,allocations,frees;void*allocated[16];size_t allocatedSizes[16];bool freed[16];
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void ptr(const void*p){cap->addPointer(p);}
void str(const CEGUI::String& x){n(x.length());for(size_t i=0;i<x.length();++i)n(x[i]);}
void step(int x){n(x);if(++calls==c->fault)throw Stop();}
void observeColour(const CEGUI::colour&x){f(x.getRed());f(x.getGreen());f(x.getBlue());f(x.getAlpha());}
void* allocate(size_t sz,const char*,int,const char*){step(1);n(sz);if(allocations==16)_exit(70);void*p=autotest::allocate(sz);std::memset(p,0xa5,sz);allocated[allocations]=p;allocatedSizes[allocations]=sz;freed[allocations++]=false;ptr(p);return p;}
void deallocate(void*p){step(2);ptr(p);for(unsigned i=0;i<allocations;++i)if(allocated[i]==p){if(freed[i])_exit(71);if(allocatedSizes[i]==24)cap->add(p,24);freed[i]=true;++frees;return;} // initial pool nodes also belong to the arena
 if(!autotest::inArena(p))_exit(72);cap->add(p,24);++frees;
}
void core(void*p){step(3);ptr(p);at<unsigned long long>(p,8)=0x1122334455667788ULL;}
void created(CTextEvent*p,CGameUI*g,CEGUI::Window*w){step(4);ptr(p);ptr(g);ptr(w);cap->addText(p->m_Text);observeColour(p->m_Colour28);observeColour(p->m_Colour40);f(p->m_Value60);f(p->m_Value64);f(p->m_Value68);n(p->m_Flag80);n(p->m_Flag81);n(p->m_Flag82);event=p;p->m_pWindow=windows[0];if(c->mutation==1){p->m_Flag80=false;p->m_Flag81=false;}}
void text(CEGUI::Window*p,const CEGUI::String&x){step(5);ptr(p);str(x);if(c->mutation==2)event->m_pWindow=windows[1];}
CEGUI::Font*font(const CEGUI::Window*p,bool flag){step(6);ptr(p);n(flag);if(c->mutation==3)event->m_Value64=-2.f;return fonts[c->flags&1];}
float extent(CEGUI::Font*p,const CEGUI::String&x,float scale){step(7);ptr(p);str(x);f(scale);if(c->mutation==4)event->m_pWindow=windows[1];return 3.25f+x.length()*2.5f;}
void size(CEGUI::Window*p,const CEGUI::UVector2&x){step(8);ptr(p);f(x.d_x.d_scale);f(x.d_x.d_offset);f(x.d_y.d_scale);f(x.d_y.d_offset);if(c->mutation==5)event->m_Value68=-5.f;}
void property(void*p,const CEGUI::String&name,const CEGUI::String&value){step(9);ptr(p);str(name);str(value);if(c->mutation==6)event->m_pWindow=windows[1];}
bool editor(void*p){step(10);ptr(p);if(c->mutation==7)at<CEGUI::Window*>(ui,0x488)=windows[4];return c->flags&4;}
void add(CEGUI::Window*p,CEGUI::Window*child){step(11);ptr(p);ptr(child);if(c->mutation==8){event->m_Value60=std::numeric_limits<float>::infinity();event->m_Value68=17.f;}if(c->mutation==9){event->m_Value68=0.f;event->m_Flag80=true;event->m_Flag81=true;}if(c->mutation==10){at<CEGUI::Window*>(ui,0x488)=windows[4];event->m_pWindow=windows[1];}}
void remove(CEGUI::Window*p,CEGUI::Window*child){step(12);ptr(p);ptr(child);}
void list(List*l){unsigned count=0;for(TLinkedListNode<CTextEvent*>*p=l->head;p;p=p->m_pNext){if(++count>6)_exit(73);ptr(p);ptr(p->m_Data);ptr(p->m_pPrevious);ptr(p->m_pNext);}n(count);}
void side(void*raw,autotest::Capture&out,bool ours){c=(Case*)raw;cap=&out;calls=allocations=frees=0;autotest::g_arenaUsed=0;
 ui=(CGameUI*)autotest::allocate(0x1b00);resource=autotest::allocate(128);for(unsigned i=0;i<5;++i)windows[i]=(CEGUI::Window*)autotest::allocate(2048);for(unsigned i=0;i<2;++i){fonts[i]=(CEGUI::Font*)autotest::allocate(1024);at<float>(fonts[i],0x278)=10.f+3*i;at<float>(fonts[i],0x27c)=-2.f-i;}
 freeList=(List*)autotest::allocate(sizeof(List));activeList=(List*)autotest::allocate(sizeof(List));
 event=(CTextEvent*)autotest::allocate(sizeof(CTextEvent));std::memset(event,0xa5,sizeof(CTextEvent));::new(&event->m_Text)std::string("old pooled text");::new(&event->m_Colour28)CEGUI::colour(.1f,.2f,.3f,.4f);::new(&event->m_Colour40)CEGUI::colour(.9f,.8f,.7f,.6f);event->m_pWindow=windows[0];event->m_Flag80=c->flags&1;event->m_Flag81=c->flags&2;event->m_Flag82=c->flags&4;
 TLinkedListNode<CTextEvent*>*previous=0;for(unsigned i=0;i<c->pool;++i){TLinkedListNode<CTextEvent*>*p=(TLinkedListNode<CTextEvent*>*)autotest::allocate(24);p->m_Data=event;p->m_pPrevious=previous;if(previous)previous->m_pNext=p;else freeList->head=p;previous=p;}
 if(c->flags&8){activeList->head=(TLinkedListNode<CTextEvent*>*)autotest::allocate(24);activeList->head->m_Data=event;}
 at<List*>(ui,0x1698)=freeList;at<List*>(ui,0x16a0)=activeList;at<CEGUI::Window*>(ui,0x470)=windows[2];at<CEGUI::Window*>(ui,0x488)=windows[3];at<void*>(ui,0x1308)=resource;
 std::string input;switch(c->text){case 0:break;case 1:input="123 critical";break;case 2:input="\xd0\x96\xe2\x98\x83";break;case 3:input=std::string("A\0B",3);break;default:input=std::string(96,'X');break;}
 Ogre::Vector3 position(1.25f,-3.5f,0.f);CEGUI::colour first(.2f,.4f,.8f,.6f),second(.9f,.3f,.1f,.5f);float values[]={-10.f,-0.f,.5f,1.f,255.f,1000.f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float scales[]={0.f,1.f,-1.f,2.25f};
 detour::Set d;TL_REDIRECT(d,createEvent,&created);TL_REDIRECT(d,editorMode,&editor);TL_REDIRECT(d,coreConstructor,&core);
 d.redirect(allocLinked,allocLinked,&allocate);d.redirect(freeLinked,freeLinked,&deallocate);d.redirect(textLinked,textLinked,&text);d.redirect(fontLinked,fontLinked,&font);d.redirect(extentLinked,extentLinked,&extent);d.redirect(sizeLinked,sizeLinked,&size);d.redirect(propertyLinked,propertyLinked,&property);d.redirect(addLinked,addLinked,&add);d.redirect(removeLinked,removeLinked,&remove);if(d.failed())_exit(74);
 bool threw=false;try{autotest::invoke(out,ours?&newTextEvent:&oldTextEvent,ui,position,input,scales[c->value%4],values[c->value],first,second,bool(c->flags&8));}catch(const Stop&){threw=true;}catch(...){_exit(75);}
 n(threw);n(calls);n(allocations);n(frees);for(unsigned i=0;i<allocations;++i){ptr(allocated[i]);n(freed[i]);}list(freeList);list(activeList);cap->addText(input);
 // Observe established fields, not undefined padding or allocator/vtable addresses.
 f(event->m_Value10);f(event->m_Value14);f(event->m_Value18);cap->addText(event->m_Text);observeColour(event->m_Colour28);observeColour(event->m_Colour40);f(event->m_Value60);f(event->m_Value64);f(event->m_Value68);f(event->m_Unrecovered6C);f(event->m_Value70);ptr(event->m_pWindow);n(event->m_Flag80);n(event->m_Flag81);n(event->m_Flag82);ptr(at<void*>(ui,0x470));ptr(at<void*>(ui,0x488));
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(gameui_text_event_production){autotest::Coverage cv("gameui_text_event_production",(uint64_t)(uintptr_t)&oldTextEvent);for(unsigned pool=0;pool<3;++pool)for(unsigned flags=0;flags<16;++flags)for(unsigned text=0;text<5;++text)for(unsigned value=0;value<8;++value){Case c={pool,flags,text,value,(pool+flags+text+value)%11,0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){host->log("    text event %u/%u/%u/%u mutation %u exits %d/%d issues %u/%u lengths %u/%u\n",pool,flags,text,value,c.mutation,x.childStatus,y.childStatus,x.capture.issue,y.capture.issue,x.capture.length,y.capture.length);cv.report(host);return 1;}}cv.report(host);return 0;}

TL_TEST(gameui_text_event_callback_matrix){autotest::Coverage cv("gameui_text_event_callback_matrix",(uint64_t)(uintptr_t)&oldTextEvent);for(unsigned pool=0;pool<3;++pool)for(unsigned flags=0;flags<16;++flags)for(unsigned mutation=0;mutation<11;++mutation)for(unsigned value=0;value<8;++value){Case c={pool,flags,(pool+flags+mutation+value)%5,value,mutation,0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){host->log("    text callback %u/%u/%u/%u exits %d/%d\n",pool,flags,mutation,value,x.childStatus,y.childStatus);cv.report(host);return 1;}}cv.report(host);return 0;}
TL_TEST(gameui_text_event_expected_exceptions){unsigned count=0;for(unsigned pool=0;pool<3;++pool)for(unsigned fault=1;fault<=(pool?10:12);++fault)for(unsigned text=0;text<5;++text){Case c={pool,1,text,0,0,fault};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(!x.reportValid||!y.reportValid||x.childStatus||y.childStatus||!x.capture.callStarted||!y.capture.callStarted||x.capture.callCompleted||y.capture.callCompleted||x.capture.issue||y.capture.issue||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length)){host->log("    text unwind %u/%u/%u exits %d/%d completed %u/%u issues %u/%u lengths %u/%u\n",pool,fault,text,x.childStatus,y.childStatus,x.capture.callCompleted,y.capture.callCompleted,x.capture.issue,y.capture.issue,x.capture.length,y.capture.length);return 1;}++count;}host->log("    EXPECTED TEXT EVENT EXCEPTIONS: %u matching unwinds, not normal coverage\n",count);return 0;}
