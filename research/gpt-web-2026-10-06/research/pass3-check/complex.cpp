extern void sink(const char*);
struct A { virtual ~A(){} virtual int f(int x){return x+1;} };
struct B:A { ~B(){} int f(int x){return x*3;} };
extern "C" A* create(){return new B;}
extern "C" int recursive(int x){if(x<2)return x;return recursive(x-1)+recursive(x-2);}
extern "C" int probe(A* a,int x){try{sink("longish literal for relocation comparison");return a->f(x);}catch(int){return -1;}}
