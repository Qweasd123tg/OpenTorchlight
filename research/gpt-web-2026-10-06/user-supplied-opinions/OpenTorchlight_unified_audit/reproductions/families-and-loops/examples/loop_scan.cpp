// Synthetic model of the paired induction variables and capacity fallback.
// This is not a recovered Torchlight function. No game inputs are accessed.
#include <stdint.h>
#include <cstdio>
struct Entry { uint64_t guid; };
struct List {
    Entry** data;
    uint32_t count;
    uint32_t capacity;
    Entry* at(uint32_t i) const { return i < capacity ? data[i] : data[0]; }
};
static Entry* raw_scan(const List& list, uint64_t wanted) {
    if (list.count != 0) {
        uint32_t i = 0;
        uint64_t byteOffset = 0;
        do {
            Entry* entry = i < list.capacity ? list.data[byteOffset / 8] : list.data[0];
            if (entry->guid == wanted) return entry;
            i = i + 1;
            byteOffset = byteOffset + 8;
        } while (i < list.count);
    }
    return 0;
}
static Entry* indexed_scan(const List& list, uint64_t wanted) {
    for (uint32_t i = 0; i < list.count; ++i) {
        Entry* entry = list.at(i);
        if (entry->guid == wanted) return entry;
    }
    return 0;
}
static Entry* unjustified_direct_scan(const List& list, uint64_t wanted) {
    for (uint32_t i = 0; i < list.count; ++i) {
        Entry* entry = list.data[i];
        if (entry->guid == wanted) return entry;
    }
    return 0;
}
int main() {
    if (sizeof(void*) != 8) return 3;
    Entry objects[19]; Entry* pointers[19];
    for (unsigned i = 0; i != 19; ++i) {objects[i].guid = i; pointers[i] = objects + i;}
    unsigned total=0, mismatch=0, unsafeMismatch=0, bounded=0, unsafeBounded=0;
    for (uint32_t n = 0; n != 19; ++n) {
        for (uint32_t capacity = 0; capacity != 19; ++capacity) {
            List list = {pointers,n,capacity};
            for (uint64_t guid = 0; guid != 20; ++guid) {
                ++total;
                Entry* a=raw_scan(list,guid);
                Entry* b=indexed_scan(list,guid);
                Entry* c=unjustified_direct_scan(list,guid);
                mismatch += a != b;
                unsafeMismatch += a != c;
                if (n<=capacity) {++bounded; unsafeBounded += a != c;}
            }
        }
    }
    List empty = {0,0,0};
    if (raw_scan(empty,1) || indexed_scan(empty,1)) return 4;
    std::printf("{\"cases\":%u,\"indexed_mismatches\":%u,\"direct_mismatches\":%u,\"bounded_cases\":%u,\"direct_bounded_mismatches\":%u}\n",total,mismatch,unsafeMismatch,bounded,unsafeBounded);
    return mismatch ? 1 : 0;
}
