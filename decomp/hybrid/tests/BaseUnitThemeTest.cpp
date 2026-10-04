#include <cstring>
#include <new>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "Editor.h"
#include "UnitThemes.h"

TL_ORIGINAL(void, originalEditorTheme, (CBaseUnit*,unsigned int), "_ZN9CBaseUnit16setEditorThemeIDEj")
extern CUnitThemes* testUnitThemes __asm__("_ZL13g_pUnitThemes");
namespace {
struct Case { unsigned int seed; };
void pointerAt(void* p,size_t offset,void* value) {std::memcpy(static_cast<char*>(p)+offset,&value,sizeof(value));}
void side(Case& c,bool ours,autotest::Capture& out) {
    long long base[0x1d8/8], manager[0x48/8], editor[0x1f8/8], themes[0x30/8], theme[6][0x38/8];
    std::memset(base,0,sizeof(base));std::memset(manager,0,sizeof(manager));std::memset(editor,0,sizeof(editor));std::memset(themes,0,sizeof(themes));std::memset(theme,0,sizeof(theme));
    char* self=reinterpret_cast<char*>(base);
    pointerAt(base,0x68,manager);
    unsigned int initial=99;std::memcpy(self+0x168,&initial,4);
    CEditor* savedEditor=gEditor;gEditor=reinterpret_cast<CEditor*>(editor);
    unsigned int flags=c.seed%4;std::memcpy(reinterpret_cast<char*>(editor)+0x64,&flags,4);
    CUnitThemes* savedThemes=testUnitThemes;testUnitThemes=reinterpret_cast<CUnitThemes*>(themes);
    TArrayList<CUnitTheme*>* available=new(reinterpret_cast<char*>(themes)+0x18)TArrayList<CUnitTheme*>(1);
    CUnitTheme* tokens[7];tokens[0]=NULL;
    for(unsigned int i=0;i<6;++i)tokens[i+1]=reinterpret_cast<CUnitTheme*>(theme[i]);
    unsigned int count=(c.seed/4)%7;
    for(unsigned int i=0;i<count;++i)available->add(tokens[i+1]);
    TArrayList<CUnitTheme*>* lists[4];
    for(unsigned int i=0;i<4;++i) {
        lists[i]=new(self+0x108+i*0x18)TArrayList<CUnitTheme*>(1);
        for(unsigned int j=0;j<7;++j)if(((c.seed+j*3+i*5)%(i+3))==0)lists[i]->add(tokens[j]);
    }
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    for(unsigned int step=0;step<3;++step) {
        unsigned int id=step==0?(c.seed/7)%9:step==1?1:0;
        if(ours)object->setEditorThemeID(id);else originalEditorTheme(object,id);
        out.add(self+0x168,4);
        for(unsigned int i=0;i<4;++i) {
            out.add(reinterpret_cast<char*>(lists[i])+8,12);
            for(unsigned int j=0;j<lists[i]->size();++j) {
                int token=-1;for(int k=0;k<7;++k)if((*lists[i])[j]==tokens[k])token=k;
                out.add(&token,sizeof(token));
            }
        }
    }
    for(unsigned int i=0;i<4;++i)lists[i]->~TArrayList<CUnitTheme*>();
    available->~TArrayList<CUnitTheme*>();testUnitThemes=savedThemes;gEditor=savedEditor;
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_editor_theme_selection) {
    int failures=0;
    for(unsigned int seed=0;seed<252;++seed) {
        Case c={seed};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
            a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    editor theme seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
