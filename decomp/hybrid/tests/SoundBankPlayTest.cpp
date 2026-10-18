#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#include "SoundBank.h"
#include "SoundManager.h"
#undef private
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(int,bankPlayOld,(CSoundBank*,int,Ogre::SceneNode*,float,float,bool),"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
extern "C" int bankPlayNew(CSoundBank*,int,Ogre::SceneNode*,float,float,bool) __asm__("_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb");
TL_FUNCTION(bankPlayRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(bankPlayChannel,"_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif")
TL_FUNCTION(bankPlayStop,"_ZN13CSoundManager9stopSoundEi")
namespace {
struct Case {unsigned index;};
struct State {
    autotest::Capture* out;
    CSoundManager* manager;
    Ogre::SceneNode* node;
    CSoundInstance* samples[3];
    unsigned seed,randomCalls,playCalls,stopCalls;
    int result;
    Ogre::Vector3 position;
};
State* active;
void number(unsigned x){active->out->add(&x,sizeof(x));}
void floating(float x){active->out->add(&x,sizeof(x));}
void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
int playRandom(int lo,int hi){number(1);number(lo);number(hi);++active->randomCalls;if(hi<lo){invalid();return lo;}return lo+active->seed%static_cast<unsigned>(hi-lo+1);}
void stop(CSoundManager* manager,int id){if(manager!=active->manager)invalid();number(2);number(id);++active->stopCalls;}
int play(CSoundManager* manager,CSoundInstance* sound,Ogre::SceneNode* node,int id,float volume){
    if(manager!=active->manager)invalid();number(3);
    unsigned chosen=3;for(unsigned i=0;i<3;++i)if(sound==active->samples[i])chosen=i;
    if(chosen==3)invalid();number(chosen);number(node==active->node?1:node==0?0:99);number(id);floating(volume);++active->playCalls;return active->result;
}
const Ogre::Vector3& position(Ogre::SceneNode* node){if(node!=active->node)invalid();number(4);return active->position;}
void side(Case& c,bool ours,autotest::Capture& out){
    autotest::g_arenaUsed=0;State state;active=&state;state.out=&out;state.randomCalls=state.playCalls=state.stopCalls=0;
    state.manager=static_cast<CSoundManager*>(autotest::allocate(sizeof(CSoundManager)));
    state.manager->m_bUnknown6A9=true;state.manager->m_bUnknown6A8=true;
    state.manager->m_listenerX=3;state.manager->m_listenerY=2;state.manager->m_listenerZ=-4;
    for(unsigned i=0;i<3;++i)state.samples[i]=static_cast<CSoundInstance*>(autotest::allocate(16));
    void** vtable=static_cast<void**>(autotest::allocate(0x208));vtable[0x200/8]=reinterpret_cast<void*>(&position);
    state.node=static_cast<Ogre::SceneNode*>(autotest::allocate(16));*reinterpret_cast<void***>(state.node)=vtable;
    state.position=Ogre::Vector3(6,99,0);state.result=(c.index&4)?-1:77;
    state.seed=(c.index/16)%3==0?0:(c.index/16)%3==1?49:99;
    CSoundBank* bank=new(autotest::allocate(sizeof(CSoundBank)))CSoundBank(*state.manager,false);
    bank->m_samples.resize(2);bank->m_radii.resize(2,12.5f);bank->m_volumes.resize(2,0.375f);bank->m_probabilities.resize(2,-1);
    for(unsigned i=0;i<3;++i)bank->m_samples[0].push_back(state.samples[i]);
    bank->m_samples[1].push_back(state.samples[2]);
    bank->m_channels.add(11);bank->m_channels.add(-1);bank->m_sampleIDs.add(0);bank->m_sampleIDs.add(1);
    bank->m_loop=c.index&1;bank->m_dirty=false;bank->m_volumeScale=0.25f;bank->m_lastVolume=-17;
    const float volumes[]={0.0f,-0.0f,1.5f,-2.0f,std::numeric_limits<float>::quiet_NaN()};
    const float radii[]={0.0f,5.0f,-4.0f};
    int sample=0;bool forget=c.index&2;Ogre::SceneNode* node=(c.index&8)?state.node:0;
    float volume=volumes[(c.index/3)%5],radius=radii[(c.index/7)%3];
    unsigned gate=c.index%16;
    if(gate==0)state.manager->m_bUnknown6A9=false;
    if(gate==1)state.manager->m_bUnknown6A8=false;
    if(gate==2)sample=-1;
    if(gate==3)sample=2;
    if(gate==4)bank->m_samples[0].clear();
    if(gate>=5&&gate<=8){const int chance[]={0,50,100,101};bank->m_probabilities[0]=chance[gate-5];}
    if(gate==9)sample=1;
    typedef int(*Fn)(CSoundBank*,int,Ogre::SceneNode*,float,float,bool);
    Fn fn=ours?bankPlayNew:bankPlayOld;
    if(!autotest::beginInvocation(out,fn))return;
    int result=fn(bank,sample,node,volume,radius,forget);out.callCompleted=1;
    number(result);number(bank->m_dirty);floating(bank->m_lastVolume);
    number(bank->m_channels.size());for(unsigned i=0;i<bank->m_channels.size();++i)number(bank->m_channels[i]);
    number(bank->m_sampleIDs.size());for(unsigned i=0;i<bank->m_sampleIDs.size();++i)number(bank->m_sampleIDs[i]);
    number(state.randomCalls);number(state.playCalls);number(state.stopCalls);
    bank->m_loop=false;bank->m_samples.clear();bank->~CSoundBank();
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(soundbank_play_sample){
    detour::Set hooks;
    TL_REDIRECT(hooks,bankPlayRandom,&playRandom);TL_REDIRECT(hooks,bankPlayChannel,&play);TL_REDIRECT(hooks,bankPlayStop,&stop);
    if(hooks.failed())return 1;
    autotest::Coverage coverage("soundbank_play_sample",0xa698a0);
    for(unsigned i=0;i<512;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log(" soundbank play case%u exits%d/%d\n",i,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=512||coverage.different||coverage.missing;
}
