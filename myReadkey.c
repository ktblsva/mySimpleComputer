#include "myReadkey.h"

int readkey(enum keys *key)
{
	struct termios termOrig;
	char buf[16];
	int numRead;
	if (tcgetattr(STDIN_FILENO, &termOrig) != 0)
		return -1;
	// if (rk_mytermregime(0, 0, 1, 0, 1) != 0)
	// 	return -1;
}
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termois termOrig;
	if (tcgetattr(STDIN_FILENO, &options) != 0)
	{
		return -1;
	}
	//канонический режим = 1
	if(regime)
	{
          termOrig.c_lflag |= ICANON;
    }
	else if (!regime)
	{
		termOrig.c_lflag &= ~ICANON;
	}
	else
	{
		return -1;
	}
	//неканонический режим работы
    if (!regime) 
    {
    	//количество символов в очереди, чтобы read завершился
        termOrig.c_cc[VTIME] = vtime;
        //сколько времени ждать появления символа
        termOrig.c_cc[VMIN] = vmin;
        //символы будут отражаться по мере набора
        if (echo == 1)
        {
        	termOrig.c_lflag |= ECHO;
        }
        else if(!echo)
        {
        	termOrig.c_lflag &= ~ECHO;
        }
        else
        {
        	return -1;
        }
        //обработка клавиш прерывания
        if (sigint)
        {
        	termOrig.c_lflag |= ISIG;
        }
        else if (!sigint)
        {
			termOrig.c_lflag &= ~ISIG;
        }
        else
        {
        	return -1;
        }
    }
    if (tcsetattr(STDIN_FILENO, TCSANOW, &termOrig) != 0)
    {
		return -1;
    }
    return 0;
}
