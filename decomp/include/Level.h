#ifndef LEVEL_H
#define LEVEL_H

#include <OgreVector3.h>

#include "RunicCore.h"
#include "Constants.h"
#include "TArrayList.h"
#include "TLinkedList.h"
#include "UnitTypes.h"

class CCharacter;

// Partial: members used by recovered TUs; unnamed regions are padding until
// level.cpp is recovered.
class CLevel : public CRunicCore
{
public:
    CCharacter* getCharacterByGuid(long long guid);
    void getActiveCharactersAtPosition(const Ogre::Vector3& position, UNITTYPES::EUNITTYPES unitType,
                                       EAlignment alignment, float radius, bool includeLiving, bool includeDead,
                                       TArrayList<CCharacter*>& characters);

    TLinkedList<CCharacter*>* getCharacters() { return m_pCharacters; }

private:
    char m_LevelData[0x98 - 0x10];
    TLinkedList<CCharacter*>* m_pCharacters;
};

#endif
