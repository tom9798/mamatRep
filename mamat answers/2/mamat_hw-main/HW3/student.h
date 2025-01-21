#ifndef __STUDENT__
#define __STUDENT__

#include "stack.h"
#include "stdlib.h"
#include <string.h>


typedef struct student {
	char *name;
	int age;
    int id;
}*pstudent_t, student_t;

/**
 * @fn elem_t student_clone(elem_t e)
 * @brief clones element student and returns pointer to new cloned student
 * @param e - pointer to existing element student
 * @return pointer to new element student
 */
elem_t student_clone(elem_t e);

/**
 * @fn void student_destroy(elem_t e)
 * @brief destoies element student
 * @param e - pointer to element student to be destroied
 * @return none
 */
void student_destroy(elem_t e);

/**
 * @fn elem_t student_clone(elem_t e)
 * @brief prints element student
 * @param e - pointer to element student to be printed
 * @return none
 */

void student_print(elem_t e);


#endif /* __STUDENT__ */ 