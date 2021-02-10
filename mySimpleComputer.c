// #ifndef MY_SIMPLE_COMPUTER_H
// #define MY_SIMPLE_COMPUTER_H
#include <stdio.h>
#include <stdlib.h>

#define MEMORYSIZE 100
#define NUM_OF_COMM 38

#define ERR_WRONG_ADDRESS 1
#define ERR_WRONG_FLAG 1
#define ERR_WRONG_VALUE 1
#define ERR_WRONG_COMMAND 1
#define ERR_WRONG_OPERAND 1

#define FLAG_OVERFLOW 1
#define FLAG_DIV_BY_ZERO 2
#define FLAG_MEMORY_BORDER 3
#define FLAG_IGNOR_PULS 4
#define FLAG_WRONG_COMMAND 5

#define BIT_SET(X, Y) X = X | (1 << (Y - 1)) //устанавалиет единицу
#define BIT_DEL(X, Y) X = X & (~(1 << (Y - 1))) //устанавливает ноль
#define BIT_GET(X, Y) X >> (Y - 1) & 0x1 //возвращает нужный бит
static int sc_memory[MEMORYSIZE];
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
        BIT_DEL(sc_reg, FLAG_MEMORY_BORDER);
        
    } else {
        printf("ERR_WRONG_ADDRESS\n");
        BIT_SET(sc_reg, FLAG_MEMORY_BORDER);
        return ERR_WRONG_ADDRESS;
    }
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if (address >= 0 && address < MEMORYSIZE) {
        *value = sc_memory[address];
        BIT_DEL(sc_reg, FLAG_MEMORY_BORDER);
        
    } else {
        printf("ERR_WRONG_ADDRESS\n");
        BIT_SET(sc_reg, FLAG_MEMORY_BORDER);
        return ERR_WRONG_ADDRESS;
    }
    return 0;
}

int sc_memorySave(char* filename)
{
    FILE* ptrFile = fopen(filename, "wb");
    if (ptrFile != NULL) {
        fwrite(sc_memory, sizeof(int), sizeof(sc_memory), ptrFile);
        fclose(ptrFile);
        return 0;
    } else {
        printf("ERROR: Can't open the file\n");
        return 1;
    }
}

int sc_memoryLoad(char* filename)
{
    FILE* ptrFile = fopen(filename, "rb");
    if (ptrFile != NULL) {
        fread(sc_memory, sizeof(int), sizeof(sc_memory), ptrFile);
        fclose(ptrFile);
        return 0;
    } else {
        printf("ERROR: Can't open the file \n");
        return 1;
    }
}

int sc_regInit()
{
    sc_reg = 0;
    return 0;
}

int sc_regSet(int reg, int value)
{
    if (reg > 0 && reg <= 5) {
        if (value == 1) {
            BIT_SET(sc_reg, reg);
            return 0;
        } else if (value == 0) {
            BIT_DEL(sc_reg, reg);
            return 0;
        } else {
            {
                printf("ERR_WRONG_VALUE\n");
                return ERR_WRONG_VALUE;
            }
        }
    } else {
        printf("ERR_WRONG_FLAG\n");
        return ERR_WRONG_FLAG;
    }
}

int sc_regGet(int reg, int* value)
{
    if (reg > 0 && reg <= 5) {
        *value = BIT_GET(sc_reg, reg);
        return 0;
    } else {
        printf("ERR_WRONG_FLAG\n");
        return ERR_WRONG_FLAG;
    }
}

int sc_commandEncode(int command, int operand, int* value)
{
    // int isCommand = 0;
    // for (int i = 0; i < 38; i++) {
    //     if (command == commands[i]) {
    //         isCommand = 1;
    //         break;
    //     }
    // }
    //
    if (operand >= 0 && operand <= 127) {
        int code = 0;
        code = operand;
        code += (command << 7);
        code = code & (~(1 << 14));
        *value = code;
        BIT_DEL(sc_reg, FLAG_WRONG_COMMAND);
        return 0;
    } else {
        BIT_SET(sc_reg, FLAG_WRONG_COMMAND);
        printf("FLAG_WRONG_COMMAND\n");
        return FLAG_WRONG_COMMAND;
    }
}

int sc_commandDecode(int value, int* command, int* operand)
{
    int commandCheck = BIT_GET(sc_reg, 14);
    if (!commandCheck) {
        *command = (value >> 7);
        for (int i = 0; i < 7; i++) {
            value = value & (~(1 << (i + 7)));
        }
        *operand = value;
        BIT_DEL(sc_reg, FLAG_WRONG_COMMAND);
        return 0;
    } else {
        BIT_SET(sc_reg, FLAG_WRONG_COMMAND);
        printf("FLAG_WRONG_COMMAND\n");
        return FLAG_WRONG_COMMAND;
    }
}

// #endif // MY_SIMPLE_COMPUTER_H