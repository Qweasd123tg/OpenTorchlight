#include <cstdio>
extern "C" int probe(unsigned,unsigned); extern "C" int outside_A(unsigned,unsigned){return 22;} extern "C" int outside_B(unsigned,unsigned){return 33;} int main(){std::printf("%d %d %d",probe(0,0),probe(1,0),probe(2,0));}
