#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Client Client;
typedef struct Desktop Desktop;

struct Client {
    Client * next;
    Client * prev;

    Window frame;
    Window window;
};

struct Desktop {
    Client* clients;
    Client* fclient;
};

static void die(const char *);
static void sigchld(int);

static void setup(void);
static void start(void);

static void keypress(XEvent *);
static void maprequest(XEvent *);
static void destroynotify(XEvent *);
static void configurenotify(XEvent *);
static void configurerequest(XEvent *);

static Client * windowtoclient(Window);
static void managewindow(Window);
static void unmanagewindow(Window);

static void (* events [LASTEvent])(XEvent *) = {
    [KeyPress] = keypress,
    [MapRequest] = maprequest,
    [DestroyNotify] = destroynotify,
    [ConfigureNotify] = configurenotify,
    [ConfigureRequest] = configurerequest
};

static Bool quit;
static Display * dpy;
static int screen;
static Window root;

static int sw;
static int sh;

static Desktop desktops [9];
static Desktop * fdesktop;

void
die(const char * err)
{
    fprintf(stderr, "ecwm: %s\n", err);
    exit(1);
}

void
sigchld(int unused)
{
    if (signal(SIGCHLD, sigchld) == SIG_ERR)
        die("Can't install SIGCHLD handler");
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

    int i;
    for (i = 0; i < 9; i++) {
        desktops[i].clients = NULL;
        desktops[i].fclient = NULL;
    }

    fdesktop = &desktops[0];

    XSelectInput(dpy, root, SubstructureNotifyMask | SubstructureRedirectMask);
}

void
start(void)
{
    XEvent ev;

    while (!quit && XNextEvent(dpy, &ev) == 0) {
        if (events[ev.type])
            events[ev.type](&ev);
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
    Client * clients;

    printf("maprequest\n");
    XMapRequestEvent * ev = &e->xmaprequest;

    if (windowtoclient(ev->window))
        return;

    managewindow(ev->window);
    XMapWindow(dpy, ev->window);
}

void 
destroynotify(XEvent * e)
{
    printf("destroynotify\n");
    XDestroyWindowEvent * ev = &e->xdestroywindow;
}

void 
configurenotify(XEvent * e)
{
    printf("configurenotify\n");
    /* Do nothing else for now */
}

void 
configurerequest(XEvent * e)
{
    printf("configurerequest\n");
    XConfigureRequestEvent * ev = &e->xconfigurerequest;
    XWindowChanges wc;
    wc.x = ev->x;
    wc.y = ev->y;
    wc.width = ev->width;
    wc.height = ev->height;
    wc.border_width = ev->border_width;
    wc.sibling = ev->above;
    wc.stack_mode = ev->detail;
    XConfigureWindow(dpy, ev->window, ev->value_mask, &wc);
}

Client *
windowtoclient(Window w)
{
    int i;
    Client * c;
    for (i = 0; i < 9; i++) {
        for (c = desktops[i].clients; c; c = c->next) {
            if (c->window == w)
                return c;
        }
    }
    return NULL;
}

void
managewindow(Window w)
{
    Client * c, * t;
    if (windowtoclient(w)) 
        return;

    if (!(c = (Client *)calloc(1, sizeof(Client))))
        die("Error calloc!");

    if (fdesktop->clients == NULL) {
        c->next = NULL;
        c->prev = NULL;
    } else {
        for (t = fdesktop->clients; t->next; t = t->next);

        c->next = NULL;
        c->prev = t;

        t->next = c;
    }

    fdesktop->fclient = c;
}

int
main(int argc, char * argv [])
{
    if (!(dpy = XOpenDisplay(NULL)))
        die("Cannot open display!");

    setup();

    start();

    XCloseDisplay(dpy);

    return 0;
}
