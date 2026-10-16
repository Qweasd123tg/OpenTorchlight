#include "ParentPairs.h"
#include <map>
#define private public
#include "DescriptorRegistry.h"
#undef private
TL_ORIGINAL(CEditorBaseObject*,parentCacheOld,(const std::wstring&),"_ZN21CDescriptorController15getCachedObjectERKSbIwSt11char_traitsIwESaIwEE")
extern "C" CEditorBaseObject* parentCacheNew(const std::wstring&) __asm__("_ZN21CDescriptorController15getCachedObjectERKSbIwSt11char_traitsIwESaIwEE");
namespace {
void side(void* raw,autotest::Capture& out,bool ours)
{
    unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;
    const wchar_t* names[]={L"",L"A",L"AA",L"AB",L"Ж",L"missing"};
    TArrayList<CEditorBaseObject*> lists[5];CEditorBaseObject* objects[7];
    for(unsigned i=0;i<7;++i)objects[i]=reinterpret_cast<CEditorBaseObject*>(autotest::allocate(16));
    g_CachedObjects.clear();
    for(unsigned k=0;k<5;++k){for(unsigned i=0;i<(seed+k)%8;++i)lists[k].add((seed+i+k)%7==0?NULL:objects[(i+k)%7]);if((seed+k)%3)g_CachedObjects[names[k]]=&lists[k];}
    std::wstring query=names[(seed/8)%6];
    typedef CEditorBaseObject*(*Fn)(const std::wstring&);Fn fn=ours?parentCacheNew:parentCacheOld;
    if(!autotest::beginInvocation(out,fn))return;
    for(unsigned repeat=0;repeat<9;++repeat){CEditorBaseObject* value=fn(query);out.addPointer(value);}
    out.callCompleted=1;
    parentpairs::scalar(out,g_CachedObjects.size());
    for(std::map<std::wstring,TArrayList<CEditorBaseObject*>*>::iterator i=g_CachedObjects.begin();i!=g_CachedObjects.end();++i){out.addText(i->first);TArrayList<CEditorBaseObject*>& l=*i->second;parentpairs::scalar(out,l.size());parentpairs::scalar(out,l.m_nCapacity);parentpairs::scalar(out,l.m_nGrowBy);for(unsigned j=0;j<l.size();++j)out.addPointer(l[j]);}
    g_CachedObjects.clear();
}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(parent_descriptor_cache){return parentpairs::run(host,"parent_descriptor_cache",(uintptr_t)parentCacheOld,96,a,b);}
