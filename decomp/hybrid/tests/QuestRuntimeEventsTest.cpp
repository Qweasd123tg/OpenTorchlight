// Independent oracle for original d0cc10 (627 bytes) / d0ce90 (2335 bytes).
// Derived from original instructions and the six-entry table at ff6918.
// Lane 0 controls collaborator outcomes and mutates bounded list shapes.
// Lane 1 runs original-only QuestUnitData methods, accepted manager lookups,
// accepted setIsComplete and accepted manager notification. No UnitData method
// gains acceptance here. Position and zero-child spawning are genuine calls.
// Guarded ABI objects cover these routines, not complete gameplay/lifetimes.
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long,qreOldComplete,(void*,bool),"_ZN6CQuest10isCompleteEb")
extern "C" long long qreNewComplete(void*,bool) __asm__("_ZN6CQuest10isCompleteEb");
TL_ORIGINAL(void,qreOldEvent,(void*,unsigned,void*,void*),"_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_")
extern "C" void qreNewEvent(void*,unsigned,void*,void*) __asm__("_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_");
TL_FUNCTION(qreComplete,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(qreUnitComplete,"_ZN14CQuestUnitData10isCompleteEb")
TL_FUNCTION(qrePickup,"_ZN14CQuestUnitData12unitPickedUpEP9CBaseUnit")
TL_FUNCTION(qreDefeat,"_ZN14CQuestUnitData12unitDefeatedEP9CBaseUnit")
TL_FUNCTION(qreInteract,"_ZN14CQuestUnitData14unitInteractedEP9CBaseUnit")
TL_FUNCTION(qreDrop,"_ZN14CQuestUnitData11unitDroppedEP9CBaseUnit")
TL_FUNCTION(qreActive,"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qreDone,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qreSetter,"_ZN6CQuest13setIsCompleteEb")
TL_FUNCTION(qreNotify,"_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit")
extern "C" bool qreAcceptedActive(void*,const std::wstring&) __asm__("_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE");
extern "C" char qreAcceptedDone(void*,const std::wstring&) __asm__("_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void qreAcceptedSetter(void*,bool) __asm__("_ZN6CQuest13setIsCompleteEb");
extern "C" void qreAcceptedNotify(void*,unsigned,void*,void*) __asm__("_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit");
namespace qre {
typedef std::wstring Wide;
typedef std::map<Wide,bool> Map;
struct List {void** data;unsigned count,capacity,grow,pad;};
struct Flags {unsigned char* data;unsigned count,capacity,grow,pad;};
struct Names {Wide* data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(List)==24&&sizeof(Wide)==8&&sizeof(Map)==48?1:-1];
// kind 0 direct isComplete; 1 event with controlled completion callback;
// 2 event composed with the corresponding original/replacement isComplete.
// state bits: cached complete, blocked +2a, force-completion argument.
// actor: 0 player, 1 other, 2 null, 3 player/null target, 4 both player/actor null.
struct Case {unsigned kind,event,shape,state,reply,real,actor,mutation,repeats;};
enum Code {UnitComplete=1,Pickup,Defeat,Interact,Drop,Active,Done,Complete,Setter,Notify};
struct Event {unsigned code,id,arg,complete,outer0,outer1,unitDone,unitCount,flag0,flag1;};
struct NodeBefore {void* p;unsigned char bytes[48];};
static const Case* cs;static autotest::Capture* cap;static bool candidateSide,modelMutated,actualMutated;
static unsigned errors,firstError,wanted,observed,arenaSize,modelCompleteCalls,actualCompleteCalls;
static unsigned char expected[65536];static Event events[2048];
static void *owner,*manager,*player,*other,*target,*resource,*level,*groupMarker;
static void *units[18],*dialogs[3],*dummyQuests[3];static List* groups[6];
static Names* names[2];static Flags* flags[2];static Map* completed;static NodeBefore mapNodes[3];static unsigned mapNodeCount;
static unsigned expectedResults[3],resultCount;
static detour::Set *unitPatches[5],*completePatch,*setterPatch,*activePatch,*donePatch,*notifyPatch;
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
static void check(bool good,unsigned line){if(!good){if(!errors)firstError=line;if(errors<4)std::fprintf(stderr,"    QRE %s kind=%u e=%u shape=%u state=%u reply=%u real=%u actor=%u mutation=%u line=%u event=%u/%u\n",candidateSide?"candidate":"original",cs->kind,cs->event,cs->shape,cs->state,cs->reply,cs->real,cs->actor,cs->mutation,line,observed,wanted);++errors;}}
#define need(x) check((x),__LINE__)
static void n(unsigned v){cap->add(&v,4);}
static void* raw(unsigned size,unsigned char fill=0){unsigned char* p=(unsigned char*)autotest::allocate(size+32);if(!p)_exit(71);std::memset(p,0xa7,size+32);std::memset(p+16,fill,size);return p+16;}
static void* mem(void* p,bool model){return model?expected+((char*)p-autotest::g_arena):p;}
template<class T>T& field(void* p,unsigned o,bool model){return at<T>(mem(p,model),o);}
static List& outer(unsigned f,bool model){return field<List>(owner,0x130+24*f,model);}
static void* slot(const List& l,unsigned i,bool model){return ((void**)mem(l.data,model))[i<l.capacity?i:0];}
static void initList(List& l,unsigned count,unsigned capacity=4){l.data=(void**)raw(32);l.count=count;l.capacity=capacity;l.grow=3;l.pad=0x55667788;}
static unsigned id(void* p){for(unsigned i=0;i<18;++i)if(units[i]==p)return i;need(false);return 0;}
static unsigned char& flag(unsigned f,unsigned i,bool model){Flags& l=field<Flags>(owner,0xf8+24*f,model);return ((unsigned char*)mem(l.data,model))[i<l.capacity?i:0];}
static unsigned packedFlags(unsigned f,bool model){Flags& l=field<Flags>(owner,0xf8+24*f,model);unsigned v=0;std::memcpy(&v,mem(l.data,model),4);return v;}
static void trace(bool model,unsigned code,unsigned who=99,unsigned arg=0){Event e={code,who,arg,field<unsigned char>(owner,0x24,model),outer(0,model).count,outer(1,model).count,who<18?field<unsigned char>(units[who],0x60,model):0,who<18?field<unsigned>(units[who],0x3c,model):0,packedFlags(0,model),packedFlags(1,model)};
 if(model){if(wanted==2048)_exit(72);events[wanted++]=e;}else{need(observed<wanted);if(observed<wanted)need(!std::memcmp(&e,&events[observed],sizeof(e)));++observed;cap->add(&e,sizeof(e));}}
static bool matches(unsigned i){switch(cs->reply){case 0:return false;case 1:return i%3==0;case 2:return i%3==1;case 3:return i%3==2;default:return true;}}
static bool lookupValue(unsigned i){return cs->reply==0?false:cs->reply==2?true:i!=1;}
static void mutation(bool model,unsigned code){bool& used=model?modelMutated:actualMutated;if(used||!cs->mutation)return;
 if(cs->mutation<7){if(code<UnitComplete||code>Drop)return;}else if(code!=Active&&code!=Done)return;used=true;
 switch(cs->mutation){case 1:outer(0,model).count=1;break;case 2:outer(0,model).count=3;break;case 3:outer(0,model).capacity=1;break;
 case 4:field<List>(groups[0],0,model).count=1;break;case 5:field<List>(groups[0],0,model).capacity=1;break;
 case 6:((void**)mem(outer(0,model).data,model))[1]=groups[5];break;
 case 7:field<Names>(owner,cs->event==3?0xc8:0xe0,model).count=1;break;
 case 8:field<Flags>(owner,cs->event==3?0xf8:0x110,model).capacity=1;break;
 }}
static void modelSetter(){trace(true,Setter,99,1);bool changed=!field<unsigned char>(owner,0x24,true);field<unsigned char>(owner,0x24,true)=1;if(cs->real&&changed)trace(true,Notify,99,4);}
static bool modelUnitComplete(unsigned i){trace(true,UnitComplete,i,0);mutation(true,UnitComplete);return field<unsigned char>(units[i],0x60,true)!=0;}
static bool modelComplete(bool force){if(!force&&field<unsigned char>(owner,0x24,true))return true;if(field<unsigned char>(owner,0x2a,true))return false;bool any=false;
 for(unsigned f=0;f<2;++f)for(unsigned i=0;i<outer(f,true).count;++i){for(unsigned j=0;;++j){List* g=(List*)slot(outer(f,true),i,true);List& l=field<List>(g,0,true);if(j>=l.count)break;unsigned u=id(slot(l,j,true));if(!modelUnitComplete(u))return false;any=true;}}
 for(unsigned f=0;f<2;++f){Flags& l=field<Flags>(owner,0xf8+24*f,true);for(unsigned i=0;i<l.count;++i){if(!flag(f,i,true))return false;any=true;}}
 if(!any){if(force)return false;List& l=field<List>(owner,0x60,true);if(l.count){bool seen=false;for(unsigned i=0;i<l.count;++i)if(field<unsigned char>(slot(l,i,true),0x76,true)){seen=true;break;}if(!seen)return false;}}
 modelSetter();return true;
}
static bool modelUnit(unsigned code,unsigned i){trace(true,code,i,cs->actor==3?0:1);mutation(true,code);unsigned char& complete=field<unsigned char>(units[i],0x60,true);unsigned& count=field<unsigned>(units[i],0x3c,true);
 if(!cs->real){++count;if(!matches(i))return false;complete=code==Drop?0:1;return true;}
 if(code==Interact){if(cs->actor==3||complete)return false;++count;if(count<field<unsigned>(units[i],0x38,true))return false;complete=1;return true;}
 if(!field<unsigned char>(units[i],0xb9,true))return false;
 if(code==Drop){if(cs->actor==3)return false;if(count)--count;complete=0;return true;}
 if(code==Defeat){if(complete)return false;++count;if(count<field<unsigned>(units[i],0x38,true))return false;complete=1;return true;}
 // Genuine pickup: matching group, quest identity, no children/UI resource.
 ++count;if(count>=field<unsigned>(units[i],0x38,true))complete=1;if(count>field<unsigned>(units[i],0x38,true))count=field<unsigned>(units[i],0x38,true);field<long long>(target,0x170,true)=field<long long>(owner,0x1c8,true);return true;
}
static void modelCompleteCallback(){trace(true,Complete,99,0);++modelCompleteCalls;if(cs->kind==1){field<unsigned char>(owner,0x24,true)=!field<unsigned char>(owner,0x24,true);return;}modelComplete(false);}
static void modelEvent(){if(cs->event>5)return;if(cs->event==2&&(cs->actor==1||cs->actor==2))return;
 if(cs->event==3||cs->event==4){unsigned f=cs->event-3;for(unsigned i=0;i<field<Names>(owner,0xc8+24*f,true).count;++i){if(flag(f,i,true))continue;Names& l=field<Names>(owner,0xc8+24*f,true);unsigned k=i<l.capacity?i:0;trace(true,f?Done:Active,99,k);mutation(true,f?Done:Active);if(lookupValue(k))flag(f,i,true)=1;}modelCompleteCallback();return;}
 unsigned code=cs->event==0?Pickup:cs->event==1?Defeat:cs->event==2?Interact:Drop;
 for(unsigned f=0;f<2;++f)for(unsigned i=0;i<outer(f,true).count;++i)for(unsigned j=0;;++j){List* g=(List*)slot(outer(f,true),i,true);List& l=field<List>(g,0,true);if(j>=l.count)break;unsigned u=id(slot(l,j,true));if(modelUnit(code,u)){if(code==Drop)field<unsigned char>(owner,0x24,true)=0;else modelCompleteCallback();break;}}
}
static void setup(){errors=firstError=wanted=observed=modelCompleteCalls=actualCompleteCalls=mapNodeCount=resultCount=0;modelMutated=actualMutated=false;autotest::g_arenaUsed=0;
 owner=raw(0x218,0x59);manager=raw(0xd0,0x61);player=raw(0x1c0,0x43);other=raw(0x1c0,0x44);target=raw(0x1c0,0x45);resource=raw(0x40);level=raw(0x40);groupMarker=raw(0x40);
 field<unsigned char>(owner,0x24,false)=cs->state&1;field<unsigned char>(owner,0x2a,false)=(cs->state&2)!=0;at<void*>(owner,0x1d0)=manager;at<long long>(owner,0x1c8)=0x1122334455667788LL;
 at<void*>(manager,0x10)=cs->event==2&&cs->actor!=4?player:0;initList(at<List>(manager,0x18),0);completed=new((char*)manager+0x70)Map;
 at<void*>(target,0x58)=0;at<void*>(target,0x68)=cs->event==2?resource:0;at<void*>(resource,0x18)=level;at<void*>(target,0x1b0)=groupMarker;at<long long>(target,0x170)=at<long long>(owner,0x1c8);at<unsigned>(target,0x178)=42;
 const wchar_t* keys[3]={L"active alpha",L"missing or false",L"\u0416\u732b"};
 for(unsigned f=0;f<2;++f){names[f]=&at<Names>(owner,0xc8+24*f);names[f]->data=(Wide*)raw(24);names[f]->count=0;names[f]->capacity=3;names[f]->grow=4;names[f]->pad=0x1122aabb;flags[f]=&at<Flags>(owner,0xf8+24*f);flags[f]->data=(unsigned char*)raw(8,0x71);flags[f]->count=0;flags[f]->capacity=8;flags[f]->grow=2;flags[f]->pad=0x2211ccdd;
  for(unsigned i=0;i<3;++i){new(names[f]->data+i)Wide(keys[i]);flags[f]->data[i]=1;}for(unsigned i=3;i<8;++i)flags[f]->data[i]=0x71;}
 for(unsigned i=0;i<3;++i){dummyQuests[i]=raw(0x218);at<unsigned char>(dummyQuests[i],0x24)=1;new((char*)dummyQuests[i]+0x50)Wide(keys[i]);if(cs->event==3&&lookupValue(i)){List& active=at<List>(manager,0x18);active.data[active.count++]=dummyQuests[i];}completed->insert(Map::value_type(Wide(keys[i]),lookupValue(i)));dialogs[i]=raw(0xa8,0x51);at<unsigned char>(dialogs[i],0x76)=0;}
 for(unsigned i=0;i<18;++i){units[i]=raw(0xc8,0x63);at<void*>(units[i],0x18)=owner;at<void*>(units[i],0x20)=groupMarker;at<unsigned>(units[i],0x10)=42;at<unsigned>(units[i],0x38)=2;at<unsigned>(units[i],0x3c)=cs->kind==0?7:cs->event==5?2:1;at<unsigned>(units[i],0x40)=1;at<unsigned>(units[i],0x44)=22;at<void*>(units[i],0x48)=0;at<unsigned>(units[i],0x50)=at<unsigned>(units[i],0x54)=0;at<unsigned char>(units[i],0x63)=0;at<unsigned>(units[i],0xb4)=1;at<unsigned char>(units[i],0xb9)=matches(i);at<unsigned char>(units[i],0x60)=cs->kind==0?1:cs->event==5?1:cs->real&&cs->event==2?!matches(i):0;}
 for(unsigned g=0;g<6;++g){groups[g]=(List*)raw(24);initList(*groups[g],3);for(unsigned i=0;i<3;++i)groups[g]->data[i]=units[g*3+i];}
 for(unsigned f=0;f<3;++f){initList(at<List>(owner,0x130+24*f),f==2?2:0);for(unsigned i=0;i<3;++i)at<List>(owner,0x130+24*f).data[i]=groups[(f*3+i)%6];}
 List& d=at<List>(owner,0x60);initList(d,0);for(unsigned i=0;i<3;++i)d.data[i]=dialogs[i];
 unsigned s=cs->shape;
 if(s>=1&&s<=8){outer(0,false).count=outer(1,false).count=2;if(s==2)outer(1,false).count=0;if(s==3)outer(0,false).count=0;if(s==4)for(unsigned g=0;g<6;++g)groups[g]->count=0;
  if(s==5){outer(0,false).count=outer(1,false).count=3;outer(0,false).capacity=outer(1,false).capacity=1;}
  if(s==6)for(unsigned g=0;g<6;++g)groups[g]->capacity=1;
  if(s==7){outer(0,false).capacity=outer(1,false).capacity=0;for(unsigned g=0;g<6;++g)groups[g]->capacity=0;}
  if(s==8){outer(0,false).data[1]=groups[0];outer(1,false).data[0]=groups[0];groups[0]->data[1]=units[0];}}
 if(s>=9&&s<=15){for(unsigned f=0;f<2;++f){names[f]->count=flags[f]->count=3;for(unsigned i=0;i<3;++i)flags[f]->data[i]=cs->kind==0?1:cs->reply==3&&i==0?1:0;}if(s==10)names[1]->count=flags[1]->count=0;if(s==11)names[0]->count=flags[0]->count=0;
  if(s==12)flags[0]->capacity=flags[1]->capacity=1;if(s==13)names[0]->capacity=names[1]->capacity=1;if(s==14)flags[0]->count=flags[1]->count=1;if(s==15)names[0]->count=names[1]->count=1;}
 if(s>=16&&s<=19){d.count=3;if(s==17||s==18)at<unsigned char>(dialogs[2],0x76)=1;if(s==18)d.capacity=1;if(s==19)at<unsigned char>(dialogs[0],0x76)=1;}
 if(cs->kind==0){if(cs->reply==1){at<unsigned char>(units[0],0x60)=0;flags[0]->data[0]=0;}if(cs->reply==2){at<unsigned char>(units[11],0x60)=0;flags[1]->data[2]=0;}if(cs->reply==3){at<unsigned char>(units[4],0x60)=0;flags[0]->data[1]=0;}}
 if(cs->mutation==2)outer(0,false).count=1;
 for(Map::iterator it=completed->begin();it!=completed->end();++it){need(mapNodeCount<3);mapNodes[mapNodeCount].p=it._M_node;std::memcpy(mapNodes[mapNodeCount++].bytes,it._M_node,48);}
 arenaSize=(unsigned)autotest::g_arenaUsed;need(arenaSize<sizeof(expected));std::memcpy(expected,autotest::g_arena,arenaSize);
 for(unsigned repeat=0;repeat<cs->repeats;++repeat){if(cs->kind==0)expectedResults[resultCount++]=modelComplete((cs->state&4)!=0);else modelEvent();}
}
// Selftests run before install_hooks. Restore the observer, explicitly call
// __tlorig_, and reinstall both entries: never call unaccepted linked UnitData.
static bool unitComplete(void* self,bool force){unsigned i=id(self);trace(false,UnitComplete,i,force);need(!force);mutation(false,UnitComplete);if(!cs->real)return at<unsigned char>(self,0x60)!=0;unitPatches[0]->restore();bool value=reinterpret_cast<bool(*)(void*,bool)>(qreUnitComplete_original)(self,force);TL_REDIRECT(*unitPatches[0],qreUnitComplete,&unitComplete);return value;}
static unsigned long pickup(void*,void*);static bool defeat(void*,void*);static bool interact(void*,void*);static bool drop(void*,void*);
static bool unitEvent(void* self,void* t,unsigned code){unsigned i=id(self);need(t==(cs->actor==3?0:target));trace(false,code,i,t?1:0);mutation(false,code);
 if(!cs->real){++at<unsigned>(self,0x3c);if(!matches(i))return false;at<unsigned char>(self,0x60)=code==Drop?0:1;return true;}
 unsigned k=code-1;unitPatches[k]->restore();bool value=false;
 if(code==Pickup)value=reinterpret_cast<bool(*)(void*,void*)>(qrePickup_original)(self,t);
 if(code==Defeat)value=reinterpret_cast<bool(*)(void*,void*)>(qreDefeat_original)(self,t);
 if(code==Interact)value=reinterpret_cast<bool(*)(void*,void*)>(qreInteract_original)(self,t);
 if(code==Drop)value=reinterpret_cast<bool(*)(void*,void*)>(qreDrop_original)(self,t);
 if(code==Pickup)TL_REDIRECT(*unitPatches[k],qrePickup,&pickup);
 if(code==Defeat)TL_REDIRECT(*unitPatches[k],qreDefeat,&defeat);
 if(code==Interact)TL_REDIRECT(*unitPatches[k],qreInteract,&interact);
 if(code==Drop)TL_REDIRECT(*unitPatches[k],qreDrop,&drop);return value;
}
// Deliberately poison the upper return bits. Original callers test AL; the
// recovered UnitData pickup declaration is an unsigned-long placeholder.
static unsigned long pickup(void* q,void* t){return 0x100UL|(unitEvent(q,t,Pickup)?1UL:0UL);}static bool defeat(void* q,void* t){return unitEvent(q,t,Defeat);}static bool interact(void* q,void* t){return unitEvent(q,t,Interact);}static bool drop(void* q,void* t){return unitEvent(q,t,Drop);}
static unsigned keyIndex(const Wide& name,unsigned family){for(unsigned i=0;i<3;++i)if(&name==names[family]->data+i)return i;need(false);return 0;}
static bool active(void* self,const Wide& name){need(self==manager);unsigned i=keyIndex(name,0);trace(false,Active,99,i);mutation(false,Active);if(!cs->real)return lookupValue(i);activePatch->restore();bool value=qreAcceptedActive(self,name);TL_REDIRECT(*activePatch,qreActive,&active);return value;}
static char done(void* self,const Wide& name){need(self==manager);unsigned i=keyIndex(name,1);trace(false,Done,99,i);mutation(false,Done);if(!cs->real)return lookupValue(i);donePatch->restore();char value=qreAcceptedDone(self,name);TL_REDIRECT(*donePatch,qreDone,&done);return value;}
static void notify(void* self,unsigned e,void* actor,void* t){need(self==manager&&e==4&&!actor&&!t);trace(false,Notify,99,e);notifyPatch->restore();qreAcceptedNotify(self,e,actor,t);TL_REDIRECT(*notifyPatch,qreNotify,&notify);}
static void setter(void* self,bool value){need(self==owner&&value);trace(false,Setter,99,value);if(!cs->real){at<unsigned char>(self,0x24)=value;return;}setterPatch->restore();qreAcceptedSetter(self,value);TL_REDIRECT(*setterPatch,qreSetter,&setter);}
static long long complete(void* self,bool force){need(self==owner&&!force);trace(false,Complete,99,force);++actualCompleteCalls;if(cs->kind==1){at<unsigned char>(self,0x24)=!at<unsigned char>(self,0x24);return at<unsigned char>(self,0x24);}
 completePatch->restore();long long result=candidateSide?qreNewComplete(self,force):qreOldComplete(self,force);TL_REDIRECT(*completePatch,qreComplete,&complete);return result;}
static void side(void* context,autotest::Capture& out,bool candidate){cs=(Case*)context;cap=&out;candidateSide=candidate;setup();
 {detour::Set uc,pu,de,in,dr,co,se,ac,do_,no;unitPatches[0]=&uc;unitPatches[1]=&pu;unitPatches[2]=&de;unitPatches[3]=&in;unitPatches[4]=&dr;completePatch=&co;setterPatch=&se;activePatch=&ac;donePatch=&do_;notifyPatch=&no;
  TL_REDIRECT(uc,qreUnitComplete,&unitComplete);TL_REDIRECT(pu,qrePickup,&pickup);TL_REDIRECT(de,qreDefeat,&defeat);TL_REDIRECT(in,qreInteract,&interact);TL_REDIRECT(dr,qreDrop,&drop);TL_REDIRECT(se,qreSetter,&setter);TL_REDIRECT(ac,qreActive,&active);TL_REDIRECT(do_,qreDone,&done);if(cs->real)TL_REDIRECT(no,qreNotify,&notify);if(cs->kind)TL_REDIRECT(co,qreComplete,&complete);
  if(uc.failed()||pu.failed()||de.failed()||in.failed()||dr.failed()||co.failed()||se.failed()||ac.failed()||do_.failed()||no.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(!cs->kind){typedef long long(*Fn)(void*,bool);Fn fn=candidate?&qreNewComplete:&qreOldComplete;if(!autotest::beginInvocation(out,fn))return;for(unsigned repeat=0;repeat<cs->repeats;++repeat){long long result=fn(owner,(cs->state&4)!=0);need(result==expectedResults[repeat]);n((unsigned)result);}}
  else {typedef void(*Fn)(void*,unsigned,void*,void*);Fn fn=candidate?&qreNewEvent:&qreOldEvent;if(!autotest::beginInvocation(out,fn))return;void* actor=cs->actor==0||cs->actor==3?player:cs->actor==1?other:0;for(unsigned repeat=0;repeat<cs->repeats;++repeat)fn(owner,cs->event,actor,cs->actor==3?0:target);}out.callCompleted=1;
 }
 need(observed==wanted);need(actualCompleteCalls==modelCompleteCalls);need(actualMutated==modelMutated);
 if(std::memcmp(expected,autotest::g_arena,arenaSize)){for(unsigned i=0;i<arenaSize;++i)if(expected[i]!=(unsigned char)autotest::g_arena[i]){if(errors<4)std::fprintf(stderr,"    QRE byte mismatch arena+%x expected=%02x actual=%02x\n",i,expected[i],(unsigned char)autotest::g_arena[i]);need(false);break;}}
 cap->add(autotest::g_arena,arenaSize);for(unsigned i=0;i<mapNodeCount;++i)need(!std::memcmp(mapNodes[i].bytes,mapNodes[i].p,48));
 n(wanted);n(actualCompleteCalls);n(firstError);n(0x7152e710u);n(errors);
 for(unsigned f=0;f<2;++f)for(unsigned i=0;i<3;++i)names[f]->data[i].~Wide();for(unsigned i=0;i<3;++i)at<Wide>(dummyQuests[i],0x50).~Wide();completed->~Map();
}
static void original(void* c,autotest::Capture& out){side(c,out,false);}static void candidate(void* c,autotest::Capture& out){side(c,out,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callCompleted&&tail[0]==0x7152e710u&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);bool ok=good(a)&&good(b);if(cv.observe(host,a,b))ok=false;if(!ok)host->log("    quest runtime kind=%u event=%u shape=%u state=%u reply=%u real=%u actor=%u mutation=%u repeats=%u status=%d/%d good=%u/%u issue=%u/%u\n",c.kind,c.event,c.shape,c.state,c.reply,c.real,c.actor,c.mutation,c.repeats,a.childStatus,b.childStatus,good(a),good(b),a.capture.issue,b.capture.issue);return ok;}
}
TL_TEST(quest_runtime_completion){using namespace qre;autotest::Coverage cv("quest_runtime_completion",0xd0cc10);unsigned n=0;
 for(unsigned shape=0;shape<=20;++shape)for(unsigned state=0;state<8;++state)for(unsigned real=0;real<2;++real){Case c={0,0,shape,state,0,real,0,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 const unsigned shapes[]={1,3,5,6,7,8,9,10,11,12,14,15};for(unsigned s=0;s<12;++s)for(unsigned reply=1;reply<4;++reply)for(unsigned real=0;real<2;++real){Case c={0,0,shapes[s],0,reply,real,0,0,1};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned m=1;m<=6;++m){Case c={0,0,1,4,0,0,0,m,1};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
TL_TEST(quest_runtime_events){using namespace qre;autotest::Coverage cv("quest_runtime_events",0xd0ce90);unsigned n=0;const unsigned values[]={0,1,2,3,4,5,6,0xffffffffu,0x80000000u};
 for(unsigned e=0;e<9;++e)for(unsigned shape=0;shape<=20;++shape)for(unsigned reply=0;reply<5;++reply){Case c={1,values[e],shape,1,reply,0,0,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned actor=1;actor<=4;++actor)for(unsigned reply=0;reply<5;++reply){Case c={1,2,1,0,reply,0,actor,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned e=0;e<6;++e)for(unsigned m=1;m<=8;++m){Case c={1,e,e==3||e==4?9:1,0,2,0,0,m,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
TL_TEST(quest_runtime_events_composed){using namespace qre;autotest::Coverage cv("quest_runtime_events_composed",0xd0ce90);unsigned n=0;
 for(unsigned e=0;e<6;++e)for(unsigned shape=0;shape<=20;++shape)for(unsigned real=0;real<2;++real)for(unsigned reply=1;reply<=4;++reply){Case c={2,e,shape,e==5?1u:0u,reply,real,0,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned actor=1;actor<=4;++actor){Case c={2,2,1,0,4,1,actor,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned e=0;e<6;++e)for(unsigned state=1;state<4;++state){Case c={2,e,e==3||e==4?9:1,state,4,0,0,0,2};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
