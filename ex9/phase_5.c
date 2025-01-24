#include <stdio.h>

void phase_5() {
    int num1, num2;
    int sum = 0;
    int counter = 0;
    int array[] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5};

    if (scanf("%d %d", &num1, &num2) != 2) {
        explode_bomb();
    }

    num1 &= 0xf;
    if (num1 == 0xf) {
        explode_bomb();
    }

    while (array[num1] != 0xf) {
        sum += array[num1];
        counter++;
        num1 = array[num1];
    }

    num1 = 0xf;
    if (counter != 0xf || sum != num2) {
        explode_bomb();
    }
}

//this code does:
//1. read two integers from the input
//2. mask the last 4 bits of the first integer
//3. if the masked integer is 0xf, explode
//4. sum the values in the array until the value in the array is 0xf
//5. if the counter is not 0xf or the sum is not equal to the second integer, explode
//6. return
//the input is the two integers
//the array is {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5}
//the first integer is used as an index to the array
//the value in the array is used as the next index











//#include <stdio.h>
//#include <stdint.h>
//
//void function() {
//    // Allocate space on the stack
//    uint64_t x;
//    uint64_t sum = 0;
//    uint64_t counter = 0;
//    uint64_t arr[] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5};
//
//    // Scan the input into an array with two integers
//    if (scanf("%lu", &x) <= 1) {
//        // Handle error case
//        return;
//    }
//
//    // Move the first integer into x
//    x = x & 0x0F; // Masking the last 4 bits of the first integer
//    if (x == 0x0F) {
//        // Handle bomb case
//        return;
//    }
//
//    // Main computation loop
//    while (1) {
//        sum += arr[counter];
//        if (x == 0x0F) {
//            break;
//        }
//        counter++;
//        if (counter >= sizeof(arr) / sizeof(arr[0])) {
//            break;
//        }
//    }
//
//    if (counter != 0x0F) {
//        // Handle bomb case
//        return;
//    }
//
//    // Compare the sum with the second integer
//    if (sum != x) {
//        // Handle bomb case
//        return;
//    }
//
//    // Clean up and return
//    return;
//}




//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "support.h"
//
//void phase_5(char *input) {
//    int num1, num2;
//    if (sscanf(input, "%d %d", &num1, &num2) != 2) {
//        explode_bomb();
//    }
//
//    num1 = num1 % 16; // masking the last 4 bits of the first integer
//    if (num1 == 0xf) {
//        explode_bomb();
//    }
//
//    int sum = 0; // sum = 0
//    int count = 0; // counter = 0
//    int values[] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5}; // the array
//
//    while (num1 != 0xf) { // while loop until num1 % 16 == 15
//        sum += values[num1];
//        num1++;
//        count++;
//    }
//
//    if (count != 0xf || sum != num2) { // check if the counter is 15 and compare the sum with the second integer
//        explode_bomb();
//    }
//}





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