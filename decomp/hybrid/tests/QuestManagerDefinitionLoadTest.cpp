// Independent loader witnesses. Real GCC 4.4 maps and real COW strings; only
// documented collaborators are controlled. This does not claim definition-parser
// coverage. Deliberately leaked quest/bucket ownership is captured before cleanup.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
TL_ORIGINAL(void,qdlOld,(void*),"_ZN13CQuestManager10loadQuestsEv")
extern "C" void qdlNew(void*) __asm__("_ZN13CQuestManager10loadQuestsEv");
TL_FUNCTION(qdlFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(qdlFS,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(qdlCtor,"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_FUNCTION(qdlLoad,"_ZN6CQuest13loadQuestDataERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qdlNPC,"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
TL_FUNCTION(qdlConvert,"_ZN7STRINGS21StringConvertToNarrowEPKw")
extern "C" char qdlOgreNew[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qdlOgreDelete[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qdlLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char qdlLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
extern "C" char qdlArrayNew[] __asm__("_Znam");
extern "C" char qdlArrayDelete[] __asm__("_ZdaPv");
extern "C" char qdlScalarNew[] __asm__("_Znwm");
extern "C" char qdlScalarDelete[] __asm__("_ZdlPv");
extern "C" char qdlWideCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");
extern "C" char qdlWideCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qdlNarrowCtor[] __asm__("_ZNSsC1EPKcRKSaIcE");
extern "C" char qdlNarrowDestroy[] __asm__("_ZNSs4_Rep10_M_destroyERKSaIcE");
namespace qdl {
typedef std::map<std::wstring,void*> Names;
typedef std::map<std::wstring,bool> Completions;
struct List {void** data;unsigned count,capacity,grow,pad;};
typedef std::map<void*,List*> NPCs;
typedef char ABI[(sizeof(Names)==48&&sizeof(Completions)==48&&sizeof(NPCs)==48&&sizeof(List)==24&&sizeof(std::wstring)==8)?1:-1];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
enum Scenario {Empty,Simple,Mixed,Keys,Truthiness,Repeated,FileFallback,FileReread,NPCFallback,NPCReread,GrowthReread,FaultInput};
enum Fault {None,PatternThrow,DirectoryThrow,FilesThrow,QuestAllocateThrow,QuestConstructThrow,QuestLoadThrow,NamePairThrow,NameNodeAllocateThrow,NameNodeCopyThrow,CompletePairThrow,CompleteNodeAllocateThrow,CompleteNodeCopyThrow,NPCThrow,BucketAllocateThrow,NPCNodeAllocateThrow,FirstArrayThrow,GrowArrayThrow,FailedLogThrow,DuplicateLogThrow,FailedConvertThrow,DuplicateConvertThrow};
struct Case {unsigned scenario,fault,mode;};
struct Stop {};
struct Block {void* p;size_t bytes;bool live;unsigned kind;};
struct Major {unsigned kind,who;};
enum {FilesEvent=1,QuestAllocationEvent,ConstructorEvent,LoadEvent,NPCEvent,DeleteEvent,LogEvent};
enum {InitialPhase,FilesPhase,ConstructorPhase,LoadPhase,MapPhase,NPCPhase,AppendPhase};
const Case* cs;autotest::Capture* cap;bool candidateSide,tracking;
unsigned errors,firstError,phase,current,questCount,bucketCount,arrayCount,nodeCount,copyCount,wideCtorCount,majorCount,majorIndex,logs,deleted,expectedCaught;
unsigned fileCount,loadLimit,npcCount[24],npcKeys[24][8],loadIndices[24],expectedLive[24],expectedNamed[24],expectedCompleted[24],expectedDeleted[24];
unsigned expectedBuckets[4][32],expectedBucketCount[4],expectedBucketCap[4];
uint64_t returns[24];std::wstring files[24],keys[24];int keyRefs[24],fileRefs[24];
void* owner;void* resource;void* fileSystem;void* logger;void* npcObjects[4];void* quests[32];bool questNames[32];
Names* names;Completions* completions;NPCs* npcs;List* temp;List* fileList;List* initialBucket;
Block rawBlocks[64],arrays[256],nodes[128];unsigned rawCount;Major majors[256];
unsigned char ownerBefore[0xd0];detour::Set* copyPatch;detour::Set* ctorPatch;detour::Set* narrowCtorPatch;detour::Set* narrowDestroyPatch;
void* messageOuter[24];void* messageArgument[24];bool outerDestroyed[24],argumentDestroyed[24];
void n(unsigned x){cap->add(&x,4);}
void needAt(bool x,unsigned line){if(!x){if(!errors)firstError=line;if(errors<8)std::fprintf(stderr," QDL %s scenario=%u fault=%u mode=%u line=%u phase=%u current=%u\n",candidateSide?"candidate":"original",cs->scenario,cs->fault,cs->mode,line,phase,current);++errors;}}
#define need(x) needAt((x),__LINE__)
void expect(unsigned kind,unsigned who){if(majorCount==256)_exit(71);majors[majorCount].kind=kind;majors[majorCount++].who=who;}
void recordMajor(unsigned kind,unsigned who){need(majorIndex<majorCount);if(majorIndex<majorCount)need(majors[majorIndex].kind==kind&&majors[majorIndex].who==who);++majorIndex;n(0x100+kind);n(who);}
unsigned qid(void* p){if(!p)return 99;for(unsigned i=0;i<32;++i)if(quests[i]==p)return i;need(false);return 98;}
unsigned npcid(void* p){for(unsigned i=0;i<4;++i)if(npcObjects[i]==p)return i;need(false);return 98;}
int refs(const std::wstring& s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);}
void* arena(size_t bytes){void* p=autotest::allocate(bytes);if(!p)_exit(71);std::memset(p,0xa7,bytes);return p;}
void* fs(){return fileSystem;}void* logSingleton(){return logger;}
void* ogreNew(size_t bytes,const char* source,int line,const char* name){need(!source&&!line&&!name);need(bytes==0x218||bytes==24);n(0x200);n(bytes);n(phase);
 if(bytes==0x218){recordMajor(QuestAllocationEvent,questCount);if(cs->fault==QuestAllocateThrow)throw Stop();}
 else {need(temp!=0);if(cs->fault==BucketAllocateThrow)throw Stop();if(cs->scenario==NPCReread&&!bucketCount){temp->count=1;temp->data[0]=npcObjects[1];}}
 void* p=arena(bytes);if(rawCount==64)_exit(71);Block& b=rawBlocks[rawCount++];b.p=p;b.bytes=bytes;b.live=true;b.kind=bytes==0x218?0:1;
 if(bytes==0x218){need(questCount<24);quests[questCount++]=p;}else ++bucketCount;return p;
}
void ogreDelete(void* p){unsigned i=0;for(;i<rawCount;++i)if(rawBlocks[i].p==p)break;need(i<rawCount);if(i<rawCount){need(rawBlocks[i].live);rawBlocks[i].live=false;}n(0x201);n(i);}
void destroy(void* p){unsigned who=qid(p);recordMajor(DeleteEvent,who);if(who<24&&messageOuter[who]){need(argumentDestroyed[who]&&!outerDestroyed[who]);n(0x240);n(who);}
 need(who<24&&questNames[who]);if(who<24&&questNames[who]){at<std::wstring>(p,0x50).~basic_string();questNames[who]=false;}++deleted;ogreDelete(p);}
void* vtable[2]={reinterpret_cast<void*>(&destroy),reinterpret_cast<void*>(&destroy)};
void construct(void* p,void* r,void* manager){unsigned who=qid(p);current=who;phase=ConstructorPhase;recordMajor(ConstructorEvent,who);need(r==resource&&manager==owner);if(cs->fault==QuestConstructThrow)throw Stop();at<void**>(p,0)=vtable;new(static_cast<char*>(p)+0x50)std::wstring();questNames[who]=true;}
unsigned getFiles(void* self,const std::wstring& path,TArrayList<std::wstring>& output,std::wstring pattern,bool a,bool b,bool c,bool d){
 phase=FilesPhase;recordMajor(FilesEvent,0);need(self==fileSystem&&path==L"media/quests/"&&pattern==L"*.dat"&&a&&b&&!c&&!d);cap->addText(path);cap->addText(pattern);
 fileList=reinterpret_cast<List*>(&output);need(!fileList->data&&!fileList->count&&!fileList->capacity&&fileList->grow==10);
 for(unsigned i=0;i<fileCount;++i)output.add(files[i]);
 if(cs->scenario==FileFallback)fileList->capacity=1;
 if(cs->fault==FilesThrow)throw Stop();phase=InitialPhase;return 0x11223344;
}
long long load(void* p,const std::wstring& filename){unsigned who=qid(p);current=who;phase=LoadPhase;recordMajor(LoadEvent,who);need(who<loadLimit);if(who<loadLimit){need(filename==files[loadIndices[who]]);cap->addText(filename);at<std::wstring>(p,0x50)=keys[who];}
 if(cs->scenario==FileReread&&who==0)fileList->count=1;
 if(cs->fault==QuestLoadThrow)throw Stop();phase=MapPhase;return returns[who];
}
void getNPC(void* p,TArrayList<void*>& output){unsigned who=qid(p);phase=NPCPhase;recordMajor(NPCEvent,who);temp=reinterpret_cast<List*>(&output);need(!temp->data&&!temp->count&&!temp->capacity&&temp->grow==100);
 need(names->find(keys[who])!=names->end()&&names->find(keys[who])->second==p);need(completions->find(keys[who])!=completions->end()&&!completions->find(keys[who])->second);
 for(unsigned i=0;i<npcCount[who];++i)output.add(npcObjects[npcKeys[who][i]]);
 if(cs->scenario==NPCFallback)temp->capacity=1;
 if(cs->fault==NPCThrow)throw Stop();phase=AppendPhase;
}
void log(void* self,const std::string& message,int severity,bool mask){recordMajor(LogEvent,current);++logs;need(self==logger&&severity==3&&!mask);std::string expected;
 bool failed=(returns[current]&255)==0;
 if(failed){expected="Unable to load quest from file: ";const std::wstring& f=files[loadIndices[current]];for(unsigned i=0;i<f.size()&&f[i];++i)expected+=static_cast<char>(f[i]);need(!questNames[current]);}
 else {expected="There appears to be two quests named the samething. ";const std::wstring& key=keys[current];for(unsigned i=0;i<key.size()&&key[i];++i)expected+=static_cast<char>(key[i]);need(questNames[current]);}
 need(message==expected);cap->addText(message);n(severity);n(mask);if(cs->fault==FailedLogThrow||cs->fault==DuplicateLogThrow)throw Stop();
}
std::string failConvert(const wchar_t*){throw Stop();}
void* arrayNew(size_t bytes){n(0x210);n(bytes);n(phase);need(arrayCount<256);
 if(phase==AppendPhase){NPCs::iterator it=npcs->find(npcObjects[cs->scenario==NPCReread?1:2]);List* b=it==npcs->end()?0:it->second;
  if(cs->fault==FirstArrayThrow){need(b&&!b->data&&!b->count&&b->capacity==2);throw Stop();}
  if(cs->fault==GrowArrayThrow&&b&&b->data){need(b->count==2&&b->capacity==2&&bytes==32);throw Stop();}
  if(cs->scenario==GrowthReread&&b==initialBucket){need(bytes==32&&b->capacity==2&&b->count==2);b->count=1;b->capacity=1;}
 }
 void* p=std::malloc(bytes?bytes:1);if(!p)throw std::bad_alloc();std::memset(p,0,bytes);if(phase==AppendPhase)for(unsigned i=0;i<bytes/8;++i)static_cast<void**>(p)[i]=quests[29];
 Block& b=arrays[arrayCount++];b.p=p;b.bytes=bytes;b.live=true;b.kind=phase;return p;
}
void arrayDelete(void* p){if(!p)return;unsigned i=arrayCount;while(i&&!(arrays[i-1].p==p&&arrays[i-1].live))--i;
 if(!i&&initialBucket&&p==initialBucket->data){n(0x211);n(0xffffffffu);need(cs->scenario==GrowthReread&&initialBucket->capacity==1&&initialBucket->count==1);std::free(p);return;}
 need(i!=0);if(i){--i;arrays[i].live=false;n(0x211);n(i);n(arrays[i].kind);}
 std::free(p);
}
void* scalarNew(size_t bytes){bool node=tracking&&bytes==48&&(phase==MapPhase||phase==AppendPhase);if(node){n(0x220);n(copyCount);n(phase);
 if((cs->fault==NameNodeAllocateThrow&&copyCount==1)||(cs->fault==CompleteNodeAllocateThrow&&copyCount==3)||(cs->fault==NPCNodeAllocateThrow&&phase==AppendPhase))throw Stop();}
 void* p=std::malloc(bytes?bytes:1);if(!p)throw std::bad_alloc();if(node){need(nodeCount<128);Block& b=nodes[nodeCount++];b.p=p;b.bytes=bytes;b.live=true;b.kind=phase;}return p;
}
void scalarDelete(void* p){if(!p)return;for(unsigned i=nodeCount;i;--i)if(nodes[i-1].p==p&&nodes[i-1].live){nodes[i-1].live=false;n(0x221);n(i-1);break;}std::free(p);}
void wideCtor(std::wstring* dst,const wchar_t* src,const std::allocator<wchar_t>& alloc){if(phase==InitialPhase&&!questCount){++wideCtorCount;need(wideCtorCount<=2);n(0x230);n(wideCtorCount);
 if((cs->fault==PatternThrow&&wideCtorCount==1)||(cs->fault==DirectoryThrow&&wideCtorCount==2))throw Stop();}
 ctorPatch->restore();reinterpret_cast<void(*)(std::wstring*,const wchar_t*,const std::allocator<wchar_t>&)>(qdlWideCtor)(dst,src,alloc);ctorPatch->redirect(qdlWideCtor,qdlWideCtor,&wideCtor);need(!ctorPatch->failed());
}
void wideCopy(std::wstring* dst,const std::wstring& src){if(phase==MapPhase){++copyCount;n(0x231);n(copyCount);cap->addText(src);
 if((cs->fault==NamePairThrow&&copyCount==1)||(cs->fault==NameNodeCopyThrow&&copyCount==2)||(cs->fault==CompletePairThrow&&copyCount==3)||(cs->fault==CompleteNodeCopyThrow&&copyCount==4))throw Stop();}
 copyPatch->restore();reinterpret_cast<void(*)(std::wstring*,const std::wstring&)>(qdlWideCopy)(dst,src);copyPatch->redirect(qdlWideCopy,qdlWideCopy,&wideCopy);need(!copyPatch->failed());
}
void narrowCtor(std::string* dst,const char* src,const std::allocator<char>& alloc){
 bool diagnostic=src&&(!std::strncmp(src,"Unable to load quest from file: ",32)||!std::strncmp(src,"There appears to be two quests named the samething. ",52));
 if(diagnostic){need(current<24);messageOuter[current]=reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(src)-24);outerDestroyed[current]=false;argumentDestroyed[current]=false;}
 narrowCtorPatch->restore();reinterpret_cast<void(*)(std::string*,const char*,const std::allocator<char>&)>(qdlNarrowCtor)(dst,src,alloc);narrowCtorPatch->redirect(qdlNarrowCtor,qdlNarrowCtor,&narrowCtor);need(!narrowCtorPatch->failed());
 if(diagnostic)messageArgument[current]=reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dst->c_str())-24);
}
void narrowDestroy(void* rep,const std::allocator<char>& alloc){for(unsigned i=0;i<24;++i){if(rep==messageOuter[i]&&!outerDestroyed[i]){outerDestroyed[i]=true;n(0x241);n(i);}if(rep==messageArgument[i]&&!argumentDestroyed[i]){argumentDestroyed[i]=true;n(0x242);n(i);}}
 narrowDestroyPatch->restore();reinterpret_cast<void(*)(void*,const std::allocator<char>&)>(qdlNarrowDestroy)(rep,alloc);narrowDestroyPatch->redirect(qdlNarrowDestroy,qdlNarrowDestroy,&narrowDestroy);need(!narrowDestroyPatch->failed());
}
void addNPC(unsigned who,unsigned npc){need(npcCount[who]<8);npcKeys[who][npcCount[who]++]=npc;}
void appendExpected(unsigned npc,unsigned who){need(expectedBucketCount[npc]<32);expectedBuckets[npc][expectedBucketCount[npc]++]=who;expectedBucketCap[npc]=((expectedBucketCount[npc]+1)/2)*2;}
// These literal fixtures are independent of manager code and map helpers.
void setup(){
 errors=firstError=phase=current=questCount=bucketCount=arrayCount=nodeCount=copyCount=wideCtorCount=majorCount=majorIndex=logs=deleted=rawCount=0;tracking=false;temp=fileList=initialBucket=0;
 std::memset(messageOuter,0,sizeof(messageOuter));std::memset(messageArgument,0,sizeof(messageArgument));std::memset(outerDestroyed,0,sizeof(outerDestroyed));std::memset(argumentDestroyed,0,sizeof(argumentDestroyed));
 std::memset(questNames,0,sizeof(questNames));std::memset(quests,0,sizeof(quests));std::memset(npcCount,0,sizeof(npcCount));std::memset(expectedLive,0,sizeof(expectedLive));std::memset(expectedNamed,0,sizeof(expectedNamed));std::memset(expectedCompleted,0,sizeof(expectedCompleted));std::memset(expectedDeleted,0,sizeof(expectedDeleted));std::memset(expectedBucketCount,0,sizeof(expectedBucketCount));std::memset(expectedBucketCap,0,sizeof(expectedBucketCap));
 autotest::g_arenaUsed=0;owner=static_cast<char*>(arena(0xf0))+16;resource=arena(16);fileSystem=arena(16);logger=arena(16);at<void*>(owner,0x38)=resource;
 names=new(static_cast<char*>(owner)+0x40)Names;completions=new(static_cast<char*>(owner)+0x70)Completions;npcs=new(static_cast<char*>(owner)+0xa0)NPCs;
 for(unsigned i=0;i<4;++i)npcObjects[i]=arena(16);for(unsigned i=24;i<32;++i)quests[i]=arena(16);
 for(unsigned i=0;i<24;++i){wchar_t f[64],k[64];std::swprintf(f,64,L"media/quests/file%02u.dat",i);std::swprintf(k,64,L"Q%02u",i);files[i]=f;keys[i]=k;returns[i]=1;loadIndices[i]=i;}
 fileCount=1;
 switch(cs->scenario){
 case Empty:fileCount=0;break;
 case Simple:addNPC(0,2);break;
 case Mixed:fileCount=6;returns[0]=0;keys[1]=L"DuplicateFalse";keys[2]=L"DuplicateTrue";keys[3]=L"NameOnly";keys[4]=L"Q04";keys[5]=L"Q04";
  (*completions)[keys[1]]=false;(*completions)[keys[2]]=true;(*names)[keys[3]]=quests[30];addNPC(3,3);addNPC(3,1);addNPC(4,1);addNPC(4,1);addNPC(4,3);break;
 case Keys:fileCount=8;keys[0]=L"";keys[1]=L"Quest";keys[2]=L"quest";keys[3]=L"\u041a\u0432\u0435\u0441\u0442";keys[4]=L"\u4efb\u52a1";keys[5]=std::wstring(180,L'x');keys[6]=std::wstring(L"A\0B",3);keys[7]=L"A";for(unsigned i=0;i<8;++i)addNPC(i,i%3);break;
 case Truthiness:fileCount=5;returns[0]=0x1122334455667700ULL;returns[1]=0x100;returns[2]=0xffffffffffffff01ULL;returns[3]=0x1122334455667780ULL;returns[4]=0xff;break;
 case Repeated:fileCount=3;for(unsigned i=0;i<3;++i){addNPC(i,2);addNPC(i,1);addNPC(i,2);addNPC(i,2);}break;
 case FileFallback:fileCount=3;for(unsigned i=0;i<3;++i){loadIndices[i]=0;returns[i]=i?0:1;}break;
 case FileReread:fileCount=3;break;
 case NPCFallback:addNPC(0,2);addNPC(0,1);addNPC(0,0);break;
 case NPCReread:addNPC(0,2);addNPC(0,0);addNPC(0,3);break;
 case GrowthReread:{addNPC(0,2);initialBucket=static_cast<List*>(arena(24));initialBucket->data=static_cast<void**>(std::malloc(16));initialBucket->data[0]=quests[30];initialBucket->data[1]=quests[31];initialBucket->count=initialBucket->capacity=2;initialBucket->grow=2;(*npcs)[npcObjects[2]]=initialBucket;break;}
 case FaultInput:for(unsigned i=0;i<3;++i)addNPC(0,2);if(cs->fault==FailedLogThrow||cs->fault==FailedConvertThrow)returns[0]=0;if(cs->fault==DuplicateLogThrow||cs->fault==DuplicateConvertThrow)(*completions)[keys[0]]=cs->mode!=0;break;
 }
 if(cs->mode)for(unsigned i=0;i<24;++i)returns[i]|=0x7123456789abcd00ULL;
 loadLimit=cs->scenario==FileReread?1:fileCount;expectedCaught=cs->fault!=None;
 if(cs->fault!=PatternThrow&&cs->fault!=DirectoryThrow)expect(FilesEvent,0);
 if(cs->fault!=PatternThrow&&cs->fault!=DirectoryThrow&&cs->fault!=FilesThrow)for(unsigned i=0;i<loadLimit;++i){
  expect(QuestAllocationEvent,i);if(cs->fault==QuestAllocateThrow)break;
  expect(ConstructorEvent,i);if(cs->fault==QuestConstructThrow)break;
  expectedLive[i]=1;expect(LoadEvent,i);if(cs->fault==QuestLoadThrow)break;
  bool failed=(returns[i]&255)==0;
  bool duplicate=(cs->scenario==Mixed&&(i==1||i==2||i==5))||(cs->fault==DuplicateLogThrow||cs->fault==DuplicateConvertThrow);
  if(failed){expect(DeleteEvent,i);expectedDeleted[i]=1;expectedLive[i]=0;if(cs->fault==FailedConvertThrow)break;expect(LogEvent,i);if(cs->fault==FailedLogThrow)break;continue;}
  if(duplicate){if(cs->fault==DuplicateConvertThrow)break;expect(LogEvent,i);if(cs->fault==DuplicateLogThrow)break;expect(DeleteEvent,i);expectedDeleted[i]=1;expectedLive[i]=0;continue;}
  if(cs->fault==NamePairThrow||cs->fault==NameNodeAllocateThrow||cs->fault==NameNodeCopyThrow)break;expectedNamed[i]=1;
  if(cs->fault==CompletePairThrow||cs->fault==CompleteNodeAllocateThrow||cs->fault==CompleteNodeCopyThrow)break;expectedCompleted[i]=1;
  expect(NPCEvent,i);if(cs->fault==NPCThrow||cs->fault==BucketAllocateThrow||cs->fault==NPCNodeAllocateThrow)break;
  if(cs->fault==FirstArrayThrow){expectedBucketCap[2]=2;break;}
  if(cs->fault==GrowArrayThrow){appendExpected(2,0);appendExpected(2,0);break;}
  if(cs->scenario==GrowthReread){expectedBuckets[2][0]=30;expectedBuckets[2][1]=0;expectedBucketCount[2]=2;expectedBucketCap[2]=4;}
  else if(cs->scenario==NPCReread)appendExpected(1,0);
  else for(unsigned j=0;j<npcCount[i];++j)appendExpected(cs->scenario==NPCFallback?2:npcKeys[i][j],i);
 }
 for(unsigned i=0;i<24;++i){keyRefs[i]=refs(keys[i]);fileRefs[i]=refs(files[i]);}
 std::memcpy(ownerBefore,owner,sizeof(ownerBefore));
}
void snapshot(unsigned caught){
 need(caught==expectedCaught);need(majorIndex==majorCount);n(caught);n(majorIndex);
 unsigned wantedNames=0,wantedComplete=cs->scenario==Mixed?2:(cs->fault==DuplicateLogThrow||cs->fault==DuplicateConvertThrow?1:0);
 for(unsigned i=0;i<24;++i){wantedNames+=expectedNamed[i];wantedComplete+=expectedCompleted[i];}
 need(names->size()==wantedNames&&completions->size()==wantedComplete);
 n(names->size());for(Names::iterator it=names->begin();it!=names->end();++it){unsigned expected=99;for(unsigned i=0;i<24;++i)if(expectedNamed[i]&&keys[i]==it->first)expected=i;need(expected!=99&&it->second==quests[expected]);cap->addText(it->first);n(qid(it->second));}
 n(completions->size());for(Completions::iterator it=completions->begin();it!=completions->end();++it){bool found=false,value=false;for(unsigned i=0;i<24;++i)if(expectedCompleted[i]&&keys[i]==it->first)found=true;
  if(cs->scenario==Mixed&&(it->first==keys[1]||it->first==keys[2])){found=true;value=it->first==keys[2];}
  if((cs->fault==DuplicateLogThrow||cs->fault==DuplicateConvertThrow)&&it->first==keys[0]){found=true;value=cs->mode!=0;}
  need(found&&it->second==value);cap->addText(it->first);n(it->second);
 }
 unsigned wantedBuckets=0;for(unsigned i=0;i<4;++i)wantedBuckets+=expectedBucketCap[i]!=0;need(npcs->size()==wantedBuckets);n(npcs->size());
 for(NPCs::iterator it=npcs->begin();it!=npcs->end();++it){unsigned who=npcid(it->first);need(who<4);if(who>=4)continue;List* b=it->second;need(b!=0);if(!b)continue;
  need(b->count==expectedBucketCount[who]&&b->capacity==expectedBucketCap[who]&&b->grow==2);n(who);n(b->count);n(b->capacity);n(b->grow);n(b->data!=0);
  if(cs->fault==FirstArrayThrow){need(!b->data&&!b->count);continue;}
  need(b->data!=0&&b->count<=32);if(b->data&&b->count<=32)for(unsigned j=0;j<b->count;++j){need(b->data[j]==quests[expectedBuckets[who][j]]);n(qid(b->data[j]));}
  if(cs->scenario==GrowthReread){need(b->data[2]==quests[29]&&b->data[3]==quests[29]);n(qid(b->data[2]));n(qid(b->data[3]));}
 }
 // Arena-backed Ogre blocks have explicit logical lifetime. Never inspect a
 // destroyed name; allocator bytes and live ownership are captured separately.
 for(unsigned i=0;i<questCount;++i){need(questNames[i]==(expectedLive[i]!=0));n(questNames[i]);if(questNames[i])cap->addText(at<std::wstring>(quests[i],0x50));}
 unsigned liveQuests=0,liveBuckets=0;for(unsigned i=0;i<rawCount;++i){n(rawBlocks[i].kind);n(rawBlocks[i].live);if(rawBlocks[i].live){if(rawBlocks[i].kind)++liveBuckets;else ++liveQuests;}}
 unsigned wantedLive=0;for(unsigned i=0;i<24;++i)wantedLive+=expectedLive[i];need(liveQuests==wantedLive);
 need(liveBuckets==wantedBuckets-(cs->scenario==GrowthReread?1u:0u)+(cs->fault==NPCNodeAllocateThrow?1u:0u));
 unsigned liveArrays=0;for(unsigned i=0;i<arrayCount;++i){n(arrays[i].kind);n(arrays[i].bytes);n(arrays[i].live);if(arrays[i].live){need(arrays[i].kind==AppendPhase);++liveArrays;}}
 need(liveArrays==wantedBuckets-(cs->fault==FirstArrayThrow?1u:0u));
 unsigned liveNodes=0;for(unsigned i=0;i<nodeCount;++i){n(nodes[i].kind);n(nodes[i].live);liveNodes+=nodes[i].live;}
 unsigned seeded=cs->scenario==Mixed?3:(cs->scenario==GrowthReread?1:(cs->fault==DuplicateLogThrow||cs->fault==DuplicateConvertThrow?1:0));
 need(liveNodes==names->size()+completions->size()+npcs->size()-seeded);
 for(unsigned i=0;i<24;++i){need(refs(files[i])==fileRefs[i]);if(keys[i].empty())continue;int added=0;const wchar_t* rep=keys[i].c_str();
  for(unsigned j=0;j<24;++j)if(keys[j].c_str()==rep)added+=expectedLive[j]+expectedNamed[j]+expectedCompleted[j]-(cs->scenario==Mixed&&j==3?1:0);
  need(refs(keys[i])==keyRefs[i]+added);
 }
 unsigned char after[0xd0];std::memcpy(after,owner,sizeof(after));std::memset(after+0x40,0,144);std::memset(ownerBefore+0x40,0,144);need(!std::memcmp(after,ownerBefore,sizeof(after)));
 for(unsigned i=0;i<16;++i)need(static_cast<unsigned char*>(owner)[-16+(int)i]==0xa7&&static_cast<unsigned char*>(owner)[0xd0+i]==0xa7);
 n(questCount);n(bucketCount);n(copyCount);n(liveQuests);n(liveBuckets);n(liveArrays);n(liveNodes);n(firstError);n(0xd3141011u);n(errors);
}
void cleanup(){
 // Outside capture: fixture ownership only. Do not credit cleanup as loader work.
 names->~Names();completions->~Completions();npcs->~NPCs();
 for(unsigned i=0;i<questCount;++i)if(questNames[i])at<std::wstring>(quests[i],0x50).~basic_string();
 for(unsigned i=0;i<arrayCount;++i)if(arrays[i].live)std::free(arrays[i].p);
}
void side(void* raw,autotest::Capture& out,bool candidate){cs=static_cast<Case*>(raw);cap=&out;candidateSide=candidate;setup();unsigned caught=0;typedef void(*Fn)(void*);Fn fn=candidate?&qdlNew:&qdlOld;
 {
  detour::Set collaborators,allocators,copies,ctors,narrowCtors,narrowDestroys;copyPatch=&copies;ctorPatch=&ctors;narrowCtorPatch=&narrowCtors;narrowDestroyPatch=&narrowDestroys;
  TL_REDIRECT(collaborators,qdlFS,&fs);TL_REDIRECT(collaborators,qdlFiles,&getFiles);TL_REDIRECT(collaborators,qdlCtor,&construct);TL_REDIRECT(collaborators,qdlLoad,&load);TL_REDIRECT(collaborators,qdlNPC,&getNPC);
  if(cs->fault==FailedConvertThrow||cs->fault==DuplicateConvertThrow)TL_REDIRECT(collaborators,qdlConvert,&failConvert);
  allocators.redirect(qdlOgreNew,qdlOgreNew,&ogreNew);allocators.redirect(qdlOgreDelete,qdlOgreDelete,&ogreDelete);allocators.redirect(qdlLogSingleton,qdlLogSingleton,&logSingleton);allocators.redirect(qdlLogMessage,qdlLogMessage,&log);
  allocators.redirect(qdlArrayNew,qdlArrayNew,&arrayNew);allocators.redirect(qdlArrayDelete,qdlArrayDelete,&arrayDelete);allocators.redirect(qdlScalarNew,qdlScalarNew,&scalarNew);allocators.redirect(qdlScalarDelete,qdlScalarDelete,&scalarDelete);
  copies.redirect(qdlWideCopy,qdlWideCopy,&wideCopy);ctors.redirect(qdlWideCtor,qdlWideCtor,&wideCtor);
  narrowCtors.redirect(qdlNarrowCtor,qdlNarrowCtor,&narrowCtor);narrowDestroys.redirect(qdlNarrowDestroy,qdlNarrowDestroy,&narrowDestroy);
  if(collaborators.failed()||allocators.failed()||copies.failed()||ctors.failed()||narrowCtors.failed()||narrowDestroys.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  tracking=true;if(!autotest::beginInvocation(out,fn))return;
  try{fn(owner);out.callCompleted=1;}catch(const Stop&){caught=1;}catch(...){caught=2;}tracking=false;
 }
 snapshot(caught);cleanup();
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void replacement(void* p,autotest::Capture& out){side(p,out,true);}
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0xd3141011u&&!tail[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(replacement,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(c.fault)ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd31410&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 else if(cv.observe(host,a,b))ok=false;
 if(!ok){unsigned x[3]={0,0,1},y[3]={0,0,1};if(a.capture.length>=12)std::memcpy(x,a.capture.data+a.capture.length-12,12);if(b.capture.length>=12)std::memcpy(y,b.capture.data+b.capture.length-12,12);host->log("    definition load scenario=%u fault=%u mode=%u status=%d/%d first-line/errors=%u/%u,%u/%u issue=%u/%u\n",c.scenario,c.fault,c.mode,a.childStatus,b.childStatus,x[0],x[2],y[0],y[2],a.capture.issue,b.capture.issue);}return ok;
}
}
TL_TEST(questmanager_definition_load){using namespace qdl;autotest::Coverage cv("questmanager_definition_load",0xd31410);unsigned count=0;for(unsigned mode=0;mode<2;++mode)for(unsigned s=Empty;s<FaultInput;++s){Case c={s,None,mode};if(!pair(host,cv,c)){cv.report(host);return 1;}++count;}cv.report(host);return cv.completed!=count||cv.missing||cv.different;}
TL_TEST(questmanager_definition_load_exceptions){using namespace qdl;autotest::Coverage cv("definition loader expected unwinds excluded",0xd31410);unsigned count=0;for(unsigned f=PatternThrow;f<=DuplicateConvertThrow;++f){Case c={FaultInput,f,0};if(!pair(host,cv,c))return 1;++count;}Case duplicateTrue={FaultInput,DuplicateLogThrow,1};if(!pair(host,cv,duplicateTrue))return 1;++count;host->log("    definition loader: %u original-LSDA-reachable unwinds, no completed coverage credited\n",count);return 0;}

// Direct actual-definition closure of the new name-map weak insert at d34040.
// Adapted from the established completion-map fixture, with real CQuest* type.
class CQuest;
typedef std::map<std::wstring,CQuest*> QMap;
typedef QMap::value_type QValue;
typedef std::_Rb_tree_node_base QBase;
typedef std::_Rb_tree_node<QValue> QNode;
typedef QMap::iterator QIterator;
#define QDL_NAME_INSERT_SYMBOL "_ZNSt8_Rb_treeISbIwSt11char_traitsIwESaIwEESt4pairIKS3_P6CQuestESt10_Select1stIS8_ESt4lessIS3_ESaIS8_EE10_M_insert_EPKSt18_Rb_tree_node_baseSH_RKS8_"
TL_ORIGINAL(QIterator, qdlNameOldInsert, (void*,const QBase*,const QBase*,const QValue&), QDL_NAME_INSERT_SYMBOL)
extern "C" QIterator qdlNameNewInsert(void*,const QBase*,const QBase*,const QValue&) __asm__(QDL_NAME_INSERT_SYMBOL);
extern "C" char qdlNameNodeNew[] __asm__("_Znwm");
extern "C" char qdlNameNodeDelete[] __asm__("_ZdlPv");
extern "C" char qdlNameWideCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
namespace qdl_nameclosure {
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
CQuest* token(bool v){return v?reinterpret_cast<CQuest*>(autotest::g_arena+0x10000):0;}
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
 new(&node->_M_value_field)QValue(key,token(v));
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
 const QValue& v=value(p);check(v.first==expectedKeys[orderedIndex]);check(v.second==token(expectedValues[orderedIndex]));cap->addText(v.first);n(v.second!=0);++orderedIndex;ordered(p->_M_right,depth+1);
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
 std::wstring key=keyFor(c.key);QValue input(key,token(c.value!=0));QBase* h=header(m);QBase* parent=h;QBase* p=h->_M_parent;bool left=true;
 while(p){parent=p;left=key<value(p).first;p=left?p->_M_left:p->_M_right;}
 // x non-null requests a left insertion. Only select it when that is a valid
 // empty child slot; no malformed tree or duplicate-key input is credited.
 const QBase* x=c.forced&&(parent==h||left)?h:0;
 unsigned char priorMap[48];std::memcpy(priorMap,m,48);
 typedef QIterator(*Fn)(void*,const QBase*,const QBase*,const QValue&);Fn fn=candidate?&qdlNameNewInsert:&qdlNameOldInsert;
 QIterator result;unsigned caught=0;
 {
  detour::Set redirects;redirects.redirect(qdlNameNodeNew,qdlNameNodeNew,&allocateNode);redirects.redirect(qdlNameNodeDelete,qdlNameNodeDelete,&deleteNode);if(c.fault==2)redirects.redirect(qdlNameWideCopy,qdlNameWideCopy,&failCopy);
  if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(!autotest::beginInvocation(out,fn))return;
  try{result=fn(m,x,parent,input);out.callCompleted=1;}catch(const std::bad_alloc&){caught=1;}catch(const CopyFailure&){caught=2;}catch(...){caught=3;}
 }
 check(caught==c.fault);check(allocations==1);check(deletions==(c.fault==2?1u:0u));check(copies==(c.fault==2?1u:0u));
 if(!caught){check(result._M_node==allocated);check(allocated!=0);known[knownCount++]=static_cast<QBase*>(allocated);expect(key,c.value!=0);}
 else check(std::memcmp(priorMap,m,48)==0);
 check(input.first==key&&input.second==token(c.value!=0));check(count(m)==expectedCount);check(h->_M_color==std::_S_red);
 if(expectedCount){check(h->_M_parent&&identity(h->_M_parent)>=0);if(h->_M_parent&&identity(h->_M_parent)>=0)check(h->_M_parent->_M_color==std::_S_black);inspect(h->_M_parent,h,0);check(visitedCount==expectedCount);
  check(identity(h->_M_left)>=0&&identity(h->_M_right)>=0);if(!errors){orderedIndex=0;ordered(h->_M_parent,0);check(orderedIndex==expectedCount);check(value(h->_M_left).first==expectedKeys[0]);check(value(h->_M_right).first==expectedKeys[expectedCount-1]);}}
 else check(!h->_M_parent&&h->_M_left==h&&h->_M_right==h);
 for(unsigned i=0;i<16;++i)check(storage[i]==0xa9&&storage[64+i]==0xa9);
 n(caught);n(allocations);n(deletions);n(copies);n(expectedCount);n(visitedCount);n(x!=0);n(left);n(!caught&&result._M_node==allocated);
 // True map lifetime destruction uses the same real allocator storage.
 if(!errors)m->~QMap();n(0x34040c01);n(errors);
}
void before(void* p,autotest::Capture& o){side(p,o,false);}void after(void* p,autotest::Capture& o){side(p,o,true);}
bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=sizeof(tail))std::memcpy(tail,o.capture.data+o.capture.length-sizeof(tail),sizeof(tail));return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x34040c01&&!tail[1];}
bool runPair(const tlhybrid_host* host,autotest::Coverage& cv,Case& c){autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault){if(cv.observe(host,a,b))ok=false;}else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==(uint64_t)(uintptr_t)&qdlNameOldInsert&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok)host->log("    map insert shape=%u key=%u value=%u forced=%u fault=%u status=%d/%d issue=%u/%u\n",c.shape,c.key,c.value,c.forced,c.fault,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);return ok;}
}
TL_TEST(quest_name_map_insert_closure){using namespace qdl_nameclosure;autotest::Coverage cv("quest_name_map_insert_closure",0xd34040);unsigned completed=0;
 for(unsigned shape=0;shape<4;++shape)for(unsigned key=0;key<15;++key)for(unsigned v=0;v<2;++v){Case c={shape,key,v,(key+v)%2,0};if(!runPair(host,cv,c)){cv.report(host);return 1;}++completed;}
 cv.report(host);return cv.completed!=completed||cv.missing||cv.different;}
TL_TEST(quest_name_map_insert_exceptions){using namespace qdl_nameclosure;autotest::Coverage cv("map insert expected exceptions excluded from coverage",0xd34040);unsigned witnesses=0;
 for(unsigned fault=1;fault<=2;++fault)for(unsigned shape=0;shape<4;++shape)for(unsigned v=0;v<2;++v){Case c={shape,14,v,v,fault};if(!runPair(host,cv,c))return 1;++witnesses;}
 host->log("    map insert: %u expected exception witnesses, no completed coverage credited\n",witnesses);return 0;}
