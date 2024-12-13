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
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] != '.' && line[i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

// Function to check if a pattern matches at the end of the line
bool match_end(const char *line, const char *pattern) {
    int line_length = strlen_custom(line);
    int pattern_length = strlen_custom(pattern);

    if (pattern_length > line_length) {
        return false;
    }

    int offset = line_length - pattern_length;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] != '.' && line[offset + i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

// Function to match the pattern with * (zero or more repetitions of the preceding character)
bool match_star(const char *line, const char *pattern) {
    if (pattern[0] == '\0') {
        return true;
    }

    char preceding = pattern[0];
    const char *remaining_pattern = pattern + 1;
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
    int pattern_length = strlen_custom(pattern);

    // Handle end of line '$' at the beginning of the pattern
    if (pattern[0] == '$' && pattern[1] == '\'') {
        return match_end(line, pattern + 2);
    }

    // Handle beginning of line '^' at the beginning of the pattern
    if (pattern[0] == '^' && pattern[1] == '\'') {
        return match_start(line, pattern + 2);
    }

    // Handle * after the single quotes at the end of the pattern
    if (pattern[pattern_length - 1] == '*' && pattern[pattern_length - 2] == '\'') {
        char preceding = pattern[pattern_length - 3];
        char subpattern[1000];
        for (int i = 1; i < pattern_length - 3; i++) {
            subpattern[i - 1] = pattern[i];
        }
        subpattern[pattern_length - 3] = '\0';
        return match_star(line, subpattern);
    }

    // Handle . character in the pattern
    if (pattern[0] == '\'' && pattern[1] == '.') {
        char subpattern[1000];
        for (int i = 1; i < pattern_length - 2; i++) {
            subpattern[i - 1] = pattern[i];
        }
        subpattern[pattern_length - 2] = '\0';
        return match_start(line, subpattern);
    }

    // Handle simple pattern match
    if (pattern[0] == '\'') {
        int i = 1;
        while (pattern[i] != '\'' && pattern[i] != '\0') {
            i++;
        }
        if (pattern[i] == '\'') {
            char subpattern[1000];
            for (int j = 1; j < i; j++) {
                subpattern[j - 1] = pattern[j];
            }
            subpattern[i - 1] = '\0';
            return match_start(line, subpattern);
        }
    }

    return false; // No match found
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
