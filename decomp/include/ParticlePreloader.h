#ifndef PARTICLEPRELOADER_H
#define PARTICLEPRELOADER_H
#include "RunicCore.h"
#include <string>
// Partial pointer interface: original CRunicCore base and observed size 0xc8.
class CParticlePreloader : public CRunicCore
{
public:
    virtual ~CParticlePreloader();
    void LoadParticle(std::wstring path);
private:
    unsigned char m_Unrecovered10[0xc8-0x10];
};
#endif
