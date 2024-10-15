#ifndef OUTLINE_VIEW_H
#define OUTLINE_VIEW_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>

#include "OutlineViewRenderNode.h"
#include "OutlineViewDelegate.h"

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

    int _numberOfRowsVisible = 1;
    int _numberOfRows = 1;
    int _offsetRows = 0;
    int _separatorHeight = 1;

private:
    OutlineViewDelegate* _delegate = NULL;

public:
    OutlineView(const char *name, Widget parent);
    ~OutlineView();

private:
  void createWidget(const char *name, Widget parent);  

public:
    void setDelegate(OutlineViewDelegate* delegate);
    OutlineViewDelegate* delegate();

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
    void handleButton1Pressed(XButtonPressedEvent* event);

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