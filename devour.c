#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>

void _fix_path(char** argv, char* upath) {
   while (*++argv) {
      strcat(upath, *argv);
      if (*(argv + 1) != 0) strcat(upath, "\\ ");
   }
}

void run_command(char** argv) {
   char cmd[512] = {0};
   while (*++argv) {
      if (strcmp(*argv, "--") == 0) {
         _fix_path(argv, cmd);
         break;
      }
      strcat(cmd, *argv);
      strcat(cmd, " ");
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
