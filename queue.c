#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node* node_t;

struct node {
	void* data;
	node_t next;
};

struct queue {
	/* Operations must be O(1), so use a linked list */
	int length;
	node_t front, back;
};

struct node* node_create(void *data) {
	// Allocate memory for the new node
	node_t new_node = (node_t) malloc(sizeof(struct node));
	// Set data and make it the end of the queue
	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}

queue_t queue_create(void) {
	// Allocate memory for a new queue
	queue_t new_queue = (queue_t) malloc(sizeof(struct queue));

	// Check that queue was successfully allocated
	if (new_queue == NULL) {
		return NULL;
	} else {
		new_queue->front = NULL;
		new_queue->back = NULL;
		new_queue->length = 0;

		return new_queue;
	}
}

int queue_destroy(queue_t queue) {
	// Return: -1 if @queue is NULL or not empty, 0 if queue was successfully destroyed
	if ((queue == NULL) || (queue->length != 0)) {
		return -1;
	}
	
	// Queue exists and is not empty
	free((queue_t) queue);
	queue = NULL;
	return 0;
}

int queue_enqueue(queue_t queue, void *data) {
	// Check if queue and *data are not NULL
	if ((queue == NULL) || (data == NULL)) {
		return -1;
	}
	// Create a new node with the node_create function
	node_t new_node = node_create(data);

	if (queue->back == NULL) {
		// Queue exists, but is empty
		queue->front = new_node;
		queue->back = new_node;
	} else {
		// Queue exists and contains at least one node
		queue->back->next = new_node;
		queue->back = new_node;
	}
	// Update the new queue size
	++queue->length;
	
	return 0;
}

int queue_dequeue(queue_t queue, void **data) {
	// Return: -1 if queue is empty, or either argument is NULL; otherwise return 0
	if ((queue == NULL) || (queue->length == 0) || (*data == NULL)) {
		return -1;
	}

	// Store node temporarily and set next node as front node
	node_t old_node = queue->front;
	queue->front = queue->front->next;

	// If there are no more nodes in the queue make the queue empty
	if (queue->front == NULL) {
		queue->back = NULL;
	}

	// Update the size
	queue->length--;
	// Free the old_node
	*data = old_node->data;
	free((node_t) old_node);
	return 0;
}

int queue_delete(queue_t queue, void *data) {
	// Verify the queue, data, and length are valid
	if ((queue == NULL) || (queue->length == 0) || (data == NULL)) {
		return -1;
	}

	// Get the current node
	node_t currentNode = queue->front;
	node_t previousNode = NULL;
	// temp will hold the queue front until delete is complete
	node_t temp = queue->front;

	// If the to-be-deleted node is at the front
	if (currentNode->data == data) {
		// Set the front node to the next node
		queue->front = queue->front->next;
		free((node_t) temp);
		// Update queue size
		queue->length--;
		// If the queue is empty
		if (queue->front == NULL) {
			queue->back = NULL;
		}
		return 0;
	} else {
		// If the to-be-deleted node is somewhere else
		// Go through rest of queue until end or match is made
		while((currentNode != NULL) && (currentNode->data != data)) {
			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		if(currentNode == NULL) {
			// If you are at the end of the queue
			return -1;
		} else {
			// Otherwise node is found
			temp = currentNode;
			previousNode->next = currentNode->next;
			free((node_t) temp);
			// Update length
			queue->length--;
			// Scenario where the removed node is the last node in the queue
			if(previousNode->next == NULL) {
				queue->back = previousNode;
			}
		}
	}
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func) {
	// Check if queue and func exist
	if ((queue == NULL) || (func == NULL)) {
		return -1;
	}

	// Get the front of the queue
	node_t currentNode = queue->front;
	node_t nextNode = currentNode->next;

	// Continue until you reach the back of the queue
	while(currentNode != NULL) {
		// Run func(queue, currentNode->data) and then go to next node
		nextNode = currentNode->next;
		(*func)(queue, currentNode->data);
		currentNode = nextNode;
	}
	
	return 0;
}

int queue_length(queue_t queue) {
	// Get queue length and return it
	int length = -1;
	if(queue != NULL) {
		length = queue->length;
	}
	return length;
}