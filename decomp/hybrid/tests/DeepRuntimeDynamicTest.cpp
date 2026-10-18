#include "tests/SmallMassCompare.h"
#include "DynamicLine.h"
TL_ORIGINAL(void,deepDynamicOld,(void*,int),"_ZN12CDynamicLineC1EN4Ogre15RenderOperation13OperationTypeE")
extern "C" void deepDynamicNew(void*,int) __asm__("_ZN12CDynamicLineC1EN4Ogre15RenderOperation13OperationTypeE");
TL_FUNCTION(deepDynamicBase,"_ZN18CDynamicRenderableC1Ev")
TL_FUNCTION(deepDynamicInit,"_ZN18CDynamicRenderable10initializeEN4Ogre15RenderOperation13OperationTypeEb")
extern "C" char deepDynamicMaterial[] __asm__("_ZN4Ogre16SimpleRenderable11setMaterialERKSs");
namespace {using namespace smallmass;
void base(void* p){event(1,p);}
void initialize(void* p,int op,bool index){event(2,p);number(op);number(index);}
void material(void* p,const std::string& name){event(3,p);text(name);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;void* self=object(sizeof(CDynamicLine));detour::Set d;TL_REDIRECT(d,deepDynamicBase,&base);TL_REDIRECT(d,deepDynamicInit,&initialize);d.redirect(deepDynamicMaterial,deepDynamicMaterial,&material);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}autotest::invoke(out,ours?deepDynamicNew:deepDynamicOld,self,int(c.index%8));std::vector<Ogre::Vector3>& points=field<std::vector<Ogre::Vector3> >(self,0x218);number(points.size());number(points.capacity());number(field<bool>(self,0x230));for(unsigned i=0;i<c.index%5;++i)points.push_back(Ogre::Vector3(i,2*i,-float(i)));number(points.size());for(unsigned i=0;i<points.size();++i)vector(points[i]);points.~vector();}
}
TL_TEST(deep_runtime_dynamic_constructor){return smallmass::run(host,0,"deep_runtime_dynamic_constructor",(uintptr_t)deepDynamicOld,execute,64);}
