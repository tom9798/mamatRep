#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEF_BINS 10
#define HIGHEST_GRADE 100
#define LOWEST_GRADE 0

static FILE *f;
static int nbins = 10;

void operate(int *bins);
void parse_argument(int argc, char **argv);

//the function uses parse_arguments, searches the requested file and 
//allocates a histogram according to input
//int argc represents the number of arguments excpects 2 else uses defaults
//argv should contain the file name and number of bins 
//main returns 1 if file name not found and 0 if the operation was a success
int main(int argc, char **argv) {

    parse_argument(argc, argv);

    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    int *bins = (int*)calloc(nbins, sizeof(int));
    if(!bins) {
        fprintf(stderr, "Memory allocation failed\n");
    }

    operate(bins);
    free(bins);
    fclose(f);

    return 0;
}
//function operate filles the histogram in array bins 
//according to the gardes in the file and prints it
//function operate gets pointer to a array bins as input 
//the function is void type therfore doesn't have a return value
void operate(int *bins) {
    int grade;
    int retval;
    double pace;
    int line_n;

    line_n = 0;

    while(1) {
        retval = fscanf(f, "%d", &grade);
        if(retval == EOF) {
            break;
        } else if(retval != 1) {
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }

        if (grade < LOWEST_GRADE || grade > HIGHEST_GRADE) {
			fprintf(stderr, "Error:  Invalid number in line %d\n", line_n+1);
		} else {
    //grade is valid and scanf is a sucsses
    //filling in the histogram
                if (grade == HIGHEST_GRADE) {
                    bins[nbins-1]++;
                } else {
                    int n = grade / (HIGHEST_GRADE / nbins);
                    bins[n]++;
                }
		}
        line_n++;
    }

    //print the histogram 
    pace = 100.0 / nbins;
    for (int i = 0; i < nbins; i++) {
        printf("%.0lf-%.0lf\t%d\n", i * pace,
                (i < nbins-1) ? (((i+1)*pace)-1) : HIGHEST_GRADE, bins[i]);               
    }
}

//the function verifies the input and intialize number of bins
//int argc represents the number of arguments excpects 2 else uses defaults
//argv should contain the file name and number of bins 
//the function is void type therfore doesn't have a return value
void parse_argument(int argc, char **argv) {
    f = stdin;
    for (int i=0; i < argc; i++)
    {
        if(!strcmp(argv[i], "-")) {
            f = stdin;
        } else if (!strcmp(argv[i], "-n_bins")) {
            nbins = (i < argc -1) ? atoi(argv[i+1]) : DEF_BINS;
            i++;
        } else {
            f = fopen(argv[i], "r");
        }
    }
    
}
