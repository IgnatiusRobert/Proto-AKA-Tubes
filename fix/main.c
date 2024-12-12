#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MAX_LINE_LENGTH 1024

double getElapsedMilliseconds(struct timeval start, struct timeval end) {
  return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

double averageIterative(const char *filename, double *runtime) {
  struct timeval start, end;
  gettimeofday(&start, NULL);

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
  gettimeofday(&end, NULL);

  *runtime = getElapsedMilliseconds(start, end);
  return (count == 0) ? 0 : sum / count;
}

double averageRecursive(FILE *file, double sum, int count) {
  char line[MAX_LINE_LENGTH];

  if (fgets(line, sizeof(line), file) == NULL) {
    return (count == 0) ? 0 : sum / count;
  }

  double value;
  if (sscanf(line, "%lf", &value) == 1) {
    sum += value;
    count++;
  }

  return averageRecursive(file, sum, count);
}

double averageRecursiveWrapper(const char *filename, double *runtime) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Tidak dapat membuka file");
    return -1;
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);

  double result = averageRecursive(file, 0.0, 0);
  fclose(file);

  gettimeofday(&end, NULL);
  *runtime = getElapsedMilliseconds(start, end);

  return result;
}

int countLines(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Tidak dapat membuka file");
    return -1;
  }

  char line[MAX_LINE_LENGTH];
  int count = 0;

  while (fgets(line, sizeof(line), file)) {
    count++;
  }

  fclose(file);
  return count;
}

void processFile(const char *filename) {
  double runtime;

  int numData = countLines(filename);
  if (numData == -1) return;

  double avgIterative = averageIterative(filename, &runtime);
  printf("%s (%d data):\n", filename, numData);
  printf("Iteratif: %.2f, runtime: %.3f ms\n", avgIterative, runtime);

  double avgRecursive = averageRecursiveWrapper(filename, &runtime);
  printf("Rekursif: %.2f, runtime: %.3f ms\n\n", avgRecursive, runtime);
}

int main() {
  const char *filenames[] = {
    "data1.csv", "data2.csv", "data3.csv", 
    "data4.csv", "data5.csv", "data6.csv", 
    "data7.csv", "data8.csv", "data9.csv", "data10.csv"
  };
  int numFiles = sizeof(filenames) / sizeof(filenames[0]);

  for (int i = 0; i < numFiles; i++) {
    processFile(filenames[i]);
  }

  return 0;
}
