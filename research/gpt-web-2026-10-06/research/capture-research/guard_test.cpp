#include "GuardedCapture.h"
#include <cstdio>
#include <cstdlib>
using namespace capture_research;
static unsigned char arena[400000],aobj[32],bobj[32],relocated[32];
static Capture a,b;static int checks=0;
#define CHECK(x) do{++checks;if(!(x)){printf("FAIL line %d\n",__LINE__);return 1;}}while(0)
static void clear(){a.length=b.length=0;a.error=b.error=Capture::OK;}
int main(){
 Inputs in;CHECK(in.add(101,aobj,sizeof(aobj)));CHECK(in.add(202,bobj,sizeof(bobj)));
 a.pointer(aobj,arena,sizeof(arena),in);b.pointer(bobj,arena,sizeof(arena),in);CHECK(compare(a,b)==DIFFERENT);
 clear();a.pointer(aobj+1,arena,sizeof(arena),in);b.pointer(aobj+2,arena,sizeof(arena),in);CHECK(compare(a,b)==DIFFERENT);
 clear();a.pointer(aobj+2,arena,sizeof(arena),in);b.pointer(aobj+2,arena,sizeof(arena),in);CHECK(compare(a,b)==SAME);
 clear();a.pointer(0,arena,sizeof(arena),in);b.pointer(arena,arena,sizeof(arena),in);CHECK(compare(a,b)==DIFFERENT);
 clear();a.pointer(arena+3,arena,sizeof(arena),in);b.pointer(arena+4,arena,sizeof(arena),in);CHECK(compare(a,b)==DIFFERENT);
 clear();a.pointer(relocated,arena,sizeof(arena),in);b.pointer(relocated,arena,sizeof(arena),in);CHECK(compare(a,b)==INCONCLUSIVE);
 clear();a.add(arena,300001);b.add(arena,300001);CHECK(compare(a,b)==INCONCLUSIVE);
 clear();CHECK(a.add(arena,Capture::capacity));CHECK(!a.add(aobj,1));CHECK(a.error==Capture::OVERFLOW);
 clear();a.add(arena,1);CHECK(!a.add(arena,(size_t)-1));CHECK(a.error==Capture::OVERFLOW);
 clear();CHECK(a.add(0,0));CHECK(compare(a,b)==SAME);
 Inputs moved;CHECK(moved.add(101,relocated,sizeof(relocated)));
 a.pointer(aobj+5,arena,sizeof(arena),in);b.pointer(relocated+5,arena,sizeof(arena),moved);CHECK(compare(a,b)==SAME);
 Inputs conflict;CHECK(conflict.add(1,aobj,32));CHECK(!conflict.add(2,aobj+1,1));
 clear();a.pointer(aobj,arena,sizeof(arena),conflict);CHECK(compare(a,b)==INCONCLUSIVE);
 Inputs duplicate;CHECK(duplicate.add(1,aobj,32));CHECK(!duplicate.add(1,bobj,32));
 clear();a.length=Capture::capacity+1;CHECK(!a.add(0,0));
 printf("%d guarded-observation assertions PASS\n",checks);return 0;
}
