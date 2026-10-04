#ifndef LEVELTEMPLATEDATA_H
#define LEVELTEMPLATEDATA_H
#include "RunicCore.h"
// Partial: 0x778 bytes, UNIT_LIGHT_FADE is named from load()'s data key.
class CLevelTemplateData : public CRunicCore
{
public:
    virtual ~CLevelTemplateData();
    bool getUnitLightFade() const { return m_bUnitLightFade; }
private:
    unsigned char m_TemplateData10[0x763-0x10];
    bool m_bUnitLightFade;
    unsigned char m_TemplateData764[0x778-0x764];
};
#endif
