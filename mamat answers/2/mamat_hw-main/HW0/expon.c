/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUM_PRIME 10



int main()
{
    int a;
    scanf("%d", &a);
    if(a == 1) {
        printf("%d", a);
        return 0;
    }

    int prime_factors_a[MAX_NUM_PRIME] = {0};
    int hist_prime_a[MAX_NUM_PRIME] = {0};
    int total_factors_a = 0;

    int smallest_factor = 2;
    int temp = a;
    while ((smallest_factor <= a/2) && (temp > 1)) {
        if (temp % smallest_factor == 0) {
            prime_factors_a[total_factors_a] = smallest_factor;
            while (temp % smallest_factor == 0) {
                hist_prime_a[total_factors_a]++;
                temp /= smallest_factor;
            }
            total_factors_a++;
        }
        smallest_factor++;
    }

    if(total_factors_a == 0) {

        total_factors_a = 1;
        hist_prime_a[0] = 1;
        prime_factors_a[0] = a;
    }

    for (int N = 2; N < a ; N++) {
        //printf("%d\n", N);
        smallest_factor = 2;
        temp = N;
        int prime_factors_N[MAX_NUM_PRIME] = {0};
        int hist_prime_N[MAX_NUM_PRIME] = {0};
        int total_factors_N = 0;

        while ((smallest_factor <= a/2) && (temp > 1)) {
            if(temp % smallest_factor == 0) {
                prime_factors_N[total_factors_N] = smallest_factor;
                while (temp % smallest_factor == 0) {
                    hist_prime_N[total_factors_N]++;
                    temp /= smallest_factor;
                }
                total_factors_N++;
            }
            smallest_factor++;
        }

        if(total_factors_N == 0) {
            total_factors_N = 1;
            hist_prime_N[0] = 1;
            prime_factors_N[0] = N;
        }

        if (total_factors_N >= total_factors_a) {
            bool flag = true;
            for (int i = 0; i < total_factors_N; i++) {

                if ((prime_factors_a[i] != prime_factors_N[i]) ||
                    (hist_prime_a[i] > N*hist_prime_N[i])) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                printf("%d\n\n", N);
                return 0;
            }

        }
    }
    printf("%d\n\n", a);
    return 0;
}
