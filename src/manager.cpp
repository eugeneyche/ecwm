#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "manager.h"
#include "base.h"

void 
sigchld(int unused)
{
    if (signal(SIGCHLD, sigchld) == SIG_ERR) {
        fprintf(stderr, "Can't install SIGCHLD handler!\n");
        exit(1);
    }
    while(0 < waitpid(-1, NULL, WNOHANG));
}

WindowManager::WindowManager()
{
    sigchld(0);

    if (!(display = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display!\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    root = RootWindow(display, screen);
    
    XSelectInput(display, root, SubstructureNotifyMask | SubstructureRedirectMask);
}

WindowManager::~WindowManager()
{
	std::map<Window, BaseWindow *>::iterator i;
	for (i = windowMap.begin(); i != windowMap.end(); i++) {
		if (i->second) {
			BaseWindow * toDelete = i->second;
			delete toDelete;
		}
	}
    XCloseDisplay(display);
}

void 
WindowManager::start()
{
    XEvent ev;

    running = True;
    while (running && XNextEvent(display, &ev) == 0) {
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

Display *
WindowManager::getDisplay()
{
    return display;
}

void
WindowManager::registerBaseWindow(BaseWindow * base)
{
	windowMap[base->getWindow()] = base;
}

void
WindowManager::unregisterBaseWindow(BaseWindow * base)
{
	windowMap.erase(base->getWindow());
}

BaseWindow *
WindowManager::windowToBaseWindow(Window window)
{
	return windowMap[window];
}
