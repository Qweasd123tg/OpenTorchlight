#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "StringUtilities.h"
#include <fenv.h>
#include <cerrno>
#include <clocale>
#include <cstring>
#include <limits>
TL_ORIGINAL(unsigned int, oldArrayN, (const std::string&,float*,unsigned int,std::string), "_ZN7STRINGS18GetArrayValueFloatERKSsPfjSs")
extern "C" unsigned int newArrayN(const std::string&,float*,unsigned int,std::string) __asm__("_ZN7STRINGS18GetArrayValueFloatERKSsPfjSs");
TL_ORIGINAL(unsigned int, oldArrayW, (const std::wstring&,float*,unsigned int,std::wstring), "_ZN7STRINGS18GetArrayValueFloatERKSbIwSt11char_traitsIwESaIwEEPfjS3_")
extern "C" unsigned int newArrayW(const std::wstring&,float*,unsigned int,std::wstring) __asm__("_ZN7STRINGS18GetArrayValueFloatERKSbIwSt11char_traitsIwESaIwEEPfjS3_");
TL_FUNCTION(arrayTokensN,"_ZN7STRINGS14TokenizeStringEPSt5queueISsSt5dequeISsSaISsEEERKSsPKc")
TL_FUNCTION(arrayTokensW,"_ZN7STRINGS14TokenizeStringEPSt5queueISbIwSt11char_traitsIwESaIwEESt5dequeIS4_SaIS4_EEERKS4_PKw")
namespace {
struct Case { unsigned text,capacity,rounding,negative,wide,observed; };
const Case* activeCase;autotest::Capture* boundaryOutput;unsigned tokenCalls;
void tokensN(std::queue<std::string>*queue,const std::string&text,const char*separators){++tokenCalls;boundaryOutput->addText(text);boundaryOutput->addText(std::string(separators));unsigned before=queue->size();boundaryOutput->add(&before,4);const unsigned counts[]={0,1,2,3,4,7,65,131};const char*values[]={"1.25","-0","nan","1e999","0.1","bad"};for(unsigned i=0;i<counts[activeCase->text%8];++i)queue->push(values[i%6]);}
void tokensW(std::queue<std::wstring>*queue,const std::wstring&text,const wchar_t*separators){++tokenCalls;boundaryOutput->addText(text);boundaryOutput->addText(std::wstring(separators));unsigned before=queue->size();boundaryOutput->add(&before,4);const unsigned counts[]={0,1,2,3,4,7,65,131};const wchar_t*values[]={L"1.25",L"-0",L"nan",L"1e999",L"0.1",L"bad"};for(unsigned i=0;i<counts[activeCase->text%8];++i)queue->push(values[i%6]);}
const char* texts[]={"", "1", "1,2", "1,2,3", "1,2,3,4", "1,2,3,4,5", ",,1,,,2,,", " , ;\t\n", "1;2 3\t4\n5", "0,-0,+0,-0.0", "0.1,0.2,1.000000059604644775390625,16777217", "nan,-nan,nan(payload),inf,-infinity", "1e39,-1e39,1e-46,-1e-46,1.1754943508222875e-38", "1e9999,-1e9999,1e-9999", "abc,12xyz,0x1.fp2,-7.5suffix", "  -3.25 , +4.5 ,\r 6", "12.5:13.5:14.5", "123,456", "1,2,3", "4 5 6", "1\n2\n3", "1\x7f,2\xff,3", "1,2,3", "4,5,6", "1,2,3", "1,2,3", "", ""};
const char* delimiters[]={",",";, \t\n", ":", "", "12", ",\0;", "\n", ","};
unsigned capacities[]={0,1,2,3,5,9,64,130};
int rounds[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
void input(unsigned id,std::string&text,std::string&sep){text=texts[id];sep=delimiters[id%8];if(id==5||id==6||id==11||id==12||id==13||id==14||id==15)sep=",";if(id==17){text.assign("1\0,2,3",7);sep=",";}if(id==18){sep.assign(",\0;",3);}if(id==22){text="1,2,3";sep=",";}if(id==23){text="4,5,6";sep="5";}if(id==24){text="1,2,3";sep=",";}if(id==25){text="1,2,3";sep="";}if(id>=26){sep=",";text="";for(unsigned i=0;i<(id==26?65u:131u);++i){if(i)text+=",";text+=i%3==0?"-0":i%3==1?"0.100000001490116119384765625":"0x1.fffffep+127";}}}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);activeCase=&c;boundaryOutput=&out;tokenCalls=0;std::setlocale(LC_ALL,"C");std::string text,sep;input(c.text,text,sep);std::wstring wideText,wideSep;for(unsigned i=0;i<text.size();++i)wideText+=wchar_t(static_cast<unsigned char>(text[i]));for(unsigned i=0;i<sep.size();++i)wideSep+=wchar_t(static_cast<unsigned char>(sep[i]));if(c.wide&&c.text==24){wideText=L"1\x3001-2.5\x3001nan\x3001inf";wideSep=L"\x3001";}if(c.wide&&c.text==25){wideText=L"\x0661\x0662,\x2212" L"3,\x0430";wideSep=L",";}
 if(c.observed){sep.clear();wideSep.clear();}
 detour::Set redirects;if(c.observed){TL_REDIRECT(redirects,arrayTokensN,&tokensN);TL_REDIRECT(redirects,arrayTokensW,&tokensW);if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}}
 unsigned words[272];for(unsigned i=0;i<272;++i)words[i]=0x3e800000u+i*997u;float*values=reinterpret_cast<float*>(words+4);float*dest=c.capacity==8?NULL:values;unsigned capacity=c.capacity==8?~0u:capacities[c.capacity];fesetround(rounds[c.rounding]);feclearexcept(FE_ALL_EXCEPT);if(c.text%3==0)feraiseexcept(FE_DIVBYZERO);errno=c.text%2?EDOM:0;unsigned result=0;
 if(c.wide){typedef unsigned int(*Fn)(const std::wstring&,float*,unsigned int,std::wstring);Fn fn=ours?newArrayW:oldArrayW;if(autotest::beginInvocation(out,fn)){result=fn(wideText,dest,capacity,wideSep);out.callCompleted=1;}}
 else{typedef unsigned int(*Fn)(const std::string&,float*,unsigned int,std::string);Fn fn=ours?newArrayN:oldArrayN;if(autotest::beginInvocation(out,fn)){result=fn(text,dest,capacity,sep);out.callCompleted=1;}}
 int exceptions=fetestexcept(FE_ALL_EXCEPT),error=errno,round=fegetround();out.add(&tokenCalls,4);if(ours&&c.negative)words[4]^=1;out.add(&result,sizeof result);out.add(words,sizeof words);out.add(&exceptions,sizeof exceptions);out.add(&error,sizeof error);out.add(&round,sizeof round);if(c.wide){out.addText(wideText);out.addText(wideSep);}else{out.addText(text);out.addText(sep);} }
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}unsigned operation;
int worker(const tlhybrid_host*host){unsigned wide=operation&1,observed=operation>=2;const char*names[]={"array_float_narrow_recovery","array_float_wide_recovery","array_float_narrow_observed","array_float_wide_observed"};const char*name=names[operation];autotest::Coverage coverage(name,wide?reinterpret_cast<uintptr_t>(oldArrayW):reinterpret_cast<uintptr_t>(oldArrayN));unsigned total=0,excluded=0;for(unsigned text=0;text<28;++text)for(unsigned capacity=0;capacity<9;++capacity)for(unsigned round=0;round<4;++round){
 // With a non-null output, the original tokenizer never advances on an empty
 // separator. Those inputs are exercised through a typed tokenizer boundary
 // below, and never admitted as equal timeouts in native coverage.
 if(!observed&&capacity!=8&&(text==3||text==19||(!wide&&text==25))){++excluded;continue;}
 ++total;Case c={text,capacity,round,0,wide,observed};autotest::Outcome&a=autotest::g_outcomes[0];autotest::Outcome&b=autotest::g_outcomes[1];autotest::runChild(original,&c,a,4000,16000);autotest::runChild(candidate,&c,b,4000,16000);if(coverage.observe(host,a,b)){host->log("    %s text%u capacity%u round%u status%d/%d valid%u/%u issue%u/%u completed%u/%u\n",name,text,capacity,round,a.childStatus,b.childStatus,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted);coverage.report(host);return 1;}}
 coverage.report(host);host->log("    %s native-nonterminating inputs excluded %u; tested with typed tokenizer boundary\n",name,excluded);Case c={4,4,0,1,wide,observed};autotest::Outcome&a=autotest::g_outcomes[0];autotest::Outcome&b=autotest::g_outcomes[1];autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    %s negative detected%u completed%u\n",name,unsigned(detected),unsigned(complete));return coverage.completed!=total||!complete||!detected;}
}
TL_TEST(array_float_narrow_recovery){operation=0;return systems_fixture::isolated(worker,host,300);}
TL_TEST(array_float_wide_recovery){operation=1;return systems_fixture::isolated(worker,host,300);}
TL_TEST(array_float_narrow_observed){operation=2;return systems_fixture::isolated(worker,host,300);}
TL_TEST(array_float_wide_observed){operation=3;return systems_fixture::isolated(worker,host,300);}
