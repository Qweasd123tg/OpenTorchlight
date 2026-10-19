#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "LinuxUtils.h"
#include <fcntl.h>
#include <cerrno>
TL_ORIGINAL(void,lqOld,(CLevel*,const std::wstring&),"_ZN6CLevel26saveRoomLayoutForQuickLoadERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void lqNew(CLevel*,const std::wstring&) __asm__("_ZN6CLevel26saveRoomLayoutForQuickLoadERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(lqLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(lqOpen,"_Z9_wfopen_sPP8_IO_FILEPKwS3_")
TL_FUNCTION(lqParse,"_Z26parseDataGroupForRoomPieceP10CDataGroupP8_IO_FILE")
namespace {
autotest::Capture*output;unsigned seed;CDataGroup*loaded;FILE*file;int fileDescriptor;unsigned opens,parses;const std::wstring*input;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*4);}
void group(CDataGroup*p){wide(p->GetGroupName());number(p->m_pParent==NULL);number(p->m_DataValues.size());number(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)group(p->m_DataGroups[i]);}
void load(CDataGroup*p,const std::wstring&filename,CTimerStatics*t){loaded=p;number(1);wide(filename);number(&filename==input);number(t==NULL);wide(p->GetGroupName());number(p->m_pParent==NULL);number(p->m_DataValues.m_nGrowBy);number(p->m_DataGroups.m_nGrowBy);number(p->m_DataValues.size());number(p->m_DataGroups.size());for(unsigned i=0;i<seed%5;++i){CDataGroup*c=p->AddDataGroup(i==seed%5-1&&seed%3?L"OBJECTS":L"OTHER");for(unsigned j=0;j<(seed/5+i)%4;++j)c->AddDataGroup(j&1?L"PROPERTIES":L"CHILDREN");}}
int open(FILE**dest,const wchar_t*path,const wchar_t*mode){++opens;number(2);wide(path);wide(mode);if(!dest||!file)std::abort();*dest=file;return seed&1?0:17;}
void parse(CDataGroup*p,FILE*f){++parses;number(3);number(p==loaded);number(f==file);group(p);const char bytes[]="quickload-fixture";if(std::fwrite(bytes,1,sizeof bytes,file)!=sizeof bytes)std::abort();}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;loaded=NULL;opens=parses=0;finishlevel::Fixture owner;const wchar_t*names[]={L"",L"level.dat",L"path with spaces/room.layout",L"\x041a\x4e2d_\x1f642",L"\xd7ff\xe000\xffff\x10000\x10ffff",L"already.room",L"room.room.room"};std::wstring name=names[seed/5%7];if(seed/35%3==1){name+=L'\0';name+=L"hidden.dat";}if(seed/35%3==2)name.append(100+(seed%100),L'\x03a9');input=&name;file=std::tmpfile();if(!file){out.issue=autotest::Capture::InvalidReport;return;}fileDescriptor=fileno(file);
 detour::Set hooks;TL_REDIRECT(hooks,lqLoad,&load);TL_REDIRECT(hooks,lqOpen,&open);TL_REDIRECT(hooks,lqParse,&parse);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;std::fclose(file);return;}
 typedef void(*Fn)(CLevel*,const std::wstring&);Fn fn=ours?lqNew:lqOld;if(!autotest::beginInvocation(out,fn)){std::fclose(file);return;}fn(&owner.level,name);out.callCompleted=1;number(opens);number(parses);errno=0;int state=fcntl(fileDescriptor,F_GETFD);bool closed=state==-1&&errno==EBADF;number(closed);if(!closed)std::fclose(file);hooks.restore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1492210),8);if(!p)new(reinterpret_cast<void*>(0x1492210))std::wstring;autotest::Coverage coverage("level_quickload",reinterpret_cast<uintptr_t>(lqOld));for(unsigned i=0;i<512;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    quickload seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned z=0;z<a.capture.length&&z<b.capture.length;++z)if(a.capture.data[z]!=b.capture.data[z]){host->log("    firstdiff%u old%02x new%02x\n",z,(unsigned char)a.capture.data[z],(unsigned char)b.capture.data[z]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=512||coverage.missing||coverage.different;}
}
TL_TEST(complete_level_quickload){return systems_fixture::isolated(&worker,host);}
