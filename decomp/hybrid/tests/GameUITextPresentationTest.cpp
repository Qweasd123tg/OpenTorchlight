// Differential receipts for the three presentation entry points. Only their
// collaborators are replaced; std::wstring, CEGUI::colour, colourToString and
// CEGUI::String construction/destruction all run for real.
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include <CEGUI.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalSmall, (CGameUI*,std::wstring,float), "_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")
TL_ORIGINAL(void, originalBig, (CGameUI*,std::wstring,float), "_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
TL_ORIGINAL(void, originalCinematic, (CGameUI*,std::wstring), "_ZN7CGameUI16setCinematicOpenESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidateSmall(CGameUI*,std::wstring,float) __asm__("_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf");
extern "C" void candidateBig(CGameUI*,std::wstring,float) __asm__("_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf");
extern "C" void candidateCinematic(CGameUI*,std::wstring) __asm__("_ZN7CGameUI16setCinematicOpenESbIwSt11char_traitsIwESaIwEE");
// The GCC 4.4 x86-64 nontrivial by-value argument is an invisible reference,
// destroyed by its caller. Supplemental cases supply a known, real parameter
// object explicitly, so the extra copy into setText can be checked by identity.
TL_ORIGINAL(void, originalCinematicParameter, (CGameUI*,std::wstring&), "_ZN7CGameUI16setCinematicOpenESbIwSt11char_traitsIwESaIwEE")
extern "C" void candidateCinematicParameter(CGameUI*,std::wstring&) __asm__("_ZN7CGameUI16setCinematicOpenESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(cinematicText, "_ZN14CCinematicMenu7setTextESbIwSt11char_traitsIwESaIwEE")
extern "C" char propertyFunction[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char visibleFunction[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char windowTextFunction[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");

namespace {
enum Kind { Small, Big, Cinematic };
enum Tag { Visible=1, WhiteProperty, BlackProperty, MenuText, OpenA, OpenB };
enum Mutation { SwapFirst=1, SwapSecond=2, ChangeSource=4, ChangePayload=8 };
enum BlockType { Raw, UI, WideString, Menu, Table };
enum { UISize=0x1a08, BigText=0x1978, SmallText=0x1988 };
struct Case {
    unsigned kind,text,duration,layout,mutation,sourceMode,repeat,sequence,fault,pattern,parameter;
    Case(unsigned k) : kind(k),text(1),duration(3),layout(0),mutation(0),sourceMode(0),
        repeat(1),sequence(0),fault(0),pattern(0),parameter(0) {}
};
struct Injected { unsigned boundary; explicit Injected(unsigned n) : boundary(n) {} };
struct Block { unsigned char* p; unsigned size,fill,type; };
struct State {
    std::wstring expectedBig,expectedSmall,expectedInput,entryText,alias;
    unsigned char expectedUI[UISize];
    unsigned step,total,properties,visible,texts,opens,sourceChanged,unwindWitness,catches,faultHits,errors;
    bool returned;
    State() : step(0),total(0),properties(0),visible(0),texts(0),opens(0),sourceChanged(0),
        unwindWitness(0),catches(0),faultHits(0),errors(0),returned(false) {}
};
const Case* current;
State* state;
autotest::Capture* capture;
CGameUI* ui;
std::wstring* input;
CEGUI::Window* windows[4];
void* menus[2];
void** tables[2];
Block blocks[12]; unsigned blockCount;
unsigned char expectedMenus[2][0x100];

template<class T> T& at(void* p,unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);
}
void number(unsigned v) { capture->add(&v,sizeof(v)); }
void pointer(const void* p) { capture->addPointer(p); }
void require(bool ok,unsigned reason) { if(!ok) _exit(50+reason); }
void expect(bool ok,unsigned reason) {
    number(reason);number(ok);if(!ok)++state->errors;
}
float duration(unsigned index) {
    static const unsigned values[]={0u,0x80000000u,1u,0x41280000u,0xbf800000u,
        0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0xffc54321u};
    float value;unsigned n=values[index%11];std::memcpy(&value,&n,4);return value;
}
std::wstring text(unsigned index) {
    switch(index%7) {
    case 0:return L"";
    case 1:return L"A new quest begins";
    case 2:return std::wstring(L"A\0B\0C",5);
    case 3:return L"\u0416\u03a9\u4e2d\u2603";
    case 4:return std::wstring(511,L'Q')+L"\u4e2d";
    case 5:return L" \t\n[] {colour} /cinematics/intro.txt ";
    default:return std::wstring(1,L'\0'); // Nonempty, despite first character zero.
    }
}
std::wstring& stored(unsigned kind) { return at<std::wstring>(ui,kind==Big?BigText:SmallText); }
std::wstring& expectedStored(unsigned kind) { return kind==Big?state->expectedBig:state->expectedSmall; }
unsigned windowOffset() { return current->kind==Big?0x110:0x118; }
unsigned durationOffset() { return current->kind==Big?0x1980:0x1990; }
unsigned fadeOffset() { return durationOffset()+4; }
template<class T> void expected(unsigned offset,const T& value) {
    std::memcpy(state->expectedUI+offset,&value,sizeof(value));
}
template<class T> void change(unsigned offset,const T& value) {
    at<T>(ui,offset)=value;expected(offset,value);
}
void* guarded(unsigned size,unsigned type,unsigned fill) {
    require(blockCount<12,1);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));require(p!=0,2);
    std::memset(p,0xd3,16);std::memset(p+16,fill,size);std::memset(p+16+size,0x6c,16);
    Block& b=blocks[blockCount++];b.p=p+16;b.size=size;b.fill=fill;b.type=type;return b.p;
}
void checkUI() {
    const unsigned char* p=reinterpret_cast<const unsigned char*>(ui);
    expect(!std::memcmp(p,state->expectedUI,BigText),3);
    expect(!std::memcmp(p+BigText+sizeof(std::wstring),state->expectedUI+BigText+sizeof(std::wstring),
        SmallText-BigText-sizeof(std::wstring)),4);
    expect(!std::memcmp(p+SmallText+sizeof(std::wstring),state->expectedUI+SmallText+sizeof(std::wstring),
        UISize-SmallText-sizeof(std::wstring)),5);
    expect(stored(Big)==state->expectedBig,6);expect(stored(Small)==state->expectedSmall,7);
    expect(*input==state->expectedInput,8);
}
void recordUI() {
    checkUI();const unsigned char* p=reinterpret_cast<const unsigned char*>(ui);
    capture->add(p,BigText);capture->addText(stored(Big));
    capture->add(p+BigText+sizeof(std::wstring),SmallText-BigText-sizeof(std::wstring));
    capture->addText(stored(Small));capture->add(p+SmallText+sizeof(std::wstring),UISize-SmallText-sizeof(std::wstring));
    capture->addText(*input);
}
void expectAssigned() {
    expectedStored(current->kind)=state->entryText;
    expected(durationOffset(),duration(current->duration));expected(fadeOffset(),1.f);
}
unsigned plannedTag(unsigned step) {
    if(current->kind==Cinematic) {
        if(step==1)return MenuText;
        if(step==2) {
            void* menu=at<void*>(state->expectedUI,0x540);
            require(menu==menus[0]||menu==menus[1],9);
            unsigned i=menu==menus[1];
            return at<void**>(expectedMenus[i],0)==tables[0]?OpenA:OpenB;
        }
    } else if(state->entryText.empty()) {
        if(step==1)return Visible;
    } else {
        if(current->kind==Big) {
            if(step==1)return Visible;if(step==2)return WhiteProperty;if(step==3)return BlackProperty;
        } else { if(step==1)return WhiteProperty;if(step==2)return BlackProperty; }
    }
    return 0; // Unexpected, but safe extra calls still produce completed differences.
}
unsigned plannedCount() {
    if(current->kind==Cinematic)return current->layout==1?0:2;
    return state->entryText.empty()?1:(current->kind==Big?3:2);
}
void boundary(unsigned tag) {
    ++state->step;++state->total;number(tag);number(state->step);
    require(state->step<=16,10);expect(tag==plannedTag(state->step),11);
    if(current->kind!=Cinematic) {
        if(state->entryText.empty())expected(fadeOffset(),0.f);
        else if(tag==WhiteProperty)expectAssigned();
    }
    recordUI();
}
void changeSource() {
    if((current->mutation&ChangeSource) && !state->sourceChanged) {
        *input=std::wstring(L"changed\0caller",14);state->expectedInput=*input;state->sourceChanged=1;
    }
}
void finishBoundary() {
    checkUI();
    if(current->fault==state->step) { ++state->faultHits;throw Injected(state->step); }
}
void forbiddenVirtual() { require(false,12); }
void forbiddenText(CEGUI::Window*,const CEGUI::String&) { require(false,13); }
void setVisible(CEGUI::Window* w,bool visible) {
    boundary(Visible);++state->visible;pointer(w);number(visible);
    expect(w==at<CEGUI::Window*>(state->expectedUI,windowOffset()),14);
    expect(visible==(!state->entryText.empty()),15);
    expect(current->kind==Big||!visible,16);
    if(current->mutation&SwapFirst)change(windowOffset(),windows[2]);
    changeSource();finishBoundary();
}
void ceguiText(const CEGUI::String& value,const char* wanted) {
    size_t n=std::strlen(wanted);expect(value.length()==n,17);number(value.length());
    require(value.length()<4096,18);
    for(size_t i=0;i<value.length();++i){expect(i<n&&value[i]==static_cast<unsigned char>(wanted[i]),18);number(value[i]);}
    // Force each real temporary to own its encoded buffer too. Its actual
    // destructor must release that buffer on normal and exceptional paths.
    expect(!std::strcmp(value.c_str(),wanted),19);capture->addText(std::string(value.c_str()));
}
void setProperty(void* w,const CEGUI::String& key,const CEGUI::String& value) {
    unsigned tag=state->properties%2?BlackProperty:WhiteProperty;
    boundary(tag);++state->properties;pointer(w);
    expect(w==at<void*>(state->expectedUI,windowOffset()),20);
    ceguiText(key,tag==WhiteProperty?"TextColour":"DropTextColour");
    ceguiText(value,tag==WhiteProperty?"FFFFFFFF":"FF000000");
    if(tag==WhiteProperty) {
        if(current->mutation&SwapSecond)change(windowOffset(),windows[3]);
        if(current->mutation&ChangePayload) {
            stored(current->kind)=std::wstring(L"callback\0state",14);
            expectedStored(current->kind)=stored(current->kind);
            change(durationOffset(),-37.25f);change(fadeOffset(),.375f);
        }
    }
    changeSource();finishBoundary();
}
void menuText(void* menu,std::wstring& value) {
    // A non-owning ABI spy: the true by-value parameter is destroyed by the
    // call site, including on exception. Do not destroy or replace the target.
    boundary(MenuText);++state->texts;pointer(menu);capture->addText(value);
    expect(menu==at<void*>(state->expectedUI,0x540),21);
    expect(value==state->entryText,22);expect(&value!=input,23);
    number(&value!=input);
    if(current->mutation&ChangePayload)value=std::wstring(L"callee\0private",14);
    if(current->mutation&SwapFirst)change(0x540,menus[1]);
    if(current->mutation&SwapSecond) {
        void* next=at<void*>(state->expectedUI,0x540);unsigned i=next==menus[1];
        at<void**>(next,0)=tables[1];at<void**>(expectedMenus[i],0)=tables[1];
    }
    changeSource();finishBoundary();
}
void open(void* menu,bool open,unsigned tag) {
    boundary(tag);++state->opens;pointer(menu);number(open);
    expect(menu==at<void*>(state->expectedUI,0x540),24);expect(open,25);
    changeSource();finishBoundary();
}
void openA(void* menu,bool value) { open(menu,value,OpenA); }
void openB(void* menu,bool value) { open(menu,value,OpenB); }

void setup() {
    autotest::g_arenaUsed=0;blockCount=0;require(sizeof(std::wstring)==8,26);
    unsigned fill=current->pattern?0xa5:0x5a;
    ui=static_cast<CGameUI*>(guarded(UISize,UI,fill));
    ::new(&stored(Big))std::wstring(L"retained BIG \u03a9");
    ::new(&stored(Small))std::wstring(L"retained small \u0416");
    input=static_cast<std::wstring*>(guarded(sizeof(std::wstring),WideString,fill));::new(input)std::wstring();
    for(unsigned i=0;i<4;++i)windows[i]=static_cast<CEGUI::Window*>(guarded(0x100,Raw,0x21+i));
    for(unsigned i=0;i<2;++i) {
        tables[i]=static_cast<void**>(guarded(0x60,Table,0));
        for(unsigned j=0;j<12;++j)tables[i][j]=reinterpret_cast<void*>(&forbiddenVirtual);
        tables[i][0x38/8]=i?reinterpret_cast<void*>(&openB):reinterpret_cast<void*>(&openA);
        menus[i]=guarded(0x100,Menu,0x63+i);at<void**>(menus[i],0)=tables[i];
        std::memcpy(expectedMenus[i],menus[i],0x100);
    }
    at<CEGUI::Window*>(ui,0x110)=windows[0];at<CEGUI::Window*>(ui,0x118)=windows[1];
    if(current->kind!=Cinematic) {
        if(current->layout==1)at<CEGUI::Window*>(ui,windowOffset())=0;
        if(current->layout==2)at<CEGUI::Window*>(ui,windowOffset())=windows[2];
        if(current->layout==3)at<CEGUI::Window*>(ui,0x118)=windows[0];
    }
    at<void*>(ui,0x540)=current->kind==Cinematic&&current->layout==1?0:menus[current->layout==2];
    if(current->kind==Cinematic&&current->layout==3) {
        at<void**>(menus[0],0)=tables[1];at<void**>(expectedMenus[0],0)=tables[1];
    }
    at<float>(ui,0x1980)=-123.5f;at<float>(ui,0x1984)=.625f;
    at<float>(ui,0x1990)=87.25f;at<float>(ui,0x1994)=-.875f;
    state->expectedBig=stored(Big);state->expectedSmall=stored(Small);
    std::memcpy(state->expectedUI,ui,UISize);
}
void prepareInvocation(unsigned iteration) {
    state->step=state->sourceChanged=0;state->returned=false;
    unsigned index=current->text;
    if(current->sequence)index=iteration==1?0:(iteration==2?3:current->text);
    *input=text(index);state->entryText=*input;state->expectedInput=*input;
    state->alias=current->sourceMode==1?*input:std::wstring(L"separate alias");
    // Force the COW clone path as well as the ordinary shared-copy path.
    if(current->sourceMode==2 && !input->empty())(*input)[0]=(*input)[0];
    checkUI();
}
void checkReferenceCounts() {
    const std::wstring* strings[]={input,&stored(Big),&stored(Small),&state->expectedBig,
        &state->expectedSmall,&state->expectedInput,&state->entryText,&state->alias};
    for(unsigned i=0;i<8;++i) {
        const std::wstring& value=*strings[i];if(value.empty())continue;
        unsigned owners=0;for(unsigned j=0;j<8;++j)if(strings[j]->data()==value.data())++owners;
        int count;std::memcpy(&count,reinterpret_cast<const char*>(value.data())-8,4);
        expect(count==int(owners)-1||(owners==1&&count==-1),27);
        number(owners);capture->add(&count,sizeof(count));
    }
}
void snapshot() {
    recordUI();number(state->total);number(state->properties);number(state->visible);
    number(state->texts);number(state->opens);number(state->sourceChanged);
    number(state->unwindWitness);number(state->catches);number(state->faultHits);
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];pointer(b.p);number(b.type);
        for(unsigned j=0;j<16;++j)require(b.p[int(j)-16]==0xd3&&b.p[b.size+j]==0x6c,28);
        capture->add(b.p-16,16);capture->add(b.p+b.size,16);
        if(b.type==Raw) {
            for(unsigned j=0;j<b.size;++j)require(b.p[j]==b.fill,29);
            capture->add(b.p,b.size);
        } else if(b.type==Menu) {
            unsigned index=b.p==menus[1];require(!std::memcmp(b.p,expectedMenus[index],b.size),30);
            pointer(at<void**>(b.p,0));capture->add(b.p+8,b.size-8);
        } else if(b.type==Table) {
            unsigned index=b.p==reinterpret_cast<unsigned char*>(tables[1]);
            for(unsigned j=0;j<12;++j) {
                void* want=reinterpret_cast<void*>(&forbiddenVirtual);
                if(j==0x38/8)want=index?reinterpret_cast<void*>(&openB):reinterpret_cast<void*>(&openA);
                require(reinterpret_cast<void**>(b.p)[j]==want,31);
            }
        }
    }
    checkReferenceCounts();
}
struct InvocationWitness {
    ~InvocationWitness() { if(!state->returned)++state->unwindWitness; }
};
void invoke(bool ours,autotest::Capture& out,unsigned iteration) {
    if(current->kind==Small||current->kind==Big) {
        void(*fn)(CGameUI*,std::wstring,float)=current->kind==Small?
            (ours?&candidateSmall:&originalSmall):(ours?&candidateBig:&originalBig);
        if(!iteration)require(autotest::beginInvocation(out,fn),32);
        fn(ui,*input,duration(current->duration));
    } else if(current->parameter) {
        void(*fn)(CGameUI*,std::wstring&)=ours?&candidateCinematicParameter:&originalCinematicParameter;
        if(!iteration)require(autotest::beginInvocation(out,fn),33);fn(ui,*input);
    } else {
        void(*fn)(CGameUI*,std::wstring)=ours?&candidateCinematic:&originalCinematic;
        if(!iteration)require(autotest::beginInvocation(out,fn),34);fn(ui,*input);
    }
}
void side(void* raw,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(raw);capture=&out;
    unsigned witness[5]={0x45585054u,0,0,0,0};
    {
        State local;state=&local;setup();
        detour::Set redirects;
        redirects.redirect(propertyFunction,propertyFunction,&setProperty);
        redirects.redirect(visibleFunction,visibleFunction,&setVisible);
        redirects.redirect(windowTextFunction,windowTextFunction,&forbiddenText);
        TL_REDIRECT(redirects,cinematicText,&menuText);require(!redirects.failed(),35);
        bool threw=false;
        for(unsigned iteration=0;iteration<current->repeat;++iteration) {
            prepareInvocation(iteration);number(0x100+iteration);
            try {
                InvocationWitness witness;invoke(ours,out,iteration);state->returned=true;
            } catch(const Injected& failure) {
                expect(failure.boundary==current->fault,36);++state->catches;threw=true;
            } catch(...) { require(false,37); }
            expect(threw==bool(current->fault),38);
            expect(state->step==(threw?current->fault:plannedCount()),39);
            expect(state->unwindWitness==(threw?1u:0u),40);
            expect(state->catches==(threw?1u:0u)&&state->faultHits==(threw?1u:0u),41);
            snapshot();if(threw)break;
        }
        // This explicit catch/RAII/state witness is separate from normal call
        // coverage. A crash, timeout, or missing catch cannot satisfy it.
        number(threw?0x554e5744u:0x5245544eu);number(state->unwindWitness);
        number(state->catches);number(state->faultHits);
        witness[1]=state->errors;witness[2]=state->unwindWitness;
        witness[3]=state->catches;witness[4]=state->faultHits;
        if(!threw)out.callCompleted=1;
        redirects.restore();require(!redirects.failed(),42);
        stored(Big).~basic_string();stored(Small).~basic_string();input->~basic_string();
    }
    // Includes real string temporaries and encoded CEGUI buffers after cleanup.
    out.addHeapInUse();
    out.add(witness,sizeof(witness));
}
void originalSide(void* p,autotest::Capture& out) { side(p,out,false); }
void candidateSide(void* p,autotest::Capture& out) { side(p,out,true); }
uint64_t address(unsigned kind) {
    if(kind==Small)return (uint64_t)(uintptr_t)&originalSmall;
    if(kind==Big)return (uint64_t)(uintptr_t)&originalBig;
    return (uint64_t)(uintptr_t)&originalCinematic;
}
void diagnostic(const tlhybrid_host* host,const char* name,unsigned i,const Case& c,
        const autotest::Outcome& a,const autotest::Outcome& b) {
    size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
    host->log("    presentation %s case %u text %u duration %u layout %u mutation %u source %u parameter %u fault %u: exits %d/%d issues %u/%u completed %u/%u lengths %u/%u first %u\n",
        name,i,c.text,c.duration,c.layout,c.mutation,c.sourceMode,c.parameter,c.fault,a.childStatus,b.childStatus,
        a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,
        (unsigned)a.capture.length,(unsigned)b.capture.length,(unsigned)first);
}
bool expectedWitness(const autotest::Outcome& outcome,bool fault) {
    unsigned words[5];if(outcome.capture.length<sizeof(words))return false;
    std::memcpy(words,outcome.capture.data+outcome.capture.length-sizeof(words),sizeof(words));
    return words[0]==0x45585054u&&!words[1]&&words[2]==unsigned(fault)&&
        words[3]==unsigned(fault)&&words[4]==unsigned(fault);
}
int run(const tlhybrid_host* host,const char* name,unsigned kind,const std::vector<Case>& cases,const std::vector<Case>& faults) {
    autotest::Coverage coverage(name,address(kind));
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        int result=coverage.observe(host,a,b);
        if(result||!expectedWitness(a,false)||!expectedWitness(b,false)) {
            diagnostic(host,name,i,c,a,b);coverage.report(host);return 1;
        }
    }
    coverage.report(host);if(coverage.completed!=cases.size()||coverage.completed<20)return 1;
    unsigned completedUnwinds=0;
    for(unsigned i=0;i<faults.size();++i) {
        Case c=faults[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&
            a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==address(kind)&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&
            host->comparison_pair(address(kind),b.capture.callTarget)&&a.capture.length==b.capture.length&&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length)&&expectedWitness(a,true)&&expectedWitness(b,true);
        if(!ok){diagnostic(host,name,i,c,a,b);return 1;}++completedUnwinds;
    }
    host->log("    %s: %u completed expected-unwind witnesses; excluded from normal coverage\n",name,completedUnwinds);
    return 0;
}
int textCases(const tlhybrid_host* host,unsigned kind,const char* name) {
    std::vector<Case> cases,faults;
    // Exact float bit-pattern matrix, including both zero signs, subnormal,
    // largest finite values, infinities and two quiet NaN payloads.
    for(unsigned t=0;t<7;++t)for(unsigned d=0;d<11;++d) {
        Case c(kind);c.text=t;c.duration=d;c.pattern=(t+d)&1;c.sourceMode=(t+d)%3;cases.push_back(c);
    }
    for(unsigned layout=0;layout<4;++layout)for(unsigned mutation=0;mutation<16;++mutation) {
        Case c(kind);c.text=mutation%7;c.layout=layout;c.mutation=mutation;c.pattern=layout&1;cases.push_back(c);
    }
    for(unsigned mode=0;mode<3;++mode)for(unsigned t=0;t<7;++t) {
        Case c(kind);c.text=t;c.sourceMode=mode;c.repeat=3;c.sequence=1;c.mutation=15;cases.push_back(c);
    }
    for(unsigned t=0;t<7;++t)for(unsigned step=1;step<=(t? (kind==Big?3u:2u):1u);++step) {
        Case c(kind);c.text=t;c.fault=step;c.mutation=15;c.sourceMode=t%3;faults.push_back(c);
    }
    return run(host,name,kind,cases,faults);
}
}

