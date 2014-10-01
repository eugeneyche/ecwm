#include "frame.h"

Frame::Frame(WindowManager * wm, Client * client) :
		BaseWindow (wm, None), client (client)
{ }

Frame::~Frame()
{ }

void
Frame::map()
{ }

void
Frame::unmap()
{ }

void
Frame::configure(unsigned long attrmask, XWindowChanges *)
{ }

void 
Frame::move(int x, int y)
{ }

void
Frame::resize(int width, int height)
{ }

void
Frame::moveResize(int x, int y, int width, int height)
{ }

void
Frame::destroy()
{ }

void
Frame::fitClient()
{ }

Rectangle
Frame::frameAreaToClientArea(Rectangle frameArea)
{ 
	Rectangle clientArea;
	return clientArea;
}
