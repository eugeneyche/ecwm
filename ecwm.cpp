#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Client Client;
typedef struct Desktop Desktop;

static void sigchld(int);

static void setup(void);
static void start(void);

static void keypress(XEvent *);
static void maprequest(XEvent *);
static void destroynotify(XEvent *);
static void configurenotify(XEvent *);
static void configurerequest(XEvent *);

static Bool quit;
Display * dpy;
int screen;
Window root;

static int sw;
static int sh;

void
sigchld(int unused)
{
    if (signal(SIGCHLD, sigchld) == SIG_ERR) {
        fprintf(stderr, "Can't install SIGCHLD handler\n");
        exit(1);
    }
    while (0 < waitpid(-1, NULL, WNOHANG));
}

void
setup(void)
{
    sigchld(0);

    screen = DefaultScreen(dpy);
    root = RootWindow(dpy, screen);

    sw = XDisplayWidth(dpy, screen);
    sh = XDisplayHeight(dpy, screen);

    XSelectInput(dpy, root, SubstructureNotifyMask | SubstructureRedirectMask);
}

void
start(void)
{
    XEvent ev;

    while (!quit && XNextEvent(dpy, &ev) == 0) {
        switch(ev.type) {
        case KeyPress:
            keypress(&ev);
            break;
        case MapRequest:
            maprequest(&ev);
            break;
        case DestroyNotify:
            destroynotify(&ev);
            break;
        case ConfigureNotify:
            configurenotify(&ev);
            break;
        case ConfigureRequest:
            configurerequest(&ev);
            break;
        }
    }
}

void 
keypress(XEvent * e)
{
    printf("keypress\n");
}

void 
maprequest(XEvent * e)
{
    Client * c;
    XMapRequestEvent * ev;

    ev = &e->xmaprequest;

    printf("maprequest\n");
    printf("\twindow: %ld\n", ev->window);

}

void 
destroynotify(XEvent * e)
{
    XDestroyWindowEvent * ev;
    Client * c;

    ev = &e->xdestroywindow;

    printf("destroynotify\n");
    printf("\twindow: %ld\n", ev->window);
    printf("\tevent: %ld\n", ev->event);
}

void 
configurenotify(XEvent * e)
{
    Client * c;
    XConfigureEvent * ev;

    ev = &e->xconfigure;

    printf("configurenotify\n");
    printf("\twindow: %ld\n", ev->window);
    printf("\tx, y, w, h: %d %d %d %d\n", ev->x, ev->y, ev->width, ev->height);
    printf("\tbw: %d\n", ev->border_width);
    printf("\tabove?: %d\n", ev->above);
    printf("\toverride?: %d\n", ev->override_redirect);
}

void 
configurerequest(XEvent * e)
{
    Client * c;
    XConfigureRequestEvent * ev;
    XWindowChanges wc;
    unsigned long attr;

    ev = &e->xconfigurerequest;

    printf("configurerequest\n");
    printf("\twindow: %ld\n", ev->window);
    printf("\tx, y, w, h: %d %d %d %d\n", ev->x, ev->y, ev->width, ev->height);
    printf("\tbw: %d\n", ev->border_width);
    printf("\tabove?: %d\n", ev->above);
    printf("\tdetail: %d\n", ev->detail);
    printf("\tsendevent: %ld\n", ev->send_event);

    attr = CWX | CWY | CWWidth | CWHeight;

    wc.x = ev->x;
    wc.y = ev->y;
    wc.width = ev->width;
    wc.height = ev->height;

    // if window is not currently managed, just pipe the request directly 
    XConfigureWindow(dpy, ev->window, attr, &wc);
}

int
main(int argc, char * argv [])
{
    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display!\n");
        exit(1);
    }

    setup();

    start();

    XCloseDisplay(dpy);

    return 0;
}
