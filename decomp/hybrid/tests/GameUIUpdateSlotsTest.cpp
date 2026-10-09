#include <string>
#include <cstring>
#include <cstdio>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreUTFString.h>
#include "GameUISlotsState.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalSlots,(CGameUI*),"_ZN7CGameUI11updateSlotsEv")
extern "C" void candidateSlots(CGameUI*) __asm__("_ZN7CGameUI11updateSlotsEv");
TL_FUNCTION(slotsDependency00,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(slotsDependency01,"_ZN6CSkill12getSkillIconEv")
TL_FUNCTION(slotsDependency02,"_ZN7STRINGS21StringConvertToNarrowEPKw")
TL_FUNCTION(slotsDependency03,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(slotsDependency04,"_ZN13CSkillManager19getSkillCoolingTimeEP6CSkill")
TL_FUNCTION(slotsDependency05,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(slotsDependency06,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(slotsDependency07,"_ZN16CResourceManager17getUnitDataByGuidEx")
TL_FUNCTION(slotsDependency08,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(slotsDependency09,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(slotsDependency10,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(slotsDependency11,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(slotsDependency12,"_ZN10CInventory23getEquipmentCountOfGuidEx")
TL_FUNCTION(slotsDependency13,"_ZN7STRINGS17GetValueAsWStringEj")
TL_FUNCTION(slotsDependency14,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(slotsDependency15,"_ZN16CStringTranslate18getTranslateStringEPKw")
extern "C" char slotsDependency16[] __asm__("_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
extern "C" char slotsDependency17[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char slotsDependency18[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char slotsDependency19[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char slotsDependency20[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char slotsDependency21[] __asm__("_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
extern "C" char slotsDependency22[] __asm__("_ZN5CEGUI6Window5setIDEj");
namespace slots_fixture {
using namespace gameui_slots_detail;
struct Case { unsigned scenario, variant; };
static unsigned long long memory[100][1024];
static CEGUI::Window* windows[48];
static CEGUI::Image* images[4];
static CEGUI::UVector2 positions[48],sizes[48];
static CEGUI::String imageValues[48],tintValues[48],tooltipValues[48];
static std::wstring iconNames[16],itemIcon;
static UIState* ui;
static CGameUI* game;
static ActorState* player;
static autotest::Capture* cap;
static Case current;
static unsigned frame,scaleCalls,masterCalls,lookupCalls,propertyCalls;
template<class T>T* object(unsigned i){return reinterpret_cast<T*>(memory[i]);}
template<class T>T& field(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void n(int x){cap->add(&x,4);}
static void f(float x){cap->add(&x,4);}
static void guid(long long x){cap->add(&x,8);}
static void ptr(const void* p){
 if(!p){n(-1);return;}
 uintptr_t a=reinterpret_cast<uintptr_t>(p),lo=reinterpret_cast<uintptr_t>(memory),hi=lo+sizeof(memory);
 if(a<lo||a>=hi){cap->issue=autotest::Capture::UnsupportedPointer;n(-2);return;}
 n((a-lo)/sizeof(memory[0]));n((a-lo)%sizeof(memory[0]));
}
static void str(const CEGUI::String& value){n(value.length());for(size_t i=0;i<value.length();++i)n(value[i]);}
static int wid(const void* p){for(int i=0;i<48;++i)if(p==windows[i])return i;_exit(61);}
static int sid(CSkill* p){for(int i=0;i<16;++i)if(p==object<CSkill>(80+i))return i;_exit(62);}
static CSkill* findSkill(CSkillManager* p,long long value){n(1);ptr(p);guid(value);++lookupCalls;if(current.scenario==30)ui->player=object<CCharacter>(lookupCalls%2?79:1);return value>=100&&value<116?object<CSkill>(80+value-100):NULL;}
static const std::wstring& skillIcon(CSkill* p){n(2);int i=sid(p);n(i);return iconNames[i];}
static std::string narrow(const wchar_t* x){n(3);std::wstring t(x);cap->addText(t);return std::string(t.begin(),t.end());}
static const CEGUI::Image* imageLookup(CGameUI* p,const unsigned char* x){n(4);ptr(p);cap->addText(std::string(reinterpret_cast<const char*>(x)));if(current.scenario==21&&std::strcmp(reinterpret_cast<const char*>(x),"item_icon")==0)return NULL;return images[std::strlen(reinterpret_cast<const char*>(x))%4];}
static float cooling(CSkillManager* p,CSkill* skill){n(5);ptr(p);int i=sid(skill);n(i);const float values[]={0,0.01f,1.0f,1.01f,-0.1f,-1.2f,99.75f,3.25f};if(current.scenario==11||current.scenario==33)return std::numeric_limits<float>::quiet_NaN();if(current.scenario==34)return current.variant&1?std::numeric_limits<float>::infinity():-std::numeric_limits<float>::infinity();return values[(i+current.variant+frame)%8];}
static std::wstring signedValue(int v){n(6);n(v);char text[32];std::sprintf(text,"%d",v);return std::wstring(text,text+std::strlen(text));}
static std::string convert(const std::wstring& value){n(7);cap->addText(value);return Ogre::UTFString(value).asUTF8();}
static CDataGroup* unitData(CResourceManager* p,long long value){n(8);ptr(p);guid(value);if(current.scenario==36)ui->resources=ui->resources==object<CResourceManager>(4)?object<CResourceManager>(99):object<CResourceManager>(4);if(current.scenario==19||current.scenario==20)return NULL;return object<CDataGroup>(7);}
static const std::wstring& dataValue(CDataGroup* p,const std::wstring& key,const std::wstring& fallback){n(9);ptr(p);cap->addText(key);cap->addText(fallback);return itemIcon;}
static CMasterResourceManager* master(){n(10);++masterCalls;if(current.scenario==25)KSETTINGS_YRATIO+=1;return object<CMasterResourceManager>(5);}
static float ratio(CDynamicPropertyFile* p,unsigned key){n(11);ptr(p);n(key);return (current.variant&1)?1.5f:0.75f;}
static float scaled(CGameUI* p,float v){n(12);ptr(p);f(v);++scaleCalls;if(current.scenario==26)ui->slotWidth+=0.25f;return v*((current.variant&2)?1.25f:0.5f);}
static int itemCount(CInventory* p,long long value){n(13);ptr(p);guid(value);if(current.scenario==17)return 0;if(current.scenario==27)return -1;return static_cast<int>((value+current.variant+frame)%7);}
static std::wstring unsignedValue(unsigned v){n(14);n(v);char text[32];std::sprintf(text,"%u",v);return std::wstring(text,text+std::strlen(text));}
static CStringTranslate* translator(){n(15);return object<CStringTranslate>(8);}
static std::wstring translate(CStringTranslate* p,const wchar_t* value){n(16);ptr(p);cap->addText(std::wstring(value));return current.variant&4?L"Назначить Ω":L"Assign";}
static CEGUI::String imageString(const CEGUI::Image* p){n(17);int i=-1;for(int j=0;j<4;++j)if(p==images[j])i=j;n(i);char text[32];std::sprintf(text,"image_%d",i);return CEGUI::String(text);}
static void property(CEGUI::PropertySet* p,const CEGUI::String& key,const CEGUI::String& value){int i=wid(static_cast<CEGUI::Window*>(p));n(18);n(i);str(key);str(value);++propertyCalls;if(current.scenario==31){ui->rightCooldown=windows[36+propertyCalls%2];ui->leftIcon=windows[38+propertyCalls%2];}if(key=="Image")imageValues[i]=value;else if(key=="ImageColours")tintValues[i]=value;else _exit(63);}
static void setText(CEGUI::Window* p,const CEGUI::String& value){int i=wid(p);n(19);n(i);str(value);p->d_text=value;}
static void setSize(CEGUI::Window* p,const CEGUI::UVector2& v){int i=wid(p);n(20);n(i);cap->add(&v,sizeof(v));sizes[i]=v;}
static void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){int i=wid(p);n(21);n(i);cap->add(&v,sizeof(v));positions[i]=v;}
static void setTooltip(CEGUI::Window* p,const CEGUI::String& value){int i=wid(p);n(22);n(i);str(value);tooltipValues[i]=value;}
static void setID(CEGUI::Window* p,unsigned value){int i=wid(p);n(23);n(i);n(value);p->d_ID=value;}
static void setup(const Case& c,autotest::Capture& out){
 current=c;cap=&out;frame=scaleCalls=masterCalls=lookupCalls=propertyCalls=0;std::memset(memory,0,sizeof(memory));
 new(reinterpret_cast<void*>(0x14b7d08))std::wstring();
 *reinterpret_cast<unsigned char*>(0x14b9c18)=0;
 game=object<CGameUI>(0);ui=&state(game);ui->player=object<CCharacter>(1);player=&actor(ui->player);player->skills=object<CSkillManager>(2);player->inventory=object<CInventory>(3);ui->resources=object<CResourceManager>(4);object<CMasterResourceManager>(5)->m_pSettings=object<CSettings>(6);KSETTINGS_YRATIO=19;
 for(int i=0;i<48;++i){windows[i]=object<CEGUI::Window>(9+i);new(&windows[i]->d_text)CEGUI::String(c.variant&1?"old":"");windows[i]->d_ID=99;windows[i]->d_userData=&ui->emptyGuid;positions[i]=CEGUI::UVector2(CEGUI::UDim(.2f,3),CEGUI::UDim(.4f,5));sizes[i]=CEGUI::UVector2(CEGUI::UDim(.3f,70),CEGUI::UDim(.6f,80));imageValues[i]="old-image";tintValues[i]="old-tint";tooltipValues[i]="old-tip";}
 for(int i=0;i<4;++i){images[i]=object<CEGUI::Image>(75+i);field<float>(images[i],0x20)=31.5f+i*13;field<float>(images[i],0x24)=19.25f+i*7;}
 for(int i=0;i<16;++i)iconNames[i]=((c.scenario==6||c.scenario==15)&&(i%2==0))?L"":L"skill_icon";
 itemIcon=L"item_icon";ui->slotWidth=48.25f+c.variant;ui->slotHeight=61.5f+c.variant;ui->emptyGuid=-1;
 ui->leftIcon=windows[0];ui->leftCooldown=windows[1];ui->rightIcon=windows[2];ui->rightCooldown=windows[3];ui->attackIcon=windows[4];ui->attackCooldown=windows[5];
 long long* caches[]={&ui->leftGuid,&ui->rightGuid,&ui->attackGuid};
 for(int i=0;i<3;++i){player->primarySkills[i]=(c.scenario==3||c.scenario==5)?-1:100+i;*caches[i]=(c.scenario==7||c.scenario==28)?player->primarySkills[i]:-99;ui->primaryUserGuids[i]=-88;}
 for(int i=0;i<10;++i){ui->buttons[i]=windows[6+i];ui->icons[i]=windows[16+i];ui->labels[i]=windows[26+i];ui->icons[i]->d_parent=ui->buttons[i];player->hotkeySkills[i]=-1;player->hotkeyItems[i]=-1;ui->skillGuids[i]=-1;ui->itemGuids[i]=-1;ui->counts[i]=-99;
  if(c.scenario>=12&&c.scenario<=15){player->hotkeySkills[i]=100+i;ui->skillGuids[i]=c.scenario==13?100+i:-1;ui->counts[i]=c.scenario==14?static_cast<int>(ceilf(float((i+c.variant)%8))):-99;}
  if(c.scenario>=15&&c.scenario<=21){player->hotkeyItems[i]=200+i;ui->itemGuids[i]=(c.scenario==18||c.scenario==20)?200+i:-1;}
  if(c.scenario==22){ui->itemGuids[i]=i&1?200+i:-1;ui->skillGuids[i]=i&1?-1:100+i;}
  if(c.scenario>=24){player->hotkeySkills[i]=i%3==0?100+i:-1;player->hotkeyItems[i]=i%3==1?200+i:-1;ui->skillGuids[i]=(c.variant&2)?100+i:-1;ui->itemGuids[i]=(c.variant&1)?200+i:-1;ui->counts[i]=c.variant%3;}
  if(c.scenario==23||(c.variant&4&&i%3==2))ui->buttons[i]=NULL;
 }
 if(c.scenario==0)ui->player=NULL;
 if(c.scenario==1)player->inventory=NULL;
 if(c.scenario==2||c.scenario==29)player->skills=NULL;
 std::memcpy(memory[79],memory[1],sizeof(ActorState));ActorState& alternate=actor(object<CCharacter>(79));alternate.skills=object<CSkillManager>(97);alternate.inventory=object<CInventory>(98);
 for(int i=0;i<3;++i)alternate.primarySkills[i]=104+i;
 if(c.scenario==33||c.scenario==34)for(int i=0;i<10;++i)player->hotkeySkills[i]=100+i;
 if(c.scenario==35)for(int i=0;i<4;++i)field<float>(images[i],0x24)=c.variant&1?-17.0f:0.0f;
}
static void snapshot(){
 n(900);ptr(ui->player);ptr(ui->resources);guid(ui->leftGuid);guid(ui->rightGuid);guid(ui->attackGuid);for(int i=0;i<3;++i)guid(ui->primaryUserGuids[i]);
 for(int i=0;i<10;++i){guid(ui->skillGuids[i]);guid(ui->itemGuids[i]);n(ui->counts[i]);}
 for(int i=0;i<40;++i){n(windows[i]->d_ID);ptr(windows[i]->d_userData);str(windows[i]->d_text);str(imageValues[i]);str(tintValues[i]);str(tooltipValues[i]);cap->add(&positions[i],sizeof(positions[i]));cap->add(&sizes[i],sizeof(sizes[i]));}
 f(ui->slotWidth);n(scaleCalls);n(masterCalls);n(lookupCalls);n(propertyCalls);n(KSETTINGS_YRATIO);
}
static void side(const Case& c,bool ours,autotest::Capture& out){
 setup(c,out);detour::Set first,second;
 TL_REDIRECT(first,slotsDependency00,&findSkill);
 TL_REDIRECT(first,slotsDependency01,&skillIcon);
 TL_REDIRECT(first,slotsDependency02,&narrow);
 TL_REDIRECT(first,slotsDependency03,&imageLookup);
 TL_REDIRECT(first,slotsDependency04,&cooling);
 TL_REDIRECT(first,slotsDependency05,&signedValue);
 TL_REDIRECT(first,slotsDependency06,&convert);
 TL_REDIRECT(first,slotsDependency07,&unitData);
 TL_REDIRECT(first,slotsDependency08,&dataValue);
 TL_REDIRECT(first,slotsDependency09,&master);
 TL_REDIRECT(first,slotsDependency10,&ratio);
 TL_REDIRECT(first,slotsDependency11,&scaled);
 TL_REDIRECT(first,slotsDependency12,&itemCount);
 TL_REDIRECT(first,slotsDependency13,&unsignedValue);
 TL_REDIRECT(first,slotsDependency14,&translator);
 TL_REDIRECT(first,slotsDependency15,&translate);
 second.redirect(slotsDependency16,slotsDependency16,&imageString);
 second.redirect(slotsDependency17,slotsDependency17,&property);
 second.redirect(slotsDependency18,slotsDependency18,&setText);
 second.redirect(slotsDependency19,slotsDependency19,&setSize);
 second.redirect(slotsDependency20,slotsDependency20,&setPosition);
 second.redirect(slotsDependency21,slotsDependency21,&setTooltip);
 second.redirect(slotsDependency22,slotsDependency22,&setID);
 if(first.failed()||second.failed())_exit(60);
 for(frame=0;frame<2;++frame){
  n(800);n(frame);
  if(frame==0){if(ours)candidateSlots(game);else originalSlots(game);}
  else {if(ours)autotest::invoke(out,&candidateSlots,game);else autotest::invoke(out,&originalSlots,game);}
  snapshot();
 }
}
static void left(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void right(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(gameui_update_slots_differential){
 using namespace slots_fixture;
 autotest::Coverage coverage("gameui_update_slots_differential",reinterpret_cast<uintptr_t>(&originalSlots));
 unsigned total=0;
 for(unsigned scenario=0;scenario<37;++scenario)for(unsigned variant=0;variant<16;++variant){
  Case c={scenario,variant};autotest::Outcome a,b;autotest::runChild(left,&c,a);autotest::runChild(right,&c,b);
  int difference=coverage.observe(host,a,b);++total;
  if(difference||a.childStatus||b.childStatus||!a.reportValid||!b.reportValid||!a.capture.callCompleted||!b.capture.callCompleted){
   coverage.report(host);
   host->log("    slots case %u variant %u differs, exits %d/%d, lengths %lu/%lu\n",scenario,variant,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
   size_t off=0;while(off<a.capture.length&&off<b.capture.length&&a.capture.data[off]==b.capture.data[off])++off;
   host->log("    first byte %lu\n",(unsigned long)off);
   for(size_t i=off/4>8?off/4-8:0;i<off/4+20;++i){unsigned x=0,y=0;if(i*4+4<=a.capture.length)std::memcpy(&x,a.capture.data+i*4,4);if(i*4+4<=b.capture.length)std::memcpy(&y,b.capture.data+i*4,4);host->log("    word %lu: %u / %u\n",(unsigned long)i,x,y);}
   return 1;
  }
 }
 coverage.report(host);host->log("    updateSlots: %u completed two-frame comparisons\n",total);return 0;
}
