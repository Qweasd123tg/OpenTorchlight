// SYNTHETIC OWNERS ONLY. No game logic or original class layout is tested.
#include "CEGUISubscriberSlot.h"
#include "CEGUIEventArgs.h"
#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
static int trace_value=0;
struct CCombineMenu {
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=1;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=2;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=3;return e.handled; }
CEGUI::SubscriberSlot make_0() { return CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_1() { return CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_2() { return CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_3() { return CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOut, this); }
};
struct CEnchantMenu {
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=4;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=5;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=6;return e.handled; }
CEGUI::SubscriberSlot make_4() { return CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_5() { return CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_6() { return CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_7() { return CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOut, this); }
};
struct CGameUI {
bool handle_ClickThrough(const CEGUI::EventArgs& e) { trace_value=7;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=8;return e.handled; }
bool handle_SkillClick(const CEGUI::EventArgs& e) { trace_value=9;return e.handled; }
bool handle_SkillMouseOut(const CEGUI::EventArgs& e) { trace_value=10;return e.handled; }
bool handle_SkillMouseOver(const CEGUI::EventArgs& e) { trace_value=11;return e.handled; }
bool handle_onClick(const CEGUI::EventArgs& e) { trace_value=12;return e.handled; }
CEGUI::SubscriberSlot make_8() { return CEGUI::SubscriberSlot(&CGameUI::handle_onClick, this); }
CEGUI::SubscriberSlot make_9() { return CEGUI::SubscriberSlot(&CGameUI::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_10() { return CEGUI::SubscriberSlot(&CGameUI::handle_ClickThrough, this); }
CEGUI::SubscriberSlot make_11() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_12() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_13() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOut, this); }
CEGUI::SubscriberSlot make_14() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillClick, this); }
CEGUI::SubscriberSlot make_15() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_16() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_17() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOut, this); }
CEGUI::SubscriberSlot make_18() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillClick, this); }
CEGUI::SubscriberSlot make_19() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_20() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_21() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOut, this); }
CEGUI::SubscriberSlot make_22() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillClick, this); }
CEGUI::SubscriberSlot make_23() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOver, this); }
CEGUI::SubscriberSlot make_24() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillMouseOut, this); }
CEGUI::SubscriberSlot make_25() { return CEGUI::SubscriberSlot(&CGameUI::handle_SkillClick, this); }
};
struct CInventoryMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=13;return e.handled; }
bool handle_EndRotateLeft(const CEGUI::EventArgs& e) { trace_value=14;return e.handled; }
bool handle_EndRotateRight(const CEGUI::EventArgs& e) { trace_value=15;return e.handled; }
bool handle_ItemClick(const CEGUI::EventArgs& e) { trace_value=16;return e.handled; }
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=17;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=18;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=19;return e.handled; }
bool handle_SetSpell(const CEGUI::EventArgs& e) { trace_value=20;return e.handled; }
bool handle_SpellMouseOut(const CEGUI::EventArgs& e) { trace_value=21;return e.handled; }
bool handle_SpellMouseOver(const CEGUI::EventArgs& e) { trace_value=22;return e.handled; }
CEGUI::SubscriberSlot make_26() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_27() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_CloseButton, this); }
CEGUI::SubscriberSlot make_28() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_ItemClick, this); }
CEGUI::SubscriberSlot make_29() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateLeft, this); }
CEGUI::SubscriberSlot make_30() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateLeft, this); }
CEGUI::SubscriberSlot make_31() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateRight, this); }
CEGUI::SubscriberSlot make_32() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateRight, this); }
CEGUI::SubscriberSlot make_33() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_34() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_35() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_36() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_37() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_38() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_39() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_SpellMouseOver, this); }
CEGUI::SubscriberSlot make_40() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_SpellMouseOut, this); }
CEGUI::SubscriberSlot make_41() { return CEGUI::SubscriberSlot(&CInventoryMenu::handle_SetSpell, this); }
};
struct CJournalMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=23;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=24;return e.handled; }
CEGUI::SubscriberSlot make_42() { return CEGUI::SubscriberSlot(&CJournalMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_43() { return CEGUI::SubscriberSlot(&CJournalMenu::handle_CloseButton, this); }
};
struct CMerchantMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=25;return e.handled; }
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=26;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=27;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=28;return e.handled; }
bool handle_PetMouseOut(const CEGUI::EventArgs& e) { trace_value=29;return e.handled; }
bool handle_PetMouseOver(const CEGUI::EventArgs& e) { trace_value=30;return e.handled; }
CEGUI::SubscriberSlot make_44() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_45() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_CloseButton, this); }
CEGUI::SubscriberSlot make_46() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_47() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_48() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_49() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOver, this); }
CEGUI::SubscriberSlot make_50() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOver, this); }
CEGUI::SubscriberSlot make_51() { return CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOut, this); }
};
struct CPetMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=31;return e.handled; }
bool handle_EndRotateLeft(const CEGUI::EventArgs& e) { trace_value=32;return e.handled; }
bool handle_EndRotateRight(const CEGUI::EventArgs& e) { trace_value=33;return e.handled; }
bool handle_ItemClick(const CEGUI::EventArgs& e) { trace_value=34;return e.handled; }
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=35;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=36;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=37;return e.handled; }
bool handle_SetSpell(const CEGUI::EventArgs& e) { trace_value=38;return e.handled; }
bool handle_SpellMouseOut(const CEGUI::EventArgs& e) { trace_value=39;return e.handled; }
bool handle_SpellMouseOver(const CEGUI::EventArgs& e) { trace_value=40;return e.handled; }
CEGUI::SubscriberSlot make_52() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_53() { return CEGUI::SubscriberSlot(&CPetMenu::handle_CloseButton, this); }
CEGUI::SubscriberSlot make_54() { return CEGUI::SubscriberSlot(&CPetMenu::handle_ItemClick, this); }
CEGUI::SubscriberSlot make_55() { return CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateLeft, this); }
CEGUI::SubscriberSlot make_56() { return CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateLeft, this); }
CEGUI::SubscriberSlot make_57() { return CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateRight, this); }
CEGUI::SubscriberSlot make_58() { return CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateRight, this); }
CEGUI::SubscriberSlot make_59() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_60() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_61() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_62() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_63() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_64() { return CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_65() { return CEGUI::SubscriberSlot(&CPetMenu::handle_SpellMouseOver, this); }
CEGUI::SubscriberSlot make_66() { return CEGUI::SubscriberSlot(&CPetMenu::handle_SpellMouseOut, this); }
CEGUI::SubscriberSlot make_67() { return CEGUI::SubscriberSlot(&CPetMenu::handle_SetSpell, this); }
};
struct CQuestMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=41;return e.handled; }
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=42;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=43;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=44;return e.handled; }
bool handle_QuestClick(const CEGUI::EventArgs& e) { trace_value=45;return e.handled; }
CEGUI::SubscriberSlot make_68() { return CEGUI::SubscriberSlot(&CQuestMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_69() { return CEGUI::SubscriberSlot(&CQuestMenu::handle_CloseButton, this); }
CEGUI::SubscriberSlot make_70() { return CEGUI::SubscriberSlot(&CQuestMenu::handle_QuestClick, this); }
CEGUI::SubscriberSlot make_71() { return CEGUI::SubscriberSlot(&CQuestMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_72() { return CEGUI::SubscriberSlot(&CQuestMenu::handle_MouseOut, this); }
};
struct CStashMenu {
bool handle_CloseButton(const CEGUI::EventArgs& e) { trace_value=46;return e.handled; }
bool handle_MouseOut(const CEGUI::EventArgs& e) { trace_value=47;return e.handled; }
bool handle_MouseOver(const CEGUI::EventArgs& e) { trace_value=48;return e.handled; }
bool handle_MouseThrough(const CEGUI::EventArgs& e) { trace_value=49;return e.handled; }
bool handle_PetMouseOut(const CEGUI::EventArgs& e) { trace_value=50;return e.handled; }
bool handle_PetMouseOver(const CEGUI::EventArgs& e) { trace_value=51;return e.handled; }
CEGUI::SubscriberSlot make_73() { return CEGUI::SubscriberSlot(&CStashMenu::handle_MouseThrough, this); }
CEGUI::SubscriberSlot make_74() { return CEGUI::SubscriberSlot(&CStashMenu::handle_CloseButton, this); }
CEGUI::SubscriberSlot make_75() { return CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_76() { return CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOver, this); }
CEGUI::SubscriberSlot make_77() { return CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOut, this); }
CEGUI::SubscriberSlot make_78() { return CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOver, this); }
CEGUI::SubscriberSlot make_79() { return CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOver, this); }
CEGUI::SubscriberSlot make_80() { return CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOut, this); }
};

