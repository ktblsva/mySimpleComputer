#ifndef MYGUI_H
#define MYGUI_H

#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"

#define HighlightColor Red 

int cursorX; int cursorY;
int mg_showGUI(int x, int y);
int mg_showKeys(int x, int y);
int mg_showFlags(int x, int y);
int mg_showMemory(int x, int y);
int mg_showBigChars (int x, int y);
int mg_showAccumulator (int x, int y);
int mg_showInstructionCounter (int x, int y);
int mg_showOperation(int x, int y);
int mg_showInputField(int x, int y);

#endif // MYGUI_H