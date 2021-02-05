#ifndef MY_SIMPLE_COMPUTER_H
#define MY_SIMPLE_COMPUTER_H
#include <stdio.h>
#include <stdlib.h>

#define MEMORYSIZE 100
#define NUM_OF_COMM 38

#define ERR_WRONG_ADDRESS -1
#define ERR_WRONG_FLAG -1
#define ERR_WRONG_VALUE -1
#define ERR_WRONG_COMMAND -1
#define ERR_WRONG_OPERAND -1

#define BIT_SET(X, Y) X = X | (1 << (Y - 1)) //устанавалиет единицу
#define BIT_DEL(X, Y) X = X & (~(1 << (Y - 1))) //устанавливает ноль
#define BIT_GET(X, Y) X >> (Y - 1) & 0x1 //возвращает нужный бит
int sc_memory[MEMORYSIZE];
int sc_reg;
int commands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41,
                  0x42, 0x43, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
                  0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
                  0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76};

int sc_memoryInit()
{
    for (int i = 0; i < MEMORYSIZE; i++) {
        sc_memory[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address >= 0 && address < MEMORYSIZE) {
        sc_memory[address] = value;
        return 0;
    } else
        return ERR_WRONG_ADDRESS;
}

int sc_memoryGet(int address, int* value)
{
    if (address >= 0 && address < MEMORYSIZE) {
        *value = sc_memory[address];
        return 0;
    } else
        return ERR_WRONG_ADDRESS;
}

int sc_memorySave(char* filename)
{
    FILE* ptrFile = fopen(filename, "wb");
    if (ptrFile != NULL) {
        fwrite(sc_memory, sizeof(int), sizeof(sc_memory), ptrFile);
        fclose(ptrFile);
        return 0;
    }
}

int sc_memoryLoad(char* filename)
{
    FILE* ptrFile = fopen(filename, "rb");
    if (ptrFile != NULL) {
        fread(sc_memory, sizeof(int), sizeof(sc_memory), ptrFile);
        fclose(ptrFile);
        return 0;
    }
}

int sc_regInit()
{
    sc_reg = 0;
    return 0;
}

int sc_regSet(int reg, int value)
{
    if (reg >= 0 && reg < 5) {
        if (value == 1) {
            BIT_SET(sc_reg, reg);
        } else if (value == 0) {
            BIT_DEL(sc_reg, reg);
        } else {
            return ERR_WRONG_VALUE;
        }
    } else {
        return ERR_WRONG_FLAG;
    }
}

int sc_regGet(int reg, int* value)
{
    if (reg >= 0 && reg < 5) {
        *value = BIT_GET(sc_reg, reg);
        return 0;
    } else {
        return ERR_WRONG_FLAG;
    }
}

int int_cmp(const void* a, const void* b)
{
    if (*(int*)a < *(int*)b)
        return -1;
    else if (*(int*)a > *(int*)b)
        return 1;
    else
        return 0;
}

int sc_commandEncode(int command, int operand, int* value)
{
    void* command_ptr;
    command_ptr
            = bsearch(&command, commands, NUM_OF_COMM, sizeof(int), int_cmp);
    if (command_ptr) {
        printf("!!!\n");
    }
    
}
#endif // MY_SIMPLE_COMPUTER_H