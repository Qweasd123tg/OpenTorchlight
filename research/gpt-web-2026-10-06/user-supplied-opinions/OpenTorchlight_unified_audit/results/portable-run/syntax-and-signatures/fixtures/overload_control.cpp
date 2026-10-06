#include <stdio.h>
struct CProbe { int read(int); int read(double); };
int CProbe::read(int) { return 11; }
int CProbe::read(double) { return 22; }
int main(){ CProbe p; printf("%d\n", p.read(1.5)); }
