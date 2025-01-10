#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"
#include "linked-list.h"


/**
 * @typedef student_t
 * @brief 'student' struct shorthand.
 *
 * @struct student
 * @brief 'student' type for containing name, id and a list of courses.
 *
 * @var name
 * A pointer to a string (char array) defining the student's name.
 *
 * @var id
 * A student's ID number
 *
 * @var courses_list
 * A pointer to an initialized linked list struct used to dynamically
 * hold a list of 'struct course' holding the course name and a grade.
 * @see linked-list.h
 */
typedef struct student{
    char* name;
    int id;
    struct list* courses_list;
} student_t;


/**
 * @typedef course_t
 * @brief 'course' struct shorthand.
 *
 * @struct course
 * @brief 'course' type for containing course name and grade.
 *
 * @var name
 * A pointer to a string (char array) defining the course's name.
 *
 * @var grade
 * The course's grade.
 */
typedef struct course{
    char* name;
    int grade;
} course_t;


/**
 * @brief Initializes a course struct.
 * @param[in] name The name the course will have.
 * @param[in] grade The grade the course will have.
 * @note grade validity is checked by user, no restriction on grade value.
 * @returns Pointer to newly made 'struct course' type or NULL on fail.
 * @see course_t
 */
course_t* init_course(const char *name, int grade);

/**
 * @brief Makes a copy of a 'struct course' element and provides it to output.
 * @param[in] element Abstracted pointer to 'struct course'
 * @param[out] output Abstracted pointer to where a 'struct course' copy
 * should be saved to.
 * @returns 0 on success, 1 on fail.
 */
int course_clone(void *element, void **output);

/**
 * @brief Clears memory held by a 'struct course' element.
 * @param[in] element Abstracted pointer to 'struct course'
 */
void course_destroy(void *element);


/**
 * @brief Initializes a student struct.
 * @param[in] name The name the student will have.
 * @param[in] id The ID the student will have.
 * @note ID validity is checked by user, no restriction on ID value.
 *
 * @note Initialized student struct contains initialized and empty
 * linked list called courses_list.
 * @see linked-list.h
 * @returns Pointer to newly made 'struct student' type or NULL on fail.
 */
student_t* init_student(const char *name, int id);

/**
 * @brief Makes a copy of a 'struct student' element and provides it to output.
 * @param[in] element Abstracted pointer to 'struct student'
 * @param[out] output Abstracted pointer to where a 'struct student' copy
 * should be saved to.
 * @returns 0 on success, 1 on fail.
 */
int student_clone(void *element, void **output);

/**
 * @brief Clears memory held by a 'struct student' element.
 * @param[in] element Abstracted pointer to 'struct student'
 * @note Invokes list_destroy() and frees memory held by all course structs in
 * that student's courses_list.
 * @see linked-list.h
 */
void student_destroy(void *element);


/**
 * @brief Finds existing course in linked-list that matches the name provided.
 * @param[in] list Pointer to the linked-list of courses.
 * @param[in] name Pointer to the name it should compare to.
 * @return Returns iterator to the first 'struct course' with the same
 * name in the linked-list of courses or NULL if none found.
 * @note stops search on first match, does not account for duplicates.
 */
struct iterator* match_course_name(struct list *list, const char *name);

/**
 * @brief Finds existing student in linked-list that matches the ID provided.
 * @param[in] list Pointer to the linked-list of students.
 * @param[in] name The integer ID it should compare to.
 * @return Returns iterator to the first 'struct student' with the same
 * ID in the linked-list of students or NULL if none found.
 * @note stops search on first match, does not account for duplicates.
 */
struct iterator* match_student_id(struct list *list, int id);


/**
 * @struct grades
 * @brief Holds a list of students
 *
 * @var students
 * @brief A linked-list of 'struct student' elements.
 * @note Each student's grades are course-dependent and stored in
 * a linked-list of courses.
 * @see student_t
 * @see linked-list.h
 */
struct grades{
    struct list* students;
};

struct grades* grades_init(){
    struct grades* gradelist = (struct grades*)malloc(sizeof(struct grades));
    if(!gradelist){
        return NULL;
    }

    gradelist->students = list_init(student_clone, student_destroy);
    if(!gradelist->students){
        free(gradelist);
        return NULL;
    }

    return gradelist;
};



void grades_destroy(struct grades *grades){
    if((!grades) || (!grades->students)){
        return;
    }

    list_destroy(grades->students);
    free(grades);
    return;
}


int grades_add_student(struct grades *grades, const char *name, int id){
    if((!grades) || (!grades->students)){
        return 1;
    }

    if(match_student_id(grades->students, id)){
        return 1;
    }

    student_t* temp = init_student(name, id);
    if(!temp){
        return 1;
    }

    int result = list_push_back(grades->students, temp);
    student_destroy(temp);

    return result;
}


int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

    if((!grades) || (!grades->students) ||
       (!name) || (grade < 0) || (grade >100)){

        return 1;
    }

    struct iterator* index = match_student_id(grades->students, id);
    if(!index){
        return 1;
    }

    student_t* student = (student_t*)list_get(index);
    if((!student->courses_list) ||
       match_course_name(student->courses_list, name)){
        return 1;
    }

    course_t* temp = init_course(name, grade);
    if(!temp){
        return 1;
    }

    int result = list_push_back(student->courses_list, temp);
    course_destroy(temp);

    return result;
}


