#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestDialog.h"
#include "QuestDefines.h"
#include "QuestDialogItem.h"
#include "StringUtilities.h"
#include "UnitResourceList.h"
#include "RunicCore.h"
#include "SoundBank.h"

void CQuestDialog::reinitialize()
{
    m_bDialogInitialized = false;
    m_bItemsGiven = false;
}

void CQuestDialog::load(_IO_FILE* pFile)
{
    char value;
    fread(&value, 1, 1, pFile);
    m_bDialogInitialized = value;
    fread(&value, 1, 1, pFile);
    m_bItemsGiven = value;
}

void CQuestDialog::save(_IO_FILE* pFile)
{
    unsigned char value;
    value = m_bDialogInitialized;
    fwrite(&value, 1, 1, pFile);
    value = m_bItemsGiven;
    fwrite(&value, 1, 1, pFile);
}

void CQuestDialog::stopDialogSound()
{
    if (m_pSoundBank != NULL)
        m_pSoundBank->stop(0x25);
}

void CQuestDialog::populate()
{
    stopDialogSound();
    if (m_pSoundBank != NULL) {
        delete reinterpret_cast<CRunicCore *>(m_pSoundBank);
        m_pSoundBank = NULL;
    }
}

bool CQuestDialog::parseDialogTag(const std::wstring& sTag, CDataGroup* pDataGroup)
{
    if (pDataGroup == NULL || m_pQuest == NULL)
        return false;

    m_bIconAboveHead = pDataGroup->GetDataValue(L"ICONABOVEHEAD", true);
    m_bFloatyText = pDataGroup->GetDataValue(L"FLOATYTEXT", false);
    std::wstring sound = pDataGroup->GetDataValue(L"SOUND", EMPTY_WSTRING);
    m_cameraOffset.x = pDataGroup->GetDataValue(L"CAMERAMODX", 0.0f);
    m_cameraOffset.y = pDataGroup->GetDataValue(L"CAMERAMODY", 0.0f);
    m_cameraOffset.z = pDataGroup->GetDataValue(L"CAMERAMODZ", 0.0f);
    m_sThemeOverride = STRINGS::StringUpper(pDataGroup->GetDataValue(L"THEMEOVERRIDE", EMPTY_WSTRING));
    m_bMakePetOnAccept = pDataGroup->GetDataValue(L"MAKE_PET_ON_ACCEPT", false);
    m_bLookAtPlayer = pDataGroup->GetDataValue(L"LOOK_AT_PLAYER", true);
    m_bRemoveAsPetOnComplete = pDataGroup->GetDataValue(L"REMOVE_AS_PET_ON_COMPLETE", true);
    m_bDestroyPet = pDataGroup->GetDataValue(L"DESTROY_PET", true);
    if (sound != EMPTY_WSTRING)
        m_sSoundName = STRINGS::StringUpper(sound);

    m_iDialogType = 0;
    for (int i = 1; i < 6; ++i)
    {
        if (pDataGroup->GetGroupName() == gQUEST_DIALOG_TYPE_NAMES[i])
        {
            m_iDialogType = i;
            break;
        }
    }

    std::vector<CDataGroup*> giveGroups;
    std::vector<CDataGroup*> removeGroups;
    const std::wstring* itemNames = reinterpret_cast<const std::wstring*>(g_QUEST_TAG_DIALOG_ITEM_NAMES);
    pDataGroup->GetDataGroupsMatchingName(itemNames[0], &giveGroups);
    pDataGroup->GetDataGroupsMatchingName(itemNames[1], &removeGroups);
    for (unsigned int i = 0; i < giveGroups.size(); ++i)
    {
        CQuestDialogItem* item = new CQuestDialogItem(this);
        item->parseDialogItemGroup(giveGroups[i], true);
        m_dialogItemsToGive.add(item);
    }
    for (unsigned int i = 0; i < removeGroups.size(); ++i)
    {
        CQuestDialogItem* item = new CQuestDialogItem(this);
        item->parseDialogItemGroup(removeGroups[i], false);
        m_dialogItemsToRemove.add(item);
    }

    if (m_iDialogType == 0 || pDataGroup->GetNumberOfDataValues() == 0)
        return false;
    for (unsigned int i = 0; i < pDataGroup->GetNumberOfDataValues(); ++i)
    {
        CDataValue::EDATAVALUETYPES type = pDataGroup->GetDataValue(i)->GetValueType();
        if ((type == CDataValue::DATAVALUE_TRANSLATE || type == CDataValue::DATAVALUE_STRING)
            && pDataGroup->GetDataValue(i)->GetDataValueName() == L"DIALOG")
        {
            std::wstring text = STRINGS::replaceWString(
                pDataGroup->GetDataValue(i)->GetValueString(true), L"\\n", L"\n");
            m_dialogText.add(text);
        }
    }
    if (m_dialogText.size() == 0)
        return false;

    m_sNPCName = pDataGroup->GetDataValue(L"UNITNAME", EMPTY_WSTRING);
    if (m_sNPCName.empty())
        m_sNPCName = sTag;
    if (m_sNPCName != EMPTY_WSTRING)
    {
        const std::wstring* resourceNames = reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES);
        m_pNPCDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(resourceNames[1], m_sNPCName);
        if (m_pNPCDataGroup == NULL)
        {
            m_pNPCDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(resourceNames[0], m_sNPCName);
            if (m_pNPCDataGroup == NULL)
                m_pNPCDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(resourceNames[3], m_sNPCName);
        }
    }
    return true;
}

