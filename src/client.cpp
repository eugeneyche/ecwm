#include "client.h"

Client::Client(WindowManager * wm, Window window) :
        BaseWindow (wm, window), frame (NULL)
{ }

Client::~Client()
{ }

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
