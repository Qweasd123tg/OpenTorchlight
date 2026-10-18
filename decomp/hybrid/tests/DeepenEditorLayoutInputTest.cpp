#include <string>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "Detour.h"
#define protected public
#include "Layout.h"
#include "LayoutDescriptor.h"
#undef protected
TL_ORIGINAL(void,diOld,(CLayoutDescriptor*,CEditorBaseObject*,unsigned,CEditorBaseObject*),"_ZN17CLayoutDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
extern "C" void diNew(CLayoutDescriptor*,CEditorBaseObject*,unsigned,CEditorBaseObject*) __asm__("_ZN17CLayoutDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_");
TL_FUNCTION(diBase,"_ZN29CPositionableObjectDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_FUNCTION(diProcess,"_ZN7CLayout13processInputsEjP17CEditorBaseObject")
TL_FUNCTION(diStart,"_ZN7CLayout5startEv")
TL_FUNCTION(diStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(diPause,"_ZN7CLayout5pauseEv")
TL_FUNCTION(diBack,"_ZN7CLayout14startBackwardsEv")
TL_FUNCTION(diEnabled,"_ZN16CSceneNodeObject10setEnabledEb")
TL_FUNCTION(diVisible,"_ZN7CLayout10setVisibleEb")
TL_FUNCTION(diBroadcast,"_ZN17CEditorBaseObject14BroadcastEventEj")
extern "C" void*diLayoutTable[] __asm__("_ZTV7CLayout");
extern "C" void*diObjectTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case{unsigned event,seed;};autotest::Capture*cap;CLayout*layout;CLayoutDescriptor*descriptor;CEditorBaseObject*sender;unsigned event,seed,calls;
void n(unsigned x){cap->add(&x,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}void record(unsigned e,void*p){++calls;n(e);if(p!=layout)invalid();}
struct Node:Ogre::SceneNode{Node():Ogre::SceneNode(NULL){}virtual void _update(bool children,bool parent){n(11);n(children);n(parent);++calls;if(!children||!parent)invalid();}};
void base(CPositionableObjectDescriptor*p,CEditorBaseObject*o,unsigned e,CEditorBaseObject*s){n(1);++calls;n(e);if(p!=descriptor||o!=layout||e!=event||s!=sender)invalid();}
bool process(CLayout*p,unsigned e,CEditorBaseObject*s){record(2,p);n(e);if(e!=event||s!=sender)invalid();return seed&1;}
void start(CLayout*p){record(3,p);}void stop(CLayout*p,bool force){record(4,p);n(force);}void pause(CLayout*p){record(5,p);}void back(CLayout*p){record(6,p);}void enabled(CSceneNodeObject*p,bool value){record(7,p);n(value);}void visible(CLayout*p,bool value){record(8,p);n(value);}void broadcast(CEditorBaseObject*p,unsigned e){record(9,p);n(e);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;event=c.event;seed=c.seed;calls=0;layout=static_cast<CLayout*>(autotest::allocate(sizeof(CLayout)));*reinterpret_cast<void***>(layout)=(seed%5==1?diObjectTable:diLayoutTable)+2;descriptor=static_cast<CLayoutDescriptor*>(autotest::allocate(sizeof(CLayoutDescriptor)));sender=seed&2?NULL:reinterpret_cast<CEditorBaseObject*>(descriptor);Node node;layout->m_pSceneNode=&node;CEditorBaseObject*object=seed%5==0?NULL:layout;
 detour::Set d;TL_REDIRECT(d,diBase,&base);TL_REDIRECT(d,diProcess,&process);TL_REDIRECT(d,diStart,&start);TL_REDIRECT(d,diStop,&stop);TL_REDIRECT(d,diPause,&pause);TL_REDIRECT(d,diBack,&back);TL_REDIRECT(d,diEnabled,&enabled);TL_REDIRECT(d,diVisible,&visible);TL_REDIRECT(d,diBroadcast,&broadcast);if(d.failed()){invalid();return;}typedef void(*Fn)(CLayoutDescriptor*,CEditorBaseObject*,unsigned,CEditorBaseObject*);Fn fn=ours?diNew:diOld;if(!autotest::beginInvocation(out,fn))return;fn(descriptor,object,event,sender);out.callCompleted=1;n(calls);if(seed%5<2&&calls)invalid();if(seed%5>=2&&(event==16||event==21)&&calls<3)invalid();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(deepen_editor_layout_input){autotest::Coverage coverage("deepen_editor_layout_input",(uintptr_t)&diOld);for(unsigned e=0;e<36;++e)for(unsigned seed=0;seed<12;++seed){Case c={e<34?e:e==34?0x80000000u:0xffffffffu,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    layout input event%u seed%u issue%u/%u exit%d/%d\n",c.event,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
