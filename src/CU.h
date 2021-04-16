#ifndef CU_H
#define CU_H
#include "mySimpleComputer.h"
#include "ALU.h"
#include "myGUI.h"
#include "myTerm.h"
#include "string.h"

int READ(int operand);
int WRITE(int operand);
int LOAD(int operand);
int STORE(int operand);
int JUMP(int operand);
int JNEG(int operand);
int JZ(int operand);
int HALT();
int JNS(int operand);
int CU();


#endif // CU_H