float grades_calc_avg(struct grades *grades, int id, char **out){
    if((!grades) || (!grades->students)){
        *out = NULL;
        return -1;
    }

    student_t* student = (student_t*)list_get(
            match_student_id(grades->students, id));

    if((!student) || (!student->courses_list)){
        *out = NULL;
        return -1;
    }
    *out = (char*)malloc((strlen(student->name) + 1)*sizeof(char));
    if(!(*out)){
        return -1;
    }
    strcpy(*out, student->name);

    int count = list_size(student->courses_list);
    int sum = 0;

    if(count == 0){
        return 0;
    }

    struct iterator* index_course = list_begin(student->courses_list);
    course_t* course;

    for(int i = 0; i < count; i++){
        course = (course_t*)list_get(index_course);
        sum += course->grade;
        index_course = list_next(index_course);
    }

    return ((float)sum/(float)count);
}


int grades_print_student(struct grades *grades, int id){
    if((!grades) || (!grades->students)){
        return 1;
    }

    student_t* student = (student_t*)list_get(
            match_student_id(grades->students, id));

    if((!student) || (!student->courses_list)){
        return 1;
    }

    struct iterator* index_course = list_begin(student->courses_list);
    course_t* course;

    printf("%s %d:", student->name, id);
    int max = list_size(student->courses_list);
    for(int i = 0; i < max; i++){
        course = (course_t*)list_get(index_course);
        printf("%s %s %d",(i ? "," : ""), course->name, course->grade);
        index_course = list_next(index_course);
    }
    printf("\n");
    return 0;
}


int grades_print_all(struct grades *grades){
    if((!grades) || (!grades->students)){
        return 1;
    }

    student_t* student;
    course_t* course;
    struct iterator* student_iterator = list_begin(grades->students);
    struct iterator* course_iterator;

    int student_count = list_size(grades->students);
    int course_count;
    for(int i = 0; i < student_count; i++){
        student = (student_t*)list_get(student_iterator);
        course_count = list_size(student->courses_list);
        course_iterator = list_begin(student->courses_list);

        printf("%s %d:", student->name, student->id);
        for(int j = 0; j < course_count; j++){
            course = (course_t*)list_get(course_iterator);
            printf("%s %s %d",(j ? "," : ""), course->name, course->grade);
            course_iterator = list_next(course_iterator);
        }
        printf("\n");
        student_iterator = list_next(student_iterator);
    }
    return 0;
}





course_t* init_course(const char *name, int grade){
    if(!name){
        return NULL;
    }

    course_t* course = (course_t*)malloc(sizeof(course_t));
    if(!course){
        return NULL;
    }

    course->name = (char*)malloc((strlen(name) + 1)*sizeof(char));
    if(!course->name){
        course_destroy(course);
        return NULL;
    }
    strcpy(course->name, name);
    course->grade = grade;

    return course;
}

int course_clone(void *element, void **output){
    course_t *course = (course_t*)element;
    course_t **clone = (course_t**)output;
    if((!course) || (!course->name)){
        return 1;
    }

    *clone = init_course(course->name, course->grade);
    if(!(*clone)){
        return 1;
    }

    return 0;
}

void course_destroy(void *element){
    course_t *course = (course_t*)element;
    if(!course){
        return;
    }

    if(course->name){
        free(course->name);
    }

    free(course);
    return;
}

student_t* init_student(const char *name, int id){
    if(!name){
        return NULL;
    }

    student_t* student = (student_t*)malloc(sizeof(student_t));
    if(!student){
        return NULL;
    }

    student->name = (char*)malloc((strlen(name) + 1)*sizeof(char));
    if(!student->name){
        student_destroy(student);
        return NULL;
    }
    strcpy(student->name, name);
    student->id = id;

    student->courses_list = list_init(course_clone, course_destroy);
    if(!student->courses_list){
        student_destroy(student);
        return NULL;
    }

    return student;
}

int student_clone(void *element, void **output){
    student_t* student = (student_t*)element;
    student_t** clone = (student_t**)output;
    if((!student) || (!student->name) || (!student->courses_list)){
        return 1;
    }

    *clone = init_student(student->name, student->id);
    if(!(*clone)){
        return 1;
    }

    struct iterator* index_original = list_begin(student->courses_list);
    course_t* course_original;

    int max = list_size(student->courses_list);
    for(int i = 0; i < max; i++){
        course_original = (course_t*)list_get(index_original);
        if((!course_original) ||
           (list_push_back((*clone)->courses_list,course_original))){

            student_destroy(*clone);
            return 1;
        }
        index_original = list_next(index_original);
    }

    return 0;
}

void student_destroy(void *element){
    student_t *student = (student_t*)element;
    if(!student){
        return;
    }

    if(student->name){
        free(student->name);
    }

    if(student->courses_list){
        list_destroy(student->courses_list);
    }

    free(student);
    return;
}

struct iterator* match_course_name(struct list *list, const char *name){
    struct iterator* index = list_begin(list);
    course_t* course;

    if(!index){
        return NULL;
    }

    int max = list_size(list);
    for(int i = 0; i < max; i++){
        course = (course_t*)list_get(index);
        if((!course) || (!course->name)){
            return NULL;
        }

        if(!strcmp(course->name,name)){
            return index;
        }

        index = list_next(index);
    }

    return NULL;
}
struct iterator* match_student_id(struct list *list, int id){
    struct iterator* index = list_begin(list);
    student_t* student;

    if(!index){
        return NULL;
    }

    int max = list_size(list);
    for(int i = 0; i < max; i++){
        student = (student_t*)list_get(index);
        if(!student){
            return NULL;
        }

        if(id == student->id){
            return index;
        }

        index = list_next(index);
    }

    return NULL;
}

