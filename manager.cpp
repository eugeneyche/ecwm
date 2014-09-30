#include <stdlib.h>
#include <signal.h>

#include "manager.h"

WindowManager::WindowManager()
{
    sigchld();

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display!\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    root = RootWindow(display, screen);
    
    XSelectInput(display, root, SubstructureNotifyMask | SubstructureRedirectMask);
}

WindowManager::~WindowManager()
{
    XCloseDisplay(dpy);
}

void
WindowManager::sigchld()
{
    /* Thank you dwm! */
    if (signal(SIGCHLD, sigchld) == SIG_ERR) {
        fprintf(stderr, "Can't install SIGCHLD handler!\n");
        exit(1);
    }
    while(0 < waitpid(-1, NULL, WNOHANG));
}

void 
WindowManager::start()
{
    XEvent ev;

    running = True;
    while (running && XNextEvent(dpy, &ev) == 0) {
        switch (ev.type) {
        case KeyPress:
            keyPress(&ev);
            break;
        case MapRequest:
            mapRequest(&ev);
            break;
        case DestroyNotify:
            destroyNotify(&ev);
            break;
        case ConfigureNotify:
            configureNotify(&ev);
            break;
        case ConfigureRequest:
            configureRequest(&ev);
            break;
        default:
            /* 
             * Probably want to do something just
             * for debugging purposes... will do so
             * later :-)
             */
            break;
        }
    }
}

Bool
WindowManager::isRunning()
{
    return running;
}

Display *
WindowManager::getDisplay()
{
    return display;
}
