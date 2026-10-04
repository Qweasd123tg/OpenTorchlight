#ifndef ISELECTED_H
#define ISELECTED_H

// Interface of editor objects told when the editor selects or deselects them.
class iSelected
{
public:
    virtual ~iSelected() {}
    virtual void editorSelectionChanged(bool selected) = 0;
};

#endif
