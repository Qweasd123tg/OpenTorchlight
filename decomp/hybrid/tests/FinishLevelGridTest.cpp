#include "FinishLevelFixture.h"
TL_ORIGINAL(void,gridOld0,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel23decrementMapPassabilityERKN4Ogre7Vector3E")
extern "C" void gridNew0(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel23decrementMapPassabilityERKN4Ogre7Vector3E");
TL_ORIGINAL(void,gridOld1,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel23incrementMapPassabilityERKN4Ogre7Vector3E")
extern "C" void gridNew1(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel23incrementMapPassabilityERKN4Ogre7Vector3E");
TL_ORIGINAL(void,gridOld2,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel26decrementObjectPassabilityERKN4Ogre7Vector3E")
extern "C" void gridNew2(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel26decrementObjectPassabilityERKN4Ogre7Vector3E");
TL_ORIGINAL(void,gridOld3,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel26incrementObjectPassabilityERKN4Ogre7Vector3E")
extern "C" void gridNew3(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel26incrementObjectPassabilityERKN4Ogre7Vector3E");
TL_ORIGINAL(bool,gridOld4,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel11mapPassableERKN4Ogre7Vector3E")
extern "C" bool gridNew4(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel11mapPassableERKN4Ogre7Vector3E");
TL_ORIGINAL(bool,gridOld5,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel16positionPassableERKN4Ogre7Vector3E")
extern "C" bool gridNew5(CLevel*,const Ogre::Vector3&) __asm__("_ZN6CLevel16positionPassableERKN4Ogre7Vector3E");
TL_ORIGINAL(void,gridOld6,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),"_ZN6CLevel26incrementObjectPassabilityERKN4Ogre7Vector3ES3_f")
extern "C" void gridNew6(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN6CLevel26incrementObjectPassabilityERKN4Ogre7Vector3ES3_f");
TL_ORIGINAL(void,gridOld7,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),"_ZN6CLevel26decrementObjectPassabilityERKN4Ogre7Vector3ES3_f")
extern "C" void gridNew7(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN6CLevel26decrementObjectPassabilityERKN4Ogre7Vector3ES3_f");
TL_ORIGINAL(void,gridOld8,(CLevel*,const Ogre::AxisAlignedBox&,float),"_ZN6CLevel26decrementObjectPassabilityERKN4Ogre14AxisAlignedBoxEf")
extern "C" void gridNew8(CLevel*,const Ogre::AxisAlignedBox&,float) __asm__("_ZN6CLevel26decrementObjectPassabilityERKN4Ogre14AxisAlignedBoxEf");
TL_ORIGINAL(void,gridOld9,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),"_ZN6CLevel23incrementMapPassabilityERKN4Ogre7Vector3ES3_f")
extern "C" void gridNew9(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN6CLevel23incrementMapPassabilityERKN4Ogre7Vector3ES3_f");
TL_ORIGINAL(void,gridOld10,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),"_ZN6CLevel23decrementMapPassabilityERKN4Ogre7Vector3ES3_f")
extern "C" void gridNew10(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN6CLevel23decrementMapPassabilityERKN4Ogre7Vector3ES3_f");
TL_ORIGINAL(void,gridOld11,(CLevel*,const Ogre::AxisAlignedBox&,float),"_ZN6CLevel23decrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf")
extern "C" void gridNew11(CLevel*,const Ogre::AxisAlignedBox&,float) __asm__("_ZN6CLevel23decrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf");
TL_ORIGINAL(void,gridOld12,(CLevel*,const Ogre::AxisAlignedBox&,float),"_ZN6CLevel23incrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf")
extern "C" void gridNew12(CLevel*,const Ogre::AxisAlignedBox&,float) __asm__("_ZN6CLevel23incrementMapPassabilityERKN4Ogre14AxisAlignedBoxEf");
TL_ORIGINAL(void,gridOld13,(CLevel*,const Ogre::AxisAlignedBox&,float),"_ZN6CLevel26incrementObjectPassabilityERKN4Ogre14AxisAlignedBoxEf")
extern "C" void gridNew13(CLevel*,const Ogre::AxisAlignedBox&,float) __asm__("_ZN6CLevel26incrementObjectPassabilityERKN4Ogre14AxisAlignedBoxEf");
namespace finishgrid {
struct Case {unsigned target,variant;};
static void side(void* p,autotest::Capture& out,bool candidate){
 Case c=*static_cast<Case*>(p);finishlevel::Fixture f;CCollisionList collision;
 unsigned w=5,h=6;f.level.m_passWidth=w;f.level.m_passHeight=h;
 f.level.m_mapPassability=new short*[w];f.level.m_objectPassability=new short*[w];
 for(unsigned x=0;x<w;++x){f.level.m_mapPassability[x]=new short[h];f.level.m_objectPassability[x]=new short[h];for(unsigned z=0;z<h;++z){f.level.m_mapPassability[x][z]=short((x+z+c.variant)%5-2);f.level.m_objectPassability[x][z]=short((x*3+z+c.variant)%7-3);}}
 f.level.m_collisionList=c.variant%3?&collision:NULL;f.level.m_topLeftX=-1.2f;f.level.m_topLeftY=2.4f;
 const float xs[]={-2.0f,-0.01f,0.0f,0.4f,0.8f,1.2f,1.99f,2.0f,2.4f,4.0f};
 Ogre::Vector3 first(xs[c.variant%10],float(c.variant),xs[(c.variant*3)%10]);
 if(f.level.m_collisionList){first.x+=f.level.m_topLeftX;first.z+=f.level.m_topLeftY;}
 Ogre::Vector3 second=first+Ogre::Vector3(xs[(c.variant+4)%10],-3.0f,xs[(c.variant+7)%10]);
 const float radii[]={0.0f,-0.4f,0.4f,0.8f,1.6f,10.0f};float radius=radii[(c.variant/8)%6];
 Ogre::AxisAlignedBox bounds;bounds.setExtents(first,second);bool result=false;
 switch(c.target){
 case 0: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew0,&f.level,first);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld0,&f.level,first);break;
 case 1: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew1,&f.level,first);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld1,&f.level,first);break;
 case 2: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew2,&f.level,first);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld2,&f.level,first);break;
 case 3: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew3,&f.level,first);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld3,&f.level,first);break;
 case 4: if(candidate)autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew4,&f.level,first);else autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld4,&f.level,first);break;
 case 5: if(candidate)autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridNew5,&f.level,first);else autotest::invoke<bool(*)(CLevel*,const Ogre::Vector3&),CLevel*,const Ogre::Vector3&>(out,gridOld5,&f.level,first);break;
 case 6: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridNew6,&f.level,first,second,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridOld6,&f.level,first,second,radius);break;
 case 7: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridNew7,&f.level,first,second,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridOld7,&f.level,first,second,radius);break;
 case 8: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridNew8,&f.level,bounds,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridOld8,&f.level,bounds,radius);break;
 case 9: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridNew9,&f.level,first,second,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridOld9,&f.level,first,second,radius);break;
 case 10: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridNew10,&f.level,first,second,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float>(out,gridOld10,&f.level,first,second,radius);break;
 case 11: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridNew11,&f.level,bounds,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridOld11,&f.level,bounds,radius);break;
 case 12: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridNew12,&f.level,bounds,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridOld12,&f.level,bounds,radius);break;
 case 13: if(candidate)autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridNew13,&f.level,bounds,radius);else autotest::invoke<void(*)(CLevel*,const Ogre::AxisAlignedBox&,float),CLevel*,const Ogre::AxisAlignedBox&,float>(out,gridOld13,&f.level,bounds,radius);break;
 }
 finishlevel::number(out,result);for(unsigned x=0;x<w;++x){out.add(f.level.m_mapPassability[x],h*sizeof(short));out.add(f.level.m_objectPassability[x],h*sizeof(short));}
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_grid_937860){autotest::Coverage coverage("finish_level_grid_937860",0x937860);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={0,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_937950){autotest::Coverage coverage("finish_level_grid_937950",0x937950);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={1,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_9381b0){autotest::Coverage coverage("finish_level_grid_9381b0",0x9381b0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={2,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_9382a0){autotest::Coverage coverage("finish_level_grid_9382a0",0x9382a0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={3,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_938390){autotest::Coverage coverage("finish_level_grid_938390",0x938390);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={4,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_938480){autotest::Coverage coverage("finish_level_grid_938480",0x938480);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={5,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_9459d0){autotest::Coverage coverage("finish_level_grid_9459d0",0x9459d0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={6,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_945ce0){autotest::Coverage coverage("finish_level_grid_945ce0",0x945ce0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={7,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_945ff0){autotest::Coverage coverage("finish_level_grid_945ff0",0x945ff0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={8,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_9468b0){autotest::Coverage coverage("finish_level_grid_9468b0",0x9468b0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={9,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_946bc0){autotest::Coverage coverage("finish_level_grid_946bc0",0x946bc0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={10,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_946ed0){autotest::Coverage coverage("finish_level_grid_946ed0",0x946ed0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={11,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_9471e0){autotest::Coverage coverage("finish_level_grid_9471e0",0x9471e0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={12,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_grid_937a40){autotest::Coverage coverage("finish_level_grid_937a40",0x937a40);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishgrid::Case c={13,n};autotest::compareCase(finishgrid::original,finishgrid::ours,&c,stats,host,"grid",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
