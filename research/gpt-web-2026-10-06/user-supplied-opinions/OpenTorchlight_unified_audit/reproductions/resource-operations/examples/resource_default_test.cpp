// SYNTHETIC CHECK ONLY: preserves a known current-value default in three reads.
// No claim about the real CDataGroup implementation or CEffect object layout.
#include <iostream>
#include <cwchar>
struct Group {
    int states[3]; // 0 absent, 1 false, 2 true
    bool GetDataValue(const wchar_t* key, bool fallback) const {
        int i=std::wcscmp(key,L"SAVE")==0?0:std::wcscmp(key,L"USEOWNERLEVEL")==0?1:2;
        return states[i]==0?fallback:states[i]==2;
    }
};
struct State {
    bool field_33,field_36,field_31;
    void raw(const Group* param_1) {
        bool c=field_33;c=param_1->GetDataValue(L"SAVE",c);field_33=c;
        c=field_36;c=param_1->GetDataValue(L"USEOWNERLEVEL",c);field_36=c;
        c=field_31;c=param_1->GetDataValue(L"EXCLUSIVE",c);field_31=c;
    }
    void reconstructed(const Group* param_1) {
        field_33 = param_1->GetDataValue(L"SAVE", field_33);
        field_36 = param_1->GetDataValue(L"USEOWNERLEVEL", field_36);
        field_31 = param_1->GetDataValue(L"EXCLUSIVE", field_31);
    }
    void mutant(const Group* p) {
        field_33=p->GetDataValue(L"SAVE",false);
        field_36=p->GetDataValue(L"USEOWNERLEVEL",false);
        field_31=p->GetDataValue(L"EXCLUSIVE",false);
    }
    bool same(const State& x) const {return field_33==x.field_33&&field_36==x.field_36&&field_31==x.field_31;}
};
int main(){
    int cases=0,errors=0,mutant_errors=0;
    for(int init=0;init<8;++init) for(int config=0;config<27;++config){
        Group g;int x=config;for(int i=0;i<3;++i){g.states[i]=x%3;x/=3;}
        State a={(init&1)!=0,(init&2)!=0,(init&4)!=0};State b=a,c=a;
        a.raw(&g);b.reconstructed(&g);c.mutant(&g);++cases;
        if(!a.same(b))++errors;if(!a.same(c))++mutant_errors;
    }
    std::cout<<"{\"cases\":"<<cases<<",\"preserved_default_mismatches\":"<<errors
             <<",\"forced_false_mismatches\":"<<mutant_errors<<",\"scope\":\"synthetic bool lookup model\"}\n";
    return errors||mutant_errors==0;
}
