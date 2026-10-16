#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include <new>
#include <fenv.h>
#include <OgreVector3.h>
#define private public
#include "LevelTemplateData.h"
#include "DataGroup.h"
#include "FileSystem.h"
#undef private
#include "Utilities.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, loadOwnerCtor, (void*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, loadOwnerDtor, (void*), "_ZN18CLevelTemplateDataD1Ev")
TL_ORIGINAL(void, originalLoad, (CLevelTemplateData*, const wchar_t*), "_ZN18CLevelTemplateData4loadEPKw")
extern "C" void candidateLoad(CLevelTemplateData*,const wchar_t*) __asm__("_ZN18CLevelTemplateData4loadEPKw");
TL_FUNCTION(loadFilesSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(loadFileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(loadFileList,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(loadGroupFile,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
namespace {
struct Case { unsigned index; };
const Case* input;autotest::Capture* output;unsigned infoCalls,listCalls,loadCalls;
void number(unsigned n){output->add(&n,sizeof(n));}
void text(const std::wstring& s){output->addText(s);}
void real(float x){output->add(&x,4);}
CFileSystem* files(){number(0x100);return NULL;}
void info(CFileSystem* self,const std::wstring& path,CFileInfo& result,bool a,bool b,bool c){
    number(0x101);number(self!=NULL);text(path);number(a);number(b);number(c);++infoCalls;
    result.m_bExists=input->index!=2 && path.find(L"missing/")==std::wstring::npos;
    result.m_sPath=path.empty()?std::wstring():std::wstring(L"resolved/")+path;
    result.m_eFormat=FILE_FORMAT_BINARY;result.m_eLocation=FILE_LOCATION_DISK;
}
unsigned list(CFileSystem* self,const std::wstring& directory,TArrayList<std::wstring>& values,std::wstring pattern,bool a,bool b,bool c,bool d){
    number(0x102);number(self!=NULL);text(directory);text(pattern);number(a);number(b);number(c);number(d);++listCalls;
    unsigned count=(input->index/4)%4;
    for(unsigned i=0;i<count;++i){
        std::wstring name=directory+(i==0?L"piece.layout":i==1?L"second.LAYOUT":L"merge/MERGE/piece.layout");
        if(input->index%13==0&&i==1)name=directory+L"piece.layout";
        values.add(name);
    }
    return count;
}
void populateRoot(CDataGroup& data,unsigned index);
void load(CDataGroup* data,const std::wstring& path,CTimerStatics* timers){
    number(0x103);text(path);number(timers!=NULL);++loadCalls;
    if(input->index==3)return;
    populateRoot(*data,input->index);
    if(input->index>=84) {
        const int colors[]={-1,0,255,256};int color=colors[(input->index-84)%4];
        data->SetDataValue(L"LIGHTMAP RED",color);data->SetDataValue(L"FOG GREEN",color);
        data->SetDataValue(L"DIRECTIONAL BLUE",color);data->SetDataValue(L"DIRECTIONAL INTENSITY",(input->index-84)<4?0.5f:-2.0f);
        return;
    }
    if(input->index<6)return;
    data->SetDataValue(L"RANDOMIZED",(input->index&1)!=0);
    unsigned types=(input->index/2)%4;
    if(input->index==70)types=11;
    for(unsigned i=0;i<types;++i){
        CDataGroup* type=data->AddDataGroup(L"CHUNKTYPE");
        std::wstring name=L"TYPE";name+=static_cast<wchar_t>(L'A'+i);
        type->AddDataValue(L"NAME",name,false);
        type->AddDataValue(L"MUST_PLACE",(input->index+i)%3==0);
        type->AddDataValue(L"ENTRANCE_CHUNK",i==0);
        type->AddDataValue(L"EXIT_CHUNK",(input->index+i)%4==0);
        type->AddDataValue(L"MAX_APPEARANCE",static_cast<int>((input->index+i)%4));
        if(input->index%5!=0)type->AddDataValue(L"FOLDER",i%4==0?L"pieces/":i%4==1?L"pieces":i%4==2?L"pieces\\":((input->index&1)?L"":L"relative"),false);
        type->AddDataValue(L"WIDTH",static_cast<int>(i%3+1));
        type->AddDataValue(L"HEIGHT",static_cast<int>((i+1)%4+1));
        unsigned exits=(input->index+i)%5;
        for(unsigned e=0;e<exits;++e){
            CDataGroup* exit=type->AddDataGroup(L"EXIT");
            const float x[]={0,3,-3,0,1};const float z[]={0,2,2,6,3};
            exit->AddDataValue(L"X",x[e]);exit->AddDataValue(L"Y",static_cast<float>(e%2));exit->AddDataValue(L"Z",z[e]);
        }
        if(input->index%3==0){
            CDataGroup* inclusive=type->AddDataGroup(L"INCLUSIVE_FILES");
            inclusive->AddDataValue(L"FILE",L"piece",false);
            if(input->index%6==0)inclusive->AddDataValue(L"SECOND",L"second.LAYOUT",false);
        }
    }
    unsigned layouts=(input->index/3)%3;
    for(unsigned i=0;i<layouts;++i){
        CDataGroup* layout=data->AddDataGroup(L"LAYOUT");
        for(unsigned k=0;k<(input->index+i)%4;++k){
            CDataGroup* chunk=layout->AddDataGroup(L"CHUNK_RANDOM");
            std::wstring name=L"TYPE";name+=static_cast<wchar_t>(L'A'+(types?k%types:0));
            if(input->index%11==0)name=L"UNKNOWN";
            chunk->AddDataValue(L"TYPE",name,false);
            chunk->AddDataValue(L"X",static_cast<float>(k*3));chunk->AddDataValue(L"Y",static_cast<float>(i));chunk->AddDataValue(L"Z",static_cast<float>(i*5));
        }
    }
}
template<class T>void listShape(const TArrayList<T>& list){number(list.m_nCount);number(list.m_nCapacity);number(list.m_nGrowBy);number(list.m_pData!=NULL);}
void randomizer(CRandomizer& value){
    listShape(value.m_Choices);for(unsigned i=0;i<value.m_Choices.size();++i)number(value.m_Choices[i]);
    listShape(value.m_Odds);for(unsigned i=0;i<value.m_Odds.size();++i)real(value.m_Odds[i]);
    listShape(value.m_ComputedOdds);for(unsigned i=0;i<value.m_ComputedOdds.size();++i)real(value.m_ComputedOdds[i]);
    number(value.m_eType);real(value.m_fDecay);number(value.m_bOddsDirty);
}
void ownerFields(CLevelTemplateData& value);
void capture(CLevelTemplateData& value){
    ownerFields(value);
    listShape(value.m_chunkTypes);
    if(value.m_chunkTypes.size()>32||value.m_chunks.size()>128||value.m_layouts.size()>32)_exit(91);
    for(unsigned i=0;i<value.m_chunkTypes.size();++i){
        CChunkType& t=*value.m_chunkTypes[i];number(t.m_entranceChunk);number(t.m_exitChunk);number(t.m_registeredWithRandomizers);number(t.m_mustPlace);
        number(t.m_width);number(t.m_height);number(t.m_maxAppearance);text(t.m_folder);text(t.m_name);
        listShape(t.m_inclusiveFiles);for(unsigned j=0;j<t.m_inclusiveFiles.size();++j)text(t.m_inclusiveFiles[j]);
        listShape(t.m_exits);for(unsigned j=0;j<t.m_exits.size();++j){real(t.m_exits[j].x);real(t.m_exits[j].y);real(t.m_exits[j].z);}
    }
    listShape(value.m_requiredChunkTypes);for(unsigned i=0;i<value.m_requiredChunkTypes.size();++i)number(value.m_chunkTypes.find(value.m_requiredChunkTypes[i]));
    listShape(value.m_chunks);for(unsigned i=0;i<value.m_chunks.size();++i){CChunk& c=*value.m_chunks[i];number(c.m_chunkValue10);number(c.m_odds);number(c.m_maxAppearance);text(c.m_filename);}
    number(value.m_layoutRandomizer!=NULL);if(value.m_layoutRandomizer)randomizer(*value.m_layoutRandomizer);
    listShape(value.m_chunkRandomizers);for(unsigned i=0;i<value.m_chunkRandomizers.size();++i)randomizer(*value.m_chunkRandomizers[i]);
    listShape(value.m_layouts);for(unsigned i=0;i<value.m_layouts.size();++i){
        CLevelLayout& layout=*value.m_layouts[i];number(layout.m_seed);listShape(layout.m_chunks);
        for(unsigned j=0;j<layout.m_chunks.size();++j)number(value.m_chunks.find(layout.m_chunks[j]));
        listShape(layout.m_chunkInstances);for(unsigned j=0;j<layout.m_chunkInstances.size();++j){
            CChunkInstance& instance=*layout.m_chunkInstances[j];number(instance.m_chunkTypeIndex);text(instance.m_name);real(instance.m_x);real(instance.m_y);real(instance.m_z);
            number(instance.m_usedExits.size());for(unsigned k=0;k<instance.m_usedExits.size();++k)number(instance.m_usedExits[k]);
        }
    }
    listShape(value.m_baseLayouts);for(unsigned i=0;i<value.m_baseLayouts.size();++i)number(value.m_layouts.find(value.m_baseLayouts[i]));
}
void side(Case& c,bool ours,autotest::Capture& out){
    input=&c;output=&out;infoCalls=listCalls=loadCalls=0;
    int objectsBefore=g_iTotalCountOfObjects;
    union Storage {long double align;unsigned char bytes[0x778];} storage;
    std::memset(storage.bytes,0xa5,sizeof(storage.bytes));loadOwnerCtor(storage.bytes,NULL);
    CLevelTemplateData* owner=reinterpret_cast<CLevelTemplateData*>(storage.bytes);
    UTILITIES::setSeed(c.index*17+1);
    detour::Set io;TL_REDIRECT(io,loadFilesSingleton,&files);TL_REDIRECT(io,loadFileInfo,&info);TL_REDIRECT(io,loadFileList,&list);TL_REDIRECT(io,loadGroupFile,&load);
    if(io.failed())_exit(92);
    const wchar_t* path=c.index==0?NULL:c.index==1?L"":c.index%2?L"media/layouts/test.dat":L"test.dat";
    void(*fn)(CLevelTemplateData*,const wchar_t*)=ours?candidateLoad:originalLoad;
    feclearexcept(FE_ALL_EXCEPT);
    if(!autotest::beginInvocation(out,fn))return;
    fn(owner,path);
    if(c.index>=72 && c.index<84) {
        number(0x200);capture(*owner);
        Case repeated={c.index-64};input=&repeated;
        fn(owner,c.index%3==0?L"missing/repeated.dat":path);
        input=&c;
    }
    out.callCompleted=1;int exceptions=fetestexcept(FE_ALL_EXCEPT);number(exceptions);
    number(infoCalls);number(listCalls);number(loadCalls);capture(*owner);
    io.restore();loadOwnerDtor(owner);number(g_iTotalCountOfObjects-objectsBefore);
}
void original(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
void populateRoot(CDataGroup& data,unsigned index){
    if(index!=5 || 1%3) data.AddDataValue(L"MONSTER_LVL_MIN",static_cast<int>((index*1+7)%520)-130);
    if(index!=5 || 2%3) data.AddDataValue(L"MONSTER_LVL_MAX",static_cast<int>((index*2+7)%520)-130);
    if(index!=5 || 3%3) data.AddDataValue(L"NO_RANDOM_QUESTS",((index+3)%2)!=0);
    if(index!=5 || 4%3) data.AddDataValue(L"TILEBASIS",static_cast<float>((index*4+3)%31)*0.25f);
    if(index!=5 || 5%3) data.AddDataValue(L"CHUNKWIDTHBASIS",static_cast<float>((index*5+3)%31)*0.25f);
    if(index!=5 || 6%3) data.AddDataValue(L"CHUNKHEIGHTBASIS",static_cast<float>((index*6+3)%31)*0.25f);
    if(index!=5 || 7%3) data.AddDataValue(L"REQUIRESEXIT",((index+7)%2)!=0);
    if(index!=5 || 8%3) data.AddDataValue(L"DONTSTORE",((index+8)%2)!=0);
    if(index!=5 || 9%3) data.AddDataValue(L"RANDOMIZED",((index+9)%2)!=0);
    if(index!=5 || 10%3) data.AddDataValue(L"HASPATHING",((index+10)%2)!=0);
    if(index!=5 || 11%3) data.AddDataValue(L"HASAUTOMAP",((index+11)%2)!=0);
    if(index!=5 || 12%3) data.AddDataValue(L"MINCHUNKS",static_cast<int>((index*12+7)%520)-130);
    if(index!=5 || 13%3) data.AddDataValue(L"MAXCHUNKS",static_cast<int>((index*13+7)%520)-130);
    if(index!=5 || 14%3) data.AddDataValue(L"POPULATE",((index+14)%2)!=0);
    if(index!=5 || 15%3) data.AddDataValue(L"ORTHOGRAPHICSHADOWS",((index+15)%2)!=0);
    if(index!=5 || 16%3) data.AddDataValue(L"UNIT_LIGHT_FADE",((index+16)%2)!=0);
    if(index!=5 || 17%3) data.AddDataValue(L"UNIT_FADE_DISTANCE",static_cast<float>((index*17+3)%31)*0.25f);
    if(index!=5 || 18%3) data.AddDataValue(L"UNIT_FADE_START",static_cast<float>((index*18+3)%31)*0.25f);
    if(index!=5 || 19%3) data.AddDataValue(L"CAMERAMULT",static_cast<float>((index*19+3)%31)*0.25f);
    if(index!=5 || 20%3) data.AddDataValue(L"MUSIC",std::wstring(L"value 20/test.dat"),false);
    if(index!=5 || 21%3) data.AddDataValue(L"SHOWFLOORNUMBER",((index+21)%2)!=0);
    if(index!=5 || 22%3) data.AddDataValue(L"LEVELNAME",std::wstring(L"value 22/test.dat"),false);
    if(index!=5 || 23%3) data.AddDataValue(L"NAME",std::wstring(L"value 23/test.dat"),false);
    if(index!=5 || 24%3) data.AddDataValue(L"RIMLIGHT",std::wstring(L"value 24/test.dat"),false);
    if(index!=5 || 25%3) data.AddDataValue(L"TORCHLIGHT",std::wstring(L"value 25/test.dat"),false);
    if(index!=5 || 26%3) data.AddDataValue(L"SHADOWFADE",std::wstring(L"value 26/test.dat"),false);
    if(index!=5 || 27%3) data.AddDataValue(L"LIGHTMASK",std::wstring(L"value 27/test.dat"),false);
    if(index!=5 || 28%3) data.AddDataValue(L"LIGHTMAP RED",static_cast<int>((index*28+7)%520)-130);
    if(index!=5 || 29%3) data.AddDataValue(L"LIGHTMAP GREEN",static_cast<int>((index*29+7)%520)-130);
    if(index!=5 || 30%3) data.AddDataValue(L"LIGHTMAP BLUE",static_cast<int>((index*30+7)%520)-130);
    if(index!=5 || 31%3) data.AddDataValue(L"CINEMATIC",std::wstring(L"value 31/test.dat"),false);
    if(index!=5 || 32%3) data.AddDataValue(L"SKYBOX",std::wstring(L"value 32/test.dat"),false);
    if(index!=5 || 33%3) data.AddDataValue(L"LEVELPARTICLE",std::wstring(L"value 33/test.dat"),false);
    if(index!=5 || 34%3) data.AddDataValue(L"WATER",std::wstring(L"value 34/test.dat"),false);
    if(index!=5 || 35%3) data.AddDataValue(L"POSTWATER",std::wstring(L"value 35/test.dat"),false);
    if(index!=5 || 36%3) data.AddDataValue(L"MIDWATER",std::wstring(L"value 36/test.dat"),false);
    if(index!=5 || 37%3) data.AddDataValue(L"MAINMENURULES",std::wstring(L"value 37/test.dat"),false);
    if(index!=5 || 38%3) data.AddDataValue(L"AUTOMAP",std::wstring(L"value 38/test.dat"),false);
    if(index!=5 || 39%3) data.AddDataValue(L"AUTOMAP_WIDTH",static_cast<float>((index*39+3)%31)*0.25f);
    if(index!=5 || 40%3) data.AddDataValue(L"AUTOMAP_HEIGHT",static_cast<float>((index*40+3)%31)*0.25f);
    if(index!=5 || 41%3) data.AddDataValue(L"AUTOMAP_ANGLE",static_cast<float>((index*41+3)%31)*0.25f);
    if(index!=5 || 42%3) data.AddDataValue(L"ACTIVERANGEMOD",static_cast<float>((index*42+3)%31)*0.25f);
    if(index!=5 || 43%3) data.AddDataValue(L"AMBIENT RED",static_cast<int>((index*43+7)%520)-130);
    if(index!=5 || 44%3) data.AddDataValue(L"AMBIENT GREEN",static_cast<int>((index*44+7)%520)-130);
    if(index!=5 || 45%3) data.AddDataValue(L"AMBIENT BLUE",static_cast<int>((index*45+7)%520)-130);
    if(index!=5 || 46%3) data.AddDataValue(L"MATERIAL AMBIENT RED",static_cast<int>((index*46+7)%520)-130);
    if(index!=5 || 47%3) data.AddDataValue(L"MATERIAL AMBIENT GREEN",static_cast<int>((index*47+7)%520)-130);
    if(index!=5 || 48%3) data.AddDataValue(L"MATERIAL AMBIENT BLUE",static_cast<int>((index*48+7)%520)-130);
    if(index!=5 || 49%3) data.AddDataValue(L"DIRECTIONAL RED",static_cast<int>((index*49+7)%520)-130);
    if(index!=5 || 50%3) data.AddDataValue(L"DIRECTIONAL GREEN",static_cast<int>((index*50+7)%520)-130);
    if(index!=5 || 51%3) data.AddDataValue(L"DIRECTIONAL BLUE",static_cast<int>((index*51+7)%520)-130);
    if(index!=5 || 52%3) data.AddDataValue(L"REGIONBOUNDS X",static_cast<float>((index*52+3)%31)*0.25f);
    if(index!=5 || 53%3) data.AddDataValue(L"REGIONBOUNDS Y",static_cast<float>((index*53+3)%31)*0.25f);
    if(index!=5 || 54%3) data.AddDataValue(L"REGIONBOUNDS Z",static_cast<float>((index*54+3)%31)*0.25f);
    if(index!=5 || 55%3) data.AddDataValue(L"DIRECTIONAL X",static_cast<float>((index*55+3)%31)*0.25f);
    if(index!=5 || 56%3) data.AddDataValue(L"DIRECTIONAL Y",static_cast<float>((index*56+3)%31)*0.25f);
    if(index!=5 || 57%3) data.AddDataValue(L"DIRECTIONAL Z",static_cast<float>((index*57+3)%31)*0.25f);
    if(index!=5 || 58%3) data.AddDataValue(L"DIRECTIONAL INTENSITY",static_cast<float>((index*58+3)%31)*0.25f);
    if(index!=5 || 59%3) data.AddDataValue(L"FOG RED",static_cast<int>((index*59+7)%520)-130);
    if(index!=5 || 60%3) data.AddDataValue(L"FOG GREEN",static_cast<int>((index*60+7)%520)-130);
    if(index!=5 || 61%3) data.AddDataValue(L"FOG BLUE",static_cast<int>((index*61+7)%520)-130);
    if(index!=5 || 62%3) data.AddDataValue(L"FOG START",static_cast<int>((index*62+7)%520)-130);
    if(index!=5 || 63%3) data.AddDataValue(L"FOG END",static_cast<int>((index*63+7)%520)-130);
}
void ownerFields(CLevelTemplateData& value){
    number(value.m_randomized);
    number(value.m_requiresExit);
    number(value.m_dontStore);
    text(value.m_string60);
    text(value.m_name);
    number(value.m_hasPathing);
    number(value.m_hasAutomap);
    number(value.m_populate);
    number(value.m_minChunks);
    number(value.m_maxChunks);
    number(value.m_monsterLevelMin);
    number(value.m_monsterLevelMax);
    number(value.m_permitsPortal);
    number(value.m_permitsPetDeparture);
    number(value.m_isTown);
    number(value.m_questSelectionExcluded);
    real(value.m_tileBasis);
    real(value.m_chunkWidthBasis);
    real(value.m_chunkHeightBasis);
    real(value.m_cameraMultiplier);
    real(value.m_sightRangeModifier);
    text(value.m_automap);
    real(value.m_automapWidth);
    real(value.m_automapHeight);
    real(value.m_automapAngle);
    randomizer(value.m_generalChunkRandomizer);
    randomizer(value.m_entranceChunkRandomizer);
    randomizer(value.m_randomizer1D8);
    randomizer(value.m_randomizer240);
    randomizer(value.m_randomizer2A8);
    randomizer(value.m_randomizer310);
    randomizer(value.m_randomizer378);
    randomizer(value.m_randomizer3E0);
    randomizer(value.m_randomizer448);
    randomizer(value.m_randomizer4B0);
    text(value.m_music);
    for(unsigned i=0;i<11;++i){text(value.m_unitSpawnerNames[i]);}
    for(unsigned i=0;i<11;++i){text(value.m_selectedUnitSpawners[i]);}
    for(unsigned i=0;i<11;++i){number(value.m_useSpawnClass[i]);}
    for(unsigned i=0;i<11;++i){real(value.m_densityRanges[i].minimum);real(value.m_densityRanges[i].maximum);}
    for(unsigned i=0;i<11;++i){real(value.m_countRanges[i].minimum);real(value.m_countRanges[i].maximum);}
    real(value.m_regionBoundsX);
    real(value.m_regionBoundsY);
    real(value.m_regionBoundsZ);
    text(value.m_cinematic);
    text(value.m_skybox);
    text(value.m_levelParticle);
    text(value.m_water);
    text(value.m_postWater);
    text(value.m_midWater);
    text(value.m_filename);
    text(value.m_torchlightTexture);
    text(value.m_sRimlightTexture);
    text(value.m_shadowFadeTexture);
    text(value.m_lightMaskTexture);
    text(value.m_mainMenuRules);
    output->add(&value.m_fogStart, sizeof(value.m_fogStart));
    output->add(&value.m_fogEnd, sizeof(value.m_fogEnd));
    real(value.m_lightmapColorR);
    real(value.m_lightmapColorG);
    real(value.m_lightmapColorB);
    real(value.m_lightmapColorA);
    real(value.m_fogColorR);
    real(value.m_fogColorG);
    real(value.m_fogColorB);
    real(value.m_fogColorA);
    real(value.m_ambientColorR);
    real(value.m_ambientColorG);
    real(value.m_ambientColorB);
    real(value.m_ambientColorA);
    real(value.m_materialAmbientColorR);
    real(value.m_materialAmbientColorG);
    real(value.m_materialAmbientColorB);
    real(value.m_materialAmbientColorA);
    real(value.m_directionalColorR);
    real(value.m_directionalColorG);
    real(value.m_directionalColorB);
    real(value.m_directionalColorA);
    output->add(&value.m_directionalX, sizeof(value.m_directionalX));
    output->add(&value.m_directionalY, sizeof(value.m_directionalY));
    output->add(&value.m_directionalZ, sizeof(value.m_directionalZ));
    output->add(&value.m_directionalIntensity, sizeof(value.m_directionalIntensity));
    number(value.m_orthographicShadows);
    number(value.m_state761);
    number(value.m_randomLayoutGenerated);
    number(value.m_bUnitLightFade);
    real(value.m_unitFadeDistance);
    real(value.m_unitFadeStart);
    number(value.m_showFloorNumber);
    text(value.m_levelName);
}
}
TL_TEST(level_template_load){
    autotest::Coverage coverage("level_template_load",(uint64_t)(uintptr_t)originalLoad);
    for(unsigned i=0;i<92;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        if(coverage.observe(host,a,b)){host->log("    load case %u status %d/%d bytes %lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte %u: %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return 1;}
    }coverage.report(host);return 0;
}
