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

//func4 output for input x=7,y=4 is 132