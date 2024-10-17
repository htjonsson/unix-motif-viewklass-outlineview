#include "Outline/OutlineDelegate.h"

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

OutlineDelegate::OutlineDelegate()
{
    _heightOfRow = 22;
}

OutlineDelegate::~OutlineDelegate()
{}

// --------------------------------------------------------------------------------------------------------------------------

const string OutlineDelegate::_titlefontName = "Verdan:style=Bold:pixelsize=10:antialias=true";
const string OutlineDelegate::_titleColorName = "black";
const string OutlineDelegate::_textfontName = "Verdan:pixelsize=10:antialias=true";
const string OutlineDelegate::_textColorName = "gray55";

// --------------------------------------------------------------------------------------------------------------------------

int 
OutlineDelegate::heightOfRow()
{
    // std::cout << "OutlineDelegate::heightOfRow() " << _heightOfRow << endl; 

    return _heightOfRow;;
}

 void 
 OutlineDelegate::setHeightOfRow(int heightOfRow)
 {
    _heightOfRow = heightOfRow;
 }

bool
OutlineDelegate::handleRowSelected(OutlineNode* node)
{    
    std::cout << "handleRowSelected" << std::endl;

    if (node->hasChildren())
    {
        if (node->isExpanded())
        {
            node->setExtended(false);
            // _nodes[rowId] = node;
            // node->printOut();
            return handleExpanded(node);   
        }
        else
        {
            node->setExtended(true);   
            // nodes[rowId] = node;
            // node->printOut();
            return handleCollapse(node);
        }               
    }
    
    // std::cout << "OutlineDelegate::rowSelected " << rowId << std::endl;

    // no need to redraw
    return true; 
}

bool 
OutlineDelegate::handleCollapse(OutlineNode* node)
{
    std::cout << "isCollapsed" << std::endl;

    return true;
}

bool 
OutlineDelegate::handleExpanded(OutlineNode* node)
{
    std::cout << "isExpanded" << std::endl;



    return true;
}

// --------------------------------------------------------------------------------------------------------------------------

void
OutlineDelegate::initImages(Graphics* g)
{
    g->getPixmapByName("toggled", xpm_toggled);
    g->getPixmapByName("untoggled", xpm_untoggled);
}

void 
OutlineDelegate::draw(OutlineNode* node, Graphics* g, XRectangle rectangle)
{
    initImages(g);


    //bOutlineViewRenderNode* node = _nodes.at(rowId);

    // default indent is 6 pixels
    int indentWidth = 12 * node->level();

    XRectangle rect = EZ::ofRectangle(rectangle, 28 + indentWidth, 3, 300, 11);
    g->drawString(  _titlefontName, 
                    _titleColorName, 
                    rect,
                    node->label());
    // image
    if (node->hasChildren())
    {
        std::cout << "OutlineDelegate::" << "hasChildren" << std::endl;
        if (node->isExpanded()) 
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
 
