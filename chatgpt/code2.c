#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_file(char* file_path, long int file_size);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Usage: %s <file_path> <file_size_in_bytes>\n", argv[0]);
        return 1;
    }

    char* file_path = argv[1];
    long int file_size = atol(argv[2]);

    if (file_size <= 0) {
        printf("Error: invalid file size specified.\n");
        return 1;
    }

    generate_random_file(file_path, file_size);

    printf("Random file of size %ld bytes written to %s.\n", file_size, file_path);

    return 0;
}

void generate_random_file(char* file_path, long int file_size)
{
    FILE* fp = fopen(file_path, "wb");

    if (fp == NULL) {
        printf("Error: could not open file for writing.");
        exit(1);
    }

    srand(time(NULL));

    char* buffer = (char*)malloc(file_size);

    for (long int i = 0; i < file_size; i++) {
        buffer[i] = (char)(rand() % 256);
    }

    fwrite(buffer, 1, file_size, fp);

    fclose(fp);

    free(buffer);
}

