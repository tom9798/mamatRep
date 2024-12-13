#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to calculate the length of a string
int strlen_custom(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to check if a pattern matches at the beginning of the line
bool match_start(const char *line, const char *pattern) {
    int i = 0;
    while (pattern[i] != '\0' && line[i] != '\0') {
        if (pattern[i] != line[i]) {
            return false;
        }
        i++;
    }
    return pattern[i] == '\0';
}

// Function to check if a pattern matches at the end of the line
bool match_end(const char *line, const char *pattern) {
    int line_length = strlen_custom(line);
    int pattern_length = strlen_custom(pattern);

    if (pattern_length > line_length) {
        return false;
    }

    int offset = line_length - pattern_length;
    int i = 0;
    while (pattern[i] != '\0') {
        if (line[offset + i] != pattern[i]) {
            return false;
        }
        i++;
    }
    return true;
}

// Function to match the pattern with * (zero or more repetitions of the preceding character)
bool match_star(const char *line, const char *pattern) {
    if (pattern[0] == '\0') {
        return true;
    }

    if (pattern[1] != '*') {
        return match_start(line, pattern);
    }

    char preceding = pattern[0];
    const char *remaining_pattern = pattern + 2;
    int i = 0;

    while (line[i] != '\0') {
        if (match_star(line + i, remaining_pattern)) {
            return true;
        }
        if (line[i] != preceding && preceding != '.') {
            break;
        }
        i++;
    }
    return match_star(line + i, remaining_pattern);
}

// Function to search for a pattern in a line
bool search_pattern(const char *line, const char *pattern) {
    if (pattern[0] == '^') {
        return match_start(line, pattern + 1);
    }

    if (pattern[strlen_custom(pattern) - 1] == '$') {
        char subpattern[1000];
        int i;
        for (i = 0; pattern[i] != '$'; i++) {
            subpattern[i] = pattern[i];
        }
        subpattern[i] = '\0';
        return match_end(line, subpattern);
    }

    return match_star(line, pattern);
}

// Main function for grep
void my_grep(FILE *f, const char *pattern) {
    char line[1000];
    int line_number = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        line_number++;

        // Remove the newline character at the end of the line if present
        int length = strlen_custom(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }

        if (search_pattern(line, pattern)) {
            printf("%d: %s\n", line_number, line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <filename> <pattern>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    my_grep(f, argv[2]);
    fclose(f);
    return 0;
}
