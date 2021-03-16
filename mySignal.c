#include "mySignal.h"

int ms_setSignals()
{
	signal(SIGALRM, ms_timerHandler);
	signal(SIGUSR1, ms_userSignal);
}

int ms_timerHandler(int sig)
{
	if ((sc_instructionCounter + 1) <= 99)
    {
    	sc_instructionCounter++;
    }
    else
    {
    	sc_instructionCounter = 0;
    }
	mg_showGUI(1,1);

	int value;
	sc_regGet(FLAG_IGNOR_PULS, &value);
	if (!value)
	{
		alarm(1);
	}

	return 0;
}

int ms_userSignal(int sig)
{
	alarm(0);
	sc_regInit();
	sc_regSet(FLAG_IGNOR_PULS,1);
	sc_instructionCounter = 0;
	sc_accumulator = 0;
	mg_showGUI(1,1);
}