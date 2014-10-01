#include <stdio.h>
#include "manager.h"

void
WindowManager::keyPress(XEvent * ev)
{
    printf("> keyPress\n");
}

void
WindowManager::mapRequest(XEvent * ev)
{
    XMapRequestEvent * mev;

	mev = &ev->xmaprequest;

    printf("> mapRequest\n");
    printf("\twindow: %ld\n", mev->window);
}

void
WindowManager::destroyNotify(XEvent * ev)
{
    XDestroyWindowEvent * dev;

    dev = &ev->xdestroywindow;

    printf("> destroyNotify\n");
    printf("\twindow: %ld\n", dev->window);
    printf("\tevent: %ld\n", dev->event);
}

void
WindowManager::configureNotify(XEvent * ev)
{
    XConfigureEvent * cev;

    cev = &ev->xconfigure;

    printf("> configureNotify\n");
    printf("\twindow: %ld\n", cev->window);
    printf("\tx, y, w, h: %d %d %d %d\n",
            cev->x,
            cev->y,
            cev->width,
            cev->height);
    printf("\tbw: %d\n", cev->border_width);
    printf("\tabove: %s\n", (cev->above) ?
            "true" : "false");
    printf("\toverride: %s\n", (cev->override_redirect) ?
            "true" : "false");
    
}

void
WindowManager::configureRequest(XEvent * ev)
{
    XConfigureRequestEvent * cev;

    cev = &ev->xconfigurerequest;

    printf("> configureRequest\n");
    printf("\twindow: %ld\n", cev->window);
    printf("\tx, y, width, height: %d %d %d %d\n",
            cev->x,
            cev->y,
            cev->width,
            cev->height);
    printf("\tbw: %d\n", cev->border_width);
    printf("\tabove: %s\n", (cev->above) ?
            "true" : "false");
    printf("\tdetail %d\n", cev->detail);
    printf("\tsendevent %s\n", (cev->send_event) ?
            "true" : "false");
}
