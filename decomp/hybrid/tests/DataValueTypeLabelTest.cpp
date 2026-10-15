#include <cstring>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#define private public
#include "DataValue.h"
#undef private
TL_ORIGINAL(std::wstring,oldType,(CDataValue*),"_ZN10CDataValue20GetValueTypeAsStringEv")
extern "C" std::wstring newType(CDataValue*) __asm__("_ZN10CDataValue20GetValueTypeAsStringEv");
namespace {struct Case{unsigned value;};void side(void*raw,autotest::Capture&out,bool ours){unsigned value=static_cast<Case*>(raw)->value;uint64_t object[7];std::memset(object,0xa5,sizeof(object));CDataValue*self=reinterpret_cast<CDataValue*>(object);self->m_eType=static_cast<CDataValue::EDATAVALUETYPES>(value);unsigned char before[sizeof(object)];std::memcpy(before,object,sizeof(object));typedef std::wstring(*Fn)(CDataValue*);Fn fn=ours?newType:oldType;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self);out.callCompleted=1;unsigned length=result.size();out.add(&length,4);out.add(result.data(),length*sizeof(wchar_t));if(std::memcmp(before,object,sizeof(object)))out.issue=autotest::Capture::InvalidReport;out.add(object,sizeof(object));}void original(void*c,autotest::Capture&out){side(c,out,false);}void candidate(void*c,autotest::Capture&out){side(c,out,true);}}
TL_TEST(data_value_type_labels){autotest::Coverage coverage("data_value_type_labels",reinterpret_cast<uintptr_t>(&oldType));const unsigned types[]={0,1,2,3,4,5,6,7,8,9,10,31,0x7fffffff,0x80000000u,0xffffffffu};for(unsigned i=0;i<15;++i){Case c={types[i]};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    type label %u exits %d/%d\n",c.value,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
