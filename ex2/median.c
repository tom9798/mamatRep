#include <stdio.h>
#include <stdlib.h>

int main () {
    //open the grades file, sort the grades, find the median and print it
    FILE *grades_file = fopen("grades.in", "r");
    if (grades_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    //iterate through the file to get the number of grades
    int num_grades = 0;
    int grade;
    while (fscanf(grades_file, "%d", &grade) != EOF) {
        num_grades++;
    }
    //rewind the file
    rewind(grades_file);
    //read the grades into an array
    int *grades = (int *)malloc(num_grades * sizeof(int));
    for (int i = 0; i < num_grades; i++) {
        fscanf(grades_file, "%d", &grades[i]);
    }

//    int num_grades;
//    fscanf(grades_file, "%d", &num_grades);
//    int *grades = (int *)malloc(num_grades * sizeof(int));
//    for (int i = 0; i < num_grades; i++) {
//        fscanf(grades_file, "%d", &grades[i]);
//    }
    fclose(grades_file);
    //sort the grades
    for (int i = 0; i < num_grades - 1; i++) {
        for (int j = i + 1; j < num_grades; j++) {
            if (grades[i] > grades[j]) {
                int temp = grades[i];
                grades[i] = grades[j];
                grades[j] = temp;
            }
        }
    }
    //find the median
    int median;
    if (num_grades % 2 == 0) {
        median = (grades[num_grades / 2 - 1] + grades[num_grades / 2]) / 2;
    } else {
        median = grades[num_grades / 2];
    }
    return 0;
}