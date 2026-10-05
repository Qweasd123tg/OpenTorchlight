#include <cstring>
#include <climits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(int,originalStrengthReq,(CEquipment*,CCharacter*),"_ZN10CEquipment22getStrengthRequirementEP10CCharacter")
TL_ORIGINAL(int,originalDexterityReq,(CEquipment*,CCharacter*),"_ZN10CEquipment23getDexterityRequirementEP10CCharacter")
TL_ORIGINAL(int,originalMagicReq,(CEquipment*,CCharacter*),"_ZN10CEquipment19getMagicRequirementEP10CCharacter")
TL_ORIGINAL(int,originalDefenseReq,(CEquipment*,CCharacter*),"_ZN10CEquipment21getDefenseRequirementEP10CCharacter")
TL_ORIGINAL(int,originalLevelReq,(CEquipment*,CCharacter*),"_ZN10CEquipment19getLevelRequirementEP10CCharacter")
TL_FUNCTION(rvIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(rvEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned seed,kind,mask,mode;bool nullActor;int base;float general,category;};const Case*input;CEquipment*item;CCharacter*actor;autotest::Capture*capture;unsigned calls;
void number(int n){capture->add(&n,sizeof(n));}
void change(){if(input->mode==1){item->m_iUnknown278=7;item->m_iUnknown27C=11;item->m_iUnknown280=13;item->m_iUnknown284=17;item->m_iUnknown288=19;}}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(10);number(p==item);number(t);change();unsigned bit=t==UNITTYPES::ITEMCATEGORYMARTIAL?1:t==UNITTYPES::ITEMCATEGORYRANGED?2:t==UNITTYPES::ITEMCATEGORYMAGIC?4:t==UNITTYPES::ARMOR?8:t==UNITTYPES::SPELL?16:0;return input->mask&bit;}
float effect(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES damage){number(11);number(p==actor);number(t);number(damage);++calls;change();if(t==static_cast<EEFFECT_TYPE>(93))return input->general;unsigned id=t==static_cast<EEFFECT_TYPE>(98)?0:t==static_cast<EEFFECT_TYPE>(100)?1:t==static_cast<EEFFECT_TYPE>(101)?2:t==static_cast<EEFFECT_TYPE>(94)?3:4;return input->category+static_cast<float>(id)*0.25f;}
void side(const Case&c,bool ours,autotest::Capture&out){Raw<CEquipment>a;Raw<CCharacter>b;item=a.get();actor=b.get();input=&c;capture=&out;calls=0;item->m_iUnknown278=c.base;item->m_iUnknown27C=c.base+1;item->m_iUnknown280=c.base+2;item->m_iUnknown284=c.base+3;item->m_iUnknown288=c.base+4;
 detour::Set patches;TL_REDIRECT(patches,rvIsa,&isa);TL_REDIRECT(patches,rvEffect,&effect);if(patches.failed())_exit(42);CCharacter*p=c.nullActor?NULL:actor;
 for(unsigned repeat=0;repeat<2;++repeat){int result=0;switch(c.kind){case 0:result=ours?item->getStrengthRequirement(p):originalStrengthReq(item,p);break;case 1:result=ours?item->getDexterityRequirement(p):originalDexterityReq(item,p);break;case 2:result=ours?item->getMagicRequirement(p):originalMagicReq(item,p);break;case 3:result=ours?item->getDefenseRequirement(p):originalDefenseReq(item,p);break;case 4:result=ours?item->getLevelRequirement(p):originalLevelReq(item,p);break;}number(result);number(calls);number(item->m_iUnknown278);number(item->m_iUnknown27C);number(item->m_iUnknown280);number(item->m_iUnknown284);number(item->m_iUnknown288);}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_requirement_values_differential){int failures=0;for(unsigned n=0;n<15360;++n){unsigned q=n/5;static const int base[]={-10,-1,0,1,7,10,30,100};static const float values[]={-20.75f,-2.8f,-1.2f,-0.8f,-0.2f,0.0f,0.2f,0.8f,1.2f,1.8f,20.7f,100.9f};Case c={n,n%5,q%32,0,(q/32)%2!=0,base[(q/64)%8],values[(q/7)%12],values[(q/11)%12]};if(q>=2048){c.mask=1u<<(q%5);c.nullActor=false;c.mode=(q/512)%2;c.base=base[(q/144)%8];c.general=values[q%12];c.category=values[(q/12)%12];}
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    requirement values case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}
 host->log("    requirement values: 15360 cases, five entries, two calls per side\n");return failures;}
