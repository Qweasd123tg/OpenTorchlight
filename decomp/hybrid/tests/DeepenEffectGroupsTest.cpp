#include "SmallMassCompare.h"
#include "EffectGroupManager.h"
#include "FileSystem.h"
#include "Utilities.h"
#include "StringUtilities.h"

TL_ORIGINAL(void,groupRollOld,(CEffectGroupManager*,unsigned,unsigned,unsigned,TArrayList<CAffix*>&),"_ZN19CEffectGroupManager26rollAndCreateRandomAffixesEjjjR10TArrayListIP6CAffixE")
extern "C" void groupRollNew(CEffectGroupManager*,unsigned,unsigned,unsigned,TArrayList<CAffix*>&) __asm__("_ZN19CEffectGroupManager26rollAndCreateRandomAffixesEjjjR10TArrayListIP6CAffixE");
TL_ORIGINAL(void,groupReloadOld,(CEffectGroupManager*),"_ZN19CEffectGroupManager6reloadEv")
extern "C" void groupReloadNew(CEffectGroupManager*) __asm__("_ZN19CEffectGroupManager6reloadEv");
TL_FUNCTION(groupFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(groupParse,"_ZN6CAffix15parseAffixGroupEv")
TL_FUNCTION(groupCan,"_ZN6CAffix22canBeAppliedToUnitTypeEj")
TL_FUNCTION(groupRandom,"_ZN9UTILITIES13randomBetweenEff")
namespace deepen_groups {
using namespace smallmass;
bool active;unsigned parsed,rolls;TSafePointer<CAffix> watched[32];
void check(bool b){number(b);if(!b)_exit(45);}
unsigned fileList(CFileSystem*,const std::wstring& path,TArrayList<std::wstring>& files,std::wstring pattern,bool recurse,bool strip,bool mods,bool skip){
 if(!active)return 0;
 number(1);text(path);text(pattern);number(field<unsigned>(&files,0x10));number(recurse);number(strip);number(mods);number(skip);
 unsigned count=input->index%7;
 for(unsigned i=0;i<count;++i){std::wstring name=L"file0";name[4]+=i;files.add(name);}
 return count;
}
void parse(CAffix* affix){
 unsigned i=affix->m_sAffixFileName.size()>4?affix->m_sAffixFileName[4]-L'0':0;
 affix->m_sDisplayName=L"DISPLAY 名称 "+STRINGS::GetValueAsWString(input->op==1&&input->index&8?i%2:i);
 affix->m_sPrefix=L"prefix";affix->m_sSuffix=L"suffix";
 affix->m_iMinSpawnRange=int(i%3)*4-1;affix->m_iMaxSpawnRange=affix->m_iMinSpawnRange+7;
 affix->m_iWeight=i%5==4?0:int(i)+1;affix->m_iSlotsOccupy=i%4+1;
 affix->m_ApplicableUnitTypes.add(i%2+1);affix->m_ApplicableUnitTypes.add(7);
 if(active){number(2);text(affix->m_sAffixFileName);text(affix->m_sDisplayName);if(parsed<32)watched[parsed].setObject(affix);++parsed;}
}
bool can(CAffix* affix,unsigned type){number(3);text(affix->m_sAffixFileName);number(type);bool answer=false;for(unsigned i=0;i<affix->m_ApplicableUnitTypes.size();++i)if(affix->m_ApplicableUnitTypes[i]==type)answer=true;number(answer);return answer;}
float random(float lo,float hi){number(4);floating(lo);floating(hi);static const float values[]={0.0f,0.2f,0.51f,0.79f,0.999f};float result=values[(input->index+rolls++)%5];floating(result);return result;}
CAffix* make(unsigned i){std::wstring name=L"file0";name[4]+=i;return new CAffix(name);}
void captureAffix(CAffix* affix){number(affix->m_pOriginalAffix!=0);if(affix->m_pOriginalAffix)text(affix->m_pOriginalAffix->m_sAffixFileName);text(affix->m_sAffixFileName);text(affix->m_sDisplayName);text(affix->m_sPrefix);text(affix->m_sSuffix);number(affix->m_iMinSpawnRange);number(affix->m_iMaxSpawnRange);number(affix->m_iWeight);number(affix->m_iSlotsOccupy);number(affix->m_uiLevel);number(affix->m_cLevelPercent);number(affix->m_Effects.size());number(affix->m_ApplicableUnitTypes.size());for(unsigned i=0;i<affix->m_ApplicableUnitTypes.size();++i)number(affix->m_ApplicableUnitTypes[i]);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;parsed=rolls=0;active=false;
 detour::Set patch;TL_REDIRECT(patch,groupFiles,&fileList);TL_REDIRECT(patch,groupParse,&parse);TL_REDIRECT(patch,groupCan,&can);TL_REDIRECT(patch,groupRandom,&random);if(patch.failed())_exit(42);
 int baseline=g_iTotalCountOfObjects;
 {
 CEffectGroupManager self(c.index&16?L"media/аффиксы":L"");
 if(c.op==0){
  unsigned unitType=c.index/16%3==0?1:c.index/16%3==1?2:7;
  unsigned mode=c.index%8;
  for(unsigned i=0;i<6;++i){CAffix* affix=make(i);self.m_mapAffixes[affix->m_sAffixFileName]=affix;}
  if(mode==1)self.m_mapAffixesByUnitType[unitType]=0;
  else if(mode>=2){TArrayList<CAffix*>* cached=new TArrayList<CAffix*>(2);if(mode!=2)for(std::map<std::wstring,CAffix*>::iterator i=self.m_mapAffixes.begin();i!=self.m_mapAffixes.end();++i)cached->add(i->second);self.m_mapAffixesByUnitType[unitType]=cached;}
  static const unsigned levels[]={0,3,6,7,10,14,0x80000000u,~0u};
  static const unsigned budgets[]={0,1,2,3,4,7,0x80000000u,~0u};
  unsigned level=levels[c.index/8%8],cost=budgets[c.index/64%8];
  TArrayList<CAffix*> result(2);if(c.index&4)result.add(make(9));
  active=true;
  typedef void(*Fn)(CEffectGroupManager*,unsigned,unsigned,unsigned,TArrayList<CAffix*>&);Fn fn=ours?groupRollNew:groupRollOld;
  int beforeRoll=g_iTotalCountOfObjects;out.addHeapInUse();if(!autotest::beginInvocation(out,fn))return;fn(&self,unitType,level,cost,result);out.callCompleted=1;out.addHeapInUse();number(g_iTotalCountOfObjects-beforeRoll);
  number(unitType);number(level);number(cost);number(rolls);number(result.size());for(unsigned i=0;i<result.size();++i)captureAffix(result[i]);
  number(self.m_mapAffixesByUnitType.size());TArrayList<CAffix*>* cache=self.m_mapAffixesByUnitType[unitType];number(cache!=0);if(cache){number(cache->size());for(unsigned i=0;i<cache->size();++i)text(cache->operator[](i)->m_sAffixFileName);}
  result.deleteAll();
 }else{
  for(unsigned i=0;i<c.index%4;++i){CAffix* affix=make(i+7);self.m_mapAffixes[affix->m_sAffixFileName]=affix;watched[16+i].setObject(affix);}
  TArrayList<CAffix*>* oldCache=new TArrayList<CAffix*>(2);for(std::map<std::wstring,CAffix*>::iterator i=self.m_mapAffixes.begin();i!=self.m_mapAffixes.end();++i)oldCache->add(i->second);self.m_mapAffixesByUnitType[1]=oldCache;if(c.index&4)self.m_mapAffixesByUnitType[2]=0;
  active=true;out.addHeapInUse();autotest::invoke(out,ours?groupReloadNew:groupReloadOld,&self);out.addHeapInUse();
  number(parsed);number(self.m_mapAffixesByUnitType.size());number(self.m_mapAffixes.size());
  for(std::map<std::wstring,CAffix*>::iterator i=self.m_mapAffixes.begin();i!=self.m_mapAffixes.end();++i){text(i->first);captureAffix(i->second);}
  for(unsigned i=0;i<parsed;++i)number(watched[i].getObject()!=0);
  for(unsigned i=0;i<c.index%4;++i)check(watched[16+i].getObject()==0);
 }
 active=false;
 }
 for(unsigned i=0;i<32;++i)check(watched[i].getObject()==0);
 number(g_iTotalCountOfObjects-baseline);out.addHeapInUse();
}
}
TL_TEST(deepen_effect_groups_roll){return smallmass::run(host,0,"deepen_effect_groups_roll",(uintptr_t)groupRollOld,&deepen_groups::execute,512);}
TL_TEST(deepen_effect_groups_reload){return smallmass::run(host,1,"deepen_effect_groups_reload",(uintptr_t)groupReloadOld,&deepen_groups::execute,84);}
