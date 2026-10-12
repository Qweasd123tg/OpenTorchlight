// Target-specific comparison of CQuest::save, original d16bb0 (1615 bytes).
// No definition loader, Quest::load, reinitialize, manager save, or world entry.
// Original constructors execute on BOTH sides. The primary and synthetic suites
// use original child bodies; a separate composition-only suite deliberately
// exercises the existing selected child bodies on its candidate side.
// The byte/write oracle below uses original ELF field offsets, not the accepted
// QuestUnitData source's legacy field-relative expressions. A leaf is 26 bytes.
// Capacity/count mutation cases are explicitly synthetic boundary coverage.
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include <fcntl.h>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
#include "TRepository.h"

TL_ORIGINAL(void,qsvOldSave,(void*,FILE*),"_ZN6CQuest4saveEP8_IO_FILE")
extern "C" void qsvNewSave(void*,FILE*) __asm__("_ZN6CQuest4saveEP8_IO_FILE");
TL_ORIGINAL(void,qsvQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qsvQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qsvResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qsvResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void*,qsvMaster,(),"_ZN22CMasterResourceManager12getSingletonEv")
TL_ORIGINAL(void,qsvDialogCtor,(void*,void*),"_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void,qsvDialogDtor,(void*),"_ZN12CQuestDialogD1Ev")
TL_ORIGINAL(void,qsvDialogSave,(void*,FILE*),"_ZN12CQuestDialog4saveEP8_IO_FILE")
extern "C" void qsvSelectedDialogSave(void*,FILE*) __asm__("_ZN12CQuestDialog4saveEP8_IO_FILE");
TL_ORIGINAL(void,qsvUnitCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qsvUnitDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qsvUnitSave,(void*,FILE*),"_ZN14CQuestUnitData4saveEP8_IO_FILE")
extern "C" void qsvSelectedUnitSave(void*,FILE*) __asm__("_ZN14CQuestUnitData4saveEP8_IO_FILE");
TL_ORIGINAL(bool,qsvUnitComplete,(void*,bool),"_ZN14CQuestUnitData10isCompleteEb")
TL_ORIGINAL(void,qsvGroupCtor,(void*,const std::wstring&,void*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qsvGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*,qsvAddWide,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(long long,qsvGuid,(void*,void*,const std::wstring&),"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(const std::wstring&,qsvGetWide,(void*,const std::wstring&,const std::wstring&),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_ORIGINAL(long long,qsvInt64,(const std::wstring&),"_ZN7STRINGS8GetInt64ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qsvDialogBoundary,"_ZN12CQuestDialog4saveEP8_IO_FILE")
TL_FUNCTION(qsvUnitBoundary,"_ZN14CQuestUnitData4saveEP8_IO_FILE")
TL_FUNCTION(qsvGuidBoundary,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
extern "C" char qsvWrite[] __asm__("fwrite");

namespace quest_save_comparison {
typedef std::wstring Wide;
typedef TArrayList<void*> List;
typedef char WideABI[sizeof(Wide)==8?1:-1];
typedef char ListABI[sizeof(List)==24?1:-1];
template<class T> T& at(void* p,unsigned o) {return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
// Omitted trailing aggregate members initialize to zero in all original cases.
struct Case {unsigned shape,guid,sink,offset,control,composition;};
enum {Write=1,Dialog=2,Unit=3,Guid=4};
struct Event {unsigned kind,id,width; unsigned char bytes[8];};
static const unsigned dialogOffsets[]={0x60,0x78,0x90,0xa8};
static const unsigned saveOffsets[]={0x130,0x148,0x160};
static const unsigned ownedOffsets[]={0x160,0x178,0x190};
static const wchar_t* const guidText[]={L"",L"",L"",L"0",L"4294967297",
    L"9223372036854775807",L"-4294967297",L"-9223372036854775808"};
static const unsigned long long guidBits[]={~0ULL,~0ULL,~0ULL,0ULL,
    0x100000001ULL,0x7fffffffffffffffULL,0xfffffffeffffffffULL,0x8000000000000000ULL};
static const Case* current;
static autotest::Capture* capture;
static void *quest,*resource,*dataGroup,*dialogs[12],*units[12],*groups[9];
static List *controlOuter,*controlInner; static void* controlReplacement;
static FILE* stream;
static int readFd;
static unsigned errors,firstError,eventIndex,dialogCalls,unitCalls,guidCalls;
static unsigned mutations,writes,failures,afterFailureChildren,firstFailedWrite;
static unsigned oracleDialogs,oracleUnits,oracleNodes,oracleGroups,oracleWrites;
static size_t expectedAccepted;
static bool switched,useSelectedChildren;
static std::vector<Event> events;
static std::vector<unsigned char> expectedBytes,expectedState;
static detour::Set *dialogPatch,*unitPatch,*guidPatch,*writePatch;
static void n(unsigned v) {capture->add(&v,sizeof(v));}
static void q(unsigned long long v) {capture->add(&v,sizeof(v));}
static void need(bool b,unsigned code) {if(!b){if(!errors)firstError=code;++errors;n(0xf2000000u+code);}}
static void* storage(unsigned size) {
    void* p=autotest::allocate(size); if(!p)_exit(71);
    std::memset(p,0xa5,size); return p;
}
static List& list(void* object,unsigned offset) {return at<List>(object,offset);}
static void reserveList(List& l) {
    need(!at<void*>(&l,0)&&!at<unsigned>(&l,8)&&!at<unsigned>(&l,12),1);
    void** p=static_cast<void**>(autotest::allocate(8*sizeof(void*)));
    if(!p)_exit(71);at<void*>(&l,0)=p;at<unsigned>(&l,12)=8;
}
static void append(List& l,void* p) {
    unsigned& count=at<unsigned>(&l,8);if(count>=8)_exit(71);
    at<void**>(&l,0)[count++]=p;
}
static void detach(List& l) {at<void*>(&l,0)=0;at<unsigned>(&l,8)=at<unsigned>(&l,12)=0;}
// Independent capacity-based selection from the original TArrayList ABI.
static void* select(void* l,unsigned i) {
    return at<void**>(l,0)[i<at<unsigned>(l,12)?i:0];
}
static unsigned identity(void* p,void** objects,unsigned count,unsigned code) {
    for(unsigned i=0;i<count;++i)if(p==objects[i])return i;
    need(false,code);return ~0u;
}
static void installDialog();static void installUnit();static void installGuid();static void installWrite();
static void mutate(unsigned kind) {
    if(mutations)return;
    const unsigned c=current->control;
    if((c==1||c==2)&&kind==Dialog) {
        at<unsigned>(controlOuter,8)=c==1?3:1;++mutations;
    } else if(c>=3&&c<=17&&kind==Unit) {
        if(c<=5)at<unsigned>(controlInner,8)=1;
        else if(c<=8)at<unsigned>(controlInner,8)=3;
        else if(c<=11)at<void**>(controlOuter,0)[0]=controlReplacement;
        else if(c<=14)at<unsigned>(controlOuter,8)=2;
        else at<unsigned>(controlOuter,8)=1;
        ++mutations;
    }
}
static void expectedEvent(unsigned kind,unsigned id,unsigned width=0,unsigned long long value=0) {
    Event e;std::memset(&e,0,sizeof(e));e.kind=kind;e.id=id;e.width=width;
    for(unsigned i=0;i<width;++i)e.bytes[i]=static_cast<unsigned char>(value>>(8*i));
    events.push_back(e);
    if(kind==Write) {++oracleWrites;expectedBytes.insert(expectedBytes.end(),e.bytes,e.bytes+width);}
}
static void word(unsigned long long value,unsigned width) {expectedEvent(Write,0,width,value);}
static bool complete(void* unit,unsigned depth=0) {
    if(depth>12)_exit(71);
    if(!at<unsigned char>(unit,0x60))return false;
    void* children=static_cast<char*>(unit)+0x48;
    for(unsigned i=0;i<at<unsigned>(children,8);++i)
        if(!complete(select(children,i),depth+1))return false;
    return true;
}
static void unitBytes(void* unit,unsigned depth=0) {
    if(depth>12)_exit(71);++oracleNodes;
    word(complete(unit)?1:0,1);word(at<unsigned char>(unit,0xb9),1);
    word(at<unsigned>(unit,0x38),4);word(at<unsigned>(unit,0x3c),4);
    word(at<unsigned>(unit,0x10),4);word(at<unsigned long long>(unit,0x30),8);
    void* children=static_cast<char*>(unit)+0x48;
    word(at<unsigned>(children,8),4);
    for(unsigned i=0;i<at<unsigned>(children,8);++i)unitBytes(select(children,i),depth+1);
}
static void planChild(unsigned kind,void* child) {
    unsigned id=kind==Dialog?identity(child,dialogs,12,2):identity(child,units,12,3);
    expectedEvent(kind,id);
    if(kind==Dialog) {
        ++oracleDialogs;word(at<unsigned char>(child,0x76),1);word(at<unsigned char>(child,0x77),1);
    } else {
        ++oracleUnits;
        if((current->sink==2&&oracleUnits==1)||(current->sink==3&&oracleUnits==3))
            expectedAccepted=expectedBytes.size();
        unitBytes(child);
    }
    mutate(kind);
}
static void makeOracle() {
    events.clear();expectedBytes.clear();oracleDialogs=oracleUnits=oracleNodes=oracleGroups=oracleWrites=0;
    mutations=0;expectedAccepted=0;
    if(current->guid)expectedEvent(Guid,0);
    word(guidBits[current->guid],8);
    word(at<unsigned>(quest,0x1c),4);word(at<unsigned>(quest,0x20),4);word(at<unsigned>(quest,0x20c),4);
    for(unsigned f=0;f<4;++f) {
        void* outer=static_cast<char*>(quest)+dialogOffsets[f];word(at<unsigned>(outer,8),4);
        for(unsigned i=0;i<at<unsigned>(outer,8);++i)planChild(Dialog,select(outer,i));
    }
    for(unsigned f=0;f<3;++f) {
        void* outer=static_cast<char*>(quest)+saveOffsets[f];word(at<unsigned>(outer,8),4);
        for(unsigned i=0;i<at<unsigned>(outer,8);++i) {
            void* group=select(outer,i);++oracleGroups;
            if(!group&&f!=1)_exit(71);
            unsigned snapshot=group?at<unsigned>(group,8):0;word(snapshot,4);
            unsigned j=0;
            // Original +148 alone keeps the written inner count as its bound.
            while(f==1?j<snapshot:j<at<unsigned>(select(outer,i),8)) {
                void* selected=select(outer,i);planChild(Unit,select(selected,j));++j;
            }
        }
    }
    if(current->sink==0)expectedAccepted=expectedBytes.size();
}
static const Event* observe(unsigned kind,unsigned id) {
    const Event* e=eventIndex<events.size()?&events[eventIndex]:0;
    need(e&&e->kind==kind&&e->id==id,4);++eventIndex;n(kind);n(id);return e;
}
static void switchSink() {
    if(switched)return;
    if(!((current->sink==2&&unitCalls==1)||(current->sink==3&&unitCalls==3)))return;
    // This deliberately changes the real fd at a documented callback boundary.
    // fwrite is still libc; /dev/full supplies the actual ENOSPC failure.
    need(std::ftell(stream)==static_cast<long>(current->offset+expectedAccepted),5);
    int fd=open("/dev/full",O_WRONLY);if(fd<0)_exit(71);
    need(dup2(fd,fileno(stream))==fileno(stream),6);need(close(fd)==0,7);switched=true;
}
static void observedDialog(void* self,FILE* file) {
    need(file==stream,8);observe(Dialog,identity(self,dialogs,12,9));++dialogCalls;
    if(failures)++afterFailureChildren;
    dialogPatch->restore();
    if(useSelectedChildren)qsvSelectedDialogSave(self,file);else qsvDialogSave(self,file);
    installDialog();
    mutate(Dialog);
}
static void observedUnit(void* self,FILE* file) {
    need(file==stream,10);observe(Unit,identity(self,units,12,11));++unitCalls;
    if(failures)++afterFailureChildren;switchSink();
    // Restore BOTH entries before forwarding. The chosen body's recursive
    // save/completion dependencies then follow their natural linked bindings.
    // Top-level identities are observed here; every descendant's writes,
    // values and order are separately checked by observedWrite. Only the
    // composition suite selects existing restored children on the candidate.
    unitPatch->restore();
    if(useSelectedChildren)qsvSelectedUnitSave(self,file);else qsvUnitSave(self,file);
    installUnit();
    mutate(Unit);
}
static long long observedGuid(void* self,void* group,const Wide& key) {
    need(self==resource&&group==dataGroup&&key==L"UNIT_GUID",12);
    need(writes==0,13);observe(Guid,0);++guidCalls;
    guidPatch->restore();long long result=qsvGuid(self,group,key);installGuid();
    need(static_cast<unsigned long long>(result)==guidBits[current->guid],14);q(result);return result;
}
static size_t observedWrite(const void* bytes,size_t size,size_t count,FILE* file) {
    need(file==stream,15);const Event* e=observe(Write,0);++writes;
    need(e&&size==e->width&&count==1&&size<=8,16);
    if(e&&size<=8)need(!std::memcmp(bytes,e->bytes,size),17);
    n(size);n(count);if(size<=8)capture->add(bytes,size);
    writePatch->restore();errno=0;
    size_t result=std::fwrite(bytes,size,count,file);int error=errno;
    installWrite();
    n(result);n(result==count?0:error);
    if(result!=count) {if(!failures)firstFailedWrite=writes;++failures;need(error==ENOSPC,18);}
    else need(current->sink==0||(!switched&&current->sink>=2),19);
    return result;
}
static void installDialog() {TL_REDIRECT(*dialogPatch,qsvDialogBoundary,&observedDialog);if(dialogPatch->failed())_exit(71);}
static void installUnit() {TL_REDIRECT(*unitPatch,qsvUnitBoundary,&observedUnit);if(unitPatch->failed())_exit(71);}
static void installGuid() {TL_REDIRECT(*guidPatch,qsvGuidBoundary,&observedGuid);if(guidPatch->failed())_exit(71);}
static void installWrite() {writePatch->redirect(qsvWrite,qsvWrite,&observedWrite);if(writePatch->failed())_exit(71);}
static void allDialogs() {
    for(unsigned f=0;f<4;++f)for(unsigned i=0;i<3;++i)append(list(quest,dialogOffsets[f]),dialogs[f*3+i]);
}
static void own(unsigned family,unsigned group) {append(list(quest,ownedOffsets[family]),groups[group]);}
static void fullGraph() {
    own(0,2);own(0,1);own(0,0);own(1,3);own(1,4);own(1,5);own(2,6);own(2,7);own(2,8);
    append(list(quest,0x130),groups[4]);append(list(quest,0x130),groups[3]);
    append(list(quest,0x130),groups[4]);append(list(quest,0x130),groups[5]);
    append(list(quest,0x148),groups[8]);append(list(quest,0x148),0);
    append(list(quest,0x148),groups[6]);append(list(quest,0x148),groups[7]);append(list(quest,0x148),groups[8]);
}
static void configureControl() {
    unsigned c=current->control;if(!c)return;
    // All controls have safe backing storage. Only logical count, advertised
    // capacity, or a selected group pointer is deliberately inconsistent.
    for(unsigned f=0;f<4;++f)at<unsigned>(&list(quest,dialogOffsets[f]),8)=0;
    for(unsigned f=0;f<5;++f)at<unsigned>(&list(quest,0x130+24*f),8)=0;
    if(c==1||c==2||(c>=20&&c<=23)) {
        unsigned family=c>=20?c-20:0;controlOuter=&list(quest,dialogOffsets[family]);
        for(unsigned i=0;i<3;++i)append(*controlOuter,dialogs[family*3+i]);
        if(c==1)at<unsigned>(controlOuter,8)=1;
        if(c>=20)at<unsigned>(controlOuter,12)=1;
        return;
    }
    unsigned family=c>=27?c-27:c>=24?c-24:(c-3)%3;
    if(family>2)_exit(71);
    unsigned first=family==0?3:family==1?6:0;
    controlInner=static_cast<List*>(groups[first]);controlReplacement=groups[first+1];
    at<unsigned>(controlInner,8)=0;at<unsigned>(controlReplacement,8)=0;
    for(unsigned i=0;i<3;++i) {append(*controlInner,units[i]);append(*static_cast<List*>(controlReplacement),units[3+i]);}
    unsigned owner=family==0?1:family==1?2:0;
    own(owner,first);own(owner,first+1);
    controlOuter=&list(quest,saveOffsets[family]);
    if(family!=2) {append(*controlOuter,groups[first]);append(*controlOuter,groups[first+1]);}
    at<unsigned>(controlOuter,8)=1;
    if(c>=6&&c<=8)at<unsigned>(controlInner,8)=1;
    if(c>=9&&c<=11)at<unsigned>(controlReplacement,8)=1;
    if(c>=15&&c<=17)at<unsigned>(controlOuter,8)=2;
    if(c>=24&&c<=26) {at<unsigned>(controlOuter,8)=3;at<unsigned>(controlOuter,12)=1;}
    if(c>=27&&c<=29)at<unsigned>(controlInner,12)=1;
}
static void setupObjects(TRepository<Wide>& repository) {
    autotest::g_arenaUsed=0;
    // Original C1 paths copy these TU-local cells before normal game static
    // initialization. Initialize just these cells, not any whole game TU.
    const unsigned cells[]={0x14f9fe8,0x14fb488,0x14ff1a8,0x1509e88,0x14dd9c8,0x14dd9d8,0x14dda88};
    for(unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)new(reinterpret_cast<void*>(cells[i])) Wide();
    *reinterpret_cast<unsigned*>(0x1500730)=0;
    if(qsvMaster())_exit(71);
    resource=storage(0x48);qsvResourceCtor(resource,0);
    need(!at<void*>(resource,0x28)&&!at<unsigned>(resource,0x30),20);
    quest=storage(0x218);qsvQuestCtor(quest,resource,0);
    need(at<void*>(quest,0x1d8)==resource&&!at<void*>(quest,0x1d0)&&at<void*>(quest,0x1e0),21);
    at<unsigned>(quest,0x1c)=current->shape==16?0x80000000u:0x81234567u;
    at<unsigned>(quest,0x20)=current->shape==16?0x7fffffffu:0x12345678u;
    at<unsigned>(quest,0x20c)=current->shape==16?0xffffffffu:0x90abcdefu;
    at<bool>(quest,0x24)=(current->shape&1)!=0;at<bool>(quest,0x26)=(current->shape&2)!=0;
    at<Wide>(quest,0x50)=L"Save-only fixture";
    for(unsigned f=0;f<4;++f)reserveList(list(quest,dialogOffsets[f]));
    for(unsigned f=0;f<5;++f)reserveList(list(quest,0x130+24*f));
    for(unsigned i=0;i<12;++i) {
        dialogs[i]=storage(0xa8);qsvDialogCtor(dialogs[i],quest);
        need(at<void*>(dialogs[i],0x10)==quest,22);
        at<bool>(dialogs[i],0x76)=(i&1)!=0;at<bool>(dialogs[i],0x77)=(i&2)!=0;
        units[i]=storage(0xc8);qsvUnitCtor(units[i],quest);
        need(at<void*>(units[i],0x18)==quest,23);reserveList(list(units[i],0x48));
        at<unsigned>(units[i],0x10)=0xa0010000u+i;
        at<unsigned>(units[i],0x38)=0xb1020304u+i*17;
        at<unsigned>(units[i],0x3c)=0xc2030405u-i*29;
        at<unsigned long long>(units[i],0x30)=0xd304050607080900ULL+i*0x100000001ULL;
        at<bool>(units[i],0x60)=i%3!=0;at<bool>(units[i],0xb9)=(i&1)!=0;
    }
    for(unsigned i=0;i<9;++i) {groups[i]=storage(sizeof(List));::new(groups[i]) List(3);reserveList(*static_cast<List*>(groups[i]));}
    append(*static_cast<List*>(groups[0]),units[0]);append(*static_cast<List*>(groups[0]),units[1]);
    append(*static_cast<List*>(groups[2]),units[2]);append(*static_cast<List*>(groups[3]),units[3]);
    append(*static_cast<List*>(groups[4]),units[4]);append(*static_cast<List*>(groups[4]),units[5]);
    append(*static_cast<List*>(groups[6]),units[6]);append(*static_cast<List*>(groups[6]),units[7]);
    append(*static_cast<List*>(groups[8]),units[8]);
    unsigned shape=current->shape;
    if(shape>=1&&shape<=4)for(unsigned i=0;i<3;++i)append(list(quest,dialogOffsets[shape-1]),dialogs[(shape-1)*3+i]);
    if(shape==5||shape==10||shape==16)allDialogs();
    if(shape==6) {own(0,1);own(1,5);own(2,7);append(list(quest,0x130),groups[5]);append(list(quest,0x148),groups[7]);}
    if(shape==7) {at<unsigned>(groups[0],8)=1;own(0,0);}
    if(shape==8) {own(1,3);append(list(quest,0x130),groups[3]);}
    if(shape==9) {at<unsigned>(groups[6],8)=1;own(2,6);append(list(quest,0x148),groups[6]);}
    if(shape==10||shape==16)fullGraph();
    if(shape==11)append(list(quest,0x148),0);
    if(shape==12) {
        own(2,6);own(2,7);append(list(quest,0x148),0);append(list(quest,0x148),groups[7]);
        append(list(quest,0x148),groups[6]);append(list(quest,0x148),0);
    }
    if(shape>=13&&shape<=15)own(0,2);
    if(shape==10||shape==16||(shape>=13&&shape<=15)) {
        append(list(units[2],0x48),units[9]);append(list(units[2],0x48),units[10]);append(list(units[10],0x48),units[11]);
        at<bool>(units[2],0x60)=shape!=13;at<bool>(units[9],0x60)=true;
        at<bool>(units[10],0x60)=shape!=14;at<bool>(units[11],0x60)=true;
    }
    controlOuter=controlInner=0;controlReplacement=0;configureControl();
    dataGroup=0;
    if(current->guid) {
        dataGroup=storage(0x60);qsvGroupCtor(dataGroup,Wide(L"QUEST_SAVE_ONLY"),0,4,4,&repository);
        if(current->guid>=2)qsvAddWide(dataGroup,Wide(L"UNIT_GUID"),Wide(guidText[current->guid]),false);
        // An unrelated key distinguishes missing-key lookup from empty storage.
        qsvAddWide(dataGroup,Wide(L"OTHER_GUID"),Wide(L"123"),false);
        at<void*>(quest,0x1e8)=dataGroup;
    }
}
static void teardown() {
    // Arena-owned fixtures are detached first. Each actual original D1 runs
    // exactly once; aliases never acquire ownership and no group is double-freed.
    for(unsigned f=0;f<4;++f)detach(list(quest,dialogOffsets[f]));
    for(unsigned f=0;f<5;++f)detach(list(quest,0x130+24*f));
    for(unsigned i=0;i<12;++i)detach(list(units[i],0x48));
    for(unsigned i=0;i<9;++i) {detach(*static_cast<List*>(groups[i]));static_cast<List*>(groups[i])->~List();}
    for(unsigned i=0;i<12;++i) {qsvDialogDtor(dialogs[i]);qsvUnitDtor(units[i]);}
    at<void*>(quest,0x1e8)=0;qsvQuestDtor(quest);qsvResourceDtor(resource);
    if(dataGroup)qsvGroupDtor(dataGroup);
}
static bool originalBindings() {
    // Self-tests precede loader install_hooks. Reject an already redirected
    // original entry instead of trusting an __tlorig_ spelling alone.
    const unsigned char save[]={0x41,0x57,0x41,0x56,0x41};
    const unsigned char unit[]={0x41,0x54,0x55,0x48,0x89};
    const unsigned char dialog[]={0x48,0x89,0x5c,0x24,0xe8};
    const unsigned char completion[]={0x55,0x48,0x89,0xfd,0x53};
    const unsigned char guid[]={0x48,0x89,0xf7,0x48,0x83};
    const unsigned char get[]={0x53,0x48,0x89,0xd3,0xe8};
    const unsigned char parser[]={0x48,0x83,0xec,0x18,0x48};
    return reinterpret_cast<uintptr_t>(&qsvOldSave)==0xd16bb0&&
        reinterpret_cast<uintptr_t>(&qsvQuestCtor)==0xd16280&&
        reinterpret_cast<uintptr_t>(&qsvResourceCtor)==0xd78820&&
        reinterpret_cast<uintptr_t>(&qsvDialogCtor)==0xd24940&&
        reinterpret_cast<uintptr_t>(&qsvUnitCtor)==0xd3e610&&
        reinterpret_cast<uintptr_t>(&qsvGroupCtor)==0xc61ad0&&
        reinterpret_cast<uintptr_t>(&qsvUnitSave)==0xd3dda0&&
        reinterpret_cast<uintptr_t>(&qsvDialogSave)==0xd1df00&&
        reinterpret_cast<uintptr_t>(&qsvUnitComplete)==0xd3dd20&&
        reinterpret_cast<uintptr_t>(&qsvGuid)==0xd6f630&&
        reinterpret_cast<uintptr_t>(&qsvGetWide)==0xc5f370&&
        reinterpret_cast<uintptr_t>(&qsvInt64)==0xc8ddc0&&
        !std::memcmp(reinterpret_cast<void*>(&qsvOldSave),save,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvUnitSave),unit,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvDialogSave),dialog,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvUnitComplete),completion,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvGuid),guid,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvGetWide),get,5)&&
        !std::memcmp(reinterpret_cast<void*>(&qsvInt64),parser,5);
}
static void side(void* raw,autotest::Capture& out,bool candidate) {
    current=static_cast<Case*>(raw);capture=&out;
    useSelectedChildren=candidate&&current->composition;
    errors=firstError=eventIndex=dialogCalls=unitCalls=guidCalls=mutations=writes=failures=afterFailureChildren=firstFailedWrite=0;
    switched=false;if(!originalBindings()){out.issue=autotest::Capture::InvalidReport;return;}
    Wide empty;TRepository<Wide> repository(empty);setupObjects(repository);
    std::vector<unsigned char> initial(autotest::g_arena,autotest::g_arena+autotest::g_arenaUsed);
    makeOracle();unsigned expectedMutations=mutations;
    expectedState.assign(autotest::g_arena,autotest::g_arena+autotest::g_arenaUsed);
    std::memcpy(autotest::g_arena,&initial[0],initial.size());mutations=0;
    if(!current->control)need(expectedBytes.size()==48+2*oracleDialogs+4*oracleGroups+26*oracleNodes,24);
    stream=current->sink==1?std::fopen("/dev/full","wb"):std::tmpfile();if(!stream)_exit(71);
    need(std::setvbuf(stream,0,_IONBF,0)==0,25);
    readFd=current->sink==1?-1:dup(fileno(stream));if(current->sink!=1&&readFd<0)_exit(71);
    std::vector<unsigned char> prefix(current->sink==1?0:current->offset,0xcc);
    if(!prefix.empty())need(std::fwrite(&prefix[0],1,prefix.size(),stream)==prefix.size(),26);
    detour::Set dp,up,gp,wp;dialogPatch=&dp;unitPatch=&up;guidPatch=&gp;writePatch=&wp;
    installDialog();installUnit();installGuid();installWrite();
    typedef void(*Save)(void*,FILE*);Save invoked=candidate?&qsvNewSave:&qsvOldSave;
    if(!autotest::beginInvocation(out,invoked))return;
    invoked(quest,stream);out.callCompleted=1;
    wp.restore();gp.restore();up.restore();dp.restore();
    need(originalBindings(),27);
    need(eventIndex==events.size()&&writes==oracleWrites,28);
    need(dialogCalls==oracleDialogs&&unitCalls==oracleUnits&&guidCalls==(current->guid?1u:0u),29);
    need(mutations==expectedMutations,30);
    need(autotest::g_arenaUsed==expectedState.size()&&!std::memcmp(autotest::g_arena,&expectedState[0],expectedState.size()),31);
    errno=0;long position=std::ftell(stream);int tellError=errno;int fileError=std::ferror(stream);
    q(static_cast<unsigned long long>(position));n(position<0?tellError:0);n(fileError!=0);
    if(current->sink==0) {need(!fileError&&!failures,32);need(position==static_cast<long>(current->offset+expectedBytes.size()),33);}
    else {need(fileError&&failures&&afterFailureChildren,34);need(current->sink==1||switched,35);}
    if(readFd>=0) {
        size_t size=prefix.size()+expectedAccepted;
        need(lseek(readFd,0,SEEK_END)==static_cast<off_t>(size),36);
        std::vector<unsigned char> bytes(size);if(size)need(pread(readFd,&bytes[0],size,0)==static_cast<ssize_t>(size),37);
        std::vector<unsigned char> expected(prefix);expected.insert(expected.end(),expectedBytes.begin(),expectedBytes.begin()+expectedAccepted);
        need(bytes==expected,38);n(size);if(size)capture->add(&bytes[0],size);need(close(readFd)==0,39);
    } else {need(expectedAccepted==0,40);n(0);}
    // No pending buffer remains: even after ENOSPC, closing an unbuffered stream
    // should succeed; preserve its result in the differential observation.
    int closed=std::fclose(stream);n(closed);need(closed==0,41);
    n(dialogCalls);n(unitCalls);n(oracleNodes);n(writes);n(failures);n(firstFailedWrite);n(afterFailureChildren);n(mutations);
    teardown();n(0x51535645u);n(errors);n(firstError);
}
static void original(void* c,autotest::Capture& out) {side(c,out,false);}
static void recovered(void* c,autotest::Capture& out) {side(c,out,true);}
static bool good(const autotest::Outcome& o) {
    unsigned footer[3]={0,1,0};if(o.capture.length>=sizeof(footer))std::memcpy(footer,o.capture.data+o.capture.length-sizeof(footer),sizeof(footer));
    return o.reportValid&&o.childStatus==0&&!o.capture.issue&&o.capture.callStarted==1&&o.capture.callCompleted==1&&footer[0]==0x51535645u&&!footer[1];
}
static bool pair(const tlhybrid_host* host,Case& c,autotest::Coverage& coverage) {
    autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(recovered,&c,b,2000,10000);
    int observed=coverage.observe(host,a,b);
    if(observed||!good(a)||!good(b)) {
        unsigned fa[3]={0,1,0},fb[3]={0,1,0};
        if(a.capture.length>=12)std::memcpy(fa,a.capture.data+a.capture.length-12,12);
        if(b.capture.length>=12)std::memcpy(fb,b.capture.data+b.capture.length-12,12);
        host->log("    Quest save shape=%u guid=%u sink=%u offset=%u synthetic=%u composition=%u status=%d/%d good=%u/%u errors=%u/%u first=%u/%u\n",
            c.shape,c.guid,c.sink,c.offset,c.control,c.composition,a.childStatus,b.childStatus,good(a),good(b),fa[1],fb[1],fa[2],fb[2]);
        return false;
    }
    return true;
}
}

