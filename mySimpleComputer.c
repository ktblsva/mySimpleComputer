#include "mySimpleComputer.h"
int sc_commands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x52, 0x55};

int sc_memoryInit() {
  for (int i = 0; i < MEMORYSIZE; i++) {
    sc_memory[i] = 0;
  }
  return 0;
}

int sc_memorySet(int address, int value) {
  if (address >= 0 && address < MEMORYSIZE) {
    sc_memory[address] = value;
    return 0;

  } else {
    sc_addOutput("ERR_WRONG_ADDRESS\n");
    BIT_SET(sc_reg, FLAG_WRONG_ADDRESS);
    return ERR_WRONG_ADDRESS;
  }
}

int sc_memoryGet(int address, int *value) {
  if (address >= 0 && address < MEMORYSIZE) {
    *value = sc_memory[address];
    return 0;

  } else {
    sc_addOutput("ERR_WRONG_ADDRESS\n");
    BIT_SET(sc_reg, FLAG_WRONG_ADDRESS);
    return ERR_WRONG_ADDRESS;
  }
}

int sc_memorySave(char *filename) {
  FILE *ptrFile = fopen(filename, "wb");
  if (ptrFile != NULL) {
    fwrite(sc_memory, sizeof(int), sizeof(sc_memory) / sizeof(int), ptrFile);
    fclose(ptrFile);
    return 0;
  } else {
    sc_addOutput("ERROR: Can't open the file\n");
    return 1;
  }
}

int sc_memoryLoad(char *filename) {
  FILE *ptrFile = fopen(filename, "rb");
  if (ptrFile != NULL) {
    fread(sc_memory, sizeof(int), sizeof(sc_memory) / sizeof(int), ptrFile);
    fclose(ptrFile);
    return 0;
  } else {
    sc_addOutput("ERROR: Can't open the file \n");
    return 1;
  }
}

int sc_regInit() {
  sc_reg = 0;
  return 0;
}

int sc_regSet(int reg, int value) {
  if ((reg > 0) && (reg <= 5)) {
    if (value) {
      if (value == 1) {
        BIT_SET(sc_reg, reg);
        return 0;
      } else {
        sc_addOutput("ERR_WRONG_VALUE\n");
        BIT_SET(sc_reg, FLAG_OVERFLOW);
        return ERR_WRONG_VALUE;
      }
    } else {
      BIT_DEL(sc_reg, reg);
      return 0;
    }

  } else {
    sc_addOutput("ERR_WRONG_FLAG\n");
    return ERR_WRONG_FLAG;
  }
}

int sc_regGet(int reg, int *value) {
  if ((reg > 0) && (reg <= 5)) {
    *value = BIT_GET(sc_reg, reg);
    return 0;
  } else {
    printf("ERR_WRONG_FLAG\n");
    return ERR_WRONG_FLAG;
  }
}

int sc_commandEncode(int command, int operand, int *value) {
  int isCommand = 0;

  for (int i = 0; i < 14; i++)
  {
    if (command == sc_commands[i])
    {
      isCommand = 1;
    }
  }



  if (isCommand) {
    if ((operand >= 0) && (operand < 128)) {
      int code = operand;
      code += (command << 7);
      code = code & (~(1 << 14));
      *value = code;
      return 0;
    } else {
      //printf("ERR_WRONG_VALUE\n");
      sc_addOutput("ERR_WRONG_VALUE");
      sc_regSet(ERR_WRONG_VALUE, 1);
      return ERR_WRONG_VALUE;
    }
  } else {
    //printf("ERR_WRONG_COMMAND\n");
    sc_addOutput("ERR_WRONG_COMMAND");
    sc_regSet(FLAG_WRONG_COMMAND,1);
    return ERR_WRONG_COMMAND;
  }
}

int sc_commandDecode(int value, int *command, int *operand) {
  int notCommand = BIT_GET(sc_reg, 14);

  if (!notCommand) {
    *command = (value >> 7);
    value -= ((value >> 7) << 7);
    *operand = value;
    return 0;
  } else {
   // printf("ERR_WRONG_COMMAND\n");
    sc_addOutput("ERR_WRONG_COMMAND");
    sc_regSet(ERR_WRONG_COMMAND, 1);
    return ERR_WRONG_COMMAND;
  }
}

char** sc_outputs = NULL;

int sc_addOutput(char* output)
{

  if (sc_outputs == NULL)
  {
    sc_outputs = (char**)malloc(sizeof(char*) * 3);
    sc_outputs[3] = (char*)malloc(sizeof(char) * 255);
    sc_outputs[2] = (char*)malloc(sizeof(char) * 255);
    sc_outputs[1] = (char*)malloc(sizeof(char)* 255);
  }

  sc_outputs[3] = sc_outputs[2];
  sc_outputs[2] = sc_outputs[1];
  sc_outputs[1] = (char*)malloc(sizeof(char)* 255);
  sprintf(sc_outputs[1],"%s",output);
  //sc_outputs[1] = output;
}
