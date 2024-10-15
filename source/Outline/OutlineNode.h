#ifndef OUTLINE_NODE_H
#define OUTLINE_NODE_H

#include <Xm/Xn.h>

#include <vector>
#include <string>

class OutlineNode
{
private:
	std::string 	_name;
	std::string 	_label;
	bool 			_expanded = false;
	XtPointer		_clientData = null;
	bool			_visible = false;
	int  			_level = 0;
    bool            __hasChildren = false;

public:
	OutlineNode(int level, std::string label);
	OutlineNode(int level, std::string label, std::string text);
	~OutlineNode();

public:
	bool isExtended();
	void setExtended(bool isExtended);

public:
	OutlineNode* parent();
	void setParent(OutlineNode* newParent);

public:
	XtPointer clientData();
	void setClientData(XtPointer clientData);

public:
	bool isVisible();
	void setVisible(bool isVisible);

public:
	int level();
	void setLevel(int level);	

public:
    bool hasChildren();
    void setHasChildren(bool hasChildren);
};

#endif // OUTLINE_NODE_H