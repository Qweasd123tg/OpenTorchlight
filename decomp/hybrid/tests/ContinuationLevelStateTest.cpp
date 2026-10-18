#include <cstring>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "LevelState.h"
#include "FormationNode.h"
#include "FormationNodeSaveAndLoad.h"
#include "EditorScene.h"
#include "Automap.h"
#include "ItemSaveState.h"
#include "CharacterSaveState.h"
#include "LogicNodeState.h"
#undef protected
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,lsOldMap,lsNewMap,(CLevelState*,CAutomap*),"_ZN11CLevelState10addAutomapEP8CAutomap")
DECL(void,lsOldForm,lsNewForm,(CLevelState*,TArrayList<CFormationNode*>*,CLevel&),"_ZN11CLevelState13addFormationsEP10TArrayListIP14CFormationNodeER6CLevel")
DECL(void,lsOldSave,lsNewSave,(CLevelState*,FILE*),"_ZN11CLevelState4saveEP8_IO_FILE")
DECL(void,lsOldItem,lsNewItem,(CLevelState*,CItem&),"_ZN11CLevelState7addItemER5CItem")
DECL(void,lsOldChar,lsNewChar,(CLevelState*,CCharacter&,CLevel&),"_ZN11CLevelState12addCharacterER10CCharacterR6CLevel")
DECL(void,lsOldDtor,lsNewDtor,(CLevelState*),"_ZN11CLevelStateD1Ev")
#undef DECL
TL_FUNCTION(lsPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(lsCharSave,"_ZN19CCharacterSaveState4saveEP8_IO_FILE")
TL_FUNCTION(lsItemSave,"_ZN14CItemSaveState4saveEP8_IO_FILE")
TL_FUNCTION(lsLogicSave,"_ZN15CLogicNodeState4saveEP8_IO_FILE")
namespace {
struct Case{unsigned op,seed;};autotest::Capture*cap;unsigned seed;CFormationNode*nodes[5];CLogicNodeState*logics[5];
void number(unsigned n){cap->add(&n,4);}void text(const std::wstring&s){cap->addText(s);}
struct LogicLifetime:CRunicCore{unsigned identity;LogicLifetime(unsigned n):identity(n){}virtual~LogicLifetime(){number(101);number(identity);}};
Ogre::Vector3 position(CPositionableObject*p,bool absolute){int n=-1;for(int i=0;i<5;++i)if(nodes[i]==p)n=i;number(103);cap->add(&n,4);cap->add(&absolute,1);return Ogre::Vector3(float(n)-2,float(seed)/4,-float(n));}
void fillItem(CItem*,CItemSaveState&s,int index,bool flag){number(107);cap->add(&index,4);cap->add(&flag,1);s.m_sItemName=seed%2?L"saved-item-Ж":L"";s.m_iIndex=index;s.m_iStackSize=seed+3;s.m_bIdentified=flag;}
void fillCharacter(CCharacter*,CCharacterSaveState&s){number(109);s.m_name=seed%2?L"character Ж":L"";s.m_hp=float(seed)*0.5f;s.m_value38=seed+9;}
void charSave(CCharacterSaveState*p,FILE*f){unsigned tag=113;number(tag);text(p->m_name);fwrite(&tag,4,1,f);fwrite(&p->m_value38,4,1,f);}
void itemSave(CItemSaveState*p,FILE*f){unsigned tag=127;number(tag);text(p->m_sItemName);fwrite(&tag,4,1,f);fwrite(&p->m_iStackSize,4,1,f);}
void logicSave(CLogicNodeState*p,FILE*f){unsigned tag=131,n=9;for(unsigned i=0;i<5;++i)if(logics[i]==p)n=i;number(tag);number(n);fwrite(&tag,4,1,f);fwrite(&n,4,1,f);}
void state(CLevelState*p){cap->add(&p->m_iLevelId,4);cap->add(&p->m_iStateVersion,4);number(p->m_sLevelName.size());text(p->m_sLevelName.substr(0,32));cap->add(&p->m_bUnknownB0,1);cap->add(&p->m_bUnknownB1,1);cap->add(&p->m_iAutomapWidth,4);cap->add(&p->m_iAutomapHeight,4);if(p->m_iAutomapWidth>0&&p->m_iAutomapHeight>0)cap->add(p->m_pAutomapData,p->m_iAutomapWidth*p->m_iAutomapHeight*4);number(p->m_lCharacters.size());for(unsigned i=0;i<p->m_lCharacters.size();++i)if(p->m_lCharacters[i]){text(p->m_lCharacters[i]->m_name);cap->add(&p->m_lCharacters[i]->m_hp,4);cap->add(&p->m_lCharacters[i]->m_value38,4);}number(p->m_lItems.size());for(unsigned i=0;i<p->m_lItems.size();++i)if(p->m_lItems[i]){text(p->m_lItems[i]->m_sItemName);cap->add(&p->m_lItems[i]->m_iIndex,4);cap->add(&p->m_lItems[i]->m_iStackSize,4);}number(p->m_lFormations.size());for(unsigned i=0;i<p->m_lFormations.size();++i){CFormationNodeSaveAndLoad*f=p->m_lFormations[i];cap->add(&f->m_bSavePosition,1);text(f->m_sFileLoaded);cap->add(&f->m_fPositionX,12);}}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;std::memset(nodes,0,sizeof(nodes));std::memset(logics,0,sizeof(logics));detour::Set patches;TL_REDIRECT(patches,lsPosition,&position);TL_REDIRECT(patches,lsCharSave,&charSave);TL_REDIRECT(patches,lsItemSave,&itemSave);TL_REDIRECT(patches,lsLogicSave,&logicSave);if(patches.failed())_exit(43);
 uint64_t memory[(sizeof(CLevelState)+7)/8];CLevelState*p=new(memory)CLevelState(int(seed)-17);TSafePointer<CLevelState> weak;weak.setObject(p);p->m_sLevelName=seed%4==0?L"":seed%4==1?L"level":seed%4==2?L"Ж\U0001f642":std::wstring(65537,L'x');p->m_iStateVersion=float(seed)-0.5f;p->m_bUnknownB0=seed%2;p->m_bUnknownB1=seed%3==0;
 uint64_t levelWitness=0;CLevel&level=*reinterpret_cast<CLevel*>(&levelWitness);float tiles[24];for(unsigned i=0;i<24;++i)tiles[i]=(int(i)-10)*0.125f+seed;uint64_t mapMemory[(sizeof(CAutomap)+7)/8];CAutomap*map=reinterpret_cast<CAutomap*>(mapMemory);map->m_iMapGridWidth=seed%5;map->m_iMapGridHeight=(seed/3)%5;map->m_pRevealedTiles=tiles;
 if(c.op==0){p->m_pAutomapData=new float[2];p->m_iAutomapWidth=2;p->m_iAutomapHeight=1;autotest::invoke(out,ours?&lsNewMap:&lsOldMap,p,map);}
 if(c.op==1){uint64_t nodeMemory[5][(sizeof(CFormationNode)+7)/8],sceneMemory[5][(sizeof(CEditorScene)+7)/8];TArrayList<CFormationNode*>list(2);for(unsigned i=0;i<seed%6;++i){nodes[i]=reinterpret_cast<CFormationNode*>(nodeMemory[i]);nodes[i]->m_bActivationStarted=(i+seed)%3==0;CEditorScene*scene=reinterpret_cast<CEditorScene*>(sceneMemory[i]);new(&scene->m_sFileLoaded)std::wstring(i%2?L"formation-Ж":L"file");nodes[i]->m_pEditorScene=scene;list.add(nodes[i]);}autotest::invoke<void(*)(CLevelState*,TArrayList<CFormationNode*>*,CLevel&),CLevelState*,TArrayList<CFormationNode*>*,CLevel&>(out,ours?&lsNewForm:&lsOldForm,p,&list,level);for(unsigned i=0;i<seed%6;++i)reinterpret_cast<CEditorScene*>(sceneMemory[i])->m_sFileLoaded.~basic_string();}
 if(c.op==3){void*vt[0x298/8];std::memset(vt,0,sizeof(vt));vt[0x290/8]=reinterpret_cast<void*>(&fillItem);void**object=vt;CItem&item=*reinterpret_cast<CItem*>(&object);for(unsigned i=0;i<seed%4;++i)p->m_lItems.push_back(new CItemSaveState);autotest::invoke<void(*)(CLevelState*,CItem&),CLevelState*,CItem&>(out,ours?&lsNewItem:&lsOldItem,p,item);}
 if(c.op==4){void*vt[0x2a0/8];std::memset(vt,0,sizeof(vt));vt[0x298/8]=reinterpret_cast<void*>(&fillCharacter);void**object=vt;CCharacter&character=*reinterpret_cast<CCharacter*>(&object);for(unsigned i=0;i<seed%4;++i)p->m_lCharacters.push_back(new CCharacterSaveState);autotest::invoke<void(*)(CLevelState*,CCharacter&,CLevel&),CLevelState*,CCharacter&,CLevel&>(out,ours?&lsNewChar:&lsOldChar,p,character,level);}
 if(c.op==2||c.op==5){p->m_iAutomapWidth=seed%5;p->m_iAutomapHeight=seed%4;unsigned count=p->m_iAutomapWidth*p->m_iAutomapHeight;p->m_pAutomapData=new float[count];std::memcpy(p->m_pAutomapData,tiles,count*4);for(unsigned i=0;i<seed%4;++i){CCharacterSaveState*ch=new CCharacterSaveState;ch->m_name=i%2?L"A":L"Ж";ch->m_value38=i+seed;p->m_lCharacters.push_back(ch);CItemSaveState*it=new CItemSaveState;it->m_sItemName=i%2?L"item":L"";it->m_iStackSize=i+seed;p->m_lItems.push_back(it);logics[i]=reinterpret_cast<CLogicNodeState*>(new LogicLifetime(i));p->m_lLogicStates.push_back(logics[i]);CFormationNodeSaveAndLoad*f=new CFormationNodeSaveAndLoad(NULL);f->m_bSavePosition=(i+seed)%2;f->m_sFileLoaded=i%2?L"file Ж":L"";f->m_fPositionX=i;f->m_fPositionY=seed;f->m_fPositionZ=-float(i);p->m_lFormations.add(f);p->m_lLevelStrings.push_back(i%2?L"":L"Ж\U0001f642");}if(c.op==5&&seed%2){p->m_lItems.push_back(NULL);p->m_lCharacters.push_back(NULL);p->m_lLogicStates.push_back(NULL);}if(c.op==2){FILE*f=tmpfile();if(!f)_exit(44);autotest::invoke(out,ours?&lsNewSave:&lsOldSave,p,f);long length=ftell(f);if(length<0||length>200000)_exit(45);number(length);rewind(f);char bytes[4096];while(size_t n=fread(bytes,1,sizeof(bytes),f))out.add(bytes,n);fclose(f);}}
 if(c.op!=5)state(p);if(c.op==5)autotest::invoke(out,ours?&lsNewDtor:&lsOldDtor,p);else lsOldDtor(p);bool invalid=weak.getObject()==NULL;out.add(&invalid,1);if(!invalid)out.issue=autotest::Capture::InvalidReport;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_level_state_storage){int failures=0;const uintptr_t functions[]={(uintptr_t)&lsOldMap,(uintptr_t)&lsOldForm,(uintptr_t)&lsOldSave,(uintptr_t)&lsOldItem,(uintptr_t)&lsOldChar,(uintptr_t)&lsOldDtor};for(unsigned op=0;op<6;++op){autotest::Coverage coverage("continuation_level_state_storage",functions[op]);for(unsigned i=0;i<32;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    level op %u seed %u status %d/%d issue %u/%u bytes %lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    level diff byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);}return failures;}
