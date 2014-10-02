#ifndef CLIENT_H_
#define CLIENT_H_

#include "base.h"
#include "frame.h"

class Client : public BaseWindow
{
private:
    Frame *         frame;

public:
    Client(WindowManager *, Window);
    ~Client(void);

    void map(void);
    void unmap(void);
    
    void configure(unsigned long, XWindowChanges *);

    void move(int, int);
    void resize(int, int);
    void moveResize(int, int, int, int);

    void destroy(void);

    void kill(void);

    void iconify(void);
    void withdraw(void);

    void reparent(void);
    void unreparent(void);
};

#endif /* CLIENT_H_ */
