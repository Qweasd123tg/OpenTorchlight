#ifndef GENERICMODEL_H
#define GENERICMODEL_H
#include "PositionableObject.h"
#include "iRandomWeight.h"
#include "iHighlight.h"
#include <vector>
#include <string>
class CKeyframe;
// Partial: size and all vtable groups preserved; expose only Item collaborators.
class CGenericModel : public CPositionableObject, public iRandomWeight, public iHighlight
{
public:
    virtual ~CGenericModel();
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int weight);
    virtual void setHighlighted(bool highlighted);
    void setCastsShadows(bool shadows);
    void setOpacity(float opacity);
    void setLightOverride(float value);
    void setRimLighting(std::wstring texture);
    void setTextureOverride(const std::wstring& texture);
    void updateAnimation(float elapsed, bool force);
    const std::vector<CKeyframe*>& getAnimationEvents() const { return m_AnimationEvents; }
private:
    unsigned char m_ModelData110[0x1b0-0x110];
    std::vector<CKeyframe*> m_AnimationEvents;
    unsigned char m_ModelData1C8[0x250-0x1c8];
};
#endif
