#include <Ogre.h>
#include "AutoTest.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleDynamicAttribute.h"
TL_TEST(particle_dynamic_sdk_owners)
{
    int failures=0;
    using namespace ParticleUniverse;
    DynamicAttributeHelper helper;
    for(unsigned i=0;i<64;++i){
        float x=(int(i)-31)*.125f,y=x+1.5f,time=(i%9)*.125f;
        DynamicAttributeFixed*fixed=new DynamicAttributeFixed;
        fixed->setValue(x);
        TL_CHECK(failures,fixed->getType()==DynamicAttribute::DAT_FIXED);
        TL_CHECK(failures,fixed->getValue(NULL,time)==x);
        TL_CHECK(failures,helper.calculate(NULL,fixed,time,999)==x);
        delete fixed;
        DynamicAttributeRandom*random=new DynamicAttributeRandom;
        random->setMinMax(x,y);
        float value=random->getValue(NULL,time);
        TL_CHECK(failures,random->getType()==DynamicAttribute::DAT_RANDOM);
        TL_CHECK(failures,value>=x&&value<=y);
        delete random;
        DynamicAttributeCurved*curve=new DynamicAttributeCurved(IT_LINEAR);
        curve->addControlPoint(0,x);curve->addControlPoint(1,y);curve->processControlPoints();
        TL_CHECK(failures,curve->getType()==DynamicAttribute::DAT_CURVED);
        TL_CHECK(failures,curve->getNumControlPoints()==2);
        TL_CHECK(failures,std::fabs(curve->getValue(NULL,.5f)-(x+y)*.5f)<.00001f);
        float a,b;curve->getControlPointValues(1,a,b);
        TL_CHECK(failures,a==1&&b==y);
        delete curve;
        DynamicAttributeOscillate*oscillate=new DynamicAttributeOscillate;
        oscillate->setBase(x);oscillate->setAmplitude(0);
        TL_CHECK(failures,oscillate->getType()==DynamicAttribute::DAT_OSCILLATE);
        TL_CHECK(failures,oscillate->getValue(NULL,time)==x);
        delete oscillate;
        TL_CHECK(failures,helper.calculate(NULL,NULL,time,y)==y);
    }
    host->log("    native Dynamic SDK C1/D1+virtualValue/helper:64 profiles x4 genuine owners\n");
    return failures;
}
