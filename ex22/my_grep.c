#include <stdio.h>
#include <stdlib.h>

void my_grep(FILE *f, char *pattern){
    int size = 0;
    int l = 0;
    while (pattern[l] != '\0') {
        if (pattern[l] == '\'') {
            // Move to the next character after the opening single quote
            l++;
            while (pattern[l] != '\0' && pattern[l] != '\'') {
                size++;
                l++;
            }
            break;
        }
        l++;
    }
//    int size = sizeof pattern;
    int length = 0;
    char line[1000];
    int line_number = 0;
    int check = 0;
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
        while (line[length] != '\0') {
            length++;
        }
        for(int i = 0; i < length; i++) {
            if (line[i] == '\0') {
                break;
            }
            //^ means the pattern is at the beginning of the line
            if(check == 1 & i == 0) {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[i + j - 1] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("%d: %s", line_number, line);
                }
            }else if(check == 2 & line[length-1-size] == '\0') {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[length-size-2+j] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("%d: %s", line_number, line);
                }
            }
        }
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


////check if the pattern is at the end of the line
//if(check == 1 & line[i+j] == '\0') {
//break;
//}
////check if the pattern is at the beginning of the line
//if(check == 2 & i == 0){
//break;
//}
