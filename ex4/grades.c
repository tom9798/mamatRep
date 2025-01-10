#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked-list.h"
#include "grades.h"
#include <stdbool.h>

typedef struct course {
    char *name;
    int grade;
} Course;

void course_destroy(void *elem) {
    Course *course = (Course*)elem;
    if (!course) {
        return;
    }
    if (course->name) {
        free(course->name);
    }
    free(course);
    return;
}

Course* init_course(const char *name, int grade) {
    Course *course = (Course*)malloc(sizeof(Course));
    if (!course) {
        return NULL;
    }
    if (!name) {
        free(course);
        return NULL;
    }
    course->name = (char*)malloc(strlen(name) + 1); //should we multiply by sizeof(char)?
    if (!course->name) {
        course_destroy(course);
        return NULL;
    }
    strcpy(course->name, name);
    course->grade = grade;
    return course;
}

int course_clone(void *elem, void **out) {
    Course *course = (Course*)elem;
    Course **clone = (Course**)out;
    if (!course) {
        return 1;
    }
    *clone = init_course(course->name, course->grade);
    if (!(*clone)) {
        return 1;
    }
    return 0;
}



typedef struct student {
    char *name;
    int id;
    struct list *courses_list;
} Student;

void student_destroy(void *elem) {
    Student *student = (Student*)elem;
    if (!student) {
        return;
    }
    if (student->name) {
        free(student->name);
    }
    list_destroy(student->courses_list);
    free(student);
    return;
}

Student* init_student(const char *name, int id) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (!student) {
        return NULL;
    }
    if (!name) {
        free(student);
        return NULL;
    }
    student->name = (char*)malloc(strlen(name) + 1); //should we multiply by sizeof(char)?
    if (!student->name) {
        student_destroy(student);
        return NULL;
    }
    strcpy(student->name, name);
    student->id = id;
    student->courses_list = list_init(course_clone, course_destroy);
    if (!student->courses_list) {
        student_destroy(student);
        return NULL;
    }
    return student;
}

int student_clone(void *elem, void **out) {
    Student *student = (Student*)elem;
    Student **clone = (Student**)out;
    if (!student) {
        return 1;
    }
    *clone = init_student(student->name, student->id);
    if (!(*clone)) {
        return 1;
    }
    struct iterator *it = list_begin(student->courses_list);
    while (it) {
        Course *course = list_get(it);
        Course *new_course = init_course(course->name, course->grade);
        if (!new_course) {
            student_destroy(*clone);
            return 1;
        }
        if (list_push_back((*clone)->courses_list, new_course) != 0) {
            student_destroy(*clone);
            return 1;
        }
        it = list_next(it);
    }
    return 0;
}

//####################check if typedef is problematic####################
typedef struct grades {
    struct list *students;
} Grades;

Grades* grades_init() {
    Grades *gradesL = (Grades*)malloc(sizeof(Grades));
    if (!gradesL) {
        return NULL;
    }
    gradesL->students = list_init(student_clone, student_destroy);
    if (!gradesL->students) {
        free(gradesL);
        return NULL;
    }
    return gradesL;
}

void grades_destroy(Grades *grades) {
    if (!grades) {
        return;
    }
    if (grades->students) {
        list_destroy(grades->students);
        free(grades);
        return;
    }
    return;
}

int grades_add_student(Grades *grades, const char *name, int id) {
    if (!grades || !grades->students) {
        return 1;
    }
    struct iterator *it = list_begin(grades->students);
    while (it) {
        Student *student = list_get(it);
        if (student->id == id) {
            return 1;
        }
        it = list_next(it);
    }
    Student *new_student = init_student(name, id);
    if (!new_student) {
        return 1;
    }
    if (list_push_back(grades->students, new_student) != 0) {
        student_destroy(new_student);
        return 1;
    }
    return 0;
}

int grades_add_grade(Grades *grades, const char *name, int id, int grade) {
    if (!grades || !grades->students || !name || grade < 0 || grade > 100) {
        return 1;
    }
    struct iterator* itStudent = list_begin(grades->students);
    while (itStudent) {
        //looking for the student with the id
        Student *student = list_get(itStudent); //current student in the iteration
        if (student->id == id){
            //now we will iterate through the courses of the relevant student
            struct iterator* itCourse = list_begin(student->courses_list);
            while (itCourse) {
                Course *course = list_get(itCourse);
                if (strcmp(course->name, name) == 0) { //if the course already exists than we return 1 to indicate failure
                    return 1;
                }
                itCourse = list_next(itCourse);
            }
            //if we got here it means that the course does not exist and we can add it
            Course *new_course = init_course(name, grade); //creating a new course template
            if (!new_course) {
                return 1;
            }
            if (list_push_back(student->courses_list, new_course) != 0) {
                course_destroy(new_course);
                return 1;
            }
            return 0;
        }
        itStudent = list_next(itStudent);
    }
    return 1;
}

float grades_calc_avg(Grades *grades, int id, char **out){
    if(!grades||!grades->students){
        *out = NULL;
        return -1;
    }
    //reach the relevant student with an iterator
    struct iterator* itStudent = list_begin(grades->students);
    while(itStudent){
        Student *student = list_get(itStudent);
        if(student->id == id){
            if (!student->courses_list) { //making sure the student has courses
                *out = NULL;
                return -1;
            }
            int sum = 0;
            struct iterator* itCourse = list_begin(student->courses_list); //now iterating through all the courses, summing the grades
            while(itCourse){
                Course* course = list_get(itStudent);
                sum += course->grade;
                itCourse = list_next(itCourse);
            }

            *out = (char*)malloc(strlen(student->name)+1); //allocating memory for the name of the student
            if(*out == NULL){
                return -1;
            }
            strcpy(*out, student->name); //copying the name of the student to the out variable
            return (float)sum/list_size(student->courses_list); //returning the average
        }
        itStudent = list_next(itStudent);
    }
    *out = NULL;
    return -1;
}

int grades_print_student(Grades *grades, int id){
    if(!grades||!grades->students){
        return 1;
    }
    struct iterator* itStudent = list_begin(grades->students);
    while(itStudent){
        Student *student = list_get(itStudent);
        if(student->id == id){
            if(!student->courses_list){ //making sure the student has courses
                return 1;
            }
            printf("%s %d: ", student->name, student->id); //STUDENT-NAME STUDENT-ID:
            struct iterator *itCourse = list_begin(student->courses_list);
            bool first = true;
            while (itCourse){
                if(!first){
                    printf(", ");
                }else{
                    first = false;
                }
                Course *course = list_get(itCourse);
                printf("%s %d", course->name, course->grade); //COURSE-1-NAME COURSE-1-GRADE, [...]
            }
            printf("\n");
            return 0;
        }
        itStudent = list_next(itStudent);
    }
    return 1;
}

int grades_print_all(Grades *grades){
    if(!grades||!grades->students){
        return 1;
    }
    struct iterator* itStudent = list_begin(grades->students);
    while(itStudent){
        Student *student = list_get(itStudent);
        grades_print_student(grades, student->id);
        itStudent = list_next(itStudent);
    }
    return 0;
}