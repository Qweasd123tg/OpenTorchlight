#include "AutoTest.h"
#include <cstdio>
namespace autotest { char g_arena[kArenaSize]; size_t g_arenaUsed=0; }
static autotest::Capture a,b;
static char buffer[autotest::Capture::kSize];
static int x,y;
int main(){
 a.length=b.length=0;a.addPointer(&x);b.addPointer(&y);
 bool same=a.length==b.length&&!memcmp(a.data,b.data,a.length);
 printf("different_external_pointers_equal=%d\n",same);
 a.length=b.length=0;a.add(buffer,sizeof(buffer));b.add(buffer,sizeof(buffer));
 const char X='X',Y='Y';a.add(&X,1);b.add(&Y,1);
 bool truncated=a.length==b.length&&!memcmp(a.data,b.data,a.length);
 printf("different_suffix_after_capacity_equal=%d length=%zu\n",truncated,a.length);
 return !(same&&truncated);
}
