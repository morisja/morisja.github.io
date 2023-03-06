#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char* file_name = "random_file.bin";
    char* file_path = "/path/to/file/random_file.bin";
    long int file_size = 5 * 1024 * 1024; // 5 megabytes

    FILE* fp = fopen(file_path, "wb");

    if (fp == NULL) {
        printf("Error: could not open file for writing.");
        return 1;
    }

    srand(time(NULL));

    char* buffer = (char*)malloc(file_size);

    for (long int i = 0; i < file_size; i++) {
        buffer[i] = (char)(rand() % 256);
    }

    fwrite(buffer, 1, file_size, fp);

    fclose(fp);

    free(buffer);

    printf("Random file of size %ld bytes written to %s.\n", file_size, file_path);

    return 0;
}

