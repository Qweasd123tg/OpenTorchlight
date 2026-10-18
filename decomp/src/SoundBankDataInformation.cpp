#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SoundBankDataInformation.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "SoundData.h"
#include "TArrayList.h"

CSoundData* CSoundBankDataInformation::getSoundDataObjectByGuid(long long guid)
{
    std::map<long long, CSoundData*>::iterator i = m_soundsByGuid.find(guid);
    if (i != m_soundsByGuid.end())
    {
        return i->second;
    }

    return NULL;
}

int CSoundBankDataInformation::getSoundIndexInCategoryByName(unsigned int categoryID, const std::wstring& soundName)
{
    std::map<unsigned int, std::map<std::wstring, CSoundData*> >::iterator category =
        m_soundsByCategoryIndex.find(categoryID);

    if (category != m_soundsByCategoryIndex.end())
    {
        int index = 0;
        std::map<std::wstring, CSoundData*>::iterator sound = category->second.begin();

        for (; sound != category->second.end(); ++sound, ++index)
        {
            if (sound->first == soundName)
                return index;
        }
    }

    return -1;
}

CSoundData* CSoundBankDataInformation::getSoundDataObjectByGuidThatIsClosest(long long guid)
{
    std::map<long long, CSoundData*>::iterator sound = m_soundsByGuid.find(guid);
    if (sound != m_soundsByGuid.end())
    {
        return sound->second;
    }

    CSoundData* closestSound = m_soundsByGuid.begin()->second;
    unsigned int maximumMatchingBits = 0;

    for (sound = m_soundsByGuid.begin(); sound != m_soundsByGuid.end(); ++sound)
    {
        const long long difference = guid ^ sound->first;
        unsigned int matchingBits = 0;

        for (unsigned int bit = 64; bit != 0; --bit)
        {
            if (difference & (1L << (bit - 1)))
            {
                break;
            }

            ++matchingBits;
        }

        if (matchingBits > maximumMatchingBits)
        {
            maximumMatchingBits = matchingBits;
            closestSound = sound->second;
        }
    }

    return closestSound;
}

std::wstring CSoundBankDataInformation::getSoundNameByCategoryIndex(unsigned int categoryID, unsigned int soundIndex)
{
    std::map<unsigned int, std::map<std::wstring, CSoundData*> >::iterator category =
        m_soundsByCategoryIndex.find(categoryID);

    if (category == m_soundsByCategoryIndex.end())
        return L"";

    std::map<std::wstring, CSoundData*>::iterator sound = category->second.begin();
    if (sound == category->second.end())
        return EMPTY_WSTRING;

    while (soundIndex--) {
        ++sound;
        if (sound == category->second.end())
            return EMPTY_WSTRING;
    }

    return sound->first;
}

std::wstring CSoundBankDataInformation::getCategoryNameByID(unsigned int categoryID)
{
    if (categoryID < m_categoryNames.size())
        return m_categoryNames[categoryID];

    if (!m_categoryNames.size())
        return EMPTY_WSTRING;

    return m_categoryNames[0];
}

CSoundData* CSoundBankDataInformation::getSoundDataObject(const std::wstring& soundName)
{
    for (unsigned int categoryID = 0; categoryID < m_categoryNames.size(); ++categoryID)
    {
        std::map<unsigned int, std::map<std::wstring, CSoundData*> >::iterator category =
            m_soundsByCategoryIndex.find(categoryID);

        if (category == m_soundsByCategoryIndex.end())
            return NULL;
        {
            std::map<std::wstring, CSoundData*>::iterator sound =
                category->second.find(soundName);

            if (sound != category->second.end())
                return sound->second;
        }
    }

    return NULL;
}

unsigned int CSoundBankDataInformation::getCategoryID(const std::wstring& categoryName)
{
    return m_categoryNames.find(categoryName);
}

CSoundData* CSoundBankDataInformation::getSoundDataObject(const std::wstring& categoryName, const std::wstring& soundName)
{
    int categoryID = m_categoryNames.find(categoryName);
    if (categoryID == -1)
        return NULL;

    std::map<unsigned int, std::map<std::wstring, CSoundData*> >::iterator category =
        m_soundsByCategoryIndex.find(categoryID);
    if (category == m_soundsByCategoryIndex.end())
        return NULL;

    std::map<std::wstring, CSoundData*>::iterator sound = category->second.find(soundName);
    if (sound == category->second.end())
        return NULL;

    return sound->second;
}

