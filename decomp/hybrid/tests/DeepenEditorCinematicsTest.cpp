#include <string>
#include <map>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "Cinematics.h"
#include "Cinematic.h"
#include "DataGroup.h"
#include "FileSystem.h"
#undef private
#include "GameVariables.h"
TL_ORIGINAL(void,dmOld,(CCinematics*),"_ZN11CCinematics6reloadEv")
extern "C" void dmNew(CCinematics*) __asm__("_ZN11CCinematics6reloadEv");
TL_FUNCTION(dmFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(dmSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(dmLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
namespace {
struct Case{unsigned seed;};autotest::Capture*cap;unsigned seed,loads,enumerations;CCinematics*receiver;std::wstring retained;
void n(unsigned x){cap->add(&x,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}
CFileSystem*singleton(){return reinterpret_cast<CFileSystem*>(receiver);}
unsigned files(CFileSystem*p,const std::wstring&path,TArrayList<std::wstring>&out,std::wstring pattern,bool recurse,bool strip,bool mods,bool skip){++enumerations;n(1);cap->addText(path);cap->addText(pattern);n(recurse);n(strip);n(mods);n(skip);if(p!=singleton()||path!=receiver->m_sPath||pattern!=L"*.dat"||!recurse||!strip||mods||skip||receiver->m_lCinematics.size())invalid();for(unsigned i=0;i<seed%5;++i){wchar_t text[64];std::swprintf(text,64,L"synthetic/cinematic%u.dat",i);out.add(text);}return out.size();}
void load(CDataGroup*p,const std::wstring&path,CTimerStatics*t){n(2);cap->addText(path);if(t||loads>=seed%5)invalid();p->AddDataValue(L"NAME",loads%2?L"DUPLICATE":L"cinematic",false);p->AddDataValue(L"TEXT",retained.c_str(),false);p->AddDataValue(L"IMAGE",L"image.dds",false);if(seed&1)p->AddDataValue(L"SOUND",L"sound.ogg",false);++loads;}
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;loads=enumerations=0;retained=L"retained cinematic Ж";CCinematics*memory=reinterpret_cast<CCinematics*>(autotest::allocate(sizeof(CCinematics)));new(static_cast<CRunicCore*>(memory))CRunicCore;new(&memory->m_sPath)std::wstring(L"cinematics/");new(&memory->m_lCinematics)TArrayList<CCinematic*>(10);new(&memory->m_mapCinematics)std::map<std::wstring,unsigned>;CCinematics&self=*memory;receiver=&self;g_pCinematics=receiver;for(unsigned i=0;i<seed%4;++i){CCinematic*p=NULL;if(i%3!=2){p=new(Ogre::NedAllocImpl::allocBytes(sizeof(CCinematic),NULL,0,NULL))CCinematic;p->m_sName=retained;p->m_sText=retained;p->m_sImage=retained;p->m_sSound=retained;}self.m_lCinematics.add(p);}self.m_mapCinematics[L"stale"]=99;self.m_mapCinematics[L"cinematic"]=44;
 detour::Set patches;TL_REDIRECT(patches,dmSingleton,&singleton);TL_REDIRECT(patches,dmFiles,&files);TL_REDIRECT(patches,dmLoad,&load);if(patches.failed()){invalid();return;}typedef void(*Fn)(CCinematics*);Fn fn=ours?dmNew:dmOld;if(!autotest::beginInvocation(out,fn))return;fn(&self);out.callCompleted=1;if(loads!=seed%5||enumerations!=1||self.m_lCinematics.size()!=seed%5)invalid();n(loads);n(enumerations);n(self.m_lCinematics.m_nGrowBy);for(unsigned i=0;i<self.m_lCinematics.size();++i){CCinematic*p=self.m_lCinematics[i];out.addText(p->m_sName);out.addText(p->m_sText);out.addText(p->m_sImage);out.addText(p->m_sSound);}n(self.m_mapCinematics.size());for(std::map<std::wstring,unsigned>::iterator i=self.m_mapCinematics.begin();i!=self.m_mapCinematics.end();++i){out.addText(i->first);n(i->second);}int refs;std::memcpy(&refs,reinterpret_cast<const char*>(retained.c_str())-8,4);out.add(&refs,4);self.~CCinematics();}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(deepen_editor_cinematics_reload){autotest::Coverage coverage("deepen_editor_cinematics_reload",(uintptr_t)&dmOld);for(unsigned seed=0;seed<48;++seed){Case c={seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    cinematics seed%u issue%u/%u exit%d/%d\n",seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
