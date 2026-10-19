#include "AutoTest.h"
#include <OgreMemoryAllocatorConfig.h>
#include <string>
#include <map>
#define private public
#include "DataGroup.h"
#include "TRepository.h"
#undef private
TL_ORIGINAL(void,dgOldCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,dgOldDtor,(CDataGroup*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(TRepository<std::wstring>*,dgOriginalRepository,(),"_ZN10CDataGroup16stringRepositoryEv")
extern "C" void dgNewDtor(CDataGroup*) __asm__("_ZN10CDataGroupD1Ev");
namespace {
struct Case { unsigned mode, seed; };
void number(autotest::Capture& out,int value) { out.add(&value,sizeof value); }
CDataGroup* group(const std::wstring& name,CDataGroup* parent,TRepository<std::wstring>* repository) {
    CDataGroup* result=static_cast<CDataGroup*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDataGroup),0,0,0));
    std::memset(result,0xa5,sizeof(CDataGroup));
    dgOldCtor(result,name,parent,3,4,repository);
    return result;
}
void release(CDataGroup* value) { dgOldDtor(value); Ogre::NedAllocImpl::deallocBytes(value); }
// The native global repository can already contain the game's resource names.
// Stream its complete ordered contents into two fingerprints instead of filling
// the bounded per-call capture with unrelated baseline strings.
struct RepositoryFingerprint {
    unsigned long long a,b;
    RepositoryFingerprint():a(14695981039346656037ULL),b(5381){}
    void add(const void* raw,size_t count) {
        const unsigned char* p=static_cast<const unsigned char*>(raw);
        for(size_t i=0;i<count;++i){a=(a^p[i])*1099511628211ULL;b=(b*33)^p[i];}
    }
    void value(unsigned n){add(&n,sizeof n);}
    void text(const std::wstring& s){value(s.size());add(s.data(),s.size()*sizeof(wchar_t));}
};
void repositoryState(autotest::Capture& out,TRepository<std::wstring>* repository) {
    number(out,repository->m_iNextID);
    RepositoryFingerprint fingerprint;
    fingerprint.text(repository->m_DefaultValue);
    fingerprint.value(repository->m_Values.size());
    for(std::map<unsigned,std::wstring>::iterator i=repository->m_Values.begin();i!=repository->m_Values.end();++i) {
        fingerprint.value(i->first);fingerprint.text(i->second);
    }
    fingerprint.value(repository->m_IDs.size());
    for(std::map<std::wstring,unsigned>::iterator i=repository->m_IDs.begin();i!=repository->m_IDs.end();++i) {
        fingerprint.text(i->first);fingerprint.value(i->second);
    }
    fingerprint.value(repository->m_RefCounts.size());
    for(std::map<unsigned,unsigned short>::iterator i=repository->m_RefCounts.begin();i!=repository->m_RefCounts.end();++i) {
        fingerprint.value(i->first);fingerprint.value(i->second);
    }
    out.add(&fingerprint.a,sizeof fingerprint.a);out.add(&fingerprint.b,sizeof fingerprint.b);
}
void side(void* raw,autotest::Capture& out,bool ours) {
    Case c=*static_cast<Case*>(raw);
    int before=g_iTotalCountOfObjects;
    TRepository<std::wstring>* repository=c.mode==0?dgOriginalRepository():new TRepository<std::wstring>(L"DEFAULT");
    if(c.mode==0) {
        void* existing=0;std::memcpy(&existing,&repository->m_DefaultValue,sizeof existing);
        if(!existing)new(repository)TRepository<std::wstring>(L"");
    }
    CDataGroup* owner=c.mode==1||c.mode==3?group(L"OWNER",NULL,repository):NULL;
    CDataGroup* target=group(c.seed%5==0?repository->m_DefaultValue:L"TARGET",owner,repository);
    CDataGroup* populated=c.mode==3?owner:target;
    TSafePointer<CRunicCore> observers[80];unsigned count=0;
    observers[count++].setObject(target);
    for(unsigned i=0;i<c.seed%5;++i) {
        CDataGroup* child=populated->AddDataGroup(i%2?L"CHILD":L"OTHER");observers[count++].setObject(child);
        for(unsigned j=0;j<(c.seed+i)%3;++j) {
            CDataGroup* nested=child->AddDataGroup(j%2?L"CHILD":L"NESTED");observers[count++].setObject(nested);
            CDataValue* value=nested->AddDataValue(L"VALUE",int(i*17+j));observers[count++].setObject(value);
        }
    }
    for(unsigned i=0;i<c.seed%8;++i) {
        CDataValue* value=populated->AddDataValue(i%2?L"VALUE":L"OTHER",std::wstring(c.seed%3?L"TEXT":L"DEFAULT"),false);
        observers[count++].setObject(value);
    }
    if(c.mode==3) {
        target->m_iNameID=owner->m_iNameID;
        target->m_b59=true;
        for(unsigned i=0;i<owner->m_DataGroups.size();++i)target->m_DataGroups.add(owner->m_DataGroups[i]);
        for(unsigned i=0;i<owner->m_DataValues.size();++i)target->m_DataValues.add(owner->m_DataValues[i]);
    }
    // A genuine live name can be shared by another live group.
    CDataGroup* sibling=(c.seed&16)&&c.mode!=2?group(L"TARGET",target,repository):NULL;
    if(c.seed%11==0)target->SetGroupName(L"RENAMED");
    number(out,count);number(out,g_iTotalCountOfObjects-before);repositoryState(out,repository);
    void(*function)(CDataGroup*)=ours?dgNewDtor:dgOldDtor;
    if(autotest::beginInvocation(out,function)) {function(target);out.callCompleted=1;}
    for(unsigned i=0;i<count;++i)number(out,observers[i].getObject()==NULL);
    number(out,g_iTotalCountOfObjects-before);
    int name=0;std::memcpy(&name,reinterpret_cast<char*>(target)+offsetof(CDataGroup,m_iNameID),sizeof name);number(out,name);
    for(unsigned offset=0x20;offset<=0x44;offset+=4) {
        if(offset==0x20||offset==0x24||offset==0x38||offset==0x3c)continue;
        unsigned word=0;std::memcpy(&word,reinterpret_cast<char*>(target)+offset,4);number(out,word);
    }
    TRepository<std::wstring>* remaining=0;std::memcpy(&remaining,reinterpret_cast<char*>(target)+offsetof(CDataGroup,m_pRepository),sizeof remaining);
    number(out,remaining==NULL);number(out,remaining==repository);
    if(c.mode!=2)repositoryState(out,repository);
    out.addHeapInUse();
    Ogre::NedAllocImpl::deallocBytes(target);
    // The sibling was intentionally not owned by the target's child list.
    if(sibling&&c.mode!=2)release(sibling);
    if(owner)release(owner);
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void recovered(void* p,autotest::Capture& out){side(p,out,true);}
}
TL_TEST(data_group_destructor_native) {
    autotest::Coverage coverage("data_group_destructor_native",0xc61550);
    for(unsigned mode=0;mode<4;++mode)for(unsigned seed=0;seed<64;++seed) {
        Case c={mode,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    DataGroup mode%u seed%u exit%d/%d issue%u/%u bytes%lu/%lu\n",mode,seed,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=256||coverage.different||coverage.missing;
}
