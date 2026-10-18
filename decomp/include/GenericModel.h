#ifndef GENERICMODEL_H
#define GENERICMODEL_H
#include "PositionableObject.h"
#include "OgreUtilityEnums.h"
#include "iRandomWeight.h"
#include "iHighlight.h"
#include <vector>
#include <deque>
#include "TArrayList.h"
#include <OgreTexture.h>
#include "ActiveAnimation.h"
#include "RenderableStates.h"
class CAnimationSet;
class CActiveAnimation;
namespace Ogre { class Material; class ColourValue; class Frustum; class AnimationState; }
#include <string>
class CDataGroup;
class CKeyframe;
class CAnimationSet;
namespace Ogre {class SkeletonInstance;}
// Partial: size and all vtable groups preserved; expose only Item collaborators.
class CGenericModel : public CPositionableObject, public iRandomWeight, public iHighlight
{
    friend class CLevel;
friend class CEquipment;
friend class CCharacter;
friend class CMonster;
friend void EditorSetActiveAnimationPaused(long long, bool);
friend class CStatsMenu;
friend class CPetMenu;
friend class CInventoryMenu;
friend class CSkillMenu;
friend class CJournalMenu;
public:
    std::string getTexureName();
    void releaseUniqueMaterials();
    void addValueIndex(int animation, CKeyframe* key, int value);
    void clearProjectorPass();
    void setRenderToLightMap(bool enabled);
    void unloadModel();
    void loadPrefabType(OGRE_UTILITIES::EPRIMITIVES primitive);
    void AddKey(unsigned int animation, CDataGroup* group);
    long getAnimationLength(const std::string& name) const;
    void setTextureOverride(Ogre::TexturePtr texture, std::string include, std::string exclude);
    void setTextureOverrideSingle(std::string name, Ogre::TexturePtr texture);
    void setProjectorPass(Ogre::Frustum*, Ogre::Frustum*, const std::string&, const std::string&);
    bool animationExistsSubstring(const std::string&) const;
    bool animationQueuedSubstring(const std::string&) const;
    void clearQueuedAnimations();
    bool loopingAnimationPlaying();
    void setAnimationSpeed(const std::string&, float speed);
    int currentAnimation() const;
    void setHighlightTexture(const std::wstring&);
    void setRenderBehindTexture(const std::wstring&);
    void loadAnimations(Ogre::Entity*, std::wstring path, std::wstring group, bool flag);
    void reInitialize(Ogre::Entity*, bool flag);
    int findRandomAnimation(const std::string& name);
    int findKey(int animation, CKeyframe* key);
    TArrayList<int>* getValueIndexes(int animation, CKeyframe* key);
    unsigned int getAnimationCount() const;
    const std::string& getAnimationName(unsigned int animation) const;
    unsigned int getKeyCount(unsigned int animation);
    CKeyframe* getKeyFrame(unsigned int animation, unsigned int key);
    const std::string& getName();
    int getAnimationLength(int animation) const;
    unsigned long activeAnimations() const;
    void setAmbient(Ogre::ColourValue& colour);
    unsigned int getAnimationIndex(const std::string&) const;
    float getAnimationLengthSeconds(int) const;
    bool animationQueued(unsigned int) const;
    bool animationPlaying(unsigned int) const;
    void queueBlendAnimation(unsigned int,bool,float,float);

    bool animationPlaying() const;

    void setAnimationTime(float time);

    CGenericModel(CResourceManager* resources, Ogre::SceneManager* manager, OGRE_UTILITIES::EPRIMITIVES primitive);
    CGenericModel(CResourceManager* resources, Ogre::SceneManager* manager,
                  std::wstring modelPath, std::wstring resourceGroup, bool flag);
    void setQueryMask(OGRE_UTILITIES::EQUERYMASK mask);
    void setWireframe(bool wireframe);

    void loadModel(std::wstring modelPath, std::wstring resourceGroup, bool flag0, bool flag1, bool flag2);

    void reloadAnimations();

    void clearAnimations();
    void playAnimation(unsigned int animation, bool loop, float speed, float length);
    void blendAnimation(unsigned int animation, bool loop, float blend, float speed, float length);
    bool animationPlayingSubstring(const std::string& animation) const;

    float getAnimationTime();


    bool animationExists(const std::string&) const;
    const std::string& getAnimationNameByPath(const std::wstring&) const;
    float getAnimationLengthSeconds(const std::string&) const;

    void generateExtremes(unsigned long,bool);
    virtual ~CGenericModel();
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int weight);
    virtual void setHighlighted(bool highlighted);
    void setRenderBehind(bool behind);
    void setCastsShadows(bool shadows);
    void setOpacity(float opacity);
    void setLightOverride(float value);
    void setRimLighting(std::wstring texture);
    void setTextureOverride(const std::wstring& texture);
    void setTextureOverrideSingle(const std::string& name,const std::wstring& texture);
    void updateAnimation(float elapsed, bool force);
    void blendAnimation(const std::string&, bool, float, float, float);
    void playAnimation(const std::string&, bool, float, float);
    void queueBlendAnimation(const std::string&, bool, float, float);
    bool animationPlaying(const std::string&) const;
    bool animationQueued(const std::string&) const;
    const std::vector<CKeyframe*>& getAnimationEvents() const { return m_AnimationEvents; }
private:
    friend class CMonsterDescriptor;
    friend class CGenericModelDescriptor;
    std::wstring m_sModelPath; // +0x110, copied by Equipment::reskinByClass
    std::wstring m_modelGroup; // +0x118
    std::string m_name;
    std::string m_string128; // +0x128
    Ogre::SkeletonInstance* m_pSkeleton;
    unsigned char m_gap138[8];
    Ogre::SceneManager* m_modelSceneManager; // +0x140
    TArrayList<Ogre::AnimationState*> m_animationStates; // +0x148
    std::deque<CActiveAnimation*> m_activeAnimations;
    std::vector<CKeyframe*> m_AnimationEvents;
    std::vector<std::vector<TArrayList<int> > > m_valueIndexes;
    CAnimationSet* m_animationSet;
    bool m_animationPaused;
    bool m_flag1e9;
    unsigned char m_gap1ea[0x204-0x1ea];
    OGRE_UTILITIES::EQUERYMASK m_queryMask; // +0x204
    std::vector<CRenderableStates> m_renderableStates;
    unsigned int m_randomWeight; // +0x220
    bool m_uniqueMaterials; // +0x224
    unsigned char m_gap225[3];
    float m_opacity; // +0x228
    unsigned char m_gap22c[4];
    Ogre::Entity* m_entity230;
    bool m_flag238;
    bool m_renderToLightMap; // +0x239
    bool m_renderFlag23A;
    unsigned char m_gap23B;
    bool m_animationLoop;
    unsigned char m_ModelData23D[3];
    float m_animationSpeed;
    unsigned int m_animationPlaying;
    unsigned char m_ModelData248[4];
    float m_animationStep; // +0x24c
};
#endif
