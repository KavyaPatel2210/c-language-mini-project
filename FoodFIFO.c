#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10
#define MENU_SIZE 10

// Structure for Circular Queue
struct CircularQueue {
    int front, rear, size;
    int orderQueue[MAX_QUEUE_SIZE];
    char orderDetails[MAX_QUEUE_SIZE][100];
    float billAmounts[MAX_QUEUE_SIZE];
};

// Structure for Menu Item
struct MenuItem {
    int itemNumber;
    char description[100];
    float price;
};

void initQueue(struct CircularQueue* q);
int isFull(struct CircularQueue* q);
int isEmpty(struct CircularQueue* q);
void enqueue(struct CircularQueue* q, int orderNumber, const char* details, float billAmount);
int dequeue(struct CircularQueue* q);
void viewOrder(struct CircularQueue* q, int orderNumber);
void generateBill(struct CircularQueue* q, int orderNumber);
void displayQueue(struct CircularQueue* q);
void displayMenu(struct MenuItem menu[], int menuSize);
void takeOrder(struct CircularQueue* q, struct MenuItem menu[], int menuSize);
void handleUserInput(struct CircularQueue* q, struct MenuItem menu[], int menuSize);

int main() {
    struct CircularQueue q;
    initQueue(&q);
    printf("\nData Structures : 202040301\nMini Project\nTitle : FOOD-F-I-F-O\nDeveloped by : \nKavya Patel(12302130501028)\nHetvi Koradiya(12302130501022)\n");

    struct MenuItem menu[MENU_SIZE] = {
        {1, "Paneer Butter Masala", 250.00},
        {2, "Veg Biryani", 300.00},
        {3, "Dal Makhani", 200.00},
        {4, "Butter Naan", 50.00},
        {5, "Veg Pulao", 150.00},
        {6, "Pav Bhaji", 180.00},
        {7, "Chole Bhature", 180.00},
        {8, "Karari Roti", 400.00},
        {9, "Gulab Jamun", 80.00},
        {10, "Masala Dosa", 120.00}
    };

    handleUserInput(&q, menu, MENU_SIZE);
    return 0;
}

void initQueue(struct CircularQueue* q) {
    q->front = q->rear = -1;
    q->size = 0;
}

int isFull(struct CircularQueue* q) {
    return q->size == MAX_QUEUE_SIZE;
}

int isEmpty(struct CircularQueue* q) {
    return q->size == 0;
}

void enqueue(struct CircularQueue* q, int orderNumber, const char* details, float billAmount) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more orders.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->orderQueue[q->rear] = orderNumber;
    strcpy(q->orderDetails[q->rear], details);
    q->billAmounts[q->rear] = billAmount;
    q->size++;
    printf("Order %d added.\n", orderNumber);
}

int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No orders to process.\n");
        return -1;
    }
    int orderNumber = q->orderQueue[q->front];
    q->size--;
    if (isEmpty(q)) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
    return orderNumber;
}

void viewOrder(struct CircularQueue* q, int orderNumber) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->front;
    while (1) {
        if (q->orderQueue[i] == orderNumber) {
            printf("Order Number: %d\n", orderNumber);
            printf("Details: %s\n", q->orderDetails[i]);
            return;
        }
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("Order %d not found.\n", orderNumber);
}

void generateBill(struct CircularQueue* q, int orderNumber) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->front;
    while (1) {
        if (q->orderQueue[i] == orderNumber) {
            printf("Bill for Order Number %d: %.2f rs\n", orderNumber, q->billAmounts[i]);
            return;
        }
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("Order %d not found.\n", orderNumber);
}

void displayQueue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->front;
    printf("Current Orders in Queue:\n");
    while (1) {
        printf("Order Number: %d, Details: %s, Bill: %.2f rs\n", q->orderQueue[i], q->orderDetails[i], q->billAmounts[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}

void displayMenu(struct MenuItem menu[], int menuSize) {
    printf("Menu:\n");
    for (int i = 0; i < menuSize; i++) {
        printf("Item Number: %d, Description: %s, Price: %.2f rs\n", menu[i].itemNumber, menu[i].description, menu[i].price);
    }
}

void takeOrder(struct CircularQueue* q, struct MenuItem menu[], int menuSize) {
    int itemNumber, quantity;
    char orderDetails[100];
    float totalBill;

    printf("Enter the menu item number to order: ");
    scanf("%d", &itemNumber);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    int i;
    for (i = 0; i < menuSize; i++) {
        if (menu[i].itemNumber == itemNumber) {
            break;
        }
    }

    if (i == menuSize) {
        printf("Invalid item number.\n");
        return;
    }

    totalBill = menu[i].price * quantity;

    sprintf(orderDetails, "%d x %s", quantity, menu[i].description);

    int orderNumber = (q->rear + 1) % MAX_QUEUE_SIZE + 1;

    enqueue(q, orderNumber, orderDetails, totalBill);
}

void handleUserInput(struct CircularQueue* q, struct MenuItem menu[], int menuSize) {
    int choice;
    while (1) {
        printf("\n----- FOOD F-I-F-O -----\n");
        printf("\n1. Display Menu\n");
        printf("2. Place an Order\n");
        printf("3. View an Order\n");
        printf("4. Generate Bill\n");
        printf("5. Process an Order\n");
        printf("6. Display All Orders\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, MENU_SIZE);
                break;
            case 2:
                takeOrder(q, menu, MENU_SIZE);
                break;
            case 3: {
                int orderNumber;
                printf("Enter order number to view: ");
                scanf("%d", &orderNumber);
                viewOrder(q, orderNumber);
                break;
            }
            case 4: {
                int orderNumber;
                printf("Enter order number to generate bill: ");
                scanf("%d", &orderNumber);
                generateBill(q, orderNumber);
                break;
            }
            case 5:
                printf("Processed Order Number: %d\n", dequeue(q));
                break;
            case 6:
                displayQueue(q);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
