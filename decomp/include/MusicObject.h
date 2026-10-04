#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "EditorBaseObject.h"
#include "ResourceManager.h"
class CSoundManager;

class CMusicObject : public CEditorBaseObject
{
public:
    virtual ~CMusicObject();
    void playAndFadeIn(float);
    void fadeOutAndStop(float);
    void reset();
    void stop();
    CMusicObject(CResourceManager*);
    unsigned long getIsPlaying();
    void playNormalLevelMusic();
    void updateMusic(float);
    void setMusicFile(std::wstring);
    void play();

    // fields
    CSoundManager* m_pSoundManager;
    std::wstring m_sMusicFile;
    std::wstring m_sUnknown68;
    bool m_bUnknown70;
    bool m_bUnknown71;
    bool m_bLoops;
    unsigned char m_gap73[0x1];
    float m_fUnknown74;
    bool m_bUnknown78;
    unsigned char m_gap79[0x3];
    float m_fUnknown7C;
    CResourceManager* m_pResourceManager;
};

#endif
