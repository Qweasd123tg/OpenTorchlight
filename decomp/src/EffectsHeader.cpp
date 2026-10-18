#include "EmptyStrings.h"
#include "GameVariables.h"

bool CheckProcessWasRestarted()
{
    return g_bWasRestarted;
}

void compressAllFiles()
{
}

extern "C" int flock(int fd, int operation);

bool DoRestartProcessFinish(bool finished)
{
    if (finished && *reinterpret_cast<int *>(g_hRestartingFile) != 0) {
        flock(*reinterpret_cast<int *>(g_hRestartingFile), 8);
        close(*reinterpret_cast<int *>(g_hRestartingFile));
        *reinterpret_cast<int *>(g_hRestartingFile) = 0;
    }

    return true;
}

#include "Settings.h"
#include "StringUtilities.h"
#include "FileUtilities.h"

CSettings* createSettings(const std::string& commandLine,bool& failed)
{
    std::wstring command=STRINGS::StringConvertToWide(commandLine.c_str(),5000);
    std::wstring directory=FILESYSTEM::GetAppDataPath();
    CSettings* settings=new CSettings(command,directory,L"local_settings.txt",L"settings.txt");
    if(settings->m_pCmdLineParser->GetIntParam(L"SAFEMODE",0)==0)
        failed=!settings->LoadSettings(L"");
    return settings;
}

#include "DataGroup.h"
#include "EffectDefines.h"
#include <OgreLogManager.h>

void parseEffects()
{
    CDataGroup data(L"",NULL,20,10,NULL);
    data.LoadFile(L"media/EffectsList.dat",static_cast<CTimerStatics*>(NULL));
    if(data.GetNumberOfDataGroups()!=145)
        Ogre::LogManager::getSingleton().logMessage("The effect file( media/effectslist.dat ) appears to no longer match up with the internal effect list.  Please revert this file.",Ogre::LML_CRITICAL,false);
    for(unsigned i=0;i<data.GetNumberOfDataGroups();++i) {
        gEFFECT_TYPE_NAMES[i]=data.GetDataGroup(i)->GetDataValue(L"NAME",EMPTY_WSTRING);
        gEFFECT_TYPE_DESCRIPTIONS_GOOD[i]=data.GetDataGroup(i)->GetDataValue(L"GOODDES",EMPTY_WSTRING);
        gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[i]=data.GetDataGroup(i)->GetDataValue(L"GOODDESOT",EMPTY_WSTRING);
        gEFFECT_TYPE_DESCRIPTIONS_BAD[i]=data.GetDataGroup(i)->GetDataValue(L"BADDES",EMPTY_WSTRING);
        gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[i]=data.GetDataGroup(i)->GetDataValue(L"BADDESOT",EMPTY_WSTRING);
        for(unsigned value=0;value<5;++value) {
            std::wstring key=L"VALUE";key+=static_cast<wchar_t>(L'1'+value);
            gEFFECT_TYPE_PROPERTY_TAGS[i][value]=data.GetDataGroup(i)->GetDataValue(key,EMPTY_WSTRING);
        }
        for(unsigned value=0;value<5;++value) {
            std::wstring key=L"GRAPH";key+=static_cast<wchar_t>(L'1'+value);
            gEFFECT_TYPE_GRAPHS[i][value]=data.GetDataGroup(i)->GetDataValue(key,EMPTY_WSTRING);
        }
        std::wstring type=STRINGS::StringUpper(data.GetDataGroup(i)->GetDataValue(L"TYPE",L"VALUE"));
        gEFFECT_TYPE_BONUS[i]=type==L"PERCENT"?1:type==L"NONE"?2:0;
        gEFFECT_TYPE_MIN_VALUES[i]=data.GetDataGroup(i)->GetDataValue(L"MINVAL",-1);
        gEFFECT_TYPE_MAX_VALUES[i]=data.GetDataGroup(i)->GetDataValue(L"MAXVAL",1);
    }
}
