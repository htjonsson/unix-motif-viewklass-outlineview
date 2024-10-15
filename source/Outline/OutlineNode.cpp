#include "OutlineNode.h"

OutlineNode::OutlineNode(int level, std::string label);
	: OutlineNode(level, label, label)
{}

OutlineNode::OutlineNode(int level, std::string label, std::string text)
{
	_level = level;
	_label = label;
	_text = text;
    _hasChildren = false;

	if (_level == 0)
		isVisible = true;
}

OutlineNode::~OutlineNode()
{}

// --------------------------------------------------------

bool 
OutlineNode::isVisible()
{
	return _visible;
}
	
void 
OutlineNode::setVisible(bool isVisible)
{
	_visible = isVisible;
}

int 
OutlineNode::level()
{
	return _level;
}

void 
OutlineNode::setLevel(int level)
{
	_level = level;
}	

bool 
OutlineNode::isExtended()
{
	return _expanded;
}

void 
OutlineNode::setExtended(bool isExtended = true)
{
	_expanded = isExtended;
}

std::string
OutlineNode::label()
{
	return _label;
}

std::string
OutlineNode::name()
{
	return _name;
}

OutlineNode* 
OutlineNode::parent()
{
	return _parent;
}

void 
OutlineNode::setParent(OutlineNode* newParent)
{
	_parent = newParent;
}

XtPointer 
OutlineNode::clientData()
{
	return _clientData;
}

void 
OutlineNode::setClientData(XtPointer clientData)
{
	_clientData = clientData;
}

bool 
OutlineNode::hasChildren()
{
    return _hasChildren;
}

void
OutlineNode::setHasChildren(bool hasChildren)
{
    _hasChildren = hasChildren;
}