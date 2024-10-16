// Motif 
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/List.h>
// ViewKlass
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
// Standard C/C++
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Outline/OutlineView.h"
#include "Outline/OutlineNode.h"

#include "DefaultResources.h"

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
    VkApp* app = new VkApp("OutlineViewApp", &argc, argv);
    // Application-specific code
    app->setDefaultResources(app->baseWidget(), _defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("OutlineView");
    
    OutlineView panel("list_view_panel", win->mainWindowWidget());

    win->addView(panel);

    // Set a default size of window as 800x600
    XtVaSetValues(win->mainWindowWidget(), XmNwidth, 800, XmNheight, 600, NULL);

    OutlineDatasource* datasource = panel.datasource();

    if (datasource)
    {
        OutlineNode* n1  = new OutlineNode(0, "Heading");
        OutlineNode* n2  = new OutlineNode(1, "Subheading 1A");
        OutlineNode* n3  = new OutlineNode(1, "Subheading 1B");
        OutlineNode* n4  = new OutlineNode(1, "Subheading 1C");
        OutlineNode* n5  = new OutlineNode(0, "Heading");
        OutlineNode* n6  = new OutlineNode(1, "Subheading 2A");
        OutlineNode* n7  = new OutlineNode(1, "Subheading 2B");
        OutlineNode* n8  = new OutlineNode(2, "Item 2B/i)");
        OutlineNode* n9  = new OutlineNode(2, "Item 2B/ii)");
        OutlineNode* n10 = new OutlineNode(3, "Subitem 2B/ii/a)");
        OutlineNode* n11 = new OutlineNode(3, "Subitem 2B/ii/b)");
        OutlineNode* n12 = new OutlineNode(2, "Item 2B/iii)");
        OutlineNode* n13 = new OutlineNode(1, "Subheading 2C");
        OutlineNode* n14 = new OutlineNode(0, "Heading 3");
        OutlineNode* n15 = new OutlineNode(1, "Subheading 3A");
        OutlineNode* n16 = new OutlineNode(1, "Subheading 3B");
        OutlineNode* n17 = new OutlineNode(1, "Subheading 3C");

        datasource->add(n1);
        datasource->add(n2);
        datasource->add(n3);
        datasource->add(n4);
        datasource->add(n5);
        datasource->add(n6);
        datasource->add(n7);
        datasource->add(n8);
        datasource->add(n9);
        datasource->add(n10);
        datasource->add(n11);
        datasource->add(n12);
        datasource->add(n13);
        datasource->add(n14);
        datasource->add(n15);
        datasource->add(n16);
        datasource->add(n17);

        panel.update();
    }

    win->show();
    // Run the application
    app->run();  

    return 0;
}

