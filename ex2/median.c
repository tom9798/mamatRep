#include <stdio.h>
#include <stdlib.h>

int main (){
    char gradesPath[100];
    FILE *grades;
    scanf("%s",gradesPath);
    grades = fopen(gradesPath, "r");
    if (grades == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    //perform a radix sort on the grades
    int gradesArray[1000];
    int gradesCount = 0;
    while (fscanf(grades, "%d", &gradesArray[gradesCount]) != EOF){
        gradesCount++;
    }
    //perform a radix sort on the grades
    int max = gradesArray[0];
    for (int i = 1; i < gradesCount; i++){
        if (gradesArray[i] > max){
            max = gradesArray[i];
        }
    }
    int exp = 1;
    int *output = (int *)malloc(gradesCount * sizeof(int));
    while (max / exp > 0){
        int count[10] = {0};
        for (int i = 0; i < gradesCount; i++){
            count[(gradesArray[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }
        for (int i = gradesCount - 1; i >= 0; i--){
            output[count[(gradesArray[i] / exp) % 10] - 1] = gradesArray[i];
            count[(gradesArray[i] / exp) % 10]--;
        }
        for (int i = 0; i < gradesCount; i++){
            gradesArray[i] = output[i];
        }
        exp *= 10;
    }
    //find the median
    if (gradesCount % 2 == 0){
        printf("%d\n", (gradesArray[gradesCount / 2 - 1] + gradesArray[gradesCount / 2]) / 2);
    fclose(grades);
    return 0;
}
