#include <stdio.h>
#include <string.h>
struct COver {
    virtual int f(int);
    virtual int f(long);
};
// Deliberately NO definitions of either virtual f().
struct Rep { long long ptr, adjustment; };
int main() {
    int (COver::*pi)(int) = &COver::f;
    int (COver::*pl)(long) = &COver::f;
    typedef char rep_size_check[(sizeof(pi) == sizeof(Rep) && sizeof(pi) == 16) ? 1 : -1];
    Rep ri, rl;
    memcpy(&ri, &pi, sizeof(ri));
    memcpy(&rl, &pl, sizeof(rl));
    printf("%lld %lld %lld %lld\n", ri.ptr, ri.adjustment, rl.ptr, rl.adjustment);
}
