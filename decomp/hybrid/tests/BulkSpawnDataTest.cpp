#include <stdint.h>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "SpawnClassData.h"
#undef private
TL_ORIGINAL(void,oMany,(CSpawnClassData*,TArrayList<CDataGroup*>&),"_ZN15CSpawnClassData18addUnitDataObjectsER10TArrayListIP10CDataGroupE")
extern "C" void nMany(CSpawnClassData*,TArrayList<CDataGroup*>&) __asm__("_ZN15CSpawnClassData18addUnitDataObjectsER10TArrayListIP10CDataGroupE");
TL_ORIGINAL(unsigned,oCalculate,(CSpawnClassData*,CCharacter*,int,int,int,int),"_ZN15CSpawnClassData16calculateChoicesEP10CCharacteriiii")
extern "C" unsigned nCalculate(CSpawnClassData*,CCharacter*,int,int,int,int) __asm__("_ZN15CSpawnClassData16calculateChoicesEP10CCharacteriiii");
TL_FUNCTION(fillTarget,"_ZN15CSpawnClassData14fillRandomizerEP10CCharacteriiii")
TL_FUNCTION(countTarget,"_ZN11CSpawnClass24calculateNumberOfChoicesEP10CCharacteriiii")
namespace{
struct Case{unsigned mode,seed;};autotest::Capture*capture;unsigned seed,fills;CCharacter*character;CDataGroup*groups[8];
void number(unsigned value){capture->add(&value,4);}
int identity(CDataGroup*p){if(!p)return -1;for(unsigned i=0;i<8;++i)if(groups[i]==p)return i;return -2;}
void fill(CSpawnClassData*self,CCharacter*who,int a,int b,int c,int d){++fills;number(1);number(who==character);capture->add(&a,4);capture->add(&b,4);capture->add(&c,4);capture->add(&d,4);if(!self->m_pRandomizer&&(seed&8))return;if(!self->m_pRandomizer){self->m_pRandomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType1Randomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType2Randomizer=new CRandomizer(RANDOMIZER_NORMAL);}for(unsigned i=0;i<(seed%5)+1;++i)self->m_pRandomizer->addChoice(i,1);for(unsigned i=0;i<(seed/3)%4;++i)self->m_pType1Randomizer->addChoice(i,1);for(unsigned i=0;i<(seed/5)%3;++i)self->m_pType2Randomizer->addChoice(i,1);self->m_lPrimaryRandomizerIDs.add(17+seed);}
int count(CSpawnClass*,CCharacter*who,int a,int b,int c,int d){number(2);number(who==character);capture->add(&a,4);capture->add(&b,4);capture->add(&c,4);capture->add(&d,4);return int(seed*12345)^int(0x80000000u);}
void side(void*raw,autotest::Capture&out,bool ours){Case&c=*static_cast<Case*>(raw);capture=&out;seed=c.seed;fills=0;uint64_t memory[(sizeof(CSpawnClassData)+7)/8],gs[8][(sizeof(CDataGroup)+7)/8],cs[(sizeof(CCharacter)+7)/8],sp[(sizeof(CSpawnClass)+7)/8];std::memset(memory,0,sizeof(memory));CSpawnClassData*self=reinterpret_cast<CSpawnClassData*>(memory);character=reinterpret_cast<CCharacter*>(cs);for(unsigned i=0;i<8;++i)groups[i]=reinterpret_cast<CDataGroup*>(gs[i]);new(&self->m_lUnitDataObjects)TArrayList<CDataGroup*>((seed%3)+1);new(&self->m_lPrimaryRandomizerIDs)TArrayList<int>(2);self->m_iMinimumLevel=int(seed)-50;self->m_iLevelOffset=3;self->m_iRarityOverride=7;self->m_iFlags=-4;self->m_pSpawnClass=seed%11==0?reinterpret_cast<CSpawnClass*>(sp):NULL;
 for(unsigned i=0;i<seed%5;++i)self->m_lUnitDataObjects.add(groups[i]);for(unsigned i=0;i<seed%4;++i)self->m_lPrimaryRandomizerIDs.add(100+i);
 if(c.mode==0){TArrayList<CDataGroup*> input((seed%3)+1);for(unsigned i=0;i<(seed/3)%8;++i)input.add((i+seed)%3?groups[i]:NULL);if((seed&16)&&input.size())input.m_nCapacity=(seed/8)%2;typedef void(*Fn)(CSpawnClassData*,TArrayList<CDataGroup*>&);Fn fn=ours?nMany:oMany;if(!autotest::beginInvocation(out,fn))return;fn(self,input);}
 else{if(seed&2){self->m_pRandomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType1Randomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType2Randomizer=new CRandomizer(RANDOMIZER_NORMAL);for(unsigned i=0;i<seed%5;++i)self->m_pRandomizer->addChoice(i,1);for(unsigned i=0;i<(seed/3)%4;++i)self->m_pType1Randomizer->addChoice(i,1);for(unsigned i=0;i<(seed/5)%3;++i)self->m_pType2Randomizer->addChoice(i,1);}int a=self->m_iMinimumLevel,b=self->m_iLevelOffset,d=self->m_iFlags,r=self->m_iRarityOverride;switch((seed/7)%5){case 1:++a;break;case 2:++b;break;case 3:++r;break;case 4:++d;break;}detour::Set patches;TL_REDIRECT(patches,fillTarget,&fill);TL_REDIRECT(patches,countTarget,&count);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef unsigned(*Fn)(CSpawnClassData*,CCharacter*,int,int,int,int);Fn fn=ours?nCalculate:oCalculate;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(self,character,a,b,r,d);number(result);number(fills);}
 out.callCompleted=1;out.add(&self->m_iMinimumLevel,4);out.add(&self->m_iLevelOffset,4);out.add(&self->m_iRarityOverride,4);out.add(&self->m_iFlags,4);number(self->m_lUnitDataObjects.size());number(self->m_lUnitDataObjects.m_nCapacity);number(self->m_lUnitDataObjects.m_nGrowBy);for(unsigned i=0;i<self->m_lUnitDataObjects.size();++i){int id=identity(self->m_lUnitDataObjects[i]);out.add(&id,4);}number(self->m_lPrimaryRandomizerIDs.size());for(unsigned i=0;i<self->m_lPrimaryRandomizerIDs.size();++i)out.add(&self->m_lPrimaryRandomizerIDs[i],4);CRandomizer*randomizers[]={self->m_pRandomizer,self->m_pType1Randomizer,self->m_pType2Randomizer};for(unsigned i=0;i<3;++i){number(randomizers[i]!=NULL);if(randomizers[i]){number(randomizers[i]->getChoiceCount());for(unsigned j=0;j<randomizers[i]->getChoiceCount();++j){int value=randomizers[i]->getChoice(j);out.add(&value,4);}delete randomizers[i];}}self->m_lUnitDataObjects.~TArrayList();self->m_lPrimaryRandomizerIDs.~TArrayList();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*n,uintptr_t a){autotest::Coverage coverage(n,a);for(unsigned seed=0;seed<144;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(candidate,&c,y);if(coverage.observe(h,x,y)){h->log("    spawn data mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(bulk_spawn_data_add_many){return run(host,0,"bulk_spawn_data_add_many",(uintptr_t)&oMany);}
TL_TEST(bulk_spawn_data_calculate){return run(host,1,"bulk_spawn_data_calculate",(uintptr_t)&oCalculate);}
