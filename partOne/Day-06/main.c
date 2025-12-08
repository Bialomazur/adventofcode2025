#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 5000
#define MAX_WIDTH 10000

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        perror("input.txt");
        return 1;
    }

    char *lines[MAX_LINES];
    int linecount = 0;
    char buffer[MAX_WIDTH + 5];
    int width = 0;

    // Read all lines
    while (fgets(buffer, sizeof(buffer), f)) {
        int len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';

        lines[linecount] = malloc(len + 1);
        strcpy(lines[linecount], buffer);
        if (len > width) width = len;
        linecount++;
    }
    fclose(f);

    // Normalize line lengths to same width (pad with spaces)
    for (int i = 0; i < linecount; i++) {
        int len = strlen(lines[i]);
        if (len < width) {
            lines[i] = realloc(lines[i], width + 1);
            for (int j = len; j < width; j++) lines[i][j] = ' ';
            lines[i][width] = '\0';
        }
    }

    long long grand_total = 0;

    int col = 0;
    while (col < width) {

        // Skip blank columns (problem separator)
        int is_blank = 1;
        for (int r = 0; r < linecount; r++) {
            if (lines[r][col] != ' ') {
                is_blank = 0;
                break;
            }
        }
        if (is_blank) {
            col++;
            continue;
        }

        // Identify contiguous non-blank column block (a problem)
        int start = col;
        int end = col;
        for (; end < width; end++) {
            int blank = 1;
            for (int r = 0; r < linecount; r++) {
                if (lines[r][end] != ' ') { blank = 0; break; }
            }
            if (blank) break;
        }

        // Extract rows inside this block
        long long numbers[MAX_LINES];
        int numcount = 0;
        char op = '?';

        for (int r = 0; r < linecount; r++) {
            int s = start;
            int e = end - 1;

            // trim leading/trailing spaces
            while (s <= e && lines[r][s] == ' ') s++;
            while (e >= s && lines[r][e] == ' ') e--;

            if (s > e) continue; // empty row

            // If it's one char and is + or * → operator row
            if (s == e && (lines[r][s] == '+' || lines[r][s] == '*')) {
                op = lines[r][s];
            } else {
                // Parse number
                char numbuf[1000];
                int idx = 0;
                for (int c = s; c <= e; c++)
                    numbuf[idx++] = lines[r][c];
                numbuf[idx] = '\0';

                numbers[numcount++] = atoll(numbuf);
            }
        }

        // Compute the problem answer
        long long result = (op == '*') ? 1 : 0;

        for (int i = 0; i < numcount; i++) {
            if (op == '*') result *= numbers[i];
            else result += numbers[i];
        }

        grand_total += result;

        col = end;  // Move to next block
    }

    printf("%lld\n", grand_total);

    // Free memory
    for (int i = 0; i < linecount; i++) free(lines[i]);

    return 0;
}
