#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//./my_grep file.txt "a*b" will search for "a*b" in file.txt
//^ is the beginning of the line
//$ is the end of the line
//. is any character
//* is 0 or more of the preceding character

//don't use strstr command
//return the line number and the line

//if the pattern is not found, return -1
//if the pattern is found, return the line number

void my_grep(FILE *f, char *pattern){
    char line[1000];
    int line_number = 0;
    while(fgets(line, 1000, f) != NULL){
        line_number++;
        for(int i = 0; i < 1000; i++){
            if(line[i] == '\0'){
                break;
            }
            if(line[i] == pattern[0]){
                int j = 0;
                while(pattern[j] != '\0'){
                    if(line[i+j] != pattern[j]){
                        break;
                    }
                    j++;
                }
                if(pattern[j] == '\0'){
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
    if(argc == 1 || !strcmp(argv[1], "-")){
        f=stdin;
    }else{
        f=fopen(argv[1], "r");
        if(f==NULL){
            printf("Error opening file\n");
            return 1;
        }
    }
    my_grep(f, argv[2]);
    fclose(f);
    return 0;
}