#include "student.h"

char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    memcpy(new_str, str, len);
    return new_str;
}

void student_print(elem_t e) {
    if (is_pointer_NULL(e)) {
        return;
    }
    pstudent_t stu = (pstudent_t)e;
    fprintf(stdout,"student name: %s, age: %d, id: %d.\n",
    stu->name, stu->age, stu->id);
}

elem_t student_clone(elem_t e) {
    if (is_pointer_NULL(e)) {
        return NULL;
    }
    else {
        pstudent_t stu = (pstudent_t)e;
        pstudent_t pnew_stu = (pstudent_t)malloc(sizeof(student_t));
        if(is_pointer_NULL(pnew_stu)) {
            return NULL;
        }
        if(is_pointer_NULL(stu->name)){
            fprintf(stderr, "Error: name does not exists");
            return NULL;
        }
        if((stu->age) < 0){
            fprintf(stderr, "Error: invalid age");
            return NULL;
        }
         if((stu->id) < 0){
            fprintf(stderr, "Error: invalid id");
            return NULL;
        }
        pnew_stu->name = strdup(stu->name);
        pnew_stu->age = stu->age;
        pnew_stu->id = stu->id;
        return pnew_stu;
    }
}

void student_destroy(elem_t e) {
    if (is_pointer_NULL(e)) {
        return;
    }
    pstudent_t stu = (pstudent_t)e;
    free(stu->name);
    free(stu);
}