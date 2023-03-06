#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_NUM_STR 10

int main() {
    char* strings[MAX_NUM_STR];
    int num_strings = 0;

    printf("Enter up to %d strings, one per line:\n", MAX_NUM_STR);
    while (num_strings < MAX_NUM_STR) {
        char input[MAX_STR_LEN + 1];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // end of input or error
        }
        input[strcspn(input, "\n")] = '\0'; // remove trailing newline

        // Allocate memory for the string and copy it into the array
        char* new_str = malloc((strlen(input) + 1) * sizeof(char));
        if (new_str == NULL) {
            fprintf(stderr, "Error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy(new_str, input);
        strings[num_strings++] = new_str;
    }

    // Print the strings
    printf("You entered %d strings:\n", num_strings);
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }

    // Free the memory used by the strings
    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
    }

    return 0;
}

