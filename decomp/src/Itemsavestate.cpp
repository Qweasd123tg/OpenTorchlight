#include "Effect.h"
#include "ItemSaveState.h"


CItemSaveState::CItemSaveState()
    : m_iStateValue28(0), m_iOriginalGuid(-1), m_iStateValue38(-1), m_iParentHierarchyHash(-1),
      m_bSaveFlag48(false), m_bSaveFlag5C(false), m_bEnabled(false), m_iUnitValue60(-1),
      m_StateByte74(0), m_bIdentified(false), m_iBaseDamage(-1), m_iBaseArmor(-1),
      m_iRoomIndex(-1), m_bItemFlag17C(true)
{
}

CItemSaveState::~CItemSaveState()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < static_cast<int>(m_Effects[i].size()); ++j) {
            if (m_Effects[i][j]) {
                delete m_Effects[i][j];
                m_Effects[i][j] = NULL;
            }
        }
    }
    m_Effects[0].clear();
    for (unsigned int i = 0; i < m_SocketedItems.size(); ++i) {
        if (m_SocketedItems[i]) {
            delete m_SocketedItems[i];
            m_SocketedItems[i] = NULL;
        }
    }
    m_SocketedItems.clear();
}

#include "UTFConversion.h"
#include "FileUtilities.h"
#include "EmptyStrings.h"
#include "StringUtilities.h"
#include "UnitThemes.h"

namespace {
template<class T> void writeItemSaveValue(FILE* file, const T& value)
{
    std::fwrite(&value, sizeof(value), 1, file);
}
void writeItemSaveText(FILE* file, const std::wstring& text)
{
    unsigned short length = static_cast<unsigned short>(text.length());
    writeItemSaveValue(file, length);
    WriteUTF32ToUTF16(file, text, length);
}
template<class T> void readItemSaveValue(FILE* file, T& value)
{
    std::fread(&value, sizeof(value), 1, file);
}
std::wstring readItemSaveText(FILE* file)
{
    unsigned short length;
    readItemSaveValue(file, length);
    return FILESYSTEM::ReadWString(file, length);
}
}

