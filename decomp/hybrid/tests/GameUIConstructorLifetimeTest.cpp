// C1/C2 are aliases of one 2158-byte function at 0xaa6380. The oracle below
// is transcribed from ELF stores, NOT from the candidate initializer list.
// Real base/manager/string constructors establish member lifetimes. Retained
// old-ABI string aliases witness reference release independently of libstdc++
// internal allocator binding; allocator events cover owner container buffers.
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <new>
#include <string>
#include <vector>
#include "GameUI.h"
#include "GameUITextEventList.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#include "AutoTest.h"
#include "Detour.h"

#define UI_C1 "_ZN7CGameUIC1ER9CSettingsR11CGameClientPvPN4Ogre12RenderWindowEPNS5_6CameraEPNS5_12SceneManagerESB_SB_P16CResourceManager"
#define UI_C2 "_ZN7CGameUIC2ER9CSettingsR11CGameClientPvPN4Ogre12RenderWindowEPNS5_6CameraEPNS5_12SceneManagerESB_SB_P16CResourceManager"
#define UI_ARGS (CGameUI*,CSettings&,CGameClient&,void*,Ogre::RenderWindow*,Ogre::Camera*,Ogre::SceneManager*,Ogre::SceneManager*,Ogre::SceneManager*,CResourceManager*)
TL_ORIGINAL(void, originalGameUIConstructor, UI_ARGS, UI_C1)
TL_ORIGINAL(void, originalGameUIBaseConstructor, UI_ARGS, UI_C2)
extern "C" void candidateGameUIConstructor UI_ARGS __asm__(UI_C1);
extern "C" void candidateGameUIBaseConstructor UI_ARGS __asm__(UI_C2);
TL_ORIGINAL(void, cleanupGameUI, (CGameUI*), "_ZN7CGameUID1Ev")
TL_FUNCTION(coreCtor, "_ZN10CRunicCoreC1Ev")
TL_FUNCTION(coreDtor, "_ZN10CRunicCoreD2Ev")
TL_FUNCTION(keyCtor, "_ZN11CKeyManagerC1Ev")
TL_FUNCTION(keyDtor, "_ZN11CKeyManagerD1Ev")
TL_FUNCTION(mouseCtor, "_ZN13CMouseManagerC1Ev")
TL_FUNCTION(mouseDtor, "_ZN13CMouseManagerD1Ev")
TL_FUNCTION(masterGetter, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(createUI, "_ZN7CGameUI6createEv")
TL_FUNCTION(ownerDtor, "_ZN7CGameUID1Ev")
extern "C" char literalStringCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");
extern "C" char copyStringCtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char keyboardState[] __asm__("SDL_GetKeyboardState");
extern "C" char setCursor[] __asm__("SDL_SetCursor");
extern "C" char freeCursor[] __asm__("SDL_FreeCursor");
extern "C" char scalarNew[] __asm__("_Znwm");
extern "C" char arrayNew[] __asm__("_Znam");
extern "C" char scalarDelete[] __asm__("_ZdlPv");
extern "C" char arrayDelete[] __asm__("_ZdaPv");
extern "C" char ogreFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");

namespace gameui_constructor_lifetime {
typedef std::wstring Wide;
template<class T> T& field(void* p,unsigned off) { return *reinterpret_cast<T*>(static_cast<unsigned char*>(p)+off); }
template<class T> struct Ref { T* p; explicit Ref(T* v):p(v){} operator T&() const { return *p; } };
struct Stop {};
struct Case { unsigned poison, existing, createResult, text, alias, fault, negative; };
struct Store { unsigned stage, offset, width; unsigned long long value; unsigned argument; };
static const Store stores[] = {
    {2, 0x10, 8, 0, 1},
    {2, 0x18, 8, 0, 2},
    {2, 0x20, 8, 0, 3},
    {2, 0x28, 8, 0, 4},
    {3, 0x38, 8, 0x0ULL, 0},
    {3, 0x40, 8, 0x0ULL, 0},
    {3, 0x48, 8, 0x0ULL, 0},
    {3, 0x50, 4, 0xffffffffULL, 0},
    {3, 0x58, 8, 0x0ULL, 0},
    {3, 0x30, 8, 0, 5},
    {3, 0x60, 4, 0xffffffffULL, 0},
    {3, 0x68, 8, 0x0ULL, 0},
    {3, 0x70, 4, 0xffffffffULL, 0},
    {3, 0x78, 8, 0, 6},
    {3, 0x80, 8, 0x0ULL, 0},
    {3, 0x88, 4, 0xffffffffULL, 0},
    {3, 0x90, 8, 0x0ULL, 0},
    {3, 0x98, 4, 0xffffffffULL, 0},
    {3, 0xa0, 8, 0x0ULL, 0},
    {3, 0xa8, 4, 0xffffffffULL, 0},
    {3, 0xb0, 8, 0xffffffffffffffffULL, 0},
    {3, 0xb8, 8, 0x0ULL, 0},
    {3, 0xc0, 4, 0xffffffffULL, 0},
    {3, 0xc8, 8, 0x0ULL, 0},
    {3, 0xd0, 4, 0xffffffffULL, 0},
    {3, 0xe0, 8, 0x0ULL, 0},
    {3, 0xe8, 8, 0x0ULL, 0},
    {3, 0xf0, 8, 0x0ULL, 0},
    {3, 0xf8, 8, 0x0ULL, 0},
    {3, 0x120, 8, 0x0ULL, 0},
    {3, 0x128, 8, 0x0ULL, 0},
    {3, 0x138, 8, 0x0ULL, 0},
    {3, 0x140, 8, 0x0ULL, 0},
    {3, 0x158, 8, 0x0ULL, 0},
    {3, 0x170, 8, 0x0ULL, 0},
    {3, 0x180, 8, 0x0ULL, 0},
    {3, 0x190, 8, 0x0ULL, 0},
    {3, 0x1d0, 8, 0x0ULL, 0},
    {3, 0x228, 8, 0xffffffffffffffffULL, 0},
    {3, 0x230, 8, 0x0ULL, 0},
    {3, 0x258, 8, 0x0ULL, 0},
    {3, 0x428, 8, 0x0ULL, 0},
    {3, 0x430, 8, 0x0ULL, 0},
    {3, 0x440, 8, 0x0ULL, 0},
    {3, 0x448, 4, 0x0ULL, 0},
    {3, 0x44c, 4, 0x0ULL, 0},
    {3, 0x450, 4, 0x19ULL, 0},
    {3, 0x458, 8, 0x0ULL, 0},
    {3, 0x460, 4, 0x0ULL, 0},
    {3, 0x464, 4, 0x0ULL, 0},
    {3, 0x468, 4, 0x5ULL, 0},
    {3, 0x4a0, 8, 0x0ULL, 0},
    {3, 0x4a8, 8, 0x0ULL, 0},
    {3, 0x4b0, 8, 0x0ULL, 0},
    {3, 0x4b8, 8, 0x0ULL, 0},
    {3, 0x4d0, 8, 0, 7},
    {3, 0x4d8, 8, 0x0ULL, 0},
    {3, 0x4e0, 8, 0x0ULL, 0},
    {3, 0x4e8, 8, 0x0ULL, 0},
    {3, 0x4f0, 8, 0x0ULL, 0},
    {3, 0x4f8, 8, 0x0ULL, 0},
    {3, 0x500, 8, 0x0ULL, 0},
    {3, 0x508, 8, 0x0ULL, 0},
    {3, 0x510, 8, 0x0ULL, 0},
    {3, 0x518, 8, 0x0ULL, 0},
    {3, 0x520, 8, 0x0ULL, 0},
    {3, 0x528, 8, 0x0ULL, 0},
    {3, 0x530, 8, 0x0ULL, 0},
    {3, 0x538, 8, 0x0ULL, 0},
    {3, 0x540, 8, 0x0ULL, 0},
    {3, 0x548, 8, 0x0ULL, 0},
    {3, 0x550, 8, 0x0ULL, 0},
    {3, 0x558, 8, 0x0ULL, 0},
    {3, 0x560, 8, 0x0ULL, 0},
    {3, 0x568, 8, 0x0ULL, 0},
    {3, 0x570, 8, 0x0ULL, 0},
    {3, 0x578, 8, 0x0ULL, 0},
    {3, 0x580, 8, 0x0ULL, 0},
    {3, 0x588, 8, 0x0ULL, 0},
    {5, 0x12f8, 1, 0x0ULL, 0},
    {5, 0x12f9, 1, 0x0ULL, 0},
    {5, 0x12fa, 1, 0x0ULL, 0},
    {5, 0x12fb, 1, 0x0ULL, 0},
    {5, 0x12fc, 4, 0x5ULL, 0},
    {5, 0x1300, 8, 0, 8},
    {5, 0x1308, 8, 0, 9},
    {5, 0x1640, 1, 0x0ULL, 0},
    {5, 0x1641, 1, 0x0ULL, 0},
    {5, 0x1642, 1, 0x0ULL, 0},
    {5, 0x1643, 1, 0x0ULL, 0},
    {5, 0x1648, 8, 0xffffffffffffffffULL, 0},
    {5, 0x1650, 8, 0xffffffffffffffffULL, 0},
    {5, 0x1660, 1, 0x0ULL, 0},
    {5, 0x1668, 8, 0xffffffffffffffffULL, 0},
    {5, 0x1670, 1, 0x0ULL, 0},
    {5, 0x1674, 4, 0xffffffffULL, 0},
    {5, 0x1678, 4, 0xffffffffULL, 0},
    {5, 0x167c, 4, 0xffffffffULL, 0},
    {5, 0x1680, 4, 0x3f800000ULL, 0},
    {5, 0x1684, 4, 0x44480000ULL, 0},
    {5, 0x1688, 4, 0x44160000ULL, 0},
    {5, 0x1690, 8, 0x0ULL, 0},
    {5, 0x1698, 8, 0x0ULL, 0},
    {5, 0x16a0, 8, 0x0ULL, 0},
    {7, 0x16c8, 4, 0x1ULL, 0},
    {7, 0x178c, 4, 0x0ULL, 0},
    {7, 0x1914, 4, 0x6ULL, 0},
    {7, 0x1918, 4, 0x6ULL, 0},
    {7, 0x1920, 8, 0, 10},
    {7, 0x1930, 8, 0x0ULL, 0},
    {7, 0x1938, 8, 0x0ULL, 0},
    {7, 0x1940, 8, 0x0ULL, 0},
    {7, 0x1948, 8, 0x0ULL, 0},
    {7, 0x1950, 8, 0x0ULL, 0},
    {7, 0x1958, 8, 0x0ULL, 0},
    {7, 0x1960, 8, 0x0ULL, 0},
    {7, 0x1968, 8, 0x0ULL, 0},
    {7, 0x1970, 8, 0x0ULL, 0},
    {8, 0x1980, 4, 0x0ULL, 0},
    {8, 0x1984, 4, 0x0ULL, 0},
    {9, 0x1990, 4, 0x0ULL, 0},
    {9, 0x1994, 4, 0x0ULL, 0},
    {9, 0x1999, 1, 0x0ULL, 0},
    {9, 0x19f0, 8, 0x0ULL, 0},
    {9, 0x19f8, 8, 0x0ULL, 0},
    {9, 0x1a00, 8, 0x0ULL, 0},
};
static Case current;
static autotest::Capture* capture;
static CGameUI* owner;
static unsigned char* bytes;
static unsigned long long ownerMemory[(0x1a08+7)/8], arguments[12][64], keeperMemory[4];
static Wide* keepers[4];
static bool retained[4];
static unsigned oracleErrors;
static unsigned lastStage, negativeHits, keyDestructions, mouseDestructions, coreDestructions;
static unsigned cursorFrees, shellFrees, initialObjects, coreOrder[8], coreOrderCount;
static bool constructing, trackBuffers;
static void* shells[2];
static unsigned char keys[512];
static detour::Set *corePatch,*keyPatch,*mousePatch,*coreDestroyPatch,*keyDestroyPatch,*mouseDestroyPatch,*literalPatch,*copyPatch;
struct Allocation { void* pointer; size_t size; unsigned kind; bool freed; };
static Allocation allocations[32];
static unsigned allocationCount, releaseCount, releaseOrder[32];
static CGameUI*& singleton() { return *reinterpret_cast<CGameUI**>(0x14b9c68); }
static Wide& emptyConstant() { return *reinterpret_cast<Wide*>(0x14b7d08); }
static int& objectCount() { return *reinterpret_cast<int*>(0x150b420); }
static unsigned* targetKeys() { return reinterpret_cast<unsigned*>(0x14b9c40); }
static unsigned* targetFunctions() { return reinterpret_cast<unsigned*>(0x14b9b80); }
static unsigned* sourceKeys() { return reinterpret_cast<unsigned*>(0x150b59c); }
static unsigned* sourceFunctions() { return reinterpret_cast<unsigned*>(0x150b5c4); }
static void n(unsigned value) { capture->add(&value,sizeof(value)); }
static void need(bool good,unsigned code) { if (!good) { n(0xf0000000u+code); ++oracleErrors; } }
static unsigned offset(void* p) { return reinterpret_cast<uintptr_t>(p)-reinterpret_cast<uintptr_t>(bytes); }
static int refs(const Wide& s) { return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8); }
static void write(unsigned char* p,unsigned off,unsigned width,unsigned long long value) { std::memcpy(p+off,&value,width); }
static unsigned long long argument(unsigned id) {
    // The ABI argument positions are deliberately unrelated to member names.
    static const unsigned which[]={0,4,5,6,7,10,0,3,2,8,1};
    return reinterpret_cast<uintptr_t>(arguments[which[id]]);
}
static void expected(unsigned stage,unsigned char* result) {
    std::memset(result,current.poison?0x5a:0xa5,0x1a08);
    if(stage>=2) { write(result,0,8,0xfe5cb0);write(result,8,8,0); }
    for(unsigned i=0;i<sizeof(stores)/sizeof(stores[0]);++i) {
        const Store& s=stores[i];
        if(s.stage<=stage)write(result,s.offset,s.width,s.argument?argument(s.argument):s.value);
    }
    if(stage>=4) {
        write(result,0x590,8,0xfd4870);write(result,0x598,8,0);
        write(result,0x5a0,1,current.poison?1:0);
        std::memset(result+0x590+0x711,0,0x200);
        std::memset(result+0x590+0x911,0,0x200);
        std::memset(result+0x590+0xb11,0,0x200);
    }
    if(stage>=5) {
        write(result,0x12a8,8,0xfd4910);write(result,0x12b0,8,0);
        std::memset(result+0x12a8+0x19,0,9);
        std::memset(result+0x12a8+0x48,0,8);
    }
    const unsigned positions[]={0x16b0,0x16b8,0x16c0,0x1978,0x1988};
    const unsigned available[]={6,7,7,8,9};
    for(unsigned i=0;i<5;++i)if(stage>=available[i])write(result,positions[i],8,0);
    if(stage==9)for(unsigned i=0;i<97;++i)write(result,0x1790+4*i,4,i);
}
static void boundary(unsigned stage) {
    need(stage==lastStage+1,10+stage);lastStage=stage;n(stage);
    unsigned char want[0x1a08],actual[0x1a08];expected(stage,want);std::memcpy(actual,bytes,sizeof(actual));
    const unsigned positions[]={0x16b0,0x16b8,0x16c0,0x1978,0x1988};
    const unsigned available[]={6,7,7,8,9};
    for(unsigned i=0;i<5;++i)if(stage>=available[i]) {
        const Wide& s=field<Wide>(owner,positions[i]);
        const wchar_t* value=i==0?L"Rourke":i==1?L"Spot":i==2?L"":current.text?L"constant-copy-probe":L"";
        need(s==value,30+i);capture->addText(s);write(actual,positions[i],8,0);
    }
    unsigned negativeOffset=0;
    if(current.negative==1&&stage==3)negativeOffset=0xe8; // a pre-key null store moved to the body
    if(current.negative==2&&stage==7)negativeOffset=0x178c; // user count moved late
    if(current.negative==3&&stage==7)negativeOffset=0x1790; // body-only array initialized early
    if(negativeOffset) {
        actual[negativeOffset]=current.negative==3?0:(current.poison?0x5a:0xa5);
        need(std::memcmp(actual,want,sizeof(actual))!=0,50+current.negative);++negativeHits;
        // Synthetic oracle negative control, not candidate source mutation.
        actual[negativeOffset]=want[negativeOffset];
    }
    if(std::memcmp(actual,want,sizeof(actual))) {
        unsigned first=0;while(first<sizeof(actual)&&actual[first]==want[first])++first;
        n(0xba000000u|first);n(first<sizeof(actual)?actual[first]:0);n(first<sizeof(actual)?want[first]:0);
        need(false,60+stage);
    }
    capture->add(actual,sizeof(actual));
    need(objectCount()-int(initialObjects)==(stage==1?0:stage<=3?1:stage==4?2:3),80+stage);
    CGameUI* selected=current.existing?reinterpret_cast<CGameUI*>(arguments[11]):stage==9?owner:0;
    need(singleton()==selected,90+stage);n(singleton()==owner?1:singleton()?2:0);
    for(unsigned i=0;i<10;++i)need(targetKeys()[i]==(stage==9?sourceKeys()[i]:0xcafe0000u+i),110+i);
    for(unsigned i=0;i<12;++i)need(targetFunctions()[i]==(stage==9?sourceFunctions()[i]:0xbeef0000u+i),130+i);
}
static void core(CRunicCore* p) {
    if(p==static_cast<CRunicCore*>(owner)) { boundary(1);if(current.fault==1)throw Stop(); }
    n(200);n(offset(p));corePatch->restore();
    reinterpret_cast<void(*)(CRunicCore*)>(coreCtor_original)(p);
    TL_REDIRECT(*corePatch,coreCtor,&core);need(!corePatch->failed(),150);
}
static CMasterResourceManager* master() {
    boundary(2);if(current.fault==2)throw Stop();
    return reinterpret_cast<CMasterResourceManager*>(arguments[9]);
}
static const unsigned char* keyboard(int* count) {
    need(count==0,151);n(201);if(current.fault==3)throw Stop();return keys;
}
static void key(CKeyManager* p) {
    need(offset(p)==0x590,152);boundary(3);keyPatch->restore();
    try { reinterpret_cast<void(*)(CKeyManager*)>(keyCtor_original)(p); }
    catch(...) { TL_REDIRECT(*keyPatch,keyCtor,&key);throw; }
    TL_REDIRECT(*keyPatch,keyCtor,&key);need(!keyPatch->failed(),153);
}
static void mouse(CMouseManager* p) {
    need(offset(p)==0x12a8,154);boundary(4);
    // Failure before this constructor's base starts: original mouse ctor has
    // a tail-call to flushAll and no fabricated member-cleanup landing pad.
    if(current.fault==4)throw Stop();
    mousePatch->restore();reinterpret_cast<void(*)(CMouseManager*)>(mouseCtor_original)(p);
    TL_REDIRECT(*mousePatch,mouseCtor,&mouse);need(!mousePatch->failed(),155);
}
static void destroyCore(CRunicCore* p) {
    unsigned off=offset(p);n(210);n(off);need(coreOrderCount<8,156);
    if(coreOrderCount<8)coreOrder[coreOrderCount++]=off;++coreDestructions;
    coreDestroyPatch->restore();reinterpret_cast<void(*)(CRunicCore*)>(coreDtor_original)(p);
    TL_REDIRECT(*coreDestroyPatch,coreDtor,&destroyCore);need(!coreDestroyPatch->failed(),157);
}
static void destroyKey(CKeyManager* p) {
    n(211);need(offset(p)==0x590,158);++keyDestructions;keyDestroyPatch->restore();
    reinterpret_cast<void(*)(CKeyManager*)>(keyDtor_original)(p);
    TL_REDIRECT(*keyDestroyPatch,keyDtor,&destroyKey);need(!keyDestroyPatch->failed(),159);
}
static void destroyMouse(CMouseManager* p) {
    n(212);need(offset(p)==0x12a8,160);++mouseDestructions;mouseDestroyPatch->restore();
    reinterpret_cast<void(*)(CMouseManager*)>(mouseDtor_original)(p);
    TL_REDIRECT(*mouseDestroyPatch,mouseDtor,&destroyMouse);need(!mouseDestroyPatch->failed(),161);
}
static void retain(Wide* p,unsigned index) {
    need(!retained[index],170+index);
    // const copy shares a real old-ABI representation. The keeper prevents a
    // free, allowing exact reference-release checks after owner unwind.
    keepers[index]=new(&keeperMemory[index])Wide(*p);retained[index]=true;
    if(!p->empty())need(refs(*p)==1,180+index);
}
static void literal(Wide* p,const wchar_t* text,const std::allocator<wchar_t>& allocator) {
    unsigned off=offset(p),stage=off==0x16b0?5:off==0x16b8?6:0;
    need(stage!=0,190);boundary(stage);need(!std::wcscmp(text,stage==5?L"Rourke":L"Spot"),191);
    if(current.fault==stage)throw Stop();
    literalPatch->restore();
    reinterpret_cast<void(*)(Wide*,const wchar_t*,const std::allocator<wchar_t>&)>(literalStringCtor)(p,text,allocator);
    literalPatch->redirect(literalStringCtor,literalStringCtor,&literal);need(!literalPatch->failed(),194);
    retain(p,stage-5);
}
static void copy(Wide* p,const Wide& source) {
    unsigned off=offset(p),stage=off==0x1978?7:off==0x1988?8:0;
    if(stage) { boundary(stage);need(&source==&emptyConstant(),192);if(current.fault==stage)throw Stop(); }
    copyPatch->restore();reinterpret_cast<void(*)(Wide*,const Wide&)>(copyStringCtor)(p,source);
    copyPatch->redirect(copyStringCtor,copyStringCtor,&copy);need(!copyPatch->failed(),193);
    if(stage)retain(p,stage-5);
}
static void* allocate(size_t size,unsigned kind) {
    void* p=std::malloc(size?size:1);if(!p)throw std::bad_alloc();
    if(trackBuffers) {
        need(allocationCount<32,200);if(allocationCount>=32)_exit(81);
        Allocation& a=allocations[allocationCount++];a.pointer=p;a.size=size;a.kind=kind;a.freed=false;
        n(220);n(allocationCount);n(kind);n(size);
    }
    return p;
}
static void* allocateScalar(size_t size) { return allocate(size,1); }
static void* allocateArray(size_t size) { return allocate(size,2); }
static void release(void* p,unsigned kind) {
    if(!p)return;
    bool found=false;
    // Reused addresses are searched newest-first; IDs remain allocation IDs.
    for(unsigned i=allocationCount;i;--i)if(allocations[i-1].pointer==p&&!allocations[i-1].freed) {
        Allocation& a=allocations[i-1];need(a.kind==kind,201);a.freed=true;found=true;
        need(releaseCount<32,202);if(releaseCount<32)releaseOrder[releaseCount++]=i;
        n(221);n(i);n(kind);break;
    }
    if(trackBuffers)need(found,203);
    std::free(p);
}
static void releaseScalar(void* p) { release(p,1); }
static void releaseArray(void* p) { release(p,2); }
static void releaseOgre(void* p) {
    need(!constructing,204);
    bool found=false;for(unsigned i=0;i<2;++i)if(shells[i]==p){shells[i]=0;found=true;++shellFrees;}
    need(found,205);n(222);std::free(p);
}
static void cursorSet(void* p) { need(!constructing&&p==0,206);n(223); }
static void cursorFree(void* p) {
    need(!constructing,207);need(p==arguments[cursorFrees],208);++cursorFrees;n(224);n(cursorFrees);
}
static void forbiddenOwnerDestructor(CGameUI*) { need(false,209);_exit(82); }
static bool create(CGameUI* p) {
    need(p==owner,210);boundary(9);
    // All fields that the real D1 necessarily dereferences are valid before a
    // successful constructor returns, even when this collaborator returns false.
    field<CSoundBank*>(p,0x16a8)=0;
    for(unsigned i=0;i<2;++i) {
        void* storage=std::malloc(sizeof(gameui_create_detail::TextEventList));
        need(storage!=0,211);if(!storage)throw std::bad_alloc();
        shells[i]=::new(storage) gameui_create_detail::TextEventList;
        field<void*>(p,0x1698+i*8)=shells[i];
    }
    trackBuffers=true;
    field<std::vector<CSubMenu*> >(p,0x1930).reserve(3);
    field<std::vector<CDropdownMenu*> >(p,0x1948).reserve(4);
    field<std::vector<EContextTip> >(p,0x1960).reserve(5);
    std::vector<SDL_Cursor*>& cursors=field<std::vector<SDL_Cursor*> >(p,0x19f0);
    cursors.reserve(5);for(unsigned i=0;i<5;++i)cursors.push_back(reinterpret_cast<SDL_Cursor*>(arguments[i]));
    // Empty element strings avoid any hidden libstdc++ allocation provenance.
    field<TArrayList<Wide> >(p,0x440).add(field<Wide>(p,0x16c0));
    field<TArrayList<CEGUI::Imageset*> >(p,0x458).add(0);
    need(allocationCount==6,212);
    need(allocations[0].size==3*sizeof(void*)&&allocations[0].kind==1,213);
    need(allocations[1].size==4*sizeof(void*)&&allocations[1].kind==1,214);
    need(allocations[2].size==5*sizeof(EContextTip)&&allocations[2].kind==1,215);
    need(allocations[3].size==5*sizeof(void*)&&allocations[3].kind==1,216);
    need(allocations[4].size==8+25*sizeof(Wide)&&allocations[4].kind==2,217);
    need(allocations[5].size==5*sizeof(void*)&&allocations[5].kind==2,218);
    if(current.fault==9)throw Stop();
    return current.createResult!=0;
}
static void checkRecovery(bool threw) {
    const unsigned fault=current.fault;
    unsigned expectedCore=fault==1?0:fault==2?1:fault==3||fault==4?2:3;
    // This original global counts completed constructions cumulatively; D1 does not decrement it.
    need(objectCount()==int(initialObjects+expectedCore),230);
    need(coreDestructions==expectedCore,231);
    need(keyDestructions==(fault&&fault<=3?0:1),232);
    need(mouseDestructions==(fault&&fault<=4?0:1),233);
    unsigned expectedOrder[3],count=0;
    if(!fault||fault>=5)expectedOrder[count++]=0x12a8;
    if(!fault||fault>=3)expectedOrder[count++]=0x590;
    if(fault!=1)expectedOrder[count++]=0;
    need(coreOrderCount==count,234);
    for(unsigned i=0;i<count&&i<coreOrderCount;++i)need(coreOrder[i]==expectedOrder[i],235+i);
    for(unsigned i=0;i<4;++i)if(retained[i]&&!keepers[i]->empty()) {
        need(refs(*keepers[i])==0,240+i);n(230);n(i);n(refs(*keepers[i]));
    }
    if(fault==9||!fault) {
        need(allocationCount==6&&releaseCount==6,250);
        for(unsigned i=0;i<6;++i)need(allocations[i].freed,251+i);
        // Automatic member cleanup: cursor vector, queued tips, dropdowns,
        // submenus, image array, icon-file array. In normal D1 the image array
        // is explicitly cleared first, before the automatic member sequence.
        static const unsigned unwind[]={4,3,2,1,6,5};
        static const unsigned normal[]={6,4,3,2,1,5};
        for(unsigned i=0;i<6&&i<releaseCount;++i)need(releaseOrder[i]==(threw?unwind[i]:normal[i]),260+i);
    } else need(allocationCount==0&&releaseCount==0,270);
    if(threw) {
        need(cursorFrees==0&&shellFrees==0,271);
        need(singleton()==(current.existing?reinterpret_cast<CGameUI*>(arguments[11]):fault==9?owner:0),272);
        if(fault==9)need(shells[0]&&shells[1],273);
    } else { need(cursorFrees==5&&shellFrees==2,274);need(singleton()==0,275); }
}
static void side(const Case& c,bool ours,autotest::Capture& out) {
    typedef char owner_size[sizeof(CGameUI)==0x1a08?1:-1];
    typedef char old_string_size[sizeof(Wide)==8?1:-1];
    current=c;capture=&out;owner=reinterpret_cast<CGameUI*>(ownerMemory);bytes=reinterpret_cast<unsigned char*>(owner);
    std::memset(bytes,c.poison?0x5a:0xa5,0x1a08);std::memset(arguments,0,sizeof(arguments));
    std::memset(retained,0,sizeof(retained));std::memset(keys,0,sizeof(keys));keys[0x39]=c.poison?0x80:0;
    oracleErrors=0;lastStage=negativeHits=keyDestructions=mouseDestructions=coreDestructions=0;
    cursorFrees=shellFrees=coreOrderCount=allocationCount=releaseCount=0;
    shells[0]=shells[1]=0;constructing=false;trackBuffers=false;initialObjects=objectCount();
    field<void*>(arguments[9],0x98)=arguments[10];
    new(&emptyConstant())Wide(c.text?L"constant-copy-probe":L"");
    // A leaked source representation forces each copy to acquire its own rep.
    if(c.text)emptyConstant()[0]=L'c';
    singleton()=c.existing?reinterpret_cast<CGameUI*>(arguments[11]):0;
    for(unsigned i=0;i<10;++i){sourceKeys()[i]=0x12340000u+101*i+c.poison;targetKeys()[i]=0xcafe0000u+i;}
    for(unsigned i=0;i<12;++i){sourceFunctions()[i]=0x87650000u+37*i+c.poison;targetFunctions()[i]=0xbeef0000u+i;}
    detour::Set baseC,keyC,mouseC,baseD,keyD,mouseD,literalC,copyC,collaborators,allocators,ownerTrap;
    corePatch=&baseC;keyPatch=&keyC;mousePatch=&mouseC;coreDestroyPatch=&baseD;keyDestroyPatch=&keyD;mouseDestroyPatch=&mouseD;
    literalPatch=&literalC;copyPatch=&copyC;
    TL_REDIRECT(baseC,coreCtor,&core);TL_REDIRECT(keyC,keyCtor,&key);TL_REDIRECT(mouseC,mouseCtor,&mouse);
    TL_REDIRECT(baseD,coreDtor,&destroyCore);TL_REDIRECT(keyD,keyDtor,&destroyKey);TL_REDIRECT(mouseD,mouseDtor,&destroyMouse);
    literalC.redirect(literalStringCtor,literalStringCtor,&literal);copyC.redirect(copyStringCtor,copyStringCtor,&copy);
    TL_REDIRECT(collaborators,masterGetter,&master);TL_REDIRECT(collaborators,createUI,&create);
    collaborators.redirect(keyboardState,keyboardState,&keyboard);collaborators.redirect(setCursor,setCursor,&cursorSet);
    collaborators.redirect(freeCursor,freeCursor,&cursorFree);collaborators.redirect(ogreFree,ogreFree,&releaseOgre);
    allocators.redirect(scalarNew,scalarNew,&allocateScalar);allocators.redirect(arrayNew,arrayNew,&allocateArray);
    allocators.redirect(scalarDelete,scalarDelete,&releaseScalar);allocators.redirect(arrayDelete,arrayDelete,&releaseArray);
    TL_REDIRECT(ownerTrap,ownerDtor,&forbiddenOwnerDestructor);
    if(baseC.failed()||keyC.failed()||mouseC.failed()||baseD.failed()||keyD.failed()||mouseD.failed()||literalC.failed()||copyC.failed()||collaborators.failed()||allocators.failed()||ownerTrap.failed())_exit(83);
    need(reinterpret_cast<uintptr_t>(&originalGameUIConstructor)==reinterpret_cast<uintptr_t>(&originalGameUIBaseConstructor),280);
    bool threw=false;constructing=true;
    try {
        typedef void (*Constructor) UI_ARGS;
        Constructor fn=ours?(c.alias?&candidateGameUIBaseConstructor:&candidateGameUIConstructor):(c.alias?&originalGameUIBaseConstructor:&originalGameUIConstructor);
        autotest::invoke(out,fn,owner,Ref<CSettings>(reinterpret_cast<CSettings*>(arguments[0])),Ref<CGameClient>(reinterpret_cast<CGameClient*>(arguments[1])),static_cast<void*>(arguments[2]),reinterpret_cast<Ogre::RenderWindow*>(arguments[3]),reinterpret_cast<Ogre::Camera*>(arguments[4]),reinterpret_cast<Ogre::SceneManager*>(arguments[5]),reinterpret_cast<Ogre::SceneManager*>(arguments[6]),reinterpret_cast<Ogre::SceneManager*>(arguments[7]),reinterpret_cast<CResourceManager*>(arguments[8]));
    } catch(const Stop&) { threw=true; } catch(...) { _exit(84); }
    n(300);n(threw);need(threw==(c.fault!=0),281);need(lastStage==(c.fault?c.fault:9),282);
    need(negativeHits==(c.negative?1:0),283);
    if(!threw) {
        need(objectCount()-int(initialObjects)==3,284);
        need(singleton()==(c.existing?reinterpret_cast<CGameUI*>(arguments[11]):owner),285);
        for(unsigned i=0;i<4;++i)if(retained[i]&&!keepers[i]->empty())need(refs(*keepers[i])==1,286+i);
    }
    constructing=false;ownerTrap.restore();
    if(!threw) { n(301);cleanupGameUI(owner); }
    checkRecovery(threw);
    trackBuffers=false;allocators.restore();
    // On failed construction the raw resources assigned by create deliberately
    // survive; reclaim fixture-owned resources only AFTER recording that fact.
    for(unsigned i=0;i<2;++i)if(shells[i]){
        static_cast<gameui_create_detail::TextEventList*>(shells[i])->~TextEventList();
        std::free(shells[i]);shells[i]=0;
    }
    literalC.restore();copyC.restore();
    for(unsigned i=0;i<4;++i)if(retained[i])keepers[i]->~Wide();
    emptyConstant().~Wide();
    n(0xc701c701u);n(oracleErrors);
}
static void original(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),false,out); }
static void candidate(void* p,autotest::Capture& out) { side(*static_cast<Case*>(p),true,out); }
static bool cleanOracle(const autotest::Capture& c) {
    if(c.length<8)return false;
    unsigned footer[2];std::memcpy(footer,c.data+c.length-8,8);
    return footer[0]==0xc701c701u&&footer[1]==0;
}
static bool valid(const autotest::Outcome& a,const autotest::Outcome& b,bool exception) {
    return cleanOracle(a.capture)&&cleanOracle(b.capture)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.callStarted&&b.capture.callStarted&&
        bool(a.capture.callCompleted)==!exception&&bool(b.capture.callCompleted)==!exception&&!a.capture.issue&&!b.capture.issue&&
        a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
}
static void mismatch(const tlhybrid_host* host,const Case& c,const autotest::Outcome& a,const autotest::Outcome& b) {
    for(unsigned side=0;side<2;++side) {
        const autotest::Capture& q=side?b.capture:a.capture;
        for(size_t i=0;i+4<=q.length;++i) {
            unsigned code;std::memcpy(&code,q.data+i,4);
            if(code>=0xf0000000u&&code<0xf0000400u)host->log("    oracle side %u failure code %u at capture %lu\n",side,code-0xf0000000u,(unsigned long)i);
            if(code>=0xba000000u&&code<0xba001a08u)host->log("    oracle side %u first differing owner byte +0x%x\n",side,code-0xba000000u);
        }
    }
    size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
    host->log("    GameUI C1/C2 case poison=%u existing=%u create=%u text=%u alias=%u fault=%u negative=%u exits=%d/%d issues=%u/%u lengths=%lu/%lu first=%lu\n",c.poison,c.existing,c.createResult,c.text,c.alias,c.fault,c.negative,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);
}
}
TL_TEST(gameui_constructor_lifetime_differential) {
    using namespace gameui_constructor_lifetime;
    autotest::Coverage coverage("gameui_constructor_lifetime_differential",reinterpret_cast<uintptr_t>(&originalGameUIConstructor));
    for(unsigned pattern=0;pattern<32;++pattern) {
        Case c={pattern&1,(pattern>>1)&1,(pattern>>2)&1,(pattern>>3)&1,(pattern>>4)&1,0,0};
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        int difference=coverage.observe(host,a,b);
        if(difference||!valid(a,b,false)){mismatch(host,c,a,b);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    C1/C2: 32 complete pairs; one original address; nine independent partial-state boundaries\n");return 0;
}
TL_TEST(gameui_constructor_lifetime_expected_exceptions) {
    using namespace gameui_constructor_lifetime;
    unsigned count=0;
    for(unsigned fault=1;fault<=9;++fault)for(unsigned pattern=0;pattern<8;++pattern) {
        Case c={pattern&1,(pattern>>1)&1,0,1,(pattern>>2)&1,fault,0};
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++count;
        if(!valid(a,b,true)){mismatch(host,c,a,b);return 1;}
    }
    host->log("    EXPECTED CONSTRUCTOR EXCEPTIONS: %u matching member-only unwinds; excluded from completed-call coverage\n",count);return 0;
}
TL_TEST(gameui_constructor_lifetime_oracle_negative_controls) {
    using namespace gameui_constructor_lifetime;
    for(unsigned negative=1;negative<=3;++negative)for(unsigned pattern=0;pattern<4;++pattern) {
        Case c={pattern&1,0,0,1,(pattern>>1)&1,0,negative};
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(!valid(a,b,false)){mismatch(host,c,a,b);return 1;}
    }
    host->log("    12 completed oracle negatives reject late +e8, late +178c and early +1790 snapshots; not source-mutation coverage\n");return 0;
}
