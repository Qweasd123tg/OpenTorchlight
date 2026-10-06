extern "C" unsigned helper(unsigned) __attribute__((noinline));
extern "C" unsigned helper(unsigned x) { return x*3u; }
extern "C" unsigned probe(unsigned* p, unsigned x) { unsigned a = *p; return a + helper(x) + *p; }
