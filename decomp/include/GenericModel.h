#ifndef GENERICMODEL_H
#define GENERICMODEL_H
#include "PositionableObject.h"
#include "iRandomWeight.h"
#include "iHighlight.h"
#include <vector>
#include <deque>
#include "TArrayList.h"
class CAnimationSet;
class CActiveAnimation;
namespace Ogre { class Material; class ColourValue; }
struct CRenderableStates { char prefix[3]; bool highlighted; bool renderBehind; char gap5[11]; Ogre::Material* material; char tail[40]; };
#include <string>
class CKeyframe;
namespace Ogre {class SkeletonInstance;}
// Partial: size and all vtable groups preserved; expose only Item collaborators.
class CGenericModel : public CPositionableObject, public iRandomWeight, public iHighlight
{
friend class CEquipment;
friend class CCharacter;
friend class CStatsMenu;
friend class CPetMenu;
friend class CInventoryMenu;
friend class CSkillMenu;
friend class CJournalMenu;
public:
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
    bool animationExists(const std::string&) const;
    bool animationPlaying(const std::string&) const;
    bool animationQueued(const std::string&) const;
    const std::vector<CKeyframe*>& getAnimationEvents() const { return m_AnimationEvents; }
private:
    std::wstring m_sModelPath; // +0x110, copied by Equipment::reskinByClass
    unsigned char m_ModelData118[8];
    std::string m_name;
    unsigned char m_ModelData128[8];
    Ogre::SkeletonInstance* m_pSkeleton;
    unsigned char m_ModelData138[0x160-0x138];
    std::deque<CActiveAnimation*> m_activeAnimations;
    std::vector<CKeyframe*> m_AnimationEvents;
    std::vector<std::vector<TArrayList<int> > > m_valueIndexes;
    CAnimationSet* m_animationSet;
    unsigned char m_gap1e8[0x208-0x1e8];
    std::vector<CRenderableStates> m_renderableStates;
    unsigned char m_gap220[0x23c-0x220];
    bool m_animationLoop;
    unsigned char m_ModelData23D[3];
    float m_animationSpeed;
    unsigned int m_animationPlaying;
    unsigned char m_ModelData248[8];
};
#endif
