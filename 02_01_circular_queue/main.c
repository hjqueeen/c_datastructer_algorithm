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
    queue->array = (int *) malloc(MAX_SIZE * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
}

int isEmpty(Queue *queue) {
    return queue->rear == -1 && queue->front == -1;
}

int isFull(Queue *queue) {
    int temp = (queue->rear + 1) % MAX_SIZE;
    return temp == queue->front;
}

void enqueue(Queue *queue, int data) {
    if (isFull(queue)) {
        printf("Cannot add data.\n");
    } else if (isEmpty(queue)) {
        queue->front = 0;
        queue->rear = 0;
        queue->array[queue->rear] = data;
    } else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        queue->array[queue->rear] = data;
    }
}

int dequeue(Queue *queue) {
    queue->front++;
    return queue->array[queue->front - 1];
}

void printQueue(Queue *queue) {
    int i = queue->front;
    do {
        printf("%d ", queue->array[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (queue->rear + 1) % MAX_SIZE);
    printf("\n");
}
void deleteQueue(Queue *queue){
    free(queue->array);
}

int main() {
    Queue circular_queue;
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
        fgets(inputCode, sizeof(inputCode), stdin);
        fflush(stdin);
        code = (int) (inputCode[0] - '0');
        switch (code) {
            case 1:
                printf("Add Number:");
                char inputNr[MAX_SIZE];
                int number = 0;
                int i = 0;
                fgets(inputNr, MAX_SIZE, stdin);
                inputNr[strcspn(inputNr, "\n")] = '\0';
                while (inputNr[i] != '\0') {
                    number = number * 10 + (inputNr[i++] - '0');
                }
                enqueue(&circular_queue, number);
                break;
            case 2:
                dequeue(&circular_queue);
                break;
            case 3:
                printQueue(&circular_queue);
                break;
            case 0:
                deleteQueue(&circular_queue);
                break;
            default:
                printf("Wrong input. Try again.\n");
                break;
        }
    } while (code != 0);
    return 0;
}
