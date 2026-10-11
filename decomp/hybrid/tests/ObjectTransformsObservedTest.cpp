#include <cstring>
#include <vector>
#include <new>
#include <fenv.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Settings.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" void* positionTable[] __asm__("_ZTV19CPositionableObject");
extern "C" void* objectTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" char randomTarget[] __asm__("_ZN4Ogre4Math11RangeRandomEff");
TL_ORIGINAL(void,original0,(void*,void*),"_ZN16CObjectControl3D10ResetScaleER10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate0(void*,void*) __asm__("_ZN16CObjectControl3D10ResetScaleER10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original1,(void*,void*),"_ZN16CObjectControl3D16ResetOrientationER10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate1(void*,void*) __asm__("_ZN16CObjectControl3D16ResetOrientationER10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original2,(void*,bool,void*),"_ZN16CObjectControl3D19snapObjectsToGroundEbR10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate2(void*,bool,void*) __asm__("_ZN16CObjectControl3D19snapObjectsToGroundEbR10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original3,(void*,float,void*),"_ZN16CObjectControl3D18ApplyRotationNoiseEfR10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate3(void*,float,void*) __asm__("_ZN16CObjectControl3D18ApplyRotationNoiseEfR10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original4,(void*,float,void*),"_ZN16CObjectControl3D16ApplyNormalNoiseEfR10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate4(void*,float,void*) __asm__("_ZN16CObjectControl3D16ApplyNormalNoiseEfR10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original5,(void*,float,bool,void*),"_ZN16CObjectControl3D15ApplyScaleNoiseEfbR10TArrayListIP17CEditorBaseObjectE")
extern "C" void candidate5(void*,float,bool,void*) __asm__("_ZN16CObjectControl3D15ApplyScaleNoiseEfbR10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(Ogre::Vector3,original6,(void*,void*),"_ZN16CObjectControl3D16getSelectedPivotER10TArrayListIP17CEditorBaseObjectE")
extern "C" Ogre::Vector3 candidate6(void*,void*) __asm__("_ZN16CObjectControl3D16getSelectedPivotER10TArrayListIP17CEditorBaseObjectE");
TL_ORIGINAL(void,original7,(void*),"_ZN16CObjectControl3D18UpdateWorkingPlaneEv")
extern "C" void candidate7(void*) __asm__("_ZN16CObjectControl3D18UpdateWorkingPlaneEv");
TL_ORIGINAL(void,original8,(void*),"_ZN9CSettingsD1Ev")
extern "C" void candidate8(void*) __asm__("_ZN9CSettingsD1Ev");
TL_FUNCTION(target_createUndo,"_ZN16CObjectControl3D10createUndoER10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(target_editor,"_ZN7CEditor12getSingletonEv")
TL_FUNCTION(target_addUndo,"_ZN7CEditor7addUndoEP5CUndob")
TL_FUNCTION(target_snap,"_ZN16CObjectControl3D18snapObjectToGroundEP19CPositionableObjectb")
TL_FUNCTION(target_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(target_planePosition,"_ZN16CObjectControl3D23getWorkingPlanePositionEv")
TL_FUNCTION(target_setPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(target_settingsBase,"_ZN20CDynamicPropertyFileD1Ev")

namespace {
struct List{void**data;unsigned count,capacity,grow,padding;};struct Case{unsigned op,seed,mode;float amount;};Case*input;autotest::Capture*output;void*active;void*objects[8];void*nodes[8];void*editors[2];void*undos[2];List*selection;unsigned calls;
void num(unsigned n){output->add(&n,4);}void ptr(void*p){output->add(&p,8);}void event(unsigned n,void*p){num(n);ptr(p);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void integer(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}
void change(){if(input->mode==3&&selection->count>1)--selection->count;if(input->mode==4)editorGlobal=editors[1];}
void createUndo(void*p,List*list){event(1,p);ptr(list);num(list->count);put(p,0xf78,undos[0]);change();}
void*editor(){num(2);++calls;change();return editors[(calls+input->seed)%2];}
void addUndo(void*p,void*undo,bool clear){event(3,p);ptr(undo);num(clear);output->add(undo,40);if(input->mode==5)put(active,0xf78,undos[1]);}
void deleteUndo(void*p){event(4,p);output->add(p,40);if(input->mode==5)put(active,0xf78,undos[1]);}
void snap(void*p,void*object,bool orient){event(5,p);ptr(object);num(orient);change();}
Ogre::Vector3 position(void*p,bool absolute){event(6,p);num(absolute);change();unsigned i=0;for(;i<8&&p!=objects[i];++i){}return Ogre::Vector3(input->amount,static_cast<float>(i)-2.5f,static_cast<float>(i)*input->amount);}
Ogre::Vector3 planePosition(void*p){event(7,p);change();return Ogre::Vector3(input->amount,-3.25f,9.5f);}
void setPosition(void*p,const Ogre::Vector3&v){event(8,p);output->add(&v,12);change();std::memcpy(static_cast<char*>(p)+0x70,&v,12);}
void scale(void*p,float x,float y,float z){event(9,p);output->add(&x,4);output->add(&y,4);output->add(&z,4);std::memcpy(static_cast<char*>(p)+0x7c,&x,4);std::memcpy(static_cast<char*>(p)+0x80,&y,4);std::memcpy(static_cast<char*>(p)+0x84,&z,4);change();}
void visible(void*p,bool v){event(10,p);num(v);change();}
float scaleX(void*p){event(11,p);change();return input->amount;}
float scaleY(void*p){event(12,p);change();return -input->amount;}
float scaleZ(void*p){event(13,p);change();return 0.75f;}
void orientation(void*p,const Ogre::Quaternion&q){event(14,p);output->add(&q,16);change();std::memcpy(static_cast<char*>(p)+0xa0,&q,16);}
void nodeOrientation(void*p,const Ogre::Quaternion&q){event(15,p);output->add(&q,16);change();std::memcpy(static_cast<char*>(p)+16,&q,16);}
const Ogre::Quaternion& getOrientation(void*p){event(16,p);change();return *reinterpret_cast<Ogre::Quaternion*>(static_cast<char*>(p)+16);}
void roll(void*p,const float&a,int space){event(17,p);output->add(&a,4);num(space);reinterpret_cast<float*>(static_cast<char*>(p)+16)[1]+=a;change();}
void pitch(void*p,const float&a,int space){event(18,p);output->add(&a,4);num(space);reinterpret_cast<float*>(static_cast<char*>(p)+16)[2]+=a;change();}
void yaw(void*p,const float&a,int space){event(19,p);output->add(&a,4);num(space);reinterpret_cast<float*>(static_cast<char*>(p)+16)[3]+=a;change();}
float random(float low,float high){num(20);output->add(&low,4);output->add(&high,4);++calls;change();if(input->mode==6)for(unsigned i=0;i<8;++i)put(objects[i],0x58,nodes[(i+1)%8]);return input->mode==7?high:input->mode==8?low:static_cast<float>(int(calls%7)-3)*0.125f;}
void settingsBase(void*p){event(21,p);output->add(p,0x160);}
void deleteParser(void*p){event(22,p);output->add(active,0x160);if(input->mode==5)put(active,0x148,NULL);}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;unsigned long long self[0xf88/8]={0},obj[8][64]={{0}},node[8][8]={{0}},ed[2][64]={{0}},manager[2][32]={{0}},undo[2][5]={{0}};active=self;
 void*table[60];std::memcpy(table,positionTable,480);table[2+19]=reinterpret_cast<void*>(&scale);table[2+10]=reinterpret_cast<void*>(&visible);table[2+22]=reinterpret_cast<void*>(&scaleX);table[2+23]=reinterpret_cast<void*>(&scaleY);table[2+24]=reinterpret_cast<void*>(&scaleZ);table[2+33]=reinterpret_cast<void*>(&orientation);
 void*nodeTable[60]={0};nodeTable[0xc8/8]=reinterpret_cast<void*>(&getOrientation);nodeTable[0xd0/8]=reinterpret_cast<void*>(&nodeOrientation);nodeTable[0x168/8]=reinterpret_cast<void*>(&roll);nodeTable[0x170/8]=reinterpret_cast<void*>(&pitch);nodeTable[0x178/8]=reinterpret_cast<void*>(&yaw);
 void*undoTable[2]={NULL,reinterpret_cast<void*>(&deleteUndo)};
 for(unsigned i=0;i<8;++i){objects[i]=obj[i];nodes[i]=node[i];put(objects[i],0,(i+c.seed)%4==0?objectTable+2:table+2);put(objects[i],0x58,nodes[i]);put(nodes[i],0,nodeTable);Ogre::Quaternion q(2.0f+i,0.125f,-0.25f,0.5f);std::memcpy(static_cast<char*>(nodes[i])+16,&q,16);}
 for(unsigned i=0;i<2;++i){editors[i]=ed[i];put(editors[i],0x120,manager[i]);integer(editors[i],0x64,(c.seed/10)%2?512:0);undos[i]=undo[i];put(undos[i],0,undoTable);integer(undos[i],0x18,(c.seed/10)%3);}
 editorGlobal=editors[0];void*values[8];for(unsigned i=0;i<8;++i)values[i]=(c.seed+i)%5?objects[i]:NULL;List list={values,(c.seed/10)%9,c.mode==9?2:8,2,0};selection=&list;
 std::vector<void*>*models=new(reinterpret_cast<char*>(self)+0xc8)std::vector<void*>;const unsigned counts[]={0,9,19,20,24};for(unsigned i=0;i<counts[(c.seed/10)%5];++i)models->push_back(objects[i%8]);
 if(c.op==7)for(unsigned i=0;i<8;++i)put(objects[i],0,table+2);
 std::memcpy(reinterpret_cast<char*>(self)+0x1fc,&c.amount,4);std::memcpy(reinterpret_cast<char*>(self)+0xec,&c.amount,4);
 if(c.op==8){std::memset(self,(c.seed*47+11)&255,0x160);void*parserTable[2]={NULL,reinterpret_cast<void*>(&deleteParser)};put(nodes[0],0,parserTable);put(self,0x140,c.seed&1?NULL:nodes[0]);CSettingsResolution*array=c.seed%3?new CSettingsResolution[c.seed%9+1]:NULL;put(self,0x148,array);
  detour::Set patches;TL_REDIRECT(patches,target_settingsBase,&settingsBase);if(patches.failed())_exit(42);autotest::invoke(out,ours?candidate8:original8,active);out.add(active,0x160);patches.restore();return;}
 detour::Set patches;
 TL_REDIRECT(patches,target_createUndo,&createUndo);
 TL_REDIRECT(patches,target_editor,&editor);
 TL_REDIRECT(patches,target_addUndo,&addUndo);
 TL_REDIRECT(patches,target_snap,&snap);
 TL_REDIRECT(patches,target_position,&position);
 TL_REDIRECT(patches,target_planePosition,&planePosition);
 TL_REDIRECT(patches,target_setPosition,&setPosition);

 patches.redirect(randomTarget,randomTarget,&random);if(patches.failed())_exit(41);feclearexcept(FE_ALL_EXCEPT);
 switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,active,static_cast<void*>(&list));break;case 1:autotest::invoke(out,ours?candidate1:original1,active,static_cast<void*>(&list));break;case 2:autotest::invoke(out,ours?candidate2:original2,active,(c.seed/10&1)!=0,static_cast<void*>(&list));break;
 case 3:autotest::invoke(out,ours?candidate3:original3,active,c.amount,static_cast<void*>(&list));break;case 4:autotest::invoke(out,ours?candidate4:original4,active,c.amount,static_cast<void*>(&list));break;case 5:autotest::invoke(out,ours?candidate5:original5,active,c.amount,(c.seed/10&1)!=0,static_cast<void*>(&list));break;
 case 6:{Ogre::Vector3(*fn)(void*,void*)=ours?candidate6:original6;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 result=fn(active,&list);out.callCompleted=1;out.add(&result,12);break;}
 case 7:autotest::invoke(out,ours?candidate7:original7,active);break;}
 num(fetestexcept(FE_ALL_EXCEPT));num(calls);ptr(editorGlobal);out.add(&list,sizeof(list));out.add(values,sizeof(values));num(models->size());for(unsigned i=0;i<models->size();++i)ptr((*models)[i]);std::memset(reinterpret_cast<char*>(self)+0xc8,0,24);out.add(self,sizeof(self));out.add(obj,sizeof(obj));out.add(node,sizeof(node));out.add(ed,sizeof(ed));out.add(manager,sizeof(manager));out.add(undo,sizeof(undo));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)original8};autotest::Coverage coverage(name,addresses[op]);const unsigned bits[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x3eaaaaabu,0x43b40000u,0x7f800000u,0xff800000u,0x7fc00123u};
 for(unsigned n=0;n<450;++n){Case c={op,n,n%10,0};unsigned raw=bits[(n/10)%9];std::memcpy(&c.amount,&raw,4);autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    object transforms %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned end=a.capture.length<b.capture.length?a.capture.length:b.capture.length;for(unsigned i=0;i<end;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u %u/%u\n",i,a.capture.data[i],b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(transforms_reset_scale_observed){return run(host,0,"transforms_reset_scale_observed");}
TL_TEST(transforms_reset_orientation_observed){return run(host,1,"transforms_reset_orientation_observed");}
TL_TEST(transforms_snap_observed){return run(host,2,"transforms_snap_observed");}
TL_TEST(transforms_rotation_noise_observed){return run(host,3,"transforms_rotation_noise_observed");}
TL_TEST(transforms_normal_noise_observed){return run(host,4,"transforms_normal_noise_observed");}
TL_TEST(transforms_scale_noise_observed){return run(host,5,"transforms_scale_noise_observed");}
TL_TEST(transforms_pivot_observed){return run(host,6,"transforms_pivot_observed");}
TL_TEST(transforms_plane_observed){return run(host,7,"transforms_plane_observed");}
TL_TEST(transforms_settings_destroy_observed){return run(host,8,"transforms_settings_destroy_observed");}
