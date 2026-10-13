// Original-derived closure for getRewardString, 0xd3d5a0, ELF 91b41ae9...174b.
// Only that address receives acceptance. calculateRewards remains original.
// Lane 0: original Quest/Rewards/Resource constructors and original calculation
// guards, with an explicitly synthetic, bounded editor/client environment.
// Lane 1: original calculation, RNG, graph lookup and graph arithmetic in a
// seeded synthetic graph environment. No world/items/spawn-class coverage.
// Lane 2: explicitly controlled calculation/formatter callbacks for reload,
// UTF-32, COW and exception boundaries. These are not calculation evidence.
// Setup objects live until their isolated child exits. Their borrowed arena
// list storage is deliberately not passed to ownership-taking destructors.
// Target-returned strings are always destroyed with the genuine COW machinery.
// The cleanup ledger covers the representations observed at these boundaries
// and their ownership transitions, not every internal libstdc++ allocation.
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void*, qrsOld, (void*,void*), "_ZN13CQuestRewards15getRewardStringEv")
extern "C" void* qrsNew(void*,void*) __asm__("_ZN13CQuestRewards15getRewardStringEv");
TL_ORIGINAL(void, qrsQuestCtor, (void*,void*,void*), "_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void, qrsRewardCtor, (void*,void*), "_ZN13CQuestRewardsC1EP6CQuest")
TL_ORIGINAL(void, qrsResourceCtor, (void*,void*), "_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, qrsCalculate, (void*), "_ZN13CQuestRewards16calculateRewardsEv")
TL_FUNCTION(qrsCalc, "_ZN13CQuestRewards16calculateRewardsEv")
TL_FUNCTION(qrsFormat, "_ZN7STRINGS17GetValueAsWStringEi")
extern "C" char qrsDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char qrsLiteralCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");
extern "C" char qrsCopyCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qrsStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
extern "C" char qrsAppendChars[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE6appendEPKwm");
extern "C" char qrsAppendText[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE6appendERKS2_");

namespace qrs {
typedef std::wstring Wide;
typedef std::map<Wide,void*> GraphMap;
typedef char WideABI[sizeof(Wide)==8 && sizeof(wchar_t)==4 && sizeof(GraphMap)==48?1:-1];
template<class T> T& at(void* p,unsigned offset) { return *reinterpret_cast<T*>(static_cast<char*>(p)+offset); }
struct Case {
    unsigned lane,guard,scenario,payload,leaked,fault,line;
    int difficulty;
    float xp,gold,fame,percent;
    Case():lane(0),guard(1),scenario(0),payload(0),leaked(0),fault(0),line(0),difficulty(1),xp(0),gold(0),fame(0),percent(100){}
};
struct Stop { unsigned site; explicit Stop(unsigned n):site(n){} };
struct Block { unsigned char* p; unsigned size; unsigned char before[0x3920]; };
struct Rep { void* p; bool live; };
static const Case* cs;
static autotest::Capture* cap;
static void *owner,*quest,*resource,*manager,*client,*editor,*output;
static Wide *payloads[3];
static Wide* wanted;
static Block blocks[24];
static Rep reps[256];
static unsigned blockCount,repCount,errors,firstError,calcCalls,formatCalls,faultHits;
static unsigned newlineCalls,lineAppends,created,destroyed,headingSeen;
static unsigned expectedFormats;
static int expectedInts[3],observedInts[3],sourceRefs[3];
static unsigned sourceHashes[3];
static float expectedFloats[3];
static bool tracking;
static detour::Set *calcPatch,*destroyPatch,*charsPatch,*textPatch,*literalPatch,*copyPatch,*dtorPatch;
static void number(unsigned n) { cap->add(&n,sizeof(n)); }
static void check(bool ok,unsigned line) { if(!ok) { if(!errors)firstError=line; ++errors; } }
#define QRS_NEED(x) check((x),__LINE__)
static void* raw(unsigned size) {
    QRS_NEED(blockCount<24 && size<=0x3920);
    if(blockCount>=24 || size>0x3920) _exit(71);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));
    if(!p) _exit(71);
    std::memset(p,0xb6,16); std::memset(p+16,0,size); std::memset(p+16+size,0x6b,16);
    blocks[blockCount].p=p; blocks[blockCount++].size=size;
    return p+16;
}
static int refs(const Wide& s) { return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8); }
static void* rep(const Wide& s) { return const_cast<char*>(reinterpret_cast<const char*>(s.c_str())-24); }
static unsigned hash(const Wide& s) { unsigned h=2166136261u;for(unsigned i=0;i<s.size();++i)h=(h^static_cast<unsigned>(s[i]))*16777619u;return h; }
static float bits(unsigned n) { float f; std::memcpy(&f,&n,4); return f; }
static int rounded(float f) {
    // Match the documented target machine conversion, including +infinity and
    // finite overflow, without invoking C++'s out-of-range float->int UB.
    float c=::ceilf(f); int n;
    __asm__("cvttss2si %1,%0":"=r"(n):"x"(c));
    return n;
}
static Wide decimal(int value) {
    char text[32]; std::snprintf(text,sizeof(text),"%d",value);
    Wide result; for(const char* p=text;*p;++p)result+=static_cast<wchar_t>(*p);
    return result;
}
static void setFloats(void* p,float xp,float gold,float fame) {
    at<float>(p,0x18)=xp; at<float>(p,0x1c)=gold; at<float>(p,0x20)=fame;
}
static void sourceMutation(unsigned call,float& xp,float& gold,float& fame) {
    if(cs->scenario==2 && call==1) { xp=2.25f; fame=4.25f; }
    if(cs->scenario==2 && call==2) fame=7.25f;
    if(cs->scenario==3 && call==1) { xp=0; fame=0; }
    if(cs->scenario==4 && call==1) { xp=bits(0x7fc01234); fame=9.5f; }
    if(cs->scenario==5 && call==1) gold=0;
}
static void controlledValues(float& xp,float& gold,float& fame) {
    xp=cs->xp; gold=cs->gold; fame=cs->fame;
    if(cs->scenario==1) { xp=3.25f; gold=1.25f; fame=5.25f; }
    if(cs->scenario==2) { xp=-3; gold=1.25f; fame=-5; }
    if(cs->scenario==3) { xp=3.25f; gold=1.25f; fame=5.25f; }
    if(cs->scenario==4) { xp=3.25f; gold=1.25f; fame=-5; }
    if(cs->scenario==5) { xp=3.25f; gold=1.25f; fame=5.25f; }
}
static void makeExpected() {
    float xp=cs->xp,gold=cs->gold,fame=cs->fame;
    if(cs->lane==1) {
        xp=static_cast<float>(rounded(102.25f*(cs->percent/100.0f)));
        if(cs->difficulty>=0 && cs->difficulty<=3) {
            gold=static_cast<float>(rounded((65.5f+cs->difficulty*40.0f)*(cs->percent/100.0f)));
            fame=static_cast<float>(rounded((9.25f+cs->difficulty*12.0f)*(cs->percent/100.0f)));
        }
    } else if(cs->lane==2) controlledValues(xp,gold,fame);
    expectedFormats=0;
    if(gold<=0 && xp<=0) *wanted=L"Reward:\n    None";
    else {
        *wanted=L"Reward(s):\n";
        const wchar_t* prefixes[]={L"    GOLD: ",L"     XP: ",L"     FAME: "};
        for(unsigned i=0;i<3;++i) {
            float value=i==0?gold:i==1?xp:fame;
            if(value>0) {
                int n=rounded(value); expectedInts[expectedFormats]=n;
                *wanted+=prefixes[i];
                *wanted+=cs->lane==2?*payloads[expectedFormats]:decimal(n);
                *wanted+=L'\n'; ++expectedFormats;
                if(cs->lane==2)sourceMutation(expectedFormats,xp,gold,fame);
            }
        }
    }
    expectedFloats[0]=xp; expectedFloats[1]=gold; expectedFloats[2]=fame;
}
static void* graph(float value) {
    void* p=raw(0x58);
    at<unsigned char>(p,0x3d)=1; // Original CGraph inference branch, no curve callback.
    at<float>(p,0x40)=0; at<float>(p,0x48)=value; at<float>(p,0x50)=-100;
    return p;
}
static void initialize() {
    blockCount=repCount=errors=firstError=calcCalls=formatCalls=faultHits=0;
    newlineCalls=lineAppends=created=destroyed=headingSeen=0; tracking=false;
    autotest::g_arenaUsed=0;
    // Self-tests run before normal game static initialization. These are empty
    // COW source cells read by the original Quest/Requirements constructors.
    const uintptr_t cells[]={0x14f9fe8,0x151d408,0x14fb488,0x14ff1a8,0x151c128,0x151ab48};
    for(unsigned i=0;i<6;++i)new(reinterpret_cast<void*>(cells[i]))Wide();
    *reinterpret_cast<void**>(0x14b3ae0)=0; // Null master keeps Resource ctor local.
    resource=raw(0x48); manager=raw(0x30); quest=raw(0x218); owner=raw(0x78);
    editor=raw(0x70); client=raw(0x3910); output=raw(sizeof(Wide));
    std::memset(output,0xc9,sizeof(Wide));
    qrsResourceCtor(resource,0); qrsQuestCtor(quest,resource,manager); qrsRewardCtor(owner,quest);
    *reinterpret_cast<void**>(0x145c6e0)=editor;
    at<unsigned>(editor,0x64)=cs->lane==0&&cs->guard==0?0:2;
    at<void*>(manager,0x10)=raw(0x20);
    void** clients=static_cast<void**>(raw(8)); clients[0]=client;
    if(cs->lane!=0 || cs->guard>=2) {
        at<void*>(resource,0x28)=clients; at<unsigned>(resource,0x30)=1; at<unsigned>(resource,0x34)=1;
    }
    if(cs->lane==0) {
        if(cs->guard==2)clients[0]=0;
        if(cs->guard==3)at<void*>(quest,0x1d0)=0;
        if(cs->guard==4)at<void*>(manager,0x10)=0;
        if(cs->guard==5) {
            void** items=static_cast<void**>(raw(8)); items[0]=0;
            at<void*>(owner,0x60)=items; at<unsigned>(owner,0x68)=1; at<unsigned>(owner,0x6c)=1;
        }
        // guard 6 has valid client/player and no percentages/items/spawn.
    }
    setFloats(owner,cs->xp,cs->gold,cs->fame);
    if(cs->lane==1) {
        at<int>(client,0x38ec)=cs->difficulty; at<int>(quest,0x1c)=27; at<int>(quest,0x20c)=12;
        for(unsigned off=0x48;off<=0x5c;off+=4)at<float>(owner,off)=cs->percent;
        void* master=raw(0x100); void* graphManager=raw(0x48);
        at<void*>(master,0x48)=graphManager; *reinterpret_cast<void**>(0x14b3ae0)=master;
        GraphMap* map=new(static_cast<char*>(graphManager)+0x18)GraphMap();
        const wchar_t* goldNames[]={L"GOLDDROP_EASY",L"GOLDDROP",L"GOLDDROP_HARD",L"GOLDDROP_VERYHARD"};
        const wchar_t* fameNames[]={L"FAME_CHAMPIONMONSTER_EASY",L"FAME_CHAMPIONMONSTER",L"FAME_CHAMPIONMONSTER_HARD",L"FAME_CHAMPIONMONSTER_VERYHARD"};
        for(unsigned i=0;i<4;++i) { (*map)[goldNames[i]]=graph(65.5f+i*40.0f); (*map)[fameNames[i]]=graph(9.25f+i*12.0f); }
        (*map)[L"EXPERIENCE_MONSTER"]=graph(102.25f);
    }
    for(unsigned i=0;i<3;++i) {
        // Not arena blocks: setup strings and expected text are not part of
        // the target's mutable input image or target allocation ledger.
        void* memory=autotest::allocate(sizeof(Wide)); if(!memory)_exit(71);
        payloads[i]=new(memory)Wide();
        if(cs->payload==0)*payloads[i]=decimal(static_cast<int>(i+10));
        else if(cs->payload==1) {
            const wchar_t points[]={static_cast<wchar_t>(L'A'+i),0,0x03a9,0x732b,0x1f642};
            payloads[i]->assign(points,5);
        } else if(cs->payload==2)payloads[i]->assign(4096+i*31,static_cast<wchar_t>(0x400+i));
        // payload 3 intentionally returns the canonical empty representation.
        if(cs->leaked && !payloads[i]->empty())(*payloads[i])[0]=payloads[i]->c_str()[0];
        sourceRefs[i]=refs(*payloads[i]);
        sourceHashes[i]=hash(*payloads[i]);
    }
    void* memory=autotest::allocate(sizeof(Wide)); if(!memory)_exit(71); wanted=new(memory)Wide();
    makeExpected();
    *reinterpret_cast<uint64_t*>(0x14ecaf0)=0x1122334455667788ULL;
    for(unsigned i=0;i<blockCount;++i)std::memcpy(blocks[i].before,blocks[i].p+16,blocks[i].size);
}
static void calculate(void* self) {
    ++calcCalls; QRS_NEED(self==owner); number(0xc100);
    if(cs->lane!=2) {
        calcPatch->restore(); qrsCalculate(self); TL_REDIRECT(*calcPatch,qrsCalc,&calculate);
    } else {
        float xp,gold,fame; controlledValues(xp,gold,fame); setFloats(self,xp,gold,fame);
        if(cs->fault==1) { ++faultHits; throw Stop(1); }
    }
}
static void watch(const Wide& s) {
    if(!tracking)return;
    void* p=rep(s);
    if(p==reinterpret_cast<void*>(0x1424540))return;
    for(unsigned i=0;i<3;++i)if(p==rep(*payloads[i]))return;
    for(unsigned i=0;i<repCount;++i)if(reps[i].p==p&&reps[i].live)return;
    QRS_NEED(repCount<256);
    if(repCount<256){reps[repCount].p=p;reps[repCount++].live=true;++created;}
}
static void released(void* p) {
    if(tracking)for(unsigned i=repCount;i;--i)if(reps[i-1].p==p && reps[i-1].live) { reps[i-1].live=false; ++destroyed; break; }
}
static void* format(void* storage,int value) {
    QRS_NEED(calcCalls==1 && formatCalls<3);
    unsigned index=formatCalls++;
    if(index<3)observedInts[index]=value;
    number(0xf100+index); cap->add(&value,sizeof(value));
    if(cs->fault==2 && formatCalls==cs->line) { ++faultHits; throw Stop(2); }
    float xp=at<float>(owner,0x18),gold=at<float>(owner,0x1c),fame=at<float>(owner,0x20);
    sourceMutation(formatCalls,xp,gold,fame); setFloats(owner,xp,gold,fame);
    Wide* result=new(storage)Wide(*payloads[index<3?index:0]); watch(*result);return result;
}
static void destroyRep(void* p,const void* allocator) {
    released(p);
    destroyPatch->restore(); reinterpret_cast<void(*)(void*,const void*)>(qrsDestroy)(p,allocator);
    destroyPatch->redirect(qrsDestroy,qrsDestroy,&destroyRep);
}
static void literalCtor(Wide* self,const wchar_t* text,const void* allocator) {
    literalPatch->restore(); reinterpret_cast<void(*)(Wide*,const wchar_t*,const void*)>(qrsLiteralCtor)(self,text,allocator);
    literalPatch->redirect(qrsLiteralCtor,qrsLiteralCtor,&literalCtor);watch(*self);
    if(tracking&&self->size()==11&&self->compare(0,11,L"Reward(s):\n")==0)++headingSeen;
}
static void copyCtor(Wide* self,const Wide& other) {
    copyPatch->restore();reinterpret_cast<void(*)(Wide*,const Wide&)>(qrsCopyCtor)(self,other);
    copyPatch->redirect(qrsCopyCtor,qrsCopyCtor,&copyCtor);watch(*self);
}
static void stringDtor(Wide* self) {
    void* p=rep(*self);bool last=refs(*self)<=0;
    dtorPatch->restore();reinterpret_cast<void(*)(Wide*)>(qrsStringDtor)(self);
    dtorPatch->redirect(qrsStringDtor,qrsStringDtor,&stringDtor);if(last)released(p);
}
static Wide* appendChars(Wide* self,const wchar_t* p,size_t n) {
    watch(*self);void* before=rep(*self);int oldRefs=refs(*self);
    if(tracking && n==1 && p[0]==L'\n') {
        ++newlineCalls;
        if(cs->fault==3 && newlineCalls==cs->line) { ++faultHits; throw Stop(3); }
    }
    charsPatch->restore();
    Wide* result=reinterpret_cast<Wide*(*)(Wide*,const wchar_t*,size_t)>(qrsAppendChars)(self,p,n);
    charsPatch->redirect(qrsAppendChars,qrsAppendChars,&appendChars);
    // Real libstdc++ performs this reallocation internally, outside the ELF's
    // PLT. Observe its completed ownership transition rather than pretending
    // a PLT factory hook sees all library-internal allocation calls.
    if(rep(*self)!=before&&oldRefs<=0)released(before);watch(*self);return result;
}
static Wide* appendText(Wide* self,const Wide& value) {
    watch(*self);watch(value);void* before=rep(*self);int oldRefs=refs(*self);
    if(tracking && self->size()>=11 && self->compare(0,11,L"Reward(s):\n")==0) {
        ++lineAppends;
        if(cs->fault==4 && lineAppends==cs->line) { ++faultHits; throw Stop(4); }
    }
    textPatch->restore();
    Wide* result=reinterpret_cast<Wide*(*)(Wide*,const Wide&)>(qrsAppendText)(self,value);
    textPatch->redirect(qrsAppendText,qrsAppendText,&appendText);
    if(rep(*self)!=before&&oldRefs<=0)released(before);watch(*self);return result;
}
static unsigned live() { unsigned n=0; for(unsigned i=0;i<repCount;++i)n+=reps[i].live; return n; }
static void side(void* context,autotest::Capture& out,bool candidate) {
    cs=static_cast<Case*>(context); cap=&out; initialize();
    unsigned caught=0; bool returned=false;
    {
        detour::Set calculation,formatter,destroys,chars,texts,literals,copies,dtors;
        calcPatch=&calculation; destroyPatch=&destroys; charsPatch=&chars; textPatch=&texts;
        literalPatch=&literals;copyPatch=&copies;dtorPatch=&dtors;
        TL_REDIRECT(calculation,qrsCalc,&calculate);
        if(cs->lane==2) {
            TL_REDIRECT(formatter,qrsFormat,&format);
            destroys.redirect(qrsDestroy,qrsDestroy,&destroyRep);
            chars.redirect(qrsAppendChars,qrsAppendChars,&appendChars); texts.redirect(qrsAppendText,qrsAppendText,&appendText);
            literals.redirect(qrsLiteralCtor,qrsLiteralCtor,&literalCtor);copies.redirect(qrsCopyCtor,qrsCopyCtor,&copyCtor);dtors.redirect(qrsStringDtor,qrsStringDtor,&stringDtor);
        }
        if(calculation.failed()||formatter.failed()||destroys.failed()||chars.failed()||texts.failed()||literals.failed()||copies.failed()||dtors.failed()) { out.issue=autotest::Capture::InvalidReport; return; }
        typedef void*(*Fn)(void*,void*); Fn fn=candidate?&qrsNew:&qrsOld;
        if(!autotest::beginInvocation(out,fn))return;
        tracking=true;
        try {
            void* result=fn(output,owner); out.callCompleted=1; returned=true;
            QRS_NEED(result==output);
        } catch(const Stop& stop) { caught=stop.site; }
        tracking=false;
        QRS_NEED(calcCalls==1);
        if(!cs->fault) {
            QRS_NEED(returned && !caught && !faultHits);
            if(returned) {
                const Wide& s=at<Wide>(output,0);
                QRS_NEED(s==*wanted); QRS_NEED(refs(s)==0); cap->addText(s);
                QRS_NEED(s.c_str()[s.size()]==0);
                // Result is independent; a shared copy separates on mutation.
                Wide copy=s; QRS_NEED(copy==s);
                if(!copy.empty())copy[0]=L'!';
                QRS_NEED(s==*wanted); QRS_NEED(copy.empty() || copy[0]==L'!');
            }
            QRS_NEED(!std::memcmp(static_cast<char*>(owner)+0x18,expectedFloats,12));
            if(cs->lane==2) {
                QRS_NEED(formatCalls==expectedFormats);
                for(unsigned i=0;i<formatCalls&&i<3;++i)QRS_NEED(observedInts[i]==expectedInts[i]);
            }
        } else {
            QRS_NEED(!returned && !out.callCompleted && caught==cs->fault && faultHits==1);
            QRS_NEED(formatCalls==(cs->fault==1?0:cs->line));
            for(unsigned i=0;i<sizeof(Wide);++i)QRS_NEED(static_cast<unsigned char*>(output)[i]==0xc9);
        }
        // Observe actual COW allocation release while destroying the returned
        // object. No synthetic destructor, allocator, or deallocator semantics.
        tracking=true;
        if(returned)at<Wide>(output,0).~Wide();
        tracking=false;
        if(cs->lane==2) {
            QRS_NEED(live()==0 && created==destroyed);
            QRS_NEED(headingSeen==(cs->fault==1?0u:1u));
            QRS_NEED(cs->fault==1 || created>0);
        }
        for(unsigned i=0;i<3;++i) { QRS_NEED(refs(*payloads[i])==sourceRefs[i]);QRS_NEED(hash(*payloads[i])==sourceHashes[i]); }
    }
    // Compare every untouched input byte and every canary. The reward fields
    // are captured as bits; no NaN numeric equality or string pointer hashing.
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i]; void* p=b.p+16;
        for(unsigned j=0;j<16;++j)QRS_NEED(b.p[j]==0xb6 && b.p[16+b.size+j]==0x6b);
        if(p==output)continue;
        for(unsigned j=0;j<b.size;++j) {
            if(p==owner && j>=0x18 && j<0x24)continue;
            QRS_NEED(b.p[16+j]==b.before[j]);
        }
        // Constructor-owned pointers are setup state, stable within each
        // fork pair; capture only byte-change witnesses for non-owner blocks.
        if(p==owner)cap->add(static_cast<char*>(owner)+0x18,12);
    }
    if(cs->lane==1)QRS_NEED(*reinterpret_cast<uint64_t*>(0x14ecaf0)==static_cast<uint64_t>(27+0x272b));
    else QRS_NEED(*reinterpret_cast<uint64_t*>(0x14ecaf0)==0x1122334455667788ULL);
    number(calcCalls); number(formatCalls); number(caught); number(faultHits); number(firstError); number(0x71525753u); number(errors);
}
static void oldSide(void* p,autotest::Capture& out) { side(p,out,false); }
static void newSide(void* p,autotest::Capture& out) { side(p,out,true); }
static bool oracle(const autotest::Outcome& o) {
    unsigned tail[2]={0,1}; if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);
    return o.reportValid && o.childStatus==0 && !o.capture.issue && tail[0]==0x71525753u && !tail[1];
}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& count) {
    autotest::Outcome a,b; autotest::runChild(oldSide,&c,a); autotest::runChild(newSide,&c,b);
    bool ok;
    if(c.fault) {
        ok=oracle(a)&&oracle(b)&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==0xd3d5a0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&
            a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    } else { ++count; ok=coverage.observe(host,a,b)==0 && oracle(a) && oracle(b); }
    if(!ok) {
        unsigned fa=0,fb=0;
        if(a.capture.length>=12)std::memcpy(&fa,a.capture.data+a.capture.length-12,4);
        if(b.capture.length>=12)std::memcpy(&fb,b.capture.data+b.capture.length-12,4);
        host->log("    reward string lane=%u guard=%u scenario=%u payload=%u leaked=%u fault=%u line=%u difficulty=%d values=%g/%g/%g status=%d/%d completed=%u/%u first=%u/%u\n",c.lane,c.guard,c.scenario,c.payload,c.leaked,c.fault,c.line,c.difficulty,c.xp,c.gold,c.fame,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted,fa,fb);
        coverage.report(host);
    }
    return ok;
}
}

