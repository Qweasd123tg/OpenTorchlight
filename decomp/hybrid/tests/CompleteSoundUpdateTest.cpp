#include <cstring>
#include <stdint.h>
#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
TL_ORIGINAL(void,soundUpdateCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,soundUpdateDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(void,soundUpdateOriginal,(CSoundManager*,Ogre::SceneNode*,const Ogre::Vector3&,float),"_ZN13CSoundManager6updateEPN4Ogre9SceneNodeERKNS0_7Vector3Ef")
extern "C" void soundUpdateCandidate(CSoundManager*,Ogre::SceneNode*,const Ogre::Vector3&,float) __asm__("_ZN13CSoundManager6updateEPN4Ogre9SceneNodeERKNS0_7Vector3Ef");
TL_FUNCTION(soundUpdatePlaying,"_ZN13CSoundManager16isChannelPlayingEi")
TL_FUNCTION(soundUpdateStop,"_ZN13CSoundManager9stopSoundEi")
TL_FUNCTION(soundUpdatePlay,"_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif")
extern "C" FMOD_RESULT soundSystemUpdate(FMOD::System*) __asm__("_ZN4FMOD6System6updateEv");
extern "C" void soundRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void soundRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
namespace {
struct Case{unsigned queue,channel,elapsed,enabled;};const Case* current;autotest::Capture* cap;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
bool playing(CSoundManager*,int c){word(1);word(c);return current->channel==2;}
void stop(CSoundManager*,int c){word(2);word(c);}
int play(CSoundManager*,CSoundInstance*s,Ogre::SceneNode*n,int channel,float volume){word(3);word(s->m_referenceCount);word(n==NULL);word(channel);real(volume);return current->elapsed==2?-1:37;}
FMOD_RESULT update(FMOD::System*){word(4);return FMOD_OK;}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;
 void*rootRaw=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;soundRootCtor(rootRaw,empty,empty,empty);
 Ogre::Root*root=static_cast<Ogre::Root*>(rootRaw);Ogre::SceneManager*scene=root->createSceneManager(Ogre::ST_GENERIC,"SoundUpdate");
 Ogre::SceneNode*node=scene->getRootSceneNode()->createChildSceneNode();node->setOrientation(Ogre::Quaternion(.5f,.5f,.5f,.5f));
 union Storage{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*s=reinterpret_cast<CSoundManager*>(storage.bytes);soundUpdateCtor(s,false);
 s->m_bUnknown6A8=c.enabled;s->m_iUnknown10=71;s->m_iUnknown18=reinterpret_cast<FMOD::System*>(0x7654);s->m_iUnknown6F0=c.channel==0?-1:19;s->m_queueTimer=.25f;s->m_lastQueuedBank=997;
 CSoundInstance* sounds[3]={0,0,0};
 for(unsigned i=0;i<c.queue;++i){sounds[i]=new CSoundInstance;sounds[i]->m_pSound=NULL;sounds[i]->m_referenceCount=10+i;s->m_soundList0.push_back(900+i);s->m_soundList1.push_back(sounds[i]);s->m_soundList2.push_back(3.25f+i);s->m_soundList3.push_back(.5f+i);}
 detour::Set d;TL_REDIRECT(d,soundUpdatePlaying,&playing);TL_REDIRECT(d,soundUpdateStop,&stop);TL_REDIRECT(d,soundUpdatePlay,&play);d.redirect(reinterpret_cast<char*>(&soundSystemUpdate),reinterpret_cast<char*>(&soundSystemUpdate),&update);if(d.failed())_exit(64);
 const float elapsed[]={0.0f,.24f,.25f,.5f};Ogre::Vector3 pos(1.25f,-2.5f,100.0f);
 if(ours)autotest::invoke(out,soundUpdateCandidate,s,node,pos,elapsed[c.elapsed]);else autotest::invoke(out,soundUpdateOriginal,s,node,pos,elapsed[c.elapsed]);
 word(s->m_iUnknown10);real(s->m_listenerX);real(s->m_listenerY);real(s->m_listenerZ);word(s->m_iUnknown6F0);real(s->m_queueTimer);word(s->m_lastQueuedBank);word(s->m_soundList0.size());
 for(unsigned i=0;i<s->m_soundList0.size();++i){word(s->m_soundList0[i]);word(s->m_soundList1[i]==sounds[i]);word(s->m_soundList1[i]==sounds[i+1]);real(s->m_soundList2[i]);real(s->m_soundList3[i]);}
 for(unsigned i=0;i<c.queue;++i)word(sounds[i]->m_referenceCount);
 d.restore();s->m_iUnknown18=NULL;s->m_iUnknown6F0=-1;s->m_soundList0.clear();s->m_soundList1.clear();s->m_soundList2.clear();s->m_soundList3.clear();soundUpdateDtor(s);
 for(unsigned i=0;i<c.queue;++i)delete sounds[i];root->destroySceneManager(scene);soundRootDtor(rootRaw);Ogre::NedAllocImpl::deallocBytes(rootRaw);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sound_update){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_update",reinterpret_cast<uintptr_t>(&soundUpdateOriginal));
 for(unsigned q=0;q<4;++q)for(unsigned c=0;c<3;++c)for(unsigned e=0;e<4;++e)for(unsigned enabled=0;enabled<2;++enabled){Case x={q,c,e,enabled};bool ok=autotest::compareCase(original,candidate,&x,stats,host,"complete_sound_update",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
