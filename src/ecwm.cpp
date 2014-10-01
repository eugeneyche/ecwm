#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "manager.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

WindowManager wm;
int
main(int argc, char * argv [])
{
    wm.start();
}
