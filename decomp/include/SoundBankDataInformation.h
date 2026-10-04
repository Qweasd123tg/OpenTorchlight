#ifndef SOUNDBANKDATAINFORMATION_H
#define SOUNDBANKDATAINFORMATION_H

#include <map>
#include <string>

#include "DataGroup.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CSoundData;

class CSoundBankDataInformation : public CRunicCore
{
public:
    virtual ~CSoundBankDataInformation();

    CSoundData* getSoundDataObjectByGuid(long long guid);
    int getSoundIndexInCategoryByName(unsigned int categoryID, const std::wstring& soundName);
    CSoundData* getSoundDataObjectByGuidThatIsClosest(long long guid);
    std::wstring getSoundNameByCategoryIndex(unsigned int categoryID, unsigned int soundIndex);
    std::wstring getCategoryNameByID(unsigned int categoryID);
    CSoundData* getSoundDataObject(const std::wstring& soundName);
    unsigned int getCategoryID(const std::wstring& categoryName);
    CSoundData* getSoundDataObject(const std::wstring& categoryName, const std::wstring& soundName);
    void getSoundNames(TArrayList<std::wstring>* soundNames);
    void getSoundNamesByCatgoryName(const std::wstring& categoryName, TArrayList<std::wstring>* soundNames);

    CSoundData* createSoundData(CDataGroup* dataGroup);
    void parseSoundData(const std::wstring& path);
    void reload(CResourceSettings* resourceSettings);

    CSoundBankDataInformation(CResourceSettings* resourceSettings);

    TArrayList<std::wstring> m_categoryNames;
    std::map<unsigned int, std::map<std::wstring, CSoundData*> > m_soundsByCategoryIndex;
    std::map<long long, CSoundData*> m_soundsByGuid;
    TArrayList<CSoundData*> m_sounds;
};

#endif