void CItemSaveState::save(FILE* file)
{
    writeItemSaveValue(file, m_iUnitValue60);
    writeItemSaveText(file, m_sItemName);
    writeItemSaveText(file, m_sStateString18);
    writeItemSaveText(file, m_sStateString20);
    writeItemSaveValue(file, m_iOriginalGuid);
    writeItemSaveValue(file, m_iParentHierarchyHash);
    writeItemSaveValue(file, m_bSaveFlag48);
    writeItemSaveValue(file, m_iStateValue38);
    writeItemSaveValue(file, m_iSpawnerGuid);
    writeItemSaveValue(file, m_iStateValue28);
    writeItemSaveValue(file, m_iStateValue6C);
    writeItemSaveValue(file, m_iIndex);
    writeItemSaveValue(file, m_bSaveFlag5C);
    writeItemSaveValue(file, m_bEnabled);
    writeItemSaveValue(file, m_bBlocksPath);
    writeItemSaveValue(file, m_bItemFlag17C);
    writeItemSaveValue(file, m_StateByte74);
    writeItemSaveValue(file, m_bIdentified);
    writeItemSaveValue(file, m_vLocalPosition);
    writeItemSaveValue(file, m_vWorldPosition);
    writeItemSaveValue(file, m_mOrientation);
    writeItemSaveValue(file, m_iStackSize);
    writeItemSaveValue(file, m_iSocketCount);
    unsigned int count = m_SocketedItems.size();
    writeItemSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
        m_SocketedItems[i]->save(file);
    writeItemSaveValue(file, m_iBaseDamage);
    writeItemSaveValue(file, m_iBaseArmor);
    writeItemSaveValue(file, m_iRoomIndex);
    writeItemSaveValue(file, m_iQuestGuid);
    writeItemSaveValue(file, m_iQuestState);
    unsigned short damageCount = static_cast<unsigned short>(m_DamageTypes.size());
    writeItemSaveValue(file, damageCount);
    // Only the prefix narrows: the original loop writes the entire list.
    for (unsigned int i = 0; i < m_DamageTypes.size(); ++i)
    {
        float bonus = static_cast<float>(m_DamageBonuses[i]);
        writeItemSaveValue(file, bonus);
        writeItemSaveValue(file, m_DamageTypes[i]);
    }
    for (int group = 0; group < 3; ++group)
    {
        count = m_Effects[group].size();
        writeItemSaveValue(file, count);
        for (unsigned int i = 0; i < count; ++i)
        {
            CEffect* effect = m_Effects[group][i];
            writeItemSaveText(file, effect->m_sName);
            writeItemSaveText(file, effect->m_name88);
            writeItemSaveText(file, effect->m_particleName);
            writeItemSaveText(file, effect->m_name90);
            writeItemSaveValue(file, effect->m_flag31);
            writeItemSaveValue(file, effect->m_eType);
            writeItemSaveValue(file, effect->m_eDamageType);
            writeItemSaveValue(file, effect->m_flag33);
            writeItemSaveValue(file, effect->m_modifierFlag32);
            writeItemSaveValue(file, effect->m_flag30);
            writeItemSaveValue(file, effect->m_flag37);
            writeItemSaveValue(file, effect->m_activation);
            writeItemSaveValue(file, effect->m_iLevel);
            long long theme = effect->m_pUnitTheme ? effect->m_pUnitTheme->getGuid() : -1;
            writeItemSaveValue(file, theme);
            writeItemSaveValue(file, effect->m_value3C);
            writeItemSaveValue(file, effect->m_value40);
            writeItemSaveValue(file, effect->m_value44);
            int duration = static_cast<int>(effect->m_fValue24);
            writeItemSaveValue(file, duration);
            writeItemSaveValue(file, effect->m_fRemainingDuration);
            writeItemSaveValue(file, effect->m_value38);
            writeItemSaveValue(file, effect->m_fValueC0);
            for (unsigned int value = 0; value < 4; ++value)
                writeItemSaveValue(file, effect->m_values[value]);
        }
    }
}

