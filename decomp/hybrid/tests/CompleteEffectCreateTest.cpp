#include <cstring>
#include <map>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "EffectManager.h"
#include "Effect.h"
#include "DataGroup.h"
#include "BaseUnit.h"
#include "Settings.h"
#include "TRepository.h"
#undef protected
#undef private
TL_ORIGINAL(void,ecOld,(CEffectManager*,CDataGroup*,bool),"_ZN14CEffectManager12createEffectEP10CDataGroupb")
extern "C" void ecNew(CEffectManager*,CDataGroup*,bool) __asm__("_ZN14CEffectManager12createEffectEP10CDataGroupb");
TL_ORIGINAL(CSettings*,stOld,(const std::string&,bool&),"_Z14createSettingsRKSsRb")
extern "C" CSettings*stNew(const std::string&,bool&) __asm__("_Z14createSettingsRKSsRb");
TL_FUNCTION(ecCtor,"_ZN7CEffectC1EP10CDataGroupP9CBaseUnit")
TL_FUNCTION(ecAdd,"_ZN14CEffectManager12addNewEffectEP7CEffect")
TL_FUNCTION(ecActivate,"_ZN9CBaseUnit14activateEffectEP7CEffect")
TL_FUNCTION(ecClear,"_ZN14CEffectManager20clearOutDescriptionsEv")
TL_FUNCTION(stCtor,"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_FUNCTION(stConvert,"_ZN7STRINGS19StringConvertToWideEPKcj")
TL_FUNCTION(stDirectory,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(stInt,"_ZN14CCmdLineParser11GetIntParamERKSbIwSt11char_traitsIwESaIwEEi")
namespace {
using namespace smallmass;
unsigned seed;CEffectManager*manager;CBaseUnit*owner;CDataGroup*data;CEffect*created;CSettings*settings;CCmdLineParser*parser;void*settingsVT[4];
void effectCtor(CEffect*p,CDataGroup*d,CBaseUnit*u){number(1);number(d==data);number(u==owner);created=p;new(&p->m_sName)std::wstring(L"created");}
CEffect*add(CEffectManager*p,CEffect*e){number(2);number(p==manager);number(e==created);manager->m_Effects[seed%3].add(e);return e;}
void activate(CBaseUnit*p,CEffect*e){number(3);number(p==owner);number(e==created);}
void clear(CEffectManager*p){number(4);number(p==manager);}
void settingsCtor(CSettings*p,std::wstring command,std::wstring directory,std::wstring local,std::wstring main){number(5);text(command);text(directory);text(local);text(main);settings=p;*reinterpret_cast<void***>(p)=settingsVT;p->m_pCmdLineParser=parser;}
std::wstring convert(const char*p,unsigned count){number(6);text(std::string(p));number(count);return seed&4?L"команда -x":L"";}
std::wstring directory(){number(7);return seed&8?L"/home/test/путь/":L"";}
int getInt(CCmdLineParser*p,const std::wstring&key,int fallback){number(8);number(p==parser);text(key);number(fallback);return int(seed%3)-1;}
bool load(CSettings*p,const std::wstring&file){number(9);number(p==settings);text(file);return seed&16;}
void side(Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;created=NULL;settings=NULL;
 if(c.op==1){
  settingsVT[3]=reinterpret_cast<void*>(&load);parser=static_cast<CCmdLineParser*>(object(sizeof(CCmdLineParser)));bool failed=seed&1;std::string cmd=seed&2?"-SAFEMODE=1 --abc":"";
  typedef CSettings*(*Fn)(const std::string&,bool&);Fn fn=ours?stNew:stOld;if(!autotest::beginInvocation(out,fn))return;CSettings*result=fn(cmd,failed);out.callCompleted=1;number(result==settings);number(failed);Ogre::GeneralAllocPolicy::deallocateBytes(result);return;
 }
 new(reinterpret_cast<void*>(0x14781e8))std::wstring();
 new(reinterpret_cast<void*>(0x14dd9c8))std::wstring();new(reinterpret_cast<void*>(0x14dd9d8))std::wstring();new(reinterpret_cast<void*>(0x14dda88))std::wstring();new(reinterpret_cast<void*>(0x152f138))std::wstring();
 manager=static_cast<CEffectManager*>(object(sizeof(CEffectManager)));owner=static_cast<CBaseUnit*>(object(sizeof(CBaseUnit)));new(&manager->m_Owner)TSafePointer<CBaseUnit>();manager->m_Owner.m_pObject=seed&1?owner:NULL;
 for(unsigned i=0;i<3;++i)new(&manager->m_Effects[i])TArrayList<CEffect*>(2);
 TRepository<std::wstring>*repo=new TRepository<std::wstring>(L"");data=new CDataGroup(seed%5==0?L"OTHER":L"EFFECT",NULL,4,2,repo);
 const wchar_t* names[]={L"",L"fire",L"FIRE",L"mixedЖ"};data->SetDataValue(L"NAME",names[seed/2%4],false);
 CEffect*old[6];for(unsigned i=0;i<6;++i){old[i]=static_cast<CEffect*>(object(sizeof(CEffect)));new(&old[i]->m_sName)std::wstring(names[(seed/7+i)%4]);if(i<seed%7)manager->m_Effects[i%3].add(old[i]);}
 typedef void(*Fn)(CEffectManager*,CDataGroup*,bool);Fn fn=ours?ecNew:ecOld;if(!autotest::beginInvocation(out,fn))return;fn(manager,seed%13==0?NULL:data,seed&2);out.callCompleted=1;number(created!=NULL);
 for(unsigned i=0;i<3;++i){number(manager->m_Effects[i].size());manager->m_Effects[i].~TArrayList<CEffect*>();}for(unsigned i=0;i<6;++i)old[i]->m_sName.~basic_string();if(created){created->m_sName.~basic_string();Ogre::GeneralAllocPolicy::deallocateBytes(created);}manager->m_Owner.m_pObject=NULL;delete data;
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned cases){detour::Set h;TL_REDIRECT(h,ecCtor,&effectCtor);TL_REDIRECT(h,ecAdd,&add);TL_REDIRECT(h,ecActivate,&activate);TL_REDIRECT(h,ecClear,&clear);TL_REDIRECT(h,stCtor,&settingsCtor);TL_REDIRECT(h,stConvert,&convert);TL_REDIRECT(h,stDirectory,&directory);TL_REDIRECT(h,stInt,&getInt);if(h.failed())return 1;return smallmass::run(host,op,name,address,&side,cases);}
}
TL_TEST(complete_effect_create){return run(host,0,"complete_effect_create",0x7f58f0,256);}

