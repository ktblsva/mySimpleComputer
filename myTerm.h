#ifndef MYTERM_H
#define MYTERM_H

#define TERM "/dev/tty3"
#define ERR_TERM -1

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

enum Colors // FGCOLOR
{ BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  UNKNOWN,
  DEFAULT
};

int mt_clrscr(void) {
  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    fprintf(stderr, "Can't open the terminal!");
    return ERR_TERM;
  }
  write(terminal, "\E[H\E[2J", sizeof("\E[H\E[2J"));
  close(terminal);
  return 0;
}

int mt_gotoXY(int rows, int columns);

int mt_getscreensize(int *rows, int *columns); //53 страница

int mt_setfgcolor(enum Colors color);
int mt_setbgcolor(enum Colors color);

#endif 