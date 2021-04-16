#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myTerm.h"

#include <unistd.h>
#include <fcntl.h>

#define ERR_TERM -1
#define ERR_WRITE -2
#define ERR_READ -3

#define LT "┌" // left top
#define LB "└" // left bottom
#define RT "┐" // right top
#define RB "┘" // right bottom
#define VL "│" // vert line
#define HL "─" // horis line

extern char bc_char_plus[];
extern char bc_char_minus[];
extern char bc_char_0[];
extern char bc_char_1[];
extern char bc_char_2[];
extern char bc_char_3[];
extern char bc_char_4[];
extern char bc_char_5[];
extern char bc_char_6[];
extern char bc_char_7[];
extern char bc_char_8[];
extern char bc_char_9[];
extern char bc_char_A[];
extern char bc_char_B[];
extern char bc_char_C[];
extern char bc_char_D[];
extern char bc_char_E[];
extern char bc_char_F[];
int bc_panel(int left, int top, int width, int height);
int bc_setBigCharPosition(int *big, int x, int y, int value);
int bc_getBigCharPosition(int *big, int x, int y, int *value);
int bc_printBigChar(int *big, int x, int y, enum Colors fg, enum Colors bg);
int bc_arrayToBig(int *big, char *arr);
int bc_writeBigChar(int fd, int* big, int count);
int bc_readBigChar(int fd, int* big, int need_count, int *count);

#endif // MYBIGCHARS_H
