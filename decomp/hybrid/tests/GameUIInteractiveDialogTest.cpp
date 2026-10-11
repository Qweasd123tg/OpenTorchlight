// Original forceInteractiveDialog against the actual recovered full-TU symbol.
// RTTI casts execute for real. Only direct collaborators and the player's
// state virtual slot are observed. No game constructors/destructors are run.
#include <cstring>
#include <vector>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"
class CPlayer; class CBaseUnit; class CQuest;
TL_ORIGINAL(void, oldInteractive, (CGameUI*,CPlayer*,CBaseUnit*,CQuest*),
    "_ZN7CGameUI22forceInteractiveDialogEP7CPlayerP9CBaseUnitP6CQuest")
extern "C" void newInteractive(CGameUI*,CPlayer*,CBaseUnit*,CQuest*)
    __asm__("_ZN7CGameUI22forceInteractiveDialogEP7CPlayerP9CBaseUnitP6CQuest");
extern "C" void* interactivePlayerTable[] __asm__("_ZTV7CPlayer");
extern "C" void* interactiveCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* interactiveItemTable[] __asm__("_ZTV5CItem");
extern "C" void* interactiveBaseTable[] __asm__("_ZTV9CBaseUnit");
TL_FUNCTION(closeFn,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(targetFn,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(itemFn,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(dialogFn,"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
TL_FUNCTION(singleFn,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(lookupFn,"_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit")
TL_FUNCTION(soundFn,"_ZN12CQuestDialog15playDialogSoundEv")
TL_FUNCTION(npcFn,"_ZN16CQuestDialogMenu6setNPCEP9CBaseUnitbP6CQuest")
TL_FUNCTION(stopFn,"_ZN10CCharacter11stopPathingEv")

namespace {
enum Tag { Close=1, Target, Item, Dialog, Singleton, Lookup, Sound, NPC, StateA, StateB, Stop };
enum { UISize=0x1a08, ActorSize=0x2000, TableSize=1224, MaxBlocks=16, MaxObject=0x2000 };
enum Mutation { SwapMenu=1, SwapUIPlayer=2, SwapStateTable=4, OpenMenu=8 };
struct Case {
    unsigned kind,nulls,open,quest,mutation,at,repeat,transition,fault,pattern,alias;
    Case() : kind(0),nulls(0),open(0),quest(0),mutation(0),at(Close),
        repeat(1),transition(0),fault(0),pattern(0),alias(0) {}
};
struct Failure { unsigned step; explicit Failure(unsigned n):step(n){} };
struct Block { unsigned char* p; unsigned size; unsigned char expected[MaxObject+32]; };
Block blocks[MaxBlocks]; unsigned blockCount;
const Case* current; autotest::Capture* capture;
void* ui; void* player; void* otherPlayer; void* unit; void* quest;
void* manager; void* lookedUpQuest; void* dialogue; void* menus[2]; void** tables[2];
void* playerArg; void* unitArg; void* questArg;
unsigned step,total,errors,unwinds,catches,faultHits,expectedMenu,expectedTable,iteration;
unsigned planned[16],plannedLength; bool returned;

template<class T> T& at(void* p,unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);
}
void number(unsigned v) { capture->add(&v,sizeof(v)); }
void pointer(const void* p) { capture->add(&p,sizeof(p)); }
void require(bool ok) { if(!ok)_exit(79); }
void expect(bool ok,unsigned reason) { number(reason);number(ok);if(!ok)++errors; }
void* object(unsigned size,unsigned fill) {
    require(blockCount<MaxBlocks&&size<=MaxObject);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));require(p!=0);
    std::memset(p,0xd3,16);std::memset(p+16,fill,size);std::memset(p+16+size,0x6c,16);
    Block& b=blocks[blockCount++];b.p=p+16;b.size=size;
    std::memcpy(b.expected,p,size+32);return b.p;
}
Block& block(void* p) {
    for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p)return blocks[i];
    require(false);return blocks[0];
}
template<class T> void change(void* p,unsigned offset,const T& value) {
    Block& b=block(p);require(offset+sizeof(T)<=b.size);
    std::memcpy(b.p+offset,&value,sizeof(value));
    std::memcpy(b.expected+16+offset,&value,sizeof(value));
}
void checkState() {
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];expect(!std::memcmp(b.p-16,b.expected,b.size+32),100+i);
    }
}
void snapshot() {
    checkState();number(blockCount);
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];number(b.size);capture->add(b.p-16,b.size+32);
    }
    number(total);number(expectedMenu);number(expectedTable);
}
bool soundPath() { return current->quest>=3; }
void plan() {
    plannedLength=0;
    if(current->nulls||at<unsigned char>(block(menus[expectedMenu]).expected+16,0x30))return;
    planned[plannedLength++]=Close;
    if(current->kind<2)planned[plannedLength++]=Target;
    else if(current->kind==2)planned[plannedLength++]=Item;
    else {planned[plannedLength++]=Target;planned[plannedLength++]=Item;}
    if(current->quest) {
        planned[plannedLength++]=Dialog;
        if(soundPath())planned[plannedLength++]=Sound;
    } else {planned[plannedLength++]=Singleton;planned[plannedLength++]=Lookup;}
    planned[plannedLength++]=NPC;
    if(!soundPath()) {
        unsigned table=expectedTable;
        if((current->mutation&SwapStateTable)&&current->at==NPC)table=1-table;
        planned[plannedLength++]=table?StateB:StateA;
        planned[plannedLength++]=Stop;
    }
}
void begin(unsigned tag,void* self,void* wanted) {
    ++step;++total;require(step<=16);number(tag);number(step);pointer(self);
    expect(step<=plannedLength&&tag==planned[step-1],1);expect(self==wanted,2);
    checkState();
}
void finish(unsigned tag) {
    if(current->at==tag) {
        if(current->mutation&SwapMenu) {
            expectedMenu=1-expectedMenu;change(ui,0x538,menus[expectedMenu]);
        }
        if(current->mutation&SwapUIPlayer)change(ui,0x38,otherPlayer);
        if((current->mutation&SwapStateTable)&&tag==NPC) {
            expectedTable=1-expectedTable;change(player,0,tables[expectedTable]+2);
        }
        if(current->mutation&OpenMenu)change(menus[expectedMenu],0x30,static_cast<unsigned char>(255));
    }
    checkState();
    if(current->fault==step) {++faultHits;throw Failure(step);}
}
void closeAll(void* self) { begin(Close,self,ui);finish(Close); }
void setTarget(void* self,void* value) {
    begin(Target,self,playerArg);pointer(value);
    expect(value==(current->kind<2?unitArg:0),3);
    // Side effect belongs to the fake, and is mirrored independently of the
    // received argument. An incorrect argument is still a completed mismatch.
    change(player,0x340,current->kind<2?unitArg:static_cast<void*>(0));finish(Target);
}
void setItem(void* self,void* value) {
    begin(Item,self,playerArg);pointer(value);
    expect(value==(current->kind==2?unitArg:0),4);
    change(player,0x350,current->kind==2?unitArg:static_cast<void*>(0));finish(Item);
}
void* getDialog(void* self,void* target) {
    begin(Dialog,self,questArg);pointer(target);expect(target==unitArg,5);
    finish(Dialog);return current->quest==1?0:dialogue;
}
void* singleton() { begin(Singleton,0,0);finish(Singleton);return manager; }
void* lookup(void* self,void* target) {
    begin(Lookup,self,manager);pointer(target);expect(target==unitArg,6);
    finish(Lookup);return lookedUpQuest; // Intentionally nonnull, never adopted.
}
void sound(void* self) { begin(Sound,self,dialogue);finish(Sound); }
void setNPC(void* self,void* target,bool flag,void* suppliedQuest) {
    begin(NPC,self,menus[expectedMenu]);pointer(target);number(flag);pointer(suppliedQuest);
    expect(target==unitArg,7);expect(flag==soundPath(),8);expect(suppliedQuest==questArg,9);
    change(menus[expectedMenu],0xc0,unitArg);finish(NPC);
}
void state(void* self,int value,unsigned tag) {
    begin(tag,self,playerArg);number(value);expect(value==2,10);
    expect(tag==(expectedTable?StateB:StateA),11);change(player,0x330,2);finish(tag);
}
void stateA(void* self,int value) { state(self,value,StateA); }
void stateB(void* self,int value) { state(self,value,StateB); }
void stop(void* self) {
    begin(Stop,self,playerArg);change(player,0x264,static_cast<unsigned char>(0));finish(Stop);
}
void initialize() {
    autotest::g_arenaUsed=0;blockCount=step=total=errors=unwinds=catches=faultHits=0;
    expectedMenu=expectedTable=0;unsigned fill=current->pattern?0xa5:0x5a;
    ui=object(UISize,fill);player=object(ActorSize,0x31);otherPlayer=object(ActorSize,0x32);
    unit=object(ActorSize,0x43);quest=object(0x218,0x54);lookedUpQuest=object(0x218,0x65);
    manager=object(0xd0,0x76);dialogue=object(0xa8,0x87);
    menus[0]=object(0x208,0x98);menus[1]=object(0x208,0xa9);
    for(unsigned i=0;i<2;++i) {
        tables[i]=static_cast<void**>(object(TableSize,0));
        // Preserve the entire original vtable group, including offset-to-top
        // and original typeinfo at [-2/-1], and replace only state slot +0x348.
        std::memcpy(tables[i],interactivePlayerTable,TableSize);
        std::memcpy(block(tables[i]).expected+16,tables[i],TableSize);
        change(tables[i],16+0x348,i?reinterpret_cast<void*>(&stateB):reinterpret_cast<void*>(&stateA));
        change(menus[i],0x30,static_cast<unsigned char>(current->open));
    }
    change(player,0,tables[0]+2);change(otherPlayer,0,tables[1]+2);
    void** unitTable=current->kind==0?interactiveCharacterTable:
        current->kind==1?interactivePlayerTable:current->kind==2?interactiveItemTable:interactiveBaseTable;
    change(unit,0,unitTable+2);
    // alias mode covers an explicit player also being the supplied unit.
    require(!current->alias||current->kind==1);
    playerArg=current->nulls&1?0:player;
    unitArg=current->nulls&2?0:(current->alias?player:unit);
    questArg=current->quest?quest:0;
    change(ui,0x38,player);change(ui,0x538,menus[0]);
    if(current->nulls)change(ui,0x538,reinterpret_cast<void*>(1));
    const unsigned flags[]={0,0,0,1,2,255};
    change(dialogue,0x74,static_cast<unsigned char>(flags[current->quest]));
}
void redirects(detour::Set& d) {
    TL_REDIRECT(d,closeFn,&closeAll);TL_REDIRECT(d,targetFn,&setTarget);
    TL_REDIRECT(d,itemFn,&setItem);TL_REDIRECT(d,dialogFn,&getDialog);
    TL_REDIRECT(d,singleFn,&singleton);TL_REDIRECT(d,lookupFn,&lookup);
    TL_REDIRECT(d,soundFn,&sound);TL_REDIRECT(d,npcFn,&setNPC);TL_REDIRECT(d,stopFn,&stop);
}
struct UnwindWitness { ~UnwindWitness(){if(!returned)++unwinds;} };
void side(void* raw,autotest::Capture& out,bool candidate) {
    current=static_cast<Case*>(raw);capture=&out;initialize();detour::Set d;redirects(d);require(!d.failed());
    void(*fn)(CGameUI*,CPlayer*,CBaseUnit*,CQuest*)=candidate?&newInteractive:&oldInteractive;
    for(iteration=0;iteration<current->repeat;++iteration) {
        if(current->transition) {
            const unsigned char values[]={0,255,0};
            change(menus[expectedMenu],0x30,values[iteration%3]);
        }
        step=0;returned=false;bool caught=false;plan();number(iteration);number(plannedLength);
        try {
            UnwindWitness witness;
            if(!iteration)require(autotest::beginInvocation(out,fn));
            fn(static_cast<CGameUI*>(ui),static_cast<CPlayer*>(playerArg),
                static_cast<CBaseUnit*>(unitArg),static_cast<CQuest*>(questArg));
            returned=true;
        } catch(const Failure& failure) {
            ++catches;caught=true;expect(failure.step==current->fault,12);
        } catch(...) { require(false); }
        expect(caught==bool(current->fault),13);
        expect(step==(caught?current->fault:plannedLength),14);
        expect(unwinds==unsigned(caught)&&catches==unsigned(caught)&&faultHits==unsigned(caught),15);
        snapshot();if(caught)break;
    }
    if(!catches)out.callCompleted=1;
    number(catches?0x554e5744u:0x5245544eu);number(unwinds);number(catches);number(faultHits);
    d.restore();require(!d.failed());
    // Independent error trailer is checked on each side, never only compared.
    const unsigned trailer[]={0x45585054u,errors,unwinds,catches,faultHits};out.add(trailer,sizeof(trailer));
}
void oldSide(void* p,autotest::Capture& c) { side(p,c,false); }
void newSide(void* p,autotest::Capture& c) { side(p,c,true); }
bool witness(const autotest::Outcome& o,bool fault) {
    unsigned v[5];if(o.capture.length<sizeof(v))return false;
    std::memcpy(v,o.capture.data+o.capture.length-sizeof(v),sizeof(v));
    return v[0]==0x45585054u&&!v[1]&&v[2]==unsigned(fault)&&v[3]==unsigned(fault)&&v[4]==unsigned(fault);
}
void diagnostic(const tlhybrid_host* host,unsigned index,const Case& c,
        const autotest::Outcome& a,const autotest::Outcome& b) {
    size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
    host->log("    interactive #%u kind=%u nulls=%u open=%u quest=%u mutation=%u at=%u repeat=%u transition=%u fault=%u: exit=%d/%d issue=%u/%u complete=%u/%u bytes=%lu/%lu first=%lu\n",
        index,c.kind,c.nulls,c.open,c.quest,c.mutation,c.at,c.repeat,c.transition,c.fault,
        a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,
        (unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);
}
}

