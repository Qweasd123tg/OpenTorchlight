#include <stdio.h>
struct CBase { virtual int step() { return 11; } };
struct CDerived : CBase { int step() { return 22; } };
struct CWrapper { int probe(CBase*); };
int CWrapper::probe(CBase* p) { return p->CBase::step(); }
int main() { CDerived d; CWrapper w; printf("%d\n", w.probe(&d)); }
