#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    int size;
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
    q->size++;
}

int dequeue(Queue* q) {
    if (!q->front) return -1;
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    q->size--;
    return data;
}

int front(Queue* q) {
    return q->front ? q->front->data : -1;
}

int size(Queue* q) {
    return q->size;
}

bool empty(Queue* q) {
    return q->size == 0;
}

void freeQueue(Queue* q) {
    while (!empty(q)) dequeue(q);
    free(q);
}

typedef struct {
    Queue* q;
} MyStack;

MyStack* myStackCreate() {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->q = createQueue();
    return stack;
}

void myStackPush(MyStack* obj, int x) {
    int sz = size(obj->q);
    enqueue(obj->q, x);
    for (int i = 0; i < sz; i++) {
        enqueue(obj->q, dequeue(obj->q));
    }
}

int myStackPop(MyStack* obj) {
    return dequeue(obj->q);
}

int myStackTop(MyStack* obj) {
    return front(obj->q);
}

bool myStackEmpty(MyStack* obj) {
    return empty(obj->q);
}

void myStackFree(MyStack* obj) {
    freeQueue(obj->q);
    free(obj);
}



/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/