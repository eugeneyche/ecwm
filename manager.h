#ifndef MANAGER_H_
#define MANAGER_H_

#include <X11/Xlib.h>

class WindowManager
{
private:
    Bool            running;

    Display *       display;
    int             screen;
    Window          root;

    void sigchld(void);

    void keyPress(XEvent *);
    void mapRequest(XEvent *);
    void destroyNotify(XEvent *);
    void configureNotify(XEvent *);
    void configureRequest(XEvent *);

public:
    WindowManager(void);
    ~WindowManager(void);

    void start(void);

    Bool isRunning(void);
    Display * getDisplay(void);
};

#endif /* MANAGER_H_ */
