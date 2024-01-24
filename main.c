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
            printf("%d\n", current->data);
            current = current->next;
        }
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

void infixToPostfix(char *infix, char *postfix) {
    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j] = infix[i];
            j++;
        } else if (isOperator(infix[i])) {
            if (cprOperator(infix[i], topChar(&stack)) == 1) {
                postfix[j] = popChar(&stack);
                j++;
                pushOperator(&stack, infix[i]);
            } else if (cprOperator(infix[i], topChar(&stack)) == 0) {
                pushOperator(&stack, infix[i]);
            } else if (cprOperator(infix[i], topChar(&stack)) == -1) {
                while (topChar(&stack) != '(') {
                    postfix[j] = popChar(&stack);
                    j++;
                }
                popChar(&stack);
            }
        }
        i++;
    }

    while (topChar(&stack) != '\0') {
        postfix[j] = popChar(&stack);
        j++;
    }
}


int main() {
    char infixExpression[MAX_SIZE];
    char postfixExpression[MAX_SIZE];

    printf("Enter the infix expression\n");
    fgets(infixExpression, MAX_SIZE, stdin);
    infixExpression[strcspn(infixExpression, "\n")] = '\0';

    infixToPostfix(infixExpression, postfixExpression);
    printf("%s\n", postfixExpression);

    return 0;
}
