#include "ParentPairs.h"
#include "Detour.h"
#define private public
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"
#undef private
#include "EditorBaseObject.h"
#include "SafePointer.h"
TL_ORIGINAL(void,parentPropCopyOld,(CDescriptorProp*,CDescriptorProp*,CEditorBaseObject*),"_ZN15CDescriptorPropC1EPS_P17CEditorBaseObject")
extern "C" void parentPropCopyNew(CDescriptorProp*,CDescriptorProp*,CEditorBaseObject*) __asm__("_ZN15CDescriptorPropC1EPS_P17CEditorBaseObject");
TL_ORIGINAL(void,parentPropSetOld,(CDescriptorProp*,PropertyStringToIndexFunction,PropertyIndexToStringFunction,void*),"_ZN15CDescriptorProp31setPropertyInterpreterFunctionsEPFjP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPvEPFS7_S1_S3_jSA_ESA_")
extern "C" void parentPropSetNew(CDescriptorProp*,PropertyStringToIndexFunction,PropertyIndexToStringFunction,void*) __asm__("_ZN15CDescriptorProp31setPropertyInterpreterFunctionsEPFjP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPvEPFS7_S1_S3_jSA_ESA_");
TL_FUNCTION(parentCopyCall,"_ZN15CDescriptorProp4copyERS_P17CEditorBaseObject")
TL_FUNCTION(parentInterpreterCtor,"_ZN30CDescriptorPropertyInterpreterC1EPFjP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPvEPFS7_S1_S3_jSA_ESA_")
namespace {
autotest::Capture* cap;unsigned seed,destroyed,freed,callbackCalls;
void* expectedContext;CEditorBaseObject* expectedObject;CDescriptorProp* expectedSource;CDescriptorProp* destination;
TSafePointer<CDescriptorProp>* unwindReference;
UNIONDATA32BIT getterValues[8];
void number(unsigned n){parentpairs::scalar(*cap,n);}
unsigned index(CEditorScene* s,CEditorBaseObject* o,const std::wstring& text,void* p)
{number(1);bool valid=!s&&o==expectedObject&&p==expectedContext;parentpairs::scalar(*cap,valid);cap->addText(text);++callbackCalls;if(!valid)cap->issue=autotest::Capture::InvalidReport;return seed*17+text.size();}
std::wstring name(CEditorScene* s,CEditorBaseObject* o,unsigned n,void* p)
{number(2);bool valid=!s&&o==expectedObject&&p==expectedContext;parentpairs::scalar(*cap,valid);number(n);++callbackCalls;if(!valid)cap->issue=autotest::Capture::InvalidReport;return seed%2?L"mapped":L"";}
UNIONDATA8BIT* getter(CEditorBaseObject* object,unsigned& bytes)
{number(7);bool valid=object==expectedObject;parentpairs::scalar(*cap,valid);if(!valid)cap->issue=autotest::Capture::InvalidReport;bytes=(seed%7+1)*4;number(bytes);return reinterpret_cast<UNIONDATA8BIT*>(getterValues);}
void setter(CEditorBaseObject*,const void*,unsigned){cap->issue=autotest::Capture::InvalidReport;}
struct Witness: CDescriptorPropertyInterpreter {
    Witness():CDescriptorPropertyInterpreter(&index,&name,NULL){}
    virtual ~Witness(){++destroyed;number(3);}
    void operator delete(void* p){++freed;number(4);CDescriptorPropertyInterpreter::operator delete(p);}
};
void throwInterpreter(CDescriptorPropertyInterpreter* p,PropertyStringToIndexFunction a,PropertyIndexToStringFunction b,void* context)
{
    number(5);bool valid=p&&a==&index&&b==&name&&context==expectedContext;parentpairs::scalar(*cap,valid);
    if(!valid)cap->issue=autotest::Capture::InvalidReport;
    throw 73;
}
void snapshot(CDescriptorProp* p)
{
    cap->addText(p->m_sName);cap->addText(p->m_sDescription);cap->addText(p->m_sCategory);
    number(p->m_pInterpreter!=NULL);number(p->m_pSetFunction!=NULL);number(p->m_pGetFunction!=NULL);
    number(p->m_eType);number(p->m_iFlags);number(p->m_pValueBuffer!=NULL);
    number(p->m_DefaultValue.size());number(p->m_LinkedProperties.size());
    number(p->m_DefaultValue.m_nCapacity);number(p->m_DefaultValue.m_nGrowBy);number(p->m_DefaultValue.m_pData!=NULL);
    number(p->m_LinkedProperties.m_nCapacity);number(p->m_LinkedProperties.m_nGrowBy);number(p->m_LinkedProperties.m_pData!=NULL);
    for(unsigned i=0;i<p->m_DefaultValue.size();++i)number(p->m_DefaultValue[i].m_uValue);
}
void throwCopy(CDescriptorProp* self,CDescriptorProp& source,CEditorBaseObject* object)
{
    number(6);bool valid=self==destination&&&source==expectedSource&&object==expectedObject;parentpairs::scalar(*cap,valid);
    snapshot(self);
    if(!valid||!self->m_sName.empty()||!self->m_sDescription.empty()||!self->m_sCategory.empty()||self->m_eType!=VARIABLE_TYPE_NOT_SET||self->m_iFlags||self->m_pInterpreter||self->m_pValueBuffer||self->m_DefaultValue.size()||self->m_LinkedProperties.size()||self->m_DefaultValue.m_nGrowBy!=10||self->m_LinkedProperties.m_nGrowBy!=10)cap->issue=autotest::Capture::InvalidReport;
    unwindReference->setObject(self);
    // Exercise actual members' unwind after the out-of-line copy throws.
    self->m_sName.assign(300+seed,L'n');self->m_sDescription.assign(400+seed,L'd');self->m_sCategory.assign(500+seed,L'c');
    for(unsigned i=0;i<17;++i){UNIONDATA32BIT v;v.m_uValue=i+seed;self->m_DefaultValue.add(v);self->m_LinkedProperties.add(&source);}
    throw 91;
}
void setterSide(void* raw,autotest::Capture& out,bool ours)
{
    seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;destroyed=freed=callbackCalls=0;
    CDescriptorProp p(L"category",L"property",L"description",NULL,NULL,VARIABLE_TYPE_INTEGER,seed);
    CEditorBaseObject object;expectedObject=&object;int context=seed;expectedContext=seed%3?&context:NULL;
    bool existing=seed%2;Witness* witness=existing?new Witness:NULL;p.m_pInterpreter=witness;
    TSafePointer<CDescriptorPropertyInterpreter> reference;reference.setObject(witness);
    PropertyStringToIndexFunction a=seed/2%4==1||seed/2%4==3?NULL:&index;
    PropertyIndexToStringFunction b=seed/2%4==2||seed/2%4==3?NULL:&name;
    bool fault=!existing&&a&&b&&seed%16==0;int caught=0;
    detour::Set patches;if(fault)TL_REDIRECT(patches,parentInterpreterCtor,&throwInterpreter);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    typedef void(*Fn)(CDescriptorProp*,PropertyStringToIndexFunction,PropertyIndexToStringFunction,void*);Fn fn=ours?parentPropSetNew:parentPropSetOld;
    if(!autotest::beginInvocation(out,fn))return;try{fn(&p,a,b,expectedContext);}catch(int n){caught=n;}out.callCompleted=1;
    number(caught);number(destroyed);number(freed);number(p.m_pInterpreter==witness);number(p.m_pInterpreter!=NULL);number(reference.getObject()==NULL);
    bool removed=existing&&(!a||!b);
    if(removed){if(p.m_pInterpreter!=witness||destroyed!=1||freed!=1||reference.getObject()!=NULL)out.issue=autotest::Capture::InvalidReport;p.m_pInterpreter=NULL;}
    else if(!fault&&a&&b){if(!p.m_pInterpreter)out.issue=autotest::Capture::InvalidReport;else{number(p.m_pInterpreter->GetValue(NULL,&object,std::wstring(seed%3?L"probe":L"")));out.addText(p.m_pInterpreter->GetValue(NULL,&object,seed+31));}}
    if(fault&&caught!=73)out.issue=autotest::Capture::InvalidReport;
    number(callbackCalls);out.addHeapInUse();
    if(p.m_pInterpreter){delete p.m_pInterpreter;p.m_pInterpreter=NULL;}
    number(destroyed);number(freed);number(reference.getObject()==NULL);
}
void copySide(void* raw,autotest::Capture& out,bool ours)
{
    seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;
    CDescriptorProp source(seed%3?std::wstring(20+seed,L'c'):L"",seed%5?std::wstring(31+seed,L'n'):L"",L"different",NULL,NULL,static_cast<EVARIABLE_TYPES>(seed%10),seed*7);
    for(unsigned i=0;i<seed%14;++i){UNIONDATA32BIT v;v.m_uValue=seed*19+i;source.m_DefaultValue.add(v);source.m_LinkedProperties.add(&source);}
    CEditorBaseObject object;expectedObject=seed%3?&object:NULL;expectedSource=&source;
    CDescriptorPropertyInterpreter borrowed(&index,&name,NULL);
    if(!expectedObject&&seed%2)source.m_pInterpreter=&borrowed;
    if(seed%5==1){source.m_pSetFunction=reinterpret_cast<void*>(&setter);source.m_pGetFunction=reinterpret_cast<void*>(&getter);source.m_eType=VARIABLE_TYPE_INTEGER;}
    for(unsigned i=0;i<8;++i)getterValues[i].m_uValue=seed*101+i;
    TSafePointer<CDescriptorProp> reference;unwindReference=&reference;
    void* memory=CDescriptorProp::operator new(sizeof(CDescriptorProp));std::memset(memory,0xa5,sizeof(CDescriptorProp));destination=static_cast<CDescriptorProp*>(memory);
    bool absent=seed%4==0;bool fault=!absent&&seed%4==3;detour::Set patches;if(fault)TL_REDIRECT(patches,parentCopyCall,&throwCopy);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    int caught=0,constructed=g_iTotalCountOfObjects;
    typedef void(*Fn)(CDescriptorProp*,CDescriptorProp*,CEditorBaseObject*);Fn fn=ours?parentPropCopyNew:parentPropCopyOld;
    if(!autotest::beginInvocation(out,fn))return;try{fn(destination,absent?NULL:&source,expectedObject);}catch(int n){caught=n;}out.callCompleted=1;
    number(caught);number(g_iTotalCountOfObjects-constructed);number(reference.getObject()==NULL);
    if(!caught){snapshot(destination);number(destination->m_pSetFunction==source.m_pSetFunction);number(destination->m_pGetFunction==source.m_pGetFunction);number(destination->m_pInterpreter==source.m_pInterpreter);unsigned sourceCount=source.m_DefaultValue.size();source.m_sName=L"mutated";source.m_DefaultValue.clear();snapshot(destination);number(sourceCount);if(destination->m_pInterpreter==&borrowed)destination->m_pInterpreter=NULL;destination->~CDescriptorProp();}
    else if(!fault||caught!=91||reference.getObject()!=NULL)out.issue=autotest::Capture::InvalidReport;
    CDescriptorProp::operator delete(memory);out.addHeapInUse();
    source.m_pInterpreter=NULL;
}
void sa(void*p,autotest::Capture&c){setterSide(p,c,false);}void sb(void*p,autotest::Capture&c){setterSide(p,c,true);}
void ca(void*p,autotest::Capture&c){copySide(p,c,false);}void cb(void*p,autotest::Capture&c){copySide(p,c,true);}
}
TL_TEST(parent_descriptor_interpreter_functions){return parentpairs::run(host,"parent_descriptor_interpreter_functions",(uintptr_t)parentPropSetOld,96,sa,sb);}
TL_TEST(parent_descriptor_copy_ctor){return parentpairs::run(host,"parent_descriptor_copy_ctor",(uintptr_t)parentPropCopyOld,96,ca,cb);}
