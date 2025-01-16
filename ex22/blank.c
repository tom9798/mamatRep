#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void my_grep(FILE *f, char *pattern) {
    int size = 0;
    int l = 0;

    // Calculate size of the pattern inside single quotes if present
    while (pattern[l] != '\0') {
        if (pattern[l] == '\'') {
            l++;
            while (pattern[l] != '\0' && pattern[l] != '\'') {
                size++;
                l++;
            }
            break;
        }
        l++;
    }

    // If no single quotes, consider the entire pattern length
    if (size == 0) {
        while (pattern[size] != '\0') {
            size++;
        }
    }

    int check = 0;
    switch (pattern[0]) {
        case '^': check = 1; break;
        case '$': check = 2; break;
        case '.': check = 3; break;
        default: check = 0; break;
    }
    if (pattern[size - 1] == '*') {
        check = 4;
    }

    char line[1000];
    int line_number = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        line_number++;
        int length = 0;

        // Calculate the length of the line
        while (line[length] != '\0') {
            length++;
        }

        // Remove the newline character at the end of the line if present
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
            length--;
        }

        for (int i = 0; i < length; i++) {
            if (line[i] == '\0') {
                break;
            }

            // ^ means the pattern is at the beginning of the line
            if (check == 1 && i == 0) {
                int j = 1;
                while (pattern[j] != '\0') {
                    if (line[i + j - 1] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '\0') {
                    printf("%d: %s\n", line_number, line);
                }
            }

            // $ means the pattern is at the end of the line
            if (check == 2 && length >= size - 1) {
                int j = 0;
                while (pattern[j] != '\0' && pattern[j] != '$') {
                    if (line[length - size + j] != pattern[j]) {
                        break;
                    }
                    j++;
                }
                if (pattern[j] == '$') {
                    printf("%d: %s\n", line_number, line);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *f;
    if (argc < 3) {
        printf("Usage: %s <filename> <pattern>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    my_grep(f, argv[2]);
    fclose(f);
    return 0;
}
