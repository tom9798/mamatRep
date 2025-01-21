void phase_2(char *input) {
    int numbers[6];
    if (read_six_numbers(input, numbers) != 6) {
        explode_bomb();
    }

    for (int i = 1; i < 6; i++) {
        if (numbers[i] != numbers[i - 1] + i + 1) {
            explode_bomb();
        }
    }
}