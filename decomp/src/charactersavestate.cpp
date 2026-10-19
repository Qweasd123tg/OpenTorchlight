#include "EmptyStrings.h"
#include "CharacterSaveState.h"
#include "ItemSaveState.h"
#include "Effect.h"


CCharacterSaveState::CCharacterSaveState()
    : m_guid10(-1), m_flag18(false), m_guid20(-1), m_guid28(-1),
      m_flag30(false), m_flag31(false), m_flag32(false), m_flag33(false),
      m_flag34(false), m_value38(0), m_guid50(-1), m_guid58(-1),
      m_value60(-1), m_value64(0), m_value68(0), m_guidB8(-1),
      m_guidC0(-1), m_guidC8(-1), m_valueD0(0), m_valueD4(0),
      m_valueD8(0), m_valueDC(0), m_hp(0), m_valueE4(0), m_valueE8(0),
      m_value184(-1), m_guid200(-1), m_value208(-1), m_flag20C(false), m_strings(10)
{
}

CCharacterSaveState::~CCharacterSaveState()
{
    for (int group = 0; group < 3; ++group)
        for (int i = 0; i < static_cast<int>(m_items[group].size()); ++i)
            if (m_items[group][i]) {
                delete m_items[group][i];
                m_items[group][i] = NULL;
            }
    for (unsigned int i = 0; i < m_pets.size(); ++i)
        if (m_pets[i]) {
            delete m_pets[i];
            m_pets[i] = NULL;
        }
    m_pets.clear();
    m_items[0].clear();
}

#include "UTFConversion.h"
#include "FileUtilities.h"
#include "UnitTheme.h"
#include "UnitThemes.h"

namespace {
template<class T> void writeCharacterSaveValue(FILE* file, const T& value)
{
    std::fwrite(&value, sizeof(value), 1, file);
}

void writeCharacterSaveText(FILE* file, const std::wstring& value)
{
    unsigned short length = static_cast<unsigned short>(value.length());
    writeCharacterSaveValue(file, length);
    WriteUTF32ToUTF16(file, value, length);
}
}

