#ifndef MANAGER_H_
#define MANAGER_H_

#include <X11/Xlib.h>
#include <map>

class Client;
class Frame;

class WindowManager
{
private:
    Bool            running;

    Display *       display;
    int             screen;
    Window          root;

	std::map<Window, Client *> clientMap;

    void keyPress(XEvent *);
    void mapRequest(XEvent *);
    void destroyNotify(XEvent *);
    void configureNotify(XEvent *);
    void configureRequest(XEvent *);

public:
    WindowManager(void);
    ~WindowManager(void);

    void start(void);

    Display * getDisplay(void);
    Window getScreen(void);
    Window getRoot(void);
	Client * windowToClient(Window);

	void registerClient(Client *);
	void unregisterClient(Client *);
};

#endif /* MANAGER_H_ */
