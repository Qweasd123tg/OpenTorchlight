#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "Timeline.h"
#include "TimelineProperty.h"
#include "Descriptor.h"
#include "LogicWrapper.h"
#undef private
#include "TimelineDescriptorNames.h"
#define TARGET(old,newer,args,symbol) TL_ORIGINAL(void,old,args,symbol) extern "C" void newer args __asm__(symbol);
TARGET(tlOldData,tlNewData,(CTimeline*,CEditorScene*,CDataGroup*),"_ZN9CTimeline23saveTimelineToDataGroupEP12CEditorSceneP10CDataGroup")
TARGET(tlOldBinary,tlNewBinary,(CTimeline*,CEditorScene*,std::ofstream*),"_ZN9CTimeline24saveTimelineToBinaryFileEP12CEditorScenePSt14basic_ofstreamIcSt11char_traitsIcEE")
TARGET(tlOldLoadData,tlNewLoadData,(CTimeline*,CEditorScene*,CDataGroup*,CDescriptorLoadConfiguration*),"_ZN9CTimeline25loadTimelineFromDataGroupEP12CEditorSceneP10CDataGroupP28CDescriptorLoadConfiguration")
TARGET(tlOldLoadBinary,tlNewLoadBinary,(CTimeline*,CEditorScene*,COgreReader*,CDescriptorLoadConfiguration*),"_ZN9CTimeline26loadTimelineFromBinaryFileEP12CEditorSceneP11COgreReaderP28CDescriptorLoadConfiguration")
#undef TARGET
TL_FUNCTION(tlLookup,"_ZN12CEditorScene16GetObjectInSceneEx")
TL_FUNCTION(tlFlags,"_ZN17CEditorBaseObject17HasBaseObjectFlagE18EEDITOROBJECT_FLAG")
TL_FUNCTION(tlInterpolation,"_ZN17CTimelineProperty20SetInterpolationTypeE22ETIMELINE_INTERP_TYPES")
TL_FUNCTION(tlReset,"_ZN9CTimeline18Reset_To_BeginningEv")
namespace {
struct Descriptor:CDescriptor {Descriptor():CDescriptor(0){} CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}void add(CDescriptorProp*p){m_PropertyIDs[p->m_sName]=m_Properties.size();m_Properties.add(p);}};
struct Case{unsigned mode,seed;};typedef std::map<std::pair<int,bool>,CTimelineProperty*> Map;
autotest::Capture*cap;CEditorScene*scene;CEditorBaseObject*objects[5];unsigned seed,resets;
void n(unsigned x){cap->add(&x,4);}void bad(){cap->issue=autotest::Capture::InvalidReport;}
CEditorBaseObject*lookup(CEditorScene*p,long long id){if(p!=scene)bad();for(unsigned i=0;i<5;++i)if(id==1000+i)return seed%7==0&&i==3?NULL:objects[i];return NULL;}
bool flags(CEditorBaseObject*p,EEDITOROBJECT_FLAG flag){for(unsigned i=0;i<5;++i)if(p==objects[i])return (seed>>(i+1))&1;bad();return false;}
void interpolation(CTimelineProperty*p,ETIMELINE_INTERP_TYPES t){p->m_interpolationType=t;}
void reset(CTimeline*p){++resets;p->m_fTimelinePosition=-0.01f;}
void tree(CDataGroup*p){cap->addText(p->GetGroupName());n(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i){CDataValue*v=p->m_DataValues[i];cap->addText(v->GetDataValueName());n(v->GetValueType());cap->addText(v->GetValueAsString());}n(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)tree(p->m_DataGroups[i]);}
void state(CTimeline&t){n(t.m_timelineProperties.size());for(std::map<long long,Map*>::iterator i=t.m_timelineProperties.begin();i!=t.m_timelineProperties.end();++i){cap->add(&i->first,8);n(i->second->size());for(Map::iterator j=i->second->begin();j!=i->second->end();++j){n(j->first.first);n(j->first.second);CTimelineProperty*p=j->second;n(p!=NULL);if(!p)continue;cap->add(&p->m_objectID,8);n(p->m_propertyID);n(p->m_eventID);n(p->m_inputEvent);n(p->m_interpolationType);n(p->m_timeline==&t);n(p->m_editorScene==scene);unsigned count=0;for(TLinkedListNode<CTimelineProperty::CTimelinePoint*>*q=p->m_timelinePoints;q;q=q->m_pNext)++count;n(count);for(TLinkedListNode<CTimelineProperty::CTimelinePoint*>*q=p->m_timelinePoints;q;q=q->m_pNext){n(q->m_Data->m_pointID);cap->add(&q->m_Data->m_timePercent,4);CDescriptorProp&d=q->m_Data->m_descriptorProperty;n(d.m_eType);n(d.m_DefaultValue.size());for(unsigned k=0;k<d.m_DefaultValue.size();++k)n(d.m_DefaultValue[k].m_uValue);n(q->m_pNext==NULL||q->m_pNext->m_pPrevious==q);}}}cap->add(&t.m_fTimelinePosition,4);n(resets);}
template<class T>void word(std::ostream&s,const T&v){s.write(reinterpret_cast<const char*>(&v),sizeof(v));}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;cap=&out;resets=0;Descriptor descriptor;CDescriptorProp prop0(L"c",L"VALUE",L"d",NULL,NULL,VARIABLE_TYPE_INTEGER,0),prop1(L"c",L"OTHER",L"d",NULL,NULL,VARIABLE_TYPE_FLOAT,0);UNIONDATA32BIT initial;initial.m_iValue=17;prop0.m_DefaultValue.add(initial);initial.m_fValue=1.25f;prop1.m_DefaultValue.add(initial);descriptor.add(&prop0);descriptor.add(&prop1);descriptor.AddInputLogic(L"EVENT",3);descriptor.AddInputLogic(L"OTHER EVENT",4);CEditorBaseObject real[5];for(unsigned i=0;i<5;++i){objects[i]=&real[i];real[i].m_pDescriptor=seed%6==0&&i==2?NULL:&descriptor;real[i].setGuid(1000+i);real[i].setOriginalGuid(100+i);}
 CEditorScene realScene(L"test");scene=&realScene;CTimeline self;self.setGuid(777);self.setOriginalGuid(77);CDescriptorLoadConfiguration configuration;configuration.m_Remaps[77]=seed%11==0?778:777;for(unsigned i=0;i<5;++i)configuration.m_Remaps[100+i]=seed%13==0&&i==1?-1:1000+i;
 detour::Set patches;TL_REDIRECT(patches,tlLookup,&lookup);TL_REDIRECT(patches,tlFlags,&flags);TL_REDIRECT(patches,tlReset,&reset);TL_REDIRECT(patches,tlInterpolation,&interpolation);if(patches.failed()){bad();return;}
 if(c.mode<2){for(unsigned i=0;i<seed%6;++i){long long id=i==4&&seed%3==0?-1:1000+i;Map*m=new Map;self.m_timelineProperties[id]=m;for(unsigned j=0;j<(seed+i)%5;++j){bool event=j&1;int index=j/2;if(index>1)continue;CTimelineProperty*p=event?new CTimelineProperty(&self,scene,&descriptor,index,true,id):new CTimelineProperty(&self,scene,&descriptor,index?&prop1:&prop0,id);(*m)[std::make_pair(index,event)]=p;for(unsigned k=0;k<(seed+j)%4;++k){int point=p->AddPoint();if(point<0)continue;p->SetTimePercentAtPoint(point,(k+1)*0.25f);if(!event){UNIONDATA32BIT values[2];values[0].m_iValue=seed*11+k;values[1].m_iValue=-17-k;p->SetValueAtPoint(point,values,1+seed%2);}}p->m_interpolationType=(seed+j)%8;}}
  if(c.mode==0){CDataGroup data(L"root",NULL,2,2,NULL);typedef void(*Fn)(CTimeline*,CEditorScene*,CDataGroup*);Fn fn=ours?tlNewData:tlOldData;if(!autotest::beginInvocation(out,fn))return;fn(&self,scene,&data);out.callCompleted=1;tree(&data);}
  else{char path[128];std::snprintf(path,sizeof(path),"/tmp/otl-deepen-timeline-%d.bin",getpid());std::ofstream file(path,std::ios::binary);typedef void(*Fn)(CTimeline*,CEditorScene*,std::ofstream*);Fn fn=ours?tlNewBinary:tlOldBinary;if(!autotest::beginInvocation(out,fn))return;fn(&self,scene,&file);out.callCompleted=1;file.close();std::ifstream input(path,std::ios::binary);std::string bytes((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());cap->addText(bytes);std::remove(path);}
 }else if(c.mode==2){CDataGroup data(L"root",NULL,2,2,NULL);if(seed%17){CDataGroup*d=data.AddDataGroup(L"TIMELINEDATA");d->AddDataValue(L"ID",77LL);for(unsigned i=0;i<seed%6;++i){CDataGroup*o=d->AddDataGroup(L"TIMELINEOBJECT");o->AddDataValue(L"OBJECTID",static_cast<long long>(100+i));for(unsigned j=0;j<(seed+i)%5;++j){CDataGroup*p=o->AddDataGroup(j==3&&seed%5==0?L"WRONG":j&1?L"TIMELINEOBJECTEVENT":L"TIMELINEOBJECTPROPERTY");if(j&1)p->AddDataValue(L"OBJECTEVENTNAME",j==3?L"missing":L"EVENT",false);else p->AddDataValue(L"OBJECTPROPERTYNAME",j==2?L"other":L"value",false);for(unsigned k=0;k<(seed+j)%4;++k){CDataGroup*q=p->AddDataGroup(L"TIMELINEPOINT");if(seed&1)q->AddDataValue(L"TIMEPERCENT",k*0.125f);if(seed&2)q->AddDataValue(L"INTERPOLATION",seed%9==8?L"unknown":gTIMELINE_INTERP_TYPES[(seed+k)%8],false);q->AddDataValue(L"VALUE",k&1?L"12,-19":L"27",false);}}}}
  typedef void(*Fn)(CTimeline*,CEditorScene*,CDataGroup*,CDescriptorLoadConfiguration*);Fn fn=ours?tlNewLoadData:tlOldLoadData;if(!autotest::beginInvocation(out,fn))return;fn(&self,seed%19?scene:NULL,seed%23?&data:NULL,seed%29?&configuration:NULL);out.callCompleted=1;tree(&data);
 }else{std::ostringstream stream(std::ios::binary);unsigned count=seed%6;word(stream,count);for(unsigned i=0;i<count;++i){long long id=100+i;unsigned properties=(seed+i)%4;word(stream,id);word(stream,properties);for(unsigned j=0;j<properties;++j){int index=j%2;bool event=j&1;unsigned points=(seed+j)%4;word(stream,index);word(stream,event);word(stream,points);for(unsigned k=0;k<points;++k){float time=k*0.25f;int interp=(seed+k)%8;word(stream,time);word(stream,interp);if(!event){unsigned size=1+seed%3;word(stream,size);for(unsigned z=0;z<size;++z){int value=seed*5+z;word(stream,value);}}}}}std::string bytes=stream.str();COgreReader reader;reader.m_pData=new char[bytes.size()];std::memcpy(reader.m_pData,bytes.data(),bytes.size());reader.m_iSize=bytes.size();typedef void(*Fn)(CTimeline*,CEditorScene*,COgreReader*,CDescriptorLoadConfiguration*);Fn fn=ours?tlNewLoadBinary:tlOldLoadBinary;if(!autotest::beginInvocation(out,fn))return;fn(&self,seed%19?scene:NULL,seed%23?&reader:NULL,seed%29?&configuration:NULL);out.callCompleted=1;n(reader.m_iPosition);}
 state(self);for(unsigned i=0;i<5;++i)real[i].m_pDescriptor=NULL;}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t addr){autotest::Coverage coverage(name,addr);for(unsigned i=0;i<100;++i){Case c={mode,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){for(unsigned z=0;z<x.capture.length&&z<y.capture.length;++z)if(x.capture.data[z]!=y.capture.data[z]){h->log("    first difference %u %u/%u\n",z,unsigned((unsigned char)x.capture.data[z]),unsigned((unsigned char)y.capture.data[z]));break;}h->log("    timeline mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_timeline_save_data){return run(host,0,"deepen_editor_timeline_save_data",(uintptr_t)&tlOldData);}
TL_TEST(deepen_editor_timeline_save_binary){return run(host,1,"deepen_editor_timeline_save_binary",(uintptr_t)&tlOldBinary);}
TL_TEST(deepen_editor_timeline_load_data){return run(host,2,"deepen_editor_timeline_load_data",(uintptr_t)&tlOldLoadData);}
TL_TEST(deepen_editor_timeline_old_binary){return run(host,3,"deepen_editor_timeline_old_binary",(uintptr_t)&tlOldLoadBinary);}
