#ifndef TIMERSTATICS_H
#define TIMERSTATICS_H

#include <map>
#include <string>
#include <utility>
#include <OgreTimer.h>

#include "RunicCore.h"
#include "TArrayList.h"

// Inline construction in CLevel::loadRoomLayout and the original destructor
// establish the owning members and the 0x80-byte extent.
class CTimerStatics : public CRunicCore
{
public:
    virtual ~CTimerStatics();
    void popTime(const wchar_t* name);
    std::wstring getStatics(bool);

    std::map<std::wstring, std::pair<unsigned int, unsigned int> > m_statistics; // 0x10
    Ogre::Timer m_timer;                                                   // 0x40
    unsigned int m_startMicroseconds;                                      // 0x58
    TArrayList<unsigned int> m_times;                                      // 0x60
    std::wstring m_name;                                                   // 0x78
};

#endif
