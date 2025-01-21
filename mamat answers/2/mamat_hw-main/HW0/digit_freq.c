/* Welcome to Mamat, 044101
 *
 * Use this project as a template for other C/C++ projects.
 * To copy this project, right-click on the project name "hello-world"
 * in the "project explorer" tab (left), then "copy" and finally "paste".
 *
 * To compile the project use "gcc" within the terminal.
 * To debug the project use "gdb" within the terminal.
 *
 * The red vertical line (right) represents the code width limit (80 chars).
 * Make sure not to cross it. */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define DIGIT 10
#define MAX 1001

int main() {
	char str[MAX] ;
	int hist[DIGIT] = {0};
	scanf("%s",str);
	int i=0;
	while (str[i] != '\0'){
	    int n = (str[i] - '0');
		if((n < DIGIT)&&(n > 0)){
			hist[n]++;
		}
	     i++;
	}
	for(int j =0 ;j < DIGIT; j++){
	    //printf("%d ", hist[j]);

	    printf("%d%c",hist[j], (j<9) ? ' ' :'\n');

	}
 return 0;
}

