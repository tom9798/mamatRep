#include <stdio.h>
#include <stdlib.h>

void my_grep(FILE *f, char *pattern){
    char line[1000];
    int line_number = 0;
    int check = 0;
    switch (pattern[0]) {
        case '^': check = 1;
        case '$': check = 2;
        case '.': check = 3;
        case '*': check = 4;
    }
    while(fgets(line, 1000, f) != NULL){
        line_number++;
        for(int i = 0; i < 1000; i++) {
            if (line[i] == '\0') {
                break;
            }
            //check if the pattern is at the end of the line
            if (check == 1 & line[i] == pattern[1]) {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[i + j] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("Line %d: %s", line_number, line);
                    return;
                }
                //check if the pattern is at the beginning of the line
            } else if (check == 2 & line[i] == pattern[1]) {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[i + j] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("Line %d: %s", line_number, line);
                    return;
                }
            //check if a char is anywhere in the line
            } else if (check == 3 & line[i] == pattern[1]) {
                printf("Line %d: %s", line_number, line);
                return;
            //check if the previous char is in the line 0 or more times
            } else if (check == 4 & line[i] == pattern[1]) {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[i + j] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("Line %d: %s", line_number, line);
                    return;
                }
            }
        }
    }
    printf("-1\n");
    return;
}

int main(int argc, char *argv[]) {
    FILE *f;
    if(argc == 1 || argv[1]== "-"){
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


////check if the pattern is at the end of the line
//if(check == 1 & line[i+j] == '\0') {
//break;
//}
////check if the pattern is at the beginning of the line
//if(check == 2 & i == 0){
//break;
//}
