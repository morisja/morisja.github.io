#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

int main() {
    char** strings = NULL;
    int num_strings = 0;
    int max_num_strings = 10;

    printf("Enter up to %d strings, one per line (or enter a blank line to stop):\n", max_num_strings);
    while (1) {
        char input[MAX_STR_LEN + 1];
        if (fgets(input, sizeof(input), stdin) == NULL || num_strings >= max_num_strings) {
            break; // end of input, error, or maximum number of strings reached
        }
        input[strcspn(input, "\n")] = '\0'; // remove trailing newline
        if (input[0] == '\0') {
            break; // blank line entered
        }

        // Allocate memory for the string and copy it into the array
        char* new_str = malloc((strlen(input) + 1) * sizeof(char));
        if (new_str == NULL) {
            fprintf(stderr, "Error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy(new_str, input);

        // Reallocate the strings array if needed
        if (num_strings >= max_num_strings) {
            max_num_strings *= 2;
            char** new_strings = realloc(strings, max_num_strings * sizeof(char*));
            if (new_strings == NULL) {
                fprintf(stderr, "Error: out of memory\n");
                exit(EXIT_FAILURE);
            }
            strings = new_strings;
        }

        // Add the new string to the array
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
    free(strings);

    return 0;
}

