#ifndef OTL_SETTINGSMENUDATA_H
#define OTL_SETTINGSMENUDATA_H
#include <string>
static bool LastMusicMute = false;
static bool LastSoundMute = false;
static float LastMusicVolume = 1.0f;
static float LastSoundVolume = 1.0f;
static const std::wstring KShadowSettingNames[6] = {L"Off", L"Lighting Only", L"Low", L"Medium", L"High", L"Very High"};
static const std::wstring KParticleSettingNames[3] = {L"Low", L"Medium", L"High"};
#endif
