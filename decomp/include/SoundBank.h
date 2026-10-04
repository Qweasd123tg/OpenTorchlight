#ifndef SOUNDBANK_H
#define SOUNDBANK_H
#include "RunicCore.h"
// Partial: complete size/vtable; only destruction is used by Item here.
class CSoundBank : public CRunicCore
{
public:
    virtual ~CSoundBank();
private:
    unsigned char m_SoundBankData[0xd0-0x10];
};
#endif
