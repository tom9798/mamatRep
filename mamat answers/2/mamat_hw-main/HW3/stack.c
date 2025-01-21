#include "stack.h"

struct element {
    struct element *next;
    elem_t value;
};

struct stack {
    struct element *head;
    size_t max_num_of_elem;
    size_t cur_num_of_elem;
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
}; 

 pstack_t stack_create(size_t max_num_of_elem, clone_t user_clone,
                    destroy_t user_destroy, print_t user_print) {
    pstack_t s = (pstack_t)malloc(sizeof(struct stack));
    if(max_num_of_elem <= 0){
        fprintf(stderr,"Error:max number of elements should be a positive int");
        return NULL;
    }
    if(is_pointer_NULL(s) || is_pointer_NULL(user_clone) ||
        is_pointer_NULL(user_destroy) || is_pointer_NULL(user_print)) {
        return NULL;
    }
    s->head = NULL;
    s->max_num_of_elem = max_num_of_elem;
    s->cur_num_of_elem = 0;
    s->clone_func = user_clone;
    s->destroy_func = user_destroy;
    s->print_func = user_print;
    return s;
}

size_t stack_size(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return 0;
    }
    return stack->cur_num_of_elem;
}

bool stack_is_empty(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return false;
    }
    else if(stack->head == NULL)
        return true;
    return false;
}

size_t stack_capacity(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return 0;
    }
    return ((stack->max_num_of_elem) - (stack->cur_num_of_elem));
}

elem_t stack_peek(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return NULL;
    }
    return stack->head->value;
    // לשאול אם צריך להחזיר את הערך או את הראש!!!!! 
}

void stack_print(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return;
    }
    struct element *temp_e = stack->head;
    while (temp_e != NULL) {
        stack->print_func(temp_e->value);
        temp_e = temp_e->next;
    }
}

void stack_pop(pstack_t stack) {
    if (is_pointer_NULL(stack)){
        return;
    }
    struct element *temp_e = stack->head;
    stack->head = temp_e->next;
    stack->destroy_func(temp_e->value);
    temp_e->next = NULL;
    free(temp_e);
    stack->cur_num_of_elem--;
}

Result stack_push(pstack_t stack, elem_t e) {
    if (is_pointer_NULL(stack) || is_pointer_NULL(e)) {
        return FAIL;
    }
    if (stack_capacity(stack) == 0){
        fprintf(stderr, "Error: stack is full");
        return FAIL;
    }
    else {
        elem_t new_value = stack->clone_func(e);
        if (is_pointer_NULL(new_value)) {
            return FAIL;
        }
        else {
            struct element *new_head = 
                            (struct element*)malloc(sizeof(struct element));
            if(is_pointer_NULL(new_head)){
                return FAIL;
            }
            new_head->next = stack->head;
            new_head->value = new_value;

            stack->head = new_head;
            stack->cur_num_of_elem++;
            return SUCCESS;
        }
    }
}

Result stack_destroy(pstack_t stack) {
    if (is_pointer_NULL(stack)) {
        return FAIL;
    }
    else {
        struct element *cur = stack->head;
        while (cur != NULL) {
            struct element *temp_next = cur->next;
            cur->next = NULL;
            stack->destroy_func(cur->value);
            free(cur);
            cur = temp_next;
        }
        return SUCCESS;
    }
}

bool is_pointer_NULL(elem_t e) {
    if(e == NULL) {
        fprintf(stderr, "Error: pointer to NULL");
        return true;
    }
    return false;
}