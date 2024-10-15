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

#include "Component/OutlineView.h"
#include "Component/OutlineViewNode.h"
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

    OutlineViewDelegate* delegate = panel.delegate();

    if (delegate)
    {
        OutlineViewNode* root = new OutlineViewNode(0, "");

        OutlineViewNode* n1,n2,n3;
        
        n1 = root->add(1, "Heading");
        n1->add(2, "Subheading 1A");
        n1->add(3, "Subheading 1B");
        n1->add(4, "Subheading 1C");

        n1 = root->add(5, "Heading");
        n1->add(6, "Subheading 1A");
        n2 = n1->add(7, "Subheading AB");
        n2->add(8, "Item 2B/i");
        n3 = n2->add(9, "Item 2B/ii");
        n3->add(10, "Item 2B/ii/a");
        n3->add(11, "Item 2B/ii/b");
        n2->add(12, "Item 2B/ii");
        n2->add(13, "Subheading");

        n1 = root->add(14, "Heading 3");
        n1->add(15, "Subheading 3A");
        n1->add(16, "Subheading 3B");
        n1->add(17, "Subheading 3C");

        root->update(delegate);

        delegate->add(1, 0, true, "Heading");
        delegate->add(2, 1, "Subheading 1A");
        delegate->add(3, 1, "Subheading 1B");
        delegate->add(4, 1, "Subheading 1C");
        delegate->add(5, 0, true, "Heading");
        delegate->add(6, 1, true, "Subheading 1A");
        delegate->add(7, 1, true, "Subheading AB");
        delegate->add(8, 2, "Item 2B/i)");
        delegate->add(9, 2, true, "Item 2B/ii)");
        delegate->add(10, 3, "Subitem 2B/ii/a)");
        delegate->add(11, 3, true, "Subitem 2B/ii/b)");
        delegate->add(12, 2, "Item 2B/iii)");
        delegate->add(13, 1, "Subheading");
        delegate->add(14, 0, true, "Heading 3");
        delegate->add(15, 1, "Subheading 3A");
        delegate->add(16, 1, "Subheading 3B");
        delegate->add(17, 1, "Subheading 3C");

        panel.update();
    }





    win->show();

    // Run the application
    app->run();  

    return 0;
}

