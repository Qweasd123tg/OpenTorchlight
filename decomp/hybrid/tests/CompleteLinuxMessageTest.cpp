#include "AutoTest.h"
#include "tests/Detour.h"
#include "LinuxUtils.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <cstdarg>
TL_ORIGINAL(int,linuxMessageOriginal,(void*,const char*,const char*,int),"_Z11MessageBoxAPvPKcS1_i")
extern "C" int linuxMessageCandidate(void*,const char*,const char*,int) __asm__("_Z11MessageBoxAPvPKcS1_i");
namespace {
struct Case{int flags,result;unsigned text;};const Case*current;autotest::Capture*cap;
void word(unsigned n){cap->add(&n,sizeof(n));}void text(const char*s){word(s!=NULL);if(s)cap->addText(std::string(s));}
int lock(){word(1);return -1;}void unlock(){word(2);}double wait(double t){word(3);cap->add(&t,sizeof(t));return 0;}
void title(const char*s){word(4);text(s);}
int choice(const char*format,const char*a,const char*b,const char*c,...){word(5);text(format);text(a);text(b);text(c);va_list args;va_start(args,c);text(va_arg(args,const char*));va_end(args);return current->result;}
int print(FILE*stream,const char*format,...){word(6);word(stream==stderr);text(format);if(std::strcmp(format,"MessageBox: %s :: %s\n")){cap->issue=autotest::Capture::InvalidReport;return 0;}va_list args;va_start(args,format);text(va_arg(args,const char*));text(va_arg(args,const char*));va_end(args);return 0;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;detour::Set d;d.redirect(reinterpret_cast<char*>(&Fl::lock),reinterpret_cast<char*>(&Fl::lock),&lock);d.redirect(reinterpret_cast<char*>(&Fl::unlock),reinterpret_cast<char*>(&Fl::unlock),&unlock);double(*waitFn)(double)=&Fl::wait;d.redirect(reinterpret_cast<char*>(waitFn),reinterpret_cast<char*>(waitFn),&wait);d.redirect(reinterpret_cast<char*>(&fl_message_title),reinterpret_cast<char*>(&fl_message_title),&title);d.redirect(reinterpret_cast<char*>(&fl_choice),reinterpret_cast<char*>(&fl_choice),&choice);d.redirect(reinterpret_cast<char*>(&fprintf),reinterpret_cast<char*>(&fprintf),&print);if(d.failed())_exit(64);
 const char*texts[]={"","hello %s %n","данные: 游戏"};int(*fn)(void*,const char*,const char*,int)=ours?linuxMessageCandidate:linuxMessageOriginal;if(autotest::beginInvocation(out,fn)){int result=fn(reinterpret_cast<void*>(0x1234),texts[c.text],texts[2-c.text],c.flags);out.callCompleted=1;out.add(&result,sizeof(result));}d.restore();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_linux_message_box){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_linux_message_box",reinterpret_cast<uintptr_t>(&linuxMessageOriginal));for(unsigned flags=0;flags<34;++flags)for(int result=-1;result<3;++result)for(unsigned text=0;text<3;++text){Case c={flags<32?static_cast<int>(flags):flags==32?-1:0x80000001,result,text};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_linux_message_box",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
