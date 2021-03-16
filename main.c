#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "mySignal.h"
#include "myGUI.h"
#include <time.h>
#include <unistd.h>

int keyHandler(enum keys key);

int main(int argc, char **argv) 
{
    sc_regInit();
    enum keys key;
    rk_mytermsave();
    rk_mytermregime(0, 0, 1, 0, 1);
    mt_clrscr();
    sc_regSet(FLAG_IGNOR_PULS,1);
    mt_printText("\E[?25l");
    ms_setSignals();
    mg_showGUI(1,1);

    do{
        rk_readkey(&key);
        keyHandler(key);
        mg_showGUI(1,1);
        
    } while (key != KEY_q);

    mt_clrscr();
    //printf("Terminal settings restored.\n");
    rk_mytermrestore();
    mt_printText("\E[?12;25h");
    return 0;
}

int keyHandler(enum keys key)
{

    int ignore;
    sc_regGet(FLAG_IGNOR_PULS,&ignore);

    if (!ignore)
    {

        switch (key) 
        {
            case KEY_l:
                sc_memoryLoad("memory");
                break;
            case KEY_s:
                sc_memorySave("memory");
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
                alarm(0);
                mt_goToXY(acX,acY);
                mt_printText("+    ");
                mt_goToXY(acX + 1,acY);
                rk_mytermregime(0, 0, 4, 1, 1);
                char buffA[5];
                mt_readText(buffA);
                int valueA;
                sscanf(buffA,"%x",&valueA);
                sc_accumulator = valueA;
                alarm(1);
                break;
            case KEY_f6:
                alarm(0);
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
                else
                {
                    sc_regSet(3,1);
                }
                alarm(1);           
                break;
            case KEY_enter:
                alarm(0);
                mt_goToXY(cursorX,cursorY);
                mt_printText("+    ");
                mt_goToXY(cursorX + 1,cursorY);
                rk_mytermregime(0, 0, 4, 1, 1);
                char buffM[5];
                mt_readText(buffM);
                int valueM;
                sscanf(buffM,"%x",&valueM);
                sc_memorySet(sc_instructionCounter, valueM);
                alarm(1);
                break;  
            }
        }
        if (key == KEY_r)
        {
            int valueR;
            sc_regGet(FLAG_IGNOR_PULS,&valueR);

            if (valueR)
            {
                sc_regSet(FLAG_IGNOR_PULS,0);
                ms_timerHandler(SIGALRM);
            }
            else
            {
                alarm(0);
                sc_regSet(FLAG_IGNOR_PULS,1);
            }
        }
        else if (key == KEY_t)
        {
            ms_timerHandler(SIGALRM);
        }
        else if (key == KEY_i)
        {
            raise(SIGUSR1);
        }
    return 0;
}
