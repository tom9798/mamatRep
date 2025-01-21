#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIGHEST_GRADE 100
#define LOWEST_GRADE 0

void operate(FILE *f);

//the function verifies the input and use operate function
//int argc represents the number of arguments 
//argv should contain the file name
//main returns 1 if file name not found and 0 if the operation was a success
int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}
	if(!f) {
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	operate(f);
	fclose(f);

	return 0;
}

//function operate calculates the minimun garde in the file and prints it
//function operate gets pointer to a file as input 
//the function is void type therfore doesn't have a return value
void operate(FILE *f) {
	int grade;
	int retval;
	int line_n;
	int min;

	line_n = 0;
	min = HIGHEST_GRADE;
//read file line by line and check if the grade is valid
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
			fprintf(stderr, "Error:  Invalid input in line %d\n", line_n+1);
			exit(1);
		}

		if (grade < LOWEST_GRADE || grade > HIGHEST_GRADE) {
			fprintf(stderr, "Error:  Invalid number in line %d\n", line_n+1);
		} else {
//grade is valid and scanf is a sucsses
// update min value according to current grade
			min = (grade < min) ? grade : min;
		}
		line_n++;
	}

	fprintf(stdout, "%d", min);

	return;
}