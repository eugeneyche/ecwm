#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "client.h"

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static void bindclient(Client * c);

extern Display * dpy;
extern int screen;
extern Window root;

static map<Window, Client *> windows;
static map<Window, Client *> frames;

Client * 
windowtoclient(Window w)
{
    return windows[w];
}

Client * 
frametoclient(Window w)
{
    return frames[w];
}

void
bindclient(Client * c)
{
    XWindowAttributes wa;
    XWindowChanges wc; 
    unsigned int attrmask; 

    printf("> bindclient\n");
    wc.x = 5;
    wc.y = 5;
    wc.width = MAX(1, c->width - 10);
    wc.height = MAX(1, c->height - 10);
    wc.border_width = 0;

    attrmask = CWX | CWY | CWWidth | CWHeight | CWBorderWidth;

    XConfigureWindow(dpy, c->window, attrmask, &wc);
}

Client *
manageclient(Window w)
{
    Client * c;
    XWindowAttributes wa;
    XSetWindowAttributes swa;
    unsigned long attrmask;

    printf("> createclient\n");

    if ((c = (Client *)malloc(sizeof(Client))) == 0) {
        fprintf(stderr, "Failed to malloc!\n");
        exit(1);
    }

    XGetWindowAttributes(dpy, w, &wa);

    swa.border_pixel = WhitePixel(dpy, screen);
    swa.background_pixel = BlackPixel(dpy, screen);
    swa.override_redirect = True;

    attrmask = CWBackPixel | CWBorderPixel | CWOverrideRedirect;

    c->x = wa.x;
    c->y = wa.y;
    c->width = wa.width;
    c->height = wa.height;
    c->border_width = 5;


    c->window = w;
    c->frame = XCreateWindow(dpy, root,
            c->x, c->y, c->width, c->height, 5,
            DefaultDepth(dpy, screen), InputOutput,
            CopyFromParent, attrmask, &swa);

    bindclient(c);

    printf("\twindow: %d\n", c->window);
    printf("\tframe: %d\n", c->frame);

    XAddToSaveSet(dpy, c->window);
    XReparentWindow(dpy, c->window, c->frame, 0, 0);
    XSelectInput(dpy, c->frame, SubstructureNotifyMask | SubstructureRedirectMask);

    windows[c->window] = c;
    frames[c->frame] = c;

    XMapWindow(dpy, c->window);
    XMapWindow(dpy, c->frame);

    return c;
}

void
unmanageclient(Client * c)
{
    printf("> destroyclient\n");
    XDestroyWindow(dpy, c->frame);

    windows.erase(c->window);
    frames.erase(c->frame);
    free(c);
}

void 
unmapclient(Client * c)
{
    printf("> unmapclient\n");
    XUnmapWindow(dpy, c->window);
    XUnmapWindow(dpy, c->frame);
}

void 
moveclient(Client * c, int x, int y)
{
    printf("> moveclient\n");
    XMoveWindow(dpy, c->window, x, y);    
    XMoveWindow(dpy, c->frame, x, y);    
}

void 
resizeclient(Client * c, int width, int height)
{
    printf("> resizeclient\n");
    XResizeWindow(dpy, c->window, width, height);    
    XResizeWindow(dpy, c->frame, width, height);    
}

void
configureclient(Client * c, XWindowChanges wc)
{
    printf("> configureclient\n");
    unsigned int attrmask; 

    attrmask = CWX | CWY | CWWidth | CWHeight | CWSibling | CWStackMode;

    c->x = wc.x;
    c->y = wc.y;
    c->width = wc.width;
    c->height = wc.height;
    c->border_width = 5;

    bindclient(c);
    XConfigureWindow(dpy, c->frame, attrmask, &wc);
}
