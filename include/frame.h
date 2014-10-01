#ifndef FRAME_H_
#define FRAME_H_

#include "base.h"

class Frame : public Base
{
private:
    Client *        client;

	Rectangle frameAreaToClientArea(Rectangle);

public:
    Frame(WindowManager *, Client *);
    ~Frame(void);

    void map(void);
    void unmap(void);
    
    void configure(unsigned long, XWindowChanges *);

    void move(int, int);
    void resize(int, int);
    void moveResize(int, int, int, int);

    void destroy(void);

	void fitClient(void);
};

#endif /* FRAME_H_ */
