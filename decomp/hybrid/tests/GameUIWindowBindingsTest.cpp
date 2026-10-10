#include <cstring>
#include <string>
#include <vector>
#include <new>
#include <CEGUI.h>
#include <OgreException.h>
#include <OgreLogManager.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, oldEvents,(CGameUI*,CEGUI::Window*),"_ZN7CGameUI16mapEventHandlersEPN5CEGUI6WindowE")
TL_ORIGINAL(void, oldFunctions,(CGameUI*,CEGUI::Window*),"_ZN7CGameUI14mapToFunctionsEPN5CEGUI6WindowE")
extern "C" void newEvents(CGameUI*,CEGUI::Window*) __asm__("_ZN7CGameUI16mapEventHandlersEPN5CEGUI6WindowE");
extern "C" void newFunctions(CGameUI*,CEGUI::Window*) __asm__("_ZN7CGameUI14mapToFunctionsEPN5CEGUI6WindowE");
TL_FUNCTION(click,"_ZN7CGameUI14handle_onClickERKN5CEGUI9EventArgsE")
#define SDK(N,S) extern "C" char N[] __asm__(S)
SDK(presentFn,"_ZNK5CEGUI11PropertySet17isPropertyPresentERKNS_6StringE");
SDK(propertyFn,"_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE");
SDK(logSingletonFn,"_ZN4Ogre10LogManager12getSingletonEv");
SDK(logFn,"_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
SDK(slotDtorFn,"_ZN5CEGUI14SubscriberSlotD1Ev");
SDK(slotDtor2Fn,"_ZN5CEGUI14SubscriberSlotD2Ev");
SDK(copyFn,"_ZN4Ogre9ExceptionC1ERKS0_");
SDK(copy2Fn,"_ZN4Ogre9ExceptionC2ERKS0_");
#undef SDK
namespace {
struct Stop { int reason; explicit Stop(int r):reason(r){} };
struct Case {
 unsigned kind, mode, name, mutation, fault, boundary, faultWindow;
 Case(unsigned k):kind(k),mode(0),name(0),mutation(0),fault(0),boundary(0),faultWindow(0){}
};
struct Block { unsigned char* p; unsigned n; };
Block blocks[32];unsigned blockCount;
Case* cs;autotest::Capture* cap;CGameUI* ui;CEGUI::Window* w[7];void** vt;
CEGUI::Window** children;CEGUI::Window** alternate;void* logger;
unsigned reads[7],calls,copyCount;bool ours,armed;detour::Set* recursionPatch;
typedef void (*Fn)(CGameUI*,CEGUI::Window*);
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(unsigned x){cap->add(&x,sizeof(x));}
struct TestOgre : Ogre::Exception { TestOgre():Ogre::Exception(17,std::string("failure\0tail",12),"binding-test"){} ~TestOgre() throw(){n(9);} };
void require(bool ok){if(!ok)cap->issue=autotest::Capture::InvalidReport;}
void* block(unsigned bytes){unsigned char* p=static_cast<unsigned char*>(autotest::allocate(bytes+32));if(!p||blockCount==32)_exit(80);memset(p,0x6d,bytes+32);blocks[blockCount].p=p;blocks[blockCount++].n=bytes;return p+16;}
void ptr(const void* p){cap->addPointer(p);}
unsigned index(const void* p){for(unsigned i=0;i<7;++i)if(p==w[i])return i;require(false);return 0;}
void text(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
void observation(unsigned tag,const void* self){n(tag);n(++calls);ptr(self);for(unsigned i=0;i<7;++i)ptr(at<void*>(w[i],0x1d8));}
Fn fn(){return cs->kind?(ours?newFunctions:oldFunctions):(ours?newEvents:oldEvents);}
void throwNow(unsigned type){if(type==1)throw TestOgre();if(type==2)throw Stop(29);throw 43;}
void recursiveStop(CGameUI* self,CEGUI::Window* window){observation(8,window);ptr(self);throwNow(cs->fault);}
void fault(unsigned boundary,unsigned id){if(cs->fault&&(cs->boundary==boundary||(cs->boundary==5&&boundary==2))&&id==cs->faultWindow)throwNow(cs->fault);}
std::string* names(){return reinterpret_cast<std::string*>(0x14b7dc0);}
std::string value(unsigned id,unsigned read){
 if(cs->mode==1)return "";
 if(cs->mode==2)return "not-a-layout-function";
 std::string s=names()[(cs->name+id)%97];
 if(cs->mode==3)for(unsigned i=0;i<s.size();++i)if(s[i]>='A'&&s[i]<='Z')s[i]+='a'-'A';
 if(cs->mode==4)for(unsigned i=0;i<s.size();i+=2)if(s[i]>='A'&&s[i]<='Z')s[i]+='a'-'A';
 if(cs->mode==5)return std::string("GUIEXITGAME\0IGNORED",19);
 if(cs->mutation==3&&read>1)s=names()[96];
 if(cs->mutation==4&&read>1)s="";
 if(cs->mutation==5&&read>1)s="unmatched-after-first-read";
 return s;
}
bool present(void* self,const CEGUI::String& key){unsigned id=index(self);observation(1,self);text(key);fault(1,id);
 if(id==1&&cs->mutation==1){at<void*>(w[0],0x78)=alternate;at<void*>(w[0],0x80)=alternate+1;}
 if(id==1&&cs->mutation==2){at<void*>(w[0],0x80)=children+5;}
 if(id==1&&cs->mutation==8&&!armed){armed=true;Fn f=fn();recursionPatch->redirect(reinterpret_cast<char*>(f),reinterpret_cast<char*>(f),&recursiveStop);}
 return cs->mode!=6;
}
CEGUI::String property(void* self,const CEGUI::String& key){unsigned id=index(self);observation(2,self);text(key);++reads[id];n(reads[id]);fault(reads[id]==1?2:3,id);std::string s=value(id,reads[id]);CEGUI::String out(reinterpret_cast<const CEGUI::utf8*>(s.data()),s.size());text(out);return out;}
CEGUI::Event::Connection subscribe(void* self,const CEGUI::String& name,const CEGUI::SubscriberSlot& slot){observation(3,self);text(name);void* impl=at<void*>(const_cast<CEGUI::SubscriberSlot*>(&slot),0);require(impl!=0);void* target=at<void*>(impl,8);bool validTarget=target==reinterpret_cast<void*>(click_original)||target==reinterpret_cast<void*>(click_linked);n(validTarget);n(at<unsigned long>(impl,16));ptr(at<void*>(impl,24));unsigned id=0;for(;id<7;++id)if(self==static_cast<char*>(static_cast<void*>(w[id]))+0x38)break;require(id<7);n(id);fault(4,id);if(cs->name%2){CEGUI::BoundSlot* bound=static_cast<CEGUI::BoundSlot*>(::operator new(sizeof(CEGUI::BoundSlot)));memset(bound,0,sizeof(*bound));at<CEGUI::SubscriberSlot*>(bound,8)=new CEGUI::SubscriberSlot(slot);return CEGUI::Event::Connection(bound);}return CEGUI::Event::Connection();}
void slotDestructor(CEGUI::SubscriberSlot* slot){n(10);n(at<void*>(slot,0)!=0);}
void* logSingleton(){observation(4,logger);return logger;}
void logMessage(void* self,const std::string& s,Ogre::LogMessageLevel level,bool mask){observation(5,self);cap->addText(s);n(level);n(mask);if(cs->boundary==5)throw Stop(71);}
void exceptionCopy(Ogre::Exception* to,const Ogre::Exception* from){n(6);++copyCount;cap->addText(from->getDescription());::new(to)Ogre::Exception(from->getNumber(),from->getDescription(),from->getSource());}
void setup(){blockCount=0;calls=copyCount=0;armed=false;memset(reads,0,sizeof(reads));ui=static_cast<CGameUI*>(block(0x1a08));logger=block(32);vt=static_cast<void**>(block(32));memset(vt,0,32);vt[2]=reinterpret_cast<void*>(&subscribe);
 for(unsigned i=0;i<7;++i){w[i]=static_cast<CEGUI::Window*>(block(0x300));at<void*>(w[i],0x38)=vt;at<void*>(w[i],0x78)=0;at<void*>(w[i],0x80)=0;at<void*>(w[i],0x88)=0;at<void*>(w[i],0x1d8)=static_cast<char*>(static_cast<void*>(ui))+0x20+i*8;}
 children=static_cast<CEGUI::Window**>(block(5*sizeof(void*)));alternate=static_cast<CEGUI::Window**>(block(5*sizeof(void*)));
 for(unsigned i=0;i<5;++i){children[i]=w[i+1];alternate[i]=w[6-i];}
 if(cs->mutation==1||cs->mutation==2||cs->mutation==6||cs->mutation==8||cs->faultWindow){at<void*>(w[0],0x78)=children;at<void*>(w[0],0x80)=children+3;}
 if(cs->mutation==6){at<void*>(w[1],0x78)=alternate;at<void*>(w[1],0x80)=alternate+2;}
 if(cs->mutation==7){at<void*>(w[0],0x78)=children;at<uintptr_t>(w[0],0x80)=reinterpret_cast<uintptr_t>(children)+(uintptr_t(0x80000000u)*8);}
 if(cs->mutation==9){names()[0]="DUPLICATE";names()[40]="DUPLICATE";names()[96]="DUPLICATE";}
}
void side(void* p,autotest::Capture& out,bool isCandidate){cs=static_cast<Case*>(p);cap=&out;ours=isCandidate;setup();detour::Set d,recursive;recursionPatch=&recursive;
 d.redirect(slotDtorFn,slotDtorFn,&slotDestructor);if(slotDtor2Fn!=slotDtorFn)d.redirect(slotDtor2Fn,slotDtor2Fn,&slotDestructor);d.redirect(presentFn,presentFn,&present);d.redirect(propertyFn,propertyFn,&property);d.redirect(logSingletonFn,logSingletonFn,&logSingleton);d.redirect(logFn,logFn,&logMessage);d.redirect(copyFn,copyFn,&exceptionCopy);if(copy2Fn!=copyFn)d.redirect(copy2Fn,copy2Fn,&exceptionCopy);require(!d.failed());unsigned caught=0;
 try{Fn f=fn();require(autotest::beginInvocation(out,f));f(ui,w[0]);out.callCompleted=1;}catch(const Ogre::Exception& e){caught=1;cap->addText(e.getDescription());}catch(const Stop& e){caught=2;n(e.reason);}catch(int x){caught=3;n(x);}catch(...){caught=4;}
 recursive.restore();unsigned expected=0;if(cs->mutation==8)expected=cs->fault;else if(cs->boundary==5)expected=2;else if(!cs->kind&&cs->fault>1)expected=cs->fault;require(caught==expected);n(caught);n(copyCount);n(calls);for(unsigned i=0;i<7;++i)n(reads[i]);
 for(unsigned i=0;i<blockCount;++i)cap->add(blocks[i].p,blocks[i].n+32);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
uint64_t address(unsigned kind){return reinterpret_cast<uint64_t>(kind?oldFunctions:oldEvents);}
int run(const tlhybrid_host* host,const char* name,unsigned kind){std::vector<Case> cases;
 for(unsigned mode=0;mode<7;++mode)for(unsigned i=0;i<(mode==0||mode==3||mode==4?97u:1u);++i){Case c(kind);c.mode=mode;c.name=i;cases.push_back(c);}
 for(unsigned m=1;m<=9;++m){Case c(kind);c.mutation=m;if(m==8)c.fault=2;cases.push_back(c);}
 for(unsigned t=1;t<=3;++t)for(unsigned boundary=1;boundary<=(kind?3u:4u);++boundary)for(unsigned child=0;child<2;++child){if(!kind&&boundary==3)continue;Case c(kind);c.fault=t;c.boundary=boundary;c.faultWindow=child;cases.push_back(c);}
 if(!kind){Case c(kind);c.fault=1;c.boundary=5;c.faultWindow=1;cases.push_back(c);}
 for(unsigned t=1;t<=3;++t){Case c(kind);c.mutation=8;c.fault=t;cases.push_back(c);}
 autotest::Coverage coverage(name,address(kind));unsigned unwind=0;
 for(unsigned i=0;i<cases.size();++i){Case c=cases[i];autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);
 if(a.capture.callCompleted){if(coverage.observe(host,a,b)){host->log("    window bindings case %u mode %u name %u mutation %u fault %u boundary %u window %u: status %d/%d issue %u/%u size %u/%u\n",i,c.mode,c.name,c.mutation,c.fault,c.boundary,c.faultWindow,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned)a.capture.length,(unsigned)b.capture.length);coverage.report(host);return 1;}}
 else{bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.callStarted&&b.capture.callStarted&&!b.capture.callCompleted&&a.capture.callTarget==address(kind)&&host->comparison_pair&&host->comparison_pair(address(kind),b.capture.callTarget)&&a.capture.length==b.capture.length&&!memcmp(a.capture.data,b.capture.data,a.capture.length);if(!ok){host->log("    window bindings unwind case %u FAIL statuses %d/%d issues %u/%u completed %u/%u\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted);return 1;}++unwind;}
 }
 coverage.report(host);host->log("    %s: %u independently checked propagated exceptions (excluded from coverage)\n",name,unwind);return coverage.completed<290;
}
}
TL_TEST(gameui_window_bindings_events){return run(host,"gameui_window_bindings_events",0);}
TL_TEST(gameui_window_bindings_functions){return run(host,"gameui_window_bindings_functions",1);}
