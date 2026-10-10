#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <CEGUIMemberFunctionSlot.h>
#include <OgreLogManager.h>
#include "SkillMenu.h"
#include "Skill.h"
#include "Character.h"
#include "GameUI.h"
#include "SkillManager.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldCreate,(CSkillMenu*),"_ZN10CSkillMenu12updateLayoutEv")
extern "C" void newCreate(CSkillMenu*) __asm__("_ZN10CSkillMenu12updateLayoutEv");
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
TL_FUNCTION(tabFn,"_ZN10CCharacter15getSkillTabNameEi")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateRefFn,"_ZN16CStringTranslate18getTranslateStringERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(translateWideFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(knownFn,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(iconFn,"_ZN6CSkill12getSkillIconEv")
TL_FUNCTION(inactiveFn,"_ZN6CSkill20getSkillIconInactiveEv")
TL_FUNCTION(requiredFn,"_ZN6CSkill29getSkillRequiredForInvestmentEv")
TL_FUNCTION(levelFn,"_ZN6CSkill29getLevelRequiredForInvestmentEv")
TL_FUNCTION(effectiveFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(dependencyFn,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(nameFn,"_ZN6CSkill14getDisplayNameEv")
TL_FUNCTION(spellFn,"_ZN10CCharacter13getKnownSpellEj")
TL_FUNCTION(valueFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(narrowFn,"_ZN7STRINGS21StringConvertToNarrowEPKw")
TL_FUNCTION(uiImageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(getUiFn,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(tipFn,"_ZN7CGameUI8queueTipE11EContextTip")
extern "C" char backFn[] __asm__("_ZN5CEGUI6Window10moveToBackEv");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char destroyFn[] __asm__("_ZN5CEGUI13WindowManager13destroyWindowEPNS_6WindowE");
extern "C" char clipFn[] __asm__("_ZN5CEGUI6Window18setClippedByParentEb");
TL_FUNCTION(callbackOverFn,"_ZN10CSkillMenu16handle_MouseOverERKN5CEGUI9EventArgsE")
TL_FUNCTION(callbackOutFn,"_ZN10CSkillMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
TL_FUNCTION(callbackSpendFn,"_ZN10CSkillMenu17handle_SpendSkillERKN5CEGUI9EventArgsE")
namespace {
struct Case {unsigned mode,scale,flags,mutate,existing;};
autotest::Capture* cap;const Case* input;CSkillMenu* menu;CGameUI* ui[2];CSkill* skill[8];CCharacter* owner;CSkillManager* manager;CStringTranslate* translator;
CEGUI::Imageset* set;CEGUI::Window* windows[128];unsigned long long windowMemory[128][(sizeof(CEGUI::Window)+7)/8];void* eventTable[4];unsigned windowCount,uniqueCount,scaleCount,connections,imageCount;unsigned refs[128];unsigned long long bound[128][4],imageMemory[128][32];CEGUI::Image* images[128];unsigned effectiveCalls[8];
std::wstring normal[8],inactive[8],required[8],display[8],translation;unsigned requirements[8];
template<class T> T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){cap->add(&x,sizeof(x));}void f(float x){cap->add(&x,sizeof(x));}
void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int id(const CEGUI::Window* p){for(unsigned i=0;i<windowCount;++i)if(p==windows[i])return i;return p?-2:-1;}
int sid(CSkill* p){for(int i=0;i<8;++i)if(p==skill[i])return i;return -1;}
CEGUI::Window* window(){if(windowCount==128)_exit(40);CEGUI::Window* p=(CEGUI::Window*)windowMemory[windowCount];windows[windowCount++]=p;*(void***)(static_cast<CEGUI::EventSet*>(p))=eventTable;p->d_riseOnClick=input->flags;p->d_wantsMultiClicks=input->flags;p->d_mousePassThroughEnabled=input->flags;p->d_zOrderingEnabled=input->flags;p->d_clippedByParent=input->flags;return p;}
std::string unique(const std::string& base){n(2);cap->addText(base);char suffix[24];std::sprintf(suffix,"%u",++uniqueCount);return base+suffix;}
CEGUI::Window* create(CEGUI::WindowManager*,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){n(3);str(type);str(name);str(prefix);return window();}
void add(CEGUI::Window* p,CEGUI::Window* q){n(4);n(id(p));n(id(q));q->d_parent=p;}
float scaled(CGameUI* p,float x){n(5);n(p==ui[0]?0:p==ui[1]?1:-1);f(x);++scaleCount;const float scales[]={0,1,.75f,-0.0f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-1.0f,-std::numeric_limits<float>::infinity()};float result=x*scales[input->scale];if(input->mutate){result+=float(scaleCount)*.03125f;menu->m_pGameUI=p==ui[0]?ui[1]:ui[0];}return result;}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(id(p));cap->add(&v,sizeof(v));}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(7);n(id(p));cap->add(&v,sizeof(v));}
void z(CEGUI::Window* p,bool b){n(8);n(id(p));n(b);p->d_zOrderingEnabled=b;}
const CEGUI::Image& getImage(const CEGUI::Imageset* p,const CEGUI::String& name){n(9);n(p==set);str(name);if(imageCount==128)_exit(41);images[imageCount]=(CEGUI::Image*)imageMemory[imageCount];return *images[imageCount++];}
CEGUI::String imageString(const CEGUI::Image* p){n(10);unsigned i=0;for(;i<imageCount;++i)if(p==images[i])break;n(i);char s[32];std::sprintf(s,"image%u",i);return CEGUI::String(s);}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(11);n(id(static_cast<CEGUI::Window*>(p)));str(k);str(v);}
void front(CEGUI::Window* p){n(12);n(id(p));}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){n(13);n(id(p));str(s);}
void text(CEGUI::Window* p,const CEGUI::String& s){n(14);n(id(p));str(s);}
void multi(CEGUI::Window* p,bool b){n(16);n(id(p));n(b);p->d_wantsMultiClicks=b;}
std::string convert(const std::wstring& s){n(17);cap->addText(s);return input->mode==15?"converted \xce\xa9":"converted label";}
// Only translate known original/replacement callback identities; retain this-adjustment.
void captureCallback(const CEGUI::MemberFunctionSlot<CSkillMenu>* slot){
 intptr_t words[2];typedef char check_member_pointer[sizeof(slot->d_function)==sizeof(words)?1:-1];
 std::memcpy(words,&slot->d_function,sizeof(words));
 char* pairs[][2]={{callbackOverFn_original,callbackOverFn_linked},{callbackOutFn_original,callbackOutFn_linked},{callbackSpendFn_original,callbackSpendFn_linked}};
 for(unsigned i=0;i<3;++i)if(words[0]==(intptr_t)pairs[i][0]||words[0]==(intptr_t)pairs[i][1]){words[0]=(intptr_t)pairs[i][0];break;}
 cap->add(words,sizeof(words));
}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& name,CEGUI::Event::Subscriber subscriber){n(20);n(id(static_cast<CEGUI::Window*>(p)));str(name);CEGUI::MemberFunctionSlot<CSkillMenu>* slot=static_cast<CEGUI::MemberFunctionSlot<CSkillMenu>*>(subscriber.d_functor_impl);captureCallback(slot);n(slot->d_object==menu);if(connections==128)_exit(42);unsigned active=0;for(unsigned i=0;i<connections;++i)active+=refs[i]-1;n(active);unsigned k=connections++;refs[k]=2;CEGUI::Event::Connection result;result.d_object=(CEGUI::BoundSlot*)bound[k];result.d_count=&refs[k];return result;}
void back(CEGUI::Window* p){n(21);n(id(p));}
void remove(CEGUI::Window* p,CEGUI::Window* q){n(22);n(id(p));n(id(q));q->d_parent=0;}
void destroy(CEGUI::WindowManager*,CEGUI::Window* p){n(23);n(id(p));}
void clip(CEGUI::Window* p,bool b){n(24);n(id(p));n(b);p->d_clippedByParent=b;}
std::wstring tab(CCharacter* p,int i){n(25);n(p==owner);n(i);return i==1?L"FIRST":i==2?L"SECOND":L"THIRD";}
CStringTranslate* translateSingleton(){n(26);return translator;}
const std::wstring& translateRef(CStringTranslate* p,const std::wstring& s){n(27);n(p==translator);cap->addText(s);translation=s+L" translated";return translation;}
std::wstring translateWide(CStringTranslate* p,const wchar_t* s){n(28);n(p==translator);cap->addText(std::wstring(s));return input->mode==15?L"":L"Buy";}
int known(CSkillManager* p,ESKILL_ACTIVATION_TYPE t){n(29);n(p==manager);n(t);return input->mode<3?0:(input->mode==14||input->mode==27||input->mode==29)?4:1;}
const std::wstring& icon(CSkill* p){n(30);int i=sid(p);n(i);if(i<0)_exit(50);return normal[i];}
const std::wstring& inactiveIcon(CSkill* p){n(31);int i=sid(p);n(i);return inactive[i];}
const std::wstring& prerequisite(CSkill* p){n(32);int i=sid(p);n(i);return required[i];}
unsigned level(CSkill* p){n(33);int i=sid(p);n(i);return requirements[i];}
void effective(CSkill* p){n(34);int i=sid(p);n(i);++effectiveCalls[i];if(input->mode==13)at<unsigned>(p,0xe0)=effectiveCalls[i];}
CSkill* dependency(CSkillManager* p,const std::wstring& s){n(35);n(p==manager);cap->addText(s);return input->mode==9?0:skill[7];}
const std::wstring& name(CSkill* p){n(36);int i=sid(p);n(i);return display[i];}
CSkill* spell(CCharacter* p,unsigned i){n(37);n(p==owner);n(i);return input->mode>=12?(i==1?0:skill[4+i]):0;}
std::string value(int x){n(38);n(x);char b[32];std::sprintf(b,"%d",x);return b;}
std::string narrow(const wchar_t* s){n(39);cap->addText(std::wstring(s));return "narrow icon";}
const CEGUI::Image* uiImage(CGameUI* p,const unsigned char* name){n(40);n(p==ui[0]?0:p==ui[1]?1:-1);cap->addText(std::string((const char*)name));images[imageCount]=(CEGUI::Image*)imageMemory[imageCount];return images[imageCount++];}
CGameUI* getUi(CResourceManager* p){n(41);n(p==menu->m_pResourceManager);return ui[0];}
void tip(CGameUI* p,EContextTip t){n(42);n(p==ui[0]);n(t);}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;windowCount=uniqueCount=scaleCount=connections=imageCount=0;memset(windowMemory,0,sizeof(windowMemory));memset(effectiveCalls,0,sizeof(effectiveCalls));
 unsigned long long mm[256]={0},um[2][16]={0},setMemory[16]={0},wm[32]={0},om[384]={0},sm[8][64]={0},mgr[32]={0},tm[16]={0};
 menu=(CSkillMenu*)mm;owner=(CCharacter*)om;manager=(CSkillManager*)mgr;translator=(CStringTranslate*)tm;ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];set=(CEGUI::Imageset*)setMemory;
 eventTable[2]=(void*)&subscribe;menu->m_pBackground=window();for(int i=0;i<4;++i)menu->m_Panes[i]=window();for(int i=0;i<3;++i)menu->m_TabLabels[i]=window();menu->m_pOwner=c.mode?owner:0;menu->m_pGameUI=ui[0];menu->m_pImages=set;menu->m_pResourceManager=(CResourceManager*)wm;menu->m_bOpenPartial=c.flags;menu->m_iPane=c.mode==14?2:0;
 CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=(CEGUI::WindowManager*)wm;
 new(&menu->m_Children)TArrayList<CEGUI::Window*>(c.flags?1:10);for(unsigned i=0;i<c.existing;++i){CEGUI::Window* q=window();q->d_parent=i%2?0:menu->m_pBackground;menu->m_Children.add(q);}
 for(int i=0;i<100;++i){menu->m_SkillGuids[i]=-100-i;menu->m_SpellGuids[i]=-200-i;}
 for(int i=0;i<8;++i){skill[i]=(CSkill*)sm[i];normal[i]=L"Icon";inactive[i]=L"Inactive";required[i]=L"";display[i]=L"Skill";requirements[i]=10;at<int>(skill[i],0x60)=i%2?4:0;at<unsigned>(skill[i],0xa8)=5;at<unsigned>(skill[i],0xdc)=1;at<unsigned>(skill[i],0xe0)=c.mode==5?2:0;at<int>(skill[i],0x10c)=i;at<int>(skill[i],0x110)=c.flags?-1:i;at<int>(skill[i],0x114)=menu->m_iPane;at<long long>(skill[i],0x150)=1000+i;at<unsigned>(skill[i],0x158)=0;}
 if(c.mode==16){at<unsigned>(skill[0],0xe0)=5;at<unsigned>(skill[0],0x158)=5;}
 if(c.mode==17)at<unsigned>(skill[0],0xe0)=0xffffffffU;
 if(c.mode==18){at<unsigned>(skill[0],0xe0)=2;at<unsigned>(skill[0],0x158)=2;}
 if(c.mode==19)at<unsigned>(skill[0],0xa8)=0;
 if(c.mode==23)at<int>(skill[0],0x114)=1;
 if(c.mode==24){at<int>(skill[0],0x10c)=-2;at<int>(skill[0],0x110)=-3;}
 if(c.mode==25)requirements[0]=0xffffffffU;
 if(c.mode==26)requirements[0]=0;
 if(c.mode==28)for(int i=4;i<8;++i)normal[i]=L"";
 if(c.mode==29){at<long long>(owner,0x950+0*8)=1000;}
 if(c.mode==30){required[0]=L"dependency";at<unsigned>(skill[7],0xdc)=0xffffffffU;}
 if(c.mode==31){normal[0]=std::wstring(80,L'x');display[0]=std::wstring(80,L'Y');}
 at<unsigned>(owner,0x100)=c.mode==25?0xffffffffU:c.mode==6?1:20;at<CSkillManager*>(owner,0x1c8)=(c.mode==1||c.mode==20)?0:manager;at<int>(owner,0x460)=c.mode==10?0:3;
 for(int i=0;i<24;++i)at<long long>(owner,0x950+i*8)=-1;
 if(c.mode==29){at<long long>(owner,0x950)=1000;at<long long>(owner,0x9b0+11*8)=1000;}
 if(c.mode==11)at<long long>(owner,0x9b0+11*8)=1000;
 if(c.mode==14){at<long long>(owner,0x950)=1000;at<long long>(owner,0x9b0+3*8)=1002;normal[1]=L"";at<int>(skill[3],0x114)=0;}
 if(c.mode==3)normal[0]=L"";
 if(c.mode==4)at<int>(skill[0],0x10c)=-1;
 if(c.mode==7||c.mode==8||c.mode==9){required[0]=L"dependency";at<unsigned>(skill[7],0xdc)=c.mode==8?1:0;}
 if(c.mode==15){normal[0]=L"\u03a9\u4e2d";display[0]=L"Skill \u03a9";at<unsigned>(skill[0],0xa8)=0;at<unsigned>(skill[0],0x158)=0;}
 TArrayList<CSkill*>* list=(TArrayList<CSkill*>*)((char*)manager+0x60);new(list)TArrayList<CSkill*>(4);for(int i=0;i<4;++i)list->add(skill[i]);
 if(c.mode==27)list->m_nCapacity=1;
 new((void*)0x14d1848)std::wstring(c.mode==22?L"sentinel":L"");new((void*)0x14d2f58)std::wstring(c.mode==21?L"cached purchase":L"");at<unsigned char>((void*)0x14d2f50,0)=c.mode==21?1:0;
 detour::Set d;TL_REDIRECT(d,scaledFn,&scaled);TL_REDIRECT(d,uniqueFn,&unique);TL_REDIRECT(d,convertFn,&convert);
 TL_REDIRECT(d,tabFn,&tab);TL_REDIRECT(d,translateSingletonFn,&translateSingleton);TL_REDIRECT(d,translateRefFn,&translateRef);TL_REDIRECT(d,translateWideFn,&translateWide);TL_REDIRECT(d,knownFn,&known);TL_REDIRECT(d,iconFn,&icon);TL_REDIRECT(d,inactiveFn,&inactiveIcon);TL_REDIRECT(d,requiredFn,&prerequisite);TL_REDIRECT(d,levelFn,&level);TL_REDIRECT(d,effectiveFn,&effective);TL_REDIRECT(d,dependencyFn,&dependency);TL_REDIRECT(d,nameFn,&name);TL_REDIRECT(d,spellFn,&spell);TL_REDIRECT(d,valueFn,&value);TL_REDIRECT(d,narrowFn,&narrow);TL_REDIRECT(d,uiImageFn,&uiImage);TL_REDIRECT(d,getUiFn,&getUi);TL_REDIRECT(d,tipFn,&tip);
