#include "AutoTest.h"
#include "Detour.h"
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"
#include "EditorBaseObject.h"
#include <limits>

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(void, old7067f0, (CDescriptorProp*, CDescriptorPropertyInterpreter*), "_ZN15CDescriptorProp22setPropertyInterpreterEP30CDescriptorPropertyInterpreter")
extern "C" void new7067f0(CDescriptorProp*, CDescriptorPropertyInterpreter*) __asm__("_ZN15CDescriptorProp22setPropertyInterpreterEP30CDescriptorPropertyInterpreter");
TL_ORIGINAL(UNIONDATA32BIT*, old709ca0, (CDescriptorProp*, CEditorBaseObject*, unsigned&), "_ZN15CDescriptorProp17getDataFromObjectEP17CEditorBaseObjectRj")
extern "C" UNIONDATA32BIT* new709ca0(CDescriptorProp*, CEditorBaseObject*, unsigned&) __asm__("_ZN15CDescriptorProp17getDataFromObjectEP17CEditorBaseObjectRj");
TL_ORIGINAL(std::wstring, old709e10, (CDescriptorProp*, CEditorBaseObject*), "_ZN15CDescriptorProp24getPropertyValueAsStringEP17CEditorBaseObject")
extern "C" std::wstring new709e10(CDescriptorProp*, CEditorBaseObject*) __asm__("_ZN15CDescriptorProp24getPropertyValueAsStringEP17CEditorBaseObject");
TL_ORIGINAL(void, old70a170, (CDescriptorProp*, const UNIONDATA32BIT*, unsigned, CEditorBaseObject*), "_ZN15CDescriptorProp7setDataEPK14UNIONDATA32BITjP17CEditorBaseObject")
extern "C" void new70a170(CDescriptorProp*, const UNIONDATA32BIT*, unsigned, CEditorBaseObject*) __asm__("_ZN15CDescriptorProp7setDataEPK14UNIONDATA32BITjP17CEditorBaseObject");
TL_ORIGINAL(void, old709a10, (CDescriptorProp*), "_ZN15CDescriptorPropD1Ev")
extern "C" void new709a10(CDescriptorProp*) __asm__("_ZN15CDescriptorPropD1Ev");
TL_FUNCTION(convertTarget,"_ZN15CDescriptorProp18convertDataTo32bitEPK13UNIONDATA8BITjRj")
namespace {
autotest::Capture* capture;unsigned calls,seed;CEditorBaseObject* expectedObject;
UNIONDATA32BIT values[8],converted[8];
void number(unsigned value){capture->add(&value,4);}
unsigned toIndex(CEditorScene* scene,CEditorBaseObject* object,const std::wstring& name,void* context)
{number(1);number(scene==NULL);number(object==expectedObject);capture->addText(name);number(context==values);return seed*17+3;}
std::wstring toName(CEditorScene* scene,CEditorBaseObject* object,unsigned index,void* context)
{number(2);number(scene==NULL);number(object==expectedObject);number(index);number(context==values);return seed%2?L"mapped":L"";}
void setter(CEditorBaseObject* object,const void* data,unsigned count)
{++calls;number(3);number(object==expectedObject);number(count);if(object!=expectedObject)capture->issue=autotest::Capture::InvalidReport;capture->add(data,count*4);}
UNIONDATA8BIT* getter(CEditorBaseObject* object,unsigned& count)
{++calls;number(4);number(object==expectedObject);if(object!=expectedObject)capture->issue=autotest::Capture::InvalidReport;count=(seed%5)*4;return reinterpret_cast<UNIONDATA8BIT*>(values);}
UNIONDATA32BIT* convert(CDescriptorProp*,const UNIONDATA8BIT* data,unsigned size,unsigned& count)
{++calls;number(5);number(size);capture->add(data,size);count=(size+3)/4;return converted;}
unsigned destroyed, interpreterFreed;
void* ownedInterpreter;
struct InterpreterWitness : CDescriptorPropertyInterpreter {
    InterpreterWitness() : CDescriptorPropertyInterpreter(&toIndex,&toName,values) {}
    virtual ~InterpreterWitness() { ++destroyed;number(7);number(this==ownedInterpreter); }
    void operator delete(void* memory) {
        ++interpreterFreed;number(8);number(memory==ownedInterpreter);
        CDescriptorPropertyInterpreter::operator delete(memory);
    }
};
void destroyProperty(const Case& c,autotest::Capture& out,bool ours)
{
    std::wstring category(c.index%4?std::wstring(32+c.index,L'c'):L"");
    std::wstring name(c.index%3?std::wstring(41+c.index,L'n'):L"");
    std::wstring description(c.index%5?std::wstring(53+c.index,L'd'):L"");
    void* memory=CDescriptorProp::operator new(sizeof(CDescriptorProp));
    CDescriptorProp* property=new(memory) CDescriptorProp(category,name,description,NULL,NULL,VARIABLE_TYPE_STRING,c.index);
    destroyed=interpreterFreed=0;ownedInterpreter=NULL;
    TSafePointer<CDescriptorProp> reference;reference.setObject(property);
    TSafePointer<CDescriptorPropertyInterpreter> interpreterReference;
    if(c.index%2){property->m_pInterpreter=new InterpreterWitness;ownedInterpreter=property->m_pInterpreter;interpreterReference.setObject(property->m_pInterpreter);}
    if(c.index%3){property->m_pValueBuffer=Ogre::NedAllocImpl::allocBytes(16+c.index*4,NULL,0,NULL);std::memset(property->m_pValueBuffer,0x5a,16+c.index*4);}
    for(unsigned i=0;i<c.index%7;++i){UNIONDATA32BIT value;value.m_uValue=c.index*17+i;property->m_DefaultValue.add(value);}
    // Linked entries are borrowed; self-reference must never be deleted.
    for(unsigned i=0;i<c.index%4;++i)property->m_LinkedProperties.add(property);
    // This original counter counts constructions, not live objects. D1 must not add objects.
    int initialCount=g_iTotalCountOfObjects;
    typedef void(*Fn)(CDescriptorProp*);Fn fn=ours?new709a10:old709a10;
    if(!autotest::beginInvocation(out,fn))return;
    fn(property);out.callCompleted=1;
    // D1 ended every member lifetime but deliberately retained the outer allocation.
    // Only external witnesses and the surviving shared string owners are read.
    number(destroyed);number(interpreterFreed);
    number(reference.getObject()==NULL);number(interpreterReference.getObject()==NULL);
    int delta=g_iTotalCountOfObjects-initialCount;out.add(&delta,sizeof(delta));
    bool aliases=category==std::wstring(c.index%4?32+c.index:0,L'c') && name==std::wstring(c.index%3?41+c.index:0,L'n') && description==std::wstring(c.index%5?53+c.index:0,L'd');
    out.add(&aliases,1);
    if(destroyed!=c.index%2 || interpreterFreed!=c.index%2 || reference.getObject()!=NULL || interpreterReference.getObject()!=NULL || delta || !aliases)out.issue=autotest::Capture::InvalidReport;
    CDescriptorProp::operator delete(memory);
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);capture=&out;seed=c.index;calls=0;
    if(c.op==4){destroyProperty(c,out,ours);return;}
    CEditorBaseObject object;expectedObject=&object;
    CDescriptorProp property(L"category",L"name",L"different description",reinterpret_cast<void*>(&setter),reinterpret_cast<void*>(&getter),static_cast<EVARIABLE_TYPES>(c.index%11),c.index);
    CDescriptorPropertyInterpreter interpreter(&toIndex,&toName,values);
    for(unsigned i=0;i<8;++i)values[i].m_iValue=(c.index+7)*(i+1);
    if(c.op==0) {
        typedef void(*Fn)(CDescriptorProp*,CDescriptorPropertyInterpreter*);Fn fn=ours?new7067f0:old7067f0;
        // Exercise creating, reconfiguring and clearing the real owned interpreter.
        if(c.index%3==1)property.m_pInterpreter=new CDescriptorPropertyInterpreter(&toIndex,&toName,converted);
        CDescriptorPropertyInterpreter* argument=c.index%3==2?NULL:&interpreter;
        if(!autotest::beginInvocation(out,fn))return;fn(&property,argument);out.callCompleted=1;
        number(property.m_pInterpreter!=NULL);
        if(property.m_pInterpreter) {
            number(property.m_pInterpreter->GetValue(NULL,&object,std::wstring(L"sample")));
            out.addText(property.m_pInterpreter->GetValue(NULL,&object,19));
        }
    } else if(c.op==1) {
        property.m_eType=c.index%2?VARIABLE_TYPE_INTEGER:VARIABLE_TYPE_STRING;
        if(c.index%4==1)property.m_pInterpreter=&interpreter;
        detour::Set patches;TL_REDIRECT(patches,convertTarget,&convert);
        if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        unsigned count=0x12345678;CEditorBaseObject* argument=c.index%6==0?NULL:&object;
        typedef UNIONDATA32BIT*(*Fn)(CDescriptorProp*,CEditorBaseObject*,unsigned&);Fn fn=ours?new709ca0:old709ca0;
        if(!autotest::beginInvocation(out,fn))return;UNIONDATA32BIT* value=fn(&property,argument,count);out.callCompleted=1;
        number(value==converted);number(value==NULL);number(count);number(calls);
        property.m_pInterpreter=NULL;
    } else if(c.op==2) {
        property.m_pGetFunction=NULL;
        unsigned count=c.index/11%4;
        property.m_eType=static_cast<EVARIABLE_TYPES>(c.index%11);
        if(property.m_eType==VARIABLE_TYPE_STRING) {
            const wchar_t* text=c.index%2?L"wide text":L"";
            for(unsigned i=0;i<=std::wcslen(text);++i){UNIONDATA32BIT value;value.m_uValue=text[i];property.m_DefaultValue.add(value);}
        } else for(unsigned i=0;i<count;++i) {
            UNIONDATA32BIT value;
            if(property.m_eType==VARIABLE_TYPE_FLOAT||property.m_eType>=VARIABLE_TYPE_VECTOR2)value.m_fValue=(float(int(c.index)-20)+i)*0.125f;
            else if(property.m_eType==VARIABLE_TYPE_BOOL)value.m_bValue=(c.index+i)%2;
            else value.m_iValue=int(c.index)-30+i;
            property.m_DefaultValue.add(value);
        }
        typedef std::wstring(*Fn)(CDescriptorProp*,CEditorBaseObject*);Fn fn=ours?new709e10:old709e10;
        if(!autotest::beginInvocation(out,fn))return;std::wstring value=fn(&property,NULL);out.callCompleted=1;out.addText(value);
    } else {
        property.m_eType=VARIABLE_TYPE_INTEGER;
        CDescriptorProp linked(L"linked",L"name",L"description",reinterpret_cast<void*>(&setter),reinterpret_cast<void*>(&getter),VARIABLE_TYPE_INTEGER,0);
        // An empty getter uses the original four-byte zero fallback. A string
        // property owns the converted buffer; an aligned integer would return
        // a pointer to that helper's expired local and make this observer read
        // arbitrary stack bytes after the linked call returns.
        if(c.index%5==0)linked.m_eType=VARIABLE_TYPE_STRING;
        if(c.index%3==1)property.m_LinkedProperties.add(&linked);
        if(c.index%4==0)property.m_pSetFunction=NULL;
        if(c.index%7==0)property.m_pGetFunction=NULL;
        const UNIONDATA32BIT* data=c.index%6==0?NULL:values;
        unsigned count=c.index%5;
        CEditorBaseObject* argument=c.index%3==0?NULL:&object;
        typedef void(*Fn)(CDescriptorProp*,const UNIONDATA32BIT*,unsigned,CEditorBaseObject*);Fn fn=ours?new70a170:old70a170;
        if(!autotest::beginInvocation(out,fn))return;fn(&property,data,count,argument);out.callCompleted=1;
        number(calls);number(property.m_DefaultValue.size());
        for(unsigned i=0;i<property.m_DefaultValue.size();++i)number(property.m_DefaultValue[i].m_uValue);
    }
}
void original(void* p,autotest::Capture& c){side(p,c,false);}void candidate(void* p,autotest::Capture& c){side(p,c,true);}
}
TL_TEST(state_descriptor_7067f0) {return runCases(host,0,88,"state_descriptor_7067f0",(uint64_t)(uintptr_t)old7067f0,original,candidate);}
TL_TEST(state_descriptor_709ca0) {return runCases(host,1,88,"state_descriptor_709ca0",(uint64_t)(uintptr_t)old709ca0,original,candidate);}
TL_TEST(state_descriptor_709e10) {return runCases(host,2,88,"state_descriptor_709e10",(uint64_t)(uintptr_t)old709e10,original,candidate);}
TL_TEST(state_descriptor_70a170) {return runCases(host,3,88,"state_descriptor_70a170",(uint64_t)(uintptr_t)old70a170,original,candidate);}

TL_TEST(state_descriptor_709a10) {return runCases(host,4,88,"state_descriptor_709a10",(uint64_t)(uintptr_t)old709a10,original,candidate);}
