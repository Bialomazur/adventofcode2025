#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Check if a number is invalid (made of two identical halves)
int is_invalid(int64_t num) {
    char buf[32];
    sprintf(buf, "%lld", num);
    int len = strlen(buf);
    if (len % 2 != 0) return 0;

    int half = len / 2;
    // Compare first half with second half
    for (int i = 0; i < half; i++) {
        if (buf[i] != buf[half + i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        perror("Could not open input.txt");
        return 1;
    }

    char line[1000000]; // Large enough for the single line input
    if (fgets(line, sizeof(line), f) == NULL) {
        fclose(f);
        fprintf(stderr, "Input file is empty\n");
        return 1;
    }
    fclose(f);

    // Remove trailing newline
    line[strcspn(line, "\n")] = 0;

    int64_t total = 0;
    char *token = strtok(line, ",");

    while (token != NULL) {
        int64_t start, end;
        if (sscanf(token, "%lld-%lld", &start, &end) != 2) {
            fprintf(stderr, "Bad range: %s\n", token);
            token = strtok(NULL, ",");
            continue;
        }

        for (int64_t n = start; n <= end; n++) {
            if (is_invalid(n)) {
                total += n;
            }
        }

        token = strtok(NULL, ",");
    }

    printf("%lld\n", total);
    return 0;
}