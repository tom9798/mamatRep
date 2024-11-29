#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE *grades;
    grades = fopen("grades.txt", "r");
    if (grades == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    int grade;
    int sum = 0;
    int count = 0;
    while (fscanf(grades, "%d", &grade) != EOF){
        sum += grade;
        count++;
    }
    printf("Average: %.2f\n", (float)sum/count);
    fclose(grades);
    return 0;
}