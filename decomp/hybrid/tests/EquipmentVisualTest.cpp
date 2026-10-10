#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "GenericModel.h"
#include "Layout.h"
#include "DataGroup.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldVisual,(CEquipment*,float),"_ZN10CEquipment18updateVisualLayoutEf")
extern "C" void newVisual(CEquipment*,float) __asm__("_ZN10CEquipment18updateVisualLayoutEf");
TL_FUNCTION(layoutCtor,"_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
TL_FUNCTION(layoutLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(layoutStart,"_ZN7CLayout5startEv")
TL_FUNCTION(dataText,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(setPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
struct Stop{};struct Case{unsigned mask,mutation,fault;float elapsed;};const Case*cs;autotest::Capture*cap;CEquipment*item;CLayout*layouts[3];CGenericModel*models[2];void*nodes[2];void*table[3][80];unsigned calls;void*created;Ogre::Vector3 positions[2];Ogre::Quaternion rotations[2];std::wstring path;
void n(int x){cap->add(&x,4);}int id(void*p,void*a,void*b,void*c=0){if(!p)return 0;return p==a?1:p==b?2:c&&p==c?3:99;}int lid(void*p){return id(p,layouts[0],layouts[1],created);}
void event(int x){n(x);if(++calls==cs->fault)throw Stop();}
void orient0(CPositionableObject*p,const Ogre::Quaternion&q){event(9);n(0);n(lid(p));cap->add(&q,sizeof(q));}
void orient1(CPositionableObject*p,const Ogre::Quaternion&q){event(9);n(1);n(lid(p));cap->add(&q,sizeof(q));}
void visible(CLayout*p,bool v){event(5);n(lid(p));n(v);p->m_bVisible=v;if(cs->mutation==1)item->m_pPositionableObject=layouts[1];}
void update(CLayout*p,float dt){event(6);n(lid(p));cap->add(&dt,4);if(cs->mutation==2)item->m_pUnitModel=models[1];if(cs->mutation==3)item->m_pPositionableObject=layouts[1];}
const Ogre::Vector3& position(void*p){event(7);n(id(p,nodes[0],nodes[1]));if(cs->mutation==4)item->m_pPositionableObject=layouts[1];return positions[p==nodes[1]?1:0];}
const Ogre::Quaternion& rotation(void*p){event(8);n(id(p,nodes[0],nodes[1]));if(cs->mutation==6)item->m_pPositionableObject=layouts[1];return rotations[p==nodes[1]?1:0];}
void move(CPositionableObject*p,const Ogre::Vector3&v){event(10);n(lid(p));cap->add(&v,sizeof(v));if(cs->mutation==5){item->m_pUnitModel=models[1];item->m_pPositionableObject=layouts[1];}}
void ctor(CLayout*p,CResourceManager*r,ELAYOUT_TYPES type){created=p;std::memset(p,0xa5,sizeof(CLayout));*(void***)p=table[0];p->m_bVisible=(cs->mask&8)!=0;event(1);n(r==item->m_pResourceManager);n(type);}
const std::wstring& data(CDataGroup*p,const std::wstring&key,const wchar_t*def){event(2);n(p==item->m_pDataGroup);cap->addText(key);cap->addText(std::wstring(def));if(cs->mutation==7)item->m_pPositionableObject=layouts[1];return path;}
void load(CLayout*p,const std::wstring&name,bool objects,CTimerStatics*timer,bool force,bool ignore,unsigned seed){event(3);n(lid(p));cap->addText(name);n(objects);n(timer!=0);n(force);n(ignore);n(seed);if(cs->mutation==8)item->m_pPositionableObject=layouts[1];}
void start(CLayout*p){event(4);n(lid(p));if(cs->mutation==9)item->m_pPositionableObject=layouts[1];}
void ptr(unsigned char*p,unsigned off,uintptr_t v){std::memcpy(p+off,&v,8);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*(Case*)raw;cs=&c;cap=&out;calls=0;created=0;unsigned long long em[(sizeof(CEquipment)+7)/8],lm[2][(sizeof(CLayout)+7)/8],mm[2][(sizeof(CGenericModel)+7)/8],nm[2][8],rm[8],dm[8];std::memset(em,0xa5,sizeof(em));std::memset(lm,0xa5,sizeof(lm));std::memset(mm,0xa5,sizeof(mm));std::memset(nm,0,sizeof(nm));item=(CEquipment*)em;item->m_bUnknown430=(c.mask&1)!=0;item->m_pResourceManager=(CResourceManager*)rm;item->m_pDataGroup=(CDataGroup*)dm;
 void* nt[80]={0};nt[0x200/8]=(void*)&position;nt[0x1f8/8]=(void*)&rotation;
 for(unsigned i=0;i<2;++i){layouts[i]=(CLayout*)lm[i];models[i]=(CGenericModel*)mm[i];nodes[i]=nm[i];std::memset(table[i],0,sizeof(table[i]));table[i][0x50/8]=(void*)&visible;table[i][0x208/8]=(void*)&update;table[i][0x108/8]=i?(void*)&orient1:(void*)&orient0;*(void***)layouts[i]=table[i];layouts[i]->m_bVisible=(c.mask&8)!=0;*(void***)nodes[i]=nt;models[i]->m_pSceneNode=(Ogre::SceneNode*)nodes[i];positions[i]=Ogre::Vector3(i+0.25f,-float(i)-2.5f,9.0f);rotations[i]=Ogre::Quaternion(i+0.5f,0.25f,-0.75f,1.5f);}
 item->m_pUnitModel=c.mask&2?models[0]:0;item->m_pPositionableObject=c.mask&4?layouts[0]:0;path=c.mask&16?std::wstring(L"layout\0tail",11):L"";
 detour::Set d;TL_REDIRECT(d,layoutCtor,&ctor);TL_REDIRECT(d,layoutLoad,&load);TL_REDIRECT(d,layoutStart,&start);TL_REDIRECT(d,dataText,&data);TL_REDIRECT(d,setPosition,&move);if(d.failed())_exit(60);bool threw=false;try{autotest::invoke(out,ours?&newVisual:&oldVisual,item,c.elapsed);}catch(const Stop&){threw=true;}catch(...){_exit(61);}n(threw);n(calls);unsigned char snapshot[sizeof(em)];std::memcpy(snapshot,em,sizeof(em));ptr(snapshot,0x68,1);ptr(snapshot,0x1b0,1);ptr(snapshot,0x2b0,id(item->m_pUnitModel,models[0],models[1]));ptr(snapshot,0x428,lid(item->m_pPositionableObject));out.add(snapshot,sizeof(snapshot));for(unsigned i=0;i<2;++i){unsigned char bytes[sizeof(CLayout)];std::memcpy(bytes,layouts[i],sizeof(bytes));ptr(bytes,0,i+1);out.add(bytes,sizeof(bytes));}if(created&&c.fault!=1)Ogre::NedAllocImpl::deallocBytes(created);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(equipment_visual_production){autotest::Coverage cv("equipment_visual_production",(uint64_t)(uintptr_t)&oldVisual);float times[]={0.0f,-0.25f,0.016f,100.0f};for(unsigned mask=0;mask<32;++mask)for(unsigned mutation=0;mutation<10;++mutation)for(unsigned dt=0;dt<4;++dt){Case c={mask,mutation,0,times[dt]};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){host->log("    visual mismatch %u/%u/%u exits %d/%d sizes %lu/%lu\n",mask,mutation,dt,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);cv.report(host);return 1;}}cv.report(host);return 0;}
TL_TEST(equipment_visual_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=10;++fault)for(unsigned mutation=0;mutation<10;++mutation){Case c={3,mutation,fault,0.25f};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(!x.reportValid||!y.reportValid||x.childStatus||y.childStatus||!x.capture.callStarted||!y.capture.callStarted||x.capture.callCompleted||y.capture.callCompleted||x.capture.issue||y.capture.issue||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length)){host->log("    visual unwind %u/%u exits %d/%d\n",fault,mutation,x.childStatus,y.childStatus);return 1;}++count;}host->log("    EXPECTED VISUAL EXCEPTIONS: %u matching unwinds\n",count);return 0;}
