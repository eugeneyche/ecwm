#ifndef FRAME_H_
#define FRAME_H_

class Frame : public Base
{
private:
    Client *        client;

public:
    Frame(WindowManager *, Client *);
    ~Frame(void);

};

#endif /* FRAME_H_ */
