#include <cstring>
#include <string>
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Settings.h"
#undef protected
#undef private
TL_ORIGINAL(CSettings*,stOld,(const std::string&,bool&),"_Z14createSettingsRKSsRb")
extern "C" CSettings*stNew(const std::string&,bool&) __asm__("_Z14createSettingsRKSsRb");
TL_FUNCTION(stCtor,"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_FUNCTION(stConvert,"_ZN7STRINGS19StringConvertToWideEPKcj")
TL_FUNCTION(stDirectory,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(stInt,"_ZN14CCmdLineParser11GetIntParamERKSbIwSt11char_traitsIwESaIwEEi")
namespace {
using namespace smallmass;
unsigned seed;CSettings*settings;CCmdLineParser*parser;void*settingsVT[4];
void settingsCtor(CSettings*p,std::wstring command,std::wstring directory,std::wstring local,std::wstring main){number(5);text(command);text(directory);text(local);text(main);settings=p;*reinterpret_cast<void***>(p)=settingsVT;p->m_pCmdLineParser=parser;}
std::wstring convert(const char*p,unsigned count){number(6);text(std::string(p));number(count);return seed&4?L"команда -x":L"";}
std::wstring directory(){number(7);return seed&8?L"/home/test/путь/":L"";}
int getInt(CCmdLineParser*p,const std::wstring&key,int fallback){number(8);number(p==parser);text(key);number(fallback);return int(seed%3)-1;}
bool load(CSettings*p,const std::wstring&file){number(9);number(p==settings);text(file);return seed&16;}
void settingsSide(Case&c,bool ours,autotest::Capture&out){output=&out;seed=c.index;settings=NULL;settingsVT[3]=reinterpret_cast<void*>(&load);parser=static_cast<CCmdLineParser*>(object(sizeof(CCmdLineParser)));bool failed=seed&1;std::string cmd=seed&2?"-SAFEMODE=1 --abc":"";typedef CSettings*(*Fn)(const std::string&,bool&);Fn fn=ours?stNew:stOld;if(!autotest::beginInvocation(out,fn))return;CSettings*result=fn(cmd,failed);out.callCompleted=1;number(result==settings);number(failed);Ogre::GeneralAllocPolicy::deallocateBytes(result);}
}
TL_TEST(complete_settings_create){detour::Set h;TL_REDIRECT(h,stCtor,&settingsCtor);TL_REDIRECT(h,stConvert,&convert);TL_REDIRECT(h,stDirectory,&directory);TL_REDIRECT(h,stInt,&getInt);if(h.failed())return 1;return smallmass::run(host,1,"complete_settings_create",0xd61a40,&settingsSide,64);}
