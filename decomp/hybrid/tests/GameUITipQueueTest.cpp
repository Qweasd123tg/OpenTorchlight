// 0xa8f450: real std::vector growth, exact settings predicate and signed indexing.
// Only GetInt is detoured. No vector, allocator or target implementation is faked.
#include <cstring>
#include <climits>
#include <new>
#include <vector>
#include "GameUI.h"
#include "Settings.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalQueueTip, (CGameUI*, EContextTip), "_ZN7CGameUI8queueTipE11EContextTip")
extern "C" void recoveredQueueTip(CGameUI*, EContextTip) __asm__("_ZN7CGameUI8queueTipE11EContextTip");
TL_FUNCTION(getIntBoundary, "_ZN20CDynamicPropertyFile6GetIntEj")

namespace {
typedef std::vector<EContextTip> Queue;
enum { UI_SIZE=0x1a08, ACTOR_SIZE=0x3000, SETTINGS_SIZE=0x140,
       QUEUE_OFFSET=0x1960, SEEN_OFFSET=0xa17, GUARD=16, LIMIT=128 };
struct Stop {};
struct Case {
    int tip, setting;
    unsigned seen, reserve, count, steps, mutation, key;
    bool nullActor, fault, alternating;
    Case() : tip(1), setting(1), seen(0), reserve(0), count(0), steps(1),
        mutation(0), key(0x713ac902u), nullActor(false), fault(false), alternating(false) {}
};
struct Block {
    unsigned char* raw;
    unsigned char* bytes;
    unsigned size;
};
const Case* input;
autotest::Capture* output;
Block ui, actors[2], settings[2];
unsigned char expectedUI[UI_SIZE], expectedActors[2][ACTOR_SIZE];
Queue* queue;
unsigned calls, expectedCalls, step;
bool valid;
int values[LIMIT];
unsigned modelSize, modelCapacity;
void* expectedSettings;
uintptr_t appendStorage;
unsigned appendSize, appendCapacity;

void require(bool v) { if (!v) _exit(90); }
void check(bool v) { if (!v) valid=false; }
void number(unsigned v) { output->add(&v,sizeof(v)); }
void integer(int v) { output->add(&v,sizeof(v)); }
void put(unsigned char* p, unsigned offset, void* value) {
    std::memcpy(p+offset,&value,sizeof(value));
}
void* get(const unsigned char* p,unsigned offset) {
    void* value=0; std::memcpy(&value,p+offset,sizeof(value)); return value;
}
Block block(unsigned size,unsigned char fill) {
    Block b; b.size=size;
    b.raw=static_cast<unsigned char*>(autotest::allocate(size+2*GUARD));
    require(b.raw!=0); b.bytes=b.raw+GUARD;
    std::memset(b.raw,0xad,GUARD); std::memset(b.bytes,fill,size);
    std::memset(b.bytes+size,0x5e,GUARD); return b;
}
void guards(const Block& b) {
    for(unsigned i=0;i<GUARD;++i) check(b.raw[i]==0xad && b.bytes[b.size+i]==0x5e);
}
// Observe the real vector's pointer for stability only. Never construct fake pointers.
uintptr_t storage() {
    uintptr_t p=0; std::memcpy(&p,queue,sizeof(p)); return p;
}
void appendModel(int value) {
    require(modelSize<LIMIT);
    if(modelSize==modelCapacity) modelCapacity=modelSize?2*modelSize:1;
    values[modelSize++]=value;
}
int tipAt(unsigned index) { return input->tip+(input->alternating?int(index%3):0); }
void setup() {
    require(sizeof(Queue)==24 && sizeof(EContextTip)==4);
    valid=true; calls=expectedCalls=0;
    ui=block(UI_SIZE,0x6c);
    for(unsigned i=0;i<2;++i) {
        actors[i]=block(ACTOR_SIZE,static_cast<unsigned char>(0x31+i*0x34));
        settings[i]=block(SETTINGS_SIZE,static_cast<unsigned char>(0x91+i*0x12));
        for(unsigned j=0;j<input->steps;++j) {
            const int offset=SEEN_OFFSET+tipAt(j);
            require(offset>=0 && offset<ACTOR_SIZE);
            actors[i].bytes[offset]=static_cast<unsigned char>(i?255:input->seen);
        }
        std::memcpy(expectedActors[i],actors[i].bytes,ACTOR_SIZE);
    }
    put(ui.bytes,0x38,input->nullActor?0:actors[0].bytes);
    put(ui.bytes,0x78,settings[0].bytes);
    queue=new(ui.bytes+QUEUE_OFFSET) Queue;
    if(input->reserve) queue->reserve(input->reserve);
    for(unsigned i=0;i<input->count;++i) {
        const int v=i%2?input->tip:13+int(i);
        queue->push_back(static_cast<EContextTip>(v)); values[i]=v;
    }
    modelSize=input->count; modelCapacity=static_cast<unsigned>(queue->capacity());
    std::memcpy(expectedUI,ui.bytes,UI_SIZE);
    std::memset(expectedUI+QUEUE_OFFSET,0,sizeof(Queue));
    KSETTINGS_SHOW_TIPS=input->key;
}
// Compute expected effects independently, before running either implementation.
bool modelStep(int tip) {
    unsigned char* actor=static_cast<unsigned char*>(get(expectedUI,0x38));
    if(!actor) return false;
    unsigned identity=actor==actors[0].bytes?0:1;
    if(expectedActors[identity][SEEN_OFFSET+tip]) return false;
    ++expectedCalls;
    expectedSettings=get(expectedUI,0x78);
    if(input->mutation==1 || input->mutation==5) modelSize=0;
    if(input->mutation==2 || input->mutation==5) modelCapacity+=7;
    if(input->mutation==3 || input->mutation==5) appendModel(100+int(step));
    if(input->mutation==4 || input->mutation==5) {
        put(expectedUI,0x38,actors[1].bytes);
        put(expectedUI,0x78,settings[1].bytes);
        expectedActors[0][SEEN_OFFSET+tip]=2;
    }
    if(input->mutation==6) put(expectedUI,0x78,settings[1].bytes);
    if(!input->fault && input->setting==1) appendModel(tip);
    return true;
}
int getInt(void* self,unsigned key) {
    number(0x47455449u); number(step); output->addPointer(self); number(key);
    ++calls;
    check(self==expectedSettings); check(key==input->key+step*17u);
    if(input->mutation==1 || input->mutation==5) queue->clear();
    if(input->mutation==2 || input->mutation==5) queue->reserve(queue->capacity()+7);
    if(input->mutation==3 || input->mutation==5) queue->push_back(static_cast<EContextTip>(100+step));
    if(input->mutation==4 || input->mutation==5) {
        put(ui.bytes,0x38,actors[1].bytes); put(ui.bytes,0x78,settings[1].bytes);
        actors[0].bytes[SEEN_OFFSET+tipAt(step)]=2;
    }
    if(input->mutation==6) put(ui.bytes,0x78,settings[1].bytes);
    // Capture the post-callback storage, so stale vector loads cannot hide behind
    // an allowed reserve or callback append. These are observations, not an oracle.
    appendStorage=storage(); appendSize=queue->size(); appendCapacity=queue->capacity();
    number(appendSize); number(appendCapacity);
    if(input->fault) throw Stop();
    return input->setting;
}
void observeStep(bool consulted,bool caught) {
    check(calls==expectedCalls);
    check(caught==(consulted && input->fault));
    check(queue->size()==modelSize); check(queue->capacity()==modelCapacity);
    const unsigned size=queue->size();
    // Bound only capture work; an incorrect size remains a completed mismatch.
    check(size<LIMIT);
    for(unsigned i=0;i<size && i<LIMIT;++i) {
        integer(static_cast<int>((*queue)[i]));
        check(i<modelSize && static_cast<int>((*queue)[i])==values[i]);
    }
    const bool appended=consulted && !caught && input->setting==1;
    const bool shouldReuse=!appended || appendSize<appendCapacity;
    check((storage()==appendStorage)==shouldReuse);
    number(size); number(queue->capacity()); number(storage()==appendStorage);
    number(calls); number(caught); number(valid);
    unsigned char actual[UI_SIZE]; std::memcpy(actual,ui.bytes,UI_SIZE);
    std::memset(actual+QUEUE_OFFSET,0,sizeof(Queue));
    check(!std::memcmp(actual,expectedUI,UI_SIZE));
    guards(ui);
    for(unsigned i=0;i<2;++i) {
        check(!std::memcmp(actors[i].bytes,expectedActors[i],ACTOR_SIZE));
        guards(actors[i]); guards(settings[i]);
        for(unsigned j=0;j<SETTINGS_SIZE;++j)
            check(settings[i].bytes[j]==static_cast<unsigned char>(0x91+i*0x12));
    }
    check(KSETTINGS_SHOW_TIPS==input->key+step*17u);
}
void snapshot() {
    // Full sentinel snapshot, normalizing only the three heap-owned vector words.
    unsigned char normalized[UI_SIZE]; std::memcpy(normalized,ui.bytes,UI_SIZE);
    std::memset(normalized+QUEUE_OFFSET,0,sizeof(Queue));
    output->add(ui.raw,GUARD); output->add(normalized,UI_SIZE);
    output->add(ui.bytes+UI_SIZE,GUARD);
    for(unsigned i=0;i<2;++i) {
        output->add(actors[i].raw,ACTOR_SIZE+2*GUARD);
        output->add(settings[i].raw,SETTINGS_SIZE+2*GUARD);
    }
    number(queue->size()); number(queue->capacity()); number(calls);
    number(KSETTINGS_SHOW_TIPS); number(0x51544950u); number(valid);
}
void side(void* raw,autotest::Capture& out,bool recovered) {
    input=static_cast<Case*>(raw); output=&out; setup();
    void(*fn)(CGameUI*,EContextTip)=recovered?&recoveredQueueTip:&originalQueueTip;
    detour::Set redirects; TL_REDIRECT(redirects,getIntBoundary,&getInt);
    require(!redirects.failed()); require(autotest::beginInvocation(out,fn));
    bool unwound=false;
    for(step=0;step<input->steps;++step) {
        KSETTINGS_SHOW_TIPS=input->key+step*17u;
        appendStorage=storage(); appendSize=queue->size(); appendCapacity=queue->capacity();
        const int tip=tipAt(step);
        const bool consulted=modelStep(tip);
        bool caught=false;
        try { fn(reinterpret_cast<CGameUI*>(ui.bytes),static_cast<EContextTip>(tip)); }
        catch(const Stop&) { caught=true; unwound=true; }
        catch(...) { _exit(91); }
        observeStep(consulted,caught);
        if(caught) break;
    }
    if(!unwound) out.callCompleted=1;
    snapshot(); redirects.restore(); require(!redirects.failed());
    queue->~Queue();
}
void original(void* p,autotest::Capture& out) { side(p,out,false); }
void recovered(void* p,autotest::Capture& out) { side(p,out,true); }
bool expectations(const autotest::Capture& c) {
    if(c.length<8) return false;
    unsigned trailer[2]; std::memcpy(trailer,c.data+c.length-8,8);
    return trailer[0]==0x51544950u && trailer[1]==1;
}
int run(const tlhybrid_host* host,const std::vector<Case>& cases,const std::vector<Case>& faults) {
    const uint64_t address=(uint64_t)(uintptr_t)&originalQueueTip;
    autotest::Coverage coverage("gameui_tip_queue",address);
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i]; autotest::Outcome a,b;
        autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
        const bool different=coverage.observe(host,a,b)!=0;
        if(different || !expectations(a.capture) || !expectations(b.capture)) {
            host->log("    queueTip case %u tip %d setting %d mutation %u: status %d/%d expectations %d/%d\n",
                i,c.tip,c.setting,c.mutation,a.status,b.status,expectations(a.capture),expectations(b.capture));
            coverage.report(host); return 1;
        }
    }
    coverage.report(host); if(coverage.completed!=cases.size()) return 1;
    for(unsigned i=0;i<faults.size();++i) {
        Case c=faults[i]; autotest::Outcome a,b;
        autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
        const bool ok=a.reportValid && b.reportValid && !a.childStatus && !b.childStatus &&
            !a.capture.issue && !b.capture.issue && a.capture.callStarted==1 && b.capture.callStarted==1 &&
            !a.capture.callCompleted && !b.capture.callCompleted && a.capture.callTarget==address &&
            host->comparison_pair(address,b.capture.callTarget) && expectations(a.capture) && expectations(b.capture) &&
            a.capture.length==b.capture.length && !std::memcmp(a.capture.data,b.capture.data,a.capture.length);
        if(!ok) { host->log("    queueTip GetInt unwind %u failed\n",i); return 1; }
    }
    host->log("    queueTip GetInt unwinds %u (separate from normal coverage); bad_alloc not instrumented\n",(unsigned)faults.size());
    return 0;
}
}

