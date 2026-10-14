// Direct getUnitName 0xd49670 closure draft. Not compiled or executed.
// Genuine original unit/DataGroup/resource construction, repository and COW
// strings. Quest is a bounded +0x1d8 scaffold, never constructed/destructed.
// Only getBaseUnitDataGroup's quest-data-present/null-quest paths are covered.
// Expected dependency exceptions are supplementary, never completed coverage.
#include <cstddef>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "QuestUnitData.h"
#include "TRepository.h"

TL_ORIGINAL(void*, qunOld, (void*,void*), "_ZN14CQuestUnitData11getUnitNameEv")
extern "C" void* qunNew(void*,void*) __asm__("_ZN14CQuestUnitData11getUnitNameEv");
TL_ORIGINAL(void, qunCtor, (void*,void*), "_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void, qunDtor, (void*), "_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void, qunResourceCtor, (void*,void*), "_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, qunResourceDtor, (void*), "_ZN16CResourceManagerD1Ev")
TL_FUNCTION(qunMaster, "_ZN22CMasterResourceManager12getSingletonEv")
TL_ORIGINAL(void, qunGroupCtor, (void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*), "_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void, qunGroupDtor, (void*), "_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*, qunAddText, (void*,const std::wstring&,const std::wstring&,bool), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(CDataGroup*, qunBase, (void*), "_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_FUNCTION(qunBaseBoundary, "_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_ORIGINAL(const std::wstring&, qunText, (void*,const std::wstring&,const std::wstring&), "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(qunTextBoundary, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")

namespace qun {
typedef std::wstring Wide;
typedef char ABI[sizeof(Wide)==8 && sizeof(wchar_t)==4 && sizeof(CQuestUnitData)==0xc8 && sizeof(CDataGroup)==0x60 && sizeof(TRepository<Wide>)==0xa0 && sizeof(CResourceManager)==0x48 ? 1 : -1];
struct Case {
    unsigned branch, text, cow, mode, fault, repeats;
    Case():branch(0),text(3),cow(0),mode(0),fault(0),repeats(1){}
};
struct Stop { unsigned site; explicit Stop(unsigned n):site(n){} };
struct Block { unsigned char* p; unsigned size; };
static const Case* cs;
static autotest::Capture* cap;
static CQuestUnitData* object;
static CDataGroup* groups[3];
static void *quest, *resource;
static Block blocks[8];
static unsigned blockCount, errors, firstError, baseCalls, textCalls, depth, faultHits, turn;
static bool active;
static detour::Set *basePatch, *textPatch;
static Wide* retainedKey;
template<class T> T& at(void* p,unsigned n) { return *reinterpret_cast<T*>(static_cast<char*>(p)+n); }
static void check(bool ok,unsigned line) { if(!ok) { if(!errors)firstError=line; ++errors; } }
#define NEED(x) check((x),__LINE__)
static void n(unsigned v) { cap->add(&v,sizeof(v)); }
static int refs(const Wide& s) { return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8); }
static void* raw(unsigned size) {
    NEED(blockCount<8); if(blockCount>=8)_exit(71);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32)); if(!p)_exit(71);
    std::memset(p,0x6d,16); std::memset(p+16,0,size); std::memset(p+16+size,0xb2,16);
    blocks[blockCount].p=p; blocks[blockCount++].size=size; return p+16;
}
static void guards() {
    for(unsigned k=0;k<blockCount;++k)for(unsigned i=0;i<16;++i) {
        NEED(blocks[k].p[i]==0x6d); NEED(blocks[k].p[16+blocks[k].size+i]==0xb2);
    }
}
static unsigned groupId(CDataGroup* p) {
    if(!p)return 0; for(unsigned i=0;i<3;++i)if(p==groups[i])return i+1; NEED(false); return 99;
}
static void state() {
    n(groupId(object->m_pBaseUnitDataGroup)); n(groupId(object->m_pQuestDataGroup));
    cap->add(&object->m_baseUnitGuid,sizeof(object->m_baseUnitGuid)); n(object->m_unitType);
    cap->addText(object->m_displayName); cap->addText(object->m_generatedChampionName);
}
static void fault(unsigned point) { if(cs->fault==point) { ++faultHits; throw Stop(point); } }
static void* noMaster() { return 0; }
static CDataGroup* base(void* self) {
    NEED(self==object); ++baseCalls; n(10); state(); fault(1);
    basePatch->restore(); ++depth; CDataGroup* value=0;
    try { value=qunBase(self); }
    catch(...) { --depth; TL_REDIRECT(*basePatch,qunBaseBoundary,&base); throw; }
    --depth; TL_REDIRECT(*basePatch,qunBaseBoundary,&base);
    n(11); n(groupId(value)); state(); fault(2);
    if(cs->mode==1)object->m_generatedChampionName=L"Generated late {unchanged}";
    if(cs->mode==2) { object->m_unitType=1; object->m_displayName=L"Late type {unchanged}"; }
    return value;
}
static const Wide& text(void* self,const Wide& key,const Wide& fallback) {
    const bool observe=active&&!depth;
    if(observe) {
        ++textCalls; n(20+textCalls); n(groupId(static_cast<CDataGroup*>(self))); cap->addText(key); state();
        NEED(fallback.empty()); NEED(textCalls<=2); NEED(key==(textCalls==1?L"DISPLAYNAME":L"NAME"));
        const unsigned first=2*textCalls+1;
        if(cs->fault==first||cs->fault==first+1) { NEED(!retainedKey); retainedKey=new Wide(key); }
        fault(first);
    }
    textPatch->restore(); const Wide* value=0;
    try { value=&qunText(self,key,fallback); }
    catch(...) { TL_REDIRECT(*textPatch,qunTextBoundary,&text); throw; }
    TL_REDIRECT(*textPatch,qunTextBoundary,&text);
    if(observe) {
        n(30+textCalls); cap->addText(*value); fault(2*textCalls+2);
        // A genuine first getter has returned. The next getter must reload
        // the object's valid cache rather than retain the first group locally.
        if(cs->mode==3&&textCalls==1)object->m_pBaseUnitDataGroup=groups[1];
    }
    return *value;
}
static Wide display(unsigned shape) {
    switch(shape) {
    case 0: case 1: case 2:return Wide();
    case 3:return L"Display";
    case 4:return L"A{secret}B";
    case 5:return L"{}";
    case 6:return L"{x}";
    case 7:return L"A{}B{later}C";
    case 8:return L"before{";
    case 9:return L"before}";
    case 10:return L"}A{x}B";
    case 11:return L"A{x}B{y}C";
    case 12:return L"A{{x}B}C";
    case 13:return L"{{}}";
    case 14:return L"{x}{y}";
    case 15:return L"\u03a9{\u732b}\U0001f642";
    case 16:return Wide(257,L'a')+L"{x}"+Wide(513,L'z');
    case 17:{ const wchar_t s[]={L'A',0,L'{',L'x',L'}',L'B'}; return Wide(s,6); }
    }
    NEED(false); return Wide();
}
static Wide groupAnswer(unsigned shape) {
    switch(shape) {
    case 0:return Wide();
    case 1:case 2:return L"Fallback";
    case 3:return L"Display";
    case 4:return L"AB";
    case 5:return L"{}";
    case 6:return Wide();
    case 7:return L"A{}B{later}C";
    case 8:return L"before{";
    case 9:return L"before}";
    case 10:return L"}AB";
    case 11:return L"AB{y}C";
    case 12:return L"AB}C";
    case 13:return L"}";
    case 14:return L"{y}";
    case 15:return L"\u03a9\U0001f642";
    case 16:return Wide(257,L'a')+Wide(513,L'z');
    case 17:return L"A"; // Genuine AddDataValue(wstring) truncates at NUL.
    }
    NEED(false); return Wide();
}
static Wide memberText(bool champion) {
    Wide s=champion?L"Champion {keep}":L"Member {keep}";
    if(cs->text==17) { s+=wchar_t(0); s+=L" tail {keep}"; }
    return s;
}
static bool noQuest() { return cs->branch==1||cs->branch==4; }
static bool champion() { return cs->branch>=3; }
static Wide answer() {
    if(cs->mode==1)return L"Generated late {unchanged}";
    if(champion())return memberText(true);
    if(cs->mode==2)return L"Late type {unchanged}";
    if(cs->branch==1||cs->branch==2)return memberText(false);
    if(cs->mode==3)return L"Second fallback";
    return turn?Wide(L"Second  group"):groupAnswer(cs->text);
}
static const Wide& borrowed(CDataGroup* group,const wchar_t* key) {
    return qunText(group,Wide(key),*reinterpret_cast<Wide*>(0x14ff1a8));
}
static CDataGroup* makeGroup(const wchar_t* name) {
    CDataGroup* g=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));
    // The parentless original D1 owns and Ogre-deallocates this repository.
    TRepository<Wide>* repository=new TRepository<Wide>(Wide());
    qunGroupCtor(g,Wide(name),0,4,4,repository); return g;
}
static void setup() {
    errors=firstError=baseCalls=textCalls=depth=faultHits=turn=blockCount=0;
    retainedKey=0; active=false; autotest::g_arenaUsed=0;
    ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();
    ::new(reinterpret_cast<void*>(0x14dda88))Wide();
    ::new(reinterpret_cast<void*>(0x1509e88))Wide();
    resource=raw(sizeof(CResourceManager));
    { detour::Set environment; TL_REDIRECT(environment,qunMaster,&noMaster);
      if(environment.failed()) { cap->issue=autotest::Capture::InvalidReport; throw Stop(999); }
      qunResourceCtor(resource,0); NEED(!environment.failed()); }
    // Bounded Quest scaffold. This selected original dependency path only
    // reads the valid ResourceManager pointer at +0x1d8. No Quest lifecycle.
    quest=raw(0x218); at<void*>(quest,0x1d8)=resource;
    groups[0]=makeGroup(L"PRIMARY"); groups[1]=makeGroup(L"SECOND"); groups[2]=makeGroup(L"STALE");
    qunAddText(groups[0],Wide(L"UNIT_GUID"),Wide(L"123456789"),false);
    qunAddText(groups[1],Wide(L"UNIT_GUID"),Wide(L"987654321"),false);
    if(cs->text>=2)qunAddText(groups[0],Wide(L"DISPLAYNAME"),display(cs->text),false);
    if(cs->text>=1)qunAddText(groups[0],Wide(L"NAME"),Wide(L"Fallback"),false);
    qunAddText(groups[1],Wide(L"DISPLAYNAME"),Wide(L"Second {hidden} group"),false);
    qunAddText(groups[1],Wide(L"NAME"),Wide(L"Second fallback"),false);
    qunAddText(groups[2],Wide(L"DISPLAYNAME"),Wide(L"STALE must not win"),false);
    object=static_cast<CQuestUnitData*>(raw(sizeof(CQuestUnitData))); qunCtor(object,noQuest()?0:quest);
    object->m_pBaseUnitDataGroup=groups[2]; object->m_pQuestDataGroup=groups[0];
    object->m_baseUnitGuid=-1; object->m_unitType=(cs->branch==2||cs->branch==5)?1:22;
    object->m_displayName=memberText(false); object->m_generatedChampionName=champion()?memberText(true):Wide();
}
static bool writable(unsigned off) {
    if((off>=0x20&&off<0x28)||(off>=0x30&&off<0x38))return true;
    if(cs->mode==1&&off>=0xc0&&off<0xc8)return true;
    return cs->mode==2&&((off>=0x44&&off<0x48)||(off>=0x68&&off<0x70));
}
static void side(void* context,autotest::Capture& out,bool candidate) {
    cs=static_cast<Case*>(context); cap=&out; setup();
    const Wide* sources[6]={&object->m_displayName,&object->m_generatedChampionName,
        &borrowed(groups[0],L"DISPLAYNAME"),&borrowed(groups[0],L"NAME"),
        &borrowed(groups[1],L"DISPLAYNAME"),&borrowed(groups[1],L"NAME")};
    Wide aliases[6], snapshots[6], survivor, finalExpected;
    for(unsigned i=0;i<6;++i) {
        if(cs->cow==1)aliases[i]=*sources[i];
        // These are nonconst member/map-value objects, never map keys. A
        // same-character nonconst access changes only legitimate COW state.
        if(cs->cow==2&&!sources[i]->empty())const_cast<Wide&>(*sources[i])[0]=sources[i]->c_str()[0];
        snapshots[i].assign(sources[i]->c_str(),sources[i]->size());
    }
    void* resultStorage=raw(sizeof(Wide)); unsigned caught=0;
    typedef void*(*Fn)(void*,void*); Fn invoke=candidate?&qunNew:&qunOld;
    { detour::Set b,t; basePatch=&b; textPatch=&t;
      TL_REDIRECT(b,qunBaseBoundary,&base); TL_REDIRECT(t,qunTextBoundary,&text);
      if(b.failed()||t.failed()) { out.issue=autotest::Capture::InvalidReport; return; }
      if(!autotest::beginInvocation(out,invoke))return;
      for(turn=0;turn<cs->repeats;++turn) {
        survivor.clear(); if(turn)object->m_pQuestDataGroup=groups[1];
        unsigned char before[0xc8]; std::memcpy(before,object,sizeof(before));
        baseCalls=textCalls=0; int priorRefs[6]; for(unsigned i=0;i<6;++i)priorRefs[i]=refs(*sources[i]);
        void* returned=0; active=true;
        try { returned=invoke(resultStorage,object); } catch(const Stop& stop) { caught=stop.site; } catch(...) { caught=999; NEED(false); }
        active=false; NEED(caught==cs->fault); NEED(baseCalls==1);
        for(unsigned i=0;i<0xc8;++i)if(!writable(i))NEED(reinterpret_cast<unsigned char*>(object)[i]==before[i]);
        const unsigned selected=turn?1:0;
        CDataGroup* expectedCache=cs->fault<=2&&cs->fault?reinterpret_cast<CDataGroup*>(at<void*>(before,0x20)):
            cs->mode==3&&textCalls?groups[1]:noQuest()?0:groups[selected];
        NEED(object->m_pBaseUnitDataGroup==expectedCache);
        const long long expectedGuid=(cs->fault==1||noQuest())?at<long long>(before,0x30):(turn?987654321LL:123456789LL);
        NEED(object->m_baseUnitGuid==expectedGuid);
        if(caught) {
            NEED(!returned&&faultHits==1);
            NEED(textCalls==(caught<=2?0u:(caught-1)/2));
            if(retainedKey) { NEED(refs(*retainedKey)==0); cap->addText(*retainedKey); delete retainedKey; retainedKey=0; }
        } else {
            NEED(returned==resultStorage); Wide& result=*static_cast<Wide*>(resultStorage); Wide expected=answer(); finalExpected=expected;
            NEED(result==expected); cap->addText(result);
            const unsigned wantedText=(champion()||cs->branch==1||cs->branch==2||cs->mode==1||cs->mode==2)?0:
                cs->mode==3?2:turn?1:cs->text<=2?2:1;
            NEED(textCalls==wantedText);
            // A return copy owns exactly one share when it aliases a source.
            for(unsigned i=0;i<6;++i)if(!sources[i]->empty()&&!(cs->mode==1&&i==1)&&!(cs->mode==2&&i==0))
                NEED(refs(*sources[i])==priorRefs[i]+(result.c_str()==sources[i]->c_str()?1:0));
            survivor=result; result.append(L" changed return"); NEED(survivor==expected); result.~Wide();
        }
        for(unsigned i=0;i<6;++i) {
            if(cs->mode==1&&i==1)NEED(*sources[i]==L"Generated late {unchanged}");
            else if(cs->mode==2&&i==0)NEED(*sources[i]==L"Late type {unchanged}");
            else NEED(*sources[i]==snapshots[i]);
            cap->addText(*sources[i]);
            if(!sources[i]->empty()&&!(cs->mode==1&&i==1)&&!(cs->mode==2&&i==0))
                NEED(refs(*sources[i])==priorRefs[i]+(!caught&&survivor.c_str()==sources[i]->c_str()?1:0));
        }
        state(); n(caught); n(baseCalls); n(textCalls); guards(); if(caught)break;
      }
      if(!cs->fault)out.callCompleted=1;
      NEED(!b.failed()&&!t.failed());
    }
    // The returned COW copy remains valid after original owners disappear.
    qunDtor(object); for(unsigned i=0;i<3;++i)qunGroupDtor(groups[i]); qunResourceDtor(resource);
    if(!caught) {
        NEED(survivor==finalExpected); survivor.append(L" after owner destruction"); cap->addText(survivor);
    }
    for(unsigned i=0;i<6;++i)if(cs->cow==1)NEED(aliases[i]==snapshots[i]);
    guards(); n(firstError); n(0x51554e43); n(errors);
}
static void oldSide(void* c,autotest::Capture& out) { side(c,out,false); }
static void newSide(void* c,autotest::Capture& out) { side(c,out,true); }
static bool oracle(const autotest::Outcome& o) {
    unsigned tail[2]={0,1}; if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);
    return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x51554e43&&!tail[1];
}
static unsigned failureLine(const autotest::Outcome& o) {
    unsigned line=0; if(o.capture.length>=12)std::memcpy(&line,o.capture.data+o.capture.length-12,4); return line;
}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& completed,unsigned& unwinds) {
    autotest::Outcome a,b; autotest::runChild(oldSide,&c,a); autotest::runChild(newSide,&c,b); bool ok;
    if(c.fault) {
        ++unwinds; ok=oracle(a)&&oracle(b)&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==0xd49670&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&
            a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    } else { ++completed; ok=coverage.observe(host,a,b)==0&&oracle(a)&&oracle(b); }
    if(!ok) {
        host->log("    unit name branch=%u text=%u cow=%u mode=%u fault=%u repeats=%u completed-pair=%u unwind-pair=%u status=%d/%d oracle=%u/%u firstError=%u/%u started=%u/%u completed=%u/%u\n",
            c.branch,c.text,c.cow,c.mode,c.fault,c.repeats,completed,unwinds,a.childStatus,b.childStatus,oracle(a),oracle(b),failureLine(a),failureLine(b),
            a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);
        coverage.report(host);
    }
    return ok;
}
#undef NEED
}
TL_TEST(quest_unit_name_closure) {
    using namespace qun; autotest::Coverage coverage("quest_unit_name_closure",0xd49670); unsigned completed=0,unwinds=0;
    for(unsigned cow=0;cow<3;++cow) {
        for(unsigned text=0;text<18;++text) { Case c; c.text=text; c.cow=cow; if(!pair(host,coverage,c,completed,unwinds))return 1; }
        for(unsigned branch=1;branch<6;++branch)for(unsigned nul=0;nul<2;++nul) {
            Case c; c.branch=branch; c.text=nul?17:4; c.cow=cow; if(!pair(host,coverage,c,completed,unwinds))return 1;
        }
        for(unsigned mode=1;mode<=3;++mode) { Case c; c.mode=mode; c.text=2; c.cow=cow; if(!pair(host,coverage,c,completed,unwinds))return 1; }
        for(unsigned branch=0;branch<3;++branch) { Case c; c.branch=branch==0?0:branch==1?2:3; c.cow=cow; c.repeats=2; if(!pair(host,coverage,c,completed,unwinds))return 1; }
        for(unsigned fault=1;fault<=6;++fault) { Case c; c.text=2; c.cow=cow; c.fault=fault; if(!pair(host,coverage,c,completed,unwinds))return 1; }
    }
    coverage.report(host); host->log("    unit name: %u completed pairs; %u expected dependency unwinds excluded from acceptance\n",completed,unwinds);
    return completed!=102||unwinds!=18||coverage.completed!=completed||coverage.different||coverage.missing;
}
