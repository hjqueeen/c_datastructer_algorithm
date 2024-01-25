#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct Queue {
    int *array;
    int front;
    int rear;
} Queue;

void init(Queue *queue) {
    // Allocate memory for the circular queue array
    queue->array = (int *)malloc(MAX_SIZE * sizeof(int));
    // Initialize front and rear to -1, indicating an empty queue
    queue->front = -1;
    queue->rear = -1;
}

int isEmpty(Queue *queue) {
    // Check if both front and rear are -1, indicating an empty queue
    return queue->rear == -1 && queue->front == -1;
}

int isFull(Queue *queue) {
    // Calculate the next index after rear
    int temp = (queue->rear + 1) % MAX_SIZE;
    // Check if it matches the front, indicating a full queue
    return temp == queue->front;
}

void enqueue(Queue *queue, int data) {
    if (isFull(queue)) {
        // Print an error message if trying to add to a full queue
        printf("Cannot add data. The queue is full.\n");
    } else if (isEmpty(queue)) {
        // If the queue is empty, set front and rear to 0 and add the data
        queue->front = 0;
        queue->rear = 0;
        queue->array[queue->rear] = data;
    } else {
        // Move rear to the next index and add the data
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        queue->array[queue->rear] = data;
    }
}

int dequeue(Queue *queue) {
    // Move front to the next index and return the data at the previous front
    queue->front++;
    return queue->array[queue->front - 1];
}

void printQueue(Queue *queue) {
    int i = queue->front;
    do {
        // Print each element in the circular queue
        printf("%d ", queue->array[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (queue->rear + 1) % MAX_SIZE);
    printf("\n");
}

void deleteQueue(Queue *queue) {
    // Free the dynamically allocated memory for the circular queue array
    free(queue->array);
}

int main() {
    Queue circular_queue;
    // Initialize the circular queue
    init(&circular_queue);
    char inputCode[MAX_SIZE];
    int code = -1;
    do {
        printf("=======================\n");
        printf("1: Add Number\n");
        printf("2: Dequeue\n");
        printf("3: Print Queue\n");
        printf("=======================\n");
        printf("0: Program end \n");
        // Read user input
        fgets(inputCode, sizeof(inputCode), stdin);
        fflush(stdin);
        // Convert the input to an integer
        code = (int)(inputCode[0] - '0');
        switch (code) {
            case 1:
                printf("Add Number:");
                char inputNr[MAX_SIZE];
                int number = 0;
                int i = 0;
                // Read user input for the number to enqueue
                fgets(inputNr, MAX_SIZE, stdin);
                inputNr[strcspn(inputNr, "\n")] = '\0';
                // Convert the input to an integer
                while (inputNr[i] != '\0') {
                    number = number * 10 + (inputNr[i++] - '0');
                }
                // Enqueue the number
                enqueue(&circular_queue, number);
                break;
            case 2:
                // Dequeue from the circular queue
                dequeue(&circular_queue);
                break;
            case 3:
                // Print the contents of the circular queue
                printQueue(&circular_queue);
                break;
            case 0:
                // Delete the circular queue and free memory before ending the program
                deleteQueue(&circular_queue);
                break;
            default:
                printf("Wrong input. Try again.\n");
                break;
        }
    } while (code != 0);
    return 0;
}