TL_TEST(gameui_tip_queue) {
    std::vector<Case> cases,faults;
    const int tips[]={-1,0,1,17,255,4096};
    const int settingsValues[]={-1,0,1,2,INT_MIN,INT_MAX};
    const unsigned seenValues[]={0,1,2,255};
    // All predicate/index combinations, including null actor with otherwise unseen tip.
    for(unsigned t=0;t<6;++t) for(unsigned s=0;s<6;++s) for(unsigned b=0;b<4;++b) {
        Case c; c.tip=tips[t]; c.setting=settingsValues[s]; c.seen=seenValues[b];
        c.reserve=5; c.count=3; c.steps=2; c.key=(t&1)?0xffffffffu:0;
        cases.push_back(c); c.nullActor=true; cases.push_back(c);
    }
    // Empty, reserved-empty, spare and exact-full real storage, crossing repeated
    // capacity transitions. Alternating tips preserve ordering; fixed tips duplicate.
    for(unsigned shape=0;shape<4;++shape) for(unsigned alternating=0;alternating<2;++alternating) {
        Case c; c.reserve=shape?4:0; c.count=shape==2?2:shape==3?4:0;
        c.steps=19; c.alternating=alternating!=0; cases.push_back(c);
    }
    for(unsigned mutation=1;mutation<=6;++mutation) for(unsigned s=0;s<3;++s) {
        Case c; c.mutation=mutation; c.setting=s==0?1:s==1?0:-1;
        c.reserve=4; c.count=4; c.steps=3; cases.push_back(c);
    }
    for(unsigned mutation=0;mutation<=6;++mutation) for(unsigned shape=0;shape<3;++shape) {
        Case c; c.mutation=mutation; c.fault=true;
        c.reserve=shape?4:0; c.count=shape==2?4:0; faults.push_back(c);
    }
    // Normal-completion negative controls for the parent: !=0 instead of ==1;
    // duplicate suppression; seen-byte writes/reversed predicate; cached vector
    // end across GetInt. These must mismatch, not crash or count as unwind coverage.
    return run(host,cases,faults);
}
