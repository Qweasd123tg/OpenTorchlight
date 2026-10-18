#include <cstring>
#include <cstdio>
#include <string>
#include <map>
#include <sstream>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "LogicGroup.h"
#include "LogicObject.h"
#include "OgreReader.h"
#undef private
TL_ORIGINAL(void,dlOld,(CLogicGroup*,CDataGroup*,COgreReader*,CDescriptorLoadConfiguration*),"_ZN11CLogicGroup25loadLogicGroupToDataGroupEP10CDataGroupP11COgreReaderP28CDescriptorLoadConfiguration")
extern "C" void dlNew(CLogicGroup*,CDataGroup*,COgreReader*,CDescriptorLoadConfiguration*) __asm__("_ZN11CLogicGroup25loadLogicGroupToDataGroupEP10CDataGroupP11COgreReaderP28CDescriptorLoadConfiguration");
TL_FUNCTION(dlAdd,"_ZN11CLogicGroup14AddLogicObjectEx")
TL_FUNCTION(dlData,"_ZN12CLogicObject26loadLogicObjectByDataGroupEP11CLogicGroupP10CDataGroupP28CDescriptorLoadConfigurationPSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
TL_FUNCTION(dlBinary,"_ZN12CLogicObject27loadLogicObjectByBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
TL_FUNCTION(dlRelink,"_ZN12CLogicObject35loadAndRelinkObjectInFromBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
extern "C" char dlLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char dlLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* cap;CLogicGroup* owner;CDescriptorLoadConfiguration* conf;COgreReader* input;unsigned seed,loads,relinks,adds,logs;int logSpace;
void n(unsigned x){cap->add(&x,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}
unsigned index(CLogicObject*p){for(unsigned i=0;i<owner->m_logicObjects.size();++i)if(owner->m_logicObjects[i]==p)return i;invalid();return 999;}
void captureMap(std::map<int,int>&m){n(m.size());for(std::map<int,int>::iterator i=m.begin();i!=m.end();++i){cap->add(&i->first,4);cap->add(&i->second,4);}}
Ogre::LogManager* getLog(){return reinterpret_cast<Ogre::LogManager*>(&logSpace);}
void logMessage(Ogre::LogManager*p,const std::string&s,Ogre::LogMessageLevel level,bool mask){++logs;n(9);cap->addText(s);n(level);n(mask);if(p!=getLog()||level!=Ogre::LML_CRITICAL||mask)invalid();}
int add(CLogicGroup*p,long long id){++adds;n(1);cap->add(&id,8);if(p!=owner)invalid();if(id==-1)return -1;CLogicObject*o=new CLogicObject(NULL,-1,owner->m_logicObjects.size());o->m_iObjectID=id;owner->m_logicObjects.add(o);return owner->m_logicObjects.size()-1;}
void loadData(CLogicObject*p,CLogicGroup*g,CDataGroup*d,CDescriptorLoadConfiguration*c,std::map<int,int>*m){++loads;n(2);n(index(p));n(d->GetDataValue(L"ID",unsigned(-1)));if(g!=owner||c!=conf||!m)invalid();if(m)captureMap(*m);p->m_fLeft=100+loads;}
void loadBinary(CLogicObject*p,CLogicGroup*g,COgreReader*r,CDescriptorLoadConfiguration*c,std::map<int,int>&m){++loads;n(3);n(index(p));if(g!=owner||c!=conf||r!=input)invalid();unsigned id=0;r->read(&id,4);m[id]=index(p);captureMap(m);p->m_fTop=200+loads;}
void relink(CLogicObject*p,CLogicGroup*g,COgreReader*r,CDescriptorLoadConfiguration*c,std::map<int,int>&m){++relinks;n(4);n(index(p));if(g!=owner||c!=conf||r!=input||loads!=seed%5)invalid();captureMap(m);p->m_fRight=300+relinks;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;loads=relinks=adds=logs=0;CLogicGroup self(NULL);owner=&self;CDescriptorLoadConfiguration configuration;conf=&configuration;COgreReader reader;input=&reader;
 for(unsigned i=0;i<seed%3;++i)self.m_logicObjects.add(new CLogicObject(NULL,-1,i));
 CDataGroup root(L"root",NULL,2,2,NULL);CDataGroup*data=NULL;COgreReader*stream=NULL;
 if(c.mode==0||c.mode==1){data=&root;if(c.mode==1||seed%5){CDataGroup*group=root.AddDataGroup(L"LOGICGROUP");for(unsigned i=0;i<seed%5;++i){CDataGroup*d=group->AddDataGroup(i%3==2?L"other":L"LOGICOBJECT");d->AddDataValue(L"ID",unsigned(i%2==0&&seed%7==0?-1:i));long long id=1000+i;d->AddDataValue(L"OBJECTID",id);configuration.m_Remaps[id]=seed%6==0?-1:2000+i;}}}
 else if(c.mode==2){stream=&reader;unsigned count=seed%5;reader.m_iSize=4*(count+1);reader.m_pData=new char[reader.m_iSize];std::memcpy(reader.m_pData,&count,4);for(unsigned i=0;i<count;++i){unsigned id=10+i;std::memcpy(reader.m_pData+4*(i+1),&id,4);}}
 detour::Set patches;TL_REDIRECT(patches,dlAdd,&add);TL_REDIRECT(patches,dlData,&loadData);TL_REDIRECT(patches,dlBinary,&loadBinary);TL_REDIRECT(patches,dlRelink,&relink);patches.redirect(reinterpret_cast<char*>(0x554918),dlLogSingleton,&getLog);patches.redirect(reinterpret_cast<char*>(0x554e68),dlLogMessage,&logMessage);if(patches.failed()){invalid();return;}
 typedef void(*Fn)(CLogicGroup*,CDataGroup*,COgreReader*,CDescriptorLoadConfiguration*);Fn fn=ours?dlNew:dlOld;if(!autotest::beginInvocation(out,fn))return;fn(&self,data,stream,&configuration);out.callCompleted=1;
 n(adds);n(loads);n(relinks);n(logs);n(reader.m_iPosition);n(self.m_logicObjects.size());if(c.mode==2&&(loads!=seed%5||relinks!=seed%3+seed%5||reader.m_iPosition!=reader.m_iSize))invalid();for(unsigned i=0;i<self.m_logicObjects.size();++i){CLogicObject*p=self.m_logicObjects[i];n(p->m_iID);out.add(&p->m_iObjectID,8);out.add(&p->m_fLeft,16);}
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(deepen_editor_logic_group){autotest::Coverage coverage("deepen_editor_logic_group",(uintptr_t)&dlOld);for(unsigned mode=0;mode<4;++mode)for(unsigned seed=0;seed<40;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){for(unsigned z=0;z<x.capture.length&&z<y.capture.length;++z)if(x.capture.data[z]!=y.capture.data[z]){host->log("first byte %u = %u/%u lengths%lu/%lu\n",z,unsigned((unsigned char)x.capture.data[z]),unsigned((unsigned char)y.capture.data[z]),(unsigned long)x.capture.length,(unsigned long)y.capture.length);break;}host->log("    logic group mode%u seed%u issue%u/%u exits%d/%d lengths%lu/%lu target%llx/%llx\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long long)x.capture.callTarget,(unsigned long long)y.capture.callTarget);coverage.report(host);return 1;}}coverage.report(host);return 0;}
