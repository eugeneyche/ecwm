#include <stdio.h>
#include "manager.h"
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
	Client * client;
    XWindowAttributes wa;

	mev = &ev->xmaprequest;

    printf("> mapRequest\n");
    printf("\twindow: %ld\n", mev->window);

    if (!XGetWindowAttributes(display, mev->window, &wa)) {
        return;
    }
    if (wa.override_redirect) {
        return;
    }
	client = windowToClient(mev->window);
	if (!client) {
		client = new Client(this, mev->window);
		registerClient(client);
	}
	client->map();
}

void
WindowManager::destroyNotify(XEvent * ev)
{
    XDestroyWindowEvent * dev;
	Client * client;

    dev = &ev->xdestroywindow;

    printf("> destroyNotify\n");
    printf("\twindow: %ld\n", dev->window);
    printf("\tevent: %ld\n", dev->event);
	
	client = windowToClient(dev->window);
	if (client) {
		unregisterClient(client);
		delete client;
	}
}

void
WindowManager::configureNotify(XEvent * ev)
{
    XConfigureEvent * cev;
	Client * client;

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
	Client * client;

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

	attrmask = cev->value_mask & (CWX | CWY | CWWidth | CWHeight);
	wc.x = cev->x;
	wc.y = cev->y;
	wc.width = cev->width;
	wc.height = cev->height;

	client = windowToClient(cev->window);
	if (client) {
		client->configure(attrmask, &wc);
	} else {
		XConfigureWindow(display, cev->window, attrmask, &wc);
	}
}
