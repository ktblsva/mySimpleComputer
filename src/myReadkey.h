#ifndef MYREADKEY_H
#define MYREADKEY_H
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "myTerm.h"

#define ERR_TERM -1
enum keys {
	KEY_l,
	KEY_s,
	KEY_r,
	KEY_t,
	KEY_i,
	KEY_q,
	KEY_f5,
	KEY_f6,
	KEY_up,
	KEY_down,
	KEY_left,
	KEY_right,
	KEY_enter,
	KEY_unknown
};
int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
#endif /*MYREADKEY_H */
