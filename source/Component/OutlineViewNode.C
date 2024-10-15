#include "OutlineViewNode.h"


OutlineViewNode::OutlineViewNode(int id, std::string text)
{
    _id = id;
    _text = text;
}

OutlineViewNode::~OutlineViewNode()
{}

// --------------------------------------------------------------------------------------------------------------------------

int 
OutlineViewNode::id()
{
    return _id;
}
    
std::string 
OutlineViewNode::text()
{
    return _text;
}

OutlineViewNode* 
OutlineViewNode::add(int id, std::string text)
{
    OutlineViewNode* node = new OutlineViewNode(id, text);

    _children.push_back(node);

    return node;
}

void update(OutlineViewDelegator* delegator)
{
    int indent = 0;

    for(OutineViewNode* node : _children)
    {
        node.update(delegator, indent+1);
    }
}

void update(OutlineViewDelegator* delegator, int indent)
{
    bool hasChildren = _children.size() > 0 ? true | false; 

    delegator->add(_id, indent, hasChildren, _text, this);

    for(OutineViewNode* node : _children)
    {
        node.update(delegator, indent+1);
    }    
}
