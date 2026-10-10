#ifndef CINEMATIC_H
#define CINEMATIC_H

#include <string>

class CDataGroup;

// Shared declaration of the existing CCinematic definition in Cinematics.cpp.
class CCinematic
{
public:
    std::wstring m_sName;
    std::wstring m_sText;
    std::wstring m_sImage;
    std::wstring m_sSound;

    void load(CDataGroup* data);
};

#endif
