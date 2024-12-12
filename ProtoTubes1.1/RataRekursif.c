#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

double calculate_average_recursive(FILE *file, double sum, int count) {
    double num;
    if (fscanf(file, "%lf,", &num) != 1) {
        return (count == 0) ? 0 : sum / count;
    }
    return calculate_average_recursive(file, sum + num, count + 1);
}

double process_file_recursive(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    double average = calculate_average_recursive(file, 0, 0);
    fclose(file);
    return average;
}

void process_csv_files_recursive(DIR *dir, struct dirent *entry, int file_count) {
    if (!entry) return;

    if (strstr(entry->d_name, ".csv")) {
        double average = process_file_recursive(entry->d_name);
        printf("%d. Rata-rata Data file %s = %.2f\n", file_count, entry->d_name, average);
        process_csv_files_recursive(dir, readdir(dir), file_count + 1);
    } else {
        process_csv_files_recursive(dir, readdir(dir), file_count);
    }
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    printf("\nPendekatan Recursive: \n");

    struct dirent *entry = readdir(dir);
    process_csv_files_recursive(dir, entry, 1);

    closedir(dir);
    return 0;
}
