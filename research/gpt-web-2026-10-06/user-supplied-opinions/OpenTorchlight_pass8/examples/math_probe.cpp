#include <OgreVector3.h>
#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fenv.h>
#include <cerrno>
// Compile with -ffp-contract=off; no fast-math. The original compiler must be tested separately.
static uint32_t state=0x731b4251u;
static uint32_t next(){state^=state<<13;state^=state>>17;state^=state<<5;return state;}
static float fbits(uint32_t u){float f;std::memcpy(&f,&u,4);return f;}
static uint32_t bits(float f){uint32_t u;std::memcpy(&u,&f,4);return u;}
__attribute__((noinline)) float raw_sqr(float x,float y,float z){return x*x+y*y+z*z;}
__attribute__((noinline)) float ogre_sqr(float x,float y,float z){return Ogre::Vector3(x,y,z).squaredLength();}
__attribute__((noinline)) float reassociated(float a,float b,float c){return a+(b+c);}
__attribute__((noinline)) float ordered(float a,float b,float c){return (a+b)+c;}
__attribute__((noinline)) float raw_norm(Ogre::Vector3& v){
 float len=std::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
 if(len>1e-08){float inv=1.0/len;v.x*=inv;v.y*=inv;v.z*=inv;}
 return len;
}
__attribute__((noinline)) float ogre_norm(Ogre::Vector3& v){return v.normalise();}
__attribute__((noinline)) float wrong_norm(Ogre::Vector3& v){
 float len=std::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
 if(len>0.0f){float inv=1.0/len;v.x*=inv;v.y*=inv;v.z*=inv;}
 return len;
}
struct Result{uint32_t values[4];int flags,error;};
static Result eval(float(*fn)(Ogre::Vector3&),Ogre::Vector3 v){
 Result r;errno=0;::feclearexcept(FE_ALL_EXCEPT);
 float f=fn(v);r.flags=::fetestexcept(FE_ALL_EXCEPT);r.error=errno;
 r.values[0]=bits(f);r.values[1]=bits(v.x);r.values[2]=bits(v.y);r.values[3]=bits(v.z);return r;
}
static bool same(const Result&a,const Result&b){
 return std::memcmp(a.values,b.values,sizeof(a.values))==0&&a.flags==b.flags&&a.error==b.error;
}
int main(){
 const uint32_t specials[]={0,0x80000000u,0x3f800000u,0xbf800000u,1,0x007fffffu,0x00800000u,0x7f7fffffu,
 0xff7fffffu,0x7f800000u,0xff800000u,0x7fc01234u,0xffc01234u,0x7f800001u};
 int total=0,sqr_fail=0,norm_fail=0,wrong_fail=0;
 for(int i=0;i<12000;++i){
  float a,b,c;
  if(i<2744){a=fbits(specials[(i/196)%14]);b=fbits(specials[(i/14)%14]);c=fbits(specials[i%14]);}
  else{a=fbits(next());b=fbits(next());c=fbits(next());}
  errno=0;::feclearexcept(FE_ALL_EXCEPT);float f=raw_sqr(a,b,c);
  int e=errno,fl=::fetestexcept(FE_ALL_EXCEPT);uint32_t fb=bits(f);
  errno=0;::feclearexcept(FE_ALL_EXCEPT);float g=ogre_sqr(a,b,c);
  int ge=errno,gfl=::fetestexcept(FE_ALL_EXCEPT);uint32_t gb=bits(g);
  sqr_fail+=(fb!=gb||e!=ge||fl!=gfl);
  Ogre::Vector3 v(a,b,c);Result r=eval(raw_norm,v),s=eval(ogre_norm,v),w=eval(wrong_norm,v);
  norm_fail+=!same(r,s);wrong_fail+=!same(r,w);++total;
 }
 float aa=ordered(1e20f,-1e20f,1.0f),bb=reassociated(1e20f,-1e20f,1.0f);
 std::printf("{\"cases\":%d,\"special_bit_pattern_triples\":2744,\"squared_length_mismatches\":%d,\"normalise_mismatches\":%d,\"zero_only_guard_mutant_mismatches\":%d,\"reassociation_counterexample\":{\"left\":%.9g,\"right\":%.9g},\"observed\":\"result bits, vector component bits, FP flags, errno; current default environment\"}\n",total,sqr_fail,norm_fail,wrong_fail,aa,bb);
 return (sqr_fail||norm_fail||!wrong_fail||aa==bb)?1:0;
}
