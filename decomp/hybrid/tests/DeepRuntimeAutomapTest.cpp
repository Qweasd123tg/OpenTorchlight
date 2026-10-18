#include "tests/SmallMassCompare.h"
#include "Automap.h"
#include "MasterResourceManager.h"
#include "GameVariables.h"
#include "Settings.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void,deepMapUpdate,(CAutomap*,const Ogre::Vector3&,float),"_ZN8CAutomap6updateERKN4Ogre7Vector3Ef")
DECL(void,deepMapZoom,(CAutomap*,float),"_ZN8CAutomap4zoomEf")
DECL(void,deepMapVisible,(CAutomap*,bool),"_ZN8CAutomap10setVisibleEb")
TL_FUNCTION(deepMapSetFloat,"_ZN20CDynamicPropertyFile8SetFloatEjf")
TL_FUNCTION(deepMapGetInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(deepMapGetFloat,"_ZN20CDynamicPropertyFile8GetFloatEj")
extern "C" char deepMapPosition[] __asm__("_ZN4Ogre6Camera11setPositionERKNS_7Vector3E");
extern "C" char deepMapBillboardPosition[] __asm__("_ZNK4Ogre9Billboard11getPositionEv");
extern "C" char deepMapColour[] __asm__("_ZN4Ogre9Billboard9setColourERKNS_11ColourValueE");
extern "C" char deepMapDimensions[] __asm__("_ZN4Ogre8Viewport13setDimensionsEffff");
extern "C" char deepMapBackground[] __asm__("_ZN4Ogre8Viewport19setBackgroundColourERKNS_11ColourValueE");
extern "C" char deepMapClear[] __asm__("_ZN4Ogre8Viewport18setClearEveryFrameEbj");
extern "C" char deepMapWidth[] __asm__("_ZNK4Ogre8Viewport14getActualWidthEv");
extern "C" char deepMapHeight[] __asm__("_ZNK4Ogre8Viewport15getActualHeightEv");
extern "C" char deepMapCamera[] __asm__("_ZN4Ogre8Viewport9setCameraEPNS_6CameraE");
namespace {using namespace smallmass;void* viewport;
void position(void* p,const Ogre::Vector3& v){event(1,p);vector(v);}
const Ogre::Vector3& billboardPosition(void* p){event(2,p);return field<Ogre::Vector3>(p,0);}
void colour(void* p,const Ogre::ColourValue& value){event(3,p);output->add(&value,sizeof(value));field<Ogre::ColourValue>(p,0x10)=value;}
void frustum(void* p,float l,float r,float t,float b){event(4,p);floating(l);floating(r);floating(t);floating(b);}
void setFloat(void* p,unsigned key,float f){event(5,p);number(key);floating(f);}
int getInt(void* p,unsigned key){event(6,p);number(key);return key==KSETTINGS_RES_WIDTH?1025:769;}
float getFloat(void* p,unsigned key){event(7,p);number(key);return input->index&8?1.25f:.75f;}
void* addViewport(void* p,void* camera,int z,float l,float t,float w,float h){event(8,p);pointer(camera);number(z);floating(l);floating(t);floating(w);floating(h);return viewport;}
void removeViewport(void* p,int z){event(9,p);number(z);}
void dimensions(void* p,float l,float t,float w,float h){event(10,p);floating(l);floating(t);floating(w);floating(h);}
void nodeVisible(void* p,bool visible,bool cascade){event(11,p);number(visible);number(cascade);}
void background(void* p,const Ogre::ColourValue& value){event(12,p);output->add(&value,sizeof(value));}
void clear(void* p,bool yes,unsigned mask){event(13,p);number(yes);number(mask);}
int width(void* p){event(14,p);return input->index&4?400:201;}
int height(void* p){event(15,p);return input->index&4?250:199;}
void aspect(void* p,float f){event(16,p);floating(f);}
void camera(void* p,void* camera){event(17,p);pointer(camera);}
void zoom(CAutomap* p,float delta){event(18,p);floating(delta);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;CAutomap* self=static_cast<CAutomap*>(object(sizeof(CAutomap)));viewport=object(8);void* settings=object(8);void* global=object(0x190);CMasterResourceManager* old=m_pMasterResourceManager;m_pMasterResourceManager=static_cast<CMasterResourceManager*>(global);field<void*>(global,0x90)=settings;void* target=object(8);field<void*>(global,0xb0)=target;void** targetVtable=static_cast<void**>(object(0x68));targetVtable[0x48/8]=reinterpret_cast<void*>(&addViewport);targetVtable[0x60/8]=reinterpret_cast<void*>(&removeViewport);field<void**>(target,0)=targetVtable;void** cameraVtable=static_cast<void**>(object(0x2b8));cameraVtable[0x278/8]=reinterpret_cast<void*>(&aspect);cameraVtable[0x2b0/8]=reinterpret_cast<void*>(&frustum);void* cam=object(8);field<void**>(cam,0)=cameraVtable;self->m_pCamera=static_cast<Ogre::Camera*>(cam);void** nodeVtable=static_cast<void**>(object(0x380));nodeVtable[0x378/8]=reinterpret_cast<void*>(&nodeVisible);void* a=object(8);void* b=object(8);field<void**>(a,0)=field<void**>(b,0)=nodeVtable;self->m_pCullQuad=static_cast<Ogre::SceneNode*>(a);self->m_pOverlayQuad=static_cast<Ogre::SceneNode*>(b);
new(&self->m_vMapTileBillboards)std::vector<Ogre::Billboard*>();new(&self->m_vMapTileRevealValues)std::vector<float>();new(&self->m_vNPCBillboards)std::vector<Ogre::Billboard*>();new(&self->m_vNPCRevealValues)std::vector<float>();new(&self->m_hiddenNPCBillboards)TArrayList<Ogre::Billboard*>(2);self->m_zoom=float(c.index%8)*10;self->m_panelSize=220;self->m_fullMapWidth=600;self->m_fullMapHeight=400;self->m_bFullscreen=c.index&1;self->m_bFullMap=c.index&2;self->m_bVisible=c.index&4;self->m_bTilesChanged=c.index&8;self->m_viewport=c.index&16?static_cast<Ogre::Viewport*>(viewport):0;self->m_minimumX=-2;self->m_minimumZ=-3;self->m_iMapGridWidth=c.index&16?3:8;self->m_iMapGridHeight=8;self->m_pRevealedTiles=new float[64];for(unsigned i=0;i<64;++i)self->m_pRevealedTiles[i]=float((i+c.index)%4)*.25f;for(unsigned i=0;i<c.index%6;++i){void* billboard=object(0x30);field<Ogre::Vector3>(billboard,0)=Ogre::Vector3(float(int(i%3)-1)*12,2,float(int((i+c.index)%4)-1)*8);self->m_vMapTileBillboards.push_back(static_cast<Ogre::Billboard*>(billboard));self->m_vMapTileRevealValues.push_back((c.index&32) && i==0?100.0f:float((i+c.index)%5)*.25f);void* npc=object(0x30);field<Ogre::Vector3>(npc,0)=field<Ogre::Vector3>(billboard,0);self->m_vNPCBillboards.push_back(static_cast<Ogre::Billboard*>(npc));self->m_vNPCRevealValues.push_back(float((i+c.index+1)%5)*.25f);if((i+c.index)%3==0)self->m_hiddenNPCBillboards.add(static_cast<Ogre::Billboard*>(npc));}
detour::Set d;TL_REDIRECT(d,deepMapSetFloat,&setFloat);TL_REDIRECT(d,deepMapGetInt,&getInt);TL_REDIRECT(d,deepMapGetFloat,&getFloat);d.redirect(deepMapPosition,deepMapPosition,&position);d.redirect(deepMapBillboardPosition,deepMapBillboardPosition,&billboardPosition);d.redirect(deepMapColour,deepMapColour,&colour);d.redirect(deepMapDimensions,deepMapDimensions,&dimensions);d.redirect(deepMapBackground,deepMapBackground,&background);d.redirect(deepMapClear,deepMapClear,&clear);d.redirect(deepMapWidth,deepMapWidth,&width);d.redirect(deepMapHeight,deepMapHeight,&height);d.redirect(deepMapCamera,deepMapCamera,&camera);if(c.op==2)d.redirect(reinterpret_cast<char*>(deepMapZoomOld),reinterpret_cast<char*>(deepMapZoomNew),&zoom);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0){Ogre::Vector3 pos(3,-2,4);typedef void(*Fn)(CAutomap*,const Ogre::Vector3&,float);autotest::invoke<Fn,CAutomap*,const Ogre::Vector3&,float>(out,ours?deepMapUpdateNew:deepMapUpdateOld,self,pos,float(c.index%5)*.125f);}else if(c.op==1)autotest::invoke(out,ours?deepMapZoomNew:deepMapZoomOld,self,float(int(c.index%7)-3)*20);else autotest::invoke(out,ours?deepMapVisibleNew:deepMapVisibleOld,self,bool(c.index&32));number(self->m_bTilesChanged);number(self->m_bVisible);floating(self->m_zoom);pointer(self->m_viewport);for(unsigned i=0;i<self->m_vMapTileBillboards.size();++i){floating(self->m_vMapTileRevealValues[i]);out.add(&field<Ogre::ColourValue>(self->m_vMapTileBillboards[i],0x10),sizeof(Ogre::ColourValue));floating(self->m_vNPCRevealValues[i]);out.add(&field<Ogre::ColourValue>(self->m_vNPCBillboards[i],0x10),sizeof(Ogre::ColourValue));}self->m_vMapTileBillboards.~vector();self->m_vMapTileRevealValues.~vector();self->m_vNPCBillboards.~vector();self->m_vNPCRevealValues.~vector();self->m_hiddenNPCBillboards.~TArrayList();delete[] self->m_pRevealedTiles;m_pMasterResourceManager=old;}
}
TL_TEST(deep_runtime_automap_update){return smallmass::run(host,0,"deep_runtime_automap_update",(uintptr_t)deepMapUpdateOld,execute,256);}
TL_TEST(deep_runtime_automap_zoom){return smallmass::run(host,1,"deep_runtime_automap_zoom",(uintptr_t)deepMapZoomOld,execute,96);}
TL_TEST(deep_runtime_automap_visible){return smallmass::run(host,2,"deep_runtime_automap_visible",(uintptr_t)deepMapVisibleOld,execute,128);}