void CItemSaveState::load(FILE* file, unsigned int version)
{
    readItemSaveValue(file, m_iUnitValue60);
    m_sItemName = readItemSaveText(file);
    m_sStateString18 = readItemSaveText(file);
    m_sStateString20 = readItemSaveText(file);
    readItemSaveValue(file, m_iOriginalGuid);
    if (version > 16)
        readItemSaveValue(file, m_iParentHierarchyHash);
    else if (version == 16)
    {
        int oldParent = 0;
        readItemSaveValue(file, oldParent);
    }
    readItemSaveValue(file, m_bSaveFlag48);
    readItemSaveValue(file, m_iStateValue38);
    readItemSaveValue(file, m_iSpawnerGuid);
    if (version > 13)
        readItemSaveValue(file, m_iStateValue28);
    m_iStateValue6C = 0;
    if (version > 22)
        readItemSaveValue(file, m_iStateValue6C);
    readItemSaveValue(file, m_iIndex);
    readItemSaveValue(file, m_bSaveFlag5C);
    readItemSaveValue(file, m_bEnabled);
    if (version > 17)
        readItemSaveValue(file, m_bBlocksPath);
    readItemSaveValue(file, m_bItemFlag17C);
    readItemSaveValue(file, m_StateByte74);
    readItemSaveValue(file, m_bIdentified);
    readItemSaveValue(file, m_vLocalPosition);
    readItemSaveValue(file, m_vWorldPosition);
    readItemSaveValue(file, m_mOrientation);
    readItemSaveValue(file, m_iStackSize);
    readItemSaveValue(file, m_iSocketCount);
    unsigned int count = 0;
    readItemSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
    {
        CItemSaveState* child = new CItemSaveState;
        m_SocketedItems.push_back(child);
        child->load(file, version);
    }
    readItemSaveValue(file, m_iBaseDamage);
    readItemSaveValue(file, m_iBaseArmor);
    readItemSaveValue(file, m_iRoomIndex);
    if (version > 18)
    {
        readItemSaveValue(file, m_iQuestGuid);
        readItemSaveValue(file, m_iQuestState);
    }
    else
    {
        std::fread(&m_iQuestGuid, 4, 1, file);
        readItemSaveValue(file, m_iQuestState);
        m_iQuestGuid = -1;
        m_iQuestState = -1;
    }
    unsigned short damageCount;
    readItemSaveValue(file, damageCount);
    for (unsigned short i = 0; i < damageCount; ++i)
    {
        float bonus;
        EDAMAGE_TYPES damage;
        readItemSaveValue(file, bonus);
        readItemSaveValue(file, damage);
        m_DamageTypes.push_back(damage);
        m_DamageBonuses.push_back(static_cast<int>(bonus));
    }
    for (int group = 0; group < 3; ++group)
    {
        int effects;
        readItemSaveValue(file, effects);
        for (int i = 0; i < effects; ++i)
        {
            std::wstring name = readItemSaveText(file);
            std::wstring secondaryName(EMPTY_WSTRING);
            if (version > 3)
                secondaryName = readItemSaveText(file);
            std::wstring fx = readItemSaveText(file);
            std::wstring graphName(EMPTY_WSTRING);
            if (version > 6)
                graphName = readItemSaveText(file);
            unsigned char flag31, flag33, flag32, flag30;
            int type, damageType, activation;
            unsigned int level;
            readItemSaveValue(file, flag31);
            readItemSaveValue(file, type);
            readItemSaveValue(file, damageType);
            readItemSaveValue(file, flag33);
            readItemSaveValue(file, flag32);
            readItemSaveValue(file, flag30);
            bool graphs = false;
            if (version > 6)
            {
                unsigned char byte;
                readItemSaveValue(file, byte);
                graphs = byte != 0;
            }
            readItemSaveValue(file, activation);
            readItemSaveValue(file, level);
            long long theme = -1;
            if (version > 4)
                readItemSaveValue(file, theme);
            else
            {
                int oldTheme = -1;
                readItemSaveValue(file, oldTheme);
            }
            int value3C, value40, value44, duration;
            float remaining, value38;
            readItemSaveValue(file, value3C);
            readItemSaveValue(file, value40);
            readItemSaveValue(file, value44);
            readItemSaveValue(file, duration);
            readItemSaveValue(file, remaining);
            readItemSaveValue(file, value38);
            CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(type), flag30 != 0,
                static_cast<EEFFECT_ACTIVATION>(activation), static_cast<float>(duration),
                0.0f, value38, graphs);
            effect->setFX(fx);
            if (graphs)
                effect->setGraphs(graphName);
            float baseValue;
            readItemSaveValue(file, baseValue);
            for (unsigned int value = 0; value < 4; ++value)
            {
                readItemSaveValue(file, effect->m_values[value]);
                effect->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            }
            if (theme != -1)
                effect->m_pUnitTheme = CUnitThemes::getSingleton()->getTheme(theme);
            effect->m_eDamageType = static_cast<EDAMAGE_TYPES>(damageType);
            effect->m_fRemainingDuration = remaining;
            effect->m_value3C = value3C;
            effect->m_value40 = value3C;
            effect->m_value44 = value44;
            effect->m_iLevel = level >= 1001 ? 0 : level;
            effect->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            effect->m_modifierFlag32 = flag32 != 0;
            effect->m_flag33 = flag33 != 0;
            effect->m_flag31 = flag31 != 0;
            effect->m_sName = STRINGS::StringUpper(name);
            effect->m_name88 = STRINGS::StringUpper(secondaryName);
            effect->m_fValueC0 = baseValue;
            m_Effects[group].push_back(effect);
        }
    }
}
