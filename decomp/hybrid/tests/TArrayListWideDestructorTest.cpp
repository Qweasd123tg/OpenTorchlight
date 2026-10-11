// Direct evidence for the weak D1/D2 closure emitted by the GameUI lifetime TU.
// Construct both owner and the genuine new[] array; never forge its cookie.
#include <string>
#include <cstring>
#include <new>
#define private public
#include "TArrayList.h"
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,wideListOriginal,(TArrayList<std::wstring>*),"_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEED1Ev")
extern "C" void wideListCandidate(TArrayList<std::wstring>*) __asm__("_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEED1Ev");
extern "C" char wideArrayDelete[] __asm__("_ZdaPv");
extern "C" char wideScalarDelete[] __asm__("_ZdlPv");
extern "C" char wideOgreDelete[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char wideRepDelete[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
namespace wide_list_dtor_fixture {
typedef TArrayList<std::wstring> List;
struct Case { unsigned storage,countMode,pattern,poison; };
struct Result { unsigned magic,errors,events,expected; };
static const unsigned resultMagic=0x574c4454u;
static const unsigned sizes[]={0,0,1,2,3,7,25};
static const Case* input;
static autotest::Capture* capture;
static List* owner;
static std::wstring* elements;
static std::wstring aliases[25];
static void* reps[25];
static bool shared[25], nonempty[25], released[25];
static unsigned capacity,errors,eventCount,expectedCount,arrayCalls,scalarCalls,ogreCalls;
static unsigned events[32],expected[32];
static void* allocation;
static detour::Set *arrayPatch,*scalarPatch,*ogrePatch,*repPatch;
static bool active;
static unsigned char before[sizeof(List)];
static void n(unsigned value){capture->add(&value,sizeof(value));}
static void event(unsigned value){if(eventCount==32){capture->issue=autotest::Capture::Overflow;return;}events[eventCount++]=value;n(value);}
static int references(void* rep){int result;std::memcpy(&result,static_cast<char*>(rep)+16,sizeof(result));return result;}
static void sharedWitness(unsigned remaining) {
    if(input->pattern==4&&capacity) {
        int r=references(reps[0]);n(r);
        if(r!=int(remaining))errors|=4;
    } else for(unsigned i=0;i<capacity;++i)if(shared[i]){
        int r=references(reps[i]);n(r);
        if(r!=int(i<remaining))errors|=4;
    }
}
static void repRelease(void* p,const void* allocator) {
    if(active) {
        int id=-1;for(unsigned i=0;i<capacity;++i)if(nonempty[i]&&!shared[i]&&reps[i]==p)id=i;
        if(id<0){errors|=1;event(99);}else{
            if(released[id])errors|=1;released[id]=true;event(100+id);
            // This callback is after the current unique string's decrement,
            // before deallocation. Every higher index must already be dead.
            if(references(p)!=-1)errors|=4;
            sharedWitness(id);
        }
    }
    // Call the real libstdc++ allocator implementation; no simulated strings.
    repPatch->restore();reinterpret_cast<void(*)(void*,const void*)>(wideRepDelete)(p,allocator);
    repPatch->redirect(wideRepDelete,wideRepDelete,&repRelease);if(repPatch->failed())_exit(101);
}
static void arrayRelease(void* p) {
    if(active) {
        ++arrayCalls;event(p==allocation?1:2);
        if(p!=allocation)errors|=2;
        // Original clears m_pData only after delete[] returns.
        if(owner->m_pData!=elements)errors|=8;
        sharedWitness(0);
        for(unsigned i=0;i<capacity;++i)if(nonempty[i]&&!shared[i]&&!released[i])errors|=1;
        size_t cookie=0;if(allocation)std::memcpy(&cookie,allocation,sizeof(cookie));
        n(cookie);if(cookie!=capacity)errors|=2;
    }
    arrayPatch->restore();reinterpret_cast<void(*)(void*)>(wideArrayDelete)(p);
    arrayPatch->redirect(wideArrayDelete,wideArrayDelete,&arrayRelease);if(arrayPatch->failed())_exit(102);
}
static void scalarRelease(void* p) {
    if(active&&(p==allocation||p==elements||p==owner)){++scalarCalls;event(3);errors|=2;return;}
    scalarPatch->restore();reinterpret_cast<void(*)(void*)>(wideScalarDelete)(p);
    scalarPatch->redirect(wideScalarDelete,wideScalarDelete,&scalarRelease);if(scalarPatch->failed())_exit(103);
}
static void ogreRelease(void* p) {
    if(active&&(p==allocation||p==elements||p==owner)){++ogreCalls;event(4);errors|=2;return;}
    ogrePatch->restore();reinterpret_cast<void(*)(void*)>(wideOgreDelete)(p);
    ogrePatch->redirect(wideOgreDelete,wideOgreDelete,&ogreRelease);if(ogrePatch->failed())_exit(104);
}
static void setup(const Case& c,void* memory) {
    input=&c;capacity=sizes[c.storage];errors=eventCount=expectedCount=arrayCalls=scalarCalls=ogreCalls=0;active=false;
    std::memset(shared,0,sizeof(shared));std::memset(nonempty,0,sizeof(nonempty));std::memset(released,0,sizeof(released));std::memset(reps,0,sizeof(reps));
    owner=::new(memory)List(c.poison?0xf13579bdu:25u);
    // Real new[] includes zero-sized non-null allocations. Count deliberately
    // does not determine how many constructed array elements must be destroyed.
    elements=c.storage?new std::wstring[capacity]:0;
    owner->m_pData=elements;
    // Adversarial metadata does not change the genuine constructed array.
    // D1 must use its cookie, never this stored capacity or logical count.
    owner->m_nCapacity=c.poison?(capacity?0u:0xfedcba98u):capacity;
    owner->m_nCount=c.countMode==0?0:c.countMode==1?(capacity?1:0):capacity;
    allocation=elements?reinterpret_cast<char*>(elements)-sizeof(size_t):0;
    if(elements){size_t cookie;std::memcpy(&cookie,allocation,sizeof(cookie));if(cookie!=capacity)_exit(105);}
    if(c.pattern==4&&capacity)aliases[0]=std::wstring(83,L'Q');
    for(unsigned i=0;i<capacity;++i) {
        nonempty[i]=c.pattern!=0&&(c.pattern!=2||i%2==0);
        if(!nonempty[i])continue;
        if(c.pattern==4)elements[i]=aliases[0];
        else elements[i]=std::wstring(40+i,wchar_t(L'a'+i));
        reps[i]=const_cast<char*>(reinterpret_cast<const char*>(elements[i].c_str()))-24;
        shared[i]=c.pattern==3||c.pattern==4||(c.pattern==5&&i%2);
        if(shared[i]&&c.pattern!=4)aliases[i]=elements[i];
    }
    // This independent oracle is based on cookie-sized reverse destruction,
    // not on either implementation's observed trace or its m_nCount.
    for(unsigned i=capacity;i>0;--i)if(nonempty[i-1]&&!shared[i-1])expected[expectedCount++]=100+i-1;
    if(elements)expected[expectedCount++]=1;
    std::memcpy(before,owner,sizeof(before));
}
static void side(const Case& c,bool ours,autotest::Capture& out) {
    capture=&out;unsigned long long storage[8];
    std::memset(storage,c.poison?0xa5:0x5a,sizeof(storage));
    setup(c,reinterpret_cast<char*>(storage)+16);
    detour::Set ap,sp,op,rp;arrayPatch=&ap;scalarPatch=&sp;ogrePatch=&op;repPatch=&rp;
    ap.redirect(wideArrayDelete,wideArrayDelete,&arrayRelease);sp.redirect(wideScalarDelete,wideScalarDelete,&scalarRelease);op.redirect(wideOgreDelete,wideOgreDelete,&ogreRelease);rp.redirect(wideRepDelete,wideRepDelete,&repRelease);
    if(ap.failed()||sp.failed()||op.failed()||rp.failed())_exit(106);
    active=true;autotest::invoke(out,ours?&wideListCandidate:&wideListOriginal,owner);active=false;
    if(eventCount!=expectedCount)errors|=16;
    for(unsigned i=0;i<eventCount&&i<expectedCount;++i)if(events[i]!=expected[i])errors|=16;
    if(arrayCalls!=unsigned(c.storage!=0)||scalarCalls||ogreCalls)errors|=2;
    // Read object representation after lifetime end, not destroyed strings.
    unsigned char after[sizeof(List)];std::memcpy(after,owner,sizeof(after));
    void* finalData=0;std::memcpy(&finalData,after,sizeof(finalData));if(finalData)errors|=8;
    if(std::memcmp(after+sizeof(void*),before+sizeof(void*),sizeof(List)-sizeof(void*)))errors|=8;
    const unsigned char* bytes=reinterpret_cast<const unsigned char*>(storage);
    for(unsigned i=0;i<sizeof(storage);++i)if(i<16||i>=16+sizeof(List))if(bytes[i]!=(c.poison?0xa5:0x5a))errors|=32;
    // Shared reps remain genuinely alive through external aliases. Every
    // character is checked, as are the final old-ABI reference counts.
    sharedWitness(0);
    for(unsigned i=0;i<capacity;++i)if(shared[i]&&(c.pattern!=4||i==0)){
        const std::wstring& value=aliases[c.pattern==4?0:i];
        unsigned length=c.pattern==4?83:40+i;wchar_t character=c.pattern==4?L'Q':wchar_t(L'a'+i);
        n(value.size());capture->add(value.data(),value.size()*sizeof(wchar_t));
        if(value.size()!=length)errors|=4;
        for(size_t j=0;j<value.size();++j)if(value[j]!=character)errors|=4;
    }
    n(arrayCalls);n(scalarCalls);n(ogreCalls);
    capture->add(after+sizeof(void*),sizeof(List)-sizeof(void*));
    Result result={resultMagic,errors,eventCount,expectedCount};capture->add(&result,sizeof(result));
}
static void original(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void candidate(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
static bool result(const autotest::Outcome& out,Result& r){if(!out.reportValid||out.capture.length<sizeof(r))return false;std::memcpy(&r,out.capture.data+out.capture.length-sizeof(r),sizeof(r));return r.magic==resultMagic;}
}
TL_TEST(tarraylist_wstring_destructor_differential) {
    using namespace wide_list_dtor_fixture;
    autotest::Coverage coverage("tarraylist_wstring_destructor_differential",reinterpret_cast<uintptr_t>(&wideListOriginal));unsigned pairs=0;
    for(unsigned storage=0;storage<7;++storage)for(unsigned count=0;count<3;++count)for(unsigned pattern=0;pattern<6;++pattern)for(unsigned poison=0;poison<2;++poison){
        Case c={storage,count,pattern,poison};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++pairs;
        int diff=coverage.observe(host,a,b);Result x,y;bool rx=result(a,x),ry=result(b,y);
        if(diff||autotest::incomplete(a)||autotest::incomplete(b)||!rx||!ry||x.errors||y.errors||a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length)){
            coverage.report(host);host->log("    wide-list case %u/%u/%u/%u exits %d/%d lengths %lu/%lu errors %x/%x events %u/%u vs %u/%u\n",storage,count,pattern,poison,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,rx?x.errors:~0u,ry?y.errors:~0u,rx?x.events:0,rx?x.expected:0,ry?y.events:0,ry?y.expected:0);return 1;
        }
    }
    coverage.report(host);host->log("    wide-list: %u real-owner/cookie-sized destructor comparisons\n",pairs);return 0;
}
