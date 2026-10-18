#include "ParentPairs.h"
#include "Detour.h"
#include "DescriptorLoadConfiguration.h"
#include <OgreLogManager.h>
TL_ORIGINAL(void,oldAdd,(CDescriptorLoadConfiguration*,long long,long long),"_ZN28CDescriptorLoadConfiguration8addRemapExx")
extern "C" void newAdd(CDescriptorLoadConfiguration*,long long,long long) __asm__("_ZN28CDescriptorLoadConfiguration8addRemapExx");
extern "C" char logSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char logMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
autotest::Capture* cap;unsigned logCount;
Ogre::LogManager& singleton(){++logCount;return *reinterpret_cast<Ogre::LogManager*>(autotest::g_arena);}
void log(Ogre::LogManager* self,const std::string& message,Ogre::LogMessageLevel level,bool skip){parentpairs::scalar(*cap,self==reinterpret_cast<Ogre::LogManager*>(autotest::g_arena));cap->addText(message);parentpairs::scalar(*cap,level);parentpairs::scalar(*cap,skip);}
void side(void* raw,autotest::Capture& out,bool ours){unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;logCount=0;CDescriptorLoadConfiguration config;const long long keys[]={-1,0,1,-2,(-9223372036854775807LL-1),9223372036854775807LL,0x100000003LL};for(unsigned i=0;i<seed%7;++i)config.m_Remaps[keys[i]]=keys[6-i];long long from=keys[seed/7%7],to=keys[seed%7];detour::Set patches;patches.redirect(logSingleton,logSingleton,&singleton);patches.redirect(logMessage,logMessage,&log);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CDescriptorLoadConfiguration*,long long,long long);Fn fn=ours?newAdd:oldAdd;autotest::invoke(out,fn,&config,from,to);parentpairs::scalar(out,logCount);parentpairs::scalar(out,config.m_Remaps.size());for(std::map<long long,long long>::iterator i=config.m_Remaps.begin();i!=config.m_Remaps.end();++i){parentpairs::scalar(out,i->first);parentpairs::scalar(out,i->second);}}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_logic_add_remap){return parentpairs::run(host,"advance_logic_add_remap",(uintptr_t)oldAdd,98,a,b);}
