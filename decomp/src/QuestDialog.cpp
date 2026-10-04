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

extern "C" void CSoundBank_stop(CSoundBank*, int)
    __asm__("_ZN10CSoundBank4stopEi");

void CQuestDialog::stopDialogSound()
{
    if (m_pSoundBank != NULL)
        CSoundBank_stop(m_pSoundBank, 0x25);
}

void CQuestDialog::populate()
{
    stopDialogSound();
    if (m_pSoundBank != NULL) {
        delete reinterpret_cast<CRunicCore *>(m_pSoundBank);
        m_pSoundBank = NULL;
    }
}