TL_TEST(gameui_interactive_dialog) {
    std::vector<Case> cases,faults;
    for(unsigned kind=0;kind<4;++kind)for(unsigned quest=0;quest<6;++quest)for(unsigned pattern=0;pattern<2;++pattern) {
        Case c;c.kind=kind;c.quest=quest;c.pattern=pattern;c.repeat=2;cases.push_back(c);
    }
    const unsigned openValues[]={1,2,255};
    for(unsigned kind=0;kind<4;++kind)for(unsigned o=0;o<3;++o) {
        Case c;c.kind=kind;c.open=openValues[o];cases.push_back(c);
    }
    for(unsigned nulls=1;nulls<4;++nulls)for(unsigned quest=0;quest<6;++quest) {
        Case c;c.nulls=nulls;c.quest=quest;cases.push_back(c);
    }
    for(unsigned quest=0;quest<6;++quest) {
        Case c;c.kind=1;c.alias=1;c.quest=quest;c.repeat=3;cases.push_back(c);
        c.alias=0;c.transition=1;c.mutation=SwapMenu|SwapUIPlayer|SwapStateTable;c.at=NPC;cases.push_back(c);
    }
    // Each possible pointer-reload boundary is isolated, then combined with
    // changing the unrelated UI player and setting the menu's open byte.
    for(unsigned kind=0;kind<4;++kind)for(unsigned q=0;q<3;++q) {
        unsigned quest=q==0?0:q==1?2:5;
        unsigned tags[]={Close,Target,Item,Dialog,Singleton,Lookup,Sound,NPC,StateA,Stop};
        for(unsigned j=0;j<sizeof(tags)/sizeof(tags[0]);++j) {
            unsigned tag=tags[j];
            bool reachable=tag==Close||tag==NPC||
                (tag==Target&&(kind<2||kind==3))||(tag==Item&&kind>=2)||
                (tag==Dialog&&quest)||(tag==Singleton&&!quest)||(tag==Lookup&&!quest)||
                (tag==Sound&&quest>=3)||((tag==StateA||tag==Stop)&&quest<3);
            if(!reachable)continue;
            for(unsigned mode=0;mode<3;++mode) {
                Case c;c.kind=kind;c.quest=quest;c.at=tag;
                c.mutation=mode==0?SwapMenu:mode==1?SwapUIPlayer:SwapMenu|SwapUIPlayer|OpenMenu;
                c.repeat=2;cases.push_back(c);
            }
        }
        Case swap;swap.kind=kind;swap.quest=quest;swap.at=NPC;swap.mutation=SwapStateTable|SwapMenu|SwapUIPlayer;
        swap.repeat=3;cases.push_back(swap);
        // Compute every reachable fault prefix from the same declarative path
        // lengths, without calling either implementation to discover coverage.
        unsigned count=1+(kind==3?2:1)+(quest?1:2)+(quest>=3?1:0)+1+(quest>=3?0:2);
        for(unsigned fault=1;fault<=count;++fault) {
            Case c;c.kind=kind;c.quest=quest;c.fault=fault;c.at=NPC;
            c.mutation=SwapMenu|SwapUIPlayer|SwapStateTable;faults.push_back(c);
            c.at=Close;faults.push_back(c);
        }
    }
    const uint64_t address=(uint64_t)(uintptr_t)&oldInteractive;
    autotest::Coverage coverage("gameui_interactive_dialog",address);
    for(unsigned i=0;i<cases.size();++i) {
        autotest::Outcome a,b;Case c=cases[i];autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);
        int result=coverage.observe(host,a,b);
        if(result||!witness(a,false)||!witness(b,false)) { diagnostic(host,i,c,a,b);coverage.report(host);return 1; }
    }
    coverage.report(host);
    if(coverage.completed!=cases.size()||coverage.completed<100||coverage.different||coverage.missing)return 1;
    unsigned unwindCount=0;
    for(unsigned i=0;i<faults.size();++i) {
        autotest::Outcome a,b;Case c=faults[i];autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&
            a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==address&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&
            host->comparison_pair(address,b.capture.callTarget)&&a.capture.length==b.capture.length&&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length)&&witness(a,true)&&witness(b,true);
        if(!ok) {diagnostic(host,i,c,a,b);return 1;}++unwindCount;
    }
    host->log("    gameui_interactive_dialog: %u completed expected-unwind witnesses, excluded from normal coverage\n",unwindCount);
    return 0;
}

// Parent-controlled negative runs: adopt getQuestForNPC's returned quest;
// run state/stop after the sound path; cache the menu before closeAll; cache
// the player's state vtable before setNPC; reverse the two null target clears;
// test open or dialogue flag as ==1 rather than !=0; omit any collaborator.
// Require normal-completion mismatches with zero incomplete children, restore
// exact positive sources, rerun positive, then the complete unchanged gate.
