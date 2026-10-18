#include "SmallMassCompare.h"
#include "MusicObject.h"
#include "SafePointer.h"
TL_ORIGINAL(void, ctorOriginal,(void*,CResourceManager*),"_ZN12CMusicObjectC1EP16CResourceManager")
extern "C" void ctorCandidate(void*,CResourceManager*) __asm__("_ZN12CMusicObjectC1EP16CResourceManager");
TL_ORIGINAL(void, dtorOriginal,(void*),"_ZN12CMusicObjectD1Ev")
TL_ORIGINAL(void, fileOriginal,(void*,std::wstring),"_ZN12CMusicObject12setMusicFileESbIwSt11char_traitsIwESaIwEE")
extern "C" void fileCandidate(void*,std::wstring) __asm__("_ZN12CMusicObject12setMusicFileESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
namespace {
using namespace smallmass;void* manager;unsigned calls;
void* singleton(){event(1,manager);++calls;return manager;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;CMusicObject* self=static_cast<CMusicObject*>(object(sizeof(CMusicObject)));manager=object(0x190);void* sound=object(0x20);CResourceManager* resource=static_cast<CResourceManager*>(object(0x50));field<void*>(manager,0x98)=c.index%3?sound:0;field<void*>(self,0x58)=reinterpret_cast<void*>(0x5a5a5a5aUL);detour::Set p;TL_REDIRECT(p,masterSingleton,&singleton);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}int before=g_iTotalCountOfObjects;
 if(c.op==0){autotest::invoke(out,ours?ctorCandidate:ctorOriginal,self,c.index%2?resource:NULL);pointer(self->m_pSoundManager);text(self->m_sMusicFile);text(self->m_sPlayingMusicFile);number(self->m_bFadeIn);number(self->m_bFadeOut);number(self->m_bLoops);floating(self->m_fRemainingPlayTime);number(self->m_bMusicPlaybackActive);floating(self->m_fPlaybackCheckTimer);pointer(self->m_pResourceManager);number(g_iTotalCountOfObjects-before);}
 else {ctorOriginal(self,NULL);const wchar_t* names[]={L"",L"a",L"ab",L"abc",L".abc",L"a.bc",L"C:\\music",L"/music",L"../music",L"тест музыки",L"aa:more",L"a:/music"};std::wstring name=names[c.index%12];self->m_sMusicFile=c.index%2?L"old source":L"";self->m_sPlayingMusicFile=c.index%3?L"old playback":L"";autotest::invoke(out,ours?fileCandidate:fileOriginal,self,name);text(self->m_sMusicFile);text(self->m_sPlayingMusicFile);text(name);}
 TSafePointer<CMusicObject> reference;reference.setObject(self);int constructed=g_iTotalCountOfObjects;dtorOriginal(self);number(reference.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);number(calls);if(reference.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;out.addHeapInUse();
}
}
TL_TEST(scene_music_construct){return smallmass::run(host,0,"scene_music_construct",(uintptr_t)ctorOriginal,execute,24);}
TL_TEST(scene_music_file){return smallmass::run(host,1,"scene_music_file",(uintptr_t)fileOriginal,execute,24);}
