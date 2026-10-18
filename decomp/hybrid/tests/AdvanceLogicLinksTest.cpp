#include "ParentPairs.h"
#include "LogicLink.h"
#include "LogicObject.h"
#include "LogicWrapper.h"
#include "DataGroup.h"
#include <fstream>
#include <unistd.h>
TL_ORIGINAL(void,oldSave,(CLogicLink*,CDataGroup*),"_ZN10CLogicLink25saveLogicLinksToDataGroupEP10CDataGroup")
extern "C" void newSave(CLogicLink*,CDataGroup*) __asm__("_ZN10CLogicLink25saveLogicLinksToDataGroupEP10CDataGroup");
TL_ORIGINAL(void,oldBinary,(CLogicLink*,std::ofstream*),"_ZN10CLogicLink26saveLogicLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE")
extern "C" void newBinary(CLogicLink*,std::ofstream*) __asm__("_ZN10CLogicLink26saveLogicLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE");
namespace {
void side(void* raw,autotest::Capture& out,bool ours,bool binary){unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;const unsigned ids[]={0,1,0x7fffffff,0x80000000u,~0u};CLogicObject target(NULL,17,ids[seed%5]);std::wstring a=seed%3?L"output Ж Ω":L"",b=seed%4?L"input é":L"";a.append(seed/5,L'x');b.append(seed/7,L'y');if(seed%8==0)a.append(1,wchar_t(0));if(seed%9==0)b.append(1,wchar_t(0));CLogicWrapper input(NULL,123,b),output(NULL,456,a);CLogicLink link(NULL,NULL,&output,&target,&input);
 if(binary){char path[]="/tmp/otl-advance-link-XXXXXX";int fd=mkstemp(path);if(fd<0){out.issue=autotest::Capture::InvalidReport;return;}close(fd);std::ofstream stream(path,std::ios::binary);typedef void(*Fn)(CLogicLink*,std::ofstream*);Fn fn=ours?newBinary:oldBinary;autotest::invoke(out,fn,&link,&stream);stream.close();std::ifstream file(path,std::ios::binary);char bytes[1024];file.read(bytes,sizeof(bytes));unsigned count=file.gcount();parentpairs::scalar(out,count);out.add(bytes,count);file.close();unlink(path);
 }else{CDataGroup data(L"ROOT",NULL,2,2,NULL);data.AddDataGroup(L"BEFORE");typedef void(*Fn)(CLogicLink*,CDataGroup*);Fn fn=ours?newSave:oldSave;autotest::invoke(out,fn,&link,&data);parentpairs::scalar(out,data.GetNumberOfDataGroups());CDataGroup* group=data.GetDataGroup(1);out.addText(group->GetGroupName());parentpairs::scalar(out,group->GetNumberOfDataValues());int id=group->GetDataValue(L"LINKINGTO",999);parentpairs::scalar(out,id);out.addText(group->GetDataValue(L"OUTPUTNAME",L"missing"));out.addText(group->GetDataValue(L"INPUTNAME",L"missing"));}}
void a(void*p,autotest::Capture&c){side(p,c,false,false);}void b(void*p,autotest::Capture&c){side(p,c,true,false);}void ba(void*p,autotest::Capture&c){side(p,c,false,true);}void bb(void*p,autotest::Capture&c){side(p,c,true,true);}
}
TL_TEST(advance_logic_link_group){return parentpairs::run(host,"advance_logic_link_group",(uintptr_t)oldSave,48,a,b);}
TL_TEST(advance_logic_link_binary){return parentpairs::run(host,"advance_logic_link_binary",(uintptr_t)oldBinary,48,ba,bb);}
