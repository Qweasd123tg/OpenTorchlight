// Original 0xa8ec90: real entry strings and exact collaborator boundaries.
// No entry detours, fake strings, relaxed receipts, or synthetic successful calls.
#include <cstring>
#include <string>
#include <vector>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalModal, (CGameUI*,std::wstring,std::wstring,bool), "_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
extern "C" void candidateModal(CGameUI*,std::wstring,std::wstring,bool) __asm__("_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b");
// GCC 4.4 x86-64 supplies nontrivial value parameters by invisible reference;
// their caller owns destruction. Supplemental calls use known real objects.
TL_ORIGINAL(void, originalModalParameters, (CGameUI*,std::wstring&,std::wstring&,bool), "_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
extern "C" void candidateModalParameters(CGameUI*,std::wstring&,std::wstring&,bool) __asm__("_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b");
TL_FUNCTION(modalUnpause, "_ZN7CGameUI7unPauseEv")
TL_FUNCTION(modalTitle, "_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(modalContents, "_ZN10CModalMenu11setContentsERSbIwSt11char_traitsIwESaIwEEbPFbP9CBaseUnitS6_ES8_")
// Both call sites resolve this external library boundary to the same address.
extern "C" char modalRemove[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");

namespace {
enum { UISize=0x1a08, MaxBlocks=16 };
enum Tag { Unpause=1, Remove, OpenA, OpenB, Title, Contents };
enum Mutation { AfterUnpause=1, AfterRemove=2, AfterOpen=4, AfterTitle=8,
                ChangeCaller=16, ChangeBody=32, SwapTable=64 };
struct Case {
    unsigned text,body,parent,nullModal,mutation,foldout,parameter,source,repeat,sequence,pattern,fault;
    bool flag;
    Case() : text(1),body(2),parent(1),nullModal(0),mutation(0),foldout(0),parameter(0),source(0),
        repeat(1),sequence(0),pattern(0),fault(0),flag(false) {}
};
struct Block { unsigned char* p; unsigned size; unsigned char expected[UISize]; };
struct Injected { unsigned tag; explicit Injected(unsigned t):tag(t){} };
struct State {
    // These are all surviving string owners; count their real COW references
    // after each invocation to witness destruction on success and exception.
    std::wstring caller[2],entry[2],alias[2],parameter[2],wantedCaller[2],wantedParameter[2];
    unsigned step,errors,catches,unwinds,hits,total,sourceChanged;
    unsigned plan[5],count;
    bool returned;
    State():step(0),errors(0),catches(0),unwinds(0),hits(0),total(0),sourceChanged(0),count(0),returned(false){}
};
const Case* current; State* state; autotest::Capture* capture;
Block blocks[MaxBlocks];unsigned blockCount;
CGameUI* ui;void* menus[4];void* folds[2];void* windows[3];void* parents[2];void** tables[2];

template<class T> T& at(void* p,unsigned offset) { return *reinterpret_cast<T*>(static_cast<char*>(p)+offset); }
void number(unsigned v) { capture->add(&v,sizeof(v)); }
void pointer(const void* p) { capture->addPointer(p); }
void require(bool ok,unsigned why) { if(!ok)_exit(50+why); }
void expect(bool ok,unsigned why) { number(why);number(ok);if(!ok)++state->errors; }
Block& block(void* p) {
    for(unsigned i=0;i<blockCount;++i)if(blocks[i].p==p)return blocks[i];
    require(false,1);return blocks[0];
}
template<class T> T expected(void* p,unsigned offset) {
    T value;std::memcpy(&value,block(p).expected+offset,sizeof(value));return value;
}
template<class T> void change(void* p,unsigned offset,T value) {
    at<T>(p,offset)=value;std::memcpy(block(p).expected+offset,&value,sizeof(value));
}
void* guarded(unsigned size,unsigned fill) {
    require(blockCount<MaxBlocks&&size<=UISize,2);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));require(p!=0,3);
    std::memset(p,0xd3,16);std::memset(p+16,fill,size);std::memset(p+16+size,0x6c,16);
    Block& b=blocks[blockCount++];b.p=p+16;b.size=size;std::memcpy(b.expected,b.p,size);return b.p;
}
void checkState() {
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];expect(!std::memcmp(b.p,b.expected,b.size),4);
        bool guards=true;for(unsigned j=0;j<16;++j)guards=guards&&b.p[int(j)-16]==0xd3&&b.p[b.size+j]==0x6c;
        expect(guards,5);
    }
    for(unsigned i=0;i<2;++i) {
        expect(state->caller[i]==state->wantedCaller[i],6);
        expect(state->parameter[i]==state->wantedParameter[i],7);
        expect(state->alias[i]==state->entry[i],8);
    }
}
std::wstring text(unsigned i) {
    switch(i%7) {
    case 0:return L"";case 1:return L"Title: a new quest";
    case 2:return std::wstring(L"A\0B\0C",5);
    case 3:return L"\u0416\u03a9\u4e2d\u2603";
    case 4:return std::wstring(767,L'Q')+L"\u4e2d";
    case 5:return L" \t\n[] {colour} /dialog/body.txt ";
    default:return std::wstring(1,L'\0');
    }
}
void* wantedMenu() { return expected<void*>(ui,0x548); }
void boundary(unsigned tag) {
    ++state->step;++state->total;number(tag);number(state->step);
    require(state->step<16,9);
    expect(state->step<=state->count&&tag==state->plan[state->step-1],10);
    checkState();
}
void finish(unsigned tag) {
    checkState();if(current->fault==tag){++state->hits;throw Injected(tag);}
}
void swapModal(unsigned bit,unsigned index) {
    if(current->mutation&bit)change(ui,0x548,menus[index]);
}
void changeSource() {
    if(!(current->mutation&ChangeCaller)||state->sourceChanged)return;
    state->caller[0]=std::wstring(L"changed\0title",13);
    state->caller[1]=std::wstring(L"changed\0body",12);
    state->wantedCaller[0]=state->caller[0];state->wantedCaller[1]=state->caller[1];state->sourceChanged=1;
}
void unpause(CGameUI* self) {
    boundary(Unpause);pointer(self);expect(self==ui,11);
    swapModal(AfterUnpause,1);
    if(current->foldout==1||current->foldout==4)change(ui,0x4c0,folds[1]);
    if(current->foldout==2||current->foldout==4)change(expected<void*>(ui,0x4c0),0x348,windows[2]);
    if(current->foldout==3||current->foldout==4)
        change(expected<void*>(expected<void*>(ui,0x4c0),0x348),0xb0,current->parent?parents[1]:(void*)0);
    if(current->mutation&SwapTable)change(wantedMenu(),0,tables[1]);
    changeSource();finish(Unpause);
}
void removeWindow(void* parent,void* child) {
    boundary(Remove);pointer(parent);pointer(child);
    void* want=expected<void*>(expected<void*>(ui,0x4c0),0x348);
    expect(child==want,12);expect(parent==expected<void*>(want,0xb0),13);
    swapModal(AfterRemove,2);
    if(current->mutation&SwapTable)change(wantedMenu(),0,tables[1]);
    finish(Remove);
}
void open(void* menu,bool value,unsigned tag) {
    boundary(tag);pointer(menu);number(value);expect(menu==wantedMenu(),14);expect(value,15);
    expect(expected<void**>(wantedMenu(),0)==tables[tag==OpenB],16);
    swapModal(AfterOpen,3);
    if(current->mutation&SwapTable)change(wantedMenu(),0,tables[1]);
    finish(tag);
}
void openA(void* p,bool value){open(p,value,OpenA);}
void openB(void* p,bool value){open(p,value,OpenB);}
void forbiddenVirtual(){require(false,17);}
void title(void* menu,const std::wstring& value) {
    boundary(Title);pointer(menu);capture->addText(value);
    expect(menu==wantedMenu(),18);expect(value==state->entry[0],19);
    expect(&value!=&state->caller[0]&&&value!=&state->caller[1],20);
    if(current->parameter)expect(&value==&state->parameter[0],21);
    swapModal(AfterTitle,0);finish(Title);
}
typedef bool (*Callback)(CBaseUnit*,CBaseUnit*);
void contents(void* menu,std::wstring& value,bool flag,Callback accept,Callback decline) {
    boundary(Contents);pointer(menu);capture->addText(value);number(flag);
    number(accept==0);number(decline==0);
    expect(menu==wantedMenu(),22);expect(flag==current->flag,23);expect(!accept&&!decline,24);
    expect(value==state->entry[1],25);
    expect(&value!=&state->caller[0]&&&value!=&state->caller[1],26);
    if(current->parameter)expect(&value==&state->parameter[1],27);
    if(current->mutation&ChangeBody) {
        value=std::wstring(L"private\0body",12);
        if(current->parameter)state->wantedParameter[1]=std::wstring(L"private\0body",12);
    }
    finish(Contents);
}
void setup() {
    autotest::g_arenaUsed=0;blockCount=0;require(sizeof(std::wstring)==8,28);
    ui=static_cast<CGameUI*>(guarded(UISize,current->pattern?0xa5:0x5a));
    for(unsigned i=0;i<2;++i) {
        tables[i]=static_cast<void**>(guarded(0x60,0));
        for(unsigned j=0;j<12;++j)change(tables[i],j*8,reinterpret_cast<void*>(&forbiddenVirtual));
        change(tables[i],0x38,i?reinterpret_cast<void*>(&openB):reinterpret_cast<void*>(&openA));
    }
    for(unsigned i=0;i<4;++i) {menus[i]=guarded(0x100,0x61+i);change(menus[i],0,tables[0]);}
    for(unsigned i=0;i<2;++i)parents[i]=guarded(0x180,0x31+i);
    for(unsigned i=0;i<3;++i) {windows[i]=guarded(0x180,0x41+i);change(windows[i],0xb0,current->parent?parents[i%2]:(void*)0);}
    for(unsigned i=0;i<2;++i) {folds[i]=guarded(0x380,0x51+i);change(folds[i],0x348,windows[i]);}
    change(ui,0x548,current->nullModal?(void*)0:menus[0]);
    // A null foldout proves the early modal test precedes all foldout access.
    change(ui,0x4c0,current->nullModal?(void*)0:folds[0]);
}
void prepare(unsigned iteration) {
    state->step=state->sourceChanged=0;state->returned=false;
    unsigned t=current->sequence?(iteration==1?0:(iteration==2?3:current->text)):current->text;
    state->caller[0]=text(t);state->caller[1]=current->source==1?state->caller[0]:text(current->body);
    // Non-const access marks a unique COW representation unshareable.
    if(current->source==2)for(unsigned i=0;i<2;++i)if(!state->caller[i].empty())state->caller[i][0]=state->caller[i][0];
    for(unsigned i=0;i<2;++i) {
        state->entry[i]=state->caller[i];state->alias[i]=state->caller[i];
        state->parameter[i]=state->caller[i];state->wantedParameter[i]=state->parameter[i];
        state->wantedCaller[i]=state->caller[i];
    }
    state->count=0;
    if(!current->nullModal) {
        state->plan[state->count++]=Unpause;
        if(current->parent)state->plan[state->count++]=Remove;
        // Predict vtable independently, including reloads and retained state.
        void* next=wantedMenu();
        if(current->mutation&AfterUnpause)next=menus[1];
        if(current->parent&&(current->mutation&AfterRemove))next=menus[2];
        bool tableB=(current->mutation&SwapTable)||expected<void**>(next,0)==tables[1];
        state->plan[state->count++]=tableB?OpenB:OpenA;
        state->plan[state->count++]=Title;state->plan[state->count++]=Contents;
    }
    checkState();
}
void references() {
    const std::wstring* strings[12];unsigned n=0;
    for(unsigned i=0;i<2;++i) {
        strings[n++]=&state->caller[i];strings[n++]=&state->entry[i];strings[n++]=&state->alias[i];
        strings[n++]=&state->parameter[i];strings[n++]=&state->wantedCaller[i];strings[n++]=&state->wantedParameter[i];
    }
    for(unsigned i=0;i<n;++i) {
        const std::wstring& s=*strings[i];capture->addText(s);if(s.empty())continue;
        unsigned owners=0;for(unsigned j=0;j<n;++j)if(strings[j]->data()==s.data())++owners;
        int refs;std::memcpy(&refs,reinterpret_cast<const char*>(s.data())-8,4);
        expect(refs==int(owners)-1||(owners==1&&refs==-1),29);number(owners);capture->add(&refs,sizeof(refs));
    }
}
void snapshot() {
    checkState();
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];pointer(b.p);number(b.size);capture->add(b.p-16,b.size+32);
    }
    references();number(state->step);number(state->total);number(state->sourceChanged);
}
struct InvocationWitness { ~InvocationWitness(){if(!state->returned)++state->unwinds;} };
void invoke(bool ours,autotest::Capture& out,unsigned iteration) {
    if(current->parameter) {
        void(*fn)(CGameUI*,std::wstring&,std::wstring&,bool)=ours?&candidateModalParameters:&originalModalParameters;
        if(!iteration)require(autotest::beginInvocation(out,fn),30);
        fn(ui,state->parameter[0],state->parameter[1],current->flag);
    } else {
        void(*fn)(CGameUI*,std::wstring,std::wstring,bool)=ours?&candidateModal:&originalModal;
        if(!iteration)require(autotest::beginInvocation(out,fn),31);
        fn(ui,state->caller[0],state->caller[1],current->flag);
    }
}
void side(void* raw,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(raw);capture=&out;unsigned witness[5]={0x45585054u,0,0,0,0};
    {
        State local;state=&local;setup();detour::Set redirects;
        TL_REDIRECT(redirects,modalUnpause,&unpause);TL_REDIRECT(redirects,modalTitle,&title);
        TL_REDIRECT(redirects,modalContents,&contents);redirects.redirect(modalRemove,modalRemove,&removeWindow);
        require(!redirects.failed(),32);
        bool threw=false;
        for(unsigned iteration=0;iteration<current->repeat;++iteration) {
            prepare(iteration);number(iteration);
            try {InvocationWitness witness;invoke(ours,out,iteration);state->returned=true;}
            catch(const Injected& failure){expect(failure.tag==current->fault,33);++state->catches;threw=true;}
            catch(...){require(false,34);}
            expect(threw==bool(current->fault),35);
            unsigned count=state->count;
            if(current->fault)for(unsigned j=0;j<state->count;++j)if(state->plan[j]==current->fault){count=j+1;break;}
            expect(state->step==count,36);expect(state->unwinds==unsigned(threw),37);
            expect(state->hits==unsigned(threw)&&state->catches==unsigned(threw),38);
            snapshot();if(threw)break;
        }
        number(threw?0x554e5744u:0x5245544eu);
        witness[1]=state->errors;witness[2]=state->unwinds;witness[3]=state->catches;witness[4]=state->hits;
        if(!threw)out.callCompleted=1;
        redirects.restore();require(!redirects.failed(),39);
    } // All real strings, including explicit parameter objects, are destroyed.
    out.addHeapInUse();out.add(witness,sizeof(witness));
}
void originalSide(void* p,autotest::Capture& out){side(p,out,false);}
void candidateSide(void* p,autotest::Capture& out){side(p,out,true);}
bool witness(const autotest::Outcome& out,bool fault) {
    unsigned w[5];if(out.capture.length<sizeof(w))return false;
    std::memcpy(w,out.capture.data+out.capture.length-sizeof(w),sizeof(w));
    return w[0]==0x45585054u&&!w[1]&&w[2]==unsigned(fault)&&w[3]==unsigned(fault)&&w[4]==unsigned(fault);
}
void diagnostic(const tlhybrid_host* host,unsigned i,const Case& c,const autotest::Outcome& a,const autotest::Outcome& b) {
    size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
    host->log("    modal case %u text/body %u/%u parent %u null %u mutation %u foldout %u parameter %u source %u fault %u: exits %d/%d issues %u/%u complete %u/%u lengths %u/%u first %u\n",
        i,c.text,c.body,c.parent,c.nullModal,c.mutation,c.foldout,c.parameter,c.source,c.fault,a.childStatus,b.childStatus,
        a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned)a.capture.length,(unsigned)b.capture.length,(unsigned)first);
}
}

