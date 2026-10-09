#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreBone.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreUTFString.h>
#include "StatsMenu.h"
#include "Character.h"
#include "GenericModel.h"
#include "GameUI.h"
#include "GameGlobals.h"
#include "MasterResourceManager.h"
#include "ResourceManager.h"
#include "DynamicPropertyFile.h"
#include "GameVariables.h"
#include "StringTranslate.h"
#include "TArrayList.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldUpdate,(CStatsMenu*,float),"_ZN10CStatsMenu6updateEf")
extern "C" void newUpdate(CStatsMenu*,float) __asm__("_ZN10CStatsMenu6updateEf");
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(valueUnsignedFn,"_ZN7STRINGS16GetValueAsStringEj")
TL_FUNCTION(valueIntFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(valueWideFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(narrowFn,"_ZN7STRINGS21StringConvertToNarrowEPKw")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(xpGateFn,"_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(fameGateFn,"_ZN22CMasterResourceManager8fameGateEi")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(globalsFn,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(animationFn,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(modelPosFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(playingFn,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(queuedFn,"_ZNK13CGenericModel15animationQueuedERKSs")
TL_FUNCTION(minimumFn,"_ZN10CCharacter23minimumDamageForDisplayEbbb")
TL_FUNCTION(maximumFn,"_ZN10CCharacter23maximumDamageForDisplayEbbb")
TL_FUNCTION(criticalFn,"_ZN10CCharacter17getCriticalChanceEv")
TL_FUNCTION(resistanceFn,"_ZN10CCharacter13damageDefenseE13EDAMAGE_TYPES")
TL_FUNCTION(armorFn,"_ZN10CCharacter2ACEv")
TL_FUNCTION(minimumArmorFn,"_ZN10CCharacter9minimumACEv")
TL_FUNCTION(baseArmorFn,"_ZN10CCharacter6baseACEv")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(uiFn,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(tipFn,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(strengthFn,"_ZN10CCharacter8strengthEv")
TL_FUNCTION(dexterityFn,"_ZN10CCharacter9dexterityEv")
TL_FUNCTION(magicFn,"_ZN10CCharacter5magicEv")
TL_FUNCTION(defenseFn,"_ZN10CCharacter7defenseEv")
TL_FUNCTION(healthFn,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(manaFn,"_ZN10CCharacter7maxManaEv")
TL_FUNCTION(blockFn,"_ZN10CCharacter14getBlockChanceEv")
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char tooltipFn[] __asm__("_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
extern "C" char getTooltipFn[] __asm__("_ZNK5CEGUI6Window14getTooltipTextEv");
extern "C" char propertyFn[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char sizeFn[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char positionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char entityFn[] __asm__("_ZN4Ogre6Entity16_updateAnimationEv");
namespace {
struct Case {unsigned owner,open,closed,profile,scale,cache,mutate;};
autotest::Capture* capture;const Case* input;CStatsMenu* menu;CCharacter* actor;CGameUI* ui[2];CResourceManager* resources;CMasterResourceManager* master;CGameGlobals* globals;CStringTranslate* translator;CDynamicPropertyFile* settings;CGenericModel* model;Ogre::Entity* entity;Ogre::SkeletonInstance* skeleton;Ogre::Bone* bones[3];Ogre::Vector3 tagPositions[3];
CEGUI::Window* windows[40];unsigned long long windowMemory[40][(sizeof(CEGUI::Window)+7)/8];unsigned windowCount,scaleCalls,positionCalls,getterCalls[12];bool modelVisible;
void* modelTable[96];void* skeletonTable[96];void* boneTable[96];
const uintptr_t caches[]={0x14d5a30,0x14d5a28,0x14d5a20,0x14d5a18,0x14d5a10,0x14d5a08,0x14d5a00};
const uintptr_t guards[]={0x14d59c8,0x14d59d0,0x14d59d8,0x14d59e0,0x14d59e8,0x14d59f0,0x14d59f8};
template<class T>T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){capture->add(&x,4);}void f(float x){capture->add(&x,4);}
void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int id(const CEGUI::Window* p){for(unsigned i=0;i<windowCount;++i)if(p==windows[i])return i;return p?-2:-1;}
CEGUI::Window* window(){if(windowCount==40)_exit(40);CEGUI::Window* p=(CEGUI::Window*)windowMemory[windowCount];windows[windowCount++]=p;new(&p->d_text)CEGUI::String();new(&p->d_tooltipText)CEGUI::String();p->d_visible=input->profile%2;return p;}
void text(CEGUI::Window* p,const CEGUI::String& s){n(1);n(id(p));str(s);p->d_text=s;}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){n(2);n(id(p));str(s);p->d_tooltipText=s;}
const CEGUI::String& getTooltip(const CEGUI::Window* p){n(3);n(id(p));return p->d_tooltipText;}
void property(CEGUI::PropertySet* p,const CEGUI::String& key,const CEGUI::String& value){n(4);n(id(static_cast<CEGUI::Window*>(p)));str(key);str(value);}
void visible(CEGUI::Window* p,bool b){n(5);n(id(p));n(b);p->d_visible=b;}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(id(p));capture->add(&v,sizeof(v));}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(7);n(id(p));capture->add(&v,sizeof(v));}
void remove(CEGUI::Window* p,CEGUI::Window* q){n(8);n(id(p));n(id(q));q->d_parent=0;}
int getInt(CDynamicPropertyFile* p,unsigned key){n(9);n(p==settings);n(key);const int widths[]={1920,0,-1,2147483647};const int heights[]={1080,0,1,-2147483647};return key==101?widths[input->profile%4]:heights[input->profile%4];}
std::string valueInt(int x){n(10);n(x);char b[32];std::sprintf(b,"%d",x);return b;}
std::string valueUnsigned(unsigned x){n(11);n(x);char b[32];std::sprintf(b,"%u",x);return b;}
std::wstring valueWide(int x){n(12);n(x);char b[32];std::sprintf(b,"%d",x);return std::wstring(b,b+std::strlen(b));}
std::string convert(const std::wstring& s){n(13);capture->addText(s);return Ogre::UTFString(s).asUTF8();}
std::string narrow(const wchar_t* s){n(14);capture->addText(std::wstring(s));return Ogre::UTFString(std::wstring(s)).asUTF8();}
CStringTranslate* translateSingleton(){n(15);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* s){n(16);n(p==translator);capture->addText(std::wstring(s));return input->cache==2?L"":input->cache==1?std::wstring(s)+L" \u03a9\u0416\u4e2d":std::wstring(s);}
CMasterResourceManager* getMaster(){n(17);return master;}
CGameGlobals* getGlobals(){n(18);return globals;}
int gate(CMasterResourceManager* p,int level,bool fame){n(fame?20:19);n(p==master);n(level);int current=fame?at<int>(actor,0x450):int(at<unsigned>(actor,0x100));int lower=10,upper=200;if(input->profile==4||input->profile==5)upper=lower;if(input->profile==6)upper=-100;return level==current?upper:lower;}
int xpGate(CMasterResourceManager* p,int level){return gate(p,level,false);}int fameGate(CMasterResourceManager* p,int level){return gate(p,level,true);}
int getter(CCharacter* p,unsigned kind){n(21);n(p==actor);n(kind);++getterCalls[kind];const unsigned offsets[]={0x42c,0x428,0x434,0x430,0x418,0x43c};int base=kind<6?at<int>(actor,offsets[kind]):40;int modifier=input->profile%3==0?2:input->profile%3==1?0:-2;int value=int(unsigned(base)+unsigned(modifier)+(input->mutate?getterCalls[kind]:0));n(value);return value;}
int strength(CCharacter* p){return getter(p,0);}int dexterity(CCharacter* p){return getter(p,1);}int magic(CCharacter* p){return getter(p,2);}int defense(CCharacter* p){return getter(p,3);}int health(CCharacter* p){return getter(p,4);}int mana(CCharacter* p){return getter(p,5);}int critical(CCharacter* p){return getter(p,6);}int block(CCharacter* p){return getter(p,7);}
int minimum(CCharacter* p,bool a,bool b,bool c){n(22);n(p==actor);n(a);n(b);n(c);int value=2+int(a)*3+int(b)*4+int(c)*2;if(b){if(input->profile==2&&!a)value=0;if(input->profile==3&&a)value=0;if(input->profile==4)value=0;if(input->profile==5&&!a)value=-7;}return value;}
int maximum(CCharacter* p,bool a,bool b,bool c){n(23);n(p==actor);n(a);n(b);n(c);int mod=input->profile%3==0?5:input->profile%3==1?0:-5;return 40+int(a)*2+int(b)*3+(c?0:mod);}
int baseArmor(CCharacter* p){n(24);n(p==actor);return 40;}int armor(CCharacter* p){n(25);n(p==actor);return 38+int(input->profile%3)*2;}int minimumArmor(CCharacter* p){n(26);n(p==actor);return -5+int(input->profile);}
int resistance(CCharacter* p,EDAMAGE_TYPES type){n(27);n(p==actor);n(type);return int(type)*11-int(input->profile)*4;}
CGameUI* getUi(CResourceManager* p){n(28);n(p==resources);return ui[0];}void tip(CGameUI* p,EContextTip t){n(29);n(p==ui[0]);n(t);}
float scaled(CGameUI* p,float x){n(30);n(p==ui[0]?0:p==ui[1]?1:-1);f(x);++scaleCalls;const float scales[]={1,0,-0.0f,-1.0f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float result=x*scales[input->scale];if(input->mutate){result+=float(scaleCalls)*.03125f;menu->m_pGameUI=p==ui[0]?ui[1]:ui[0];}return result;}
void animation(CGenericModel* p,float elapsed,bool force){n(31);n(p==model);f(elapsed);n(force);}
void entityUpdate(Ogre::Entity* p){n(32);n(p==entity);}
Ogre::Bone* bone(Ogre::SkeletonInstance* p,const std::string& name){n(33);n(p==skeleton);capture->addText(name);return bones[name=="tag_topcharacter"?0:name=="tag_bottomcharacter"?1:2];}
const Ogre::Vector3& derived(Ogre::Bone* p){n(34);unsigned i=0;for(;i<3;++i)if(p==bones[i])break;n(i);if(i==3)_exit(45);return tagPositions[i];}
Ogre::Vector3 modelPosition(CPositionableObject* p,bool relative){n(35);n((void*)p==(void*)model);n(relative);++positionCalls;return Ogre::Vector3(float(positionCalls)*(input->mutate?3:0)-float(input->profile),7,2);}
bool playing(const CGenericModel* p,const std::string& name){n(36);n(p==model);capture->addText(name);return input->profile%3==1;}
bool queued(const CGenericModel* p,const std::string& name){n(37);n(p==model);capture->addText(name);return input->profile%3==2;}
void modelShow(CGenericModel* p,bool b){n(38);n(p==model);n(b);modelVisible=b;}
void side(const Case& c,bool ours,autotest::Capture& out){
 capture=&out;input=&c;windowCount=scaleCalls=positionCalls=0;memset(getterCalls,0,sizeof(getterCalls));memset(windowMemory,0,sizeof(windowMemory));modelVisible=true;
 uint64_t mm[96]={0},am[192]={0},um[2][16]={0},rm[16]={0},gm[64]={0},tm[16]={0},settingsMemory[16]={0},masterMemory[16]={0},modelMemory[128]={0},entityMemory[64]={0},skeletonMemory[64]={0},boneMemory[3][64]={0};
 menu=(CStatsMenu*)mm;actor=(CCharacter*)am;ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];resources=(CResourceManager*)rm;globals=(CGameGlobals*)gm;translator=(CStringTranslate*)tm;settings=(CDynamicPropertyFile*)settingsMemory;master=(CMasterResourceManager*)masterMemory;model=(CGenericModel*)modelMemory;entity=(Ogre::Entity*)entityMemory;skeleton=(Ogre::SkeletonInstance*)skeletonMemory;
 menu->m_pParent=window();menu->m_pRoot=window();menu->m_pRoot->d_parent=menu->m_pParent;menu->m_pTopPanel=window();menu->m_pBottomPanel=window();menu->m_pExperienceBar=window();menu->m_pFameBar=window();menu->m_pNameText=window();menu->m_pFameTitleText=window();menu->m_pLevelText=window();menu->m_pFameLevelText=window();for(int i=0;i<4;++i)menu->m_AttributeTexts[i]=window();for(int i=0;i<3;++i)menu->m_DamageTexts[i]=window();menu->m_pArmorText=window();menu->m_pManaText=window();menu->m_pHealthText=window();menu->m_pExperienceText=window();menu->m_pFameText=window();for(int i=0;i<4;++i)menu->m_ResistanceTexts[i]=window();menu->m_pPointsText=window();menu->m_pPointsContainer=window();for(int i=0;i<4;++i)menu->m_SpendButtons[i]=window();for(int i=0;i<4;++i)menu->m_ReclaimButtons[i]=window();
 menu->m_pOwner=c.owner?actor:0;menu->m_pProperties=settings;menu->m_pGameUI=ui[0];menu->m_pResourceManager=resources;menu->m_pModel=model;menu->m_bOpenPartial=c.open;menu->m_bFullyClosed=c.closed;menu->m_fScreenEdge=-77;
 menu->m_ExperienceWidth=CEGUI::UDim(c.profile%2?.25f:-.25f,120);menu->m_ExperienceHeight=CEGUI::UDim(.25f,8);menu->m_FameWidth=CEGUI::UDim(-.75f,95);menu->m_FameHeight=CEGUI::UDim(9,29);
 if(c.profile==11){menu->m_ExperienceWidth.d_scale=std::numeric_limits<float>::quiet_NaN();menu->m_ExperienceHeight.d_offset=-0.0f;}
 for(int i=0;i<4;++i)menu->m_InvestedPoints[i]=c.profile==2?i-1:c.profile==3?-1:0;
 new(&menu->m_TextA0)std::wstring(L"first damage");new(&menu->m_TextB0)std::wstring(L"second damage");new(&menu->m_DamageDescription)std::wstring(L"combined damage");new(&menu->m_ArmorDescription)std::wstring(L"armor");
 at<unsigned>(actor,0x100)=c.profile==8?0:c.profile==9?0xffffffffU:2;at<int>(actor,0x448)=c.profile==5?10:c.profile==7?-30:100;at<int>(actor,0x44c)=at<int>(actor,0x448)+3;at<int>(actor,0x450)=c.profile==8?0:2;at<int>(actor,0x45c)=c.profile==0?3:c.profile==1?0:-1;
 const unsigned fields[]={0x42c,0x428,0x434,0x430,0x418,0x43c};for(int i=0;i<6;++i)at<int>(actor,fields[i])=50+i*10;
 new((char*)actor+0x4c0)std::wstring(c.cache==1?L"Hero \u03a9\u0416\u4e2d":L"Hero");
 TArrayList<std::wstring>* names=(TArrayList<std::wstring>*)((char*)globals+0xc0);new(names)TArrayList<std::wstring>(3);names->add(L"NOVICE");names->add(L"HERO");names->add(L"LEGEND");if(c.profile==11)names->m_nCapacity=1;
 for(int i=0;i<7;++i){new((void*)caches[i])std::wstring(c.cache==3?L"cached":L"");*(unsigned char*)guards[i]=c.cache==3;}
 modelTable[10]=(void*)&modelShow;skeletonTable[54]=(void*)&bone;boneTable[64]=(void*)&derived;*(void***)model=modelTable;*(void***)skeleton=skeletonTable;at<Ogre::Entity*>(model,0x60)=entity;at<Ogre::SkeletonInstance*>(model,0x130)=skeleton;
 for(int i=0;i<3;++i){bones[i]=(Ogre::Bone*)boneMemory[i];*(void***)bones[i]=boneTable;tagPositions[i]=Ogre::Vector3(float(i*7)-float(c.profile)*100,15+i*3,0);}
 KSETTINGS_RES_WIDTH=101;KSETTINGS_RES_HEIGHT=102;
 detour::Set d;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(settingsFn,getInt);R(valueUnsignedFn,valueUnsigned);R(valueIntFn,valueInt);R(valueWideFn,valueWide);R(narrowFn,narrow);R(convertFn,convert);R(xpGateFn,xpGate);R(fameGateFn,fameGate);R(masterFn,getMaster);R(globalsFn,getGlobals);R(animationFn,animation);R(modelPosFn,modelPosition);R(playingFn,playing);R(queuedFn,queued);R(minimumFn,minimum);R(maximumFn,maximum);R(criticalFn,critical);R(resistanceFn,resistance);R(armorFn,armor);R(minimumArmorFn,minimumArmor);R(baseArmorFn,baseArmor);R(scaledFn,scaled);R(uiFn,getUi);R(tipFn,tip);R(translateSingletonFn,translateSingleton);R(translateFn,translate);R(strengthFn,strength);R(dexterityFn,dexterity);R(magicFn,magic);R(defenseFn,defense);R(healthFn,health);R(manaFn,mana);R(blockFn,block);
#undef R
#define I(N,F) d.redirect(N,N,&F)
 I(textFn,text);I(tooltipFn,tooltip);I(getTooltipFn,getTooltip);I(propertyFn,property);I(visibleFn,visible);I(sizeFn,size);I(positionFn,position);I(removeFn,remove);I(entityFn,entityUpdate);
#undef I
 if(d.failed())_exit(43);
 for(int frame=0;frame<2;++frame){n(90);n(frame);if(frame){if(ours)newUpdate(menu,.125f);else oldUpdate(menu,.125f);}else{if(ours)autotest::invoke(out,&newUpdate,menu,0.0f);else autotest::invoke(out,&oldUpdate,menu,0.0f);}n(91);for(int i=0;i<4;++i)n(menu->m_InvestedPoints[i]);f(menu->m_fScreenEdge);n(menu->m_bFullyClosed);n(modelVisible);for(unsigned i=0;i<windowCount;++i){n(id(windows[i]->d_parent));n(windows[i]->d_visible);str(windows[i]->d_text);str(windows[i]->d_tooltipText);}}
 n(scaleCalls);n(positionCalls);capture->add(getterCalls,sizeof(getterCalls));for(int i=0;i<7;++i){capture->addText(*(std::wstring*)caches[i]);n(*(unsigned char*)guards[i]);}
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(stats_update_differential){
 autotest::Coverage coverage("stats_update_differential",(uint64_t)(uintptr_t)&oldUpdate);unsigned total=0;
 for(unsigned owner=0;owner<2;++owner)for(unsigned open=0;open<2;++open)for(unsigned closed=0;closed<2;++closed)for(unsigned profile=0;profile<12;++profile)for(unsigned scale=0;scale<6;++scale)for(unsigned cache=0;cache<4;++cache)for(unsigned mutate=0;mutate<2;++mutate){
 Case c={owner,open,closed,profile,scale,cache,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
 if(pair||autotest::incomplete(x)||autotest::incomplete(y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    owner %u open %u closed %u profile %u scale %u cache %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",owner,open,closed,profile,scale,cache,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>40?first-40:0;i<first+100&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}
 }coverage.report(host);host->log("    stats update: %u cases, two frames each\n",total);return 0;
}
