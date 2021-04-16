#ifndef MYTERM_H
#define MYTERM_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ERR_TERM -1
#define ERR_TERM_SIZE -2
#define TERM "/dev/tty"

enum Colors {
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  Unknown,
  Default
};

int mt_readText(char *text, int size);
int mt_printText(char *text);
int mt_clrscr(void);
int mt_goToXY(int x, int y);
int mt_getScreenSize(int *rows, int *columns);
int mt_setFgColor(enum Colors color);
int mt_setBgColor(enum Colors color);

#endif // MYTERM_H
