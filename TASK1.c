#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char data[100];

    // -------- 1. Create and Write to File --------
    fp = fopen("demo.txt", "w"); // creates file if it doesn't exist
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter text to write to the file: ");
    fgets(data, sizeof(data), stdin);  // read input from user
    fputs(data, fp);                   // write to file
    fclose(fp);
    printf("Data written successfully.\n\n");

    // -------- 2. Read from File --------
    fp = fopen("demo.txt", "r");
    if (fp == NULL) {
        printf("Error reading file!\n");
        return 1;
    }

    printf("Reading from file:\n");
    while (fgets(data, sizeof(data), fp) != NULL) {
        printf("%s", data);
    }
    fclose(fp);
    printf("\n\n");

    // -------- 3. Append to File --------
    fp = fopen("demo.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for append!\n");
        return 1;
    }

    printf("Enter text to append: ");
    fgets(data, sizeof(data), stdin);
    fputs(data, fp);
    fclose(fp);
    printf("Data appended successfully.\n\n");

    // -------- 4. Final Read --------
    fp = fopen("demo.txt", "r");
    if (fp == NULL) {
        printf("Error reading file!\n");
        return 1;
    }

    printf("Final file content:\n");
    while (fgets(data, sizeof(data), fp) != NULL) {
        printf("%s", data);
    }
    fclose(fp);

    return 0;
}
