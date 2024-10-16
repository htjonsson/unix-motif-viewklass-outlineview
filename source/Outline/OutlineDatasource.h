#ifndef OUTLINE_DATASOURCE_H
#define OUTLINE_DATASOURCE_H

#include "OutlineNode.h"

#include <vector>
#include <string>

class OutlineDatasource
{
private:
	std::vector<OutlineNode*> _nodes;

public:
	void add(OutlineNode* child);
	void add(OutlineNode* parent, OutlineNode* child);

public:
	int listOfVisible(std::vector<OutlineNode*>* result);

private:
	int indexOf(OutlineNode* node);
	bool isLeaf(int index);

public:
	void hideChildren(OutlineNode* node);
	void hideChildren(int index);

public:
	void showChildren(OutlineNode* node);
	void showChildren(int index);

public:
    int numberOfRows();

public:
	void update();
};

#endif // OUTLINE_VIEW_H