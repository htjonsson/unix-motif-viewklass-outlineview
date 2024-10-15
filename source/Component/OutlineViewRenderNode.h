#ifndef OUTLINE_VIEW_RENDER_NODE_H
#define OUTLINE_VIEW_RENDER_NODE_H

#include <string>

class OutlineViewRenderNode
{
public:
    int             _id;
    int             _indent = 0;
    std::string     _text;
    int             _toggle = 0; 
    /*
        _toggle == 0 => NONE
        _toggle == 1 => EXPANDED
        _toggle == 2 => COLLAPSED
    */

public:
    OutlineViewRenderNode(int id, int indent, bool isToggle, std::string text);
    ~OutlineViewRenderNode();

public:
    std::string text();
    bool isToggle();
    int indent();

public:
    bool isExpended();
    void setExpended();
    bool isCollapsed();
    void setCollapsed();

public:
    void printOut();
};

#endif // OUTLINE_VIEW_RENDER_NODE_H