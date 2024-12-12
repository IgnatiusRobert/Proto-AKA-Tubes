#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 1000
#define MAX_LINE_LENGTH 1024

// Function to read numbers from a CSV file
int read_csv(const char *filename, int *numbers) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    if (!fgets(line, MAX_LINE_LENGTH, file)) {
        fclose(file);
        return 0;
    }

    fclose(file);

    int count = 0;
    char *token = strtok(line, ",");
    while (token != NULL && count < MAX_NUMBERS) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, ",");
    }

    return count;
}

// Iterative function to calculate average
float calculate_average_iterative(int *numbers, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return count > 0 ? (float)sum / count : 0;
}

int main() {
    const char *filename = "data.csv";
    int numbers[MAX_NUMBERS];

    int count = read_csv(filename, numbers);
    if (count <= 0) {
        printf("Error reading numbers from file: %s\n", filename);
        return 1;
    }

    float average = calculate_average_iterative(numbers, count);
    printf("Iterative Average: %.2f\n", average);

    return 0;
}