TL_TEST(quest_persistence_save_original_children) {
    using namespace quest_save_comparison;
    autotest::Coverage coverage("quest_persistence_save_original_children",0xd16bb0);
    if(!host->comparison_pair||!host->comparison_pair(0xd16bb0,reinterpret_cast<uint64_t>(&qsvNewSave)))return 1;
    unsigned cases=0;
    for(unsigned shape=0;shape<=16;++shape) {
        Case c={shape,0,0,shape%2?7u:0u,0};++cases;if(!pair(host,c,coverage)){coverage.report(host);return 1;}
    }
    // Real original DataGroup -> resource helper -> original number parser.
    for(unsigned guid=1;guid<8;++guid)for(unsigned shape=0;shape<2;++shape) {
        Case c={shape?10u:0u,guid,0,shape?7u:0u,0};++cases;if(!pair(host,c,coverage)){coverage.report(host);return 1;}
    }
    // Actual early and late stdio failures. The late cases retain a readable
    // duplicate of the original temporary file and independently check its
    // accepted prefix after the live stream fd switches to /dev/full.
    for(unsigned sink=1;sink<=3;++sink) {
        Case c={10,4,sink,sink==1?0u:7u,0};++cases;if(!pair(host,c,coverage)){coverage.report(host);return 1;}
    }
    coverage.report(host);
    host->log("    CQuest::save: real original constructors, GUID helpers and recursive children; %u complete cases; no definition loading or world coverage\n",cases);
    return coverage.completed!=cases||coverage.different||coverage.missing;
}

