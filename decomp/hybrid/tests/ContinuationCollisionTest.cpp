#include <cstring>
#include <vector>
#include <OgreMatrix4.h>
#include "AutoTest.h"
#define private public
#include "CollisionList.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,coOptimize,cnOptimize,(CCollisionList*),"_ZN14CCollisionList8optimizeEv")
DECL(void,coNormals,cnNormals,(CCollisionList*),"_ZN14CCollisionList16calculateNormalsEv")
DECL(void,coBounds,cnBounds,(CCollisionList*),"_ZN14CCollisionList19calculateFaceBoundsEv")
DECL(bool,coPoint,cnPoint,(CCollisionList*,const Ogre::Vector3&,int),"_ZN14CCollisionList7pointInERKN4Ogre7Vector3Ei")
DECL(void,coAppend,cnAppend,(CCollisionList*,CCollisionList*,const Ogre::Matrix4&,int),"_ZN14CCollisionList16addCollisionListEPS_RKN4Ogre7Matrix4Ei")
DECL(bool,coRay,cnRay,(CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),"_ZN14CCollisionList12rayCollisionERKN4Ogre7Vector3ES3_S3_S3_RS1_S4_RjS4_Rf")
DECL(bool,coRaySubset,cnRaySubset,(CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),"_ZN14CCollisionList12rayCollisionERKSt6vectorIjSaIjEERKN4Ogre7Vector3ES8_S8_S8_RS6_S9_RjS9_Rf")
DECL(bool,coSphere,cnSphere,(CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),"_ZN14CCollisionList15sphereCollisionERKN4Ogre7Vector3ES3_S3_S3_fRS1_S4_S4_RjS4_Rf")
DECL(bool,coSphereSubset,cnSphereSubset,(CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),"_ZN14CCollisionList15sphereCollisionERKSt6vectorIjSaIjEERKN4Ogre7Vector3ES8_S8_S8_fRS6_S9_S9_RjS9_Rf")
#undef DECL
namespace {
template<class Fn, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> void collisionInvoke(autotest::Capture& out,Fn fn,A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9){if(!autotest::beginInvocation(out,fn))return;autotest::record(out,(fn(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9),autotest::ReturnTag<bool>()));out.callCompleted=1;}


template<class Fn, class A0, class A1, class A2> void collisionInvoke(autotest::Capture& out,Fn fn,A0 a0, A1 a1, A2 a2){if(!autotest::beginInvocation(out,fn))return;autotest::record(out,(fn(a0, a1, a2),autotest::ReturnTag<bool>()));out.callCompleted=1;}
template<class Fn, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> void collisionInvoke(autotest::Capture& out,Fn fn,A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10){if(!autotest::beginInvocation(out,fn))return;autotest::record(out,(fn(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10),autotest::ReturnTag<bool>()));out.callCompleted=1;}
template<class Fn, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> void collisionInvoke(autotest::Capture& out,Fn fn,A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11){if(!autotest::beginInvocation(out,fn))return;autotest::record(out,(fn(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11),autotest::ReturnTag<bool>()));out.callCompleted=1;}
template<class Fn, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> void collisionInvoke(autotest::Capture& out,Fn fn,A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12){if(!autotest::beginInvocation(out,fn))return;autotest::record(out,(fn(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12),autotest::ReturnTag<bool>()));out.callCompleted=1;}

struct Case {unsigned op,seed;};
template<class T> void array(autotest::Capture& out,const std::vector<T>& values){unsigned n=values.size(),capacity=values.capacity();out.add(&n,4);out.add(&capacity,4);if(n)out.add(&values[0],n*sizeof(T));}
void meshState(autotest::Capture& out,CCollisionList& p){out.add(&p.m_vBoundsMin,24);array(out,p.m_FaceMaxBounds);array(out,p.m_FaceMinBounds);array(out,p.m_Vertices);array(out,p.m_Colors);array(out,p.m_Normals);array(out,p.m_IndicesA);array(out,p.m_IndicesB);array(out,p.m_IndicesC);array(out,p.m_Materials);out.add(&p.m_iIgnoredMaterial,4);}
void fill(CCollisionList& p,unsigned seed){
 if(seed%16==0)return;
 Ogre::Vector3 vertices[]={Ogre::Vector3(-2,0,-2),Ogre::Vector3(2,0,-2),Ogre::Vector3(2,0,2),Ogre::Vector3(-2,0,2),Ogre::Vector3(0,-3,0),Ogre::Vector3(0,3,0),Ogre::Vector3(0,3,3)};
 for(unsigned i=0;i<7;++i){p.addVertex(vertices[i],-1);if(seed%3)p.addColor(Ogre::Vector3(i*0.125f,i*0.25f,i*0.5f),-1);}
 p.addFace(0,1,2,11,-1);p.addFace(0,2,3,12,-1);p.addFace(4,5,6,13,-1);
 coNormals(&p);coBounds(&p);
 p.m_iIgnoredMaterial=seed%7==0?11:seed%7==1?12:seed%7==2?13:100000;
}
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*static_cast<Case*>(raw);CCollisionList p,source;fill(p,c.seed);fill(source,c.seed+3);
 Ogre::Vector3 hit(71,72,73),normal(81,82,83),position(61,62,63),color(91,92,93);unsigned material=0x12345678;float distance=c.seed%4==0?0:c.seed%4==1?1:c.seed%4==2?99999.0f:100.0f;
 if(c.op==0){
  if(!p.m_Vertices.empty())for(unsigned i=0;i<c.seed%5+1;++i){p.addVertex(p.m_Vertices[i%3],-1);unsigned v=p.m_Vertices.size()-1;p.addFace(v,1,2,20+i,-1);}
  autotest::invoke(out,ours?&cnOptimize:&coOptimize,&p);
 }else if(c.op==1){
  if(c.seed%6==0&&!p.m_IndicesA.empty())p.m_IndicesB[0]=p.m_IndicesA[0];
  p.m_Normals.push_back(Ogre::Vector3(17,18,19));autotest::invoke(out,ours?&cnNormals:&coNormals,&p);
 }else if(c.op==2){
  p.m_vBoundsMin=Ogre::Vector3(70);p.m_vBoundsMax=Ogre::Vector3(-70);
  p.m_FaceMinBounds.push_back(Ogre::Vector3(40));p.m_FaceMaxBounds.push_back(Ogre::Vector3(-40));autotest::invoke(out,ours?&cnBounds:&coBounds,&p);
 }else if(c.op==3){
  if(p.m_IndicesA.empty())fill(p,1);
  static const float xy[]={-3,-2,-1,0,1,2,3,0.000001f};
  Ogre::Vector3 point(xy[c.seed%8],c.seed%3==0?5.0f:0.0f,xy[(c.seed/3)%8]);
  int face=c.seed%2;collisionInvoke<bool(*)(CCollisionList*,const Ogre::Vector3&,int),CCollisionList*,const Ogre::Vector3&,int>(out,ours?&cnPoint:&coPoint,&p,point,face);
 }else if(c.op==4){
  Ogre::Matrix4 transform=Ogre::Matrix4::IDENTITY;transform[0][0]=c.seed%3+0.5f;transform[1][1]=-0.5f;transform[2][2]=2;transform[0][3]=c.seed%7;transform[1][3]=-3;transform[2][3]=1.5f;if(c.seed%5==0)transform[3][2]=0.125f;
  int mat=c.seed%2?-1:99;
  autotest::invoke<void(*)(CCollisionList*,CCollisionList*,const Ogre::Matrix4&,int),CCollisionList*,CCollisionList*,const Ogre::Matrix4&,int>(out,ours?&cnAppend:&coAppend,&p,&source,transform,mat);
 }else{
  static const Ogre::Vector3 starts[]={Ogre::Vector3(1,4,0),Ogre::Vector3(1,-4,0),Ogre::Vector3(3,0.5f,0),Ogre::Vector3(2,0.5f,2),Ogre::Vector3(-3,0.5f,0),Ogre::Vector3(1,0,0),Ogre::Vector3(1,4,3),Ogre::Vector3(0,0.5f,0)};
  Ogre::Vector3 start=starts[c.seed%8],end=start;end.y=c.seed%3==0?start.y:c.seed%3==1?-4:0.25f;
  if(c.seed%8==4){start=Ogre::Vector3(3,1,1);end=Ogre::Vector3(-3,1,1);}
  Ogre::Vector3 minimum(-10),maximum(10);if(c.seed%11==0){minimum=Ogre::Vector3(100);maximum=Ogre::Vector3(101);}
  // Subset indices must name existing mesh faces, including for empty meshes.
  std::vector<unsigned> faces;if(c.seed%9&&!p.m_IndicesA.empty()){faces.push_back(2);faces.push_back(0);if(c.seed%2)faces.push_back(1);}
  float radius=c.seed%4==0?0:c.seed%4==1?0.25f:c.seed%4==2?1:3;
  if(c.op==5)collisionInvoke<bool(*)(CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&>(out,ours?&cnRay:&coRay,&p,start,end,minimum,maximum,hit,normal,material,color,distance);
  if(c.op==6)collisionInvoke<bool(*)(CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&>(out,ours?&cnRaySubset:&coRaySubset,&p,faces,start,end,minimum,maximum,hit,normal,material,color,distance);
  if(c.op==7)collisionInvoke<bool(*)(CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),CCollisionList*,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&>(out,ours?&cnSphere:&coSphere,&p,start,end,minimum,maximum,radius,position,hit,normal,material,color,distance);
  if(c.op==8)collisionInvoke<bool(*)(CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&),CCollisionList*,const std::vector<unsigned>&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,float&>(out,ours?&cnSphereSubset:&coSphereSubset,&p,faces,start,end,minimum,maximum,radius,position,hit,normal,material,color,distance);
 }
 out.add(&hit,12);out.add(&normal,12);out.add(&position,12);out.add(&color,12);out.add(&material,4);out.add(&distance,4);meshState(out,p);meshState(out,source);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_collision_geometry){
 int failures=0;const uintptr_t functions[]={reinterpret_cast<uintptr_t>(&coOptimize),reinterpret_cast<uintptr_t>(&coNormals),reinterpret_cast<uintptr_t>(&coBounds),reinterpret_cast<uintptr_t>(&coPoint),reinterpret_cast<uintptr_t>(&coAppend),reinterpret_cast<uintptr_t>(&coRay),reinterpret_cast<uintptr_t>(&coRaySubset),reinterpret_cast<uintptr_t>(&coSphere),reinterpret_cast<uintptr_t>(&coSphereSubset)};
 for(unsigned op=0;op<9;++op){autotest::Coverage coverage("continuation_collision_geometry",functions[op]);unsigned hits=0;
  for(unsigned seed=0;seed<48;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;if(op>=3&&op!=4&&ok)hits+=a.capture.data[0]!=0;
   if(!ok)host->log("    geometry operation %u seed %u status %d/%d bytes %lu/%lu\n",op,seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
   TL_CHECK(failures,ok);if(!ok){for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    diff byte %u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}
  }coverage.report(host);if(op>=3&&op!=4){host->log("    geometry operation %u hits %u\n",op,hits);TL_CHECK(failures,hits>0&&hits<48);}
 }
 return failures;
}
