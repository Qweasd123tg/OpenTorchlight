#include "SmallMassCompare.h"
#include "MusicObject.h"
#include "SoundManager.h"

TL_ORIGINAL(void, musicOriginal,(void*),"_ZN12CMusicObject4playEv")
extern "C" void musicCandidate(void*) __asm__("_ZN12CMusicObject4playEv");
TL_FUNCTION(musicFile,"_ZN13CSoundManager19getMusicFilePlayingEv")
TL_FUNCTION(musicPlay,"_ZN13CSoundManager9playMusicERSbIwSt11char_traitsIwESaIwEEb")
namespace {
using namespace smallmass;
CMusicObject* music;
void* manager;
std::wstring* current;
unsigned calls;
std::wstring getFile(void* self){event(1,self);number(calls++);return *current;}
float play(void* self,std::wstring& name,bool loops) {
    event(2,self);text(name);number(loops);
    if(input->index&4)name+=L" normalized";
    *current=input->index&8?L"actual playing file":name;
    static const unsigned returns[]={0x3e000000,0x80000000,0x7fc01234,0x7f800000,0xbf400000};
    return bits(returns[(input->index/5)%5]);
}
void broadcast(void* self,unsigned id) {
    event(3,self);number(id);text(music->m_sMusicFile);text(music->m_sPlayingMusicFile);
    floating(music->m_fRemainingPlayTime);number(music->m_bMusicPlaybackActive);
}
void execute(Case& c,bool ours,autotest::Capture& out) {
    input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;
    music=static_cast<CMusicObject*>(object(sizeof(CMusicObject)));
    manager=object(sizeof(CSoundManager));
    void** table=static_cast<void**>(object(0x38));table[0x30/8]=reinterpret_cast<void*>(&broadcast);
    field<void*>(music,0)=table;
    new(&music->m_sMusicFile)std::wstring(L"requested music");
    new(&music->m_sPlayingMusicFile)std::wstring(c.index%5==1?L"playing":c.index%5==2?L"playin":c.index%5==3?L"playXng":L"");
    std::wstring playing=L"playing";current=&playing;
    music->m_pSoundManager=c.index%5?static_cast<CSoundManager*>(manager):NULL;
    music->m_bLoops=c.index&1;music->m_bFadeIn=c.index&2;music->m_bFadeOut=c.index&4;
    music->m_bMusicPlaybackActive=c.index&8;music->m_fRemainingPlayTime=3.75f;
    music->m_fPlaybackCheckTimer=-0.125f;
    detour::Set redirects;TL_REDIRECT(redirects,musicFile,&getFile);TL_REDIRECT(redirects,musicPlay,&play);
    if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    autotest::invoke(out,ours?musicCandidate:musicOriginal,static_cast<void*>(music));
    text(music->m_sMusicFile);text(music->m_sPlayingMusicFile);text(playing);
    out.add(static_cast<char*>(static_cast<void*>(music))+0x70,0x10);number(calls);
    music->m_sMusicFile.~basic_string();music->m_sPlayingMusicFile.~basic_string();
}
}
TL_TEST(advance_music_play){return smallmass::run(host,0,"advance_music_play",(uintptr_t)musicOriginal,execute,100);}
