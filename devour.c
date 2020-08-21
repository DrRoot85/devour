#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>

void run_command(char** argv) {
   int is_unsafe = 0;
   char cmd[512] = {0};

   while (*++argv) {
      if (!strcmp(*argv, "--")) {
         is_unsafe = 1;
         continue;
      }
      strcat(cmd, *argv);
      strcat(cmd, is_unsafe && *(argv + 1) != 0 ? "\\ " : " ");
   }
   system(cmd);
}

int main(int argc, char** argv) {
   int rev;
   Window win;
   Display* dis = XOpenDisplay(0);

   XGetInputFocus(dis, &win, &rev);
   XUnmapWindow(dis, win);
   XFlush(dis);
   run_command(argv);
   XMapWindow(dis, win);
   XCloseDisplay(dis);
   return 0;
}
