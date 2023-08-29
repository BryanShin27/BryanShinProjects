#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct node node;
typedef struct node* node_t;

struct node {
    void* data;
    node_t next;
}

struct stack {
    int size;
    node_t top, bottom;
}

node_t node_create(void *data) {
    // Allocate memory for the new node
    node_t new_node = (node_t) malloc (sizeof(node));
    // Set data and make it the top
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

stack_t stack_create(void) {
    // Allocate memory for a new stack
    stack_t new_stack = (stack_t) malloc (sizeof(stack));

    // Check that stack was successfully allocated
    if (new_stack == NULL) {
        return NULL;
    } else {
        new_stack->top = NULL;
        new_stack->bottom = NULL;
        new_stack->length = 0;

        return new_stack;
    }
}

int stack_destroy(stack_t stack) {
    // Return: -1 if @stack is NULL or not empty, 0 if stack was successfully destroyed
    if ((stack == NULL) || (stack->length != 0)) {
        return -1;
    }

    // Stack exists and is not empty
    free((stack_t) stack);
    stack = NULL;
    return 0;
}

int stack_push(stack_t stack, void *data) {
    // Check if stack and *data are not NULL
    if ((stack == NULL) || (data == NULL)) {
        return -1;
    }
    // Create a new node
    node_t new_node = node_create(data);

    if (stack->bottom == NULL) {
        // Stack exists, but is empty
        stack->top = new_node;
        stack->bottom = new_node;
    } else {
        // Stack exists, and contains at least one item
        stack->bottom->next = new_node;
        stack->bottom = new_node;
    }

    // Update the stack size
    stack->length++;

    return 0;
}

int stack_pop(stack_t stack, void **data) {
    // Return: -1 if the stack is empty, or either argument is NULL; otherwise return 0
    if ((stack == NULL) || (stack->size == 0) || (*data == NULL)) {
        return -1;
    }

    // Store node temporarily and set next node as top node
    node_t old_node = stack->top;
    stack->top = stack->top->next;

    // If there are no more nodes in the stack, make the stack empty
    if (stack->top == NULL) {
        stack->bottom = NULL;
    }

    // Update the size of the stack
    stack->size--;
    // Free the old node
    *data = old_node->data;
    free((node_t) old_node);
    return 0;
}

int stack_delete(stack_t stack, void *data) {
    // Verify the stack, data, and size are all valid
    if ((queue == NULL) || (queue->length == 0) || (data == NULL)) {
        return -1;
    }

    // Get the current node
    node_t currentNode = queue->top;
    node_t previousNode = NULL;
    // temp will hold the stack top until delete is complete
    node_t tempNode = queue->top;

    // If the node-to-delete is at the top
    if (currentNode->data == data) {
        // Set the top node to the next node
        stack->top = stack->top->next;
        free((node_t) temp);
        // Update stack size
        stack->length--;
        // If the stack is empty
        if (stack->top == NULL) {
            stack->bottom = NULL;
        }
        return 0;
    } else {
        // If the node to delete is somewhere else,
        // go through the rest of the stack until the end, or match is found
        while ((currentNode != NULL) && (currentNode->data != data)) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    if (currentNode == NULL) {
        // if you reached the end of the stack
        return -1;
    } else {
        // otherwise match is found
        temp = currentNode;
        previousNode->next = currentNode->next;
        free((node_t) temp);
        // Update stack size
        stack->length--;
        // If removed node was last in queue
        if (previousNode->next == NULL) {
            stack->bottom = previousNode;
        }
    }

    return 0;
}

int stack_iterate(stack_t stack, stack_func_t func) {
    // Check if stack and func exist
    if ((stack == NULL) | (func == NULL)) {
        return -1;
    }

    // Get the top of the stack
    node_t currentNode = stack->top;
    node_t nextNode = currentNode->next;

    // Continue until you reach the bottom of the stack
    while (currentNode != NULL) {
        // Run func(queue, currentNode->data) and then go to the next node
        nextNode = currentNode->next;
        (*func)(queue, currentNode->data); 
        currentNode = nextNode;      
    }

    return 0;
}

int stack_size(stack_t stack) {
    // Get stack size and return it
    int size = -1;
    if (stack != NULL) {
        size = queue->size;
    }
    return size;
}

