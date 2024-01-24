#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Customer {
    char firstName[50];
    char lastName[50];
    int customerNumber;
    struct Customer *next;
} Customer;

typedef struct Queue {
    Customer *front;
    Customer *rear;
} Queue;

void init(Queue *queue) {
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return;
    }
    queue->front = NULL;
    queue->rear = NULL;
};

Queue *create() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failure\n");
        return NULL;
    }
    init(queue);
    return queue;
}

int isEmpty(Queue *queue) {
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return -1;
    }
    if (queue->front == NULL && queue->rear == NULL) {
        // Queue is empty
        return 1;
    } else {
        // Queue is not empty
        return 0;
    }
};

Customer *createNode(char *firstname, char *lastname, int customerNr) {
    Customer *new = (Customer *) malloc(sizeof(Customer));
    if (new == NULL) {
        printf("Memory allocation failure\n");
        return NULL;
    }
    strcpy(new->firstName, firstname);
    strcpy(new->lastName, lastname);
    new->customerNumber = customerNr;
    new->next = NULL;
    return new;
}

/*
 * Customer *node : node to add
 * return 0: enqueue success
 * return -1: enqueue failed
 */
int enqueue(Queue *queue, Customer *node) {
    if (queue == NULL || node == NULL) {
        printf("Error: Queue or Node is NULL\n");
        return -1;
    }

    if (isEmpty(queue)) {
        queue->front = node;
        queue->rear = node;
    } else {
        // Add new element to the end of queue
        queue->rear->next = node;
        // Update rear of queue
        queue->rear = node;
    }
    return 0;
};

/* Find the previous node of the node that matches the entered information. */
Customer *findPreNode(Queue *queue, char *firstName, char *lastName) {
    // Validation
    if (queue == NULL || isEmpty(queue)) {
        printf("Error: Queue is NULL or empty\n");
        return NULL;
    }
    // If first node matches
    if (queue->front->firstName == firstName && queue->front->lastName == lastName) {
        return queue->front;
    }
    // Search from second node
    Customer *current = queue->front->next;
    while (current != NULL) {
        if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
            return current;
        }
        current = current->next;
    }
    // Unable to find previous node
    return NULL;
};

int dequeue(Queue *queue) {
    if (queue == NULL || isEmpty(queue)) {
        printf("Error: Queue is NULL or empty\n");
        return -1;
    }
    Customer *toDequeue = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(toDequeue);
    return 0;
}

Customer *front(Queue *queue) {
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return NULL;
    } else if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return NULL;
    } else {
        return queue->front;
    }
};

int size(Queue *queue) {
    int count = 0;
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return -1;
    } else if (!isEmpty(queue)) {
        Customer *current = queue->front;
        while (current != NULL) {
            count++;
            current = current->next;
        }
    }
    return count;
};

void printNode(Customer *node) {
    if (node == NULL) {
        return;
    }
    printf("Customer Number: %d\n", node->customerNumber);
    printf("Customer Name: %s %s\n", node->firstName, node->lastName);
    printf("------------------------------------\n");
};

void printQueue(Queue *queue) {
    if (queue == NULL) {
        printf("Error: Queue is NULL\n");
        return;
    } else if (!isEmpty(queue)) {
        Customer *current = queue->front;
        while (current != NULL) {
            printNode(current);
            current = current->next;
        }
    }
};

void generateRandomName(char *name, int length) {
    // Define vowels and consonants
    char vowels[] = "aeiou";
    char consonants[] = "bcdfghjklmnpqrstvwxyz";

    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            // Choose a consonant for even indices
            name[i] = consonants[rand() % (sizeof(consonants) - 1)];
        } else {
            // Choose a vowel for odd indices
            name[i] = vowels[rand() % (sizeof(vowels) - 1)];
        }
    }

    name[0] = toupper(name[0]); // Convert the first character to uppercase
    name[length] = '\0'; // Add null character at the end of the string
}

int main() {
    Queue *myQueue = create();

    if (myQueue == NULL) {
        printf("Error: Queue is NULL\n");
        return -1;
    }

    int code = -1;
    int result = 0;
    int customerNr = 20030000;
    do {
        char firstName[50];
        char lastName[50];

        printf("=======================\n");
        printf("1: Add Customer\n");
        printf("2: Remove Customer\n");
        printf("3: Read First Customer\n");
        printf("4: Get Queue Size\n");
        printf("5: Print Queue\n");
        printf("6: Enqueue 10 random customers\n");
        printf("=======================\n");
        printf("0: Program end \n");
        scanf("%d", &code);

        if (code < 0 || code > 6) {
            printf("Input wrong\n");
            continue; // Go to the start
        }

        Customer *customer;
        switch (code) {
            case 1:
                // Get values from the console
                printf("Firstname:");
                scanf("%s", firstName);
                printf("Lastname:");
                scanf("%s", lastName);

                // Create customer
                customer = createNode(firstName, lastName, ++customerNr);
                if (customer == NULL) {
                    printf("Error: Unable to create customer.\n");
                    break;
                }
                // Add customer to the queue
                result = enqueue(myQueue, customer);
                if (result == -1) {
                    printf("Error: Unable to add customer.\n");
                } else {
                    printf("Customer added successfully.\n");
                }
                break;
            case 2:
                result = dequeue(myQueue);
                if (result == -1) {
                    printf("Error: Unable to delete customer.\n");
                } else {
                    printf("Customer deleted successfully.\n");
                }
                break;
            case 3:
                customer = front(myQueue);
                if (customer != NULL) {
                    printNode(customer);
                }
                break;
            case 4:
                result = size(myQueue);
                if (result > 0) {
                    printf("Queue Size: %d\n", result);
                }
                break;
            case 5:
                printQueue(myQueue);
                break;
            case 6:
                // Initialize the random number generator
                srand((unsigned int) time(NULL));
                for (int i = 0; i < 10; i++) {
                    generateRandomName(firstName, 6);
                    generateRandomName(lastName, 4);
                    customer = createNode(firstName, lastName, ++customerNr);
                    if (customer != NULL) {
                        enqueue(myQueue, customer);
                    }
                }
                printf("Success: Enqueue 10 random customers\n");
            default:
                break;
        }
    } while (code != 0);
    return 0;
}