#include "OutlineNode.h"



OutlineNode::OutlineNode(int level, std::string name, std::string label)
{
	_level = level;
	_label = label;
	_name = name;
    _hasChildren = false;

	if (_level == 0)
		_visible = true;
}

OutlineNode::OutlineNode(int level, std::string name)
	: OutlineNode(level, name, name)
{}

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

std::string 
OutlineNode::label()
{
	return _label;
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
OutlineNode::isExpanded()
{
	return _expanded;
}

void 
OutlineNode::setExtended(bool isExpanded = true)
{
	_expanded = isExpanded;
}

std::string
OutlineNode::name()
{
	return _name;
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

void
OutlineNode::printOut()
{
    std::cout << "label: " << _label << " level: " << _level << " visible: " << _visible << " expanded: " << _expaned << " hasChildren: " << _hasChildren << std::endl;
}