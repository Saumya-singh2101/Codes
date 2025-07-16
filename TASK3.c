#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Compress file using Run-Length Encoding
void compressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("File error!\n");
        return;
    }

    char curr, prev;
    int count = 1;

    prev = fgetc(in);
    if (prev == EOF) {
        printf("Empty file.\n");
        fclose(in);
        fclose(out);
        return;
    }

    while ((curr = fgetc(in)) != EOF) {
        if (curr == prev) {
            count++;
        } else {
            fprintf(out, "%c%d", prev, count);
            prev = curr;
            count = 1;
        }
    }

    fprintf(out, "%c%d", prev, count);

    fclose(in);
    fclose(out);
    printf("Compression done. Output written to %s\n", outputFile);
}

// Decompress RLE-encoded file
void decompressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("File error!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (!isalpha(ch)) continue;

        char countStr[10];
        int i = 0;
        char digit;

        while ((digit = fgetc(in)) != EOF && isdigit(digit)) {
            countStr[i++] = digit;
        }
        countStr[i] = '\0';
        int count = atoi(countStr);

        for (int j = 0; j < count; j++) {
            fputc(ch, out);
        }

        if (digit != EOF)
            ungetc(digit, in); // put back non-digit
    }

    fclose(in);
    fclose(out);
    printf("Decompression done. Output written to %s\n", outputFile);
}

// Menu for compress/decompress
int main() {
    int choice;
    char inputFile[100], outputFile[100];

    while (1) {
        printf("\nRun-Length Encoding (RLE) Tool\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        getchar(); // consume newline
        switch (choice) {
            case 1:
                printf("Enter input file name: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;

                printf("Enter output (compressed) file name: ");
                fgets(outputFile, sizeof(outputFile), stdin);
                outputFile[strcspn(outputFile, "\n")] = 0;

                compressFile(inputFile, outputFile);
                break;

            case 2:
                printf("Enter input (compressed) file name: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;

                printf("Enter output (decompressed) file name: ");
                fgets(outputFile, sizeof(outputFile), stdin);
                outputFile[strcspn(outputFile, "\n")] = 0;

                decompressFile(inputFile, outputFile);
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
