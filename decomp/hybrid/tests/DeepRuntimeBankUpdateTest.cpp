#include "tests/SmallMassCompare.h"
#include "SoundBank.h"
TL_ORIGINAL(void,deepBankUpdateOld,(void*,float,void*),"_ZN10CSoundBank6updateEfPN4Ogre9SceneNodeE")
extern "C" void deepBankUpdateNew(void*,float,void*) __asm__("_ZN10CSoundBank6updateEfPN4Ogre9SceneNodeE");
TL_FUNCTION(deepBankIncrement,"_ZN13CSoundManager18incrementSoundBankEv")
TL_FUNCTION(deepBankPlaying,"_ZN13CSoundManager16isChannelPlayingEi")
TL_FUNCTION(deepBankStopChannel,"_ZN13CSoundManager9stopSoundEi")
TL_FUNCTION(deepBankStopAll,"_ZN10CSoundBank4stopEv")
TL_FUNCTION(deepBankScale,"_ZN10CSoundBank20configureVolumeScaleEfRKN4Ogre7Vector3E")
TL_FUNCTION(deepBankPlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(deepBankVolume,"_ZN13CSoundManager14setSoundVolumeEif")
namespace {using namespace smallmass;Ogre::Vector3 position;
void increment(void* p){event(1,p);}
bool playing(void* p,int ch){event(2,p);number(ch);return (unsigned(ch)+input->index)%3;}
void stopChannel(void* p,int ch){event(3,p);number(ch);}
void stopAll(void* p){event(4,p);field<TArrayList<int> >(p,0x18).clear();field<TArrayList<int> >(p,0x30).clear();}
float scale(void* p,float r,const Ogre::Vector3& v){event(5,p);floating(r);vector(v);float values[]={-1,0,.0001f,.5f,2};return values[(input->index/16)%5];}
int play(void* p,int id,void* node,float vol,float radius,bool flag){event(6,p);number(id);pointer(node);floating(vol);floating(radius);number(flag);if(input->index&8){field<TArrayList<int> >(p,0x18).add(77);field<TArrayList<int> >(p,0x30).add(0);}return 77;}
void volume(void* p,int id,float value){event(7,p);number(id);floating(value);}
const Ogre::Vector3& getPosition(void* p){event(8,p);return position;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;void* self=object(sizeof(CSoundBank));void* manager=object(0x720);field<void*>(self,0x10)=manager;TArrayList<int>& channels=*new(static_cast<char*>(self)+0x18)TArrayList<int>(2);TArrayList<int>& ids=*new(static_cast<char*>(self)+0x30)TArrayList<int>(2);for(unsigned i=0;i<c.index%5;++i){channels.add(i%3?i*7:-1);ids.add(100+i);}field<bool>(self,0xc8)=c.index&1;field<bool>(self,0xa8)=c.index&2;field<float>(self,0xac)=.5f;field<float>(self,0xb0)=12.5f;position=Ogre::Vector3(0,1,0);Ogre::Vector3 listener=c.index&4?Ogre::Vector3(3,-2,4):position;field<float>(manager,0x20)=listener.x;field<float>(manager,0x24)=listener.y;field<float>(manager,0x28)=listener.z;field<Ogre::Vector3>(self,0xb8)=c.index&8?listener:Ogre::Vector3(0,0,0);void** vtable=static_cast<void**>(object(0x220));vtable[0x200/8]=reinterpret_cast<void*>(&getPosition);void* node=object(8);field<void**>(node,0)=vtable;
detour::Set d;TL_REDIRECT(d,deepBankIncrement,&increment);TL_REDIRECT(d,deepBankPlaying,&playing);TL_REDIRECT(d,deepBankStopChannel,&stopChannel);TL_REDIRECT(d,deepBankStopAll,&stopAll);TL_REDIRECT(d,deepBankScale,&scale);TL_REDIRECT(d,deepBankPlay,&play);TL_REDIRECT(d,deepBankVolume,&volume);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}autotest::invoke(out,ours?deepBankUpdateNew:deepBankUpdateOld,self,.125f,c.index&128?static_cast<void*>(0):node);number(channels.size());for(unsigned i=0;i<channels.size();++i)number(channels[i]);number(ids.size());for(unsigned i=0;i<ids.size();++i)number(ids[i]);number(field<bool>(self,0xa8));vector(field<Ogre::Vector3>(self,0xb8));floating(field<float>(self,0xc4));channels.~TArrayList();ids.~TArrayList();}
}
TL_TEST(deep_runtime_bank_update){return smallmass::run(host,0,"deep_runtime_bank_update",(uintptr_t)deepBankUpdateOld,execute,256);}
