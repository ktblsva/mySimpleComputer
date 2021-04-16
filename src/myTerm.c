#include "myTerm.h"

int mt_readText(char *text,int size) {
  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  int numRead = read(terminal, text, size);
  text[numRead] = '\0';
  return 0;
}

int mt_printText(char *text) {
  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  write(terminal, text, strlen(text));
  close(terminal);
  return 0;
}

int mt_clrscr() {
  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  write(terminal, "\E[H\E[2J", sizeof("\E[H\E[2J"));
  close(terminal);
  return 0;
}

int mt_getScreenSize(int *rows, int *columns) {
  struct winsize {
    unsigned short row;
    unsigned short col;
    unsigned short xpixel;
    unsigned short ypixel;
  };
  
  struct winsize ws;

  if (!ioctl(1, TIOCGWINSZ, &ws)) {
    *rows = ws.row;
    *columns = ws.col;
    return 0;
  } else {
    return ERR_TERM_SIZE;
  }
}

int mt_goToXY(int x, int y) {
  int row, col;
  mt_getScreenSize(&row, &col);

  if (((x > col) || (x < 0)) || ((y > row) || (y < 0))) {
    return ERR_TERM_SIZE;
  }

  char buff[50];
  sprintf(buff, "\E[%d;%dH", y, x);

  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  write(terminal, buff, strlen(buff));
  close(terminal);
  return 0;
}

int mt_setFgColor(enum Colors color) {
  char buff[50];
  sprintf(buff, "\E[0;3%dm", color);

  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  write(terminal, buff, strlen(buff));
  close(terminal);
  return 0;
}

int mt_setBgColor(enum Colors color) {
  char buff[50];
  sprintf(buff, "\E[4%dm", color);

  int terminal = open(TERM, O_RDWR);
  if (terminal == -1) {
    return ERR_TERM;
  }
  write(terminal, buff, strlen(buff));
  close(terminal);
  return 0;
}