#include <cstring>
#include <map>
#include <string>
#include <new>
#include "tests/SmallMassCompare.h"
#include "SkillController.h"
TL_ORIGINAL(void,scOldCtor,(CSkillController*,CResourceManager*),"_ZN16CSkillControllerC1EP16CResourceManager")
extern "C" void scNewCtor(CSkillController*,CResourceManager*) __asm__("_ZN16CSkillControllerC1EP16CResourceManager");
TL_FUNCTION(scBaseCtor,"_ZN19CPositionableObjectC2EP16CResourceManagerPN4Ogre12SceneManagerE")
namespace {
using namespace smallmass;
CResourceManager* expected;
void base(CPositionableObject*self,CResourceManager*r,Ogre::SceneManager*s){number(1);number(r==expected);number(s!=NULL);std::memset(self,0x5a,sizeof(CPositionableObject));}
void ctorSide(Case&c,bool ours,autotest::Capture&out){
 output=&out;
 new(reinterpret_cast<void*>(0x1521d28))std::wstring();
 const wchar_t*names[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(0x1523300+8*i))std::wstring(names[i]);
 CSkillController*self=static_cast<CSkillController*>(object(sizeof(CSkillController)));expected=c.index&1?reinterpret_cast<CResourceManager*>(0x123450):NULL;
 typedef void(*Fn)(CSkillController*,CResourceManager*);Fn fn=ours?scNewCtor:scOldCtor;
 if(!autotest::beginInvocation(out,fn))return;fn(self,expected);out.callCompleted=1;
 // The base body is a collaborator boundary; its tail bytes must survive the derived constructor.
 out.add(reinterpret_cast<char*>(self)+sizeof(void*),sizeof(CPositionableObject)-sizeof(void*));
 number(self->m_pResourceManager==expected);number(self->m_pUnitInteractDataGroup!=NULL);number(self->m_pRunicCore!=NULL);number(self->m_iRunicCoreSafePointerId);
 text(self->m_sCategory);text(self->m_sUnitInteractWith);text(self->m_sSkillName);
 number(self->m_pSecondaryRunicCore!=NULL);number(self->m_iSecondaryRunicCoreSafePointerId);
 number(self->m_bLearnSkillOnStart);number(self->m_bUnlearnSkillOnStop);number(self->m_bSkillStartRequested);number(self->m_bSkillStopRequested);number(self->m_bForceStop);number(self->m_bUsePlayerAsTarget);number(self->m_bUseUnitTarget);number(self->m_iSkillLevel);
 self->m_sCategory.~basic_string();self->m_sUnitInteractWith.~basic_string();self->m_sSkillName.~basic_string();
}
}
TL_TEST(complete_skill_controller_constructor){detour::Set h;TL_REDIRECT(h,scBaseCtor,&base);if(h.failed())return 1;return smallmass::run(host,0,"complete_skill_controller_constructor",0xe17970,&ctorSide,8);}
