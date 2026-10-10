#ifndef EDITOR_H
#define EDITOR_H

#include <list>
#include <map>
#include <string>

#include <OgreTimer.h>
#include <OgreVector3.h>

#include "RunicCore.h"
#include "EditorDefines.h"
#include "TArrayList.h"

class CEditorObjectManager;
class CEditorScene;
class CResourceManager;
class CSettings;
namespace Ogre { class Camera; }
class CUndo;
class CPOV;
class CGameClient;
class iEditorResourceManager;

// Partial: layout from CEditor::CEditor (504 bytes). Members of Editor.cpp are
// declared as recovered TUs need them; unnamed members are not identified yet.
class CEditor : public CRunicCore
{
public:
    TArrayList<CEditorScene*>& getEditorScenes() { return m_EditorScenes; }

    CResourceManager* getResourceManager() { return m_pUnknown128; }

    void addUndo(CUndo* undo, bool clearRedo);
    void addRedo(CUndo* redo);
    CEditorScene* GetEditorScene(std::wstring name);
    Ogre::Timer* getTimer() { return &m_Timer; }

    Ogre::Camera* getCamera();
    void setAmbientColor(int red,int green,int blue);
    void setMaterialAmbientColor(int red,int green,int blue);
    void setDirectionalColor(int red,int green,int blue);
    void setDirectionalIntensity(float intensity);
    CSettings* getSettings() { return m_pSettings; }

    CGameClient* getGameClient();
    void setCompletedQuests(const std::wstring& quests);
    void setActiveQuests(const std::wstring& quests);

    bool isDisabled() const { return m_bDisabled; }
    iEditorResourceManager* getEditorResourceManager() const { return m_pEditorResourceManager; }

    void setFlag(EEDITOR_FLAGS flag);
    void removeFlag(EEDITOR_FLAGS flag);
    void SetBackgroundColor(float red, float green, float blue);
    void flushKeyManager();
    unsigned int GetEditorSceneIDByName(const wchar_t* name);

    void SetMouseWheelDelta(int delta);
    void SetPovVelocityMult(float multiplier);
    void SetRenderWindowHasFocus(bool focused);
    CEditorScene* GetEditorScene(unsigned int index);
    unsigned int getUndoSize();
    void doUndo();
    unsigned int getRedoSize();
    void doRedo();
    void deleteAllUndos();
    void FlyToPositionLookingAtPos(Ogre::Vector3 position, Ogre::Vector3 target);
    void keyEvent(unsigned int event, unsigned int code);
    void mouseEvent(unsigned int event, unsigned int code);
    void ResetCamera(Ogre::Vector3 position);

    friend void EditorSetMonsterAutoSpawn(wchar_t*);
    CEditor();
    static CEditor* getSingleton();
    virtual ~CEditor();

    // Guard of the editor API: the editor is initialized and not disabled.
    bool isActive() const { return !m_bDisabled && m_pEditorResourceManager != NULL; }

    CEditorObjectManager* getObjectManager() { return m_pObjectManager; }
    int getFlags() const { return m_iFlags; }

    int getLevelDepth() const { return m_iLevelDepth; }
    void setLevelDepth(int depth) { m_iLevelDepth = depth; }
    void setCharacterLevel(int level) { m_iCharacterLevel = level; }
    void setRunGodded(bool godded) { m_bRunGodded = godded; }
    void setAiFreeze(bool freeze) { m_bAiFreeze = freeze; }
    void setLevelPopulate(bool populate) { m_bLevelPopulate = populate; }
    void setLevelPopulateChampions(bool populate) { m_bLevelPopulateChampions = populate; }
    void setLevelCreatePet(bool create) { m_bLevelCreatePet = create; }
    void setUseTempStartPos(bool use) { m_bUseTempStartPos = use; }
    void setTempStartPos(float x, float y, float z)
    {
        m_vTempStartPos.x = x;
        m_vTempStartPos.y = y;
        m_vTempStartPos.z = z;
    }

private:
    friend void EditorSetMonsterAutoSpawn(wchar_t* name);
    friend void EditorSetEditorMonsterSpawnclass(wchar_t* name);
    friend void EditorSetEditorPlayerFile(wchar_t* name);
    friend void EditorSetCommandAutoRun(wchar_t* name);
    friend bool EditorGetMuted();
    friend void EditorSetMuted(bool muted);
    char m_Unknown10[0x38];
    bool m_bRenderWindowHasFocus;
    // Checked by the editor API, never set in the shipped build.
    bool m_bDisabled;
    bool m_bUnknown4A;
    bool m_bUnknown4B;
    CSettings* m_pSettings;
    iEditorResourceManager* m_pEditorResourceManager;
    float m_fUnknown60;
    int m_iFlags;
    int m_iUnknown68;
    CPOV* m_pCameraController;
    int m_iUnknown78[3];
    Ogre::Camera* m_pUnknown88;
    void* m_pUnknown90;
    int m_iUnknown98[6];
    void* m_pUnknownB0;
    int m_iMouseWheelDelta;
    TArrayList<CEditorScene*> m_EditorScenes;
    std::map<std::wstring, unsigned int> m_EditorSceneIDs;
    Ogre::Timer m_Timer;
    CEditorObjectManager* m_pObjectManager;
    CResourceManager* m_pUnknown128;
    void* m_pUnknown130;
    void* m_pUnknown138;
    std::list<CUndo*> m_Undos;
    std::list<CUndo*> m_Redos;
    unsigned int m_iMaxUndos;
    bool m_bUnknown164;
    void* m_pUnknown168;
    int m_iCharacterLevel;
    int m_iLevelDepth;
    bool m_bLevelPopulate;
    std::wstring m_sUnknown180;
    bool m_bLevelPopulateChampions;
    bool m_bLevelCreatePet;
    bool m_bRunGodded;
    bool m_bAiFreeze;
    std::wstring m_sUnknown190;
    std::wstring m_sUnknown198;
    std::wstring m_sUnknown1A0;
    std::wstring m_sUnknown1A8;
    bool m_bUseTempStartPos;
    Ogre::Vector3 m_vTempStartPos;

public:
    // Read and written as a pair by EditorParticleMovementConfig (defaults 5 and 10).
    float m_fParticleMovementA;
    float m_fParticleMovementB;

private:
    TArrayList<std::wstring> m_ActiveQuests;
    TArrayList<std::wstring> m_CompletedQuests;
};

extern CEditor* gEditor;

#endif
