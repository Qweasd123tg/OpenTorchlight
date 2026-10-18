#include "ParentPairs.h"
#include "Detour.h"
#include "Cinematics.h"
#include "Cinematic.h"
#include "DataGroup.h"
#include "GameVariables.h"
#include <new>
TL_ORIGINAL(void,oldLoad,(CCinematic*,CDataGroup*),"_ZN10CCinematic4loadEP10CDataGroup")
extern "C" void newLoad(CCinematic*,CDataGroup*) __asm__("_ZN10CCinematic4loadEP10CDataGroup");
TL_ORIGINAL(void,oldDestroy,(CCinematics*),"_ZN11CCinematicsD1Ev")
extern "C" void newDestroy(CCinematics*) __asm__("_ZN11CCinematicsD1Ev");
extern "C" char nedFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
autotest::Capture* cap;CCinematics* receiver;CCinematic* entries[12];unsigned freed;std::wstring values[4];
void freeEntry(void* p){unsigned index=99;for(unsigned i=0;i<12;++i)if(p==entries[i])index=i;parentpairs::scalar(*cap,index);parentpairs::scalar(*cap,receiver->m_mapCinematics.size());if(index==99){cap->issue=autotest::Capture::InvalidReport;return;}for(unsigned i=0;i<index;++i)if(receiver->m_lCinematics[i])cap->issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<4;++i){int references;std::memcpy(&references,reinterpret_cast<const char*>(values[i].c_str())-8,4);parentpairs::scalar(*cap,references);}++freed;}
void loadSide(void* raw,autotest::Capture& out,bool ours){unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;CDataGroup data(L"CINEMATIC",NULL,2,2,NULL);const wchar_t* names[]={L"NAME",L"TEXT",L"IMAGE",L"SOUND"};for(unsigned i=0;i<4;++i)if(seed&(1u<<i)){std::wstring value=seed%3?L"cinematic Ж Ω":L"";value.append(seed/4,wchar_t('a'+i));if(seed%7==0)value.append(1,wchar_t(0));data.SetDataValue(names[i],value,false);}CCinematic entry;entry.m_sName=L"previous-name";entry.m_sText=L"previous-text";entry.m_sImage=L"previous-image";entry.m_sSound=L"previous-sound";typedef void(*Fn)(CCinematic*,CDataGroup*);Fn fn=ours?newLoad:oldLoad;autotest::invoke(out,fn,&entry,&data);out.addText(entry.m_sName);out.addText(entry.m_sText);out.addText(entry.m_sImage);out.addText(entry.m_sSound);}
void destroySide(void* raw,autotest::Capture& out,bool ours){unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;freed=0;for(unsigned i=0;i<12;++i)entries[i]=NULL;for(unsigned j=0;j<4;++j){values[j]=L"retained string Ж";values[j].append(j+seed%5,wchar_t('a'+j));}void* memory=autotest::allocate(sizeof(CCinematics));receiver=reinterpret_cast<CCinematics*>(memory);new(static_cast<CRunicCore*>(receiver)) CRunicCore;new(&receiver->m_sPath) std::wstring(L"cinematic-fixture");new(&receiver->m_lCinematics) TArrayList<CCinematic*>(2);new(&receiver->m_mapCinematics) std::map<std::wstring,unsigned>;unsigned count=seed%12;for(unsigned i=0;i<count;++i){if((seed+i)%4){void* p=Ogre::NedAllocImpl::allocBytes(sizeof(CCinematic),NULL,0,NULL);entries[i]=new(p) CCinematic;entries[i]->m_sName=values[0];entries[i]->m_sText=values[1];entries[i]->m_sImage=values[2];entries[i]->m_sSound=values[3];}receiver->m_lCinematics.add(entries[i]);std::wstring key=values[i%4];key.append(i,L'x');receiver->m_mapCinematics[key]=i;}g_pCinematics=seed&1?receiver:NULL;detour::Set patches;patches.redirect(nedFree,nedFree,&freeEntry);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CCinematics*);Fn fn=ours?newDestroy:oldDestroy;autotest::invoke(out,fn,receiver);parentpairs::scalar(out,freed);parentpairs::scalar(out,g_pCinematics==NULL);parentpairs::scalar(out,receiver->m_lCinematics.size());patches.restore();for(unsigned i=0;i<count;++i)if(entries[i])Ogre::NedAllocImpl::deallocBytes(entries[i]);}
void la(void*p,autotest::Capture&c){loadSide(p,c,false);}void lb(void*p,autotest::Capture&c){loadSide(p,c,true);}void da(void*p,autotest::Capture&c){destroySide(p,c,false);}void db(void*p,autotest::Capture&c){destroySide(p,c,true);}
}
TL_TEST(advance_logic_cinematic_load){return parentpairs::run(host,"advance_logic_cinematic_load",(uintptr_t)oldLoad,48,la,lb);}
TL_TEST(advance_logic_cinematics_destroy){return parentpairs::run(host,"advance_logic_cinematics_destroy",(uintptr_t)oldDestroy,36,da,db);}
