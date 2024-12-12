#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

double calculate_average_iterative(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    double sum = 0;
    int count = 0;
    double num;

    while (fscanf(file, "%lf,", &num) == 1) {
        sum += num;
        count++;
    }

    fclose(file);
    return (count == 0) ? 0 : sum / count;
}

void process_csv_files_iterative() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    int file_count = 1;

    printf("\nPendekatan Iterative\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".csv")) {
            double average = calculate_average_iterative(entry->d_name);
            printf("%d. Rata-rata Data file %s = %.2f\n", file_count++, entry->d_name, average);
        }
    }

    closedir(dir);
}

int main() {
    process_csv_files_iterative();
    return 0;
}
