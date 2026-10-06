#include <cstdio>
#include <cstring>
#include <cstddef>
struct Left { virtual int left(); };
struct Right { virtual int f(int); virtual int f(long); };
struct Derived:Left,Right { virtual int f(int); };
template<class T> void show(const char* name,T p){
 std::ptrdiff_t repr[2];
 if(sizeof(p)!=sizeof(repr)){puts("unsupported member pointer representation");return;}
 std::memcpy(repr,&p,sizeof(p));
 std::printf("%s pointer=%ld adjustment=%ld slot_if_virtual=%ld\n",name,(long)repr[0],(long)repr[1],(long)((repr[0]-1)/(std::ptrdiff_t)sizeof(void*)));
}
int main(){
 int(Right::*r)(int)=&Right::f;int(Derived::*d)(int)=r;
 int(Right::*rl)(long)=&Right::f;int(Derived::*dl)(long)=rl;
 int(Derived::*direct)(int)=&Derived::f;
 show("Right::f(int)",r);show("Right::f(int) viewed as Derived",d);
 show("Right::f(long) viewed as Derived",dl);show("Derived::f(int)",direct);
 return 0;
}
