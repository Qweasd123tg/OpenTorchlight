#include <string>
#include <vector>
#include <deque>
#include <cstring>
#include <limits>
#define private public
#include "Graph.h"
#include "Inventory.h"
#include "EquipmentRef.h"
#undef private
#include "UtilitiesMath.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(int,oldGetBool,(const std::wstring&),"_ZN7STRINGS7GetBoolERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(long long,oldGetInt64,(const std::wstring&),"_ZN7STRINGS8GetInt64ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(std::wstring,oldClean,(const std::wstring&),"_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(std::wstring,oldAppData,(),"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_ORIGINAL(void,oldGraphClear,(CGraph*,unsigned),"_ZN6CGraph5clearEj")
TL_ORIGINAL(void,oldWorld,(Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Matrix4&),"_ZN4MATH12worldToLocalERN4Ogre7Vector3ERKS1_RKNS0_7Matrix4E")
TL_ORIGINAL(int,oldPaneSize,(CInventory*,EINVENTORY_PANES),"_ZN10CInventory11getPaneSizeE16EINVENTORY_PANES")
TL_ORIGINAL(void,oldPush,(std::deque<std::string>*,const std::string&),"_ZNSt5dequeISsSaISsEE16_M_push_back_auxERKSs")
extern "C" int newGetBool(const std::wstring&) __asm__("_ZN7STRINGS7GetBoolERKSbIwSt11char_traitsIwESaIwEE");
extern "C" long long newGetInt64(const std::wstring&) __asm__("_ZN7STRINGS8GetInt64ERKSbIwSt11char_traitsIwESaIwEE");
extern "C" std::wstring newClean(const std::wstring&) __asm__("_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE");
extern "C" std::wstring newAppData() __asm__("_ZN10FILESYSTEM14GetAppDataPathEv");
extern "C" void newGraphClear(CGraph*,unsigned) __asm__("_ZN6CGraph5clearEj");
extern "C" void newWorld(Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Matrix4&) __asm__("_ZN4MATH12worldToLocalERN4Ogre7Vector3ERKS1_RKNS0_7Matrix4E");
extern "C" int newPaneSize(CInventory*,EINVENTORY_PANES) __asm__("_ZN10CInventory11getPaneSizeE16EINVENTORY_PANES");
extern "C" void newPush(std::deque<std::string>*,const std::string&) __asm__("_ZNSt5dequeISsSaISsEE16_M_push_back_auxERKSs");
TL_FUNCTION(homeFn,"_ZN10LinuxUtils10GetHomeDirEv")
TL_FUNCTION(curveClearFn,"_ZN16ParticleUniverse22DynamicAttributeCurved22removeAllControlPointsEv")
TL_FUNCTION(paneFn,"_ZN10CInventory12getPaneIndexE16EINVENTORY_PANES")
namespace {
struct Case{unsigned mode,seed;};unsigned seed;autotest::Capture* capture;void* objects[5];
void n(unsigned v){capture->add(&v,4);}std::wstring home(){n(10);const wchar_t* homes[]={L"",L"/home/user/",L"/tmp",L"/\x416/",L"a\\b/"};std::wstring value=homes[seed%5];if(seed/5==1)value+=std::wstring(1024,L'x');if(seed/5==2)value.append(L"a\0b",3);if(seed/5==3)value+=L"../dir//";if(seed/5==4)value+=L"\x4e2d\x6587/";return value;}
void curveClear(ParticleUniverse::DynamicAttributeCurved* p){n(20);for(unsigned i=0;i<5;++i)if(p==objects[i]){n(i);return;}_exit(61);}
unsigned paneIndex(CInventory*,EINVENTORY_PANES pane){n(unsigned(pane));return seed%4;}
std::wstring text(unsigned i){const wchar_t* values[]={L"",L"false",L"False",L"0",L"true",L"TRUE",L"1",L"f",L"F",L"\x416",L"/a//b\\c/",L"\\\\x///y",L"relative",L"//",L"/",L"\\"};if(i<16)return values[i];if(i<32)return std::wstring(L"a\0b\\//",7);return std::wstring(i,L'\\')+L"/x//y";}
void side(void* data,autotest::Capture& out,bool ours){Case c=*(Case*)data;seed=c.seed;capture=&out;std::wstring v=text(seed%48),shared=v;
 if(c.mode==0){typedef int(*Fn)(const std::wstring&);autotest::invoke<Fn,const std::wstring&>(out,ours?&newGetBool:&oldGetBool,v);}
 if(c.mode==1){const wchar_t* nums[]={L"0",L"1",L"-1",L"9223372036854775807",L"-9223372036854775808",L"  +123tail",L"123.5",L"000024",L"-00009",L"\t42\n"};v=std::wstring(seed/10,L' ')+nums[seed%10];typedef long long(*Fn)(const std::wstring&);autotest::invoke<Fn,const std::wstring&>(out,ours?&newGetInt64:&oldGetInt64,v);}
 if(c.mode==2){typedef std::wstring(*Fn)(const std::wstring&);autotest::invoke<Fn,const std::wstring&>(out,ours?&newClean:&oldClean,v);}
 if(c.mode==3){detour::Set d;TL_REDIRECT(d,homeFn,&home);if(d.failed())_exit(60);autotest::invoke(out,ours?&newAppData:&oldAppData);}
 if(c.mode==4){unsigned long long memory[(sizeof(CGraph)+7)/8],storage[5][8];std::memset(memory,0xa5,sizeof(memory));CGraph* g=(CGraph*)memory;ParticleUniverse::DynamicAttributeCurved* refs[5];for(unsigned i=0;i<5;++i){objects[i]=storage[i];refs[i]=(seed/180)&(1u<<i)?NULL:(ParticleUniverse::DynamicAttributeCurved*)objects[i];}g->m_Lines.m_pData=refs;g->m_Lines.m_nCount=3;g->m_Lines.m_nCapacity=(seed/6)%5;g->m_iLineCount=(seed/30)%6;detour::Set d;TL_REDIRECT(d,curveClearFn,&curveClear);if(d.failed())_exit(60);autotest::invoke(out,ours?&newGraphClear:&oldGraphClear,g,seed%6);out.add(memory,sizeof(memory));out.add(refs,sizeof(refs));}
 if(c.mode==5){const float f[]={0.f,-0.f,1.f,-1.f,0.25f,10000.f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};Ogre::Vector3 p(f[seed%8],f[(seed/8)%8],f[(seed/64)%8]),r(-33.f,19.f,123.f);Ogre::Matrix4 m;for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col)m[row][col]=f[(row*3+col+seed/7)%6];Ogre::Vector3& target=seed&1?p:r;typedef void(*Fn)(Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Matrix4&);autotest::invoke<Fn,Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Matrix4&>(out,ours?&newWorld:&oldWorld,target,p,m);out.add(&p,sizeof(p));out.add(&r,sizeof(r));out.add(&m,sizeof(m));}
 if(c.mode==6){unsigned long long memory[(sizeof(CInventory)+7)/8];std::memset(memory,0xa5,sizeof(memory));CInventory* inv=(CInventory*)memory;new(&inv->m_paneStarts)std::vector<unsigned>();for(unsigned i=0;i<4;++i)inv->m_paneStarts.push_back(i*10+seed/4);inv->m_iUnknown28=seed%3?40:-1;detour::Set d;TL_REDIRECT(d,paneFn,&paneIndex);if(d.failed())_exit(60);autotest::invoke(out,ours?&newPaneSize:&oldPaneSize,inv,static_cast<EINVENTORY_PANES>(seed%4));out.add(memory,sizeof(memory));inv->m_paneStarts.~vector();}
 if(c.mode==7){std::deque<std::string> q;for(unsigned i=0;i<63+(seed%5)*64;++i)q.push_back(std::string(i%7,'a'+i%20));std::string value=seed%2?std::string(900,'z'):std::string("a\0b",3);if(seed%3==0)value=q.front();typedef void(*Fn)(std::deque<std::string>*,const std::string&);autotest::invoke<Fn,std::deque<std::string>*,const std::string&>(out,ours?&newPush:&oldPush,&q,value);n(q.size());for(unsigned i=0;i<q.size();++i)out.addText(q[i]);out.addText(value);}
 out.addText(v);out.addText(shared);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host* host,unsigned mode){void* addresses[]={(void*)&oldGetBool,(void*)&oldGetInt64,(void*)&oldClean,(void*)&oldAppData,(void*)&oldGraphClear,(void*)&oldWorld,(void*)&oldPaneSize,(void*)&oldPush};const char* names[]={"pass10_legacy_getbool","pass10_legacy_int64","pass10_legacy_cleanpath","pass10_legacy_appdata","pass10_existing_graph_clear","pass10_existing_worldlocal","pass10_legacy_panesize","pass10_legacy_dequepush"};unsigned counts[]={48,50,48,25,180*8,512,32,30};autotest::Coverage cv(names[mode],(uint64_t)(uintptr_t)addresses[mode]);for(unsigned i=0;i<counts[mode];++i){Case c={mode,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus){host->log("    utility %u case %u exits %d/%d\n",mode,i,x.childStatus,y.childStatus);cv.report(host);return 1;}}cv.report(host);return 0;}
}
TL_TEST(pass10_legacy_getbool){return run(host,0);}TL_TEST(pass10_legacy_int64){return run(host,1);}TL_TEST(pass10_legacy_cleanpath){return run(host,2);}TL_TEST(pass10_legacy_appdata){return run(host,3);}TL_TEST(pass10_existing_graph_clear){return run(host,4);}TL_TEST(pass10_existing_worldlocal){return run(host,5);}TL_TEST(pass10_legacy_panesize){return run(host,6);}TL_TEST(pass10_legacy_dequepush){return run(host,7);}
