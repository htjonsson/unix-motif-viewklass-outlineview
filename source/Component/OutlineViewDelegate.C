#include "Component/OutlineViewDelegate.h"

#include <Vk/VkPixmap.h>
#include <Xm/Xm.h>
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

#include "images/toggled.xpm"
#include "images/untoggled.xpm"

using namespace std;

OutlineViewDelegate::OutlineViewDelegate()
{
    _numberOfRows = 0;
    _heightOfRow = 22;
}

OutlineViewDelegate::~OutlineViewDelegate()
{
    for(OutlineViewRenderNode* node : _nodes)
        delete node;

    _nodes.clear();
}

// --------------------------------------------------------------------------------------------------------------------------

const string OutlineViewDelegate::_titlefontName = "Verdan:style=Bold:pixelsize=10:antialias=true";
const string OutlineViewDelegate::_titleColorName = "black";
const string OutlineViewDelegate::_textfontName = "Verdan:pixelsize=10:antialias=true";
const string OutlineViewDelegate::_textColorName = "gray55";

// ------------------------------------------------------------------------------------------------------------------------
//
//      DATA LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineViewDelegate::add(int id, int indent, std::string text)
{
    add(id, indent, false, text);
}

void 
OutlineViewDelegate::add(int id, int indent, bool isToggle, std::string text)
{
    OutlineViewRenderNode* item = new OutlineViewRenderNode(id, indent, isToggle, text);  

    _nodes.push_back(item);
}

// --------------------------------------------------------------------------------------------------------------------------

int 
OutlineViewDelegate::numberOfRows()
{
    return _nodes.size();
}

void
OutlineViewDelegate::setNumberOfRows(int numberOfRows)
{
    _numberOfRows =  numberOfRows;
}

int 
OutlineViewDelegate::heightOfRow()
{
    // std::cout << "OutlineViewDelegate::heightOfRow() " << _heightOfRow << endl; 

    return _heightOfRow;;
}

 void 
 OutlineViewDelegate::setHeightOfRow(int heightOfRow)
 {
    _heightOfRow = heightOfRow;
 }

bool
OutlineViewDelegate::handleRowSelected(int rowId)
{
    if (_nodes.size() > rowId)
    {
        OutlineViewRenderNode* node = _nodes.at(rowId);

        if (node->isToggle())
        {
            if (node->isCollapsed())
            {
                node->setExpended();
                _nodes[rowId] = node;
                node->printOut();
                return handleExpanded(rowId);

                
            }
            else
            {
                node->setCollapsed();   
                _nodes[rowId] = node;
                node->printOut();
                return handleCollapse(rowId);
            }               
        }
    }

    std::cout << "OutlineViewDelegate::rowSelected " << rowId << std::endl;

    // no need to redraw
    return false; 
}

bool 
OutlineViewDelegate::handleCollapse(int rowId)
{
    std::cout << "isCollapsed" << std::endl;

    return true;
}

bool 
OutlineViewDelegate::handleExpanded(int rowId)
{
    std::cout << "isExpanded" << std::endl;

    return true;
}

// --------------------------------------------------------------------------------------------------------------------------

void
OutlineViewDelegate::initImages(Graphics* g)
{
    g->getPixmapByName("toggled", xpm_toggled);
    g->getPixmapByName("untoggled", xpm_untoggled);
}

void 
OutlineViewDelegate::draw(int rowId, Graphics* g, XRectangle rectangle)
{
    initImages(g);

    if (_nodes.size() > rowId)
    {
        OutlineViewRenderNode* node = _nodes.at(rowId);

        // default indent is 6 pixels
        int indentWidth = 12 * node->indent();

        XRectangle rect = EZ::ofRectangle(rectangle, 28 + indentWidth, 3, 300, 11);
        g->drawString(  _titlefontName, 
                        _titleColorName, 
                        rect,
                        node->text());

        // image
        if (node->isToggle())
        {
            if (node->isExpended()) 
            {
                rect = EZ::ofRectangle(rectangle, 6 + indentWidth, 0, 12, 21);
                g->draw("toggled", rect);  
                std::cout << "toggled" << std::endl;
            }
            else
            {
                rect = EZ::ofRectangle(rectangle, 6 + indentWidth, 0, 12, 13);
                g->draw("untoggled", rect); 
                std::cout << "untoggled" << std::endl;              
            }
        }                        
    }
}
 
