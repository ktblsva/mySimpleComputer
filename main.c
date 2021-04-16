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

    if (ignore)
    {

        switch (key) 
        {
            case KEY_l:
            	mt_goToXY(cursorX, cursorY);
            	mt_printText(" Filename to load:> ");
            	rk_mytermregime(1,0,0,1,1);
            	char buffL[255];
            	mt_readText(buffL, sizeof(buffL));
            	buffL[strlen(buffL) - 1] = '\0';
                sc_memoryLoad(buffL);
                char outputL[255];
                sprintf(outputL, "Filename to load:> %s", buffL);
                sc_addOutput(outputL);
                break;
            case KEY_s:
            	mt_goToXY(cursorX, cursorY);
            	mt_printText(" Filename to save:> ");
            	char buffS[255];
            	rk_mytermregime(1,0,0,1,1);
            	mt_readText(buffS, sizeof(buffS));
            	buffS[strlen(buffS) - 1] = '\0';
                sc_memorySave(buffS);
                char outputS[255];
                sprintf(outputS, "Filename to save:> %s", buffS);
                sc_addOutput(outputS);
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
                mt_goToXY(cursorX,cursorY);
                mt_printText(" Accumulator:> ");
                rk_mytermregime(0, 0, 1, 1, 1);
                char buffAf[2];
                mt_readText(buffAf, sizeof(buffAf));
                int sign = 1;
                if (buffAf[0] == '-' || buffAf[0] == '+')
                {
                	rk_mytermregime(0, 0, 4, 1, 1);
                    if (buffAf[0] == '-')
                    {
                	   sign = -1;
                    }
                }
                else
                {
                	rk_mytermregime(0, 0, 3, 1, 1);
                }
        		char buffAs [5];
        		mt_readText(buffAs, sizeof(buffAs));
        		char buffA[6];
        		if (sign)
        		{
        			sprintf(buffA, "%s", buffAf);
        		}
        		sprintf(buffA,"%s%s", buffA, buffAs);
        		int valueA;
                sscanf(buffA,"%x",&valueA);
                sc_accumulator = valueA;

                char outputA[255];
                sprintf(outputA,"Accumulator:> %s", buffA);
                sc_addOutput(outputA);
                break;
            case KEY_f6:
                mt_goToXY(cursorX, cursorY);
                mt_printText(" Instruction Counter:> ");
                rk_mytermregime(0, 0, 2, 1, 1);
                char buffI[5];
                mt_readText(buffI, sizeof(buffI));
                int valueI;
                sscanf(buffI,"%x",&valueI);
                
                if ((valueI >= 0) && (valueI < 100))
                {
                    sc_instructionCounter = valueI;
                    sc_regSet(FLAG_WRONG_ADDRESS,0);
                    char outputI[255];
                    sprintf(outputI, "Instruction Counter:> %s", buffI);
                    sc_addOutput(outputI);
                }
                else
                {
                    sc_regSet(FLAG_WRONG_ADDRESS,1);
                }     
                break;
            case KEY_enter:
                mt_goToXY(cursorX, cursorY);
                mt_printText(" Command:> ");
                rk_mytermregime(0, 0, 2, 1, 1);
                char buffM[3];
                mt_readText(buffM, sizeof(buffM));
                int commandM;
                sscanf(buffM,"%x",&commandM);
                mt_printText(" Operand:> ");
                rk_mytermregime(0, 0, 2, 1, 1);
                mt_readText(buffM, sizeof(buffM));
                int operandM;
                sscanf(buffM,"%x", &operandM);
                int valueM;
                int protection;
                sc_regSet(FLAG_WRONG_COMMAND, 0);
                protection = sc_commandEncode(commandM,operandM,&valueM);

                if (protection == 0)
                {
                	sc_memorySet(sc_instructionCounter, valueM);
                	char outputM[255];
                	sprintf(outputM,"Command:> %X Operand:> %X",commandM, operandM);
                	sc_addOutput(outputM);
                }
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