TL_TEST(gameui_text_presentation_small) { return textCases(host,Small,"gameui_text_presentation_small"); }
TL_TEST(gameui_text_presentation_big) { return textCases(host,Big,"gameui_text_presentation_big"); }
TL_TEST(gameui_text_presentation_cinematic) {
    std::vector<Case> cases,faults;
    for(unsigned t=0;t<7;++t)for(unsigned layout=0;layout<4;++layout)for(unsigned parameter=0;parameter<2;++parameter) {
        Case c(Cinematic);c.text=t;c.layout=layout;c.parameter=parameter;c.sourceMode=t%3;c.pattern=layout&1;cases.push_back(c);
    }
    for(unsigned mutation=0;mutation<16;++mutation)for(unsigned mode=0;mode<3;++mode) {
        Case c(Cinematic);c.text=(mutation+mode)%7;c.mutation=mutation;c.sourceMode=mode;c.parameter=1;cases.push_back(c);
    }
    for(unsigned t=0;t<7;++t) {
        Case c(Cinematic);c.text=t;c.repeat=3;c.sequence=1;c.mutation=15;c.parameter=t&1;cases.push_back(c);
    }
    for(unsigned t=0;t<7;++t)for(unsigned step=1;step<=2;++step)for(unsigned parameter=0;parameter<2;++parameter) {
        Case c(Cinematic);c.text=t;c.fault=step;c.mutation=15;c.parameter=parameter;c.sourceMode=t%3;faults.push_back(c);
    }
    return run(host,"gameui_text_presentation_cinematic",Cinematic,cases,faults);
}

// Negative controls for the parent gate: (1) clear stored text/duration on the
// empty path; (2) show nonempty small text; (3) move big visibility after assign;
// (4) swap/drop either colour property or alpha; (5) cache the window across a
// collaborator; (6) clamp/canonicalize duration; (7) treat initial NUL as empty;
// (8) cache the cinematic menu or dispatch setOpen nonvirtually; (9) pass the
// cinematic text object through without its extra value copy. Each is rejected
// by an independent expectation above, as well as by differential traces.
