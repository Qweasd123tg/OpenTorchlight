#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "RunicCore.h"
#include "TArrayList.h"

// Enumerator names are ours. A decaying randomizer scales the odds of every
// picked choice by m_fDecay, so repeated picks become less likely.
enum ERANDOMIZER_TYPE
{
    RANDOMIZER_NORMAL,
    RANDOMIZER_DECAY
};

// Weighted random choice between integer values.
class CRandomizer : public CRunicCore
{
public:
    CRandomizer(ERANDOMIZER_TYPE type);
    virtual ~CRandomizer() {}

    int getOdds(int index);
    void setChoiceOdds(int choice, int odds);
    void removeChoice(unsigned int choice);
    void setRandomSeed(unsigned int seed);
    void clear();
    int addChoice(int choice, int odds);
    void computeOdds();
    void setRandomizerToNormal(float odds);
    int getRandom(int& index);
    int getRandom();
    bool hasValidChoices();

    bool hasChoices() const { return m_Odds.size() != 0; }

private:
    TArrayList<int> m_Choices;
    TArrayList<float> m_Odds;
    TArrayList<float> m_ComputedOdds;
    ERANDOMIZER_TYPE m_eType;
    float m_fDecay;
    bool m_bOddsDirty;
};

#endif
