#include "OutlineViewRenderNode.h"

#include <iostream>

OutlineViewRenderNode::OutlineViewRenderNode(int id, int indent, bool isToggle, std::string text)
{
    _id = id;
    _indent = indent;
    _toggle = isToggle == true ? 1 : 0;
    _text = text;
}

OutlineViewRenderNode::~OutlineViewRenderNode()
{}


std::string 
OutlineViewRenderNode::text()
{
    return _text;
}

bool
OutlineViewRenderNode::isToggle()
{
    return _toggle == 0 ? false : true;
}

int
OutlineViewRenderNode::indent()
{
    return _indent;
}

bool 
OutlineViewRenderNode::isExpended()
{
    if (_toggle == 1)
    {
        return true;
    }
    return false;
}

void 
OutlineViewRenderNode::setExpended()
{
    _toggle = 1;
}

bool 
OutlineViewRenderNode::isCollapsed()
{
    if (_toggle == 2)
    {
        return true;
    }
    return false;
}

void 
OutlineViewRenderNode::setCollapsed()
{
    _toggle = 2;
}

void
OutlineViewRenderNode::printOut()
{
    std::cout << "_toggle " << _toggle << std::endl;
}

