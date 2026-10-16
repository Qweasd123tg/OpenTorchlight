#ifndef PARENT_PAIRS_H
#define PARENT_PAIRS_H
#include "AutoTest.h"
namespace parentpairs {
struct Case { unsigned seed; };
inline int run(const tlhybrid_host* h,const char* name,uintptr_t address,unsigned count,autotest::Body a,autotest::Body b)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={i};
        autotest::Outcome& x=autotest::g_outcomes[0];autotest::Outcome& y=autotest::g_outcomes[1];
        autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
        if(coverage.observe(h,x,y)) {
            h->log("    %s seed %u issue %u/%u status %d/%d completed %u/%u\n",name,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,x.capture.callCompleted,y.capture.callCompleted);
            coverage.report(h);return 1;
        }
    }
    coverage.report(h);return coverage.completed!=count||coverage.different||coverage.missing;
}
template<class T> void scalar(autotest::Capture& c,const T& v){c.add(&v,sizeof(v));}
}
#endif
