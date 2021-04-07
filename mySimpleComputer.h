#ifndef MY_SIMPLE_COMPUTER_H
#define MY_SIMPLE_COMPUTER_H
#include <stdio.h>
#include <stdlib.h>

#define MEMORYSIZE 100
#define NUM_OF_COMM 38

#define FLAG_WRONG_COMMAND 5
#define FLAG_IGNOR_PULS 4
#define FLAG_WRONG_ADDRESS 3
#define FLAG_DIV_BY_ZERO 2
#define FLAG_OVERFLOW 1

#define ERR_WRONG_ADDRESS -1
#define ERR_WRONG_FLAG -2
#define ERR_WRONG_VALUE -3
#define ERR_WRONG_COMMAND -4
#define ERR_WRONG_OPERAND -5

#define BIT_SET(X, Y) X = X | (1 << (Y - 1)) //устанавалиет единицу
#define BIT_DEL(X, Y) X = X & (~(1 << (Y - 1))) //устанавливает ноль
#define BIT_GET(X, Y) X >> (Y - 1) & 0x1 //возвращает нужный бит
int sc_instructionCounter;
int sc_accumulator;
int sc_memory[MEMORYSIZE];
int sc_reg;
extern int sc_commands[];

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
#endif // MY_SIMPLE_COMPUTER_H
