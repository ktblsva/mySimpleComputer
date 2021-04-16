#include "ALU.h"

int ALU(int command, int operand)
{
	int tmp;
	sc_memoryGet(operand, &tmp);
	switch(command)
	{
		case 0x30: //сложение, результат в акк
				sc_accumulator += tmp;
				break;
		case 0x31: //вычитание
				sc_accumulator -= tmp;
				break;
		case 0x32: //деление
				if (tmp == 0)
				{
					sc_regSet(FLAG_DIV_BY_ZERO, 1);
					return -1;
				}
				sc_regSet(FLAG_DIV_BY_ZERO, 0);
				sc_accumulator /= tmp;
				break;
		case 0x33: //произведение
				sc_accumulator *= tmp;
				break;
		case 0x52: //логич и
				//sc_accumulator &= tmp;
				;
				int a = sc_accumulator;
				int b = tmp;
				for(int i = 0; i < 8; i++)
				{
					if((a & (1 << i)) & (b & (1 << i)))
					{
						sc_accumulator |= 1 << i;
					}
				}
				break; 
	}
	// if ((sc_accumulator > 0x7FFF) || (sc_accumulator < 0)) 
	// {
	// 	sc_accumulator &= 0x7FFF;
	// 	sc_regSet(FLAG_OVERFLOW, 1);
	// }
	// else
	// {	
	// 	sc_regSet(FLAG_OVERFLOW, 0);
	// }
}