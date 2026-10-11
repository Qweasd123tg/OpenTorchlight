#include <cstring>
#include <utility>
#include <fenv.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreMatrix4.h>
#include <OgreMath.h>
#include "AutoTest.h"
#include "Detour.h"
typedef std::pair<bool,float> Pair;
extern "C" char target_random[] __asm__("_ZN4Ogre4Math11RangeRandomEff");
TL_ORIGINAL(float,original0,(void*,float),"_ZN6CShape23getAngleOffsetAtPercentEf")
extern "C" float candidate0(void*,float) __asm__("_ZN6CShape23getAngleOffsetAtPercentEf");
TL_ORIGINAL(Ogre::Vector3,original1,(void*,float,float),"_ZN6CShape25calculatePositionOnSphereEff")
extern "C" Ogre::Vector3 candidate1(void*,float,float) __asm__("_ZN6CShape25calculatePositionOnSphereEff");
TL_ORIGINAL(Ogre::Vector3,original2,(void*,float,float),"_ZN6CShape36calculatePositionOnLineBetweenAnglesEff")
extern "C" Ogre::Vector3 candidate2(void*,float,float) __asm__("_ZN6CShape36calculatePositionOnLineBetweenAnglesEff");
TL_ORIGINAL(Ogre::Vector3,original3,(void*,float,float),"_ZN6CShape39calculatePositionBetweenAnglesAndRadiusEff")
extern "C" Ogre::Vector3 candidate3(void*,float,float) __asm__("_ZN6CShape39calculatePositionBetweenAnglesAndRadiusEff");
TL_ORIGINAL(Pair,original4,(void*,float,const Ogre::Vector3&,float),"_ZN6CShape22lineIntersectsPositionEfRKN4Ogre7Vector3Ef")
extern "C" Pair candidate4(void*,float,const Ogre::Vector3&,float) __asm__("_ZN6CShape22lineIntersectsPositionEfRKN4Ogre7Vector3Ef");
TL_ORIGINAL(Pair,original5,(void*,float,const Ogre::Vector3&,float),"_ZN6CShape31positionWithRadiusIntersectsBoxEfRKN4Ogre7Vector3Ef")
extern "C" Pair candidate5(void*,float,const Ogre::Vector3&,float) __asm__("_ZN6CShape31positionWithRadiusIntersectsBoxEfRKN4Ogre7Vector3Ef");
TL_ORIGINAL(Pair,original6,(void*,float,const Ogre::Vector3&,float),"_ZN6CShape29getPositionIsInShapeAtPercentEfRKN4Ogre7Vector3Ef")
extern "C" Pair candidate6(void*,float,const Ogre::Vector3&,float) __asm__("_ZN6CShape29getPositionIsInShapeAtPercentEfRKN4Ogre7Vector3Ef");
TL_FUNCTION(target_radius,"_ZN6CShape18getRadiusAtPercentEf")
TL_FUNCTION(target_release,"_ZN6CShape26getAngleOfReleaseAtPercentEf")
TL_FUNCTION(target_offset,"_ZN6CShape23getAngleOffsetAtPercentEf")
TL_FUNCTION(target_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(target_line,"_ZN6CShape21calculateLineSequmentEfRN4Ogre7Vector3ES2_")
TL_FUNCTION(target_maximum,"_ZN6CShape21getMaxRadiusAtPercentEf")
TL_FUNCTION(target_angleIntersects,"_ZN6CShape23positionIntersectsAngleEfRKN4Ogre7Vector3Ef")
TL_FUNCTION(target_lineIntersects,"_ZN6CShape22lineIntersectsPositionEfRKN4Ogre7Vector3Ef")
TL_FUNCTION(target_boxIntersects,"_ZN6CShape31positionWithRadiusIntersectsBoxEfRKN4Ogre7Vector3Ef")
TL_FUNCTION(target_closest,"_ZN4MATH18closestPointOnLineERKN4Ogre7Vector3ES3_S3_RS1_")

TL_ORIGINAL(Ogre::Vector3,original7,(void*,float,float),"_ZN6CShape22calculatePositionOnBoxEff")
extern "C" Ogre::Vector3 candidate7(void*,float,float) __asm__("_ZN6CShape22calculatePositionOnBoxEff");
TL_ORIGINAL(void,original8,(void*,float,Ogre::Vector3&,Ogre::Vector3&),"_ZN6CShape21calculateLineSequmentEfRN4Ogre7Vector3ES2_")
extern "C" void candidate8(void*,float,Ogre::Vector3&,Ogre::Vector3&) __asm__("_ZN6CShape21calculateLineSequmentEfRN4Ogre7Vector3ES2_");
TL_FUNCTION(target_minimum,"_ZN6CShape21getMinRadiusAtPercentEf")
TL_FUNCTION(target_volatile,"_ZN9UTILITIES21randomBetweenVolatileEff")
namespace {
struct Case{unsigned op,seed,mode;float percent,radius,value;};Case*input;autotest::Capture*output;void*active;void*nodes[2];unsigned calls;Ogre::Vector3*startPointer,*endPointer,*pointPointer;Ogre::Quaternion rotations[2];
void num(unsigned n){output->add(&n,4);}void ptr(void*p){output->add(&p,8);}void fl(float v){output->add(&v,4);}void vec(const Ogre::Vector3&v){output->add(&v,12);}void event(unsigned n,void*p){num(n);ptr(p);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void word(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}
void change(){++calls;if(input->mode==1)word(active,0x100,calls%5);if(input->mode==2){word(active,0x104,2);float size=9.75f;std::memcpy(static_cast<char*>(active)+0x138,&size,4);size=0.5f;std::memcpy(static_cast<char*>(active)+0x140,&size,4);}if(input->mode==3)put(active,0x58,nodes[calls%2]);}
float radius(void*p,float percent){event(1,p);fl(percent);change();return input->value;}
float release(void*p,float percent){event(2,p);fl(percent);change();return input->value;}
float offset(void*p,float percent){event(3,p);fl(percent);change();return input->radius;}
Ogre::Vector3 position(void*p,bool absolute){event(4,p);num(absolute);change();if(input->mode==6)pointPointer->z=3.25f;return Ogre::Vector3(input->value,-2.5f,input->percent);}
void line(void*p,float percent,Ogre::Vector3&start,Ogre::Vector3&end){event(5,p);fl(percent);vec(start);vec(end);change();start=Ogre::Vector3(input->value,-1.5f,input->percent);end=Ogre::Vector3(input->radius,2.25f,input->value);startPointer=&start;endPointer=&end;}
float minimum(void*p,float percent){event(15,p);fl(percent);change();return input->radius;}
float maximum(void*p,float percent){event(6,p);fl(percent);change();return input->value;}
Pair angleIntersects(void*p,float percent,const Ogre::Vector3&point,float r){event(7,p);fl(percent);vec(point);fl(r);change();return Pair(input->seed&1,input->value);}
Pair lineIntersects(void*p,float percent,const Ogre::Vector3&point,float r){event(8,p);fl(percent);vec(point);fl(r);change();return Pair(input->seed&1,input->value);}
Pair boxIntersects(void*p,float percent,const Ogre::Vector3&point,float r){event(9,p);fl(percent);vec(point);fl(r);change();return Pair(input->seed&1,input->value);}
void closest(const Ogre::Vector3&start,const Ogre::Vector3&end,const Ogre::Vector3&point,Ogre::Vector3&out){num(10);vec(start);vec(end);vec(point);vec(out);change();out=Ogre::Vector3(input->radius,5.0f,input->value);if(input->mode==6)pointPointer->x=3.5f;}
float random(float low,float high){num(11);fl(low);fl(high);change();if(input->mode==5&&startPointer){startPointer->x=5.5f;endPointer->z=-2.75f;}return input->mode==7?low:input->mode==8?high:float(int(calls%9)-4)*0.125f;}
float dynamic(void*p,void*particle,float percent){event(12,p);ptr(particle);fl(percent);change();return input->radius;}
const Ogre::Quaternion& orientation(void*p){event(13,p);change();return rotations[p==nodes[1]?1:0];}
Ogre::Matrix4 transformation(void*p){event(14,p);change();Ogre::Matrix4 m=Ogre::Matrix4::IDENTITY;switch((input->seed/10)%6){case 0:break;case 1:m[0][3]=7.0f;m[2][3]=-3.0f;break;case 2:m[0][0]=2.0f;m[2][2]=0.25f;break;case 3:m[0][2]=-1.0f;m[2][0]=1.0f;m[0][0]=m[2][2]=0;break;case 4:m[3][0]=0.125f;m[3][2]=0.0625f;break;case 5:for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col)m[row][col]=0.0f;break;}return m;}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;startPointer=endPointer=NULL;unsigned long long selfData[0x168/8],node[2][8]={{0}},attribute[8]={0};std::memset(selfData,(c.seed*17+3)&255,sizeof(selfData));void*self=selfData;active=self;
 void*shapeTable[40]={0};shapeTable[0x100/8]=reinterpret_cast<void*>(&transformation);void*nodeTable[72]={0};nodeTable[0x1f8/8]=reinterpret_cast<void*>(&orientation);void*dynamicTable[4]={0};dynamicTable[2]=reinterpret_cast<void*>(&dynamic);put(attribute,0,dynamicTable);put(self,0,shapeTable);
 for(unsigned i=0;i<2;++i){nodes[i]=node[i];put(nodes[i],0,nodeTable);rotations[i]=Ogre::Quaternion(1.0f-i*0.2f,i*0.25f,0.125f,i*0.5f);}
 put(self,0x58,nodes[0]);put(self,0x118,c.seed&16?NULL:attribute);const unsigned modes[]={0,1,2,3,4,0x80000000u,0xffffffffu};word(self,0x100,modes[(c.seed/10)%7]);word(self,0x104,modes[(c.seed/10)%7]);std::memcpy(static_cast<char*>(self)+0x138,&c.value,4);std::memcpy(static_cast<char*>(self)+0x140,&c.radius,4);
 Ogre::Vector3 point(c.percent,c.value,c.radius);pointPointer=&point;Ogre::Math::setAngleUnit(c.mode==9?Ogre::Math::AU_RADIAN:Ogre::Math::AU_DEGREE);
 detour::Set patches;
 if(true){TL_REDIRECT(patches,target_radius,&radius);}
 if(true){TL_REDIRECT(patches,target_release,&release);}
 if(c.op!=0){TL_REDIRECT(patches,target_offset,&offset);}
 if(true){TL_REDIRECT(patches,target_position,&position);}
 if(c.op!=8){TL_REDIRECT(patches,target_line,&line);}
 TL_REDIRECT(patches,target_minimum,&minimum);TL_REDIRECT(patches,target_volatile,&random);
 if(true){TL_REDIRECT(patches,target_maximum,&maximum);}
 if(true){TL_REDIRECT(patches,target_angleIntersects,&angleIntersects);}
 if(c.op!=4){TL_REDIRECT(patches,target_lineIntersects,&lineIntersects);}
 if(c.op!=5){TL_REDIRECT(patches,target_boxIntersects,&boxIntersects);}
 if(true){TL_REDIRECT(patches,target_closest,&closest);}
 patches.redirect(target_random,target_random,&random);if(patches.failed())_exit(41);feclearexcept(FE_ALL_EXCEPT);
 switch(c.op){
 case 7:{Ogre::Vector3(*fn)(void*,float,float)=ours?candidate7:original7;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(self,c.percent,c.radius);out.callCompleted=1;vec(result);break;}
 case 8:{Ogre::Vector3 start(c.value,c.radius,c.percent),end(c.radius,c.percent,c.value);Ogre::Vector3&targetEnd=c.seed%3==0?start:end;startPointer=&start;endPointer=&targetEnd;void(*fn)(void*,float,Ogre::Vector3&,Ogre::Vector3&)=ours?candidate8:original8;if(!autotest::beginInvocation(out,fn))return;fn(self,c.percent,start,targetEnd);out.callCompleted=1;vec(start);vec(end);break;}
 case 0:{float(*fn)(void*,float)=ours?candidate0:original0;if(!autotest::beginInvocation(out,fn))return;float result=fn(self,c.percent);out.callCompleted=1;fl(result);break;}
 case 1:{Ogre::Vector3(*fn)(void*,float,float)=ours?candidate1:original1;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(self,c.percent,c.radius);out.callCompleted=1;vec(result);break;}
 case 2:{Ogre::Vector3(*fn)(void*,float,float)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(self,c.percent,c.radius);out.callCompleted=1;vec(result);break;}
 case 3:{Ogre::Vector3(*fn)(void*,float,float)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(self,c.percent,c.radius);out.callCompleted=1;vec(result);break;}
 case 4:{Pair(*fn)(void*,float,const Ogre::Vector3&,float)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;Pair result=fn(self,c.percent,point,c.radius);out.callCompleted=1;num(result.first);fl(result.second);break;}
 case 5:{Pair(*fn)(void*,float,const Ogre::Vector3&,float)=ours?candidate5:original5;if(!autotest::beginInvocation(out,fn))return;Pair result=fn(self,c.percent,point,c.radius);out.callCompleted=1;num(result.first);fl(result.second);break;}
 case 6:{Pair(*fn)(void*,float,const Ogre::Vector3&,float)=ours?candidate6:original6;if(!autotest::beginInvocation(out,fn))return;Pair result=fn(self,c.percent,point,c.radius);out.callCompleted=1;num(result.first);fl(result.second);break;}

 }num(fetestexcept(FE_ALL_EXCEPT));num(calls);vec(point);out.add(selfData,sizeof(selfData));out.add(node,sizeof(node));out.add(attribute,sizeof(attribute));patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)original8};const unsigned bits[]={0,0x80000000u,0x3f000000u,0x3f800000u,0xbf800000u,0x40800000u,0xc0600000u,0x7f800000u,0xff800000u,0x7fc01234u};autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<1400;++n){Case c={op,n,n%10,0,0,0};unsigned a=bits[(n/10)%10],b=bits[(n/100)%10],d=bits[(n/30)%10];std::memcpy(&c.percent,&a,4);std::memcpy(&c.radius,&b,4);std::memcpy(&c.value,&d,4);autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(recovered,&c,y);if(coverage.observe(host,x,y)){host->log("    shape next %u/%u status %d/%d bytes %lu/%lu\n",op,n,x.status,y.status,(unsigned long)x.capture.length,(unsigned long)y.capture.length);for(unsigned i=0;i<x.capture.length&&i<y.capture.length;++i)if(x.capture.data[i]!=y.capture.data[i]){host->log("    first byte %u %u/%u\n",i,(unsigned char)x.capture.data[i],(unsigned char)y.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(shape_next_angle_offset){return run(host,0,"shape_next_angle_offset");}
TL_TEST(shape_next_sphere){return run(host,1,"shape_next_sphere");}
TL_TEST(shape_next_line){return run(host,2,"shape_next_line");}
TL_TEST(shape_next_arc){return run(host,3,"shape_next_arc");}
TL_TEST(shape_next_line_intersection){return run(host,4,"shape_next_line_intersection");}
TL_TEST(shape_next_box_intersection){return run(host,5,"shape_next_box_intersection");}
TL_TEST(shape_next_contains){return run(host,6,"shape_next_contains");}

TL_TEST(shape_next_box){return run(host,7,"shape_next_box");}
TL_TEST(shape_next_segment){return run(host,8,"shape_next_segment");}
