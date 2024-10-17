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
	void add(OutlineNode* node);

public:
	int listOfVisible(std::vector<OutlineNode*>* result);

private:
	int childrenOf(OutlineNode* parent, std::vector<OutlineNode*>* result);
	void setVisibilityBy(OutlineNode* parent);

private:
	int indexOf(OutlineNode* node);
	bool isLeaf(int index);

public:
	void makeChildrenNonVisible(OutlineNode* node);
	void makeChildrenNonVisible(int index);

public:
	void makeChildrenVisible(OutlineNode* node);
	void makeChildrenVisible(int index);

public:
    int numberOfRows();

public:
	void update();

public:
    void printOut();
};

#endif // OUTLINE_VIEW_H