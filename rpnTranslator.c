#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void stack_push(char data, Node** top)
{
    Node* tmp = new Node();
    tmp->data = data;
    tmp->next = *top;
    *top = tmp;
}

void stack_print(Node* top)
{
    if (top == NULL) printf("Stack/Queue is empty!\n");
    else
    {
        Node* tmp = top;
        while (tmp)
        {
            printf("%d ", tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

char stack_pop(Node** top)
{
    Node* tmp;
    char d;
    if (*top == NULL)
    {
        //printf("Stack/Queue is underflow!\n");
        return -1;
    }
    else
    {
        tmp = *top;
        *top = tmp->next;
        d = tmp->data;
        delete tmp;
        return d;
    }
}

char stack_top(Node* top)
{
    if (top != nullptr)
    {
        return top->data;
    }
}

int checkPriority(char sign)
{
    switch (sign)
    {
    case '*':
    case '/':
        return 4;
    case '+':
    case '-':
        return 2;
    case '(':
    case ')':
        return 1;
    }
}

char* translateToRPN(char* inf, char rpn[])
{
    //char rpn[255] = "\0";
    Node* root = nullptr;
    int i = 0;
    int j = 0;
    while (inf[i] != '\0' && inf[i] != '\n')
    {
       char x = inf[i];
       if ((x >= 'a' && x <= 'z') || x >= 'A' && x <= 'Z')
       {
           rpn[j] = x;
           j++;
           //printf("%s\n", rpn);
       }
       else if (x == '(')
       {
           stack_push(x, &root);
       }
       else if (x == ')')
       {
           while (stack_top(root) != '(')
           {
               char c = stack_pop(&root);
               if (c != 0)
               {
                   rpn[j] = c;
                   j++;
               }
           }
           stack_pop(&root);
       }
       else if (x == '+' || x == '-' || x == '*' || x == '/')
       {
           while (root != nullptr && checkPriority(root->data) >= checkPriority(x))
           {
               char c = stack_pop(&root);
               if (c != 0)
               {
                   rpn[j] = c;
                   j++;
               }
           }
           stack_push(x, &root);
       }
       else if (x != ' ')
       {
           //free(rpn);
           fprintf("Wrong expression!\n");
           exit(EXIT_FAILURE);
       }
       i++;
    }
    while (root != nullptr)
    {
        char c = stack_pop(&root);
        if (c != 0)
        {
            rpn[j] = c;
            j++;
        }
    }
    for (int k = 0; k < j; k++)
    {
        if (rpn[k] == '(' || rpn[k] == ')')
        {
            fprintf("Check your expression!\n");
            exit(EXIT_FAILURE);
        }
    }
    rpn[j] = '\0';
    return rpn;
}

char preCalcProcessing(char* expr)
{
    char* ptr = strtok(expr, " =");
    char* val = ptr;
    if (!(*(val) >= 'A' && *(val) <= 'Z'))
    {
        printf("NOT CORRECT!\n");
    }
    ptr = strtok(NULL, " ");
    char* eq = ptr;
    if (*(eq)!='=')
    {
        printf("Wrong expression!\n");
    }
    ptr = strtok(NULL, "");
    char* exp = ptr;
    int i = 0;
    int pos = 0;
    int j = 0;
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
            exp[pos] = intToConst(atoi(num));
        }
        i++;
    }
    expr = exp;
    return val;
}

