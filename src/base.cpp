#include "base.h"

BaseWindow::BaseWindow(WindowManager * wm, Window window) :
        wm (wm), window (window)
{ 
    if (window != None) {
        XWindowAttributes wa;

        XGetWindowAttributes(wm->getDisplay(), window, &wa);

        area.x = wa.x;
        area.y = wa.y;
        area.width = wa.width;
        area.height = wa.height;
    } else {
        area.x = 0;
        area.y = 0;
        area.width = 0;
        area.height = 0;
    }
}

BaseWindow::~BaseWindow()
{ }

Window
BaseWindow::getWindow()
{
	return window;
}

Rectangle
BaseWindow::getArea()
{
    return area;
}

void
BaseWindow::map()
{
    XMapWindow(wm->getDisplay(), window);
}

void
BaseWindow::unmap()
{
    XUnmapWindow(wm->getDisplay(), window);
}

void
BaseWindow::configure(unsigned long attrmask, XWindowChanges * wc)
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
	
    XConfigureWindow(wm->getDisplay(), window, attrmask, wc);
}

void
BaseWindow::move(int x, int y)
{
	area.x = x;
	area.y = y;
    XMoveWindow(wm->getDisplay(), window, x, y);
}

void
BaseWindow::resize(int width, int height)
{
	area.width = width;
	area.height = height;
    XResizeWindow(wm->getDisplay(), window, width, height);
}

void
BaseWindow::moveResize(int x, int y, int width, int height)
{
	area.x = x;
	area.y = y;
	area.width = width;
	area.height = height;
    XMoveResizeWindow(wm->getDisplay(), window, x, y, width, height);
}

void
BaseWindow::destroy()
{
    XDestroyWindow(wm->getDisplay(), window);
}
