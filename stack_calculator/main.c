#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_SIZE 50

typedef struct Node {
    int data;
    char operator;
    struct Node *next;
} Node;

Node *stack = NULL;

Node *init() {
    return NULL;
}

// Push a node onto the stack
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

// Push a data node onto the stack
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

// Push an operator node onto the stack
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

// Pop the top node from the stack
void pop(Node **top) {
    if (*top == NULL) {
        return;
    } else {
        Node *temp = (*top)->next;
        free(*top);
        *top = temp;
    }
}

// Pop the top operator from the stack and return it
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

// Get the top operator from the stack without removing it
char topChar(Node **top) {
    if (*top == NULL) {
        return '\0';
    } else {
        return (*top)->operator;
    }
}

// Get the top data from the stack without removing it
int topInt(Node **top) {
    if (*top == NULL) {
        return INT_MIN;
    } else {
        return (*top)->data;
    }
}

// Print the stack elements
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

// Check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

// Compare operators based on precedence
int compareOperator(char c, char stackOperator) {
    switch (c) {
        case '+':
        case '-':
            switch (stackOperator) {
                case '*':
                case '/':
                    return 1; // Higher precedence
                default:
                    return 0;
            }
        case ')':
            return -1;
        default:
            return 0;
    }
}

// Convert infix expression to postfix expression
void infixToPostfix(char *infix, Node **postfix) {
    int i = 0;
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
            if (compareOperator(infix[i], topChar(&stack)) == 1) {
                // If the operator has higher precedence, push the top operator from the stack to the postfix expression
                pushOperator(postfix, popChar(&stack));
                // Push the current operator onto the stack
                pushOperator(&stack, infix[i]);
            } else if (compareOperator(infix[i], topChar(&stack)) == 0) {
                // If operators have the same precedence, push the current operator onto the stack
                pushOperator(&stack, infix[i]);
            } else if (compareOperator(infix[i], topChar(&stack)) == -1) {
                // If the current operator is ')', pop operators from the stack and push them to the postfix expression
                // until '(' is encountered on the stack
                while (topChar(&stack) != '(') {
                    pushOperator(postfix, popChar(&stack));
                }
                // Pop '(' from the stack
                popChar(&stack);
            }
            i++;
        }
    }

    // Pop any remaining operators from the stack to the postfix expression
    while (topChar(&stack) != '\0') {
        pushOperator(postfix, popChar(&stack));
    }
}

// Delete the entire stack
void deleteStack(Node **top) {
    Node *current = *top;
    while (current != NULL) {
        *top = current->next;
        free(current);
        current = *top;
    }
}

// Inverse the order of elements in the stack
void inverseStack(Node **temp, Node **new) {
    while (*temp != NULL) {
        pushNode(new, *temp);
        pop(temp);
    }
}

// Calculate the result of the postfix expression
int calculatePostfix(Node **top) {
    Node *calc = NULL;
    Node *current = *top;
    int number = 0;
    while (current != NULL) {
        if (current->operator == '\0') { // This node has data
            pushData(&calc, current->data);
        } else if (isOperator(current->operator)) { // This node has an operator
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
        current = current->next;
    }
    return number;
}

int main() {
    char infixExpression[MAX_SIZE];

    Node *temp = NULL;
    Node *postfixExpression = NULL;

    printf("Enter the infix expression:\n");
    fgets(infixExpression, MAX_SIZE, stdin);
    infixExpression[strcspn(infixExpression, "\n")] = '\0';

    infixToPostfix(infixExpression, &temp);

    // Reverse the order of elements in the temporary stack to get the postfix expression
    inverseStack(&temp, &postfixExpression);

    // Print the postfix expression
    printf("Postfix: ");
    printStack(&postfixExpression);

    // Calculate and print the result of the postfix expression
    printf("Result: %d", calculatePostfix(&postfixExpression));

    // Delete the dynamically allocated memory used for the stacks
    deleteStack(&postfixExpression);
    deleteStack(&stack);
    deleteStack(&temp);

    return 0;
}