#ifndef OUTLINE_VIEW_DELEGATE_H
#define OUTLINE_VIEW_DELEGATE_H

#include "OutlineViewRenderNode.h"
#include "EZ/Graphics.h"
#include "EZ/EZ.h"
#include <Xm/Xm.h>
#include <string>
#include <vector>

using namespace std;

class OutlineViewDelegate
{
public:
    OutlineViewDelegate();
    virtual ~OutlineViewDelegate();

private:
    int _numberOfRows;

private:
    std::vector<OutlineViewRenderNode*> _nodes;

public:
    virtual int numberOfRows();
    void setNumberOfRows(int numberOfRows);

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
    virtual bool handleRowSelected(int rowId);
    virtual bool handleCollapse(int rowId);
    virtual bool handleExpanded(int rowId);

public:
    virtual void draw(int rowId, Graphics* graphics, XRectangle rectangle);
};

#endif // OUTLINE_VIEW_DELEGATE_H
