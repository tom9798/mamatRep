//include all standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


void operate(FILE *f);

int main(int argc, char *argv[]) {
    FILE *f;
    if(argc == 1 || !strcmp(argv[1], "-")){
        f=stdin;
    }else{
        f=fopen(argv[1], "r");
        if(f==NULL){
            printf("Error opening file\n");
            return 1;
        }
    }
    operate(f);
}

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void operate(FILE *f){
    //read the file
    int num_grades = 0;
    int grade;
    int line = 0;
    while (fscanf(f, "%d", &grade) != EOF) {
        line += 1;
        if (grade>100 | grade <0){
//            printf("Error at line %d: invalid input %d\n", line, grade);
//print the error to the stderr
            fprintf(stderr, "Error at line %d: invalid input %d\n", line, grade);
            return;
        };
        num_grades++;
    }
    //rewind the file
    rewind(f);
    //read the grades into an array
    int *grades = (int *)malloc(num_grades * sizeof(int));
    for (int i = 0; i < num_grades - 1; i++) {
        fscanf(f, "%d", &grades[i]);
    }

    fclose(f);
    //sort the grades
//    for (int i = 0; i < num_grades - 1; i++) {
//        for (int j = i + 1; j < num_grades; j++) {
//            if (grades[i] > grades[j]) {
//                int temp = grades[i];
//                grades[i] = grades[j];
//                grades[j] = temp;
//            }
//        }
//    }
    qsort(grades, num_grades, sizeof(int), compare);

    //find the median
    int median;
    median = grades[(num_grades + 1)/ 2];
    printf("%d\n", median);
    free(grades);
    
    return;
}
