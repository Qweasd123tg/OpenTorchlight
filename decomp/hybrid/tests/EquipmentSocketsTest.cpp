#include <cstring>
#include <climits>
#include <limits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "GameGlobals.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(int,originalMaxSockets,(CEquipment*),"_ZN10CEquipment13getMaxSocketsEv")
TL_ORIGINAL(void,originalAddSockets,(CEquipment*),"_ZN10CEquipment10addSocketsEv")
TL_FUNCTION(soIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(soRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(soGlobals,"_ZN12CGameGlobals12getSingletonEv")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,kind,types,flags,mode;int count,maximum;float chance,roll;};const Case*input;autotest::Capture*capture;CEquipment*item;CGameGlobals*globals;CDataGroup*alternate;unsigned draws;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(10);number(p==item);number(t);if(input->mode==1)++item->m_iSocketCount;if(input->mode==2)item->m_pDataGroup=alternate;unsigned bit=t==UNITTYPES::WEAPON?1:t==UNITTYPES::ARMOR?2:t==UNITTYPES::RING?4:t==UNITTYPES::NECKLACE?8:0;return input->types&bit;}
float random(float lo,float hi){number(11);real(lo);real(hi);++draws;if(input->mode==3)item->m_iSocketCount=123;if(input->mode==5)globals->m_fSecondSocketChance=75.0f;return input->roll;}
CGameGlobals*global(){number(12);if(input->mode==4)item->m_iSocketCount=456;return globals;}
void side(const Case&c,bool ours,autotest::Capture&out){Raw<CEquipment>a;Raw<CResourceManager>b;Raw<CGameGlobals>g;unsigned long long level=0;CDataGroup data(L"ITEM",0,8,8,0),other(L"OTHER",0,8,8,0);alternate=&other;other.AddDataValue(L"MAX_SOCKETS",6u);if(c.flags%3==2)data.AddDataValue(L"MAX_SOCKETS",static_cast<unsigned int>(c.maximum));item=a.get();globals=g.get();input=&c;capture=&out;draws=0;item->m_pDataGroup=c.flags%3?&data:NULL;item->m_iSocketCount=static_cast<unsigned>(c.count);item->m_pResourceManager=c.flags&4?NULL:b.get();b.get()->m_pLevel=c.flags&8?NULL:reinterpret_cast<CLevel*>(&level);globals->m_fSecondSocketChance=c.chance;
 detour::Set patches;TL_REDIRECT(patches,soIsa,&isa);TL_REDIRECT(patches,soRandom,&random);TL_REDIRECT(patches,soGlobals,&global);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(c.kind==0)number(ours?item->getMaxSockets():originalMaxSockets(item));else if(ours)item->addSockets();else originalAddSockets(item);number(item->m_iSocketCount);number(draws);number(item->m_pDataGroup==alternate);real(globals->m_fSecondSocketChance);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_sockets_differential){int failures=0;for(unsigned n=0;n<12593;++n){unsigned q=n/2;static const int counts[]={-3,-1,0,1,2,3,5};static const int maximum[]={-2,0,1,2,3,5,INT_MAX};static const float chances[]={-1,0,25,50,100,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};static const float rolls[]={0,249.99998f,250,250.00002f,500,1000,std::numeric_limits<float>::quiet_NaN()};Case c={n,n%2,q%16,(q/16)%16,(q/784)%6,counts[(q/16)%7],maximum[(q/112)%7],chances[(q/7)%7],rolls[q%7]};
 if(n>=12544){unsigned edge=n-12544;c.kind=1;c.flags=2;c.types=1;c.mode=0;c.count=0;c.maximum=5;c.chance=chances[edge/7];c.roll=rolls[edge%7];}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    sockets case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    sockets: 12593 cases, two entries, two calls per side\n");return failures;}
