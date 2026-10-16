// Differential fixture for original ELF 91b41ae9...41724b, 0x973370.
// Authored from prepared packet tu-pipbn9ai and the original disassembly.
// This file has not itself been compiled or executed at authoring time.
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <new>
#include <string>
#include <vector>
#include <fenv.h>
#define private public
#include "LevelTemplateData.h"
#undef private
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(int, ltgOriginal, (CLevelTemplateData*, int), "_ZN18CLevelTemplateData18createRandomLayoutEi")
extern "C" int ltgCandidate(CLevelTemplateData*, int) __asm__("_ZN18CLevelTemplateData18createRandomLayoutEi");
TL_ORIGINAL(void, ltgOwnerConstruct, (void*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, ltgOwnerDestroy, (void*), "_ZN18CLevelTemplateDataD1Ev")
TL_FUNCTION(ltgRandom, "_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(ltgValid, "_ZN11CRandomizer15hasValidChoicesEv")
TL_FUNCTION(ltgOdds, "_ZN11CRandomizer13setChoiceOddsEii")
TL_FUNCTION(ltgAdd, "_ZN11CRandomizer9addChoiceEii")
TL_FUNCTION(ltgReset, "_ZN18CLevelTemplateData9resetOddsEv")
TL_FUNCTION(ltgInteger, "_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(ltgSeed, "_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(ltgIntersects, "_ZN18CLevelTemplateData16intersectsChunksEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
TL_FUNCTION(ltgExits, "_ZN18CLevelTemplateData10exitsMatchEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
TL_FUNCTION(ltgMatch, "_ZN18CLevelTemplateData10matchExitsEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
TL_FUNCTION(ltgCoreCtor1, "_ZN10CRunicCoreC1Ev")
TL_FUNCTION(ltgCoreCtor2, "_ZN10CRunicCoreC2Ev")
TL_FUNCTION(ltgCoreDtor1, "_ZN10CRunicCoreD1Ev")
TL_FUNCTION(ltgCoreDtor2, "_ZN10CRunicCoreD2Ev")
extern "C" char ltgFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");

namespace level_template_generator {
typedef char OwnerABI[sizeof(CLevelTemplateData)==0x778 && sizeof(CRandomizer)==0x68 && sizeof(std::wstring)==8 && sizeof(CChunkInstance)==0x48 && sizeof(CLevelLayout)==0x48 ? 1 : -1];
enum Family {
    NoEntrance, EmptySuccess, RealCorridor, ControlledCorridor, RequiredPresent,
    RequiredRetry, ChoiceRetry, Appearance, AppearanceRetry, SkipSingle,
    SkipEmpty, PlacementRetry, ExitDirection, CapDirection, ExitReject,
    CapReject, MissingExit, MissingCap, InvalidType, ExistingLayouts,
    TerminalExit, TerminalRequired, TerminalInvalid, TerminalCap
};
struct Case { unsigned family, variant; };
struct Lifetime { void* pointer; unsigned destroyed, freed, kind; };
static const Case* input;
static autotest::Capture* capture;
static CLevelTemplateData* owner;
static unsigned errors, attempts, generalCalls, integerCalls, seedCalls;
static unsigned resetCalls, addCalls, oddsZeroCalls, geometryCalls, matchCalls;
static unsigned directionalMask, concreteMask, objectCount, initialLayouts;
static bool targetPending, nextObjectIsLayout, active;
static Lifetime objects[4096];
static detour::Set *validPatch, *oddsPatch, *addPatch, *resetPatch;
static detour::Set *intersectsPatch, *exitsPatch, *matchPatch;
static detour::Set *ctorPatch, *dtorPatch, *freePatch;
static const unsigned exitOffsets[4]={0x1d8,0x240,0x2a8,0x310};
static const unsigned capOffsets[4]={0x378,0x3e0,0x448,0x4b0};
static void word(unsigned value) { capture->add(&value,4); }
static void signedWord(int value) { capture->add(&value,4); }
static void need(bool value,unsigned check) {
    if(!value) { ++errors; word(0xf7000000u+check); }
}
static void fatal(bool value,unsigned check) {
    if(!value) { need(false,check); capture->issue=autotest::Capture::InvalidReport; _exit(91); }
}
static unsigned direction() { return input->variant%4; }
static bool terminal() { return input->family>=TerminalExit; }
static bool directional() {
    return (input->family>=ExitDirection && input->family<=MissingCap) || input->family==TerminalCap;
}
static CRandomizer& pool(unsigned offset) {
    return *reinterpret_cast<CRandomizer*>(reinterpret_cast<char*>(owner)+offset);
}
// Embedded pools retain their owner-relative identity; separately allocated
// concrete pools retain their actual m_chunkRandomizers array index.
static unsigned poolID(CRandomizer* p) {
    for(unsigned i=0;i<10;++i) if(p==&pool(0x108+i*0x68)) return 0x108+i*0x68;
    if(p==owner->m_layoutRandomizer) return 0xe8;
    for(unsigned i=0;i<owner->m_chunkRandomizers.size();++i)
        if(p==owner->m_chunkRandomizers[i]) return 0x10000+i;
    need(false,1); return ~0u;
}
static int latestObject(const void* p,bool unfreedOnly) {
    for(unsigned i=objectCount;i;--i)
        if(objects[i-1].pointer==p && (!unfreedOnly || !objects[i-1].freed)) return i-1;
    return -1;
}
static unsigned objectID(const void* p) {
    int i=latestObject(p,true); need(i>=0,2); return i<0?~0u:unsigned(i);
}
static void instance(CChunkInstance* p) {
    word(objectID(p)); signedWord(p->m_chunkTypeIndex);
    capture->add(&p->m_x,12); capture->addText(p->m_name);
    word(p->m_usedExits.size());
    for(unsigned i=0;i<p->m_usedExits.size();++i) signedWord(p->m_usedExits[i]);
}
static void peers(CChunkInstance* p,std::vector<CChunkInstance*>& v) {
    instance(p); word(v.size());
    for(unsigned i=0;i<v.size();++i) instance(v[i]);
}
static void coreConstruct(CRunicCore* p) {
    ctorPatch->restore();
    reinterpret_cast<void(*)(CRunicCore*)>(ltgCoreCtor1_original)(p);
    TL_REDIRECT(*ctorPatch,ltgCoreCtor1,&coreConstruct);
    TL_REDIRECT(*ctorPatch,ltgCoreCtor2,&coreConstruct);
    fatal(!ctorPatch->failed(),3);
    if(!active) return;
    fatal(objectCount<4096,4); need(latestObject(p,true)<0,5);
    Lifetime& object=objects[objectCount]; object.pointer=p;
    object.destroyed=object.freed=0; object.kind=nextObjectIsLayout?2:1;
    nextObjectIsLayout=false; word(10); word(objectCount++); word(object.kind);
}
static void coreDestroy(CRunicCore* p) {
    int id=latestObject(p,true);
    if(active&&id>=0) { word(11); word(id); need(!objects[id].destroyed,6); ++objects[id].destroyed; }
    dtorPatch->restore();
    reinterpret_cast<void(*)(CRunicCore*)>(ltgCoreDtor1_original)(p);
    TL_REDIRECT(*dtorPatch,ltgCoreDtor1,&coreDestroy);
    TL_REDIRECT(*dtorPatch,ltgCoreDtor2,&coreDestroy);
    fatal(!dtorPatch->failed(),7);
}
static void objectFree(void* p) {
    int id=latestObject(p,true);
    if(active&&id>=0) { word(12); word(id); need(objects[id].destroyed==1,8); ++objects[id].freed; }
    freePatch->restore(); reinterpret_cast<void(*)(void*)>(ltgFree)(p);
    freePatch->redirect(ltgFree,ltgFree,&objectFree); fatal(!freePatch->failed(),9);
}
static int seedValue(unsigned v) {
    static const unsigned seeds[]={0,1,0xffffffffu,0x80000000u,0x7fffffffu,0x12345678u,42,0xdeadbeefu};
    int result; unsigned bits=seeds[v%8]; std::memcpy(&result,&bits,4); return result;
}
static void setSeed(int seed) { word(20); signedWord(seed); ++seedCalls; }
static int target() {
    switch(input->family) {
        case RealCorridor: case ControlledCorridor: return 1+int(input->variant%3);
        case RequiredPresent: case SkipSingle: case SkipEmpty: return 1;
        case AppearanceRetry: return attempts==1?2:0;
        case PlacementRetry: return attempts==1?1:0;
        case EmptySuccess: return -int(input->variant%3);
        default: return 0;
    }
}
static int integer(int low,int high) {
    ++integerCalls; word(21); signedWord(low); signedWord(high);
    int result;
    if(targetPending) { targetPending=false; result=target(); }
    else { need(low==0&&high>=0,10); result=input->variant&4?high:low; }
    signedWord(result); return result;
}
static int firstPositive(CRandomizer* p) {
    for(unsigned i=0;i<p->m_Odds.size();++i)
        if(p->m_Odds[i]>0.0f) return p->m_Choices[i];
    need(false,11); return 0;
}
static int random(CRandomizer* p) {
    unsigned id=poolID(p); int result=0;
    if(id==0x170) {
        ++attempts; generalCalls=0; targetPending=true;
        if((input->family==MissingExit||input->family==MissingCap)&&attempts==2) {
            // A deterministic dependency transition: only the previously empty
            // directional pool becomes available on the second outer attempt.
            CRandomizer& changed=pool(input->family==MissingExit?exitOffsets[direction()]:capOffsets[direction()]);
            changed.m_Odds.m_nCount=1;
        }
        if((input->family==RequiredRetry||input->family==AppearanceRetry)&&attempts>1) result=4;
        else if(input->family==InvalidType) result=input->variant&1?-1:0x7fffffff;
    } else if(id==0x108) {
        ++generalCalls; result=1;
        if(input->family==SkipSingle&&generalCalls==1) result=5;
        if(input->family==SkipEmpty&&generalCalls==1) result=3;
        if(input->family==PlacementRetry&&attempts==1) {
            unsigned successAt=input->variant==4?999u:1000u;
            result=input->variant>=4&&generalCalls>=successAt?1:4;
        }
    } else if(id>=0x10000&&id<0x10006) {
        concreteMask|=1u<<(id-0x10000); result=firstPositive(p);
    } else if(id>=0x1d8&&id<=0x4b0) {
        directionalMask|=1u<<((id-0x1d8)/0x68); result=2;
    } else need(false,12);
    word(22); word(id); signedWord(result); return result;
}
static bool valid(CRandomizer* p) {
    word(23); word(poolID(p)); bool result;
    if(input->family==TerminalInvalid || (input->family==ChoiceRetry&&attempts==1)) result=false;
    else {
        validPatch->restore();
        result=reinterpret_cast<bool(*)(CRandomizer*)>(ltgValid_original)(p);
        TL_REDIRECT(*validPatch,ltgValid,&valid); fatal(!validPatch->failed(),13);
    }
    word(result); return result;
}
static void odds(CRandomizer* p,int choice,int value) {
    word(24); word(poolID(p)); signedWord(choice); signedWord(value);
    if(!value) ++oddsZeroCalls;
    oddsPatch->restore();
    reinterpret_cast<void(*)(CRandomizer*,int,int)>(ltgOdds_original)(p,choice,value);
    TL_REDIRECT(*oddsPatch,ltgOdds,&odds); fatal(!oddsPatch->failed(),14);
}
static int add(CRandomizer* p,int choice,int value) {
    word(25); word(poolID(p)); signedWord(choice); signedWord(value); ++addCalls;
    need(p==owner->m_layoutRandomizer,15); nextObjectIsLayout=true;
    addPatch->restore();
    int result=reinterpret_cast<int(*)(CRandomizer*,int,int)>(ltgAdd_original)(p,choice,value);
    TL_REDIRECT(*addPatch,ltgAdd,&add); fatal(!addPatch->failed(),16);
    signedWord(result); return result;
}
static void reset(CLevelTemplateData* p) {
    need(p==owner,17); word(26); ++resetCalls;
    resetPatch->restore();
    reinterpret_cast<void(*)(CLevelTemplateData*)>(ltgReset_original)(p);
    TL_REDIRECT(*resetPatch,ltgReset,&reset); fatal(!resetPatch->failed(),18);
}
static bool rejectIntersection() {
    return (input->family==ExitReject||input->family==CapReject)&&attempts==1&&!(input->variant&4);
}
static bool intersects(CLevelTemplateData* p,CChunkInstance* q,std::vector<CChunkInstance*>& v) {
    need(p==owner,19); ++geometryCalls; word(30); peers(q,v); bool result;
    if(directional()||input->family==ControlledCorridor) result=rejectIntersection();
    else {
        intersectsPatch->restore();
        result=reinterpret_cast<bool(*)(CLevelTemplateData*,CChunkInstance*,std::vector<CChunkInstance*>&)>(ltgIntersects_original)(p,q,v);
        TL_REDIRECT(*intersectsPatch,ltgIntersects,&intersects); fatal(!intersectsPatch->failed(),20);
    }
    word(result); return result;
}
static bool exits(CLevelTemplateData* p,CChunkInstance* q,std::vector<CChunkInstance*>& v) {
    need(p==owner,21); word(31); peers(q,v); bool result;
    if(directional()||input->family==ControlledCorridor)
        result=!((input->family==ExitReject||input->family==CapReject)&&attempts==1&&(input->variant&4));
    else {
        exitsPatch->restore();
        result=reinterpret_cast<bool(*)(CLevelTemplateData*,CChunkInstance*,std::vector<CChunkInstance*>&)>(ltgExits_original)(p,q,v);
        TL_REDIRECT(*exitsPatch,ltgExits,&exits); fatal(!exitsPatch->failed(),22);
    }
    word(result); return result;
}
static void useAllExits(CChunkInstance* p) {
    CChunkType* type=owner->m_chunkTypes[p->m_chunkTypeIndex];
    for(unsigned i=0;i<type->m_exits.size();++i) p->m_usedExits.push_back(i);
}
static void match(CLevelTemplateData* p,CChunkInstance* q,std::vector<CChunkInstance*>& v) {
    need(p==owner,23); ++matchCalls; word(32); peers(q,v);
    if(directional()) {
        // Controlled geometry families close every peer exit deliberately. This
        // keeps dimensional/directional dispatch tests separate from geometry.
        useAllExits(q); for(unsigned i=0;i<v.size();++i) useAllExits(v[i]);
    } else {
        matchPatch->restore();
        reinterpret_cast<void(*)(CLevelTemplateData*,CChunkInstance*,std::vector<CChunkInstance*>&)>(ltgMatch_original)(p,q,v);
        TL_REDIRECT(*matchPatch,ltgMatch,&match); fatal(!matchPatch->failed(),24);
    }
    word(33); peers(q,v);
}
static void choice(CRandomizer& p,int id,int weight) {
    p.m_Choices.add(id); p.m_Odds.add(float(weight)); p.m_bOddsDirty=true;
}
static Ogre::Vector3 exitPoint(unsigned d,CChunkType* type) {
    float tile=owner->m_tileBasis;
    float width=owner->m_chunkWidthBasis*tile;
    float height=owner->m_chunkHeightBasis*tile;
    float middle=0.5f*type->m_height*height;
    if(d==0) return Ogre::Vector3(0,0,-0.5f*tile);
    if(d==1) return Ogre::Vector3(0,0,type->m_height*height-0.5f*tile);
    if(d==2) return Ogre::Vector3(0.5f*width,0,middle);
    return Ogre::Vector3(-0.5f*width,0,middle);
}
static unsigned opposite(unsigned d) { return d^1; }
static void makeSetup() {
    owner->m_requiresExit=input->family==ExitDirection||input->family==ExitReject||input->family==MissingExit||input->family==TerminalExit;
    owner->m_randomLayoutGenerated=(input->family==ExistingLayouts||input->family==NoEntrance) && (input->variant&1);
    owner->m_minChunks=owner->m_maxChunks=0;
    if(input->family==RealCorridor||input->family==ControlledCorridor) {
        owner->m_minChunks=input->variant&16?3:1;
        owner->m_maxChunks=input->variant&16?1:3;
    } else if(input->family==EmptySuccess) {
        owner->m_minChunks=input->variant&16?0:-2;
        owner->m_maxChunks=input->variant&16?-2:0;
    } else if(input->family==RequiredPresent||input->family==SkipSingle||input->family==SkipEmpty) {
        owner->m_minChunks=owner->m_maxChunks=1;
    } else if(input->family==AppearanceRetry) owner->m_maxChunks=2;
    else if(input->family==PlacementRetry) owner->m_maxChunks=1;
    owner->m_tileBasis=0.5f*float(1u<<(input->variant/4%4));
    owner->m_chunkWidthBasis=10.0f; owner->m_chunkHeightBasis=10.0f;
    owner->m_name=L"generator owner"; owner->m_levelName=L"generator level";
    owner->m_layoutRandomizer=new CRandomizer(RANDOMIZER_NORMAL);
    // Exact capacity six avoids invalid-but-in-capacity uninitialized pointers.
    owner->m_chunkTypes.setGrowBy(1); owner->m_chunks.setGrowBy(1); owner->m_chunkRandomizers.setGrowBy(1);
    for(unsigned i=0;i<6;++i) {
        CChunkType* t=new CChunkType;
        t->m_entranceChunk=i==0; t->m_exitChunk=i==2;
        t->m_registeredWithRandomizers=true; t->m_mustPlace=false;
        t->m_width=t->m_height=1; t->m_maxAppearance=100;
        if(directional()&&i==0) { t->m_width=2; t->m_height=3; }
        if(directional()&&i==2) { t->m_width=4; t->m_height=5; }
        t->m_folder=L"fixture/"; t->m_name=std::wstring(1,wchar_t(L'A'+i));
        t->m_inclusiveFiles.add(t->m_name+L".layout"); owner->m_chunkTypes.add(t);
        CChunk* ch=new CChunk;
        ch->m_chunkValue10=i; ch->m_odds=1+int(i); ch->m_maxAppearance=100;
        ch->m_filename=t->m_name+L".layout"; owner->m_chunks.add(ch);
        CRandomizer* r=new CRandomizer(RANDOMIZER_NORMAL);
        owner->m_chunkRandomizers.add(r);
        if(i!=3 || input->family!=SkipEmpty) choice(*r,input->family==AppearanceRetry?0:i,ch->m_odds);
    }
    if(input->family!=NoEntrance) choice(owner->m_entranceChunkRandomizer,0,1);
    choice(owner->m_generalChunkRandomizer,1,1);
    for(unsigned i=0;i<4;++i) { choice(pool(exitOffsets[i]),2,1); choice(pool(capOffsets[i]),2,1); }
    bool corridor=(input->family==PlacementRetry&&input->variant>=4)||input->family==RealCorridor||input->family==ControlledCorridor||input->family==RequiredPresent||input->family==AppearanceRetry||input->family==SkipSingle||input->family==SkipEmpty;
    if(corridor||directional()) owner->m_chunkTypes[0]->m_exits.add(exitPoint(direction(),owner->m_chunkTypes[0]));
    if(corridor) {
        owner->m_chunkTypes[1]->m_exits.add(exitPoint(opposite(direction()),owner->m_chunkTypes[1]));
        owner->m_chunkTypes[1]->m_exits.add(exitPoint(direction(),owner->m_chunkTypes[1]));
        owner->m_chunkTypes[2]->m_exits.add(exitPoint(opposite(direction()),owner->m_chunkTypes[2]));
        owner->m_chunkTypes[3]->m_exits.add(exitPoint(opposite(direction()),owner->m_chunkTypes[3]));
        owner->m_chunkTypes[3]->m_exits.add(exitPoint(direction(),owner->m_chunkTypes[3]));
        owner->m_chunkTypes[5]->m_exits.add(exitPoint(opposite(direction()),owner->m_chunkTypes[5]));
    }
    if(input->family==RequiredPresent) {
        owner->m_requiredChunkTypes.add(owner->m_chunkTypes[0]);
        owner->m_requiredChunkTypes.add(owner->m_chunkTypes[1]);
        owner->m_requiredChunkTypes.add(owner->m_chunkTypes[1]);
    }
    if(input->family==RequiredRetry||input->family==TerminalRequired)
        owner->m_requiredChunkTypes.add(owner->m_chunkTypes[4]);
    if(input->family==Appearance) {
        static const int maxima[]={0,1,2,-1}; owner->m_chunks[0]->m_maxAppearance=maxima[input->variant%4];
    }
    if(input->family==AppearanceRetry) owner->m_chunks[0]->m_maxAppearance=1;
    if(input->family==MissingExit) pool(exitOffsets[direction()]).m_Odds.m_nCount=0;
    if(input->family==MissingCap||input->family==TerminalCap) pool(capOffsets[direction()]).m_Odds.m_nCount=0;
    owner->m_layouts.setGrowBy(input->variant&1?1:3);
    initialLayouts=input->family==ExistingLayouts?(input->variant%4==3?10:input->variant%4):input->variant/8%2;
    for(unsigned i=0;i<initialLayouts;++i) {
        CLevelLayout* layout=new CLevelLayout; layout->m_seed=-100-int(i);
        CChunkInstance* ci=new CChunkInstance;
        ci->m_chunkTypeIndex=0; ci->m_name=L"preexisting";
        ci->m_x=100+i; ci->m_y=-3; ci->m_z=7; ci->m_usedExits.push_back(13);
        layout->m_chunkInstances.add(ci); layout->m_chunks.add(owner->m_chunks[0]);
        owner->m_layouts.add(layout); owner->m_baseLayouts.add(layout);
        choice(*owner->m_layoutRandomizer,i,7+i);
    }
}
static void randomSnapshot(CRandomizer& r) {
    word(r.m_Choices.size()); word(r.m_Choices.m_nCapacity); word(r.m_Choices.m_nGrowBy);
    for(unsigned i=0;i<r.m_Choices.size();++i) signedWord(r.m_Choices[i]);
    word(r.m_Odds.size()); word(r.m_Odds.m_nCapacity); word(r.m_Odds.m_nGrowBy);
    for(unsigned i=0;i<r.m_Odds.size();++i) capture->add(&r.m_Odds[i],4);
    word(r.m_ComputedOdds.size()); word(r.m_ComputedOdds.m_nCapacity); word(r.m_ComputedOdds.m_nGrowBy);
    for(unsigned i=0;i<r.m_ComputedOdds.size();++i) capture->add(&r.m_ComputedOdds[i],4);
    signedWord(r.m_eType); capture->add(&r.m_fDecay,4); word(r.m_bOddsDirty);
}
static unsigned chunkID(CChunk* p) {
    for(unsigned i=0;i<owner->m_chunks.size();++i) if(owner->m_chunks[i]==p) return i;
    need(false,25); return ~0u;
}
static void snapshot() {
    word(40); word(owner->m_randomLayoutGenerated); word(owner->m_requiresExit);
    signedWord(owner->m_minChunks); signedWord(owner->m_maxChunks);
    capture->add(&owner->m_tileBasis,12); capture->addText(owner->m_name); capture->addText(owner->m_levelName);
    word(owner->m_layouts.size()); word(owner->m_layouts.m_nCapacity); word(owner->m_layouts.m_nGrowBy);
    for(unsigned i=0;i<owner->m_layouts.size();++i) {
        CLevelLayout* l=owner->m_layouts[i]; signedWord(l->m_seed);
        word(i<initialLayouts?0x10000+i:objectID(l));
        word(l->m_chunks.size()); word(l->m_chunks.m_nCapacity); word(l->m_chunks.m_nGrowBy);
        for(unsigned j=0;j<l->m_chunks.size();++j) word(chunkID(l->m_chunks[j]));
        word(l->m_chunkInstances.size()); word(l->m_chunkInstances.m_nCapacity); word(l->m_chunkInstances.m_nGrowBy);
        for(unsigned j=0;j<l->m_chunkInstances.size();++j) {
            CChunkInstance* ci=l->m_chunkInstances[j];
            if(i>=initialLayouts) instance(ci);
            else { signedWord(ci->m_chunkTypeIndex); capture->addText(ci->m_name); capture->add(&ci->m_x,12); word(ci->m_usedExits.size()); for(unsigned k=0;k<ci->m_usedExits.size();++k) signedWord(ci->m_usedExits[k]); }
        }
    }
    word(owner->m_baseLayouts.size());
    for(unsigned i=0;i<owner->m_baseLayouts.size();++i) need(owner->m_baseLayouts[i]==owner->m_layouts[i],26);
    for(unsigned i=0;i<10;++i) randomSnapshot(pool(0x108+i*0x68));
    randomSnapshot(*owner->m_layoutRandomizer);
    for(unsigned i=0;i<owner->m_chunkRandomizers.size();++i) randomSnapshot(*owner->m_chunkRandomizers[i]);
    for(unsigned i=0;i<owner->m_chunkTypes.size();++i) {
        CChunkType* t=owner->m_chunkTypes[i]; capture->add(&t->m_entranceChunk,4);
        signedWord(t->m_width); signedWord(t->m_height); signedWord(t->m_maxAppearance);
        capture->addText(t->m_folder); capture->addText(t->m_name); word(t->m_exits.size());
        for(unsigned j=0;j<t->m_exits.size();++j) capture->add(&t->m_exits[j],12);
        CChunk* ch=owner->m_chunks[i]; signedWord(ch->m_chunkValue10); signedWord(ch->m_odds); signedWord(ch->m_maxAppearance); capture->addText(ch->m_filename);
    }
}
static void semanticChecks(int result,int seed) {
    unsigned f=input->family;
    bool retry=f==RequiredRetry||f==ChoiceRetry||f==AppearanceRetry||f==PlacementRetry||f==ExitReject||f==CapReject||f==MissingExit||f==MissingCap;
    unsigned expectedAttempts=f==NoEntrance?0:terminal()?1000:retry?2:1;
    if(f==PlacementRetry&&input->variant==4) expectedAttempts=1;
    need(attempts==expectedAttempts,30);
    need(result==(f==NoEntrance?0:seed),31);
    need(seedCalls==(f!=NoEntrance&&seed!=0?1u:0u),32);
    need(owner->m_randomLayoutGenerated==(f==NoEntrance?bool(input->variant&1):true),33);
    need(addCalls==(f==NoEntrance||terminal()?0u:1u),34);
    need(owner->m_layouts.size()==initialLayouts+addCalls,35);
    unsigned expectedResets=expectedAttempts;
    if(f==NoEntrance||f==TerminalExit) expectedResets=0;
    if(f==PlacementRetry||f==ExitReject||f==MissingExit) expectedResets=1;
    need(resetCalls==expectedResets,36);
    if(f==RealCorridor||f==ControlledCorridor) need(geometryCalls&&matchCalls,37);
    if(f==SkipSingle||f==SkipEmpty) need(generalCalls==2,38);
    if(f==Appearance) need(oddsZeroCalls==(input->variant%4<2?1u:0u),39);
    if(f==AppearanceRetry) need(oddsZeroCalls==3,40);
    if(f==ExitDirection||f==ExitReject||f==MissingExit)
        need((directionalMask&(1u<<direction()))!=0,41);
    if(f==CapDirection||f==CapReject||f==MissingCap)
        need((directionalMask&(1u<<(4+direction())))!=0,42);
    if(directional()&&!terminal()&&addCalls==1) {
        CLevelLayout* layout=owner->m_layouts[initialLayouts];
        need(layout->m_chunkInstances.size()==2,48);
        if(layout->m_chunkInstances.size()==2) {
            CChunkInstance* placed=layout->m_chunkInstances[1];
            // Negative directions use the entrance dimensions (2 x 3).
            // Positive directions use the selected new dimensions (4 x 5).
            float expectedX=0.0f, expectedZ=0.0f;
            if(direction()==0) expectedZ=-3.0f*owner->m_tileBasis*owner->m_chunkHeightBasis;
            if(direction()==1) expectedZ=5.0f*owner->m_tileBasis*owner->m_chunkHeightBasis;
            if(direction()==2) expectedX=4.0f*owner->m_tileBasis*owner->m_chunkWidthBasis;
            if(direction()==3) expectedX=-2.0f*owner->m_tileBasis*owner->m_chunkWidthBasis;
            need(placed->m_x==expectedX&&placed->m_y==0.0f&&placed->m_z==expectedZ,49);
        }
    }
    unsigned live=0;
    for(unsigned i=0;i<objectCount;++i) if(!objects[i].destroyed) ++live;
    unsigned stored=0;
    for(unsigned i=initialLayouts;i<owner->m_layouts.size();++i) stored+=1+owner->m_layouts[i]->m_chunkInstances.size();
    need(live==stored,43);
}
static void side(Case& c,bool ours,autotest::Capture& out) {
    input=&c; capture=&out;
    errors=attempts=generalCalls=integerCalls=seedCalls=resetCalls=addCalls=oddsZeroCalls=geometryCalls=matchCalls=directionalMask=concreteMask=objectCount=initialLayouts=0;
    active=targetPending=nextObjectIsLayout=false;
    // Original TU globals have not run at the headless pre-main boundary.
    new(reinterpret_cast<void*>(0x1495cc8))std::wstring();
    union Storage { long double align; unsigned char bytes[0x778]; } storage;
    std::memset(storage.bytes,0xa5,sizeof(storage.bytes));
    ltgOwnerConstruct(storage.bytes,0); owner=reinterpret_cast<CLevelTemplateData*>(storage.bytes);
    makeSetup();
    TSafePointer<CRunicCore> initialWitnesses[24]; unsigned initialWitnessCount=0;
    for(unsigned i=0;i<initialLayouts;++i) {
        initialWitnesses[initialWitnessCount++].setObject(owner->m_layouts[i]);
        initialWitnesses[initialWitnessCount++].setObject(owner->m_layouts[i]->m_chunkInstances[0]);
    }
    detour::Set rng,valids,oddsSet,adds,resets,intersections,exitTests,matches,constructors,destructors,frees;
    validPatch=&valids; oddsPatch=&oddsSet; addPatch=&adds; resetPatch=&resets;
    intersectsPatch=&intersections; exitsPatch=&exitTests; matchPatch=&matches;
    ctorPatch=&constructors; dtorPatch=&destructors; freePatch=&frees;
    TL_REDIRECT(rng,ltgRandom,&random); TL_REDIRECT(rng,ltgInteger,&integer); TL_REDIRECT(rng,ltgSeed,&setSeed);
    TL_REDIRECT(valids,ltgValid,&valid); TL_REDIRECT(oddsSet,ltgOdds,&odds); TL_REDIRECT(adds,ltgAdd,&add); TL_REDIRECT(resets,ltgReset,&reset);
    TL_REDIRECT(intersections,ltgIntersects,&intersects); TL_REDIRECT(exitTests,ltgExits,&exits); TL_REDIRECT(matches,ltgMatch,&match);
    TL_REDIRECT(constructors,ltgCoreCtor1,&coreConstruct); TL_REDIRECT(constructors,ltgCoreCtor2,&coreConstruct);
    TL_REDIRECT(destructors,ltgCoreDtor1,&coreDestroy); TL_REDIRECT(destructors,ltgCoreDtor2,&coreDestroy);
    frees.redirect(ltgFree,ltgFree,&objectFree);
    fatal(!rng.failed()&&!valids.failed()&&!oddsSet.failed()&&!adds.failed()&&!resets.failed()&&!intersections.failed()&&!exitTests.failed()&&!matches.failed()&&!constructors.failed()&&!destructors.failed()&&!frees.failed(),44);
    int seed=seedValue(c.variant); int (*fn)(CLevelTemplateData*,int)=ours?ltgCandidate:ltgOriginal;
    feclearexcept(FE_ALL_EXCEPT); active=true;
    if(!autotest::beginInvocation(out,fn)) return;
    int result=fn(owner,seed); out.callCompleted=1;
    word(50); signedWord(result); signedWord(fetestexcept(FE_ALL_EXCEPT));
    semanticChecks(result,seed); snapshot();
    for(unsigned i=0;i<initialWitnessCount;++i) need(initialWitnesses[i].getObject()!=0,45);
    // The original owning destructor checks transferred objects and retained
    // layouts too; no fixture-owned generated object is manually deleted.
    ltgOwnerDestroy(owner);
    for(unsigned i=0;i<initialWitnessCount;++i) need(initialWitnesses[i].getObject()==0,46);
    for(unsigned i=0;i<objectCount;++i) { need(objects[i].destroyed==1&&objects[i].freed==1,47); }
    active=false;
    word(attempts); word(integerCalls); word(seedCalls); word(resetCalls); word(addCalls);
    word(oddsZeroCalls); word(geometryCalls); word(matchCalls); word(directionalMask); word(concreteMask); word(objectCount);
    word(0x4c544747); word(errors);
}
static void original(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),false,out); }
static void recovered(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),true,out); }
static bool good(const autotest::Outcome& o) {
    unsigned tail[2]={0,1}; if(o.capture.length>=8) std::memcpy(tail,o.capture.data+o.capture.length-8,8);
    return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x4c544747&&!tail[1];
}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c) {
    autotest::Outcome a,b; autotest::runChild(original,&c,a); autotest::runChild(recovered,&c,b);
    bool different=coverage.observe(host,a,b);
    if(!different&&good(a)&&good(b)) return true;
    host->log("tlhybrid: generator family=%u variant=%u status=%d/%d good=%u/%u bytes=%lu/%lu\n",c.family,c.variant,a.childStatus,b.childStatus,unsigned(good(a)),unsigned(good(b)),(unsigned long)a.capture.length,(unsigned long)b.capture.length);
    for(size_t i=0;i<a.capture.length&&i<b.capture.length;++i) if(a.capture.data[i]!=b.capture.data[i]) { host->log("tlhybrid: generator first byte %lu: %u/%u\n",(unsigned long)i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]); break; }
    for(unsigned side=0;side<2;++side) {
        const autotest::Capture& result=side?b.capture:a.capture;
        for(size_t i=0;i+4<=result.length;i+=4) {
            unsigned value; std::memcpy(&value,result.data+i,4);
            if((value&0xffff0000u)==0xf7000000u) host->log("tlhybrid: generator side %u semantic check %u at %lu\n",side,value-0xf7000000u,(unsigned long)i);
        }
    }
    return false;
}
}
TL_TEST(level_template_create_random_layout) {
    using namespace level_template_generator;
    autotest::Coverage coverage("level_template_create_random_layout",0x973370);
    for(unsigned family=0;family<20;++family) for(unsigned variant=0;variant<(family==PlacementRetry?6u:56u);++variant) {
        Case c={family,variant}; if(!pair(host,coverage,c)) { coverage.report(host); return 1; }
    }
    // Terminal outer exhaustion is deliberately cheap: zero placement attempts.
    // Never combine it with 1000 failed inner placements or an early-skip loop.
    for(unsigned family=20;family<24;++family) {
        Case c={family,family-20}; if(!pair(host,coverage,c)) { coverage.report(host); return 1; }
    }
    coverage.report(host);
    return coverage.completed!=1074 || coverage.different || coverage.missing;
}
