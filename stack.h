#ifndef _STACK_H
#define _STACK_H

typedef struct stack stack;

/*
 * stack_t - Queue type
 *
 * A stack is a FILO data structure. Data items are pushed one after the
 * other.  When dequeueing, the queue must returned the oldest enqueued item
 * first and so on.
 *
 * Apart from delete and iterate operations, all operations should be O(1).
 */
typedef struct stack* stack_t;

/*
 * stack_create - Allocate an empty stack
 *
 * Create a new object of type 'struct stack' and return its address.
 *
 * Return: Pointer to new empty stack. NULL in case of failure when allocating
 * the new stack.
 */
stack_t stack_create(void);

/*
 * queue_destroy - Deallocate a queue
 * @queue: Queue to deallocate
 *
 * Deallocate the memory associated to the queue object pointed by @queue.
 *
 * Return: -1 if @queue is NULL or if @queue is not empty. 0 if @queue was
 * successfully destroyed.
 */
int stack_destroy(stack_t stack);

/*
 * stack_push - Push data item
 * @stack: Stack in which to push item
 * @data: Address of data item to push
 * 
 * Push the address contained in @data in the stack @stack.
 * 
 * Return: -1 if @stack or @data are NULL, or in case of memory allocation error
 * when pushing. 0 if @data was successfully pushed in @stack.
 */
int stack_push(stack_t stack, void *data);

/*
 * stack_pop - Pop data item
 * @stack: Stack in which to pop item
 * @data: Address of data pointer where item is received
 * 
 * Remove the newest item of stack @stack and assign this item (the value of a 
 * pointer) to @data.
 * 
 * Return: -1 if @stack or @data are NULL, or if the stack is empty. 0 if @data
 * was set with the oldest item available in @stack.
 * 
 */
int stack_pop(stack_t stack, void **data);

/*
 * stack_delete - Delete data item
 * @stack: Stack in which to delete item
 * @data: Data to delete
 * 
 * Find in stack @stack, the first (i.e. newest) item equal to @data and delete
 * this item.
 * 
 * Return: -1 if @queue or @data are NULL, or if @data was not found in the
 * stack. 0 if @data was found and deleted from @stack.
 * 
 */
int stack_delete(stack_t stack, void *data);

/*
 * stack_func_t - Stack callback function type
 * @stack: Stack to which item belongs
 * @data: Data item
 * 
 * Function to be run on each item using stack_iterate(). The current item is
 * received as @data.
 */
typedef void(*stack_func_t)(stack_t stack, void *data);

/*
 * stack_iterate - Iterate through a stack
 * @stack: Stack to iterate through
 * @func: Function to call on each stack item
 * 
 * This function iterates through the items in stack @stack, from the oldest
 * item to the newest item, and calls the given callback function @func on each
 * item. The callback function receives the current data item as parameter.
 * 
 * Note that this function should be resistant to data items being deleted
 * as part of the iteration (i.e. in @func).
 * 
 * Return: -1 if @stack or @func are NULL. 0 otherwise.
 */
int stack_iterate(stack_t stack, stack_func_t func);

/*
 * stack_length - Stack length
 * @stack: Stack to get the length of
 * 
 * Return the length of stack @stack.
 * 
 * Return: -1 if @stack is NULL. Length of @stack otherwise.
 */
int stack_size(stack_t stack);

#endif /* _STACK_H */
