void phase_3(char *input) {
    int index, value;
    int array[] = {749, 380, 568, -65, 0, -65};
    // array = {369, -188, 633, -65, +65, -65}

    if (sscanf(input, "%d %d", &index, &value) <= 1) {
        explode_bomb();
    }

    if (index > 7) {
        explode_bomb();
    }

    int result = array[index];
    if (result != value) {
        explode_bomb();
    }
}