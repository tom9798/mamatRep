#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void search(int j, char *pattern, char *line, int i, bool *linePrinted, int line_number) {
    int offset = j;
    if (line[i + j - offset] != pattern[j]) {
        return;
    }
    j++;
    if (pattern[j] == '\'' && !*linePrinted) {
        *linePrinted = true;
        printf("%d: %s", line_number, line);
    }
}

void my_grep(FILE *f, char *pattern){
    int size = 0;
    int l = 0;
    while (pattern[l] != '\0') {
        if (pattern[l] != '\'' && pattern[l] != '^' && pattern[l] != '$' && pattern[l] != '*') {
            size++;
        }
        l++;
    }

    int length = 0;
    char line[1000];
    int line_number = 0;
    int check;
    bool linePrinted;

    switch (pattern[0]) {
        case '^': check = 1; break;
        case '$': check = 2; break;
        case '.': check = 3; break;
        default: check =0; break;
    }

    if (pattern[size-1]=='*'){
        check = 4;
    }

    while(fgets(line, 1000, f) != NULL){

        line_number++;

        //get the line length
        while (line[length-1] != '\n' && line[length] != '\0') {
            //if it's the last line, add 1 to the length
            length++;
        }
        if (line[length-1] != '\n') {
            length++;
        }

        linePrinted = false;

        //going through the line
        for(int i = 0; i < length; i++) {
            if (line[i] == '\0') {
                break;
            }

            //the pattern is somewhere in the line
            if (check == 0) {
                search(1, pattern, line, i, &linePrinted, line_number);
            }


            //^ means the pattern is at the beginning of the line
            if(check == 1 & i == 0) {
                search(2, pattern, line, i, &linePrinted, line_number);
            }


            //$ means the pattern is at the end of the line
            if(check == 2 & i == length - size - 1) {
                search(2, pattern, line, i, &linePrinted, line_number);
            }
        }
        length = 0;
    }
    return;
}

int main(int argc, char *argv[]) {
    FILE *f;
    if(argc == 1 || argv[1] == "-"){
        f=stdin;
    }else{
        f=fopen(argv[1], "r");
        if(f==NULL){
            printf("Error occurred\n");
            return 1;
        }
    }
    my_grep(f, argv[2]);
    fclose(f);
    return 0;
}