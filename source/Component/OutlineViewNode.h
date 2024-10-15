#ifndef OUTLINE_VIEW_NODE_H
#define OUTLINE_VIEW_NODE_H

#include <string>
#include <vector>

class OutlineViewNode
{
public:
    OutlineViewNode(int id, std::string text);
    ~OutlineViewNode();

private:
    int                             _id;
    std::string                     _text;
    std::vector<OutlineViewNode*>   _children;

public:
    int id();
    std::string text();

public:
    OutlineViewNode* add(int id, std::string text);
};

#endif // OUTLINE_VIEW_NODE_H