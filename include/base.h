#ifndef BASE_H_
#define BASE_H_

#include "manager.h"
#include "geometry.h"

class BaseWindow
{
protected:
    WindowManager * wm;
    Window          window;

    Rectangle       area;

public:
    BaseWindow(WindowManager *, Window);
    virtual ~BaseWindow(void);

	Window getWindow(void);
    Rectangle getArea(void);

    virtual void map(void);
    virtual void unmap(void);
    
    virtual void configure(unsigned long, XWindowChanges *);

    virtual void move(int, int);
    virtual void resize(int, int);
    virtual void moveResize(int, int, int, int);

    virtual void destroy(void);
};

#endif /* BASE_H_ */
