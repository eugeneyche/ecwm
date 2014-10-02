#ifndef FRAME_H_
#define FRAME_H_

#include "base.h"

class Frame : public BaseWindow
{
private:
    Client *        client;

	Rectangle frameAreaToClientArea(Rectangle);
	Rectangle clientAreaToFrameArea(Rectangle);

public:
    Frame(WindowManager *, Client *);
    ~Frame(void);

	void fitClient(void);
};

#endif /* FRAME_H_ */
