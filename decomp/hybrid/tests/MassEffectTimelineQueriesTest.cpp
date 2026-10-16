#include "AutoTest.h"
#include "Detour.h"
#include "Affix.h"
#include "Effect.h"
#include "Timeline.h"
#include "DescriptorProp.h"
#include "DescriptorPropertyInterpreter.h"
#include <cstring>
#include <limits>
TL_ORIGINAL(void, constructAffix, (void*,const std::wstring&), "_ZN6CAffixC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, destroyAffix, (void*), "_ZN6CAffixD1Ev")
TL_ORIGINAL(void, constructEffect, (void*,EEFFECT_TYPE,bool,EEFFECT_ACTIVATION,float,float,float,bool), "_ZN7CEffectC1E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb")
TL_ORIGINAL(void, destroyEffect, (void*), "_ZN7CEffectD1Ev")
TL_ORIGINAL(bool, oldDuration, (void*,EEFFECT_TYPE), "_ZN6CAffix17effectHasDurationE12EEFFECT_TYPE")
extern "C" bool newDuration(void*,EEFFECT_TYPE) __asm__("_ZN6CAffix17effectHasDurationE12EEFFECT_TYPE");
TL_ORIGINAL(bool, oldExists, (void*,EEFFECT_TYPE), "_ZN6CAffix12effectExistsE12EEFFECT_TYPE")
extern "C" bool newExists(void*,EEFFECT_TYPE) __asm__("_ZN6CAffix12effectExistsE12EEFFECT_TYPE");
TL_ORIGINAL(std::wstring, oldStats, (void*,unsigned), "_ZN6CAffix15getDisplayStatsEj")
extern "C" std::wstring newStats(void*,unsigned) __asm__("_ZN6CAffix15getDisplayStatsEj");
TL_FUNCTION(parseAffix, "_ZN6CAffix15parseAffixGroupEv")
TL_FUNCTION(effectStats, "_ZN7CEffect15getDisplayStatsEjb")
TL_ORIGINAL(unsigned, oldElement, (void*), "_ZN15CDescriptorProp14getElementSizeEv")
extern "C" unsigned newElement(void*) __asm__("_ZN15CDescriptorProp14getElementSizeEv");
TL_ORIGINAL(void, constructTimeline, (void*), "_ZN9CTimelineC1Ev")
TL_ORIGINAL(void, destroyTimeline, (void*), "_ZN9CTimelineD1Ev")
typedef std::pair<int,bool> Key;
TL_ORIGINAL(Key, oldPropertyID, (void*,long long,int), "_ZN9CTimeline39GetPropertyIDForObjectInTimelineByIndexExi")
extern "C" Key newPropertyID(void*,long long,int) __asm__("_ZN9CTimeline39GetPropertyIDForObjectInTimelineByIndexExi");
#include "TimelineProperty.h"
TL_ORIGINAL(void, constructProperty, (void*,CTimeline*,CEditorScene*,CDescriptor*,unsigned,bool,long long), "_ZN17CTimelinePropertyC1EP9CTimelineP12CEditorSceneP11CDescriptorjbx")
TL_ORIGINAL(void, destroyProperty, (void*), "_ZN17CTimelinePropertyD1Ev")
TL_ORIGINAL(CTimelineProperty*, oldProperty, (void*,long long,int,bool), "_ZN9CTimeline11GetPropertyExib")
extern "C" CTimelineProperty* newProperty(void*,long long,int,bool) __asm__("_ZN9CTimeline11GetPropertyExib");
namespace {
struct Case {unsigned operation,index;};
autotest::Capture* output;CEffect* effects[5];unsigned calls,seed;
unsigned parsed;void* constructingAffix;
void parseForSetup(void* object) { if(object!=constructingAffix)output->issue=autotest::Capture::InvalidReport; ++parsed; }
std::wstring display(void* object,unsigned level,bool flag) {
    unsigned identity=5;for(unsigned i=0;i<5;++i)if(object==effects[i])identity=i;
    output->add(&identity,sizeof(identity));output->add(&level,sizeof(level));output->add(&flag,sizeof(flag));++calls;
    if(identity==5||flag)output->issue=autotest::Capture::InvalidReport;
    const wchar_t* values[]={L"",L"one",L"\x0434\x0432\x0430",L"\n",L"three"};
    return values[(identity+seed)%5];
}
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);seed=c.index;output=&out;calls=0;
    if(c.operation<3) {
        CAffix* affix=static_cast<CAffix*>(autotest::allocate(sizeof(CAffix)));
        if(!affix){out.issue=autotest::Capture::InvalidReport;return;}
        constructingAffix=affix;parsed=0;
        {
            // Preserve the real lifetime/containers without loading an affix file
            // through the uninitialised global resource manager during setup.
            detour::Set setup;TL_REDIRECT(setup,parseAffix,parseForSetup);
            if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}
            constructAffix(affix,L"");
        }
        out.add(&parsed,sizeof(parsed));if(parsed!=1){out.issue=autotest::Capture::InvalidReport;return;}
        affix->m_Effects.clear();
        for(unsigned i=0;i<5;++i) {
            effects[i]=static_cast<CEffect*>(autotest::allocate(sizeof(CEffect)));
            constructEffect(effects[i],static_cast<EEFFECT_TYPE>((i+c.index/6)%4),false,static_cast<EEFFECT_ACTIVATION>(0),0,0,0,false);
            const float durations[]={0,-1,1,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-0.0f};
            float duration=durations[(i+c.index)%6];std::memcpy(reinterpret_cast<char*>(effects[i])+0x24,&duration,sizeof(duration));
        }
        for(unsigned i=0;i<c.index%6;++i)affix->m_Effects.add(effects[i]);
        EEFFECT_TYPE query=static_cast<EEFFECT_TYPE>((c.index/6)%6);
        unsigned char affixBefore[sizeof(CAffix)],effectBefore[5][sizeof(CEffect)];
        std::memcpy(affixBefore,affix,sizeof(CAffix));for(unsigned i=0;i<5;++i)std::memcpy(effectBefore[i],effects[i],sizeof(CEffect));
        detour::Set redirects;if(c.operation==2)TL_REDIRECT(redirects,effectStats,display);
        if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        if(c.operation<2) {
            typedef bool(*Fn)(void*,EEFFECT_TYPE);Fn fn=c.operation==0?(ours?newDuration:oldDuration):(ours?newExists:oldExists);
            if(!autotest::beginInvocation(out,fn))return;bool result=fn(affix,query);out.callCompleted=1;out.add(&result,sizeof(result));
        } else {
            typedef std::wstring(*Fn)(void*,unsigned);Fn fn=ours?newStats:oldStats;
            if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(affix,c.index*13);out.callCompleted=1;out.addText(result);out.add(&calls,sizeof(calls));
        }
        // Compare the entire receiver state within each child, then record
        // logical data instead of allocator-dependent object/string addresses.
        bool unchanged=std::memcmp(affixBefore,affix,sizeof(CAffix))==0;
        out.add(&unchanged,sizeof(unchanged));if(!unchanged)out.issue=autotest::Capture::InvalidReport;
        out.addText(affix->m_sAffixFileName);out.addText(affix->m_sDisplayName);out.addText(affix->m_sPrefix);out.addText(affix->m_sSuffix);
        unsigned count=affix->m_Effects.size();out.add(&count,sizeof(count));
        for(unsigned i=0;i<count;++i){unsigned identity=5;for(unsigned j=0;j<5;++j)if(affix->m_Effects[i]==effects[j])identity=j;out.add(&identity,sizeof(identity));if(identity==5)out.issue=autotest::Capture::InvalidReport;}
        for(unsigned i=0;i<5;++i){
            unchanged=std::memcmp(effectBefore[i],effects[i],sizeof(CEffect))==0;out.add(&unchanged,sizeof(unchanged));if(!unchanged)out.issue=autotest::Capture::InvalidReport;
            out.add(reinterpret_cast<char*>(effects[i])+0x1c,12);
            const unsigned strings[]={0x78,0x80,0x88,0x90,0xb0};for(unsigned j=0;j<5;++j)out.addText(*reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(effects[i])+strings[j]));
        }
        affix->m_Effects.clear();for(unsigned i=0;i<5;++i)destroyEffect(effects[i]);destroyAffix(affix);
    } else if(c.operation==3) {
        CDescriptorProp property(L"category",L"name",L"description",NULL,NULL,static_cast<EVARIABLE_TYPES>(c.index%12),0);
        for(unsigned i=0;i<(c.index/12)%7;++i){UNIONDATA32BIT value;value.m_iValue=i;property.m_DefaultValue.add(value);}
        CDescriptorPropertyInterpreter interpreter(NULL,NULL,NULL);
        if(c.index>=84)property.m_pInterpreter=&interpreter;
        typedef unsigned(*Fn)(void*);Fn fn=ours?newElement:oldElement;
        if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(&property);out.callCompleted=1;out.add(&result,sizeof(result));out.add(&property,sizeof(property));
        property.m_pInterpreter=NULL;
    } else {
        CTimeline* timeline=static_cast<CTimeline*>(autotest::allocate(sizeof(CTimeline)));constructTimeline(timeline);
        typedef std::map<Key,CTimelineProperty*> Properties;Properties properties;
        CTimelineProperty* values[9];
        for(unsigned i=0;i<9;++i) {
            values[i]=static_cast<CTimelineProperty*>(autotest::allocate(sizeof(CTimelineProperty)));
            constructProperty(values[i],timeline,NULL,NULL,i,bool(i%2),i);
        }
        for(unsigned i=0;i<c.index%9;++i)properties.insert(std::make_pair(Key(int(i/2)-2,bool(i%2)),values[i]));
        timeline->m_timelineProperties[0]=&properties;
        timeline->m_timelineProperties[0x100000003LL]=&properties;
        long long id=c.index%4==0?-1:c.index%4==1?0:c.index%4==2?0x100000003LL:5;
        int index=int(c.index/4)%12-2;
        if(c.operation==4) {
            typedef Key(*Fn)(void*,long long,int);Fn fn=ours?newPropertyID:oldPropertyID;
            if(!autotest::beginInvocation(out,fn))return;Key result=fn(timeline,id,index);out.callCompleted=1;out.add(&result.first,sizeof(result.first));out.add(&result.second,sizeof(result.second));
        } else {
            typedef CTimelineProperty*(*Fn)(void*,long long,int,bool);Fn fn=ours?newProperty:oldProperty;
            int propertyID=int(c.index/8)%7-3;bool isEvent=bool(c.index&4);
            if(!autotest::beginInvocation(out,fn))return;CTimelineProperty* result=fn(timeline,id,propertyID,isEvent);out.callCompleted=1;
            int identity=-1;for(unsigned i=0;i<9;++i)if(result==values[i])identity=i;
            if(result&&identity==-1)out.issue=autotest::Capture::InvalidReport;
            out.add(&identity,sizeof(identity));
        }
        unsigned count=properties.size();out.add(&count,sizeof(count));for(Properties::const_iterator i=properties.begin();i!=properties.end();++i){out.add(&i->first.first,sizeof(i->first.first));out.add(&i->first.second,sizeof(i->first.second));}
        timeline->m_timelineProperties.clear();for(unsigned i=0;i<9;++i)destroyProperty(values[i]);destroyTimeline(timeline);
    }
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uint64_t address) {
    autotest::Coverage coverage(name,address);unsigned count=operation==3?168:operation>=4?288:72;
    for(unsigned i=0;i<count;++i){Case c={operation,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    %s case %u original status %d report %u issue %u started %u completed %u; candidate status %d report %u issue %u started %u completed %u\n",name,i,a.childStatus,a.reportValid,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.reportValid,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(mass_affix_duration){return run(host,0,"mass_affix_duration",(uint64_t)(uintptr_t)oldDuration);}
TL_TEST(mass_affix_exists){return run(host,1,"mass_affix_exists",(uint64_t)(uintptr_t)oldExists);}
TL_TEST(mass_affix_stats){return run(host,2,"mass_affix_stats",(uint64_t)(uintptr_t)oldStats);}
TL_TEST(mass_descriptor_element){return run(host,3,"mass_descriptor_element",(uint64_t)(uintptr_t)oldElement);}
TL_TEST(mass_timeline_property_key){return run(host,4,"mass_timeline_property_key",(uint64_t)(uintptr_t)oldPropertyID);}

TL_TEST(mass_timeline_property_lookup){return run(host,5,"mass_timeline_property_lookup",(uint64_t)(uintptr_t)oldProperty);}
