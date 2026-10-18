#include "SmallMassCompare.h"
#include <algorithm>
#include <limits>
#include <deque>
#include <vector>
#include <OgreAnimationState.h>
#define private public
#define protected public
#include "GenericModel.h"
#undef protected
#undef private
#include "AnimationSet.h"
#include "Utilities.h"
TL_ORIGINAL(bool,model_queued_old,(CGenericModel*,unsigned),"_ZNK13CGenericModel15animationQueuedEj")
extern "C" bool model_queued_new(CGenericModel*,unsigned) __asm__("_ZNK13CGenericModel15animationQueuedEj");
TL_ORIGINAL(bool,model_playing_old,(CGenericModel*,unsigned),"_ZNK13CGenericModel16animationPlayingEj")
extern "C" bool model_playing_new(CGenericModel*,unsigned) __asm__("_ZNK13CGenericModel16animationPlayingEj");
TL_ORIGINAL(bool,model_any_old,(CGenericModel*),"_ZNK13CGenericModel16animationPlayingEv")
extern "C" bool model_any_new(CGenericModel*) __asm__("_ZNK13CGenericModel16animationPlayingEv");
TL_ORIGINAL(bool,model_loop_old,(CGenericModel*),"_ZN13CGenericModel23loopingAnimationPlayingEv")
extern "C" bool model_loop_new(CGenericModel*) __asm__("_ZN13CGenericModel23loopingAnimationPlayingEv");
TL_ORIGINAL(int,model_current_old,(CGenericModel*),"_ZNK13CGenericModel16currentAnimationEv")
extern "C" int model_current_new(CGenericModel*) __asm__("_ZNK13CGenericModel16currentAnimationEv");
TL_ORIGINAL(float,model_time_old,(CGenericModel*),"_ZN13CGenericModel16getAnimationTimeEv")
extern "C" float model_time_new(CGenericModel*) __asm__("_ZN13CGenericModel16getAnimationTimeEv");
TL_ORIGINAL(void,model_settime_old,(CGenericModel*,float),"_ZN13CGenericModel16setAnimationTimeEf")
extern "C" void model_settime_new(CGenericModel*,float) __asm__("_ZN13CGenericModel16setAnimationTimeEf");
TL_ORIGINAL(void,model_speed_old,(CGenericModel*,const std::string&,float),"_ZN13CGenericModel17setAnimationSpeedERKSsf")
extern "C" void model_speed_new(CGenericModel*,const std::string&,float) __asm__("_ZN13CGenericModel17setAnimationSpeedERKSsf");
TL_ORIGINAL(bool,model_queuedsub_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel24animationQueuedSubstringERKSs")
extern "C" bool model_queuedsub_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel24animationQueuedSubstringERKSs");
TL_ORIGINAL(bool,model_playingsub_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel25animationPlayingSubstringERKSs")
extern "C" bool model_playingsub_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel25animationPlayingSubstringERKSs");
TL_ORIGINAL(bool,model_exists_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel15animationExistsERKSs")
extern "C" bool model_exists_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel15animationExistsERKSs");
TL_ORIGINAL(bool,model_existssub_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel24animationExistsSubstringERKSs")
extern "C" bool model_existssub_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel24animationExistsSubstringERKSs");
TL_ORIGINAL(unsigned,model_index_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel17getAnimationIndexERKSs")
extern "C" unsigned model_index_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel17getAnimationIndexERKSs");
TL_ORIGINAL(const std::string&,model_path_old,(CGenericModel*,const std::wstring&),"_ZNK13CGenericModel22getAnimationNameByPathERKSbIwSt11char_traitsIwESaIwEE")
extern "C" const std::string& model_path_new(CGenericModel*,const std::wstring&) __asm__("_ZNK13CGenericModel22getAnimationNameByPathERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(float,model_seconds_old,(CGenericModel*,int),"_ZNK13CGenericModel25getAnimationLengthSecondsEi")
extern "C" float model_seconds_new(CGenericModel*,int) __asm__("_ZNK13CGenericModel25getAnimationLengthSecondsEi");
TL_ORIGINAL(float,model_secondsname_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel25getAnimationLengthSecondsERKSs")
extern "C" float model_secondsname_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel25getAnimationLengthSecondsERKSs");
TL_ORIGINAL(long,model_length_old,(CGenericModel*,const std::string&),"_ZNK13CGenericModel18getAnimationLengthERKSs")
extern "C" long model_length_new(CGenericModel*,const std::string&) __asm__("_ZNK13CGenericModel18getAnimationLengthERKSs");
TL_ORIGINAL(int,model_random_old,(CGenericModel*,const std::string&),"_ZN13CGenericModel19findRandomAnimationERKSs")
extern "C" int model_random_new(CGenericModel*,const std::string&) __asm__("_ZN13CGenericModel19findRandomAnimationERKSs");
TL_ORIGINAL(void,model_clearqueued_old,(CGenericModel*),"_ZN13CGenericModel21clearQueuedAnimationsEv")
extern "C" void model_clearqueued_new(CGenericModel*) __asm__("_ZN13CGenericModel21clearQueuedAnimationsEv");
TL_ORIGINAL(void,model_clear_old,(CGenericModel*),"_ZN13CGenericModel15clearAnimationsEv")
extern "C" void model_clear_new(CGenericModel*) __asm__("_ZN13CGenericModel15clearAnimationsEv");
TL_ORIGINAL(void,model_queue_old,(CGenericModel*,unsigned,bool,float,float),"_ZN13CGenericModel19queueBlendAnimationEjbff")
extern "C" void model_queue_new(CGenericModel*,unsigned,bool,float,float) __asm__("_ZN13CGenericModel19queueBlendAnimationEjbff");
TL_ORIGINAL(void,model_play_old,(CGenericModel*,unsigned,bool,float,float),"_ZN13CGenericModel13playAnimationEjbff")
extern "C" void model_play_new(CGenericModel*,unsigned,bool,float,float) __asm__("_ZN13CGenericModel13playAnimationEjbff");
TL_ORIGINAL(void,model_blend_old,(CGenericModel*,unsigned,bool,float,float,float),"_ZN13CGenericModel14blendAnimationEjbfff")
extern "C" void model_blend_new(CGenericModel*,unsigned,bool,float,float,float) __asm__("_ZN13CGenericModel14blendAnimationEjbfff");
TL_ORIGINAL(void,model_playname_old,(CGenericModel*,const std::string&,bool,float,float),"_ZN13CGenericModel13playAnimationERKSsbff")
extern "C" void model_playname_new(CGenericModel*,const std::string&,bool,float,float) __asm__("_ZN13CGenericModel13playAnimationERKSsbff");
TL_ORIGINAL(void,model_blendname_old,(CGenericModel*,const std::string&,bool,float,float,float),"_ZN13CGenericModel14blendAnimationERKSsbfff")
extern "C" void model_blendname_new(CGenericModel*,const std::string&,bool,float,float,float) __asm__("_ZN13CGenericModel14blendAnimationERKSsbfff");
TL_ORIGINAL(void,model_addvalue_old,(CGenericModel*,int,CKeyframe*,int),"_ZN13CGenericModel13addValueIndexEiP9CKeyframei")
extern "C" void model_addvalue_new(CGenericModel*,int,CKeyframe*,int) __asm__("_ZN13CGenericModel13addValueIndexEiP9CKeyframei");
TL_ORIGINAL(void,model_ctor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,model_dtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_FUNCTION(model_random,"_ZN9UTILITIES21randomBetweenVolatileEff")
namespace finish_model {
static const uint64_t addresses[]={0x8a53f0,0x8a76c0,0x8a5550,0x8a7300,0x8a7880,0x8a7f40,0x8a5230,0x8a74a0,0x8a61f0,0x8a6560,0x8a25c0,0x8a4310,0x8a4130,0x8a22c0,0x89ab60,0x8a2750,0x8a28e0,0x8a2de0,0x8a68e0,0x8a5690,0x8a1320,0x8a5a40,0x8a6d70,0x8a5cf0,0x8a71d0,0x89abc0};
using namespace smallmass;
unsigned randomCalls;
unsigned negative;
bool badQueued(CGenericModel*,unsigned){return false;}
void badClear(CGenericModel* self){self->m_activeAnimations.clear();}
float random(float lo,float hi){number(700);floating(lo);floating(hi);static const float v[]={0,499.99f,500,1000,-1,250};return v[(input->index+randomCalls++)%6];}

static const char* names[]={"","IDLE","idle","RUN","RUN_FAST","run_slow","MISSING","IDLE_IDLE","名"};
static const float values[]={0,-0.0f,-1,1,0.25f,10,100,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
void side(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;randomCalls=0;
 Ogre::AnimationStateSet stateSet;
 CGenericModel* self=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));
 model_ctor(self,0,0,OGRE_UTILITIES::PRIMITIVE_SPHERE);
 CAnimationSet* animations=new CAnimationSet;
 const unsigned nn=c.index%6;
 for(unsigned i=0;i<6;++i){animations->m_lUnknown28.push_back(names[(i+c.index/6)%9]);if(i<nn)animations->m_lUnknown40.push_back(i%2?L"Media/Run":L"media/idle");}
 animations->m_nUnknown=nn;
 self->m_animationSet=c.index%7==0?0:animations;
 if(c.op==16)self->m_animationSet=animations;
 Ogre::AnimationState* states[6];for(unsigned i=0;i<6;++i){std::string name="state";name+=char('0'+i);states[i]=stateSet.createAnimationState(name,0,values[(i+c.index/3)%10],1,false);self->m_animationStates.add(states[i]);}
 if(c.op==14&&c.index&16)animations->m_nUnknown=16;
 if(c.op==13)animations->m_lUnknown28.resize(c.index%6);
 if(c.op>=19&&c.op<=24&&c.index%13==0)self->m_animationStates.clear();
 unsigned count=c.index%6==0?0:c.index%6==1?1:c.index%6==2?3:c.index%6==3?8:c.index%6==4?70:137;
 TSafePointer<CActiveAnimation> watchers[140];
 for(unsigned i=0;i<count;++i){CActiveAnimation* a=new CActiveAnimation;a->m_animation=(i+c.index/5)%6;a->m_length=values[(i+c.index/7)%10];a->m_duration=float(i)+0.5f;a->m_time=float(i)-2;a->m_loop=(i+c.index/11)&1;a->m_playing=(i+c.index/3)&1;a->m_queued=(i+c.index/2)%3==1;a->m_flag27=a->m_flag28=a->m_flag29=a->m_flag2a=false;a->m_blendRemaining=2;a->m_blendDuration=3;a->m_weight=0.7f;a->m_speed=1;self->m_activeAnimations.push_back(a);watchers[i].setObject(a);}
 const std::string name=names[c.index/6%9];const std::wstring path=c.index&1?L"MEDIA/RUN":L"Media/Idle";
 unsigned id=c.index%8<6?c.index%8:c.index%8==6?10:unsigned(-1);float v=values[c.index/9%10];

 int constructorCount=g_iTotalCountOfObjects;
 switch(c.op){

case 0: autotest::beginInvocation(out,ours&&negative==1?badQueued:(ours?model_queued_new:model_queued_old)); number((ours&&negative==1?badQueued:(ours?model_queued_new:model_queued_old))(self,id)); break;
case 1: autotest::beginInvocation(out,ours?model_playing_new:model_playing_old); number((ours?model_playing_new:model_playing_old)(self,id)); break;
case 2: autotest::beginInvocation(out,ours?model_any_new:model_any_old); number((ours?model_any_new:model_any_old)(self)); break;
case 3: autotest::beginInvocation(out,ours?model_loop_new:model_loop_old); number((ours?model_loop_new:model_loop_old)(self)); break;
case 4: autotest::beginInvocation(out,ours?model_current_new:model_current_old); number((ours?model_current_new:model_current_old)(self)); break;
case 5: autotest::beginInvocation(out,ours?model_time_new:model_time_old); floating((ours?model_time_new:model_time_old)(self)); break;
case 6: autotest::beginInvocation(out,ours?model_settime_new:model_settime_old); (ours?model_settime_new:model_settime_old)(self,v); break;
case 7: autotest::beginInvocation(out,ours?model_speed_new:model_speed_old); (ours?model_speed_new:model_speed_old)(self,name,v); break;
case 8: autotest::beginInvocation(out,ours?model_queuedsub_new:model_queuedsub_old); number((ours?model_queuedsub_new:model_queuedsub_old)(self,name)); break;
case 9: autotest::beginInvocation(out,ours?model_playingsub_new:model_playingsub_old); number((ours?model_playingsub_new:model_playingsub_old)(self,name)); break;
case 10: autotest::beginInvocation(out,ours?model_exists_new:model_exists_old); number((ours?model_exists_new:model_exists_old)(self,name)); break;
case 11: autotest::beginInvocation(out,ours?model_existssub_new:model_existssub_old); number((ours?model_existssub_new:model_existssub_old)(self,name)); break;
case 12: autotest::beginInvocation(out,ours?model_index_new:model_index_old); number((ours?model_index_new:model_index_old)(self,name)); break;
case 13: autotest::beginInvocation(out,ours?model_path_new:model_path_old); text((ours?model_path_new:model_path_old)(self,path)); break;
case 14: autotest::beginInvocation(out,ours?model_seconds_new:model_seconds_old); floating((ours?model_seconds_new:model_seconds_old)(self,(c.index%11<2?int(c.index%11)-2:c.index%11<6?int(c.index%11)-2:int(c.index%11)+4))); break;
case 15: autotest::beginInvocation(out,ours?model_secondsname_new:model_secondsname_old); floating((ours?model_secondsname_new:model_secondsname_old)(self,name)); break;
case 16: autotest::beginInvocation(out,ours?model_length_new:model_length_old); {long result=(ours?model_length_new:model_length_old)(self,name);out.add(&result,sizeof(result));} break;
case 17: autotest::beginInvocation(out,ours?model_random_new:model_random_old); number((ours?model_random_new:model_random_old)(self,name)); break;
case 18: autotest::beginInvocation(out,ours&&negative==2?badClear:(ours?model_clearqueued_new:model_clearqueued_old)); (ours&&negative==2?badClear:(ours?model_clearqueued_new:model_clearqueued_old))(self); break;
case 19: autotest::beginInvocation(out,ours?model_clear_new:model_clear_old); (ours?model_clear_new:model_clear_old)(self); break;
case 20: autotest::beginInvocation(out,ours?model_queue_new:model_queue_old); (ours?model_queue_new:model_queue_old)(self,id,bool(c.index&1),v,1.75f); break;
case 21: autotest::beginInvocation(out,ours?model_play_new:model_play_old); (ours?model_play_new:model_play_old)(self,id,bool(c.index&1),v,-1.0f); break;
case 22: autotest::beginInvocation(out,ours?model_blend_new:model_blend_old); (ours?model_blend_new:model_blend_old)(self,id,bool(c.index&1),v,1.75f,values[c.index/11%10]); break;
case 23: autotest::beginInvocation(out,ours?model_playname_new:model_playname_old); (ours?model_playname_new:model_playname_old)(self,name,bool(c.index&1),v,-1.0f); break;
case 24: autotest::beginInvocation(out,ours?model_blendname_new:model_blendname_old); (ours?model_blendname_new:model_blendname_old)(self,name,bool(c.index&1),v,1.75f,-1.0f); break;
case 25: autotest::beginInvocation(out,ours?model_addvalue_new:model_addvalue_old);animations->m_lAnimationGroups.resize(1);animations->m_lAnimationGroups[0].push_back(0);self->m_animationSet=animations;self->m_valueIndexes.resize(1);self->m_valueIndexes[0].resize(1);for(unsigned j=0;j<c.index%8;++j)self->m_valueIndexes[0][0].add(j); (ours?model_addvalue_new:model_addvalue_old)(self,0,0,int(c.index)); break;

 }
 out.callCompleted=1;
 number(g_iTotalCountOfObjects-constructorCount);number(stateSet.getDirtyFrameNumber());number(stateSet.hasEnabledAnimationState());
 number(self->m_activeAnimations.size());
 for(unsigned i=0;i<self->m_activeAnimations.size();++i){CActiveAnimation* a=self->m_activeAnimations[i];number(a->m_animation);floating(a->m_length);floating(a->m_duration);floating(a->m_time);number(a->m_loop);number(a->m_playing);number(a->m_queued);number(a->m_flag27);number(a->m_flag28);number(a->m_flag29);number(a->m_flag2a);floating(a->m_blendRemaining);floating(a->m_blendDuration);floating(a->m_weight);floating(a->m_speed);}
 for(unsigned i=0;i<6;++i){Ogre::AnimationState* a=states[i];number(a->getLoop());number(a->getEnabled());floating(a->getWeight());floating(a->getTimePosition());}
 for(unsigned i=0;i<count;++i)number(watchers[i].getObject()!=0);
 if(c.op==25){TArrayList<int>& a=self->m_valueIndexes[0][0];number(a.size());for(unsigned i=0;i<a.size();++i)number(a[i]);}
 number(randomCalls);self->m_animationSet=0;model_dtor(self);delete animations;
 for(unsigned i=0;i<count;++i)number(watchers[i].getObject()==0);
}

}
TL_TEST(finish_model_queued){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,0,"finish_model_queued",0x8a53f0,&finish_model::side,192);}
TL_TEST(finish_model_playing){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,1,"finish_model_playing",0x8a76c0,&finish_model::side,192);}
TL_TEST(finish_model_any){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,2,"finish_model_any",0x8a5550,&finish_model::side,192);}
TL_TEST(finish_model_loop){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,3,"finish_model_loop",0x8a7300,&finish_model::side,192);}
TL_TEST(finish_model_current){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,4,"finish_model_current",0x8a7880,&finish_model::side,192);}
TL_TEST(finish_model_time){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,5,"finish_model_time",0x8a7f40,&finish_model::side,192);}
TL_TEST(finish_model_settime){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,6,"finish_model_settime",0x8a5230,&finish_model::side,192);}
TL_TEST(finish_model_speed){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,7,"finish_model_speed",0x8a74a0,&finish_model::side,192);}
TL_TEST(finish_model_queuedsub){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,8,"finish_model_queuedsub",0x8a61f0,&finish_model::side,192);}
TL_TEST(finish_model_playingsub){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,9,"finish_model_playingsub",0x8a6560,&finish_model::side,192);}
TL_TEST(finish_model_exists){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,10,"finish_model_exists",0x8a25c0,&finish_model::side,192);}
TL_TEST(finish_model_existssub){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,11,"finish_model_existssub",0x8a4310,&finish_model::side,192);}
TL_TEST(finish_model_index){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,12,"finish_model_index",0x8a4130,&finish_model::side,192);}
TL_TEST(finish_model_path){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,13,"finish_model_path",0x8a22c0,&finish_model::side,192);}
TL_TEST(finish_model_seconds){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,14,"finish_model_seconds",0x89ab60,&finish_model::side,192);}
TL_TEST(finish_model_secondsname){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,15,"finish_model_secondsname",0x8a2750,&finish_model::side,192);}
TL_TEST(finish_model_length){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,16,"finish_model_length",0x8a28e0,&finish_model::side,192);}
TL_TEST(finish_model_random){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,17,"finish_model_random",0x8a2de0,&finish_model::side,192);}
TL_TEST(finish_model_clearqueued){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,18,"finish_model_clearqueued",0x8a68e0,&finish_model::side,192);}
TL_TEST(finish_model_clear){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,19,"finish_model_clear",0x8a5690,&finish_model::side,192);}
TL_TEST(finish_model_queue){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,20,"finish_model_queue",0x8a1320,&finish_model::side,192);}
TL_TEST(finish_model_play){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,21,"finish_model_play",0x8a5a40,&finish_model::side,192);}
TL_TEST(finish_model_blend){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,22,"finish_model_blend",0x8a6d70,&finish_model::side,192);}
TL_TEST(finish_model_playname){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,23,"finish_model_playname",0x8a5cf0,&finish_model::side,192);}
TL_TEST(finish_model_blendname){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,24,"finish_model_blendname",0x8a71d0,&finish_model::side,192);}
TL_TEST(finish_model_addvalue){detour::Set patch;TL_REDIRECT(patch,model_random,&finish_model::random);if(patch.failed())return 1;return smallmass::run(host,25,"finish_model_addvalue",0x89abc0,&finish_model::side,192);}

namespace finish_model {
void negativeOld(void* p,autotest::Capture& out){finish_model::side(*static_cast<Case*>(p),false,out);}
void negativeNew(void* p,autotest::Capture& out){finish_model::side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(finish_model_body_negative_controls){
 for(unsigned mode=1;mode<=2;++mode){smallmass::Case c={mode==1?0u:18u,mode==1?3u:2u};finish_model::negative=0;autotest::runChild(&finish_model::negativeOld,&c,autotest::g_outcomes[0]);finish_model::negative=mode;autotest::runChild(&finish_model::negativeNew,&c,autotest::g_outcomes[1]);finish_model::negative=0;const autotest::Outcome& a=autotest::g_outcomes[0];const autotest::Outcome& b=autotest::g_outcomes[1];if(!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||a.capture.issue||b.capture.issue||!a.capture.callCompleted||!b.capture.callCompleted)return 1;if(a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length))return 1;}
 host->log("    2 normal completed body counterfactuals rejected: always-false queued result and clearing queued pointers without destruction; not acceptance coverage\n");return 0;
}
