#include <stdio.h>
#include "manager.h"
#include "base.h"
#include "client.h"

void
WindowManager::keyPress(XEvent * ev)
{
    printf("> keyPress\n");
}

void
WindowManager::mapRequest(XEvent * ev)
{
    XMapRequestEvent * mev;
	BaseWindow * base;

	mev = &ev->xmaprequest;

    printf("> mapRequest\n");
    printf("\twindow: %ld\n", mev->window);

	base = windowToBaseWindow(mev->window);
	if (!base) {
		base = new Client(this, mev->window);
		registerBaseWindow(base);
	}
	base->map();
}

void
WindowManager::destroyNotify(XEvent * ev)
{
    XDestroyWindowEvent * dev;
	BaseWindow * base;

    dev = &ev->xdestroywindow;

    printf("> destroyNotify\n");
    printf("\twindow: %ld\n", dev->window);
    printf("\tevent: %ld\n", dev->event);
	
	base = windowToBaseWindow(dev->window);
	if (base) {
		unregisterBaseWindow(base);
		delete base;
	}
}

void
WindowManager::configureNotify(XEvent * ev)
{
    XConfigureEvent * cev;
	BaseWindow * base;

	unsigned long attrmask;
	XWindowChanges wc;

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

	/* Do nothing for now */
}

void
WindowManager::configureRequest(XEvent * ev)
{
    XConfigureRequestEvent * cev;
	BaseWindow * base;

	unsigned long attrmask;
	XWindowChanges wc;

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

	attrmask = CWX | CWY | CWWidth | CWHeight;
	wc.x = cev->x;
	wc.y = cev->y;
	wc.width = cev->width;
	wc.height = cev->height;

	base = windowToBaseWindow(cev->window);
	if (base) {
		base->configure(attrmask, &wc);
	} else {
		XConfigureWindow(display, cev->window, attrmask, &wc);
	}
}
