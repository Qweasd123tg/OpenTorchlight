#include <cstring>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Path.h"
#include "SoundBank.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalEquipmentUpdateDrop,(CEquipment*,float),"_ZN10CEquipment10updateDropEf")
TL_FUNCTION(udSpline,"_ZN5CPath27GetSplinePositionAtDistanceEf")
TL_FUNCTION(udPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(udSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(udIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
extern "C" void* dropEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void tracedoriginalEquipmentUpdateDrop(CEquipment*,float) __asm__("_ZN10CEquipment10updateDropEf");
namespace {
struct Case{unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* equipment;CPath* paths[2];unsigned enabledCalls,sounds,positions,orientations;int service[2];
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}void vector(const Ogre::Vector3& v){real(v.x);real(v.y);real(v.z);}void matrix(const Ogre::Matrix4& m){for(unsigned r=0;r<4;++r)for(unsigned c=0;c<4;++c)real(m[r][c]);}
void enabled(CEquipment* p,bool value){number(10);number(p==equipment);number(value);real(p->m_fUnknown258);number(p->m_bUnknown25C);p->m_bEnabled=value;++enabledCalls;if(input->mode==1){p->m_fUnknown258=0.125f;p->m_pPath=paths[1];}}
Ogre::Vector3 spline(CPath* p,float distance){number(11);number(p==paths[0]?0:p==paths[1]?1:-1);real(distance);return Ogre::Vector3(distance,distance*2.0f+(p==paths[1]?3.0f:1.0f),distance*(-0.5f));}
void position(CPositionableObject* p,const Ogre::Vector3& v){number(12);number(p==equipment);number(&v==&equipment->m_vPosition);vector(v);vector(equipment->m_vPosition);++positions;if(input->mode==3){equipment->m_pPath->m_fPathLength=8.0f;equipment->m_fUnknown258=0.75f;}}
void sound(CSoundBank* p,int kind,Ogre::SceneNode* node,float a,float b,bool flag){number(13);number(p==reinterpret_cast<CSoundBank*>(&service[0]));number(kind);number(node==reinterpret_cast<Ogre::SceneNode*>(&service[1]));real(a);real(b);number(flag);real(equipment->m_fUnknown258);number(equipment->m_bUnknown25C);++sounds;if(input->mode==2){equipment->m_fUnknown258=0.375f;equipment->m_pPath=paths[1];}}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){number(14);number(p==equipment);number(type);unsigned flags=input->mode?1:(input->seed/2)%16;return type==UNITTYPES::WEAPON?(flags&1)!=0:type==UNITTYPES::SHIELD?(flags&2)!=0:type==UNITTYPES::POTION?(flags&4)!=0:type==UNITTYPES::SCROLL?(flags&8)!=0:false;}
void orientation(CPositionableObject* p,const Ogre::Matrix4& value,bool translation){number(15);number(p==equipment);number(&value==&equipment->m_mOrientation);number(translation);matrix(value);matrix(equipment->m_mOrientation);++orientations;if(input->mode==4)equipment->m_bUnknown25C=true;}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;capture=&out;enabledCalls=sounds=positions=orientations=0;unsigned long long storage[(sizeof(CEquipment)+7)/8],pathStorage[2][(sizeof(CPath)+7)/8];std::memset(storage,0,sizeof(storage));std::memset(pathStorage,0,sizeof(pathStorage));equipment=reinterpret_cast<CEquipment*>(storage);paths[0]=reinterpret_cast<CPath*>(pathStorage[0]);paths[1]=reinterpret_cast<CPath*>(pathStorage[1]);
 void* table[110];std::memcpy(table,dropEquipmentTable+2,sizeof(table));table[8]=reinterpret_cast<void*>(&enabled);table[35]=reinterpret_cast<void*>(&orientation);void** pointer=table;std::memcpy(equipment,&pointer,sizeof(pointer));
 static const float lengths[]={0.0f,0.5f,1.0f,5.0f,10.0f};static const float steps[]={-0.05f,0.0f,0.001f,0.05f,0.5f};float length=lengths[(c.seed/32)%5];paths[0]->m_fPathLength=length;paths[1]->m_fPathLength=2.5f;equipment->m_bUnknown25C=c.mode||(c.seed&1);equipment->m_pPath=equipment->m_bUnknown25C?paths[0]:NULL;
 unsigned distance=(c.seed/160)%4;equipment->m_fUnknown258=c.mode?length-0.01f:distance==0?-1.0f:distance==1?0.0f:distance==2?length-0.1f:length+0.1f;equipment->m_pSoundBank=reinterpret_cast<CSoundBank*>(&service[0]);equipment->m_pSceneNode=reinterpret_cast<Ogre::SceneNode*>(&service[1]);equipment->m_vPosition=Ogre::Vector3(10,20,30);equipment->m_bEnabled=false;
 for(unsigned r=0;r<4;++r)for(unsigned col=0;col<4;++col){equipment->m_mDropOrientation[r][col]=(r*4+col+1)*0.1f;equipment->m_mOrientation[r][col]=(r==col?2.0f:0.25f);}
 detour::Set patches;TL_REDIRECT(patches,udSpline,&spline);TL_REDIRECT(patches,udPosition,&position);TL_REDIRECT(patches,udSound,&sound);TL_REDIRECT(patches,udIsa,&isa);if(patches.failed())_exit(42);
 float elapsed=c.mode?0.5f:steps[(c.seed/640)%5];for(unsigned repeat=0;repeat<2;++repeat){if(repeat==0){autotest::invoke(out,ours?&tracedoriginalEquipmentUpdateDrop:&originalEquipmentUpdateDrop,equipment,elapsed);}else{if(ours)equipment->updateDrop(elapsed);else originalEquipmentUpdateDrop(equipment,elapsed);}number(equipment->m_bUnknown25C);number(equipment->m_bEnabled);real(equipment->m_fUnknown258);vector(equipment->m_vPosition);matrix(equipment->m_mOrientation);number(enabledCalls);number(sounds);number(positions);number(orientations);number(equipment->m_pPath==paths[1]);}
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_update_drop_differential){
autotest::Coverage coverage0("equipment_update_drop_differential",(uint64_t)(uintptr_t)&originalEquipmentUpdateDrop);
int failures=0;for(unsigned n=0;n<3584;++n){Case c={n<3200?n:n-3200,n<3200?0u:1+(n-3200)/96};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage0.observe(host,a,b);bool ok=pair==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    update drop seed %u mode %u status %d/%d lengths %lu/%lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok){coverage0.report(host);return failures;}}host->log("    equipment update drop: 3584 cases, two calls per side\n");{coverage0.report(host);return failures;}}
