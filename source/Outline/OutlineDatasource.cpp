#include "OutlineDatasource.h"

void
OutlineDatasource::add(OutlineNode* child)
{
	parent->setHasChildren(false);
    _nodes.push_back(child);    
}

void
OutlineDatasource::update()
{
    // Check if node has a child and then assign it, if not already set
    for(int i = 1; i < _nodes.size(); i++)
    {
		OutlineNode* current = _nodes.at(i-1);
		OutlineNode* next = _nodes.at(i);

        if (current->level() < next->level())
            current->setHasChildren(true);
        else
            current->setHasChildren(false);
    }
    
	for(int i = 0; i < _nodes.size(); i++)
		setVisibilityBy(_nodes.at(i));
}

void 
OutlineDatasource::setVisibilityBy(OutlineNode* parent)
{
	std::vector<OutlineNode*> children;

	if (childrenOf(parent, &children) != -1)
	{
		bool isVisible = false;
		if (parent->isExpanded() && parent->isVisible())
			isVisible = true;
			
		for(OutlineNode* node : children)
			node->setVisible(isVisible);
	}
}

int
OutlineDatasource::childrenOf(OutlineNode* parent, std::vector<OutlineNode*>* result)
{
	int index = indexOf(parent);

	if (parent->hasChildren() == false)
		return -1;

	for(int i = index+1; i < _nodes.size(); i++)
	{
		OutlineNode* current = _nodes.at(i);

		if (parent->level() == current->level() + 1)
			result->push_back(current);
		else
			break;
	}

	return result->size();
}

int 
OutlineDatasource::listOfVisible(std::vector<OutlineNode*>* result)
{
	for(OutlineNode* node : _nodes)
	{
		if (node->isVisible() == true)
			result->push_back(node);
	}

	return result->size();
}

int 
OutlineDatasource::indexOf(OutlineNode* node)
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		OutlineNode* current = _nodes.at(i);

		if (current == node)
			return i;
	}

	return -1;
}

bool 
OutlineDatasource::isLeaf(int index)
{
	if (_nodes.size()-1 < index)
	{
		OutlineNode* next = _nodes.at(index+1);
		OutlineNode* current = _nodes.at(index);

		if (current->level() > next->level())
			return false;
	}
	return true;
}

void 
OutlineDatasource::makeChildrenNonVisible(OutlineNode* node)
{
	int index = indexOf(node);

	if (index != -1)
		hideChildren(index);
}

void 
OutlineDatasource::makeChildrenNonVisible(int index)
{
	if (isLeaf(index) == true)
		return;

	OutlineNode* current = _nodes.at(index);

	for (int i = index + 1; i < _nodes.size(); i++)
	{
		OutlineNode* next = _nodes.at(i);

		if (current->level() <= next->level())
			break;

		next->setVisible(false);
	}
}

void 
OutlineDatasource::makeChildrenVisible(OutlineNode* node)
{
	int index = indexOf(node);

	if (index != -1)
		showChildren(index);
}

void 
OutlineDatasource::makeChildrenVisible(int index)
{
	if (isLeaf(index) == true)
		return;

	OutlineNode* current = _nodes.at(index);

	for (int i = index + 1; i < _nodes.size(); i++)
	{
		OutlineNode* next = _nodes.at(i);

		if (current->level() + 1 == next->level())
			break;

		next->setVisible(true);
	}
}	

int 
OutlineDatasource::numberOfRows()
{
    return _nodes.size();
}

void 
printOut()
{
    for(OutlineNode* node : _nodes)
    {
        note->printOut();
    }
}