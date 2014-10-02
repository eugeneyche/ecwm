#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "manager.h"
#include "client.h"

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
	std::map<Window, Client *>::iterator i;
	for (i = clientMap.begin(); i != clientMap.end(); i++) {
		if (i->second) {
			delete i->second;
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

Window
WindowManager::getScreen()
{
    return screen;
}

Window
WindowManager::getRoot()
{
    return root;
}

void
WindowManager::registerClient(Client * client)
{
	clientMap[client->getWindow()] = client;
}

void
WindowManager::unregisterClient(Client * client)
{
	clientMap.erase(client->getWindow());
}

Client *
WindowManager::windowToClient(Window window)
{
	return clientMap[window];
}
