
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <time.h>

int showMemory(int x, int y) {

  int width = 10 * 5 + 9 + 2;
  // int height = 11;
  // mt_goToXY(x + width / 2 - 3 + 1, y);
  int wid, heig;
  mt_getScreenSize(&wid, &heig);
  printf("%d x %d \n", wid, heig);
  printf("1: %d ", mt_goToXY(x + width / 2 - 3 + 1, y));
  mt_printText("Memory");
  int cell = 0;
  for (int i = 1; i < 11; i++) {
    printf("2: %d ", mt_goToXY(2 + x, y + i + 1));
    for (int j = 1; j < 11; j++) {
      char buff[6];
      int value;
      sc_memoryGet(cell, &value);
      cell++;
      sprintf(buff, "+%.4i", value);
      mt_printText(buff);
      if (j != 10) {
        mt_printText(" ");
      }
    }
  }

  mt_printText("\n");
  return 0;
}

int main() {
  srand(time(NULL));
  sc_memoryInit();
  for (int i = 0; i < MEMORYSIZE; i++) {
    sc_memorySet(i, rand() % 100);
  }
  sc_memorySave("sc_memory.txt");
  int value = 0;
  int cellNumber = -1;
  printf("Enter number of cell (0-99): ");
  scanf("%d", &cellNumber);
  sc_memoryGet(cellNumber, &value);
  printf("sc_memoryGet: %d - %d \n", cellNumber, value);
  sc_memoryInit();
  sc_memoryLoad("sc_memory.txt");
  printf("Memory: ");
  for (int i = 0; i < MEMORYSIZE; i++) {
    printf("%d ", sc_memory[i]);
  }

  printf("\n");
  sc_regInit();
  sc_regSet(1, 0);
  sc_regSet(2, 1);
  sc_regSet(3, 0);
  sc_regSet(4, 1);
  sc_regSet(5, 0);
  printf("Flags of register: ");
  for (int i = 1; i <= 5; i++) {
    sc_regGet(i, &value);
    printf("%d ", value);
  }
  printf("\n");
  sc_regGet(0, 0);
  printf("\n");

  int comm = -1;
  int operand = -1;
  printf("Enter command(0-37): ");
  scanf("%d", &comm);
  printf("Enter operand(0-127): ");
  scanf("%d", &operand);
  sc_commandEncode(comm, operand, &value);
  printf("\n %d", value);
  sc_commandDecode(value, &comm, &operand);
  printf("\n command: %d \n operand: %d \n", comm, operand);
  mt_clrscr();
  showMemory(1, 1);
  return 0;
}