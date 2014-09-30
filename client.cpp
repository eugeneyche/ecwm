#include "client.h"

Client::Client(WindowManager * wm, Window window) :
        Base (wm, window), frame (NULL)
{ }

Client::~Client()
{
    /* 
     * Need to unpair the client and
     * the frame if there is one. Also needs
     * to do so in a manner that does not 
     * compromise the original window, to
     * comply with Xlib conventions.
     */
}

void
Client::kill()
{ }

void
Client::iconify()
{ }

void
Client::withdraw()
{ }

void
Client::reparent()
{ }

void
Client::unreparent()
{ }