struct PmfBits { intptr_t target, adjustment; };
struct AdapterBits { void* vptr; PmfBits pmf; void* receiver; };
template<class T> AdapterBits view(const CEGUI::MemberFunctionSlot<T>& slot) {
    AdapterBits b;
    if (sizeof(b)!=sizeof(slot)) { std::cerr<<"unsupported adapter ABI";std::exit(2); }
    std::memcpy(&b,&slot,sizeof(b)); return b;
}
struct First { virtual ~First(){}; int a; };
struct Second {
    virtual ~Second(){};
    virtual bool changed(const CEGUI::EventArgs&) { trace_value=701;return false; }
    bool direct(const CEGUI::EventArgs&) { trace_value=702;return true; }
};
struct Derived: First,Second {
    bool changed(const CEGUI::EventArgs&) { trace_value=703;return true; }
};
int test_pmf() {
    int errors=0; CEGUI::EventArgs e; Derived d;
    typedef bool(Derived::*P)(const CEGUI::EventArgs&);
    P v=static_cast<P>(&Second::changed), n=static_cast<P>(&Second::direct);
    CEGUI::MemberFunctionSlot<Derived> sv(v,&d), sn(n,&d);
    AdapterBits vb=view(sv),nb=view(sn);
    const intptr_t adjustment=reinterpret_cast<char*>(static_cast<Second*>(&d))-reinterpret_cast<char*>(&d);
    trace_value=0; if(!sv(e)||trace_value!=703) ++errors;
    trace_value=0; if(!sn(e)||trace_value!=702) ++errors;
    if(!(vb.pmf.target&1)||!adjustment||vb.pmf.adjustment!=adjustment||nb.pmf.adjustment!=adjustment) ++errors;
    if(nb.pmf.target&1) ++errors;
    if(vb.receiver!=&d||nb.receiver!=&d) ++errors;
    std::cout<<"PMF "<<adjustment<<" "<<vb.pmf.target<<" "<<vb.pmf.adjustment<<" "<<errors<<"\n";
    return errors;
}

