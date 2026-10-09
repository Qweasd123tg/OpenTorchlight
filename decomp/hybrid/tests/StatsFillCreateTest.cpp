#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <CEGUIMemberFunctionSlot.h>
#include <OgreLogManager.h>
#include "StatsMenuFill.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldCreate,(CStatsMenuFill*),"_ZN14CStatsMenuFill11createMenusEv")
extern "C" void newCreate(CStatsMenuFill*) __asm__("_ZN14CStatsMenuFill11createMenusEv");
TL_FUNCTION(mouseUpHandler,"_ZN14CStatsMenuFill16handle_onMouseUpERKN5CEGUI9EventArgsE")
TL_FUNCTION(addHandler,"_ZN14CStatsMenuFill16handle_AddToStatERKN5CEGUI9EventArgsE")
TL_FUNCTION(removeHandler,"_ZN14CStatsMenuFill21handle_RemoveFromStatERKN5CEGUI9EventArgsE")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(uniqueFn,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(imagesetFn,"_ZNK5CEGUI15ImagesetManager11getImagesetERKNS_6StringE");
IMPORT(createFn,"_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(sizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(positionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(zFn,"_ZN5CEGUI6Window19setZOrderingEnabledEb");
IMPORT(imageFn,"_ZNK5CEGUI8Imageset8getImageERKNS_6StringE");
IMPORT(imageStringFn,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
IMPORT(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(tooltipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
IMPORT(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMPORT(fontFn,"_ZN5CEGUI6Window7setFontERKNS_6StringE");
IMPORT(multiFn,"_ZN5CEGUI6Window24setWantsMultiClickEventsEb");
IMPORT(logSingletonFn,"_ZN4Ogre10LogManager12getSingletonEv");
IMPORT(logFn,"_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
#undef IMPORT
namespace {
struct Case {unsigned missing,scale,existing,extra,growth,flags,labels,mutate;};
autotest::Capture* cap;const Case* input;CStatsMenuFill* menu;CGameUI* ui[2];CEGUI::Imageset* sets[2];CEGUI::Window* windows[128];unsigned long long windowMemory[128][(sizeof(CEGUI::Window)+7)/8];void* eventTable[4];unsigned windowCount,uniqueCount,scaleCount,connections,imageCount;unsigned refs[64];unsigned long long bound[64][4],imageMemory[100][32];CEGUI::Image* images[100];void* logManager;
void n(int x){cap->add(&x,sizeof(x));}void f(float x){cap->add(&x,sizeof(x));}
void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int id(const CEGUI::Window* p){for(unsigned i=0;i<windowCount;++i)if(p==windows[i])return i;return p?-2:-1;}
CEGUI::Window* window(){if(windowCount==128)_exit(40);CEGUI::Window* p=(CEGUI::Window*)windowMemory[windowCount];windows[windowCount++]=p;*(void***)(static_cast<CEGUI::EventSet*>(p))=eventTable;p->d_riseOnClick=input->flags;p->d_wantsMultiClicks=input->flags;p->d_mousePassThroughEnabled=input->flags;p->d_zOrderingEnabled=input->flags;return p;}
// Read only while the target is executing. Never dereference escaped stack
// userdata after return; retain alias identity separately in the final state.
void liveData(){char here;void* first=0;for(unsigned i=0;i<windowCount;++i)if(windows[i]->d_userData){void* p=windows[i]->d_userData;n(i);intptr_t distance=(intptr_t)p-(intptr_t)&here;bool stack=distance>-1024*1024&&distance<1024*1024;n(stack);if(stack)n(*(volatile unsigned*)p);if(!first)first=p;n(first==p);}n(-77);}
CEGUI::Imageset* getSet(const CEGUI::ImagesetManager*,const CEGUI::String& name){n(1);str(name);return name=="GuiLook"?sets[0]:input->missing?0:sets[1];}
std::string unique(const std::string& base){n(2);cap->addText(base);liveData();char suffix[24];std::sprintf(suffix,"%u",++uniqueCount);return base+suffix;}
CEGUI::Window* create(CEGUI::WindowManager*,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){n(3);str(type);str(name);str(prefix);return window();}
void add(CEGUI::Window* p,CEGUI::Window* q){n(4);n(id(p));n(id(q));q->d_parent=p;}
float scaled(CGameUI* p,float x){n(5);n(p==ui[0]?0:p==ui[1]?1:-1);f(x);++scaleCount;const float scales[]={0.0f,0.75f,1.0f,-1.0f,-0.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float result=x*scales[input->scale];if(input->mutate){result+=float(scaleCount)*0.03125f;menu->m_pGameUI=p==ui[0]?ui[1]:ui[0];}return result;}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(id(p));cap->add(&v,sizeof(v));}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(7);n(id(p));cap->add(&v,sizeof(v));}
void z(CEGUI::Window* p,bool b){n(8);n(id(p));n(b);p->d_zOrderingEnabled=b;}
const CEGUI::Image& getImage(const CEGUI::Imageset* p,const CEGUI::String& name){n(9);n(p==sets[0]?0:p==sets[1]?1:-1);str(name);if(imageCount==100)_exit(41);images[imageCount]=(CEGUI::Image*)imageMemory[imageCount];return *images[imageCount++];}
CEGUI::String imageString(const CEGUI::Image* p){n(10);unsigned i=0;for(;i<imageCount;++i)if(p==images[i])break;n(i);char s[32];std::sprintf(s,"image%u",i);return CEGUI::String(s);}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(11);n(id(static_cast<CEGUI::Window*>(p)));str(k);str(v);}
void front(CEGUI::Window* p){n(12);n(id(p));}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){n(13);n(id(p));str(s);}
void text(CEGUI::Window* p,const CEGUI::String& s){n(14);n(id(p));str(s);}
void font(CEGUI::Window* p,const CEGUI::String& s){n(15);n(id(p));str(s);}
void multi(CEGUI::Window* p,bool b){n(16);n(id(p));n(b);p->d_wantsMultiClicks=b;}
std::string convert(const std::wstring& s){n(17);cap->addText(s);return input->labels==2?"converted \xce\xa9":"converted label";}
Ogre::LogManager& logger(){n(18);return *(Ogre::LogManager*)logManager;}
void log(Ogre::LogManager* p,const std::string& s,Ogre::LogMessageLevel level,bool b){n(19);n(p==logManager);cap->addText(s);n(level);n(b);}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& name,CEGUI::Event::Subscriber subscriber){n(20);n(id(static_cast<CEGUI::Window*>(p)));str(name);CEGUI::MemberFunctionSlot<CStatsMenuFill>* slot=static_cast<CEGUI::MemberFunctionSlot<CStatsMenuFill>*>(subscriber.d_functor_impl);intptr_t words[2];typedef char check_member_pointer[sizeof(slot->d_function)==sizeof(words)?1:-1];std::memcpy(words,&slot->d_function,sizeof(words));
// Canonicalize only the corresponding recovered address; retain this-adjustment.
if(words[0]==reinterpret_cast<intptr_t>(mouseUpHandler_linked))words[0]=reinterpret_cast<intptr_t>(mouseUpHandler_original);
if(words[0]==reinterpret_cast<intptr_t>(addHandler_linked))words[0]=reinterpret_cast<intptr_t>(addHandler_original);
if(words[0]==reinterpret_cast<intptr_t>(removeHandler_linked))words[0]=reinterpret_cast<intptr_t>(removeHandler_original);
cap->add(words,sizeof(words));n(slot->d_object==menu);if(connections==64)_exit(42);unsigned active=0;for(unsigned i=0;i<connections;++i)active+=refs[i]-1;n(active);unsigned k=connections++;refs[k]=2;CEGUI::Event::Connection result;result.d_object=(CEGUI::BoundSlot*)bound[k];result.d_count=&refs[k];return result;}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;windowCount=uniqueCount=scaleCount=connections=imageCount=0;memset(windowMemory,0,sizeof(windowMemory));
 unsigned long long mm[64]={0},um[2][16]={0},setMemory[2][16]={0},manager[32]={0};menu=(CStatsMenuFill*)mm;ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];sets[0]=(CEGUI::Imageset*)setMemory[0];sets[1]=(CEGUI::Imageset*)setMemory[1];logManager=manager;
 eventTable[2]=(void*)&subscribe;CEGUI::Window* root=window();menu->m_pUnknown20=root;menu->m_pGameUI=ui[0];
 CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton=(CEGUI::ImagesetManager*)manager;CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=(CEGUI::WindowManager*)manager;
 TArrayList<CEGUI::Window*>* lists[]={&menu->m_AddButtons,&menu->m_RemoveButtons,&menu->m_Bars,&menu->m_AmountTexts,&menu->m_StatSlots,&menu->m_PercentTexts};
 const unsigned grows[]={1,4,10};for(int i=0;i<6;++i){new(lists[i])TArrayList<CEGUI::Window*>(grows[c.growth]);unsigned capacity=c.existing+c.extra;lists[i]->m_nCapacity=capacity;lists[i]->m_nCount=c.existing;lists[i]->m_pData=capacity?new CEGUI::Window*[capacity]:0;for(unsigned j=0;j<capacity;++j)lists[i]->m_pData[j]=j<c.existing?window():0;}
 for(int i=0;i<4;++i){menu->m_AddHeld[i]=c.flags;menu->m_RemoveHeld[i]=!c.flags;}
 std::wstring* labels=(std::wstring*)0x14d6c20;const wchar_t* names[]={L"MELEE",L"RANGED",L"MAGIC",L"DEFENSE"};for(int i=0;i<4;++i)new(&labels[i])std::wstring(c.labels==1?L"":c.labels==2?std::wstring(names[i])+L" \u03a9\u4e2d\u6587":std::wstring(names[i]));
 detour::Set d;TL_REDIRECT(d,scaledFn,&scaled);TL_REDIRECT(d,uniqueFn,&unique);TL_REDIRECT(d,convertFn,&convert);
#define R(N,F) d.redirect(N,N,&F)
 R(imagesetFn,getSet);R(createFn,create);R(addFn,add);R(sizeFn,size);R(positionFn,position);R(zFn,z);R(imageFn,getImage);R(imageStringFn,imageString);R(propertyFn,property);R(frontFn,front);R(tooltipFn,tooltip);R(textFn,text);R(fontFn,font);R(multiFn,multi);R(logSingletonFn,logger);R(logFn,log);
#undef R
 if(d.failed())_exit(43);
 if(ours)autotest::invoke(out,&newCreate,menu);else autotest::invoke(out,&oldCreate,menu);
 n(100);for(int i=0;i<6;++i){n(lists[i]->m_nCount);n(lists[i]->m_nCapacity);n(lists[i]->m_nGrowBy);for(unsigned j=0;j<lists[i]->m_nCount;++j)n(id(lists[i]->m_pData[j]));}
 n(id(menu->m_pExperienceText));for(int i=0;i<4;++i){n(menu->m_AddHeld[i]);n(menu->m_RemoveHeld[i]);}
 n(windowCount);void* alias=0;for(unsigned i=0;i<windowCount;++i){CEGUI::Window* p=windows[i];n(id(p->d_parent));n(p->d_riseOnClick);n(p->d_wantsMultiClicks);n(p->d_mousePassThroughEnabled);n(p->d_zOrderingEnabled);n(p->d_userData!=0);if(p->d_userData){if(!alias)alias=p->d_userData;n(p->d_userData==alias);}}
 n(connections);for(unsigned i=0;i<connections;++i)n(refs[i]);n(scaleCount);
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(stats_fill_create_differential){
 autotest::Coverage coverage("stats_fill_create_differential",(uint64_t)(uintptr_t)&oldCreate);unsigned total=0;
 const unsigned counts[]={0,1,4};
 for(unsigned missing=0;missing<2;++missing)for(unsigned scale=0;scale<8;++scale)for(unsigned count=0;count<3;++count)for(unsigned extra=0;extra<2;++extra)for(unsigned grow=0;grow<3;++grow)for(unsigned flags=0;flags<2;++flags)for(unsigned labels=0;labels<3;++labels)for(unsigned mutate=0;mutate<2;++mutate){
  if(missing&&(scale||count||extra||grow||labels||mutate))continue;
  Case c={missing,scale,counts[count],extra*3,grow,flags,labels,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
  bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&!memcmp(x.capture.data,y.capture.data,x.capture.length);
  if(!ok){coverage.report(host);size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    missing %u scale %u count %u extra %u grow %u flags %u labels %u mutate %u: status %d/%d bytes %lu/%lu first %lu\n",missing,scale,c.existing,c.extra,grow,flags,labels,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>40?first-40:0;i<first+60&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}
 }coverage.report(host);host->log("    stats fill create: %u cases\n",total);return 0;
}
