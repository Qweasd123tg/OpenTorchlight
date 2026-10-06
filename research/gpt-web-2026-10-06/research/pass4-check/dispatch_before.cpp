#include <cstdio>
struct CBase { virtual int step(){return 11;} }; struct CDerived:CBase {int step(){return 22;}};
int probe(CBase* object){return object->CBase::step();}
int main(){CDerived d;printf("%d\n",probe(&d));}