TL_TEST(quest_reward_string_closure) {
    using namespace qrs;
    autotest::Coverage coverage("quest_reward_string_closure",0xd3d5a0); unsigned count=0,unwinds=0;
    // Mandatory invocation, fame-only suppression, full truth table and each
    // viable real calculation early exit. All ordinary calls complete.
    for(unsigned guard=0;guard<7;++guard)for(unsigned mask=0;mask<8;++mask) {
        Case c; c.guard=guard; c.xp=mask&1?2.25f:0; c.gold=mask&2?7.125f:0; c.fame=mask&4?11.5f:0;
        if(!pair(host,coverage,c,count))return 1;
    }
    const unsigned values[]={0,0x80000000u,0xbf800000u,1,0x3f7fffffu,0x3f800000u,0x3f800001u,0x4b7fffffu,0x4effffffu,0x4f000000u,0x7f800000u,0xff800000u,0x7fc01234u};
    for(unsigned i=0;i<sizeof(values)/sizeof(values[0]);++i)for(unsigned position=0;position<3;++position) {
        Case c; c.xp=0; c.gold=0; c.fame=9.5f;
        if(position==0)c.xp=bits(values[i]); else if(position==1)c.gold=bits(values[i]); else { c.gold=1; c.fame=bits(values[i]); }
        if(!pair(host,coverage,c,count))return 1;
    }
    const float percentages[]={25,33,100,150};
    for(int difficulty=-1;difficulty<=4;++difficulty)for(unsigned p=0;p<4;++p) {
        Case c; c.lane=1; c.difficulty=difficulty; c.percent=percentages[p]; c.xp=-17;c.gold=-19;c.fame=-23;
        if(!pair(host,coverage,c,count))return 1;
    }
    for(unsigned scenario=0;scenario<6;++scenario)for(unsigned payload=0;payload<4;++payload)for(unsigned leaked=0;leaked<2;++leaked) {
        Case c; c.lane=2;c.scenario=scenario;c.payload=payload;c.leaked=leaked;c.xp=3.25f;c.gold=1.25f;c.fame=5.25f;
        if(!pair(host,coverage,c,count))return 1;
    }
    // Expected LSDA-covered unwinds are deliberately excluded from Coverage.
    for(unsigned fault=1;fault<=4;++fault)for(unsigned line=1;line<=(fault==1?1u:3u);++line)for(unsigned leaked=0;leaked<2;++leaked) {
        Case c;c.lane=2;c.fault=fault;c.line=line;c.leaked=leaked;c.payload=1;c.xp=3.25f;c.gold=1.25f;c.fame=5.25f;
        if(!pair(host,coverage,c,count))return 1; ++unwinds;
    }
    coverage.report(host);
    host->log("    reward string: %u completed target-only pairs; %u expected cleanup unwinds (no acceptance credit)\n",count,unwinds);
    return coverage.completed!=count || count!=167 || unwinds!=20 || coverage.different || coverage.missing;
}
