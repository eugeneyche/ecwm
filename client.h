#ifndef CLIENT_H_
#define CLIENT_H_

#include "manager.h"
#include "geometry.h"

class Client : public Base
{
private:
    Frame *         frame;

public:
    Client(WindowManager *, Window);
    ~Client(void);

    void kill(void);

    void iconify(void);
    void withdraw(void);

    void reparent(void);
    void unreparent(void);
};

#endif /* CLIENT_H_ */
