#include <stdio.h>

#define MAX_ARRAY_SIZE 10000

void twoSum(int nums[], int nums_size, int target);

int main() {
	int target;
	int nums[MAX_ARRAY_SIZE] = {0};
	int array_size = 0;

	scanf("%d", &target);

	while (scanf("%d", &nums[array_size++]) == 1);
	array_size--;

	twoSum(nums, array_size, target);

	return (0);
}

void twoSum(int nums[], int nums_size, int target) {
    //no sort option
//    for (int i = 0; i < nums_size; i++) {
//        for (int j = i + 1; j < nums_size; j++) {
//            if (nums[i] + nums[j] == target) {
//                printf("(%d, %d)\n", i, j);
//                return;
//            }
//        }
//    }

    //sort the array and create a copy of the original array
    int temp;
    int origin[nums_size];
    for (int i = 0; i < nums_size; i++) {
        origin[i] = nums[i];
    }
    for (int i = 0; i < nums_size; i++) {
        for (int j = i + 1; j < nums_size; j++) {
            if (nums[i] > nums[j]) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    //find the two numbers that add up to the target in the sorted array
    int left = 0;
    int right = nums_size - 1;
    int left_num = 0;
    int right_num = 0;
    while (left < right) {
        if (nums[left] + nums[right] == target) {
            left_num = nums[left];
            right_num = nums[right];
            break;
        } else if (nums[left] + nums[right] < target) {
            left++;
        } else {
            right--;
        }
    }
    //find the index of the two numbers
    for (int i = 0; i < nums_size; i++) {
        if (origin[i] == left_num) {
            left = i;
        }else if (origin[i] == right_num) {
            right = i;
            break;
        }
    }
    printf("(%d, %d)\n", left, right);
    return;
}
