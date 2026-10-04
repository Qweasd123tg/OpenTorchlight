#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>

#include "GameEnums.h"
#include "RunicCore.h"
#include "iStatListener.h"

class CAchievement : public CRunicCore, public iStatListener
{
public:
    virtual ~CAchievement();

    virtual void statChanged(unsigned int statType,
                             UNIONDATA32BIT oldValue,
                             UNIONDATA32BIT newValue);

    ESTATS getStatType();
    void checkForAchieved();
    void setValue(float value);
    void setValue(int value);
    void cheat();
    void forceComplete();
    void addValue(float value);
    void addValue(int value);
    void increment();

    CAchievement(std::string name, ESTATS statType,
                 float currentValue, float requiredValue);
    CAchievement(std::string name, ESTATS statType,
                 int currentValue, int requiredValue);

    std::wstring getStatCompleteString();

    std::string m_strName;
    bool m_bAchieved;
    ESTATS m_eStatType;
    float m_fCurrentValue;
    float m_fRequiredValue;
};

#endif
