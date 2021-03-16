#include "myGUI.h"

int mg_showGUI(int x, int y)
{
    mg_showMemory(x, y);
    mg_showFlags((x - 1) + 10 * 5 + 9 + 4, (y - 1) + 10);
    mg_showKeys((x - 1) + 61 - 15 + 1 + 1, (y - 1) + 12 + 1);
    mg_showBigChars(x,(y - 1) + 13);
    mg_showAccumulator((x - 1) + 10 * 5 + 9 + 4, y);
    mg_showInstructionCounter((x - 1) + 10 * 5 + 9 + 4, (y - 1) + 1 + 3);
    mg_showOperation((x - 1) + 10 * 5 + 9 + 4, (y - 1) + 1 + 3 + 3);
}

int mg_showKeys(int x, int y) 
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

int mg_showFlags(int x, int y) 
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

int mg_showMemory(int x, int y) 
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
            if (cell == sc_instructionCounter)
            {
                mt_setBgColor(HighlightColor);
                cursorX = (2 + x) + 6 * (j - 1);
                cursorY = y + i;
            }
            cell++;
            sprintf(buff, "+%.4X", value);
            mt_printText(buff);
            if (cell - 1 == sc_instructionCounter)
            {
                mt_setBgColor(Default);
            }
            if (j != 10) 
            {
                mt_printText(" ");
            }
        }
    }

    mt_printText("\n");
    return 0;
}

int mg_showBigChars (int x, int y)
{
    int width = 46;
    int height = 10;
    bc_panel(x,y,width,height);

    char buff[6];
    //int index;
    int value;
    value = 3;
    sc_memoryGet(sc_instructionCounter, &value);
    sprintf(buff,"+%.4X", value);

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
            case 'A':
                bc_arrayToBig(big,bc_char_A);
                break;
            case 'B':
                bc_arrayToBig(big,bc_char_B);
                break;
            case 'C':
                bc_arrayToBig(big, bc_char_C);
                break;
            case 'D':
                bc_arrayToBig(big, bc_char_D);
                break;
            case 'E':
                bc_arrayToBig(big,  bc_char_E);
                break;
            case 'F':
                bc_arrayToBig(big, bc_char_F);
                break;
            default:
                bc_arrayToBig(big,bc_char_0);
        }

        bc_printBigChar(big, x + 1 + 1 * i + (8 * i), y + 1,White,Default);
    }

    return 0;
}

int mg_showAccumulator (int x, int y)
{

    int width = 22; 
    int height = 3;

    bc_panel(x,y,width,height);

    mt_goToXY(x + width / 2 - 11 / 2,y);
    mt_printText("Accumulator");

    mt_goToXY(x + width / 2 - (5 / 2), y + 1);
    acX = x + width / 2 - (5 / 2); acY = y + 1;
    char buff[6];
    sprintf(buff,"+%.4X", sc_accumulator);
    mt_printText(buff);

    return 0;
}

int mg_showInstructionCounter (int x, int y)
{
    int width = 22; 
    int height = 3;

    bc_panel(x,y,width,height);

    mt_goToXY(x + width / 2 - 19 / 2, y);
    mt_printText("Instruction Counter");

    mt_goToXY(x + width / 2 - (5 / 2), y + 1);
    icX = x + width / 2 - (5 / 2); icY = y + 1;
    char buff[6];
    sprintf(buff,"+%.4X", sc_instructionCounter);
    mt_printText(buff);

}

int mg_showOperation(int x, int y)
{
    int width = 22; 
    int height = 3;

    bc_panel(x,y,width,height);

    mt_goToXY(x + width / 2 - 9 / 2, y);
    mt_printText("Operation");   
}