#include "mySimpleComputer.h"
#include <time.h>

int main()
{
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
    sc_regSet(0, 0);
    sc_regSet(1, 1);
    sc_regSet(2, 0);
    sc_regSet(3, 1);
    sc_regSet(4, 0);
    printf("Flags of register: ");
    for (int i = 0; i < 5; i++) {
        sc_regGet(i, &value);
        printf("%d ", value);
    }
    printf("\n");
    int comm=-1;
    printf("Enter command(0-37): ");
    scanf("%d", &comm);
    sc_commandEncode(comm, 0, &value);
    return 0;
}