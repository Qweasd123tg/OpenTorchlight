#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,std::wstring,float), "_ZN10CCharacter18transformCharacterESbIwSt11char_traitsIwESaIwEEf")
extern "C" void candidate0(void*,std::wstring,float) __asm__("_ZN10CCharacter18transformCharacterESbIwSt11char_traitsIwESaIwEEf");
TL_ORIGINAL(void, original1, (void*), "_ZN10CCharacter6fameUpEv")
extern "C" void candidate1(void*) __asm__("_ZN10CCharacter6fameUpEv");
TL_ORIGINAL(void, original2, (void*,float,void*), "_ZN10CCharacter14fishingAICatchEfR6CLevel")
extern "C" void candidate2(void*,float,void*) __asm__("_ZN10CCharacter14fishingAICatchEfR6CLevel");
TL_FUNCTION(dep_achievements, "_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(dep_achievement, "_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(dep_complete, "_ZN12CAchievement13forceCompleteEv")
TL_FUNCTION(dep_alignment, "_ZN10CCharacter9alignmentEv")
TL_FUNCTION(dep_convert, "_ZN10CCharacter16convertCharacterESbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(dep_setAlignment, "_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(dep_visible, "_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(dep_globals, "_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(dep_points, "_ZN7CPlayer33getSkillPointsAwardedForFameLevelEj")
TL_FUNCTION(dep_sample, "_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(dep_translator, "_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(dep_translate, "_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(dep_gameUI, "_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(dep_master, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dep_maxFame, "_ZN22CMasterResourceManager15getMaxFameLevelEv")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(dep_modal, "_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(dep_big, "_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(dep_small, "_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")

extern "C" void* originalCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* originalPlayerTable[] __asm__("_ZTV7CPlayer");
extern "C" std::wstring cachedFame __asm__("_ZZN10CCharacter6fameUpEvE15g_FameIncreased");
extern "C" unsigned char guardFame __asm__("_ZGVZN10CCharacter6fameUpEvE15g_FameIncreased");
extern "C" std::wstring cachedRank __asm__("_ZZN10CCharacter6fameUpEvE17g_YouAttainedRank");
extern "C" unsigned char guardRank __asm__("_ZGVZN10CCharacter6fameUpEvE17g_YouAttainedRank");
extern "C" std::wstring cachedFishing __asm__("_ZZN10CCharacter14fishingAICatchEfR6CLevelE9g_Fishing");
extern "C" unsigned char guardFishing __asm__("_ZGVZN10CCharacter14fishingAICatchEfR6CLevelE9g_Fishing");
extern "C" std::wstring cachedNothing __asm__("_ZZN10CCharacter14fishingAICatchEfR6CLevelE15g_CaughtNothing");
extern "C" unsigned char guardNothing __asm__("_ZGVZN10CCharacter14fishingAICatchEfR6CLevelE15g_CaughtNothing");
namespace {
using namespace smallmass;
void *self,*settings,*services,*ui;
void* achievements(){number(1);return services;}
void* achievement(void* p,int type){event(2,p);number(type);return type==6&&input->index%5==0?0:services;}
void complete(void* p){event(3,p);}
int alignment(void* p){event(4,p);return field<int>(p,0x338);}
void convert(void* p,std::wstring name,bool flag){event(5,p);text(name);number(flag);field<std::wstring>(p,0x4c0)=L"transformed display";field<int>(p,0x338)=99;}
void setAlignment(void* p,int value){event(6,p);number(value);field<int>(p,0x338)=value;}
void visible(void* p,bool value,bool immediate){event(7,p);number(value);number(immediate);field<bool>(p,0x81)=value;}
void* globals(){number(8);return settings;}
int points(void* p,unsigned level){event(9,p);number(level);return int(level%7)+1;}
void sample(void* p,int id,float volume,float pitch){event(10,p);number(id);floating(volume);floating(pitch);}
void* translator(){number(11);return services;}
std::wstring translate(void* p,const wchar_t* source){event(12,p);text(std::wstring(source));return L"["+std::wstring(source)+L"]";}
void* gameUI(void* p){event(13,p);return ui;}
void* master(){number(14);return services;}
int maxFame(void* p){event(15,p);return 5;}
bool playing(void* p,const std::string& name){event(16,p);text(name);return input->index%3==0;}
void modal(void* p,std::wstring title,std::wstring body,bool flag){event(17,p);text(title);text(body);number(flag);}
void big(void* p,std::wstring value,float duration){event(18,p);text(value);floating(duration);}
void small(void* p,std::wstring value,float duration){event(19,p);text(value);floating(duration);}
void state(void* p,int value){event(20,p);number(value);field<int>(p,0x330)=value;}
void initCache(std::wstring& value,unsigned char& guard,const wchar_t* cached){new(&value)std::wstring(input->index&64?cached:L"");guard=input->index&16?1:0;}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;self=object(0xa70);settings=object(0x110);services=object(0x100);ui=object(0x500);
 void* resources=object(0x48);void* level=object(0x2f0);void* client=object(0x120);
 void** storage=static_cast<void**>(object(0x450));storage[1]=(c.index&1?originalPlayerTable:originalCharacterTable)[1];void** table=storage+2;table[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=table;
 field<void*>(self,0x68)=resources;field<void*>(resources,0x18)=level;field<void*>(level,0x220)=client;field<void*>(client,0x78)=ui;
 field<void*>(self,0x200)=object(0x258);field<void*>(self,0x298)=c.index%3?services:0;
 field<unsigned>(self,0x100)=c.index%12;field<int>(self,0x450)=int(c.index%9)-1;field<int>(self,0x460)=7;
 field<int>(self,0x330)=c.index%4==0?0x2a:2;field<int>(self,0x338)=c.index%6;field<long long>(self,0x690)=c.index&2?-1LL:0x234567898765LL;field<long long>(self,0x1a0)=0xabcdef123456LL;
 new(static_cast<char*>(self)+0x4c0)std::wstring(c.index%3?L"Companion Ω":L"");
 std::wstring* ranks=static_cast<std::wstring*>(object(5*sizeof(std::wstring)));
 for(unsigned i=0;i<5;++i)new(ranks+i)std::wstring(i==0?L"Unknown":i==1?L"Known":i==2?L"Respected":i==3?L"Famous":L"Legend");
 smallmass::list(settings,0xc0,ranks,1+c.index%5,5);
 if(c.op==1){initCache(cachedFame,guardFame,L"cached fame");initCache(cachedRank,guardRank,L"cached rank");}
 if(c.op==2){initCache(cachedFishing,guardFishing,L"cached fishing");initCache(cachedNothing,guardNothing,L"cached nothing");}
 detour::Set patches;
 TL_REDIRECT(patches,dep_achievements,&achievements);
 TL_REDIRECT(patches,dep_achievement,&achievement);
 TL_REDIRECT(patches,dep_complete,&complete);
 TL_REDIRECT(patches,dep_alignment,&alignment);
 TL_REDIRECT(patches,dep_convert,&convert);
 TL_REDIRECT(patches,dep_setAlignment,&setAlignment);
 TL_REDIRECT(patches,dep_visible,&visible);
 TL_REDIRECT(patches,dep_globals,&globals);
 TL_REDIRECT(patches,dep_points,&points);
 TL_REDIRECT(patches,dep_sample,&sample);
 TL_REDIRECT(patches,dep_translator,&translator);
 TL_REDIRECT(patches,dep_translate,&translate);
 TL_REDIRECT(patches,dep_gameUI,&gameUI);
 TL_REDIRECT(patches,dep_master,&master);
 TL_REDIRECT(patches,dep_maxFame,&maxFame);
 TL_REDIRECT(patches,dep_playing,&playing);
 TL_REDIRECT(patches,dep_modal,&modal);
 TL_REDIRECT(patches,dep_big,&big);
 TL_REDIRECT(patches,dep_small,&small);

 if(patches.failed())_exit(41);
 const wchar_t* names[]={L"rat",L"pet mimic",L"PET MIMIC",L"Pet Mimic ",L""};
 const float times[]={0,1.5f,-999,-1,500};
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,std::wstring(names[c.index%5]),times[(c.index/5)%5]);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,.125f,services);break;
 }
 number(field<int>(self,0x330));number(field<int>(self,0x338));number(field<bool>(self,0x81));number(field<int>(self,0x450));number(field<int>(self,0x460));floating(field<float>(self,0x688));out.add(&field<long long>(self,0x690),8);text(field<std::wstring>(self,0x4c0));
}
}
TL_TEST(mass3_842150) { return smallmass::run(host,0,"mass3_842150",(uint64_t)(uintptr_t)original0,execute,128); }
TL_TEST(mass3_837630) { return smallmass::run(host,1,"mass3_837630",(uint64_t)(uintptr_t)original1,execute,128); }
TL_TEST(mass3_83c140) { return smallmass::run(host,2,"mass3_83c140",(uint64_t)(uintptr_t)original2,execute,128); }
