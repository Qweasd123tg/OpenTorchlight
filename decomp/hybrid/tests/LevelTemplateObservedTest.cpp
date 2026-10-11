#include <cstring>
#include <fenv.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void*,original0,(void*),"_ZN18CLevelTemplateData15getRandomLayoutEv")
extern "C" void* candidate0(void*) __asm__("_ZN18CLevelTemplateData15getRandomLayoutEv");
TL_ORIGINAL(void,original1,(void*),"_ZN18CLevelTemplateData9resetOddsEv")
extern "C" void candidate1(void*) __asm__("_ZN18CLevelTemplateData9resetOddsEv");
TL_ORIGINAL(unsigned,original2,(void*,int,unsigned),"_ZN18CLevelTemplateData24getNumberOfUnitsToCreateE21ELEVELLAYOUT_CREATIONj")
extern "C" unsigned candidate2(void*,int,unsigned) __asm__("_ZN18CLevelTemplateData24getNumberOfUnitsToCreateE21ELEVELLAYOUT_CREATIONj");
TL_FUNCTION(target_random,"_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(target_odds,"_ZN11CRandomizer13setChoiceOddsEii")
TL_FUNCTION(target_between,"_ZN9UTILITIES13randomBetweenEff")
TL_FUNCTION(target_integer,"_ZN9UTILITIES20randomIntegerBetweenEii")

namespace {
struct List{void*data;unsigned count,capacity,grow,pad;};struct Case{unsigned op,seed,mode;};Case*input;autotest::Capture*output;void*active;void*randoms[3];unsigned calls;
void num(unsigned n){output->add(&n,4);}void ptr(void*p){output->add(&p,8);}void fl(float f){output->add(&f,4);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void word(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}
int random(void*p){num(1);ptr(p);++calls;if(input->mode==3)reinterpret_cast<List*>(static_cast<char*>(active)+0xb8)->capacity=1;return input->seed%8==7?-1:input->seed%8;}
void odds(void*p,int choice,int value){num(2);ptr(p);num(choice);num(value);++calls;if(input->mode==3)word(randoms[0],0x30,0);if(input->mode==4)reinterpret_cast<List*>(static_cast<char*>(active)+0xf0)->count=1;if(input->mode==5){void**v=static_cast<void**>(reinterpret_cast<List*>(static_cast<char*>(active)+0xf0)->data);v[0]=randoms[calls%3];}if(input->mode==6)reinterpret_cast<List*>(static_cast<char*>(active)+0x28)->capacity=1;}
float between(float low,float high){num(3);fl(low);fl(high);++calls;return input->mode==0?low:input->mode==1?high:input->mode==2?-1.25f:input->mode==3?0.25f:(low+high)*0.5f;}
int integer(int low,int high){num(4);num(low);num(high);++calls;return static_cast<int>(input->seed*1234567u);}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;unsigned long long self[0x778/8],randomData[3][0x68/8],chunk[8][0x20/8];std::memset(self,(c.seed*31+7)&255,sizeof(self));std::memset(randomData,0,sizeof(randomData));std::memset(chunk,0,sizeof(chunk));active=self;void*layouts[8],*chunks[8],*rands[3];int choices[3][8];float oddsValues[3][8]={{0}};
 for(unsigned i=0;i<8;++i){layouts[i]=reinterpret_cast<void*>(0x123400u+i*32);chunks[i]=chunk[i];word(chunks[i],0x14,c.seed*1234567u+i);}
 for(unsigned i=0;i<3;++i){rands[i]=randoms[i]=randomData[i];for(unsigned j=0;j<8;++j)choices[i][j]=(c.seed+i+j)%9==8?-1:(c.seed+i+j)%8;List choiceList={choices[i],8,c.mode==7?1:8,2,0};std::memcpy(static_cast<char*>(randoms[i])+0x10,&choiceList,sizeof(choiceList));List oddsList={oddsValues[i],(c.seed/8+i)%9,8,2,0};if(c.mode==2)oddsList.count=0x80000000u;std::memcpy(static_cast<char*>(randoms[i])+0x28,&oddsList,sizeof(oddsList));}
 List layoutList={layouts,8,c.mode==7?1:8,2,0},chunkList={chunks,8,c.mode==7?1:8,2,0},randomList={rands,(c.seed/8)%4,c.mode==7?1:3,2,0};std::memcpy(reinterpret_cast<char*>(self)+0xb8,&layoutList,sizeof(layoutList));std::memcpy(reinterpret_cast<char*>(self)+0x28,&chunkList,sizeof(chunkList));std::memcpy(reinterpret_cast<char*>(self)+0xf0,&randomList,sizeof(randomList));put(self,0xe8,c.mode==0?NULL:randoms[0]);
 const unsigned bits[]={0,0x80000000u,0xbf800000u,0x3e800000u,0x3f800000u,0x41200000u,0x4f000000u,0x7f800000u,0xff800000u,0x7fc01234u};unsigned section=c.seed%11;unsigned countLow=bits[(c.seed/11)%10],countHigh=bits[(c.seed/110)%10],densityLow=bits[(c.seed/17)%10],densityHigh=bits[(c.seed/37)%10];
 if(c.seed>=1100){countLow=0;countHigh=0;densityLow=bits[((c.seed-1100)/11)%10];densityHigh=bits[((c.seed-1100)/110)%10];}
 std::memcpy(reinterpret_cast<char*>(self)+0x634+section*8,&countLow,4);std::memcpy(reinterpret_cast<char*>(self)+0x638+section*8,&countHigh,4);std::memcpy(reinterpret_cast<char*>(self)+0x5dc+section*8,&densityLow,4);std::memcpy(reinterpret_cast<char*>(self)+0x5e0+section*8,&densityHigh,4);
 const unsigned areas[]={0,1,13,1000,0x7fffffffu,0x80000000u,0xffffffffu,42};detour::Set patches;TL_REDIRECT(patches,target_random,&random);TL_REDIRECT(patches,target_odds,&odds);TL_REDIRECT(patches,target_between,&between);TL_REDIRECT(patches,target_integer,&integer);if(patches.failed())_exit(41);feclearexcept(FE_ALL_EXCEPT);
 if(c.op==0){void*(*fn)(void*)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;void*result=fn(active);out.callCompleted=1;ptr(result);}else if(c.op==1)autotest::invoke(out,ours?candidate1:original1,active);else autotest::invoke(out,ours?candidate2:original2,active,static_cast<int>(section),areas[c.mode]);
 num(fetestexcept(FE_ALL_EXCEPT));num(calls);out.add(self,sizeof(self));out.add(randomData,sizeof(randomData));out.add(chunk,sizeof(chunk));out.add(rands,sizeof(rands));out.add(choices,sizeof(choices));out.add(oddsValues,sizeof(oddsValues));patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2};autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<(op==2?2200u:640u);++n){Case c={op,n,n%8};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    level next %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_template_random_layout){return run(host,0,"level_template_random_layout");}
TL_TEST(level_template_reset_odds){return run(host,1,"level_template_reset_odds");}
TL_TEST(level_template_unit_count){return run(host,2,"level_template_unit_count");}
