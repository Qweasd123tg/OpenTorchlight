// Synthetic ABI probes using the archive's real Ogre 1.6.5 math headers.
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <stdint.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <new>
struct Mixed { uint64_t integer; double real; };
struct Big { double a,b,c; };
struct Small {
    uint64_t value;
    Small(uint64_t n):value(n){}
    Small(const Small& x):value(x.value){}
    ~Small(){}
};
typedef std::wstring Text;
extern "C" {
__attribute__((noinline)) Ogre::Vector3 get_v3(const Ogre::Vector3* p){return *p;}
__attribute__((noinline)) Ogre::Quaternion get_quat(const Ogre::Quaternion* p){return *p;}
__attribute__((noinline)) Mixed get_mixed(const Mixed* p){return *p;}
__attribute__((noinline)) Big get_big(const Big* p){return *p;}
__attribute__((noinline)) Small get_small(const Small* p){return *p;}
__attribute__((noinline)) Text get_text(const Text* p){return *p;}
unsigned char capture[64];
void capture_return(void(*fn)(),const void* src,void* dst,int hidden);
// Argument probes are compiled to assembly for inspection; the pointer destination
// is volatile so every field is represented. They are not an ABI parser.
volatile float argument_float[4];
volatile uint64_t argument_integer[2];
__attribute__((noinline)) void take_v3(uint64_t first,Ogre::Vector3 value,uint64_t last){
 argument_integer[0]=first;argument_integer[1]=last;
 argument_float[0]=value.x;argument_float[1]=value.y;argument_float[2]=value.z;
}
}
static bool eq(const void* a,const void* b,size_t n){return std::memcmp(a,b,n)==0;}
union Storage{long double align;unsigned char bytes[128];};
int main(){
 int fail=0;
 Ogre::Vector3 v(1.25f,-2.5f,6.75f); capture_return((void(*)())get_v3,&v,0,0);
 bool v_ok=eq(capture+16,&v.x,8)&&eq(capture+32,&v.z,4);fail+=!v_ok;
 Ogre::Quaternion q(1.25f,-2.5f,6.75f,8.0f);capture_return((void(*)())get_quat,&q,0,0);
 bool q_ok=eq(capture+16,&q.w,8)&&eq(capture+32,&q.y,8);fail+=!q_ok;
 Mixed m={UINT64_C(0x123456789abcdef0),-7.25};capture_return((void(*)())get_mixed,&m,0,0);
 bool m_ok=eq(capture,&m.integer,8)&&eq(capture+16,&m.real,8);fail+=!m_ok;
 Big b={1.25,-2.5,6.75};Storage sb;capture_return((void(*)())get_big,&b,sb.bytes,1);
 void* ptr=sb.bytes;bool b_ok=eq(sb.bytes,&b,sizeof(b))&&eq(capture,&ptr,8);fail+=!b_ok;
 Small s(UINT64_C(0x123456789abcdef0));Storage ss;capture_return((void(*)())get_small,&s,ss.bytes,1);
 ptr=ss.bytes;Small* sr=reinterpret_cast<Small*>(ss.bytes);
 bool s_ok=sr->value==s.value&&eq(capture,&ptr,8);fail+=!s_ok;sr->~Small();
 Text t=L"ABI";Storage st;capture_return((void(*)())get_text,&t,st.bytes,1);
 ptr=st.bytes;Text* tr=reinterpret_cast<Text*>(st.bytes);
 bool t_ok=*tr==t&&eq(capture,&ptr,8);fail+=!t_ok;tr->~Text();
 std::printf("{\"scope\":\"six synthetic return probes; real archive Ogre headers; system compiler\",\"types\":[");
 std::printf("{\"name\":\"Ogre::Vector3\",\"size\":%lu,\"observed\":\"XMM0 low 64 + XMM1 low 32\",\"pass\":%s},",(unsigned long)sizeof(v),v_ok?"true":"false");
 std::printf("{\"name\":\"Ogre::Quaternion\",\"size\":%lu,\"observed\":\"XMM0 low 64 + XMM1 low 64\",\"pass\":%s},",(unsigned long)sizeof(q),q_ok?"true":"false");
 std::printf("{\"name\":\"Mixed\",\"size\":%lu,\"observed\":\"RAX + XMM0 low 64\",\"pass\":%s},",(unsigned long)sizeof(m),m_ok?"true":"false");
 std::printf("{\"name\":\"Big\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s},",(unsigned long)sizeof(b),b_ok?"true":"false");
 std::printf("{\"name\":\"Small nontrivial\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s},",(unsigned long)sizeof(s),s_ok?"true":"false");
 std::printf("{\"name\":\"old ABI std::wstring\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s}],\"failures\":%d}\n",(unsigned long)sizeof(t),t_ok?"true":"false",fail);
 return fail?1:0;
}
