
#include <time.h>
#include "mySimpleComputer.h"

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
    return 0;
}