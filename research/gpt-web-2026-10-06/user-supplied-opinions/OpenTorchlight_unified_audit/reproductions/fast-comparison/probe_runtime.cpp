// Diagnostic of the existing capture helpers, not a game test.
#include "AutoTest.h"
#include <iostream>
#include <cstdlib>
namespace autotest {
char g_arena[kArenaSize];
size_t g_arenaUsed = 0;
Pool g_pool;
Outcome g_outcomes[2];
}
static bool equal(const autotest::Capture& a, const autotest::Capture& b) {
    return a.length == b.length && std::memcmp(a.data,b.data,a.length) == 0;
}
struct Padded { unsigned char tag; unsigned int value; };
int main() {
    autotest::Capture *a = new autotest::Capture, *b = new autotest::Capture;
    a->length=b->length=0;
    int* x=new int(7); int* y=new int(7);
    a->addPointer(x); b->addPointer(y);
    bool pointerCollision=equal(*a,*b);
    a->length=b->length=0;
    char* bytes=new char[autotest::Capture::kSize];
    std::memset(bytes,0,autotest::Capture::kSize);
    a->add(bytes,autotest::Capture::kSize); b->add(bytes,autotest::Capture::kSize);
    char afterA=1,afterB=2; a->add(&afterA,1); b->add(&afterB,1);
    bool truncated=equal(*a,*b);
    a->length=b->length=0;
    autotest::Value<Padded> p,q; std::memset(&p,0,sizeof(p)); std::memset(&q,0x55,sizeof(q));
    p.value.tag=q.value.tag=1; p.value.value=q.value.value=123;
    autotest::record(*a,p); autotest::record(*b,q);
    bool paddingDifference=!equal(*a,*b);
    std::cout << "{\"external_pointer_collision\":" << (pointerCollision?"true":"false")
              << ",\"capture_overflow_is_silently_ignored\":" << (truncated?"true":"false")
              << ",\"aggregate_padding_is_observed\":" << (paddingDifference?"true":"false")
              << ",\"aggregate_size\":" << sizeof(Padded) << "}\n";
    delete x;delete y;delete[] bytes;delete a;delete b;
    return pointerCollision && truncated && paddingDifference ? 0:1;
}
