// Synthetic state-machine tests: lazy strings and deterministic allocation failures.
// Not tests of any original Torchlight method.
#include <string>
#include <vector>
#include <cstdio>
#include <stdexcept>
#include <new>
#include <cstring>
struct Provider{
    unsigned encoded,index,calls;
    Provider(unsigned e):encoded(e),index(0),calls(0){}
    std::string fetch(){unsigned digit=(encoded>>(2*index++))&3u;calls++;
        if(digit==3)throw std::runtime_error("unavailable");
        return digit==0?"":digit==1?"A":"B";}
};
struct Cache {
    bool constructed;std::string value;
    Cache():constructed(false){}
    std::string low_level(Provider&p){if(!constructed){value="";constructed=true;}
        if(value.empty())value=p.fetch();return value;}
    std::string recovered(Provider&p){ // models a persistent local static std::string
        if(value.empty())value=p.fetch();return value;}
    std::string once_mutant(Provider&p){if(!constructed){value=p.fetch();constructed=true;}return value;}
};
static std::string invoke(Cache&c,Provider&p,int which){
    try{return std::string("ok:")+(which==0?c.low_level(p):which==1?c.recovered(p):c.once_mutant(p));}
    catch(const std::exception&){return "throw";}
}
struct Allocator {
    unsigned next,fail_at,live;std::vector<int>trace;
    Allocator(unsigned f):next(0),fail_at(f),live(0){}
    int acquire(){unsigned id=++next;trace.push_back(100+(int)id);
        if(id==fail_at){trace.push_back(-(int)id);throw std::bad_alloc();}live++;return id;}
    void release(int id){trace.push_back(200+id);live--;}
};
struct Owned {Allocator&a;int id;Owned(Allocator&x):a(x),id(x.acquire()){}~Owned(){a.release(id);}
private:Owned(const Owned&);Owned&operator=(const Owned&);};
static int cleanup_reference(Allocator&a){
    int ids[4]={0,0,0,0};unsigned made=0;int result;
    try{for(unsigned i=0;i<4;i++){ids[i]=a.acquire();made++;}a.trace.push_back(999);result=7;}
    catch(const std::bad_alloc&){result=-1;}
    while(made)a.release(ids[--made]);return result;
}
static int raii_candidate(Allocator&a){
    try{Owned one(a),two(a),three(a),four(a);a.trace.push_back(999);return 7;}
    catch(const std::bad_alloc&){return -1;}
}
static int leaking_mutant(Allocator&a){
    int ids[4]={0,0,0,0};unsigned made=0;int result;
    try{for(unsigned i=0;i<4;i++){ids[i]=a.acquire();made++;}a.trace.push_back(999);result=7;}
    catch(const std::bad_alloc&){result=-1;}
    // Deliberate bug: first acquired resource is leaked on failure after its creation.
    while(made){--made;if(made==0&&result==-1)break;a.release(ids[made]);}return result;
}
int main(){
    unsigned sequence_bad=0,mutant_bad=0;
    for(unsigned encoded=0;encoded<256;encoded++){
        Provider a(encoded),b(encoded),c(encoded);Cache x,y,z;bool bad=false,mut=false;
        for(unsigned call=0;call<4;call++){
            std::string r=invoke(x,a,0),s=invoke(y,b,1),t=invoke(z,c,2);
            bad|=r!=s||a.calls!=b.calls;mut|=r!=t||a.calls!=c.calls;
        }
        sequence_bad+=bad;mutant_bad+=mut;
    }
    unsigned failure_bad=0,leak_detected=0,return_only_detected=0;
    for(unsigned fail=0;fail<=4;fail++){
        Allocator a(fail),b(fail),c(fail);int r=cleanup_reference(a),s=raii_candidate(b),t=leaking_mutant(c);
        failure_bad+=r!=s||a.trace!=b.trace||a.live!=b.live;
        leak_detected+=r!=t||a.trace!=c.trace||a.live!=c.live;return_only_detected+=r!=t;
    }
    std::printf("{\"scope\":\"synthetic lifecycle model only\",\"lazy_sequences\":256,\"calls_per_sequence\":4,"
       "\"recovered_cache_mismatches\":%u,\"once_initialization_mutant_sequences\":%u,"
       "\"failure_injection_cases\":5,\"raii_trace_mismatches\":%u,\"leak_mutant_cases_detected\":%u,"
       "\"leak_mutant_cases_detected_by_return_only\":%u}\n",sequence_bad,mutant_bad,failure_bad,leak_detected,return_only_detected);
    return sequence_bad||failure_bad;
}
