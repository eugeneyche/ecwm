#include "window.h"

ECWindow::ECWindow(Display* dpy, Window win) :
        dpy (dpy),
        win (win)
{
    XWindowAttributes wa;
    XGetWindowAttributes(dpy, win, &wa);
    geom.moveResize(wa.x, wa.y, wa.width, wa.height);
}

ECWindow::~ECWindow()
{ }

void
ECWindow::map()
{
    XMapWindow(dpy, win);
}

void
ECWindow::unmap()
{
    XUnmapWindow(dpy, win);
}

void
ECWindow::configure(unsigned int attr, XWindowChanges* wcp)
{
    XConfigureWindow(dpy, win, attr, wcp);
    int x, y, width, height;

    x = geom.getX();
    y = geom.getY();
    width = geom.getWidth();
    height = geom.getHeight();

    if (attr | CWX) {
        x = wcp->x;
    }
    if (attr | CWY) {
        y = wcp->y;
    }
    if (attr | CWWidth) {
        width = wcp->width;
    }
    if (attr | CWHeight) {
        height = wcp->height;
    }

    geom.moveResize(x, y, width, height);
}

void
ECWindow::move(int x, int y)
{
    geom.move(x, y);
    XMoveWindow(dpy, win, x, y);
}

void
ECWindow::resize(int width, int height)
{
    geom.resize(width, height);
    XMoveWindow(dpy, win, width, height);
}

void
ECWindow::moveResize(int x, int y, int width, int height)
{
    geom.moveResize(x, y, width, height);
    XMoveResizeWindow(dpy, win, x, y, width, height);
}
