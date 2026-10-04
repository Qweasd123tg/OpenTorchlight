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

        if (category != m_soundsByCategoryIndex.end())
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
    for (unsigned int i = 0; i < m_categoryNames.size(); ++i) {
        if (m_categoryNames[i] == categoryName)
            return i;
    }

    return static_cast<unsigned int>(-1);
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
        m_categoryNames.~TArrayList();
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
