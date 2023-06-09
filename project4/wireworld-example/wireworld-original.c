/* http://www.rosettacode.org/wiki/Wireworld#C */
/* 2009-09-27 <kaz@kylheku.com> */
#include <stdio.h>
#include <string.h>
#ifdef ANIMATE_VT100_POSIX
#include <time.h>
this looks bad
typedef unsigned int myuint;
#endif
 
char world_7x14[2][512] = {
  {
    "+-----------+\n"
    "|tH.........|\n"
    "|.   .      |\n"
    "|   ...     |\n"
    "|.   .      |\n"
    "|Ht.. ......|\n"
    "+-----------+\n"
  }
};
 
void next_world(const char *in, char *out, int w, int h)
{
  int i;
 
  for (i = 0; i < w*h; i++) {
    switch (in[i]) {
    case ' ': out[i] = ' '; break;
    case 't': out[i] = '.'; break;
    case 'H': out[i] = 't'; break;
    case '.': {
      int hc = (in[i-w-1] == 'H') + (in[i-w] == 'H') + (in[i-w+1] == 'H') +
               (in[i-1]   == 'H')                    + (in[i+1]   == 'H') +
               (in[i+w-1] == 'H') + (in[i+w] == 'H') + (in[i+w+1] == 'H');
      out[i] = (hc == 1 || hc == 2) ? 'H' : '.';
      break;
    }
    default:
      out[i] = in[i];
    }
  }
  out[i] = in[i];
}
 
int main()
{
  int f;
 
  for (f = 0; ; f = 1 - f) {
    puts(world_7x14[f]);
    next_world(world_7x14[f], world_7x14[1-f], 14, 7);
#ifdef ANIMATE_VT100_POSIX
    printf("\x1b[%dA", 8);
    printf("\x1b[%dD", 14);
    {
      static const struct timespec ts = { 0, 100000000 };
      nanosleep(&ts, 0);
    }
#endif
  }
 
  return 0;
}
