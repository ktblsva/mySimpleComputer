
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include <time.h>
#include <unistd.h>


int cursorX = 0; int cursorY = 0; int icX; int icY; int acX; int acY;
int showMemory(int x, int y);
int showFlags(int x, int y);
int showKeys(int x, int y);
int showBigChars(int x, int y);
int showAccumulator(int x, int y);
int showInstructionCounter(int x, int y);
int showOperation(int x, int y);
int keyHandler(enum keys key);

#define HighlightColor Red 

void print_key(enum keys key)
{
    switch (key) {
        case KEY_l:
            printf("l\n");
            break;
        case KEY_s:
            printf("s\n");
            break;
        case KEY_r:
            printf("r\n");
            break;
        case KEY_t:
            printf("t\n");
            break;
        case KEY_i:
            printf("i\n");
            break;
        case KEY_q:
            printf("q\n");
            break;
        case KEY_up:
            printf("up\n");
            break;
        case KEY_down:
            printf("down\n");
            break;
        case KEY_left:
            printf("left\n");
            break;
        case KEY_right:
            printf("right\n");
            break;
        case KEY_f5:
            printf("F5\n");
            break;
        case KEY_f6:
            printf("F6\n");
            break;
    }
}

int main(int argc, char **argv) 
{
    enum keys key;
    rk_mytermsave();
    rk_mytermregime(0, 0, 1, 0, 1);
    mt_clrscr();
    mt_printText("\E[?25l");

    do{
        //mt_clrscr();
        showMemory(1, 1);
        showFlags(10 * 5 + 9 + 4, 10);
        showKeys(61 - 15 + 1 + 1, 12 + 1);
        showBigChars(1,13);
        showAccumulator(10 * 5 + 9 + 4, 1);
        showInstructionCounter(10 * 5 + 9 + 4,1 + 3);
        showOperation(10 * 5 + 9 + 4, 1 + 3 + 3);

        rk_readkey(&key);
        //print_key(key);
        keyHandler(key);
        
    } while (key != KEY_q);

    mt_clrscr();
    //printf("Terminal settings restored.\n");
    rk_mytermrestore();
    mt_printText("\E[?12;25h");
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

int showAccumulator (int x, int y)
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

int showInstructionCounter (int x, int y)
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

int showOperation(int x, int y)
{
    int width = 22; 
    int height = 3;

    bc_panel(x,y,width,height);

    mt_goToXY(x + width / 2 - 9 / 2, y);
    mt_printText("Operation");   
}

int keyHandler(enum keys key)
{

    switch (key) {
        case KEY_l:
            sc_memoryLoad("memory");
            break;
        case KEY_s:
            sc_memorySave("memory");
            break;
        case KEY_r:
            printf("r\n");
            break;
        case KEY_t:
            printf("t\n");
            break;
        case KEY_i:
            printf("i\n");
            break;
        case KEY_up:

            if ((sc_instructionCounter - 10) >= 0)
            {
                sc_instructionCounter -= 10;
            }
            else
            {
                sc_instructionCounter += 90;
            }

            break;
        case KEY_down:

            if ((sc_instructionCounter + 10) <= 99)
            {
                sc_instructionCounter += 10;
            }
            else
            {
                sc_instructionCounter -= 90;
            }

            break;
        case KEY_left:

            if ((sc_instructionCounter - 1) >= 0)
            {
                sc_instructionCounter--;
            }
            else
            {
                sc_instructionCounter = 99;
            }

            break;
        case KEY_right:

            if ((sc_instructionCounter + 1) <= 99)
            {
                sc_instructionCounter++;
            }
            else
            {
                sc_instructionCounter = 0;
            }

            break;
        case KEY_f5:
            mt_goToXY(acX,acY);
            mt_printText("+    ");
            mt_goToXY(acX + 1,acY);
            rk_mytermregime(0, 0, 4, 1, 1);
            char buffA[5];
            mt_readText(buffA);
            int valueA;
            sscanf(buffA,"%x",&valueA);
            sc_accumulator = valueA;
            
            break;
        case KEY_f6:

            mt_goToXY(icX,icY);
            mt_printText("+    ");
            mt_goToXY(icX + 1,icY);
            rk_mytermregime(0, 0, 4, 1, 1);
            char buffI[5];
            mt_readText(buffI);
            int valueI;
            sscanf(buffI,"%x",&valueI);
            
            if ((valueI >= 0) && (valueI < 100))
            {
                sc_instructionCounter = valueI;
            }
                        
            break;
        case KEY_enter:

            mt_goToXY(cursorX,cursorY);
            mt_printText("+    ");
            mt_goToXY(cursorX + 1,cursorY);
            rk_mytermregime(0, 0, 4, 1, 1);
            char buffM[5];
            mt_readText(buffM);
            int valueM;
            sscanf(buffM,"%x",&valueM);
            sc_memorySet(sc_instructionCounter, valueM);
            break;  
    }
    return 0;
}
