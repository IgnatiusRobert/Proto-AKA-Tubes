#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024

// Fungsi untuk menghitung rata-rata secara iteratif
double averageIterative(const char *filename, clock_t *runtime) {
  clock_t start = clock();  // Start time
  
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Tidak dapat membuka file");
    return -1;
  }

  char line[MAX_LINE_LENGTH];
  double sum = 0.0;
  int count = 0;

  while (fgets(line, sizeof(line), file)) {
    double value;
    if (sscanf(line, "%lf", &value) == 1) {
      sum += value;
      count++;
    }
  }

  fclose(file);
  
  *runtime = clock() - start;  // End time and calculate runtime
  return (count == 0) ? 0 : sum / count;  // Menghindari pembagian dengan nol
}

// Fungsi untuk menghitung rata-rata secara rekursif
double averageRecursive(FILE *file, double sum, int count, clock_t *runtime) {
  char line[MAX_LINE_LENGTH];

  // Membaca baris dari file
  if (fgets(line, sizeof(line), file) == NULL) {
    return (count == 0) ? 0 : sum / count;  // Menghindari pembagian dengan nol
  }

  double value;
  if (sscanf(line, "%lf", &value) == 1) {
    sum += value;
    count++;
  }

  return averageRecursive(file, sum, count, runtime);  // Rekursif
}

double averageRecursiveWrapper(const char *filename, clock_t *runtime) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Tidak dapat membuka file");
    return -1;
  }

  clock_t start = clock();  // Start time
  double result = averageRecursive(file, 0.0, 0, runtime);
  fclose(file);
  
  *runtime = clock() - start;  // End time and calculate runtime
  return result;
}

void processFile(const char *filename) {
  clock_t runtime;
  
  // Menghitung rata-rata secara iteratif
  double avgIterative = averageIterative(filename, &runtime);
  printf("%s:\n", filename);
  printf("Iteratif: %.2f, runtime: %.3f ms\n", avgIterative, (double)runtime / CLOCKS_PER_SEC * 1000);

  // Menghitung rata-rata secara rekursif
  double avgRecursive = averageRecursiveWrapper(filename, &runtime);
  printf("Rekursif: %.2f, runtime: %.3f ms\n\n", avgRecursive, (double)runtime / CLOCKS_PER_SEC * 1000);
}

int main() {
  const char *filenames[] = {"data1.csv", "data2.csv", "data3.csv"};
  int numFiles = sizeof(filenames) / sizeof(filenames[0]);

  for (int i = 0; i < numFiles; i++) {
    processFile(filenames[i]);
  }

  return 0;
}
