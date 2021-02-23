
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include <time.h>

int showMemory(int x, int y);
int showFlags(int x, int y);
int showKeys(int x, int y);
int showBigChars(int x, int y);
int showAccumulator(int x, int y);


int main() 
{
    mt_clrscr();

    showMemory(1, 1);
    showFlags(10 * 5 + 9 + 4, 10);
    showKeys(61 - 15 + 1 + 1, 12 + 1);
    showBigChars(1,13);
    showAccumulator(10 * 5 + 9 + 4, 1);
    mt_printText("\E[?25l");

    return 0;
}

int showKeys(int x, int y) 
{
    int width = 22+15;
    int height = 10;
    bc_panel(x,y,width,height);
    mt_goToXY(x + 2, y);
    mt_printText("Keys:");
    mt_goToXY(x + 1, y + 1);
    mt_printText("l  - load");
    mt_goToXY(x + 1, y + 2);
    mt_printText("s  - save");
    mt_goToXY(x + 1, y + 3);
    mt_printText("r  - run");
    mt_goToXY(x + 1, y + 4);
    mt_printText("t  - step");
    mt_goToXY(x + 1, y + 5);
    mt_printText("i  - reset");
    mt_goToXY(x + 1, y + 6);
    mt_printText("F5 - accumulator");
    mt_goToXY(x + 1, y + 7);
    mt_printText("F6 - instructionCounter");
    mt_goToXY(x + 1, y + 8);
    mt_printText(" ");
    return 0;
}

int showFlags(int x, int y) 
{
    int width = 22;
    int height = 3;
    bc_panel(x,y, width, height);
    mt_goToXY(x + width / 2 - 3 + 1, y);
    mt_printText("Flags");
    mt_goToXY(x + width / 2 - 3 - 1, y + 1);

    for (int i = 1; i <= 5; i++) 
    {
        int flag;
        sc_regGet(i, &flag);
        if (flag) 
        {
            mt_setFgColor(Red);
        } 
        else 
        {
            mt_setFgColor(White);
        }

        switch (i) 
        {
            case 1:
                mt_printText("O "); // overflow
                break;
            case 2: 
                mt_printText("D "); // div by zero
                break;
            case 3: 
                mt_printText("M "); // out of border memory
                break;
            case 4:
                mt_printText("I "); // ignore impulse
                break;
            case 5: 
                mt_printText("C "); // wrong command
                break;
        }
    }
    mt_setFgColor(White);
    return 0;
}

int showMemory(int x, int y) 
{
    int width = 10 * 5 + 9 + 2;
    int height = 12;
    bc_panel(x,y,width,height);

    mt_goToXY(x + width / 2 - 3 + 1, y);
    mt_printText("Memory");
    int cell = 0;
    for (int i = 1; i < 11; i++) 
    {
        mt_goToXY(2 + x, y + i);
        for (int j = 1; j < 11; j++)
        {
            char buff[6];
            int value;
            sc_memoryGet(cell, &value);
            cell++;
            sprintf(buff, "+%.4i", value);
            mt_printText(buff);
            if (j != 10) 
            {
                mt_printText(" ");
            }
        }
    }

    mt_printText("\n");
    return 0;
}

int showBigChars (int x, int y)
{
    int width = 46;
    int height = 10;
    bc_panel(x,y,width,height);

    char buff[6];
    //int index;
    int value;
    value = 3;
    sc_memoryGet(sc_instructionCounter, &value);
    sprintf(buff,"+%.4i", value);

    for (int i = 0; i < strlen(buff); i++)
    {
        int big[2];

        switch(buff[i])
        {
            case '+':
                bc_arrayToBig(big,bc_char_plus);
                break;
            case '0':
                bc_arrayToBig(big,bc_char_0);
                break;
            case '1':
                bc_arrayToBig(big,bc_char_1);
                break;
            case '2':
                bc_arrayToBig(big,bc_char_2);
                break;
            case '3':
                bc_arrayToBig(big,bc_char_3);
                break;
            case '4':
                bc_arrayToBig(big,bc_char_4);
                break;
            case '5':
                bc_arrayToBig(big,bc_char_5);
                break;
            case '6':
                bc_arrayToBig(big,bc_char_6);
                break;
            case '7':
                bc_arrayToBig(big,bc_char_7);
                break;
            case '8':
                bc_arrayToBig(big,bc_char_8);
                break;
            case '9':
                bc_arrayToBig(big,bc_char_9);
                break;
            default:
                bc_arrayToBig(big,bc_char_0);
        }

        bc_printBigChar(big, x + 1 + (8 * i), y + 1,White,Black);
    }

    return 0;
}

int showAccumulator (int x, int y)
{
    int width = 22; 
    int height = 3;

    bc_panel(x,y,width,height);

    return 0;
}
