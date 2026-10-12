// Bounded framing witnesses: both an index-gate mutant and a v19-extra-read
// mutant can finish on these all-initialized streams. Controlled reset isolates
// load framing here; genuine reset/load composition is tested in the main file.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,qrlbOld,(void*,FILE*,void*,unsigned),"_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
extern "C" void qrlbNew(void*,FILE*,void*,unsigned) __asm__("_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj");
TL_FUNCTION(qrlbSingleton,"_ZN15CDungeonManager12getSingletonEv")
TL_FUNCTION(qrlbLookup,"_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrlbReset,"_ZN6CQuest17reinitializeQuestEbb")
TL_FUNCTION(qrlbUnit,"_ZN14CQuestUnitData4loadEP8_IO_FILEi")
namespace qrlb {
typedef std::wstring Wide;
struct List {void** data;unsigned count,capacity,grow,pad;};
template<class T>T& at(void* p,unsigned offset){return *reinterpret_cast<T*>((char*)p+offset);}
static void *owner,*resource,*client,*dm,*group,*unit,*oldGuid;static FILE* file;static autotest::Capture* cap;
static unsigned kind,errors,resets,loads,lookups;static unsigned char expected[0x218];
static void need(bool x){if(!x)++errors;}static void n(unsigned x){cap->add(&x,4);}
static void* raw(unsigned bytes){void* p=autotest::allocate(bytes);if(!p)_exit(71);return p;}
static void* singleton(){return dm;}
static void* lookup(void* self,Wide name){need(self==dm&&name==L"Bounded framing");++lookups;return 0;}
static void reset(void* self,bool resolve,bool skip){need(self==owner&&resolve&&skip);++resets;at<void*>(self,0x1e8)=0;at<unsigned char>(self,0x24)=at<unsigned char>(self,0x26)=at<unsigned char>(self,0x209)=at<unsigned char>(self,0x210)=0;}
static void loadUnit(void* self,FILE* f,int version){need(self==unit&&f==file&&version==20);++loads;unsigned value=0;need(std::fread(&value,4,1,f)==1);at<unsigned>(self,0x3c)=value;}
static void side(void* context,autotest::Capture& out,bool candidate){
 kind=*(unsigned*)context;cap=&out;errors=resets=loads=lookups=0;autotest::g_arenaUsed=0;owner=raw(0x218);resource=raw(0x40);client=raw(0x3910);dm=raw(0x40);group=raw(24);unit=raw(0xc8);oldGuid=raw(0x40);
 at<void*>(owner,0x1d8)=resource;at<void*>(owner,0x1e8)=oldGuid;at<unsigned>(owner,0x20c)=0x11223344u;at<unsigned char>(owner,0x24)=at<unsigned char>(owner,0x26)=at<unsigned char>(owner,0x209)=at<unsigned char>(owner,0x210)=1;
 new((char*)owner+0x30)Wide(L"Bounded framing");void** clients=(void**)raw(8);clients[0]=client;at<void*>(resource,0x28)=clients;at<unsigned>(resource,0x30)=1;at<int>(client,0x1090)=100;at<unsigned>(unit,0x3c)=0x73747576u;
 List& inner=at<List>(group,0);inner.data=(void**)raw(8);inner.data[0]=unit;inner.count=inner.capacity=1;inner.grow=2;
 for(unsigned f=0;f<3;++f){List& l=at<List>(owner,0x130+f*24);l.data=(void**)raw(8);l.data[0]=group;l.count=(!kind&&!f)?1:0;l.capacity=1;l.grow=2;}
 unsigned char input[80];std::memset(input,0,sizeof(input));for(unsigned i=0;i<8;++i)input[i]=255;input[8]=17;input[12]=4;
 unsigned expectedPosition;if(!kind){input[16]=0x78;input[17]=0x56;input[18]=0x34;input[19]=0x12;input[36]=2;input[40]=1;expectedPosition=56;}else expectedPosition=44;
 // Original: no unit call, end56. Index-gate mutant: reads word44 as payload,
 // then zero inner/count headers at48/52/56, ends60. Both remain well-defined.
 // v19 original ends44. Extra-read mutant uses the zero at44 and ends48.
 file=std::tmpfile();if(!file)_exit(71);need(std::fwrite(input,1,sizeof(input),file)==sizeof(input));std::rewind(file);
 std::memcpy(expected,owner,0x218);at<unsigned>(expected,0x1c)=17;at<unsigned>(expected,0x20)=4;if(!kind)at<unsigned>(expected,0x20c)=0x12345678u;expected[0x24]=expected[0x209]=expected[0x210]=0;expected[0x26]=1;
 {detour::Set d;TL_REDIRECT(d,qrlbSingleton,&singleton);TL_REDIRECT(d,qrlbLookup,&lookup);TL_REDIRECT(d,qrlbReset,&reset);TL_REDIRECT(d,qrlbUnit,&loadUnit);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(void*,FILE*,void*,unsigned);Fn fn=candidate?&qrlbNew:&qrlbOld;if(!autotest::beginInvocation(out,fn))return;fn(owner,file,resource,kind?19:20);out.callCompleted=1;}
 need(resets==1&&lookups==1&&!loads);need(!std::memcmp(owner,expected,0x218));need(at<unsigned>(unit,0x3c)==0x73747576u);need((unsigned)std::ftell(file)==expectedPosition&&!std::feof(file)&&!std::ferror(file));need(*reinterpret_cast<uint64_t*>(0x14ecaf0)==104);
 cap->add(owner,0x218);n(at<unsigned>(unit,0x3c));n((unsigned)std::ftell(file));n(resets);n(lookups);n(loads);n(0x7152bf10u);n(errors);std::fclose(file);at<Wide>(owner,0x30).~Wide();
}
static void old(void* p,autotest::Capture& o){side(p,o,false);}static void fresh(void* p,autotest::Capture& o){side(p,o,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callCompleted&&tail[0]==0x7152bf10u&&!tail[1];}
}
TL_TEST(quest_persistence_load_bounded_framing){using namespace qrlb;autotest::Coverage cv("quest_persistence_load_bounded_framing",0xd17b20);for(unsigned kind=0;kind<2;++kind){autotest::Outcome a,b;autotest::runChild(old,&kind,a);autotest::runChild(fresh,&kind,b);bool ok=good(a)&&good(b);if(cv.observe(host,a,b))ok=false;if(!ok){host->log("    Quest bounded framing kind=%u status=%d/%d good=%u/%u completed=%u/%u issue=%u/%u\n",kind,a.childStatus,b.childStatus,good(a),good(b),a.capture.callCompleted,b.capture.callCompleted,a.capture.issue,b.capture.issue);cv.report(host);return 1;}}cv.report(host);return cv.completed!=2||cv.different||cv.missing;}
