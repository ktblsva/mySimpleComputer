#include "myReadkey.h"

int rk_readkey(enum keys *key)
{
	struct termios termOrig;
	char buf[16];
	int numRead;
	int terminal = open(TERM, O_RDWR);
  	if (terminal == -1) 
  	{
    	return ERR_TERM;
  	}
	if (tcgetattr(terminal, &termOrig) != 0)
	{
		return -1;
	}
	if (rk_mytermregime(0, 0, 1, 0, 1) != 0)
	{
		return -1;
	}
	numRead = read(terminal, buf, 15);
	buf[numRead] = '\0';
	if (strcmp(buf, "l") == 0)
	{
		*key = KEY_l;
	}
	else
	if (strcmp(buf, "s") == 0)
	{
		*key = KEY_s;
	}
	else
	if (strcmp(buf, "r") == 0)
	{
		*key = KEY_r;
	}
	else
	if (strcmp(buf, "t") == 0)
	{
		*key = KEY_t;
	}
	else
	if (strcmp(buf, "i") == 0)
	{
		*key = KEY_i;
	}
	else
	if (strcmp(buf, "q") == 0)
	{
		*key = KEY_q;
	}
	else
	if ((strcmp(buf, "\n") == 0) || (strcmp(buf, "\r") == 0)) // \r
	{
		*key = KEY_enter;
	}
	else
	if ((strcmp(buf, "\E[15~") == 0) || (strcmp(buf, "\E[[E") == 0)) //  \E[15~ \E[[E
	{
		*key = KEY_f5;
	}
	else
	if (strcmp(buf, "\E[17~") == 0)
	{
		*key = KEY_f6;
	}
	else
	if (strcmp(buf, "\E[A") == 0)
	{
		*key = KEY_up;
	}
	else
	if (strcmp(buf, "\E[B") == 0)
	{
		*key = KEY_down;
	}
	else
	if (strcmp(buf, "\E[C") == 0)
	{
		*key = KEY_right;
	}
	else
	if (strcmp(buf, "\E[D") == 0)
	{
		*key = KEY_left;
	}
	else
	{
		*key = KEY_unknown;
	}
	if (tcsetattr(terminal, TCSANOW, &termOrig) != 0)
		return -1;

	return 0;
}
int rk_mytermsave()
{
	int terminal = open(TERM, O_RDWR);
  	if (terminal == -1) 
  	{
    	return ERR_TERM;
  	}
	struct termios opt;
	FILE *toSave;
	if (tcgetattr(terminal, &opt) != 0)
	{
		return -1;
	}
	if ((toSave = fopen("termSettings", "wb")) == NULL)
	{
		return -1;
	}
	fwrite(&opt, sizeof(opt), 1, toSave);
	fclose(toSave);
	return 0;
}

int rk_mytermrestore()
{
	int terminal = open(TERM, O_RDWR);
  	if (terminal == -1) 
  	{
    	return ERR_TERM;
  	}
	struct termios opt;
	FILE *toSave;
	if ((toSave = fopen("termsettings", "rb")) == NULL)
	{
		return -1;
	}
	if (fread(&opt, sizeof(opt), 1, toSave) > 0)
	{
		if (tcsetattr(terminal, TCSAFLUSH, &opt) != 0)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return 0;

}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	int terminal = open(TERM, O_RDWR);
  	if (terminal == -1) 
  	{
    	return ERR_TERM;
  	}
	struct termios termOrig;
	if (tcgetattr(terminal, &termOrig) != 0)
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
    }
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
    
    if (tcsetattr(terminal, TCSANOW, &termOrig) != 0)
    {
		return -1;
    }
    return 0;
}
