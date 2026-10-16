#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <string>
#include <new>
#include <unistd.h>
#include "AutoTest.h"
#define private public
#include "DataGroup.h"
#include "DataValue.h"
#include "BinaryStyle.h"
#undef private
TL_ORIGINAL(void,oValues,(CBinaryStyle*,std::ofstream&,CDataGroup*),"_ZN12CBinaryStyle14SaveDataValuesERSt14basic_ofstreamIcSt11char_traitsIcEEP10CDataGroup")
extern "C" void nValues(CBinaryStyle*,std::ofstream&,CDataGroup*) __asm__("_ZN12CBinaryStyle14SaveDataValuesERSt14basic_ofstreamIcSt11char_traitsIcEEP10CDataGroup");
TL_ORIGINAL(void,oValueCtor,(CDataValue*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES,TRepository<std::wstring>*),"_ZN10CDataValueC1Ej14UNIONDATA64BITNS_15EDATAVALUETYPESEP11TRepositoryISbIwSt11char_traitsIwESaIwEEE")
TL_ORIGINAL(void,oValueDtor,(CDataValue*),"_ZN10CDataValueD1Ev")
namespace{
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);uint64_t gs[(sizeof(CDataGroup)+7)/8],styleStorage[(sizeof(CBinaryStyle)+7)/8];std::memset(gs,0,sizeof(gs));CDataGroup*group=reinterpret_cast<CDataGroup*>(gs);CBinaryStyle*style=reinterpret_cast<CBinaryStyle*>(styleStorage);new(&group->m_DataValues)TArrayList<CDataValue*>((seed%3)+1);uint64_t bits[]={0,1,0xffffffffffffffffULL,0x8000000000000000ULL,0x7ff0000000000000ULL,0x7ff8000012345678ULL,0x3ff4000000000000ULL};for(unsigned i=0;i<seed%13;++i){CDataValue*value=static_cast<CDataValue*>(CDataValue::operator new(sizeof(CDataValue)));UNIONDATA64BIT data;std::memcpy(&data,&bits[(i+seed)%7],8);oValueCtor(value,unsigned(-1),data,static_cast<CDataValue::EDATAVALUETYPES>((i+seed)%10),NULL);value->m_iNameID=seed*17+i;group->m_DataValues.add(value);}if(seed&16&&group->m_DataValues.size())group->m_DataValues.m_nCapacity=(seed/8)%2;char name[]="/tmp/otl-binary-storage-XXXXXX";int fd=mkstemp(name);if(fd<0){out.issue=autotest::Capture::InvalidReport;return;}close(fd);std::ofstream stream(name,std::ios::binary);if(seed%9==0)stream.setstate(std::ios::failbit);typedef void(*Fn)(CBinaryStyle*,std::ofstream&,CDataGroup*);Fn fn=ours?nValues:oValues;if(!autotest::beginInvocation(out,fn))return;fn(style,stream,group);out.callCompleted=1;unsigned state=stream.rdstate();out.add(&state,4);stream.close();FILE*input=fopen(name,"rb");if(!input){out.issue=autotest::Capture::InvalidReport;return;}unsigned char bytes[2048];unsigned count=fread(bytes,1,sizeof(bytes),input);out.add(&count,4);out.add(bytes,count);fclose(input);unlink(name);if(seed%9!=0){unsigned expected=4;for(unsigned i=0;i<group->m_DataValues.size();++i){unsigned index=i<group->m_DataValues.m_nCapacity?i:0;unsigned tag=(index+seed)%10;expected+=8+((tag==7||tag==3)?8:4);}if(count!=expected)out.issue=autotest::Capture::InvalidReport;}for(unsigned i=0;i<group->m_DataValues.size();++i){CDataValue*value=group->m_DataValues.m_pData[i];value->m_iNameID=unsigned(-1);oValueDtor(value);CDataValue::operator delete(value);}group->m_DataValues.~TArrayList();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(bulk_binary_values){autotest::Coverage coverage("bulk_binary_values",(uintptr_t)&oValues);for(unsigned seed=0;seed<130;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    binary seed %u issue %u/%u exits %d/%d\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
