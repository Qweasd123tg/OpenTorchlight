#include <cstring>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#define private public
#include "DynamicPropertyFile.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(unsigned,oString,nString,(CDynamicPropertyFile*,const std::wstring&,std::wstring,bool),"_ZN20CDynamicPropertyFile22GetStringPropertyIndexERKSbIwSt11char_traitsIwESaIwEES3_b")
DECL(unsigned,oFloat,nFloat,(CDynamicPropertyFile*,const std::wstring&,float,bool),"_ZN20CDynamicPropertyFile21GetFloatPropertyIndexERKSbIwSt11char_traitsIwESaIwEEfb")
DECL(unsigned,oInt,nInt,(CDynamicPropertyFile*,const std::wstring&,int,bool),"_ZN20CDynamicPropertyFile19GetIntPropertyIndexERKSbIwSt11char_traitsIwESaIwEEib")
#undef DECL
namespace {
struct Case{unsigned mode,seed;};
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);uint64_t bytes[(sizeof(CDynamicPropertyFile)+7)/8];std::memset(bytes,0,sizeof(bytes));CDynamicPropertyFile*self=reinterpret_cast<CDynamicPropertyFile*>(bytes);new(&self->m_intValues)std::vector<int>();new(&self->m_floatValues)std::vector<float>();new(&self->m_stringValues)std::vector<std::wstring>();new(&self->m_nonLocalVariables)std::vector<std::wstring>();new(&self->m_intIndices)std::map<std::wstring,unsigned>();new(&self->m_floatIndices)std::map<std::wstring,unsigned>();new(&self->m_stringIndices)std::map<std::wstring,unsigned>();const wchar_t*names[]={L"",L"a",L"A",L"aa",L"Ж",L"missing"};unsigned bits[]={0x80000000,0,0x3f800000,0x7fc00001,0x7f800000,0xff800000};
 if(c.seed&16){self->m_intValues.reserve(16);self->m_floatValues.reserve(16);self->m_stringValues.reserve(16);self->m_nonLocalVariables.reserve(16);}
 for(unsigned i=0;i<c.seed%6;++i){self->m_intIndices[names[i]]=i;self->m_floatIndices[names[i]]=i;self->m_stringIndices[names[i]]=i;self->m_intValues.push_back(int(i)-3);self->m_floatValues.push_back(float(i)-0.5f);self->m_stringValues.push_back(names[(i+2)%6]);if(c.seed&8)self->m_nonLocalVariables.push_back(names[i]);}
 for(unsigned i=0;i<4;++i){std::wstring name=names[((c.seed/3)+(i%2))%6],text=names[(c.seed+i)%6];float value;std::memcpy(&value,&bits[(c.seed+i)%6],4);unsigned result;
 if(c.mode==0){unsigned(*fn)(CDynamicPropertyFile*,const std::wstring&,std::wstring,bool)=ours?nString:oString;if(i==0&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,text,(c.seed+i)&1);}
 else if(c.mode==1){unsigned(*fn)(CDynamicPropertyFile*,const std::wstring&,float,bool)=ours?nFloat:oFloat;if(i==0&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,value,(c.seed+i)&1);}
 else{unsigned(*fn)(CDynamicPropertyFile*,const std::wstring&,int,bool)=ours?nInt:oInt;if(i==0&&!autotest::beginInvocation(out,fn))return;result=fn(self,name,int(c.seed)*int(i)-123,(c.seed+i)&1);}out.add(&result,4);}out.callCompleted=1;
 unsigned size=self->m_intValues.size();out.add(&size,4);for(unsigned i=0;i<size;++i)out.add(&self->m_intValues[i],4);size=self->m_floatValues.size();out.add(&size,4);for(unsigned i=0;i<size;++i)out.add(&self->m_floatValues[i],4);size=self->m_stringValues.size();out.add(&size,4);for(unsigned i=0;i<size;++i)out.addText(self->m_stringValues[i]);size=self->m_nonLocalVariables.size();out.add(&size,4);for(unsigned i=0;i<size;++i)out.addText(self->m_nonLocalVariables[i]);std::map<std::wstring,unsigned>*maps[]={&self->m_intIndices,&self->m_floatIndices,&self->m_stringIndices};for(unsigned g=0;g<3;++g){size=maps[g]->size();out.add(&size,4);for(std::map<std::wstring,unsigned>::iterator j=maps[g]->begin();j!=maps[g]->end();++j){out.addText(j->first);out.add(&j->second,4);}maps[g]->~map();}self->m_intValues.~vector();self->m_floatValues.~vector();self->m_stringValues.~vector();self->m_nonLocalVariables.~vector();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned m,const char*n,uintptr_t address){autotest::Coverage coverage(n,address);for(unsigned i=0;i<120;++i){Case c={m,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    property mode %u seed %u issue %u/%u exits %d/%d\n",m,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(state_property_string_index,0,oString)
TEST(state_property_float_index,1,oFloat)
TEST(state_property_int_index,2,oInt)
