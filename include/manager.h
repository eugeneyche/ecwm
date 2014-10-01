#ifndef MANAGER_H_
#define MANAGER_H_

#include <X11/Xlib.h>
#include <map>

class BaseWindow;
class Client;
class Frame;

class WindowManager
{
private:
    Bool            running;

    Display *       display;
    int             screen;
    Window          root;

	std::map<Window, BaseWindow *> windowMap;

    void keyPress(XEvent *);
    void mapRequest(XEvent *);
    void destroyNotify(XEvent *);
    void configureNotify(XEvent *);
    void configureRequest(XEvent *);

	void registerBaseWindow(BaseWindow *);
	void unregisterBaseWindow(BaseWindow *);

public:
    WindowManager(void);
    ~WindowManager(void);

    void start(void);

    Display * getDisplay(void);
	BaseWindow * windowToBaseWindow(Window);
};

#endif /* MANAGER_H_ */
