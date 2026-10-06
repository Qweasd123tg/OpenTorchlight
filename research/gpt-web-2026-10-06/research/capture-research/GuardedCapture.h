#ifndef RESEARCH_GUARDED_CAPTURE_H
#define RESEARCH_GUARDED_CAPTURE_H
#include <stdint.h>
#include <stddef.h>
#include <cstring>
namespace capture_research {
struct Inputs {
    struct Region { uintptr_t start; size_t size; uint64_t id; } regions[64];
    size_t count; bool valid;
    Inputs():count(0),valid(true){}
    bool add(uint64_t id,const void* p,size_t size){
        uintptr_t a=(uintptr_t)p;
        if(!valid||!id||!p||!size||size>(~(uintptr_t)0)-a||count==64){valid=false;return false;}
        for(size_t i=0;i<count;++i){
            const Region& r=regions[i];
            if(id==r.id||(a<r.start+r.size&&r.start<a+size)){valid=false;return false;}
        }
        regions[count].start=a;regions[count].size=size;regions[count].id=id;++count;return true;
    }
};
struct Capture {
    enum { capacity=256*1024 };
    enum Error { OK, OVERFLOW, UNKNOWN_POINTER, INVALID_INPUTS };
    unsigned char bytes[capacity]; size_t length; Error error;
    Capture():length(0),error(OK){}
    bool add(const void* p,size_t n){
        if(error!=OK)return false;
        if(length>capacity||n>capacity-length){error=OVERFLOW;return false;}
        if(n)std::memcpy(bytes+length,p,n);
        length+=n;
        return true;
    }
    bool pointer(const void* p,const void* arena,size_t arenaSize,const Inputs& inputs){
        if(error!=OK)return false;
        if(!inputs.valid){error=INVALID_INPUTS;return false;}
        uint64_t tag=0,id=0,offset=0;
        if(p){
            uintptr_t a=(uintptr_t)p,b=(uintptr_t)arena;
            if(arena&&a>=b&&a-b<arenaSize){tag=1;offset=a-b;}
            else {
                bool found=false;
                for(size_t i=0;i<inputs.count;++i){
                    const Inputs::Region& r=inputs.regions[i];
                    if(a>=r.start&&a-r.start<r.size){tag=2;id=r.id;offset=a-r.start;found=true;break;}
                }
                if(!found){error=UNKNOWN_POINTER;return false;}
            }
        }
        // Serialize fields individually; no uninitialized struct padding.
        return add(&tag,sizeof(tag))&&add(&id,sizeof(id))&&add(&offset,sizeof(offset));
    }
};
enum Comparison { SAME, DIFFERENT, INCONCLUSIVE };
inline Comparison compare(const Capture& a,const Capture& b){
    if(a.error!=Capture::OK||b.error!=Capture::OK)return INCONCLUSIVE;
    return a.length==b.length&&!std::memcmp(a.bytes,b.bytes,a.length)?SAME:DIFFERENT;
}
}
#endif
