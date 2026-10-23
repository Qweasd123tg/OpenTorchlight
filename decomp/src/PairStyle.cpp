#include "EmptyStrings.h"
#include "PairStyle.h"

CPairStyle::CPairStyle()
{
}

CPairStyle::~CPairStyle()
{
}

#include "FileSystem.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "StringUtilities.h"
#include <OgreLogManager.h>
#include <OgreUTFString.h>

int CPairStyle::SaveDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup)
{
    if (fileName == EMPTY_WSTRING || !dataGroup)
        return 0;
    FILE* file = NULL;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(fileName, info, false, false, false);
    if (!info.m_bExists) {
        std::wstring cleanPath = FILESYSTEM::CleanPath(fileName);
        std::wstring localPath = FILESYSTEM::GetLocalPath();
        SetCurrentDirectory(localPath.c_str());
        info.m_sPath = cleanPath;
        info.m_sModName = "";
    }
    info.m_sPath = STRINGS::StringConvertToWide(info.m_sModName) + info.m_sPath;
    _wfopen_s(&file, info.m_sPath.c_str(), L"wb");
    if (!file) {
        std::wstring message = L"Unable to save file: " + info.m_sPath + L"\n\nDo you need to get a lock?";
        Ogre::LogManager::getSingleton().logMessage(
            std::string(STRINGS::StringConvertToNarrow(message.c_str()).c_str()),
            Ogre::LML_CRITICAL, false);
    }
    if (!file)
        return 0;
    unsigned short marker = 0xfeff;
    std::fwrite(&marker, 2, 1, file);
    Save(file, dataGroup);
    std::fclose(file);
    CBinaryStyle binary;
    binary.SaveDataGroupToFile(info.m_sPath + L".ADM", dataGroup);
    return 1;
}

void CPairStyle::ParseSubGroups(CFileReader* reader, CDataGroup* dataGroup)
{
    if (!dataGroup || !reader)
        return;
    std::queue<std::wstring> tokens;
    for (;;) {
        reader->ReadLineTokenize(&tokens, L":\n\t\r", L'`');
        if (reader->EndOfFile())
            return;
        if (!tokens.empty()) {
            std::wstring token = tokens.front();
            tokens.pop();
            if (token.length() > 2) {
                std::wstring::size_type close;
                if (token.find(L'<') == 0 &&
                    (close = token.rfind(L'>', token.length()-1)) != std::wstring::npos) {
                    std::wstring type(token, 1, close-1);
                    std::wstring name(token, close+1, token.length()-close-1);
                    if (!tokens.empty()) {
                        std::wstring value = tokens.front();
                        tokens.pop();
                        while (!tokens.empty()) {
                            value = value + L":" + tokens.front();
                            tokens.pop();
                        }
                        dataGroup->AddDataValue(STRINGS::StringUpper(name), type, value);
                    }
                } else if (token.find(L'[') == 0 && token.find(L'/', 1) == 1 &&
                           token.rfind(L']', token.length()-1) == token.length()-1) {
                    return;
                } else if (token.find(L'[') == 0 &&
                           token.rfind(L']', token.length()-1) == token.length()-1) {
                    if (dataGroup->GetGroupName() == L"") {
                        dataGroup->SetGroupName(STRINGS::StringUpper(
                            std::wstring(token, 1, token.length()-2)));
                    } else {
                        CDataGroup* child = dataGroup->AddDataGroup(STRINGS::StringUpper(
                            std::wstring(token, 1, token.length()-2)));
                        ParseSubGroups(reader, child);
                    }
                }
            }
        }
        while (!tokens.empty())
            tokens.pop();
    }
}

int CPairStyle::LoadDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup,
                                   CTimerStatics*)
{
    if (fileName == EMPTY_WSTRING || !dataGroup)
        return 0;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(fileName, info, false, true, false);
    CFileReader reader;
    if (!reader.ReadFile(info.m_sPath))
        return 0;
    dataGroup->SetGroupName(L"");
    ParseSubGroups(&reader, dataGroup);
    CBinaryStyle binary;
    binary.SaveDataGroupToFile(static_cast<std::wstring>(
        Ogre::UTFString(info.m_sModName) + Ogre::UTFString(info.m_sPath) + Ogre::UTFString(".adm")),
        dataGroup);
    return 1;
}
