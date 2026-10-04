#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>

#include "AllDescriptorsScene.h"
#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "TArrayList.h"
#include "iHighlight.h"
#include "iRandomWeight.h"

class CParticle;
class CTimerStatics;

class CLayout : public CAllDescriptorsScene, public iRandomWeight, public iHighlight
{
public:
    enum ELAYOUT_FUNCTION_TYPES
    {
        LAYOUT_FUNCTION_START = 0,
        LAYOUT_FUNCTION_STOP = 1,
        LAYOUT_FUNCTION_PAUSE = 2,
        LAYOUT_FUNCTION_RESUME = 3,
        LAYOUT_FUNCTION_START_BACKWARDS = 4
    };

    virtual ~CLayout();

    virtual void SetSceneOwner(CEditorScene* sceneOwner);
    virtual void setVisible(bool visible);
    virtual void update(float elapsedTime);
    virtual void eventFiredByDescriptor(unsigned int eventID,
                                        CDescriptor* descriptor,
                                        CEditorBaseObject* eventObject);
    virtual unsigned int getNumberOfParticlesUpdating();
    virtual void editorObjectCreated(CEditorBaseObject* editorObject);
    virtual void editorObjectsAboutToBeDelete();
    virtual void editorObjectLoaded(CEditorBaseObject* editorObject);
    virtual void setHighlighted(bool highlighted);

    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int randomWeight);

    static void setCacheingParticlesForLevel(bool enable);
    static CLayout* getLayoutToClone(const std::wstring& layoutName);

    void processInputs(unsigned int inputID, CEditorBaseObject* inputObject);
    void setDurationModification(float durationModification);

    CLayout(CResourceManager* resourceManager, ELAYOUT_TYPES layoutType);

    void callFunctionOnObjects(ELAYOUT_FUNCTION_TYPES functionType,
                               bool stopImmediately);
    void resume();
    void pause();
    void stop(bool stopImmediately);
    void startBackwards();
    void start();

    void setStartOnLoad(bool startOnLoad);
    void addLayoutForCloningAndControlling(std::wstring layoutName);
    void removeAllCloneableObjects();
    void initOnLoad();

    void loadLayoutFile(const std::wstring& fileName,
                        bool loadObjects,
                        CTimerStatics* timer,
                        bool forceLoad,
                        bool ignoreSameFile,
                        unsigned int seed);

    bool m_bStartOnLoad;
    unsigned char m_gap1A1[3];
    unsigned int m_iRandomWeight;
    int m_iUnknown1A8;
    int m_iUnknown1AC;
    int m_iUnknown1B0;
    float m_fDurationModification;
    ELAYOUT_TYPES m_Unknown1B8;
    unsigned char m_gap1BC[4];
    long long m_iUnknown1C0;
    bool m_bUnknown1C8;
    bool m_bUnknown1C9;
    unsigned char m_gap1CA[6];
    TArrayList<CEditorBaseObject*> m_Unknown1D0;
    bool m_bUnknown1E8;
    unsigned char m_gap1E9[7];
    CParticle* m_pParticle;
};

#endif
