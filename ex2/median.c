#include <stdio.h>
#include <stdlib.h>

void openGradesFile(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        exit(1);
    }
    printf("File opened successfully\n");
    fclose(file);
}

int main() {
    char path[100];
    printf("Enter the path to the file: ");
    scanf("%s", path);
    openGradesFile(path);
    return 0;
}