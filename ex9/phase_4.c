void phase_4(char *input) {
    int num1, num2;
    if (sscanf(input, "%d %d", &num1, &num2) != 2) {
        explode_bomb();
    }

    if (num1 < 2 || num1 > 4) {
        explode_bomb();
    }

    int result = func4(num1, 7);
    if (result != num2) {
        explode_bomb();
    }
}

int func4(int x, int y) {
    if (x <= 0) {
        return 0;
    }
    if (x == 1) {
        return y;
    }
    return y + func4(x - 1, y) + func4(x - 2, y);
}

//func4 stages for input x=7,y=4 are:
// 1. 4 + func4(6, 4) + func4(5, 4)
// 2. 4 + (4 + func4(5, 4) + func4(4, 4)) + (4 + func4(4, 4) + func4(3, 4))
// 3. 4 + (4 + (4 + func4(4, 4) + func4(3, 4)) + (4 + func4(3, 4) + func4(2, 4))) + (4 + (4 + func4(3, 4) + func4(2, 4)) + (4 + func4(2, 4) + func4(1, 4)))
// 4. 4 + (4 + (4 + (4 + func4(3, 4) + func4(2, 4)) + (4 + func4(2, 4) + func4(1, 4))) + (4 + (4 + func4(2, 4) + func4(1, 4)) + (4 + func4(1, 4) + 4)) + (4 + (4 + func4(2, 4) + func4(1, 4)) + (4 + func4(1, 4) + 4))
// 5. 4 + (4 + (4 + (4 + (4 + func4(2, 4) + func4(1, 4)) + (4 + func4(1, 4) + 4)) + (4 + (4 + func4(1, 4) + 4) + (4 + 4 + 4))) + (4 + (4 + func4(1, 4) + 4) + (4 + 4 + 4)) + (4 + (4 + func4(1, 4) + 4) + (4 + 4 + 4))
// 6. 4 + (4 + (4 + (4 + (4 + 4 + 4) + (4 + 4 + 4)) + (4 + (4 + 4 + 4) + (4 + 4 + 4))) + (4 + (4 + 4 + 4) + (4 + 4 + 4)) + (4 + (4 + 4 + 4) + (4 + 4 + 4))
// 7. 4 + (4 + (4 + (4 + 12 + 12) + (4 + 12 + 12)) + (4 + 12 + 12) + (4 + 12 + 12))
// 8. 4 + (4 + (4 + 28) + 28 + 28)
// 9. 4 + (4 + 32 + 28)
// 10. 4 + 64
// 11. 68