#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
#include "stdlib.h"
#include "stdio.h"

typedef enum { SUCCESS = 0, FAIL } Result; 

typedef struct stack *pstack_t;
typedef void *elem_t;

/* ------------------------------------------ */
/* Add here declarations of function pointers */
/* ------------------------------------------ */

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);


/**
 * @fn bool is_pointer_NULL(elem_t e)
 * @brief check if the given pointer is null
 * @param e - a given pointer.
 * @return true if the pointer is null, false othwrwise.
 */
bool is_pointer_NULL(elem_t e);

/**
 * @fn pstack_t stack_create(size_t max_num_of_elem, clone_t user_clone,
                    destroy_t user_destroy, print_t user_print);
 * @brief creates the user_stack.
 * @param max_num_of_elem - max capacity of elements
 * @param user_clone - pointer to the userFunction that clones an element
 * @param user_destroy - pointer to the userFunction that destroys an element
 * @param user_print - pointer to the userFunction that prints an element
 * @return pointer to a stack
 */
pstack_t stack_create(size_t max_num_of_elem, clone_t user_clone,
                    destroy_t user_destroy, print_t user_print); //V

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return SUCCESS if the stack was destroied properly, FAIL else.
 */
 Result stack_destroy(pstack_t stack);

/**
 * @fn void stack_print(pstack_t stack);
 * @brief prints the user_stack
 * such first printed element is the last element inserted
 * @param stack - pointer to the stack to print
 * @return none
 */
void stack_print(pstack_t stack);

/**
 * @fn Result stack_push(pstack_t stack, elem_t e);
 * @brief inserts a clone of the user's element 
 * @param stack - pointer to the stack
 * @param e - pointer to the element to be inserted
 * @return Result SUCCESS/FAIL
 */
Result stack_push(pstack_t stack, elem_t e); 

/**
 * @fn void stack_pop(pstack_t stack);
 * @brief removes the last inserted element from the stack and destroys it
 * @param stack - pointer to the stack
 * @return none
 */
void stack_pop(pstack_t stack);

/**
 * @fn elem_t stack_peek(pstack_t stack);
 * @brief peeks the last element inserted to the stack
 * @param stack - pointer to the stack
 * @return - pointer to the last inserted element or NULL for FAIL
 */
elem_t stack_peek(pstack_t stack);

/**
 * @fn size_t stack_size(pstack_t stack);
 * @brief finds the  current size of the stack
 * @param stack - pointer to the stack
 * @return - current number of elements in the stack
 */
size_t stack_size(pstack_t stack); 

/**
 * @fn bool stack_is_empty(pstack_t stack);
 * @brief checks if the stack is empty or not
 * @param stack - pointer to the stack
 * @return true if the stack is empty. false if stack is not empty
 */
bool stack_is_empty(pstack_t stack); 

/**
 * @fn size_t stack_capacity(pstack_t stack);
 * @brief calculate how many places are free in the stack
 * @param stack - pointer to the stack
 * @return the number of available places in the stack
 */
size_t stack_capacity(pstack_t stack); 

#endif /* __STACK__ */