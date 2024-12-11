#include <stdio.h>
#include <stdlib.h>

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
