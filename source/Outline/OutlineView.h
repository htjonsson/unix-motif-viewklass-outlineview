#ifndef OUTLINE_VIEW_H
#define OUTLINE_VIEW_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>

#include "OutlineNode.h"
#include "OutlineDelegate.h"
#include "OutlineDatasource.h"

class OutlineView : public VkComponent
{
private:
    Widget _drawingArea;
    Widget _verticalScrollbar;
    Widget _horizontalScrollbar;

private:
    Graphics graphics;

private:
    Dimension _rowHeight = 30;
    Dimension _rowWidth = 0;

    int _numberOfRowsVisible = 0;
    int _numberOfRows = 0;
    int _offsetRows = 0;
    int _separatorHeight = 1;
    int _indentWidth = 12;

private:
    OutlineDelegate*    _delegate = NULL;
    OutlineDatasource*  _datasource = NULL;

public:
    OutlineView(const char *name, Widget parent);
    ~OutlineView();

private:
  void createWidget(const char *name, Widget parent);  

public:
    void setDatasource(OutlineDatasource* datasource);
    OutlineDatasource* datasource();

public:
    void setDelegate(OutlineDelegate* delegate);
    OutlineDelegate* delegate();

public:
    void setNumberOfRows(int numberOfRows);
    int numnberOfRows();

public:
    void setHeightOfRow(int heightOfRow);

private:
    void setupUserInterface(Widget w);

private:
    void redraw(Window window);

public:
    void setRowsVisible(Dimension height);
    int getRowIdByY(int y);

private:
    int _selectedRow = -1;

public:
    void setSelectedRow(int id);
    int selectedRow();
    void clearSelectionRow();

public:
    void update();

private:
    void handleScrolled(int orientation, int value);
    void handleExpose(Window window); 
    void handleResize(Window window);   
    void handleEvent(XEvent* event);  
    void handleButtonPressed(XButtonPressedEvent* event);

private:
    void handleButton1Pressed(XButtonPressedEvent* event);
    void handleButton4Pressed(XButtonPressedEvent* event);
    void handleButton5Pressed(XButtonPressedEvent* event);

private:
    static void inputCallback(Widget widget, XtPointer clientData, XtPointer callData);
    static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData); 
    static void resizeCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);     
};

#endif // OUTLINE_VIEW_H