void CCharacterSaveState::save(FILE* file)
{
    writeCharacterSaveValue(file, m_flag20C);
    writeCharacterSaveValue(file, m_guid20);
    writeCharacterSaveValue(file, m_guid28);
    writeCharacterSaveValue(file, m_guid10);
    writeCharacterSaveValue(file, m_flag18);
    writeCharacterSaveValue(file, m_flag30);
    writeCharacterSaveValue(file, m_flag31);
    writeCharacterSaveValue(file, m_flag32);
    writeCharacterSaveValue(file, m_flag33);
    writeCharacterSaveValue(file, m_flag34);
    writeCharacterSaveValue(file, m_transformationTime);
    writeCharacterSaveValue(file, m_townTravelTime);
    writeCharacterSaveValue(file, m_petMode);
    writeCharacterSaveValue(file, m_alignment);
    writeCharacterSaveValue(file, m_scale);
    writeCharacterSaveValue(file, m_guid50);
    writeCharacterSaveValue(file, m_guid58);
    writeCharacterSaveValue(file, m_value60);
    writeCharacterSaveText(file, m_name);
    writeCharacterSaveValue(file, m_value64);
    writeCharacterSaveValue(file, m_value68);
    writeCharacterSaveValue(file, m_position);
    writeCharacterSaveValue(file, m_orientation);
    writeCharacterSaveValue(file, m_valueD0);
    writeCharacterSaveValue(file, m_valueD4);
    writeCharacterSaveValue(file, m_valueD8);
    writeCharacterSaveValue(file, m_valueDC);
    writeCharacterSaveValue(file, m_hp);
    writeCharacterSaveValue(file, m_valueE4);
    writeCharacterSaveValue(file, m_valueE8);
    writeCharacterSaveValue(file, m_mana);
    writeCharacterSaveValue(file, m_maxManaBase);
    writeCharacterSaveValue(file, m_maxManaBonus);
    writeCharacterSaveValue(file, m_experienceReward);
    writeCharacterSaveValue(file, m_fameReward);
    writeCharacterSaveValue(file, m_playTime);
    writeCharacterSaveValue(file, m_bravery);
    writeCharacterSaveValue(file, m_freeStatPoints);
    writeCharacterSaveValue(file, m_freeSkillPoints);
    writeCharacterSaveValue(file, m_freePerkPoints);
    writeCharacterSaveValue(file, m_guidB8);
    writeCharacterSaveValue(file, m_guidC0);
    writeCharacterSaveValue(file, m_guidC8);
    unsigned int count = m_values.size();
    writeCharacterSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
        writeCharacterSaveValue(file, m_values[i]);
    for (unsigned int i = 0; i < 4; ++i)
    {
        writeCharacterSaveText(file, m_knownSpells[i]);
        writeCharacterSaveValue(file, m_spellLevels[i]);
    }
    for (unsigned int i = 0; i < 7; ++i)
        writeCharacterSaveValue(file, m_damageDefense[i]);
    writeCharacterSaveValue(file, m_meleeStat);
    writeCharacterSaveValue(file, m_rangedStat);
    writeCharacterSaveValue(file, m_defenseStat);
    writeCharacterSaveValue(file, m_magicStat);
    writeCharacterSaveValue(file, m_value174);
    writeCharacterSaveValue(file, m_value184);
    writeCharacterSaveValue(file, m_guid200);
    writeCharacterSaveValue(file, m_value208);
    count = m_strings.size();
    writeCharacterSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
    {
        // The prefix truncates to 16 bits, but this list writes the full length.
        unsigned int length = m_strings[i].length();
        std::fwrite(&length, 2, 1, file);
        WriteUTF32ToUTF16(file, m_strings[i], length);
    }
    count = m_pets.size();
    writeCharacterSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
        m_pets[i]->save(file);
    for (int group = 0; group < 3; ++group)
    {
        count = m_items[group].size();
        writeCharacterSaveValue(file, count);
        for (unsigned int i = 0; i < count; ++i)
        {
            CEffect* effect = m_items[group][i];
            writeCharacterSaveText(file, effect->m_sName);
            writeCharacterSaveText(file, effect->m_name88);
            writeCharacterSaveText(file, effect->m_particleName);
            writeCharacterSaveText(file, effect->m_name90);
            writeCharacterSaveValue(file, effect->m_flag31);
            writeCharacterSaveValue(file, effect->m_eType);
            writeCharacterSaveValue(file, effect->m_eDamageType);
            writeCharacterSaveValue(file, effect->m_flag33);
            writeCharacterSaveValue(file, effect->m_modifierFlag32);
            writeCharacterSaveValue(file, effect->m_flag30);
            writeCharacterSaveValue(file, effect->m_flag37);
            writeCharacterSaveValue(file, effect->m_activation);
            writeCharacterSaveValue(file, effect->m_iLevel);
            long long theme = effect->m_pUnitTheme ? effect->m_pUnitTheme->getGuid() : -1;
            writeCharacterSaveValue(file, theme);
            writeCharacterSaveValue(file, effect->m_value3C);
            writeCharacterSaveValue(file, effect->m_value40);
            writeCharacterSaveValue(file, effect->m_value44);
            int duration = static_cast<int>(effect->m_fValue24);
            writeCharacterSaveValue(file, duration);
            writeCharacterSaveValue(file, effect->m_fRemainingDuration);
            writeCharacterSaveValue(file, effect->m_value38);
            writeCharacterSaveValue(file, effect->m_fValueC0);
            for (unsigned int value = 0; value < 4; ++value)
                writeCharacterSaveValue(file, effect->m_values[value]);
        }
    }
}

#include "StringUtilities.h"

