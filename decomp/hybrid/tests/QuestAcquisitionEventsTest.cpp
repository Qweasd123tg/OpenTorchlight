// Independent original-ELF oracle: d33150 and d2f470. C++98 only.
// Expected traces are authored from the fresh packets, never candidate source.
// Each side forks before touching either function-local translated-string cache.
#include <map>
#include <string>
#include <cstring>
#include <cstdlib>
#include <new>
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(long long, qaeOldGive, (void*,void*,void*,bool), "_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
extern "C" long long qaeNewGive(void*,void*,void*,bool) __asm__("_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb");
TL_ORIGINAL(void, qaeOldEvent, (void*,int,void*,void*), "_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit")
extern "C" void qaeNewEvent(void*,int,void*,void*) __asm__("_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit");
TL_ORIGINAL(void, qaeOldControllerAccept, (void*,bool), "_ZN16CQuestController16setQuestAcceptedEb")
extern "C" void qaeNewControllerAccept(void*,bool) __asm__("_ZN16CQuestController16setQuestAcceptedEb");
TL_ORIGINAL(void, qaeOldClientEvent, (void*,int,void*,void*), "_ZN11CGameClient14questEventFireE13EQUEST_EVENTSP10CCharacterP9CBaseUnit")
TL_FUNCTION(qaeManagerSingleton,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qaeAccepted,"_ZN6CQuest16setQuestAcceptedEb")
TL_FUNCTION(qaeIsComplete,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(qaeQuestEvent,"_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_")
TL_FUNCTION(qaeDetails,"_ZN6CQuest15getQuestDetailsEv")
TL_FUNCTION(qaeTags,"_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qaeTranslateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(qaeTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(qaeQueue,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(qaePlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(qaeBig,"_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(qaeSmall,"_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(qaeUISingleton,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qaeRefresh,"_ZN7CGameUI16refreshQuestMenuEv")
TL_FUNCTION(qaeTip,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(qaeIcons,"_ZN6CLevel14updateNPCIconsEv")
TL_FUNCTION(qaeAutomap,"_ZN6CLevel18updateAutomapIconsEv")
TL_FUNCTION(qaeControllerAccepted,"_ZN16CQuestController20questHasBeenAcceptedEb")
TL_FUNCTION(qaeControllerComplete,"_ZN16CQuestController21questHasBeenCompletedEb")
TL_FUNCTION(qaeComplete,"_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(qaeRemove,"_ZN13CQuestManager11removeQuestEP6CQuestb")
TL_FUNCTION(qaeReward,"_ZN13CQuestManager18giveRewardForQuestEP6CQuest")
TL_FUNCTION(qaeInitialize,"_ZN6CQuest22initializeQuestWithNPCEP9CBaseUnit")
TL_FUNCTION(qaeMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qaeSetting,"_ZN20CDynamicPropertyFile9GetStringEj")
extern "C" char qaeArrayNew[] __asm__("_Znam");
extern "C" char qaeArrayDelete[] __asm__("_ZdaPv");

namespace qae {
struct List {void** data; unsigned count,capacity,grow,pad;};
typedef std::map<std::wstring,bool> Completed;
typedef char ABI[(sizeof(List)==24&&sizeof(std::wstring)==8&&sizeof(Completed)==48)?1:-1];
template<class T> T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
enum Code {TranslateSingleton=1,Translate,Accepted,IsComplete,QuestEvent,Details,Tags,Queue,Play,Big,Small,UISingleton,Refresh,Tip,Icons,Automap,ControllerAccepted,Complete,Remove,ArrayNew,ArrayDelete,Reward,Initialize,ControllerComplete,Master,Setting,ManagerSingleton};
struct Case {unsigned mode,variant,fault;};
struct Record {unsigned code,id,value;std::wstring text;};
struct TagResult {unsigned id,offset;std::wstring text;};
struct Stop {};
const Case* cs;autotest::Capture* cap;unsigned kind,errors,used,wantUsed,tagRead,tagCount,translateCalls,pass,nested,allocations,deletions;
Record wanted[256];TagResult tagResults[128];
unsigned sequences[8][64],seqCount[8],seqRead[8],questUpdates[8];
void *owner,*player,*resource,*playerResource,*level[2],*client[2],*ui[3],*sound[2],*translator,*character,*unit,*master,*settings;
void *quest[8],*controller[4],*wrapper[4],*dialogs[2],*alternateDialogs[2];
List* active;List* controllers;Completed* completed;
void** initialData;unsigned initialCount,initialCapacity,expectedCount,expectedCapacity;
void* allocationRaw[8];unsigned allocationBytes[8];
unsigned char ownerBefore[0xd0],questBefore[8][0x220];
std::wstring settingText;
typedef void(*EventFn)(void*,int,void*,void*);EventFn eventFn;

void need(bool b){if(!b)++errors;}
void n(unsigned x){cap->add(&x,sizeof(x));}
void* raw(unsigned size){return autotest::allocate(size);}
unsigned qid(void* p){for(unsigned i=0;i<8;++i)if(p==quest[i])return i;return 99;}
unsigned cid(void* p){for(unsigned i=0;i<4;++i)if(p==controller[i])return i;return 99;}
unsigned lid(void* p){return p==level[0]?0:p==level[1]?1:99;}
unsigned uid(void* p){for(unsigned i=0;i<3;++i)if(p==ui[i])return i;return 99;}
void expect(unsigned code,unsigned id=0,unsigned value=0,const std::wstring& text=L""){
 need(wantUsed<256);if(wantUsed>=256)return;Record&r=wanted[wantUsed++];r.code=code;r.id=id;r.value=value;r.text=text;
}
void emit(unsigned code,unsigned id=0,unsigned value=0,const std::wstring& text=L""){
 n(code);n(id);n(value);cap->addText(text);need(used<wantUsed);
 if(used<wantUsed){Record&r=wanted[used];need(r.code==code&&r.id==id&&r.value==value&&r.text==text);}++used;
 if(cs->fault==code)throw Stop();
}
void status(unsigned id,unsigned value){need(seqCount[id]<64);sequences[id][seqCount[id]++]=value;expect(IsComplete,id,value);}
void tag(unsigned id,unsigned offset,const std::wstring& value){need(tagCount<128);TagResult&r=tagResults[tagCount++];r.id=id;r.offset=offset;r.text=value;expect(Tags,id,offset,value);}
void translation(const wchar_t* source,const wchar_t* result){expect(TranslateSingleton);expect(Translate,0,0,source);(void)result;}
void refresh(){expect(UISingleton);expect(Refresh,2);}
void icons(unsigned first=0,unsigned second=0){expect(Icons,first);expect(Automap,second);}
void sounds(unsigned sample,bool first=true,bool second=true){if(first)expect(Queue,0,sample);if(second)expect(Play,1,sample);}
void fallback(unsigned id,unsigned a,unsigned b,unsigned c,int e){status(id,a);expect(QuestEvent,id,e);status(id,b);status(id,c);}

void setup(unsigned category){kind=category;errors=used=wantUsed=tagRead=tagCount=translateCalls=pass=nested=allocations=deletions=0;
 std::memset(seqCount,0,sizeof(seqCount));std::memset(seqRead,0,sizeof(seqRead));std::memset(questUpdates,0,sizeof(questUpdates));autotest::g_arenaUsed=0;
 owner=raw(0xd0);player=raw(0x2b0);resource=raw(0x50);playerResource=raw(0x50);translator=raw(16);character=raw(16);unit=raw(16);master=raw(0xa0);settings=raw(16);
 for(unsigned i=0;i<2;++i){level[i]=raw(0x240);client[i]=raw(0x90);sound[i]=raw(16);dialogs[i]=raw(0x80);alternateDialogs[i]=raw(0x80);at<unsigned char>(dialogs[i],0x76)=1;}
 for(unsigned i=0;i<3;++i)ui[i]=raw(16);
 for(unsigned i=0;i<2;++i){at<void*>(level[i],0x220)=client[i];at<void*>(client[i],0x78)=ui[i];}
 at<void*>(owner,0x10)=player;at<void*>(owner,0x30)=sound[1];at<void*>(owner,0x38)=resource;at<void*>(resource,0x18)=level[0];
 at<void*>(player,0x68)=playerResource;at<void*>(player,0x298)=sound[0];at<void*>(playerResource,0x18)=level[0];at<void*>(master,0x90)=settings;settingText=L"unrelated retirement quest";
 active=(List*)((char*)owner+0x18);active->data=(void**)raw(16*sizeof(void*));active->capacity=8;active->grow=4;active->pad=0x27ac310;
 completed=new((char*)owner+0x70)Completed;
 for(unsigned i=0;i<8;++i){quest[i]=raw(0x220);new((char*)quest[i]+0x38)std::wstring(L"raw title");new((char*)quest[i]+0x40)std::wstring(L"raw subtitle");new((char*)quest[i]+0x50)std::wstring(L"Quest Mixed Case");new((char*)quest[i]+0x58)std::wstring(L"raw description");at<void*>(quest[i],0x1d0)=owner;at<unsigned char>(quest[i],0x29)=1;}
 for(unsigned i=0;i<4;++i){controller[i]=raw(0xc0);wrapper[i]=raw(16);at<void*>(wrapper[i],0)=controller[i];new((char*)controller[i]+0xa8)std::wstring(L"Quest Mixed Case");}
 controllers=(List*)((char*)quest[0]+0x1b0);controllers->data=(void**)raw(8*sizeof(void*));controllers->capacity=4;controllers->grow=2;for(unsigned i=0;i<4;++i)controllers->data[i]=wrapper[i];
 initialData=active->data;initialCount=initialCapacity=expectedCount=expectedCapacity=0;
}

void* translateSingleton(){emit(TranslateSingleton);return translator;}
std::wstring translate(void* self,const wchar_t* text){need(self==translator);emit(Translate,0,0,text);++translateCalls;
 if((kind==0&&cs->mode==31)||(kind==1&&cs->mode==33)){if(translateCalls<3)return L"";}
 return kind==1?L"translated complete":L"translated new quest";
}
void accepted(void* self,bool value){unsigned id=qid(self);need(value&&id<8);need(active->count&&active->data[active->count-1]==self);emit(Accepted,id,value);at<unsigned char>(self,0x26)=value;}
unsigned long long isComplete(void* self,bool include){unsigned id=qid(self);need(id<8&&!include);unsigned value=0;
 if(id<8){need(seqRead[id]<seqCount[id]);if(seqRead[id]<seqCount[id])value=sequences[id][seqRead[id]++];}
 if(kind==2){if(at<unsigned char>(self,0x24))need((value&255)!=0);}
 emit(IsComplete,id,value);return value|(cs->variant?0x6ab5cd1200000000ULL:0ULL);
}
void questEvent(void* self,int e,void* a,void* b){unsigned id=qid(self);need(id<8);need(a==(kind==2?0:character)&&b==(kind==2?0:unit));emit(QuestEvent,id,e);if(id<8)++questUpdates[id];
 if(kind==2){need(e==3);need(active->count==1&&active->data[0]==quest[0]&&at<unsigned char>(quest[0],0x26)==1);return;}
 if(kind==1&&id==0&&questUpdates[0]==1){
  if(cs->mode==24){active->data[1]=quest[1];active->count=2;}
  if(cs->mode==25)active->count=1;
  if(cs->mode==26){active->data[0]=quest[2];active->count=2;}
  if(cs->mode==32)at<unsigned char>(self,0x209)=1;
 }
}
std::wstring details(void* self){unsigned id=qid(self);emit(Details,id);
 if(kind==0&&cs->mode==22)at<unsigned char>(self,0x25)=1;
 if(kind==1&&cs->mode==31)at<unsigned char>(self,0x29)=0;
 return (kind==0&&cs->mode==11)||(kind==1&&cs->mode==12)?L"":L"details exist";
}
std::wstring tags(void* self,const std::wstring& source){unsigned id=qid(self),off=99;for(unsigned o=0x38;o<=0x58;o+=8)if(&source==&at<std::wstring>(self,o))off=o;
 need(tagRead<tagCount);std::wstring result;
 if(tagRead<tagCount){TagResult&r=tagResults[tagRead++];need(r.id==id&&r.offset==off);result=r.text;}
 emit(Tags,id,off,result);return result;
}
void queue(void* self,int sample,float a,float b){need(self==sound[0]&&a==1.0f&&b==1.0f);if(kind==1&&cs->mode!=23)need(at<unsigned char>(quest[0],0x209)==0);emit(Queue,0,sample);if(kind==0&&cs->mode==23)at<unsigned char>(quest[0],0x25)=1;}
void play(void* self,int sample,void* node,float a,float b,bool flag){need(self==sound[1]&&!node&&a==0.0f&&b==0.0f&&!flag);if(kind==1&&cs->mode!=23)need(at<unsigned char>(quest[0],0x209)==0);emit(Play,1,sample);}
// By-value wstring deliberately matches the original nontrivial hidden-reference ABI.
void big(void* self,std::wstring text,float seconds){need(seconds==2.0f);if(kind==1&&cs->mode!=23)need(at<unsigned char>(quest[0],0x209)==0);emit(Big,uid(self),0,text);
 if(kind==1&&cs->mode==30){at<void*>(playerResource,0x18)=level[1];at<void*>(level[0],0x220)=client[1];at<void*>(level[1],0x220)=client[0];}
 if(kind==1&&cs->mode==23&&!nested){need(at<unsigned char>(quest[0],0x209)==0);nested=1;eventFn(owner,1,character,unit);nested=0;need(at<unsigned char>(quest[0],0x209)==1);}
 text=L"callback owns its by-value copy";
}
void small(void* self,std::wstring text,float seconds){need(seconds==2.0f);if(kind==1&&cs->mode!=23)need(at<unsigned char>(quest[0],0x209)==0);emit(Small,uid(self),0,text);text=L"changed local copy";}
void* singleton(){emit(UISingleton);return ui[2];}
void refreshUI(void* self){need(self==ui[2]);emit(Refresh,2);}
void tip(void* self,int value){need(self==ui[2]&&value==20);if(cs->mode!=23)need(at<unsigned char>(quest[0],0x209)==0);emit(Tip,2,value);}
void updateIcons(void* self){emit(Icons,lid(self));if(kind==0&&cs->mode==37)at<void*>(resource,0x18)=level[1];}
void updateAutomap(void* self){emit(Automap,lid(self));}
void controllerAccepted(void* self,bool value){unsigned id=cid(self);emit(ControllerAccepted,id,value);
 if(kind==2){need(!at<unsigned char>(quest[0],0x26));need(active->count==0);}
 if(kind==2&&(cs->mode&4)&&(cs->mode&2)&&value)at<void*>(controller[0],0x98)=quest[1];
 if(kind==0&&id==0){if(cs->mode==34)controllers->count=3;if(cs->mode==35)controllers->count=1;}
}
void controllerComplete(void* self,bool value){emit(ControllerComplete,cid(self),value);need(kind==2&&value&&active->count==0);}
long long complete(void* self,void* q){need(self==owner&&q==quest[0]);emit(Complete,0);at<unsigned char>(q,0x26)=0;active->count=0;return 1;}
long long remove(void* self,void* q,bool abandoned){need(self==owner&&q==quest[0]&&!abandoned);emit(Remove,0,abandoned);return 1;}
void reward(void* self,void* q){need(self==owner&&q==quest[0]&&active->count==1&&at<unsigned char>(q,0x26));emit(Reward);}
void initialize(void* q,void* npc){need(q==quest[0]&&!npc&&!at<unsigned char>(q,0x26));for(unsigned i=0;i<2;++i)need(!at<unsigned char>(dialogs[i],0x76));emit(Initialize);}
void* getMaster(){emit(Master);return master;}
void* getManager(){emit(ManagerSingleton);return owner;}
const std::wstring& getSetting(void* self,unsigned){need(self==settings);emit(Setting);return settingText;}
void* arrayNew(size_t bytes){if(kind==0)need(active->capacity==(cs->mode==6?4:initialCapacity));emit(ArrayNew,0,bytes);need(allocations<8);unsigned char* p=(unsigned char*)raw(bytes+32);std::memset(p,0xad,bytes+32);std::memset(p+16,0,bytes);allocationRaw[allocations]=p;allocationBytes[allocations++]=bytes;return p+16;}
void arrayDelete(void* p){need(p==initialData);emit(ArrayDelete);++deletions;}

void hook(detour::Set& d,bool fakeAccepted,bool fakeFinish){
 TL_REDIRECT(d,qaeIsComplete,&isComplete);TL_REDIRECT(d,qaeQuestEvent,&questEvent);TL_REDIRECT(d,qaeDetails,&details);TL_REDIRECT(d,qaeTags,&tags);
 TL_REDIRECT(d,qaeTranslateSingleton,&translateSingleton);TL_REDIRECT(d,qaeTranslate,&translate);TL_REDIRECT(d,qaeQueue,&queue);TL_REDIRECT(d,qaePlay,&play);
 TL_REDIRECT(d,qaeBig,&big);TL_REDIRECT(d,qaeSmall,&small);TL_REDIRECT(d,qaeUISingleton,&singleton);TL_REDIRECT(d,qaeRefresh,&refreshUI);TL_REDIRECT(d,qaeTip,&tip);
 TL_REDIRECT(d,qaeIcons,&updateIcons);TL_REDIRECT(d,qaeAutomap,&updateAutomap);TL_REDIRECT(d,qaeControllerAccepted,&controllerAccepted);
 if(fakeAccepted)TL_REDIRECT(d,qaeAccepted,&accepted);
 if(fakeFinish){TL_REDIRECT(d,qaeComplete,&complete);TL_REDIRECT(d,qaeRemove,&remove);}
}
void saveBefore(){initialData=active->data;initialCount=active->count;initialCapacity=active->capacity;std::memcpy(ownerBefore,owner,0xd0);for(unsigned i=0;i<8;++i)std::memcpy(questBefore[i],quest[i],0x220);}
void tail(bool caught){if(!caught){need(used==wantUsed);need(tagRead==tagCount);for(unsigned i=0;i<8;++i)need(seqRead[i]==seqCount[i]);}
 for(unsigned i=0;i<allocations;++i){unsigned char* p=(unsigned char*)allocationRaw[i];for(unsigned j=0;j<16;++j)need(p[j]==0xad&&p[16+allocationBytes[i]+j]==0xad);}
 n(used);n(tagRead);n(translateCalls);n(allocations);n(deletions);n(caught);n(0x51414531);n(errors);
}
bool good(const autotest::Outcome& o){unsigned end[2]={0,1};if(o.capture.length>=8)std::memcpy(end,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&end[0]==0x51414531&&!end[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cov,autotest::Body a,autotest::Body b,Case& c,bool fault=false){
 autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);bool ok=good(x)&&good(y)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(fault)ok=ok&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==cov.original&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget);
 else if(cov.observe(host,x,y))ok=false;
 if(!ok){unsigned xe=~0u,ye=~0u;if(x.capture.length>=4)std::memcpy(&xe,x.capture.data+x.capture.length-4,4);if(y.capture.length>=4)std::memcpy(&ye,y.capture.data+y.capture.length-4,4);host->log(" quest acquisition/events mode=%u variant=%u fault=%u status=%d/%d oracle=%u/%u errors=%u/%u lengths=%lu/%lu\n",c.mode,c.variant,c.fault,x.childStatus,y.childStatus,good(x),good(y),xe,ye,(unsigned long)x.capture.length,(unsigned long)y.capture.length);}
 return ok;
}
}

namespace qae_event {
using namespace qae;
void completion(unsigned id,bool audio,bool first,bool second,bool uiEnabled,bool translateNow,bool showTip,unsigned smallUI=0,const wchar_t* title=L"translated complete"){
 status(id,0);expect(QuestEvent,id,1);status(id,1);expect(Details,id);if(audio)sounds(32,first,second);
 if(uiEnabled){if(translateNow)translation(L"Quest Complete",title);expect(Big,0,0,title);tag(id,0x58,L"completed description");expect(Small,smallUI,0,L"completed description");if(showTip){expect(UISingleton);expect(Tip,2,20);}}
}
void plan(){unsigned m=cs->mode;active->count=1;active->data[0]=quest[0];expectedCount=1;expectedCapacity=8;
 if(m==0){at<void*>(owner,0x10)=0;return;}if(m==1){active->count=expectedCount=0;return;}if(m==2){active->data[0]=0;return;}
 if(m==3){status(0,1);return;}
 if(m==4||m==5||m==8||m==36){fallback(0,m==8?0x100:0,m==36?0x100:0,m==5?1:0,1);if(m!=5)refresh();return;}
 if(m==6||m==7||m==9||m==10||m==38){unsigned a=m==9||m==10?0x101:m==38?2:1;fallback(0,a,a,m==7?2:m==10?0x102:m==9?0x201:a,5);if(m!=7&&m!=10)refresh();return;}
 if(m==22||m==32){if(m==22)at<unsigned char>(quest[0],0x209)=1;fallback(0,0,1,0,1);refresh();return;}
 if(m==24||m==25||m==26||m==27||m==28||m==29||m==39){
  if(m==24){fallback(0,0,0,0,1);fallback(1,0,0,0,1);expectedCount=2;}
  if(m==25){active->count=3;active->data[1]=quest[1];active->data[2]=quest[2];fallback(0,0,0,0,1);expectedCount=1;}
  if(m==26){active->count=3;active->data[1]=quest[1];active->data[2]=quest[2];fallback(0,0,0,0,1);fallback(1,0,0,0,1);expectedCount=2;}
  if(m==27){active->count=3;active->capacity=1;expectedCount=3;expectedCapacity=1;for(unsigned i=0;i<3;++i)fallback(0,0,0,0,1);}
  if(m==28){active->count=3;active->data[0]=0;active->data[1]=quest[1];active->data[2]=quest[2];expectedCount=3;status(1,1);fallback(2,0,0,0,1);}
  if(m==29){active->count=2;active->data[1]=quest[1];expectedCount=2;fallback(0,0,0,0,1);fallback(1,0,0,1,1);}
  if(m==39){active->count=3;active->data[0]=active->data[1]=active->data[2]=0;expectedCount=3;return;}
  refresh();return;
 }
 if(m==23){status(0,0);expect(QuestEvent,0,1);status(0,1);expect(Details);sounds(32);translation(L"Quest Complete",L"translated complete");expect(Big,0,0,L"translated complete");completion(0,true,true,true,true,false,false);refresh();tag(0,0x58,L"completed description");expect(Small,0,0,L"completed description");refresh();return;}
 if(m==33||m==34){for(unsigned i=0;i<3;++i){completion(0,true,true,true,true,m==33||!i,false,0,m==33&&i<2?L"":L"translated complete");refresh();}return;}
 if(m==13)at<void*>(player,0x298)=0;if(m==14)at<void*>(owner,0x30)=0;if(m==15){at<void*>(player,0x298)=0;at<void*>(owner,0x30)=0;}
 if(m==16)at<void*>(player,0x68)=0;if(m==17)at<void*>(playerResource,0x18)=0;if(m==18)at<unsigned char>(quest[0],0x29)=0;
 if(m==19||m==21)at<unsigned char>(quest[0],0x2c)=1;if(m==20||m==21)at<unsigned char>(quest[0],0x208)=1;
 bool uiEnabled=m!=16&&m!=17&&m!=18&&m!=31;
 if(m==37){status(0,0);expect(QuestEvent,0,1);status(0,0x101);expect(Details);sounds(32);translation(L"Quest Complete",L"translated complete");expect(Big,0,0,L"translated complete");tag(0,0x58,L"completed description");expect(Small,0,0,L"completed description");}
 else completion(0,m!=12,m!=13&&m!=15,m!=14&&m!=15,uiEnabled,uiEnabled,m==19||m==20||m==21,m==30?1:0);
 refresh();
}
bool notifies(unsigned m){return m>=11&&m<=21||m==23||m==30||m==31||m==33||m==34||m==35||m==37;}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;setup(1);plan();saveBefore();eventFn=candidate?&qaeNewEvent:&qaeOldEvent;bool caught=false;
 {detour::Set d,route;hook(d,false,false);EventFn entry=eventFn;void* entryOwner=owner;
  if(cs->variant&2){at<void*>(client[0],0x68)=owner;entry=&qaeOldClientEvent;entryOwner=client[0];if(candidate)route.redirect(reinterpret_cast<char*>(&qaeOldEvent),reinterpret_cast<char*>(&qaeOldEvent),&qaeNewEvent);}
  if(d.failed()||route.failed()){out.issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(out,entry))return;
  try{unsigned repeat=cs->mode==33||cs->mode==34?3:1;for(pass=0;pass<repeat;++pass){if(pass)at<unsigned char>(quest[0],0x209)=0;entry(entryOwner,(cs->mode==6||cs->mode==7||cs->mode==9||cs->mode==10||cs->mode==38)?5:1,character,unit);}out.callCompleted=1;}catch(const Stop&){caught=true;}}
 need(caught==(cs->fault!=0));if(!caught){need(active->count==expectedCount&&active->capacity==expectedCapacity);if(cs->mode==26){need(active->data[0]==quest[2]&&active->data[1]==quest[1]);}if(cs->mode==24)need(active->data[1]==quest[1]);
  for(unsigned i=0;i<8;++i){unsigned char expected[0x220];std::memcpy(expected,questBefore[i],sizeof(expected));if(i==0&&(notifies(cs->mode)||cs->mode==32))expected[0x209]=1;if(i==0&&cs->mode==31)expected[0x29]=0;need(!std::memcmp(expected,quest[i],sizeof(expected)));n(at<unsigned char>(quest[i],0x209));}
  unsigned char expected[0xd0];std::memcpy(expected,ownerBefore,sizeof(expected));at<unsigned>(expected,0x20)=expectedCount;need(!std::memcmp(expected,owner,sizeof(expected)));
 }
 tail(caught);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}

TL_TEST(questmanager_acquisition_events){using namespace qae;autotest::Coverage cov("questmanager_acquisition_events",0xd2f470);unsigned count=0;
 for(unsigned mode=0;mode<40;++mode)for(unsigned variant=0;variant<2;++variant){Case c={mode,variant,0};if(!pair(host,cov,qae_event::a,qae_event::b,c)){cov.report(host);return 1;}++count;}
 cov.report(host);return cov.completed!=count||cov.completed<20||cov.different||cov.missing;
}

namespace qae_give {
using namespace qae;
void uiPlan(unsigned id,unsigned m,const wchar_t* translated=L"translated new quest"){
 if(m==14){tag(id,0x38,L"title check");tag(id,0x40,L"");tag(id,0x38,L"title output");expect(Big,0,0,L"title output");return;}
 if(m==15){tag(id,0x38,L"");tag(id,0x38,L"");tag(id,0x40,L"subtitle check");tag(id,0x40,L"subtitle output");expect(Small,0,0,L"subtitle output");return;}
 if(m==16){tag(id,0x38,L"first title");tag(id,0x40,L"first subtitle");tag(id,0x38,L"second title");tag(id,0x38,L"third title");tag(id,0x40,L"third subtitle");tag(id,0x38,L"title output");expect(Big,0,0,L"title output");tag(id,0x40,L"subtitle output");expect(Small,0,0,L"subtitle output");return;}
 if(m==17){tag(id,0x38,L"first title");tag(id,0x40,L"first subtitle");tag(id,0x38,L"");tag(id,0x40,L"second subtitle");tag(id,0x40,L"changing subtitle output");expect(Small,0,0,L"changing subtitle output");return;}
 if(m==18){tag(id,0x38,L"");tag(id,0x38,L"second title");tag(id,0x38,L"third title");tag(id,0x40,L"third subtitle");tag(id,0x38,L"changing title output");expect(Big,0,0,L"changing title output");tag(id,0x40,L"changing subtitle output");expect(Small,0,0,L"changing subtitle output");return;}
 tag(id,0x38,L"");tag(id,0x38,L"");tag(id,0x40,L"");tag(id,0x38,L"");tag(id,0x58,m==13?L"":L"description check");if(m==13)return;
 expect(Big,0,0,translated);tag(id,0x58,m==19?L"changed description output":L"description output");expect(Small,0,0,m==19?L"changed description output":L"description output");
}
bool rejects(unsigned m){return m<3;}
bool hasPlayer(unsigned m){return m!=4&&m!=5&&m!=6&&m!=7&&m!=8&&m!=30&&m!=31&&m!=32&&m!=3;}
bool announces(unsigned m){return hasPlayer(m)&&m!=9&&m!=10&&m!=27&&m!=28&&m!=29&&m!=33&&m!=34&&m!=35&&m!=36&&m!=37&&m!=38;}
void plan(){unsigned m=cs->mode;expectedCount=1;expectedCapacity=8;
 if(!hasPlayer(m))at<void*>(owner,0x10)=0;
 if(m==0){expectedCount=0;return;}if(m==1){at<unsigned char>(quest[0],0x26)=1;expectedCount=0;return;}if(m==2){active->data[0]=quest[0];active->count=1;return;}
 if(m==5)at<void*>(resource,0x18)=0;
 if(m==3){active->count=2;active->capacity=1;active->data[0]=quest[1];active->data[1]=quest[0];expectedCount=3;expectedCapacity=5;}
 if(m==6){active->data=0;active->capacity=0;expectedCapacity=4;}
 if(m==7){active->count=active->capacity=2;active->data[0]=quest[1];active->data[1]=quest[2];expectedCount=3;expectedCapacity=6;}
 if(m==8){active->count=2;active->data[0]=quest[1];active->data[1]=quest[2];expectedCount=3;}
 if(m==10)at<unsigned char>(quest[0],0x25)=1;
 if(m==20)at<void*>(player,0x68)=0;if(m==21)at<void*>(playerResource,0x18)=0;
 if(m==24||m==26)at<void*>(player,0x298)=0;if(m==25||m==26)at<void*>(owner,0x30)=0;
 if(m>=27&&m<=30)at<unsigned char>(quest[0],0x2b)=1;
 if(m>=33&&m<=36){controllers->count=m==34?1:3;controllers->data[0]=wrapper[0];controllers->data[1]=wrapper[1];controllers->data[2]=wrapper[2];
  if(m==33){at<std::wstring>(controller[1],0xa8)=L"quest mixed case";at<void*>(wrapper[2],0)=0;}
  if(m==36)controllers->capacity=1;
 }
 unsigned repeats=m==31||m==32?3:1;if(repeats==3)expectedCount=3;
 for(unsigned p=0;p<repeats;++p){unsigned id=p;if(!p||m==31)translation(L"New Quest",m==31&&p<2?L"":L"translated new quest");
  if(!p&&(m==3||m==6||m==7)){expect(ArrayNew,0,expectedCapacity*8);if(m!=6)expect(ArrayDelete);}
  expect(Accepted,id,1);
  if(announces(m)){expect(Details,id);if(m!=11){tag(id,0x58,m==13?L"":L"audio description");if(m!=13)sounds(31,m!=24&&m!=26,m!=25&&m!=26);}
   if(m!=20&&m!=21&&m!=22&&m!=23)uiPlan(id,m);
  }
  if(m==27)status(0,0x100);if(m==28||m==29){status(0,m==29?0x101:1);expect(Complete);expect(Remove);expectedCount=0;}
  if(m!=5)icons(0,m==37?1:0);
  if(m==33||m==35)expect(ControllerAccepted,0,1);
  if(m==34){expect(ControllerAccepted,0,1);expect(ControllerAccepted,1,1);expect(ControllerAccepted,2,1);}
  if(m==36)for(unsigned i=0;i<3;++i)expect(ControllerAccepted,0,1);
 }
}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;setup(0);plan();saveBefore();typedef long long(*Fn)(void*,void*,void*,bool);Fn fn=candidate?&qaeNewGive:&qaeOldGive;bool caught=false;long long result=-1;
 {detour::Set d,alloc;hook(d,true,true);alloc.redirect(qaeArrayNew,qaeArrayNew,&arrayNew);alloc.redirect(qaeArrayDelete,qaeArrayDelete,&arrayDelete);if(d.failed()||alloc.failed()){out.issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(out,fn))return;
  try{unsigned repeats=cs->mode==31||cs->mode==32?3:1;bool announce=cs->mode!=9&&!(cs->mode>=27&&cs->mode<=29)&&cs->mode<33;for(pass=0;pass<repeats;++pass){result=fn(owner,cs->mode==0?0:quest[pass],cs->variant?(void*)1:unit,announce);need(result==(rejects(cs->mode)?0:1));}out.callCompleted=1;}catch(const Stop&){caught=true;}}
 need(caught==(cs->fault!=0));if(!caught){need(active->count==expectedCount&&active->capacity==expectedCapacity);need(active->grow==4&&active->pad==0x27ac310);
  if(!rejects(cs->mode)&&cs->mode!=28&&cs->mode!=29){unsigned target=initialCount;need(active->data[target]==quest[0]);if(cs->mode==3)need(active->data[1]==0);if(cs->mode==31||cs->mode==32){need(active->data[1]==quest[1]&&active->data[2]==quest[2]);}for(unsigned i=0;i<initialCapacity&&i<initialCount;++i)need(active->data[i]==initialData[i]);}
  for(unsigned i=0;i<8;++i){unsigned char expected[0x220];std::memcpy(expected,questBefore[i],sizeof(expected));if(!rejects(cs->mode)&&(i==0||((cs->mode==31||cs->mode==32)&&i<3)))expected[0x26]=1;if(i==0&&(cs->mode==28||cs->mode==29))expected[0x26]=0;if(i==0&&(cs->mode==22||cs->mode==23))expected[0x25]=1;if(i==0&&cs->mode==34)at<unsigned>(expected,0x1b8)=3;if(i==0&&cs->mode==35)at<unsigned>(expected,0x1b8)=1;need(!std::memcmp(expected,quest[i],sizeof(expected)));n(at<unsigned char>(quest[i],0x26));}
  unsigned char expected[0xd0];std::memcpy(expected,ownerBefore,sizeof(expected));at<void*>(expected,0x18)=active->data;at<unsigned>(expected,0x20)=expectedCount;at<unsigned>(expected,0x24)=expectedCapacity;need(!std::memcmp(expected,owner,sizeof(expected)));n((unsigned)result);n(active->count);n(active->capacity);
 }
 tail(caught);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}

TL_TEST(questmanager_give_acquisition){using namespace qae;autotest::Coverage cov("questmanager_give_acquisition",0xd33150);unsigned count=0;
 for(unsigned mode=0;mode<39;++mode)for(unsigned variant=0;variant<2;++variant){Case c={mode,variant,0};if(!pair(host,cov,qae_give::a,qae_give::b,c)){cov.report(host);return 1;}++count;}
 cov.report(host);return cov.completed!=count||cov.completed<20||cov.different||cov.missing;
}

TL_TEST(questmanager_acquisition_events_exceptions){using namespace qae;autotest::Coverage eventCov("event unwind excluded",0xd2f470),giveCov("give unwind excluded",0xd33150);
 const unsigned eventFaults[]={IsComplete,QuestEvent,Details,Queue,Play,Translate,Big,Tags,Small,Refresh};
 for(unsigned i=0;i<sizeof(eventFaults)/sizeof(eventFaults[0]);++i){Case c={11,0,eventFaults[i]};if(!pair(host,eventCov,qae_event::a,qae_event::b,c,true))return 1;}
 const unsigned giveFaults[]={Translate,Accepted,Details,Tags,Queue,Play,Big,Small,Icons,Automap};
 for(unsigned i=0;i<sizeof(giveFaults)/sizeof(giveFaults[0]);++i){Case c={12,0,giveFaults[i]};if(!pair(host,giveCov,qae_give::a,qae_give::b,c,true))return 1;}
 Case allocation={6,0,ArrayNew};if(!pair(host,giveCov,qae_give::a,qae_give::b,allocation,true))return 1;
 host->log(" acquisition/events: 21 expected collaborator/allocation unwinds, excluded from completed coverage\n");return 0;
}

namespace qae_chain {
using namespace qae;
void plan(){controllers->count=1;List* accept=(List*)((char*)quest[0]+0x60);accept->data=(void**)raw(16);accept->data[0]=dialogs[0];accept->data[1]=dialogs[1];accept->count=accept->capacity=2;accept->grow=2;
 at<unsigned char>(quest[0],0x2b)=1;at<unsigned char>(quest[0],0x20b)=cs->mode&1;
 if(cs->mode&4){expect(ManagerSingleton);at<void*>(controller[0],0x98)=quest[0];at<unsigned char>(quest[0],0x25)=1;List* other=(List*)((char*)quest[1]+0x60);other->data=(void**)raw(16);other->data[0]=alternateDialogs[0];other->data[1]=alternateDialogs[1];other->count=other->capacity=2;other->grow=2;}
 translation(L"New Quest",L"translated new quest");fallback(0,0,0,0,3);refresh();status(0,1);expect(Reward);expect(Initialize);
 if(!(cs->mode&1))status(0,1);expect(ControllerComplete,0,1);icons();expect(Master);expect(Setting);expect(Initialize);expect(ControllerAccepted,0,0);icons();icons();expect(ControllerAccepted,0,1);
}
void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;setup(2);plan();saveBefore();typedef long long(*Fn)(void*,void*,void*,bool);Fn fn=candidate?&qaeNewGive:&qaeOldGive;
 {detour::Set d,eventRoute,giveRoute;hook(d,false,false);TL_REDIRECT(d,qaeReward,&reward);TL_REDIRECT(d,qaeInitialize,&initialize);TL_REDIRECT(d,qaeControllerComplete,&controllerComplete);TL_REDIRECT(d,qaeMaster,&getMaster);TL_REDIRECT(d,qaeSetting,&getSetting);TL_REDIRECT(d,qaeManagerSingleton,&getManager);
  // Actual accepted(true) is an original-only method in the baseline. Route
  // only its original event tail to the selected replacement on this side.
  if(candidate)eventRoute.redirect(reinterpret_cast<char*>(&qaeOldEvent),reinterpret_cast<char*>(&qaeOldEvent),&qaeNewEvent);
  if(candidate&&(cs->mode&4))giveRoute.redirect(reinterpret_cast<char*>(&qaeOldGive),reinterpret_cast<char*>(&qaeOldGive),&qaeNewGive);
  if(d.failed()||eventRoute.failed()||giveRoute.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->mode&4){typedef void(*ControllerFn)(void*,bool);ControllerFn controllerFn=candidate&&(cs->variant&4)?&qaeNewControllerAccept:&qaeOldControllerAccept;if(!autotest::beginInvocation(out,controllerFn))return;controllerFn(controller[0],true);out.callCompleted=1;}
  else{if(!autotest::beginInvocation(out,fn))return;long long r=fn(owner,quest[0],cs->variant?(void*)1:unit,false);out.callCompleted=1;need(r==1);}}
 need(active->count==0);need(at<unsigned char>(quest[0],0x26)==0);need(at<unsigned char>(quest[0],0x24)==!(cs->mode&1));need(at<unsigned char>(quest[0],0x209)==0);need(completed->size()==1&&completed->begin()->first==L"Quest Mixed Case"&&completed->begin()->second==!(cs->mode&1));for(unsigned i=0;i<2;++i){need(at<unsigned char>(dialogs[i],0x76)==((cs->mode&4)&&!(cs->mode&2)));need(at<unsigned char>(alternateDialogs[i],0x76)==((cs->mode&4)&&(cs->mode&2)));}need(!at<unsigned char>(quest[1],0x26));
 n(active->count);n(at<unsigned char>(quest[0],0x24));n(at<unsigned char>(quest[0],0x26));n(completed->size());n(completed->begin()->second);tail(false);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}

TL_TEST(questmanager_real_acquisition_chain){using namespace qae;autotest::Coverage cov("questmanager_real_acquisition_chain",0xd33150);
 for(unsigned mode=0;mode<2;++mode)for(unsigned variant=0;variant<2;++variant){Case c={mode,variant,0};if(!pair(host,cov,qae_chain::a,qae_chain::b,c)){cov.report(host);return 1;}}
 cov.report(host);return cov.completed!=4||cov.different||cov.missing;
}

// This boundary deliberately invokes the ORIGINAL controller on both sides.
// It validates manager consumers, not the deferred replacement controller.
TL_TEST(questmanager_original_controller_acquisition_consumer){using namespace qae;
 for(unsigned mode=4;mode<8;++mode)for(unsigned variant=0;variant<2;++variant){Case c={mode,variant,0};autotest::Outcome x,y;autotest::runChild(qae_chain::a,&c,x);autotest::runChild(qae_chain::b,&c,y);
  bool ok=good(x)&&good(y)&&x.capture.callStarted&&y.capture.callStarted&&x.capture.callCompleted&&y.capture.callCompleted&&x.capture.callTarget==0xde6c00&&y.capture.callTarget==0xde6c00&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
  if(!ok){host->log(" original controller acquisition consumer mode=%u variant=%u oracle=%u/%u status=%d/%d\n",mode,variant,good(x),good(y),x.childStatus,y.childStatus);return 1;}}
 host->log(" original controller acquisition: 8 state/order comparisons; no controller replacement acceptance claimed\n");return 0;
}

TL_TEST(questmanager_original_client_event_consumer){using namespace qae;const unsigned cases[]={0,1,3,4,5,6,11,19,23,30,33,34};
 for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i){Case c={cases[i],2,0};autotest::Outcome x,y;autotest::runChild(qae_event::a,&c,x);autotest::runChild(qae_event::b,&c,y);
  bool ok=good(x)&&good(y)&&x.capture.callStarted&&y.capture.callStarted&&x.capture.callCompleted&&y.capture.callCompleted&&x.capture.callTarget==0x56e890&&y.capture.callTarget==0x56e890&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
  if(!ok){host->log(" original client event consumer mode=%u oracle=%u/%u status=%d/%d\n",c.mode,good(x),good(y),x.childStatus,y.childStatus);return 1;}}
 host->log(" original client event: 12 manager boundary comparisons; no consumer replacement acceptance claimed\n");return 0;
}

// New controller acceptance. Existing original-only consumer stays original-only.
// Real manager give, quest setter/event, complete/remove and dialog setter remain
// active; external effects only retain the already-reviewed PR94 interceptors.
TL_TEST(questcontroller_real_acquisition_chain){using namespace qae;autotest::Coverage cov("questcontroller_real_acquisition_chain",0xde6c00);
 for(unsigned mode=4;mode<8;++mode)for(unsigned variant=4;variant<6;++variant){Case c={mode,variant,0};if(!pair(host,cov,qae_chain::a,qae_chain::b,c)){cov.report(host);return 1;}}
 cov.report(host);return cov.completed!=8||cov.different||cov.missing;
}
