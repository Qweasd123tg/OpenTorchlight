#ifndef IHIGHLIGHT_H
#define IHIGHLIGHT_H
class iHighlight
{
public:
    virtual ~iHighlight();
    virtual void setHighlighted(bool highlighted) = 0;
};
#endif