TL_TEST(gameui_modal_dialog) {
    std::vector<Case> cases,faults;
    for(unsigned t=0;t<7;++t)for(unsigned p=0;p<2;++p)for(unsigned abi=0;abi<2;++abi)for(unsigned flag=0;flag<2;++flag) {
        Case c;c.text=t;c.body=(t+3)%7;c.parent=p;c.parameter=abi;c.flag=flag;c.source=t%3;c.pattern=t&1;cases.push_back(c);
        c.nullModal=1;c.mutation=127;cases.push_back(c);
    }
    // Individual changes diagnose each reload; combinations catch retained
    // aliases and ordering. Both parent branches and real by-value calls remain.
    for(unsigned m=0;m<128;++m)for(unsigned p=0;p<2;++p) {
        Case c;c.mutation=m;c.parent=p;c.parameter=m&1;c.text=m%7;c.body=(m+2)%7;
        c.source=m%3;c.flag=(m&2)!=0;c.foldout=m%5;c.pattern=p;cases.push_back(c);
    }
    for(unsigned fold=0;fold<5;++fold)for(unsigned abi=0;abi<2;++abi) {
        Case c;c.mutation=127;c.foldout=fold;c.parameter=abi;c.repeat=3;c.sequence=1;c.source=1;cases.push_back(c);
    }
    for(unsigned source=0;source<3;++source)for(unsigned abi=0;abi<2;++abi) {
        Case c;c.source=source;c.parameter=abi;c.repeat=3;cases.push_back(c);
    }
    for(unsigned t=0;t<7;++t)for(unsigned abi=0;abi<2;++abi)for(unsigned p=0;p<2;++p)for(unsigned tag=Unpause;tag<=Contents;++tag) {
        if((tag==Remove&&!p)||tag==OpenA)continue;
        Case c;c.text=t;c.body=(t+1)%7;c.parameter=abi;c.parent=p;c.mutation=127;c.foldout=4;
        c.flag=(t&1)!=0;c.source=t%3;c.fault=tag;faults.push_back(c);
    }
    // Also inject the unchanged-vtable callback, independently of OpenB.
    for(unsigned abi=0;abi<2;++abi){Case c;c.parameter=abi;c.fault=OpenA;faults.push_back(c);}
    uint64_t address=(uint64_t)(uintptr_t)&originalModal;
    autotest::Coverage coverage("gameui_modal_dialog",address);
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        int result=coverage.observe(host,a,b);
        if(result||!witness(a,false)||!witness(b,false)){diagnostic(host,i,c,a,b);coverage.report(host);return 1;}
    }
    coverage.report(host);if(coverage.completed!=cases.size()||coverage.completed<100)return 1;
    unsigned completedUnwinds=0;
    for(unsigned i=0;i<faults.size();++i) {
        Case c=faults[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&
            a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==address&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&
            host->comparison_pair(address,b.capture.callTarget)&&a.capture.length==b.capture.length&&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length)&&witness(a,true)&&witness(b,true);
        if(!ok){diagnostic(host,i,c,a,b);return 1;}++completedUnwinds;
    }
    host->log("    gameui_modal_dialog: %u completed expected-unwind witnesses, excluded from normal coverage\n",completedUnwinds);
    return 0;
}

// Required parent-run negative controls, all intended as clean completed
// differences (not crashes): cache the initial modal across callbacks; deliver
// title before setOpen; copy body into a local before setContents. The last is
// rejected by explicit parameter identity even when contents mutation is hidden
// from the ordinary caller. Additional controls: cache foldout/window/parent
// before unPause; cache the virtual table; pass a nonnull callback or invert flag;
// omit any helper; use c_str() to copy strings with embedded NULs. Restore the
// exact positive source/manifest and rerun it before the unmodified full gate.