#define R(N,F) d.redirect(N,N,&F)
 R(createFn,create);R(addFn,add);R(sizeFn,size);R(positionFn,position);R(zFn,z);R(imageFn,getImage);R(imageStringFn,imageString);R(propertyFn,property);R(frontFn,front);R(tooltipFn,tooltip);R(textFn,text);R(multiFn,multi);R(backFn,back);R(removeFn,remove);R(destroyFn,destroy);R(clipFn,clip);
#undef R
 if(d.failed())_exit(43);
 if(ours)autotest::invoke(out,&newCreate,menu);else autotest::invoke(out,&oldCreate,menu);
 n(100);n(menu->m_Children.m_nCount);n(menu->m_Children.m_nCapacity);n(menu->m_Children.m_nGrowBy);for(unsigned j=0;j<menu->m_Children.size();++j)n(id(menu->m_Children[j]));
 cap->add(menu->m_SkillGuids,sizeof(menu->m_SkillGuids));cap->add(menu->m_SpellGuids,sizeof(menu->m_SpellGuids));
 n(windowCount);for(unsigned i=0;i<windowCount;++i){CEGUI::Window* p=windows[i];n(id(p->d_parent));n(p->d_riseOnClick);n(p->d_wantsMultiClicks);n(p->d_mousePassThroughEnabled);n(p->d_zOrderingEnabled);n(p->d_clippedByParent);n(p->d_userData?(intptr_t)p->d_userData-(intptr_t)menu:-1);}
 n(connections);for(unsigned i=0;i<connections;++i)n(refs[i]);n(scaleCount);cap->add(effectiveCalls,sizeof(effectiveCalls));cap->addText(*(std::wstring*)0x14d2f58);
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(skill_layout_differential){
 autotest::Coverage coverage("skill_layout_differential",(uint64_t)(uintptr_t)&oldCreate);unsigned total=0;
 for(unsigned mode=0;mode<32;++mode)for(unsigned scale=0;scale<8;++scale)for(unsigned flags=0;flags<2;++flags)for(unsigned mutate=0;mutate<2;++mutate)for(unsigned existing=0;existing<2;++existing){
 Case c={mode,scale,flags,mutate,existing*2};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&!memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(!ok){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    mode %u scale %u flags %u mutate %u existing %u: status %d/%d bytes %lu/%lu first %lu\n",mode,scale,flags,mutate,c.existing,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>40?first-40:0;i<first+80&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}coverage.report(host);return 1;}
 }coverage.report(host);host->log("    skill layout: %u cases\n",total);return 0;
}
