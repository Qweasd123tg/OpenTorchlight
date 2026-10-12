// d339d0: unordered raw-list removal, genuine completion map, then a list
// of TSafePointer<CQuestController>* cells, NOT CQuestDialog objects.
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include "QuestController.h"
#include "SafePointer.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldReset,(void*,void*),"_ZN13CQuestManager10resetQuestEP6CQuest")
extern "C" void newReset(void*,void*) __asm__("_ZN13CQuestManager10resetQuestEP6CQuest");
TL_FUNCTION(completedFn,"_ZN16CQuestController21questHasBeenCompletedEb")
extern "C" char resetScalarNew[] __asm__("_Znwm");
extern "C" char resetScalarDelete[] __asm__("_ZdlPv");
extern "C" char resetStringCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char resetStringDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
namespace quest_reset {
typedef std::map<std::wstring,bool> Map;
typedef TSafePointer<CQuestController> Cell;
typedef char MapSize[sizeof(Map)==48?1:-1];
typedef char CellSize[sizeof(Cell)==16?1:-1];
struct Case {unsigned scenario,variant,fault;};
struct Stop {};
struct Block {unsigned char* p;unsigned size;unsigned char before[0x220];};
struct Allocation {void* p;size_t size;bool freed;};
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>((char*)p+off);}
const Case* cs;autotest::Capture* cap;unsigned errors,blocks,events,reentries,allocations,frees,attempts,copies,destroys,liveCopies;bool tracking,mutated,unwound;
Block block[16];Allocation allocation[32];void *owner,*quest,*controllers[4],*other[4];Cell* cells[4];Cell** lists[2];void** playerList;Map* complete;std::wstring* name;int refs[4];unsigned expectedEvents[12],expectedCount;unsigned initialListCount,expectedListCount;void* expectedList[4];unsigned expectedDialogCount;typedef void(*Fn)(void*,void*);Fn invoked;
detour::Set *copyPatch,*destroyPatch;void* copiedRep[16];bool repDestroyed[16];
void need(bool b){if(!b)++errors;}
void number(unsigned n){cap->add(&n,4);}
void* raw(unsigned n){if(n>0x220||blocks==16)_exit(71);unsigned char* p=(unsigned char*)autotest::allocate(n+32);if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,n);std::memset(p+16+n,0x6c,16);block[blocks].p=p;block[blocks++].size=n;return p+16;}
int ref(const std::wstring& s){return *(const int*)((const char*)s.c_str()-8);}
unsigned id(void* p){for(unsigned i=0;i<4;++i)if(p==controllers[i])return i;need(false);return 99;}
void mutateOnDestroy(){if(mutated)return;mutated=true;if(cs->scenario==21)at<void*>(cells[0],0)=controllers[3];if(cs->scenario==22)at<unsigned>(quest,0x1bc)=1;}
void* allocate(size_t n){++attempts;if(tracking&&cs->fault==1&&attempts==1){number(0xfa11);number(n);throw std::bad_alloc();}void* p=std::malloc(n?n:1);if(!p)throw std::bad_alloc();if(tracking){need(allocations<32);if(allocations>=32)_exit(71);Allocation& a=allocation[allocations++];a.p=p;a.size=n;a.freed=false;number(0xa110);number(allocations);number(n);}return p;}
void release(void* p){if(!p)return;bool found=false;for(unsigned i=allocations;i;--i){Allocation& a=allocation[i-1];if(a.p==p&&!a.freed){a.freed=true;found=true;++frees;if(tracking){number(0xfee1);number(i);if(a.size!=48&&(cs->scenario==21||cs->scenario==22))mutateOnDestroy();}break;}}if(tracking)need(found);std::free(p);}
unsigned liveBuffers(){return liveCopies;}
void copyName(std::wstring* destination,const std::wstring& source){unsigned controller=99;for(unsigned i=0;i<4;++i)if(&source==&at<std::wstring>(controllers[i],0xa8))controller=i;
 if(controller!=99){number(0xc0f1);number(controller);if(cs->fault==2){number(0xfa12);throw std::bad_alloc();}}
 copyPatch->restore();reinterpret_cast<void(*)(std::wstring*,const std::wstring&)>(resetStringCopy)(destination,source);copyPatch->redirect(resetStringCopy,resetStringCopy,&copyName);need(!copyPatch->failed());
 if(controller!=99){need(copies<16);if(copies>=16)_exit(71);copiedRep[copies]=(void*)((char*)destination->c_str()-24);repDestroyed[copies]=refs[controller]>=0;if(!repDestroyed[copies])++liveCopies;++copies;}
}
void destroyName(void* rep,const std::allocator<wchar_t>& allocator){for(unsigned i=0;i<copies;++i)if(copiedRep[i]==rep&&!repDestroyed[i]){repDestroyed[i]=true;++destroys;--liveCopies;number(0xd357);number(i);if(cs->scenario==21||cs->scenario==22)mutateOnDestroy();break;}
 destroyPatch->restore();reinterpret_cast<void(*)(void*,const std::allocator<wchar_t>&)>(resetStringDestroy)(rep,allocator);destroyPatch->redirect(resetStringDestroy,resetStringDestroy,&destroyName);need(!destroyPatch->failed());
}
void completed(void* self,bool value){unsigned i=id(self);number(0xca11);number(i);number(value);need(!value);need(events<expectedCount&&i==expectedEvents[events]);++events;
 // Every copied controller name has already been destroyed at this boundary.
 need(liveBuffers()==0);for(unsigned j=0;j<4;++j)need(ref(at<std::wstring>(controllers[j],0xa8))==refs[j]);
 need(complete->find(*name)!=complete->end()&&!complete->find(*name)->second);
 if(events!=1)return;
 switch(cs->scenario){
 case 14:at<Cell**>(quest,0x1b0)=lists[1];break;
 case 15:at<unsigned>(quest,0x1b8)=1;break;
 case 16:at<unsigned>(quest,0x1b8)=3;break;
 case 17:at<void*>(cells[1],0)=controllers[3];break;
 case 18:at<void*>(cells[1],0)=0;break;
 case 19:{++reentries;unsigned count=at<unsigned>(quest,0x1b8);at<unsigned>(quest,0x1b8)=0;invoked(owner,quest);at<unsigned>(quest,0x1b8)=count;break;}
 case 20:at<unsigned>(quest,0x1bc)=1;break;
 case 23:throw Stop();
 }
}
void addExpected(unsigned a){expectedEvents[expectedCount++]=a;}
void setup(){autotest::g_arenaUsed=0;errors=blocks=events=reentries=allocations=frees=attempts=expectedCount=copies=destroys=liveCopies=0;tracking=mutated=unwound=false;
 owner=raw(0xb0);quest=raw(0x200);for(unsigned i=0;i<4;++i){controllers[i]=raw(0xc0);cells[i]=new(raw(16))Cell;other[i]=autotest::allocate(16);at<void*>(cells[i],0)=controllers[i];at<unsigned>(cells[i],8)=i+17;at<void*>(controllers[i],0)=cs->variant&1?0:other[i];}
 playerList=(void**)autotest::allocate(32);lists[0]=(Cell**)autotest::allocate(32);lists[1]=(Cell**)autotest::allocate(32);
 name=new((char*)quest+0x50)std::wstring(cs->scenario==7?L"\u0416\u0443\u043a long quest name":L"quest reset controller long identity");
 if(cs->scenario==8){const wchar_t embedded[]={L'q',0,L'u',L'e',L's',L't',L' ',L'l',L'o',L'n',L'g'};name->assign(embedded,11);}
 for(unsigned i=0;i<4;++i){std::wstring* s=new((char*)controllers[i]+0xa8)std::wstring(name->c_str(),name->size());if(cs->variant&1||cs->scenario==21||cs->scenario==22)(*s)[0]=(*s)[0];refs[i]=ref(*s);lists[0][i]=cells[i];lists[1][i]=cells[i];}
 lists[1][1]=cells[2];lists[1][2]=cells[3];
 if(cs->scenario==5||cs->scenario==6||cs->scenario==10||cs->scenario==13){unsigned i=cs->scenario==10?2:cs->scenario==13?1:0;std::wstring& s=at<std::wstring>(controllers[i],0xa8);if(cs->scenario==6)s+=L" suffix";else s[0]=L'X';refs[i]=ref(s);}
 if(cs->scenario==2||cs->scenario==10)at<void*>(cells[0],0)=0;
 complete=new((char*)owner+0x70)Map;if(cs->variant==1||cs->variant==2)complete->insert(Map::value_type(*name,cs->variant==2));if(cs->variant==3){complete->insert(Map::value_type(L"before unrelated",true));complete->insert(Map::value_type(L"zz unrelated",false));}
 initialListCount=4;unsigned listMode=cs->scenario%6;for(unsigned i=0;i<4;++i)playerList[i]=other[i];
 if(listMode==1)playerList[0]=quest;if(listMode==2)playerList[1]=quest;if(listMode==3)playerList[3]=quest;if(listMode==4){playerList[0]=quest;playerList[3]=quest;}if(listMode==5){initialListCount=0;}if(cs->scenario==19){playerList[0]=quest;playerList[3]=quest;}
 at<void**>(owner,0x18)=playerList;at<unsigned>(owner,0x20)=initialListCount;at<unsigned>(owner,0x24)=listMode==3?1:4;at<unsigned>(owner,0x28)=7;
 expectedListCount=initialListCount;for(unsigned i=0;i<4;++i)expectedList[i]=playerList[i];
 unsigned removes=cs->scenario==0?0:cs->scenario==19?2:1;
 for(unsigned r=0;r<removes;++r)for(unsigned i=0;i<expectedListCount;++i)if(expectedList[i]==quest){--expectedListCount;expectedList[i]=expectedList[expectedListCount];break;}
 unsigned count=cs->scenario<=8?1:3,capacity=4;if(cs->scenario==0||cs->scenario==1)count=0;if(cs->scenario==11||cs->scenario==12||cs->scenario==13)count=4;if(cs->scenario==11)capacity=1;if(cs->scenario==12)capacity=0;if(cs->scenario==13)capacity=2;if(cs->scenario==16)count=1;
 at<Cell**>(quest,0x1b0)=lists[0];at<unsigned>(quest,0x1b8)=count;at<unsigned>(quest,0x1bc)=capacity;at<unsigned>(quest,0x1c0)=9;expectedDialogCount=cs->scenario==15?1:cs->scenario==16?3:count;
 switch(cs->scenario){
 case 0:case 1:case 2:case 5:case 6:break;
 case 3:case 4:case 7:case 8:case 15:case 23:addExpected(0);break;
 case 10:addExpected(1);break;
 case 11:case 12:for(unsigned i=0;i<4;++i)addExpected(0);break;
 case 13:for(unsigned i=0;i<3;++i)addExpected(0);break;
 case 14:addExpected(0);addExpected(2);addExpected(3);break;
 case 17:addExpected(0);addExpected(3);addExpected(2);break;
 case 18:addExpected(0);addExpected(2);break;
 case 20:case 22:for(unsigned i=0;i<3;++i)addExpected(0);break;
 case 21:addExpected(3);addExpected(1);addExpected(2);break;
 default:addExpected(0);addExpected(1);addExpected(2);break;
 }
 if(cs->fault)expectedCount=0;
 for(unsigned i=0;i<blocks;++i)std::memcpy(block[i].before,block[i].p+16,block[i].size);
}
void snapshot(){const unsigned copyCounts[]={0,0,0,1,1,1,1,1,1,3,2,4,4,4,3,1,3,3,2,3,3,3,3,1};need(copies==(cs->fault?0u:copyCounts[cs->scenario]));need(events==expectedCount);need(reentries==(cs->scenario==19?1u:0u));need(at<unsigned>(owner,0x20)==expectedListCount);for(unsigned i=0;i<4;++i){need(playerList[i]==expectedList[i]);cap->addPointer(playerList[i]);}
 bool inserted=cs->scenario!=0&&!(cs->fault==1&&(cs->variant==0||cs->variant==3));unsigned expectedSize=(cs->variant==3?2:cs->variant==0?0:1)+(inserted&&(cs->variant==0||cs->variant==3)?1:0);need(complete->size()==expectedSize);
 unsigned seen=0;for(Map::iterator i=complete->begin();i!=complete->end();++i){cap->addText(i->first);number(i->second);if(i->first==*name){++seen;need(i->second==(cs->scenario==0&&cs->variant==2));}else if(i->first==L"before unrelated")need(i->second);else if(i->first==L"zz unrelated")need(!i->second);else need(false);}need(seen==((cs->variant==1||cs->variant==2||inserted)?1u:0u));
 need(at<unsigned>(quest,0x1b8)==expectedDialogCount);need(at<unsigned>(quest,0x1bc)==((cs->scenario==20||cs->scenario==22)?1u:cs->scenario==11?1u:cs->scenario==12?0u:cs->scenario==13?2u:4u));need(at<Cell**>(quest,0x1b0)==lists[cs->scenario==14?1:0]);
 for(unsigned i=0;i<4;++i){void* want=controllers[i];if((cs->scenario==2||cs->scenario==10)&&i==0)want=0;if(cs->scenario==17&&i==1)want=controllers[3];if(cs->scenario==18&&i==1)want=0;if(cs->scenario==21&&i==0)want=controllers[3];need(at<void*>(cells[i],0)==want);cap->addPointer(at<void*>(cells[i],0));need(ref(at<std::wstring>(controllers[i],0xa8))==refs[i]);}
 for(unsigned i=0;i<blocks;++i){Block& b=block[i];for(unsigned j=0;j<16;++j){need(b.p[j]==0xd3);need(b.p[16+b.size+j]==0x6c);}unsigned char expected[0x220];std::memcpy(expected,b.before,b.size);
  if(b.p+16==owner){std::memset(expected+0x70,0,48);at<unsigned>(expected,0x20)=expectedListCount;}
  if(b.p+16==quest){at<Cell**>(expected,0x1b0)=lists[cs->scenario==14?1:0];at<unsigned>(expected,0x1b8)=expectedDialogCount;at<unsigned>(expected,0x1bc)=at<unsigned>(quest,0x1bc);}
  for(unsigned j=0;j<4;++j)if(b.p+16==(void*)cells[j])at<void*>(expected,0)=at<void*>(cells[j],0);
  unsigned char actual[0x220];std::memcpy(actual,b.p+16,b.size);if(b.p+16==owner)std::memset(actual+0x70,0,48);need(!std::memcmp(actual,expected,b.size));
 }
 need(liveBuffers()==0);number(events);number(reentries);number(expectedListCount);number(complete->size());number(allocations);number(frees);number(copies);number(destroys);number(unwound);number(0x51525354u);number(errors);
}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;setup();invoked=candidate?&newReset:&oldReset;detour::Set callbacks,allocators,copyRedirect,destroyRedirect;copyPatch=&copyRedirect;destroyPatch=&destroyRedirect;copyRedirect.redirect(resetStringCopy,resetStringCopy,&copyName);destroyRedirect.redirect(resetStringDestroy,resetStringDestroy,&destroyName);TL_REDIRECT(callbacks,completedFn,&completed);allocators.redirect(resetScalarNew,resetScalarNew,&allocate);allocators.redirect(resetScalarDelete,resetScalarDelete,&release);if(callbacks.failed()||allocators.failed()||copyRedirect.failed()||destroyRedirect.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 tracking=true;if(!autotest::beginInvocation(out,invoked))return;try{invoked(owner,cs->scenario==0?0:quest);out.callCompleted=1;}catch(const std::bad_alloc&){unwound=true;need(cs->fault!=0);}catch(const Stop&){unwound=true;need(cs->scenario==23);}tracking=false;need(unwound==(cs->fault!=0||cs->scenario==23));snapshot();allocators.restore();callbacks.restore();copyRedirect.restore();destroyRedirect.restore();complete->~Map();name->~basic_string();for(unsigned i=0;i<4;++i){at<std::wstring>(controllers[i],0xa8).~basic_string();cells[i]->invalidate();cells[i]->~Cell();}
}
void a(void* c,autotest::Capture& o){side(c,o,false);}void b(void* c,autotest::Capture& o){side(c,o,true);}
bool good(const autotest::Capture& c){unsigned f[2];if(c.length<8)return false;std::memcpy(f,c.data+c.length-8,8);return f[0]==0x51525354u&&!f[1];}
}
TL_TEST(questmanager_reset){using namespace quest_reset;autotest::Coverage coverage("questmanager_reset",0xd339d0);unsigned count=0;
 for(unsigned s=0;s<23;++s)for(unsigned v=0;v<4;++v){Case c={s,v,0};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;if(coverage.observe(host,x,y)||!good(x.capture)||!good(y.capture)){host->log(" reset scenario=%u variant=%u oracle=%u/%u\n",s,v,good(x.capture),good(y.capture));coverage.report(host);return 1;}}
 coverage.report(host);if(coverage.completed!=count||coverage.different||coverage.missing)return 1;
 const Case faults[]={{23,1,0},{3,0,1},{3,3,1},{3,1,2},{3,3,2}};
 for(unsigned i=0;i<sizeof(faults)/sizeof(faults[0]);++i){Case c=faults[i];autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);bool ok=x.reportValid&&y.reportValid&&!x.childStatus&&!y.childStatus&&!x.capture.issue&&!y.capture.issue&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==0xd339d0&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget)&&good(x.capture)&&good(y.capture)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);if(!ok){host->log(" reset separate expected unwind %u failed\n",i);return 1;}}
 host->log(" reset expected unwinds: 5, separate from completed coverage\n");return 0;}
