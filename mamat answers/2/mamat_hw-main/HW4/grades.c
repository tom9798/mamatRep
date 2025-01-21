#include "grades.h"
#include "linked-list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {ERROR = -1, SUCCESS, FAIL};

//This function creates a duplicate of the input string str.
//It allocates memory for the new string and copies the contents of str into it.
//It returns a pointer to the newly allocated string.
char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    memcpy(new_str, str, len);
    return new_str;
}

//This function checks if a pointer ptr is NULL or not.
//It returns true if the pointer is NULL and false otherwise.
bool is_pointer_NULL(void* e) {
    return !e;
}

typedef struct course {
    char *name;
    int grade;
} *pcourse_t, course_t; 

typedef struct student {
    char *name;
    int id;
    struct list *courses;
} *pstudent_t, student_t;

typedef struct grades {
    struct list *students;
} *pgrades_t, grades_t;

void course_destroy(pcourse_t pcourse);
int course_clone(pcourse_t pcourse, pcourse_t *out);
void student_destroy(pstudent_t pstudent);
int student_clone(pstudent_t pstudent, pstudent_t *out);
pstudent_t find_id(pgrades_t grades, int id);
pcourse_t find_course(pstudent_t pstudent, const char *name);
void print_student(pstudent_t pstudent);

//This function frees the memory allocated for the course structure pointed
// to by pcourse.
//It also frees the memory allocated for the course name.
void course_destroy(pcourse_t pcourse) {
    free(pcourse->name);
    free(pcourse);
}

//This function creates a deep copy of the course structure pcourse.
//It stores the copy in the memory location pointed to by out.
//It returns SUCCESS if the cloning is successful, and FAIL otherwise.
int course_clone(pcourse_t pcourse, pcourse_t *out) {
    *out = NULL;
    if (is_pointer_NULL(pcourse)) {
        return FAIL;
    }
    pcourse_t pnew_course =  (pcourse_t)malloc(sizeof(course_t));
    if (is_pointer_NULL(pnew_course)) {
        return FAIL;
    }
    pnew_course->grade = pcourse->grade;
    pnew_course->name = strdup(pcourse->name);
    *out = pnew_course; 
    return SUCCESS;
}

//This function frees the memory allocated for the student structure pointed to
// by pstudent.
//It also frees the memory allocated for the student name and destroys the 
//linked list of courses.
void student_destroy(pstudent_t pstudent) {
    list_destroy(pstudent->courses);
    free(pstudent->name);
    free(pstudent);
}

//This function creates a deep copy of the student structure pstudent.
//It stores the copy in the memory location pointed to by out.
//It returns SUCCESS if the cloning is successful, and FAIL otherwise.
int student_clone(pstudent_t pstudent, pstudent_t *out) {
    *out = NULL;
    if (is_pointer_NULL(pstudent)) {
        return FAIL;
    }
    pstudent_t pnew_student = (pstudent_t)malloc(sizeof(student_t));
    if (is_pointer_NULL(pnew_student)) {
        return FAIL;
    }
    pnew_student->id = pstudent->id;
    pnew_student->name = strdup(pstudent->name);

    struct list* new_list = list_init((element_clone_t)course_clone, 
                                      (element_destroy_t)course_destroy);
    struct iterator *it = list_end(pstudent->courses);

    pcourse_t *new_course = NULL;
    pcourse_t cur_course;

    while (it != NULL) {
        cur_course = (pcourse_t)list_get(it);
        if(is_pointer_NULL(cur_course)){
            return FAIL;
        }
        if (course_clone(cur_course, new_course)) {
            return FAIL;
        }
        if (list_push_front(new_list, *new_course)) {
            return FAIL;
        }
        it = list_prev(it);
    }

    pnew_student->courses = new_list;
    *out = pnew_student;
    return SUCCESS;
}

struct grades* grades_init() {
    pgrades_t pgrades = (pgrades_t)malloc(sizeof(grades_t));
    if (is_pointer_NULL(pgrades)) {
        return NULL;
    }
    pgrades->students = list_init((element_clone_t)student_clone, 
                                  (element_destroy_t)student_destroy);
    if (is_pointer_NULL(pgrades->students)) {
        return NULL;
    }
    return pgrades;
}

