#ifndef CLIENT_H_
#define CLIENT_H_

#include <X11/Xlib.h>

typedef struct Client Client;

struct Client {
    Window frame;
    Window window;

    int x, y;
    int width, height;
    int border_width;
};

Client * windowtoclient(Window);
Client * frametoclient(Window);

Client * manageclient(Window);
void unmanageclient(Client *);
void mapclient(Client *);
void unmapclient(Client *);
void moveclient(Client *, int, int);
void resizeclient(Client *, int, int);
void configureclient(Client *, XWindowChanges);

#endif /* CLIENT_H_ */
