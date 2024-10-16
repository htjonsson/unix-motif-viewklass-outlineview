// https://www.oreilly.com/openbook/motif/vol6a/Vol6a_html/appa.html#28

#include "OutlineView.h"
#include "EZ/EZ.h"
#include "EZ/Graphics.h"

#include <Xm/ScrolledW.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrollBar.h>
#include <string>
#include <iostream>

using namespace std;

OutlineView::OutlineView(const char *name, Widget parent)
    : VkComponent(name)
{
    setDelegate(new OutlineDelegate());
    setDatasource(new OutlineDatasource());
    setNumberOfRows(datasource()->numberOfRows());
    
    createWidget(name, parent);    
}

OutlineView::~OutlineView()
{
    if (_delegate != NULL)
        delete _delegate;

    if (_datasource != NULL)
        delete _datasource;
}

void OutlineView::createWidget(const char *name, Widget parent)
{
    _baseWidget = XtVaCreateManagedWidget(name,
                                          xmScrolledWindowWidgetClass, parent,
                                          XmNscrollingPolicy, XmAPPLICATION_DEFINED,
                                          XmNvisualPolicy, XmVARIABLE,
                                          XmNshadowThickness, 0,
                                          NULL);

    // --------------------------------------------------------------------------

    _drawingArea = XtVaCreateManagedWidget("list_view_panel_drawing_a",
                                           xmDrawingAreaWidgetClass, _baseWidget,
                                           NULL);

    // --------------------------------------------------------------------------

    _verticalScrollbar = XtVaCreateManagedWidget("list_view_panel_vertical_scrollbar",
                                                 xmScrollBarWidgetClass, _baseWidget,
                                                 XmNorientation, XmVERTICAL,
                                                 XmNminimum, 0,
                                                 XmNmaximum, 1,
                                                  NULL);

    // --------------------------------------------------------------------------

    _horizontalScrollbar = XtVaCreateManagedWidget("list_view_panel_horizontal_scrollbar",
                                                   xmScrollBarWidgetClass, _baseWidget,
                                                   XmNorientation, XmHORIZONTAL,
                                                   NULL);

    // --------------------------------------------------------------------------

    XmScrolledWindowSetAreas(_baseWidget, _horizontalScrollbar, _verticalScrollbar, _drawingArea);

    // --------------------------------------------------------------------------

    XtAddCallback(_drawingArea, XmNexposeCallback, exposeCallback, this);
    XtAddCallback(_drawingArea, XmNresizeCallback, resizeCallback, this);
    XtAddCallback(_drawingArea, XmNinputCallback, inputCallback, this);

    // --------------------------------------------------------------------------

    XtAddCallback(_verticalScrollbar, XmNvalueChangedCallback, valueChangedVerticalCallback, this);
    XtAddCallback(_verticalScrollbar, XmNdragCallback, dragVerticalCallback, this);

    // --------------------------------------------------------------------------

    XtAddCallback(_horizontalScrollbar, XmNvalueChangedCallback, valueChangedHorizontalCallback, this);
    XtAddCallback(_horizontalScrollbar, XmNdragCallback, dragHorizontalCallback, this);
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      DELEGATE LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineView::setDelegate(OutlineDelegate *delegate)
{
    _delegate = delegate;
}

OutlineDelegate*
OutlineView::delegate()
{
    return _delegate;
}

void 
OutlineView::setDatasource(OutlineDatasource* datasource)
{
    _datasource = datasource;
}
    
OutlineDatasource* 
OutlineView::datasource()
{
    return _datasource;
}

int 
OutlineView::numnberOfRows()
{
    return _numberOfRows;
}

void
OutlineView::setNumberOfRows(int numberOfRows)
{
    if (_numberOfRows != numberOfRows && numberOfRows > 1)
    {
        _numberOfRows = numberOfRows;

        XtVaSetValues(_verticalScrollbar, XmNmaximum, _numberOfRows, NULL);
    }
}

void
OutlineView::update()
{
    if (_datasource)
    {
        _datasource.update();

        setNumberOfRows(_datasource->numberOfRows());
    }
        
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      SELECTED ROW LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineView::setSelectedRow(int id)
{
    if (_numberOfRows > id || id < 0)
        clearSelectionRow();

    _selectedRow = id;
}
    
int 
OutlineView::selectedRow()
{
    return _selectedRow;
}
    
void 
OutlineView::clearSelectionRow()
{
    _selectedRow = -1;
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      DRAWING LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineView::setRowsVisible(Dimension height)
{
    if (height > 0)
    {
        XtWarning("Can't calculate rows visible");
        return;
    }

    float rows = (float)height / (float)_rowHeight;
    _numberOfRowsVisible = (int)rows;
}

void 
OutlineView::redraw(Window window)
{   
    graphics.useWith(_drawingArea);

    std::cout << "redraw()" << std::endl;

    // Clear the drawarea with white color
    XRectangle windowReact = EZ::makeRectangle(0, 0, 0, 0);
    XtVaGetValues(_drawingArea, XmNwidth, &windowReact.width, XmNheight, &windowReact.height, NULL);
    graphics.fillRectangle(windowReact, "white");

    if (_delegate == NULL)
    {
        XtWarning("Delegator not found");
        return;
    }

    if (_datasource == NULL)
    {
        XtWarning("Datasource not found");
        return;
    }

    int hightOfRow = _delegate->heightOfRow();

    // std::cout << "[numberOfRows] " << _numberOfRows << std::endl;
    // std::cout << "[offsetRows] " << _offsetRows << std::endl;

    std::vector<OutlineNode*> nodes;
    _datasource->listOfVisible(&nodes);

    // Edge case when nothing too see
    if (_offsetRows >= nodes.size())
        _offsetRows = nodes.size()-2;

    for (int i = 0; i < _numberOfRowsVisible; i++)
    {
        int rowId = i + (_offsetRows); 

        if (_datasource != NULL && nodes.size() > rowId)
        {   
            int offset = (hightOfRow + _separatorHeight) * i;

            if (rowId == selectedRow())
            {
                XRectangle selectedRowReact = EZ::makeRectangle(6, offset, windowReact.width-12, hightOfRow-_separatorHeight);
                graphics.fillRectangle(selectedRowReact, "gray98");
            }

            XRectangle rectangle = EZ::makeRectangle(6, offset, _rowWidth-12, hightOfRow-_separatorHeight);
            _delegate->draw(nodes.at(rowId), &graphics, rectangle);
        }     
    }
}

int
OutlineView::getRowIdByY(int y)
{
    if (_delegate == NULL)
        return -1;

    int hightOfRow = _delegate->heightOfRow();

    for (int i = 0; i < _numberOfRowsVisible; i++)
    {
        int rowId = i + (_offsetRows); 

        if (_datasource->numberOfRows() > rowId)
        {   
            int offset = (hightOfRow + _separatorHeight) * i;

            if (y >= offset && y <= offset + hightOfRow)
            {
                return rowId;
            }                
        }
    }
    return -1;
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      HANDLER ACTIONS
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineView::handleScrolled(int orientation, int value)
{
    // std::cout << "scrolled " << value << std::endl;

    _offsetRows = value;

    redraw(XtWindow(_drawingArea));
}

void 
OutlineView::handleExpose(Window window)
{
    // std::cout << "expose()" << std::endl;

    redraw(window);
}

void 
OutlineView::handleResize(Window window)
{
    Dimension width, height;
    GC gc;

    XtVaGetValues(_drawingArea, XmNwidth, &width, XmNheight, &height, NULL);

    _rowWidth = width;

    // std::cout << "XmNwidth " << width << std::endl;
    // std::cout << "XmNheight " << height << std::endl;

    if (_delegate != NULL)
    {
        // Calculate how many rows are visible
        int heightOfRow =  _delegate->heightOfRow();

        // std::cout << "heightOfRow " << heightOfRow << std::endl;

        _numberOfRowsVisible = (int)(height/heightOfRow) + 1;

        // std::cout << "numberOfRowsVisible " << _numberOfRowsVisible << std::endl;
    }
}

void 
OutlineView::handleEvent(XEvent* event)
{
    // cout << "type : " << event->type << endl;

    // https://stackoverflow.com/questions/35745561/how-can-i-convert-an-xevent-to-a-string
    switch(event->type)
    {
        
        // case 2: cout << "XKeyPressedEvent" << endl; break;
        // case 3: handleKeyReleased((XKeyReleasedEvent*)event); break;
        case 4: handleButtonPressed((XButtonPressedEvent*)event); break;
        // case 5: handleButtonReleased((XButtonReleasedEvent*)event); break;
        // case 6: cout << "XPointerMovedEvent" << endl; break;
        // case 7: cout << "XEnterWindowEvent" << endl; break;
        // case 8: cout << "XLeaveWindowEvent" << endl; break;
        // case 9: cout << "XFocusInEvent" << endl; break;
        // case 10: cout << "XFocusOutEvent" << endl; break;
        // case 11: cout << "XKeymapEvent" << endl; break;
        // case 12: cout << "XExposeEvent" << endl; break;
        // case 13: cout << "XGraphicsExposeEvent" << endl; break;
        default: break; // cout << "Undefined" << endl; break;
    }
}

void 
OutlineView::handleButton1Pressed(XButtonPressedEvent* event)
{
    cout << "handleButton1Pressed" << " y: " << event->y << endl;    

    int rowId = getRowIdByY(event->y);

    cout << "handleButton1Pressed" << " rowId: " << rowId<< endl;  

    setSelectedRow(rowId);

    if (_delegate != NULL && _datasource != NULL)
    {
        std::vector<OutlineNode*> nodes;
        _datasource->listOfVisible(&nodes);

        cout << "handleButton1Pressed" << " nodes: " << nodes.size()<< endl;  

        if (rowId < nodes.size())
        {
            OutlineNode* node = nodes.at(rowId);

            if(_delegate->handleRowSelected(node, _datasource))
                redraw(XtWindow(_drawingArea));
        }
    }    
}

void
OutlineView::handleButton4Pressed(XButtonPressedEvent* event)
{
    cout << "handleButton4Pressed" << endl;
}

void
OutlineView::handleButton5Pressed(XButtonPressedEvent* event)
{
    cout << "handleButton5Pressed" << endl;
}

void 
OutlineView::handleButtonPressed(XButtonPressedEvent* event)
{
    // cout << "handleButtonPressed" << endl;
    // cout << "x: " << event->x << " y: " << event->y << endl;

    // https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
    switch(event->button)
    {
        case Button1: handleButton1Pressed(event); break;
        // case Button2: cout << "Button2" << endl; break;
        // case Button3: cout << "Button3" << endl; break;
        case Button4: handleButton4Pressed(event); break;
        case Button5: handleButton5Pressed(event); break;
        default: break;
    }
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      MOTIF CALLBACKS LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
OutlineView::exposeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "exposeCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleExpose(cbs->window);
    }
}

void OutlineView::inputCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "inputCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (clientData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleEvent(cbs->event); 
    }
}   

void OutlineView::resizeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "resizeCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleResize(cbs->window);
    }
}

void OutlineView::valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "valueChangedVerticalCallback" << std::endl;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void OutlineView::dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "dragVerticalCallback" << std::endl;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void OutlineView::valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "valueChangedHorizontalCallback" << std::endl;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void OutlineView::dragHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    // std::cout << "dragHorizontalCallbackWidget" << std::endl;

    if (callData != NULL)
    {
        OutlineView *view = (OutlineView*)clientData;
        view->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}
