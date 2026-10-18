#include "SmallMassCompare.h"
#include "POV.h"

TL_ORIGINAL(void, lateralOriginal, (void*,float), "_ZN4CPOV19DampLateralVelocityEf")
TL_ORIGINAL(void, capOriginal, (void*,float), "_ZN4CPOV18CapContactVelocityEf")
TL_ORIGINAL(void, orientationOriginal, (void*,const Ogre::Matrix4&), "_ZN4CPOV14SetOrientationERKN4Ogre7Matrix4E")
TL_ORIGINAL(void, viewOriginal, (void*,const Ogre::Matrix4&), "_ZN4CPOV18SetViewOrientationERKN4Ogre7Matrix4E")
extern "C" void lateralCandidate(void*,float) __asm__("_ZN4CPOV19DampLateralVelocityEf");
extern "C" void capCandidate(void*,float) __asm__("_ZN4CPOV18CapContactVelocityEf");
extern "C" void orientationCandidate(void*,const Ogre::Matrix4&) __asm__("_ZN4CPOV14SetOrientationERKN4Ogre7Matrix4E");
extern "C" void viewCandidate(void*,const Ogre::Matrix4&) __asm__("_ZN4CPOV18SetViewOrientationERKN4Ogre7Matrix4E");

namespace {
using namespace smallmass;
float scalar(unsigned i) {
    static const unsigned special[] = {0,0x80000000,0x3f800000,0xbf800000,
        0x30800000,0xb0800000,0x7fc01234,0x7f800000,0xff800000,0x3e800000};
    return i < 10 ? bits(special[i]) : float(int(i%23)-11)*0.375f;
}
void execute(Case& c,bool ours,autotest::Capture& out) {
    autotest::g_arenaUsed=0;
    unsigned char* self=static_cast<unsigned char*>(object(sizeof(CPOV)));
    for(unsigned i=0;i<sizeof(CPOV);++i)self[i]=(i*37+c.index*13)&255;
    Ogre::Matrix4 matrix;
    for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j) {
        matrix[i][j]=scalar(c.index+i*7+j*13);
        field<Ogre::Matrix4>(self,0x18)[i][j]=scalar(c.index+i*3+j*11);
        field<Ogre::Matrix4>(self,0x58)[i][j]=scalar(c.index+i*17+j*5);
    }
    for(unsigned i=0;i<3;++i) {
        field<float>(self,0x138+i*4)=scalar(c.index+i*3);
        field<float>(self,0xf0+i*4)=scalar(c.index/3+i*5);
        field<float>(self,0x108+i*4)=scalar(c.index/5+i*7);
    }
    float amount=scalar(c.index/2);
    if(c.op==0)autotest::invoke(out,ours?lateralCandidate:lateralOriginal,self,amount);
    else if(c.op==1)autotest::invoke(out,ours?capCandidate:capOriginal,self,amount);
    else {
        const Ogre::Matrix4& argument=c.index%3==0?field<Ogre::Matrix4>(self,0x18):
            c.index%3==1?field<Ogre::Matrix4>(self,0x58):matrix;
        autotest::invoke<void (*)(void*,const Ogre::Matrix4&),void*,const Ogre::Matrix4&>(out,c.op==2?(ours?orientationCandidate:orientationOriginal):
            (ours?viewCandidate:viewOriginal),self,argument);
    }
    out.add(self,sizeof(CPOV));
}
}
TL_TEST(advance_pov_lateral){return smallmass::run(host,0,"advance_pov_lateral",(uintptr_t)lateralOriginal,execute,120);}
TL_TEST(advance_pov_cap){return smallmass::run(host,1,"advance_pov_cap",(uintptr_t)capOriginal,execute,120);}
TL_TEST(advance_pov_orientation){return smallmass::run(host,2,"advance_pov_orientation",(uintptr_t)orientationOriginal,execute,120);}
TL_TEST(advance_pov_view){return smallmass::run(host,3,"advance_pov_view",(uintptr_t)viewOriginal,execute,120);}
