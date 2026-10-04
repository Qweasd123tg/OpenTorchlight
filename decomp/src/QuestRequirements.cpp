#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestRequirements.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "StringUtilities.h"
#include "TArrayList.h"

long long CQuestRequirements::parseRequirementTag(CDataGroup* dataGroup)
{
    m_pDataGroup = dataGroup;
    if (dataGroup != NULL)
    {
        m_iUnknown20 = m_pDataGroup->GetDataValue(L"MINPLAYERLEVEL", -1);
        m_iUnknown24 = m_pDataGroup->GetDataValue(L"MAXPLAYERLEVEL", -1);
        m_iUnknown28 = m_pDataGroup->GetDataValue(L"MINDUNGEONDEPTH", -1);
        m_iUnknown2C = m_pDataGroup->GetDataValue(L"MAXDUNGEONDEPTH", -1);

        reinterpret_cast<std::wstring&>(m_pUnknown30).assign(
            STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"RULESET", EMPTY_WSTRING))
        );

        TArrayList<std::wstring>& requirements =
            reinterpret_cast<TArrayList<std::wstring>&>(m_Unknown38);
        const std::wstring* requirementNames =
            reinterpret_cast<const std::wstring*>(gQUEST_REQUIREMENTS);

        for (int i = 0; i < 3; ++i)
        {
            CDataGroup* group = dataGroup->GetDataGroupByName(requirementNames[i], false);
            if (group != NULL)
            {
                for (unsigned int j = 0; j < group->GetNumberOfDataValues(); ++j)
                {
                    CDataValue::EDATAVALUETYPES type = group->GetDataValue(j)->GetValueType();
                    if (type == CDataValue::DATAVALUE_TRANSLATE || type == CDataValue::DATAVALUE_STRING)
                        requirements.add(STRINGS::StringUpper(group->GetDataValue(j)->GetValueAsString()));
                }
            }
        }
    }

    return 1;
}