void grades_destroy(struct grades *grades) {
    list_destroy(grades->students);
    free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id) {
    if (is_pointer_NULL(grades)) {
        return FAIL;
    }
    pstudent_t exist = find_id(grades, id);
    if (exist) {
        return FAIL;
    }
    pstudent_t pnew_student = (pstudent_t)malloc(sizeof(student_t));
    if (is_pointer_NULL(pnew_student)) {
        return FAIL;
    }
    pnew_student->name = strdup(name);
    pnew_student->id = id;
    pnew_student->courses = list_init((element_clone_t)course_clone, 
                                      (element_destroy_t)course_destroy);
    if (is_pointer_NULL(pnew_student->courses)) {
        return FAIL;
    }
    int check = list_push_front(grades->students, pnew_student);
    student_destroy(pnew_student); 
    return check;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade) {
    pstudent_t student = find_id(grades, id);
    if (grade < 0 || grade > 100 || !student || find_course(student, name)) {
        return FAIL;
    }
    pcourse_t pnew_course = (pcourse_t)malloc(sizeof(course_t));
    if (is_pointer_NULL(pnew_course)) {
        return FAIL;
    }
    pnew_course->name = strdup(name);
    pnew_course->grade = grade;
    int check = list_push_front(student->courses, pnew_course);
    course_destroy(pnew_course);
    return check;
}

float grades_calc_avg(struct grades *grades, int id, char **out) {
    *out = NULL;
    pstudent_t student = find_id(grades, id);
    if (!student) {
        
        return ERROR;
    }
    struct iterator *it = list_end(student->courses);
    float sum = 0;
    pcourse_t pcur_course;
    while (it != NULL) {
        pcur_course = list_get(it);
        if (!pcur_course) {
            return ERROR;
        }
        sum += pcur_course->grade;
        it = list_prev(it);
    }
    char *name = strdup(student->name);
    *out = name;
    int size = list_size(student->courses);
    if (size == 0) {
        return sum;
    }
    return sum / size;
}

int grades_print_student(struct grades *grades, int id) {
    pstudent_t pstudent = find_id(grades, id);
    if (!pstudent) {
        return FAIL;
    }
    print_student(pstudent);
    return SUCCESS;
}

int grades_print_all(struct grades *grades) {
    pstudent_t pcur_student;
    if (grades && (list_size(grades->students)) == 0) {
        return SUCCESS;
    }
    struct iterator *it = list_end(grades->students);
    if (it == NULL) {
        return FAIL;
    }
    while (it != NULL) {
        pcur_student = list_get(it);
        if (!pcur_student)  {
            return FAIL;
        }
        print_student(pcur_student);
        it = list_prev(it);
    }
    return SUCCESS;
}

//This function searches for a student with the given id within the grades 
//structure grades.
//It returns a pointer to the student if found, and NULL otherwise.
pstudent_t find_id(pgrades_t grades, int id) {
    if (is_pointer_NULL(grades)) {
        return NULL;
    }
    pstudent_t pcur_student;
    struct iterator *it = list_end(grades->students);
    while (it != NULL) {
        pcur_student = list_get(it);
        if (is_pointer_NULL(pcur_student)) {
            return NULL;
        }
        if (pcur_student->id == id) {
            return pcur_student;
        }
        it = list_prev(it);
    }
    return NULL;
}

//This function searches for a course with the given name within the student
// structure pstudent.
//It returns a pointer to the course if found, and NULL otherwise.
pcourse_t find_course(pstudent_t pstudent, const char *name) {
    if (is_pointer_NULL(pstudent)) {
        return NULL;
    }
    pcourse_t pcur_course;
    struct iterator *it = list_end(pstudent->courses);
    while (it != NULL) {
        pcur_course = (pcourse_t)list_get(it);
        if (is_pointer_NULL(pcur_course)) {
            return NULL;
        }
        if (!strcmp(pcur_course->name, name)) {
            return pcur_course;
        }
        it = list_prev(it);
    }
    return NULL;
}

//This function prints the details of the student, including their name, ID, 
//and the list of courses they are enrolled in, along with the corresponding 
//grades.
void print_student(pstudent_t pstudent) {
    fprintf(stdout, "%s %d:", pstudent->name, pstudent->id);
    pcourse_t pcur_course;
    struct iterator *it = list_end(pstudent->courses);
    if (it == NULL) {
        fprintf(stdout, "\n");
    }
    while (it != NULL) {
        pcur_course = list_get(it);
        pcourse_t first_course = list_get(list_begin(pstudent->courses));
        if (!first_course || !pcur_course) {
            return;
        }
        if (pcur_course == first_course) {
            fprintf(stdout, " %s %d\n", pcur_course->name, pcur_course->grade);
        } else {
            fprintf(stdout, " %s %d,", pcur_course->name, pcur_course->grade);
        }
        it = list_prev(it);
    }
}
