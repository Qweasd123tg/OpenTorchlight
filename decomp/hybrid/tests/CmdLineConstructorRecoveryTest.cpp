#include "AutoTest.h"
#include "CmdLineParser.h"
#include <cstring>
TL_ORIGINAL(void,oldCommandCtor,(CCmdLineParser*,const std::wstring&),"_ZN14CCmdLineParserC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,commandDtor,(CCmdLineParser*),"_ZN14CCmdLineParserD1Ev")
extern "C" void newCommandCtor(CCmdLineParser*,const std::wstring&) __asm__("_ZN14CCmdLineParserC1ERKSbIwSt11char_traitsIwESaIwEE");
namespace {
union Storage{long double alignment;char data[sizeof(CCmdLineParser)];};
struct Case{unsigned seed;bool negative;};
std::wstring input(unsigned seed){
 const wchar_t* words[]={L"",L" ",L"  ",L"\t",L"a",L"-a",L"--a",L"/a",L"a=1",L"a,b,c",L"a=1=2",L"a,b=3,4",L"=a",L"a=",L"a,,b,",L"a===b==c=",L"A=0",L"a=two",L"\"a b\"",L"日本語=значение",L"=",L",",L"a\tb",L"a\nb"};
 if(seed<24)return words[seed];
 if(seed<600){unsigned value=seed-24;return std::wstring(words[value%24])+L" "+words[value/24%24];}
 if(seed<616){std::wstring result;unsigned count=63+(seed-600)*9;for(unsigned i=0;i<count;++i){result+=words[(i*7+seed)%24];result+=(i%3==0?L" ":L"  ");}return result;}
 std::wstring result(L"x=ab\0cd z=2",12);result[0]=wchar_t('a'+seed%4);return result;
}
void number(autotest::Capture&out,long long value){out.add(&value,sizeof(value));}
void side(void*raw,autotest::Capture&out,bool ours){
 const Case&c=*static_cast<Case*>(raw);std::wstring command=input(c.seed);Storage storage;std::memset(storage.data,c.seed&1?0x5a:0,sizeof(storage.data));
 CCmdLineParser*parser=reinterpret_cast<CCmdLineParser*>(storage.data);int before=g_iTotalCountOfObjects;
 typedef void(*Function)(CCmdLineParser*,const std::wstring&);Function function=ours?newCommandCtor:oldCommandCtor;
 if(!autotest::beginInvocation(out,function))return;function(parser,command);out.callCompleted=1;
 if(ours&&c.negative)parser->m_params[L"negative control"].push_back(L"detected");
 out.addText(command);number(out,g_iTotalCountOfObjects-before);number(out,parser->m_params.size());
 for(std::map<std::wstring,std::vector<std::wstring> >::const_iterator i=parser->m_params.begin();i!=parser->m_params.end();++i){out.addText(i->first);number(out,i->second.size());number(out,i->second.capacity());for(unsigned j=0;j<i->second.size();++j)out.addText(i->second[j]);}
 commandDtor(parser);number(out,g_iTotalCountOfObjects-before);
}
void a(void*p,autotest::Capture&out){side(p,out,false);}void b(void*p,autotest::Capture&out){side(p,out,true);}
}
TL_TEST(command_constructor_recovery){
 autotest::Coverage coverage("command_constructor_recovery",0xc8b180);
 for(unsigned i=0;i<624;++i){Case c={i,false};autotest::Outcome before,after;autotest::runChild(a,&c,before);autotest::runChild(b,&c,after);
  if(coverage.observe(host,before,after)){host->log("    command ctor seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,before.childStatus,after.childStatus,before.capture.issue,after.capture.issue,(unsigned long)before.capture.length,(unsigned long)after.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);Case c={19,true};autotest::Outcome before,after;autotest::runChild(a,&c,before);autotest::runChild(b,&c,after);bool detected=before.capture.length!=after.capture.length||std::memcmp(before.capture.data,after.capture.data,before.capture.length);host->log("    command ctor negative control detected%u\n",detected?1u:0u);
 return !detected||autotest::incomplete(before)||autotest::incomplete(after)||!before.reportValid||!after.reportValid||before.childStatus||after.childStatus;
}
