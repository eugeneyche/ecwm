#include <stdio.h>

#include "frame.h"
#include "client.h"

#define BORDER_WIDTH 2

Frame::Frame(WindowManager * wm, Client * client) :
		BaseWindow (wm, None), client (client)
{ 
    XSetWindowAttributes swa;

    area = clientAreaToFrameArea(client->getArea());

    swa.background_pixel = BlackPixel(wm->getDisplay(), wm->getScreen());
    swa.border_pixel = WhitePixel(wm->getDisplay(), wm->getScreen());
    swa.override_redirect = True;

    window = XCreateWindow(wm->getDisplay(), wm->getRoot(), area.x, area.y,
            area.width, area.height, BORDER_WIDTH, 
            DefaultDepth(wm->getDisplay(), wm->getScreen()), 
            CopyFromParent, CopyFromParent, CWOverrideRedirect | CWBorderPixel |
            CWBackPixel, &swa);

    XSelectInput(wm->getDisplay(), window, SubstructureRedirectMask | SubstructureNotifyMask);
}

Frame::~Frame()
{ }

void
Frame::fitClient()
{ 
    XWindowChanges wc;
    unsigned long attrmask;
    Rectangle clientArea;
    XConfigureEvent ce;

    clientArea = client->getArea();
    area = clientAreaToFrameArea(clientArea);

    attrmask = CWX | CWY | CWWidth | CWHeight;

    wc.x = area.x;
    wc.y = area.y;
    wc.width = area.width;
    wc.height = area.height;

    XConfigureWindow(wm->getDisplay(), window, attrmask, &wc);

    attrmask |= CWBorderWidth;

    wc.x = 5;
    wc.y = 35;
    wc.width = clientArea.width;
    wc.height = clientArea.height;
    wc.border_width = 0;

    ce.type = ConfigureNotify;
    ce.display = wm->getDisplay();
    ce.event = wm->getRoot();
    ce.window = client->getWindow();
    ce.x = clientArea.x;
    ce.y = clientArea.y;
    ce.width = clientArea.width;
    ce.height = clientArea.height;
    ce.border_width = 2;
    ce.above = None;
    ce.override_redirect = False;

    XConfigureWindow(wm->getDisplay(), client->getWindow(), attrmask, &wc);

    XSendEvent(wm->getDisplay(), wm->getRoot(), False,
            SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&ce);
}

Rectangle
Frame::frameAreaToClientArea(Rectangle frameArea)
{ 
	Rectangle clientArea;

    frameArea.x = clientArea.x;
    frameArea.y = clientArea.y;
    frameArea.width = clientArea.width - 10;
    frameArea.height = clientArea.height - 40;

	return clientArea;
}

Rectangle
Frame::clientAreaToFrameArea(Rectangle clientArea)
{ 
	Rectangle frameArea;

    frameArea.x = clientArea.x;
    frameArea.y = clientArea.y;
    frameArea.width = clientArea.width + 10;
    frameArea.height = clientArea.height + 40;

	return frameArea;
}
