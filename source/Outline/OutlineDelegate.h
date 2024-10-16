#ifndef OUTLINE_DELEGATE_H
#define OUTLINE_DELEGATE_H

#include "OutlineNode.h"
#include "EZ/Graphics.h"
#include "EZ/EZ.h"

#include <Xm/Xm.h>
#include <string>
#include <vector>

using namespace std;

class OutlineDelegate
{
public:
    OutlineDelegate();
    virtual ~OutlineDelegate();

private:
    int _heightOfRow;

public:
    void add(int id, int indent, std::string text);
    void add(int id, int indent, bool isToggle, std::string text);

private:
    static const string _titlefontName;
    static const string _titleColorName;
    static const string _textfontName;
    static const string _textColorName;

private:
    void initImages(Graphics* g);

public:
    int heightOfRow();
    void setHeightOfRow(int heightOfRow);

public:
    virtual bool handleRowSelected(OutlineNode* node);
    virtual bool handleCollapse(OutlineNode* node);
    virtual bool handleExpanded(OutlineNode* node);

public:
    virtual void draw(OutlineNode* node, Graphics* graphics, XRectangle rectangle);
};

#endif // OUTLINE_VIEW_DELEGATE_H
