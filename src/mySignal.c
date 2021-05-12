#include "mySignal.h"
#include "CU.h"

int ms_setSignals()
{
	signal(SIGALRM, ms_timerHandler);
	signal(SIGUSR1, ms_userSignal);
}

int ms_timerHandler(int sig)
{
	CU();
	int value;
	sc_regGet(FLAG_IGNOR_PULS, &value);
	if((sc_instructionCounter < 99 && sc_instructionCounter >= 0) && !value)
	{
		sc_instructionCounter++;
	}
	else if (sc_instructionCounter >= 99)
	{
		sc_instructionCounter = 0;
	}
	if (!value)
	{
		ualarm(400,0);
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