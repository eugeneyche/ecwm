#include "base.h"

Base::Base(WindowManager * wm, Window window) :
        wm (wm), window (window)
{ }

Base::~Base()
{ }

void
Base::map()
{
    XMapWindow(wm->getDisplay(), window);
}

void
Base::unmap()
{
    XUnmapWindow(wm->getDisplay(), window);
}

void
Base::configure(unsigned long attrmask, XWindowChanges * wc)
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
Base::move(int x, int y)
{
	area.x = x;
	area.y = y;
    XMoveWindow(wm->getDisplay(), window, x, y);
}

void
Base::resize(int width, int height)
{
	area.width = width;
	area.height = height;
    XResizeWindow(wm->getDisplay(), window, width, height);
}

void
Base::moveResize(int x, int y, int width, int height)
{
	area.x = x;
	area.y = y;
	area.width = width;
	area.height = height;
    XMoveResizeWindow(wm->getDisplay(), window, x, y, width, height);
}

void
Base::destroy()
{
    XDestroyWindow(wm->getDisplay(), window);
}
