#include "OutlineDatasource.h"

void
OutlineDatasource::add(OutlineNode* child)
{
	_nodes.push_back(child);
}

void
OutlineDatasource::add(OutlineNode* parent, OutlilneNode* child)
{
	_nodes.push_back(child);
	child.setParent(parent);
}

void
OutlineDatasource::Update()
{
    for(int i = +1; i < _nodes.size(); i++)
    {
		OutlineNode* current = _nodes.at(i-1);
		OutlineNode* next = _nodes.at(i);

        if (current->level() < next->level())
            current->setHasChildren(true);
        else
            current->setHasChildren(false);
    }
}

int 
OutlineDatasource::listOfVisible(vector<OutlineNode*> result)
{
	for(OutlineNode* node : _nodes)
	{
		if (node->isVisible() == true)
			result.push_back(node);
	}

	return result.size();
}

int 
OutlineDatasource::indexOf(OutlineNode* node)
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		OutlineNode* current = _nodes.at(index);

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

		if (current->level > next.level)
			return false;
	}
	return true;
}

void 
OutlineDatasource::hideChildren(OutlineNode* node)
{
	int index = indexOf(node);

	if (index != -1)
		hideChildren(index);
}

void 
OutlineDatasource::hideChildren(int index)
{
	if (isLeaf(index) == true)
		return;

	OutlineNode* current = _nodes.at(index);

	for (int i = index + 1; i < _nodes.size(); i++)
	{
		OutlineNode* next = _nodes.at(i);

		if (current->level <= next->level)
			break;

		next->setVisible(false);
	}
}

void 
OutlineDatasource::showChildren(OutlineNode* node)
{
	int index = indexOf(node);

	if (index != -1)
		showChildren(index);
}

void 
OutlineDatasource::showChildren(int index)
{
	if (isLeaf(index) == true)
		return;

	OutlineNode* current = _nodes.at(index);

	for (int i = index + 1; i < _nodes.size(); i++)
	{
		OutlineNode* next = _nodes.at(i);

		if (current->level + 1 == next->level)
			break;

		next->setVisible(true);
	}
}	

int 
OutlineDatasource::numberOfRows()
{
    return _nodes.size();
}