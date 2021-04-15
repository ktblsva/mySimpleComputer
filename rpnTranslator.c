#include "rpnTranslator.h"


void stack_push(char data, Node** top)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
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
        free(tmp);
        return d;
    }
}

char stack_top(Node* top)
{
    if (top != NULL)
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
    Node* root = NULL;
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
           while (root != NULL && checkPriority(root->data) >= checkPriority(x))
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
           fprintf(stderr,"Wrong expression!\n");
           exit(EXIT_FAILURE);
       }
       i++;
    }
    while (root != NULL)
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
            fprintf(stderr,"Check your expression!\n");
            exit(EXIT_FAILURE);
        }
    }
    rpn[j] = '\0';
    return rpn;
}



