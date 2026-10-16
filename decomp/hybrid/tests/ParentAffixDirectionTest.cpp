#include "ParentPairs.h"
#define private public
#include "Affix.h"
#include "Effect.h"
#undef private
TL_ORIGINAL(void,parentAffixOld,(CAffix*,const Ogre::Vector3*),"_ZN6CAffix12setDirectionEPKN4Ogre7Vector3E")
extern "C" void parentAffixNew(CAffix*,const Ogre::Vector3*) __asm__("_ZN6CAffix12setDirectionEPKN4Ogre7Vector3E");
namespace {
void side(void* raw,autotest::Capture& out,bool ours)
{
    unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;
    CAffix* affix=static_cast<CAffix*>(autotest::allocate(sizeof(CAffix)));
    CEffect* effects[6];for(unsigned i=0;i<6;++i)effects[i]=static_cast<CEffect*>(autotest::allocate(sizeof(CEffect)));
    new(&affix->m_Effects)TArrayList<CEffect*>(2);
    const unsigned bits[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x7f800000u,0xff800000u,0x7fc01001u,1u};
    for(unsigned i=0;i<6;++i){unsigned xyz[3]={bits[(seed+i)%8],bits[(seed/2+i+3)%8],bits[(seed/4+i+5)%8]};std::memcpy(&effects[i]->m_direction,xyz,sizeof(xyz));}
    for(unsigned i=0;i<seed%7;++i)affix->m_Effects.add(effects[(seed%3==0?i/2:i)%6]);
    Ogre::Vector3 direction;unsigned xyz[3]={bits[(seed/3)%8],bits[(seed/5+2)%8],bits[(seed/7+4)%8]};std::memcpy(&direction,xyz,sizeof(xyz));
    const Ogre::Vector3* input=seed%4==0?NULL:seed%4==1?&direction:seed%4==2?&effects[(seed/4)%6]->m_direction:&Ogre::Vector3::UNIT_Z;
    typedef void(*Fn)(CAffix*,const Ogre::Vector3*);Fn fn=ours?parentAffixNew:parentAffixOld;autotest::invoke(out,fn,affix,input);
    // Observe whole bounded effect storage: vector writes must preserve neighbours.
    for(unsigned i=0;i<6;++i)out.add(effects[i],sizeof(CEffect));
    out.add(&direction,sizeof(direction));parentpairs::scalar(out,affix->m_Effects.size());
    affix->m_Effects.~TArrayList();
}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(parent_affix_direction){return parentpairs::run(host,"parent_affix_direction",(uintptr_t)parentAffixOld,128,a,b);}
