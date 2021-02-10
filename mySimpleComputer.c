#include "mySimpleComputer.h"
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

    } else {
        printf("ERR_WRONG_ADDRESS\n");
        BIT_SET(sc_reg, FLAG_WRONG_ADDRESS);
        return ERR_WRONG_ADDRESS;
    }
}

int sc_memoryGet(int address, int* value)
{
    if (address >= 0 && address < MEMORYSIZE) {
        *value = sc_memory[address];
        return 0;

    } else {
        printf("ERR_WRONG_ADDRESS\n");
        BIT_SET(sc_reg, FLAG_WRONG_ADDRESS);
        return ERR_WRONG_ADDRESS;
    }
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
    if ((reg > 0) && (reg <= 5)) {
        if (value) {
            if (value == 1) {
                BIT_SET(sc_reg, reg);
                return 0;
            } else {
                printf("ERR_WRONG_VALUE\n");
                BIT_SET(sc_reg, FLAG_OVERFLOW);
                return ERR_WRONG_VALUE;
            }
        } else {
            BIT_DEL(sc_reg, reg);
            return 0;
        }

    } else {
        printf("ERR_WRONG_FLAG\n");
        return ERR_WRONG_FLAG;
    }
}

int sc_regGet(int reg, int* value)
{
    if ((reg > 0) && (reg <= 5)) {
        *value = BIT_GET(sc_reg, reg);
        return 0;
    } else {
        printf("ERR_WRONG_FLAG\n");
        return ERR_WRONG_FLAG;
    }
}

int sc_commandEncode(int command, int operand, int* value)
{
    int isCommand = 1;

    if (isCommand) {
        if ((operand >= 0) && (operand < 128)) {
            int code = operand;
            code += (command << 7);
            code = code & (~(1 << 14));
            *value = code;
            return 0;
        } else {
            printf("ERR_WRONG_VALUE\n");
            sc_regSet(ERR_WRONG_VALUE, 1);
            return ERR_WRONG_VALUE;
        }
    } else {
        printf("ERR_WRONG_COMMAND\n");
        BIT_SET(sc_reg, FLAG_WRONG_COMMAND);
        return ERR_WRONG_COMMAND;
    }
}

int sc_commandDecode(int value, int* command, int* operand)
{
    int notCommand = BIT_GET(sc_reg, 14);

    if (!notCommand) {
        *command = (value >> 7);
        value -= ((value >> 7) << 7);
        *operand = value;
        return 0;
    } else {
        printf("ERR_WRONG_COMMAND\n");
        sc_regSet(ERR_WRONG_COMMAND, 1);
        return ERR_WRONG_COMMAND;
    }
}
