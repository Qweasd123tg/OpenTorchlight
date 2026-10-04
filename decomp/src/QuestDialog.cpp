#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestDialog.h"
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
