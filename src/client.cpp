#include "client.h"

Client::Client(WindowManager * wm, Window window) :
        BaseWindow (wm, window), frame (NULL)
{ }

Client::~Client()
{ 
    if (frame) {
        frame->destroy();
        delete frame;
        frame = NULL;
    }
}

void
Client::map()
{
    if (frame) {
        frame->map();
        frame->fitClient();
    } else {
        reparent();
        frame->map();
        frame->fitClient();
    }
    XMapWindow(wm->getDisplay(), window);
}

void
Client::unmap()
{
    if (frame) {
        unreparent();
    }
    XUnmapWindow(wm->getDisplay(), window);
}

void
Client::configure(unsigned long attrmask, XWindowChanges * wc)
{
    int x, y, width, height;

    if (attrmask & CWX) {
        area.x = wc->x;
    }
    if (attrmask & CWY) {
        area.y = wc->y;
    }
    if (attrmask & CWWidth) {
        area.width = wc->width;
    }
    if (attrmask & CWHeight) {
        area.height = wc->height;
    }

    if (frame) {
        frame->fitClient();
    } else {
        XConfigureWindow(wm->getDisplay(), window, attrmask, wc);
    }
}

void 
Client::move(int x, int y)
{ 
	area.x = x;
	area.y = y;

    if (frame) {
        frame->fitClient();
    } else {
        XMoveWindow(wm->getDisplay(), window, area.x, area.y);
    }
}

void 
Client::resize(int width, int height)
{ 
	area.width = width;
	area.height = height;

    if (frame) {
        frame->fitClient();
    } else {
        XResizeWindow(wm->getDisplay(), window, area.width, area.height);
    }
}

void 
Client::moveResize(int x, int y, int width, int height)
{ 
	area.x = x;
	area.y = y;
	area.width = width;
	area.height = height;

    if (frame) {
        frame->fitClient();
    } else {
        XMoveResizeWindow(wm->getDisplay(), window, area.x, area.y, 
                area.width, area.height);
    }
}

void
Client::destroy()
{ 
    if (frame) {
        unreparent();
    }
    BaseWindow::destroy();
}

void
Client::kill()
{ /* Send kill to window, not actually destroy window */ }

void
Client::iconify()
{ /* This may not be necessary? */ }

void
Client::withdraw()
{ /* This may not be necessary? */ }

void
Client::reparent()
{ 
    frame = new Frame(wm, this);
    XAddToSaveSet(wm->getDisplay(), window);
    XReparentWindow(wm->getDisplay(), window, frame->getWindow(), 0, 0);
}

void
Client::unreparent()
{ 
    if (frame) {
        XReparentWindow(wm->getDisplay(), window, wm->getRoot(), area.x, area.y);
        frame->destroy();
        delete frame;
        frame = NULL;
    }
}
