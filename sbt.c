#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "mySimpleComputer.h"
#include "rpnTranslator.h"

#define ERR_EXPECTED_ADDRESS_OF_MEMORY_CELL -1
#define ERR_WRONG_COMMAND -2
#define ERR_WRONG_OPERAND -3
#define ERR_BY_ENCODE -4

struct variable
{
	char Name;
	int Address;
	int Value;
};

struct variable Variables[52];
char lastConstantName = 'a';

struct command
{
	int Number;
	char* Command;
	int Address;
};

FILE *input = NULL;
FILE *output = NULL;

const char commandID[][7] =
{"REM", "INPUT", "PRINT","GOTO","IF","LET","END"};
int basicCommandCouner = 0;
int assemblerCommandCounter = 0;
struct command* program;

int gotoCounter = -1;
struct command *gotoRecords;

int getVariableAddress(char name)
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
		}
	}
}

char intToConstant(int value)
{
	for (int i = 0; i < 52; i++)
	{
		if (Variables[i].Name == NULL)
		{
			sprintf(Variables[i].Name,"%c",lastConstantName);
			lastConstantName++;
			Variables[i].Address = 99 - i;
			Variables[i].Value = value;
			fprintf(output, "%d = %x\n",Variables[i].Address, abs(Variables[i].Value));
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

char preCalcProcessing(char* expr)
{
	printf("%s\n", expr);
    char* ptr = strtok(expr, " =");
    char* val = ptr;
    printf("%s\n", ptr);
    printf("%s\n", val);
    printf("PREOK\n");
    if (!(*(val) >= 'A' && *(val) <= 'Z'))
    {
        printf("NOT CORRECT!\n");
    }
    printf("PREOK\n");
    ptr = strtok(NULL, " ");
     printf("PREOKEQ\n");
    char* eq = ptr;
     printf("PREOKEQ\n");
    if (strcmp(eq,"=") != 0)
    {
        printf("Wrong expression!\n");
    }
    printf("PREOK\n");
    ptr = strtok(NULL, "");
    char* exp = ptr;
    int i = 0;
    int pos = 0;
    int j = 0;
    printf("PREOK\n");
    while (exp[i] != '\n' && exp[i] != '\0')
    {
        if (exp[i] >= '0' && exp[i] <= '9')
        {
            char num[256];
            j = 0;
            num[j] = exp[i];
            j++;
            pos = i;
            exp[i] = 'a';
            i++;
            while (exp[i] >= '0' && exp[i] <= '9')
            {
                num[j] = exp[i];
                j++;
                exp[i] = ' ';
                i++;
            }
            num[j] = '\0';
            printf("INTTOCS\n");
            exp[pos] = intToConstant(atoi(num));
        }
        i++;
    }
    printf("PREOK\n");
    expr = exp;
    return val;
}

void loadFile(const char* filename, const char* secondFilename)
{
	if((input = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Can't open file: no such file.\n");
		exit(EXIT_FAILURE);
	}

	output = fopen(secondFilename,"w");
	return;
}

void translation()
{
	printf("OK\n");
	gotoRecords = (struct command*)malloc(sizeof(struct command) * gotoCounter + 1);
	int instructionCounter =0;
	printf("OK\n");
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
	rewind(input);
	printf("OK\n");

	program = (struct command*)malloc(sizeof(struct command) * instructionCounter);
	printf("OK\n");
	for (int i = 0 ;i < instructionCounter; i++)
	{
		program[i].Command = (char*)malloc(sizeof(char) * 255);
		if(!fgets(program[i].Command, 254, input))
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
	printf("OK\n");

	for (int i = 0; i < instructionCounter; i++)
	{
		char* lin;

		char* ptr = strtok(program[i].Command," ");
		lin = ptr;

		int line = atoi(lin);
		if ((line == NULL) && (strcmp(lin,"0") != 0) && (strcmp(lin,"00") != 0))
		{
			fprintf(stderr, "Line %d: expected line number.\n", i++);
			break;
		}

		if (i - 1 >= 0)
		{
			if (line <= program[i - 1].Number)
			{
				fprintf(stderr, "Line %d: Wrong line number\n", i++);
				break;
			}
		}
		
		program[i].Number = line;

		char* command;
		ptr = strtok(NULL," ");
		command = ptr;
		char* arguments;
		ptr = strtok(NULL, "");
		arguments = ptr;
		program[i].Address = assemblerCommandCounter;

		if (strcmp(command,"GOTO") != 0)
		{
			function(command, arguments);
		}
		else
		{
			gotoCounter++;
			gotoRecords = realloc(gotoRecords, sizeof(struct command) * gotoCounter + 1);
			gotoRecords[gotoCounter] = program[i];
			assemblerCommandCounter++;
		}

	}
	printf("OK\n");

	for (int i = 0; i <= gotoCounter; i++)
	{
		int address = gotoRecords[i].Address;
		char* ptr = strtok(gotoRecords[i].Command,"");
		ptr = strtok(NULL," ");
		ptr = strtok(NULL,"");
		int operand = atoi(ptr);
		GOTO(address,operand);
	}
	printf("OK\n");
}

void INPUT(char* arguments)
{
	if (!((strlen(arguments) == 2) && (arguments[0] >= 'A') && (arguments[0] <= 'Z')))
	{
		fprintf(stderr, "Wrong variable name.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(output, "%d READ %d\n", assemblerCommandCounter, getVariableAddress(arguments));
	assemblerCommandCounter++;
}

void PRINT(char *arguments)
{
	if (!((strlen(arguments) == 2) && (arguments[0] >= 'A') && (arguments[0] <= 'Z')))
	{
		fprintf(stderr, "Wrong variable name.\n" );
		exit(EXIT_FAILURE);
	}

	fprintf(output, "%d WRITE %d\n", assemblerCommandCounter, getVariableAddress(arguments));
	assemblerCommandCounter++;
}

void parsRPN(char* rpn, char* var)
{
    int i = 0;
    int depth = 0;
    int operand1, operand2;
    while (rpn[i] != '\0' && rpn[i] != '\n')
    {
        char x = rpn[i];
        if ((x >= 'a' && x <= 'z') || x >= 'A' && x <= 'Z')
        {
            fprintf(output, "%d LOAD %d\n", assemblerCommandCounter, getVariableAddress(x));
            fprintf(output, "%d STORE %d\n", assemblerCommandCounter, assemblerCommandCounter);
            assemblerCommandCounter++;
            depth++;
        }
        if (x == '+' || x == '-' || x == '*' || x == '/')
        {
            if (depth < 2)
            {
                fprintf(stderr, "Uncorrect LET statement, check your expression.\n");
                exit(EXIT_FAILURE);
            }
            else
            {
              operand1 = assemblerCommandCounter - 1;
              operand2 = assemblerCommandCounter - 2;
              fprintf(output, "%d LOAD %d\n", assemblerCommandCounter, operand1); //закидываем самый правый операнд в акк
              assemblerCommandCounter++; 
              switch (x)
              {
              case '+':
                    fprintf(output, "%d ADD %d\n", assemblerCommandCounter, operand2);
                    assemblerCommandCounter++;
                    break;
              case '-': //SUB
                    fprintf(output, "%d SUB %d\n", assemblerCommandCounter, operand2);
                    assemblerCommandCounter++;
                    break;
              case '/': //DIVIDE
                    fprintf(output, "%d DIVIDE %d\n", assemblerCommandCounter, operand2);
                    assemblerCommandCounter++;
                    break;
              case '*': //MUL
                    fprintf(output, "%d MUL %d\n", assemblerCommandCounter, operand2);
                    assemblerCommandCounter++;
                    break;
              }
              fprintf(output, "%d STORE %d\n", assemblerCommandCounter, operand2);
              assemblerCommandCounter++;  
              depth--;
            }
        }
        i++;
    }
    if (depth != 1)//??
    {
      fprintf(stderr, "Uncorrect LET statement, check your expression.\n");
      exit(EXIT_FAILURE);
    }
    fprintf(output, "%d STORE %d\n", assemblerCommandCounter, getVariableAddress(var));
}

void GOTO(int address,int operand)
{
	for (int i = 0; i < basicCommandCouner; i++)
	{
		if (program[i].Number == operand)
		{
			fprintf(output, "%d JUMP %d\n",address, program[i].Address);
		}
	}
}

void IF(char* arguments)
{
	printf("IFOK");
	int mySign = -1;
	printf("IFOK");
	int before = 0;
	printf("IFOK");
	int after = 0;
	printf("IFOK");
	for (int i = 0; i < strlen(arguments); i++)
	{
		if ((arguments[i] == '>') || (arguments[i] == '<') || (arguments[i] == '='))
		{
			if (mySign != -1)
			{
				fprintf(stderr, "Wrong statement!\n");
				exit(EXIT_FAILURE);
			}

			mySign = i;

			if (!(arguments[i - 1] == ' '))
			{
				before = 1;
			}

			if (!(arguments[i + 1] == ' '))
			{
				after = 1;
			}
		}
	}
	printf("IFOK");

	char* expression = (char*)malloc(sizeof(char) * 255);
	if (!(before) && !(after))
	{
		expression = strtok(arguments,"");
	}
	else
	{
		int j = 0;
		for (int i = 0; i < strlen(arguments);i++)
		{
			if (i == mySign)
			{
				if (before)
				{
					expression[j] = ' ';
					j++;
				}
				expression[j] = arguments[i];
				j++;
				if (after)
				{
					expression[j] = ' ';
					j++;
				}
			}
			else
			{
				expression[j] = arguments[i];
				j++;
			}
		}
		expression[j] = '\0';
	}
	printf("IFOK");
	char* ptr = strtok(expression," ");
	char* operand1 = ptr;
	char operand1Name;

	if (strlen(operand1) > 1)
	{
		if(atoi(operand1))
		{
			operand1Name = intToConstant(atoi(operand1));
		}
	}
	else
	{
		if ((operand1[0] >= '0') && (operand1[0] <= '9'))
		{
			operand1Name = intToConstant(atoi(operand1));
		}
		else if ((operand1[0] >= 'A') && (operand1[0] <= 'Z'))
		{
			operand1Name = operand1[0];
		}
		else
		{
			fprintf(stderr, "Wrong statement!\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("IFOK");
	ptr = strtok(NULL," ");
	char* logicalSign = ptr;
	printf("IFOK");
	ptr = strtok(NULL," ");
	char* operand2 = ptr;
	char operand2Name;
	printf("IFOK");
	if (strlen(operand2) > 1)
	{
		if(atoi(operand2))
		{
			operand2Name = intToConstant(atoi(operand2));
		}
	}
	else
	{
		if ((operand2[0] >= '0') && (operand2[0] <= '9'))
		{
			operand2Name = intToConstant(atoi(operand2));
		}
		else if ((operand2[0] >= 'A') && (operand2[0] <= 'Z'))
		{
			operand2Name = operand2[0];
		}
		else
		{
			fprintf(stderr, "Wrong statement!\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("IFOK");

	int falsePosition;

	if  (logicalSign[0] == "<")
	{
		fprintf(output, "%d LOAD %d\n",assemblerCommandCounter,getVariableAddress(operand1Name));
		assemblerCommandCounter++;
		fprintf(output, "%d SUB %d\n", assemblerCommandCounter,getVariableAddress(operand2Name));
		assemblerCommandCounter++;
		fprintf(output, "%d JNEG %d\n",assemblerCommandCounter, assemblerCommandCounter + 2);
		assemblerCommandCounter++;
		falsePosition = assemblerCommandCounter;
		assemblerCommandCounter++;
	}
	else if (logicalSign[0] == ">")
	{
		fprintf(output, "%d LOAD %d\n",assemblerCommandCounter,getVariableAddress(operand2Name));
		assemblerCommandCounter++;
		fprintf(output, "%d SUB %d\n", assemblerCommandCounter,getVariableAddress(operand1Name));
		assemblerCommandCounter++;
		fprintf(output, "%d JNEG %d\n",assemblerCommandCounter, assemblerCommandCounter + 2);
		assemblerCommandCounter++;
		falsePosition = assemblerCommandCounter;
		assemblerCommandCounter++;
	}
	else if (logicalSign[0] == "=")
	{
		fprintf(output, "%d LOAD %d\n",assemblerCommandCounter,getVariableAddress(operand1Name));
		assemblerCommandCounter++;
		fprintf(output, "%d SUB %d\n", assemblerCommandCounter,getVariableAddress(operand2Name));
		assemblerCommandCounter++;
		fprintf(output, "%d JZ %d\n",assemblerCommandCounter, assemblerCommandCounter + 2);
		assemblerCommandCounter++;
		falsePosition = assemblerCommandCounter;
		assemblerCommandCounter++;
	}
	printf("IFOK");

	ptr = strtok(NULL," ");
	char* command = ptr;
	ptr = strtok(NULL,"");
	char* commandArguments = ptr;
	printf("IFOK");
	if (strcmp(command,"IF") == 0)
	{
		fprintf(stderr, "Multiple IF!\n");
		exit(EXIT_FAILURE);
	}
	else if (strcmp(command,"GOTO") != 0)
	{
		function(command, commandArguments);
	}
	else
	{
		gotoCounter++;
		gotoRecords = realloc(gotoRecords, sizeof(struct command) * gotoCounter + 1);
		struct command gotoCommand;
		gotoCommand.Address = assemblerCommandCounter;
		char buff = (char*)malloc(sizeof(char) * 255);
		sprintf(buff,"00 GOTO %s",arguments);
		gotoCommand.Command = buff;
		gotoRecords[gotoCounter];
		assemblerCommandCounter++;
	}
	printf("IFOK");

	fprintf(output, "%d JUMP %d\n", falsePosition, assemblerCommandCounter);
	printf("IFOK");
}

void LET(char* arguments)
{
	char fin[255];
	char var;
	printf("LETOK\n");
	var = preCalcProcessing(arguments);
	printf("LETOK\n");
	translateToRPN(arguments, fin);
	printf("LETOK\n");
	parsRPN(fin, var);
	printf("LETOK\n");
}

void END()
{
	fprintf(output, "%d HALT 00\n", assemblerCommandCounter);
	assemblerCommandCounter++;
}

void function(char* command, char* arguments)
{

	if (strcmp(command,"REM") == 0)
	{
	}
	else if (strcmp(command,"INPUT") == 0)
	{
		printf("IN\n");
		INPUT(arguments);
	}
	else if (strcmp(command,"PRINT") == 0)
	{
		printf("PR\n");
		PRINT(arguments);
	} 
	else if(strcmp(command,"IF") == 0)
	{
		printf("IF\n");
		IF(arguments);
	}
	else if(strcmp(command,"LET") == 0)
	{
		printf("LET\n");
		LET(arguments);
	}
	else if(strcmp(command, "END") == 0)
	{
		printf("END\n");
		END();
	}
	else
	{
		fprintf(stderr, "%s is not a command.\n", command);
	}

}



int main(int argc, const char** argv)
{

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s input.sa output.o\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	loadFile(argv[1], "tmp.sa");
	
	translation();
	printf("OK\n");


	char sat[255];
	sprintf(sat,"./sat tmp.sa %s",argv[2]);
	printf("OK\n");
	system(sat);
	printf("OK\n");
	return 0;
}