void CSoundBankDataInformation::reload(CResourceSettings* resourceSettings)
{
    if (resourceSettings != NULL)
    {
        m_sounds.deleteAll();
        m_soundsByCategoryIndex.clear();
        m_soundsByGuid.clear();
        m_sounds.clear();
        m_categoryNames.clear();
        parseSoundData(resourceSettings->GetString(KRESOURCESETTING_S_SOUND_DATA_FOLDER));
    }
}

CSoundBankDataInformation::CSoundBankDataInformation(CResourceSettings* resourceSettings)
    : CRunicCore(),
      m_categoryNames(10),
      m_soundsByCategoryIndex(),
      m_soundsByGuid(),
      m_sounds(25)
{
    if (resourceSettings != NULL)
        parseSoundData(resourceSettings->GetString(KRESOURCESETTING_S_SOUND_DATA_FOLDER));
}

void CSoundBankDataInformation::getSoundNames(TArrayList<std::wstring>* names)
{
    for (unsigned int category = 0; category < m_categoryNames.size(); ++category) {
        std::map<std::wstring, CSoundData*> sounds = m_soundsByCategoryIndex[category];
        for (std::map<std::wstring, CSoundData*>::iterator i = sounds.begin(); i != sounds.end(); ++i)
            names->add(i->first);
    }
}

void CSoundBankDataInformation::getSoundNamesByCatgoryName(const std::wstring& category, TArrayList<std::wstring>* names)
{
    int index = m_categoryNames.find(category);
    {
        std::map<std::wstring, CSoundData*> sounds = m_soundsByCategoryIndex[index];
        for (std::map<std::wstring, CSoundData*>::iterator i = sounds.begin(); i != sounds.end(); ++i)
            names->add(i->first);
    }
}

CSoundBankDataInformation::~CSoundBankDataInformation()
{
    m_sounds.deleteAll();
}

#include "StringUtilities.h"
#include "FileSystem.h"
CSoundData* CSoundBankDataInformation::createSoundData(CDataGroup* group)
{
    if (!group) return NULL;
    CDataGroup* files = group->GetDataGroupByName(L"FILES", false);
    if (!files || !files->GetNumberOfDataValues()) return NULL;
    CSoundData* sound = new CSoundData;
    sound->m_iGuid = -1;
    sound->m_flag2c = false;
    sound->m_files.setGrowBy(1);
    sound->m_group = NULL;
    sound->m_iGuid = group->GetDataValue(L"GUID", static_cast<long long>(-1));
    if (sound->m_iGuid == -1 || !files->GetNumberOfDataValues()) {
        // The original deletes its input here and leaves the allocated sound.
        delete group;
        return NULL;
    }
    sound->m_float38 = group->GetDataValue(L"RADIUS", 0.0f);
    sound->m_float28 = group->GetDataValue(L"VOLUME", 1.0f);
    sound->m_float30 = group->GetDataValue(L"FREQUENCYVARIATION", 0.0f);
    sound->m_float34 = group->GetDataValue(L"VOLUMEVARIATION", 0.0f);
    sound->m_name = STRINGS::StringUpper(group->GetDataValue(L"NAME", EMPTY_WSTRING));
    sound->m_category = STRINGS::StringUpper(group->GetDataValue(L"CATEGORY", EMPTY_WSTRING));
    sound->m_flag2c = group->GetDataValue(L"LOOPS", false);
    sound->m_probability = group->GetDataValue(L"PLAYCHANCE", -1);
    sound->m_files.setGrowBy(files->GetNumberOfDataValues());
    for (unsigned int i = 0; i < files->GetNumberOfDataValues(); ++i)
        sound->m_files.add(files->GetDataValue(i)->GetValueString(true));
    return sound;
}

void CSoundBankDataInformation::parseSoundData(const std::wstring& path)
{
    TArrayList<std::wstring> files(10);
    CFileSystem::getSingleton()->getFileList(path, files, L"*.dat", false, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i) {
        std::wstring file = files[i];
        CDataGroup data(EMPTY_WSTRING, NULL, 20, 10, NULL);
        data.LoadFile(file, NULL);
        for (unsigned int j = 0; j < data.GetNumberOfDataGroups(); ++j) {
            CSoundData* sound = createSoundData(data.GetDataGroup(j));
            if (!sound) continue;
            if (m_soundsByGuid.find(sound->m_iGuid) != m_soundsByGuid.end()) {
                delete sound;
                continue;
            }
            m_soundsByGuid[sound->m_iGuid] = sound;
            m_sounds.add(sound);
            int category = m_categoryNames.find(sound->m_category);
            if (category == -1) {
                m_categoryNames.add(sound->m_category);
                category = m_categoryNames.size() - 1;
            }
            m_soundsByCategoryIndex[category][sound->m_name] = sound;
        }
    }
}
