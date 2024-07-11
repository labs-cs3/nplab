#include <stdio.h>

int main() {
    FILE *fp;
    int c, blank_count = 0;

    // Open the file for reading
    fp = fopen("f1.txt", "r");

    // Check if file opened successfully
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read characters from the file
    while ((c = fgetc(fp)) != EOF) {
        // Check if the character is a blank space
        if (c == ' ') {
            blank_count++;
        }
    }

    // Close the file
    fclose(fp);

    // Print the number of blanks
    printf("Number of blanks in the file: %d\n", blank_count);

    return 0;
}
