#include "grades.h"
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"


//define course struct with functions
typedef struct course {
    char *name;
    int grade;
} course;

//clone course
int course_clone(void *element, void **output) {
    course* course = (course*)element;
    course* new_course = (course*)malloc(sizeof(course));
    if (new_course == NULL) {
        return 1;
    }
    new_course->name = (char*)malloc(strlen(course->name) + 1);
    if (new_course->name == NULL) {
        free(new_course);
        return 1;
    }
    strcpy(new_course->name, course->name);
    new_course->grade = course->grade;
    *output = new_course;
    return 0;
}

//destroy course
void course_destroy(void *element) {
    course* course = (course*)element;
    free(course->name);
    free(course);
}



//define student struct with functions
typedef struct student {
    char *name;
    int id;
    struct list *courses;
} student;

//clone student
int student_clone(void *element, void **output) {
    student* student = (student*)element;
    student* new_student = (student*)malloc(sizeof(student));
    if (new_student == NULL) {
        return 1;
    }
    new_student->name = (char*)malloc(strlen(student->name) + 1);
    if (new_student->name == NULL) {
        free(new_student);
        return 1;
    }
    strcpy(new_student->name, student->name);
    new_student->id = student->id;

    new_student->courses = list_init(course_clone, course_destroy);
    if (new_student->courses == NULL) {
        free(new_student->name);
        free(new_student);
        return 1;
    }
    *output = new_student;
    return 0;
}

//destroy student
void student_destroy(void *element) {
    student *student = (student*)element;
    free(student->name);
    list_destroy(student->courses);
    free(student);
}

//define grades struct and functions
typedef struct grades {
    struct list *students;
} grades;

struct grades* grades_init() {
    grades *grades = malloc(sizeof(grades));
    if (grades == NULL) {
        return NULL;
    }
    grades->students = list_init(student_clone, student_destroy);
    if (grades->students == NULL) {
        free(grades);
        return NULL;
    }
    return grades;
}

void grades_destroy(grades *grades) {
    list_destroy(grades->students);
    free(grades);
}

int grades_add_student(grades *grades, const char *name, int id) {
    student *student = malloc(sizeof(student));
    if (student == NULL) {
        return 1;
    }
    student->name = (char*)malloc(strlen(name) + 1);
    if (student->name == NULL) {
        free(student);
        return 1;
    }
    strcpy(student->name, name);
    student->id = id;
    student->courses = list_init(course_clone, course_destroy);
    if (student->courses == NULL) {
        free(student->name);
        free(student);
        return 1;
    }
    if (list_push_back(grades->students, student) != 0) {
        free(student->name);
        list_destroy(student->courses);
        free(student);
        return 1;
    }
    return 0;
}

int grades_add_grade(grades *grades, const char *name, int id, int grade) {
    if (grade < 0 || grade > 100) {
        return 1;
    }
    struct iterator *it = list_begin(grades->students);
    while (it) {
        student *student = list_get(it);
        if (student->id == id && student->name != name) {
            course *course = malloc(sizeof(course));
            if (course == NULL) {
                return 1;
            }
            course->name = (char*)malloc(strlen(name) + 1);
            if (course->name == NULL) {
                free(course);
                return 1;
            }
            strcpy(course->name, name);
            course->grade = grade;
            if (list_push_back(student->courses, course) != 0) {
                free(course->name);
                free(course);
                return 1;
            }
            return 0;
        }
        it = list_next(it);
    }
    return 1;
}

float grades_calc_avg(grades *grades, int id, char **out) {
    struct iterator *it = list_begin(grades->students);
    while (it) {
        student *student = list_get(it);
        if (student->id == id) {
            struct iterator *it2 = list_begin(student->courses);
            int sum = 0;
            int count = 0;
            while (it2) {
                course *course = list_get(it2);
                sum += course->grade;
                count++;
                it2 = list_next(it2);
            }
            if (count == 0) {
                *out = NULL;
                return 0;
            }
            *out = malloc(strlen(student->name) + 1);
            if (*out == NULL) {
                return -1;
            }
            strcpy(*out, student->name);
            return (float)sum / count;
        }
        it = list_next(it);
    }
    *out = NULL;
    return -1;
}

//check if list begin is the first element inserted
int grades_print_student(grades *grades, int id) {
    struct iterator *it = list_begin(grades->students);
    while (it) {
        student *student = list_get(it);
        if (student->id == id) {
            printf("%s %d: ", student->name, student->id);
            struct iterator *it2 = list_begin(student->courses);
            while (it2) {
                course *course = list_get(it2);
                printf("%s %d, ", course->name, course->grade);
                it2 = list_next(it2);
            }
            printf("\n");
            return 0;
        }
        it = list_next(it);
    }
    return 1;
}

int grades_print_all(grades *grades) {
    if (grades->students == NULL) {
        return 1;
    }
    struct iterator *it = list_begin(grades->students);
    while (it) {
        student *student = list_get(it);
        printf("%s %d: ", student->name, student->id);
        struct iterator *it2 = list_begin(student->courses);
        while (it2) {
            course *course = list_get(it2);
            printf("%s %d, ", course->name, course->grade);
            it2 = list_next(it2);
        }
        printf("\n");
        it = list_next(it);
    }
    return 0;
}