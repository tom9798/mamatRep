#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy(FILE *f, FILE *f2){
    char c;
    while((c=fgetc(f))!=EOF){
        fputc(c, f2);
    }
    return;
}

int main(int argc, char *argv[]) {
    FILE *f;
    FILE *f2;
    if(argc == 1 || !strcmp(argv[1], "-")){
        f=stdin;
    }else{
        f=fopen(argv[1], "r");
        if(f==NULL){
            printf("Error opening file\n");
            return 1;
        }
    }
    if(argc == 2 || !strcmp(argv[2], "-")){
        f2=stdout;
    }else{
        f2=fopen(argv[2], "w");
        if(f2==NULL){
            printf("Error opening file\n");
            return 1;
        }
    }
    copy(f, f2);
    fclose(f);
    fclose(f2);
    return 0;
}