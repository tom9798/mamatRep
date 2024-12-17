#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

// Function to calculate the length of a string
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to check if a character matches, considering '.' wildcard
int char_match(char c, char p) {
    return (p == '.') || (c == p);
}

// Helper function to match from a specific point in the line
int match_from(const char *line, const char *pattern) {
    if (*pattern == '\0') {
        return 1;
    }
    if (*pattern == '$' && *(pattern + 1) == '\0') {
        return *line == '\0' || *line == '\n';
    }

    if (*(pattern + 1) == '*') {
        while (*line && char_match(*line, *pattern)) {
            if (match_from(line, pattern + 2)) {
                return 1;
            }
            line++;
        }
        return match_from(line, pattern + 2);
    }
    if (*line && char_match(*line, *pattern)) {
        return match_from(line + 1, pattern + 1);
    }

    return 0;
}

// Function to match a line against a pattern
int match_pattern(const char *line, const char *pattern) {
    if (pattern[0] == '^') {  // Pattern should match from the start
        return match_from(line, pattern + 1);
    }

    int line_len = my_strlen(line);
    int pattern_len = my_strlen(pattern);
    for (int i = 0; i <= line_len - pattern_len; i++) {
        if (match_from(line + i, pattern)) {
            return 1;
        }
    }
    return 0;
}

// Function to search lines in a file
void search_in_file(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (match_pattern(line, pattern)) {
            printf("%s: %s", filename, line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    search_in_file(argv[1], argv[2]);
    return 0;
}