namespace {
template<class T> void readCharacterSaveValue(FILE* file, T& value)
{
    std::fread(&value, sizeof(value), 1, file);
}

void readCharacterSaveBool(FILE* file, bool& value)
{
    unsigned char byte;
    readCharacterSaveValue(file, byte);
    value = byte != 0;
}

std::wstring readCharacterSaveText(FILE* file)
{
    unsigned short length;
    readCharacterSaveValue(file, length);
    return FILESYSTEM::ReadWString(file, length);
}
}

void CCharacterSaveState::load(FILE* file, unsigned int version)
{
    readCharacterSaveBool(file, m_flag20C);
    readCharacterSaveValue(file, m_guid20);
    readCharacterSaveValue(file, m_guid28);
    readCharacterSaveValue(file, m_guid10);
    readCharacterSaveBool(file, m_flag18);
    readCharacterSaveBool(file, m_flag30);
    readCharacterSaveBool(file, m_flag31);
    readCharacterSaveBool(file, m_flag32);
    readCharacterSaveBool(file, m_flag33);
    readCharacterSaveValue(file, m_flag34);
    readCharacterSaveValue(file, m_transformationTime);
    readCharacterSaveValue(file, m_townTravelTime);
    readCharacterSaveValue(file, m_petMode);
    readCharacterSaveValue(file, m_alignment);
    readCharacterSaveValue(file, m_scale);
    m_guid50 = -1;
    if (version > 7)
        readCharacterSaveValue(file, m_guid50);
    else
    {
        int oldParent;
        readCharacterSaveValue(file, oldParent);
    }
    readCharacterSaveValue(file, m_guid58);
    readCharacterSaveValue(file, m_value60);
    m_name = readCharacterSaveText(file);
    readCharacterSaveValue(file, m_value64);
    readCharacterSaveValue(file, m_value68);
    readCharacterSaveValue(file, m_position);
    readCharacterSaveValue(file, m_orientation);
    readCharacterSaveValue(file, m_valueD0);
    readCharacterSaveValue(file, m_valueD4);
    readCharacterSaveValue(file, m_valueD8);
    readCharacterSaveValue(file, m_valueDC);
    readCharacterSaveValue(file, m_hp);
    readCharacterSaveValue(file, m_valueE4);
    if (version > 1)
        readCharacterSaveValue(file, m_valueE8);
    else
        m_valueE8 = 0;
    readCharacterSaveValue(file, m_mana);
    readCharacterSaveValue(file, m_maxManaBase);
    if (version > 1)
        readCharacterSaveValue(file, m_maxManaBonus);
    else
        m_maxManaBonus = 0;
    readCharacterSaveValue(file, m_experienceReward);
    readCharacterSaveValue(file, m_fameReward);
    readCharacterSaveValue(file, m_playTime);
    readCharacterSaveValue(file, m_bravery);
    readCharacterSaveValue(file, m_freeStatPoints);
    readCharacterSaveValue(file, m_freeSkillPoints);
    readCharacterSaveValue(file, m_freePerkPoints);
    readCharacterSaveValue(file, m_guidB8);
    readCharacterSaveValue(file, m_guidC0);
    if (version > 11)
        readCharacterSaveValue(file, m_guidC8);
    int values = 0;
    readCharacterSaveValue(file, values);
    m_values.resize(values);
    for (unsigned int i = 0; i < static_cast<unsigned int>(values); ++i)
        readCharacterSaveValue(file, m_values[i]);
    for (unsigned int i = 0; i < 4; ++i)
    {
        m_knownSpells[i] = readCharacterSaveText(file);
        readCharacterSaveValue(file, m_spellLevels[i]);
    }
    for (unsigned int i = 0; i < 7; ++i)
        readCharacterSaveValue(file, m_damageDefense[i]);
    readCharacterSaveValue(file, m_meleeStat);
    readCharacterSaveValue(file, m_rangedStat);
    readCharacterSaveValue(file, m_defenseStat);
    readCharacterSaveValue(file, m_magicStat);
    readCharacterSaveValue(file, m_value174);
    readCharacterSaveValue(file, m_value184);
    if (version > 18)
    {
        readCharacterSaveValue(file, m_guid200);
        readCharacterSaveValue(file, m_value208);
    }
    else
    {
        std::fread(&m_guid200, 4, 1, file);
        readCharacterSaveValue(file, m_value208);
        m_guid200 = -1;
        m_value208 = -1;
    }
    unsigned int count = 0;
    if (version > 8)
    {
        readCharacterSaveValue(file, count);
        for (unsigned int i = 0; i < count; ++i)
            m_strings.add(readCharacterSaveText(file));
    }
    count = 0;
    readCharacterSaveValue(file, count);
    for (unsigned int i = 0; i < count; ++i)
    {
        CItemSaveState* item = new CItemSaveState;
        m_pets.push_back(item);
        item->load(file, version);
    }
    for (int group = 0; group < 3; ++group)
    {
        int effects;
        readCharacterSaveValue(file, effects);
        for (int i = 0; i < effects; ++i)
        {
            std::wstring name = readCharacterSaveText(file);
            std::wstring secondaryName(EMPTY_WSTRING);
            if (version > 3)
                secondaryName = readCharacterSaveText(file);
            std::wstring fx = readCharacterSaveText(file);
            std::wstring graphName(EMPTY_WSTRING);
            if (version > 6)
                graphName = readCharacterSaveText(file);
            unsigned char flag31, flag33, flag32, flag30;
            int type, damageType, activation;
            unsigned int level;
            readCharacterSaveValue(file, flag31);
            readCharacterSaveValue(file, type);
            readCharacterSaveValue(file, damageType);
            readCharacterSaveValue(file, flag33);
            readCharacterSaveValue(file, flag32);
            readCharacterSaveValue(file, flag30);
            bool graphs = false;
            if (version > 6)
                readCharacterSaveBool(file, graphs);
            readCharacterSaveValue(file, activation);
            readCharacterSaveValue(file, level);
            long long theme = -1;
            if (version > 4)
                readCharacterSaveValue(file, theme);
            else
            {
                int oldTheme = -1;
                readCharacterSaveValue(file, oldTheme);
            }
            int value3C, value40, value44, duration;
            float remaining, value38;
            readCharacterSaveValue(file, value3C);
            readCharacterSaveValue(file, value40);
            readCharacterSaveValue(file, value44);
            readCharacterSaveValue(file, duration);
            readCharacterSaveValue(file, remaining);
            readCharacterSaveValue(file, value38);
            CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(type), flag30 != 0,
                static_cast<EEFFECT_ACTIVATION>(activation), static_cast<float>(duration),
                0.0f, value38, graphs);
            effect->setFX(fx);
            if (graphs)
                effect->setGraphs(graphName);
            float baseValue;
            readCharacterSaveValue(file, baseValue);
            for (unsigned int value = 0; value < 4; ++value)
            {
                readCharacterSaveValue(file, effect->m_values[value]);
                effect->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            }
            if (theme != -1)
                effect->m_pUnitTheme = CUnitThemes::getSingleton()->getTheme(theme);
            effect->m_eDamageType = static_cast<EDAMAGE_TYPES>(damageType);
            effect->m_fRemainingDuration = remaining;
            // The native loader copies the first word to both fields.
            effect->m_value3C = value3C;
            effect->m_value40 = value3C;
            effect->m_value44 = value44;
            effect->m_iLevel = level >= 1001 ? 0 : level;
            effect->calculateBaseValue(static_cast<CEffect::ECALCULATETYPES>(0));
            effect->m_modifierFlag32 = flag32 != 0;
            effect->m_flag33 = flag33 != 0;
            effect->m_flag31 = flag31 != 0;
            effect->m_sName = STRINGS::StringUpper(name);
            effect->m_name88 = STRINGS::StringUpper(name);
            effect->m_fValueC0 = baseValue;
            m_items[group].push_back(effect);
        }
    }
}
