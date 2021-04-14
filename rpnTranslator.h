#ifndef RPN_TRANSLATOR_H
#define RPN_TRANSLATOR_H

struct Node
{
	char data;
	Node* next;
};
void stack_push(char data, Node** top);
void stack_print(Node* top);
char stack_pop(Node** top);
char stack_top(Node* top);
int checkPriority(char sign);
char* translateToRPN(char* inf, char rpn[]);
char preCalcProcessing(char* expr);

#endif //RPN_TRANSLATOR_H