#include <Ogre.h>
#include <cstdlib>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#include "ParticlePropertyConversions.h"

TL_ORIGINAL(ParticleUniverse::DynamicAttribute*, dynamicOldCreate, (const float*,unsigned), "_Z19getDynPropFromArrayPKfj")
TL_ORIGINAL(float*, dynamicInspect, (ParticleUniverse::DynamicAttribute*,unsigned&), "_Z19getArrayFromDynPropPN16ParticleUniverse16DynamicAttributeERj")

namespace {
struct Case { unsigned seed, negative; };
void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);
    float values[64];
    const unsigned counts[]={0,1,2,3,4,5,6,7,9,10,13,16};
    unsigned type=c.seed%9;
    unsigned count=counts[c.seed/9%12];
    values[0]=type==8 ? -1.0f : float(type);
    for (unsigned i=1;i<64;++i) values[i]=float(i-1)*.125f;
    if (type==2 || type==3) {
        for (unsigned i=1;i+1<64;i+=2) {
            values[i]=float((i-1)/2)*2.0f;
            values[i+1]=.5f+float(i)*.125f;
        }
    }
    if (type==4 || type==5) {
        for (unsigned i=1;i+2<64;i+=3) {
            values[i]=float((i-1)/3)*2.0f;
            values[i+1]=.5f+float(i)*.125f;
            values[i+2]=values[i+1]+.75f;
        }
    }
    typedef ParticleUniverse::DynamicAttribute* (*F)(const float*,unsigned);
    F f=ours?getDynPropFromArray:dynamicOldCreate;
    ParticleUniverse::DynamicAttribute* attribute=NULL;
    if (autotest::beginInvocation(out,f)) {attribute=f(values,count);out.callCompleted=1;}
    unsigned valid=attribute!=NULL;out.add(&valid,sizeof valid);
    if (!attribute) {out.issue=autotest::Capture::InvalidReport;return;}
    unsigned actualType=attribute->getType();out.add(&actualType,sizeof actualType);
    unsigned flattenedCount=0;
    float* flattened=dynamicInspect(attribute,flattenedCount);
    if (flattenedCount>256 || (flattenedCount&&!flattened)) {out.issue=autotest::Capture::InvalidReport;return;}
    out.add(&flattenedCount,sizeof flattenedCount);
    out.add(flattened,flattenedCount*sizeof(float));
    std::srand(71);
    for (unsigned i=0;i<13;++i) {
        float value=attribute->getValue(NULL,float(i)/12.0f);
        if (ours&&c.negative&&i==0) value+=1.0f;
        out.add(&value,sizeof value);
    }
    delete attribute;
}
void before(void*p,autotest::Capture&c) {side(p,c,false);}
void after(void*p,autotest::Capture&c) {side(p,c,true);}
int worker(const tlhybrid_host*host)
{
    int failures=0;autotest::Coverage coverage("particle_dynamic_from_array",0xa30da0);
    for (unsigned i=0;i<108;++i) {
        Case c={i,0};autotest::Outcome a,b;
        autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        int bad=coverage.observe(host,a,b);TL_CHECK(failures,!bad);
        if (bad) {host->log("    dynamic seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return failures;}
    }
    coverage.report(host);Case c={58,1};autotest::Outcome a,b;
    autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);
    return failures;
}
}
TL_TEST(particle_dynamic_from_array) {return systems_fixture::isolated(worker,host);}
