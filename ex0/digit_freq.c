// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    char input[1000];
    int freq[10] = {0};
    //cat into stdin
    
    //printf("Enter a string: ");
    scanf("%s", input);
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            freq[input[i] - '0']++;
        }
    }
    //printf("Frequency of digits: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", freq[i]);
        if (i < 9) {
            printf(" ");
        }
    }
    printf("\n");
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}