#include "Quest.h"
#include "QuestManager.h"
#include "Utilities.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "MasterResourceManager.h"

bool CQuestDialog::dialogIsForNPC(CBaseUnit* unit)
{
    if (m_pQuest == NULL) return false;
    if (m_pNPCDataGroup != NULL)
        return unit != NULL && m_pNPCDataGroup == unit->getDataGroup();
    if (m_pQuest->m_iUnknown1E8 == 0) return false;
    return reinterpret_cast<CDataGroup*>(m_pQuest->m_iUnknown1E8) == unit->getDataGroup();
}

std::wstring CQuestDialog::getDialog(bool random)
{
    int index = 0;
    if (m_dialogText.size() > 1 && m_pQuest != NULL)
    {
        if (m_pQuest->m_iUnknown1C != -1) UTILITIES::setSeed(m_pQuest->m_iUnknown1C);
        index = UTILITIES::randomIntegerBetween(1,m_dialogText.size()) - 1;
    }
    if (!random && m_pQuest != NULL)
        return m_pQuest->replaceStringTags(m_dialogText[index]);
    return m_dialogText[index];
}

void CQuestDialog::giveOrRemoveItems(CBaseUnit* unit)
{
    if (m_bItemsGiven) return;
    for (unsigned int i=0;i<m_dialogItemsToRemove.size();++i)
        m_dialogItemsToRemove[i]->dialogComplete(m_pQuest->getPlayer());
    for (unsigned int i=0;i<m_dialogItemsToGive.size();++i)
        m_dialogItemsToGive[i]->dialogComplete(m_pQuest->getPlayer());
    CPlayer* player = m_pQuest->getPlayer();
    if (m_bMakePetOnAccept && player != NULL && unit != NULL)
    {
        CCharacter* character = dynamic_cast<CCharacter*>(unit);
        if (character != NULL)
        {
            player->addPet(character);
            m_pQuest->m_pQuestManager->calculateNPCIcon(character);
        }
    }
    m_bItemsGiven = true;
}

void CQuestDialog::cleanUp()
{
    CPlayer* player = m_pQuest->getPlayer();
    if (!m_bDialogInitialized || !m_bRemoveAsPetOnComplete || player == NULL) return;
    for (int i=0;i<static_cast<int>(player->m_Followers.size());++i)
    {
        CCharacter* pet = player->m_Followers[i];
        if (m_pNPCDataGroup != pet->getDataGroup()) continue;
        player->removePet(pet);
        if (m_bDestroyPet)
        {
            pet->m_bBaseUnitFlag190 = true;
            pet->setVisible(false,true);
        }
        else m_pQuest->m_pQuestManager->calculateNPCIcon(pet);
        --i;
    }
}

void CQuestDialog::playDialogSound()
{
    if (m_pSoundBank == NULL)
    {
        CSoundData* data = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation->getSoundDataObject(m_sSoundName);
        if (data != NULL)
        {
            if (m_pSoundBank == NULL)
                m_pSoundBank = new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
            if (m_pSoundBank != NULL) m_pSoundBank->addSample(0x25,data->m_iGuid);
        }
    }
    if (m_pSoundBank != NULL) m_pSoundBank->playSample(0x25,NULL,0.0f,0.0f,false);
}

CQuestDialog::CQuestDialog(CQuest* quest)
    : CRunicCore(),m_pQuest(quest),m_dialogText(1),m_dialogItemsToGive(1),m_dialogItemsToRemove(1),
      m_sNPCName(),m_pNPCDataGroup(NULL),m_iDialogType(0),
      m_bFloatyText(false),m_bIconAboveHead(true),m_bDialogInitialized(false),m_bItemsGiven(false),
      m_bMakePetOnAccept(true),m_bRemoveAsPetOnComplete(false),m_bDestroyPet(false),m_bLookAtPlayer(false),
      m_pSoundBank(NULL),m_cameraOffset(0,0,0),m_sThemeOverride(EMPTY_WSTRING),m_sSoundName()
{
}

CQuestDialog::~CQuestDialog()
{
    m_dialogItemsToGive.deleteAll();
    m_dialogItemsToRemove.deleteAll();
    if (m_pSoundBank != NULL)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
}
