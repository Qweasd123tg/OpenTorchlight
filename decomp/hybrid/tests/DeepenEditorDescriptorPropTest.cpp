#include <string>
#include <map>
#include "AutoTest.h"
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"
#include "EditorBaseObject.h"
#include "DataGroup.h"
TL_ORIGINAL(void,dpOldSerialize,(CDescriptorProp*,CDataGroup*,unsigned),"_ZN15CDescriptorProp17serializePropertyEP10CDataGroupj")
extern "C" void dpNewSerialize(CDescriptorProp*,CDataGroup*,unsigned) __asm__("_ZN15CDescriptorProp17serializePropertyEP10CDataGroupj");
TL_ORIGINAL(void,dpOldSet,(CDescriptorProp*,std::wstring,CEditorBaseObject*),"_ZN15CDescriptorProp24setPropertyValueByStringESbIwSt11char_traitsIwESaIwEEP17CEditorBaseObject")
extern "C" void dpNewSet(CDescriptorProp*,std::wstring,CEditorBaseObject*) __asm__("_ZN15CDescriptorProp24setPropertyValueByStringESbIwSt11char_traitsIwESaIwEEP17CEditorBaseObject");
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;CEditorBaseObject*object;unsigned callbacks;size_t textLength;
void n(unsigned x){cap->add(&x,4);}void bad(){cap->issue=autotest::Capture::InvalidReport;}
void setter(CEditorBaseObject*p,const void*data,unsigned count){++callbacks;if(p!=object)bad();n(count);if(count>1000){bad();return;}cap->add(data,count*4);}
UNIONDATA8BIT*getter(CEditorBaseObject*,unsigned&count){static UNIONDATA32BIT words[4];count=4;return reinterpret_cast<UNIONDATA8BIT*>(words);}
unsigned interpret(CEditorScene*s,CEditorBaseObject*p,const std::wstring&value,void*context){n(0x1234);if(s||p!=object||context!=cap)bad();cap->addText(value);return value.size()+17;}
std::wstring name(CEditorScene*,CEditorBaseObject*,unsigned,void*){return L"named";}
void tree(CDataGroup*p){cap->addText(p->GetGroupName());n(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i){CDataValue*v=p->m_DataValues[i];cap->addText(v->GetDataValueName());n(v->GetValueType());cap->addText(v->GetValueAsString());}n(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)tree(p->m_DataGroups[i]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;callbacks=0;unsigned type=c.seed%10;unsigned flags=0;if(c.mode==0){const unsigned bits[]={0,1,2,4,8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,0x800,0x1000,0x2000,0x4000,0x8000};flags=c.seed<17?bits[c.seed]:bits[c.seed%17]|bits[(c.seed/3)%17]|bits[(c.seed/7)%17];if(c.seed>100)flags=0xffff;}
 CEditorBaseObject real;object=&real;CDescriptorProp property(c.seed%3?L"cat":L"",c.seed%4?L"named":L"",c.seed%5?L"Ж description":L"",reinterpret_cast<void*>(&setter),reinterpret_cast<void*>(&getter),static_cast<EVARIABLE_TYPES>(type),flags);if(c.seed&32)property.m_pInterpreter=new CDescriptorPropertyInterpreter(&interpret,&name,cap);UNIONDATA32BIT item;item.m_uValue=0x12345678;for(unsigned i=0;i<c.seed%4;++i)property.m_DefaultValue.add(item);
 if(c.mode==0){CDataGroup data(L"root",NULL,1,1,NULL);data.AddDataValue(L"keep",12);data.AddDataGroup(L"PROPERTY")->AddDataValue(L"NAME",L"old",false);typedef void(*Fn)(CDescriptorProp*,CDataGroup*,unsigned);Fn fn=ours?dpNewSerialize:dpOldSerialize;if(!autotest::beginInvocation(out,fn))return;fn(&property,flags&0x80&&c.seed%2?NULL:&data,0x80000000u+c.seed);out.callCompleted=1;tree(&data);}
 else{const wchar_t*texts[]={L"",L"0",L"false",L"FALSE",L"true",L"12",L"-19",L"4294967295",L"1.25",L"-0.75,2.5,10,0,-11,27",L",",L",,1,,,2,",L"12,wrong,15",L" 12 , -17 ",L"Ж:field",L"0,1,false,true,F,f,other"};std::wstring value=texts[(c.seed/10)%16],original=value;textLength=value.size();CEditorBaseObject*arg=c.seed&1?object:NULL;typedef void(*Fn)(CDescriptorProp*,std::wstring,CEditorBaseObject*);Fn fn=ours?dpNewSet:dpOldSet;if(!autotest::beginInvocation(out,fn))return;fn(&property,value,arg);out.callCompleted=1;if(value!=original)bad();cap->addText(value);n(callbacks);if(property.m_pValueBuffer)out.add(property.m_pValueBuffer,((value.size()*4&~3u)+4));n(property.m_pValueBuffer!=NULL);}
 n(property.m_DefaultValue.size());for(unsigned i=0;i<property.m_DefaultValue.size();++i)n(property.m_DefaultValue[i].m_uValue);n(property.m_eType);n(property.m_iFlags);out.addText(property.m_sName);out.addText(property.m_sDescription);out.addText(property.m_sCategory);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t addr){autotest::Coverage coverage(name,addr);unsigned count=mode?320:180;for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){for(unsigned z=0;z<x.capture.length&&z<y.capture.length;++z)if(x.capture.data[z]!=y.capture.data[z]){h->log("    first difference %u %u/%u\n",z,unsigned((unsigned char)x.capture.data[z]),unsigned((unsigned char)y.capture.data[z]));break;}h->log("    descriptor prop mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_descriptor_serialize){return run(host,0,"deepen_editor_descriptor_serialize",(uintptr_t)&dpOldSerialize);}
TL_TEST(deepen_editor_descriptor_parse){return run(host,1,"deepen_editor_descriptor_parse",(uintptr_t)&dpOldSet);}
