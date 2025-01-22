#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

void phase_5(char *input) {
    int num1, num2;
    if (sscanf(input, "%d %d", &num1, &num2) != 2) {
        explode_bomb();
    }

    num1 = num1 % 16; // masking the last 4 bits of the first integer
    if (num1 == 0xf) {
        explode_bomb();
    }

    int sum = 0; // sum = 0
    int count = 0; // counter = 0
    int values[] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5}; // the array

    while (num1 != 0xf) { // while loop until num1 % 16 == 15
        sum += values[num1];
        num1++;
        count++;
    }

    if (count != 0xf || sum != num2) { // check if the counter is 15 and compare the sum with the second integer
        explode_bomb();
    }
}





//void phase_5(char *input) {
//    int num1, num2;
//    if (sscanf(input, "%d %d", &num1, &num2) != 2) {
//        explode_bomb();
//    }
//
//    num1 = num1%16;
//    if (num1 == 0xf) {
//        explode_bomb();
//    }
//
//    int sum = 0;
//    int count = 0;
//    int values[] = {10, 2};
//
//    while (num1%16 != 0xf) {
//        sum += values[num1];
//        num1++;
//        count++;
//    }
//
//    if (count != 0xf || sum != num2) {
//        explode_bomb();
//    }