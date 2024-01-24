#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  MAX_SIZE 50

typedef struct Node {
    int data;
    char operator;
    struct Node *next;
} Node;

Node *stack = NULL;

Node *init() {
    return NULL;
}

void pushNode(Node **top, Node *node) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exit(1);
    }
    new->data = node->data;
    new->operator = node->operator;
    new->next = *top;
    *top = new;
}

void pushData(Node **top, int data) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exit(1);
    }
    new->data = data;
    new->operator = '\0';
    new->next = *top;
    *top = new;
}

void pushOperator(Node **top, char operator) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exit(1);
    }
    new->data = INT_MIN;
    new->operator = operator;
    new->next = *top;
    *top = new;
}

void pop(Node **top) {
    if (*top == NULL) {
        return;
    } else {
        Node *temp = (*top)->next;
        free(*top);
        *top = temp;
    }
}


char popChar(Node **top) {
    if (*top == NULL) {
        return '\0';
    } else {
        Node *temp = (*top)->next;
        char tempChar = (*top)->operator;
        free(*top);
        *top = temp;
        return tempChar;
    }
}

char topChar(Node **top) {
    if (*top == NULL) {
        return '\0';
    } else {
        return (*top)->operator;
    }
}

int topInt(Node **top) {
    if (*top == NULL) {
        return INT_MIN;
    } else {
        return (*top)->data;
    }
}

void printStack(Node **top) {
    if (top != NULL) {
        Node *current = *top;
        while (current != NULL) {
            if (current->operator == '\0')
                printf("%d ", current->data);
            else
                printf("%c ", current->operator);

            current = current->next;
        }
        printf("\n");
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

int cprOperator(char c, char stackOperator) {
    switch (c) {
        case '+':
        case '-':
            switch (stackOperator) {
                case '*':
                case '/':
                    return 1;
                default:
                    return 0;
            }
        case ')':
            return -1;
        default:
            return 0;
    }
}

void infixToPostfix(char *infix, Node **postfix) {
    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            int number = 0;
            // When two or more digits are received as input, convert to decimal.
            while (isdigit(infix[i])) {
                number = number * 10 + (infix[i] - '0');
                i++;
            }
            pushData(postfix, number);
        } else if (isOperator(infix[i])) {
            if (cprOperator(infix[i], topChar(&stack)) == 1) {
                pushOperator(postfix, popChar(&stack));
                pushOperator(&stack, infix[i]);
            } else if (cprOperator(infix[i], topChar(&stack)) == 0) {
                pushOperator(&stack, infix[i]);
            } else if (cprOperator(infix[i], topChar(&stack)) == -1) {
                while (topChar(&stack) != '(') {
                    pushOperator(postfix, popChar(&stack));
                }
                popChar(&stack);
            }
            i++;
        }

    }

    while (topChar(&stack) != '\0') {
        pushOperator(postfix, popChar(&stack));
    }
}

void deleteStack(Node **top) {
    Node *current = *top;
    while (current != NULL) {
        *top = current->next;
        free(current);
        current = *top;
    }
}

void inverseStack(Node **temp, Node **new) {
    while (*temp != NULL) {
        pushNode(new, *temp);
        pop(temp);
    }
}

int caculatePostfix(Node **top) {
    Node *calc = NULL;
    Node *current = *top;
    int number = 0;
    while (current != NULL) {
        if (current->operator == '\0') { // This node has data
            pushData(&calc, current->data);
        } else {
            if (isOperator(current->operator)) {
                int a = topInt(&calc);
                pop(top);
                pop(&calc);
                int b = topInt(&calc);
                pop(top);
                pop(&calc);
                switch (current->operator) {
                    case '+':
                        number = b + a;
                        break;
                    case '-':
                        number = b - a;
                        break;
                    case '*':
                        number = b * a;
                        break;
                    case '/':
                        number = b / a;
                        break;
                }
                pushData(&calc, number);
            }
        }
        current = current->next;
    }
    return number;
}

int main() {
    char infixExpression[MAX_SIZE];

    Node *temp = NULL;
    Node *postfixExpression = NULL;

    printf("Enter the infix expression\n");
    fgets(infixExpression, MAX_SIZE, stdin);
    infixExpression[strcspn(infixExpression, "\n")] = '\0';

    infixToPostfix(infixExpression, &temp);
    inverseStack(&temp, &postfixExpression);
    printf("Postfix: ");
    printStack(&postfixExpression);

    printf("Result: %d", caculatePostfix(&postfixExpression));

    deleteStack(&postfixExpression);
    deleteStack(&stack);
    deleteStack(&temp);
    return 0;
}
