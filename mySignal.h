#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <signal.h>
#include "mySimpleComputer.h"
#include "myGUI.h"

int ms_setSignals();
int ms_timerHandler(int sig);
int ms_userSignal(int sig);

#endif // MYSIGNAL_H