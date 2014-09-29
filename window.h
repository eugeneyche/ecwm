#ifndef WINDOW_H_
#define WINDOW_H_

#include <X11/Xlib.h>

#include "geometry.h"

class ECWindow
{
private:
    Display*    dpy;
    Window      win;
    Rectangle   geom;

public:
    ECWindow(Display*, Window);
    ~ECWindow();
    
    void map();
    void unmap();

    void configure(unsigned int, XWindowChanges*);
    void move(int, int);
    void resize(int, int);
    void moveResize(int, int, int, int);

    void destroy();
};

#endif /* WINDOW_H_ */
