#include <stdio.h>
struct CProbe { int x; int get() const; };
int CProbe::get()
{
    return x;
}
