#include "tests/SmallMassCompare.h"
#include "ParticleCache.h"
TL_ORIGINAL(void,deepCacheOld,(CParticleCache*,Ogre::SceneNode*),"_ZN14CParticleCache10playSoundsEPN4Ogre9SceneNodeE")
extern "C" void deepCacheNew(CParticleCache*,Ogre::SceneNode*) __asm__("_ZN14CParticleCache10playSoundsEPN4Ogre9SceneNodeE");
TL_FUNCTION(deepCachePlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
using namespace smallmass;
unsigned calls;void* bank;void* otherBank;
int play(void* p,int sound,void* node,float volume,float pitch,bool force) {event(1,p);number(sound);pointer(node);floating(volume);floating(pitch);number(force);++calls;return int(calls)-2;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* storage=object(sizeof(CParticleCache));CParticleCache* cache=static_cast<CParticleCache*>(storage);bank=object(8);otherBank=object(8);void* node=object(8);new(&cache->mSoundSampleIDs)TArrayList<int>(1+c.index%4);new(&cache->mSoundSampleVolumes)TArrayList<float>(1+c.index%3);
for(unsigned i=0;i<c.index%8;++i){cache->mSoundSampleIDs.add(int(i*3)-7);cache->mSoundSampleVolumes.add(float(int(c.index%9)-4)*0.25f+float(i));}cache->m_pSoundBank=static_cast<CSoundBank*>(c.index&8?bank:0);
detour::Set d;TL_REDIRECT(d,deepCachePlay,&play);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}autotest::invoke(out,ours?deepCacheNew:deepCacheOld,cache,static_cast<Ogre::SceneNode*>(c.index&16?node:0));number(calls);number(cache->mSoundSampleIDs.size());number(cache->mSoundSampleVolumes.size());for(unsigned i=0;i<cache->mSoundSampleIDs.size();++i){number(cache->mSoundSampleIDs[i]);floating(cache->mSoundSampleVolumes[i]);}cache->mSoundSampleVolumes.~TArrayList();cache->mSoundSampleIDs.~TArrayList();}
}
TL_TEST(deep_runtime_cache_sounds){return smallmass::run(host,0,"deep_runtime_cache_sounds",(uintptr_t)deepCacheOld,execute,64);}
