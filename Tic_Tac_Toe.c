#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Stack structure to store previous values for undo
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize the stack
void initStack(struct Stack *s) {
    s->top = -1;
}

// Push a value onto the stack
void push(struct Stack *s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

// Pop a value from the stack
int pop(struct Stack *s) {
    if (s->top == -1) {
        return -1; // Indicates empty stack
    }
    return s->arr[(s->top)--];
}

// Check if the stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int main() {
    struct Stack undoStack;
    int currentValue = 0; // Current value in the game
    int choice;
    int targetValue;
    int moves = 0;

    initStack(&undoStack);

    // Generate a random target between 20 and 69
    srand(time(0));
    targetValue = rand() % 50 + 20;

    printf("\n     TARGET STACK: UNDO CHALLENGE     \n");
    printf("Target Value: %d\n\n", targetValue);
    printf("Rules:\n");
    printf("1. Start from 0 and reach the target value.\n");
    printf("2. You can perform the following operations:\n");
    printf("   - Add 1\n");
    printf("   - Add 5\n");
    printf("   - Multiply by 2\n");
    printf("3. Use 'Undo' to revert to the previous value.\n");
    printf("4. Try to reach the target in minimum moves.\n\n");

    while (1) {
        printf("Current Value: %d | Moves: %d\n", currentValue, moves);
        printf("Choose an action:\n");
        printf("1. Add 1\n");
        printf("2. Add 5\n");
        printf("3. Multiply by 2\n");
        printf("4. Undo\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                push(&undoStack, currentValue); // Save current state
                currentValue += 1;
                moves++;
                printf("Added 1!\n\n");
                break;

            case 2:
                push(&undoStack, currentValue);
                currentValue += 5;
                moves++;
                printf("Added 5!\n\n");
                break;

            case 3:
                push(&undoStack, currentValue);
                currentValue *= 2;
                moves++;
                printf("Multiplied by 2!\n\n");
                break;

            case 4:
                if (isEmpty(&undoStack)) {
                    printf("Nothing to undo!\n\n");
                } else {
                    currentValue = pop(&undoStack); // Restore previous value
                    moves++;
                    printf("Undo successful!\n\n");
                }
                break;

            case 5:
                printf("Exiting game...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n\n");
        }

        // Check for victory
        if (currentValue == targetValue) {
            printf("\n  You reached the target value!  \n");
            printf("Total moves: %d\n", moves);
            break;
        }

        // Check if user exceeded target
        if (currentValue > targetValue) {
            printf("   You exceeded the target! Try undo.\n\n");
        }
    }

    return 0;
}