int main(){ int errors=0,checks=0;CEGUI::EventArgs e;
{ CCombineMenu object;
{ CEGUI::SubscriberSlot s=object.make_0(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=3)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_1(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=2)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_2(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=2)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_3(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=1)++errors;}s.cleanup(); }
}
{ CEnchantMenu object;
{ CEGUI::SubscriberSlot s=object.make_4(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=6)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_5(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=5)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_6(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=5)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_7(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=4)++errors;}s.cleanup(); }
}
{ CGameUI object;
{ CEGUI::SubscriberSlot s=object.make_8(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=12)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_9(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=8)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_10(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=7)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_11(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_12(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_13(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=10)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_14(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=9)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_15(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_16(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_17(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=10)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_18(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=9)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_19(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_20(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_21(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=10)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_22(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=9)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_23(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=11)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_24(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=10)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_25(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=9)++errors;}s.cleanup(); }
}
{ CInventoryMenu object;
{ CEGUI::SubscriberSlot s=object.make_26(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=19)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_27(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=13)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_28(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=16)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_29(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=14)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_30(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=14)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_31(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=15)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_32(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=15)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_33(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=18)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_34(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=18)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_35(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=17)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_36(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=18)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_37(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=18)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_38(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=17)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_39(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=22)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_40(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=21)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_41(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=20)++errors;}s.cleanup(); }
}
{ CJournalMenu object;
{ CEGUI::SubscriberSlot s=object.make_42(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=24)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_43(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=23)++errors;}s.cleanup(); }
}
{ CMerchantMenu object;
{ CEGUI::SubscriberSlot s=object.make_44(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=28)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_45(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=25)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_46(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=27)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_47(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=27)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_48(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=26)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_49(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=30)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_50(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=30)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_51(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=29)++errors;}s.cleanup(); }
}
{ CPetMenu object;
{ CEGUI::SubscriberSlot s=object.make_52(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=37)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_53(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=31)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_54(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=34)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_55(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=32)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_56(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=32)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_57(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=33)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_58(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=33)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_59(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=36)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_60(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=36)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_61(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=35)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_62(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=36)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_63(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=36)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_64(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=35)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_65(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=40)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_66(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=39)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_67(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=38)++errors;}s.cleanup(); }
}
{ CQuestMenu object;
{ CEGUI::SubscriberSlot s=object.make_68(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=44)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_69(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=41)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_70(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=45)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_71(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=43)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_72(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=42)++errors;}s.cleanup(); }
}
{ CStashMenu object;
{ CEGUI::SubscriberSlot s=object.make_73(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=49)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_74(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=46)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_75(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=48)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_76(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=48)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_77(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=47)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_78(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=51)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_79(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=51)++errors;}s.cleanup(); }
{ CEGUI::SubscriberSlot s=object.make_80(); for(int flag=0;flag<2;++flag){e.handled=flag!=0;trace_value=0;bool v=s(e);++checks;if(v!=e.handled||trace_value!=50)++errors;}s.cleanup(); }
}
errors+=test_pmf();std::cout<<"TOTAL "<<checks<<" "<<errors<<"\n";return errors?1:0;}
