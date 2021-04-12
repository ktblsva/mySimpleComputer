#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mySimpleComputer.h"

#define ERR_EXPECTED_ADDRESS_OF_MEMORY_CELL -1
#define ERR_WRONG_COMMAND -2
#define ERR_WRONG_OPERAND -3
#define ERR_BY_ENCODE -4

struct variable
{
	char Name[2];
	int Address;
	int Value;
};

struct variable Variables[52];
char lastConstantName = 'a';

FILE *input = NULL;
FILE *output = NULL;

const char commandID[][7] =
{"REM", "INPUT", "PRINT","GOTO","IF","LET","END"};
int basicCommandCouner = 0;
int assemblerCommandCounter = 0;

int getVariableAddress(char* name)
{
	for (int i = 0; i < 52; i++)
	{
		if (Variables[i].Name == name)
		{
			return Variables[i].Address;
		}

		if (Variables[i].Name == NULL)
		{
			Variables[i].Name = name;
			Variables[i].Address = 99 - i;
			return Variables[i].Address;
			break;
		}
	}
}

char* intToConstant(int value)
{
	for (int i = 0; i < 52; i++)
	{
		if (Variables[i].Name == NULL)
		{
			sprintf(Variables[i].Name,"%c",lastConstantName);
			lastConstantName++;
			Variables[i].Address = 99 - i;
			Variables[i].Value = value;
			fprintf(output, "%d STORE %d\n",Variables[i].Address, Variables[i].Value);
			return Variables[i].Name;
		}

		if (Variables[i].Value != NULL)
		{
			if (Variables[i].Value == value)
			{
				return Variables[i].Name;
			}
		}
	}
}

void load_file(const char* filename)
{
	if((input = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Can't open file: no such file.\n");
		exit(EXIT_FAILURE);
	}
	return;
}

void translation(const char* filename)
{
	int instructionCounter =0;

	while (1)
	{
		char temp[255];
		fgets(temp, 254, input);
		if (feof(input))
		{
			break;
		}
		instructionCounter++;
	}
	revind(input);

	char** program = (char**)malloc(sizeof(char*) * instructionCounter);
	for (int i = 0 ;i < instructionCounter; i++)
	{
		program[i] = (char)malloc(sizeof(char) * 255);
		if(!fgets(program[i], 255, input))
		{
			if(feof(input))
			{
				fprintf(stderr, "Line %d: end of file.\n", i++);
				return;
			}
			else
			{
				fprintf(stderr, "Line %d: can't read line from file.\n", i++);
				return;
			}
		}

	}

	for (int i = 0; i < instructionCounter; i++)
	{
		char* lin;

		char* ptr = strtok(program[i]," ");
		lin = ptr;

		int line = atoi(line);
		if ((line == NULL) && (strcmp(lin,"0") != 0) && (strcmp(lin,"00") != 0))
		{
			fprintf(stderr, "Line %d: expected line number.\n", i++);
			break;
		}

		if (i - 1 >= 0)
		{
			char* last;
			char* ptr2 = strtok(program[i - 1]," ");
			if (line <= atoi(last))
			{
				fprintf(stderr, "Line %d: Wrong line number\n", i++);
				free(last);
				free(ptr2);
				break;
			}

			free(last);
			free(ptr2);
		}

		char* command;
		ptr = strtok(NULL," ");
		command = ptr;
		char* arguments;
		ptr = strtok(NULL, "");
		arguments = ptr;

		function(command, arguments);

	}
}

void INPUT(char* arguments)
{
	if (!((strlen(arguments) == 1) && (arguments[0] >= 'A') && (arguments[0] <= 'Z')))
	{
		fprintf(stderr, "Wrong variable name.\n", );
		exit(EXIT_FAILURE);
	}

	fprintf(output, "%d READ %d\n", assemblerCommandCounter, getVariableAddres(arguments));
	assemblerCommandCounter++;
}
void PRINT(char *)
{
	if (!((strlen(arguments) == 1) && (arguments[0] >= 'A') && (arguments[0] <= 'Z')))
	{
		fprintf(stderr, "Wrong variable name.\n", );
		exit(EXIT_FAILURE);
	}

	fprintf(output, "%d WRITE %d\n", assemblerCommandCounter, getVariableAddres(arguments));
	assemblerCommandCounter++;
}
void GOTO();
void IF();
void LET();
void END()
{
	fprintf(output, "%d HALT 00\n", assemblerCommandCounter);
	assemblerCommandCounter++;
}

void function(char* command, char* arguments);
{
	switch(command)
	{
		case("REM"):
			break;
		case("INPUT"):
			INPUT(arguments);
			break;
		case("PRINT"):
			PRINT();
			break;
		case("GOTO")
			GOTO();
			break;
		case("IF"):
			IF();
			break;
		case("LET"):
			LET();
			break;
		case("END"):
			END();
			break;
		default:
			fprintf(stderr, "%s is not a command.\n", command);
			break;
	}
}



int main(int argc, const char** argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s input.sa output.o\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	sc_memoryInit();
	load_file(argv[1]);
	translation(argv[2]);
	return 0;
}