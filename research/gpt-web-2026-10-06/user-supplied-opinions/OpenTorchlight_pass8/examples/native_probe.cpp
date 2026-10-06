// Test-only ABI views and readable candidates. No original game classes are replaced.
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <stdint.h>
#include <cassert>
extern "C" void ref_capture(unsigned char*);
extern "C" void generated_capture(unsigned char*);
extern "C" bool ref_keyheld(const unsigned char*,unsigned);
extern "C" int ref_getodds(void*,int);
extern "C" void ref_setodds(void*,int,int);
extern "C" void ref_removechoice(void*,unsigned);
static uint32_t seed=0x93b28719u;
static uint32_t random32(){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
static void fill(void* v,size_t n){unsigned char*p=(unsigned char*)v;for(size_t i=0;i<n;++i)p[i]=(unsigned char)random32();}
template<class T> struct ListView {
    T* data; unsigned count,capacity,grow;
    T& at(unsigned i) {return data[i<capacity?i:0];}
    void removeAt(unsigned i){if(i<count){--count;data[i]=data[count];}}
};
struct State {
    unsigned char base[16];
    ListView<int> choices;
    ListView<float> odds,computed;
    unsigned type;float decay;unsigned char dirty;
};
struct Fixture {State s;int choices[8];float odds[8],computed[8];};
static void bind(Fixture&x){x.s.choices.data=x.choices;x.s.odds.data=x.odds;x.s.computed.data=x.computed;}
static void make(Fixture&f,bool wellformed){
    fill(&f,sizeof(f));bind(f);
    ListView<int>& c=f.s.choices;ListView<float>&o=f.s.odds;ListView<float>&p=f.s.computed;
    c.count=random32()%9;c.capacity=wellformed?c.count+random32()%(9-c.count):random32()%9;
    o.count=random32()%9;o.capacity=wellformed?o.count+random32()%(9-o.count):random32()%9;
    p.count=random32()%9;p.capacity=wellformed?p.count+random32()%(9-p.count):random32()%9;
    f.s.dirty=(unsigned char)(random32()%2);
    for(unsigned i=0;i<8;i++){f.choices[i]=(int)(random32()%9)-4;f.odds[i]=((int)(random32()%200001)-100000)*0.125f;}
}
static bool equal(const Fixture&a,const Fixture&b){
    unsigned char x[sizeof(State)],y[sizeof(State)];std::memcpy(x,&a.s,sizeof(x));std::memcpy(y,&b.s,sizeof(y));
    const size_t ptrs[]={offsetof(State,choices),offsetof(State,odds),offsetof(State,computed)};
    for(unsigned i=0;i<3;i++){std::memset(x+ptrs[i],0,sizeof(void*));std::memset(y+ptrs[i],0,sizeof(void*));}
    return std::memcmp(x,y,sizeof(x))==0 && std::memcmp(a.choices,b.choices,sizeof(a.choices))==0 &&
        std::memcmp(a.odds,b.odds,sizeof(a.odds))==0 && std::memcmp(a.computed,b.computed,sizeof(a.computed))==0;
}
static void duplicate(Fixture&dst,const Fixture&src){std::memcpy(&dst,&src,sizeof(dst));bind(dst);}
// These three candidates were written from the listing; only generated_capture is automatic.
static int candidate_get(State&s,int i){return (int)s.odds.at((unsigned)i);}
static void candidate_set(State&s,int choice,int odds){
    for(unsigned i=0;i<s.choices.count;i++)if(s.choices.at(i)==choice){s.odds.at(i)=(float)odds;s.dirty=1;return;}
}
static void candidate_remove(State&s,unsigned choice){
    for(unsigned i=0;i<s.choices.count;i++)if((unsigned)s.choices.at(i)==choice){
        s.odds.removeAt(i);s.choices.removeAt(i);s.computed.removeAt(i);s.dirty=1;return;
    }
}
int main(){
    if(sizeof(ListView<int>)!=24 || offsetof(State,choices)!=0x10 || offsetof(State,odds)!=0x28 ||
       offsetof(State,computed)!=0x40 || offsetof(State,dirty)!=0x60) return 2;
    unsigned capture_bad=0,capture_mutant=0,key_bad=0,key_mutant=0,get_bad=0,set_bad=0,remove_bad=0,set_mutant=0;
    unsigned char a[4096],b[4096],c[4096];
    for(unsigned t=0;t<4096;t++){
        fill(a,sizeof(a));std::memcpy(b,a,sizeof(a));std::memcpy(c,a,sizeof(a));
        ref_capture(a);generated_capture(b);generated_capture(c);std::memset(c+0x911,0,512);
        capture_bad+=std::memcmp(a,b,sizeof(a))!=0;capture_mutant+=std::memcmp(a,c,sizeof(a))!=0;
    }
    std::memset(a,0,sizeof(a));
    for(unsigned key=0;key<512;key++)for(unsigned held=0;held<4;held++)for(unsigned pressed=0;pressed<4;pressed++){
        a[0x211+key]=held;a[0x11+key]=pressed;
        bool original=ref_keyheld(a,key),expected=held==1||pressed==1;
        key_bad+=original!=expected;key_mutant+=original!=(held!=0||pressed!=0);
    }
    const unsigned random_cases=20000;unsigned wellformed_cases=0;
    for(unsigned t=0;t<random_cases;t++){
        Fixture a,b,c;bool wellformed=(t%2)==0;wellformed_cases+=wellformed;
        make(a,wellformed);duplicate(b,a);duplicate(c,a);
        int idx=(int)(random32()%13)-2;
        get_bad+=ref_getodds(&a.s,idx)!=candidate_get(b.s,idx);
        int choice=(int)(random32()%13)-6;int odds=(int)(random32()%20000001)-10000000;
        ref_setodds(&a.s,choice,odds);candidate_set(b.s,choice,odds);set_bad+=!equal(a,b);
        // Mutant: mark dirty even when no matching choice is found.
        candidate_set(c.s,choice,odds);c.s.dirty=1;set_mutant+=!equal(a,c);
        make(a,wellformed);duplicate(b,a);
        unsigned remove=(unsigned)((int)(random32()%13)-6);
        ref_removechoice(&a.s,remove);candidate_remove(b.s,remove);remove_bad+=!equal(a,b);
    }
    std::printf("{\"reference\":\"native reassembly of archival text; not independently verified ELF\","
        "\"capture_cases\":4096,\"capture_mismatches\":%u,\"wrong_held_clear_mutant\":%u,"
        "\"keyheld_cases\":8192,\"keyheld_mismatches\":%u,\"truthiness_mutant\":%u,"
        "\"randomizer_cases_per_method\":%u,\"count_le_capacity_cases_per_method\":%u,"
        "\"getodds_mismatches\":%u,\"setodds_mismatches\":%u,\"removechoice_mismatches\":%u,"
        "\"always_dirty_mutant\":%u,\"comparison\":\"return values and entire object/backing arrays with pointer identity normalized\"}\n",
        capture_bad,capture_mutant,key_bad,key_mutant,random_cases,wellformed_cases,get_bad,set_bad,remove_bad,set_mutant);
    return capture_bad||key_bad||get_bad||set_bad||remove_bad;
}
