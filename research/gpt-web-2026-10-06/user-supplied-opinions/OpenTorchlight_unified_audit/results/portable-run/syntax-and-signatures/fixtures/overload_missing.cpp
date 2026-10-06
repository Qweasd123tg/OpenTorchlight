#include <stdio.h>
struct CProbe
{
 int read(int);
};
int CProbe::read(int) { return 11; }
int main(){ CProbe p; printf("%d\n", p.read(1.5)); }