TL_TEST(quest_persistence_save_synthetic_traversal) {
    using namespace quest_save_comparison;
    autotest::Coverage coverage("quest_persistence_save_synthetic_traversal",0xd16bb0);
    unsigned cases=0;
    for(unsigned control=1;control<=29;++control) {
        if(control==18||control==19)continue;
        Case c={0,0,0,3,control};++cases;if(!pair(host,c,coverage)){coverage.report(host);return 1;}
    }
    coverage.report(host);
    host->log("    CQuest::save: %u explicitly synthetic count/capacity/group-reselection cases; original children do not naturally mutate these collections\n",cases);
    return coverage.completed!=cases||coverage.different||coverage.missing;
}

TL_TEST(quest_persistence_save_selected_composition) {
    using namespace quest_save_comparison;
    // Composition-only evidence: compare original save + original children
    // against selected save + existing selected children. This neither restores
    // helpers nor gives them target-level coverage/acceptance receipts.
    autotest::Coverage coverage("quest_persistence_save_selected_composition",0xd16bb0);
    if(!host->comparison_pair||!host->comparison_pair(0xd16bb0,reinterpret_cast<uint64_t>(&qsvNewSave)))return 1;
    if(&qsvSelectedUnitSave==&qsvUnitSave||&qsvSelectedDialogSave==&qsvDialogSave) {
        host->log("    Quest save composition requires the existing selected restored unit/dialog save bindings\n");
        return 1;
    }
    const unsigned shapes[]={7,10,14,15};
    for(unsigned i=0;i<sizeof(shapes)/sizeof(shapes[0]);++i) {
        Case c={shapes[i],4,0,7,0,1};
        if(!pair(host,c,coverage)) {coverage.report(host);return 1;}
    }
    coverage.report(host);
    host->log("    CQuest::save composition-only: 4 original-versus-selected child-dependency pairs; no helper coverage or acceptance credit\n");
    return coverage.completed!=4||coverage.different||coverage.missing;
}
