#include "base.h"

Base::Base(WindowManager * wm, Window window)
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
    XConfigureWindow(wm->getDisplay(), window, attrmask, wc);
}

void
Base::move(int x, int y)
{
    XMoveWindow(wm->getDisplay(), window, x, y);
}

void
Base::resize(int width, int height)
{
    XResizeWindow(wm->getDisplay(), window, width, height);
}

void
Base::moveResize(int x, int y, int width, int height)
{
    XMoveResizeWindow(wm->getDisplay(), window, x, y, width, height);
}

void
Base::destroy()
{
    XDestroyWindow(wm->getDisplay(), window);
}
