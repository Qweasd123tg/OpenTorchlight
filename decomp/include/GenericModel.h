#ifndef GENERICMODEL_H
#define GENERICMODEL_H
#include "PositionableObject.h"
#include "iRandomWeight.h"
#include "iHighlight.h"
#include <vector>
#include <string>
class CKeyframe;
namespace Ogre {class SkeletonInstance;}
// Partial: size and all vtable groups preserved; expose only Item collaborators.
class CGenericModel : public CPositionableObject, public iRandomWeight, public iHighlight
{
friend class CEquipment;
friend class CStatsMenu;
friend class CPetMenu;
friend class CInventoryMenu;
friend class CSkillMenu;
public:
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
    std::wstring m_sModelPath; // +0x110, copied by Equipment::reskinByClass
    unsigned char m_ModelData118[0x130-0x118];
    Ogre::SkeletonInstance* m_pSkeleton;
    unsigned char m_ModelData138[0x1b0-0x138];
    std::vector<CKeyframe*> m_AnimationEvents;
    unsigned char m_ModelData1C8[0x250-0x1c8];
};
#endif
