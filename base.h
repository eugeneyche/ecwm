#ifndef BASE_H_
#define BASE_H_

#include "manager.h"

class Base
{
protected:
    WindowManager * wm;
    Window          window;

    Rectangle       area;

public:
    Base(WindowManager *, Window);
    ~Base(void);

    virtual void map(void);
    virtual void unmap(void);
    
    virtual void configure(unsigned long, XWindowChanges *);

    virtual void move(int, int);
    virtual void resize(int, int);
    virtual void moveResize(int, int, int, int);

    virtual void destroy(void);
};

#endif /* BASE_H_ */
