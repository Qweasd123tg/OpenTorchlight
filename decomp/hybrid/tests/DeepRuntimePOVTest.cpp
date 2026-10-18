#include "tests/SmallMassCompare.h"
#include "POV.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void,deepPOVUpdate,(CPOV*,float,float),"_ZN4CPOV6UpdateEff")
DECL(void,deepPOVMouse,(CPOV*,void*,float),"_ZN4CPOV16UpdateMouseInputEPvf")
DECL(void,deepPOVReset,(CPOV*,bool,float,float),"_ZN4CPOV8ResetPOVEbff")
TL_FUNCTION(deepPOVFly,"_ZN4CPOV14UpdateFlyingToEf")
TL_FUNCTION(deepPOVInputs,"_ZN4CPOV12UpdateInputsEf")
TL_FUNCTION(deepPOVExtract,"_ZN4CPOV25ExtractOrientationVectorsEv")
TL_FUNCTION(deepPOVCap,"_ZN4CPOV18CapContactVelocityEf")
TL_FUNCTION(deepPOVCursor,"_Z12GetCursorPosP5POINT")
TL_FUNCTION(deepPOVKey,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(deepPOVSetCursor,"_Z12SetCursorPosii")
TL_FUNCTION(deepPOVGetInt,"_ZN20CDynamicPropertyFile6GetIntEj")
namespace {using namespace smallmass;
struct Point{long long x,y;};
long long flying(CPOV* p,float t){event(1,p);floating(t);p->m_fUnknownE0+=2;return input->index&1;}
void inputs(CPOV* p,float t){event(2,p);floating(t);p->m_fUnknown138+=float(int(input->index%5)-2);}
void extract(CPOV* p){event(3,p);p->m_fUnknownDC+=.25f;}
void cap(CPOV* p,float maximum){event(4,p);floating(maximum);p->m_fUnknown140=-p->m_fUnknown140;}
void update(CPOV* p,float t,float scale){event(5,p);floating(t);floating(scale);p->m_fUnknownD8+=3;}
bool cursor(Point* p){number(6);p->x=input->index%8==0?0:input->index%8==1?900:300;p->y=input->index%8==2?-1:input->index%8==3?700:200;return true;}
short key(unsigned key){number(7);number(key);return key==2?(input->index&8?-32768:0):(input->index&16?-32768:0);}
bool setCursor(int x,int y){number(8);number(x);number(y);return true;}
int getInt(void* p,unsigned key){event(9,p);number(key);if(key==KSETTINGS_WIN_WIDTH)return 800;if(key==KSETTINGS_WIN_HEIGHT)return 600;if(key==KSETTINGS_RES_WIDTH)return 1025;return 769;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;CPOV* p=static_cast<CPOV*>(object(sizeof(CPOV)));p->m_settings=static_cast<CSettings*>(object(8));Ogre::Quaternion q(Ogre::Radian(float(int(c.index%7)-3)*.2f),Ogre::Vector3::UNIT_X);p->m_orientation=Ogre::Matrix4(q);p->m_viewOrientation=Ogre::Matrix4::IDENTITY;for(unsigned i=0xd8;i<=0x144;i+=4)field<float>(p,i)=float(int(i+c.index)%19-9)*.3f;p->m_bUnknown178=c.index&2;p->m_bUnknown14E=c.index&32;p->m_fUnknown158=float(int(c.index%25)-12)*.4f;p->m_fUnknown160=-p->m_fUnknown158;p->m_fUnknown15C=3;p->m_fUnknown164=4;p->m_iUnknown168=300+int(c.index%5)*18-36;p->m_iUnknown170=200+int(c.index%7)*12-36;
for(unsigned i=0x148;i<=0x14d;++i)field<bool>(p,i)=true;
detour::Set d;TL_REDIRECT(d,deepPOVFly,&flying);TL_REDIRECT(d,deepPOVInputs,&inputs);TL_REDIRECT(d,deepPOVCap,&cap);TL_REDIRECT(d,deepPOVExtract,&extract);TL_REDIRECT(d,deepPOVCursor,&cursor);TL_REDIRECT(d,deepPOVKey,&key);TL_REDIRECT(d,deepPOVSetCursor,&setCursor);TL_REDIRECT(d,deepPOVGetInt,&getInt);if(c.op==2)d.redirect(reinterpret_cast<char*>(deepPOVUpdateOld),reinterpret_cast<char*>(deepPOVUpdateNew),&update);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0)autotest::invoke(out,ours?deepPOVUpdateNew:deepPOVUpdateOld,p,float(c.index%6)*.125f,float(c.index%5)*.25f);
else if(c.op==1)autotest::invoke(out,ours?deepPOVMouseNew:deepPOVMouseOld,p,static_cast<void*>(0),.125f);
else autotest::invoke(out,ours?deepPOVResetNew:deepPOVResetOld,p,bool(c.index&1),c.index&2?0.0f:1.25f,c.index&4?0.0f:-2.5f);
out.add(reinterpret_cast<char*>(p)+0x18,sizeof(CPOV)-0x18);}
}
TL_TEST(deep_runtime_pov_update){return smallmass::run(host,0,"deep_runtime_pov_update",(uintptr_t)deepPOVUpdateOld,execute,128);}
TL_TEST(deep_runtime_pov_mouse){return smallmass::run(host,1,"deep_runtime_pov_mouse",(uintptr_t)deepPOVMouseOld,execute,128);}
TL_TEST(deep_runtime_pov_reset){return smallmass::run(host,2,"deep_runtime_pov_reset",(uintptr_t)deepPOVResetOld,execute,128);}
